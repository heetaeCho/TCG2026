#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "exiv2/basicio.hpp"
#include "jpgimage.hpp"  // Assuming this header contains the 'isExvType' function

namespace Exiv2 {
namespace {

class MockBasicIo : public BasicIo {
public:
    MOCK_METHOD(size_t, read, (byte * buf, size_t rcount), (override));
    MOCK_METHOD(int, error, (), (const, override));
    MOCK_METHOD(bool, eof, (), (const, override));
    MOCK_METHOD(int, seek, (int64_t offset, Position pos), (override));
};

TEST_F(JpgImageTest_1229, isExvType_ReturnsTrue_WhenValidExvHeader_1229) {
    // Arrange
    MockBasicIo mockIo;
    byte validHeader[7] = { 0xff, 0x01, 'e', 'x', 'i', 'v', '2' };
    EXPECT_CALL(mockIo, read(testing::_, 7))
        .WillOnce(testing::SetArrayArgument<0>(validHeader, validHeader + 7))
        .WillRepeatedly(testing::Return(7));
    EXPECT_CALL(mockIo, error()).WillOnce(testing::Return(0));
    EXPECT_CALL(mockIo, eof()).WillOnce(testing::Return(false));

    // Act
    bool result = isExvType(mockIo, true);

    // Assert
    EXPECT_TRUE(result);
}

TEST_F(JpgImageTest_1230, isExvType_ReturnsFalse_WhenInvalidExvHeader_1230) {
    // Arrange
    MockBasicIo mockIo;
    byte invalidHeader[7] = { 0xff, 0x02, 'e', 'x', 'i', 'v', '2' };  // Invalid header
    EXPECT_CALL(mockIo, read(testing::_, 7))
        .WillOnce(testing::SetArrayArgument<0>(invalidHeader, invalidHeader + 7))
        .WillRepeatedly(testing::Return(7));
    EXPECT_CALL(mockIo, error()).WillOnce(testing::Return(0));
    EXPECT_CALL(mockIo, eof()).WillOnce(testing::Return(false));

    // Act
    bool result = isExvType(mockIo, true);

    // Assert
    EXPECT_FALSE(result);
}

TEST_F(JpgImageTest_1231, isExvType_ReturnsFalse_WhenErrorInRead_1231) {
    // Arrange
    MockBasicIo mockIo;
    EXPECT_CALL(mockIo, read(testing::_, 7))
        .WillOnce(testing::Return(0));  // Simulating read error
    EXPECT_CALL(mockIo, error()).WillOnce(testing::Return(1));  // Error occurred
    EXPECT_CALL(mockIo, eof()).WillOnce(testing::Return(false));

    // Act
    bool result = isExvType(mockIo, true);

    // Assert
    EXPECT_FALSE(result);
}

TEST_F(JpgImageTest_1232, isExvType_ReturnsFalse_WhenEof_1232) {
    // Arrange
    MockBasicIo mockIo;
    byte validHeader[7] = { 0xff, 0x01, 'e', 'x', 'i', 'v', '2' };
    EXPECT_CALL(mockIo, read(testing::_, 7))
        .WillOnce(testing::SetArrayArgument<0>(validHeader, validHeader + 7))
        .WillRepeatedly(testing::Return(7));
    EXPECT_CALL(mockIo, error()).WillOnce(testing::Return(0));
    EXPECT_CALL(mockIo, eof()).WillOnce(testing::Return(true));  // EOF reached

    // Act
    bool result = isExvType(mockIo, true);

    // Assert
    EXPECT_FALSE(result);
}

TEST_F(JpgImageTest_1233, isExvType_CallsSeek_WhenNotAdvancing_1233) {
    // Arrange
    MockBasicIo mockIo;
    byte validHeader[7] = { 0xff, 0x01, 'e', 'x', 'i', 'v', '2' };
    EXPECT_CALL(mockIo, read(testing::_, 7))
        .WillOnce(testing::SetArrayArgument<0>(validHeader, validHeader + 7))
        .WillRepeatedly(testing::Return(7));
    EXPECT_CALL(mockIo, error()).WillOnce(testing::Return(0));
    EXPECT_CALL(mockIo, eof()).WillOnce(testing::Return(false));
    EXPECT_CALL(mockIo, seek(-7, BasicIo::cur)).Times(1);  // Seek is expected to be called

    // Act
    bool result = isExvType(mockIo, false);

    // Assert
    EXPECT_TRUE(result);
}

TEST_F(JpgImageTest_1234, isExvType_DoesNotCallSeek_WhenAdvancing_1234) {
    // Arrange
    MockBasicIo mockIo;
    byte validHeader[7] = { 0xff, 0x01, 'e', 'x', 'i', 'v', '2' };
    EXPECT_CALL(mockIo, read(testing::_, 7))
        .WillOnce(testing::SetArrayArgument<0>(validHeader, validHeader + 7))
        .WillRepeatedly(testing::Return(7));
    EXPECT_CALL(mockIo, error()).WillOnce(testing::Return(0));
    EXPECT_CALL(mockIo, eof()).WillOnce(testing::Return(false));
    EXPECT_CALL(mockIo, seek(testing::_, testing::_)).Times(0);  // Seek should NOT be called

    // Act
    bool result = isExvType(mockIo, true);

    // Assert
    EXPECT_TRUE(result);
}

}  // namespace
}  // namespace Exiv2