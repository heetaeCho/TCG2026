#include <gtest/gtest.h>
#include <exiv2/value.hpp>
#include <cstring>
#include <sstream>

using namespace Exiv2;

class DataValueTest_794 : public ::testing::Test {
protected:
    void SetUp() override {
    }
};

// Test default construction with undefined type
TEST_F(DataValueTest_794, ConstructWithUndefinedType_794) {
    DataValue dv(undefined);
    EXPECT_EQ(dv.count(), 0u);
    EXPECT_EQ(dv.size(), 0u);
}

// Test default construction with unsignedByte type
TEST_F(DataValueTest_794, ConstructWithUnsignedByteType_794) {
    DataValue dv(unsignedByte);
    EXPECT_EQ(dv.count(), 0u);
    EXPECT_EQ(dv.size(), 0u);
}

// Test read from string with valid space-separated integers
TEST_F(DataValueTest_794, ReadFromStringValidInput_794) {
    DataValue dv(undefined);
    int result = dv.read("10 20 30 40");
    EXPECT_EQ(result, 0);
    EXPECT_EQ(dv.count(), 4u);
    EXPECT_EQ(dv.size(), 4u);
}

// Test read from string with single value
TEST_F(DataValueTest_794, ReadFromStringSingleValue_794) {
    DataValue dv(undefined);
    int result = dv.read("42");
    EXPECT_EQ(result, 0);
    EXPECT_EQ(dv.count(), 1u);
}

// Test read from empty string
TEST_F(DataValueTest_794, ReadFromEmptyString_794) {
    DataValue dv(undefined);
    int result = dv.read("");
    EXPECT_EQ(result, 0);
    EXPECT_EQ(dv.count(), 0u);
    EXPECT_EQ(dv.size(), 0u);
}

// Test read from string with invalid (non-integer) input
TEST_F(DataValueTest_794, ReadFromStringInvalidInput_794) {
    DataValue dv(undefined);
    int result = dv.read("abc def");
    EXPECT_EQ(result, 1);
}

// Test read from string with mixed valid and invalid input
TEST_F(DataValueTest_794, ReadFromStringMixedInput_794) {
    DataValue dv(undefined);
    int result = dv.read("10 abc 30");
    EXPECT_EQ(result, 1);
}

// Test read from byte buffer
TEST_F(DataValueTest_794, ReadFromByteBuffer_794) {
    DataValue dv(undefined);
    const byte buf[] = {0x01, 0x02, 0x03, 0x04, 0x05};
    int result = dv.read(buf, 5, littleEndian);
    EXPECT_EQ(result, 0);
    EXPECT_EQ(dv.count(), 5u);
    EXPECT_EQ(dv.size(), 5u);
}

// Test read from byte buffer with zero length
TEST_F(DataValueTest_794, ReadFromByteBufferZeroLength_794) {
    DataValue dv(undefined);
    const byte buf[] = {0x01};
    int result = dv.read(buf, 0, littleEndian);
    EXPECT_EQ(result, 0);
    EXPECT_EQ(dv.count(), 0u);
    EXPECT_EQ(dv.size(), 0u);
}

// Test copy to byte buffer
TEST_F(DataValueTest_794, CopyToByteBuffer_794) {
    DataValue dv(undefined);
    const byte src[] = {0xAA, 0xBB, 0xCC};
    dv.read(src, 3, littleEndian);
    
    byte dest[3] = {0};
    size_t copied = dv.copy(dest, littleEndian);
    EXPECT_EQ(copied, 3u);
    EXPECT_EQ(dest[0], 0xAA);
    EXPECT_EQ(dest[1], 0xBB);
    EXPECT_EQ(dest[2], 0xCC);
}

// Test toString for valid index
TEST_F(DataValueTest_794, ToStringValidIndex_794) {
    DataValue dv(undefined);
    dv.read("10 20 30");
    std::string s = dv.toString(0);
    EXPECT_EQ(s, "10");
    s = dv.toString(1);
    EXPECT_EQ(s, "20");
    s = dv.toString(2);
    EXPECT_EQ(s, "30");
}

// Test toInt64 for valid index
TEST_F(DataValueTest_794, ToInt64ValidIndex_794) {
    DataValue dv(undefined);
    dv.read("100 200 255");
    EXPECT_EQ(dv.toInt64(0), 100);
    EXPECT_EQ(dv.toInt64(1), 200);
    EXPECT_EQ(dv.toInt64(2), 255);
}

// Test toUint32 for valid index
TEST_F(DataValueTest_794, ToUint32ValidIndex_794) {
    DataValue dv(undefined);
    dv.read("50 100 200");
    EXPECT_EQ(dv.toUint32(0), 50u);
    EXPECT_EQ(dv.toUint32(1), 100u);
    EXPECT_EQ(dv.toUint32(2), 200u);
}

// Test toFloat for valid index
TEST_F(DataValueTest_794, ToFloatValidIndex_794) {
    DataValue dv(undefined);
    dv.read("42 128");
    EXPECT_FLOAT_EQ(dv.toFloat(0), 42.0f);
    EXPECT_FLOAT_EQ(dv.toFloat(1), 128.0f);
}

// Test toRational for valid index
TEST_F(DataValueTest_794, ToRationalValidIndex_794) {
    DataValue dv(undefined);
    dv.read("10 20");
    Rational r = dv.toRational(0);
    EXPECT_EQ(r.first, 10);
    EXPECT_EQ(r.second, 1);
}

