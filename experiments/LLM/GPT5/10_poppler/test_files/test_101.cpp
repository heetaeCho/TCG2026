// Object_getArray_ut_101.cpp
#include <gtest/gtest.h>

#include "poppler/Object.h"

namespace {

class ObjectGetArrayTest_101 : public ::testing::Test {};

// Normal operation: when constructed as an array object, getArray() returns the same pointer.
TEST_F(ObjectGetArrayTest_101, GetArrayReturnsSamePointerForArrayObject_101)
{
    // We don't need a real Array instance (incomplete type is fine); just a stable non-null pointer value.
    Array *const fakeArrayPtr = reinterpret_cast<Array *>(static_cast<uintptr_t>(0x1234));

    Object obj(fakeArrayPtr);
    EXPECT_EQ(obj.getArray(), fakeArrayPtr);
}

// Boundary condition: array object holding nullptr should return nullptr (still an observable outcome).
TEST_F(ObjectGetArrayTest_101, GetArrayAllowsNullArrayPointer_101)
{
    Array *const nullArrayPtr = nullptr;

    Object obj(nullArrayPtr);
    EXPECT_EQ(obj.getArray(), nullptr);
}

// Exceptional/error case: calling getArray() on a non-array Object should trigger the type check.
// In Poppler this is commonly implemented via an assertion-like macro; use a death test when supported.
TEST_F(ObjectGetArrayTest_101, GetArrayOnNonArrayTriggersTypeCheck_101)
{
    Object obj(123); // definitely not an array

#if GTEST_HAS_DEATH_TEST
    // If OBJECT_TYPE_CHECK aborts/asserts, this should terminate the process.
    // Use a broad matcher to avoid depending on implementation-specific messages.
    ASSERT_DEATH_IF_SUPPORTED(
        {
            (void)obj.getArray();
        },
        ".*");
#else
    GTEST_SKIP() << "Death tests are not supported in this build/environment.";
#endif
}

} // namespace