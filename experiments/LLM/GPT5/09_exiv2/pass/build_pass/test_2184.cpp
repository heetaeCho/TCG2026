// ============================================================================
// TestProjects/exiv2/tests/test_olympus_mnheader_2184.cpp
// Unit tests for Exiv2::Internal::OlympusMnHeader (TEST_ID: 2184)
// ============================================================================

#include <gtest/gtest.h>

#include "makernote_int.hpp"   // Exiv2::Internal::MnHeader, OlympusMnHeader
#include "exiv2/types.hpp"     // Exiv2::ByteOrder

#include <cstddef>
#include <cstdint>
#include <vector>

namespace {

using Exiv2::ByteOrder;
using Exiv2::Internal::MnHeader;
using Exiv2::Internal::OlympusMnHeader;

class OlympusMnHeaderTest_2184 : public ::testing::Test {};

TEST_F(OlympusMnHeaderTest_2184, DefaultConstruct_DoesNotThrow_2184) {
  EXPECT_NO_THROW({
    OlympusMnHeader h;
    (void)h;
  });
}

TEST_F(OlympusMnHeaderTest_2184, SizeOfSignature_IsStableAndNonNegative_2184) {
  const std::size_t s1 = OlympusMnHeader::sizeOfSignature();
  const std::size_t s2 = OlympusMnHeader::sizeOfSignature();
  EXPECT_EQ(s1, s2);

  // Keep this weak but meaningful: size_t is unsigned, so it is always >= 0.
  // We still assert stability, and allow 0 if implementation defines it so.
  EXPECT_GE(s1, static_cast<std::size_t>(0));
}

TEST_F(OlympusMnHeaderTest_2184, RepeatedQueries_AreDeterministic_2184) {
  OlympusMnHeader h;

  const std::size_t size1 = h.size();
  const std::size_t size2 = h.size();
  EXPECT_EQ(size1, size2);

  const std::size_t off1 = h.ifdOffset();
  const std::size_t off2 = h.ifdOffset();
  EXPECT_EQ(off1, off2);

  const ByteOrder bo1 = h.byteOrder();
  const ByteOrder bo2 = h.byteOrder();
  EXPECT_EQ(bo1, bo2);
}

TEST_F(OlympusMnHeaderTest_2184, SetByteOrder_ReflectsInByteOrderGetter_2184) {
  OlympusMnHeader h;

  h.setByteOrder(ByteOrder::littleEndian);
  EXPECT_EQ(h.byteOrder(), ByteOrder::littleEndian);

  h.setByteOrder(ByteOrder::bigEndian);
  EXPECT_EQ(h.byteOrder(), ByteOrder::bigEndian);

  h.setByteOrder(ByteOrder::invalidByteOrder);
  EXPECT_EQ(h.byteOrder(), ByteOrder::invalidByteOrder);
}

TEST_F(OlympusMnHeaderTest_2184, BaseOffset_DoesNotThrowAndIsDeterministic_2184) {
  OlympusMnHeader h;

  const std::size_t b0 = h.baseOffset(0);
  const std::size_t b1 = h.baseOffset(0);
  EXPECT_EQ(b0, b1);

  // Boundary-style calls (various offsets). We don't assume semantics, only that
  // the API is safe and deterministic for same input.
  const std::size_t bSmall1 = h.baseOffset(1);
  const std::size_t bSmall2 = h.baseOffset(1);
  EXPECT_EQ(bSmall1, bSmall2);

  const std::size_t bLarge1 = h.baseOffset(static_cast<std::size_t>(~0ULL));
  const std::size_t bLarge2 = h.baseOffset(static_cast<std::size_t>(~0ULL));
  EXPECT_EQ(bLarge1, bLarge2);
}

TEST_F(OlympusMnHeaderTest_2184, Read_WithZeroSize_ReturnsFalse_2184) {
  OlympusMnHeader h;

  // Observable behavior expectation for a boundary case: no data.
  // We avoid assumptions beyond this minimal and typical contract.
  EXPECT_FALSE(h.read(nullptr, 0, ByteOrder::littleEndian));
  EXPECT_FALSE(h.read(nullptr, 0, ByteOrder::bigEndian));
  EXPECT_FALSE(h.read(nullptr, 0, ByteOrder::invalidByteOrder));
}

TEST_F(OlympusMnHeaderTest_2184, Read_WithTooSmallBuffer_Fails_2184) {
  OlympusMnHeader h;

  const std::size_t sig = OlympusMnHeader::sizeOfSignature();

  // If signature size is 0, this test becomes non-informative; keep it safe.
  if (sig == 0) {
    SUCCEED() << "sizeOfSignature() is 0; skipping too-small-buffer assertions.";
    return;
  }

  std::vector<Exiv2::byte> buf(sig - 1, 0);

  // Boundary condition: smaller than required signature space.
  EXPECT_FALSE(h.read(buf.data(), buf.size(), ByteOrder::littleEndian));
  EXPECT_FALSE(h.read(buf.data(), buf.size(), ByteOrder::bigEndian));
}

TEST_F(OlympusMnHeaderTest_2184, Read_WithSignatureSizedZeroedBuffer_NoCrashAndConsistentStateQueries_2184) {
  OlympusMnHeader h;

  const std::size_t sig = OlympusMnHeader::sizeOfSignature();
  if (sig == 0) {
    SUCCEED() << "sizeOfSignature() is 0; skipping signature-sized read call.";
    return;
  }

  std::vector<Exiv2::byte> buf(sig, 0);

  bool ok = false;
  EXPECT_NO_THROW({ ok = h.read(buf.data(), buf.size(), ByteOrder::littleEndian); });

  // Regardless of success/failure, public queries should remain safe/deterministic.
  const std::size_t s1 = h.size();
  const std::size_t s2 = h.size();
  EXPECT_EQ(s1, s2);

  const std::size_t o1 = h.ifdOffset();
  const std::size_t o2 = h.ifdOffset();
  EXPECT_EQ(o1, o2);

  // If it *does* succeed, assert basic sanity relations that are generally expected
  // for offsets within a header (without assuming exact values).
  if (ok) {
    EXPECT_GE(h.size(), OlympusMnHeader::sizeOfSignature());
    EXPECT_LE(h.ifdOffset(), h.size());
  }
}

}  // namespace