#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <exiv2/basicio.hpp>
#include <exiv2/bmffimage.hpp>
#include <cstring>

using namespace Exiv2;
using ::testing::_;
using ::testing::Return;
using ::testing::DoAll;
using ::testing::SetArrayArgument;
using ::testing::Invoke;

// Mock class for BasicIo
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

class IsBmffTypeTest_1204 : public ::testing::Test {
protected:
    MockBasicIo mockIo;
};

// Test: ftyp box is recognized as BMFF type with advance=false
TEST_F(IsBmffTypeTest_1204, FtypBoxRecognizedAdvanceFalse_1204) {
    // Construct a valid ftyp header: first 4 bytes are size, next 4 are 'ftyp', then 4 more bytes
    byte ftypBuf[12] = {0x00, 0x00, 0x00, 0x18, 'f', 't', 'y', 'p', 'h', 'e', 'i', 'c'};

    EXPECT_CALL(mockIo, read(_, 12))
        .WillOnce(DoAll(
            Invoke([&ftypBuf](byte* buf, size_t rcount) {
                std::memcpy(buf, ftypBuf, 12);
            }),
            Return(12)));
    EXPECT_CALL(mockIo, error()).WillRepeatedly(Return(0));
    EXPECT_CALL(mockIo, eof()).WillRepeatedly(Return(false));
    // advance=false, so seek should be called to reset
    EXPECT_CALL(mockIo, seek(0, BasicIo::beg)).WillOnce(Return(0));

    bool result = isBmffType(mockIo, false);
    EXPECT_TRUE(result);
}

// Test: ftyp box is recognized as BMFF type with advance=true
TEST_F(IsBmffTypeTest_1204, FtypBoxRecognizedAdvanceTrue_1204) {
    byte ftypBuf[12] = {0x00, 0x00, 0x00, 0x18, 'f', 't', 'y', 'p', 'h', 'e', 'i', 'c'};

    EXPECT_CALL(mockIo, read(_, 12))
        .WillOnce(DoAll(
            Invoke([&ftypBuf](byte* buf, size_t rcount) {
                std::memcpy(buf, ftypBuf, 12);
            }),
            Return(12)));
    EXPECT_CALL(mockIo, error()).WillRepeatedly(Return(0));
    EXPECT_CALL(mockIo, eof()).WillRepeatedly(Return(false));
    // advance=true and matched, so seek should NOT be called
    EXPECT_CALL(mockIo, seek(_, _)).Times(0);

    bool result = isBmffType(mockIo, true);
    EXPECT_TRUE(result);
}

// Test: JXL box is recognized as BMFF type with advance=false
TEST_F(IsBmffTypeTest_1204, JxlBoxRecognizedAdvanceFalse_1204) {
    byte jxlBuf[12] = {0x00, 0x00, 0x00, 0x0C, 'J', 'X', 'L', ' ', 0x0D, 0x0A, 0x87, 0x0A};

    EXPECT_CALL(mockIo, read(_, 12))
        .WillOnce(DoAll(
            Invoke([&jxlBuf](byte* buf, size_t rcount) {
                std::memcpy(buf, jxlBuf, 12);
            }),
            Return(12)));
    EXPECT_CALL(mockIo, error()).WillRepeatedly(Return(0));
    EXPECT_CALL(mockIo, eof()).WillRepeatedly(Return(false));
    EXPECT_CALL(mockIo, seek(0, BasicIo::beg)).WillOnce(Return(0));

    bool result = isBmffType(mockIo, false);
    EXPECT_TRUE(result);
}

// Test: JXL box is recognized as BMFF type with advance=true
TEST_F(IsBmffTypeTest_1204, JxlBoxRecognizedAdvanceTrue_1204) {
    byte jxlBuf[12] = {0x00, 0x00, 0x00, 0x0C, 'J', 'X', 'L', ' ', 0x0D, 0x0A, 0x87, 0x0A};

    EXPECT_CALL(mockIo, read(_, 12))
        .WillOnce(DoAll(
            Invoke([&jxlBuf](byte* buf, size_t rcount) {
                std::memcpy(buf, jxlBuf, 12);
            }),
            Return(12)));
    EXPECT_CALL(mockIo, error()).WillRepeatedly(Return(0));
    EXPECT_CALL(mockIo, eof()).WillRepeatedly(Return(false));
    EXPECT_CALL(mockIo, seek(_, _)).Times(0);

    bool result = isBmffType(mockIo, true);
    EXPECT_TRUE(result);
}

// Test: Non-BMFF data returns false
TEST_F(IsBmffTypeTest_1204, NonBmffDataReturnsFalse_1204) {
    byte randomBuf[12] = {0x00, 0x00, 0x00, 0x00, 'P', 'N', 'G', '\r', 0x00, 0x00, 0x00, 0x00};

    EXPECT_CALL(mockIo, read(_, 12))
        .WillOnce(DoAll(
            Invoke([&randomBuf](byte* buf, size_t rcount) {
                std::memcpy(buf, randomBuf, 12);
            }),
            Return(12)));
    EXPECT_CALL(mockIo, error()).WillRepeatedly(Return(0));
    EXPECT_CALL(mockIo, eof()).WillRepeatedly(Return(false));
    // Not matched, so seek should be called regardless of advance
    EXPECT_CALL(mockIo, seek(0, BasicIo::beg)).WillOnce(Return(0));

    bool result = isBmffType(mockIo, true);
    EXPECT_FALSE(result);
}

