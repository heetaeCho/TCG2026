#include <gtest/gtest.h>
#include <sstream>
#include <cstdint>

// Minimal mock/stub for Exiv2 types needed by the interface
namespace Exiv2 {

struct ExifData {};

class Value {
 public:
  virtual ~Value() = default;
  virtual uint32_t toUint32(long n = 0) const = 0;
};

namespace Internal {

class Nikon3MakerNote {
 public:
  std::ostream& print0x0083(std::ostream& os, const Value& value, const ExifData*) {
    const uint32_t lensType = value.toUint32();
    bool valid = false;
    if (lensType & 1) {
      os << "MF ";
      valid = true;
    }
    if (lensType & 2) {
      os << "D ";
      valid = true;
    }
    if (lensType & 4) {
      os << "G ";
      valid = true;
    }
    if (lensType & 8) {
      os << "VR";
      valid = true;
    }
    if (!valid)
      os << "(" << lensType << ")";
    return os;
  }
};

}  // namespace Internal
}  // namespace Exiv2

// A concrete mock Value for testing
class MockValue : public Exiv2::Value {
 public:
  explicit MockValue(uint32_t v) : val_(v) {}
  uint32_t toUint32(long /*n*/ = 0) const override { return val_; }

 private:
  uint32_t val_;
};

class Nikon3MakerNoteTest_463 : public ::testing::Test {
 protected:
  Exiv2::Internal::Nikon3MakerNote maker_;
  std::ostringstream os_;
};

// Test: lensType == 0, no flags set => should print "(0)"
TEST_F(Nikon3MakerNoteTest_463, NoFlagsSet_PrintsRawValue_463) {
  MockValue val(0);
  maker_.print0x0083(os_, val, nullptr);
  EXPECT_EQ(os_.str(), "(0)");
}

// Test: lensType == 1 => MF only
TEST_F(Nikon3MakerNoteTest_463, MFOnly_463) {
  MockValue val(1);
  maker_.print0x0083(os_, val, nullptr);
  EXPECT_EQ(os_.str(), "MF ");
}

// Test: lensType == 2 => D only
TEST_F(Nikon3MakerNoteTest_463, DOnly_463) {
  MockValue val(2);
  maker_.print0x0083(os_, val, nullptr);
  EXPECT_EQ(os_.str(), "D ");
}

// Test: lensType == 4 => G only
TEST_F(Nikon3MakerNoteTest_463, GOnly_463) {
  MockValue val(4);
  maker_.print0x0083(os_, val, nullptr);
  EXPECT_EQ(os_.str(), "G ");
}

// Test: lensType == 8 => VR only
TEST_F(Nikon3MakerNoteTest_463, VROnly_463) {
  MockValue val(8);
  maker_.print0x0083(os_, val, nullptr);
  EXPECT_EQ(os_.str(), "VR");
}

// Test: lensType == 3 => MF + D
TEST_F(Nikon3MakerNoteTest_463, MFAndD_463) {
  MockValue val(3);
  maker_.print0x0083(os_, val, nullptr);
  EXPECT_EQ(os_.str(), "MF D ");
}

// Test: lensType == 5 => MF + G
TEST_F(Nikon3MakerNoteTest_463, MFAndG_463) {
  MockValue val(5);
  maker_.print0x0083(os_, val, nullptr);
  EXPECT_EQ(os_.str(), "MF G ");
}

// Test: lensType == 6 => D + G
TEST_F(Nikon3MakerNoteTest_463, DAndG_463) {
  MockValue val(6);
  maker_.print0x0083(os_, val, nullptr);
  EXPECT_EQ(os_.str(), "D G ");
}

// Test: lensType == 9 => MF + VR
TEST_F(Nikon3MakerNoteTest_463, MFAndVR_463) {
  MockValue val(9);
  maker_.print0x0083(os_, val, nullptr);
  EXPECT_EQ(os_.str(), "MF VR");
}

// Test: lensType == 10 => D + VR
TEST_F(Nikon3MakerNoteTest_463, DAndVR_463) {
  MockValue val(10);
  maker_.print0x0083(os_, val, nullptr);
  EXPECT_EQ(os_.str(), "D VR");
}

// Test: lensType == 12 => G + VR
TEST_F(Nikon3MakerNoteTest_463, GAndVR_463) {
  MockValue val(12);
  maker_.print0x0083(os_, val, nullptr);
  EXPECT_EQ(os_.str(), "G VR");
}

