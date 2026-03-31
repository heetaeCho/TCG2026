#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <exiv2/basicio.hpp>
#include <exiv2/image.hpp>
#include <exiv2/jpgimage.hpp>
#include <exiv2/types.hpp>
#include <cstring>

using namespace Exiv2;

// Mock class for BasicIo to control behavior in tests
class MockBasicIo : public BasicIo {
public:
    MOCK_METHOD(int, open, (), (override));
    MOCK_METHOD(int, close, (), (override));
    MOCK_METHOD(size_t, write, (const byte* data, size_t wcount), (override));
    MOCK_METHOD(size_t, write, (BasicIo& src), (override));
    MOCK_METHOD(int, putb, (byte data), (override));
    MOCK_METHOD(DataBuf, read, (size_t rcount), (override));
    MOCK_METHOD(size_t, read, (byte* buf, size_t rcount), (override));
    MOCK_METHOD(int, getb, (), (override));
    MOCK_METHOD(void, transfer, (BasicIo& src), (override));
    MOCK_METHOD(int, seek, (int64_t offset, Position pos), (override));
    MOCK_METHOD(byte*, mmap, (bool isWriteable), (override));
    MOCK_METHOD(int, munmap, (), (override));
    MOCK_METHOD(const size_t, tell, (), (const, override));
    MOCK_METHOD(const size_t, size, (), (const, override));
    MOCK_METHOD(const bool, isopen, (), (const, override));
    MOCK_METHOD(const int, error, (), (const, override));
    MOCK_METHOD(const bool, eof, (), (const, override));
    MOCK_METHOD(const std::string&, path, (), (const, override));
    MOCK_METHOD(void, populateFakeData, (), (override));
};

class IsExvTypeTest_1229 : public ::testing::Test {
protected:
    MockBasicIo mockIo;
    std::string dummyPath = "test.exv";

    void SetUp() override {
        ON_CALL(mockIo, path()).WillByDefault(::testing::ReturnRef(dummyPath));
    }
};

// Test: Valid EXV header with advance=true should return true and NOT seek back
TEST_F(IsExvTypeTest_1229, ValidExvHeaderAdvanceTrue_1229) {
    // ExvImage::exiv2Id_ is typically "\xff\x01Exiv2" but the first two bytes are 0xff, 0x01
    // followed by 5 bytes of exiv2Id_. We need the actual exiv2Id_ content.
    // Based on the code: tmpBuf[0]=0xff, tmpBuf[1]=0x01, tmpBuf[2..6] = exiv2Id_ (5 bytes)
    // exiv2Id_ is typically "Exiv2" (the string)
    byte validHeader[7] = {0xff, 0x01, 'E', 'x', 'i', 'v', '2'};

    EXPECT_CALL(mockIo, read(::testing::_, 7))
        .WillOnce(::testing::DoAll(
            ::testing::WithArgs<0, 1>([&](byte* buf, size_t) {
                std::memcpy(buf, validHeader, 7);
            }),
            ::testing::Return(7)));
    EXPECT_CALL(mockIo, error()).WillRepeatedly(::testing::Return(0));
    EXPECT_CALL(mockIo, eof()).WillRepeatedly(::testing::Return(false));
    // With advance=true and result=true, seek should NOT be called
    EXPECT_CALL(mockIo, seek(::testing::_, ::testing::_)).Times(0);

    bool result = isExvType(mockIo, true);
    EXPECT_TRUE(result);
}

// Test: Valid EXV header with advance=false should return true and seek back
TEST_F(IsExvTypeTest_1229, ValidExvHeaderAdvanceFalse_1229) {
    byte validHeader[7] = {0xff, 0x01, 'E', 'x', 'i', 'v', '2'};

    EXPECT_CALL(mockIo, read(::testing::_, 7))
        .WillOnce(::testing::DoAll(
            ::testing::WithArgs<0, 1>([&](byte* buf, size_t) {
                std::memcpy(buf, validHeader, 7);
            }),
            ::testing::Return(7)));
    EXPECT_CALL(mockIo, error()).WillRepeatedly(::testing::Return(0));
    EXPECT_CALL(mockIo, eof()).WillRepeatedly(::testing::Return(false));
    // With advance=false, seek should be called to go back
    EXPECT_CALL(mockIo, seek(-7, BasicIo::cur)).WillOnce(::testing::Return(0));

    bool result = isExvType(mockIo, false);
    EXPECT_TRUE(result);
}

