#include <gtest/gtest.h>
#include <sstream>
#include <string>

#include "exiv2/exif.hpp"
#include "exiv2/tags.hpp"
#include "exiv2/value.hpp"
#include "exiv2/types.hpp"

// Include the internal header for Nikon3MakerNote
// Adjust path as needed based on your build system
#include "nikonmn_int.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

class Nikon3MakerNoteTest_469 : public ::testing::Test {
 protected:
  std::ostringstream os;

  // Helper to create an UnsignedShort value with a single entry
  Value::UniquePtr makeUShortValue(uint16_t val) {
    auto v = Value::create(unsignedShort);
    v->read(std::to_string(val));
    return v;
  }

  // Helper to create ExifData with a specific camera model
  ExifData makeExifDataWithModel(const std::string& model) {
    ExifData exifData;
    ExifKey key("Exif.Image.Model");
    auto v = Value::create(asciiString);
    v->read(model);
    exifData.add(key, v.get());
    return exifData;
  }
};

// Test: When value count != 1, should output parenthesized raw value
TEST_F(Nikon3MakerNoteTest_469, WrongCount_OutputsParenthesized_469) {
  // Create a value with 2 unsigned short entries
  auto v = Value::create(unsignedShort);
  v->read("1 2");
  ASSERT_EQ(v->count(), 2u);

  Nikon3MakerNote::print0x0089(os, *v, nullptr);
  std::string result = os.str();
  EXPECT_EQ(result.front(), '(');
  EXPECT_EQ(result.back(), ')');
}

// Test: When value typeId is not unsignedShort, should output parenthesized raw value
TEST_F(Nikon3MakerNoteTest_469, WrongTypeId_OutputsParenthesized_469) {
  auto v = Value::create(unsignedLong);
  v->read("5");
  ASSERT_EQ(v->count(), 1u);
  ASSERT_NE(v->typeId(), unsignedShort);

  Nikon3MakerNote::print0x0089(os, *v, nullptr);
  std::string result = os.str();
  EXPECT_EQ(result.front(), '(');
  EXPECT_EQ(result.back(), ')');
}

// Test: Value 0 should output "Single-frame"
TEST_F(Nikon3MakerNoteTest_469, ValueZero_SingleFrame_469) {
  auto v = makeUShortValue(0);

  Nikon3MakerNote::print0x0089(os, *v, nullptr);
  std::string result = os.str();
  // Value 0 => "Single-frame"
  EXPECT_NE(result.find("Single-frame"), std::string::npos);
}

// Test: Value with no bits in 0x87 set should start with "Single-frame, "
TEST_F(Nikon3MakerNoteTest_469, NoBitsIn0x87_PrefixesSingleFrame_469) {
  // 0x87 = 0b10000111 = bits 0,1,2,7
  // Value 0x08 (bit 3) has none of bits 0,1,2,7 set, and is non-zero
  auto v = makeUShortValue(0x08);

  Nikon3MakerNote::print0x0089(os, *v, nullptr);
  std::string result = os.str();
  EXPECT_NE(result.find("Single-frame"), std::string::npos);
}

// Test: Value with bits in 0x87 set should NOT start with "Single-frame, "
TEST_F(Nikon3MakerNoteTest_469, BitsIn0x87_NoSingleFramePrefix_469) {
  // 0x01 has bit 0 set, which is in 0x87
  auto v = makeUShortValue(0x01);

  Nikon3MakerNote::print0x0089(os, *v, nullptr);
  std::string result = os.str();
  // Should contain "Continuous" from the bitmask but not "Single-frame, "
  EXPECT_EQ(result.find("Single-frame"), std::string::npos);
}

// Test: Non-D70 model, uses nikonShootingMode bitmask
TEST_F(Nikon3MakerNoteTest_469, NonD70Model_UsesShootingMode_469) {
  auto v = makeUShortValue(0x01); // Continuous
  ExifData exifData = makeExifDataWithModel("Nikon D800");

  Nikon3MakerNote::print0x0089(os, *v, &exifData);
  std::string result = os.str();
  EXPECT_NE(result.find("Continuous"), std::string::npos);
}

