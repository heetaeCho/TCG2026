#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <string>
#include "exiv2/preview.hpp"  // Assuming the header path

namespace Exiv2 {
    // Mocking external collaborator if necessary (e.g., PreviewManager)
    class MockPreviewManager : public PreviewManager {
    public:
        MOCK_METHOD(void, someMethod, (PreviewImage&), ());
    };
}

class PreviewImageTest_1211 : public ::testing::Test {
protected:
    Exiv2::PreviewProperties properties_;
    Exiv2::DataBuf data_;
    Exiv2::PreviewImage previewImage_;

    PreviewImageTest_1211()
        : properties_(), data_(), previewImage_(properties_, std::move(data_)) {}

    void SetUp() override {
        // Setting up any necessary mock behavior or default values
    }

    void TearDown() override {
        // Clean up after each test
    }
};

// Test for normal operation of extension() method.
TEST_F(PreviewImageTest_1211, ExtensionReturnsCorrectValue_1211) {
    std::string expected_extension = "jpg";
    properties_.extension_ = expected_extension;
    
    EXPECT_EQ(previewImage_.extension(), expected_extension);
}

// Test for normal operation of mimeType() method.
TEST_F(PreviewImageTest_1211, MimeTypeReturnsCorrectValue_1212) {
    std::string expected_mime_type = "image/jpeg";
    EXPECT_EQ(previewImage_.mimeType(), expected_mime_type);
}

// Test for verifying the copy() method to check if it behaves as expected.
TEST_F(PreviewImageTest_1211, CopyReturnsCorrectData_1213) {
    Exiv2::DataBuf copy_data = previewImage_.copy();
    
    // Perform necessary checks to ensure the copy is correct.
    EXPECT_EQ(copy_data.size(), previewImage_.size());
    EXPECT_EQ(memcmp(copy_data.pData(), previewImage_.pData(), previewImage_.size()), 0);
}

// Test for boundary conditions like empty data in PreviewImage.
TEST_F(PreviewImageTest_1211, EmptyPreviewImage_1214) {
    Exiv2::PreviewProperties empty_properties;
    Exiv2::DataBuf empty_data;

    Exiv2::PreviewImage empty_preview(empty_properties, std::move(empty_data));

    EXPECT_EQ(empty_preview.extension(), "");
    EXPECT_EQ(empty_preview.size(), 0u);
    EXPECT_EQ(empty_preview.width(), 0u);
    EXPECT_EQ(empty_preview.height(), 0u);
}

// Test for the exceptional case where the extension is empty or invalid.
TEST_F(PreviewImageTest_1211, InvalidExtensionThrowsException_1215) {
    properties_.extension_ = "";

    try {
        previewImage_.extension();
        FAIL() << "Expected std::runtime_error due to invalid extension.";
    } catch (const std::runtime_error& err) {
        EXPECT_EQ(std::string(err.what()), "Invalid extension.");
    }
}

// Test for boundary conditions related to the size of the image.
TEST_F(PreviewImageTest_1211, PreviewImageZeroSize_1216) {
    properties_.extension_ = "jpg";
    Exiv2::DataBuf zero_data;

    Exiv2::PreviewImage zero_size_preview(properties_, std::move(zero_data));

    EXPECT_EQ(zero_size_preview.size(), 0u);
}

// Test for the id() method behavior.
TEST_F(PreviewImageTest_1211, IDReturnsCorrectValue_1217) {
    PreviewId expected_id = PreviewId(12345);  // Assuming PreviewId can be directly assigned or constructed
    EXPECT_EQ(previewImage_.id(), expected_id);
}