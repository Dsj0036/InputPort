#pragma once
#include "game.h"
#include "System.h"
#include "game\minecraft\tesselator.h"
#include "vectors.h"
namespace Gui
{
	void __draw_font__(uint32_t font, uint32_t r4, uint32_t x, uint32_t y, uint32_t color, uint32_t r8, uint32_t r9) {
		Call<uint32_t>(0xA7E2E8, font, r4, x, y, color, r8, r9);
	}

	template<typename ...Arguments>
	void DrawText(int x, int y, wchar* frm, Arguments...s) {
		wchar_t buffer[128]{ 0 };
		printfw(buffer, 128, frm, s...);
		RString LOC = buffer;
		__draw_font__(Game::Get()->instance->Font, (uint)&LOC, x, y, -1l, 0, 1);
	}
	void DrawText(int x, int y, wchar* text, uint32_t col = -1) {
		RString LOC = text;
		__draw_font__(Game::Get()->instance->Font, (uint)&LOC, x, y, col, 0, 1);
	}
	void DrawText(int x, int y, char* text) {
		wchar_t buffer[256];
		printfw(buffer, 256, L"%s", text);
		RString LOC = buffer;
		__draw_font__(Game::Get()->instance->Font, (uint)&LOC, x, y, -1l, 0, 1);
	}
	// Draws texts with standard's library
	void DrawText2(int x, int y, wchar* text) {
		std::wstring wstr = text;
		__draw_font__(Game::Get()->instance->Font, (uint)&wstr, 0, 0, 0xFFFFFFFF, 0, 1);
	}

	template<typename ...Arguments>
	void DrawText2(int x, int y, wchar* text, uint32_t color, Arguments...s) {
		wchar_t buffer[128];
		printfw(buffer, 128, text, s...);
		std::wstring buf = buffer;
		__draw_font__(Game::Get()->instance->Font, (uint)&buf, x, y, color, 0, 1);
		buf.erase();
		buf.clear();
	}
}