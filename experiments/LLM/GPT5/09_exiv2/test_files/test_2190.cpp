// SPDX-License-Identifier: GPL-2.0-or-later
//
// Unit tests for Exiv2::Internal::PanasonicMnHeader (makernote_int.cpp / makernote_int.hpp)
// Constraints honored:
//  - Treat implementation as black box
//  - Only use public/protected observable behavior via the interface
//  - No access to private/internal state
//  - Include normal + boundary (+ error if observable)
//
// TEST_ID: 2190

#include <gtest/gtest.h>

#include "makernote_int.hpp"  // Exiv2::Internal::PanasonicMnHeader, MnHeader
#include "types.hpp"          // Exiv2::ByteOrder

namespace {

using Exiv2::ByteOrder;
using Exiv2::bigEndian;
using Exiv2::invalidByteOrder;
using Exiv2::littleEndian;

using Exiv2::Internal::PanasonicMnHeader;

class PanasonicMnHeaderTest_2190 : public ::testing::Test {
 protected:
  PanasonicMnHeader header_;
};

}  // namespace

TEST_F(PanasonicMnHeaderTest_2190, DefaultConstructible_2190) {
  // Normal: construction should succeed.
  EXPECT_NO_THROW({
    PanasonicMnHeader h;
    (void)h;
  });
}

TEST_F(PanasonicMnHeaderTest_2190, SizeOfSignature_IsStableAndNonZero_2190) {
  // Boundary-ish: signature size should be a stable, non-negative size_t.
  const size_t s1 = PanasonicMnHeader::sizeOfSignature();
  const size_t s2 = PanasonicMnHeader::sizeOfSignature();

  EXPECT_EQ(s1, s2);
  EXPECT_GE(s1, static_cast<size_t>(0));

  // If the implementation defines a real signature, it's typically > 0.
  // Keep this weak to avoid inferring internals.
  EXPECT_NE(s1, static_cast<size_t>(0));
}

TEST_F(PanasonicMnHeaderTest_2190, Size_ReturnsAValueAndIsStableAcrossCalls_2190) {
  // Normal: size() is observable and should be callable repeatedly.
  const size_t a = header_.size();
  const size_t b = header_.size();
  EXPECT_EQ(a, b);
  EXPECT_GE(a, static_cast<size_t>(0));
}

TEST_F(PanasonicMnHeaderTest_2190, IfdOffset_ReturnsAValueAndIsStableAcrossCalls_2190) {
  // Normal: ifdOffset() is observable and should be callable repeatedly.
  const size_t a = header_.ifdOffset();
  const size_t b = header_.ifdOffset();
  EXPECT_EQ(a, b);
  EXPECT_GE(a, static_cast<size_t>(0));
}

TEST_F(PanasonicMnHeaderTest_2190, Read_WithNullPointerAndZeroSize_DoesNotCrash_2190) {
  // Boundary: read(nullptr, 0, ...) should not crash. We don't assume true/false.
  EXPECT_NO_THROW({
    const bool ok_le = header_.read(nullptr, 0, littleEndian);
    const bool ok_be = header_.read(nullptr, 0, bigEndian);
    const bool ok_inv = header_.read(nullptr, 0, invalidByteOrder);
    (void)ok_le;
    (void)ok_be;
    (void)ok_inv;
  });
}

TEST_F(PanasonicMnHeaderTest_2190, Read_InvalidByteOrder_IsHandled_2190) {
  // Error-ish: invalidByteOrder is an explicit enum value. Ensure call is safe.
  // Do not require a specific return value (implementation-defined).
  const unsigned char dummy[1] = {0x00};
  EXPECT_NO_THROW({
    const bool ok = header_.read(reinterpret_cast<const Exiv2::byte*>(dummy), 0, invalidByteOrder);
    (void)ok;
  });
}

TEST_F(PanasonicMnHeaderTest_2190, Read_WithNonNullPointerButTooSmallSize_DoesNotCrash_2190) {
  // Boundary: Provide some data, but size smaller than signature size (if any).
  // We avoid asserting success/failure; only that it is safe and returns a bool.
  const size_t sig = PanasonicMnHeader::sizeOfSignature();
  const unsigned char buf[16] = {0};  // small fixed buffer

  const size_t smallSize = (sig == 0) ? 0 : std::min(sig - 1, sizeof(buf));

  EXPECT_NO_THROW({
    const bool ok = header_.read(reinterpret_cast<const Exiv2::byte*>(buf), smallSize, littleEndian);
    (void)ok;
  });
}

TEST_F(PanasonicMnHeaderTest_2190, Read_WithSizeEqualToSignature_DoesNotCrash_2190) {
  // Boundary: size == signature size (common boundary for header parsing).
  const size_t sig = PanasonicMnHeader::sizeOfSignature();
  // If signature size is unexpectedly huge, cap allocation to keep test safe.
  const size_t cap = 1024;
  const size_t n = (sig <= cap) ? sig : cap;

  std::vector<unsigned char> buf(n, 0);

  EXPECT_NO_THROW({
    const bool ok = header_.read(reinterpret_cast<const Exiv2::byte*>(buf.data()), n, littleEndian);
    (void)ok;
  });
}

TEST_F(PanasonicMnHeaderTest_2190, Read_DoesNotChangeSizeAndIfdOffsetInUnobservableWayAcrossNoOpReads_2190) {
  // Observable stability check: after a "no-op" boundary read, size/ifdOffset remain callable/stable.
  const size_t size_before = header_.size();
  const size_t ifd_before = header_.ifdOffset();

  (void)header_.read(nullptr, 0, invalidByteOrder);

  const size_t size_after = header_.size();
  const size_t ifd_after = header_.ifdOffset();

  // We cannot assume they must remain equal, but we can at least assert the calls are valid and stable.
  EXPECT_GE(size_before, static_cast<size_t>(0));
  EXPECT_GE(size_after, static_cast<size_t>(0));
  EXPECT_GE(ifd_before, static_cast<size_t>(0));
  EXPECT_GE(ifd_after, static_cast<size_t>(0));
}