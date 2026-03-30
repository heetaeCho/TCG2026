#include <gtest/gtest.h>
#include "exiv2/image.hpp"

namespace Exiv2 {
    class ImageTest_56 : public ::testing::Test {
    protected:
        ImageTest_56() : image_(ImageType::JPEG, 0, nullptr) {}
        
        Image image_;
    };

    // Test case for setting and getting the image type and supported metadata
    TEST_F(ImageTest_56, SetTypeSupported_Success_56) {
        // Setup: calling setTypeSupported with valid parameters
        image_.setTypeSupported(ImageType::JPEG, 5);

        // Verifying the set values
        EXPECT_EQ(image_.imageType(), ImageType::JPEG);
        EXPECT_EQ(image_.supportedMetadata_, 5);
    }

    // Test case for setting supported metadata boundary
    TEST_F(ImageTest_56, SetTypeSupported_BoundaryConditions_56) {
        // Test with minimum valid metadata value
        image_.setTypeSupported(ImageType::TIFF, 0);
        EXPECT_EQ(image_.supportedMetadata_, 0);

        // Test with maximum valid metadata value (assuming 65535 as the max)
        image_.setTypeSupported(ImageType::PNG, 65535);
        EXPECT_EQ(image_.supportedMetadata_, 65535);
    }

    // Test case for invalid image type handling (edge case)
    TEST_F(ImageTest_56, SetTypeSupported_InvalidImageType_56) {
        // ImageType::INVALID might represent an invalid or undefined image type
        image_.setTypeSupported(ImageType::INVALID, 0);
        EXPECT_EQ(image_.imageType(), ImageType::INVALID);
    }

    // Test case for checking if setting supported metadata works with edge value
    TEST_F(ImageTest_56, SetTypeSupported_MaxSupportedMetadata_56) {
        uint16_t maxMetadata = 65535;
        image_.setTypeSupported(ImageType::BMP, maxMetadata);

        // Verifying boundary condition
        EXPECT_EQ(image_.supportedMetadata_, maxMetadata);
    }

    // Test case for image comment functionality (setting and getting comment)
    TEST_F(ImageTest_56, SetComment_56) {
        std::string comment = "Test Image Comment";

        // Set comment
        image_.setComment(comment);

        // Verify if the comment was set correctly
        EXPECT_EQ(image_.comment(), comment);
    }

    // Test case for checking empty comment behavior
    TEST_F(ImageTest_56, SetEmptyComment_56) {
        std::string emptyComment = "";

        // Set empty comment
        image_.setComment(emptyComment);

        // Verify if the comment is empty
        EXPECT_EQ(image_.comment(), emptyComment);
    }

    // Test case for checking exceptional behavior when setting invalid ICC Profile
    TEST_F(ImageTest_56, SetInvalidIccProfile_56) {
        DataBuf invalidProfile;

        // Call the method with invalid profile and check the results
        EXPECT_NO_THROW(image_.setIccProfile(std::move(invalidProfile), false));

        // Verify no exception and no crash
        EXPECT_TRUE(true); // We assume the function does not crash for invalid profile input
    }

    // Test case for checking metadata support functionality
    TEST_F(ImageTest_56, SupportsMetadata_56) {
        MetadataId metadataId = MetadataId::Exif;
        
        // Check if the image supports Exif metadata
        bool supportsExif = image_.supportsMetadata(metadataId);
        
        // Verify expected result (it will return true or false based on internal behavior)
        EXPECT_TRUE(supportsExif);
    }

    // Test case for verifying byte swap functionality (using static method)
    TEST_F(ImageTest_56, ByteSwap_56) {
        uint32_t value = 0x12345678;
        bool swap = true;

        // Perform byte swap and verify the result
        uint32_t swappedValue = Image::byteSwap(value, swap);
        EXPECT_NE(swappedValue, value);  // Ensure the swapped value is different
    }

    // Test case for verifying big endian platform check
    TEST_F(ImageTest_56, IsBigEndianPlatform_56) {
        bool isBigEndian = Image::isBigEndianPlatform();
        
        // This test would depend on the platform where it is run
        EXPECT_TRUE(isBigEndian);  // Verify expected result, change based on your platform
    }

    // Test case for verifying little endian platform check
    TEST_F(ImageTest_56, IsLittleEndianPlatform_56) {
        bool isLittleEndian = Image::isLittleEndianPlatform();
        
        // This test would depend on the platform where it is run
        EXPECT_FALSE(isLittleEndian);  // Verify expected result, change based on your platform
    }
}