// Test: D70 model, uses nikonShootingModeD70 bitmask
TEST_F(Nikon3MakerNoteTest_469, D70Model_UsesD70ShootingMode_469) {
  auto v = makeUShortValue(0x01); // Continuous
  ExifData exifData = makeExifDataWithModel("Nikon D70");

  Nikon3MakerNote::print0x0089(os, *v, &exifData);
  std::string result = os.str();
  EXPECT_NE(result.find("Continuous"), std::string::npos);
}

// Test: D70s model (contains "D70"), should use D70 bitmask
TEST_F(Nikon3MakerNoteTest_469, D70sModel_UsesD70ShootingMode_469) {
  auto v = makeUShortValue(0x04); // bit 2
  ExifData exifData = makeExifDataWithModel("Nikon D70s");

  Nikon3MakerNote::print0x0089(os, *v, &exifData);
  std::string result = os.str();
  // D70 bitmask: bit 2 = "PC control" (lowercase 'c')
  EXPECT_NE(result.find("PC control"), std::string::npos);
}

// Test: Non-D70 model, bit 2 should give "PC Control" (uppercase 'C')
TEST_F(Nikon3MakerNoteTest_469, NonD70Model_PCControl_469) {
  auto v = makeUShortValue(0x04); // bit 2
  ExifData exifData = makeExifDataWithModel("Nikon D800");

  Nikon3MakerNote::print0x0089(os, *v, &exifData);
  std::string result = os.str();
  // Non-D70 bitmask: bit 2 = "PC Control" (uppercase 'C')
  EXPECT_NE(result.find("PC Control"), std::string::npos);
}

// Test: Null metadata, should use non-D70 shooting mode
TEST_F(Nikon3MakerNoteTest_469, NullMetadata_UsesNonD70ShootingMode_469) {
  auto v = makeUShortValue(0x01); // Continuous

  Nikon3MakerNote::print0x0089(os, *v, nullptr);
  std::string result = os.str();
  EXPECT_NE(result.find("Continuous"), std::string::npos);
}

// Test: Metadata without model key, should use non-D70 shooting mode
TEST_F(Nikon3MakerNoteTest_469, MetadataWithoutModel_UsesNonD70ShootingMode_469) {
  auto v = makeUShortValue(0x04); // PC Control
  ExifData exifData; // Empty, no model

  Nikon3MakerNote::print0x0089(os, *v, &exifData);
  std::string result = os.str();
  EXPECT_NE(result.find("PC Control"), std::string::npos);
}

// Test: Multiple bits set in shooting mode
TEST_F(Nikon3MakerNoteTest_469, MultipleBitsSet_469) {
  // 0x03 = bits 0 and 1 => "Continuous" and "Delay"
  auto v = makeUShortValue(0x03);

  Nikon3MakerNote::print0x0089(os, *v, nullptr);
  std::string result = os.str();
  EXPECT_NE(result.find("Continuous"), std::string::npos);
  EXPECT_NE(result.find("Delay"), std::string::npos);
}

// Test: Self-timer bit (bit 3, value 0x08) with no 0x87 bits
TEST_F(Nikon3MakerNoteTest_469, SelfTimerBit_WithSingleFramePrefix_469) {
  // 0x08 = bit 3 = "Self-timer", and bits 0,1,2,7 are not set so "Single-frame, " prefix
  auto v = makeUShortValue(0x08);

  Nikon3MakerNote::print0x0089(os, *v, nullptr);
  std::string result = os.str();
  EXPECT_NE(result.find("Single-frame"), std::string::npos);
  EXPECT_NE(result.find("Self-timer"), std::string::npos);
}

// Test: Exposure Bracketing bit (bit 4, value 0x10)
TEST_F(Nikon3MakerNoteTest_469, ExposureBracketing_469) {
  auto v = makeUShortValue(0x10);

  Nikon3MakerNote::print0x0089(os, *v, nullptr);
  std::string result = os.str();
  EXPECT_NE(result.find("Exposure Bracketing"), std::string::npos);
}

