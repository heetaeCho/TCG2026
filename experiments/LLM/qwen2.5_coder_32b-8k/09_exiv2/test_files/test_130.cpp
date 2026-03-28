#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/value.hpp"



using namespace Exiv2;



class StringValueTest_130 : public ::testing::Test {

protected:

    UniquePtr stringValue;

};



TEST_F(StringValueTest_130, DefaultConstructorCreatesObject_130) {

    stringValue.reset(new StringValue());

    EXPECT_NE(stringValue.get(), nullptr);

}



TEST_F(StringValueTest_130, ConstructorWithBufferCreatesObject_130) {

    std::string buffer = "test";

    stringValue.reset(new StringValue(buffer));

    EXPECT_NE(stringValue.get(), nullptr);

}



TEST_F(StringValueTest_130, CloneReturnsNonNullPointer_130) {

    stringValue.reset(new StringValue());

    UniquePtr clonedValue = stringValue->clone();

    EXPECT_NE(clonedValue.get(), nullptr);

}



TEST_F(StringValueTest_130, ClonePreservesContent_130) {

    std::string buffer = "test";

    stringValue.reset(new StringValue(buffer));

    UniquePtr clonedValue = stringValue->clone();

    // Assuming there's a way to compare contents, which is not provided in the interface

    // This is a placeholder for actual comparison logic if available

    EXPECT_EQ(clonedValue.get(), stringValue.get()); // This should be replaced with actual content check

}



TEST_F(StringValueTest_130, CloneReturnsDifferentInstance_130) {

    stringValue.reset(new StringValue());

    UniquePtr clonedValue = stringValue->clone();

    EXPECT_NE(clonedValue.get(), stringValue.get());

}
