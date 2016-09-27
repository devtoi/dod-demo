//clang++ -O2 -std=c++14 % -o %:r && ./%:r
#include <iostream>
#include <vector>
#include <array>
#include <chrono>

struct OOPBall
{
	std::array<float, 3> pos;
	std::array<float, 4> color;
	std::array<float, 3> movement;
	float radius;
	void Update()
	{
		pos[0] += movement[0];
		pos[1] += movement[1];
		pos[2] += movement[2];
	}
	void Render(std::vector<std::array<float, 8>>& rendertarget)
	{
		rendertarget.push_back( {
				pos[0], pos[1], pos[2],
				color[0], color[1], color[2], color[3],
				radius } );
	}
};

int main()
{
	std::vector<OOPBall> oopballs;
	std::vector<std::array<float, 8>> rendertarget;
	for ( int i = 0; i < 1'000'000; ++i )
	{
		OOPBall ball;
		ball.pos = { 0.0f, (float)i, 0.0f };
		ball.movement = { (float)i, 0.0f, 0.0f };
		ball.color = { 1.0f, 0.0f, 1.0f, 1.0f };
		ball.radius = 1.0f;
		oopballs.push_back( ball );
	}
	std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
	for ( auto& ball : oopballs )
	{
		ball.Update();
	}
	for ( auto& ball : oopballs )
	{
		ball.Render(rendertarget);
	}
	std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
	std::cout << "OOP took " << std::chrono::duration_cast<std::chrono::milliseconds>( end - start ).count() << "ms" << std::endl;
	return 0;
}
