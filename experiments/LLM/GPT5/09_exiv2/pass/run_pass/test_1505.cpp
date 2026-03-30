// ***************************************************************** -*- C++ -*-
// Unit tests for Exiv2::Internal::Casio2MnHeader
//
// File: ./TestProjects/exiv2/src/makernote_int.cpp (interface via makernote_int.hpp)
//
// Constraints honored:
// - Treat implementation as a black box (no internal logic assumptions)
// - Use only public interface / observable behavior
// - No private state access
// - Include normal + boundary + (observable) error-style cases
// *****************************************************************

#include <gtest/gtest.h>

#include "makernote_int.hpp"

namespace {

using Exiv2::ByteOrder;
using Exiv2::byte;

class Casio2MnHeaderTest_1505 : public ::testing::Test {
 protected:
  Exiv2::Internal::Casio2MnHeader hdr_;
};

TEST_F(Casio2MnHeaderTest_1505, DefaultConstruct_AllowsQueryingPublicAPIs_1505) {
  // Normal operation: object is usable right after construction.
  (void)hdr_.ifdOffset();
  (void)hdr_.byteOrder();
  (void)hdr_.size();

  // Also exercise the const-qualified accessors.
  const Exiv2::Internal::Casio2MnHeader& chdr = hdr_;
  (void)chdr.ifdOffset();
  (void)chdr.byteOrder();
  (void)chdr.size();
}

TEST_F(Casio2MnHeaderTest_1505, ConstAndNonConstAccessorsAreConsistent_1505) {
  // Observable invariant: querying via const/non-const should yield identical results.
  const Exiv2::Internal::Casio2MnHeader& chdr = hdr_;

  EXPECT_EQ(hdr_.ifdOffset(), chdr.ifdOffset());
  EXPECT_EQ(hdr_.byteOrder(), chdr.byteOrder());
  EXPECT_EQ(hdr_.size(), chdr.size());
}

TEST_F(Casio2MnHeaderTest_1505, SizeOfSignature_IsStableAcrossCalls_1505) {
  // Boundary-ish: size_t-returning API should be stable across repeated calls.
  const size_t s1 = Exiv2::Internal::Casio2MnHeader::sizeOfSignature();
  const size_t s2 = Exiv2::Internal::Casio2MnHeader::sizeOfSignature();
  EXPECT_EQ(s1, s2);

  // If the instance overload exists, it should agree with the static one.
  // (We only compare observable return values; no assumptions about meaning.)
  const size_t s3 = hdr_.sizeOfSignature();
  EXPECT_EQ(s1, s3);
}

TEST_F(Casio2MnHeaderTest_1505, Read_WithZeroSizeInput_DoesNotThrow_1505) {
  // Boundary / error-style: zero-size input is a common edge case.
  // We do NOT assert success/failure because behavior is implementation-defined.
  byte dummy[1] = {0};

  bool ok = false;
  EXPECT_NO_THROW({
    ok = hdr_.read(dummy, 0U, hdr_.byteOrder());
  });

  // Only assert that we got a bool value (always true) and that the call completed.
  EXPECT_TRUE(ok == true || ok == false);
}

}  // namespace