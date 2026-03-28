// File: ./TestProjects/yaml-cpp/test/stream_utf8adjust_test_170.cpp

#include <gtest/gtest.h>
#include <cstdint>

namespace YAML {
// Forward declaration: definition is provided by the production TU
// (./TestProjects/yaml-cpp/src/stream.cpp) that is linked into the test binary.
char Utf8Adjust(unsigned long ch, unsigned char lead_bits, unsigned char rshift);
}  // namespace YAML

namespace {

class Utf8AdjustTest_170 : public ::testing::Test {
protected:
  static unsigned char U8(char c) { return static_cast<unsigned char>(c); }
};

TEST_F(Utf8AdjustTest_170, TwoByteSequence_Cent_U00A2_170) {
  // U+00A2 '¢' => UTF-8: C2 A2
  const unsigned long ch = 0x00A2UL;

  const unsigned char b0 = U8(YAML::Utf8Adjust(ch, /*lead_bits=*/3, /*rshift=*/6));
  const unsigned char b1 = U8(YAML::Utf8Adjust(ch, /*lead_bits=*/2, /*rshift=*/0));

  EXPECT_EQ(b0, 0xC2);
  EXPECT_EQ(b1, 0xA2);
}

TEST_F(Utf8AdjustTest_170, TwoByteSequence_MinU0080_170) {
  // U+0080 => UTF-8: C2 80
  const unsigned long ch = 0x0080UL;

  const unsigned char b0 = U8(YAML::Utf8Adjust(ch, 3, 6));
  const unsigned char b1 = U8(YAML::Utf8Adjust(ch, 2, 0));

  EXPECT_EQ(b0, 0xC2);
  EXPECT_EQ(b1, 0x80);
}

TEST_F(Utf8AdjustTest_170, TwoByteSequence_MaxU07FF_170) {
  // U+07FF => UTF-8: DF BF
  const unsigned long ch = 0x07FFUL;

  const unsigned char b0 = U8(YAML::Utf8Adjust(ch, 3, 6));
  const unsigned char b1 = U8(YAML::Utf8Adjust(ch, 2, 0));

  EXPECT_EQ(b0, 0xDF);
  EXPECT_EQ(b1, 0xBF);
}

TEST_F(Utf8AdjustTest_170, ThreeByteSequence_Euro_U20AC_170) {
  // U+20AC '€' => UTF-8: E2 82 AC
  const unsigned long ch = 0x20ACUL;

  const unsigned char b0 = U8(YAML::Utf8Adjust(ch, /*lead_bits=*/4, /*rshift=*/12));
  const unsigned char b1 = U8(YAML::Utf8Adjust(ch, /*lead_bits=*/2, /*rshift=*/6));
  const unsigned char b2 = U8(YAML::Utf8Adjust(ch, /*lead_bits=*/2, /*rshift=*/0));

  EXPECT_EQ(b0, 0xE2);
  EXPECT_EQ(b1, 0x82);
  EXPECT_EQ(b2, 0xAC);
}

TEST_F(Utf8AdjustTest_170, ThreeByteSequence_MaxUFFFF_170) {
  // U+FFFF => UTF-8: EF BF BF
  const unsigned long ch = 0xFFFFUL;

  const unsigned char b0 = U8(YAML::Utf8Adjust(ch, 4, 12));
  const unsigned char b1 = U8(YAML::Utf8Adjust(ch, 2, 6));
  const unsigned char b2 = U8(YAML::Utf8Adjust(ch, 2, 0));

  EXPECT_EQ(b0, 0xEF);
  EXPECT_EQ(b1, 0xBF);
  EXPECT_EQ(b2, 0xBF);
}

TEST_F(Utf8AdjustTest_170, FourByteSequence_GrinningFace_U1F600_170) {
  // U+1F600 '😀' => UTF-8: F0 9F 98 80
  const unsigned long ch = 0x1F600UL;

  const unsigned char b0 = U8(YAML::Utf8Adjust(ch, /*lead_bits=*/5, /*rshift=*/18));
  const unsigned char b1 = U8(YAML::Utf8Adjust(ch, /*lead_bits=*/2, /*rshift=*/12));
  const unsigned char b2 = U8(YAML::Utf8Adjust(ch, /*lead_bits=*/2, /*rshift=*/6));
  const unsigned char b3 = U8(YAML::Utf8Adjust(ch, /*lead_bits=*/2, /*rshift=*/0));

  EXPECT_EQ(b0, 0xF0);
  EXPECT_EQ(b1, 0x9F);
  EXPECT_EQ(b2, 0x98);
  EXPECT_EQ(b3, 0x80);
}

TEST_F(Utf8AdjustTest_170, FourByteSequence_MaxU10FFFF_170) {
  // U+10FFFF => UTF-8: F4 8F BF BF
  const unsigned long ch = 0x10FFFFUL;

  const unsigned char b0 = U8(YAML::Utf8Adjust(ch, 5, 18));
  const unsigned char b1 = U8(YAML::Utf8Adjust(ch, 2, 12));
  const unsigned char b2 = U8(YAML::Utf8Adjust(ch, 2, 6));
  const unsigned char b3 = U8(YAML::Utf8Adjust(ch, 2, 0));

  EXPECT_EQ(b0, 0xF4);
  EXPECT_EQ(b1, 0x8F);
  EXPECT_EQ(b2, 0xBF);
  EXPECT_EQ(b3, 0xBF);
}

TEST_F(Utf8AdjustTest_170, Boundary_RShiftBeyondCodepointBits_ProducesHeaderOnlyBits_170) {
  // Boundary-style check: when shifting beyond the codepoint's significant bits,
  // the payload bits should be zero, so the result becomes just the UTF-8 header for that lead_bits.
  const unsigned long ch = 0x41UL;  // 'A' (small value), used only as a convenient input.
  const unsigned char b = U8(YAML::Utf8Adjust(ch, /*lead_bits=*/3, /*rshift=*/24));

  // For a 2-byte leading byte (110xxxxx), with all payload bits zero => 11000000 (0xC0).
  EXPECT_EQ(b, 0xC0);
}

}  // namespace