#include "../stdafx.h"		
#include "PerlinNoise.h"
#include <numeric>
#include <random>

std::vector<std::vector<int>> PerlinNoise::generatePerlinNoise(const unsigned int seed, const int width, const int height, const int depth)
{
	auto permutationVector = generatePermutationVec(seed);
	std::vector<std::vector<int>> res(height, std::vector<int>(width, 0));

	// Visit every x, y coordinate and assign a z value
	for (auto i = 0; i < height; ++i) {
		for (auto j = 0; j < width; ++j) {
			const auto x = double(j) / double(width);
			const auto y = double(i) / double(height);

			const auto n = noise(permutationVector, x * 10, y * 10, 0.8);
			res[i][j] = int(round(n * depth));
		}
	}

	return res;
}

std::vector<int> PerlinNoise::generatePermutationVec(const unsigned int seed)
{
	std::vector<int> p(256);
	std::iota(p.begin(), p.end(), 0);

	std::default_random_engine engine(seed);
	std::shuffle(p.begin(), p.end(), engine);

	p.insert(p.end(), p.begin(), p.end());
	return p;
}

double PerlinNoise::noise(std::vector<int> &permutation, double x, double y, double z)
{
	const auto flooredX = floor(x);
	const auto flooredY = floor(y);
	const auto flooredZ = floor(z);

	const auto unitX = int(flooredX) & 255;
	const auto unitY = int(flooredY) & 255;
	const auto unitZ = int(flooredZ) & 255;

	const auto a = permutation[unitX] + unitY;
	const auto aa = permutation[a] + unitZ;
	const auto ab = permutation[a + 1] + unitZ;
	const auto b = permutation[unitX + 1] + unitY;
	const auto ba = permutation[b] + unitZ;
	const auto bb = permutation[b + 1] + unitZ;

	x -= flooredX;
	y -= flooredY;
	z -= flooredZ;

	const auto u = fade(x);
	const auto v = fade(y);
	const auto w = fade(z);

	const auto res = lerp(
		w,
		lerp(v, lerp(u, grad(permutation[aa], x, y, z),
			grad(permutation[ba], x - 1, y, z)),
			lerp(u, grad(permutation[ab], x, y - 1, z),
				grad(permutation[bb], x - 1, y - 1, z))),
		lerp(v, lerp(u, grad(permutation[aa + 1], x, y, z - 1),
			grad(permutation[ba + 1], x - 1, y, z - 1)),
			lerp(u, grad(permutation[ab + 1], x, y - 1, z - 1),
				grad(permutation[bb + 1], x - 1, y - 1, z - 1)
			)
		)
	);
	return (res + 1.0) / 2.0;
}

double PerlinNoise::fade(const double t)
{
	return std::pow(t, 3) * (t * (t * 6 - 15) + 10);
}

double PerlinNoise::lerp(const double t, const double a, const double b)
{
	return a + t * (b - a);
}

double PerlinNoise::grad(const int hash, const double x, const double y, const double z)
{
	const auto h = hash & 15;
	// Convert lower 4 bits of hash into 12 gradient directions
	const auto u = h < 8 ? x : y;
	const auto v = h < 4 ? y : h == 12 || h == 14 ? x : z;

	return ((h & 1) == 0 ? u : -u) + ((h & 2) == 0 ? v : -v);
}
