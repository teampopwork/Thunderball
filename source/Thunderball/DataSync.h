#ifndef __DATASYNC_H__
#define __DATASYNC_H__

#include <SexyAppFramework/Common.h>
#include <SexyAppFramework/SmartPtr.h>
#include <list>
#include <map>
#include <set>
#include <string>
#include <vector>

namespace Sexy
{
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

// VTABLE: POPCAPGAME1 0x005d5f34
class DataReaderException : public std::exception {};

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

// VTABLE: POPCAPGAME1 0x0060db14
class DataReader {
public:
	FILE* mFileHandle;
	const void* mMemoryHandle;
	ulong mMemoryLength;
	ulong mMemoryPosition;
	int mUnk0x14;
	bool mDeallocate;
	char mUnk0x19;
	int mUnk0x1c;

	explicit DataReader();

	virtual ~DataReader(); // vtable+0x0

	void OpenMemory(const void* theMemory, ulong theLength, bool deallocate);
	bool OpenFile(const std::string& theFileName);
	void Close();

	void ReadBytes(void* theBuffer, ulong theLength);
	ulong ReadLong();
	ushort ReadShort();
	uchar ReadByte();
	bool ReadBool();
	float ReadFloat();
	void ReadString(std::string& theString);
	bool ReadBit();
	void EndBit();
};

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

// VTABLE: POPCAPGAME1 0x0060db08
class DataWriter {
public:
	FILE* mFileHandle;
	void* mMemoryHandle;
	ulong mMemoryPosition;
	ulong mMemoryLength;
	char mUnk0x14;
	int mUnk0x18;

	explicit DataWriter();
	virtual ~DataWriter();

	void OpenMemory(ulong theLength);
	void Close();
	void EnsureCapacity(ulong theLength);

	void WriteBytes(const void* theBuffer, ulong theLength);
	void WriteLong(ulong theValue);
	void WriteShort(ushort theValue);
	void WriteByte(uchar theValue);
	void WriteBool(bool theValue);
	void WriteFloat(float theValue);
	void WriteString(const std::string& theString);
	void WriteBit(bool theValue);
	void EndBit();

	void SetLong(ulong theValue, ulong thePosition);

};

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

// VTABLE: POPCAPGAME1 0x0060db00
class DataSync {
public:
	typedef std::map<void*, int> PointerToIntMap;
	typedef std::map<int, void*> IntToPointerMap;
	typedef std::map<RefCount*, int> RefCountToIntMap;
	typedef std::map<int, RefCount*> IntToRefCountMap;

	DataReader* mReader; // +0x4
	DataWriter* mWriter; // +0x8
	DataReader mReaderObj; // +0xC ????
	DataWriter mWriterObj; // +0x2C ????

	int mVersion; // +0x48
	bool mUnk0x4c; // +0x4c

	DataSync();
	explicit DataSync(DataReader& reader);
	explicit DataSync(DataWriter& writer);

	virtual ~DataSync();

	void SyncBytes(void* theValue, ulong theSize);
	void SyncLong(int& theValue);
	void SyncLong(unsigned int& theValue);
	void SyncLong(ulong& theValue);
	void SyncShort(int& theValue);
	void SyncShort(ushort& theValue);
	void SyncSShort(int& theValue);
	void SyncByte(int& theValue);
	void SyncByte(ushort& theValue);
	void SyncSByte(int& theValue);
	void SyncBool(bool& theValue);
	void SyncFloat(float& theValue);
	void SyncString(std::string& theValue);
	void SyncBoolBit(bool& theValue);
	void EndBit();

	void SyncPointers();
	void SyncPointer(void** thePtr);

	int AddRefCount(RefCount* thePtr);
	RefCount* GetRefCount(int theIndex);

	void RegisterPointer(void* thePtr);
	void Reset();	
	void ResetPointerTable();

	DataReader* StartReadMemory(const void* theMemory, ulong theLength, bool deallocate);
	void SetReader(DataReader* theReader);
	DataWriter* StartWriteMemory(ulong theLength);
	void SetWriter(DataWriter* theWriter);

private:
	PointerToIntMap mPointerToIntMap;
	IntToPointerMap mIntToPointerMap;
	RefCountToIntMap mRefCountToIntMap;
	IntToRefCountMap mIntToRefCountMap; // +0x
	std::vector<void**> mPointerSyncList; // +0x80
	int mCurPointerIndex; // +0x90
};

template <typename TContainer>
void DataSync_SyncSTLContainer(DataSync& theSync, TContainer& theValue)
{
	typedef TContainer type;

	if (theSync.mReader != NULL) {
		theValue.clear();
		ulong aLength = theSync.mReader->ReadLong();
		for (ulong i = 0; i < aLength; i++) {
			typename type::value_type aValue;
			theValue.push_back(aValue);

			typename type::value_type& aRef = theValue.back();
			aRef.SyncState(theSync);
		}
	}
	else {
		theSync.mWriter->WriteLong(theValue.size());
		for (typename type::iterator i = theValue.begin(); i != theValue.end(); ++i) {
			i->SyncState(theSync);
		}
	}
}

template <typename T>
T* DataSync_SyncRefCount(DataSync& theSync, T* thePointer)
{
	if (theSync.mReader != NULL) {
		int refCount = theSync.mReader->ReadLong();
		if (refCount == 0) {
			return NULL;
		}
		else if (refCount == 1) {
			T* newObject = new T();
			theSync.AddRefCount(newObject);
			newObject->SyncState(&theSync);
			return newObject;
		}
		else {
			return (T*)theSync.GetRefCount(refCount);
		}
		
	}
	else {
		int refCount = theSync.AddRefCount(thePointer);
		theSync.mWriter->WriteLong(refCount);
		if (refCount == 1) {
			thePointer->SyncState(&theSync);
		}
		return thePointer;
	}
}

template <typename T>
void DataSync_SyncSmartPointer(DataSync& theSync, SmartPtr<T>& thePointer)
{
	if (theSync.mReader != NULL) {
		RefCount* refCount = DataSync_SyncRefCount(theSync, (T*)thePointer);
		thePointer = (T*)refCount;
	}
	else {
		
		DataSync_SyncRefCount(theSync, (T*)thePointer);

	}
}

template <typename T>
T* DataSync_SyncRefCountFactory(DataSync& theSync, T& theFactory)
{
	if (theSync.mReader == NULL) {
		ulong refCount = theSync.AddRefCount(theFactory);
		theSync.mWriter->WriteLong(refCount);
		if (refCount == 1) {
			theSync.mWriter->WriteLong(theFactory->GetClass());
			theFactory.SyncState(theSync);
		}
	}
	else {
		ulong refCount = theSync.mReader->ReadLong();
		if (refCount == 0) {
			return NULL;
		}
		else if (refCount == 1) {
			T* newObject = theFactory.ClassFactory(theSync.mReader->ReadLong());
			theSync.AddRefCount(newObject, refCount);
			newObject->SyncState(theSync);
			return newObject;
		}
		else {
			return theSync.GetRefCount(theFactory, refCount);
		}
	}

	return NULL;
}

} // namespace Sexy

#endif
