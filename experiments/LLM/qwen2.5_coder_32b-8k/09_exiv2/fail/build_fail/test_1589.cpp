#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/exif.hpp"

#include "exiv2/value.hpp"

#include "./TestProjects/exiv2/src/sonymn_int.hpp"



using namespace Exiv2;

using namespace Exiv2::Internal;



class SonyMakerNoteTest_1589 : public ::testing::Test {

protected:

    Value mockValue;

    const ExifData* mockMetadata = nullptr;

};



TEST_F(SonyMakerNoteTest_1589, PrintMultiBurstMode_NormalOperation_TypeIdUndefinedCountOne_1589) {

    mockValue.typeId() = undefined;

    EXPECT_CALL(mockValue, count()).WillOnce(::testing::Return(1));



    std::ostringstream os;

    SonyMakerNote::printMultiBurstMode(os, mockValue, mockMetadata);

    EXPECT_EQ(os.str(), "(<unknown>)");

}



TEST_F(SonyMakerNoteTest_1589, PrintMultiBurstMode_NormalOperation_TypeIdNotUndefinedCountOne_1589) {

    mockValue.typeId() = unsignedByte;

    EXPECT_CALL(mockValue, count()).WillOnce(::testing::Return(1));



    std::ostringstream os;

    EXPECT_CALL(*this, printMinoltaSonyBoolValue(os, mockValue, mockMetadata))

        .WillOnce(::testing::ReturnRef(os));

    SonyMakerNote::printMultiBurstMode(os, mockValue, mockMetadata);

}



TEST_F(SonyMakerNoteTest_1589, PrintMultiBurstMode_BoundaryCondition_CountZero_1589) {

    mockValue.typeId() = undefined;

    EXPECT_CALL(mockValue, count()).WillOnce(::testing::Return(0));



    std::ostringstream os;

    SonyMakerNote::printMultiBurstMode(os, mockValue, mockMetadata);

    EXPECT_EQ(os.str(), "(<unknown>)");

}



TEST_F(SonyMakerNoteTest_1589, PrintMultiBurstMode_BoundaryCondition_CountGreaterThanOne_1589) {

    mockValue.typeId() = undefined;

    EXPECT_CALL(mockValue, count()).WillOnce(::testing::Return(2));



    std::ostringstream os;

    SonyMakerNote::printMultiBurstMode(os, mockValue, mockMetadata);

    EXPECT_EQ(os.str(), "(<unknown>)");

}



TEST_F(SonyMakerNoteTest_1589, PrintMultiBurstMode_ExceptionalCase_TypeIdUndefinedCountZero_1589) {

    mockValue.typeId() = undefined;

    EXPECT_CALL(mockValue, count()).WillOnce(::testing::Return(0));



    std::ostringstream os;

    SonyMakerNote::printMultiBurstMode(os, mockValue, mockMetadata);

    EXPECT_EQ(os.str(), "(<unknown>)");

}



TEST_F(SonyMakerNoteTest_1589, PrintMultiBurstMode_ExceptionalCase_TypeIdUndefinedCountGreaterThanOne_1589) {

    mockValue.typeId() = undefined;

    EXPECT_CALL(mockValue, count()).WillOnce(::testing::Return(2));



    std::ostringstream os;

    SonyMakerNote::printMultiBurstMode(os, mockValue, mockMetadata);

    EXPECT_EQ(os.str(), "(<unknown>)");

}
