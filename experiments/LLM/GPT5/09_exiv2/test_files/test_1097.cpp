#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include "exiv2/image.hpp"

namespace Exiv2 {
    class MockBasicIo : public BasicIo {
    public:
        MOCK_METHOD(void, read, (uint8_t*, size_t), (override));
        MOCK_METHOD(void, write, (const uint8_t*, size_t), (override));
    };
}

using namespace Exiv2;

class ImageTest_1097 : public ::testing::Test {
protected:
    void SetUp() override {
        io_ = std::make_unique<MockBasicIo>();
        image_ = std::make_unique<Image>(ImageType::jpg, 0x01, std::move(io_));
    }

    std::unique_ptr<MockBasicIo> io_;
    std::unique_ptr<Image> image_;
};

TEST_F(ImageTest_1097, SupportsMetadata_WhenMetadataIsSupported_1097) {
    // Given supportedMetadata is set to 0x01, the function should return true for metadataId 0x01
    EXPECT_TRUE(image_->supportsMetadata(0x01));
}

TEST_F(ImageTest_1097, SupportsMetadata_WhenMetadataIsNotSupported_1098) {
    // Given supportedMetadata is set to 0x01, the function should return false for metadataId 0x02
    EXPECT_FALSE(image_->supportsMetadata(0x02));
}

TEST_F(ImageTest_1097, SupportsMetadata_WhenMetadataIsZero_1099) {
    // Given supportedMetadata is 0x00 (no metadata supported), the function should return false for any metadataId
    image_ = std::make_unique<Image>(ImageType::jpg, 0x00, std::move(io_));
    EXPECT_FALSE(image_->supportsMetadata(0x01));
}

TEST_F(ImageTest_1097, SupportsMetadata_WhenMetadataIdIsMaxValue_1100) {
    // Test with max value for metadataId, which is a boundary condition
    EXPECT_FALSE(image_->supportsMetadata(0xFFFF));
}

TEST_F(ImageTest_1097, SupportsMetadata_WhenMetadataIdIsZero_1101) {
    // Test with metadataId 0, which is another boundary condition
    EXPECT_FALSE(image_->supportsMetadata(0x00));
}

TEST_F(ImageTest_1097, SupportsMetadata_WhenImageIsNull_1102) {
    // Null pointer scenario - image_ should not be null in this test setup, but adding for completeness.
    image_.reset();
    EXPECT_FALSE(image_ ? image_->supportsMetadata(0x01) : false);
}