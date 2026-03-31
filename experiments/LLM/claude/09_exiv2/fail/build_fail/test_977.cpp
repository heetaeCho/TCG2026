#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <array>
#include <cstdint>

#include "exiv2/basicio.hpp"
#include "exiv2/error.hpp"

// We need to declare isPngType since it's in the Exiv2 namespace
namespace Exiv2 {
bool isPngType(BasicIo& iIo, bool advance);
}

using namespace Exiv2;

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

// PNG signature: {137, 80, 78, 71, 13, 10, 26, 10}
static const std::array<byte, 8> pngSignature = {137, 80, 78, 71, 13, 10, 26, 10};

class IsPngTypeTest_977 : public ::testing::Test {
protected:
    MockBasicIo mockIo;
};

// Test: When initial error() returns true, should throw kerInputDataReadFailed
TEST_F(IsPngTypeTest_977, ThrowsWhenInitialErrorIsTrue_977) {
    EXPECT_CALL(mockIo, error())
        .WillOnce(::testing::Return(1));  // non-zero means error
    EXPECT_CALL(mockIo, eof())
        .WillOnce(::testing::Return(false));

    EXPECT_THROW(isPngType(mockIo, false), Error);
}

// Test: When initial eof() returns true, should throw kerInputDataReadFailed
TEST_F(IsPngTypeTest_977, ThrowsWhenInitialEofIsTrue_977) {
    EXPECT_CALL(mockIo, error())
        .WillOnce(::testing::Return(0));
    EXPECT_CALL(mockIo, eof())
        .WillOnce(::testing::Return(true));

    EXPECT_THROW(isPngType(mockIo, false), Error);
}

// Test: When both error() and eof() are true initially, should throw
TEST_F(IsPngTypeTest_977, ThrowsWhenBothErrorAndEofAreTrue_977) {
    EXPECT_CALL(mockIo, error())
        .WillOnce(::testing::Return(1));
    EXPECT_CALL(mockIo, eof())
        .WillOnce(::testing::Return(true));

    EXPECT_THROW(isPngType(mockIo, false), Error);
}

// Test: When read causes error, returns false and seeks back
TEST_F(IsPngTypeTest_977, ReturnsFalseWhenReadCausesError_977) {
    // Initial check: no error, no eof
    EXPECT_CALL(mockIo, error())
        .WillOnce(::testing::Return(0))   // initial check
        .WillOnce(::testing::Return(1));  // after read check
    EXPECT_CALL(mockIo, eof())
        .WillOnce(::testing::Return(false))  // initial check
        .WillRepeatedly(::testing::Return(false));  // after read check

    EXPECT_CALL(mockIo, read(::testing::_, 8))
        .WillOnce(::testing::Return(0));  // read fails

    // Since read failed (error after read), it returns false
    // Since !advance || !rc => seeks back
    // advance=false so it will seek back regardless
    // But actually, the condition is checked: after read, if error() || eof() => return false (no seek back for this path)
    
    bool result = isPngType(mockIo, false);
    EXPECT_FALSE(result);
}

// Test: When read causes eof, returns false
TEST_F(IsPngTypeTest_977, ReturnsFalseWhenReadCausesEof_977) {
    EXPECT_CALL(mockIo, error())
        .WillOnce(::testing::Return(0))   // initial check
        .WillOnce(::testing::Return(0));  // after read check
    EXPECT_CALL(mockIo, eof())
        .WillOnce(::testing::Return(false))  // initial check
        .WillOnce(::testing::Return(true));  // after read check

    EXPECT_CALL(mockIo, read(::testing::_, 8))
        .WillOnce(::testing::Return(4));  // partial read

    bool result = isPngType(mockIo, false);
    EXPECT_FALSE(result);
}

