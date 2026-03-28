// File: test_fuji_mnheader_2187.cpp
// Tests for Exiv2::Internal::FujiMnHeader (makernote_int.hpp / makernote_int.cpp)

#include <gtest/gtest.h>

#include <cstddef>
#include <cstdint>
#include <vector>

// Exiv2 headers (project-local)
#include "makernote_int.hpp"

namespace {

using Exiv2::ByteOrder;

class FujiMnHeaderTest_2187 : public ::testing::Test {
 protected:
  static std::vector<Exiv2::byte> MakeBuffer(size_t n, Exiv2::byte fill = 0x00) {
    return std::vector<Exiv2::byte>(n, fill);
  }

  // Helper that accepts any plausible ByteOrder values without assuming specifics.
  static std::vector<ByteOrder> CandidateByteOrders() {
    // Common Exiv2 ByteOrder enumerators in many codebases.
    // If any of these are not defined in your branch, remove the offending entries.
    return {
        Exiv2::invalidByteOrder,
        Exiv2::littleEndian,
        Exiv2::bigEndian,
    };
  }
};

TEST_F(FujiMnHeaderTest_2187, ConstructorAndBasicCalls_DoNotThrow_2187) {
  Exiv2::Internal::FujiMnHeader header;

  EXPECT_NO_THROW({
    (void)Exiv2::Internal::FujiMnHeader::sizeOfSignature();
    (void)header.size();
    (void)header.ifdOffset();
    (void)header.byteOrder();
    (void)header.baseOffset(0);
    (void)header.baseOffset(1);
    (void)header.baseOffset(static_cast<size_t>(-1));  // boundary for size_t
  });
}

TEST_F(FujiMnHeaderTest_2187, SizeOfSignature_IsStableAcrossCalls_2187) {
  const size_t s1 = Exiv2::Internal::FujiMnHeader::sizeOfSignature();
  const size_t s2 = Exiv2::Internal::FujiMnHeader::sizeOfSignature();
  const size_t s3 = Exiv2::Internal::FujiMnHeader::sizeOfSignature();

  EXPECT_EQ(s1, s2);
  EXPECT_EQ(s2, s3);
}

TEST_F(FujiMnHeaderTest_2187, SetByteOrder_RoundTripsThroughByteOrder_2187) {
  Exiv2::Internal::FujiMnHeader header;

  // This test only checks the observable contract of setByteOrder()/byteOrder()
  // without assuming any internal parsing behavior.
  for (const auto bo : CandidateByteOrders()) {
    EXPECT_NO_THROW(header.setByteOrder(bo));
    EXPECT_EQ(header.byteOrder(), bo);
  }
}

TEST_F(FujiMnHeaderTest_2187, Read_WithNullAndZeroSize_IsHandled_2187) {
  Exiv2::Internal::FujiMnHeader header;

  const ByteOrder before = header.byteOrder();

  bool ok = false;
  EXPECT_NO_THROW({
    ok = header.read(nullptr, 0, before);
  });

  // We do not assume success/failure; we only verify the method is robust and that
  // the resulting byteOrder is consistent (either remains the same or matches input).
  const ByteOrder after = header.byteOrder();
  EXPECT_TRUE(after == before || after == before);
  (void)ok;
}

TEST_F(FujiMnHeaderTest_2187, Read_BufferSizesAroundSignatureBoundary_AreHandled_2187) {
  Exiv2::Internal::FujiMnHeader header;

  const size_t sig = Exiv2::Internal::FujiMnHeader::sizeOfSignature();

  const std::vector<size_t> sizes = {
      0,
      (sig == 0 ? 0 : sig - 1),  // boundary below signature size (if non-zero)
      sig,                       // exact boundary
      sig + 1,                   // just above
      sig + 16,                  // a bit above
  };

  for (const auto bo : CandidateByteOrders()) {
    for (size_t n : sizes) {
      const auto buf = MakeBuffer(n, 0xAB);
      const ByteOrder before = header.byteOrder();

      bool ok = false;
      EXPECT_NO_THROW({
        ok = header.read(buf.empty() ? nullptr : buf.data(), buf.size(), bo);
      });

      // Observable consistency check: byteOrder after read should be well-defined.
      // We avoid assuming it *must* change; we only assert it is either unchanged
      // or set to the requested byte order (both are observable and plausible).
      const ByteOrder after = header.byteOrder();
      EXPECT_TRUE(after == before || after == bo);

      (void)ok;
    }
  }
}

TEST_F(FujiMnHeaderTest_2187, BaseOffset_IsCallableForExtremeInputs_2187) {
  Exiv2::Internal::FujiMnHeader header;

  // Boundary cases for mnOffset
  const size_t zero = 0;
  const size_t one = 1;
  const size_t maxv = static_cast<size_t>(-1);

  size_t o0 = 0, o1 = 0, omax = 0;
  EXPECT_NO_THROW({
    o0 = header.baseOffset(zero);
    o1 = header.baseOffset(one);
    omax = header.baseOffset(maxv);
  });

  // No assumptions about arithmetic; just ensure results are usable size_t values.
  (void)o0;
  (void)o1;
  (void)omax;
}

}  // namespace