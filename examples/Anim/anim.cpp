#include "CppGame.h"
#include <stdlib.h>

namespace CppAnim {

struct CurveEquation {
	virtual float F(float x) = 0;
};

struct Animation {
	float Time = 0.0f;
	float Factor = 1;
	float Delta = 1;
	Vec4 Colors[3] = { };
};

void UpdateAnimation(Animation *anim, float dt) {
	anim->Time += dt * anim->Factor;
	anim->Time = Clamp(0, 1, anim->Time);
}

void ReverseAnimation(Animation *anim) {
	anim->Factor *= -1;
}

void Animate(Animation *anim, float x0, float x1, CurveEquation *a, CurveEquation *b) {
	float py[3], y[3];

	float px = x0;

	py[0] = a->F(px);
	py[1] = b->F(px);
	py[2] = Lerp(py[0], py[1], SmoothStep(0.0f, 1.0f, anim->Time));

	for (float x = px + anim->Delta; x < x1; x += anim->Delta) {
		y[0] = a->F(x);
		y[1] = b->F(x);
		y[2] = Lerp(y[0], y[1], SmoothStep(0.0f, 1.0f, anim->Time));

		DrawLine(Vec2(px, py[0]), Vec2(x, y[0]), anim->Colors[0]);
		DrawLine(Vec2(px, py[1]), Vec2(x, y[1]), anim->Colors[1]);
		DrawLine(Vec2(px, py[2]), Vec2(x, y[2]), anim->Colors[2]);

		px = x;
		py[0] = y[0];
		py[1] = y[1];
		py[2] = y[2];
	}
}

//
//
//

struct Bezier2 : public CurveEquation {
	float Strength = 1;
	virtual float F(float x) override {
		return -2 * Square(Strength * x) * (Strength * x) + 3 * Square(Strength * x);
	}
};

struct SinWave : public CurveEquation {
	float Amplitude = 1;
	float Frequency = 1;
	virtual float F(float x) override {
		return Amplitude * Sin(Frequency * x);
	}
};

static Animation g_Animation;
static Bezier2 g_Bezier2;
static SinWave g_SinWave;

void FixedUpdate(Platform *p, float dt) {
	UpdateAnimation(&g_Animation, dt);
}

void UpdateAndRender(Platform *p, float dt, float alpha) {
	if (KeyIsPressed(p, Key_Escape)) {
		PlatformQuit(p);
	}

	if (KeyIsPressed(p, Key_Space)) {
		ReverseAnimation(&g_Animation);
	}

	SetThickness(0.5f);
	SetClearColor(.2f, .2f, .2f, 1);

	float half_w = 100 * p->AspectRatio, half_h = 100;

	BeginScene2D(-half_w, half_w, -half_h, half_h);
	// Co-ordinates
	DrawLine(Vec2(-ceilf(half_w), 0), Vec2(ceilf(half_w), 0), Vec4(1, 0, 0, 1));
	DrawLine(Vec2(0, -ceilf(half_h)), Vec2(0, ceilf(half_h)), Vec4(0, 1, 0, 1));
	// Curves
	Animate(&g_Animation, -ceilf(half_w), ceilf(half_w), &g_Bezier2, &g_SinWave);

	EndScene2D();
}

bool OnLoad(Platform *p) {
	g_Animation.Time = 0;
	g_Animation.Factor = 0.4f;
	g_Animation.Delta = 0.1f;
	g_Animation.Colors[0] = Vec4(1, 1, 0, 0.5f);
	g_Animation.Colors[1] = Vec4(1, 0, 1, 0.5f);
	g_Animation.Colors[2] = Vec4(0, 1, 1, 1.0f);

	g_Bezier2.Strength = 0.07f;
	g_SinWave.Amplitude = 50;
	g_SinWave.Frequency = 0.1f;

	return true;
}

}

#if !defined(CPP_EXAMPLE_MENU)

CppGameCall void CppGameInitialize(Platform *platform, int argc, char **argv) {
	platform->Name = "Anim";
	platform->OnLoad = CppAnim::OnLoad;
	platform->FixedUpdate = CppAnim::FixedUpdate;
	platform->UpdateAndRender = CppAnim::UpdateAndRender;
}

#endif
