#include "game\define.h"
#include <cellstatus.h>
#include <sys/prx.h>
#include "include\diag.h"
#include "game\safer_init.hpp"
#include "game\game.hpp"

PRX_CPP(__start__, Onyx_InputPort, 1, 0);


void System_OnExceptionThrown(int errn, char* msg) {
	System::Diagnostics::Debugger::WriteLine("Exception thrown: (%x) %s", errn, msg);
}

extern int __errn = 0;

extern "C" int __start__(void*...) {

	log("Module loaded. ");

	System::OnExceptCallback = System_OnExceptionThrown;
	
	Initialization::Load();

	return __errn;
}