#pragma once
#include "opds.h"
#include "System.h"
#include "client.h"
namespace PatchedSceneNavigation {
	CREATE_DUMMY_STUB(int, __gotFocus__, int, int, int);
	
	int gainFocusOverride(int doc, int dummy, int dummy2) {
		Onyx::FocusedScene = nullptr; // update, and stop all dependants.
		
		int r = __gotFocus__(doc, dummy, dummy2); // execute original stub.
		
		log("Gain focus: %x", doc);

		Onyx::FocusedScene = (UIScene*)doc; // put back.

		return r;
	}
	

	void Write() {
		hookfunction(opds::documentGotFocus, take(gainFocusOverride), take(__gotFocus__));
	}
}