// Test: Valid PNG signature with advance=true returns true and does NOT seek back
TEST_F(IsPngTypeTest_977, ReturnsTrueForValidPngWithAdvance_977) {
    EXPECT_CALL(mockIo, error())
        .WillOnce(::testing::Return(0))   // initial check
        .WillOnce(::testing::Return(0));  // after read check
    EXPECT_CALL(mockIo, eof())
        .WillOnce(::testing::Return(false))  // initial check
        .WillOnce(::testing::Return(false)); // after read check

    EXPECT_CALL(mockIo, read(::testing::NotNull(), 8))
        .WillOnce(::testing::Invoke([](byte* buf, size_t rcount) -> size_t {
            std::memcpy(buf, pngSignature.data(), 8);
            return 8;
        }));

    // advance=true and rc=true => should NOT seek back
    EXPECT_CALL(mockIo, seek(::testing::_, ::testing::_))
        .Times(0);

    bool result = isPngType(mockIo, true);
    EXPECT_TRUE(result);
}

// Test: Valid PNG signature with advance=false returns true and seeks back
TEST_F(IsPngTypeTest_977, ReturnsTrueForValidPngWithNoAdvance_977) {
    EXPECT_CALL(mockIo, error())
        .WillOnce(::testing::Return(0))
        .WillOnce(::testing::Return(0));
    EXPECT_CALL(mockIo, eof())
        .WillOnce(::testing::Return(false))
        .WillOnce(::testing::Return(false));

    EXPECT_CALL(mockIo, read(::testing::NotNull(), 8))
        .WillOnce(::testing::Invoke([](byte* buf, size_t rcount) -> size_t {
            std::memcpy(buf, pngSignature.data(), 8);
            return 8;
        }));

    // advance=false => seeks back even though rc=true
    EXPECT_CALL(mockIo, seek(-8, BasicIo::cur))
        .Times(1)
        .WillOnce(::testing::Return(0));

    bool result = isPngType(mockIo, false);
    EXPECT_TRUE(result);
}

// Test: Invalid signature with advance=true returns false and seeks back
TEST_F(IsPngTypeTest_977, ReturnsFalseForInvalidPngWithAdvance_977) {
    EXPECT_CALL(mockIo, error())
        .WillOnce(::testing::Return(0))
        .WillOnce(::testing::Return(0));
    EXPECT_CALL(mockIo, eof())
        .WillOnce(::testing::Return(false))
        .WillOnce(::testing::Return(false));

    EXPECT_CALL(mockIo, read(::testing::NotNull(), 8))
        .WillOnce(::testing::Invoke([](byte* buf, size_t rcount) -> size_t {
            // Fill with invalid data
            std::memset(buf, 0, 8);
            return 8;
        }));

    // !rc => seeks back regardless of advance
    EXPECT_CALL(mockIo, seek(-8, BasicIo::cur))
        .Times(1)
        .WillOnce(::testing::Return(0));

    bool result = isPngType(mockIo, true);
    EXPECT_FALSE(result);
}

// Test: Invalid signature with advance=false returns false and seeks back
TEST_F(IsPngTypeTest_977, ReturnsFalseForInvalidPngWithNoAdvance_977) {
    EXPECT_CALL(mockIo, error())
        .WillOnce(::testing::Return(0))
        .WillOnce(::testing::Return(0));
    EXPECT_CALL(mockIo, eof())
        .WillOnce(::testing::Return(false))
        .WillOnce(::testing::Return(false));

    EXPECT_CALL(mockIo, read(::testing::NotNull(), 8))
        .WillOnce(::testing::Invoke([](byte* buf, size_t rcount) -> size_t {
            // JPEG signature instead
            byte jpegSig[] = {0xFF, 0xD8, 0xFF, 0xE0, 0x00, 0x10, 0x4A, 0x46};
            std::memcpy(buf, jpegSig, 8);
            return 8;
        }));

    EXPECT_CALL(mockIo, seek(-8, BasicIo::cur))
        .Times(1)
        .WillOnce(::testing::Return(0));

    bool result = isPngType(mockIo, false);
    EXPECT_FALSE(result);
}

