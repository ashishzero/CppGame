#include "CppGame.h"

bool OnLoad(Platform *p) {
	return true;
}

void FixedUpdate(Platform *p, float dt) {

}

void UpdateAndRender(Platform *p, float dt, float alpha) {
	if (KeyIsPressed(p, KeyEscape)) {
		PlatformQuit(p);
	}

	BeginScene2D(0, p->RenderTargetWidth, 0, p->RenderTargetHeight);


	EndScene2D();
}

CppGameCall void CppGameInitialize(Platform *platform, int argc, char **argv) {
	platform->Name = "Ui Example";
	platform->OnLoad = OnLoad;
	platform->FixedUpdate = FixedUpdate;
	platform->UpdateAndRender = UpdateAndRender;
}
