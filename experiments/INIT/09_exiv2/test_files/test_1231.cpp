#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "exiv2/tgaimage.hpp"
#include "exiv2/error.hpp"
#include "exiv2/basicio.hpp"

using namespace Exiv2;

class MockBasicIo : public BasicIo {
public:
    MOCK_METHOD(int, open, (), (override));
    MOCK_METHOD(size_t, read, (byte* buf, size_t rcount), (override));
    MOCK_METHOD(int, error, (), (const, override));
    MOCK_METHOD(bool, eof, (), (const, override));
    MOCK_METHOD(const std::string&, path, (), (const, override));
};

// Test fixture class for TgaImage
class TgaImageTest : public ::testing::Test {
protected:
    void SetUp() override {
        io_ = std::make_unique<MockBasicIo>();
        tgaImage_ = std::make_unique<TgaImage>(std::move(io_));
    }

    std::unique_ptr<MockBasicIo> io_;
    std::unique_ptr<TgaImage> tgaImage_;
};

// Normal operation test case for readMetadata
TEST_F(TgaImageTest, ReadMetadata_Success_1231) {
    // Mock behavior: assume the file opens successfully
    EXPECT_CALL(*io_, open()).WillOnce(testing::Return(0));
    EXPECT_CALL(*io_, read(testing::_ , testing::_)).WillOnce(testing::Return(18)); // read 18 bytes (TGA header)
    EXPECT_CALL(*io_, error()).WillOnce(testing::Return(0)); // No error

    // Execute
    EXPECT_NO_THROW(tgaImage_->readMetadata());
}

// Boundary condition: file opens with error
TEST_F(TgaImageTest, ReadMetadata_FileOpenFailed_1232) {
    // Mock behavior: simulate a file open failure
    EXPECT_CALL(*io_, open()).WillOnce(testing::Return(-1));
    
    // Check if the appropriate exception is thrown
    EXPECT_THROW(tgaImage_->readMetadata(), Error);
}

// Boundary condition: EOF while reading TGA header
TEST_F(TgaImageTest, ReadMetadata_EofWhileReadingHeader_1233) {
    // Mock behavior: file opens successfully but EOF occurs while reading
    EXPECT_CALL(*io_, open()).WillOnce(testing::Return(0));
    EXPECT_CALL(*io_, read(testing::_ , testing::_)).WillOnce(testing::Return(0)); // No bytes read
    EXPECT_CALL(*io_, eof()).WillOnce(testing::Return(true));

    // Expect exception due to failure to read header
    EXPECT_THROW(tgaImage_->readMetadata(), Error);
}

// Error handling: Not a TGA image type
TEST_F(TgaImageTest, ReadMetadata_NotATga_1234) {
    // Mock behavior: file opens successfully but it is not a TGA image
    EXPECT_CALL(*io_, open()).WillOnce(testing::Return(0));
    EXPECT_CALL(*io_, read(testing::_ , testing::_)).WillOnce(testing::Return(18)); // read 18 bytes (TGA header)
    EXPECT_CALL(*io_, error()).WillOnce(testing::Return(0)); // No error
    EXPECT_CALL(*io_, eof()).WillOnce(testing::Return(false));

    // Simulate "isTgaType" returning false to trigger the exception
    EXPECT_THROW(tgaImage_->readMetadata(), Error);
}

// Test case for exception when reading data fails
TEST_F(TgaImageTest, ReadMetadata_ReadFailure_1235) {
    // Mock behavior: simulate a read failure (less than expected bytes)
    EXPECT_CALL(*io_, open()).WillOnce(testing::Return(0));
    EXPECT_CALL(*io_, read(testing::_ , testing::_)).WillOnce(testing::Return(10)); // Read only 10 bytes

    // Expect exception due to insufficient data
    EXPECT_THROW(tgaImage_->readMetadata(), Error);
}