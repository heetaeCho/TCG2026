#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <exiv2/basicio.hpp>
#include <exiv2/gifimage.hpp>
#include <cstring>

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

class IsGifTypeTest_214 : public ::testing::Test {
protected:
    MockBasicIo mockIo;
};

// Test: Valid GIF87a signature with advance=true should return true and not seek back
TEST_F(IsGifTypeTest_214, ValidGif87aWithAdvance_214) {
    const byte gif87a[] = {'G', 'I', 'F', '8', '7', 'a'};

    EXPECT_CALL(mockIo, read(::testing::_, 6))
        .WillOnce(::testing::DoAll(
            ::testing::Invoke([&](byte* buf, size_t) {
                std::memcpy(buf, gif87a, 6);
            }),
            ::testing::Return(6)));
    EXPECT_CALL(mockIo, error()).WillOnce(::testing::Return(0));
    EXPECT_CALL(mockIo, eof()).WillOnce(::testing::Return(false));
    // Should NOT seek back when advance=true and matched
    EXPECT_CALL(mockIo, seek(::testing::_, ::testing::_)).Times(0);

    bool result = isGifType(mockIo, true);
    EXPECT_TRUE(result);
}

// Test: Valid GIF89a signature with advance=true should return true and not seek back
TEST_F(IsGifTypeTest_214, ValidGif89aWithAdvance_214) {
    const byte gif89a[] = {'G', 'I', 'F', '8', '9', 'a'};

    EXPECT_CALL(mockIo, read(::testing::_, 6))
        .WillOnce(::testing::DoAll(
            ::testing::Invoke([&](byte* buf, size_t) {
                std::memcpy(buf, gif89a, 6);
            }),
            ::testing::Return(6)));
    EXPECT_CALL(mockIo, error()).WillOnce(::testing::Return(0));
    EXPECT_CALL(mockIo, eof()).WillOnce(::testing::Return(false));
    EXPECT_CALL(mockIo, seek(::testing::_, ::testing::_)).Times(0);

    bool result = isGifType(mockIo, true);
    EXPECT_TRUE(result);
}

// Test: Valid GIF87a signature with advance=false should return true and seek back
TEST_F(IsGifTypeTest_214, ValidGif87aWithoutAdvance_214) {
    const byte gif87a[] = {'G', 'I', 'F', '8', '7', 'a'};

    EXPECT_CALL(mockIo, read(::testing::_, 6))
        .WillOnce(::testing::DoAll(
            ::testing::Invoke([&](byte* buf, size_t) {
                std::memcpy(buf, gif87a, 6);
            }),
            ::testing::Return(6)));
    EXPECT_CALL(mockIo, error()).WillOnce(::testing::Return(0));
    EXPECT_CALL(mockIo, eof()).WillOnce(::testing::Return(false));
    // Should seek back when advance=false even if matched
    EXPECT_CALL(mockIo, seek(-6, BasicIo::cur)).WillOnce(::testing::Return(0));

    bool result = isGifType(mockIo, false);
    EXPECT_TRUE(result);
}

// Test: Valid GIF89a signature with advance=false should return true and seek back
TEST_F(IsGifTypeTest_214, ValidGif89aWithoutAdvance_214) {
    const byte gif89a[] = {'G', 'I', 'F', '8', '9', 'a'};

    EXPECT_CALL(mockIo, read(::testing::_, 6))
        .WillOnce(::testing::DoAll(
            ::testing::Invoke([&](byte* buf, size_t) {
                std::memcpy(buf, gif89a, 6);
            }),
            ::testing::Return(6)));
    EXPECT_CALL(mockIo, error()).WillOnce(::testing::Return(0));
    EXPECT_CALL(mockIo, eof()).WillOnce(::testing::Return(false));
    EXPECT_CALL(mockIo, seek(-6, BasicIo::cur)).WillOnce(::testing::Return(0));

    bool result = isGifType(mockIo, false);
    EXPECT_TRUE(result);
}

// Test: Invalid signature with advance=true should return false and seek back
TEST_F(IsGifTypeTest_214, InvalidSignatureWithAdvance_214) {
    const byte invalid[] = {'P', 'N', 'G', '8', '9', 'a'};

    EXPECT_CALL(mockIo, read(::testing::_, 6))
        .WillOnce(::testing::DoAll(
            ::testing::Invoke([&](byte* buf, size_t) {
                std::memcpy(buf, invalid, 6);
            }),
            ::testing::Return(6)));
    EXPECT_CALL(mockIo, error()).WillOnce(::testing::Return(0));
    EXPECT_CALL(mockIo, eof()).WillOnce(::testing::Return(false));
    // Should seek back when not matched regardless of advance
    EXPECT_CALL(mockIo, seek(-6, BasicIo::cur)).WillOnce(::testing::Return(0));

    bool result = isGifType(mockIo, true);
    EXPECT_FALSE(result);
}

