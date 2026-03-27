#include <gtest/gtest.h>

#include "exiv2/value.hpp"



using namespace Exiv2;



class StringValueBaseTest_803 : public ::testing::Test {

protected:

    TypeId typeId = static_cast<TypeId>(1); // Assuming a valid TypeId for testing purposes

    std::string testBuffer = "testString";

    StringValueBase stringValueBase{typeId, ""};

};



TEST_F(StringValueBaseTest_803, ReadFromStdString_Success_803) {

    int result = stringValueBase.read(testBuffer);

    EXPECT_EQ(result, 0);

    EXPECT_EQ(stringValueBase.value_, testBuffer);

}



TEST_F(StringValueBaseTest_803, ReadFromEmptyString_803) {

    std::string emptyBuffer;

    int result = stringValueBase.read(emptyBuffer);

    EXPECT_EQ(result, 0);

    EXPECT_EQ(stringValueBase.value_, emptyBuffer);

}



TEST_F(StringValueBaseTest_803, Count_ReturnsZero_803) {

    size_t count = stringValueBase.count();

    EXPECT_EQ(count, 0);

}



TEST_F(StringValueBaseTest_803, Size_ReturnsSizeOfStoredString_803) {

    stringValueBase.read(testBuffer);

    size_t size = stringValueBase.size();

    EXPECT_EQ(size, testBuffer.size());

}



TEST_F(StringValueBaseTest_803, ToInt64_ThrowsForNonNumericString_803) {

    stringValueBase.read("nonNumeric");

    EXPECT_THROW(stringValueBase.toInt64(0), AnyError);

}



TEST_F(StringValueBaseTest_803, ToUint32_ThrowsForNonNumericString_803) {

    stringValueBase.read("nonNumeric");

    EXPECT_THROW(stringValueBase.toUint32(0), AnyError);

}



TEST_F(StringValueBaseTest_803, ToFloat_ThrowsForNonNumericString_803) {

    stringValueBase.read("nonNumeric");

    EXPECT_THROW(stringValueBase.toFloat(0), AnyError);

}



TEST_F(StringValueBaseTest_803, ToRational_ThrowsForInvalidFormat_803) {

    stringValueBase.read("invalidRational");

    EXPECT_THROW(stringValueBase.toRational(0), AnyError);

}
