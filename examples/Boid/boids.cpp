#include "CppGame.h"
#include <stdlib.h>
#include <time.h>

const uint32_t MAX_BOIDS = 200;

struct Boid {
	Vec2 Position;
	Vec2 Velocity;
};

struct CircularObstable {
	Vec2  Position;
	float Radius;
};

static Boid *boids;
static CircularObstable obstacles[5];

void FixedUpdate(Platform *p, float dt) {
	float view_distance = 30;
	float field_of_view = DegreesToRadians(120);

	float cohesion = 0.1f;
	float separation = 0.7f;
	float alignment = 0.5f;

	float RenderTargetWidth = p->RenderTargetWidth;
	float RenderTargetHeight = p->RenderTargetHeight;

	for (uint32_t i = 0; i < MAX_BOIDS; ++i) {
		auto boid = boids + i;

		Vec2     center(0);
		Vec2     separate(0);
		Vec2     velocity(0);
		uint32_t neighbours = 0;

		for (uint32_t j = 0; j < MAX_BOIDS; ++j) {
			if (i == j) continue;
			auto another = boids + j;

			if (Length(boid->Position - another->Position) <= view_distance &&
				AngleBetween(NormalizeChecked(boid->Velocity),
							 NormalizeChecked(another->Position - boid->Position)) <= field_of_view) {
				neighbours += 1;
				center += another->Position;
				velocity += another->Velocity;
				if (Length(boid->Position - another->Position) <= 20) {
					separate -= (another->Position - boid->Position);
				}
			}
		}

		if (neighbours) {
			center /= (float)neighbours;
			velocity /= (float)neighbours;
			boid->Velocity += (center - boid->Position) * cohesion + (velocity - boid->Velocity) * alignment;
		}

		boid->Velocity += separate * separation;

		float drag = 1;
		boid->Velocity *= Pow(0.5f, drag * dt);
		boid->Position += boid->Velocity * dt;

		//TODO: Do proper collision
		for (uint32_t index = 0; index < ArrayCount(obstacles); ++index) {
			if (LengthSq(boid->Position - obstacles[index].Position) <= Square(obstacles[index].Radius)) {
				float t = obstacles[index].Radius / Length(boid->Position - obstacles[index].Position);
				Vec2  tang = obstacles[index].Position - boid->Position;
				Vec2  norm = NormalizeChecked(Vec2(-tang.y, tang.x));
				boid->Position -= t * NormalizeChecked(tang);
				boid->Velocity = Reflect(boid->Velocity, norm);
			}
		}

		//TODO: Do proper collision
		if (boid->Position.x <= 0) {
			boid->Velocity.x *= -1;
			boid->Position.x = 0;
		}
		if (boid->Position.x >= RenderTargetWidth) {
			boid->Velocity.x *= -1;
			boid->Position.x = RenderTargetWidth;
		}
		if (boid->Position.y <= 0) {
			boid->Velocity.y *= -1;
			boid->Position.y = 0;
		}
		if (boid->Position.y >= RenderTargetHeight) {
			boid->Velocity.y *= -1;
			boid->Position.y = RenderTargetHeight;
		}
	}
}

void UpdateAndRender(Platform *p, float dt, float alpha) {
	if (KeyIsPressed(p, KeyEscape)) {
		PlatformQuit(p);
	}

	SetClearColor(.2f, .2f, .2f, 1);

	BeginScene2D(0, p->RenderTargetWidth, 0, p->RenderTargetHeight);

	Vec2 a(-1, -1);
	Vec2 b(-1, 1);
	Vec2 c(1.2f, 0);

	for (uint32_t index = 0; index < MAX_BOIDS; ++index) {
		auto  boid = boids + index;
		float angle = ArcTan2(boid->Velocity.y, boid->Velocity.x);
		Mat2  rot = RotationMat2(angle);
		Vec2  ta = rot * (a * 5) + boid->Position;
		Vec2  tb = rot * (b * 5) + boid->Position;
		Vec2  tc = rot * (c * 5) + boid->Position;
		DrawTriangle(ta, tb, tc, Vec4(0, 1, 1, 1));
	}

	for (uint32_t index = 0; index < ArrayCount(obstacles); ++index)
		DrawCircle(obstacles[index].Position, obstacles[index].Radius, Vec4(1));

	EndScene2D();
}

CppGameCall void CppGameInitialize(Platform *platform, int argc, char **argv) {
	platform->Name = "Boids";
	platform->FixedUpdate = FixedUpdate;
	platform->UpdateAndRender = UpdateAndRender;

	srand((uint32_t)time(0));

	boids = (Boid *)platform->Alloc(sizeof(Boid) * MAX_BOIDS);

	float w = platform->RenderTargetWidth;
	float h = platform->RenderTargetHeight;

	for (uint32_t index = 0; index < MAX_BOIDS; ++index) {
		auto b = boids + index;
		b->Position = Vec2(w * (float)((float)rand() / (float)RAND_MAX), (float)h * (float)((float)rand() / (float)RAND_MAX));
		b->Velocity = 100 * Vec2(2 * (float)((float)rand() / (float)RAND_MAX) - 1, 2 * (float)((float)rand() / (float)RAND_MAX) - 1);
	}

	obstacles[0].Position = 0.5f * Vec2(w, h);
	obstacles[0].Radius = 50;
	obstacles[1].Position = 0.25f * Vec2(w, h);
	obstacles[1].Radius = 55;
	obstacles[2].Position = 0.75f * Vec2(w, h);
	obstacles[2].Radius = 55;

	obstacles[3].Position = Vec2(0.25f * w, 0.75f * h);
	obstacles[3].Radius = 55;
	obstacles[4].Position = Vec2(0.75f * w, 0.25f * h);
	obstacles[4].Radius = 55;
}
