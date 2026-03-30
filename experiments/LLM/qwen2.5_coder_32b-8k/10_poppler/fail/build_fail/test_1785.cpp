#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "StructElement.h"  // Assuming StructElement.h contains the declaration of StructElement and related types



using namespace testing;



// Test fixture for StructElement tests

class StructElementTest_1785 : public ::testing::Test {

protected:

    // Setup can be done here if necessary

};



TEST_F(StructElementTest_1785, KnownName_ReturnsCorrectType_1785) {

    // Arrange

    const char* name = "Document";



    // Act

    StructElement::Type result = StructElement::nameToType(name);



    // Assert

    EXPECT_NE(result, StructElement::Unknown);

}



TEST_F(StructElementTest_1785, UnknownName_ReturnsUnknownType_1785) {

    // Arrange

    const char* name = "NonExistentType";



    // Act

    StructElement::Type result = StructElement::nameToType(name);



    // Assert

    EXPECT_EQ(result, StructElement::Unknown);

}



TEST_F(StructElementTest_1785, EmptyString_ReturnsUnknownType_1785) {

    // Arrange

    const char* name = "";



    // Act

    StructElement::Type result = StructElement::nameToType(name);



    // Assert

    EXPECT_EQ(result, StructElement::Unknown);

}



TEST_F(StructElementTest_1785, NullPointer_ReturnsUnknownType_1785) {

    // Arrange

    const char* name = nullptr;



    // Act

    StructElement::Type result = StructElement::nameToType(name);



    // Assert

    EXPECT_EQ(result, StructElement::Unknown);

}
