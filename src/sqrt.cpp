// http://graphics.stanford.edu/~seander/bithacks.html

#include <cstdint>
#include <string>
#include <iostream>
#include <chrono>
#include <cmath>
#include <vector>
#include <sstream>

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


double measure_time(uint32_t(*fn)(uint32_t)) 
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
	return duration<double, std::milli>(high_resolution_clock::now() - t).count();
}

std::string get_compiler() 
{
	std::ostringstream oss;
#if defined(__clang__)
	oss << "clang " << __clang_version__ ;
#elif defined(__GNUC__) || defined(__GNUG__)
	oss << "gnuc " << __GNUC__ << "." << __GNUC_MINOR__ << "." << __GNUC_PATCHLEVEL__ ;
#elif defined(_MSC_VER)
	oss << "msc " << _MSC_FULL_VER ;
#endif
	return oss.str();
}

int main(int argc, char **argv)
{
	std::string cmp = get_compiler();
	for (int i=5; i-->0;) {
		std::cout << "\"" << cmp << "\", \"isqrt1\", "      << std::to_string(measure_time(isqrt1)) << "\n";
		std::cout << "\"" << cmp << "\", \"double_sqrt\", " << std::to_string(measure_time(double_sqrt)) << "\n";
		std::cout << "\"" << cmp << "\", \"float_sqrt\", "  << std::to_string(measure_time(float_sqrt)) << "\n";
		std::cout << "\"" << cmp << "\", \"noop\", "        << std::to_string(measure_time(noop)) << "\n";
	}
	return 0;
}

