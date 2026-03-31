#include <gtest/gtest.h>
#include <cstdint>
#include <cstring>

// Since checkMagicNum is a static function in a .cc file, we include the source
// to access it within the ImageEmbeddingUtils namespace for testing purposes.
#include "ImageEmbeddingUtils.cc"

using namespace ImageEmbeddingUtils;

class CheckMagicNumTest_1857 : public ::testing::Test {
protected:
};

// Test that matching magic numbers return true
TEST_F(CheckMagicNumTest_1857, MatchingMagicNumberReturnsTrue_1857)
{
    const char fileContent[] = "\x89PNG";
    const uint8_t magicNum[] = { 0x89, 0x50, 0x4E, 0x47 };
    EXPECT_TRUE(checkMagicNum(fileContent, magicNum, 4));
}

// Test that non-matching magic numbers return false
TEST_F(CheckMagicNumTest_1857, NonMatchingMagicNumberReturnsFalse_1857)
{
    const char fileContent[] = "\x89PNG";
    const uint8_t magicNum[] = { 0xFF, 0xD8, 0xFF, 0xE0 };
    EXPECT_FALSE(checkMagicNum(fileContent, magicNum, 4));
}

// Test with size 0 - memcmp with size 0 always returns 0, so should be true
TEST_F(CheckMagicNumTest_1857, ZeroSizeAlwaysReturnsTrue_1857)
{
    const char fileContent[] = "anything";
    const uint8_t magicNum[] = { 0xFF };
    EXPECT_TRUE(checkMagicNum(fileContent, magicNum, 0));
}

// Test with single byte matching
TEST_F(CheckMagicNumTest_1857, SingleByteMatch_1857)
{
    const char fileContent[] = "\xFF";
    const uint8_t magicNum[] = { 0xFF };
    EXPECT_TRUE(checkMagicNum(fileContent, magicNum, 1));
}

// Test with single byte not matching
TEST_F(CheckMagicNumTest_1857, SingleByteNoMatch_1857)
{
    const char fileContent[] = "\xFE";
    const uint8_t magicNum[] = { 0xFF };
    EXPECT_FALSE(checkMagicNum(fileContent, magicNum, 1));
}

// Test partial match - first bytes match but later bytes differ
TEST_F(CheckMagicNumTest_1857, PartialMatchReturnsFalse_1857)
{
    const char fileContent[] = "\x89\x50\x4E\x00";
    const uint8_t magicNum[] = { 0x89, 0x50, 0x4E, 0x47 };
    EXPECT_FALSE(checkMagicNum(fileContent, magicNum, 4));
}

// Test with JPEG magic number
TEST_F(CheckMagicNumTest_1857, JpegMagicNumber_1857)
{
    const char fileContent[] = "\xFF\xD8\xFF";
    const uint8_t magicNum[] = { 0xFF, 0xD8, 0xFF };
    EXPECT_TRUE(checkMagicNum(fileContent, magicNum, 3));
}

// Test that only the specified number of bytes are compared
TEST_F(CheckMagicNumTest_1857, OnlyComparesSizeBytes_1857)
{
    const char fileContent[] = "\x89\x50XXXX";
    const uint8_t magicNum[] = { 0x89, 0x50, 0x4E, 0x47 };
    // Only compare first 2 bytes, which match
    EXPECT_TRUE(checkMagicNum(fileContent, magicNum, 2));
}

// Test with all zero bytes
TEST_F(CheckMagicNumTest_1857, AllZeroBytes_1857)
{
    const char fileContent[] = "\x00\x00\x00\x00";
    const uint8_t magicNum[] = { 0x00, 0x00, 0x00, 0x00 };
    EXPECT_TRUE(checkMagicNum(fileContent, magicNum, 4));
}

// Test where first byte differs
TEST_F(CheckMagicNumTest_1857, FirstByteDiffers_1857)
{
    const char fileContent[] = "\x00\x50\x4E\x47";
    const uint8_t magicNum[] = { 0x89, 0x50, 0x4E, 0x47 };
    EXPECT_FALSE(checkMagicNum(fileContent, magicNum, 4));
}

// Test where last byte differs
TEST_F(CheckMagicNumTest_1857, LastByteDiffers_1857)
{
    const char fileContent[] = "\x89\x50\x4E\x00";
    const uint8_t magicNum[] = { 0x89, 0x50, 0x4E, 0x47 };
    EXPECT_FALSE(checkMagicNum(fileContent, magicNum, 4));
}

// Test with max uint8_t size value (255 bytes)
TEST_F(CheckMagicNumTest_1857, LargerMatchingBuffers_1857)
{
    char fileContent[64];
    uint8_t magicNum[64];
    memset(fileContent, 0xAB, 64);
    memset(magicNum, 0xAB, 64);
    EXPECT_TRUE(checkMagicNum(fileContent, magicNum, 64));
}

// Test with larger buffers that don't match
TEST_F(CheckMagicNumTest_1857, LargerNonMatchingBuffers_1857)
{
    char fileContent[64];
    uint8_t magicNum[64];
    memset(fileContent, 0xAB, 64);
    memset(magicNum, 0xAB, 64);
    magicNum[63] = 0xAC; // differ at last byte
    EXPECT_FALSE(checkMagicNum(fileContent, magicNum, 64));
}
