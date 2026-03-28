#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <exiv2/basicio.hpp>

// We need access to the isMkvType function
namespace Exiv2 {
bool isMkvType(BasicIo& iIo, bool advance);
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

class IsMkvTypeTest_106 : public ::testing::Test {
protected:
    MockBasicIo mockIo;
};

// Test: Valid MKV magic bytes with advance=true should return true and NOT seek back
TEST_F(IsMkvTypeTest_106, ValidMkvMagicWithAdvanceTrue_106) {
    Exiv2::byte mkvMagic[] = {0x1a, 0x45, 0xdf, 0xa3};

    EXPECT_CALL(mockIo, read(_, 4))
        .WillOnce(DoAll(
            SetArrayArgument<0>(mkvMagic, mkvMagic + 4),
            Return(4)));
    EXPECT_CALL(mockIo, error())
        .WillOnce(Return(0));
    EXPECT_CALL(mockIo, eof())
        .WillOnce(Return(false));
    // When advance=true and result=true, seek should NOT be called
    EXPECT_CALL(mockIo, seek(_, _)).Times(0);

    bool result = Exiv2::isMkvType(mockIo, true);
    EXPECT_TRUE(result);
}

// Test: Valid MKV magic bytes with advance=false should return true and seek back to beginning
TEST_F(IsMkvTypeTest_106, ValidMkvMagicWithAdvanceFalse_106) {
    Exiv2::byte mkvMagic[] = {0x1a, 0x45, 0xdf, 0xa3};

    EXPECT_CALL(mockIo, read(_, 4))
        .WillOnce(DoAll(
            SetArrayArgument<0>(mkvMagic, mkvMagic + 4),
            Return(4)));
    EXPECT_CALL(mockIo, error())
        .WillOnce(Return(0));
    EXPECT_CALL(mockIo, eof())
        .WillOnce(Return(false));
    // When advance=false, seek should be called to go back to beginning
    EXPECT_CALL(mockIo, seek(0, Exiv2::BasicIo::beg))
        .WillOnce(Return(0));

    bool result = Exiv2::isMkvType(mockIo, false);
    EXPECT_TRUE(result);
}

// Test: Invalid magic bytes with advance=true should return false and seek back
TEST_F(IsMkvTypeTest_106, InvalidMagicBytesWithAdvanceTrue_106) {
    Exiv2::byte invalidMagic[] = {0x00, 0x00, 0x00, 0x00};

    EXPECT_CALL(mockIo, read(_, 4))
        .WillOnce(DoAll(
            SetArrayArgument<0>(invalidMagic, invalidMagic + 4),
            Return(4)));
    EXPECT_CALL(mockIo, error())
        .WillOnce(Return(0));
    EXPECT_CALL(mockIo, eof())
        .WillOnce(Return(false));
    // When result=false, seek is called regardless of advance
    EXPECT_CALL(mockIo, seek(0, Exiv2::BasicIo::beg))
        .WillOnce(Return(0));

    bool result = Exiv2::isMkvType(mockIo, true);
    EXPECT_FALSE(result);
}

// Test: Invalid magic bytes with advance=false should return false and seek back
TEST_F(IsMkvTypeTest_106, InvalidMagicBytesWithAdvanceFalse_106) {
    Exiv2::byte invalidMagic[] = {0xFF, 0xFF, 0xFF, 0xFF};

    EXPECT_CALL(mockIo, read(_, 4))
        .WillOnce(DoAll(
            SetArrayArgument<0>(invalidMagic, invalidMagic + 4),
            Return(4)));
    EXPECT_CALL(mockIo, error())
        .WillOnce(Return(0));
    EXPECT_CALL(mockIo, eof())
        .WillOnce(Return(false));
    EXPECT_CALL(mockIo, seek(0, Exiv2::BasicIo::beg))
        .WillOnce(Return(0));

    bool result = Exiv2::isMkvType(mockIo, false);
    EXPECT_FALSE(result);
}

// Test: IO error during read should return false
TEST_F(IsMkvTypeTest_106, IoErrorReturnsfalse_106) {
    Exiv2::byte anyData[] = {0x1a, 0x45, 0xdf, 0xa3};

    EXPECT_CALL(mockIo, read(_, 4))
        .WillOnce(DoAll(
            SetArrayArgument<0>(anyData, anyData + 4),
            Return(4)));
    EXPECT_CALL(mockIo, error())
        .WillOnce(Return(1));  // error occurred

    bool result = Exiv2::isMkvType(mockIo, true);
    EXPECT_FALSE(result);
}

// Test: EOF during read should return false
TEST_F(IsMkvTypeTest_106, EofReturnsfalse_106) {
    Exiv2::byte anyData[] = {0x1a, 0x45, 0xdf, 0xa3};

    EXPECT_CALL(mockIo, read(_, 4))
        .WillOnce(DoAll(
            SetArrayArgument<0>(anyData, anyData + 4),
            Return(2)));
    EXPECT_CALL(mockIo, error())
        .WillOnce(Return(0));
    EXPECT_CALL(mockIo, eof())
        .WillOnce(Return(true));  // eof occurred

    bool result = Exiv2::isMkvType(mockIo, true);
    EXPECT_FALSE(result);
}

// Test: First byte wrong
TEST_F(IsMkvTypeTest_106, FirstByteWrong_106) {
    Exiv2::byte data[] = {0x00, 0x45, 0xdf, 0xa3};

    EXPECT_CALL(mockIo, read(_, 4))
        .WillOnce(DoAll(
            SetArrayArgument<0>(data, data + 4),
            Return(4)));
    EXPECT_CALL(mockIo, error())
        .WillOnce(Return(0));
    EXPECT_CALL(mockIo, eof())
        .WillOnce(Return(false));
    EXPECT_CALL(mockIo, seek(0, Exiv2::BasicIo::beg))
        .WillOnce(Return(0));

    bool result = Exiv2::isMkvType(mockIo, true);
    EXPECT_FALSE(result);
}

// Test: Second byte wrong
TEST_F(IsMkvTypeTest_106, SecondByteWrong_106) {
    Exiv2::byte data[] = {0x1a, 0x00, 0xdf, 0xa3};

    EXPECT_CALL(mockIo, read(_, 4))
        .WillOnce(DoAll(
            SetArrayArgument<0>(data, data + 4),
            Return(4)));
    EXPECT_CALL(mockIo, error())
        .WillOnce(Return(0));
    EXPECT_CALL(mockIo, eof())
        .WillOnce(Return(false));
    EXPECT_CALL(mockIo, seek(0, Exiv2::BasicIo::beg))
        .WillOnce(Return(0));

    bool result = Exiv2::isMkvType(mockIo, true);
    EXPECT_FALSE(result);
}

// Test: Third byte wrong
TEST_F(IsMkvTypeTest_106, ThirdByteWrong_106) {
    Exiv2::byte data[] = {0x1a, 0x45, 0x00, 0xa3};

    EXPECT_CALL(mockIo, read(_, 4))
        .WillOnce(DoAll(
            SetArrayArgument<0>(data, data + 4),
            Return(4)));
    EXPECT_CALL(mockIo, error())
        .WillOnce(Return(0));
    EXPECT_CALL(mockIo, eof())
        .WillOnce(Return(false));
    EXPECT_CALL(mockIo, seek(0, Exiv2::BasicIo::beg))
        .WillOnce(Return(0));

    bool result = Exiv2::isMkvType(mockIo, true);
    EXPECT_FALSE(result);
}

// Test: Fourth byte wrong
TEST_F(IsMkvTypeTest_106, FourthByteWrong_106) {
    Exiv2::byte data[] = {0x1a, 0x45, 0xdf, 0x00};

    EXPECT_CALL(mockIo, read(_, 4))
        .WillOnce(DoAll(
            SetArrayArgument<0>(data, data + 4),
            Return(4)));
    EXPECT_CALL(mockIo, error())
        .WillOnce(Return(0));
    EXPECT_CALL(mockIo, eof())
        .WillOnce(Return(false));
    EXPECT_CALL(mockIo, seek(0, Exiv2::BasicIo::beg))
        .WillOnce(Return(0));

    bool result = Exiv2::isMkvType(mockIo, true);
    EXPECT_FALSE(result);
}

// Test: All bytes wrong
TEST_F(IsMkvTypeTest_106, AllBytesWrong_106) {
    Exiv2::byte data[] = {0x52, 0x49, 0x46, 0x46}; // "RIFF" header (not MKV)

    EXPECT_CALL(mockIo, read(_, 4))
        .WillOnce(DoAll(
            SetArrayArgument<0>(data, data + 4),
            Return(4)));
    EXPECT_CALL(mockIo, error())
        .WillOnce(Return(0));
    EXPECT_CALL(mockIo, eof())
        .WillOnce(Return(false));
    EXPECT_CALL(mockIo, seek(0, Exiv2::BasicIo::beg))
        .WillOnce(Return(0));

    bool result = Exiv2::isMkvType(mockIo, false);
    EXPECT_FALSE(result);
}

// Test: Both error and eof true should return false early
TEST_F(IsMkvTypeTest_106, BothErrorAndEof_106) {
    Exiv2::byte anyData[] = {0x1a, 0x45, 0xdf, 0xa3};

    EXPECT_CALL(mockIo, read(_, 4))
        .WillOnce(DoAll(
            SetArrayArgument<0>(anyData, anyData + 4),
            Return(0)));
    EXPECT_CALL(mockIo, error())
        .WillOnce(Return(1));

    bool result = Exiv2::isMkvType(mockIo, true);
    EXPECT_FALSE(result);
}

// Test using MemIo with valid MKV data
TEST(IsMkvTypeMemIoTest_106, ValidMkvWithMemIoAdvanceTrue_106) {
    Exiv2::byte mkvData[] = {0x1a, 0x45, 0xdf, 0xa3, 0x01, 0x02, 0x03, 0x04};
    Exiv2::MemIo memIo(mkvData, sizeof(mkvData));

    bool result = Exiv2::isMkvType(memIo, true);
    EXPECT_TRUE(result);
    // After advance=true and result=true, position should be at 4
    EXPECT_EQ(memIo.tell(), 4u);
}

// Test using MemIo with valid MKV data, advance=false
TEST(IsMkvTypeMemIoTest_106, ValidMkvWithMemIoAdvanceFalse_106) {
    Exiv2::byte mkvData[] = {0x1a, 0x45, 0xdf, 0xa3, 0x01, 0x02, 0x03, 0x04};
    Exiv2::MemIo memIo(mkvData, sizeof(mkvData));

    bool result = Exiv2::isMkvType(memIo, false);
    EXPECT_TRUE(result);
    // After advance=false, position should be reset to 0
    EXPECT_EQ(memIo.tell(), 0u);
}

// Test using MemIo with invalid data
TEST(IsMkvTypeMemIoTest_106, InvalidDataWithMemIo_106) {
    Exiv2::byte invalidData[] = {0x00, 0x01, 0x02, 0x03};
    Exiv2::MemIo memIo(invalidData, sizeof(invalidData));

    bool result = Exiv2::isMkvType(memIo, true);
    EXPECT_FALSE(result);
    // Position should be reset to 0 since result is false
    EXPECT_EQ(memIo.tell(), 0u);
}

// Test using MemIo with empty data (less than 4 bytes)
TEST(IsMkvTypeMemIoTest_106, EmptyMemIo_106) {
    Exiv2::MemIo memIo;

    bool result = Exiv2::isMkvType(memIo, true);
    EXPECT_FALSE(result);
}

// Test using MemIo with exactly 4 bytes of valid MKV magic
TEST(IsMkvTypeMemIoTest_106, ExactlyFourBytesValid_106) {
    Exiv2::byte mkvData[] = {0x1a, 0x45, 0xdf, 0xa3};
    Exiv2::MemIo memIo(mkvData, sizeof(mkvData));

    bool result = Exiv2::isMkvType(memIo, true);
    EXPECT_TRUE(result);
}

// Test using MemIo with fewer than 4 bytes
TEST(IsMkvTypeMemIoTest_106, FewerThanFourBytes_106) {
    Exiv2::byte data[] = {0x1a, 0x45, 0xdf};
    Exiv2::MemIo memIo(data, sizeof(data));

    bool result = Exiv2::isMkvType(memIo, true);
    EXPECT_FALSE(result);
}
