#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "exiv2/image.hpp"
#include "exiv2/basicio.hpp"

namespace Exiv2 {

// Mocking BasicIo for testing Image's behavior with dependency injection.
class MockBasicIo : public BasicIo {
public:
    MOCK_METHOD(int, open, (), (override));
    MOCK_METHOD(int, close, (), (override));
    MOCK_METHOD(size_t, write, (const byte* data, size_t wcount), (override));
    MOCK_METHOD(size_t, read, (byte* buf, size_t rcount), (override));
    MOCK_METHOD(int, getb, (), (override));
    MOCK_METHOD(void, transfer, (BasicIo & src), (override));
    MOCK_METHOD(int, seek, (int64_t offset, Position pos), (override));
    MOCK_METHOD(bool, isopen, (), (const, override));
    MOCK_METHOD(int, error, (), (const, override));
    MOCK_METHOD(bool, eof, (), (const, override));
    MOCK_METHOD(const std::string&, path, (), (const, override));
    MOCK_METHOD(void, populateFakeData, (), (override));
};

// Test Fixture for Image class
class ImageTest : public ::testing::Test {
protected:
    std::unique_ptr<MockBasicIo> mockIo;
    ImageTest() : mockIo(std::make_unique<MockBasicIo>()) {}

    // Helper function to create an Image instance for tests
    std::unique_ptr<Image> createImage() {
        return std::make_unique<Image>(ImageType::TIFF, 0, std::move(mockIo));
    }
};

// Test: Verify that good() returns false when io_->open() fails
TEST_F(ImageTest, GoodReturnsFalseWhenOpenFails_1096) {
    // Mock the behavior of open to return an error
    EXPECT_CALL(*mockIo, open()).WillOnce(testing::Return(-1));

    auto image = createImage();
    EXPECT_FALSE(image->good());
}

// Test: Verify that good() returns true when io_->open() succeeds and checkType returns true
TEST_F(ImageTest, GoodReturnsTrueWhenOpenSucceeds_1097) {
    // Mock the behavior of open to succeed
    EXPECT_CALL(*mockIo, open()).WillOnce(testing::Return(0));

    // Mock ImageFactory::checkType to return true
    EXPECT_CALL(*mockIo, open()).WillOnce(testing::Return(0));
    EXPECT_TRUE(ImageFactory::checkType(ImageType::TIFF, *mockIo, false));

    auto image = createImage();
    EXPECT_TRUE(image->good());
}

// Test: Verify that good() returns false when checkType fails
TEST_F(ImageTest, GoodReturnsFalseWhenCheckTypeFails_1098) {
    // Mock the behavior of open to succeed
    EXPECT_CALL(*mockIo, open()).WillOnce(testing::Return(0));

    // Mock ImageFactory::checkType to return false
    EXPECT_CALL(*mockIo, open()).WillOnce(testing::Return(0));
    EXPECT_FALSE(ImageFactory::checkType(ImageType::TIFF, *mockIo, false));

    auto image = createImage();
    EXPECT_FALSE(image->good());
}

// Test: Verify that good() returns false when io_->open() fails (edge case)
TEST_F(ImageTest, GoodReturnsFalseOnEdgeCase_1099) {
    // Mock open to always fail
    EXPECT_CALL(*mockIo, open()).WillOnce(testing::Return(-1));

    auto image = createImage();
    EXPECT_FALSE(image->good());
}

}  // namespace Exiv2