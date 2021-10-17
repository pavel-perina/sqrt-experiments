/*
Some links:
	http://graphics.stanford.edu/~seander/bithacks.html
	https://stackoverflow.com/questions/34652001/how-to-get-a-square-root-for-32-bit-input-in-one-clock-cycle-only
	https://stackoverflow.com/questions/31117497/fastest-integer-square-root-in-the-least-amount-of-instructions
	https://en.wikipedia.org/wiki/Methods_of_computing_square_roots
*/
#include <cstdint>
#include <string>
#include <iostream>
#include <chrono>
#include <cmath>
#include <vector>
#include <sstream>

// https://stackoverflow.com/a/31118777/5294293


/***********************************************************************************/
// https://stackoverflow.com/a/56717339/5294293
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

/***********************************************************************************/

/*
// Integer Square Root function
// Contributors include Arne Steinarson for the basic approximation idea,
// Dann Corbit and Mathew Hendry for the first cut at the algorithm,
// Lawrence Kirby for the rearrangement, improvments and range optimization
// and Paul Hsieh for the round-then-adjust idea.
*/
static uint32_t fred_sqrt(uint32_t x) {
	static const uint8_t sqq_table[] = {
	   0,  16,  22,  27,  32,  35,  39,  42,  45,  48,  50,  53,  55,  57,
	  59,  61,  64,  65,  67,  69,  71,  73,  75,  76,  78,  80,  81,  83,
	  84,  86,  87,  89,  90,  91,  93,  94,  96,  97,  98,  99, 101, 102,
	 103, 104, 106, 107, 108, 109, 110, 112, 113, 114, 115, 116, 117, 118,
	 119, 120, 121, 122, 123, 124, 125, 126, 128, 128, 129, 130, 131, 132,
	 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143, 144, 144, 145,
	 146, 147, 148, 149, 150, 150, 151, 152, 153, 154, 155, 155, 156, 157,
	 158, 159, 160, 160, 161, 162, 163, 163, 164, 165, 166, 167, 167, 168,
	 169, 170, 170, 171, 172, 173, 173, 174, 175, 176, 176, 177, 178, 178,
	 179, 180, 181, 181, 182, 183, 183, 184, 185, 185, 186, 187, 187, 188,
	 189, 189, 190, 191, 192, 192, 193, 193, 194, 195, 195, 196, 197, 197,
	 198, 199, 199, 200, 201, 201, 202, 203, 203, 204, 204, 205, 206, 206,
	 207, 208, 208, 209, 209, 210, 211, 211, 212, 212, 213, 214, 214, 215,
	 215, 216, 217, 217, 218, 218, 219, 219, 220, 221, 221, 222, 222, 223,
	 224, 224, 225, 225, 226, 226, 227, 227, 228, 229, 229, 230, 230, 231,
	 231, 232, 232, 233, 234, 234, 235, 235, 236, 236, 237, 237, 238, 238,
	 239, 240, 240, 241, 241, 242, 242, 243, 243, 244, 244, 245, 245, 246,
	 246, 247, 247, 248, 248, 249, 249, 250, 250, 251, 251, 252, 252, 253,
	 253, 254, 254, 255
	};

	uint32_t xn;

	if (x >= 0x10000)
		if (x >= 0x1000000)
			if (x >= 0x10000000)
				if (x >= 0x40000000) {
					if (x >= 65535UL * 65535UL)
						return 65535;
					xn = sqq_table[x >> 24] << 8;
				}
				else
					xn = sqq_table[x >> 22] << 7;
			else
				if (x >= 0x4000000)
					xn = sqq_table[x >> 20] << 6;
				else
					xn = sqq_table[x >> 18] << 5;
		else {
			if (x >= 0x100000)
				if (x >= 0x400000)
					xn = sqq_table[x >> 16] << 4;
				else
					xn = sqq_table[x >> 14] << 3;
			else
				if (x >= 0x40000)
					xn = sqq_table[x >> 12] << 2;
				else
					xn = sqq_table[x >> 10] << 1;

			goto nr1;
		}
	else
		if (x >= 0x100) {
			if (x >= 0x1000)
				if (x >= 0x4000)
					xn = (sqq_table[x >> 8] >> 0) + 1;
				else
					xn = (sqq_table[x >> 6] >> 1) + 1;
			else
				if (x >= 0x400)
					xn = (sqq_table[x >> 4] >> 2) + 1;
				else
					xn = (sqq_table[x >> 2] >> 3) + 1;

			goto adj;
		}
		else
			return sqq_table[x] >> 4;

	/* Run two iterations of the standard convergence formula */

	xn = (xn + 1 + x / xn) / 2;
nr1:
	xn = (xn + 1 + x / xn) / 2;
adj:

	if (xn * xn > x) /* Correct rounding if necessary */
		xn--;

	return xn;
}

/***********************************************************************************/


static const uint8_t clz_tab[32] = {
	31, 22, 30, 21, 18, 10, 29,  2, 20, 17, 15, 13, 9,  6, 28, 1,
	23, 19, 11,  3, 16, 14,  7, 24, 12,  4,  8, 25, 5, 26, 27, 0 };