// Test write to ostream
TEST_F(DataValueTest_794, WriteToOstream_794) {
    DataValue dv(undefined);
    dv.read("10 20 30");
    std::ostringstream os;
    dv.write(os);
    std::string output = os.str();
    EXPECT_FALSE(output.empty());
}

// Test write to ostream with empty value
TEST_F(DataValueTest_794, WriteToOstreamEmpty_794) {
    DataValue dv(undefined);
    std::ostringstream os;
    dv.write(os);
    // Should not crash; output may be empty
}

// Test clone
TEST_F(DataValueTest_794, ClonePreservesData_794) {
    DataValue dv(undefined);
    dv.read("5 10 15");
    auto cloned = dv.clone();
    ASSERT_NE(cloned, nullptr);
    EXPECT_EQ(cloned->count(), 3u);
    EXPECT_EQ(cloned->toInt64(0), 5);
    EXPECT_EQ(cloned->toInt64(1), 10);
    EXPECT_EQ(cloned->toInt64(2), 15);
}

// Test that read replaces previous data
TEST_F(DataValueTest_794, ReadReplacesExistingData_794) {
    DataValue dv(undefined);
    dv.read("1 2 3 4 5");
    EXPECT_EQ(dv.count(), 5u);
    
    dv.read("10 20");
    EXPECT_EQ(dv.count(), 2u);
    EXPECT_EQ(dv.toInt64(0), 10);
    EXPECT_EQ(dv.toInt64(1), 20);
}

// Test reading from byte buffer and then copying
TEST_F(DataValueTest_794, ReadByteAndCopyRoundTrip_794) {
    DataValue dv(undefined);
    const byte src[] = {0x00, 0xFF, 0x7F, 0x80};
    dv.read(src, 4, bigEndian);
    
    byte dest[4] = {0};
    size_t copied = dv.copy(dest, bigEndian);
    EXPECT_EQ(copied, 4u);
    EXPECT_EQ(memcmp(src, dest, 4), 0);
}

// Test construction from byte buffer directly
TEST_F(DataValueTest_794, ConstructFromByteBuffer_794) {
    const byte buf[] = {0x01, 0x02, 0x03};
    DataValue dv(buf, 3, littleEndian, undefined);
    EXPECT_EQ(dv.count(), 3u);
    EXPECT_EQ(dv.size(), 3u);
}

// Test count after reading whitespace-only string
TEST_F(DataValueTest_794, ReadWhitespaceOnlyString_794) {
    DataValue dv(undefined);
    int result = dv.read("   ");
    EXPECT_EQ(result, 0);
    EXPECT_EQ(dv.count(), 0u);
}

// Test read with large number of values
TEST_F(DataValueTest_794, ReadManyValues_794) {
    DataValue dv(undefined);
    std::string input;
    for (int i = 0; i < 100; ++i) {
        if (i > 0) input += " ";
        input += std::to_string(i);
    }
    int result = dv.read(input);
    EXPECT_EQ(result, 0);
    EXPECT_EQ(dv.count(), 100u);
}

// Test boundary: value 0
TEST_F(DataValueTest_794, ReadZeroValue_794) {
    DataValue dv(undefined);
    int result = dv.read("0");
    EXPECT_EQ(result, 0);
    EXPECT_EQ(dv.count(), 1u);
    EXPECT_EQ(dv.toInt64(0), 0);
}

// Test boundary: value 255 (max byte)
TEST_F(DataValueTest_794, ReadMaxByteValue_794) {
    DataValue dv(undefined);
    int result = dv.read("255");
    EXPECT_EQ(result, 0);
    EXPECT_EQ(dv.toInt64(0), 255);
}

// Test size equals count for byte data
TEST_F(DataValueTest_794, SizeEqualsCountForByteData_794) {
    DataValue dv(undefined);
    const byte buf[] = {0x10, 0x20, 0x30, 0x40, 0x50};
    dv.read(buf, 5, littleEndian);
    EXPECT_EQ(dv.size(), dv.count());
}

// Test toInt64 with out of range index throws or handles gracefully
TEST_F(DataValueTest_794, ToInt64OutOfRangeIndex_794) {
    DataValue dv(undefined);
    dv.read("10 20");
    // Accessing an out of range index - may throw
    EXPECT_THROW(dv.toInt64(5), std::out_of_range);
}

// Test toFloat with out of range index
TEST_F(DataValueTest_794, ToFloatOutOfRangeIndex_794) {
    DataValue dv(undefined);
    dv.read("10");
    EXPECT_THROW(dv.toFloat(5), std::out_of_range);
}

// Test string with trailing spaces
TEST_F(DataValueTest_794, ReadStringWithTrailingSpaces_794) {
    DataValue dv(undefined);
    int result = dv.read("10 20 30   ");
    EXPECT_EQ(result, 0);
    EXPECT_EQ(dv.count(), 3u);
}

// Test string with leading spaces
TEST_F(DataValueTest_794, ReadStringWithLeadingSpaces_794) {
    DataValue dv(undefined);
    int result = dv.read("   10 20 30");
    EXPECT_EQ(result, 0);
    EXPECT_EQ(dv.count(), 3u);
}

// Test negative values in string read
TEST_F(DataValueTest_794, ReadNegativeValues_794) {
    DataValue dv(undefined);
    int result = dv.read("-1 -128 127");
    // Depending on implementation, negative values might be valid integers
    // but may not be valid for byte data. Check return value.
    // The implementation reads as int, so it should succeed.
    if (result == 0) {
        EXPECT_EQ(dv.count(), 3u);
    }
}
