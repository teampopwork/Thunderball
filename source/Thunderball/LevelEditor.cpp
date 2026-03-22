#include "LevelEditor.h"

#include <SexyAppFramework/Common.h>

using namespace Sexy;

// FUNCTION: POPCAPGAME1 0x0040b010
EditVal::EditVal()
{
	mStringCached = false;
	mNumCached = false;
	mString = "";
	mNum = 0;
}

// FUNCTION: POPCAPGAME1 0x004111a0
EditVal::EditVal(std::string& theValue)
{
	mStringCached = true;
	mNumCached = false;
	mString = theValue;
}

// FUNCTION: POPCAPGAME1 0x0040b030
EditVal::EditVal(double theValue)
{
	mStringCached = false;
	mNumCached = true;
	mNum = theValue;
}

// FUNCTION: POPCAPGAME1 0x00411210
std::string EditVal::ToString()
{
	if (mStringCached == false) {
		char local_14[2];
		mString = StrFormat(local_14, "%g", mNum);
		mStringCached = true;
	}

	return mString;
}

// FUNCTION: POPCAPGAME1 0x004091b0
double EditVal::ToNum()
{
	if (mNumCached == false) {
		int iVar1 = sscanf(mString.c_str(), "%lf", &mNum);
		if (iVar1 != 1) {
			mNum = 0;
		}
		mNumCached = true;
	}

	return mNum;
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

// STUB: POPCAPGAME1 0x00402d00
EditValObj::EditValObj()
{
}

// SYNTHETIC: POPCAPGAME1 0x004073e0
// Sexy::EditValObj::`scalar deleting destructor'

// FUNCTION: POPCAPGAME1 0x0054b760
void EditValObj::EditGetSetValHook(const std::string& param_1, bool param_2)
{
}

// STUB: POPCAPGAME1 0x0041ec80
void EditValObj::EditValSyncNum(int* theNum)
{
}

// STUB: POPCAPGAME1 0x004112a0
void EditValObj::EditValSyncNum(int* theNum, int param_2, int param_3)
{
}

// STUB: POPCAPGAME1 0x00411380
void EditValObj::EditValSyncNum(ulong* theNum)
{
}

// STUB: POPCAPGAME1 0x00411470
void EditValObj::EditValSyncNum(float* theNum)
{
}

// STUB: POPCAPGAME1 0x00411530
void EditValObj::EditValSyncNum(float* theNum, float param_2, float param_3)
{
}

// STUB: POPCAPGAME1 0x00411640
void EditValObj::EditValSyncBool(bool* theBool)
{
}

// STUB: POPCAPGAME1 0x0041ed40
void EditValObj::EditValSyncString(std::string* theString)
{
}

// STUB: POPCAPGAME1 0x0040a100
double EditValObj::GetEditValNum()
{
	return 0;
}

// STUB: POPCAPGAME1 0x00411730
void EditValObj::SetEditValNum(double theNum)
{
}

// STUB: POPCAPGAME1 0x004091f0
std::string EditValObj::EditKeyPrefix(const std::string& param_1, const std::string& param_2)
{
	return "";
}

// STUB: POPCAPGAME1 0x00402d20
void EditValObj::EditGetSetVal(const std::string& theKey, EditVal* theVal, bool param_3, bool param_4)
{
}

// STUB: POPCAPGAME1 0x00407410
void EditValObj::EditSetVal(const std::string& theKey, EditVal* theVal, bool param_3)
{
}

// STUB: POPCAPGAME1 0x00407430
void EditValObj::EditGetVal(const std::string& theKey, EditVal* theVal)
{
}

// STUB: POPCAPGAME1 0x00402d60
void EditValObj::EditGetSetValDelegate(EditValObj* theObj, const std::string& param_2)
{
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

// STUB: POPCAPGAME1 0x00402f90
GlobalEditVal::GlobalEditVal()
{
}

// SYNTHETIC: POPCAPGAME1 0x00407490
// Sexy::GlobalEditVal::`scalar deleting destructor'

// STUB: POPCAPGAME1 0x00402fc0
GlobalEditVal::~GlobalEditVal()
{
}

// STUB: POPCAPGAME1 0x0041ee00
void GlobalEditVal::EditGetSetValHook(const std::string& param_1, bool param_2)
{
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