uint8_t clz(uint32_t a)
{
	a |= a >> 16;
	a |= a >> 8;
	a |= a >> 4;
	a |= a >> 2;
	a |= a >> 1;
	return clz_tab[0x07c4acdd * a >> 27];
}

/* 16 x 16 -> 32 bit unsigned multiplication; should be single instruction */
uint32_t umul16w(uint16_t a, uint16_t b)
{
	return (uint32_t)a * b;
}

/* Reza Hashemian, "Square Rooting Algorithms for Integer and Floating-Point
   Numbers", IEEE Transactions on Computers, Vol. 39, No. 8, Aug. 1990, p. 1025
*/
uint16_t isqrt2(uint32_t x)
{
	volatile uint16_t y, z, lsb, mpo, mmo, lz, t;

	if (x == 0) return x; // early out, code below can't handle zero

	lz = clz(x);         // #leading zeros, 32-lz = #bits of argument
	lsb = lz & 1;
	mpo = 17 - (lz >> 1); // m+1, result has roughly half the #bits of argument
	mmo = mpo - 2;        // m-1
	t = 1 << mmo;         // power of two for two's complement of initial guess
	y = t - (x >> (mpo - lsb)); // initial guess for sqrt
	t = t + t;            // power of two for two's complement of result
	z = y;

	y = (umul16w(y, y) >> mpo) + z;
	y = (umul16w(y, y) >> mpo) + z;
	if (x >= 0x40400) {
		y = (umul16w(y, y) >> mpo) + z;
		y = (umul16w(y, y) >> mpo) + z;
		if (x >= 0x1002000) {
			y = (umul16w(y, y) >> mpo) + z;
			y = (umul16w(y, y) >> mpo) + z;
		}
	}

	y = t - y; // raw result is 2's complement of iterated solution
	y = y - umul16w(lsb, (umul16w(y, 19195) >> 16)); // mult. by sqrt(0.5) 

	if ((int32_t)(x - umul16w(y, y)) < 0) y--; // iteration may overestimate 
	if ((int32_t)(x - umul16w(y, y)) < 0) y--; // result, adjust downward if 
	if ((int32_t)(x - umul16w(y, y)) < 0) y--; // necessary 

	return y; // (int)sqrt(x)
}

static const uint16_t sqrt_tab[32] =
{ 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
  0x85ff, 0x8cff, 0x94ff, 0x9aff, 0xa1ff, 0xa7ff, 0xadff, 0xb3ff,
  0xb9ff, 0xbeff, 0xc4ff, 0xc9ff, 0xceff, 0xd3ff, 0xd8ff, 0xdcff,
  0xe1ff, 0xe6ff, 0xeaff, 0xeeff, 0xf3ff, 0xf7ff, 0xfbff, 0xffff
};

/* 32/16->16 bit division. Note: Will overflow if x[31:16] >= y */
uint16_t udiv_32_16(uint32_t x, uint16_t y)
{
	uint16_t r = x / y;
	return r;
}

/* table lookup for initial guess followed by division-based Newton iteration*/
uint16_t isqrt3(uint32_t x)
{
	volatile uint16_t q, lz, y, i, xh;

	if (x == 0) return x; // early out, code below can't handle zero

	// initial guess based on leading 5 bits of argument normalized to 2.30
	lz = clz(x);
	i = ((x << (lz & ~1)) >> 27);
	y = sqrt_tab[i] >> (lz >> 1);
	xh = (x >> 16); // needed for overflow check on division

	// first Newton iteration, guard against overflow in division
	q = 0xffff;
	if (xh < y) q = udiv_32_16(x, y);
	y = (q + y) >> 1;
	if (lz < 10) {
		// second Newton iteration, guard against overflow in division
		q = 0xffff;
		if (xh < y) q = udiv_32_16(x, y);
		y = (q + y) >> 1;
	}

	if (umul16w(y, y) > x) y--; // adjust quotient if too large

	return y; // (int)sqrt(x)
}

/***********************************************************************************/

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
	const int n_passes = 10'000'000;
	std::vector<uint32_t> results(n_passes);
	auto t = high_resolution_clock::now();
	for (int i = 0; i < n_passes; ++i) {
		results[i] = fn(i);
	}
	return duration<double, std::milli>(high_resolution_clock::now() - t).count();
}

double measure_time16(uint16_t(*fn)(uint32_t))
{
	using std::chrono::high_resolution_clock;
	using std::chrono::duration;
	const int n_passes = 10'000'000;
	std::vector<uint16_t> results(n_passes);
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
		std::cout << cmp << ",isqrt1,"      << std::to_string(measure_time(isqrt1)) << "\n";
		std::cout << cmp << ",isqrt2,"      << std::to_string(measure_time16(isqrt2)) << "\n";
		std::cout << cmp << ",isqrt3,"      << std::to_string(measure_time16(isqrt3)) << "\n";
		std::cout << cmp << ",fred_sqrt,"   << std::to_string(measure_time(fred_sqrt)) << "\n";
		std::cout << cmp << ",double_sqrt," << std::to_string(measure_time(double_sqrt)) << "\n";
		std::cout << cmp << ",float_sqrt,"  << std::to_string(measure_time(float_sqrt)) << "\n";
		std::cout << cmp << ",noop,"        << std::to_string(measure_time(noop)) << "\n";
	}
	return 0;
}

