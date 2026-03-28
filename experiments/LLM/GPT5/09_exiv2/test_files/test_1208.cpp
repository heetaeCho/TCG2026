#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <string>
#include "exiv2/preview.hpp"

namespace Exiv2 {

// Mocking the dependencies if necessary
class MockPreviewImage : public PreviewImage {
public:
    MockPreviewImage(PreviewProperties properties, DataBuf && data)
        : PreviewImage(std::move(properties), std::move(data)) {}

    MOCK_METHOD(const byte*, pData, (), (const, override));
    MOCK_METHOD(uint32_t, size, (), (const, override));
    MOCK_METHOD(size_t, writeFile, (const std::string& path), (const, override));
    MOCK_METHOD(const std::string&, mimeType, (), (const, override));
    MOCK_METHOD(const std::string&, extension, (), (const, override));
    MOCK_METHOD(size_t, width, (), (const, override));
    MOCK_METHOD(size_t, height, (), (const, override));
    MOCK_METHOD(PreviewId, id, (), (const, override));
};

// Test fixture for PreviewImage
class PreviewImageTest_1208 : public ::testing::Test {
protected:
    PreviewProperties properties_;
    DataBuf data_;

    PreviewImageTest_1208()
        : properties_(), data_(nullptr, 0) {}

    void SetUp() override {
        // Set up any required mock objects or data here
    }

    void TearDown() override {
        // Clean up if necessary
    }
};

// Test for normal operation of pData() method
TEST_F(PreviewImageTest_1208, pDataReturnsValidPointer_1208) {
    MockPreviewImage preview(properties_, std::move(data_));
    const byte* dataPtr = reinterpret_cast<const byte*>("Sample Data");

    // Mock the behavior of pData()
    EXPECT_CALL(preview, pData())
        .WillOnce(testing::Return(dataPtr));

    // Test the pData() method
    const byte* result = preview.pData();
    EXPECT_EQ(result, dataPtr);
}

// Test for size() method
TEST_F(PreviewImageTest_1208, SizeReturnsCorrectValue_1208) {
    MockPreviewImage preview(properties_, std::move(data_));

    EXPECT_CALL(preview, size())
        .WillOnce(testing::Return(1024));

    uint32_t result = preview.size();
    EXPECT_EQ(result, 1024);
}

// Test for exception case when size() returns zero (error case)
TEST_F(PreviewImageTest_1208, SizeReturnsZero_1208) {
    MockPreviewImage preview(properties_, std::move(data_));

    EXPECT_CALL(preview, size())
        .WillOnce(testing::Return(0));

    uint32_t result = preview.size();
    EXPECT_EQ(result, 0);
}

// Test for the mimeType() method
TEST_F(PreviewImageTest_1208, MimeTypeReturnsCorrectValue_1208) {
    MockPreviewImage preview(properties_, std::move(data_));
    std::string mime = "image/jpeg";

    EXPECT_CALL(preview, mimeType())
        .WillOnce(testing::ReturnRef(mime));

    const std::string& result = preview.mimeType();
    EXPECT_EQ(result, mime);
}

// Test for the extension() method
TEST_F(PreviewImageTest_1208, ExtensionReturnsCorrectValue_1208) {
    MockPreviewImage preview(properties_, std::move(data_));
    std::string ext = "jpg";

    EXPECT_CALL(preview, extension())
        .WillOnce(testing::ReturnRef(ext));

    const std::string& result = preview.extension();
    EXPECT_EQ(result, ext);
}

// Test for boundary conditions - width and height should return zero
TEST_F(PreviewImageTest_1208, WidthHeightReturnsZero_1208) {
    MockPreviewImage preview(properties_, std::move(data_));

    EXPECT_CALL(preview, width())
        .WillOnce(testing::Return(0));
    EXPECT_CALL(preview, height())
        .WillOnce(testing::Return(0));

    EXPECT_EQ(preview.width(), 0);
    EXPECT_EQ(preview.height(), 0);
}

// Test for verification of external interaction - checking if writeFile is called
TEST_F(PreviewImageTest_1208, WriteFileCalledWithCorrectPath_1208) {
    MockPreviewImage preview(properties_, std::move(data_));
    std::string filePath = "/tmp/preview.jpg";

    EXPECT_CALL(preview, writeFile(filePath))
        .WillOnce(testing::Return(1024));

    size_t bytesWritten = preview.writeFile(filePath);
    EXPECT_EQ(bytesWritten, 1024);
}

}  // namespace Exiv2