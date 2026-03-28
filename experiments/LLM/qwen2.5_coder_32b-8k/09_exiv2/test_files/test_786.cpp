#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/value.hpp"

#include "exiv2/types.hpp"



using namespace Exiv2;

using testing::_;

using testing::Eq;



class ValueTest_786 : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup code, if needed

    }

};



TEST_F(ValueTest_786, CreateWithInvalidTypeId_786) {

    auto value = Value::create(invalidTypeId);

    EXPECT_NE(value.get(), nullptr);

}



TEST_F(ValueTest_786, CreateWithSignedByte_786) {

    auto value = Value::create(signedByte);

    EXPECT_NE(value.get(), nullptr);

}



TEST_F(ValueTest_786, CreateWithUnsignedByte_786) {

    auto value = Value::create(unsignedByte);

    EXPECT_NE(value.get(), nullptr);

}



TEST_F(ValueTest_786, CreateWithAsciiString_786) {

    auto value = Value::create(asciiString);

    EXPECT_NE(value.get(), nullptr);

}



TEST_F(ValueTest_786, CreateWithUnsignedShort_786) {

    auto value = Value::create(unsignedShort);

    EXPECT_NE(value.get(), nullptr);

}



TEST_F(ValueTest_786, CreateWithUnsignedLong_786) {

    auto value = Value::create(unsignedLong);

    EXPECT_NE(value.get(), nullptr);

}



TEST_F(ValueTest_786, CreateWithUnsignedRational_786) {

    auto value = Value::create(unsignedRational);

    EXPECT_NE(value.get(), nullptr);

}



TEST_F(ValueTest_786, CreateWithUndefined_786) {

    auto value = Value::create(undefined);

    EXPECT_NE(value.get(), nullptr);

}



TEST_F(ValueTest_786, CreateWithSignedShort_786) {

    auto value = Value::create(signedShort);

    EXPECT_NE(value.get(), nullptr);

}



TEST_F(ValueTest_786, CreateWithSignedLong_786) {

    auto value = Value::create(signedLong);

    EXPECT_NE(value.get(), nullptr);

}



TEST_F(ValueTest_786, CreateWithSignedRational_786) {

    auto value = Value::create(signedRational);

    EXPECT_NE(value.get(), nullptr);

}



TEST_F(ValueTest_786, CreateWithTiffFloat_786) {

    auto value = Value::create(tiffFloat);

    EXPECT_NE(value.get(), nullptr);

}



TEST_F(ValueTest_786, CreateWithTiffDouble_786) {

    auto value = Value::create(tiffDouble);

    EXPECT_NE(value.get(), nullptr);

}



TEST_F(ValueTest_786, CreateWithString_786) {

    auto value = Value::create(string);

    EXPECT_NE(value.get(), nullptr);

}



TEST_F(ValueTest_786, CreateWithDate_786) {

    auto value = Value::create(date);

    EXPECT_NE(value.get(), nullptr);

}



TEST_F(ValueTest_786, CreateWithTime_786) {

    auto value = Value::create(time);

    EXPECT_NE(value.get(), nullptr);

}



TEST_F(ValueTest_786, CreateWithComment_786) {

    auto value = Value::create(comment);

    EXPECT_NE(value.get(), nullptr);

}



TEST_F(ValueTest_786, CreateWithXmpText_786) {

    auto value = Value::create(xmpText);

    EXPECT_NE(value.get(), nullptr);

}



TEST_F(ValueTest_786, CreateWithXmpBag_786) {

    auto value = Value::create(xmpBag);

    EXPECT_NE(value.get(), nullptr);

}



TEST_F(ValueTest_786, CreateWithXmpSeq_786) {

    auto value = Value::create(xmpSeq);

    EXPECT_NE(value.get(), nullptr);

}



TEST_F(ValueTest_786, CreateWithXmpAlt_786) {

    auto value = Value::create(xmpAlt);

    EXPECT_NE(value.get(), nullptr);

}



TEST_F(ValueTest_786, CreateWithLangAlt_786) {

    auto value = Value::create(langAlt);

    EXPECT_NE(value.get(), nullptr);

}



TEST_F(ValueTest_786, CreateWithTiffIfd_786) {

    auto value = Value::create(tiffIfd);

    EXPECT_NE(value.get(), nullptr);

}
