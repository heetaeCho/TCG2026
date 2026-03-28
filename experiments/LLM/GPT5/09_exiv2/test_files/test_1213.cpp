#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "preview.hpp" // Include the header for the PreviewImage class

namespace Exiv2 {

class PreviewImageTest_1213 : public ::testing::Test {
protected:
    PreviewProperties properties_;
    DataBuf data_;
    
    // Setup a valid PreviewImage for normal operation tests
    void SetUp() override {
        properties_.height_ = 200;
        properties_.width_ = 300;
        properties_.extension_ = "jpg";
        previewImage_ = PreviewImage(properties_, std::move(data_));
    }

    PreviewImage previewImage_;
};

// Normal operation test for height function
TEST_F(PreviewImageTest_1213, Height_1213) {
    EXPECT_EQ(previewImage_.height(), 200);
}

// Normal operation test for width function
TEST_F(PreviewImageTest_1213, Width_1213) {
    EXPECT_EQ(previewImage_.width(), 300);
}

// Normal operation test for extension function
TEST_F(PreviewImageTest_1213, Extension_1213) {
    EXPECT_EQ(previewImage_.extension(), "jpg");
}

// Boundary condition test: check for zero height (edge case)
TEST_F(PreviewImageTest_1213, Height_Zero_1213) {
    properties_.height_ = 0;
    previewImage_ = PreviewImage(properties_, std::move(data_));
    EXPECT_EQ(previewImage_.height(), 0);
}

// Boundary condition test: check for zero width (edge case)
TEST_F(PreviewImageTest_1213, Width_Zero_1213) {
    properties_.width_ = 0;
    previewImage_ = PreviewImage(properties_, std::move(data_));
    EXPECT_EQ(previewImage_.width(), 0);
}

// Exceptional case test: check if invalid or null data is handled
TEST_F(PreviewImageTest_1213, InvalidData_1213) {
    DataBuf invalidData;
    properties_.height_ = 200;
    properties_.width_ = 300;
    previewImage_ = PreviewImage(properties_, std::move(invalidData));
    EXPECT_EQ(previewImage_.size(), 0);
}

// Verify external interaction with the PreviewManager (if applicable)
TEST_F(PreviewImageTest_1213, VerifyPreviewManagerInteraction_1213) {
    // Mock the PreviewManager interactions here if necessary
    // Example mock behavior for PreviewManager handling of PreviewImage
    // using Google Mock would be done if the PreviewManager interacted with PreviewImage
}

// Test for the copy function to ensure it returns correct DataBuf
TEST_F(PreviewImageTest_1213, Copy_1213) {
    DataBuf copiedData = previewImage_.copy();
    EXPECT_NE(copiedData.size(), 0);
}

// Test for the writeFile function
TEST_F(PreviewImageTest_1213, WriteFile_1213) {
    std::string filePath = "/path/to/save";
    size_t result = previewImage_.writeFile(filePath);
    EXPECT_GT(result, 0); // Assuming writeFile returns the number of bytes written
}

} // namespace Exiv2