// Test: Invalid signature with advance=false should return false and seek back
TEST_F(IsGifTypeTest_214, InvalidSignatureWithoutAdvance_214) {
    const byte invalid[] = {'J', 'P', 'E', 'G', '0', '0'};

    EXPECT_CALL(mockIo, read(::testing::_, 6))
        .WillOnce(::testing::DoAll(
            ::testing::Invoke([&](byte* buf, size_t) {
                std::memcpy(buf, invalid, 6);
            }),
            ::testing::Return(6)));
    EXPECT_CALL(mockIo, error()).WillOnce(::testing::Return(0));
    EXPECT_CALL(mockIo, eof()).WillOnce(::testing::Return(false));
    EXPECT_CALL(mockIo, seek(-6, BasicIo::cur)).WillOnce(::testing::Return(0));

    bool result = isGifType(mockIo, false);
    EXPECT_FALSE(result);
}

// Test: IO error during read should return false
TEST_F(IsGifTypeTest_214, IoErrorDuringRead_214) {
    EXPECT_CALL(mockIo, read(::testing::_, 6))
        .WillOnce(::testing::Return(0));
    EXPECT_CALL(mockIo, error()).WillOnce(::testing::Return(1));

    bool result = isGifType(mockIo, true);
    EXPECT_FALSE(result);
}

// Test: EOF during read should return false
TEST_F(IsGifTypeTest_214, EofDuringRead_214) {
    EXPECT_CALL(mockIo, read(::testing::_, 6))
        .WillOnce(::testing::Return(3));
    EXPECT_CALL(mockIo, error()).WillOnce(::testing::Return(0));
    EXPECT_CALL(mockIo, eof()).WillOnce(::testing::Return(true));

    bool result = isGifType(mockIo, true);
    EXPECT_FALSE(result);
}

// Test: Almost correct signature (GIF88a) should return false
TEST_F(IsGifTypeTest_214, AlmostCorrectSignatureGif88a_214) {
    const byte almostGif[] = {'G', 'I', 'F', '8', '8', 'a'};

    EXPECT_CALL(mockIo, read(::testing::_, 6))
        .WillOnce(::testing::DoAll(
            ::testing::Invoke([&](byte* buf, size_t) {
                std::memcpy(buf, almostGif, 6);
            }),
            ::testing::Return(6)));
    EXPECT_CALL(mockIo, error()).WillOnce(::testing::Return(0));
    EXPECT_CALL(mockIo, eof()).WillOnce(::testing::Return(false));
    EXPECT_CALL(mockIo, seek(-6, BasicIo::cur)).WillOnce(::testing::Return(0));

    bool result = isGifType(mockIo, true);
    EXPECT_FALSE(result);
}

// Test: All zeros should return false
TEST_F(IsGifTypeTest_214, AllZerosSignature_214) {
    const byte zeros[] = {0, 0, 0, 0, 0, 0};

    EXPECT_CALL(mockIo, read(::testing::_, 6))
        .WillOnce(::testing::DoAll(
            ::testing::Invoke([&](byte* buf, size_t) {
                std::memcpy(buf, zeros, 6);
            }),
            ::testing::Return(6)));
    EXPECT_CALL(mockIo, error()).WillOnce(::testing::Return(0));
    EXPECT_CALL(mockIo, eof()).WillOnce(::testing::Return(false));
    EXPECT_CALL(mockIo, seek(-6, BasicIo::cur)).WillOnce(::testing::Return(0));

    bool result = isGifType(mockIo, true);
    EXPECT_FALSE(result);
}

// Test: Partial GIF signature (only "GIF" prefix) should return false
TEST_F(IsGifTypeTest_214, PartialGifSignature_214) {
    const byte partial[] = {'G', 'I', 'F', '0', '0', '0'};

    EXPECT_CALL(mockIo, read(::testing::_, 6))
        .WillOnce(::testing::DoAll(
            ::testing::Invoke([&](byte* buf, size_t) {
                std::memcpy(buf, partial, 6);
            }),
            ::testing::Return(6)));
    EXPECT_CALL(mockIo, error()).WillOnce(::testing::Return(0));
    EXPECT_CALL(mockIo, eof()).WillOnce(::testing::Return(false));
    EXPECT_CALL(mockIo, seek(-6, BasicIo::cur)).WillOnce(::testing::Return(0));

    bool result = isGifType(mockIo, true);
    EXPECT_FALSE(result);
}

