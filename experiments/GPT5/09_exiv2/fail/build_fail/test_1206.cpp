#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <string>
#include "exiv2/preview.hpp"

namespace Exiv2 {
    // Mock the external writeFile function, if needed
    MOCK_FUNCTION(int, writeFile, (const DataBuf& buf, const std::string& name), (const));
}

class PreviewImageTest : public ::testing::Test {
protected:
    Exiv2::PreviewImage previewImage;

    PreviewImageTest()
        : previewImage(Exiv2::PreviewProperties(), Exiv2::DataBuf()) {}

    // Additional setup can be added here if necessary
};

TEST_F(PreviewImageTest, WriteFile_Test_1206) {
    // Mocking the external interaction with writeFile
    EXPECT_CALL(*this, Exiv2::writeFile).WillOnce([](const Exiv2::DataBuf& buf, const std::string& name) {
        return 0;  // Simulate successful write
    });

    // Act
    size_t result = previewImage.writeFile("test_image.jpg");

    // Verify
    ASSERT_EQ(result, 0);
    // Add any additional assertions here if needed
}

TEST_F(PreviewImageTest, WriteFile_Failure_Test_1207) {
    // Mocking the external interaction with writeFile
    EXPECT_CALL(*this, Exiv2::writeFile).WillOnce([](const Exiv2::DataBuf& buf, const std::string& name) {
        return -1;  // Simulate write failure
    });

    // Act
    size_t result = previewImage.writeFile("test_image.jpg");

    // Verify
    ASSERT_EQ(result, static_cast<size_t>(-1));
}

TEST_F(PreviewImageTest, Copy_Test_1208) {
    // Act
    Exiv2::DataBuf result = previewImage.copy();

    // Verify
    ASSERT_EQ(result.size(), previewImage.size());
    // Check that the copy operation creates an actual copy
}

TEST_F(PreviewImageTest, MimeType_Test_1209) {
    // Set the mimeType in the previewImage object (if needed)
    const std::string expectedMimeType = "image/jpeg";

    // Act
    const std::string& mimeType = previewImage.mimeType();

    // Verify
    ASSERT_EQ(mimeType, expectedMimeType);
}

TEST_F(PreviewImageTest, Extension_Test_1210) {
    // Set the extension in the previewImage object (if needed)
    const std::string expectedExtension = ".jpg";

    // Act
    const std::string& extension = previewImage.extension();

    // Verify
    ASSERT_EQ(extension, expectedExtension);
}

TEST_F(PreviewImageTest, Size_Test_1211) {
    // Set the size in the previewImage object (if needed)
    uint32_t expectedSize = 1024;

    // Act
    uint32_t size = previewImage.size();

    // Verify
    ASSERT_EQ(size, expectedSize);
}

TEST_F(PreviewImageTest, Width_Test_1212) {
    // Set the width in the previewImage object (if needed)
    size_t expectedWidth = 800;

    // Act
    size_t width = previewImage.width();

    // Verify
    ASSERT_EQ(width, expectedWidth);
}

TEST_F(PreviewImageTest, Height_Test_1213) {
    // Set the height in the previewImage object (if needed)
    size_t expectedHeight = 600;

    // Act
    size_t height = previewImage.height();

    // Verify
    ASSERT_EQ(height, expectedHeight);
}

TEST_F(PreviewImageTest, Id_Test_1214) {
    // Set the id in the previewImage object (if needed)
    PreviewId expectedId = 1234;

    // Act
    PreviewId id = previewImage.id();

    // Verify
    ASSERT_EQ(id, expectedId);
}

TEST_F(PreviewImageTest, CopyFromOtherObject_Test_1215) {
    // Create a new PreviewImage object with a different state
    Exiv2::PreviewProperties newProperties;
    Exiv2::DataBuf newData;
    Exiv2::PreviewImage otherPreview(newProperties, std::move(newData));

    // Act
    previewImage = otherPreview;

    // Verify the properties and data are copied correctly
    ASSERT_EQ(previewImage.size(), otherPreview.size());
    ASSERT_EQ(previewImage.mimeType(), otherPreview.mimeType());
}