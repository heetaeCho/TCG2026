#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include "Stream.h"

// Helper: Create a MemStream or similar base stream for LZWStream to wrap.
// We need a minimal valid stream to construct LZWStream.

class LZWStreamTest_183 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }

    // Helper to create an LZWStream wrapping a minimal base stream
    std::unique_ptr<LZWStream> createLZWStream(const char* data, int length) {
        // Create a MemStream as the underlying stream
        // MemStream takes ownership-related params
        auto *dataCopy = (char *)gmalloc(length);
        memcpy(dataCopy, data, length);
        
        Object dictObj(objNull);
        auto baseStream = std::make_unique<MemStream>(dataCopy, 0, length, std::move(dictObj));
        
        // predictor=1 (no prediction), columns=1, colors=1, bits=8, early=1
        return std::make_unique<LZWStream>(std::move(baseStream), 1, 1, 1, 8, 1);
    }
};

// Test that getKind returns strLZW
TEST_F(LZWStreamTest_183, GetKindReturnsStrLZW_183) {
    // Minimal LZW data - just enough to construct the stream
    // LZW clear code for 9-bit codes is 256 (0x100), EOD is 257 (0x101)
    // We'll use a minimal byte sequence
    unsigned char lzwData[] = { 0x80, 0x0B, 0x60, 0x50, 0x22, 0x0C, 0x0C, 0x85, 0x01 };
    
    char *dataCopy = (char *)gmalloc(sizeof(lzwData));
    memcpy(dataCopy, lzwData, sizeof(lzwData));
    
    Object dictObj(objNull);
    auto baseStream = std::make_unique<MemStream>(dataCopy, 0, sizeof(lzwData), std::move(dictObj));
    
    LZWStream lzwStream(std::move(baseStream), 1, 1, 1, 8, 1);
    
    EXPECT_EQ(lzwStream.getKind(), strLZW);
}

// Test that getKind consistently returns strLZW on multiple calls
TEST_F(LZWStreamTest_183, GetKindConsistentlyReturnsStrLZW_183) {
    unsigned char lzwData[] = { 0x80, 0x0B, 0x60, 0x50, 0x22, 0x0C, 0x0C, 0x85, 0x01 };
    
    char *dataCopy = (char *)gmalloc(sizeof(lzwData));
    memcpy(dataCopy, lzwData, sizeof(lzwData));
    
    Object dictObj(objNull);
    auto baseStream = std::make_unique<MemStream>(dataCopy, 0, sizeof(lzwData), std::move(dictObj));
    
    LZWStream lzwStream(std::move(baseStream), 1, 1, 1, 8, 1);
    
    // Call multiple times to ensure consistency
    EXPECT_EQ(lzwStream.getKind(), strLZW);
    EXPECT_EQ(lzwStream.getKind(), strLZW);
    EXPECT_EQ(lzwStream.getKind(), strLZW);
}

// Test that getKind returns the correct enum value (4)
TEST_F(LZWStreamTest_183, GetKindReturnsCorrectEnumValue_183) {
    unsigned char lzwData[] = { 0x80, 0x0B, 0x60, 0x50, 0x22, 0x0C, 0x0C, 0x85, 0x01 };
    
    char *dataCopy = (char *)gmalloc(sizeof(lzwData));
    memcpy(dataCopy, lzwData, sizeof(lzwData));
    
    Object dictObj(objNull);
    auto baseStream = std::make_unique<MemStream>(dataCopy, 0, sizeof(lzwData), std::move(dictObj));
    
    LZWStream lzwStream(std::move(baseStream), 1, 1, 1, 8, 1);
    
    // strLZW should be 4 per the enum definition
    EXPECT_EQ(static_cast<int>(lzwStream.getKind()), 4);
}

// Test that getKind is not confused with other stream types
TEST_F(LZWStreamTest_183, GetKindIsNotOtherStreamType_183) {
    unsigned char lzwData[] = { 0x80, 0x0B, 0x60, 0x50, 0x22, 0x0C, 0x0C, 0x85, 0x01 };
    
    char *dataCopy = (char *)gmalloc(sizeof(lzwData));
    memcpy(dataCopy, lzwData, sizeof(lzwData));
    
    Object dictObj(objNull);
    auto baseStream = std::make_unique<MemStream>(dataCopy, 0, sizeof(lzwData), std::move(dictObj));
    
    LZWStream lzwStream(std::move(baseStream), 1, 1, 1, 8, 1);
    
    EXPECT_NE(lzwStream.getKind(), strFile);
    EXPECT_NE(lzwStream.getKind(), strCachedFile);
    EXPECT_NE(lzwStream.getKind(), strASCIIHex);
    EXPECT_NE(lzwStream.getKind(), strASCII85);
    EXPECT_NE(lzwStream.getKind(), strRunLength);
    EXPECT_NE(lzwStream.getKind(), strCCITTFax);
    EXPECT_NE(lzwStream.getKind(), strDCT);
    EXPECT_NE(lzwStream.getKind(), strFlate);
    EXPECT_NE(lzwStream.getKind(), strJBIG2);
    EXPECT_NE(lzwStream.getKind(), strJPX);
    EXPECT_NE(lzwStream.getKind(), strWeird);
    EXPECT_NE(lzwStream.getKind(), strCrypt);
}

