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

class EditValObj : public RefCount {
public:
	EditValObj();

	void EditGetSetValHook(const std::string& param_1, bool param_2);

	void EditValSyncNum(int* theNum);
	void EditValSyncNum(int* theNum, int param_2, int param_3);

	void EditValSyncNum(ulong* theNum);

	void EditValSyncNum(float* theNum);
	void EditValSyncNum(float* theNum, float param_2, float param_3);

	void EditValSyncBool(bool* theBool);
	void EditValSyncString(std::string* theString);

	double GetEditValNum();
	void SetEditValNum(double theNum);

	std::string EditKeyPrefix(const std::string& param_1, const std::string& param_2);

	void EditGetSetVal(const std::string& theKey, EditVal* theVal, bool param_3, bool param_4);
	void EditSetVal(const std::string& theKey, EditVal* theVal, bool param_3);
	void EditGetVal(const std::string& theKey, EditVal* theVal);

	void EditGetSetValDelegate(EditValObj* theObj, const std::string& param_2);
};

class GlobalEditVal : public EditValObj {
public:
	virtual ~GlobalEditVal();
	GlobalEditVal();
	virtual void EditGetSetValHook(const std::string& param_1, bool param_2);
};

} // namespace Sexy

#endif // __LEVELEDITOR_H__