// Test: Case sensitivity - lowercase "gif89a" should return false
TEST_F(IsGifTypeTest_214, LowercaseGifSignature_214) {
    const byte lowercase[] = {'g', 'i', 'f', '8', '9', 'a'};

    EXPECT_CALL(mockIo, read(::testing::_, 6))
        .WillOnce(::testing::DoAll(
            ::testing::Invoke([&](byte* buf, size_t) {
                std::memcpy(buf, lowercase, 6);
            }),
            ::testing::Return(6)));
    EXPECT_CALL(mockIo, error()).WillOnce(::testing::Return(0));
    EXPECT_CALL(mockIo, eof()).WillOnce(::testing::Return(false));
    EXPECT_CALL(mockIo, seek(-6, BasicIo::cur)).WillOnce(::testing::Return(0));

    bool result = isGifType(mockIo, true);
    EXPECT_FALSE(result);
}

// Test: GIF87A (uppercase 'A') should return false - only lowercase 'a' is valid
TEST_F(IsGifTypeTest_214, UppercaseAInSignature_214) {
    const byte upperA[] = {'G', 'I', 'F', '8', '7', 'A'};

    EXPECT_CALL(mockIo, read(::testing::_, 6))
        .WillOnce(::testing::DoAll(
            ::testing::Invoke([&](byte* buf, size_t) {
                std::memcpy(buf, upperA, 6);
            }),
            ::testing::Return(6)));
    EXPECT_CALL(mockIo, error()).WillOnce(::testing::Return(0));
    EXPECT_CALL(mockIo, eof()).WillOnce(::testing::Return(false));
    EXPECT_CALL(mockIo, seek(-6, BasicIo::cur)).WillOnce(::testing::Return(0));

    bool result = isGifType(mockIo, true);
    EXPECT_FALSE(result);
}

// Test: Both error and eof set should return false
TEST_F(IsGifTypeTest_214, BothErrorAndEof_214) {
    EXPECT_CALL(mockIo, read(::testing::_, 6))
        .WillOnce(::testing::Return(0));
    EXPECT_CALL(mockIo, error()).WillOnce(::testing::Return(1));

    bool result = isGifType(mockIo, false);
    EXPECT_FALSE(result);
}

// Test using MemIo for integration-like testing with GIF87a
TEST_F(IsGifTypeTest_214, MemIoGif87aAdvance_214) {
    const byte gif87a[] = {'G', 'I', 'F', '8', '7', 'a', 0, 0};
    MemIo memIo(gif87a, sizeof(gif87a));

    bool result = isGifType(memIo, true);
    EXPECT_TRUE(result);
    // After advance, position should be at 6
    EXPECT_EQ(memIo.tell(), 6u);
}

// Test using MemIo for integration-like testing with GIF89a
TEST_F(IsGifTypeTest_214, MemIoGif89aAdvance_214) {
    const byte gif89a[] = {'G', 'I', 'F', '8', '9', 'a', 0, 0};
    MemIo memIo(gif89a, sizeof(gif89a));

    bool result = isGifType(memIo, true);
    EXPECT_TRUE(result);
    EXPECT_EQ(memIo.tell(), 6u);
}

// Test using MemIo: advance=false should reset position
TEST_F(IsGifTypeTest_214, MemIoGif89aNoAdvance_214) {
    const byte gif89a[] = {'G', 'I', 'F', '8', '9', 'a', 0, 0};
    MemIo memIo(gif89a, sizeof(gif89a));

    bool result = isGifType(memIo, false);
    EXPECT_TRUE(result);
    // Position should be reset to 0
    EXPECT_EQ(memIo.tell(), 0u);
}

// Test using MemIo: invalid data
TEST_F(IsGifTypeTest_214, MemIoInvalidData_214) {
    const byte invalidData[] = {'N', 'O', 'T', 'G', 'I', 'F'};
    MemIo memIo(invalidData, sizeof(invalidData));

    bool result = isGifType(memIo, true);
    EXPECT_FALSE(result);
    // Position should be reset since not matched
    EXPECT_EQ(memIo.tell(), 0u);
}

// Test using MemIo: too short data (less than 6 bytes)
TEST_F(IsGifTypeTest_214, MemIoTooShortData_214) {
    const byte shortData[] = {'G', 'I', 'F'};
    MemIo memIo(shortData, sizeof(shortData));

    bool result = isGifType(memIo, true);
    EXPECT_FALSE(result);
}

// Test using MemIo: empty data
TEST_F(IsGifTypeTest_214, MemIoEmptyData_214) {
    MemIo memIo;

    bool result = isGifType(memIo, true);
    EXPECT_FALSE(result);
}