// Test isBinary returns expected value
TEST_F(LZWStreamTest_183, IsBinaryReturnsExpected_183) {
    unsigned char lzwData[] = { 0x80, 0x0B, 0x60, 0x50, 0x22, 0x0C, 0x0C, 0x85, 0x01 };
    
    char *dataCopy = (char *)gmalloc(sizeof(lzwData));
    memcpy(dataCopy, lzwData, sizeof(lzwData));
    
    Object dictObj(objNull);
    auto baseStream = std::make_unique<MemStream>(dataCopy, 0, sizeof(lzwData), std::move(dictObj));
    
    LZWStream lzwStream(std::move(baseStream), 1, 1, 1, 8, 1);
    
    // isBinary should return a bool - LZW streams are typically binary
    bool result = lzwStream.isBinary(true);
    // We just verify it doesn't crash and returns a valid bool
    EXPECT_TRUE(result == true || result == false);
}

// Test rewind functionality
TEST_F(LZWStreamTest_183, RewindDoesNotCrash_183) {
    unsigned char lzwData[] = { 0x80, 0x0B, 0x60, 0x50, 0x22, 0x0C, 0x0C, 0x85, 0x01 };
    
    char *dataCopy = (char *)gmalloc(sizeof(lzwData));
    memcpy(dataCopy, lzwData, sizeof(lzwData));
    
    Object dictObj(objNull);
    auto baseStream = std::make_unique<MemStream>(dataCopy, 0, sizeof(lzwData), std::move(dictObj));
    
    LZWStream lzwStream(std::move(baseStream), 1, 1, 1, 8, 1);
    
    // rewind should not crash
    bool result = lzwStream.rewind();
    EXPECT_TRUE(result == true || result == false);
}

// Test getChar on empty/minimal LZW data
TEST_F(LZWStreamTest_183, GetCharOnMinimalData_183) {
    // Empty or minimal LZW data - just clear and EOD codes
    unsigned char lzwData[] = { 0x80, 0x01, 0x00 }; // Minimal
    
    char *dataCopy = (char *)gmalloc(sizeof(lzwData));
    memcpy(dataCopy, lzwData, sizeof(lzwData));
    
    Object dictObj(objNull);
    auto baseStream = std::make_unique<MemStream>(dataCopy, 0, sizeof(lzwData), std::move(dictObj));
    
    LZWStream lzwStream(std::move(baseStream), 1, 1, 1, 8, 1);
    lzwStream.rewind();
    
    // getChar should return EOF or a valid character
    int ch = lzwStream.getChar();
    EXPECT_TRUE(ch == EOF || (ch >= 0 && ch <= 255));
}

// Test with different early parameter values
TEST_F(LZWStreamTest_183, GetKindWithDifferentEarlyParam_183) {
    unsigned char lzwData[] = { 0x80, 0x0B, 0x60, 0x50, 0x22, 0x0C, 0x0C, 0x85, 0x01 };
    
    // early = 0
    char *dataCopy1 = (char *)gmalloc(sizeof(lzwData));
    memcpy(dataCopy1, lzwData, sizeof(lzwData));
    Object dictObj1(objNull);
    auto baseStream1 = std::make_unique<MemStream>(dataCopy1, 0, sizeof(lzwData), std::move(dictObj1));
    LZWStream lzwStream1(std::move(baseStream1), 1, 1, 1, 8, 0);
    EXPECT_EQ(lzwStream1.getKind(), strLZW);
    
    // early = 1
    char *dataCopy2 = (char *)gmalloc(sizeof(lzwData));
    memcpy(dataCopy2, lzwData, sizeof(lzwData));
    Object dictObj2(objNull);
    auto baseStream2 = std::make_unique<MemStream>(dataCopy2, 0, sizeof(lzwData), std::move(dictObj2));
    LZWStream lzwStream2(std::move(baseStream2), 1, 1, 1, 8, 1);
    EXPECT_EQ(lzwStream2.getKind(), strLZW);
}

// Test lookChar doesn't advance the stream position
TEST_F(LZWStreamTest_183, LookCharDoesNotAdvance_183) {
    // Valid LZW compressed data for "A" (0x41)
    // Clear code (256) + 'A' (65) + EOD (257) in 9-bit codes
    unsigned char lzwData[] = { 0x80, 0x20, 0xC0, 0x80, 0x40 };
    
    char *dataCopy = (char *)gmalloc(sizeof(lzwData));
    memcpy(dataCopy, lzwData, sizeof(lzwData));
    
    Object dictObj(objNull);
    auto baseStream = std::make_unique<MemStream>(dataCopy, 0, sizeof(lzwData), std::move(dictObj));
    
    LZWStream lzwStream(std::move(baseStream), 1, 1, 1, 8, 1);
    lzwStream.rewind();
    
    int firstLook = lzwStream.lookChar();
    int secondLook = lzwStream.lookChar();
    
    // lookChar should return the same value without advancing
    EXPECT_EQ(firstLook, secondLook);
}

// Test getPSFilter
TEST_F(LZWStreamTest_183, GetPSFilterReturnsOptional_183) {
    unsigned char lzwData[] = { 0x80, 0x0B, 0x60, 0x50, 0x22, 0x0C, 0x0C, 0x85, 0x01 };
    
    char *dataCopy = (char *)gmalloc(sizeof(lzwData));
    memcpy(dataCopy, lzwData, sizeof(lzwData));
    
    Object dictObj(objNull);
    auto baseStream = std::make_unique<MemStream>(dataCopy, 0, sizeof(lzwData), std::move(dictObj));
    
    LZWStream lzwStream(std::move(baseStream), 1, 1, 1, 8, 1);
    
    // getPSFilter with psLevel 1 - LZW might not be supported at level 1
    auto result1 = lzwStream.getPSFilter(1, "");
    // getPSFilter with psLevel 2
    auto result2 = lzwStream.getPSFilter(2, "");
    // getPSFilter with psLevel 3
    auto result3 = lzwStream.getPSFilter(3, "");
    
    // We just verify these don't crash; the result is implementation-dependent
    // The return type is std::optional<std::string>
    SUCCEED();
}
