// =================================================================================================
// TEST_ID 2064
// Unit tests for CodePoint_from_UTF8_Multi (./TestProjects/exiv2/xmpsdk/src/UnicodeConversions.cpp)
// =================================================================================================

#include <gtest/gtest.h>

#include <cstddef>
#include <cstdint>

// Include the implementation file directly so we can call the internal `static` function.
// This is a common technique for testing internal-linkage helpers without changing production code.
#include "TestProjects/exiv2/xmpsdk/src/UnicodeConversions.cpp"

namespace {

class UnicodeConversionsTest_2064 : public ::testing::Test {
protected:
  static void Call(const UTF8Unit* in, size_t len, UTF32Unit* outCp, size_t* outRead) {
    CodePoint_from_UTF8_Multi(in, len, outCp, outRead);
  }
};

TEST_F(UnicodeConversionsTest_2064, DecodesValidTwoByteSequence_2064) {
  // U+00A2 (¢) => C2 A2
  const UTF8Unit bytes[] = {UTF8Unit(0xC2), UTF8Unit(0xA2)};
  UTF32Unit cp = 0;
  size_t read = 999;

  EXPECT_NO_THROW(Call(bytes, sizeof(bytes), &cp, &read));
  EXPECT_EQ(read, size_t(2));
  EXPECT_EQ(cp, UTF32Unit(0x00A2));
}

TEST_F(UnicodeConversionsTest_2064, DecodesValidThreeByteSequence_2064) {
  // U+20AC (€) => E2 82 AC
  const UTF8Unit bytes[] = {UTF8Unit(0xE2), UTF8Unit(0x82), UTF8Unit(0xAC)};
  UTF32Unit cp = 0;
  size_t read = 999;

  EXPECT_NO_THROW(Call(bytes, sizeof(bytes), &cp, &read));
  EXPECT_EQ(read, size_t(3));
  EXPECT_EQ(cp, UTF32Unit(0x20AC));
}

TEST_F(UnicodeConversionsTest_2064, DecodesValidFourByteSequence_2064) {
  // U+1F600 (😀) => F0 9F 98 80
  const UTF8Unit bytes[] = {UTF8Unit(0xF0), UTF8Unit(0x9F), UTF8Unit(0x98), UTF8Unit(0x80)};
  UTF32Unit cp = 0;
  size_t read = 999;

  EXPECT_NO_THROW(Call(bytes, sizeof(bytes), &cp, &read));
  EXPECT_EQ(read, size_t(4));
  EXPECT_EQ(cp, UTF32Unit(0x1F600));
}

TEST_F(UnicodeConversionsTest_2064, NotEnoughInputLeavesReadAsZeroAndDoesNotModifyCp_2064) {
  // Lead byte indicates a 3-byte sequence, but we only provide 2 bytes.
  const UTF8Unit bytes[] = {UTF8Unit(0xE2), UTF8Unit(0x82)}; // partial for U+20AC
  UTF32Unit cp = UTF32Unit(0xDEADBEEF); // sentinel
  size_t read = 999;

  EXPECT_NO_THROW(Call(bytes, sizeof(bytes), &cp, &read));
  EXPECT_EQ(read, size_t(0));
  EXPECT_EQ(cp, UTF32Unit(0xDEADBEEF)); // should remain unchanged when no full input is consumed
}

TEST_F(UnicodeConversionsTest_2064, ThrowsOnInvalidSequenceLength_ContinuationAsLead_2064) {
  // A continuation byte (10xxxxxx) as the first byte implies an invalid sequence length.
  const UTF8Unit bytes[] = {UTF8Unit(0x80)};
  UTF32Unit cp = 0;
  size_t read = 999;

  EXPECT_ANY_THROW(Call(bytes, sizeof(bytes), &cp, &read));
}

TEST_F(UnicodeConversionsTest_2064, ThrowsOnInvalidSequenceLength_FiveByteLead_2064) {
  // 0xF8 would imply a 5-byte sequence, which is invalid for UTF-8.
  const UTF8Unit bytes[] = {UTF8Unit(0xF8), UTF8Unit(0x80), UTF8Unit(0x80), UTF8Unit(0x80), UTF8Unit(0x80)};
  UTF32Unit cp = 0;
  size_t read = 999;

  EXPECT_ANY_THROW(Call(bytes, sizeof(bytes), &cp, &read));
}

TEST_F(UnicodeConversionsTest_2064, ThrowsOnInvalidDataByte_NotAContinuation_2064) {
  // Lead indicates 3 bytes, but the next byte is not 10xxxxxx.
  const UTF8Unit bytes[] = {UTF8Unit(0xE2), UTF8Unit(0x28), UTF8Unit(0xA1)};
  UTF32Unit cp = 0;
  size_t read = 999;

  EXPECT_ANY_THROW(Call(bytes, sizeof(bytes), &cp, &read));
}

TEST_F(UnicodeConversionsTest_2064, ThrowsOnSurrogateCodePoint_2064) {
  // UTF-8 encoding for U+D800 (a surrogate) => ED A0 80 (must be rejected).
  const UTF8Unit bytes[] = {UTF8Unit(0xED), UTF8Unit(0xA0), UTF8Unit(0x80)};
  UTF32Unit cp = 0;
  size_t read = 999;

  EXPECT_ANY_THROW(Call(bytes, sizeof(bytes), &cp, &read));
}

TEST_F(UnicodeConversionsTest_2064, ThrowsOnOutOfRangeCodePoint_2064) {
  // Code point > 0x10FFFF, e.g. U+110000 encoded as F4 90 80 80 (must be rejected).
  const UTF8Unit bytes[] = {UTF8Unit(0xF4), UTF8Unit(0x90), UTF8Unit(0x80), UTF8Unit(0x80)};
  UTF32Unit cp = 0;
  size_t read = 999;

  EXPECT_ANY_THROW(Call(bytes, sizeof(bytes), &cp, &read));
}

} // namespace