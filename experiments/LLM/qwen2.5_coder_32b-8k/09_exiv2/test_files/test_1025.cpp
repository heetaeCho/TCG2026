#include <gtest/gtest.h>

#include "ExifData.h" // Assuming ExifData class is defined in this header



// Test case to check if a known lens ID is correctly mapped to its name

TEST(LensIDMappingTest, KnownLensID) {

    ExifData exif;

    uint32_t lensID = 25621; // Minolta AF 50mm F1.4 [New]

    std::string expectedName = "Minolta AF 50mm F1.4 [New]";

    std::string result = exif.getLensName(lensID);

    EXPECT_EQ(result, expectedName);

}



// Test case to check if an unknown lens ID returns a default or empty string

TEST(LensIDMappingTest, UnknownLensID) {

    ExifData exif;

    uint32_t lensID = 99999; // Random invalid lens ID

    std::string result = exif.getLensName(lensID);

    EXPECT_TRUE(result.empty() || result == "Unknown Lens");

}



// Test case to check if a lens ID with multiple mappings returns the correct name

TEST(LensIDMappingTest, MultipleMappings) {

    ExifData exif;

    uint32_t lensID = 25810; // Minolta AF 70-210mm F3.5-4.5

    std::string expectedName = "Minolta AF 70-210mm F3.5-4.5"; // Should be the first mapping listed

    std::string result = exif.getLensName(lensID);

    EXPECT_EQ(result, expectedName);

}



// Test case to check if a lens ID with special characters in its name is correctly mapped

TEST(LensIDMappingTest, SpecialCharactersInName) {

    ExifData exif;

    uint32_t lensID = 65280; // Sigma 16mm F2.8 Filtermatic Fisheye

    std::string expectedName = "Sigma 16mm F2.8 Filtermatic Fisheye";

    std::string result = exif.getLensName(lensID);

    EXPECT_EQ(result, expectedName);

}



// Test case to check if a lens ID with the value 65535 (usually reserved for unknown or manual lenses) is handled correctly

TEST(LensIDMappingTest, ManualOrUnknownLensID) {

    ExifData exif;

    uint32_t lensID = 65535; // Manual lens | Sony E 50mm F1.8 OSS | E PZ 16-50mm F3.5-5.6 OSS

    std::string result = exif.getLensName(lensID);

    EXPECT_TRUE(result.empty() || result == "Manual Lens" || result == "Sony E 50mm F1.8 OSS" || result == "E PZ 16-50mm F3.5-5.6 OSS");

}

```


