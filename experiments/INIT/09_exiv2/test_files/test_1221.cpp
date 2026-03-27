#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "jpgimage.hpp"
#include "basicio.hpp"

namespace Exiv2 {

class MockBasicIo : public BasicIo {
public:
    MOCK_METHOD(size_t, write, (const byte* data, size_t wcount), (override));
    MOCK_METHOD(int, error, (), (const override));
};

class JpegImageTest : public ::testing::Test {
protected:
    std::unique_ptr<MockBasicIo> mockIo;
    JpegImageTest() : mockIo(std::make_unique<MockBasicIo>()) {}
};

// Test case for normal operation (successful writeHeader)
TEST_F(JpegImageTest, WriteHeader_Success_1221) {
    JpegImage jpegImage(std::move(mockIo), true);
    
    byte tmpBuf[2] = {0xff, -40};  // Expected SOI marker byte sequence
    EXPECT_CALL(*mockIo, write(tmpBuf, 2)).WillOnce(testing::Return(2));
    EXPECT_CALL(*mockIo, error()).WillOnce(testing::Return(0));  // No error
    
    EXPECT_EQ(jpegImage.writeHeader(*mockIo), 0);  // Expect success (0)
}

// Test case for error when write fails
TEST_F(JpegImageTest, WriteHeader_WriteFails_1222) {
    JpegImage jpegImage(std::move(mockIo), true);
    
    byte tmpBuf[2] = {0xff, -40};  // Expected SOI marker byte sequence
    EXPECT_CALL(*mockIo, write(tmpBuf, 2)).WillOnce(testing::Return(0));  // Write fails
    EXPECT_CALL(*mockIo, error()).WillOnce(testing::Return(0));  // No error
    
    EXPECT_EQ(jpegImage.writeHeader(*mockIo), 4);  // Expect failure (error code 4)
}

// Test case for error when there is an error during write operation
TEST_F(JpegImageTest, WriteHeader_ErrorDuringWrite_1223) {
    JpegImage jpegImage(std::move(mockIo), true);
    
    byte tmpBuf[2] = {0xff, -40};  // Expected SOI marker byte sequence
    EXPECT_CALL(*mockIo, write(tmpBuf, 2)).WillOnce(testing::Return(2));
    EXPECT_CALL(*mockIo, error()).WillOnce(testing::Return(1));  // Error during write
    
    EXPECT_EQ(jpegImage.writeHeader(*mockIo), 4);  // Expect failure (error code 4)
}

// Test case for boundary condition with no data written
TEST_F(JpegImageTest, WriteHeader_NoDataWritten_1224) {
    JpegImage jpegImage(std::move(mockIo), true);
    
    byte tmpBuf[2] = {0xff, -40};  // Expected SOI marker byte sequence
    EXPECT_CALL(*mockIo, write(tmpBuf, 2)).WillOnce(testing::Return(0));  // No data written
    
    EXPECT_EQ(jpegImage.writeHeader(*mockIo), 4);  // Expect failure (error code 4)
}

}  // namespace Exiv2