#pragma once
#include "System.h"
#include "cell\keyboard\libkb.h"
#include "cell\libkey2char.h"
#include "include\diag.h"
#include "opds.h"
#ifdef ONYX
#include "debug.h"
#endif
namespace Keyboard {

#ifdef ONYX
	Trampoline<int, cInput*> gCinput_InitializeKeyboard;
#endif
#ifndef ONYX
#define __printf System::Diagnostics::Debugger::WriteLine
	class cInput;
	CREATE_DUMMY_STUB(int, InitializeKeyboard_s, ...);

#endif


	li_ptr GetCodeTypeLI() {
		return opds::GetCodeTypeLI();
	}

	li_ptr GetReadModeLI() {
		return opds::GetReadModeLI();
	}
	/// <summary>
	/// Gets the game input manager instance.
	/// </summary>
	/// <returns>cInput* const</returns>
	cInput* const getInputManager() {
		return *(cInput**)0x16BD748;
	}
	void ForceCinputPacketMode() {
		GetReadModeLI().setValue(CELL_KB_RMODE_PACKET);
		GetCodeTypeLI().setValue(CELL_KB_CODETYPE_RAW);
	}
	void ForceCinputTextMode() {

		GetReadModeLI().setValue(CELL_KB_RMODE_INPUTCHAR);
		GetCodeTypeLI().setValue(CELL_KB_CODETYPE_ASCII);
	}
	int InitializeKeyboard(cInput* instance) {
		// ignore game's keyboard setup; manually initialize.
		return 0;
	}
	void HookCaller() {
		hookfunction(opds::initialize_keyboard, take(InitializeKeyboard), take(InitializeKeyboard_s));
	}
	void InitializeTypeCodeConverter();
}
