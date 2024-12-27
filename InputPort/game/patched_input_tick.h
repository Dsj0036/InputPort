#pragma once
#include "System.h"
#include "opds.h"
#include "managed_input_feature.h"
#include "console_ui_controller.h"
#include "game.h"
#include "fui.h"
#include "framestat.h"
#include "client.hpp"
namespace MinecraftTick {

	int oldLength = 0;
	int container = 0;
	int topScene = 0;
	int pression = 0;
	int escape_delay = 0;
	float lx;
	float ly;
	float FPS_Last = 0.0f;
	int cameraCooldown = 0;
	num ring[6];

	// 8AB9AC = relative mouse speed multiplier.      
	// maybe good value for 8AB9AC = 0x4000
	/*	Must convert and clamp mouse delta for cleaner movement.	 */



	void ForceHotbarUpdate() {
		// avoid crashing the hotbar when scrolling.
		// do forced update.
		if (Onyx::Hud) {
			Onyx::ForceUpdateHudIfPossible();
		}
	}

	void AddBitsIfKeycharEquals(OnyxCellPadData* out, byte digital, uint16_t val, uint16_t char_, uint16_t expected) {
		if (char_ == expected) {
			out->button[digital] |= val;
		}
	}

	void EnsureNormalSpeed() {

		float X = Onyx::input_feature::mouse_delta.x;
		float Y = Onyx::input_feature::mouse_delta.y;

		Onyx::input_feature::mousePosition.x += X;
		Onyx::input_feature::mousePosition.y += Y;

	}
	void HotbarSelect(int key) {
		if (key > '0' && key <= '9') {
			//Hand::reset();
			//Crosshair::__elapsedFrames = -5;
			//Crosshair::__active = true;
			auto* player = Onyx::getLocalPlayer();
			(*player->getInventory()->getSelectedIndexEx()) = (key - '0' - 1);
			// uiscene hud update tick
			ForceHotbarUpdate();
		}

	}
	void MenuCnvKeyDown(OnyxCellPadData* data, int key) {
		if (key == ' ' || (Onyx::input_feature::click & CELL_MOUSE_BUTTON_1)) {
			data->button[CELL_PAD_BTN_OFFSET_DIGITAL2] |= CELL_PAD_CTRL_CROSS;
			data->button[CELL_PAD_BTN_OFFSET_PRESS_CROSS] |= 80;
		}
		if (Onyx::input_feature::click & CELL_MOUSE_BUTTON_2) {
			data->button[CELL_PAD_BTN_OFFSET_DIGITAL2] |= CELL_PAD_CTRL_SQUARE;
			data->button[CELL_PAD_BTN_OFFSET_PRESS_SQUARE] |= 80;
		}
		if (Onyx::input_feature::click & CELL_MOUSE_BUTTON_3) {
			data->button[CELL_PAD_BTN_OFFSET_DIGITAL2] |= CELL_PAD_CTRL_TRIANGLE;
			data->button[CELL_PAD_BTN_OFFSET_PRESS_TRIANGLE] |= 80;
		}

		AddBitsIfKeycharEquals(data, CELL_PAD_BTN_OFFSET_DIGITAL2, CELL_PAD_CTRL_CROSS, key, '\n');
		AddBitsIfKeycharEquals(data, CELL_PAD_BTN_OFFSET_PRESS_CROSS, 80, key, '\n');
		AddBitsIfKeycharEquals(data, CELL_PAD_BTN_OFFSET_DIGITAL2, CELL_PAD_CTRL_CROSS, key, ' ');
		AddBitsIfKeycharEquals(data, CELL_PAD_BTN_OFFSET_PRESS_CROSS, 80, key, ' ');
		AddBitsIfKeycharEquals(data, CELL_PAD_BTN_OFFSET_DIGITAL2, CELL_PAD_CTRL_CIRCLE, key, 0x8029);
		AddBitsIfKeycharEquals(data, CELL_PAD_BTN_OFFSET_PRESS_CIRCLE, 80, key, 0x8029);
		AddBitsIfKeycharEquals(data, CELL_PAD_BTN_OFFSET_DIGITAL1, CELL_PAD_CTRL_LEFT, key, 0x8050);
		AddBitsIfKeycharEquals(data, CELL_PAD_BTN_OFFSET_DIGITAL1, CELL_PAD_CTRL_DOWN, key, 0x8051);
		AddBitsIfKeycharEquals(data, CELL_PAD_BTN_OFFSET_DIGITAL1, CELL_PAD_CTRL_UP, key, 0x8052);
		AddBitsIfKeycharEquals(data, CELL_PAD_BTN_OFFSET_DIGITAL1, CELL_PAD_CTRL_RIGHT, key, 0x8053);

		AddBitsIfKeycharEquals(data, CELL_PAD_BTN_OFFSET_DIGITAL1, CELL_PAD_CTRL_LEFT, key, 'a');
		AddBitsIfKeycharEquals(data, CELL_PAD_BTN_OFFSET_DIGITAL1, CELL_PAD_CTRL_LEFT, key, 'A');

		AddBitsIfKeycharEquals(data, CELL_PAD_BTN_OFFSET_DIGITAL1, CELL_PAD_CTRL_DOWN, key, 's');
		AddBitsIfKeycharEquals(data, CELL_PAD_BTN_OFFSET_DIGITAL1, CELL_PAD_CTRL_DOWN, key, 'S');
		AddBitsIfKeycharEquals(data, CELL_PAD_BTN_OFFSET_DIGITAL1, CELL_PAD_CTRL_UP, key, 'W');
		AddBitsIfKeycharEquals(data, CELL_PAD_BTN_OFFSET_DIGITAL1, CELL_PAD_CTRL_UP, key, 'd');

		AddBitsIfKeycharEquals(data, CELL_PAD_BTN_OFFSET_DIGITAL1, CELL_PAD_CTRL_RIGHT, key, 'D');
		AddBitsIfKeycharEquals(data, CELL_PAD_BTN_OFFSET_DIGITAL1, CELL_PAD_CTRL_RIGHT, key, 'd');

		AddBitsIfKeycharEquals(data, CELL_PAD_BTN_OFFSET_DIGITAL2, CELL_PAD_CTRL_L1, key, 0x803a);
		AddBitsIfKeycharEquals(data, CELL_PAD_BTN_OFFSET_DIGITAL2, CELL_PAD_CTRL_R1, key, 0x803b);

		AddBitsIfKeycharEquals(data, CELL_PAD_BTN_OFFSET_PRESS_L1, 80, key, 0x803a);
		AddBitsIfKeycharEquals(data, CELL_PAD_BTN_OFFSET_PRESS_R1, 80, key, 0x803b);



		int w = Onyx::input_feature::mouseData.wheel;
		if (w > 0) {
			data->button[CELL_PAD_BTN_OFFSET_DIGITAL1] |= CELL_PAD_CTRL_UP;
		}
		else if (w < 0) {
			data->button[CELL_PAD_BTN_OFFSET_DIGITAL1] |= CELL_PAD_CTRL_DOWN;
		}

	}
	void WorldCnvKeyDown(OnyxCellPadData* data, int key) {
		using namespace Onyx::input_feature;
		bool up = false;
		bool down = false;

		if (key > 500) {
			System::Diagnostics::Debugger::WriteLine("[ManagedInputFeature] Unknown key: %x", key);
		}
		if (key == 'w' || key == 'W') {
			data->button[CELL_PAD_BTN_OFFSET_ANALOG_LEFT_Y] = 0;
			up = true;
		}
		else if (key == 's' || key == 'S') {
			data->button[CELL_PAD_BTN_OFFSET_ANALOG_LEFT_Y] = 255;
			down = true;
		}


		if (key == 'a' || key == 'A') {
			data->button[CELL_PAD_BTN_OFFSET_ANALOG_LEFT_X] = up || down ? 50 : 0;

		}
		if (key == 'd' || key == 'D') {
			data->button[CELL_PAD_BTN_OFFSET_ANALOG_LEFT_X] = up || down ? 200 : 255;
		}
		if (key == ' ') {
			data->button[CELL_PAD_BTN_OFFSET_DIGITAL2] |= CELL_PAD_CTRL_CROSS;
			data->button[CELL_PAD_BTN_OFFSET_PRESS_CROSS] |= 80;
		}
		if (key == 'q' || key == 'Q') {
			auto* player = Onyx::getLocalPlayer();
			player->drop();
		}
		if (key == 'f' || key == 'F') {
			//uintptr_t mal = fj::MALLOC(56);
			//if (mal > 0 && Crosshair::__elapsedFrames >= 0) {
			{
				//double PlayerPosition[3]{ 100,100,100 };
				//Hand::reset();
				//Crosshair::__active = true;
				//Crosshair::__elapsedFrames = -20;
				//uintptr_t packet[2];
				//Call<int>(0x58F548, mal, 6, PlayerPosition, 0x014C8E64, 0); // create action packet
				//Call<int>(0xE2C550, &packet, mal); // create weak ptr for it.
				//GameClientPacketListener::Send((uint)packet);
			}
		}
		if (key == 'E' || key == 'e') {

			data->button[CELL_PAD_BTN_OFFSET_DIGITAL2] |= CELL_PAD_CTRL_TRIANGLE;
			data->button[CELL_PAD_BTN_OFFSET_PRESS_TRIANGLE] |= 80;
		}
		if (key == 'G' || key == 'g') {
			data->button[CELL_PAD_BTN_OFFSET_DIGITAL2] |= CELL_PAD_CTRL_SQUARE;
			data->button[CELL_PAD_BTN_OFFSET_PRESS_SQUARE] |= 80;
		}
		if ((key == 'R' || key == 'r') && cameraCooldown == 0) {
			int T = Onyx::getLocalPlayer()->GetThirdPersonView();
			if (T == 0) {
				Onyx::getLocalPlayer()->SetThirdPersonView(2);
			}
			else {
				Onyx::getLocalPlayer()->SetThirdPersonView(0);
			}
			cameraCooldown = 80;
		}

		if (cameraCooldown > 0) {
			cameraCooldown--;
		}
		if (escape_delay > 0) {
			escape_delay--;
		}
		HotbarSelect(key);
		if (key == '\t') {
			data->button[CELL_PAD_BTN_OFFSET_DIGITAL1] |= CELL_PAD_CTRL_SELECT;
		}
		if (key == '\n') {
			data->button[CELL_PAD_BTN_OFFSET_DIGITAL1] |= CELL_PAD_CTRL_START;
		}
		//K_F1.setDown(key == 0x803A);

		if (kbData.mkey & CELL_KB_MKEY_L_CTRL) {
			data->button[CELL_PAD_BTN_OFFSET_DIGITAL1] |= CELL_PAD_CTRL_L3;
		}
		else if (kbData.mkey & CELL_KB_MKEY_L_SHIFT) {
			data->button[CELL_PAD_BTN_OFFSET_DIGITAL1] |= CELL_PAD_CTRL_R3;
		}

		if (key == 0x8029 && escape_delay == 0) {
			data->button[CELL_PAD_BTN_OFFSET_DIGITAL1] |= CELL_PAD_CTRL_START;
			escape_delay = 80;
		}
#if DISCARD
		if (key == 0x804c) {
			int R = cellPadDbgLddRegisterController(
				CELL_PAD_CAPABILITY_PS3_CONFORMITY | CELL_PAD_CAPABILITY_PRESS_MODE |
				CELL_PAD_CAPABILITY_HP_ANALOG_STICK
			);
			if (R == 0) {
				int handle = R;
				R = cellPadDbgLddSetDataInsertMode(R, CELL_PAD_LDD_INSERT_DATA_INTO_GAME_MODE_ON);
				if (R < 0) {
					goto err;
				}
				else {
					CellPadData data{ 0 };
					data.button[CELL_PAD_BTN_OFFSET_ANALOG_LEFT_X] =
						data.button[CELL_PAD_BTN_OFFSET_ANALOG_LEFT_Y] =
						data.button[CELL_PAD_BTN_OFFSET_ANALOG_RIGHT_X] =
						data.button[CELL_PAD_BTN_OFFSET_ANALOG_RIGHT_Y] = 0x80;

					data.button[0] = 1;
					data.button[1] = 1;
					data.len = 2;
					R = cellPadLddDataInsert(handle, &data);
					if (R < 0) {
						goto err;
					}
					else {
						R = cellPadLddUnregisterController(handle);
						if (R < 0) {
							goto err;
						}
						else {
							fj::notify(L"[FJ] Done");
						}
					}
				}
			}
			else {
			err:
				fj::clientPrint(L"[FJ] Error faking PS. %x", R);
			}
		}
		if (key == 0x804d && (!safecrash::shown)) {
			(g_UIController)->PlayUISFX(Sound::PORTAL_AMBIENT);
			safecrash::shown = true;
			safecrash::interval = 120;
			//*(unsigned char*)0x00884148 = 0x41;
			cellMsgDialogOpen(
				CELL_MSGDIALOG_BUTTON_TYPE_YESNO |
				CELL_MSGDIALOG_DIALOG_TYPE_NORMAL |
				CELL_MSGDIALOG_DEFAULT_CURSOR_YES,
				"Are you sure for exiting the game?", CellMsgDialogCallback(safecrash::dialog), 0, 0);
		}
#endif
		data->len = 27;
	}

