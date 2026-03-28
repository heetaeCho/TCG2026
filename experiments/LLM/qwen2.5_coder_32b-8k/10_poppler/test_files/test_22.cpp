#include <gtest/gtest.h>

#include "GooString.h"



// Test fixture for GooString

class GooStringTest_22 : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup can be used to initialize common objects if needed.

    }



    void TearDown() override {

        // Cleanup can be handled here if necessary.

    }

};



// Test normal operation of copy method

TEST_F(GooStringTest_22, CopyCreatesIdenticalInstance_22) {

    GooString original("test");

    auto copied = original.copy();

    EXPECT_EQ(original.toStr(), copied->toStr());

}



// Test boundary condition: copying an empty string

TEST_F(GooStringTest_22, CopyEmptyString_22) {

    GooString original("");

    auto copied = original.copy();

    EXPECT_EQ("", copied->toStr());

}



// Test normal operation of getChar and setChar methods

TEST_F(GooStringTest_22, GetSetCharFunctionality_22) {

    GooString str("hello");

    EXPECT_EQ('h', str.getChar(0));

    str.setChar(0, 'H');

    EXPECT_EQ('H', str.getChar(0));

}



// Test boundary condition: getChar and setChar with last valid index

TEST_F(GooStringTest_22, GetSetCharLastIndex_22) {

    GooString str("test");

    EXPECT_EQ('t', str.getChar(3));

    str.setChar(3, 'T');

    EXPECT_EQ('T', str.getChar(3));

}



// Test exceptional case: getChar with out-of-bounds index

TEST_F(GooStringTest_22, GetCharOutOfBounds_22) {

    GooString str("test");

    // Assuming that getChar does not throw an exception for simplicity.

    // If it throws, the test should be adjusted accordingly.

    EXPECT_NE('x', str.getChar(10));

}



// Test exceptional case: setChar with out-of-bounds index

TEST_F(GooStringTest_22, SetCharOutOfBounds_22) {

    GooString str("test");

    // Assuming that setChar does not throw an exception for simplicity.

    // If it throws, the test should be adjusted accordingly.

    str.setChar(10, 'x');

    EXPECT_NE('x', str.getChar(3));

}



// Test normal operation of toStr method

TEST_F(GooStringTest_22, ToStrReturnsCorrectValue_22) {

    GooString str("sample");

    EXPECT_EQ("sample", str.toStr());

}