// Test: Auto ISO bit (bit 5, value 0x20)
TEST_F(Nikon3MakerNoteTest_469, AutoISO_469) {
  auto v = makeUShortValue(0x20);

  Nikon3MakerNote::print0x0089(os, *v, nullptr);
  std::string result = os.str();
  EXPECT_NE(result.find("Auto ISO"), std::string::npos);
}

// Test: White-Balance Bracketing bit (bit 6, value 0x40)
TEST_F(Nikon3MakerNoteTest_469, WhiteBalanceBracketing_469) {
  auto v = makeUShortValue(0x40);

  Nikon3MakerNote::print0x0089(os, *v, nullptr);
  std::string result = os.str();
  EXPECT_NE(result.find("White-Balance Bracketing"), std::string::npos);
}

// Test: IR Control bit (bit 7, value 0x80), this bit is in 0x87
TEST_F(Nikon3MakerNoteTest_469, IRControl_469) {
  auto v = makeUShortValue(0x80);

  Nikon3MakerNote::print0x0089(os, *v, nullptr);
  std::string result = os.str();
  // bit 7 is in 0x87, so no "Single-frame" prefix
  EXPECT_EQ(result.find("Single-frame"), std::string::npos);
  EXPECT_NE(result.find("IR Control"), std::string::npos);
}

// Test: D-Lighting Bracketing bit (bit 8, value 0x100)
TEST_F(Nikon3MakerNoteTest_469, DLightingBracketing_469) {
  auto v = makeUShortValue(0x100);

  Nikon3MakerNote::print0x0089(os, *v, nullptr);
  std::string result = os.str();
  // 0x100 has no bits in 0x87, so "Single-frame, " prefix
  EXPECT_NE(result.find("Single-frame"), std::string::npos);
  EXPECT_NE(result.find("D-Lighting Bracketing"), std::string::npos);
}

// Test: D70 with specific bits - "Unused LE-NR slowdown" (bit 5, 0x20) only in D70 bitmask
TEST_F(Nikon3MakerNoteTest_469, D70_UnusedLENRSlowdown_469) {
  auto v = makeUShortValue(0x20); // bit 5
  ExifData exifData = makeExifDataWithModel("Nikon D70");

  Nikon3MakerNote::print0x0089(os, *v, &exifData);
  std::string result = os.str();
  // D70 bitmask: bit 5 = "Unused LE-NR slowdown"
  EXPECT_NE(result.find("Unused LE-NR slowdown"), std::string::npos);
}

// Test: Return value is the same ostream reference
TEST_F(Nikon3MakerNoteTest_469, ReturnsOstreamReference_469) {
  auto v = makeUShortValue(0);

  std::ostream& ret = Nikon3MakerNote::print0x0089(os, *v, nullptr);
  EXPECT_EQ(&ret, &os);
}

// Test: Return value is the same ostream reference for error case
TEST_F(Nikon3MakerNoteTest_469, ReturnsOstreamReferenceOnError_469) {
  auto v = Value::create(unsignedLong);
  v->read("5");

  std::ostream& ret = Nikon3MakerNote::print0x0089(os, *v, nullptr);
  EXPECT_EQ(&ret, &os);
}

// Test: signed short type should output parenthesized
TEST_F(Nikon3MakerNoteTest_469, SignedShortType_OutputsParenthesized_469) {
  auto v = Value::create(signedShort);
  v->read("1");
  ASSERT_EQ(v->count(), 1u);
  ASSERT_NE(v->typeId(), unsignedShort);

  Nikon3MakerNote::print0x0089(os, *v, nullptr);
  std::string result = os.str();
  EXPECT_EQ(result.front(), '(');
  EXPECT_EQ(result.back(), ')');
}

// Test: Empty value (count 0) should output parenthesized
TEST_F(Nikon3MakerNoteTest_469, EmptyValue_OutputsParenthesized_469) {
  auto v = Value::create(unsignedShort);
  // Don't read any value, count should be 0
  ASSERT_EQ(v->count(), 0u);

  Nikon3MakerNote::print0x0089(os, *v, nullptr);
  std::string result = os.str();
  EXPECT_EQ(result.front(), '(');
  EXPECT_EQ(result.back(), ')');
}
