#pragma once
#include "game\fui.h"
#include "minecraft\MultiplayerLocalPlayer.h"
#include "minecraft.hpp"
namespace Onyx {

	UIScene* FocusedScene = nullptr;
	UIScene* Hud = nullptr;

	/* [Nullable] Obtains the current player storage. In-game only.*/
	MultiplayerLocalPlayer* getLocalPlayer() {
		return (MultiplayerLocalPlayer*)Game::Get()->instance->localplayer;
	}
	void ForceUpdateHudIfPossible();

}