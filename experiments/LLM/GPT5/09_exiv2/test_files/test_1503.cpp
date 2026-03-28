// File: test_casio2mnheader_1503.cpp
// TEST_ID: 1503
//
// Unit tests for Exiv2::Internal::Casio2MnHeader (partial interface)
// Constraints respected:
// - Treat implementation as black box
// - Use only observable behavior / provided interface
// - No private state access
// - Include normal + boundary + (observable) error cases
//
// Note: The provided partial implementation shows a non-static sizeOfSignature()
// that returns sizeof(signature_). We therefore only assert general invariants
// that must hold for any reasonable signature size (non-zero, stable), without
// inferring the actual bytes or structure.
//
// These tests are written to be robust even if the signature size changes.

#include <gtest/gtest.h>

#include <cstddef>
#include <type_traits>

// Include the real header from the codebase.
#include "makernote_int.hpp"

namespace {

// Fixture name includes TEST_ID per project convention.
class Casio2MnHeaderTest_1503 : public ::testing::Test {};

}  // namespace

TEST_F(Casio2MnHeaderTest_1503, SizeOfSignature_IsNonZero_1503) {
  // Normal invariant: a signature should have a concrete non-zero size.
  Exiv2::Internal::Casio2MnHeader hdr;
  const size_t sigSize = hdr.sizeOfSignature();
  EXPECT_GT(sigSize, 0u);
}

TEST_F(Casio2MnHeaderTest_1503, SizeOfSignature_IsStableAcrossCalls_1503) {
  // Boundary-ish: repeated calls should be consistent (no hidden mutation assumed).
  Exiv2::Internal::Casio2MnHeader hdr;
  const size_t a = hdr.sizeOfSignature();
  const size_t b = hdr.sizeOfSignature();
  const size_t c = hdr.sizeOfSignature();
  EXPECT_EQ(a, b);
  EXPECT_EQ(b, c);
}

TEST_F(Casio2MnHeaderTest_1503, SizeOfSignature_ConsistentAcrossInstances_1503) {
  // Boundary: different instances should report the same signature size.
  Exiv2::Internal::Casio2MnHeader hdr1;
  Exiv2::Internal::Casio2MnHeader hdr2;
  EXPECT_EQ(hdr1.sizeOfSignature(), hdr2.sizeOfSignature());
}

TEST_F(Casio2MnHeaderTest_1503, SizeOfSignature_ReturnTypeIsSizeT_1503) {
  // Compile-time contract check: return type should match the signature in the interface.
  using RetT = decltype(std::declval<Exiv2::Internal::Casio2MnHeader&>().sizeOfSignature());
  static_assert(std::is_same_v<RetT, size_t>, "Casio2MnHeader::sizeOfSignature() must return size_t");
  SUCCEED();
}

TEST_F(Casio2MnHeaderTest_1503, SizeOfSignature_ReasonableUpperBound_1503) {
  // Boundary: signature sizes are typically small; enforce a very generous bound
  // to catch pathological behavior without assuming internals.
  Exiv2::Internal::Casio2MnHeader hdr;
  const size_t sigSize = hdr.sizeOfSignature();

  // 1 KiB is intentionally lenient; if this fails, something is very off.
  EXPECT_LE(sigSize, 1024u);
}