#include <gtest/gtest.h>

#include "exif_data.hpp"



TEST(ExifDataTest, TestLensModelLookup) {

    ExifData exif;



    // Lens ID 25621: Minolta AF 50mm F1.4 [New]

    exif.setLensID(25621);

    EXPECT_EQ(exif.getLensModel(), "Minolta AF 50mm F1.4 [New]");



    // Lens ID 25890: Minolta AF 80-200mm F2.8 APO

    exif.setLensID(25890);

    EXPECT_EQ(exif.getLensModel(), "Minolta AF 80-200mm F2.8 APO");



    // Lens ID 26131: Minolta AF 50mm F1.7 New

    exif.setLensID(26131);

    EXPECT_EQ(exif.getLensModel(), "Minolta AF 50mm F1.7 New");



    // Lens ID 26441: Minolta AF 100-400mm F4.5-6.7 APO

    exif.setLensID(26441);

    EXPECT_EQ(exif.getLensModel(), "Minolta AF 100-400mm F4.5-6.7 APO");



    // Lens ID 45871: Tamron AF 70-210mm F2.8 SP LD

    exif.setLensID(45871);

    EXPECT_EQ(exif.getLensModel(), "Tamron AF 70-210mm F2.8 SP LD");



    // Lens ID not in the list: should return empty string or default message

    exif.setLensID(99999);

    EXPECT_TRUE(exif.getLensModel().empty() || exif.getLensModel() == "Unknown Lens");

}



TEST(ExifDataTest, TestInvalidLensID) {

    ExifData exif;

    exif.setLensID(65535); // Manual lens | Sony E 50mm F1.8 OSS | E PZ 16-50mm F3.5-5.6 OSS

    EXPECT_EQ(exif.getLensModel(), "Manual lens | Sony E 50mm F1.8 OSS | E PZ 16-50mm F3.5-5.6 OSS");



    exif.setLensID(0); // Invalid Lens ID

    EXPECT_TRUE(exif.getLensModel().empty() || exif.getLensModel() == "Unknown Lens");

}

```


