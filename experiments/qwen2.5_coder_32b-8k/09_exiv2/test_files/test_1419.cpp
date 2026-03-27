#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <exiv2/exif.hpp>

#include <exiv2/value.hpp>



using namespace Exiv2;

using namespace Exiv2::Internal;



class TagsIntTest_1419 : public ::testing::Test {

protected:

    std::ostringstream os;

    Value value;

    ExifData metadata;

};



TEST_F(TagsIntTest_1419, Print0xa40c_NormalOperation_1419) {

    // Assuming the value is set to a valid tag id within exifSubjectDistanceRange

    value.setDataArea(reinterpret_cast<const byte*>(&exifSubjectDistanceRange[1].value_), sizeof(exifSubjectDistanceRange[1].value_));

    print0xa40c(os, value, &metadata);

    EXPECT_EQ(os.str(), "Macro");

}



TEST_F(TagsIntTest_1419, Print0xa40c_BoundaryConditionMin_1419) {

    // Assuming the value is set to the minimum tag id within exifSubjectDistanceRange

    value.setDataArea(reinterpret_cast<const byte*>(&exifSubjectDistanceRange[0].value_), sizeof(exifSubjectDistanceRange[0].value_));

    print0xa40c(os, value, &metadata);

    EXPECT_EQ(os.str(), "Unknown");

}



TEST_F(TagsIntTest_1419, Print0xa40c_BoundaryConditionMax_1419) {

    // Assuming the value is set to the maximum tag id within exifSubjectDistanceRange

    value.setDataArea(reinterpret_cast<const byte*>(&exifSubjectDistanceRange[3].value_), sizeof(exifSubjectDistanceRange[3].value_));

    print0xa40c(os, value, &metadata);

    EXPECT_EQ(os.str(), "Distant view");

}



TEST_F(TagsIntTest_1419, Print0xa40c_OutOfBounds_1419) {

    // Assuming the value is set to an out-of-bounds tag id

    int outOfBoundsValue = 4; // This should be outside the valid range of exifSubjectDistanceRange indices

    value.setDataArea(reinterpret_cast<const byte*>(&outOfBoundsValue), sizeof(outOfBoundsValue));

    print0xa40c(os, value, &metadata);

    EXPECT_EQ(os.str(), "");

}



TEST_F(TagsIntTest_1419, Print0xa40c_MetadataNull_1419) {

    // Assuming the metadata is null

    int validValue = 2;

    value.setDataArea(reinterpret_cast<const byte*>(&validValue), sizeof(validValue));

    print0xa40c(os, value, nullptr);

    EXPECT_EQ(os.str(), "Close view");

}