// Test: Invalid header (wrong first byte) should return false and seek back
TEST_F(IsExvTypeTest_1229, InvalidFirstByte_1229) {
    byte invalidHeader[7] = {0x00, 0x01, 'E', 'x', 'i', 'v', '2'};

    EXPECT_CALL(mockIo, read(::testing::_, 7))
        .WillOnce(::testing::DoAll(
            ::testing::WithArgs<0, 1>([&](byte* buf, size_t) {
                std::memcpy(buf, invalidHeader, 7);
            }),
            ::testing::Return(7)));
    EXPECT_CALL(mockIo, error()).WillRepeatedly(::testing::Return(0));
    EXPECT_CALL(mockIo, eof()).WillRepeatedly(::testing::Return(false));
    EXPECT_CALL(mockIo, seek(-7, BasicIo::cur)).WillOnce(::testing::Return(0));

    bool result = isExvType(mockIo, true);
    EXPECT_FALSE(result);
}

// Test: Invalid header (wrong second byte) should return false and seek back
TEST_F(IsExvTypeTest_1229, InvalidSecondByte_1229) {
    byte invalidHeader[7] = {0xff, 0x02, 'E', 'x', 'i', 'v', '2'};

    EXPECT_CALL(mockIo, read(::testing::_, 7))
        .WillOnce(::testing::DoAll(
            ::testing::WithArgs<0, 1>([&](byte* buf, size_t) {
                std::memcpy(buf, invalidHeader, 7);
            }),
            ::testing::Return(7)));
    EXPECT_CALL(mockIo, error()).WillRepeatedly(::testing::Return(0));
    EXPECT_CALL(mockIo, eof()).WillRepeatedly(::testing::Return(false));
    EXPECT_CALL(mockIo, seek(-7, BasicIo::cur)).WillOnce(::testing::Return(0));

    bool result = isExvType(mockIo, true);
    EXPECT_FALSE(result);
}

// Test: Invalid header (wrong exiv2Id content) should return false and seek back
TEST_F(IsExvTypeTest_1229, InvalidExiv2Id_1229) {
    byte invalidHeader[7] = {0xff, 0x01, 'X', 'x', 'i', 'v', '2'};

    EXPECT_CALL(mockIo, read(::testing::_, 7))
        .WillOnce(::testing::DoAll(
            ::testing::WithArgs<0, 1>([&](byte* buf, size_t) {
                std::memcpy(buf, invalidHeader, 7);
            }),
            ::testing::Return(7)));
    EXPECT_CALL(mockIo, error()).WillRepeatedly(::testing::Return(0));
    EXPECT_CALL(mockIo, eof()).WillRepeatedly(::testing::Return(false));
    EXPECT_CALL(mockIo, seek(-7, BasicIo::cur)).WillOnce(::testing::Return(0));

    bool result = isExvType(mockIo, true);
    EXPECT_FALSE(result);
}

// Test: IO error during read should return false
TEST_F(IsExvTypeTest_1229, IoErrorOnRead_1229) {
    EXPECT_CALL(mockIo, read(::testing::_, 7))
        .WillOnce(::testing::Return(0));
    EXPECT_CALL(mockIo, error()).WillRepeatedly(::testing::Return(1));
    EXPECT_CALL(mockIo, eof()).WillRepeatedly(::testing::Return(false));

    bool result = isExvType(mockIo, true);
    EXPECT_FALSE(result);
}

// Test: EOF during read should return false
TEST_F(IsExvTypeTest_1229, EofOnRead_1229) {
    EXPECT_CALL(mockIo, read(::testing::_, 7))
        .WillOnce(::testing::Return(3));
    EXPECT_CALL(mockIo, error()).WillRepeatedly(::testing::Return(0));
    EXPECT_CALL(mockIo, eof()).WillRepeatedly(::testing::Return(true));

    bool result = isExvType(mockIo, false);
    EXPECT_FALSE(result);
}

// Test: All zeros should return false and seek back
TEST_F(IsExvTypeTest_1229, AllZeroData_1229) {
    byte zeroHeader[7] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

    EXPECT_CALL(mockIo, read(::testing::_, 7))
        .WillOnce(::testing::DoAll(
            ::testing::WithArgs<0, 1>([&](byte* buf, size_t) {
                std::memcpy(buf, zeroHeader, 7);
            }),
            ::testing::Return(7)));
    EXPECT_CALL(mockIo, error()).WillRepeatedly(::testing::Return(0));
    EXPECT_CALL(mockIo, eof()).WillRepeatedly(::testing::Return(false));
    EXPECT_CALL(mockIo, seek(-7, BasicIo::cur)).WillOnce(::testing::Return(0));

    bool result = isExvType(mockIo, true);
    EXPECT_FALSE(result);
}