	void UpdateRing() {
		using namespace Onyx::input_feature;

		if (kbInfo.now_connect > 0) {
			if (kbData.len > 0) {
				pression = kbData.len;
				for (int i = 0; i < 6; i++) {
					if (i >= pression) {
						ring[i] = 0;
					}
					else {
						ring[i] = kbData.keycode[i];
					}

				}

			}
		}
		if (kbData.keycode[0] == 0) {
			ring[0] = 0;
			ring[1] = 0;
			ring[2] = 0;
			ring[3] = 0;
			ring[4] = 0;
			ring[5] = 0;
			oldLength = pression;
			pression = 0;
			return;
		}
	}

	void WorldPadData(OnyxCellPadData* data) {
		using namespace Onyx::input_feature;
		if (Onyx::input_feature::click & CELL_MOUSE_BUTTON_1) {
			data->button[CELL_PAD_BTN_OFFSET_DIGITAL2] |= CELL_PAD_CTRL_R2;
			data->button[CELL_PAD_BTN_OFFSET_PRESS_R2] |= 80;
		}
		if (Onyx::input_feature::click & CELL_MOUSE_BUTTON_2) {
			data->button[CELL_PAD_BTN_OFFSET_DIGITAL2] |= CELL_PAD_CTRL_L2;
			data->button[CELL_PAD_BTN_OFFSET_PRESS_L2] |= 80;
		}

		if (Onyx::input_feature::click & CELL_MOUSE_BUTTON_3) {

			// pick block
			sub(opds::pick_block, Onyx::getLocalPlayer(), 0);
		}

		UpdateRing();
		for (int i = 0; i < 6; i++) {
			WorldCnvKeyDown(data, ring[i]);
		}


	}
	void MenuPadData(OnyxCellPadData* data) {
		UpdateRing();

		for (int i = 0; i < 6; i++) {
			MenuCnvKeyDown(data, ring[i]);
		}
	}

