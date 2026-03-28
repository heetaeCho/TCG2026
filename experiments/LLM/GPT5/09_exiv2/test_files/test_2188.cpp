// SPDX-License-Identifier: GPL-2.0-or-later
// File: test_nikon2_mnheader_2188.cpp

#include <gtest/gtest.h>

#include <cstddef>
#include <cstdint>
#include <limits>
#include <type_traits>

// Exiv2 internal header under test
#include "makernote_int.hpp"
#include "exiv2/types.hpp"

namespace {

using Exiv2::ByteOrder;
using Exiv2::bigEndian;
using Exiv2::invalidByteOrder;
using Exiv2::littleEndian;

using Exiv2::Internal::MnHeader;
using Exiv2::Internal::Nikon2MnHeader;

TEST(Nikon2MnHeaderTest_2188, DefaultConstructorDoesNotThrow_2188) {
  EXPECT_NO_THROW({
    Nikon2MnHeader h;
    (void)h;
  });
}

TEST(Nikon2MnHeaderTest_2188, StaticSizeOfSignatureIsStableAndNonZero_2188) {
  const size_t s1 = Nikon2MnHeader::sizeOfSignature();
  const size_t s2 = Nikon2MnHeader::sizeOfSignature();

  // Black-box, but a "signature" size should be stable and typically non-zero.
  EXPECT_EQ(s1, s2);
  EXPECT_GT(s1, 0u);
}

TEST(MnHeaderTest_2188, DeletedCopyAndAssign_2188) {
  static_assert(!std::is_copy_constructible<MnHeader>::value,
                "MnHeader copy-ctor must be deleted.");
  static_assert(!std::is_copy_assignable<MnHeader>::value,
                "MnHeader copy-assign must be deleted.");

  // Nikon2MnHeader derives from MnHeader, so it should also be non-copyable.
  static_assert(!std::is_copy_constructible<Nikon2MnHeader>::value,
                "Nikon2MnHeader should not be copy-constructible.");
  static_assert(!std::is_copy_assignable<Nikon2MnHeader>::value,
                "Nikon2MnHeader should not be copy-assignable.");
}

TEST(MnHeaderTest_2188, SetByteOrderRoundTrip_2188) {
  MnHeader h;

  h.setByteOrder(littleEndian);
  EXPECT_EQ(h.byteOrder(), littleEndian);

  h.setByteOrder(bigEndian);
  EXPECT_EQ(h.byteOrder(), bigEndian);

  h.setByteOrder(invalidByteOrder);
  EXPECT_EQ(h.byteOrder(), invalidByteOrder);
}

TEST(MnHeaderTest_2188, BaseOffsetAcceptsBoundaryValues_2188) {
  MnHeader h;

  // Boundary inputs: 0 and max size_t.
  EXPECT_NO_THROW({
    const size_t b0 = h.baseOffset(0);
    (void)b0;
  });

  EXPECT_NO_THROW({
    const size_t bmax = h.baseOffset(std::numeric_limits<size_t>::max());
    (void)bmax;
  });
}

TEST(Nikon2MnHeaderTest_2188, ReadHandlesEmptyInputWithoutCrashing_2188) {
  Nikon2MnHeader h;

  // Boundary: empty buffer (nullptr, size 0). We don't assume success/failure,
  // only that the call is safe and returns a bool.
  bool r1 = true;
  EXPECT_NO_THROW({ r1 = h.read(nullptr, 0u, invalidByteOrder); });
  EXPECT_TRUE(r1 == true || r1 == false);

  bool r2 = true;
  EXPECT_NO_THROW({ r2 = h.read(nullptr, 0u, littleEndian); });
  EXPECT_TRUE(r2 == true || r2 == false);

  // After read attempts, these accessors should still be callable.
  EXPECT_NO_THROW({
    const size_t s = h.size();
    const size_t o = h.ifdOffset();
    (void)s;
    (void)o;
  });
}

}  // namespace