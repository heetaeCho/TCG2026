#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/value.hpp"

#include <string>

#include <sstream>



using namespace Exiv2;

using ::testing::_;

using ::testing::Return;



class StringValueBaseTest_807 : public ::testing::Test {

protected:

    StringValueBase* stringValueBase;



    void SetUp() override {

        stringValueBase = new StringValueBase(TypeId::asciiString, "initial");

    }



    void TearDown() override {

        delete stringValueBase;

    }

};



TEST_F(StringValueBaseTest_807, InitialSize_807) {

    EXPECT_EQ(stringValueBase->size(), 7U); // "initial" has 7 characters

}



TEST_F(StringValueBaseTest_807, ReadStringBuffer_807) {

    int result = stringValueBase->read("newvalue");

    EXPECT_EQ(result, 0);

    EXPECT_EQ(stringValueBase->size(), 8U); // "newvalue" has 8 characters

}



TEST_F(StringValueBaseTest_807, ReadByteBuffer_807) {

    const char* buffer = "bytebuffer";

    int result = stringValueBase->read(reinterpret_cast<const byte*>(buffer), 12, ByteOrder::bigEndian);

    EXPECT_EQ(result, 0);

    EXPECT_EQ(stringValueBase->size(), 12U); // 12 characters were read

}



TEST_F(StringValueBaseTest_807, CopyBuffer_807) {

    byte buffer[10];

    size_t result = stringValueBase->copy(buffer, ByteOrder::bigEndian);

    EXPECT_EQ(result, 7U); // "initial" has 7 characters

    std::string copiedString(reinterpret_cast<char*>(buffer), result);

    EXPECT_EQ(copiedString, "initial");

}



TEST_F(StringValueBaseTest_807, CountValues_807) {

    size_t result = stringValueBase->count();

    EXPECT_EQ(result, 1U); // Assuming count returns number of values, which is 1 for a single string

}



TEST_F(StringValueBaseTest_807, WriteToStream_807) {

    std::ostringstream oss;

    stringValueBase->write(oss);

    EXPECT_EQ(oss.str(), "initial");

}



TEST_F(StringValueBaseTest_807, ToInt64_807) {

    int64_t result = stringValueBase->toInt64(0);

    EXPECT_EQ(result, 0); // Cannot convert non-numeric string to int64

}



TEST_F(StringValueBaseTest_807, ToUint32_807) {

    uint32_t result = stringValueBase->toUint32(0);

    EXPECT_EQ(result, 0U); // Cannot convert non-numeric string to uint32

}



TEST_F(StringValueBaseTest_807, ToFloat_807) {

    float result = stringValueBase->toFloat(0);

    EXPECT_FLOAT_EQ(result, 0.0f); // Cannot convert non-numeric string to float

}



TEST_F(StringValueBaseTest_807, ToRational_807) {

    Rational result = stringValueBase->toRational(0);

    EXPECT_TRUE(result == Rational(0)); // Cannot convert non-numeric string to rational

}
