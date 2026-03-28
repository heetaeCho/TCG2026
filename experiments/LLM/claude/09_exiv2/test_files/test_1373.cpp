#include <gtest/gtest.h>
#include <sstream>
#include <exiv2/exiv2.hpp>

// We need access to the Internal namespace function
namespace Exiv2 {
namespace Internal {
std::ostream& printBitmask(std::ostream& os, const Value& value, const ExifData* metadata);
}
}

using namespace Exiv2;

class PrintBitmaskTest_1373 : public ::testing::Test {
protected:
    std::ostringstream os;
};

// Test with unsignedShort type, single element, no bits set -> "(none)"
TEST_F(PrintBitmaskTest_1373, UnsignedShortNoBitsSet_1373) {
    auto value = Value::create(unsignedShort);
    value->read("0");
    Internal::printBitmask(os, *value, nullptr);
    EXPECT_EQ(os.str(), "(none)");
}

// Test with unsignedShort type, single element, bit 0 set
TEST_F(PrintBitmaskTest_1373, UnsignedShortBit0Set_1373) {
    auto value = Value::create(unsignedShort);
    value->read("1");
    Internal::printBitmask(os, *value, nullptr);
    EXPECT_EQ(os.str(), "0");
}

// Test with unsignedShort type, single element, bit 1 set
TEST_F(PrintBitmaskTest_1373, UnsignedShortBit1Set_1373) {
    auto value = Value::create(unsignedShort);
    value->read("2");
    Internal::printBitmask(os, *value, nullptr);
    EXPECT_EQ(os.str(), "1");
}

// Test with unsignedShort type, single element, bits 0 and 1 set (value=3)
TEST_F(PrintBitmaskTest_1373, UnsignedShortBits0And1Set_1373) {
    auto value = Value::create(unsignedShort);
    value->read("3");
    Internal::printBitmask(os, *value, nullptr);
    EXPECT_EQ(os.str(), "0,1");
}

// Test with unsignedShort type, value = 5 (bits 0 and 2)
TEST_F(PrintBitmaskTest_1373, UnsignedShortBits0And2Set_1373) {
    auto value = Value::create(unsignedShort);
    value->read("5");
    Internal::printBitmask(os, *value, nullptr);
    EXPECT_EQ(os.str(), "0,2");
}

// Test with unsignedShort, all 16 bits set (value = 65535)
TEST_F(PrintBitmaskTest_1373, UnsignedShortAllBitsSet_1373) {
    auto value = Value::create(unsignedShort);
    value->read("65535");
    Internal::printBitmask(os, *value, nullptr);
    // Should output "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15"
    EXPECT_EQ(os.str(), "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15");
}

// Test with signedShort type, no bits set -> "(none)"
TEST_F(PrintBitmaskTest_1373, SignedShortNoBitsSet_1373) {
    auto value = Value::create(signedShort);
    value->read("0");
    Internal::printBitmask(os, *value, nullptr);
    EXPECT_EQ(os.str(), "(none)");
}

// Test with signedShort type, bit 0 set
TEST_F(PrintBitmaskTest_1373, SignedShortBit0Set_1373) {
    auto value = Value::create(signedShort);
    value->read("1");
    Internal::printBitmask(os, *value, nullptr);
    EXPECT_EQ(os.str(), "0");
}

// Test with signedShort type, multiple bits set
TEST_F(PrintBitmaskTest_1373, SignedShortMultipleBitsSet_1373) {
    auto value = Value::create(signedShort);
    value->read("7");
    Internal::printBitmask(os, *value, nullptr);
    EXPECT_EQ(os.str(), "0,1,2");
}

// Test with unsignedShort, value = 256 (bit 8 set)
TEST_F(PrintBitmaskTest_1373, UnsignedShortBit8Set_1373) {
    auto value = Value::create(unsignedShort);
    value->read("256");
    Internal::printBitmask(os, *value, nullptr);
    EXPECT_EQ(os.str(), "8");
}

// Test with unsignedShort, value = 32768 (bit 15 set)
TEST_F(PrintBitmaskTest_1373, UnsignedShortBit15Set_1373) {
    auto value = Value::create(unsignedShort);
    value->read("32768");
    Internal::printBitmask(os, *value, nullptr);
    EXPECT_EQ(os.str(), "15");
}

// Test with multiple elements in the value array (unsignedShort)
// Two elements: first=1 (bit 0), second=1 (bit 16 in overall numbering)
TEST_F(PrintBitmaskTest_1373, UnsignedShortMultipleElements_1373) {
    auto value = Value::create(unsignedShort);
    value->read("1 1");
    Internal::printBitmask(os, *value, nullptr);
    // First element: bit 0 set -> outputs "0"
    // Second element: bit 0 of second word -> overall bit 16
    EXPECT_EQ(os.str(), "0,16");
}