	void HandleMouseWheelOnWrld() {
		if ((g_UIController->IsModalActive()) || (!Minecraft::getGameStarted())) {
			return;
		}
		auto* player = Onyx::getLocalPlayer();
		if (!player) {
			return;
		}
		signed int w = Onyx::input_feature::mouseData.wheel;
		int* selection = player->getInventory()->getSelectedIndexEx();
		if (w < 0) {
			*selection = (*selection < 8) ? *selection + 1 : *selection;
			if (*selection == 8)
			{
				*selection = -1;
			}
			ForceHotbarUpdate();
		}
		else if (w > 0) {
			*selection = (*selection > 0 ? *selection - 1 : *selection);
			if (*selection == 0)
			{
				*selection = 8;
			}
			ForceHotbarUpdate();
		}


	}

	void HandleMouseWrld() {

		float X = Onyx::input_feature::mouse_delta.x;
		float Y = Onyx::input_feature::mouse_delta.y;

		auto* player = Onyx::getLocalPlayer();
		if (FPS_Last != 0.0f) {
			float inc = std::min(1.0f + (Framestat::fps - FPS_Last), 0.0f);
			X += inc * Onyx::input_feature::mouse_smoothing.x;
			Y += inc * Onyx::input_feature::mouse_smoothing.y;
		}
		if (Onyx::input_feature::mouseData.update) {
			float LX = (X + Onyx::input_feature::mouse_smoothing.x) / 3.0F;
			float LY = (Y + Onyx::input_feature::mouse_smoothing.y) / 3.0F;
			player->rotYaw += LX;
			player->rotPitch += LY;
			player->rotationYaw += LX;
			player->rotationPitch += LY;
		}
		HandleMouseWheelOnWrld();
		FPS_Last = Framestat::fps;
	}

