#include "CppGame.h"
#include <stdlib.h>

static float t = 0.0f;
static float d = 1;

float f(float x) {
	float a = 0.07f;
	return -2 * Square(a * x) * (a * x) + 3 * Square(a * x);
}

float g(float x) {
	return 50 * Sin(0.1f * x);
}

void FixedUpdate(Platform *p, float dt) {
	t += d * dt * 0.4f;
	t = Clamp(0, 1, t);
}

void UpdateAndRender(Platform *p, float dt, float alpha) {
	if (KeyIsPressed(p, KeyEscape)) {
		PlatformQuit(p);
	} 
	
	if (KeyIsPressed(p, KeySpace)) {
		d *= -1;
	}

	SetClearColor(.2f, .2f, .2f, 1);

	float half_w = 100 * p->AspectRatio;
	float half_h = 100;
	float dx = 0.1f;

	SetThickness(0.5f);

	BeginScene2D(-half_w, half_w, -half_h, half_h);

	DrawLine(Vec2(-ceilf(half_w), 0), Vec2(ceilf(half_w), 0), Vec4(1, 0, 0, 1));
	DrawLine(Vec2(0, -ceilf(half_h)), Vec2(0, ceilf(half_h)), Vec4(0, 1, 0, 1));

	{
		float py[3], y[3];

		float px = -ceilf(half_w);

		py[0] = f(px);
		py[1] = g(px);
		py[2] = Lerp(py[0], py[1], SmoothStep(0.0f, 1.0f, t));

		for (float x = px + dx; x < ceilf(half_w); x += dx) {
			y[0] = f(x);
			y[1] = g(x);
			y[2] = Lerp(y[0], y[1], SmoothStep(0.0f, 1.0f, t));

			DrawLine(Vec2(px, py[0]), Vec2(x, y[0]), Vec4(1, 1, 0, 0.5f));
			DrawLine(Vec2(px, py[1]), Vec2(x, y[1]), Vec4(1, 0, 1, 0.5f));
			DrawLine(Vec2(px, py[2]), Vec2(x, y[2]), Vec4(0, 1, 1, 1.0f));

			px = x;
			py[0] = y[0];
			py[1] = y[1];
			py[2] = y[2];
		}
	}

	EndScene2D();
}

CppGameCall void CppGameInitialize(Platform *platform, int argc, char **argv) {
	platform->Name = "Boids";
	platform->FixedUpdate = FixedUpdate;
	platform->UpdateAndRender = UpdateAndRender;
}