// Test: Almost valid PNG signature (one byte different) returns false
TEST_F(IsPngTypeTest_977, ReturnsFalseForAlmostValidPng_977) {
    EXPECT_CALL(mockIo, error())
        .WillOnce(::testing::Return(0))
        .WillOnce(::testing::Return(0));
    EXPECT_CALL(mockIo, eof())
        .WillOnce(::testing::Return(false))
        .WillOnce(::testing::Return(false));

    EXPECT_CALL(mockIo, read(::testing::NotNull(), 8))
        .WillOnce(::testing::Invoke([](byte* buf, size_t rcount) -> size_t {
            // Copy valid signature but change last byte
            std::memcpy(buf, pngSignature.data(), 8);
            buf[7] = 0x00;  // Change last byte
            return 8;
        }));

    EXPECT_CALL(mockIo, seek(-8, BasicIo::cur))
        .Times(1)
        .WillOnce(::testing::Return(0));

    bool result = isPngType(mockIo, true);
    EXPECT_FALSE(result);
}

// Test: Almost valid PNG signature (first byte different) returns false
TEST_F(IsPngTypeTest_977, ReturnsFalseForFirstByteDifferent_977) {
    EXPECT_CALL(mockIo, error())
        .WillOnce(::testing::Return(0))
        .WillOnce(::testing::Return(0));
    EXPECT_CALL(mockIo, eof())
        .WillOnce(::testing::Return(false))
        .WillOnce(::testing::Return(false));

    EXPECT_CALL(mockIo, read(::testing::NotNull(), 8))
        .WillOnce(::testing::Invoke([](byte* buf, size_t rcount) -> size_t {
            std::memcpy(buf, pngSignature.data(), 8);
            buf[0] = 138;  // Change first byte (should be 137)
            return 8;
        }));

    EXPECT_CALL(mockIo, seek(-8, BasicIo::cur))
        .Times(1)
        .WillOnce(::testing::Return(0));

    bool result = isPngType(mockIo, true);
    EXPECT_FALSE(result);
}

// Test: All zeros returns false
TEST_F(IsPngTypeTest_977, ReturnsFalseForAllZeros_977) {
    EXPECT_CALL(mockIo, error())
        .WillOnce(::testing::Return(0))
        .WillOnce(::testing::Return(0));
    EXPECT_CALL(mockIo, eof())
        .WillOnce(::testing::Return(false))
        .WillOnce(::testing::Return(false));

    EXPECT_CALL(mockIo, read(::testing::NotNull(), 8))
        .WillOnce(::testing::Invoke([](byte* buf, size_t rcount) -> size_t {
            std::memset(buf, 0, 8);
            return 8;
        }));

    EXPECT_CALL(mockIo, seek(-8, BasicIo::cur))
        .Times(1)
        .WillOnce(::testing::Return(0));

    bool result = isPngType(mockIo, false);
    EXPECT_FALSE(result);
}

// Test: All 0xFF bytes returns false
TEST_F(IsPngTypeTest_977, ReturnsFalseForAllFF_977) {
    EXPECT_CALL(mockIo, error())
        .WillOnce(::testing::Return(0))
        .WillOnce(::testing::Return(0));
    EXPECT_CALL(mockIo, eof())
        .WillOnce(::testing::Return(false))
        .WillOnce(::testing::Return(false));

    EXPECT_CALL(mockIo, read(::testing::NotNull(), 8))
        .WillOnce(::testing::Invoke([](byte* buf, size_t rcount) -> size_t {
            std::memset(buf, 0xFF, 8);
            return 8;
        }));

    EXPECT_CALL(mockIo, seek(-8, BasicIo::cur))
        .Times(1)
        .WillOnce(::testing::Return(0));

    bool result = isPngType(mockIo, true);
    EXPECT_FALSE(result);
}
