// =================================================================================================
// Unit tests for Exiv2::Internal::Casio2MnHeader
// File: ./TestProjects/exiv2/src/makernote_int.cpp (interface)
// =================================================================================================

#include <gtest/gtest.h>

#include <cstddef>
#include <cstdint>
#include <vector>

#include "makernote_int.hpp"  // Exiv2::Internal::Casio2MnHeader (+ MnHeader, ByteOrder, byte)

namespace {

using Exiv2::ByteOrder;
using Exiv2::byte;
using Exiv2::Internal::Casio2MnHeader;

class Casio2MnHeaderTest_1506 : public ::testing::Test {
 protected:
  static std::vector<byte> MakeBuffer(size_t n, byte fill = 0x00) {
    return std::vector<byte>(n, fill);
  }
};

TEST_F(Casio2MnHeaderTest_1506, DefaultConstruction_MethodsAreCallableAndStable_1506) {
  Casio2MnHeader h;

  // All of these are part of the public interface; verify they are callable and stable.
  EXPECT_NO_THROW({
    const size_t s1 = h.size();
    const size_t s2 = h.size();
    EXPECT_EQ(s1, s2);

    const size_t o1 = h.ifdOffset();
    const size_t o2 = h.ifdOffset();
    EXPECT_EQ(o1, o2);

    const ByteOrder b1 = h.byteOrder();
    const ByteOrder b2 = h.byteOrder();
    EXPECT_EQ(b1, b2);
  });
}

TEST_F(Casio2MnHeaderTest_1506, SizeOfSignature_IsNonZero_1506) {
  const size_t sig = Casio2MnHeader::sizeOfSignature();
  EXPECT_GT(sig, 0u);
}

TEST_F(Casio2MnHeaderTest_1506, Read_WithNullptrAndZeroSize_ReturnsFalse_1506) {
  Casio2MnHeader h;

  // Error/boundary: null buffer and 0 size.
  // The interface returns bool; we expect a failure rather than success.
  EXPECT_FALSE(h.read(nullptr, 0, h.byteOrder()));
}

TEST_F(Casio2MnHeaderTest_1506, Read_WithTooSmallBuffer_ReturnsFalse_1506) {
  Casio2MnHeader h;

  const size_t sig = Casio2MnHeader::sizeOfSignature();
  if (sig == 0) {
    GTEST_SKIP() << "sizeOfSignature() returned 0; cannot form a 'too small' buffer.";
  }

  // Boundary: smaller than required signature size.
  auto buf = MakeBuffer(sig - 1, 0x00);
  EXPECT_FALSE(h.read(buf.data(), buf.size(), h.byteOrder()));
}

TEST_F(Casio2MnHeaderTest_1506, Read_WithAllZeroBuffer_FailsOrReturnsFalse_1506) {
  Casio2MnHeader h;

  // Typical invalid-data case: large enough buffer but unlikely to be a valid header.
  const size_t sig = Casio2MnHeader::sizeOfSignature();
  const size_t n = (sig == 0) ? 16u : (sig + 16u);
  auto buf = MakeBuffer(n, 0x00);

  // Observable behavior: read() indicates success/failure via bool.
  EXPECT_FALSE(h.read(buf.data(), buf.size(), h.byteOrder()));
}

TEST_F(Casio2MnHeaderTest_1506, AfterFailedRead_StateRemainsCallableAndStable_1506) {
  Casio2MnHeader h;

  const ByteOrder beforeBo = h.byteOrder();
  const size_t beforeSize = h.size();
  const size_t beforeOff = h.ifdOffset();

  // Force a failed read.
  EXPECT_FALSE(h.read(nullptr, 0, beforeBo));

  // Still callable and stable afterwards.
  EXPECT_NO_THROW({
    EXPECT_EQ(h.byteOrder(), h.byteOrder());
    EXPECT_EQ(h.size(), h.size());
    EXPECT_EQ(h.ifdOffset(), h.ifdOffset());
  });

  // And at minimum, the object should remain in a self-consistent state.
  // (We avoid asserting specific internal changes.)
  EXPECT_EQ(h.size(), beforeSize);
  EXPECT_EQ(h.ifdOffset(), beforeOff);
  EXPECT_EQ(h.byteOrder(), beforeBo);
}

TEST_F(Casio2MnHeaderTest_1506, BasicInvariants_SizeAndOffsets_AreNonNegativeAndConsistent_1506) {
  Casio2MnHeader h;

  const size_t s = h.size();
  const size_t o = h.ifdOffset();
  const size_t sig = Casio2MnHeader::sizeOfSignature();

  // These are lightweight interface-level consistency checks (no internal logic assumptions).
  EXPECT_GE(s, 0u);
  EXPECT_GE(o, 0u);
  EXPECT_GE(s, sig);
}

}  // namespace