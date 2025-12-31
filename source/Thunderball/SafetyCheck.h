#ifndef __SAFETYCHECK_H__
#define __SAFETYCHECK_H__

#include <stddef.h>

#define ASSERT_OFFSET(ClassName, MemberName, ExpectedOffset)                                                           \
	typedef char valid_offset_##MemberName[(offsetof(ClassName, MemberName) == ExpectedOffset) ? 1 : -1]

#define ASSERT_SIZE(ClassName, ExpectedSize)                                                                           \
	typedef char valid_size_##ClassName[(sizeof(ClassName) == ExpectedSize) ? 1 : -1]

#endif // SAFETYCHECK_H
