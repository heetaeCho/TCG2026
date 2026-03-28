#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "exiv2/basicio.hpp"
#include "exiv2/tiffimage.hpp"
#include "exiv2/tiffimage_int.hpp"

namespace Exiv2 {

// Mock the BasicIo class to simulate its behavior for testing purposes
class MockBasicIo : public BasicIo {
public:
    MOCK_METHOD(void, read, (byte* buf, size_t rcount), (override));
    MOCK_METHOD(int, error, (), (const override));
    MOCK_METHOD(bool, eof, (), (const override));
    MOCK_METHOD(int, seek, (int64_t offset, Position pos), (override));
};

} // namespace Exiv2

// TEST_ID 1737 - Normal operation: when read successfully
TEST_F(TiffImageTest_1737, isTiffType_ReadSuccess_1737) {
    using namespace Exiv2;

    MockBasicIo mockIo;
    byte buf[8] = {0};

    // Expect the read to succeed and return no error or EOF
    EXPECT_CALL(mockIo, read(buf, 8)).Times(1);
    EXPECT_CALL(mockIo, error()).WillOnce(testing::Return(0));  // No error
    EXPECT_CALL(mockIo, eof()).WillOnce(testing::Return(false)); // No EOF

    TiffHeader tiffHeader(ByteOrder::bigEndian, 0, true);
    EXPECT_CALL(tiffHeader, read(buf, 8)).WillOnce(testing::Return(true));

    // Test the function behavior
    EXPECT_TRUE(isTiffType(mockIo, true));
}

// TEST_ID 1738 - Boundary condition: when the read size is exactly 8 bytes
TEST_F(TiffImageTest_1738, isTiffType_ReadExact8Bytes_1738) {
    using namespace Exiv2;

    MockBasicIo mockIo;
    byte buf[8] = {0};

    // Expect the read to succeed and return no error or EOF
    EXPECT_CALL(mockIo, read(buf, 8)).Times(1);
    EXPECT_CALL(mockIo, error()).WillOnce(testing::Return(0));  // No error
    EXPECT_CALL(mockIo, eof()).WillOnce(testing::Return(false)); // No EOF

    TiffHeader tiffHeader(ByteOrder::bigEndian, 0, true);
    EXPECT_CALL(tiffHeader, read(buf, 8)).WillOnce(testing::Return(true));

    // Test the function behavior for boundary size
    EXPECT_TRUE(isTiffType(mockIo, true));
}

// TEST_ID 1739 - Exceptional case: error during read
TEST_F(TiffImageTest_1739, isTiffType_ReadError_1739) {
    using namespace Exiv2;

    MockBasicIo mockIo;
    byte buf[8] = {0};

    // Simulate a read error
    EXPECT_CALL(mockIo, read(buf, 8)).Times(1);
    EXPECT_CALL(mockIo, error()).WillOnce(testing::Return(1));  // Error occurred
    EXPECT_CALL(mockIo, eof()).WillOnce(testing::Return(false)); // No EOF

    // Test the function behavior when error occurs
    EXPECT_FALSE(isTiffType(mockIo, true));
}

// TEST_ID 1740 - Exceptional case: EOF during read
TEST_F(TiffImageTest_1740, isTiffType_EOF_1740) {
    using namespace Exiv2;

    MockBasicIo mockIo;
    byte buf[8] = {0};

    // Simulate EOF during read
    EXPECT_CALL(mockIo, read(buf, 8)).Times(1);
    EXPECT_CALL(mockIo, error()).WillOnce(testing::Return(0));  // No error
    EXPECT_CALL(mockIo, eof()).WillOnce(testing::Return(true)); // EOF encountered

    // Test the function behavior when EOF occurs
    EXPECT_FALSE(isTiffType(mockIo, true));
}

// TEST_ID 1741 - Boundary condition: when advance is false and read is successful
TEST_F(TiffImageTest_1741, isTiffType_AdvanceFalse_1741) {
    using namespace Exiv2;

    MockBasicIo mockIo;
    byte buf[8] = {0};

    // Expect the read to succeed and return no error or EOF
    EXPECT_CALL(mockIo, read(buf, 8)).Times(1);
    EXPECT_CALL(mockIo, error()).WillOnce(testing::Return(0));  // No error
    EXPECT_CALL(mockIo, eof()).WillOnce(testing::Return(false)); // No EOF

    TiffHeader tiffHeader(ByteOrder::bigEndian, 0, true);
    EXPECT_CALL(tiffHeader, read(buf, 8)).WillOnce(testing::Return(true));

    // Test with advance being false
    EXPECT_TRUE(isTiffType(mockIo, false));
}

// TEST_ID 1742 - Verification of external interaction: seek call after read when advance is false
TEST_F(TiffImageTest_1742, isTiffType_SeekOnAdvanceFalse_1742) {
    using namespace Exiv2;

    MockBasicIo mockIo;
    byte buf[8] = {0};

    // Expect the read to succeed and return no error or EOF
    EXPECT_CALL(mockIo, read(buf, 8)).Times(1);
    EXPECT_CALL(mockIo, error()).WillOnce(testing::Return(0));  // No error
    EXPECT_CALL(mockIo, eof()).WillOnce(testing::Return(false)); // No EOF
    EXPECT_CALL(mockIo, seek(-8, BasicIo::cur)).Times(1);  // Verify seek call

    TiffHeader tiffHeader(ByteOrder::bigEndian, 0, true);
    EXPECT_CALL(tiffHeader, read(buf, 8)).WillOnce(testing::Return(true));

    // Test with advance being false, expect a seek call
    EXPECT_TRUE(isTiffType(mockIo, false));
}