#pragma once
#include "System.h"
#include "include\diag.h"
#include "vectors.h"
#include "keyboard.h"
#include "game\keyboard_controller.h"
#include "game.h"
namespace Onyx {

	namespace input_feature {
		namespace mouse_thread {
			thread id;
			bool work = true;
			short interval = 0;
			bool isRanning = 0;
			signed int tick = 0;

			float MouseSmoothing = 0.4f; // Factor de suavizado
			bool mustTick() {
				if (tick < 0) {
					if (interval == 0) {
						interval = 1000;
					}
					tick = interval;
				}
				return tick == 0;
			}
		}
		System::Diagnostics::Stopwatch stopwatch;
		System::Diagnostics::Stopwatch stopwatch_kb;
		Vec2 mousePosition;
		bool isPacket = false;
		byte mouse_port;
		byte keyboard_port;

		Vector2 mouse_smoothing;
		Vector2 mouse_delta;
		OnyxCellKeyboardData kbData;
		CellKbInfo kbInfo;
		CellMouseData mouseData;
		CellMouseInfo mouse_info;
		OnyxKeyRing keyRing;
		byte click = 0;
		long double NanoDelayLast = 0;
		long double NanoCurrent = 0;
		double readInterval = 3.0;
		// READONLY
		uint64_t currentTimeNano = 0;

		// delay mouse
		uint64_t final_mouse_delay = 0;
		// delay keyb
		uint64_t final_keyb_delay = 0;

		CellKbInfo* getCellKbInfo() {
			return &kbInfo;
		}
		bool isReady() {
			return mouse_info.now_connect > 0 && getCellKbInfo()->now_connect > 0;
		}
		double calculateSmoothnessDelayBased();
		double calculateSmoothnessFrametimeBased();

		void readTime() {
			currentTimeNano = Minecraft::System::processTimeInNanosecs();
		}
		void clearRing() {
			kbData.clear();
		}
		void updateRaw(bool mouse) {
			if (mouse) {
				click = mouseData.update ? mouseData.buttons : click;
			}
			else {
				keyRing.Update(&kbData);
			}
		}

		uint32_t readMouseEx() {
			uint32_t err = cellMouseGetData(mouse_port, &mouseData);
			if (err == 0) {
				updateRaw(true);
			}
			return err;
		}
		uint32_t read(bool forced = false) {
			if (forced) {
				uint err = readKeyboard(keyboard_port, &kbData);
				if (err < 0) {
					clearRing();
					return err;
				}
				else {
					updateRaw(false);
				}
			}
			else {
				if (!isReady()) {
					return EAGAIN;
				}
				NanoCurrent = currentTimeNano;

				if ((NanoCurrent - NanoDelayLast) > (readInterval * 0xF4240)) {
					NanoDelayLast = NanoCurrent;

					stopwatch_kb.Stop();

					final_keyb_delay = stopwatch_kb.getDeltaMilliseconds();

					//uint err = cellMouseGetData(mouse_port, &mouseData);
					uint err = readKeyboard(keyboard_port, &kbData);
					if (err < 0) {
						clearRing();
						return err;
					}
					else {
						updateRaw(false);
					}
					stopwatch_kb.Restart();
				}
			}
			return CELL_KB_ERROR_DATA_READ_FAILED;
		}
		void mouseTick() {
			if (mouse_thread::work) {
				if (mouse_thread::mustTick()) {
					uint32_t R = readMouseEx();
					if (R < 0) {
						System::Diagnostics::Debugger::WriteLine("readMouseEx: %x", R);
					}
					else {
						mouse_delta = { mouseData.x_axis, mouseData.y_axis };
						mouse_smoothing.x = mouse_thread::MouseSmoothing * mouse_delta.x + (1 - mouse_thread::MouseSmoothing) * mouse_smoothing.x;
						mouse_smoothing.y = mouse_thread::MouseSmoothing * mouse_delta.y + (1 - mouse_thread::MouseSmoothing) * mouse_smoothing.y;

						mousePosition.x += mouse_smoothing.x;
						mousePosition.y += mouse_smoothing.y;

						mousePosition.Clamp2(Vector2::Empty, { 1270, 710 });
					}
				}

			}
		}
		void mouseThread(uint64_t) {
			mouse_thread::isRanning = true;
			while (Minecraft::getMustLoopProcess()) {
				if (mouse_thread::work) {
					mouseTick();
				}
				else {
					sleep(100);
				}

			}
			mouse_thread::isRanning = false;
		}

		uint32_t findPorts() {
			uint32_t err = cellKbGetInfo(getCellKbInfo());
			if (err < 0) {
#if TEST
				System::Diagnostics::Debugger::WriteLine("[ManagedInputFeature] cellKbGetInfo: %x", err);
#endif
				return err;
			}
			auto* inf = getCellKbInfo();
			for (int i = 0; i < 4; i++) {
				if (inf->status[i]) {
					if (keyboard_port != i) {
						System::Diagnostics::Debugger::WriteLine("[ManagedInputFeature] keyboard found: %i", i);
					}

					keyboard_port = i;
					Keyboard::ForceCinputPacketMode();
					cellKbSetCodeType(keyboard_port, CELL_KB_CODETYPE_ASCII);
					cellKbSetReadMode(keyboard_port, CELL_KB_RMODE_PACKET);
					isPacket = true;
					break;
				}
			}
			err = cellMouseGetInfo(&mouse_info);
			if (err < 0) {
				return err;
			}
			for (int i = 0; i < 4; i++) {
				if (mouse_info.status[i]) {
					mouse_port = i;
					break;
				}
			}
			return err;


		}
		// from cinput
		void normalTickSequenceEverything() {
			if (!isReady()) {
				uint32_t R = findPorts();
				mouse_thread::work = mouse_info.now_connect > 0;
				if (R < 0) {
					System::Diagnostics::Debugger::WriteLine("findPorts returned: %x\n", R);
				}
			}
			if (kbInfo.now_connect > 0) {
				read();
			}
		}

		void setPacketMode() {
			Keyboard::ForceCinputPacketMode();
			cellKbSetCodeType(keyboard_port, CELL_KB_CODETYPE_ASCII);
			cellKbSetReadMode(keyboard_port, CELL_KB_RMODE_PACKET);
			isPacket = true;
		}
		void setTextMode() {
			Keyboard::ForceCinputTextMode();
			cellKbSetCodeType(keyboard_port, CELL_KB_CODETYPE_ASCII);
			cellKbSetReadMode(keyboard_port, CELL_KB_RMODE_INPUTCHAR);
			isPacket = false;
		}

		void Initialize() {
			cellKbInit(2);
			cellMouseInit(1);
			stopwatch.Restart();
			setPacketMode();
			//sys_ppu_thread_create(&mouse_thread::id, mouseThread, 0, 1200, 12000, 0, "");
		}
	}
	namespace Kbm {
		bool isDown(Keys::Enum value) {
			return input_feature::keyRing.isKeyDown(value);
		}
		double getMouseX() {
			return static_cast<double>((byte)input_feature::mouseData.x_axis) * 0.5;
		}
		double getMouseY() {
			return static_cast<double>((byte)input_feature::mouseData.y_axis) * 0.5;
		}


	}
}