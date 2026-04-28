#include "DataSync.h"

#include <SexyAppFramework/Debug.h>
#include <SexyAppFramework/SmartPtr.h>

using namespace Sexy;

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

// FUNCTION: POPCAPGAME1 0x004bbe20
DataReader::DataReader()
	: mFileHandle(NULL), mMemoryHandle(NULL), mMemoryLength(0), mMemoryPosition(0), mDeallocate(false)
{
}

// SYNTHETIC: POPCAPGAME1 0x004bbdf0
// Sexy::DataReader::`scalar deleting destructor'

// FUNCTION: POPCAPGAME1 0x004bbec0
DataReader::~DataReader()
{
	Close();
}

// FUNCTION: POPCAPGAME1 0x004bbed0
void DataReader::OpenMemory(const void* theMemory, ulong theLength, bool deallocate)
{
	Close();

	mMemoryHandle = theMemory;
	mMemoryLength = theLength;
	mDeallocate = deallocate;
}

// FUNCTION: POPCAPGAME1 0x004bbf30
bool DataReader::OpenFile(const std::string& theFileName)
{
	Close();

	mFileHandle = fopen(theFileName.c_str(), "rb");
	return mFileHandle != NULL;
}

// FUNCTION: POPCAPGAME1 0x004bbe60
void DataReader::Close()
{
	if (mFileHandle) {
		fclose(mFileHandle);
		mFileHandle = NULL;
	}

	if (mDeallocate && mMemoryHandle) {
		delete[] mMemoryHandle;
	}

	mMemoryHandle = NULL;
	mMemoryLength = 0;
	mMemoryPosition = 0;
	mDeallocate = false;
}

// FUNCTION: POPCAPGAME1 0x004bbf70
void DataReader::ReadBytes(void* theBuffer, ulong theLength)
{
	if (mMemoryHandle) {
		mMemoryPosition += theLength;
		if (mMemoryPosition <= mMemoryLength) {
			memcpy(theBuffer, mMemoryHandle, theLength);
			mMemoryHandle = (char*) mMemoryHandle + theLength;
			return;
		}
	}

	if (mFileHandle && theLength == fread(theBuffer, 1, theLength, mFileHandle)) {
		return;
	}

	throw DataReaderException();
}

// FUNCTION: POPCAPGAME1 0x004bc190
ulong DataReader::ReadLong()
{
	ulong result;
	ReadBytes(&result, sizeof(result));
	return result;
}

// FUNCTION: POPCAPGAME1 0x004bc1b0
ushort DataReader::ReadShort()
{
	ushort result = 0;
	ReadBytes(&result, sizeof(result));
	return result;
}

// FUNCTION: POPCAPGAME1 0x004bc1d0
uchar DataReader::ReadByte()
{
	uchar result = 0;
	ReadBytes(&result, sizeof(result));
	return result;
}

// FUNCTION: POPCAPGAME1 0x004bc1f0
bool DataReader::ReadBool()
{
	return ReadByte() != 0;
}

// FUNCTION: POPCAPGAME1 0x004bc200
float DataReader::ReadFloat()
{
	ulong result;
	ReadBytes(&result, sizeof(result));
	return reinterpret_cast<float&>(result);
}

// FUNCTION: POPCAPGAME1 0x004bc220
void DataReader::ReadString(std::string& theString)
{
	ulong length = ReadShort();
	theString.resize(length, 0);
	ReadBytes(&theString[0], length);
}

// FUNCTION: POPCAPGAME1 0x004bc290
bool DataReader::ReadBit()
{
	if (mUnk0x1c == 0) {
		mUnk0x1c = ReadByte();
	}

	int iVar2 = 1 >> (mUnk0x1c & 0x1f);
	mUnk0x1c++;
	if (7 < mUnk0x1c) {
		mUnk0x1c = 0;
	}
	return bool(iVar2);
}

