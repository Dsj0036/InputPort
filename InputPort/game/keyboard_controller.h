#pragma once
#include "System.h"
#include "cell\keyboard.h"
#include "cell\mouse.h"
#include "cell\pad.h"
#include "game.h"
#include "console_ui_controller.hpp"
class OnyxCellPadData {
public:
	int32_t len;
	uint16_t button[19];
};

class OnyxCellKeyboardData {
public:
	uint32_t   led;
	uint32_t   mkey;
	int32_t     len;
	uint16_t keycode[12];
	void clear() {
		sys::memset(keycode, 0, sizeof(keycode));
	}
	bool atLeastEquals(wchar_t value) const {
		return
			keycode[0] == value ||
			keycode[1] == value ||
			keycode[2] == value ||
			keycode[3] == value ||
			keycode[4] == value ||
			keycode[5] == value;
	}
	short toFunctionalKey(byte slot) {
		int min = 0x803a;

		bool R = keycode[slot] >= min && keycode[slot] <= (min + 12);

		if (R) {
			return keycode[slot] - min;
		}
		return 0x7F;

	}
	// returns 0 if no key 
	byte getFunctionalKey() {
		for (byte i = 0; i < 12; i++) {
			if (toFunctionalKey(i) != 0x7F) {
				return keycode[i];
			}
		}
		return 0;
	}
	bool isNumericPressed(byte ten) const {
		if (ten >= '0' && ten <= '9') {
			return atLeastEquals(ten);
		}
		return false;
	}
	bool isAlphaPressed(char ascii_char)const {
		if (ascii_char >= 'A' && ascii_char <= 'Z') {
			return atLeastEquals(_sys_tolower(ascii_char));
		}
		else {
			return atLeastEquals(ascii_char);
		}
	}


};


int32_t readKeyboard(uint32_t port, OnyxCellKeyboardData* out) {
	return cellKbRead(port, (CellKbData*)out);
}
class Keys {
	Keys() = delete;
public:
	enum Enum {
		NONE,
		ESCAPE,
		FUNCTION,
		TAB,
		CTRL,
		SHIFT,
		L_ALT,
		VERTICAL_SLASH,
		DELETE,
		ENTER,
		SPACE,
		ARROW_UP,
		ARROW_DOWN,
		ARROW_LEFT,
		ARROW_RIGHT,
		CONTEXT,
		Q,
		W,
		E,
		R,
		T,
		Y,
		A,
		S,
		D,
		F,
		C,
		MAX_ARRAY,
	};

	static uint16_t get(Keys::Enum key) {
		switch (key)
		{
			CASE_RETURN(Keys::NONE, 0);
			CASE_RETURN(ESCAPE, 0x8029);
			CASE_RETURN(FUNCTION, 0x803a);
			CASE_RETURN(TAB, 9);
			CASE_RETURN(CTRL, 0x700000);
			CASE_RETURN(SHIFT, 0x700001);
			CASE_RETURN(L_ALT, 0x700002);
			CASE_RETURN(VERTICAL_SLASH, 0x60);
			CASE_RETURN(DELETE, 8);
			CASE_RETURN(ENTER, 0xA);
			CASE_RETURN(SPACE, 0X20);
			CASE_RETURN(ARROW_UP, 0);
			CASE_RETURN(ARROW_DOWN, 0);
			CASE_RETURN(ARROW_LEFT, 0);
			CASE_RETURN(ARROW_RIGHT, 0);
			CASE_RETURN(CONTEXT, 0x8065);
			CASE_RETURN(Q, 'A');
			CASE_RETURN(W, 'W');
			CASE_RETURN(E, 'E');
			CASE_RETURN(R, 'R');
			CASE_RETURN(T, 'T');
			CASE_RETURN(Y, 'Y');
			CASE_RETURN(A, 'A');
			CASE_RETURN(S, 0);
			CASE_RETURN(D, 0);
			CASE_RETURN(F, 0);
			CASE_RETURN(C, 0);
			CASE_RETURN(MAX_ARRAY, 0);

		default:
			break;
		}
	}
};

