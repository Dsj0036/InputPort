#pragma once
#include "System.h"
#include "include\diag.h"
#include "include\ptr.h"
#include "opds.h"
#include "client.h"
namespace PatchedHud {
	CREATE_DUMMY_STUB(int, __hud__, int);

	int Update(int R) {
		Onyx::Hud = (UIScene*)R;
		R = __hud__(R);
		return R;
	}

	void Write() {
		hookfunction(opds::hud_tick, take(Update), take(__hud__));
	}
}