#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <array>
#include <stdexcept>
#include "exiv2/basicio.hpp"

namespace Exiv2 {
    // Mocking BasicIo class to simulate read and seek behavior
    class MockBasicIo : public BasicIo {
    public:
        MOCK_METHOD(size_t, read, (byte* buf, size_t rcount), (override));
        MOCK_METHOD(int, error, (), (const, override));
        MOCK_METHOD(bool, eof, (), (const, override));
        MOCK_METHOD(int64_t, seek, (int64_t offset, Position pos), (override));
    };
}

using namespace testing;

class GifImageTest_214 : public Test {
protected:
    Exiv2::MockBasicIo mockIo;
};

// Normal operation test: Test if GIF type is detected correctly
TEST_F(GifImageTest_214, IsGifType_MatchesGif87a_214) {
    std::array<byte, 6> gif87aId{'G', 'I', 'F', '8', '7', 'a'};
    
    // Mock the read method to return GIF87a ID
    EXPECT_CALL(mockIo, read(_, 6))
        .WillOnce(DoAll(SetArrayArgument<0>(gif87aId.begin(), gif87aId.end()), Return(6)));
    EXPECT_CALL(mockIo, error()).WillOnce(Return(0));
    EXPECT_CALL(mockIo, eof()).WillOnce(Return(false));

    // Verify that isGifType correctly identifies the GIF87a type
    EXPECT_TRUE(Exiv2::isGifType(mockIo, true));
}

// Normal operation test: Test if GIF type is detected correctly for GIF89a
TEST_F(GifImageTest_214, IsGifType_MatchesGif89a_214) {
    std::array<byte, 6> gif89aId{'G', 'I', 'F', '8', '9', 'a'};

    // Mock the read method to return GIF89a ID
    EXPECT_CALL(mockIo, read(_, 6))
        .WillOnce(DoAll(SetArrayArgument<0>(gif89aId.begin(), gif89aId.end()), Return(6)));
    EXPECT_CALL(mockIo, error()).WillOnce(Return(0));
    EXPECT_CALL(mockIo, eof()).WillOnce(Return(false));

    // Verify that isGifType correctly identifies the GIF89a type
    EXPECT_TRUE(Exiv2::isGifType(mockIo, true));
}

// Boundary test: Test when read returns less than expected bytes
TEST_F(GifImageTest_214, IsGifType_ReadLessThanExpected_214) {
    std::array<byte, 6> gif87aId{'G', 'I', 'F', '8', '7', 'a'};

    // Mock the read method to return less than 6 bytes (error case)
    EXPECT_CALL(mockIo, read(_, 6)).WillOnce(Return(3));  // Simulate incomplete read
    EXPECT_CALL(mockIo, error()).WillOnce(Return(0));
    EXPECT_CALL(mockIo, eof()).WillOnce(Return(false));

    // Verify that isGifType returns false due to incomplete read
    EXPECT_FALSE(Exiv2::isGifType(mockIo, true));
}

// Boundary test: Test when read fails due to error
TEST_F(GifImageTest_214, IsGifType_ReadError_214) {
    std::array<byte, 6> gif87aId{'G', 'I', 'F', '8', '7', 'a'};

    // Mock the read method to simulate an error during reading
    EXPECT_CALL(mockIo, read(_, 6)).WillOnce(Return(0));  // Simulate read error
    EXPECT_CALL(mockIo, error()).WillOnce(Return(1));  // Indicate error
    EXPECT_CALL(mockIo, eof()).WillOnce(Return(false));

    // Verify that isGifType returns false due to read error
    EXPECT_FALSE(Exiv2::isGifType(mockIo, true));
}

// Boundary test: Test when read reaches EOF
TEST_F(GifImageTest_214, IsGifType_EofReached_214) {
    std::array<byte, 6> gif87aId{'G', 'I', 'F', '8', '7', 'a'};

    // Mock the read method to simulate EOF
    EXPECT_CALL(mockIo, read(_, 6)).WillOnce(Return(6));
    EXPECT_CALL(mockIo, error()).WillOnce(Return(0));
    EXPECT_CALL(mockIo, eof()).WillOnce(Return(true));  // Simulate EOF

    // Verify that isGifType returns false due to EOF
    EXPECT_FALSE(Exiv2::isGifType(mockIo, true));
}

// Exceptional case: Test seek behavior when not advancing
TEST_F(GifImageTest_214, IsGifType_NoAdvance_214) {
    std::array<byte, 6> gif87aId{'G', 'I', 'F', '8', '7', 'a'};

    // Mock the read method to return GIF87a ID
    EXPECT_CALL(mockIo, read(_, 6))
        .WillOnce(DoAll(SetArrayArgument<0>(gif87aId.begin(), gif87aId.end()), Return(6)));
    EXPECT_CALL(mockIo, error()).WillOnce(Return(0));
    EXPECT_CALL(mockIo, eof()).WillOnce(Return(false));
    
    // Mock seek call when not advancing
    EXPECT_CALL(mockIo, seek(-6, Exiv2::BasicIo::cur)).Times(1);

    // Verify that isGifType performs seek due to the "advance" flag being false
    EXPECT_TRUE(Exiv2::isGifType(mockIo, false));
}