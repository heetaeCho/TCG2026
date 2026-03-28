#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/exif.hpp"

#include "exiv2/value.hpp"

#include "tags_int.cpp"



using namespace Exiv2;

using namespace Exiv2::Internal;



class Print0x8822Test_1397 : public ::testing::Test {

protected:

    ExifData metadata;

    Value value;

};



TEST_F(Print0x8822Test_1397, NormalOperation_1397) {

    std::ostringstream os;

    value.setDataArea(reinterpret_cast<const byte*>(&exifExposureProgram[2].num_), sizeof(exifExposureProgram[2].num_));

    print0x8822(os, value, &metadata);

    EXPECT_EQ(os.str(), "Auto");

}



TEST_F(Print0x8822Test_1397, BoundaryCondition_Min_1397) {

    std::ostringstream os;

    value.setDataArea(reinterpret_cast<const byte*>(&exifExposureProgram[0].num_), sizeof(exifExposureProgram[0].num_));

    print0x8822(os, value, &metadata);

    EXPECT_EQ(os.str(), "Not defined");

}



TEST_F(Print0x8822Test_1397, BoundaryCondition_Max_1397) {

    std::ostringstream os;

    value.setDataArea(reinterpret_cast<const byte*>(&exifExposureProgram[8].num_), sizeof(exifExposureProgram[8].num_));

    print0x8822(os, value, &metadata);

    EXPECT_EQ(os.str(), "Landscape mode");

}



TEST_F(Print0x8822Test_1397, ExceptionalCase_OutOfBounds_1397) {

    std::ostringstream os;

    uint16_t out_of_bounds_value = 10; // This value is not defined in exifExposureProgram

    value.setDataArea(reinterpret_cast<const byte*>(&out_of_bounds_value), sizeof(out_of_bounds_value));

    print0x8822(os, value, &metadata);

    EXPECT_EQ(os.str(), "Unknown");

}



TEST_F(Print0x8822Test_1397, MetadataNullptr_1397) {

    std::ostringstream os;

    uint16_t valid_value = 3; // Aperture priority

    value.setDataArea(reinterpret_cast<const byte*>(&valid_value), sizeof(valid_value));

    print0x8822(os, value, nullptr);

    EXPECT_EQ(os.str(), "Aperture priority");

}
