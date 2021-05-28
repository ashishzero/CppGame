#include "CppGame.h"

#define CPP_EXAMPLE_MENU
#include "../Boid/boids.cpp"
#include "../Anim/anim.cpp"

namespace CppUi {

static uint32_t g_Banner;
static float g_BannerWidth;
static float g_BannerHeight;

constexpr float BANNER_OFFSET_Y = 50;

static Vec2 g_BannerPos;
static Vec2 g_BannerDim;
static Vec2 g_BannerTargetPos;
static Vec2 g_BannerTargetDim;
static float g_BannerMovementTime;

enum DispState {
	DispState_Menu,
	DispState_Boid,
	DispState_Anim,
};

static DispState g_DispState = DispState_Menu;

void ResetBannerPosDimMid(float w, float h) {
	g_BannerPos = Lerp(g_BannerPos, g_BannerTargetPos, SmoothStep(0.0f, 1.0f, g_BannerMovementTime));
	g_BannerDim = Lerp(g_BannerDim, g_BannerTargetDim, SmoothStep(0.0f, 1.0f, g_BannerMovementTime));

	g_BannerMovementTime = 0;

	g_BannerTargetDim = 0.4f * Vec2(g_BannerWidth, g_BannerHeight);
	g_BannerTargetPos.x = 0.5f * (w - g_BannerTargetDim.x);
	g_BannerTargetPos.y = h < g_BannerTargetDim.y ? 0.0f : BANNER_OFFSET_Y;
}

void ResetBannerPosDimTopLeft() {
	g_BannerPos = Lerp(g_BannerPos, g_BannerTargetPos, SmoothStep(0.0f, 1.0f, g_BannerMovementTime));
	g_BannerDim = Lerp(g_BannerDim, g_BannerTargetDim, SmoothStep(0.0f, 1.0f, g_BannerMovementTime));

	g_BannerMovementTime = 0;

	g_BannerTargetDim = 0.15f * Vec2(g_BannerWidth, g_BannerHeight);
	g_BannerTargetPos.x = 5;
	g_BannerTargetPos.y = 5;
}

void ResetBannerPosDim(float w, float h) {
	switch (g_DispState) {
		case DispState_Menu:
		{
			ResetBannerPosDimMid(w, h);
		} break;

		default:
		{
			ResetBannerPosDimTopLeft();
		} break;
	}
}

bool OnLoad(Platform *p) {
	if (!CppBoid::OnLoad(p)) return false;
	if (!CppAnim::OnLoad(p)) return false;

	uint32_t channels = 0;
	uint32_t w, h;
	g_Banner = CreateTextureFromFile(p, "Banner.png", &w, &h, &channels);
	g_BannerWidth = (float)w;
	g_BannerHeight = (float)h;

	ResetBannerPosDim(p->RenderTargetWidth, p->RenderTargetHeight);
	g_BannerDim = g_BannerTargetDim;
	g_BannerPos = g_BannerTargetPos;

	return true;
}

void OnResize(Platform *p, uint32_t w, uint32_t h) {
	CppBoid::PlaceObstacles(p, w, h);	
	ResetBannerPosDim(p->RenderTargetWidth, p->RenderTargetHeight);
}

void FixedUpdate(Platform *p, float dt) {
	switch (g_DispState) {
		case DispState_Menu:
		{

		} break;

		case DispState_Boid:
		{
			CppBoid::FixedUpdate(p, dt);
		} break;

		case DispState_Anim:
		{
			CppAnim::FixedUpdate(p, dt);
		} break;
	}

	g_BannerMovementTime += 2 * dt;
	g_BannerMovementTime = Clamp(0, 1, g_BannerMovementTime);
}

void UpdateAndRender(Platform *p, float dt, float alpha) {
	if (KeyIsPressed(p, Key_Escape)) {
		PlatformQuit(p);
	}

	if (KeyIsPressed(p, Key_0)) {
		g_DispState = DispState_Menu;
		ResetBannerPosDim(p->RenderTargetWidth, p->RenderTargetHeight);
	}

	if (KeyIsPressed(p, Key_1)) {
		g_DispState = DispState_Boid;
		ResetBannerPosDim(p->RenderTargetWidth, p->RenderTargetHeight);
	}

	if (KeyIsPressed(p, Key_2)) {
		g_DispState = DispState_Anim;
		ResetBannerPosDim(p->RenderTargetWidth, p->RenderTargetHeight);
	}

	switch (g_DispState) {
		case DispState_Menu:
		{

		} break;

		case DispState_Boid:
		{
			CppBoid::UpdateAndRender(p, dt, alpha);
		} break;		
		
		case DispState_Anim:
		{
			CppAnim::UpdateAndRender(p, dt, alpha);
		} break;
	}

	auto banner_disp_pos = Lerp(g_BannerPos, g_BannerTargetPos, SmoothStep(0.0f, 1.0f, g_BannerMovementTime));
	auto banner_disp_dim = Lerp(g_BannerDim, g_BannerTargetDim, SmoothStep(0.0f, 1.0f, g_BannerMovementTime));

	SetClearColor(0.1f, 0.1f, 0.1f, 1);

	BeginScene2D(0, p->RenderTargetWidth, 0, p->RenderTargetHeight);

	SetTexture(g_Banner);

	DrawRect(banner_disp_pos, banner_disp_dim, Rect(0, 0, 1, 1), Vec4(1));

	EndScene2D();
}

}

CppGameCall void CppGameInitialize(Platform *platform, int argc, char **argv) {
	platform->Name = "Ui Example";
	platform->OnLoad = CppUi::OnLoad;
	platform->OnWindowResize = CppUi::OnResize;
	platform->FixedUpdate = CppUi::FixedUpdate;
	platform->UpdateAndRender = CppUi::UpdateAndRender;
}