class OnyxKeyRing {
public:
	bool ring[Keys::MAX_ARRAY];
	bool function[12];

	bool isKeyDown(Keys::Enum value) const {
		return ring[value];
	}
	void Update(OnyxCellKeyboardData* kb) {
		ring[Keys::ESCAPE] = kb->atLeastEquals(Keys::get(Keys::ESCAPE));
		ring[Keys::SPACE] = kb->atLeastEquals(Keys::get(Keys::SPACE));
		ring[Keys::DELETE] = kb->atLeastEquals(Keys::get(Keys::DELETE));
		ring[Keys::CONTEXT] = kb->atLeastEquals(Keys::get(Keys::CONTEXT));
		ring[Keys::FUNCTION] = kb->atLeastEquals(Keys::get(Keys::FUNCTION));
		ring[Keys::SHIFT] = kb->mkey | CELL_KB_MKEY_L_SHIFT;
		ring[Keys::CTRL] = kb->mkey | CELL_KB_MKEY_L_CTRL;
		ring[Keys::L_ALT] = kb->mkey | CELL_KB_MKEY_L_ALT;
		ring[Keys::VERTICAL_SLASH] = kb->atLeastEquals(Keys::get(Keys::VERTICAL_SLASH));

		for (int i = 0; i < 12; i++) {
			function[i] = kb->atLeastEquals(Keys::get(Keys::FUNCTION) + i);
		}

	}
	bool isFunctionDown(byte func) const {
		return function[func];
	}
};

class SingleKey {
	void(*callback)(bool) = nullptr;
	bool state = false;
	bool toggle = false;
public:
	bool TickHold(bool currentState) {
		if (this->state != currentState) {
			if (this->state == true && currentState == false) {
				if (callback) {
					callback(toggle);
				}
			}
			this->state = currentState;
			return true;
		}
		return false;
	}

	void OnKeyReleased(void(*callback)(bool current)) {
		this->callback = callback;
	}
};


namespace KeyboardController {

#define CONVERT(code, button) |= (IsPressed(len, ring, code) ? button : 0)
#define CONVERT_PRESS(code, butn, press) |= (IsPressed(len, ring, code) ? butn : 0);\
	pad->button[press] = 20\


	// todo: https://help.minecraft.net/hc/en-us/articles/360059148111-Hotkeys-in-Minecraft-Java-Edition
	bool IsPressed(int& len, uint64_t& ring, uint32_t key) {
		uint16_t keycode0 = (uint16_t)(ring & 0xFFFF);
		uint16_t keycode1 = (uint16_t)((ring >> 16) & 0xFFFF);
		uint16_t keycode2 = (uint16_t)((ring >> 32) & 0xFFFF);
		uint16_t keycode3 = (uint16_t)((ring >> 48) & 0xFFFF);
		if (keycode0 == key ||
			(keycode1 == key && len > 1) ||
			(keycode2 == key && len > 2) ||
			(keycode3 == key && len > 3)) {

			return true;
		}
		return false;
	}

	
#ifdef ONYX