// Test: lensType == 7 => MF + D + G
TEST_F(Nikon3MakerNoteTest_463, MFAndDAndG_463) {
  MockValue val(7);
  maker_.print0x0083(os_, val, nullptr);
  EXPECT_EQ(os_.str(), "MF D G ");
}

// Test: lensType == 15 => all flags set: MF + D + G + VR
TEST_F(Nikon3MakerNoteTest_463, AllFlagsSet_463) {
  MockValue val(15);
  maker_.print0x0083(os_, val, nullptr);
  EXPECT_EQ(os_.str(), "MF D G VR");
}

// Test: lensType == 11 => MF + D + VR
TEST_F(Nikon3MakerNoteTest_463, MFAndDAndVR_463) {
  MockValue val(11);
  maker_.print0x0083(os_, val, nullptr);
  EXPECT_EQ(os_.str(), "MF D VR");
}

// Test: lensType == 13 => MF + G + VR
TEST_F(Nikon3MakerNoteTest_463, MFAndGAndVR_463) {
  MockValue val(13);
  maker_.print0x0083(os_, val, nullptr);
  EXPECT_EQ(os_.str(), "MF G VR");
}

// Test: lensType == 14 => D + G + VR
TEST_F(Nikon3MakerNoteTest_463, DAndGAndVR_463) {
  MockValue val(14);
  maker_.print0x0083(os_, val, nullptr);
  EXPECT_EQ(os_.str(), "D G VR");
}

// Test: lensType == 16 => no known bits in low 4, but non-zero => prints "(16)"
TEST_F(Nikon3MakerNoteTest_463, UnknownBitsOnly_463) {
  MockValue val(16);
  maker_.print0x0083(os_, val, nullptr);
  EXPECT_EQ(os_.str(), "(16)");
}

// Test: lensType == 32 => another unknown bit only => prints "(32)"
TEST_F(Nikon3MakerNoteTest_463, HigherUnknownBit_463) {
  MockValue val(32);
  maker_.print0x0083(os_, val, nullptr);
  EXPECT_EQ(os_.str(), "(32)");
}

// Test: lensType with both known and unknown bits (e.g., 17 = 16 | 1) => MF is printed since bit 0 is set
TEST_F(Nikon3MakerNoteTest_463, MixedKnownAndUnknownBits_463) {
  MockValue val(17);  // 0x11 = bit 0 (MF) + bit 4 (unknown)
  maker_.print0x0083(os_, val, nullptr);
  EXPECT_EQ(os_.str(), "MF ");
}

// Test: lensType == 255 => all low 4 bits set plus higher bits
TEST_F(Nikon3MakerNoteTest_463, AllBitsInByte_463) {
  MockValue val(255);
  maker_.print0x0083(os_, val, nullptr);
  EXPECT_EQ(os_.str(), "MF D G VR");
}

// Test: return value is the same ostream reference
TEST_F(Nikon3MakerNoteTest_463, ReturnsOstreamReference_463) {
  MockValue val(0);
  std::ostream& result = maker_.print0x0083(os_, val, nullptr);
  EXPECT_EQ(&result, &os_);
}

// Test: ExifData pointer is nullptr (common case, should work fine)
TEST_F(Nikon3MakerNoteTest_463, NullExifDataPointer_463) {
  MockValue val(8);
  maker_.print0x0083(os_, val, nullptr);
  EXPECT_EQ(os_.str(), "VR");
}

// Test: ExifData pointer is non-null (should not affect output)
TEST_F(Nikon3MakerNoteTest_463, NonNullExifDataPointer_463) {
  MockValue val(8);
  Exiv2::ExifData exifData;
  maker_.print0x0083(os_, val, &exifData);
  EXPECT_EQ(os_.str(), "VR");
}

// Test: large value with no known bits
TEST_F(Nikon3MakerNoteTest_463, LargeValueNoKnownBits_463) {
  MockValue val(0xFFFFFFF0);
  maker_.print0x0083(os_, val, nullptr);
  // No bits 0-3 set, so it prints the raw value
  std::ostringstream expected;
  expected << "(" << 0xFFFFFFF0u << ")";
  EXPECT_EQ(os_.str(), expected.str());
}

// Test: large value with all known bits set
TEST_F(Nikon3MakerNoteTest_463, LargeValueAllKnownBitsSet_463) {
  MockValue val(0xFFFFFFFF);
  maker_.print0x0083(os_, val, nullptr);
  EXPECT_EQ(os_.str(), "MF D G VR");
}
