#include <gtest/gtest.h>

#include "exiv2/exif.hpp"



namespace Exiv2 {



class ExifdatumTest_732 : public ::testing::Test {

protected:

    ExifKey key;

    Value* value = nullptr;

    Exifdatum exifDatum;



    ExifdatumTest_732() : key("Exif.Image.Artist"), exifDatum(key, value) {}

};



TEST_F(ExifdatumTest_732, AssignUint16Value_NormalOperation_732) {

    uint16_t testValue = 42;

    Exifdatum& result = exifDatum = testValue;

    EXPECT_EQ(&result, &exifDatum);

}



TEST_F(ExifdatumTest_732, AssignUint16Value_BoundaryCondition_732) {

    uint16_t minValue = 0;

    uint16_t maxValue = UINT16_MAX;



    Exifdatum& resultMin = exifDatum = minValue;

    EXPECT_EQ(&resultMin, &exifDatum);



    Exifdatum& resultMax = exifDatum = maxValue;

    EXPECT_EQ(&resultMax, &exifDatum);

}



TEST_F(ExifdatumTest_732, Key_ReturnsCorrectValue_732) {

    std::string expectedKey = "Exif.Image.Artist";

    EXPECT_EQ(exifDatum.key(), expectedKey);

}



TEST_F(ExifdatumTest_732, FamilyName_ReturnsExpectedString_732) {

    const char* expectedFamilyName = "Exif";

    EXPECT_STREQ(exifDatum.familyName(), expectedFamilyName);

}



TEST_F(ExifdatumTest_732, GroupName_ReturnsExpectedString_732) {

    std::string expectedGroupName = "Image";

    EXPECT_EQ(exifDatum.groupName(), expectedGroupName);

}



TEST_F(ExifdatumTest_732, TagName_ReturnsExpectedString_732) {

    std::string expectedTagName = "Artist";

    EXPECT_EQ(exifDatum.tagName(), expectedTagName);

}



TEST_F(ExifdatumTest_732, TagLabel_ReturnsEmptyString_732) {

    // Assuming tagLabel returns an empty string as it's not specified in the interface

    EXPECT_TRUE(exifDatum.tagLabel().empty());

}



TEST_F(ExifdatumTest_732, TagDesc_ReturnsEmptyString_732) {

    // Assuming tagDesc returns an empty string as it's not specified in the interface

    EXPECT_TRUE(exifDatum.tagDesc().empty());

}



TEST_F(ExifdatumTest_732, Tag_ReturnsCorrectValue_732) {

    uint16_t expectedTag = 0x013B; // Known tag for Artist

    EXPECT_EQ(exifDatum.tag(), expectedTag);

}



}  // namespace Exiv2
