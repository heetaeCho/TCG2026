#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <exiv2/basicio.hpp>
#include <array>
#include <cstring>

// We need to include the header that declares isRiffType
// Based on the file structure, it should be in riffvideo.hpp or similar
namespace Exiv2 {
bool isRiffType(BasicIo& iIo, bool advance);
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
using ::testing::Invoke;

class RiffVideoTest_83 : public ::testing::Test {
protected:
    MockBasicIo mockIo;
};

// Test: Valid RIFF header with advance=true should return true and NOT seek back
TEST_F(RiffVideoTest_83, ValidRiffHeaderWithAdvance_83) {
    Exiv2::byte riffData[] = {'R', 'I', 'F', 'F'};

    EXPECT_CALL(mockIo, read(_, 4))
        .WillOnce(DoAll(
            SetArrayArgument<0>(riffData, riffData + 4),
            Return(4)));
    EXPECT_CALL(mockIo, error())
        .WillOnce(Return(0));
    EXPECT_CALL(mockIo, eof())
        .WillOnce(Return(false));
    // Should NOT call seek when advance=true and matched
    EXPECT_CALL(mockIo, seek(_, _)).Times(0);

    bool result = Exiv2::isRiffType(mockIo, true);
    EXPECT_TRUE(result);
}

// Test: Valid RIFF header with advance=false should return true and seek back
TEST_F(RiffVideoTest_83, ValidRiffHeaderWithoutAdvance_83) {
    Exiv2::byte riffData[] = {'R', 'I', 'F', 'F'};

    EXPECT_CALL(mockIo, read(_, 4))
        .WillOnce(DoAll(
            SetArrayArgument<0>(riffData, riffData + 4),
            Return(4)));
    EXPECT_CALL(mockIo, error())
        .WillOnce(Return(0));
    EXPECT_CALL(mockIo, eof())
        .WillOnce(Return(false));
    // Should seek back when advance=false even if matched
    EXPECT_CALL(mockIo, seek(-4, Exiv2::BasicIo::cur))
        .WillOnce(Return(0));

    bool result = Exiv2::isRiffType(mockIo, false);
    EXPECT_TRUE(result);
}

// Test: Invalid header with advance=true should return false and seek back
TEST_F(RiffVideoTest_83, InvalidHeaderWithAdvance_83) {
    Exiv2::byte invalidData[] = {'A', 'V', 'I', ' '};

    EXPECT_CALL(mockIo, read(_, 4))
        .WillOnce(DoAll(
            SetArrayArgument<0>(invalidData, invalidData + 4),
            Return(4)));
    EXPECT_CALL(mockIo, error())
        .WillOnce(Return(0));
    EXPECT_CALL(mockIo, eof())
        .WillOnce(Return(false));
    // Should seek back when not matched
    EXPECT_CALL(mockIo, seek(-4, Exiv2::BasicIo::cur))
        .WillOnce(Return(0));

    bool result = Exiv2::isRiffType(mockIo, true);
    EXPECT_FALSE(result);
}

// Test: Invalid header with advance=false should return false and seek back
TEST_F(RiffVideoTest_83, InvalidHeaderWithoutAdvance_83) {
    Exiv2::byte invalidData[] = {'X', 'Y', 'Z', 'W'};

    EXPECT_CALL(mockIo, read(_, 4))
        .WillOnce(DoAll(
            SetArrayArgument<0>(invalidData, invalidData + 4),
            Return(4)));
    EXPECT_CALL(mockIo, error())
        .WillOnce(Return(0));
    EXPECT_CALL(mockIo, eof())
        .WillOnce(Return(false));
    EXPECT_CALL(mockIo, seek(-4, Exiv2::BasicIo::cur))
        .WillOnce(Return(0));

    bool result = Exiv2::isRiffType(mockIo, false);
    EXPECT_FALSE(result);
}

// Test: IO error on read should return false
TEST_F(RiffVideoTest_83, IoErrorReturnsFlase_83) {
    Exiv2::byte someData[] = {'R', 'I', 'F', 'F'};

    EXPECT_CALL(mockIo, read(_, 4))
        .WillOnce(DoAll(
            SetArrayArgument<0>(someData, someData + 4),
            Return(4)));
    EXPECT_CALL(mockIo, error())
        .WillOnce(Return(1));  // error occurred

    bool result = Exiv2::isRiffType(mockIo, true);
    EXPECT_FALSE(result);
}

// Test: EOF on read should return false
TEST_F(RiffVideoTest_83, EofReturnsFlase_83) {
    Exiv2::byte someData[] = {0, 0, 0, 0};

    EXPECT_CALL(mockIo, read(_, 4))
        .WillOnce(DoAll(
            SetArrayArgument<0>(someData, someData + 4),
            Return(0)));
    EXPECT_CALL(mockIo, error())
        .WillOnce(Return(0));
    EXPECT_CALL(mockIo, eof())
        .WillOnce(Return(true));  // EOF

    bool result = Exiv2::isRiffType(mockIo, true);
    EXPECT_FALSE(result);
}

// Test: Partial match (only first bytes match RIFF) should return false
TEST_F(RiffVideoTest_83, PartialMatchReturnsFalse_83) {
    Exiv2::byte partialData[] = {'R', 'I', 'F', 'X'};  // last byte differs

    EXPECT_CALL(mockIo, read(_, 4))
        .WillOnce(DoAll(
            SetArrayArgument<0>(partialData, partialData + 4),
            Return(4)));
    EXPECT_CALL(mockIo, error())
        .WillOnce(Return(0));
    EXPECT_CALL(mockIo, eof())
        .WillOnce(Return(false));
    EXPECT_CALL(mockIo, seek(-4, Exiv2::BasicIo::cur))
        .WillOnce(Return(0));

    bool result = Exiv2::isRiffType(mockIo, true);
    EXPECT_FALSE(result);
}

// Test: All zeros should return false
TEST_F(RiffVideoTest_83, AllZerosReturnsFalse_83) {
    Exiv2::byte zeroData[] = {0, 0, 0, 0};

    EXPECT_CALL(mockIo, read(_, 4))
        .WillOnce(DoAll(
            SetArrayArgument<0>(zeroData, zeroData + 4),
            Return(4)));
    EXPECT_CALL(mockIo, error())
        .WillOnce(Return(0));
    EXPECT_CALL(mockIo, eof())
        .WillOnce(Return(false));
    EXPECT_CALL(mockIo, seek(-4, Exiv2::BasicIo::cur))
        .WillOnce(Return(0));

    bool result = Exiv2::isRiffType(mockIo, true);
    EXPECT_FALSE(result);
}

// Test: Case sensitivity - lowercase 'riff' should not match
TEST_F(RiffVideoTest_83, CaseSensitiveNoMatch_83) {
    Exiv2::byte lowerData[] = {'r', 'i', 'f', 'f'};

    EXPECT_CALL(mockIo, read(_, 4))
        .WillOnce(DoAll(
            SetArrayArgument<0>(lowerData, lowerData + 4),
            Return(4)));
    EXPECT_CALL(mockIo, error())
        .WillOnce(Return(0));
    EXPECT_CALL(mockIo, eof())
        .WillOnce(Return(false));
    EXPECT_CALL(mockIo, seek(-4, Exiv2::BasicIo::cur))
        .WillOnce(Return(0));

    bool result = Exiv2::isRiffType(mockIo, true);
    EXPECT_FALSE(result);
}

// Test: First byte differs from 'R'
TEST_F(RiffVideoTest_83, FirstByteDiffers_83) {
    Exiv2::byte data[] = {'X', 'I', 'F', 'F'};

    EXPECT_CALL(mockIo, read(_, 4))
        .WillOnce(DoAll(
            SetArrayArgument<0>(data, data + 4),
            Return(4)));
    EXPECT_CALL(mockIo, error())
        .WillOnce(Return(0));
    EXPECT_CALL(mockIo, eof())
        .WillOnce(Return(false));
    EXPECT_CALL(mockIo, seek(-4, Exiv2::BasicIo::cur))
        .WillOnce(Return(0));

    bool result = Exiv2::isRiffType(mockIo, false);
    EXPECT_FALSE(result);
}

// Test: Both error and eof true should return false
TEST_F(RiffVideoTest_83, BothErrorAndEof_83) {
    Exiv2::byte someData[] = {0, 0, 0, 0};

    EXPECT_CALL(mockIo, read(_, 4))
        .WillOnce(DoAll(
            SetArrayArgument<0>(someData, someData + 4),
            Return(0)));
    EXPECT_CALL(mockIo, error())
        .WillOnce(Return(1));

    bool result = Exiv2::isRiffType(mockIo, false);
    EXPECT_FALSE(result);
}

// Test: Similar but not exact - "RIFX" (RIFX is actually a different format)
TEST_F(RiffVideoTest_83, RifxDoesNotMatch_83) {
    Exiv2::byte rifxData[] = {'R', 'I', 'F', 'X'};

    EXPECT_CALL(mockIo, read(_, 4))
        .WillOnce(DoAll(
            SetArrayArgument<0>(rifxData, rifxData + 4),
            Return(4)));
    EXPECT_CALL(mockIo, error())
        .WillOnce(Return(0));
    EXPECT_CALL(mockIo, eof())
        .WillOnce(Return(false));
    EXPECT_CALL(mockIo, seek(-4, Exiv2::BasicIo::cur))
        .WillOnce(Return(0));

    bool result = Exiv2::isRiffType(mockIo, true);
    EXPECT_FALSE(result);
}