	void TickMouseStageOnScene(UIScene* scene) {
		uint file = ((uint)scene) + 32;
		if (file > 0x7fff) {

			file = *(uint*)file;
			auto rootNode = *(_DWORD*)(file + 224);
			if (rootNode > 0x7F7F) {
				auto node2 = (FJ_FuiNode*)*(_DWORD*)(rootNode + 224);
				if (*(uint*)node2 != 0x013E3850) {
					//MouseStages::Tick(node2, Onyx::input_feature::mousePosition);
				}
			}
		}
	}

	void AfterFunctionOneReleased() {
		//MouseStages::IsKeyboardFocused = true;
		//Onyx::SetCameraman(Onyx::IsCameraman = !Onyx::IsCameraman);
	}

	void OnPauseMenuTick() {
		//if (MemoryInput::GetButtonsState() > 0) {
		//	MouseStages::IsKeyboardFocused = true;
		//}
		//TickMouseStageOnScene((UIScene*)__UISCENE_PAUSEMENU);
		EnsureNormalSpeed();

	}

	void ModPadData(OnyxCellPadData* data) {
		if (Onyx::input_feature::mouse_info.now_connect > 0 && Onyx::input_feature::kbInfo.now_connect > 0) {
			if (Minecraft::getGameStarted() && (!g_UIController->IsModalActive())) {
				WorldPadData(data);
			}
			else if (Minecraft::getGameStarted()) {

				//if (Onyx::IsMessageBoxFocused()) {
				//	TickMouseStageOnScene(Onyx::FocusedScene);
				//}
				MenuPadData(data);
			}
			else if (g_UIController->IsModalActive()) {
				if (*(int*)Onyx::FocusedScene == 0x013F84C8) {

					return;
				}

				auto topScene = (UIScene*)g_UIController->GetTopScene();
				if (!topScene) {
#if TEST
					System::Diagnostics::Debugger::WriteLine("[ManagedInputFeature] UIController cannot determine the focused scene. (%x)", topScene);
#endif
					return;
				}
				if (topScene->getFile()) {
					if (MinecraftTick::topScene != (int)topScene) {
						MinecraftTick::topScene = (int)topScene;
#if TEST
						System::Diagnostics::Debugger::WriteLine("[ManagedInputFeature] Gain focus; scene: (%x)", topScene);
#endif
					}
					TickMouseStageOnScene((UIScene*)MinecraftTick::topScene);
					EnsureNormalSpeed();
					MenuPadData(data);
					//MouseStages::Tick(*(FJ_FuiNode**)topScene->getFile()->getRootNode(), Onyx::input_feature::mousePosition);
				}
#if TEST
				else {
					System::Diagnostics::Debugger::WriteLine("[ManagedInputFeature] Scene: %x doesn't have an file storage.", topScene);
				}
#endif
			}
		}

	}

