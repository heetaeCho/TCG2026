#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "exiv2/basicio.hpp"  // Include the necessary header files

namespace Exiv2 {

// Mock class to simulate BasicIo behavior
class MockBasicIo : public BasicIo {
public:
    MOCK_METHOD(size_t, read, (byte* buf, size_t rcount), (override));
    MOCK_METHOD(int, error, (), (const, override));
    MOCK_METHOD(bool, eof, (), (const, override));
    MOCK_METHOD(void, seek, (int64_t offset, Position pos), (override));
};

}  // namespace Exiv2

// Test Fixture class for setting up tests
class MatroskaVideoTest_106 : public ::testing::Test {
protected:
    Exiv2::MockBasicIo mockIo;
    const bool advance = true;
    const bool noAdvance = false;
};

// Test: Verifies that the function returns true when the MKV signature matches.
TEST_F(MatroskaVideoTest_106, ValidMkvSignature_106) {
    byte buf[4] = { 0x1a, 0x45, 0xdf, 0xa3 };
    EXPECT_CALL(mockIo, read(testing::_, 4)).WillOnce(testing::SetArrayArgument<0>(buf, buf + 4));
    EXPECT_CALL(mockIo, error()).WillOnce(testing::Return(0));
    EXPECT_CALL(mockIo, eof()).WillOnce(testing::Return(false));
    EXPECT_CALL(mockIo, seek(testing::_, Exiv2::BasicIo::beg)).Times(1);

    bool result = Exiv2::isMkvType(mockIo, advance);
    EXPECT_TRUE(result);
}

// Test: Verifies that the function returns false if the MKV signature does not match.
TEST_F(MatroskaVideoTest_106, InvalidMkvSignature_106) {
    byte buf[4] = { 0x00, 0x00, 0x00, 0x00 };  // Invalid signature
    EXPECT_CALL(mockIo, read(testing::_, 4)).WillOnce(testing::SetArrayArgument<0>(buf, buf + 4));
    EXPECT_CALL(mockIo, error()).WillOnce(testing::Return(0));
    EXPECT_CALL(mockIo, eof()).WillOnce(testing::Return(false));
    EXPECT_CALL(mockIo, seek(testing::_, Exiv2::BasicIo::beg)).Times(1);

    bool result = Exiv2::isMkvType(mockIo, advance);
    EXPECT_FALSE(result);
}

// Test: Verifies that the function returns false when an error occurs during reading.
TEST_F(MatroskaVideoTest_106, ReadError_106) {
    byte buf[4];
    EXPECT_CALL(mockIo, read(testing::_, 4)).WillOnce(testing::Return(0));  // Simulate error in read
    EXPECT_CALL(mockIo, error()).WillOnce(testing::Return(1));  // Error condition
    EXPECT_CALL(mockIo, eof()).WillOnce(testing::Return(false));
    EXPECT_CALL(mockIo, seek(testing::_, Exiv2::BasicIo::beg)).Times(1);

    bool result = Exiv2::isMkvType(mockIo, advance);
    EXPECT_FALSE(result);
}

// Test: Verifies that the function returns false when EOF is encountered.
TEST_F(MatroskaVideoTest_106, EofEncountered_106) {
    byte buf[4];
    EXPECT_CALL(mockIo, read(testing::_, 4)).WillOnce(testing::SetArrayArgument<0>(buf, buf + 4));
    EXPECT_CALL(mockIo, error()).WillOnce(testing::Return(0));
    EXPECT_CALL(mockIo, eof()).WillOnce(testing::Return(true));  // Simulate EOF
    EXPECT_CALL(mockIo, seek(testing::_, Exiv2::BasicIo::beg)).Times(1);

    bool result = Exiv2::isMkvType(mockIo, advance);
    EXPECT_FALSE(result);
}

// Test: Verifies that the function works without advancing the file pointer.
TEST_F(MatroskaVideoTest_106, NoAdvance_106) {
    byte buf[4] = { 0x1a, 0x45, 0xdf, 0xa3 };
    EXPECT_CALL(mockIo, read(testing::_, 4)).WillOnce(testing::SetArrayArgument<0>(buf, buf + 4));
    EXPECT_CALL(mockIo, error()).WillOnce(testing::Return(0));
    EXPECT_CALL(mockIo, eof()).WillOnce(testing::Return(false));
    EXPECT_CALL(mockIo, seek(testing::_, Exiv2::BasicIo::beg)).Times(0);  // No seek call

    bool result = Exiv2::isMkvType(mockIo, noAdvance);
    EXPECT_TRUE(result);
}

// Test: Verifies that the function handles an invalid seek operation properly.
TEST_F(MatroskaVideoTest_106, InvalidSeek_106) {
    byte buf[4] = { 0x1a, 0x45, 0xdf, 0xa3 };
    EXPECT_CALL(mockIo, read(testing::_, 4)).WillOnce(testing::SetArrayArgument<0>(buf, buf + 4));
    EXPECT_CALL(mockIo, error()).WillOnce(testing::Return(0));
    EXPECT_CALL(mockIo, eof()).WillOnce(testing::Return(false));
    EXPECT_CALL(mockIo, seek(testing::_, Exiv2::BasicIo::beg)).WillOnce(testing::Return(-1));  // Invalid seek

    bool result = Exiv2::isMkvType(mockIo, advance);
    EXPECT_FALSE(result);
}