// File: fuji_mnheader_test_1454.cpp
// Unit tests for Exiv2::Internal::FujiMnHeader
//
// Constraints honored:
// - Treat implementation as black box (no internal state access, no logic re-implementation)
// - Test only observable behavior via public interface
// - Include normal / boundary / error-ish (observable) cases

#include <gtest/gtest.h>

#include <array>
#include <cstddef>
#include <cstdint>

#include "makernote_int.hpp"  // Exiv2::Internal::FujiMnHeader, MnHeader, IoWrapper, ByteOrder, byte

namespace {

class FujiMnHeaderTest_1454 : public ::testing::Test {
 protected:
  Exiv2::Internal::FujiMnHeader header_;
};

TEST_F(FujiMnHeaderTest_1454, SizeOfSignature_IsNonZero_1454) {
  const size_t sig = Exiv2::Internal::FujiMnHeader::sizeOfSignature();
  EXPECT_GT(sig, 0u);

  // Also verify the instance method exists and is consistent with the static.
  EXPECT_EQ(header_.sizeOfSignature(), sig);
}

TEST_F(FujiMnHeaderTest_1454, ConstSize_MatchesNonConstSize_1454) {
  // Verify both overloads are callable and agree.
  const auto& const_ref = header_;
  const size_t a = header_.size();
  const size_t b = const_ref.size();
  EXPECT_EQ(a, b);
}

TEST_F(FujiMnHeaderTest_1454, Read_WithTooSmallBuffer_ReturnsFalse_1454) {
  const size_t sig = Exiv2::Internal::FujiMnHeader::sizeOfSignature();

  // Boundary: 0 bytes and (sig-1) bytes are too small to contain a signature.
  // Use a non-null pointer when size > 0.
  std::array<Exiv2::byte, 8> small{};
  EXPECT_FALSE(header_.read(small.data(), 0u, Exiv2::littleEndian));

  if (sig > 0) {
    const size_t n = (sig > small.size()) ? small.size() : (sig - 1);
    EXPECT_FALSE(header_.read(small.data(), n, Exiv2::littleEndian));
  }
}

TEST_F(FujiMnHeaderTest_1454, Read_WithZeroedSignatureSizedBuffer_ReturnsFalse_1454) {
  const size_t sig = Exiv2::Internal::FujiMnHeader::sizeOfSignature();

  // If signature size is unexpectedly huge, cap the allocation to keep the test reasonable.
  const size_t cap = 256u;
  const size_t n = (sig <= cap) ? sig : cap;

  std::vector<Exiv2::byte> buf(n, static_cast<Exiv2::byte>(0));

  // A buffer filled with zeros should not match a real Fuji signature/header.
  // This is an observable, error-ish case: read should reject invalid data.
  EXPECT_FALSE(header_.read(buf.data(), buf.size(), Exiv2::littleEndian));
}

TEST_F(FujiMnHeaderTest_1454, Accessors_AreCallableAndDeterministicForSameInput_1454) {
  // These are pure interface-level checks: methods are callable and stable for the same input.
  const auto& const_ref = header_;

  const size_t ifd1 = const_ref.ifdOffset();
  const size_t ifd2 = const_ref.ifdOffset();
  EXPECT_EQ(ifd1, ifd2);

  const Exiv2::ByteOrder bo1 = const_ref.byteOrder();
  const Exiv2::ByteOrder bo2 = const_ref.byteOrder();
  EXPECT_EQ(bo1, bo2);

  const size_t base1 = const_ref.baseOffset(0u);
  const size_t base2 = const_ref.baseOffset(0u);
  EXPECT_EQ(base1, base2);

  const size_t base3 = const_ref.baseOffset(123u);
  const size_t base4 = const_ref.baseOffset(123u);
  EXPECT_EQ(base3, base4);
}

}  // namespace