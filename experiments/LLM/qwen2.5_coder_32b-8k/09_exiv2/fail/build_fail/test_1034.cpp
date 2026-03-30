#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/exif.hpp"

#include "exiv2/value.hpp"

#include "./TestProjects/exiv2/src/minoltamn_int.cpp"



using namespace Exiv2;

using namespace Exiv2::Internal;



class MinoltaSonyRotationPrintTest : public ::testing::Test {

protected:

    std::ostringstream os;

    Value mockValue;

    const ExifData* metadata = nullptr; // Assuming no internal state is accessed, metadata can be null



    void SetUp() override {

        mockValue.ok_ = true;

    }

};



TEST_F(MinoltaSonyRotationPrintTest_1034, NormalOperation_Horizontal_1034) {

    EXPECT_CALL(mockValue, toInt64(0)).WillOnce(::testing::Return(0));

    printMinoltaSonyRotation(os, mockValue, metadata);

    EXPECT_EQ("Horizontal (normal)\n", os.str());

}



TEST_F(MinoltaSonyRotationPrintTest_1034, NormalOperation_Rotate90CW_1034) {

    EXPECT_CALL(mockValue, toInt64(0)).WillOnce(::testing::Return(1));

    printMinoltaSonyRotation(os, mockValue, metadata);

    EXPECT_EQ("Rotate 90 CW\n", os.str());

}



TEST_F(MinoltaSonyRotationPrintTest_1034, NormalOperation_Rotate270CW_1034) {

    EXPECT_CALL(mockValue, toInt64(0)).WillOnce(::testing::Return(2));

    printMinoltaSonyRotation(os, mockValue, metadata);

    EXPECT_EQ("Rotate 270 CW\n", os.str());

}



TEST_F(MinoltaSonyRotationPrintTest_1034, BoundaryCondition_OutOfRangeNegative_1034) {

    EXPECT_CALL(mockValue, toInt64(0)).WillOnce(::testing::Return(-1));

    printMinoltaSonyRotation(os, mockValue, metadata);

    EXPECT_EQ("Unknown rotation value (-1)\n", os.str());

}



TEST_F(MinoltaSonyRotationPrintTest_1034, BoundaryCondition_OutOfRangePositive_1034) {

    EXPECT_CALL(mockValue, toInt64(0)).WillOnce(::testing::Return(3));

    printMinoltaSonyRotation(os, mockValue, metadata);

    EXPECT_EQ("Unknown rotation value (3)\n", os.str());

}



TEST_F(MinoltaSonyRotationPrintTest_1034, ErrorCase_ValueNotOk_1034) {

    mockValue.ok_ = false;

    EXPECT_CALL(mockValue, toInt64(0)).WillOnce(::testing::Return(0));

    printMinoltaSonyRotation(os, mockValue, metadata);

    EXPECT_EQ("Invalid value\n", os.str());

}
