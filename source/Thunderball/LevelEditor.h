#ifndef __LEVELEDITOR_H__
#define __LEVELEDITOR_H__

#include <SexyAppFramework/Common.h>
#include <SexyAppFramework/SmartPtr.h>

#include <string>

namespace Sexy
{
class EditVal {
public:
	bool mStringCached;
	bool mNumCached;
	std::string mString;
	double mNum;

	EditVal();
	EditVal(std::string& theValue);
	EditVal(double theValue);

	double ToNum();
	std::string ToString();
};

// VTABLE: POPCAPGAME1 0x005d2a24
class EditValObj : public RefCount {
public:
	EditVal* mEditVal; // +0x8
	bool mUnk0xc; // +0xc
	bool mUnk0xd; // +0xd

	EditValObj();

	virtual bool EditGetSetValHook(const std::string& param_1, bool param_2);

	bool EditValSyncNum(int& theNum);
	bool EditValSyncNum(int& theNum, int param_2, int param_3);

	bool EditValSyncNum(ulong& theNum);

	bool EditValSyncNum(float& theNum);
	bool EditValSyncNum(float& theNum, float param_2, float param_3);

	bool EditValSyncBool(bool& theBool);
	bool EditValSyncString(std::string& theString);

	double GetEditValNum();
	void SetEditValNum(double theNum);

	bool EditKeyPrefix(const std::string& param_1, const std::string& param_2);

	void EditGetSetVal(const std::string& theKey, EditVal* theVal, bool param_3, bool param_4);
	void EditSetVal(const std::string& theKey, EditVal* theVal, bool param_3);
	void EditGetVal(const std::string& theKey, EditVal* theVal);

	bool EditGetSetValDelegate(EditValObj* theObj, const std::string& param_2);
};

class GlobalEditVal : public EditValObj {
public:
	virtual ~GlobalEditVal();
	GlobalEditVal();
	virtual bool EditGetSetValHook(const std::string& param_1, bool param_2);
};

} // namespace Sexy

#endif // __LEVELEDITOR_H__
