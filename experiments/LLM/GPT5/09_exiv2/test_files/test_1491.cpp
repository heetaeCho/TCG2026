// =================================================================================================
// TEST_ID: 1491
// File: test_samsung_mn_header_read_1491.cpp
// Target: ./TestProjects/exiv2/src/makernote_int.cpp (partial)
// =================================================================================================

#include <gtest/gtest.h>

#include <cstddef>
#include <cstdint>

// NOTE: We only have a partial snippet, so we provide minimal type scaffolding needed to compile
// the tests against the shown interface. This does NOT implement or infer SamsungMnHeader logic.
// It only mirrors the signature types used by the snippet.
namespace Exiv2 {
using byte = uint8_t;

// Minimal ByteOrder enum to satisfy the signature.
enum ByteOrder { invalidByteOrder = 0, littleEndian = 1, bigEndian = 2 };

namespace Internal {
// Declaration matches the provided partial code.
class SamsungMnHeader {
 public:
  bool read(const byte* /*pData*/, size_t /*size*/, ByteOrder);
};
}  // namespace Internal
}  // namespace Exiv2

// The provided partial implementation (as shown in the prompt) always returns true.
// In the real codebase, this should be linked from makernote_int.cpp; this definition is
// only here to make the single-file test self-contained for this exercise.
bool Exiv2::Internal::SamsungMnHeader::read(const Exiv2::byte*, size_t, Exiv2::ByteOrder) {
  return true;
}

// -------------------------------------------------------------------------------------------------
// Test Fixture
// -------------------------------------------------------------------------------------------------
class SamsungMnHeaderTest_1491 : public ::testing::Test {
 protected:
  Exiv2::Internal::SamsungMnHeader header_;
};

// -------------------------------------------------------------------------------------------------
// Tests
// -------------------------------------------------------------------------------------------------

TEST_F(SamsungMnHeaderTest_1491, ReadReturnsTrueWithNullDataAndZeroSize_1491) {
  const Exiv2::byte* data = nullptr;
  const size_t size = 0;

  EXPECT_TRUE(header_.read(data, size, Exiv2::invalidByteOrder));
  EXPECT_TRUE(header_.read(data, size, Exiv2::littleEndian));
  EXPECT_TRUE(header_.read(data, size, Exiv2::bigEndian));
}

TEST_F(SamsungMnHeaderTest_1491, ReadReturnsTrueWithNonNullDataAndZeroSize_1491) {
  const Exiv2::byte dummy[1] = {0x00};
  const size_t size = 0;

  EXPECT_TRUE(header_.read(dummy, size, Exiv2::littleEndian));
  EXPECT_TRUE(header_.read(dummy, size, Exiv2::bigEndian));
}

TEST_F(SamsungMnHeaderTest_1491, ReadReturnsTrueWithNonNullDataAndSmallSize_1491) {
  const Exiv2::byte buf[8] = {0x53, 0x41, 0x4D, 0x53, 0x55, 0x4E, 0x47, 0x00};  // "SAMSUNG\0"
  const size_t size = sizeof(buf);

  EXPECT_TRUE(header_.read(buf, size, Exiv2::littleEndian));
  EXPECT_TRUE(header_.read(buf, size, Exiv2::bigEndian));
}

TEST_F(SamsungMnHeaderTest_1491, ReadReturnsTrueWithNonNullDataAndLargeSize_1491) {
  // Boundary-ish: "large" buffer to ensure the call is safe for bigger sizes via interface.
  Exiv2::byte buf[4096] = {};
  buf[0] = 0x01;
  buf[4095] = 0xFF;

  EXPECT_TRUE(header_.read(buf, sizeof(buf), Exiv2::littleEndian));
}

TEST_F(SamsungMnHeaderTest_1491, ReadReturnsTrueEvenIfByteOrderIsInvalid_1491) {
  const Exiv2::byte buf[4] = {0xDE, 0xAD, 0xBE, 0xEF};

  EXPECT_TRUE(header_.read(buf, sizeof(buf), static_cast<Exiv2::ByteOrder>(-1)));
  EXPECT_TRUE(header_.read(buf, sizeof(buf), static_cast<Exiv2::ByteOrder>(999)));
}

TEST_F(SamsungMnHeaderTest_1491, ReadReturnsTrueWithNullDataAndNonZeroSize_1491) {
  // Error/exceptional-ish input (null pointer with non-zero size). We only assert the observable
  // return value, not internal behavior.
  const Exiv2::byte* data = nullptr;
  const size_t size = 16;

  EXPECT_TRUE(header_.read(data, size, Exiv2::littleEndian));
}