#pragma warning( disable : 4786 )

#include "CritSect.h"
#include <windows.h>

using namespace Sexy;

////////////////////////////////////////////////////////////////////////////////

// FUNCTION: POPCAPGAME1 0x004fb8e0
CritSect::CritSect(void)
{
	InitializeCriticalSection(&mCriticalSection);
}

////////////////////////////////////////////////////////////////////////////////

// FUNCTION: POPCAPGAME1 0x004fb8f0
CritSect::~CritSect(void)
{
	DeleteCriticalSection(&mCriticalSection);
}