// Test: Non-BMFF data returns false with advance=false
TEST_F(IsBmffTypeTest_1204, NonBmffDataAdvanceFalseReturnsFalse_1204) {
    byte randomBuf[12] = {0x89, 0x50, 0x4E, 0x47, 0x0D, 0x0A, 0x1A, 0x0A, 0x00, 0x00, 0x00, 0x0D};

    EXPECT_CALL(mockIo, read(_, 12))
        .WillOnce(DoAll(
            Invoke([&randomBuf](byte* buf, size_t rcount) {
                std::memcpy(buf, randomBuf, 12);
            }),
            Return(12)));
    EXPECT_CALL(mockIo, error()).WillRepeatedly(Return(0));
    EXPECT_CALL(mockIo, eof()).WillRepeatedly(Return(false));
    EXPECT_CALL(mockIo, seek(0, BasicIo::beg)).WillOnce(Return(0));

    bool result = isBmffType(mockIo, false);
    EXPECT_FALSE(result);
}

// Test: IO error during read returns false
TEST_F(IsBmffTypeTest_1204, IoErrorReturnsFalse_1204) {
    byte dummyBuf[12] = {};

    EXPECT_CALL(mockIo, read(_, 12))
        .WillOnce(DoAll(
            Invoke([&dummyBuf](byte* buf, size_t rcount) {
                std::memcpy(buf, dummyBuf, 12);
            }),
            Return(0)));
    EXPECT_CALL(mockIo, error()).WillRepeatedly(Return(1));  // Indicate error
    EXPECT_CALL(mockIo, eof()).WillRepeatedly(Return(false));

    bool result = isBmffType(mockIo, true);
    EXPECT_FALSE(result);
}

// Test: EOF during read returns false
TEST_F(IsBmffTypeTest_1204, EofDuringReadReturnsFalse_1204) {
    byte dummyBuf[12] = {};

    EXPECT_CALL(mockIo, read(_, 12))
        .WillOnce(DoAll(
            Invoke([&dummyBuf](byte* buf, size_t rcount) {
                std::memcpy(buf, dummyBuf, 12);
            }),
            Return(0)));
    EXPECT_CALL(mockIo, error()).WillRepeatedly(Return(0));
    EXPECT_CALL(mockIo, eof()).WillRepeatedly(Return(true));  // Indicate EOF

    bool result = isBmffType(mockIo, false);
    EXPECT_FALSE(result);
}

// Test: All zeros data returns false
TEST_F(IsBmffTypeTest_1204, AllZerosReturnsFalse_1204) {
    byte zeroBuf[12] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    EXPECT_CALL(mockIo, read(_, 12))
        .WillOnce(DoAll(
            Invoke([&zeroBuf](byte* buf, size_t rcount) {
                std::memcpy(buf, zeroBuf, 12);
            }),
            Return(12)));
    EXPECT_CALL(mockIo, error()).WillRepeatedly(Return(0));
    EXPECT_CALL(mockIo, eof()).WillRepeatedly(Return(false));
    EXPECT_CALL(mockIo, seek(0, BasicIo::beg)).WillOnce(Return(0));

    bool result = isBmffType(mockIo, true);
    EXPECT_FALSE(result);
}

// Test: Partial ftyp match (e.g., 'fty' but not 'ftyp') returns false
TEST_F(IsBmffTypeTest_1204, PartialFtypMatchReturnsFalse_1204) {
    byte partialBuf[12] = {0x00, 0x00, 0x00, 0x18, 'f', 't', 'y', 'x', 'h', 'e', 'i', 'c'};

    EXPECT_CALL(mockIo, read(_, 12))
        .WillOnce(DoAll(
            Invoke([&partialBuf](byte* buf, size_t rcount) {
                std::memcpy(buf, partialBuf, 12);
            }),
            Return(12)));
    EXPECT_CALL(mockIo, error()).WillRepeatedly(Return(0));
    EXPECT_CALL(mockIo, eof()).WillRepeatedly(Return(false));
    EXPECT_CALL(mockIo, seek(0, BasicIo::beg)).WillOnce(Return(0));

    bool result = isBmffType(mockIo, true);
    EXPECT_FALSE(result);
}

