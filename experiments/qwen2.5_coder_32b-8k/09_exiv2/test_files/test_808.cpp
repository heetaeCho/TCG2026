#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/value.hpp"

#include <sstream>



using namespace Exiv2;

using ::testing::Eq;



class StringValueBaseTest_808 : public ::testing::Test {

protected:

    std::string testString = "testValue";

    TypeId typeId = static_cast<TypeId>(1); // Assuming a valid type id for the purpose of testing

    StringValueBase* stringValueBase;



    void SetUp() override {

        stringValueBase = new StringValueBase(typeId, testString);

    }



    void TearDown() override {

        delete stringValueBase;

    }

};



TEST_F(StringValueBaseTest_808, WriteToStream_808) {

    std::ostringstream os;

    stringValueBase->write(os);

    EXPECT_EQ(testString, os.str());

}



TEST_F(StringValueBaseTest_808, ConstructorInitialization_808) {

    EXPECT_EQ(testString, stringValueBase->value_);

}



TEST_F(StringValueBaseTest_808, ReadFromStringBuffer_808) {

    std::string newStringValue = "newTestValue";

    int result = stringValueBase->read(newStringValue);

    EXPECT_EQ(0, result); // Assuming read returns 0 on success

    EXPECT_EQ(newStringValue, stringValueBase->value_);

}



TEST_F(StringValueBaseTest_808, ReadFromByteBuffer_808) {

    const byte newByteValue[] = "newTestValue";

    int result = stringValueBase->read(newByteValue, sizeof(newByteValue), littleEndian);

    EXPECT_EQ(0, result); // Assuming read returns 0 on success

    EXPECT_EQ("newTestValue", stringValueBase->value_);

}



TEST_F(StringValueBaseTest_808, CopyToBuffer_808) {

    byte buffer[100];

    size_t copiedSize = stringValueBase->copy(buffer, littleEndian);

    EXPECT_EQ(testString.size(), copiedSize);

    EXPECT_STREQ(testString.c_str(), reinterpret_cast<char*>(buffer));

}



TEST_F(StringValueBaseTest_808, CountMethod_808) {

    size_t count = stringValueBase->count();

    EXPECT_EQ(1, count); // Assuming count returns 1 for a single string value

}



TEST_F(StringValueBaseTest_808, SizeMethod_808) {

    size_t size = stringValueBase->size();

    EXPECT_EQ(testString.size(), size);

}



TEST_F(StringValueBaseTest_808, ToInt64Conversion_808) {

    int64_t result = stringValueBase->toInt64(0);

    EXPECT_EQ(0, result); // Assuming conversion to int64 returns 0 for non-numeric strings

}



TEST_F(StringValueBaseTest_808, ToUint32Conversion_808) {

    uint32_t result = stringValueBase->toUint32(0);

    EXPECT_EQ(0U, result); // Assuming conversion to uint32 returns 0 for non-numeric strings

}



TEST_F(StringValueBaseTest_808, ToFloatConversion_808) {

    float result = stringValueBase->toFloat(0);

    EXPECT_FLOAT_EQ(0.0f, result); // Assuming conversion to float returns 0.0 for non-numeric strings

}



TEST_F(StringValueBaseTest_808, ToRationalConversion_808) {

    Rational result = stringValueBase->toRational(0);

    EXPECT_EQ(Rational(0, 1), result); // Assuming conversion to Rational returns (0/1) for non-numeric strings

}
