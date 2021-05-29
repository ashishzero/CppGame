#include "CppGame.h"
#include <string.h>

#define CPP_EXAMPLE_MENU
#include "../Boid/boids.cpp"
#include "../Anim/anim.cpp"

static Font g_Font;

void CreateDefaultFont(Platform *p) {
	constexpr uint32_t FIRST_CODEPOINT = 32;
	constexpr uint32_t LAST_CODEPOINT = 126;
	constexpr uint32_t CODEPOINT_COUNT = LAST_CODEPOINT - FIRST_CODEPOINT + 1;

	static GlyphRange g_GlyphRange;
	static GlyphInfo g_GlyphInfos[CODEPOINT_COUNT];

	g_Font.Size = 72;
	g_Font.Ascender = 1;
	g_Font.Descender = 0;
	g_Font.RangeCount = 1;
	g_Font.Range = &g_GlyphRange;
	g_Font.Range->Codepoint.Buffer = nullptr;
	g_Font.Range->Codepoint.First = FIRST_CODEPOINT;
	g_Font.Range->Codepoint.Count = CODEPOINT_COUNT;
	g_Font.Range->Info = g_GlyphInfos;

	uint32_t channels = 0, width = 0, height = 0;
	g_Font.Texture = CreateTextureFromFile(p, "Font.png", &width, &height, &channels);

	g_GlyphInfos[32 - FIRST_CODEPOINT] = { Rect(0, 0, 0, 0), Vec2(0 , 0), 16 };
	g_GlyphInfos[33 - FIRST_CODEPOINT] = { Rect(213 , 128 , 11 , 52), Vec2(5 , 0), 19 };
	g_GlyphInfos[34 - FIRST_CODEPOINT] = { Rect(92 , 380 , 22 , 18), Vec2(4 , 0), 28 };
	g_GlyphInfos[35 - FIRST_CODEPOINT] = { Rect(0 , 289 , 40 , 50), Vec2(1 , 2), 41 };
	g_GlyphInfos[36 - FIRST_CODEPOINT] = { Rect(0 , 0 , 35 , 70), Vec2(4 , -8), 41 };
	g_GlyphInfos[37 - FIRST_CODEPOINT] = { Rect(175 , 71 , 40 , 54), Vec2(1 , 0), 41 };
	g_GlyphInfos[38 - FIRST_CODEPOINT] = { Rect(216 , 71 , 49 , 54), Vec2(2 , -1), 50 };
	g_GlyphInfos[39 - FIRST_CODEPOINT] = { Rect(115 , 380 , 10 , 18), Vec2(4 , 0), 16 };
	g_GlyphInfos[40 - FIRST_CODEPOINT] = { Rect(134 , 0 , 17 , 66), Vec2(3 , -5), 21 };
	g_GlyphInfos[41 - FIRST_CODEPOINT] = { Rect(152 , 0 , 17 , 66), Vec2(2 , -5), 21 };
	g_GlyphInfos[42 - FIRST_CODEPOINT] = { Rect(12 , 380 , 27 , 28), Vec2(3 , -2), 31 };
	g_GlyphInfos[43 - FIRST_CODEPOINT] = { Rect(339 , 340 , 36 , 35), Vec2(3 , 16), 41 };
	g_GlyphInfos[44 - FIRST_CODEPOINT] = { Rect(76 , 380 , 15 , 19), Vec2(1 , 42), 17 };
	g_GlyphInfos[45 - FIRST_CODEPOINT] = { Rect(205 , 330 , 25 , 8), Vec2(4 , 27), 31 };
	g_GlyphInfos[46 - FIRST_CODEPOINT] = { Rect(184 , 380 , 11 , 11), Vec2(4 , 41), 17 };
	g_GlyphInfos[47 - FIRST_CODEPOINT] = { Rect(325 , 0 , 29 , 56), Vec2(2 , -2), 31 };
	g_GlyphInfos[48 - FIRST_CODEPOINT] = { Rect(177 , 236 , 39 , 51), Vec2(2 , 2), 41 };
	g_GlyphInfos[49 - FIRST_CODEPOINT] = { Rect(41 , 289 , 25 , 50), Vec2(6 , 2), 41 };
	g_GlyphInfos[50 - FIRST_CODEPOINT] = { Rect(67 , 289 , 34 , 50), Vec2(4 , 2), 41 };
	g_GlyphInfos[51 - FIRST_CODEPOINT] = { Rect(217 , 236 , 34 , 51), Vec2(4 , 2), 41 };
	g_GlyphInfos[52 - FIRST_CODEPOINT] = { Rect(102 , 289 , 38 , 50), Vec2(2 , 2), 41 };
	g_GlyphInfos[53 - FIRST_CODEPOINT] = { Rect(141 , 289 , 36 , 50), Vec2(3 , 3), 41 };
	g_GlyphInfos[54 - FIRST_CODEPOINT] = { Rect(252 , 236 , 38 , 51), Vec2(2 , 2), 41 };
	g_GlyphInfos[55 - FIRST_CODEPOINT] = { Rect(291 , 236 , 33 , 51), Vec2(5 , 2), 41 };
	g_GlyphInfos[56 - FIRST_CODEPOINT] = { Rect(325 , 236 , 40 , 51), Vec2(1 , 2), 41 };
	g_GlyphInfos[57 - FIRST_CODEPOINT] = { Rect(366 , 236 , 38 , 51), Vec2(2 , 2), 41 };
	g_GlyphInfos[58 - FIRST_CODEPOINT] = { Rect(0 , 380 , 11 , 34), Vec2(4 , 18), 17 };
	g_GlyphInfos[59 - FIRST_CODEPOINT] = { Rect(399 , 71 , 15 , 43), Vec2(2 , 18), 19 };
	g_GlyphInfos[60 - FIRST_CODEPOINT] = { Rect(113 , 340 , 33 , 38), Vec2(4 , 14), 41 };
	g_GlyphInfos[61 - FIRST_CODEPOINT] = { Rect(40 , 380 , 35 , 22), Vec2(4 , 22), 41 };
	g_GlyphInfos[62 - FIRST_CODEPOINT] = { Rect(147 , 340 , 34 , 38), Vec2(5 , 14), 41 };
	g_GlyphInfos[63 - FIRST_CODEPOINT] = { Rect(142 , 128 , 30 , 53), Vec2(2 , -1), 32 };
	g_GlyphInfos[64 - FIRST_CODEPOINT] = { Rect(47 , 0 , 67 , 69), Vec2(3 , -3), 71 };
	g_GlyphInfos[65 - FIRST_CODEPOINT] = { Rect(225 , 128 , 43 , 52), Vec2(1 , 0), 44 };
	g_GlyphInfos[66 - FIRST_CODEPOINT] = { Rect(269 , 128 , 38 , 52), Vec2(5 , 0), 45 };
	g_GlyphInfos[67 - FIRST_CODEPOINT] = { Rect(266 , 71 , 36 , 54), Vec2(3 , -1), 40 };
	g_GlyphInfos[68 - FIRST_CODEPOINT] = { Rect(308 , 128 , 40 , 52), Vec2(5 , 0), 47 };
	g_GlyphInfos[69 - FIRST_CODEPOINT] = { Rect(0 , 183 , 34 , 52), Vec2(5 , 0), 40 };
	g_GlyphInfos[70 - FIRST_CODEPOINT] = { Rect(35 , 183 , 34 , 52), Vec2(5 , 0), 39 };
	g_GlyphInfos[71 - FIRST_CODEPOINT] = { Rect(303 , 71 , 40 , 54), Vec2(3 , -1), 45 };
	g_GlyphInfos[72 - FIRST_CODEPOINT] = { Rect(70 , 183 , 41 , 52), Vec2(5 , 0), 49 };
	g_GlyphInfos[73 - FIRST_CODEPOINT] = { Rect(112 , 183 , 11 , 52), Vec2(5 , 0), 19 };
	g_GlyphInfos[74 - FIRST_CODEPOINT] = { Rect(307 , 0 , 17 , 57), Vec2(1 , 0), 22 };
	g_GlyphInfos[75 - FIRST_CODEPOINT] = { Rect(124 , 183 , 38 , 52), Vec2(5 , 0), 42 };
	g_GlyphInfos[76 - FIRST_CODEPOINT] = { Rect(163 , 183 , 31 , 52), Vec2(5 , 0), 35 };
	g_GlyphInfos[77 - FIRST_CODEPOINT] = { Rect(195 , 183 , 53 , 52), Vec2(5 , 0), 61 };
	g_GlyphInfos[78 - FIRST_CODEPOINT] = { Rect(249 , 183 , 41 , 52), Vec2(5 , 0), 50 };
	g_GlyphInfos[79 - FIRST_CODEPOINT] = { Rect(344 , 71 , 43 , 54), Vec2(3 , -1), 48 };
	g_GlyphInfos[80 - FIRST_CODEPOINT] = { Rect(291 , 183 , 38 , 52), Vec2(5 , 0), 43 };
	g_GlyphInfos[81 - FIRST_CODEPOINT] = { Rect(263 , 0 , 43 , 64), Vec2(3 , -1), 48 };
	g_GlyphInfos[82 - FIRST_CODEPOINT] = { Rect(330 , 183 , 39 , 52), Vec2(5 , 0), 45 };
	g_GlyphInfos[83 - FIRST_CODEPOINT] = { Rect(0 , 128 , 37 , 54), Vec2(2 , -1), 40 };
	g_GlyphInfos[84 - FIRST_CODEPOINT] = { Rect(370 , 183 , 40 , 52), Vec2(0 , 0), 38 };
	g_GlyphInfos[85 - FIRST_CODEPOINT] = { Rect(173 , 128 , 39 , 53), Vec2(5 , 0), 47 };
	g_GlyphInfos[86 - FIRST_CODEPOINT] = { Rect(0 , 236 , 43 , 52), Vec2(1 , 0), 43 };
	g_GlyphInfos[87 - FIRST_CODEPOINT] = { Rect(349 , 128 , 65 , 52), Vec2(1 , 0), 65 };
	g_GlyphInfos[88 - FIRST_CODEPOINT] = { Rect(44 , 236 , 42 , 52), Vec2(0 , 0), 41 };
	g_GlyphInfos[89 - FIRST_CODEPOINT] = { Rect(87 , 236 , 41 , 52), Vec2(0 , 0), 40 };
	g_GlyphInfos[90 - FIRST_CODEPOINT] = { Rect(129 , 236 , 36 , 52), Vec2(2 , 0), 39 };
	g_GlyphInfos[91 - FIRST_CODEPOINT] = { Rect(222 , 0 , 19 , 65), Vec2(5 , -4), 25 };
	g_GlyphInfos[92 - FIRST_CODEPOINT] = { Rect(355 , 0 , 32 , 56), Vec2(1 , -2), 33 };
	g_GlyphInfos[93 - FIRST_CODEPOINT] = { Rect(242 , 0 , 20 , 65), Vec2(2 , -4), 25 };
	g_GlyphInfos[94 - FIRST_CODEPOINT] = { Rect(376 , 340 , 36 , 27), Vec2(3 , 2), 41 };
	g_GlyphInfos[95 - FIRST_CODEPOINT] = { Rect(231 , 330 , 35 , 8), Vec2(6 , 56), 46 };
	g_GlyphInfos[96 - FIRST_CODEPOINT] = { Rect(126 , 380 , 22 , 14), Vec2(-1 , -4), 18 };
	g_GlyphInfos[97 - FIRST_CODEPOINT] = { Rect(205 , 289 , 35 , 40), Vec2(2 , 13), 37 };
	g_GlyphInfos[98 - FIRST_CODEPOINT] = { Rect(37 , 71 , 34 , 55), Vec2(4 , -2), 39 };
	g_GlyphInfos[99 - FIRST_CODEPOINT] = { Rect(241 , 289 , 29 , 40), Vec2(3 , 13), 32 };
	g_GlyphInfos[100 - FIRST_CODEPOINT] = { Rect(72 , 71 , 33 , 55), Vec2(3 , -2), 39 };
	g_GlyphInfos[101 - FIRST_CODEPOINT] = { Rect(271 , 289 , 33 , 40), Vec2(3 , 13), 37 };
	g_GlyphInfos[102 - FIRST_CODEPOINT] = { Rect(388 , 0 , 26 , 55), Vec2(1 , -3), 25 };
	g_GlyphInfos[103 - FIRST_CODEPOINT] = { Rect(0 , 71 , 36 , 56), Vec2(3 , 13), 38 };
	g_GlyphInfos[104 - FIRST_CODEPOINT] = { Rect(38 , 128 , 33 , 54), Vec2(4 , -2), 40 };
	g_GlyphInfos[105 - FIRST_CODEPOINT] = { Rect(166 , 236 , 10 , 52), Vec2(4 , 0), 17 };
	g_GlyphInfos[106 - FIRST_CODEPOINT] = { Rect(115 , 0 , 18 , 68), Vec2(-4 , 0), 17 };
	g_GlyphInfos[107 - FIRST_CODEPOINT] = { Rect(72 , 128 , 33 , 54), Vec2(4 , -2), 36 };
	g_GlyphInfos[108 - FIRST_CODEPOINT] = { Rect(388 , 71 , 10 , 54), Vec2(5 , -2), 18 };
	g_GlyphInfos[109 - FIRST_CODEPOINT] = { Rect(0 , 340 , 54 , 39), Vec2(4 , 13), 61 };
	g_GlyphInfos[110 - FIRST_CODEPOINT] = { Rect(374 , 289 , 33 , 39), Vec2(4 , 13), 40 };
	g_GlyphInfos[111 - FIRST_CODEPOINT] = { Rect(305 , 289 , 35 , 40), Vec2(3 , 13), 39 };
	g_GlyphInfos[112 - FIRST_CODEPOINT] = { Rect(106 , 71 , 34 , 55), Vec2(4 , 13), 39 };
	g_GlyphInfos[113 - FIRST_CODEPOINT] = { Rect(141 , 71 , 33 , 55), Vec2(3 , 13), 39 };
	g_GlyphInfos[114 - FIRST_CODEPOINT] = { Rect(55 , 340 , 23 , 39), Vec2(4 , 13), 26 };
	g_GlyphInfos[115 - FIRST_CODEPOINT] = { Rect(341 , 289 , 32 , 40), Vec2(2 , 13), 34 };
	g_GlyphInfos[116 - FIRST_CODEPOINT] = { Rect(178 , 289 , 26 , 50), Vec2(1 , 3), 26 };
	g_GlyphInfos[117 - FIRST_CODEPOINT] = { Rect(79 , 340 , 33 , 39), Vec2(4 , 14), 39 };
	g_GlyphInfos[118 - FIRST_CODEPOINT] = { Rect(182 , 340 , 35 , 38), Vec2(1 , 14), 35 };
	g_GlyphInfos[119 - FIRST_CODEPOINT] = { Rect(218 , 340 , 55 , 38), Vec2(1 , 14), 56 };
	g_GlyphInfos[120 - FIRST_CODEPOINT] = { Rect(274 , 340 , 33 , 38), Vec2(1 , 14), 34 };
	g_GlyphInfos[121 - FIRST_CODEPOINT] = { Rect(106 , 128 , 35 , 54), Vec2(1 , 14), 36 };
	g_GlyphInfos[122 - FIRST_CODEPOINT] = { Rect(308 , 340 , 30 , 38), Vec2(2 , 14), 33 };
	g_GlyphInfos[123 - FIRST_CODEPOINT] = { Rect(170 , 0 , 25 , 66), Vec2(1 , -5), 26 };
	g_GlyphInfos[124 - FIRST_CODEPOINT] = { Rect(36 , 0 , 10 , 70), Vec2(5 , -2), 18 };
	g_GlyphInfos[125 - FIRST_CODEPOINT] = { Rect(196 , 0 , 25 , 66), Vec2(2 , -5), 26 };
	g_GlyphInfos[126 - FIRST_CODEPOINT] = { Rect(149 , 380 , 34 , 12), Vec2(4 , 26), 41 };

	Vec2 tex_dim((float)width, (float)height);
	for (uint32_t index = 0; index < ArrayCount(g_GlyphInfos); ++index) {
		g_GlyphInfos[index].Dimension = g_GlyphInfos[index].TexCoord.Max;
		g_GlyphInfos[index].TexCoord.Max += g_GlyphInfos[index].TexCoord.Min;
		g_GlyphInfos[index].TexCoord.Min /= tex_dim;
		g_GlyphInfos[index].TexCoord.Max /= tex_dim;
	}
}

float GetFontScale(float size) {
	return size * g_Font.Size;
}

float CalculateMaxHeight(String text, float size) {
	return CalculateMaxHeight(text, size, &g_Font);
}

float CalculateText(String text, float size) {
	return CalculateText(text, size, &g_Font);
}

void DrawText(String text, Vec2 position, Vec4 color, float size) {
	DrawText(text, position, color, size, &g_Font);
}

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

	CreateDefaultFont(p);

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
