#include <gtest/gtest.h>
#include <type_traits>

// Include necessary headers
#include "XRef.h"
#include "Object.h"

class ObjectStreamTest_1892 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test that ObjectStream is not copy constructible (deleted copy constructor)
TEST_F(ObjectStreamTest_1892, NotCopyConstructible_1892) {
    EXPECT_FALSE(std::is_copy_constructible<ObjectStream>::value);
}

// Test that ObjectStream is not copy assignable (deleted assignment operator)
TEST_F(ObjectStreamTest_1892, NotCopyAssignable_1892) {
    EXPECT_FALSE(std::is_copy_assignable<ObjectStream>::value);
}

// Test creating ObjectStream with null XRef - should not be ok
TEST_F(ObjectStreamTest_1892, NullXRefIsNotOk_1892) {
    ObjectStream objStream(nullptr, 0, 0);
    EXPECT_FALSE(objStream.isOk());
}

// Test that getObjStrNum returns the value passed to the constructor
TEST_F(ObjectStreamTest_1892, GetObjStrNumReturnsConstructorValue_1892) {
    ObjectStream objStream(nullptr, 42, 0);
    EXPECT_EQ(objStream.getObjStrNum(), 42);
}

// Test getObjStrNum with zero
TEST_F(ObjectStreamTest_1892, GetObjStrNumZero_1892) {
    ObjectStream objStream(nullptr, 0, 0);
    EXPECT_EQ(objStream.getObjStrNum(), 0);
}

// Test getObjStrNum with negative value
TEST_F(ObjectStreamTest_1892, GetObjStrNumNegative_1892) {
    ObjectStream objStream(nullptr, -1, 0);
    EXPECT_EQ(objStream.getObjStrNum(), -1);
}

// Test that an invalid ObjectStream (null XRef) reports not ok
TEST_F(ObjectStreamTest_1892, InvalidStreamIsNotOk_1892) {
    ObjectStream objStream(nullptr, 10, 0);
    EXPECT_FALSE(objStream.isOk());
}

// Test getObject on an invalid ObjectStream returns null/invalid object
TEST_F(ObjectStreamTest_1892, GetObjectOnInvalidStreamReturnsNull_1892) {
    ObjectStream objStream(nullptr, 0, 0);
    ASSERT_FALSE(objStream.isOk());
    Object obj = objStream.getObject(0, 0);
    EXPECT_TRUE(obj.isNull());
}

// Test getObject with various indices on invalid stream
TEST_F(ObjectStreamTest_1892, GetObjectNegativeIndexOnInvalidStream_1892) {
    ObjectStream objStream(nullptr, 0, 0);
    ASSERT_FALSE(objStream.isOk());
    Object obj = objStream.getObject(-1, 0);
    EXPECT_TRUE(obj.isNull());
}

// Test getObject with large index on invalid stream
TEST_F(ObjectStreamTest_1892, GetObjectLargeIndexOnInvalidStream_1892) {
    ObjectStream objStream(nullptr, 0, 0);
    ASSERT_FALSE(objStream.isOk());
    Object obj = objStream.getObject(99999, 0);
    EXPECT_TRUE(obj.isNull());
}

// Test with large objStrNum value
TEST_F(ObjectStreamTest_1892, LargeObjStrNum_1892) {
    ObjectStream objStream(nullptr, 999999, 0);
    EXPECT_EQ(objStream.getObjStrNum(), 999999);
    EXPECT_FALSE(objStream.isOk());
}

// Test with high recursion value and null XRef
TEST_F(ObjectStreamTest_1892, HighRecursionNullXRef_1892) {
    ObjectStream objStream(nullptr, 1, 100);
    EXPECT_FALSE(objStream.isOk());
}
