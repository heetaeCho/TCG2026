// SPDX-License-Identifier: GPL-2.0-or-later

#include <gtest/gtest.h>

#include "makernote_int.hpp"
#include "types.hpp"

namespace Exiv2::Internal {

class PentaxMnHeaderTest_2192 : public ::testing::Test {};

TEST_F(PentaxMnHeaderTest_2192, DefaultConstruction_DoesNotThrow_2192) {
  EXPECT_NO_THROW({
    PentaxMnHeader h;
    (void)h;
  });
}

TEST_F(PentaxMnHeaderTest_2192, SizeOfSignature_IsNonZeroAndStable_2192) {
  const size_t s1 = PentaxMnHeader::sizeOfSignature();
  const size_t s2 = PentaxMnHeader::sizeOfSignature();
  EXPECT_GT(s1, 0u);
  EXPECT_EQ(s1, s2);
}

TEST_F(PentaxMnHeaderTest_2192, DefaultObject_AccessorsAreStableAcrossCalls_2192) {
  PentaxMnHeader h;

  const size_t size1 = h.size();
  const size_t size2 = h.size();
  EXPECT_EQ(size1, size2);

  const size_t ifd1 = h.ifdOffset();
  const size_t ifd2 = h.ifdOffset();
  EXPECT_EQ(ifd1, ifd2);

  const ByteOrder bo1 = h.byteOrder();
  const ByteOrder bo2 = h.byteOrder();
  EXPECT_EQ(bo1, bo2);
}

TEST_F(PentaxMnHeaderTest_2192, DefaultConstruction_ByteOrderIsInvalid_2192) {
  PentaxMnHeader h;
  EXPECT_EQ(h.byteOrder(), invalidByteOrder);
}

TEST_F(PentaxMnHeaderTest_2192, Read_WithNullptrAndNonZeroSize_ReturnsFalse_2192) {
  PentaxMnHeader h;

  // Boundary/error case: null data with non-zero size should be rejected (observable via return value).
  EXPECT_FALSE(h.read(nullptr, 1u, invalidByteOrder));
}

TEST_F(PentaxMnHeaderTest_2192, Read_WithTooSmallBuffer_ReturnsFalse_2192) {
  PentaxMnHeader h;

  const size_t sig = PentaxMnHeader::sizeOfSignature();
  if (sig == 0u) {
    GTEST_SKIP() << "Signature size reported as 0; cannot exercise boundary condition.";
  }
  if (sig == 1u) {
    GTEST_SKIP() << "Signature size is 1; no smaller non-zero buffer size exists to test.";
  }

  // Boundary: provide a buffer smaller than the signature.
  std::vector<byte> buf(sig - 1u, static_cast<byte>(0));
  EXPECT_FALSE(h.read(buf.data(), buf.size(), invalidByteOrder));
}

TEST_F(PentaxMnHeaderTest_2192, Read_DoesNotThrow_ForZeroSizeInput_2192) {
  PentaxMnHeader h;

  // Boundary: size==0 (with any pointer value) should not throw; return value is observable but
  // may vary across implementations, so we only assert safety here.
  EXPECT_NO_THROW({
    const bool ok = h.read(nullptr, 0u, invalidByteOrder);
    (void)ok;
  });
}

}  // namespace Exiv2::Internal