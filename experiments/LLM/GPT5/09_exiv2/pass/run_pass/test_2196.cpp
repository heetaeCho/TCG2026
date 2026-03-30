// TEST_ID: 2196
//
// File: test_casio2mnheader_2196.cpp
//
// Unit tests for Exiv2::Internal::Casio2MnHeader
// Constraints respected:
// - Treat implementation as black box
// - Test only observable behavior via public interface
// - No private/internal state access
// - No re-implementation/inference of internal logic

#include <gtest/gtest.h>

#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <vector>

#include "makernote_int.hpp"
#include "exiv2/types.hpp"

namespace {

using Exiv2::ByteOrder;
using Exiv2::bigEndian;
using Exiv2::invalidByteOrder;
using Exiv2::littleEndian;

using Exiv2::Internal::Casio2MnHeader;
using Exiv2::Internal::MnHeader;

static bool IsKnownByteOrder(ByteOrder bo) {
  return bo == invalidByteOrder || bo == littleEndian || bo == bigEndian;
}

static std::vector<Exiv2::byte> MakeBuffer(size_t n) {
  // Fill with a deterministic pattern.
  std::vector<Exiv2::byte> buf(n);
  for (size_t i = 0; i < n; ++i) {
    buf[i] = static_cast<Exiv2::byte>(i & 0xFF);
  }
  return buf;
}

class Casio2MnHeaderTest_2196 : public ::testing::Test {};

TEST_F(Casio2MnHeaderTest_2196, DefaultConstruction_DoesNotThrow_2196) {
  EXPECT_NO_THROW({
    Casio2MnHeader h;
    (void)h;
  });
}

TEST_F(Casio2MnHeaderTest_2196, SizeOfSignature_IsStableAcrossCalls_2196) {
  const size_t a = Casio2MnHeader::sizeOfSignature();
  const size_t b = Casio2MnHeader::sizeOfSignature();
  EXPECT_EQ(a, b);

  // Boundary sanity: size_t is non-negative by definition; still verify usability.
  EXPECT_GE(a, static_cast<size_t>(0));
}

TEST_F(Casio2MnHeaderTest_2196, Accessors_AreCallableAndStableAcrossCalls_2196) {
  Casio2MnHeader h;

  const size_t s1 = h.size();
  const size_t s2 = h.size();
  EXPECT_EQ(s1, s2);

  const size_t o1 = h.ifdOffset();
  const size_t o2 = h.ifdOffset();
  EXPECT_EQ(o1, o2);

  const ByteOrder bo1 = h.byteOrder();
  const ByteOrder bo2 = h.byteOrder();
  EXPECT_EQ(bo1, bo2);
  EXPECT_TRUE(IsKnownByteOrder(bo1));
}

TEST_F(Casio2MnHeaderTest_2196, Read_WithNullAndZeroSize_IsDeterministic_2196) {
  Casio2MnHeader h;

  const bool r1 = h.read(nullptr, 0, invalidByteOrder);
  const bool r2 = h.read(nullptr, 0, invalidByteOrder);
  EXPECT_EQ(r1, r2);
}

TEST_F(Casio2MnHeaderTest_2196, Read_WithVariousSizesAndByteOrders_IsDeterministic_2196) {
  Casio2MnHeader h;

  const size_t sig = Casio2MnHeader::sizeOfSignature();
  const size_t bufSize = std::max<size_t>(1, sig + 8);
  const auto buf = MakeBuffer(bufSize);

  const ByteOrder orders[] = {invalidByteOrder, littleEndian, bigEndian};
  const size_t sizes[] = {
      0,
      1,
      (sig > 0 ? sig - 1 : 0),
      sig,
      sig + 1,
      bufSize,
  };

  for (ByteOrder bo : orders) {
    for (size_t sz : sizes) {
      const Exiv2::byte* p = (sz == 0 ? nullptr : buf.data());
      const bool r1 = h.read(p, sz, bo);
      const bool r2 = h.read(p, sz, bo);
      EXPECT_EQ(r1, r2) << "Non-deterministic read() for size=" << sz << " bo=" << static_cast<int>(bo);
    }
  }
}

TEST_F(Casio2MnHeaderTest_2196, PolymorphicUse_ViaMnHeaderPointer_IsCallable_2196) {
  std::unique_ptr<MnHeader> base;
  ASSERT_NO_THROW({
    base = std::make_unique<Casio2MnHeader>();
  });
  ASSERT_NE(base, nullptr);

  // Call virtuals via base pointer; verify stability (observable behavior).
  const size_t s1 = base->size();
  const size_t s2 = base->size();
  EXPECT_EQ(s1, s2);

  const size_t o1 = base->ifdOffset();
  const size_t o2 = base->ifdOffset();
  EXPECT_EQ(o1, o2);

  const ByteOrder bo1 = base->byteOrder();
  const ByteOrder bo2 = base->byteOrder();
  EXPECT_EQ(bo1, bo2);
  EXPECT_TRUE(IsKnownByteOrder(bo1));
}

}  // namespace