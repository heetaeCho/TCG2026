#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <string>
#include "preview.hpp"

namespace Exiv2 {

class PreviewImageTest : public ::testing::Test {
protected:
    PreviewProperties properties_;
    DataBuf data_;

    PreviewImageTest() {
        properties_.mimeType_ = "image/jpeg";
        properties_.extension_ = "jpg";
        properties_.id_ = PreviewId{};
        data_ = DataBuf{/* sample data */};
    }

    PreviewImage createPreviewImage() {
        return PreviewImage(properties_, std::move(data_));
    }
};

// Test case for normal operation: Checking if the mimeType() method returns the correct MIME type.
TEST_F(PreviewImageTest, MimeTypeReturnsCorrectValue_1210) {
    PreviewImage previewImage = createPreviewImage();
    EXPECT_EQ(previewImage.mimeType(), "image/jpeg");
}

// Test case for boundary condition: Checking if an empty mimeType is handled correctly.
TEST_F(PreviewImageTest, MimeTypeEmptyReturnsCorrectValue_1211) {
    properties_.mimeType_ = "";  // Set to empty value
    PreviewImage previewImage = createPreviewImage();
    EXPECT_EQ(previewImage.mimeType(), "");
}

// Test case for exceptional case: Simulating invalid data (handled internally in the constructor).
TEST_F(PreviewImageTest, MimeTypeWithNullData_1212) {
    properties_.mimeType_ = "image/png";
    data_ = DataBuf();  // Empty data
    PreviewImage previewImage = createPreviewImage();
    EXPECT_EQ(previewImage.mimeType(), "image/png");  // Check if mimeType() still works with null data
}

// Test case for verifying external interactions: Verifying if copy() method is invoked.
TEST_F(PreviewImageTest, VerifyCopyInteraction_1213) {
    PreviewImage previewImage = createPreviewImage();
    EXPECT_CALL(previewImage, copy()).Times(1);  // Verify copy is called once
    previewImage.copy();  // Trigger copy
}

// Test case for boundary condition: Testing for invalid file path input in writeFile.
TEST_F(PreviewImageTest, WriteFileInvalidPath_1214) {
    PreviewImage previewImage = createPreviewImage();
    EXPECT_EQ(previewImage.writeFile("invalid_path"), 0);  // Assuming writeFile returns 0 on failure
}

// Test case for normal operation: Verifying mimeType extension consistency.
TEST_F(PreviewImageTest, MimeTypeAndExtensionMatch_1215) {
    PreviewImage previewImage = createPreviewImage();
    EXPECT_EQ(previewImage.mimeType(), "image/jpeg");
    EXPECT_EQ(previewImage.extension(), "jpg");
}

// Test case for boundary condition: Testing with a long mimeType string.
TEST_F(PreviewImageTest, LongMimeTypeReturnsCorrectValue_1216) {
    properties_.mimeType_ = std::string(1000, 'a');  // Long mime type string
    PreviewImage previewImage = createPreviewImage();
    EXPECT_EQ(previewImage.mimeType(), std::string(1000, 'a'));
}

}  // namespace Exiv2