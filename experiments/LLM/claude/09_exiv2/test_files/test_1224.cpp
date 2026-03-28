#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "exiv2/basicio.hpp"

// We need access to the function under test
namespace Exiv2 {
bool isJpegType(BasicIo& iIo, bool advance);
}

// Mock class for BasicIo
class MockBasicIo : public Exiv2::BasicIo {
public:
    MOCK_METHOD(int, open, (), (override));
    MOCK_METHOD(int, close, (), (override));
    MOCK_METHOD(size_t, write, (const Exiv2::byte* data, size_t wcount), (override));
    MOCK_METHOD(size_t, write, (Exiv2::BasicIo& src), (override));
    MOCK_METHOD(int, putb, (Exiv2::byte data), (override));
    MOCK_METHOD(Exiv2::DataBuf, read, (size_t rcount), (override));
    MOCK_METHOD(size_t, read, (Exiv2::byte* buf, size_t rcount), (override));
    MOCK_METHOD(int, getb, (), (override));
    MOCK_METHOD(void, transfer, (Exiv2::BasicIo& src), (override));
    MOCK_METHOD(int, seek, (int64_t offset, Position pos), (override));
    MOCK_METHOD(Exiv2::byte*, mmap, (bool isWriteable), (override));
    MOCK_METHOD(int, munmap, (), (override));
    MOCK_METHOD(const size_t, tell, (), (const, override));
    MOCK_METHOD(const size_t, size, (), (const, override));
    MOCK_METHOD(const bool, isopen, (), (const, override));
    MOCK_METHOD(const int, error, (), (const, override));
    MOCK_METHOD(const bool, eof, (), (const, override));
    MOCK_METHOD(const std::string&, path, (), (const, override));
    MOCK_METHOD(void, populateFakeData, (), (override));
};

using ::testing::_;
using ::testing::Return;
using ::testing::DoAll;
using ::testing::SetArrayArgument;
using ::testing::InSequence;

class IsJpegTypeTest_1224 : public ::testing::Test {
protected:
    MockBasicIo mockIo;
};

// Test: Valid JPEG signature with advance=true should return true and NOT seek back
TEST_F(IsJpegTypeTest_1224, ValidJpegWithAdvance_1224) {
    Exiv2::byte jpegHeader[] = {0xFF, 0xD8};  // soi_ = -40 = 0xD8 as unsigned byte
    
    InSequence seq;
    EXPECT_CALL(mockIo, read(_, 2))
        .WillOnce(DoAll(
            SetArrayArgument<0>(jpegHeader, jpegHeader + 2),
            Return(2)));
    EXPECT_CALL(mockIo, error())
        .WillOnce(Return(0));
    EXPECT_CALL(mockIo, eof())
        .WillOnce(Return(false));
    // With advance=true and result=true, seek should NOT be called
    EXPECT_CALL(mockIo, seek(_, _)).Times(0);
    
    bool result = Exiv2::isJpegType(mockIo, true);
    EXPECT_TRUE(result);
}

// Test: Valid JPEG signature with advance=false should return true and seek back
TEST_F(IsJpegTypeTest_1224, ValidJpegWithoutAdvance_1224) {
    Exiv2::byte jpegHeader[] = {0xFF, 0xD8};
    
    InSequence seq;
    EXPECT_CALL(mockIo, read(_, 2))
        .WillOnce(DoAll(
            SetArrayArgument<0>(jpegHeader, jpegHeader + 2),
            Return(2)));
    EXPECT_CALL(mockIo, error())
        .WillOnce(Return(0));
    EXPECT_CALL(mockIo, eof())
        .WillOnce(Return(false));
    // With advance=false, seek should be called to go back
    EXPECT_CALL(mockIo, seek(-2, Exiv2::BasicIo::cur))
        .WillOnce(Return(0));
    
    bool result = Exiv2::isJpegType(mockIo, false);
    EXPECT_TRUE(result);
}

