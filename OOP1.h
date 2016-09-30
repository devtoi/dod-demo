#pragma once
#include <vector>
#include <array>
#include <chrono>
#include <iostream>
#include <random>
#include "glm/vec3.hpp"
#include "glm/vec4.hpp"
#include "glm/gtx/normalize_dot.hpp"

using glm::vec3;
using glm::vec4;

struct OOP1Ball
{
	vec3 pos;
	vec4 color;
	float dmg;
	vec3 aimdirection;
	vec3 direction;
	float radius;
	float speed;
	float hp;
	vec3 cursorPos;
	size_t targetIndex;
	
	void Move()
	{
		aimdirection = glm::normalize(pos - cursorPos);
		pos += direction * speed;
	}

	void Attack(std::vector<OOP1Ball*>* balls)
	{
		balls->at(targetIndex)->hp -= dmg;
	}

	void Render(std::vector<std::array<float, 8>>& rendertarget)
	{
		rendertarget.push_back( {
				pos.x, pos.y, pos.z,
				color.x, color.y, color.z, color.w,
				radius } );
	}
};

void OOP1Test(int nr_of_balls, std::vector<std::array<float, 8>>& rendertarget)
{
	std::vector<OOP1Ball*> oopballs;
	std::vector<OOP1Ball*> oopballsNotUsed;
	std::mt19937 rndnotused(701);
	std::mt19937 rnd(701);
	std::uniform_real_distribution<float> rf(0.0f, 1.0f);
	for (int i = 0; i < nr_of_balls; ++i)
	{
		{
			OOP1Ball* ball = new OOP1Ball();
			ball->pos = glm::normalize(vec3(rf(rnd), rf(rnd), rf(rnd)) * 1000.0f);
			ball->color = vec4( rf(rnd), rf(rnd), rf(rnd), rf(rnd) );
			ball->direction = glm::normalize(vec3(rf(rnd), rf(rnd), rf(rnd)));
			ball->aimdirection = glm::normalize(vec3(rf(rnd), rf(rnd), rf(rnd)));
			ball->cursorPos = glm::normalize(vec3(rf(rnd), rf(rnd), rf(rnd)) * 1000.0f);
			ball->radius = rf(rnd);
			ball->speed = rf(rnd) * 10.0f;
			ball->dmg = rf(rnd);
			ball->hp = rf(rnd) * 10.0f;
			ball->targetIndex = rnd() % nr_of_balls;
			oopballs.push_back(ball);
		}
		{
			OOP1Ball* ball = new OOP1Ball();
			ball->pos = glm::normalize(vec3(rf(rndnotused), rf(rndnotused), rf(rndnotused)) * 1000.0f);
			ball->direction = glm::normalize(vec3(rf(rndnotused), rf(rndnotused), rf(rndnotused)));
			ball->color = vec4( rf(rndnotused), rf(rndnotused), rf(rndnotused), rf(rndnotused) );
			ball->radius = rf(rndnotused);
			ball->speed = rf(rndnotused) * 10.0f;
			ball->dmg = rf(rndnotused);
			ball->hp = rf(rndnotused) * 10.0f;
			oopballsNotUsed.push_back(ball);
		}
		{
			OOP1Ball* ball = new OOP1Ball();
			ball->pos = glm::normalize(vec3(rf(rndnotused), rf(rndnotused), rf(rndnotused)) * 1000.0f);
			ball->direction = glm::normalize(vec3(rf(rndnotused), rf(rndnotused), rf(rndnotused)));
			ball->color = vec4( rf(rndnotused), rf(rndnotused), rf(rndnotused), rf(rndnotused) );
			ball->radius = rf(rndnotused);
			ball->speed = rf(rndnotused) * 10.0f;
			ball->dmg = rf(rndnotused);
			ball->hp = rf(rndnotused) * 10.0f;
			oopballsNotUsed.push_back(ball);
		}
		{
			OOP1Ball* ball = new OOP1Ball();
			ball->pos = glm::normalize(vec3(rf(rndnotused), rf(rndnotused), rf(rndnotused)) * 1000.0f);
			ball->direction = glm::normalize(vec3(rf(rndnotused), rf(rndnotused), rf(rndnotused)));
			ball->color = vec4( rf(rndnotused), rf(rndnotused), rf(rndnotused), rf(rndnotused) );
			ball->radius = rf(rndnotused);
			ball->speed = rf(rndnotused) * 10.0f;
			ball->dmg = rf(rndnotused);
			ball->hp = rf(rndnotused) * 10.0f;
			oopballsNotUsed.push_back(ball);
		}
	}

	std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
	for ( auto& ball : oopballs )
	{
		ball->Move();
	}
	for ( auto& ball : oopballs )
	{
		ball->Attack(&oopballs);
	}
	for ( auto& ball : oopballs )
	{
		ball->Render(rendertarget);
	}
	std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
	std::cout << "OOP1 took " << std::chrono::duration_cast<std::chrono::milliseconds>( end - start ).count() << "ms" << std::endl;
	for ( auto& ball : oopballs )
	{
		delete ball;
	}
	for ( auto& ball : oopballsNotUsed )
	{
		delete ball;
	}
}