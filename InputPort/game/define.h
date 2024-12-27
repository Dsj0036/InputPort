#pragma once
#include "include\diag.h"

#define __EnableLogging__ true
#if __EnableLogging__
#define log System::Diagnostics::Debugger::WriteLine
#else 
#define log (void)0
#endif