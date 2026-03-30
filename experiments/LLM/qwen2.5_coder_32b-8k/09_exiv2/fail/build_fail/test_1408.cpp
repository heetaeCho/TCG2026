#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/exif.hpp"

#include "exiv2/value.hpp"

#include "./TestProjects/exiv2/src/tags_int.cpp"



using namespace Exiv2;

using namespace Exiv2::Internal;



class Print0xa217Test_1408 : public ::testing::Test {

protected:

    MockValue mockValue;

    ExifData exifData;

};



TEST_F(Print0xa217Test_1408, NormalOperation_1408) {

    EXPECT_CALL(mockValue, ok())

        .WillRepeatedly(::testing::Return(true));



    std::ostringstream os;

    print0xa217(os, mockValue, &exifData);

    EXPECT_EQ(os.str(), "Not defined");

}



TEST_F(Print0xa217Test_1408, BoundaryCondition_ValueNotDefined_1408) {

    EXPECT_CALL(mockValue, ok())

        .WillRepeatedly(::testing::Return(true));



    std::ostringstream os;

    mockValue.ok_ = false;

    print0xa217(os, mockValue, &exifData);

    EXPECT_EQ(os.str(), "");

}



TEST_F(Print0xa217Test_1408, ExceptionalCase_MetadataNull_1408) {

    EXPECT_CALL(mockValue, ok())

        .WillRepeatedly(::testing::Return(true));



    std::ostringstream os;

    print0xa217(os, mockValue, nullptr);

    EXPECT_EQ(os.str(), "Not defined");

}



class MockValue : public Value {

public:

    MOCK_METHOD(bool, ok, (), (const));

};



TEST_F(Print0xa217Test_1408, VerificationOfExternalInteractions_1408) {

    EXPECT_CALL(mockValue, ok())

        .WillRepeatedly(::testing::Return(true));



    std::ostringstream os;

    print0xa217(os, mockValue, &exifData);

    EXPECT_EQ(os.str(), "Not defined");

}



TEST_F(Print0xa217Test_1408, NormalOperation_ValueTwoChipColorArea_1408) {

    EXPECT_CALL(mockValue, ok())

        .WillRepeatedly(::testing::Return(true));



    std::ostringstream os;

    mockValue.toUint32(0) = 2; // Simulate the value to be two-chip color area

    print0xa217(os, mockValue, &exifData);

    EXPECT_EQ(os.str(), "One-chip color area");

}



TEST_F(Print0xa217Test_1408, BoundaryCondition_ValueGreaterThanMax_1408) {

    EXPECT_CALL(mockValue, ok())

        .WillRepeatedly(::testing::Return(true));



    std::ostringstream os;

    mockValue.toUint32(0) = 9; // Simulate the value to be out of bounds

    print0xa217(os, mockValue, &exifData);

    EXPECT_EQ(os.str(), "");

}