	void Apply(uint64_t& ring, CellKbData* kb, CellPadData* pad) {

		int& len = kb->len;

		if ((!Minecraft::IS_MODAL_ACTIVE) && Minecraft::getGameStarted()) {

			pad->button[CELL_PAD_BTN_OFFSET_DIGITAL2]
				CONVERT_PRESS('r', CELL_PAD_CTRL_SQUARE, CELL_PAD_BTN_OFFSET_PRESS_SQUARE);
			pad->button[CELL_PAD_BTN_OFFSET_DIGITAL2]
				CONVERT_PRESS('R', CELL_PAD_CTRL_SQUARE, CELL_PAD_BTN_OFFSET_PRESS_SQUARE);

			pad->button[CELL_PAD_BTN_OFFSET_DIGITAL2]
				CONVERT_PRESS('E', CELL_PAD_CTRL_TRIANGLE, CELL_PAD_BTN_OFFSET_PRESS_TRIANGLE);
			pad->button[CELL_PAD_BTN_OFFSET_DIGITAL2]
				CONVERT_PRESS('e', CELL_PAD_CTRL_TRIANGLE, CELL_PAD_BTN_OFFSET_PRESS_TRIANGLE);

			pad->button[CELL_PAD_BTN_OFFSET_DIGITAL2]
				CONVERT_PRESS('q', CELL_PAD_CTRL_CIRCLE, CELL_PAD_BTN_OFFSET_PRESS_CIRCLE);
			pad->button[CELL_PAD_BTN_OFFSET_DIGITAL2]
				CONVERT_PRESS('Q', CELL_PAD_CTRL_CIRCLE, CELL_PAD_BTN_OFFSET_PRESS_CIRCLE);

			pad->button[CELL_PAD_BTN_OFFSET_DIGITAL2]
				CONVERT_PRESS(' ', CELL_PAD_CTRL_CROSS, CELL_PAD_BTN_OFFSET_PRESS_CROSS);

			pad->button[CELL_PAD_BTN_OFFSET_DIGITAL1]
				CONVERT('\t', CELL_PAD_CTRL_SELECT);


			pad->button[CELL_PAD_BTN_OFFSET_DIGITAL2]
				CONVERT_PRESS('\n', CELL_PAD_CTRL_CROSS, CELL_PAD_BTN_OFFSET_PRESS_CROSS);


			pad->button[CELL_PAD_BTN_OFFSET_DIGITAL1]
				CONVERT(KeyCodeHelper::ESCAPE, CELL_PAD_CTRL_START);


			pad->button[CELL_PAD_BTN_OFFSET_DIGITAL1] |= (kb->mkey & CELL_KB_MKEY_L_SHIFT) ? CELL_PAD_CTRL_R3 : 0;
			pad->button[CELL_PAD_BTN_OFFSET_DIGITAL1] |= (kb->mkey & CELL_KB_MKEY_L_CTRL) ? CELL_PAD_CTRL_L3 : 0;

		}
		else if ((!Minecraft::getGameStarted()) || (!Minecraft::IS_MODAL_ACTIVE)) {


			pad->button[CELL_PAD_BTN_OFFSET_DIGITAL2]
				CONVERT_PRESS(' ', CELL_PAD_CTRL_CROSS, CELL_PAD_BTN_OFFSET_PRESS_CROSS);

			pad->button[CELL_PAD_BTN_OFFSET_DIGITAL2]
				CONVERT_PRESS(KeyCodeHelper::ENTER, CELL_PAD_CTRL_CROSS, CELL_PAD_BTN_OFFSET_PRESS_CROSS);
			pad->button[CELL_PAD_BTN_OFFSET_DIGITAL1]
				CONVERT_PRESS(KeyCodeHelper::W, CELL_PAD_CTRL_UP, CELL_PAD_BTN_OFFSET_PRESS_UP);
			pad->button[CELL_PAD_BTN_OFFSET_DIGITAL1]
				CONVERT_PRESS(KeyCodeHelper::S, CELL_PAD_CTRL_DOWN, CELL_PAD_BTN_OFFSET_PRESS_DOWN);
			pad->button[CELL_PAD_BTN_OFFSET_DIGITAL1]
				CONVERT_PRESS(KeyCodeHelper::A, CELL_PAD_CTRL_LEFT, CELL_PAD_BTN_OFFSET_PRESS_LEFT);
			pad->button[CELL_PAD_BTN_OFFSET_DIGITAL1]
				CONVERT_PRESS(KeyCodeHelper::D, CELL_PAD_CTRL_RIGHT, CELL_PAD_BTN_OFFSET_PRESS_RIGHT);

			// Arrows


			pad->button[CELL_PAD_BTN_OFFSET_DIGITAL1]
				CONVERT_PRESS(KeyCodeHelper::UP, CELL_PAD_CTRL_UP, CELL_PAD_BTN_OFFSET_PRESS_UP);
			pad->button[CELL_PAD_BTN_OFFSET_DIGITAL1]
				CONVERT_PRESS(KeyCodeHelper::DOWN, CELL_PAD_CTRL_DOWN, CELL_PAD_BTN_OFFSET_PRESS_DOWN);
			pad->button[CELL_PAD_BTN_OFFSET_DIGITAL1]
				CONVERT_PRESS(KeyCodeHelper::LEFT, CELL_PAD_CTRL_LEFT, CELL_PAD_BTN_OFFSET_PRESS_LEFT);
			pad->button[CELL_PAD_BTN_OFFSET_DIGITAL1]
				CONVERT_PRESS(KeyCodeHelper::RIGHT, CELL_PAD_CTRL_RIGHT, CELL_PAD_BTN_OFFSET_PRESS_RIGHT);


			pad->button[CELL_PAD_BTN_OFFSET_DIGITAL2]
				CONVERT_PRESS(KeyCodeHelper::ESCAPE, CELL_PAD_CTRL_CIRCLE, CELL_PAD_BTN_OFFSET_PRESS_CIRCLE);


		}
		len = 27;
	}
#endif