// Test: Invalid JPEG signature (wrong first byte) with advance=true should return false and seek back
TEST_F(IsJpegTypeTest_1224, InvalidFirstByteWithAdvance_1224) {
    Exiv2::byte invalidHeader[] = {0x00, 0xD8};
    
    InSequence seq;
    EXPECT_CALL(mockIo, read(_, 2))
        .WillOnce(DoAll(
            SetArrayArgument<0>(invalidHeader, invalidHeader + 2),
            Return(2)));
    EXPECT_CALL(mockIo, error())
        .WillOnce(Return(0));
    EXPECT_CALL(mockIo, eof())
        .WillOnce(Return(false));
    // result=false, so seek should be called regardless of advance
    EXPECT_CALL(mockIo, seek(-2, Exiv2::BasicIo::cur))
        .WillOnce(Return(0));
    
    bool result = Exiv2::isJpegType(mockIo, true);
    EXPECT_FALSE(result);
}

// Test: Invalid JPEG signature (wrong second byte) with advance=true should return false and seek back
TEST_F(IsJpegTypeTest_1224, InvalidSecondByteWithAdvance_1224) {
    Exiv2::byte invalidHeader[] = {0xFF, 0x00};
    
    InSequence seq;
    EXPECT_CALL(mockIo, read(_, 2))
        .WillOnce(DoAll(
            SetArrayArgument<0>(invalidHeader, invalidHeader + 2),
            Return(2)));
    EXPECT_CALL(mockIo, error())
        .WillOnce(Return(0));
    EXPECT_CALL(mockIo, eof())
        .WillOnce(Return(false));
    EXPECT_CALL(mockIo, seek(-2, Exiv2::BasicIo::cur))
        .WillOnce(Return(0));
    
    bool result = Exiv2::isJpegType(mockIo, true);
    EXPECT_FALSE(result);
}

// Test: Invalid JPEG signature (both bytes wrong) with advance=false should return false and seek back
TEST_F(IsJpegTypeTest_1224, BothBytesInvalidWithoutAdvance_1224) {
    Exiv2::byte invalidHeader[] = {0x00, 0x00};
    
    InSequence seq;
    EXPECT_CALL(mockIo, read(_, 2))
        .WillOnce(DoAll(
            SetArrayArgument<0>(invalidHeader, invalidHeader + 2),
            Return(2)));
    EXPECT_CALL(mockIo, error())
        .WillOnce(Return(0));
    EXPECT_CALL(mockIo, eof())
        .WillOnce(Return(false));
    EXPECT_CALL(mockIo, seek(-2, Exiv2::BasicIo::cur))
        .WillOnce(Return(0));
    
    bool result = Exiv2::isJpegType(mockIo, false);
    EXPECT_FALSE(result);
}

// Test: Read error should return false immediately
TEST_F(IsJpegTypeTest_1224, ReadErrorReturnsFalse_1224) {
    EXPECT_CALL(mockIo, read(_, 2))
        .WillOnce(Return(0));
    EXPECT_CALL(mockIo, error())
        .WillOnce(Return(1));  // error occurred
    
    bool result = Exiv2::isJpegType(mockIo, true);
    EXPECT_FALSE(result);
}

// Test: EOF condition should return false immediately
TEST_F(IsJpegTypeTest_1224, EofReturnsFalse_1224) {
    EXPECT_CALL(mockIo, read(_, 2))
        .WillOnce(Return(0));
    EXPECT_CALL(mockIo, error())
        .WillOnce(Return(0));
    EXPECT_CALL(mockIo, eof())
        .WillOnce(Return(true));  // EOF reached
    
    bool result = Exiv2::isJpegType(mockIo, true);
    EXPECT_FALSE(result);
}

// Test: EOF condition with advance=false should return false
TEST_F(IsJpegTypeTest_1224, EofWithoutAdvanceReturnsFalse_1224) {
    EXPECT_CALL(mockIo, read(_, 2))
        .WillOnce(Return(0));
    EXPECT_CALL(mockIo, error())
        .WillOnce(Return(0));
    EXPECT_CALL(mockIo, eof())
        .WillOnce(Return(true));
    
    bool result = Exiv2::isJpegType(mockIo, false);
    EXPECT_FALSE(result);
}

// Test: Read error with advance=false should return false
TEST_F(IsJpegTypeTest_1224, ReadErrorWithoutAdvanceReturnsFalse_1224) {
    EXPECT_CALL(mockIo, read(_, 2))
        .WillOnce(Return(0));
    EXPECT_CALL(mockIo, error())
        .WillOnce(Return(1));
    
    bool result = Exiv2::isJpegType(mockIo, false);
    EXPECT_FALSE(result);
}

