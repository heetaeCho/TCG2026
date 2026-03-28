#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/exiv2/src/value.cpp"



using namespace Exiv2;



class StringValueBaseTest : public ::testing::Test {

protected:

    std::string testString = "test_string";

    StringValueBase stringValue;

};



TEST_F(StringValueBaseTest_805, CopyToBuffer_NormalOperation_805) {

    byte buffer[100];

    size_t result = stringValue.copy(buffer, ByteOrder::big);

    EXPECT_EQ(result, 0); // Empty string case



    stringValue.value_ = testString;

    result = stringValue.copy(buffer, ByteOrder::big);

    EXPECT_EQ(result, testString.size());

    EXPECT_STREQ(reinterpret_cast<char*>(buffer), testString.c_str());

}



TEST_F(StringValueBaseTest_805, CopyToBuffer_BoundaryCondition_EmptyString_805) {

    byte buffer[1];

    size_t result = stringValue.copy(buffer, ByteOrder::little);

    EXPECT_EQ(result, 0); // Empty string case

}



TEST_F(StringValueBaseTest_805, CopyToBuffer_BoundaryCondition_BufferTooSmall_805) {

    stringValue.value_ = testString;

    byte buffer[3]; // Buffer smaller than the string length

    size_t result = stringValue.copy(buffer, ByteOrder::big);

    EXPECT_EQ(result, 3); // It should copy as much as fits

    EXPECT_STREQ(reinterpret_cast<char*>(buffer), "tes");

}



TEST_F(StringValueBaseTest_805, CopyToBuffer_ExceptionalCase_NullBuffer_805) {

    stringValue.value_ = testString;

    size_t result = stringValue.copy(nullptr, ByteOrder::big);

    EXPECT_EQ(result, 0); // Should handle null buffer gracefully

}
