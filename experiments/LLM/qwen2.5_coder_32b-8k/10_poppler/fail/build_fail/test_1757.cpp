#include <gtest/gtest.h>

#include "Object.h"



using namespace std;



// Test fixture for Object class tests related to isTextAlignName function.

class IsTextAlignNameTest_1757 : public ::testing::Test {

protected:

    Object nameStart;

    Object nameEnd;

    Object nameCenter;

    Object nameJustify;

    Object nameInvalid;



    IsTextAlignNameTest_1757() 

        : nameStart("Start"), 

          nameEnd("End"), 

          nameCenter("Center"), 

          nameJustify("Justify"), 

          nameInvalid("Invalid") {}

};



// Test to verify normal operation with valid "Start" alignment.

TEST_F(IsTextAlignNameTest_1757, StartAlignmentValid_1757) {

    EXPECT_TRUE(isTextAlignName(&nameStart));

}



// Test to verify normal operation with valid "End" alignment.

TEST_F(IsTextAlignNameTest_1757, EndAlignmentValid_1757) {

    EXPECT_TRUE(isTextAlignName(&nameEnd));

}



// Test to verify normal operation with valid "Center" alignment.

TEST_F(IsTextAlignNameTest_1757, CenterAlignmentValid_1757) {

    EXPECT_TRUE(isTextAlignName(&nameCenter));

}



// Test to verify normal operation with valid "Justify" alignment.

TEST_F(IsTextAlignNameTest_1757, JustifyAlignmentValid_1757) {

    EXPECT_TRUE(isTextAlignName(&nameJustify));

}



// Test to verify boundary condition with an invalid name.

TEST_F(IsTextAlignNameTest_1757, InvalidNameBoundary_1757) {

    EXPECT_FALSE(isTextAlignName(&nameInvalid));

}



// Test to verify exceptional case with a non-name object type.

TEST_F(IsTextAlignNameTest_1757, NonNameObjectExceptional_1757) {

    Object notAName(42); // Assuming 42 is an invalid ObjType for name

    EXPECT_FALSE(isTextAlignName(&notAName));

}



// Test to verify exceptional case with a null object.

TEST_F(IsTextAlignNameTest_1757, NullObjectExceptional_1757) {

    Object nullObject = Object::null();

    EXPECT_FALSE(isTextAlignName(&nullObject));

}
