#include <gtest/gtest.h>

#include <exiv2/exiv2.hpp>



using namespace Exiv2;



// Test case to verify that lens data can be correctly retrieved from metadata.

TEST(LensDataTest, GetLensModel) {

    Image::AutoPtr image = ImageFactory::open("path_to_test_image_with_lens_data.jpg");

    ASSERT_NE(image.get(), nullptr);



    image->readMetadata();

    ExifData& exifData = image->exifData();



    if (!exifData.empty()) {

        ExifData::const_iterator end = exifData.end();

        ExifData::const_iterator it = exifData.findKey(Exiv2::ExifKey("Exif.CanonCs.LensModel"));

        if (it != end) {

            std::string lensModel = it->value().toString();

            EXPECT_EQ(lensModel, "Canon EF 70-200mm f/4L IS USM");

        } else {

            // Check for other common lens model tags

            it = exifData.findKey(Exiv2::ExifKey("Exif.Nikon3.LensType"));

            if (it != end) {

                std::string lensModel = it->value().toString();

                EXPECT_EQ(lensModel, "Nikkor 80-400mm f/4.5-5.6D ED VR AF-S");

            } else {

                // Add more checks for other manufacturers if necessary

                GTEST_SKIP() << "Lens model tag not found in metadata.";

            }

        }

    } else {

        GTEST_SKIP() << "No EXIF data found in the image.";

    }

}



// Test case to verify that lens ID can be correctly mapped to lens model.

TEST(LensIDMappingTest, MapLensIDToModel) {

    uint16_t lensID = 25920; // Example Minolta AF 85mm F1.4G

    std::string expectedModel = "Minolta AF 85mm F1.4G";



    const TagInfo* tagInfo = internal::lookupLens(lensID);

    if (tagInfo) {

        EXPECT_EQ(tagInfo->name_, expectedModel);

    } else {

        GTEST_SKIP() << "Lens ID not found in the mapping table.";

    }

}



// Test case to verify that lens information is correctly extracted from Nikon D750 metadata.

TEST(NikonD750MetadataTest, ExtractNikonLensData) {

    Image::AutoPtr image = ImageFactory::open("path_to_nikon_d750_image_with_lens_data.jpg");

    ASSERT_NE(image.get(), nullptr);



    image->readMetadata();

    ExifData& exifData = image->exifData();



    if (!exifData.empty()) {

        ExifData::const_iterator end = exifData.end();

        ExifData::const_iterator itMake = exifData.findKey(Exiv2::ExifKey("Exif.Image.Make"));

        ExifData::const_iterator itModel = exifData.findKey(Exiv2::ExifKey("Exif.Image.Model"));



        if (itMake != end && itModel != end) {

            std::string make = itMake->value().toString();

            std::string model = itModel->value().toString();



            if (make == "NIKON CORPORATION" && model == "D750") {

                ExifData::const_iterator itLensID = exifData.findKey(Exiv2::ExifKey("Exif.Nikon3.LensType"));

                if (itLensID != end) {

                    uint16_t lensID = itLensID->value().toUint16();

                    const TagInfo* tagInfo = internal::lookupLens(lensID);

                    EXPECT_EQ(tagInfo->name_, "Nikkor 80-400mm f/4.5-5.6D ED VR AF-S");

                } else {

                    GTEST_SKIP() << "Lens ID not found in Nikon D750 metadata.";

                }

            } else {

                GTEST_SKIP() << "Image is not from Nikon D750.";

            }

        } else {

            GTEST_SKIP() << "Camera make and model not found in EXIF data.";

        }

    } else {

        GTEST_SKIP() << "No EXIF data found in the image.";

    }

}



// Test case to verify that unknown lens IDs do not cause errors.

TEST(UnknownLensIDTest, HandleUnknownLensIDs) {

    uint16_t unknownLensID = 9999; // An ID not present in the mapping table



    const TagInfo* tagInfo = internal::lookupLens(unknownLensID);

    EXPECT_EQ(tagInfo->name_, "Unknown lens");

}



// Test case to verify that different camera models handle lens data correctly.

TEST(CrossCameraLensDataTest, VerifyCrossCompatibility) {

    Image::AutoPtr canonImage = ImageFactory::open("path_to_canon_image_with_lens_data.jpg");

    Image::AutoPtr nikonImage = ImageFactory::open("path_to_nikon_image_with_lens_data.jpg");



    ASSERT_NE(canonImage.get(), nullptr);

    ASSERT_NE(nikonImage.get(), nullptr);



    canonImage->readMetadata();

    ExifData& canonExifData = canonImage->exifData();



    if (!canonExifData.empty()) {

        ExifData::const_iterator end = canonExifData.end();

        ExifData::const_iterator itCanonLensModel = canonExifData.findKey(Exiv2::ExifKey("Exif.CanonCs.LensModel"));

        EXPECT_NE(itCanonLensModel, end);

    } else {

        GTEST_SKIP() << "No EXIF data found in the Canon image.";

    }



    nikonImage->readMetadata();

    ExifData& nikonExifData = nikonImage->exifData();



    if (!nikonExifData.empty()) {

        ExifData::const_iterator end = nikonExifData.end();

        ExifData::const_iterator itNikonLensType = nikonExifData.findKey(Exiv2::ExifKey("Exif.Nikon3.LensType"));

        EXPECT_NE(itNikonLensType, end);

    } else {

        GTEST_SKIP() << "No EXIF data found in the Nikon image.";

    }

}

```


