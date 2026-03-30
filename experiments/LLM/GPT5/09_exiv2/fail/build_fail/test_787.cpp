// =================================================================================================
// TEST_ID: 787
// File: test_value_setDataArea_787.cpp
// Unit tests for: Exiv2::Value::setDataArea(const byte*, size_t)
// =================================================================================================

#include <gtest/gtest.h>

#include <cstddef>
#include <cstdint>

// Include the library header if available in your build.
// If your project already includes Exiv2 headers via other means, keep this include as-is.
// If compilation fails due to missing header paths, adjust to your project's include layout.
#include "value.hpp"

namespace {

// Provide a minimal fallback for Exiv2::byte if the included headers don't define it.
// This is safe because it's only a type alias and does not re-implement any logic.
// If Exiv2::byte is already defined, this will be unused.
using FallbackByte = unsigned char;

class ValueTest_787 : public ::testing::Test {
 protected:
  Exiv2::Value value_;
};

}  // namespace

// Normal operation: basic call returns observable result.
TEST_F(ValueTest_787, SetDataAreaReturnsMinusOneWithValidBuffer_787) {
  // Arrange
  const FallbackByte buf[4] = {0x00, 0x11, 0x22, 0x33};

  // Act
  const int rc = value_.setDataArea(reinterpret_cast<const Exiv2::byte*>(buf), sizeof(buf));

  // Assert (black-box: only verify observable return value)
  EXPECT_EQ(-1, rc);
}

// Boundary: nullptr buffer with zero length.
TEST_F(ValueTest_787, SetDataAreaReturnsMinusOneWithNullptrAndZeroLen_787) {
  const int rc = value_.setDataArea(nullptr, 0);
  EXPECT_EQ(-1, rc);
}

// Boundary: nullptr buffer with non-zero length (should still be safely handled by interface).
TEST_F(ValueTest_787, SetDataAreaReturnsMinusOneWithNullptrAndNonZeroLen_787) {
  const int rc = value_.setDataArea(nullptr, 1);
  EXPECT_EQ(-1, rc);
}

// Boundary: non-null buffer with zero length.
TEST_F(ValueTest_787, SetDataAreaReturnsMinusOneWithNonNullBufferAndZeroLen_787) {
  const FallbackByte buf[1] = {0x7F};
  const int rc = value_.setDataArea(reinterpret_cast<const Exiv2::byte*>(buf), 0);
  EXPECT_EQ(-1, rc);
}

// Boundary: small buffer sizes (1 byte).
TEST_F(ValueTest_787, SetDataAreaReturnsMinusOneWithOneByteBuffer_787) {
  const FallbackByte buf[1] = {0xAB};
  const int rc = value_.setDataArea(reinterpret_cast<const Exiv2::byte*>(buf), sizeof(buf));
  EXPECT_EQ(-1, rc);
}

// Boundary: larger size parameter (use a reasonably sized stack buffer).
TEST_F(ValueTest_787, SetDataAreaReturnsMinusOneWithLargerBuffer_787) {
  FallbackByte buf[256] = {};
  buf[0] = 0xDE;
  buf[255] = 0xAD;

  const int rc = value_.setDataArea(reinterpret_cast<const Exiv2::byte*>(buf), sizeof(buf));
  EXPECT_EQ(-1, rc);
}

// Exceptional/error case (observable): verify it does not throw for any pointer/length combo.
// (Even if exceptions are not expected, this documents interface robustness.)
TEST_F(ValueTest_787, SetDataAreaDoesNotThrow_787) {
  const FallbackByte buf[8] = {0, 1, 2, 3, 4, 5, 6, 7};

  EXPECT_NO_THROW({
    (void)value_.setDataArea(reinterpret_cast<const Exiv2::byte*>(buf), sizeof(buf));
    (void)value_.setDataArea(nullptr, 0);
    (void)value_.setDataArea(nullptr, 8);
    (void)value_.setDataArea(reinterpret_cast<const Exiv2::byte*>(buf), 0);
  });
}