	void Tick() {

		if (Minecraft::getGameStarted()) {
			if (!g_UIController->IsModalActive()) {
				HandleMouseWrld();
			}
		}

	}

}
namespace PatchedInputTick {

	CREATE_DUMMY_STUB(int, __tick_containers__, ...);
	CREATE_DUMMY_STUB(int, __tick_input_manager__, ...);
	void SanitizeInventoryPointing();

	int TickContainers(int a, int b, int c) {
		float* pos = (float*)(a + 0x10);

		//if (container != a) {
		//	System::Diagnostics::Debugger::WriteLine("Container: %x", a);
		//	container = a;
		//}

		float fac = -0.0099999998;
		float x = (float)Onyx::input_feature::mouseData.x_axis / 1.15f;
		float y = (float)Onyx::input_feature::mouseData.y_axis / 1.15f;
		pos[0] += x;
		pos[1] += y;
		int R = __tick_containers__(a, b, c);
		return R;
	}
	any TickInputManager(int instance) {
		any R = __tick_input_manager__(instance);

		MinecraftTick::Tick();

		return R;
	}

	void Write() {
		SanitizeInventoryPointing();

		hookfunction(opds::input_manager_tick, take(TickInputManager), take(__tick_input_manager__));
		hookfunction(opds::tick_containers, take(TickContainers), take(__tick_containers__));
	}
}