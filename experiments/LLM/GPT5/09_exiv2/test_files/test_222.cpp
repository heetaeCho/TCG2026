#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "exiv2/rafimage.hpp"
#include "exiv2/error.hpp"

namespace Exiv2 {

// Mock the BasicIo class
class MockBasicIo : public BasicIo {
public:
    MOCK_METHOD(void, open, (const std::string& path), (override));
    MOCK_METHOD(void, close, (), (override));
    MOCK_METHOD(void, read, (void* buffer, size_t size), (override));
    MOCK_METHOD(void, write, (const void* buffer, size_t size), (override));
};

// Test Suite for RafImage
class RafImageTest : public ::testing::Test {
protected:
    std::unique_ptr<RafImage> rafImage;
    std::shared_ptr<MockBasicIo> mockIo;

    void SetUp() override {
        mockIo = std::make_shared<MockBasicIo>();
        rafImage = std::make_unique<RafImage>(std::move(mockIo), true);
    }

    void TearDown() override {
        rafImage.reset();
    }
};

// TEST_ID is 222
TEST_F(RafImageTest, WriteMetadataThrowsError_222) {
    // Arrange: Ensure that the writeMetadata function throws the expected error
    EXPECT_THROW({
        rafImage->writeMetadata();
    }, Error);
}

}  // namespace Exiv2