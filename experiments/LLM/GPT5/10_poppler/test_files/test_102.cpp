// Object_getDict_tests_102.cpp

#include <gtest/gtest.h>

#include "poppler/Object.h"

class ObjectGetDictTest_102 : public ::testing::Test {};

// Normal operation: when constructed as a dict object, getDict() should be callable and
// return the stored Dict* (here we use nullptr to avoid ownership/lifetime assumptions).
TEST_F(ObjectGetDictTest_102, GetDictReturnsSamePointerWhenTypeIsDict_102)
{
    Dict *raw = nullptr;
    Object o(raw);

    EXPECT_TRUE(o.isDict());
    EXPECT_EQ(o.getDict(), raw);
}

// Boundary condition: nullptr Dict* is still a valid pointer value to store/return for a dict-typed Object.
TEST_F(ObjectGetDictTest_102, GetDictAllowsNullPointerForDictType_102)
{
    Object o(static_cast<Dict *>(nullptr));

    EXPECT_TRUE(o.isDict());
    EXPECT_EQ(o.getDict(), nullptr);
}

// Normal operation / robustness: moved-to object should preserve observable dict-pointer value.
// (We avoid asserting moved-from state, as it's not part of the provided interface contract.)
TEST_F(ObjectGetDictTest_102, GetDictAfterMovePreservesPointerValue_102)
{
    Object src(static_cast<Dict *>(nullptr));
    Object dst(std::move(src));

    EXPECT_TRUE(dst.isDict());
    EXPECT_EQ(dst.getDict(), nullptr);
}

// Exceptional/error case (debug builds): calling getDict() on a non-dict object should trigger the
// type check (often implemented via assert/abort). This is only reliably observable in !NDEBUG.
#ifndef NDEBUG
TEST_F(ObjectGetDictTest_102, GetDictOnNonDictDiesInDebug_102)
{
    Object o; // default: objNone
    ASSERT_DEATH_IF_SUPPORTED(
        {
            (void)o.getDict();
        },
        ".*");
}
#endif

// Exceptional/error case (debug builds): another non-dict type should also trip the type check.
#ifndef NDEBUG
TEST_F(ObjectGetDictTest_102, GetDictOnIntDiesInDebug_102)
{
    Object o(1);
    ASSERT_DEATH_IF_SUPPORTED(
        {
            (void)o.getDict();
        },
        ".*");
}
#endif