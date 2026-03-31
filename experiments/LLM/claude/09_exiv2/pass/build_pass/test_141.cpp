#include <gtest/gtest.h>
#include <exiv2/value.hpp>
#include <exiv2/types.hpp>

using namespace Exiv2;

// Test normal operation with big endian byte order
TEST(ToDataURationalTest_141, NormalOperationBigEndian_141) {
    byte buf[8] = {0};
    URational val(1, 2);
    size_t result = toData(buf, val, bigEndian);
    EXPECT_EQ(result, 8u);
    
    // Verify by reading back
    URational readBack = getURational(buf, bigEndian);
    EXPECT_EQ(readBack.first, 1u);
    EXPECT_EQ(readBack.second, 2u);
}

// Test normal operation with little endian byte order
TEST(ToDataURationalTest_141, NormalOperationLittleEndian_141) {
    byte buf[8] = {0};
    URational val(3, 4);
    size_t result = toData(buf, val, littleEndian);
    EXPECT_EQ(result, 8u);
    
    URational readBack = getURational(buf, littleEndian);
    EXPECT_EQ(readBack.first, 3u);
    EXPECT_EQ(readBack.second, 4u);
}

// Test with zero numerator
TEST(ToDataURationalTest_141, ZeroNumerator_141) {
    byte buf[8] = {0};
    URational val(0, 1);
    size_t result = toData(buf, val, bigEndian);
    EXPECT_EQ(result, 8u);
    
    URational readBack = getURational(buf, bigEndian);
    EXPECT_EQ(readBack.first, 0u);
    EXPECT_EQ(readBack.second, 1u);
}

// Test with zero denominator
TEST(ToDataURationalTest_141, ZeroDenominator_141) {
    byte buf[8] = {0};
    URational val(1, 0);
    size_t result = toData(buf, val, bigEndian);
    EXPECT_EQ(result, 8u);
    
    URational readBack = getURational(buf, bigEndian);
    EXPECT_EQ(readBack.first, 1u);
    EXPECT_EQ(readBack.second, 0u);
}

// Test with both zero
TEST(ToDataURationalTest_141, BothZero_141) {
    byte buf[8] = {0};
    URational val(0, 0);
    size_t result = toData(buf, val, bigEndian);
    EXPECT_EQ(result, 8u);
    
    URational readBack = getURational(buf, bigEndian);
    EXPECT_EQ(readBack.first, 0u);
    EXPECT_EQ(readBack.second, 0u);
}

// Test with maximum uint32 values
TEST(ToDataURationalTest_141, MaxValues_141) {
    byte buf[8] = {0};
    URational val(0xFFFFFFFF, 0xFFFFFFFF);
    size_t result = toData(buf, val, bigEndian);
    EXPECT_EQ(result, 8u);
    
    URational readBack = getURational(buf, bigEndian);
    EXPECT_EQ(readBack.first, 0xFFFFFFFFu);
    EXPECT_EQ(readBack.second, 0xFFFFFFFFu);
}

// Test with max numerator and min denominator
TEST(ToDataURationalTest_141, MaxNumeratorMinDenominator_141) {
    byte buf[8] = {0};
    URational val(0xFFFFFFFF, 1);
    size_t result = toData(buf, val, littleEndian);
    EXPECT_EQ(result, 8u);
    
    URational readBack = getURational(buf, littleEndian);
    EXPECT_EQ(readBack.first, 0xFFFFFFFFu);
    EXPECT_EQ(readBack.second, 1u);
}

// Test return value is always 8 bytes
TEST(ToDataURationalTest_141, ReturnValueIs8_141) {
    byte buf[8] = {0};
    URational val(42, 100);
    
    size_t resultBE = toData(buf, val, bigEndian);
    EXPECT_EQ(resultBE, 8u);
    
    size_t resultLE = toData(buf, val, littleEndian);
    EXPECT_EQ(resultLE, 8u);
}

// Test that big endian and little endian produce different byte sequences for non-trivial values
TEST(ToDataURationalTest_141, EndiannessDifference_141) {
    byte bufBE[8] = {0};
    byte bufLE[8] = {0};
    URational val(0x01020304, 0x05060708);
    
    toData(bufBE, val, bigEndian);
    toData(bufLE, val, littleEndian);
    
    // The byte representations should differ for multi-byte values
    bool same = true;
    for (int i = 0; i < 8; ++i) {
        if (bufBE[i] != bufLE[i]) {
            same = false;
            break;
        }
    }
    EXPECT_FALSE(same);
    
    // But reading back with the correct endianness should give the same value
    URational readBE = getURational(bufBE, bigEndian);
    URational readLE = getURational(bufLE, littleEndian);
    EXPECT_EQ(readBE.first, readLE.first);
    EXPECT_EQ(readBE.second, readLE.second);
}

// Test with typical EXIF-like rational value (e.g., focal length)
TEST(ToDataURationalTest_141, TypicalExifValue_141) {
    byte buf[8] = {0};
    URational val(500, 10); // e.g., 50mm focal length
    size_t result = toData(buf, val, littleEndian);
    EXPECT_EQ(result, 8u);
    
    URational readBack = getURational(buf, littleEndian);
    EXPECT_EQ(readBack.first, 500u);
    EXPECT_EQ(readBack.second, 10u);
}

// Test roundtrip consistency with various values
TEST(ToDataURationalTest_141, RoundtripConsistency_141) {
    byte buf[8] = {0};
    
    std::vector<URational> testValues = {
        {1, 1},
        {100, 1},
        {1, 100},
        {72, 1},
        {300, 1},
        {256, 256},
        {0x7FFFFFFF, 0x7FFFFFFF},
    };
    
    for (const auto& val : testValues) {
        for (auto bo : {bigEndian, littleEndian}) {
            toData(buf, val, bo);
            URational readBack = getURational(buf, bo);
            EXPECT_EQ(readBack.first, val.first) 
                << "Failed for (" << val.first << ", " << val.second << ")";
            EXPECT_EQ(readBack.second, val.second) 
                << "Failed for (" << val.first << ", " << val.second << ")";
        }
    }
}
