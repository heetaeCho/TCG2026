#include <gtest/gtest.h>
#include <string>
#include <cstdint>
#include <cstring>

// Include the necessary Catch2 headers
#include "catch2/catch_tostring.hpp"

namespace {

// Helper to call rawMemoryToString
using Catch::Detail::rawMemoryToString;

TEST(RawMemoryToStringTest_259, SingleByteZero_259) {
    unsigned char byte = 0x00;
    std::string result = rawMemoryToString(&byte, sizeof(byte));
    EXPECT_EQ(result, "0x00");
}

TEST(RawMemoryToStringTest_259, SingleByteFF_259) {
    unsigned char byte = 0xFF;
    std::string result = rawMemoryToString(&byte, sizeof(byte));
    EXPECT_EQ(result, "0xff");
}

TEST(RawMemoryToStringTest_259, SingleByteArbitrary_259) {
    unsigned char byte = 0xAB;
    std::string result = rawMemoryToString(&byte, sizeof(byte));
    EXPECT_EQ(result, "0xab");
}

TEST(RawMemoryToStringTest_259, TwoBytes_259) {
    uint16_t value = 0x0102;
    std::string result = rawMemoryToString(&value, sizeof(value));
    // Result depends on endianness but should be 4 hex chars after "0x"
    EXPECT_EQ(result.substr(0, 2), "0x");
    EXPECT_EQ(result.size(), 6u); // "0x" + 4 hex digits
}

TEST(RawMemoryToStringTest_259, FourBytesKnownValue_259) {
    // Use a known byte array to avoid endianness ambiguity in the stored value
    unsigned char bytes[4] = {0x01, 0x02, 0x03, 0x04};
    std::string result = rawMemoryToString(bytes, 4);
    // The function should print bytes in big-endian order regardless of platform
    // On little-endian: reads from index 3 down to 0 -> 04030201
    // On big-endian: reads from index 0 up to 3 -> 01020304
    EXPECT_EQ(result.substr(0, 2), "0x");
    EXPECT_EQ(result.size(), 10u); // "0x" + 8 hex digits
    
    // Either "0x04030201" (little-endian platform) or "0x01020304" (big-endian platform)
    EXPECT_TRUE(result == "0x04030201" || result == "0x01020304");
}

TEST(RawMemoryToStringTest_259, ZeroSize_259) {
    unsigned char byte = 0xAA;
    std::string result = rawMemoryToString(&byte, 0);
    // With size 0, no bytes should be printed
    EXPECT_EQ(result, "0x");
}

TEST(RawMemoryToStringTest_259, EightBytes_259) {
    unsigned char bytes[8] = {0xDE, 0xAD, 0xBE, 0xEF, 0xCA, 0xFE, 0xBA, 0xBE};
    std::string result = rawMemoryToString(bytes, 8);
    EXPECT_EQ(result.substr(0, 2), "0x");
    EXPECT_EQ(result.size(), 18u); // "0x" + 16 hex digits
}

TEST(RawMemoryToStringTest_259, StartsWithHexPrefix_259) {
    unsigned char byte = 0x42;
    std::string result = rawMemoryToString(&byte, sizeof(byte));
    EXPECT_EQ(result.substr(0, 2), "0x");
}

TEST(RawMemoryToStringTest_259, AllZeroBytes_259) {
    unsigned char bytes[4] = {0x00, 0x00, 0x00, 0x00};
    std::string result = rawMemoryToString(bytes, 4);
    EXPECT_EQ(result, "0x00000000");
}

TEST(RawMemoryToStringTest_259, AllFFBytes_259) {
    unsigned char bytes[4] = {0xFF, 0xFF, 0xFF, 0xFF};
    std::string result = rawMemoryToString(bytes, 4);
    EXPECT_EQ(result, "0xffffffff");
}

TEST(RawMemoryToStringTest_259, SingleByteLowNibbleOnly_259) {
    unsigned char byte = 0x0A;
    std::string result = rawMemoryToString(&byte, sizeof(byte));
    // Should be zero-padded to 2 digits
    EXPECT_EQ(result, "0x0a");
}

TEST(RawMemoryToStringTest_259, LargeBuffer_259) {
    unsigned char bytes[16];
    for (int i = 0; i < 16; ++i) {
        bytes[i] = static_cast<unsigned char>(i);
    }
    std::string result = rawMemoryToString(bytes, 16);
    EXPECT_EQ(result.substr(0, 2), "0x");
    EXPECT_EQ(result.size(), 34u); // "0x" + 32 hex digits
}

TEST(RawMemoryToStringTest_259, ConsistentEndianOrdering_259) {
    // Two identical buffers should produce identical results
    unsigned char bytes1[3] = {0x11, 0x22, 0x33};
    unsigned char bytes2[3] = {0x11, 0x22, 0x33};
    std::string result1 = rawMemoryToString(bytes1, 3);
    std::string result2 = rawMemoryToString(bytes2, 3);
    EXPECT_EQ(result1, result2);
}

TEST(RawMemoryToStringTest_259, DifferentBuffersProduceDifferentResults_259) {
    unsigned char bytes1[2] = {0x01, 0x02};
    unsigned char bytes2[2] = {0x03, 0x04};
    std::string result1 = rawMemoryToString(bytes1, 2);
    std::string result2 = rawMemoryToString(bytes2, 2);
    EXPECT_NE(result1, result2);
}

TEST(RawMemoryToStringTest_259, IntTypeRepresentation_259) {
    int value = 1;
    std::string result = rawMemoryToString(&value, sizeof(value));
    EXPECT_EQ(result.substr(0, 2), "0x");
    EXPECT_EQ(result.size(), 2 + sizeof(int) * 2);
    
    // On any platform, int value 1 should produce:
    // big-endian: "0x00000001" (for 4-byte int)
    // little-endian: "0x00000001" (because the function reverses for little-endian)
    if (sizeof(int) == 4) {
        EXPECT_EQ(result, "0x00000001");
    }
}

} // namespace
