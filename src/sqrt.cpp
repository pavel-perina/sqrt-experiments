// http://graphics.stanford.edu/~seander/bithacks.html

#include <cstdint>
#include <string>
#include <iostream>
#include <chrono>
#include <cmath>
#include <vector>

uint32_t isqrt1(uint32_t x) 
{
	uint32_t r = 0, r2 = 0;
	for (int p = 15; p >= 0; --p) {
		uint32_t tr2 = r2 + (r << (p + 1)) + (1u << (p + p));
		if (tr2 <= x) {
			r2 = tr2;
			r |= (1u << p);
		}
	}
	return r;
}


uint32_t double_sqrt(uint32_t a)
{
	return (uint32_t)sqrt((double)a);
}


uint32_t float_sqrt(uint32_t a)
{
	return (uint32_t)sqrtf((float)a);
}


uint32_t noop(uint32_t a)
{
	return 0;
}


void measure(const std::string &name, uint32_t(*fn)(uint32_t) ) 
{
	using std::chrono::high_resolution_clock;
	using std::chrono::duration;
	uint32_t a = 666;		// 25.8
	const int n_passes = 10'000'000;
	std::vector<uint32_t> results(n_passes);
	auto t = high_resolution_clock::now();
	for (int i = 0; i < n_passes; ++i) {
		results[i] = fn(i);
	}
	std::cout << name << duration<double, std::milli>(high_resolution_clock::now() - t).count() << "ms\n";
}

void print_compiler() 
{
	std::cout << "Compiler: ";
#if defined(__clang__)
	std::cout << "clang " << __clang_version__ << "\n";
#elif defined(__GNUC__) || defined(__GNUG__)
	std::cout << "gnuc " << __GNUC__ << "." << __GNUC_MINOR__ << "." << __GNUC_PATCHLEVEL__ << "\n";
#elif defined(_MSC_VER)
	std::cout << "msc " << _MSC_FULL_VER << "\n";
#endif

}

int main(int argc, char **argv)
{
	print_compiler();
	for (int i=5; i-->0;) {
		measure("isqrt1 | ", isqrt1);
		measure("double | ", double_sqrt);
		measure("float  | ", float_sqrt);
		measure("noop   | ", noop);
	}
	return 0;
}

