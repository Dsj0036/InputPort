#pragma once
#include "System.h"
#include "patched_input.h"
#include "keyboard_controller.h"
#include "keyboard.h"
#include "managed_input_feature.h"
#include "patched_input_tick.h"
namespace PatchedInput {

	

	CREATE_DUMMY_STUB(int, Input_StubSpace, ...);

	int Override(int port, OnyxCellPadData* paddata) {
		int R = Input_StubSpace(port, paddata);
		if (port == 0) {
			uint32_t R = Onyx::input_feature::findPorts();
			Onyx::input_feature::mouse_thread::work = Onyx::input_feature::mouse_info.now_connect > 0;
			Onyx::input_feature::mouseTick();
			if (Onyx::input_feature::kbInfo.now_connect > 0) {
				Onyx::input_feature::read(true);	
			}
			MinecraftTick::ModPadData(paddata);
		}

		return R;
	}
	void Write() {
		hookfunction(opds::pad_read, take(Override), take(Input_StubSpace));
	}
}