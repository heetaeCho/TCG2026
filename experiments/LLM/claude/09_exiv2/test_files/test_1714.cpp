#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <exiv2/basicio.hpp>
#include <exiv2/pgfimage.hpp>
#include <array>
#include <cstring>

// We need access to the isPgfType function
namespace Exiv2 {
bool isPgfType(BasicIo& iIo, bool advance);
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
using ::testing::Invoke;

class IsPgfTypeTest_1714 : public ::testing::Test {
protected:
    MockBasicIo mockIo;
};

// Test: Valid PGF signature with advance=true should return true and NOT seek back
TEST_F(IsPgfTypeTest_1714, ValidPgfSignatureWithAdvance_1714) {
    Exiv2::byte pgfSig[] = {0x50, 0x47, 0x46}; // 'P', 'G', 'F'

    EXPECT_CALL(mockIo, read(_, 3))
        .WillOnce(DoAll(
            SetArrayArgument<0>(pgfSig, pgfSig + 3),
            Return(3)));
    EXPECT_CALL(mockIo, error())
        .WillOnce(Return(0));
    EXPECT_CALL(mockIo, eof())
        .WillOnce(Return(false));
    // Should NOT seek back when advance=true and signature matches
    EXPECT_CALL(mockIo, seek(_, _)).Times(0);

    bool result = Exiv2::isPgfType(mockIo, true);
    EXPECT_TRUE(result);
}

// Test: Valid PGF signature with advance=false should return true and seek back
TEST_F(IsPgfTypeTest_1714, ValidPgfSignatureWithoutAdvance_1714) {
    Exiv2::byte pgfSig[] = {0x50, 0x47, 0x46};

    EXPECT_CALL(mockIo, read(_, 3))
        .WillOnce(DoAll(
            SetArrayArgument<0>(pgfSig, pgfSig + 3),
            Return(3)));
    EXPECT_CALL(mockIo, error())
        .WillOnce(Return(0));
    EXPECT_CALL(mockIo, eof())
        .WillOnce(Return(false));
    // Should seek back when advance=false even though signature matches
    EXPECT_CALL(mockIo, seek(-3, Exiv2::BasicIo::cur))
        .WillOnce(Return(0));

    bool result = Exiv2::isPgfType(mockIo, false);
    EXPECT_TRUE(result);
}

// Test: Invalid signature with advance=true should return false and seek back
TEST_F(IsPgfTypeTest_1714, InvalidSignatureWithAdvance_1714) {
    Exiv2::byte notPgf[] = {0x41, 0x42, 0x43}; // 'A', 'B', 'C'

    EXPECT_CALL(mockIo, read(_, 3))
        .WillOnce(DoAll(
            SetArrayArgument<0>(notPgf, notPgf + 3),
            Return(3)));
    EXPECT_CALL(mockIo, error())
        .WillOnce(Return(0));
    EXPECT_CALL(mockIo, eof())
        .WillOnce(Return(false));
    // Should seek back because signature doesn't match
    EXPECT_CALL(mockIo, seek(-3, Exiv2::BasicIo::cur))
        .WillOnce(Return(0));

    bool result = Exiv2::isPgfType(mockIo, true);
    EXPECT_FALSE(result);
}

// Test: Invalid signature with advance=false should return false and seek back
TEST_F(IsPgfTypeTest_1714, InvalidSignatureWithoutAdvance_1714) {
    Exiv2::byte notPgf[] = {0x00, 0x00, 0x00};

    EXPECT_CALL(mockIo, read(_, 3))
        .WillOnce(DoAll(
            SetArrayArgument<0>(notPgf, notPgf + 3),
            Return(3)));
    EXPECT_CALL(mockIo, error())
        .WillOnce(Return(0));
    EXPECT_CALL(mockIo, eof())
        .WillOnce(Return(false));
    EXPECT_CALL(mockIo, seek(-3, Exiv2::BasicIo::cur))
        .WillOnce(Return(0));

    bool result = Exiv2::isPgfType(mockIo, false);
    EXPECT_FALSE(result);
}

// Test: IO error during read should return false
TEST_F(IsPgfTypeTest_1714, IoErrorReturnsFlase_1714) {
    Exiv2::byte buf[] = {0x50, 0x47, 0x46};

    EXPECT_CALL(mockIo, read(_, 3))
        .WillOnce(DoAll(
            SetArrayArgument<0>(buf, buf + 3),
            Return(3)));
    EXPECT_CALL(mockIo, error())
        .WillOnce(Return(1)); // error occurred

    bool result = Exiv2::isPgfType(mockIo, true);
    EXPECT_FALSE(result);
}

// Test: EOF during read should return false
TEST_F(IsPgfTypeTest_1714, EofReturnsFlase_1714) {
    Exiv2::byte buf[] = {0x50, 0x47, 0x00};

    EXPECT_CALL(mockIo, read(_, 3))
        .WillOnce(DoAll(
            SetArrayArgument<0>(buf, buf + 3),
            Return(2)));
    EXPECT_CALL(mockIo, error())
        .WillOnce(Return(0));
    EXPECT_CALL(mockIo, eof())
        .WillOnce(Return(true)); // EOF reached

    bool result = Exiv2::isPgfType(mockIo, true);
    EXPECT_FALSE(result);
}

// Test: Partial match (first two bytes match, third doesn't)
TEST_F(IsPgfTypeTest_1714, PartialMatchReturnsFalse_1714) {
    Exiv2::byte partialPgf[] = {0x50, 0x47, 0x00}; // 'P', 'G', '\0'

    EXPECT_CALL(mockIo, read(_, 3))
        .WillOnce(DoAll(
            SetArrayArgument<0>(partialPgf, partialPgf + 3),
            Return(3)));
    EXPECT_CALL(mockIo, error())
        .WillOnce(Return(0));
    EXPECT_CALL(mockIo, eof())
        .WillOnce(Return(false));
    EXPECT_CALL(mockIo, seek(-3, Exiv2::BasicIo::cur))
        .WillOnce(Return(0));

    bool result = Exiv2::isPgfType(mockIo, true);
    EXPECT_FALSE(result);
}

// Test: Only first byte matches
TEST_F(IsPgfTypeTest_1714, OnlyFirstByteMatchesReturnsFalse_1714) {
    Exiv2::byte data[] = {0x50, 0x00, 0x00}; // 'P', '\0', '\0'

    EXPECT_CALL(mockIo, read(_, 3))
        .WillOnce(DoAll(
            SetArrayArgument<0>(data, data + 3),
            Return(3)));
    EXPECT_CALL(mockIo, error())
        .WillOnce(Return(0));
    EXPECT_CALL(mockIo, eof())
        .WillOnce(Return(false));
    EXPECT_CALL(mockIo, seek(-3, Exiv2::BasicIo::cur))
        .WillOnce(Return(0));

    bool result = Exiv2::isPgfType(mockIo, false);
    EXPECT_FALSE(result);
}

// Test: All zeros
TEST_F(IsPgfTypeTest_1714, AllZerosReturnsFalse_1714) {
    Exiv2::byte data[] = {0x00, 0x00, 0x00};

    EXPECT_CALL(mockIo, read(_, 3))
        .WillOnce(DoAll(
            SetArrayArgument<0>(data, data + 3),
            Return(3)));
    EXPECT_CALL(mockIo, error())
        .WillOnce(Return(0));
    EXPECT_CALL(mockIo, eof())
        .WillOnce(Return(false));
    EXPECT_CALL(mockIo, seek(-3, Exiv2::BasicIo::cur))
        .WillOnce(Return(0));

    bool result = Exiv2::isPgfType(mockIo, true);
    EXPECT_FALSE(result);
}

// Test: Case sensitivity - lowercase 'pgf' should not match
TEST_F(IsPgfTypeTest_1714, LowercasePgfReturnsFalse_1714) {
    Exiv2::byte data[] = {0x70, 0x67, 0x66}; // 'p', 'g', 'f'

    EXPECT_CALL(mockIo, read(_, 3))
        .WillOnce(DoAll(
            SetArrayArgument<0>(data, data + 3),
            Return(3)));
    EXPECT_CALL(mockIo, error())
        .WillOnce(Return(0));
    EXPECT_CALL(mockIo, eof())
        .WillOnce(Return(false));
    EXPECT_CALL(mockIo, seek(-3, Exiv2::BasicIo::cur))
        .WillOnce(Return(0));

    bool result = Exiv2::isPgfType(mockIo, true);
    EXPECT_FALSE(result);
}

// Test: Both error and eof
TEST_F(IsPgfTypeTest_1714, BothErrorAndEofReturnsFalse_1714) {
    Exiv2::byte data[] = {0x00, 0x00, 0x00};

    EXPECT_CALL(mockIo, read(_, 3))
        .WillOnce(DoAll(
            SetArrayArgument<0>(data, data + 3),
            Return(0)));
    EXPECT_CALL(mockIo, error())
        .WillOnce(Return(1));

    bool result = Exiv2::isPgfType(mockIo, false);
    EXPECT_FALSE(result);
}

// Test with MemIo for integration-like testing using real BasicIo implementation
class IsPgfTypeMemIoTest_1714 : public ::testing::Test {
};

TEST_F(IsPgfTypeMemIoTest_1714, MemIoValidPgfSignature_1714) {
    Exiv2::byte data[] = {0x50, 0x47, 0x46, 0xAA, 0xBB};
    Exiv2::MemIo memIo(data, sizeof(data));

    bool result = Exiv2::isPgfType(memIo, true);
    EXPECT_TRUE(result);
    // Position should have advanced past the 3 signature bytes
    EXPECT_EQ(memIo.tell(), 3u);
}

TEST_F(IsPgfTypeMemIoTest_1714, MemIoValidPgfNoAdvance_1714) {
    Exiv2::byte data[] = {0x50, 0x47, 0x46, 0xAA, 0xBB};
    Exiv2::MemIo memIo(data, sizeof(data));

    bool result = Exiv2::isPgfType(memIo, false);
    EXPECT_TRUE(result);
    // Position should be back to start since advance=false
    EXPECT_EQ(memIo.tell(), 0u);
}

TEST_F(IsPgfTypeMemIoTest_1714, MemIoInvalidSignature_1714) {
    Exiv2::byte data[] = {0x41, 0x42, 0x43, 0x44};
    Exiv2::MemIo memIo(data, sizeof(data));

    bool result = Exiv2::isPgfType(memIo, true);
    EXPECT_FALSE(result);
    // Position should be back to start since signature didn't match
    EXPECT_EQ(memIo.tell(), 0u);
}

TEST_F(IsPgfTypeMemIoTest_1714, MemIoTooShort_1714) {
    Exiv2::byte data[] = {0x50, 0x47};
    Exiv2::MemIo memIo(data, sizeof(data));

    bool result = Exiv2::isPgfType(memIo, true);
    EXPECT_FALSE(result);
}

TEST_F(IsPgfTypeMemIoTest_1714, MemIoEmptyData_1714) {
    Exiv2::MemIo memIo;

    bool result = Exiv2::isPgfType(memIo, true);
    EXPECT_FALSE(result);
}

TEST_F(IsPgfTypeMemIoTest_1714, MemIoExactlyThreeBytesPgf_1714) {
    Exiv2::byte data[] = {0x50, 0x47, 0x46};
    Exiv2::MemIo memIo(data, sizeof(data));

    bool result = Exiv2::isPgfType(memIo, true);
    EXPECT_TRUE(result);
    EXPECT_EQ(memIo.tell(), 3u);
}

TEST_F(IsPgfTypeMemIoTest_1714, MemIoCalledTwiceWithAdvance_1714) {
    Exiv2::byte data[] = {0x50, 0x47, 0x46, 0x50, 0x47, 0x46};
    Exiv2::MemIo memIo(data, sizeof(data));

    bool result1 = Exiv2::isPgfType(memIo, true);
    EXPECT_TRUE(result1);
    EXPECT_EQ(memIo.tell(), 3u);

    bool result2 = Exiv2::isPgfType(memIo, true);
    EXPECT_TRUE(result2);
    EXPECT_EQ(memIo.tell(), 6u);
}

TEST_F(IsPgfTypeMemIoTest_1714, MemIoCalledTwiceWithoutAdvance_1714) {
    Exiv2::byte data[] = {0x50, 0x47, 0x46};
    Exiv2::MemIo memIo(data, sizeof(data));

    bool result1 = Exiv2::isPgfType(memIo, false);
    EXPECT_TRUE(result1);
    EXPECT_EQ(memIo.tell(), 0u);

    bool result2 = Exiv2::isPgfType(memIo, false);
    EXPECT_TRUE(result2);
    EXPECT_EQ(memIo.tell(), 0u);
}