	void ApplyMouse(byte buttons, bool CTRL, CellMouseData* mouseData, CellPadData* pad) {
		bool mainMenu = !Minecraft::getGameStarted();
		if (mainMenu) {
			pad->len = 27;

			int CTRL_SCROLL = (mouseData->wheel == 0 ? 0 : (mouseData->wheel > 0 ? CELL_PAD_CTRL_L2 : CELL_PAD_CTRL_R2));

			pad->button[CELL_PAD_BTN_OFFSET_DIGITAL2] |= CTRL_SCROLL;
			if (CTRL_SCROLL != 0) {
				int CTRL_OFFSET = CTRL_SCROLL == CELL_PAD_CTRL_L2 ? CELL_PAD_BTN_OFFSET_PRESS_L2 : CELL_PAD_BTN_OFFSET_PRESS_R2;
				pad->button[CTRL_OFFSET] |= CTRL_SCROLL;
			}

		}
		else if (g_UIController->IsModalActive())
		{
			pad->len = 27;
			if (mouseData->x_axis != 0 && mouseData->y_axis != 0) {


				uint16_t msx = 0x80 + (mouseData->x_axis * 2);
				uint16_t msy = 0x80 + (mouseData->y_axis * 2);

				//SmoothTuple(msx, msy, 0.4);

				pad->button[CELL_PAD_BTN_OFFSET_ANALOG_LEFT_X] = msx;
				pad->button[CELL_PAD_BTN_OFFSET_ANALOG_LEFT_Y] = msy;

			}

			/// INVENTORY TRIANGLE
			int press_modifier = CTRL ? CELL_PAD_CTRL_TRIANGLE : CELL_PAD_CTRL_CROSS;
			int press_offset = CTRL ? CELL_PAD_BTN_OFFSET_PRESS_SQUARE : CELL_PAD_BTN_OFFSET_PRESS_CROSS;
			if (buttons & CELL_MOUSE_BUTTON_1) {
				pad->button[press_offset] = 20;
				pad->button[CELL_PAD_BTN_OFFSET_DIGITAL2] |= press_modifier;
			}
			if (buttons & CELL_MOUSE_BUTTON_2) {

				pad->button[CELL_PAD_BTN_OFFSET_PRESS_SQUARE] = 20;
				pad->button[CELL_PAD_BTN_OFFSET_DIGITAL2] |= CELL_PAD_CTRL_SQUARE;
			}

		}

	}
}