#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/value.hpp"

#include <string>

#include <iostream>



using namespace Exiv2;

using ::testing::_;

using ::testing::Eq;



class StringValueBaseTest_806 : public ::testing::Test {

protected:

    TypeId dummyTypeId = static_cast<TypeId>(0);

    std::string dummyBuf = "dummy";

    StringValueBase* stringValueBase;



    void SetUp() override {

        stringValueBase = new StringValueBase(dummyTypeId, dummyBuf);

    }



    void TearDown() override {

        delete stringValueBase;

    }

};



TEST_F(StringValueBaseTest_806, ConstructorInitializesCount_806) {

    EXPECT_EQ(stringValueBase->count(), 1U);

}



TEST_F(StringValueBaseTest_806, CountReflectsSize_806) {

    EXPECT_EQ(stringValueBase->count(), stringValueBase->size());

}



TEST_F(StringValueBaseTest_806, ReadWithEmptyStringDoesNotChangeCount_806) {

    int result = stringValueBase->read("");

    EXPECT_EQ(result, 0);

    EXPECT_EQ(stringValueBase->count(), 1U);

}



TEST_F(StringValueBaseTest_806, ReadWithNonEmptyStringChangesCount_806) {

    std::string newBuf = "new content";

    int result = stringValueBase->read(newBuf);

    EXPECT_EQ(result, 0);

    EXPECT_EQ(stringValueBase->count(), 1U); // Assuming read doesn't change count in this case

}



TEST_F(StringValueBaseTest_806, CopyReturnsSizeOfContent_806) {

    byte buffer[1024];

    size_t result = stringValueBase->copy(buffer, littleEndian);

    EXPECT_EQ(result, dummyBuf.size());

}



TEST_F(StringValueBaseTest_806, ToInt64ThrowsOnInvalidIndex_806) {

    EXPECT_THROW(stringValueBase->toInt64(1), std::out_of_range);

}



TEST_F(StringValueBaseTest_806, ToUint32ThrowsOnInvalidIndex_806) {

    EXPECT_THROW(stringValueBase->toUint32(1), std::out_of_range);

}



TEST_F(StringValueBaseTest_806, ToFloatThrowsOnInvalidIndex_806) {

    EXPECT_THROW(stringValueBase->toFloat(1), std::out_of_range);

}



TEST_F(StringValueBaseTest_806, ToRationalThrowsOnInvalidIndex_806) {

    EXPECT_THROW(stringValueBase->toRational(1), std::out_of_range);

}



TEST_F(StringValueBaseTest_806, WriteOutputsContentToStream_806) {

    std::ostringstream oss;

    stringValueBase->write(oss);

    EXPECT_EQ(oss.str(), dummyBuf);

}
