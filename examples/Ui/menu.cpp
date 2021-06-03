#include "CppGame.h"
#include <string.h>

#define CPP_EXAMPLE_MENU
#include "../Boid/boids.cpp"
#include "../Anim/anim.cpp"

#include <stdio.h>
#include <stdlib.h>

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

	_DispState_Count
};

static DispState g_DispState = DispState_Menu;
static float g_DispStateTransition = 0;
static float g_DispStateDir = 1;

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

typedef void(*OnUiButtonPressed)(struct UiButton *);

struct UiButton {
	bool				Active;
	float				ActiveTime;
	String				Label;
	float				Size;
	Vec4				BackColor;
	Vec4				TextColor;
	Vec4				HoveredColor;
	float				HoveredTime;
	OnUiButtonPressed	OnPressed;
	struct UiContext *	Context;
	UiButton *			Next;
};

struct UiContext {
	float MaxWidth;
	float PaddingY;

	UiButton *Hot;
	UiButton *Active;

	UiButton *Root;
	UiButton *Last;

	Platform *P;
};

static UiContext g_Ui;
static UiButton *g_Buttons[_DispState_Count];

UiButton *AddUiButton(String label, float size = 1) {
	UiButton *button = (UiButton *)g_Ui.P->Alloc(sizeof(UiButton));

	button->Active = true;
	button->ActiveTime = 1;
	button->Label = label;
	button->Size = size;
	button->TextColor = Vec4(1);
	button->BackColor = Vec4(0.2f, 0.2f, 0.0f, 1);
	button->HoveredColor = Vec4(0.5f, 0.5f, 0.0f, 1);
	button->HoveredTime = 0;
	button->OnPressed = [](UiButton *) { };
	button->Context = &g_Ui;
	button->Next = nullptr;

	if (g_Ui.Last) {
		g_Ui.Last->Next = button;
		g_Ui.Last = button;
	} else {
		g_Ui.Root = g_Ui.Last = button;
	}

	return button;
}

bool PointInsideRect(Vec2 p, Rect rect) {
	return p.x >= rect.Min.x && p.x <= rect.Max.x && p.y >= rect.Min.y && p.y <= rect.Max.y;
}

void UiUpdate(float dt) {
	g_Ui.MaxWidth = 0;

	for (UiButton *b = g_Ui.Root; b; b = b->Next) {
		if (b->Active) {
			b->ActiveTime += 4 * dt;
			b->ActiveTime = Clamp(0, 1, b->ActiveTime);

			float w = CalculateText(b->Label, b->Size);
			g_Ui.MaxWidth = Maximum(g_Ui.MaxWidth, w);

			if (g_Ui.Active == b) {
				b->OnPressed(b);
				g_Ui.Active = nullptr;
			} else if (g_Ui.Hot == b && ButtonIsPressed(g_Ui.P, Button_Left)) {
				g_Ui.Active = b;
			}

			if (b == g_Ui.Hot) {
				b->HoveredTime += 3 * dt;
				b->HoveredTime = Clamp(0, 1, b->HoveredTime);
			} else {
				b->HoveredTime -= 3 * dt;
				b->HoveredTime = Clamp(0, 1, b->HoveredTime);
			}
		} else {
			b->ActiveTime -= 3 * dt;
			b->ActiveTime = Clamp(0, 1, b->ActiveTime);
		}
	}
}

void UiRender(Vec2 p) {
	Vec2 cursor = g_Ui.P->Mouse.Position;

	g_Ui.Hot = nullptr;

	for (UiButton *b = g_Ui.Root; b; b = b->Next) {
		float alpha = SmoothStep(0.0f, 1.0f, b->ActiveTime);
		Vec2 dim = Vec2(g_Ui.MaxWidth, GetFontScale(b->Size));

		float t = SmoothStep(0.0f, 1.0f, b->HoveredTime);
		Vec2 d = 8 * Vec2(SmoothStep(0.0f, 1.0f, b->HoveredTime), 0);
		Vec4 color = Lerp(b->BackColor, b->HoveredColor, t);
		color.w *= alpha;

		DrawRect(p - d, alpha * (dim + 2 * d), color);
		DrawRectOutline(p - d - Vec2(1), alpha * (dim + 2 * d + Vec2(2)), Vec4(0, 0, 0, alpha));

		float w = CalculateText(b->Label, b->Size);
		float h = CalculateMaxHeight(b->Label, b->Size);

		DrawText(b->Label, p + 0.5f * Vec2(g_Ui.MaxWidth - w, GetFontScale(b->Size) - h), 
				 Vec4(b->TextColor.xyz, b->TextColor.w * alpha), alpha * b->Size);

		if (b->Active) {
			if (g_Ui.Active == nullptr && PointInsideRect(cursor, Rect(p, p + dim))) {
				g_Ui.Hot = b;
			}
		}

		p.y += alpha * (dim.y + g_Ui.PaddingY);
	}
}

