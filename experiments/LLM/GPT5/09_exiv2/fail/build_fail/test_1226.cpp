#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "exiv2/jpgimage.hpp"
#include "exiv2/basicio.hpp"

// Mock the BasicIo class to test interactions with it
class MockBasicIo : public Exiv2::BasicIo {
public:
    MOCK_METHOD(size_t, write, (const byte* data, size_t wcount), (override));
    MOCK_METHOD(int, error, (), (const override));
};

// Test fixture for ExvImage class
class ExvImageTest_1226 : public ::testing::Test {
protected:
    void SetUp() override {
        mockIo = std::make_unique<MockBasicIo>();
        exvImage = std::make_unique<Exiv2::ExvImage>(std::move(mockIo), true);
    }

    std::unique_ptr<MockBasicIo> mockIo;
    std::unique_ptr<Exiv2::ExvImage> exvImage;
};

// Test: Normal operation of writeHeader method
TEST_F(ExvImageTest_1226, WriteHeader_Success_1226) {
    // Arrange: Set up mock to simulate successful write
    byte testBuffer[7] = {0xff, 0x01, 0x01, 0x02, 0x03, 0x04, 0x05};
    EXPECT_CALL(*mockIo, write(testBuffer, 7)).WillOnce(testing::Return(7));
    EXPECT_CALL(*mockIo, error()).WillOnce(testing::Return(0));

    // Act: Call writeHeader
    int result = exvImage->writeHeader(*mockIo);

    // Assert: Verify the result is success (0)
    EXPECT_EQ(result, 0);
}

// Test: writeHeader fails due to write failure
TEST_F(ExvImageTest_1226, WriteHeader_WriteFailure_1226) {
    // Arrange: Set up mock to simulate a write failure
    byte testBuffer[7] = {0xff, 0x01, 0x01, 0x02, 0x03, 0x04, 0x05};
    EXPECT_CALL(*mockIo, write(testBuffer, 7)).WillOnce(testing::Return(4));  // Partial write
    EXPECT_CALL(*mockIo, error()).WillOnce(testing::Return(0));

    // Act: Call writeHeader
    int result = exvImage->writeHeader(*mockIo);

    // Assert: Verify the result is failure (4)
    EXPECT_EQ(result, 4);
}

// Test: writeHeader fails due to error in BasicIo
TEST_F(ExvImageTest_1226, WriteHeader_Error_1226) {
    // Arrange: Set up mock to simulate an error condition
    byte testBuffer[7] = {0xff, 0x01, 0x01, 0x02, 0x03, 0x04, 0x05};
    EXPECT_CALL(*mockIo, write(testBuffer, 7)).WillOnce(testing::Return(7));
    EXPECT_CALL(*mockIo, error()).WillOnce(testing::Return(1));  // Simulate an error

    // Act: Call writeHeader
    int result = exvImage->writeHeader(*mockIo);

    // Assert: Verify the result is failure (4) due to error
    EXPECT_EQ(result, 4);
}

// Test: Verify mimeType method
TEST_F(ExvImageTest_1226, MimeType_Valid_1226) {
    // Act: Call mimeType
    std::string mimeType = exvImage->mimeType();

    // Assert: Verify the mimeType is correct (Assuming mimeType returns "image/exv")
    EXPECT_EQ(mimeType, "image/exv");
}