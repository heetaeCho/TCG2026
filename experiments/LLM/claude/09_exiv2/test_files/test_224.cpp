#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <exiv2/basicio.hpp>
#include <exiv2/rafimage.hpp>
#include <array>
#include <cstring>

namespace Exiv2 {
// Forward declaration of the function under test
bool isRafType(BasicIo& iIo, bool advance);
}

// Mock class for BasicIo
class MockBasicIo : public Exiv2::BasicIo {
public:
    MOCK_METHOD(int, open, (), (override));
    MOCK_METHOD(int, close, (), (override));
    MOCK_METHOD(size_t, write, (const Exiv2::byte* data, size_t wcount), (override));
    MOCK_METHOD(size_t, write, (BasicIo& src), (override));
    MOCK_METHOD(int, putb, (Exiv2::byte data), (override));
    MOCK_METHOD(Exiv2::DataBuf, read, (size_t rcount), (override));
    MOCK_METHOD(size_t, read, (Exiv2::byte* buf, size_t rcount), (override));
    MOCK_METHOD(int, getb, (), (override));
    MOCK_METHOD(void, transfer, (BasicIo& src), (override));
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

class IsRafTypeTest_224 : public ::testing::Test {
protected:
    MockBasicIo mockIo;
    const std::array<Exiv2::byte, 8> validRafId = {'F', 'U', 'J', 'I', 'F', 'I', 'L', 'M'};
};

// Test: Valid RAF signature with advance=true should return true and NOT seek back
TEST_F(IsRafTypeTest_224, ValidRafSignatureWithAdvance_224) {
    InSequence seq;

    EXPECT_CALL(mockIo, read(_, 8))
        .WillOnce(DoAll(
            SetArrayArgument<0>(validRafId.begin(), validRafId.end()),
            Return(8)));
    EXPECT_CALL(mockIo, error()).WillOnce(Return(0));
    EXPECT_CALL(mockIo, eof()).WillOnce(Return(false));
    // Should NOT call seek when advance=true and rc=true

    bool result = Exiv2::isRafType(mockIo, true);
    EXPECT_TRUE(result);
}

// Test: Valid RAF signature with advance=false should return true and seek back
TEST_F(IsRafTypeTest_224, ValidRafSignatureWithoutAdvance_224) {
    InSequence seq;

    EXPECT_CALL(mockIo, read(_, 8))
        .WillOnce(DoAll(
            SetArrayArgument<0>(validRafId.begin(), validRafId.end()),
            Return(8)));
    EXPECT_CALL(mockIo, error()).WillOnce(Return(0));
    EXPECT_CALL(mockIo, eof()).WillOnce(Return(false));
    EXPECT_CALL(mockIo, seek(-8, Exiv2::BasicIo::cur)).WillOnce(Return(0));

    bool result = Exiv2::isRafType(mockIo, false);
    EXPECT_TRUE(result);
}

// Test: Invalid signature with advance=true should return false and seek back
TEST_F(IsRafTypeTest_224, InvalidSignatureWithAdvance_224) {
    InSequence seq;
    std::array<Exiv2::byte, 8> invalidId = {'N', 'O', 'T', 'R', 'A', 'F', '!', '!'};

    EXPECT_CALL(mockIo, read(_, 8))
        .WillOnce(DoAll(
            SetArrayArgument<0>(invalidId.begin(), invalidId.end()),
            Return(8)));
    EXPECT_CALL(mockIo, error()).WillOnce(Return(0));
    EXPECT_CALL(mockIo, eof()).WillOnce(Return(false));
    EXPECT_CALL(mockIo, seek(-8, Exiv2::BasicIo::cur)).WillOnce(Return(0));

    bool result = Exiv2::isRafType(mockIo, true);
    EXPECT_FALSE(result);
}

// Test: Invalid signature with advance=false should return false and seek back
TEST_F(IsRafTypeTest_224, InvalidSignatureWithoutAdvance_224) {
    InSequence seq;
    std::array<Exiv2::byte, 8> invalidId = {'X', 'Y', 'Z', 'A', 'B', 'C', 'D', 'E'};

    EXPECT_CALL(mockIo, read(_, 8))
        .WillOnce(DoAll(
            SetArrayArgument<0>(invalidId.begin(), invalidId.end()),
            Return(8)));
    EXPECT_CALL(mockIo, error()).WillOnce(Return(0));
    EXPECT_CALL(mockIo, eof()).WillOnce(Return(false));
    EXPECT_CALL(mockIo, seek(-8, Exiv2::BasicIo::cur)).WillOnce(Return(0));

    bool result = Exiv2::isRafType(mockIo, false);
    EXPECT_FALSE(result);
}

// Test: Read error returns false
TEST_F(IsRafTypeTest_224, ReadErrorReturnsFalse_224) {
    InSequence seq;

    EXPECT_CALL(mockIo, read(_, 8))
        .WillOnce(Return(0));
    EXPECT_CALL(mockIo, error()).WillOnce(Return(1));  // error occurred

    bool result = Exiv2::isRafType(mockIo, true);
    EXPECT_FALSE(result);
}

// Test: EOF during read returns false
TEST_F(IsRafTypeTest_224, EofDuringReadReturnsFalse_224) {
    InSequence seq;

    EXPECT_CALL(mockIo, read(_, 8))
        .WillOnce(Return(4));  // partial read
    EXPECT_CALL(mockIo, error()).WillOnce(Return(0));
    EXPECT_CALL(mockIo, eof()).WillOnce(Return(true));  // EOF reached

    bool result = Exiv2::isRafType(mockIo, true);
    EXPECT_FALSE(result);
}

// Test: Partial match (first 7 bytes correct, last byte different)
TEST_F(IsRafTypeTest_224, PartialMatchReturnsFalse_224) {
    InSequence seq;
    std::array<Exiv2::byte, 8> partialId = {'F', 'U', 'J', 'I', 'F', 'I', 'L', 'X'};

    EXPECT_CALL(mockIo, read(_, 8))
        .WillOnce(DoAll(
            SetArrayArgument<0>(partialId.begin(), partialId.end()),
            Return(8)));
    EXPECT_CALL(mockIo, error()).WillOnce(Return(0));
    EXPECT_CALL(mockIo, eof()).WillOnce(Return(false));
    EXPECT_CALL(mockIo, seek(-8, Exiv2::BasicIo::cur)).WillOnce(Return(0));

    bool result = Exiv2::isRafType(mockIo, true);
    EXPECT_FALSE(result);
}

// Test: All zeros should return false
TEST_F(IsRafTypeTest_224, AllZerosReturnsFalse_224) {
    InSequence seq;
    std::array<Exiv2::byte, 8> zeros = {0, 0, 0, 0, 0, 0, 0, 0};

    EXPECT_CALL(mockIo, read(_, 8))
        .WillOnce(DoAll(
            SetArrayArgument<0>(zeros.begin(), zeros.end()),
            Return(8)));
    EXPECT_CALL(mockIo, error()).WillOnce(Return(0));
    EXPECT_CALL(mockIo, eof()).WillOnce(Return(false));
    EXPECT_CALL(mockIo, seek(-8, Exiv2::BasicIo::cur)).WillOnce(Return(0));

    bool result = Exiv2::isRafType(mockIo, false);
    EXPECT_FALSE(result);
}

// Test: First byte wrong only
TEST_F(IsRafTypeTest_224, FirstByteWrongReturnsFalse_224) {
    InSequence seq;
    std::array<Exiv2::byte, 8> almostId = {'f', 'U', 'J', 'I', 'F', 'I', 'L', 'M'};

    EXPECT_CALL(mockIo, read(_, 8))
        .WillOnce(DoAll(
            SetArrayArgument<0>(almostId.begin(), almostId.end()),
            Return(8)));
    EXPECT_CALL(mockIo, error()).WillOnce(Return(0));
    EXPECT_CALL(mockIo, eof()).WillOnce(Return(false));
    EXPECT_CALL(mockIo, seek(-8, Exiv2::BasicIo::cur)).WillOnce(Return(0));

    bool result = Exiv2::isRafType(mockIo, true);
    EXPECT_FALSE(result);
}

// Test: Both error and eof set returns false
TEST_F(IsRafTypeTest_224, BothErrorAndEofReturnsFalse_224) {
    InSequence seq;

    EXPECT_CALL(mockIo, read(_, 8))
        .WillOnce(Return(0));
    EXPECT_CALL(mockIo, error()).WillOnce(Return(1));

    bool result = Exiv2::isRafType(mockIo, false);
    EXPECT_FALSE(result);
}

// Test: Valid signature - verify seek is not called when advance=true
TEST_F(IsRafTypeTest_224, ValidSignatureAdvanceTrueNoSeek_224) {
    EXPECT_CALL(mockIo, read(_, 8))
        .WillOnce(DoAll(
            SetArrayArgument<0>(validRafId.begin(), validRafId.end()),
            Return(8)));
    EXPECT_CALL(mockIo, error()).WillOnce(Return(0));
    EXPECT_CALL(mockIo, eof()).WillOnce(Return(false));
    EXPECT_CALL(mockIo, seek(_, _)).Times(0);  // seek should NOT be called

    bool result = Exiv2::isRafType(mockIo, true);
    EXPECT_TRUE(result);
}
