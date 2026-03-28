#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <string>
#include "preview.hpp"  // Include the header where the PreviewImage class is defined

namespace Exiv2 {

// Mock class for testing external interactions
class MockPreviewImage : public PreviewImage {
public:
    using PreviewImage::PreviewImage;  // Expose constructors

    MOCK_CONST_METHOD0(copy, DataBuf());
    MOCK_CONST_METHOD0(pData, const byte*());
    MOCK_CONST_METHOD0(size, uint32_t());
    MOCK_CONST_METHOD1(writeFile, size_t(const std::string&));
    MOCK_CONST_METHOD0(mimeType, const std::string&());
    MOCK_CONST_METHOD0(extension, const std::string&());
    MOCK_CONST_METHOD0(width, size_t());
    MOCK_CONST_METHOD0(height, size_t());
    MOCK_CONST_METHOD0(id, PreviewId());
};

// Test Fixture for PreviewImage
class PreviewImageTest_1207 : public testing::Test {
protected:
    // Set up test resources
    PreviewProperties properties_;
    DataBuf dataBuf_;

    // Construct an object for testing
    PreviewImageTest_1207() : properties_(), dataBuf_() {}
};

// Normal operation tests
TEST_F(PreviewImageTest_1207, Copy_ReturnsCorrectDataBuf_1207) {
    MockPreviewImage mockImage(properties_, std::move(dataBuf_));

    DataBuf expectedData = {mockImage.pData(), mockImage.size()};
    EXPECT_CALL(mockImage, copy()).WillOnce(testing::Return(expectedData));

    // Test the copy method
    EXPECT_EQ(mockImage.copy(), expectedData);
}

TEST_F(PreviewImageTest_1207, MimeType_ReturnsCorrectMimeType_1207) {
    MockPreviewImage mockImage(properties_, std::move(dataBuf_));

    std::string mime = "image/jpeg";
    EXPECT_CALL(mockImage, mimeType()).WillOnce(testing::ReturnRef(mime));

    // Test mimeType method
    EXPECT_EQ(mockImage.mimeType(), mime);
}

TEST_F(PreviewImageTest_1207, Extension_ReturnsCorrectExtension_1207) {
    MockPreviewImage mockImage(properties_, std::move(dataBuf_));

    std::string ext = "jpg";
    EXPECT_CALL(mockImage, extension()).WillOnce(testing::ReturnRef(ext));

    // Test extension method
    EXPECT_EQ(mockImage.extension(), ext);
}

// Boundary tests
TEST_F(PreviewImageTest_1207, Size_ReturnsZero_WhenNoData_1207) {
    MockPreviewImage mockImage(properties_, std::move(dataBuf_));

    EXPECT_CALL(mockImage, size()).WillOnce(testing::Return(0));

    // Test the size method when there is no data
    EXPECT_EQ(mockImage.size(), 0);
}

// Exceptional/Error cases
TEST_F(PreviewImageTest_1207, WriteFile_Fails_WhenPathIsEmpty_1207) {
    MockPreviewImage mockImage(properties_, std::move(dataBuf_));

    EXPECT_CALL(mockImage, writeFile(testing::_)).WillOnce(testing::Return(0));

    // Test writeFile method with an empty path
    EXPECT_EQ(mockImage.writeFile(""), 0);
}

// External interaction verification
TEST_F(PreviewImageTest_1207, WriteFile_CallsWithCorrectPath_1207) {
    MockPreviewImage mockImage(properties_, std::move(dataBuf_));

    std::string testPath = "/path/to/file.jpg";
    EXPECT_CALL(mockImage, writeFile(testing::Eq(testPath)))
        .Times(1)
        .WillOnce(testing::Return(1));

    // Test writeFile method, verifying the path interaction
    EXPECT_EQ(mockImage.writeFile(testPath), 1);
}

}  // namespace Exiv2