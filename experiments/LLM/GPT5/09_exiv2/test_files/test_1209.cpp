#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "exiv2/preview.hpp"
#include "exiv2/types.hpp"

namespace Exiv2 {

class PreviewImageTest : public ::testing::Test {
protected:
    // Setup and teardown code can be added here if needed for initializing common test data
    PreviewImageTest() = default;
    ~PreviewImageTest() override = default;
};

// Test for the size() method in PreviewImage class
TEST_F(PreviewImageTest, Size_1209) {
    // Arrange: Create a PreviewImage instance with some mock data
    DataBuf data(100); // Let's assume 100 is a valid size
    PreviewProperties properties;
    PreviewImage preview(properties, std::move(data));

    // Act: Call the size method
    uint32_t size = preview.size();

    // Assert: Verify that the size matches the expected value
    EXPECT_EQ(size, 100);  // The size should be 100 based on the constructor
}

// Test for the copy() method in PreviewImage class
TEST_F(PreviewImageTest, Copy_1209) {
    // Arrange: Create a PreviewImage instance with mock data
    DataBuf data(50); // 50 bytes
    PreviewProperties properties;
    PreviewImage preview(properties, std::move(data));

    // Act: Call the copy method
    DataBuf copiedData = preview.copy();

    // Assert: Verify the copied data has the same size
    EXPECT_EQ(copiedData.size(), 50); // Size should be same as the original preview data
}

// Test for the pData() method in PreviewImage class
TEST_F(PreviewImageTest, PData_1209) {
    // Arrange: Create a PreviewImage instance with mock data
    DataBuf data(200); // 200 bytes
    PreviewProperties properties;
    PreviewImage preview(properties, std::move(data));

    // Act: Get the pointer to the data
    const byte* pData = preview.pData();

    // Assert: Verify that the pointer is not null
    EXPECT_NE(pData, nullptr); // The data pointer should not be null
}

// Test for the mimeType() method in PreviewImage class
TEST_F(PreviewImageTest, MimeType_1209) {
    // Arrange: Create a PreviewImage instance with mock data
    DataBuf data(100); // Some data
    PreviewProperties properties;
    PreviewImage preview(properties, std::move(data));

    // Act: Call the mimeType method
    const std::string& mimeType = preview.mimeType();

    // Assert: Check the mime type (assuming it's "image/jpeg" for this test)
    EXPECT_EQ(mimeType, "image/jpeg"); // Expecting mime type as "image/jpeg"
}

// Test for the extension() method in PreviewImage class
TEST_F(PreviewImageTest, Extension_1209) {
    // Arrange: Create a PreviewImage instance with mock data
    DataBuf data(200); // Some data
    PreviewProperties properties;
    PreviewImage preview(properties, std::move(data));

    // Act: Call the extension method
    const std::string& extension = preview.extension();

    // Assert: Check that the extension is expected (e.g., "jpg")
    EXPECT_EQ(extension, "jpg"); // Assuming the extension is "jpg"
}

// Test for the writeFile() method in PreviewImage class
TEST_F(PreviewImageTest, WriteFile_1209) {
    // Arrange: Create a PreviewImage instance with mock data
    DataBuf data(150); // Some data
    PreviewProperties properties;
    PreviewImage preview(properties, std::move(data));
    std::string path = "/some/path/preview.jpg";

    // Act: Call the writeFile method
    size_t bytesWritten = preview.writeFile(path);

    // Assert: Verify that the writeFile method returns the expected number of bytes written
    EXPECT_GT(bytesWritten, 0); // Assuming it writes some bytes
}

// Test for the exceptional case where size() is called on an empty PreviewImage
TEST_F(PreviewImageTest, Size_EmptyPreview_1209) {
    // Arrange: Create an empty PreviewImage instance
    PreviewProperties properties;
    PreviewImage preview(properties, DataBuf());

    // Act: Call the size method
    uint32_t size = preview.size();

    // Assert: Verify that the size is 0 for an empty preview
    EXPECT_EQ(size, 0); // Size should be 0 for empty data
}

// Test for the exceptional case where mimeType() is called on a PreviewImage with no mime type set
TEST_F(PreviewImageTest, MimeType_NoMimeType_1209) {
    // Arrange: Create a PreviewImage instance with mock data but no mime type set
    DataBuf data(100);
    PreviewProperties properties;
    PreviewImage preview(properties, std::move(data));

    // Act: Call the mimeType method
    const std::string& mimeType = preview.mimeType();

    // Assert: Check for an empty mime type (assuming the default is empty)
    EXPECT_EQ(mimeType, ""); // Expecting an empty string if mimeType is not set
}

}  // namespace Exiv2