#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "riffvideo.cpp"
#include "basicio.hpp"

// Mock the BasicIo class
class MockBasicIo : public Exiv2::BasicIo {
public:
    MOCK_METHOD(void, read, (byte* buf, size_t rcount), (override));
    MOCK_METHOD(int, error, (), (const, override));
    MOCK_METHOD(bool, eof, (), (const, override));
    MOCK_METHOD(void, seek, (int64_t offset, Exiv2::BasicIo::Position pos), (override));
};

// Test Fixture
class RiffVideoTest : public testing::Test {
protected:
    MockBasicIo mockIo;

    // Helper function to set up the mock behavior
    void setupMockRead(const std::array<byte, 4>& buf, bool eof = false, bool error = false) {
        // Mock the read method to return the provided buffer
        EXPECT_CALL(mockIo, read(testing::_, 4))
            .WillOnce(testing::DoAll(testing::SetArrayArgument<0>(buf.begin(), buf.end()), testing::Return(4)));
        EXPECT_CALL(mockIo, eof()).WillRepeatedly(testing::Return(eof));
        EXPECT_CALL(mockIo, error()).WillRepeatedly(testing::Return(error));
    }
};

// Test case for normal operation: Buffer matches "RIFF"
TEST_F(RiffVideoTest, isRiffType_MatchesRiff_True_83) {
    std::array<byte, 4> riffBuf = {'R', 'I', 'F', 'F'};
    setupMockRead(riffBuf);

    bool result = Exiv2::isRiffType(mockIo, true);

    EXPECT_TRUE(result);
}

// Test case for normal operation: Buffer does not match "RIFF"
TEST_F(RiffVideoTest, isRiffType_NoMatch_False_84) {
    std::array<byte, 4> nonRiffBuf = {'X', 'Y', 'Z', 'W'};
    setupMockRead(nonRiffBuf);

    bool result = Exiv2::isRiffType(mockIo, true);

    EXPECT_FALSE(result);
}

// Test case for when `advance` is false but buffer matches "RIFF"
TEST_F(RiffVideoTest, isRiffType_MatchesRiff_NoAdvance_85) {
    std::array<byte, 4> riffBuf = {'R', 'I', 'F', 'F'};
    setupMockRead(riffBuf);

    bool result = Exiv2::isRiffType(mockIo, false);

    EXPECT_TRUE(result);
}

// Test case for EOF behavior
TEST_F(RiffVideoTest, isRiffType_EOF_ReturnsFalse_86) {
    std::array<byte, 4> riffBuf = {'R', 'I', 'F', 'F'};
    setupMockRead(riffBuf, true);  // Simulate EOF

    bool result = Exiv2::isRiffType(mockIo, true);

    EXPECT_FALSE(result);
}

// Test case for error in reading buffer
TEST_F(RiffVideoTest, isRiffType_ReadError_ReturnsFalse_87) {
    std::array<byte, 4> riffBuf = {'R', 'I', 'F', 'F'};
    setupMockRead(riffBuf, false, true);  // Simulate error

    bool result = Exiv2::isRiffType(mockIo, true);

    EXPECT_FALSE(result);
}

// Test case for seeking behavior when `advance` is false
TEST_F(RiffVideoTest, isRiffType_SeekPosition_NotAdvanced_88) {
    std::array<byte, 4> riffBuf = {'R', 'I', 'F', 'F'};
    setupMockRead(riffBuf);

    // Verify the seek method is called to move the pointer back by 4 bytes
    EXPECT_CALL(mockIo, seek(-4, Exiv2::BasicIo::cur)).Times(1);

    bool result = Exiv2::isRiffType(mockIo, false);

    EXPECT_TRUE(result);
}