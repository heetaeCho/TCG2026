#include <gtest/gtest.h>
#include <sstream>
#include <exiv2/exiv2.hpp>
#include "tags_int.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

// Define test bitmask arrays

// Array with a zero-mask entry first (for the val==0 case)
static constexpr TagDetailsBitmask bitmaskWithZero[] = {
    {0x0000, "None"},
    {0x0001, "Bit0"},
    {0x0002, "Bit1"},
    {0x0004, "Bit2"},
};

// Array without a zero-mask entry first
static constexpr TagDetailsBitmask bitmaskNoZero[] = {
    {0x0001, "Alpha"},
    {0x0002, "Beta"},
    {0x0004, "Gamma"},
    {0x0008, "Delta"},
};

// Single element array with zero mask
static constexpr TagDetailsBitmask bitmaskSingleZero[] = {
    {0x0000, "Empty"},
};

// Single element array with non-zero mask
static constexpr TagDetailsBitmask bitmaskSingleNonZero[] = {
    {0x0001, "OnlyBit"},
};

class PrintTagBitmaskTest_184 : public ::testing::Test {
 protected:
  std::ostringstream os;
};

// Test: When value is 0 and first entry has mask 0, print the first entry's label
TEST_F(PrintTagBitmaskTest_184, ZeroValueWithZeroMaskEntry_184) {
  Exiv2::UShortValue value;
  value.read("0");
  printTagBitmask<std::size(bitmaskWithZero), bitmaskWithZero>(os, value, nullptr);
  EXPECT_EQ(os.str(), "None");
}

// Test: When value is 0 and first entry does NOT have mask 0, nothing is printed
TEST_F(PrintTagBitmaskTest_184, ZeroValueWithoutZeroMaskEntry_184) {
  Exiv2::UShortValue value;
  value.read("0");
  printTagBitmask<std::size(bitmaskNoZero), bitmaskNoZero>(os, value, nullptr);
  EXPECT_EQ(os.str(), "");
}

// Test: Single bit set matches single entry
TEST_F(PrintTagBitmaskTest_184, SingleBitSet_184) {
  Exiv2::UShortValue value;
  value.read("1");
  printTagBitmask<std::size(bitmaskNoZero), bitmaskNoZero>(os, value, nullptr);
  EXPECT_EQ(os.str(), "Alpha");
}

// Test: Multiple bits set prints comma-separated labels
TEST_F(PrintTagBitmaskTest_184, MultipleBitsSet_184) {
  Exiv2::UShortValue value;
  value.read("3"); // 0x0001 | 0x0002
  printTagBitmask<std::size(bitmaskNoZero), bitmaskNoZero>(os, value, nullptr);
  EXPECT_EQ(os.str(), "Alpha, Beta");
}

// Test: All bits set in the array
TEST_F(PrintTagBitmaskTest_184, AllBitsSet_184) {
  Exiv2::UShortValue value;
  value.read("15"); // 0x000F = all four bits
  printTagBitmask<std::size(bitmaskNoZero), bitmaskNoZero>(os, value, nullptr);
  EXPECT_EQ(os.str(), "Alpha, Beta, Gamma, Delta");
}

// Test: Value has bits set that don't match any entry
TEST_F(PrintTagBitmaskTest_184, NoMatchingBits_184) {
  Exiv2::UShortValue value;
  value.read("16"); // 0x0010, no matching mask
  printTagBitmask<std::size(bitmaskNoZero), bitmaskNoZero>(os, value, nullptr);
  EXPECT_EQ(os.str(), "");
}

// Test: Partial match - some bits match, some don't
TEST_F(PrintTagBitmaskTest_184, PartialMatch_184) {
  Exiv2::UShortValue value;
  value.read("5"); // 0x0001 | 0x0004
  printTagBitmask<std::size(bitmaskNoZero), bitmaskNoZero>(os, value, nullptr);
  EXPECT_EQ(os.str(), "Alpha, Gamma");
}

// Test: Non-zero value with array that has zero-mask first entry (zero mask entry skipped in loop)
TEST_F(PrintTagBitmaskTest_184, NonZeroValueWithZeroMaskArray_184) {
  Exiv2::UShortValue value;
  value.read("1");
  printTagBitmask<std::size(bitmaskWithZero), bitmaskWithZero>(os, value, nullptr);
  EXPECT_EQ(os.str(), "Bit0");
}

// Test: Single element array with zero mask, value is 0
TEST_F(PrintTagBitmaskTest_184, SingleZeroMaskZeroValue_184) {
  Exiv2::UShortValue value;
  value.read("0");
  printTagBitmask<std::size(bitmaskSingleZero), bitmaskSingleZero>(os, value, nullptr);
  EXPECT_EQ(os.str(), "Empty");
}

// Test: Single element array with non-zero mask, matching value
TEST_F(PrintTagBitmaskTest_184, SingleNonZeroMaskMatchingValue_184) {
  Exiv2::UShortValue value;
  value.read("1");
  printTagBitmask<std::size(bitmaskSingleNonZero), bitmaskSingleNonZero>(os, value, nullptr);
  EXPECT_EQ(os.str(), "OnlyBit");
}

// Test: Single element array with non-zero mask, non-matching value
TEST_F(PrintTagBitmaskTest_184, SingleNonZeroMaskNonMatchingValue_184) {
  Exiv2::UShortValue value;
  value.read("2");
  printTagBitmask<std::size(bitmaskSingleNonZero), bitmaskSingleNonZero>(os, value, nullptr);
  EXPECT_EQ(os.str(), "");
}

// Test: Middle bit only
TEST_F(PrintTagBitmaskTest_184, MiddleBitOnly_184) {
  Exiv2::UShortValue value;
  value.read("4"); // 0x0004
  printTagBitmask<std::size(bitmaskNoZero), bitmaskNoZero>(os, value, nullptr);
  EXPECT_EQ(os.str(), "Gamma");
}

// Test: Last bit only
TEST_F(PrintTagBitmaskTest_184, LastBitOnly_184) {
  Exiv2::UShortValue value;
  value.read("8"); // 0x0008
  printTagBitmask<std::size(bitmaskNoZero), bitmaskNoZero>(os, value, nullptr);
  EXPECT_EQ(os.str(), "Delta");
}

// Test: ExifData pointer is null (should work fine, it's unused)
TEST_F(PrintTagBitmaskTest_184, NullExifDataPointer_184) {
  Exiv2::UShortValue value;
  value.read("3");
  printTagBitmask<std::size(bitmaskNoZero), bitmaskNoZero>(os, value, nullptr);
  EXPECT_EQ(os.str(), "Alpha, Beta");
}

// Test: Large value with high bits
TEST_F(PrintTagBitmaskTest_184, HighBitValue_184) {
  Exiv2::ULongValue value;
  value.read("65535"); // 0xFFFF
  printTagBitmask<std::size(bitmaskNoZero), bitmaskNoZero>(os, value, nullptr);
  EXPECT_EQ(os.str(), "Alpha, Beta, Gamma, Delta");
}

// Test: Returns ostream reference
TEST_F(PrintTagBitmaskTest_184, ReturnsOstreamReference_184) {
  Exiv2::UShortValue value;
  value.read("1");
  auto& result = printTagBitmask<std::size(bitmaskNoZero), bitmaskNoZero>(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}