// FUNCTION: POPCAPGAME1 0x004bbeb0
void DataReader::EndBit()
{
	mUnk0x1c = 0;
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

// FUNCTION: POPCAPGAME1 0x004bba70
DataWriter::DataWriter() : mFileHandle(NULL), mMemoryHandle(NULL), mMemoryLength(0), mMemoryPosition(0)
{
}

// FUNCTION: POPCAPGAME1 0x004bbd20
DataWriter::~DataWriter()
{
	Close();
}

// FUNCTION: POPCAPGAME1 0x004bbd70
void DataWriter::OpenMemory(ulong theLength)
{
	Close();

	if (theLength < 32) {
		theLength = 32;
	}

	mMemoryLength = theLength;
	mMemoryHandle = new char[theLength];
}

// FUNCTION: POPCAPGAME1 0x004bbc40
void DataWriter::Close()
{
	if (mFileHandle) {
		fclose(mFileHandle);
		mFileHandle = NULL;
	}

	if (mMemoryHandle) {
		delete[] mMemoryHandle;
	}

	mMemoryHandle = NULL;
	mMemoryLength = 0;
	mMemoryPosition = 0;
}

// FUNCTION: POPCAPGAME1 0x004bbac0
void DataWriter::EnsureCapacity(ulong theLength)
{
	if (mMemoryLength < theLength) {
		ulong newLength = mMemoryLength;
		do {
			newLength *= 2;
		} while (newLength < theLength);
		mMemoryLength = newLength;

		void* newMemory = new char[newLength];
		memcpy(newMemory, mMemoryHandle, mMemoryPosition);
		delete[] mMemoryHandle;

		mMemoryHandle = newMemory;
	}
}

// FUNCTION: POPCAPGAME1 0x004bbb10
void DataWriter::WriteBytes(const void* theBuffer, ulong theLength)
{
	if (mMemoryHandle) {
		EnsureCapacity(mMemoryPosition + theLength);
		memcpy((char*) mMemoryHandle + mMemoryPosition, theBuffer, theLength);
		mMemoryPosition += theLength;
	}
	else if (mFileHandle) {
		fwrite(theBuffer, 1, theLength, mFileHandle);
	}
}

// FUNCTION: POPCAPGAME1 0x004bbb90
void DataWriter::WriteLong(ulong theValue)
{
	WriteBytes(&theValue, sizeof(theValue));
}

// FUNCTION: POPCAPGAME1 0x004bbbb0
void DataWriter::WriteShort(ushort theValue)
{
	WriteBytes(&theValue, sizeof(theValue));
}

// FUNCTION: POPCAPGAME1 0x004bbbd0
void DataWriter::WriteByte(uchar theValue)
{
	WriteBytes(&theValue, sizeof(theValue));
}

// FUNCTION: POPCAPGAME1 0x004bbbf0
void DataWriter::WriteBool(bool theValue)
{
	WriteBytes(&theValue, sizeof(theValue));
}

// FUNCTION: POPCAPGAME1 0x004bbb90
void DataWriter::WriteFloat(float theValue)
{
	ulong result = reinterpret_cast<ulong&>(theValue);
	WriteBytes(&result, sizeof(result));
}

// FUNCTION: POPCAPGAME1 0x004bbda0
void DataWriter::WriteString(const std::string& theString)
{
	WriteShort(theString.length());
	WriteBytes(theString.c_str(), theString.length());
}

// FUNCTION: POPCAPGAME1 0x004bbc90
void DataWriter::WriteBit(bool theValue)
{

	if (mMemoryHandle == NULL) {
		if (mFileHandle != 0) {
			if (theValue != '\0') {
				mUnk0x14 = mUnk0x14 | 1 << ((char) mUnk0x18 & 0x1f);
			}
			mUnk0x18++;
			if (7 < mUnk0x18) {
				mUnk0x14 = 0;
				mUnk0x18 = 0;
				WriteByte(0);
			}
		}
	}
	else {
		if (mUnk0x18 == 0) {
			WriteByte(0);
		}
		if (theValue != '\0') {
			char* pbVar1 = (char*) ((mMemoryPosition - 1) + (int) mMemoryHandle);
			*pbVar1 = *pbVar1 | 1 << ((char) mUnk0x18 & 0x1f);
		}
		mUnk0x18++;
		if (7 < mUnk0x18) {
			mUnk0x18 = 0;
		}
	}
}

// FUNCTION: POPCAPGAME1 0x004bba90
void DataWriter::EndBit()
{
	if (mUnk0x18 != 0) {
		if (mFileHandle != NULL) {
			fwrite(&mUnk0x14, 1, 1, mFileHandle);
		}
		mUnk0x18 = 0;
	}
}

// FUNCTION: POPCAPGAME1 0x004bbc10
void DataWriter::SetLong(ulong param_1, ulong param_2)
{
	if (mMemoryHandle != NULL) {
		if (param_2 + 4U <= mMemoryLength) {
			*(ulong*) ((int) mMemoryHandle + param_2) = param_1;
		}
	}
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

// FUNCTION: POPCAPGAME1 0x004bb6f0
DataSync::DataSync()
{
	Reset();
}

// FUNCTION: POPCAPGAME1 0x004bb810
DataSync::DataSync(DataReader& reader)
{
	Reset();
	mReader = &reader;
}

// FUNCTION: POPCAPGAME1 0x004bb940
DataSync::DataSync(DataWriter& writer)
{
	Reset();
	mWriter = &writer;
}

// SYNTHETIC: POPCAPGAME1 0x004bb600
// Sexy::DataSync::`scalar deleting destructor'

// FUNCTION: POPCAPGAME1 0x004bb0b0
DataSync::~DataSync()
{
}

// FUNCTION: POPCAPGAME1 0x004ba7f0
void DataSync::SyncBytes(void* theValue, ulong theSize)
{
	if (mReader) {
		mReader->ReadBytes(theValue, theSize);
	}
	else if (mWriter) {
		mWriter->WriteBytes(theValue, theSize);
	}
}

// FUNCTION: POPCAPGAME1 0x004ba810
void DataSync::SyncLong(int& theValue)
{
	if (mReader) {
		theValue = mReader->ReadLong();
	}
	else {
		mWriter->WriteLong(theValue);
	}
}

void DataSync::SyncLong(unsigned int& theValue)
{
	if (mReader) {
		theValue = mReader->ReadLong();
	}
	else {
		mWriter->WriteLong(theValue);
	}
}

// FUNCTION: POPCAPGAME1 0x004ba810
void DataSync::SyncLong(unsigned long& theValue)
{
	if (mReader) {
		theValue = mReader->ReadLong();
	}
	else {
		mWriter->WriteLong(theValue);
	}
}

void DataSync::SyncShort(int& theValue)
{
	if (mReader) {
		theValue = mReader->ReadShort();
	}
	else {
		mWriter->WriteShort(theValue);
	}
}

// FUNCTION: POPCAPGAME1 0x004ba840
void DataSync::SyncShort(unsigned short& theValue)
{
	if (mReader) {
		theValue = mReader->ReadShort();
	}
	else {
		mWriter->WriteShort(theValue);
	}
}

// FUNCTION: POPCAPGAME1 0x004ba870
void DataSync::SyncSShort(int& theValue)
{
	if (mReader) {
		theValue = static_cast<short>(mReader->ReadShort());
	}
	else {
		mWriter->WriteShort(static_cast<ushort>(theValue));
	}
}

// FUNCTION: POPCAPGAME1 0x004ba8a0
void DataSync::SyncByte(int& theValue)
{
	if (mReader) {
		theValue = mReader->ReadByte();
	}
	else {
		mWriter->WriteByte(static_cast<uchar>(theValue));
	}
}

// FUNCTION: POPCAPGAME1 0x004ba8a0
void DataSync::SyncByte(unsigned short& theValue)
{
	if (mReader) {
		theValue = static_cast<uchar>(mReader->ReadByte());
	}
	else {
		mWriter->WriteByte(static_cast<uchar>(theValue));
	}
}

// FUNCTION: POPCAPGAME1 0x004ba8d0
void DataSync::SyncSByte(int& theValue)
{
	if (mReader) {
		theValue = (int)(char)mReader->ReadByte();
	}
	else {
		mWriter->WriteByte((uchar) theValue);
	}
}

// FUNCTION: POPCAPGAME1 0x004ba920
void DataSync::SyncBool(bool& theValue)
{
	if (mReader) {
		theValue = mReader->ReadBool();
	}
	else {
		mWriter->WriteBool(theValue);
	}
}

// FUNCTION: POPCAPGAME1 0x004ba980
void DataSync::SyncFloat(float& theValue)
{
	if (mReader) {
		theValue = mReader->ReadFloat();
	}
	else {
		mWriter->WriteFloat(theValue);
	}
}

// FUNCTION: POPCAPGAME1 0x004ba9b0
void DataSync::SyncString(std::string& theValue)
{
	if (mReader) {
		mReader->ReadString(theValue);
	}
	else {
		mWriter->WriteString(theValue);
	}
}

// FUNCTION: POPCAPGAME1 0x004ba950
void DataSync::SyncBoolBit(bool& theValue)
{
	if (mReader) {
		mReader->ReadBit();
	}
	else {
		mWriter->WriteBit(theValue);
	}
}

// FUNCTION: POPCAPGAME1 0x004ba900
void DataSync::EndBit()
{
	if (mReader != NULL) {
		mReader->EndBit();
	}
	else {
		mWriter->EndBit();
	}
}

// FUNCTION: POPCAPGAME1 0x004bb3e0
void DataSync::SyncPointers()
{
	if (mReader) {
		for (std::vector<void**>::iterator i = mPointerSyncList.begin(); i != mPointerSyncList.end(); ++i) {
			int a = (int) mReader->ReadLong();
			IntToPointerMap::iterator aFindItr = mIntToPointerMap.find(a);

			if (aFindItr == mIntToPointerMap.end()) {
				throw DataReaderException();
			}
			**i = aFindItr->second;
		}
	}
	else {
		for (std::vector<void**>::iterator i = mPointerSyncList.begin(); i != mPointerSyncList.end(); ++i) {
			PointerToIntMap::iterator aFindItr = mPointerToIntMap.find(**i);
			assert(aFindItr != mPointerToIntMap.end());
			mWriter->WriteLong(aFindItr->second);
		}
	}

	ResetPointerTable();
}

void DataSync::SyncPointer(void** thePointer)
{
	mPointerSyncList.push_back(thePointer);
}

// FUNCTION: POPCAPGAME1 0x004bb330
int DataSync::AddRefCount(RefCount* refCount)
{
	if (refCount == NULL) {
		return 0;
	}

	std::pair<std::map<RefCount*, int>::iterator, bool> result =
		mRefCountToIntMap.insert(std::make_pair(refCount, 0));

	if (!result.second) {
		return result.first->second;
	}

	int refId = (int) mRefCountToIntMap.size() + 1;
	result.first->second = refId;
	mIntToRefCountMap[refId] = refCount;
	return 1;
}

// FUNCTION: POPCAPGAME1 0x004baac0
RefCount* DataSync::GetRefCount(int theIndex)
{
	IntToRefCountMap::iterator aFindItr = mIntToRefCountMap.find(theIndex);
	if (aFindItr != mIntToRefCountMap.end()) {
		return aFindItr->second;
	}

	return NULL;
}

void DataSync::RegisterPointer(void* thePtr)
{
	DBG_ASSERT(thePtr != NULL);

	std::pair<PointerToIntMap::iterator, bool> aPTIEntry = mPointerToIntMap.insert(std::make_pair(thePtr, 0));
	if (aPTIEntry.second) {
		int num = mCurPointerIndex++;
		aPTIEntry.first->second = num;
		mIntToPointerMap[num] = thePtr;
	}
}

// FUNCTION: POPCAPGAME1 0x004bb630
void DataSync::Reset()
{
	mReader = NULL;
	mWriter = NULL;
	mReaderObj.OpenMemory(NULL, 0, false);
	mWriterObj.Close();
	mUnk0x4c = true;

	ResetPointerTable();
}

// FUNCTION: POPCAPGAME1 0x004bb1f0
void DataSync::ResetPointerTable()
{
	mIntToPointerMap.clear();
	mPointerToIntMap.clear();
	mPointerSyncList.clear();
	mRefCountToIntMap.clear();
	mIntToRefCountMap.clear();
	mCurPointerIndex = 2;
	mPointerToIntMap[NULL] = 0;
	mIntToPointerMap[0] = NULL;
}

// FUNCTION: POPCAPGAME1 0x004bb6a0
DataReader* DataSync::StartReadMemory(const void* theMemory, ulong theLength, bool deallocate)
{
	SetReader(&mReaderObj);
	mReaderObj.OpenMemory(theMemory, theLength, deallocate);
	return &mReaderObj;
}

// FUNCTION: POPCAPGAME1 0x004bb660
void DataSync::SetReader(DataReader* theReader)
{
	Reset();
	mReader = theReader;
}

// FUNCTION: POPCAPGAME1 0x004bb6d0
DataWriter* DataSync::StartWriteMemory(ulong theLength)
{
	SetWriter(&mWriterObj);
	mWriterObj.OpenMemory(theLength);
	return &mWriterObj;
}

// FUNCTION: POPCAPGAME1 0x004bb680
void DataSync::SetWriter(DataWriter* theWriter)
{
	Reset();
	mWriter = theWriter;
}
