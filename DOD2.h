#pragma once
#include <vector>
#include <array>
#include <chrono>
#include <iostream>
#include "glm/vec3.hpp"
#include "glm/vec4.hpp"
#include "glm/gtx/normalize_dot.hpp"

using glm::vec3;
using glm::vec4;

struct DOD1Balls
{
	std::vector<vec3> poses;
	std::vector<vec4> colors;
	std::vector<float> dmgs;
	std::vector<vec3> aimdirections;
	std::vector<vec3> directions;
	std::vector<float> radiuses;
	std::vector<float> speeds;
	std::vector<float> hps;
	std::vector<vec3> cursorPoses;
	std::vector<size_t> targetIndexes;
	void Move()
	{
		for (size_t i = 0; i < poses.size(); ++i)
		{
			poses[i] += directions[i] * speeds[i];
		}
		for (size_t i = 0; i < aimdirections.size(); ++i)
		{
			aimdirections[i] += glm::normalize(cursorPoses[i] - poses[i]);
		}
	}

	void Attack()
	{
		for (size_t i = 0; i < hps.size(); ++i)
		{
			hps[targetIndexes[i]] -= dmgs[i];
		}
	}

	void Render(std::vector<std::array<float, 8>>& rendertarget)
	{
		for (size_t i = 0; i < poses.size(); ++i)
		{
			vec3& pos = poses[i];
			vec4& color = colors[i];
			rendertarget.push_back({
					pos.x, pos.y, pos.z,
					color.x, color.y, color.z, color.w,
					radiuses[i] });
		}
	}
};

void DOD1Test(int nr_of_balls, std::vector<std::array<float, 8>>& rendertarget)
{
	DOD1Balls balls;
	std::mt19937 rnd(701);
	std::uniform_real_distribution<float> rf(0.0f, 1.0f);
	for ( int i = 0; i < nr_of_balls; ++i )
	{
		balls.poses.push_back(glm::normalize(vec3(rf(rnd), rf(rnd), rf(rnd)) * 1000.0f));
		balls.colors.push_back(vec4(rf(rnd), rf(rnd), rf(rnd), rf(rnd)));
		balls.dmgs.push_back(rf(rnd));
		balls.aimdirections.push_back(glm::normalize(vec3(rf(rnd), rf(rnd), rf(rnd))));
		balls.directions.push_back(glm::normalize(vec3(rf(rnd), rf(rnd), rf(rnd))));
		balls.radiuses.push_back(rf(rnd));
		balls.speeds.push_back(rf(rnd) * 10.0f);
		balls.hps.push_back(rf(rnd) * 10.0f);
		balls.cursorPoses.push_back(glm::normalize(vec3(rf(rnd), rf(rnd), rf(rnd)) * 1000.0f));
		balls.targetIndexes.push_back(rnd() % nr_of_balls);
	}
	std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
	balls.Move();
	balls.Attack();
	balls.Render(rendertarget);
	std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
	std::cout << "DOD1 took " << std::chrono::duration_cast<std::chrono::milliseconds>( end - start ).count() << "ms" << std::endl;
}
