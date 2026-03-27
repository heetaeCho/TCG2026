// =================================================================================================
// TEST_ID: 2050
// File: test_UnicodeConversions_2050.cpp
// Unit tests for: ./TestProjects/exiv2/xmpsdk/src/UnicodeConversions.cpp
// =================================================================================================

#include <gtest/gtest.h>
#include <cstdint>

// Include the implementation unit to access its internal static inline helpers.
// This is intentional: UTF16InSwap has internal linkage (static) in the .cpp file.
#include "TestProjects/exiv2/xmpsdk/src/UnicodeConversions.cpp"

namespace {

class UnicodeConversionsTest_2050 : public ::testing::Test {};

TEST_F(UnicodeConversionsTest_2050, UTF16InSwap_SwapsBytesForTypicalValue_2050) {
  const UTF16Unit in = static_cast<UTF16Unit>(0x1234);
  const UTF16Unit out = UTF16InSwap(&in);
  EXPECT_EQ(out, static_cast<UTF16Unit>(0x3412));
  EXPECT_EQ(in, static_cast<UTF16Unit>(0x1234));  // input must not be modified
}

TEST_F(UnicodeConversionsTest_2050, UTF16InSwap_ZeroRemainsZero_2050) {
  const UTF16Unit in = static_cast<UTF16Unit>(0x0000);
  EXPECT_EQ(UTF16InSwap(&in), static_cast<UTF16Unit>(0x0000));
}

TEST_F(UnicodeConversionsTest_2050, UTF16InSwap_LowByteOnlyMovesToHighByte_2050) {
  const UTF16Unit in = static_cast<UTF16Unit>(0x00FF);
  EXPECT_EQ(UTF16InSwap(&in), static_cast<UTF16Unit>(0xFF00));
}

TEST_F(UnicodeConversionsTest_2050, UTF16InSwap_HighByteOnlyMovesToLowByte_2050) {
  const UTF16Unit in = static_cast<UTF16Unit>(0xFF00);
  EXPECT_EQ(UTF16InSwap(&in), static_cast<UTF16Unit>(0x00FF));
}

TEST_F(UnicodeConversionsTest_2050, UTF16InSwap_MaxValueRemainsMaxValue_2050) {
  const UTF16Unit in = static_cast<UTF16Unit>(0xFFFF);
  EXPECT_EQ(UTF16InSwap(&in), static_cast<UTF16Unit>(0xFFFF));
}

TEST_F(UnicodeConversionsTest_2050, UTF16InSwap_SwapsBytesForAnotherPattern_2050) {
  const UTF16Unit in = static_cast<UTF16Unit>(0xABCD);
  EXPECT_EQ(UTF16InSwap(&in), static_cast<UTF16Unit>(0xCDAB));
}

TEST_F(UnicodeConversionsTest_2050, UTF16InSwap_DoubleSwapReturnsOriginal_2050) {
  const UTF16Unit original = static_cast<UTF16Unit>(0x4E21);
  const UTF16Unit swapped = UTF16InSwap(&original);

  // Apply swap again using a second variable to keep the original const-correct in this test.
  const UTF16Unit swapped_copy = swapped;
  const UTF16Unit roundtrip = UTF16InSwap(&swapped_copy);

  EXPECT_EQ(roundtrip, original);
}

TEST_F(UnicodeConversionsTest_2050, UTF16InSwap_NullptrDeathIfSupported_2050) {
  // The interface requires a pointer; passing nullptr is an invalid use.
  // If supported, verify it fails fast (observable as a process death).
  EXPECT_DEATH_IF_SUPPORTED({ (void)UTF16InSwap(nullptr); }, "");
}

}  // namespace