// Test: Partial JXL match (e.g., 'JXL!' instead of 'JXL ') returns false
TEST_F(IsBmffTypeTest_1204, PartialJxlMatchReturnsFalse_1204) {
    byte partialJxl[12] = {0x00, 0x00, 0x00, 0x0C, 'J', 'X', 'L', '!', 0x0D, 0x0A, 0x87, 0x0A};

    EXPECT_CALL(mockIo, read(_, 12))
        .WillOnce(DoAll(
            Invoke([&partialJxl](byte* buf, size_t rcount) {
                std::memcpy(buf, partialJxl, 12);
            }),
            Return(12)));
    EXPECT_CALL(mockIo, error()).WillRepeatedly(Return(0));
    EXPECT_CALL(mockIo, eof()).WillRepeatedly(Return(false));
    EXPECT_CALL(mockIo, seek(0, BasicIo::beg)).WillOnce(Return(0));

    bool result = isBmffType(mockIo, false);
    EXPECT_FALSE(result);
}

// Test: Both error and eof returns false
TEST_F(IsBmffTypeTest_1204, BothErrorAndEofReturnsFalse_1204) {
    byte dummyBuf[12] = {};

    EXPECT_CALL(mockIo, read(_, 12))
        .WillOnce(DoAll(
            Invoke([&dummyBuf](byte* buf, size_t rcount) {
                std::memcpy(buf, dummyBuf, 12);
            }),
            Return(0)));
    EXPECT_CALL(mockIo, error()).WillRepeatedly(Return(1));
    EXPECT_CALL(mockIo, eof()).WillRepeatedly(Return(true));

    bool result = isBmffType(mockIo, true);
    EXPECT_FALSE(result);
}

// Test: Case sensitivity - lowercase 'jxl ' should not match
TEST_F(IsBmffTypeTest_1204, LowercaseJxlDoesNotMatch_1204) {
    byte lowercaseJxl[12] = {0x00, 0x00, 0x00, 0x0C, 'j', 'x', 'l', ' ', 0x0D, 0x0A, 0x87, 0x0A};

    EXPECT_CALL(mockIo, read(_, 12))
        .WillOnce(DoAll(
            Invoke([&lowercaseJxl](byte* buf, size_t rcount) {
                std::memcpy(buf, lowercaseJxl, 12);
            }),
            Return(12)));
    EXPECT_CALL(mockIo, error()).WillRepeatedly(Return(0));
    EXPECT_CALL(mockIo, eof()).WillRepeatedly(Return(false));
    EXPECT_CALL(mockIo, seek(0, BasicIo::beg)).WillOnce(Return(0));

    bool result = isBmffType(mockIo, true);
    EXPECT_FALSE(result);
}

// Test: Case sensitivity - uppercase 'FTYP' should not match
TEST_F(IsBmffTypeTest_1204, UppercaseFtypDoesNotMatch_1204) {
    byte upperFtyp[12] = {0x00, 0x00, 0x00, 0x18, 'F', 'T', 'Y', 'P', 'h', 'e', 'i', 'c'};

    EXPECT_CALL(mockIo, read(_, 12))
        .WillOnce(DoAll(
            Invoke([&upperFtyp](byte* buf, size_t rcount) {
                std::memcpy(buf, upperFtyp, 12);
            }),
            Return(12)));
    EXPECT_CALL(mockIo, error()).WillRepeatedly(Return(0));
    EXPECT_CALL(mockIo, eof()).WillRepeatedly(Return(false));
    EXPECT_CALL(mockIo, seek(0, BasicIo::beg)).WillOnce(Return(0));

    bool result = isBmffType(mockIo, true);
    EXPECT_FALSE(result);
}

// Test: ftyp with various brand codes (avif)
TEST_F(IsBmffTypeTest_1204, FtypAvifBrandRecognized_1204) {
    byte avifBuf[12] = {0x00, 0x00, 0x00, 0x1C, 'f', 't', 'y', 'p', 'a', 'v', 'i', 'f'};

    EXPECT_CALL(mockIo, read(_, 12))
        .WillOnce(DoAll(
            Invoke([&avifBuf](byte* buf, size_t rcount) {
                std::memcpy(buf, avifBuf, 12);
            }),
            Return(12)));
    EXPECT_CALL(mockIo, error()).WillRepeatedly(Return(0));
    EXPECT_CALL(mockIo, eof()).WillRepeatedly(Return(false));
    EXPECT_CALL(mockIo, seek(_, _)).Times(0);

    bool result = isBmffType(mockIo, true);
    EXPECT_TRUE(result);
}

// Test: Seek is called when advance=true but not matched
TEST_F(IsBmffTypeTest_1204, SeekCalledWhenAdvanceTrueButNotMatched_1204) {
    byte notBmff[12] = {0xFF, 0xD8, 0xFF, 0xE0, 0x00, 0x10, 'J', 'F', 'I', 'F', 0x00, 0x01};

    EXPECT_CALL(mockIo, read(_, 12))
        .WillOnce(DoAll(
            Invoke([&notBmff](byte* buf, size_t rcount) {
                std::memcpy(buf, notBmff, 12);
            }),
            Return(12)));
    EXPECT_CALL(mockIo, error()).WillRepeatedly(Return(0));
    EXPECT_CALL(mockIo, eof()).WillRepeatedly(Return(false));
    EXPECT_CALL(mockIo, seek(0, BasicIo::beg)).Times(1).WillOnce(Return(0));

    bool result = isBmffType(mockIo, true);
    EXPECT_FALSE(result);
}
