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

struct RenderComponent
{
	vec4 color;
	float radious;
};

struct MovementComponent
{
	vec3 direction;
	float speed;
};

struct AimDirectionComponent
{
	vec3 aimdirection;
	vec3 cursorPos;
};

struct AttackComponent
{
	size_t targetIndex;
	float dmg;
};

struct DOD2Balls
{
	std::vector<vec3> poses;
	std::vector<RenderComponent> renderComponents;
	std::vector<AimDirectionComponent> aimdirections;
	std::vector<MovementComponent> movementComponents;
	std::vector<AttackComponent> attackComponents;
	std::vector<float> hps;

	void Move()
	{
		for (size_t i = 0; i < poses.size(); ++i)
		{
			MovementComponent& move = movementComponents[i];
			poses[i] += move.direction * move.speed;
		}
		for (size_t i = 0; i < aimdirections.size(); ++i)
		{
			AimDirectionComponent& aim = aimdirections[i];
			aim.aimdirection = glm::normalize(aim.cursorPos - poses[i]);
		}
	}

	void Attack()
	{
		for (size_t i = 0; i < hps.size(); ++i)
		{
			AttackComponent& attack = attackComponents[i];
			hps[attack.targetIndex] -= attack.dmg;
		}
	}

	void Render(std::vector<std::array<float, 8>>& rendertarget)
	{
		for (size_t i = 0; i < poses.size(); ++i)
		{
			vec3& pos = poses[i];
			RenderComponent& render = renderComponents[i];
			rendertarget.push_back({
					pos.x, pos.y, pos.z,
					render.color.x, render.color.y, render.color.z, render.color.w,
					render.radious });
		}
	}
};

void DOD2Test(int nr_of_balls, std::vector<std::array<float, 8>>& rendertarget)
{
	DOD2Balls balls;
	std::mt19937 rnd(701);
	std::uniform_real_distribution<float> rf(0.0f, 1.0f);
	for ( int i = 0; i < nr_of_balls; ++i )
	{
		balls.poses.push_back(glm::normalize(vec3(rf(rnd), rf(rnd), rf(rnd)) * 1000.0f));
		balls.renderComponents.push_back(RenderComponent{vec4(rf(rnd), rf(rnd), rf(rnd), rf(rnd)), rf(rnd)});
		balls.movementComponents.push_back(MovementComponent{glm::normalize(vec3(rf(rnd), rf(rnd), rf(rnd))), rf(rnd) * 10.0f});
		balls.aimdirections.push_back(AimDirectionComponent{ glm::normalize(vec3(rf(rnd), rf(rnd), rf(rnd))),  glm::normalize(vec3(rf(rnd), rf(rnd), rf(rnd)) * 1000.0f) });
		balls.hps.push_back(rf(rnd) * 10.0f);
		balls.attackComponents.push_back(AttackComponent{ rnd() % nr_of_balls, rf(rnd) });
	}
	std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
	balls.Move();
	balls.Attack();
	balls.Render(rendertarget);
	std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
	std::cout << "DOD2 took " << std::chrono::duration_cast<std::chrono::milliseconds>( end - start ).count() << "ms" << std::endl;
}