void SwitchDispState(DispState state, float w, float h) {
	switch (state) {
		case DispState_Boid:
		case DispState_Anim:
		{
			g_DispStateTransition = 1;
			g_DispStateDir = -0.5f;

			g_DispState = state;
			ResetBannerPosDimTopLeft();

			g_Buttons[DispState_Menu]->Active = true;
			g_Buttons[DispState_Anim]->Active = false;
			g_Buttons[DispState_Boid]->Active = false;
		} break;

		case DispState_Menu:
		{
			g_DispStateTransition = 0;
			g_DispStateDir = 1.4f;

			ResetBannerPosDimMid(w, h);

			g_Buttons[DispState_Menu]->Active = false;
			g_Buttons[DispState_Anim]->Active = true;
			g_Buttons[DispState_Boid]->Active = true;
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

	ResetBannerPosDimMid(p->RenderTargetWidth, p->RenderTargetHeight);
	g_BannerDim = g_BannerTargetDim;
	g_BannerPos = g_BannerTargetPos;

	g_Ui.P = p;
	g_Ui.PaddingY = 8;

	g_Buttons[DispState_Boid] = AddUiButton("Boid");
	g_Buttons[DispState_Anim] = AddUiButton("Anim");
	g_Buttons[DispState_Menu] = AddUiButton("Back", 0.4f);

	g_Buttons[DispState_Boid]->OnPressed = [](UiButton *button) {
		SwitchDispState(DispState_Boid, button->Context->P->RenderTargetWidth, button->Context->P->RenderTargetHeight);
	};
	g_Buttons[DispState_Anim]->OnPressed = [](UiButton *button) {
		SwitchDispState(DispState_Anim, button->Context->P->RenderTargetWidth, button->Context->P->RenderTargetHeight);
	};
	g_Buttons[DispState_Menu]->OnPressed = [](UiButton *button) {
		SwitchDispState(DispState_Menu, button->Context->P->RenderTargetWidth, button->Context->P->RenderTargetHeight);
	};

	SwitchDispState(DispState_Menu, p->RenderTargetWidth, p->RenderTargetHeight);

	return true;
}

void OnResize(Platform *p, uint32_t w, uint32_t h) {
	CppBoid::PlaceObstacles(p, w, h);
	if (g_DispState == DispState_Menu)
		ResetBannerPosDimMid(p->RenderTargetWidth, p->RenderTargetHeight);
	else
		ResetBannerPosDimTopLeft();
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

	g_DispStateTransition += dt * g_DispStateDir;

	if (g_DispStateTransition > 1)
		g_DispState = DispState_Menu;

	g_DispStateTransition = Clamp(0, 1, g_DispStateTransition);

	g_BannerMovementTime += 2 * dt;
	g_BannerMovementTime = Clamp(0, 1, g_BannerMovementTime);
}

void UpdateAndRender(Platform *p, float dt, float alpha) {
	if (KeyIsPressed(p, Key_Escape)) {
		PlatformQuit(p);
	}

	if (KeyIsPressed(p, Key_0)) {
		SwitchDispState(DispState_Menu, p->RenderTargetWidth, p->RenderTargetHeight);
	}
	if (KeyIsPressed(p, Key_1)) {
		SwitchDispState(DispState_Boid, p->RenderTargetWidth, p->RenderTargetHeight);
	}
	if (KeyIsPressed(p, Key_2)) {
		SwitchDispState(DispState_Anim, p->RenderTargetWidth, p->RenderTargetHeight);
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

	UiUpdate(dt);

	auto banner_disp_pos = Lerp(g_BannerPos, g_BannerTargetPos, SmoothStep(0.0f, 1.0f, g_BannerMovementTime));
	auto banner_disp_dim = Lerp(g_BannerDim, g_BannerTargetDim, SmoothStep(0.0f, 1.0f, g_BannerMovementTime));

	Vec4 clear_color(0.1f, 0.1f, 0.1f, 1);
	SetClearColor(clear_color);

	BeginScene2D(0, p->RenderTargetWidth, 0, p->RenderTargetHeight);

	clear_color.w *= SmoothStep(0.0f, 1.0f, g_DispStateTransition);
	DrawRect(Vec2(0), Vec2(p->RenderTargetWidth, p->RenderTargetHeight), Rect(0, 0, 1, 1), clear_color);

	SetTexture(g_Banner);

	if (PointInsideRect(p->Mouse.Position, Rect(banner_disp_pos, banner_disp_pos + banner_disp_dim))) {
		constexpr uint32_t SPLITS = 10;

		Vec2 a, b, c, d;
		float ds = 1.0f / (float)SPLITS;
		float ta = 0, tb = ds;

		Vec2 pos = banner_disp_pos;
		Vec2 dim = Vec2(ds * banner_disp_dim.x, banner_disp_dim.y);

		for (uint32_t split = 0; split < SPLITS; ++split) {
			a = pos;
			b = a;
			b.y += dim.y;
			c = a + dim;
			d = a;
			d.x += dim.x;

			float amp = 5;
			float freq = 0.05f;

			a.y += amp * Map01(-1.0f, 1.0f, Sin(freq * p->Time.Time * a.x));
			b.y += amp * Map01(-1.0f, 1.0f, Sin(freq * p->Time.Time * b.x));
			c.y += amp * Map01(-1.0f, 1.0f, Sin(freq * p->Time.Time * c.x));
			d.y += amp * Map01(-1.0f, 1.0f, Sin(freq * p->Time.Time * d.x));

			DrawQuad(a, b, c, d, Vec2(ta, 0), Vec2(ta, 1), Vec2(tb, 1), Vec2(tb, 0), Vec4(1));

			ta = tb;
			tb += ds;

			pos.x += dim.x;
		}

	} else {
		DrawRect(banner_disp_pos, banner_disp_dim, Rect(0, 0, 1, 1), Vec4(1));
	}


	SetTexture(0);

	Vec2 ui_pos;
	ui_pos.y = banner_disp_pos.y + banner_disp_dim.y + 5;
	ui_pos.x = banner_disp_pos.x + 0.5f * (banner_disp_dim.x - g_Ui.MaxWidth);
	UiRender(ui_pos);

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
