#pragma once
#include "System.h"
#include "opds.h"
#include "framestat.h"
#include "tex.h"
#include "gl.hpp"
namespace PatchedFullscreen {
	int sFullscreen(...); // reference to game's original behaviour returning stub, recreated by trap2.

	int Fullscreen(int instance) {
		int R = sFullscreen(instance);

		Framestat::Tick();

		if (!Minecraft::getGameStarted()) {
			
				
		}

		return R;
	}
	TRAP2(int, opds::fullscreen, Fullscreen);

}