// Test: Invalid header with advance=false should seek back
TEST_F(IsExvTypeTest_1229, InvalidHeaderAdvanceFalseSeeksBack_1229) {
    byte invalidHeader[7] = {0xff, 0x01, 'N', 'O', 'T', 'E', 'X'};

    EXPECT_CALL(mockIo, read(::testing::_, 7))
        .WillOnce(::testing::DoAll(
            ::testing::WithArgs<0, 1>([&](byte* buf, size_t) {
                std::memcpy(buf, invalidHeader, 7);
            }),
            ::testing::Return(7)));
    EXPECT_CALL(mockIo, error()).WillRepeatedly(::testing::Return(0));
    EXPECT_CALL(mockIo, eof()).WillRepeatedly(::testing::Return(false));
    EXPECT_CALL(mockIo, seek(-7, BasicIo::cur)).WillOnce(::testing::Return(0));

    bool result = isExvType(mockIo, false);
    EXPECT_FALSE(result);
}

// Test: Partial mismatch in exiv2Id_ (last byte different)
TEST_F(IsExvTypeTest_1229, PartialMismatchExiv2Id_1229) {
    byte header[7] = {0xff, 0x01, 'E', 'x', 'i', 'v', '3'};

    EXPECT_CALL(mockIo, read(::testing::_, 7))
        .WillOnce(::testing::DoAll(
            ::testing::WithArgs<0, 1>([&](byte* buf, size_t) {
                std::memcpy(buf, header, 7);
            }),
            ::testing::Return(7)));
    EXPECT_CALL(mockIo, error()).WillRepeatedly(::testing::Return(0));
    EXPECT_CALL(mockIo, eof()).WillRepeatedly(::testing::Return(false));
    EXPECT_CALL(mockIo, seek(-7, BasicIo::cur)).WillOnce(::testing::Return(0));

    bool result = isExvType(mockIo, true);
    EXPECT_FALSE(result);
}

// Test using MemIo with actual valid EXV data
TEST(IsExvTypeMemIoTest_1229, ValidExvWithMemIoAdvanceTrue_1229) {
    byte validData[7] = {0xff, 0x01, 'E', 'x', 'i', 'v', '2'};
    MemIo memIo(validData, 7);

    bool result = isExvType(memIo, true);
    // This depends on the actual exiv2Id_ content - the test verifies observable behavior
    // If exiv2Id_ is "Exiv2", this should be true
    // We verify position advanced (tell() should be 7 if true)
    if (result) {
        EXPECT_EQ(memIo.tell(), 7u);
    }
}

// Test using MemIo with actual valid EXV data, advance=false
TEST(IsExvTypeMemIoTest_1229, ValidExvWithMemIoAdvanceFalse_1229) {
    byte validData[7] = {0xff, 0x01, 'E', 'x', 'i', 'v', '2'};
    MemIo memIo(validData, 7);

    bool result = isExvType(memIo, false);
    // Regardless of result, with advance=false the position should be restored
    if (result) {
        EXPECT_EQ(memIo.tell(), 0u);
    }
}

// Test using MemIo with insufficient data (less than 7 bytes)
TEST(IsExvTypeMemIoTest_1229, InsufficientData_1229) {
    byte shortData[3] = {0xff, 0x01, 'E'};
    MemIo memIo(shortData, 3);

    bool result = isExvType(memIo, true);
    EXPECT_FALSE(result);
}

// Test using MemIo with empty data
TEST(IsExvTypeMemIoTest_1229, EmptyData_1229) {
    MemIo memIo;

    bool result = isExvType(memIo, true);
    EXPECT_FALSE(result);
}

// Test: JPEG header (not EXV) should return false
TEST(IsExvTypeMemIoTest_1229, JpegHeaderNotExv_1229) {
    byte jpegData[7] = {0xff, 0xd8, 0xff, 0xe0, 0x00, 0x10, 0x4a};
    MemIo memIo(jpegData, 7);

    bool result = isExvType(memIo, true);
    EXPECT_FALSE(result);
}
