#pragma once
#include <vector>
#include <array>
#include <chrono>
#include <iostream>

struct DOD1Balls
{
	std::vector<std::array<float, 3>> poses;
	std::vector<std::array<float, 4>> colors;
	std::vector<std::array<float, 3>> movements;
	std::vector<float> radiuses;
	void Update()
	{
		for (size_t i = 0; i < poses.size(); ++i)
		{
			std::array<float, 3>& pos = poses[i];
			std::array<float, 3>& movement = movements[i];
			pos[0] += movement[0];
			pos[1] += movement[1];
			pos[2] += movement[2];
		}
	}
	void Render(std::vector<std::array<float, 8>>& rendertarget)
	{
		for (size_t i = 0; i < poses.size(); ++i)
		{
			std::array<float, 3>& pos = poses[i];
			std::array<float, 4>& color = colors[i];
			rendertarget.push_back({
					pos[0], pos[1], pos[2],
					color[0], color[1], color[2], color[3],
					radiuses[i] });
		}
	}
};

void DOD1Test(int nr_of_balls, std::vector<std::array<float, 8>>& rendertarget)
{
	DOD1Balls balls;
	for ( int i = 0; i < nr_of_balls; ++i )
	{
		balls.poses.push_back({ 0.0f, (float)i, 0.0f });
		balls.movements.push_back({ (float)i, 0.0f, 0.0f });
		balls.colors.push_back({ 1.0f, 0.0f, 1.0f, 1.0f });
		balls.radiuses.push_back(1.0f);
	}
	std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
	balls.Update();
	balls.Render(rendertarget);
	std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
	std::cout << "DOD1 took " << std::chrono::duration_cast<std::chrono::milliseconds>( end - start ).count() << "ms" << std::endl;
}