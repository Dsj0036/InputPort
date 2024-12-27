#pragma once

#pragma once
#include "System.h"
#include "game.h"

#include "managed_input_feature.h"
#include "fui.h"
#include "game.h"

namespace MouseStages {
	float lastTickMouseX = 0;
	float lastTickMouseY = 0;
	bool IsKeyboardFocused = 0;
	FJ_FuiNode* currentFocus = nullptr;
	const char* currentFocusName = nullptr;
	Rectangle currentFocusRectangle;

	void setStageFocusTo(uint stage, FJ_FuiNode* target) {

		Call<uint>(0x0070C510, stage, target);
	}
	Rectangle getNodeRectangle(FJ_FuiNode* node) {
		Rectangle rect;
		rect.Position.x = (float)node->getX();
		rect.Position.y = (float)node->getY();
		rect.Size.x = (float)node->getWidth();
		rect.Size.y = (float)node->getHeight();
		return rect;
	}
	namespace MainMenu {


		signed int GetIndexByMouse(const Vector2& mouse) {
			Rectangle first_Button{ Rectangle::fromAbsolute(410, 250, 865, 290) };
			return 00000; // not implemented yet.

		}

	}

	bool isNodeNotContainer(FJ_FuiNode* nod) {

		return
			(!safest_compare(nod->getName(), "ButtonList")) ||
			(!safest_compare(nod->getName(), "BackgroundPanel_List"));
	}

	void Tick(FJ_FuiNode* root, const Vector2& mouse) {
		uint st = (uint)root->getStage();

		bool moved = mouse.x != lastTickMouseX || lastTickMouseY != mouse.y;
		if (moved) {
		repeat:
			for (int i = 0; i < root->getNumChildren(); i++) {
				auto nod = root->At(i);
				Rectangle rect = getNodeRectangle(nod);
				bool isContainer = !isNodeNotContainer(nod);
				if (rect.Contains(mouse) && (!isContainer)) {
					currentFocusName = nod->getName();
					bool notTimer = (!safest_compare(currentFocusName, "Timer")) || safest_compare(currentFocusName, "Fac");

					if ((notTimer) && currentFocus != nod) // not a container list
					{
						currentFocus = nod;
						currentFocusRectangle = rect;
						setStageFocusTo(st, nod);
						g_UIController->PlayUISFX(Sound::FOCUS);



						lastTickMouseX = mouse.x;
						lastTickMouseY = mouse.y;
					}
					break;
				}
				else if (isContainer) {

					goto repeat;
					break;
				}
			}

		}
		if (IsKeyboardFocused) {
			currentFocusRectangle = Rectangle::Empty;

		}
		if (moved) {
			IsKeyboardFocused = false;
			lastTickMouseX = mouse.x;
			lastTickMouseY = mouse.y;
		}

	}
}


namespace MouseEngine {
	bool currentState = false;

	bool ValidateVtable(uint32_t adr, uint32_t vt) {
		uint vtable = 0;
		int R = read_process(adr, &vtable, 4);
		if (R < 0) {
			return 0;
		}
		return vtable == vt;
	}
	bool ValidateReadable(uint32_t adr) {
		uint vtable = 0;
		int R = read_process(adr, &vtable, 4);
		if (R < 0) {
			return 0;
		}
		return true;
	}
	bool isMouseAble(uint menuType) {
		return ValidateVtable((uint32_t)Onyx::FocusedScene, 0x13FD7D0) ||		// main menu
			ValidateVtable((uint32_t)Onyx::FocusedScene, 0x13f7db8) ||			// help and options
			ValidateVtable((uint32_t)Onyx::FocusedScene, 0x13feac0) ||			// settings
			ValidateVtable((uint32_t)Onyx::FocusedScene, 0x13fe9d8);		// options multilist

	}

	void DispatchMouseInput(UIScene* target = nullptr) {
		if (Onyx::FocusedScene == nullptr && (target == nullptr)) {
			return;
		}
		if (target == nullptr) {
			uint vtable = *(uint*)Onyx::FocusedScene;
			if (isMouseAble(vtable)) {

				uint file = ((uint)Onyx::FocusedScene) + 32;
				if (file > 0x7fff) {

					file = *(uint*)file;
					auto rootNode = *(_DWORD*)(file + 224);
					if (rootNode > 0x7F7F) {
						auto node2 = (FJ_FuiNode*)*(_DWORD*)(rootNode + 224);
						//MouseStages::Tick(node2, ManagedInputFeature::mousePosition);
					}
				}
			}
		}
		// Enforce handling to specific scene.
		else {

			FuiFile* file = target->getFile();
			if (((uint)file) > 0x7fff) {

				uint document = *(uint*)file;
				auto rootNode = *(_DWORD*)(document + 224);
				if (rootNode > 0x7F7F) {
					auto node2 = (FJ_FuiNode*)*(_DWORD*)(rootNode + 224);
					//MouseStages::Tick(node2, ManagedInputFeature::mousePosition);
				}
			}
		}

	}

	bool OnDeathMenu() {
		UIScene* deathMenu = FindSceneEx(EUIScene::DEATH_MENU);
		if (deathMenu == nullptr) {
			return false;
		}
		else {

		}
	}
	void MouseLogic() {
		if (fj::isGameStarted() && (!IS_MODAL_ACTIVE))
			return;
		if (!Onyx::FocusedScene)
			return;
		if (ValidateReadable((uint32_t)Onyx::FocusedScene)) {

			if (Onyx::FocusedScene && (IS_MODAL_ACTIVE) && *(uint*)Onyx::FocusedScene > 0x7FFFFF) {
				uint rootNode = (uint)Scene_getRootNode((uint)Onyx::FocusedScene);
				if (GLES::GetFramesSinceBoot() > 60 * 6) {
					DispatchMouseInput();
				}
			}
		}

	}

	void Frame() {
		//if (ManagedInputFeature::available && ManagedInputFeature::mouseInfo.now_connect > 0) {
			//MouseLogic();
		//}
	}
}

