#pragma once
#include "sys/system_types.h"
#include "game/game.h"

// misaki-gpt.
namespace Framestat {
	float fps;

	static int count = 0;
	static uint64_t basetime = 0;
	int toInt(float input) {
		bool negative = input < 0.0f;
		if (negative) input *= -1.0f;

		uint32_t output = static_cast<uint32_t>(input);
		if (negative) {
			output -= 0x80000000;
			output = 0x80000000 - output;
			output -= 1;
		}
		return output;
	}
	void Tick()
	{
		if (count == 0) {
			basetime = Minecraft::System::processTimeInMillisecs();
		}
		else {
			uint64_t now = Minecraft::System::processTimeInMillisecs();
			if (now - basetime >= 1000) {
				fps = (toFloat(count * 1000) / toFloat(now - basetime) + 0.5f);
				basetime = now;
				count = 0;
			}
		}
		count++;
	}
	int getFPS() {
		return cast<float, int>(fps);
	}
}
#pragma once