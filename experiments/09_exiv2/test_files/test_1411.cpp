#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/exif.hpp"

#include "exiv2/value.hpp"



using namespace Exiv2;

using namespace Exiv2::Internal;



class TagsIntTest_1411 : public ::testing::Test {

protected:

    Value value_;

    ExifData metadata_;



    TagsIntTest_1411() : value_(TypeId::unsignedShort) {}

};



TEST_F(TagsIntTest_1411, NormalOperation_Print0xa401_NormalProcess_1411) {

    std::ostringstream oss;

    value_.setDataArea(reinterpret_cast<const byte*>(&exifCustomRendered[0].value_), sizeof(exifCustomRendered[0].value_));

    print0xa401(oss, value_, &metadata_);

    EXPECT_EQ(oss.str(), "Normal process");

}



TEST_F(TagsIntTest_1411, NormalOperation_Print0xa401_CustomProcess_1411) {

    std::ostringstream oss;

    value_.setDataArea(reinterpret_cast<const byte*>(&exifCustomRendered[1].value_), sizeof(exifCustomRendered[1].value_));

    print0xa401(oss, value_, &metadata_);

    EXPECT_EQ(oss.str(), "Custom process");

}



TEST_F(TagsIntTest_1411, BoundaryCondition_Print0xa401_OutOfBoundsValue_1411) {

    std::ostringstream oss;

    uint16_t outOfBoundsValue = 2; // Assuming only values 0 and 1 are valid

    value_.setDataArea(reinterpret_cast<const byte*>(&outOfBoundsValue), sizeof(outOfBoundsValue));

    print0xa401(oss, value_, &metadata_);

    EXPECT_EQ(oss.str(), ""); // No corresponding string in exifCustomRendered

}



TEST_F(TagsIntTest_1411, BoundaryCondition_Print0xa401_ZeroLengthData_1411) {

    std::ostringstream oss;

    value_.setDataArea(nullptr, 0);

    print0xa401(oss, value_, &metadata_);

    EXPECT_EQ(oss.str(), ""); // No data to process

}



TEST_F(TagsIntTest_1411, ExceptionalCase_Print0xa401_InvalidData_1411) {

    std::ostringstream oss;

    uint8_t invalidData = 255; // Invalid value

    value_.setDataArea(&invalidData, sizeof(invalidData));

    print0xa401(oss, value_, &metadata_);

    EXPECT_EQ(oss.str(), ""); // No corresponding string in exifCustomRendered

}