// Test with multiple elements, first=0, second=1 (bit 16 overall)
TEST_F(PrintBitmaskTest_1373, UnsignedShortMultipleElementsFirstZero_1373) {
    auto value = Value::create(unsignedShort);
    value->read("0 1");
    Internal::printBitmask(os, *value, nullptr);
    EXPECT_EQ(os.str(), "16");
}

// Test with multiple elements all zero -> "(none)"
TEST_F(PrintBitmaskTest_1373, UnsignedShortMultipleElementsAllZero_1373) {
    auto value = Value::create(unsignedShort);
    value->read("0 0");
    Internal::printBitmask(os, *value, nullptr);
    EXPECT_EQ(os.str(), "(none)");
}

// Test with non-short type (unsignedLong) - should fall through to printValue
TEST_F(PrintBitmaskTest_1373, UnsignedLongFallsThrough_1373) {
    auto value = Value::create(unsignedLong);
    value->read("42");
    Internal::printBitmask(os, *value, nullptr);
    // Should call printValue instead, which typically prints the value as-is
    EXPECT_FALSE(os.str().empty());
}

// Test with asciiString type - should fall through to printValue
TEST_F(PrintBitmaskTest_1373, AsciiStringFallsThrough_1373) {
    auto value = Value::create(asciiString);
    value->read("hello");
    Internal::printBitmask(os, *value, nullptr);
    EXPECT_FALSE(os.str().empty());
}

// Test with unsignedShort, value = 4 (only bit 2 set)
TEST_F(PrintBitmaskTest_1373, UnsignedShortOnlyBit2Set_1373) {
    auto value = Value::create(unsignedShort);
    value->read("4");
    Internal::printBitmask(os, *value, nullptr);
    EXPECT_EQ(os.str(), "2");
}

// Test with unsignedShort, value = 8 (only bit 3 set)
TEST_F(PrintBitmaskTest_1373, UnsignedShortOnlyBit3Set_1373) {
    auto value = Value::create(unsignedShort);
    value->read("8");
    Internal::printBitmask(os, *value, nullptr);
    EXPECT_EQ(os.str(), "3");
}

// Test with unsignedShort, alternating bits (value = 0xAAAA = 43690, bits 1,3,5,7,9,11,13,15)
TEST_F(PrintBitmaskTest_1373, UnsignedShortAlternatingBits_1373) {
    auto value = Value::create(unsignedShort);
    value->read("43690");  // 0xAAAA
    Internal::printBitmask(os, *value, nullptr);
    EXPECT_EQ(os.str(), "1,3,5,7,9,11,13,15");
}

// Test with unsignedShort, alternating bits (value = 0x5555 = 21845, bits 0,2,4,6,8,10,12,14)
TEST_F(PrintBitmaskTest_1373, UnsignedShortAlternatingBitsOdd_1373) {
    auto value = Value::create(unsignedShort);
    value->read("21845");  // 0x5555
    Internal::printBitmask(os, *value, nullptr);
    EXPECT_EQ(os.str(), "0,2,4,6,8,10,12,14");
}

// Test with three elements in the value array
TEST_F(PrintBitmaskTest_1373, UnsignedShortThreeElements_1373) {
    auto value = Value::create(unsignedShort);
    value->read("1 0 1");
    Internal::printBitmask(os, *value, nullptr);
    // First element bit 0 -> "0", third element bit 0 -> bit 32 overall
    EXPECT_EQ(os.str(), "0,32");
}

// Test with metadata parameter as nullptr (normal operation for short types)
TEST_F(PrintBitmaskTest_1373, NullMetadataWithShortType_1373) {
    auto value = Value::create(unsignedShort);
    value->read("10");  // bits 1 and 3
    Internal::printBitmask(os, *value, nullptr);
    EXPECT_EQ(os.str(), "1,3");
}

// Test return value is the same ostream
TEST_F(PrintBitmaskTest_1373, ReturnsOstream_1373) {
    auto value = Value::create(unsignedShort);
    value->read("1");
    std::ostream& result = Internal::printBitmask(os, *value, nullptr);
    EXPECT_EQ(&result, &os);
}

// Test with ExifData object (non-null metadata) for non-short type
TEST_F(PrintBitmaskTest_1373, NonShortTypeWithMetadata_1373) {
    ExifData exifData;
    auto value = Value::create(unsignedLong);
    value->read("100");
    Internal::printBitmask(os, *value, &exifData);
    EXPECT_FALSE(os.str().empty());
}

// Test single high bit: value = 16384 (bit 14)
TEST_F(PrintBitmaskTest_1373, UnsignedShortBit14Set_1373) {
    auto value = Value::create(unsignedShort);
    value->read("16384");
    Internal::printBitmask(os, *value, nullptr);
    EXPECT_EQ(os.str(), "14");
}

// Test value = 128 (bit 7)
TEST_F(PrintBitmaskTest_1373, UnsignedShortBit7Set_1373) {
    auto value = Value::create(unsignedShort);
    value->read("128");
    Internal::printBitmask(os, *value, nullptr);
    EXPECT_EQ(os.str(), "7");
}