// Test: First byte 0xFF but second byte is another marker (not SOI) should return false
TEST_F(IsJpegTypeTest_1224, ValidFFButNotSOI_1224) {
    Exiv2::byte header[] = {0xFF, 0xE0};  // app0_ marker, not SOI
    
    InSequence seq;
    EXPECT_CALL(mockIo, read(_, 2))
        .WillOnce(DoAll(
            SetArrayArgument<0>(header, header + 2),
            Return(2)));
    EXPECT_CALL(mockIo, error())
        .WillOnce(Return(0));
    EXPECT_CALL(mockIo, eof())
        .WillOnce(Return(false));
    EXPECT_CALL(mockIo, seek(-2, Exiv2::BasicIo::cur))
        .WillOnce(Return(0));
    
    bool result = Exiv2::isJpegType(mockIo, true);
    EXPECT_FALSE(result);
}

// Test: 0xFF followed by EOI marker should return false (not SOI)
TEST_F(IsJpegTypeTest_1224, FFFollowedByEOI_1224) {
    Exiv2::byte header[] = {0xFF, 0xD9};  // EOI marker
    
    InSequence seq;
    EXPECT_CALL(mockIo, read(_, 2))
        .WillOnce(DoAll(
            SetArrayArgument<0>(header, header + 2),
            Return(2)));
    EXPECT_CALL(mockIo, error())
        .WillOnce(Return(0));
    EXPECT_CALL(mockIo, eof())
        .WillOnce(Return(false));
    EXPECT_CALL(mockIo, seek(-2, Exiv2::BasicIo::cur))
        .WillOnce(Return(0));
    
    bool result = Exiv2::isJpegType(mockIo, true);
    EXPECT_FALSE(result);
}

// Test: Invalid signature with advance=false should seek back
TEST_F(IsJpegTypeTest_1224, InvalidSignatureSeeksBackWithoutAdvance_1224) {
    Exiv2::byte invalidHeader[] = {0x89, 0x50};  // PNG signature start
    
    InSequence seq;
    EXPECT_CALL(mockIo, read(_, 2))
        .WillOnce(DoAll(
            SetArrayArgument<0>(invalidHeader, invalidHeader + 2),
            Return(2)));
    EXPECT_CALL(mockIo, error())
        .WillOnce(Return(0));
    EXPECT_CALL(mockIo, eof())
        .WillOnce(Return(false));
    EXPECT_CALL(mockIo, seek(-2, Exiv2::BasicIo::cur))
        .WillOnce(Return(0));
    
    bool result = Exiv2::isJpegType(mockIo, false);
    EXPECT_FALSE(result);
}

// Test: Boundary - 0xFF followed by 0xFF should return false
TEST_F(IsJpegTypeTest_1224, FFFollowedByFF_1224) {
    Exiv2::byte header[] = {0xFF, 0xFF};
    
    InSequence seq;
    EXPECT_CALL(mockIo, read(_, 2))
        .WillOnce(DoAll(
            SetArrayArgument<0>(header, header + 2),
            Return(2)));
    EXPECT_CALL(mockIo, error())
        .WillOnce(Return(0));
    EXPECT_CALL(mockIo, eof())
        .WillOnce(Return(false));
    EXPECT_CALL(mockIo, seek(-2, Exiv2::BasicIo::cur))
        .WillOnce(Return(0));
    
    bool result = Exiv2::isJpegType(mockIo, true);
    EXPECT_FALSE(result);
}

// Test: Boundary - 0xD8 followed by 0xFF (swapped bytes) should return false
TEST_F(IsJpegTypeTest_1224, SwappedJpegBytes_1224) {
    Exiv2::byte header[] = {0xD8, 0xFF};
    
    InSequence seq;
    EXPECT_CALL(mockIo, read(_, 2))
        .WillOnce(DoAll(
            SetArrayArgument<0>(header, header + 2),
            Return(2)));
    EXPECT_CALL(mockIo, error())
        .WillOnce(Return(0));
    EXPECT_CALL(mockIo, eof())
        .WillOnce(Return(false));
    EXPECT_CALL(mockIo, seek(-2, Exiv2::BasicIo::cur))
        .WillOnce(Return(0));
    
    bool result = Exiv2::isJpegType(mockIo, true);
    EXPECT_FALSE(result);
}
