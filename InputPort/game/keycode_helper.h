#pragma once
#include "System.h"
#include "include\func.h"
class KeyCodeButton {
	num value;
	bool wasPressing = false;
	bool isPressing = false;
	System::Func<void> release_callback;
public:
	KeyCodeButton(num value) : release_callback(nullptr) {
		this->value = value;
	}

	void setDown(bool isit) {
		wasPressing = isPressing;
		if (wasPressing != isit && (!isit)) {
			release_callback();
		}
		isPressing = isit;
	}
	bool isDown() const {
		return isPressing;
	}
	void afterRelease(System::Func<void> callback) {
		release_callback = callback;
	}

};

namespace KeyCodeHelper {
	typedef wchar_t wide;
	typedef byte single;

	const static single DELETE = 8;
	const static wide UP = 32850;
	const static wide DOWN = 32849;
	const static wide LEFT = 32848;
	const static wide RIGHT = 32849;

	const static single SPACE = ' ';
	const static single W = 'w';
	const static single A = 'a';
	const static single S = 's';
	const static single D = 'd';
	const static single ZERO = '0';
	const static single ONE = ZERO + 1;
	const static single TWO = ONE + 1;
	const static single THREE = TWO + 1;
	const static single FOUR = THREE + 1;
	const static single FIVE = FOUR + 1;
	const static single SIX = FIVE + 1;
	const static single SEVEN = SIX + 1;
	const static single EIGHT = SEVEN + 1;
	const static single NINE = EIGHT + 1;

	const static single TAB = 8;
	const static wide ESCAPE = 32809;
	const static wide CAPS = 32825;

	const static wide HYPHEN = 32825; // Symbol -> -
	const static single DOT = '.'; // Symbol -> .
	const static single COMMA = ',';// Symbol -> , 

	const static wide INTRO = 16394;
	const static wide SCROLL_LOCK = 32839;
	const static wide INSERT = 32841;
	const static wide BEGIN = INSERT + 1;
	const static wide PAGE_UP = BEGIN + 1;
	const static wide SUPRESS = PAGE_UP + 1;
	const static wide END = SUPRESS + 1;
	const static wide PAGE_DOWN = END + 1;
	const static wide CONTEXT = 32869;
	const static wide NUMERIC_SLASH = 16431;
	const static wide PAUSE = 32840;
	const static wide PRINT = 32838;

	const static wide NUMERIC_ASTERISK = 16426;
	const static wide NUMERIC_HYPHEN = 16429;
	const static wide NUMERIC_PLUS = 16427;
	const static wide NUMERIC_SUPRESS = 42228;


	const static wide FUNCTION1 = 32826;
	const static wide FUNCTION2 = FUNCTION1 + 1;
	const static wide FUNCTION3 = FUNCTION2 + 1;
	const static wide FUNCTION4 = FUNCTION3 + 1;
	const static wide FUNCTION5 = FUNCTION4 + 1;
	const static wide FUNCTION6 = FUNCTION5 + 1;
	const static wide FUNCTION7 = FUNCTION6 + 1;
	const static wide FUNCTION8 = FUNCTION7 + 1;
	const static wide FUNCTION9 = FUNCTION8 + 1;
	const static wide FUNCTION10 = FUNCTION9 + 1;
	const static wide FUNCTION11 = FUNCTION10 + 1;
	const static wide FUNCTION12 = FUNCTION11 + 1;
	const static wide ENTER = 10;



}