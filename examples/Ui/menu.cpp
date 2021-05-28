#include "CppGame.h"

#define CPP_EXAMPLE_MENU
#include "../Boid/boids.cpp"
#include "../Anim/anim.cpp"

namespace CppUi {

static struct {
	PlatformFixedUpdate FixedUpdate;
	PlatformUpdateAndRender UpdateAndRender;
} Running;

bool OnLoad(Platform *p) {
	if (!CppBoid::OnLoad(p)) return false;
	if (!CppAnim::OnLoad(p)) return false;
	return true;
}

void FixedUpdate(Platform *p, float dt) {
	if (Running.FixedUpdate) {
		Running.FixedUpdate(p, dt);
		return;
	}
}

void UpdateAndRender(Platform *p, float dt, float alpha) {
	if (KeyIsPressed(p, Key_Escape)) {
		PlatformQuit(p);
	}

	if (KeyIsPressed(p, Key_0)) {
		Running.FixedUpdate = nullptr;
		Running.UpdateAndRender = nullptr;
	}

	if (KeyIsPressed(p, Key_1)) {
		Running.FixedUpdate = CppBoid::FixedUpdate;
		Running.UpdateAndRender = CppBoid::UpdateAndRender;
	}

	if (KeyIsPressed(p, Key_2)) {
		Running.FixedUpdate = CppAnim::FixedUpdate;
		Running.UpdateAndRender = CppAnim::UpdateAndRender;
	}

	if (Running.UpdateAndRender) {
		Running.UpdateAndRender(p, dt, alpha);

		BeginScene2D(0, p->RenderTargetWidth, 0, p->RenderTargetHeight);

		EndScene2D();
	} else {
		BeginScene2D(0, p->RenderTargetWidth, 0, p->RenderTargetHeight);

		EndScene2D();
	}
}

}

CppGameCall void CppGameInitialize(Platform *platform, int argc, char **argv) {
	platform->Name = "Ui Example";
	platform->OnLoad = CppUi::OnLoad;
	platform->FixedUpdate = CppUi::FixedUpdate;
	platform->UpdateAndRender = CppUi::UpdateAndRender;
}
