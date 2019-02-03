#pragma once

class PerlinNoise
{
public:
	PerlinNoise() = default;
	virtual ~PerlinNoise() = default;
	// Make objects non-copyable
	// https://msdn.microsoft.com/en-us/library/dn457344.aspx 
	PerlinNoise(const PerlinNoise&) = delete;
	PerlinNoise& operator=(const PerlinNoise&) = delete;

	std::vector<std::vector<int>> generatePerlinNoise(unsigned int seed, int width, int height, int depth = 255);

private:
	std::vector<int> generatePermutationVec(unsigned int seed);
	double noise(std::vector<int> &permutation, double x, double y, double z);
	double fade(double t);
	double lerp(double t, double a, double b);
	double grad(int hash, double x, double y, double z);
};
