#include <gtest/gtest.h>

#include <exiv2/exiv2.hpp>



using namespace Exiv2;



// Test case to check if lens ID 25500 (Minolta AF 50mm F1.7) can be correctly mapped to its description.

TEST(LensTest, MinoltaAF50F1_7) {

    TagInfo tag("LensID", N_("Lens ID"), N_("Exif.Minolta.LensID"), N_("Lens ID"),

                ttUnsignedLong, 4, mkMinolta);

    

    const char* lensDesc = "Minolta AF 50mm F1.7";

    uint32_t lensId = 25500;

    Value::AutoPtr value(new ULongValue(&lensId));

    tag.value_ = value.get();

    

    std::string result = tag.writeComment();

    EXPECT_EQ(result, lensDesc);

}



// Test case to check if lens ID 12345 (an invalid or non-existent lens) returns an empty string.

TEST(LensTest, InvalidLensID) {

    TagInfo tag("LensID", N_("Lens ID"), N_("Exif.Minolta.LensID"), N_("Lens ID"),

                ttUnsignedLong, 4, mkMinolta);

    

    uint32_t invalidLensId = 12345;

    Value::AutoPtr value(new ULongValue(&invalidLensId));

    tag.value_ = value.get();

    

    std::string result = tag.writeComment();

    EXPECT_EQ(result, "");

}



// Test case to check if lens ID 26071 (Minolta AF 35-80mm F4-5.6) can be correctly mapped to its description.

TEST(LensTest, MinoltaAF35to80F4_5_6) {

    TagInfo tag("LensID", N_("Lens ID"), N_("Exif.Minolta.LensID"), N_("Lens ID"),

                ttUnsignedLong, 4, mkMinolta);

    

    const char* lensDesc = "Minolta AF 35-80mm F4-5.6";

    uint32_t lensId = 26071;

    Value::AutoPtr value(new ULongValue(&lensId));

    tag.value_ = value.get();

    

    std::string result = tag.writeComment();

    EXPECT_EQ(result, lensDesc);

}



// Test case to check if lens ID 45871 (Tamron AF 70-210mm F2.8 SP LD) can be correctly mapped to its description.

TEST(LensTest, TamronAF70to210F2_8SP_LD) {

    TagInfo tag("LensID", N_("Lens ID"), N_("Exif.Minolta.LensID"), N_("Lens ID"),

                ttUnsignedLong, 4, mkMinolta);

    

    const char* lensDesc = "Tamron AF 70-210mm F2.8 SP LD";

    uint32_t lensId = 45871;

    Value::AutoPtr value(new ULongValue(&lensId));

    tag.value_ = value.get();

    

    std::string result = tag.writeComment();

    EXPECT_EQ(result, lensDesc);

}



// Test case to check if lens ID 65535 (Manual lens | Sony E 50mm F1.8 OSS | E PZ 16-50mm F3.5-5.6 OSS) can be correctly mapped to its description.

TEST(LensTest, MultipleLensID_65535) {

    TagInfo tag("LensID", N_("Lens ID"), N_("Exif.Minolta.LensID"), N_("Lens ID"),

                ttUnsignedLong, 4, mkMinolta);

    

    const char* lensDesc = "Manual lens | Sony E 50mm F1.8 OSS | E PZ 16-50mm F3.5-5.6 OSS";

    uint32_t lensId = 65535;

    Value::AutoPtr value(new ULongValue(&lensId));

    tag.value_ = value.get();

    

    std::string result = tag.writeComment();

    EXPECT_EQ(result, lensDesc);

}



// Test case to check if lens ID 0 (should be an invalid or non-existent lens) returns an empty string.

TEST(LensTest, ZeroLensID) {

    TagInfo tag("LensID", N_("Lens ID"), N_("Exif.Minolta.LensID"), N_("Lens ID"),

                ttUnsignedLong, 4, mkMinolta);

    

    uint32_t zeroLensId = 0;

    Value::AutoPtr value(new ULongValue(&zeroLensId));

    tag.value_ = value.get();

    

    std::string result = tag.writeComment();

    EXPECT_EQ(result, "");

}
