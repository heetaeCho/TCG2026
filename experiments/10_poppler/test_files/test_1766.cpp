#include <gtest/gtest.h>

#include "Object.h"



using namespace std;



// Test fixture for testing isListNumberingName function

class IsListNumberingNameTest_1766 : public ::testing::Test {

protected:

    Object* obj;

};



// Test normal operation with valid list numbering names

TEST_F(IsListNumberingNameTest_1766, ValidNamesReturnTrue_1766) {

    obj = new Object("None");

    EXPECT_TRUE(isListNumberingName(obj));

    delete obj;



    obj = new Object("Disc");

    EXPECT_TRUE(isListNumberingName(obj));

    delete obj;



    obj = new Object("Circle");

    EXPECT_TRUE(isListNumberingName(obj));

    delete obj;



    obj = new Object("Square");

    EXPECT_TRUE(isListNumberingName(obj));

    delete obj;



    obj = new Object("Decimal");

    EXPECT_TRUE(isListNumberingName(obj));

    delete obj;



    obj = new Object("UpperRoman");

    EXPECT_TRUE(isListNumberingName(obj));

    delete obj;



    obj = new Object("LowerRoman");

    EXPECT_TRUE(isListNumberingName(obj));

    delete obj;



    obj = new Object("UpperAlpha");

    EXPECT_TRUE(isListNumberingName(obj));

    delete obj;



    obj = new Object("LowerAlpha");

    EXPECT_TRUE(isListNumberingName(obj));

    delete obj;

}



// Test boundary conditions with empty string

TEST_F(IsListNumberingNameTest_1766, EmptyStringReturnsFalse_1766) {

    obj = new Object("");

    EXPECT_FALSE(isListNumberingName(obj));

    delete obj;

}



// Test exceptional cases with invalid names

TEST_F(IsListNumberingNameTest_1766, InvalidNamesReturnFalse_1766) {

    obj = new Object("Invalid");

    EXPECT_FALSE(isListNumberingName(obj));

    delete obj;



    obj = new Object("AnotherInvalid");

    EXPECT_FALSE(isListNumberingName(obj));

    delete obj;

}



// Test with non-name objects

TEST_F(IsListNumberingNameTest_1766, NonNameObjectReturnsFalse_1766) {

    obj = new Object(42);

    EXPECT_FALSE(isListNumberingName(obj));

    delete obj;



    obj = new Object(3.14);

    EXPECT_FALSE(isListNumberingName(obj));

    delete obj;



    obj = new Object(true);

    EXPECT_FALSE(isListNumberingName(obj));

    delete obj;

}



// Test with null object

TEST_F(IsListNumberingNameTest_1766, NullObjectReturnsFalse_1766) {

    obj = &Object::null();

    EXPECT_FALSE(isListNumberingName(obj));

}
