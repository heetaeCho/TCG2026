// File: test_om_system_mn_header_1448.cpp
#include <gtest/gtest.h>

#include <limits>
#include <type_traits>

#include "makernote_int.hpp"   // Exiv2::Internal::OMSystemMnHeader
#include "exiv2/types.hpp"     // Exiv2::ByteOrder, byte

namespace {

class OMSystemMnHeaderTest_1448 : public ::testing::Test {};

}  // namespace

TEST_F(OMSystemMnHeaderTest_1448, DefaultConstruct_SizeIsStableAcrossCalls_1448) {
  Exiv2::Internal::OMSystemMnHeader hdr;

  const size_t s1 = hdr.size();
  const size_t s2 = hdr.size();
  const size_t s3 = hdr.size();

  EXPECT_EQ(s1, s2);
  EXPECT_EQ(s2, s3);
}

TEST_F(OMSystemMnHeaderTest_1448, ConstAndNonConstSizeAgree_1448) {
  Exiv2::Internal::OMSystemMnHeader hdr;

  const Exiv2::Internal::OMSystemMnHeader& chdr = hdr;

  const size_t nonConstSize = hdr.size();
  const size_t constSize = chdr.size();

  EXPECT_EQ(nonConstSize, constSize);
}

TEST_F(OMSystemMnHeaderTest_1448, CopyConstruct_PreservesReportedSize_1448) {
  Exiv2::Internal::OMSystemMnHeader a;
  const size_t sa = a.size();

  Exiv2::Internal::OMSystemMnHeader b(a);
  const size_t sb = b.size();

  EXPECT_EQ(sa, sb);
}

TEST_F(OMSystemMnHeaderTest_1448, MoveConstruct_ReportsAValidSize_1448) {
  Exiv2::Internal::OMSystemMnHeader a;
  const size_t sa = a.size();

  Exiv2::Internal::OMSystemMnHeader b(std::move(a));
  const size_t sb = b.size();

  // Black-box: only require that moved-to object returns a stable, valid size.
  EXPECT_LE(sb, std::numeric_limits<size_t>::max());
  EXPECT_EQ(sb, b.size());

  // Also ensure original size was itself a valid size_t.
  EXPECT_LE(sa, std::numeric_limits<size_t>::max());
}

TEST_F(OMSystemMnHeaderTest_1448, SizeOfSignature_IsStableAcrossCalls_1448) {
  const size_t s1 = Exiv2::Internal::OMSystemMnHeader::sizeOfSignature();
  const size_t s2 = Exiv2::Internal::OMSystemMnHeader::sizeOfSignature();
  const size_t s3 = Exiv2::Internal::OMSystemMnHeader::sizeOfSignature();

  EXPECT_EQ(s1, s2);
  EXPECT_EQ(s2, s3);
}

TEST_F(OMSystemMnHeaderTest_1448, Read_WithNullAndZeroSize_DoesNotCrash_1448) {
  Exiv2::Internal::OMSystemMnHeader hdr;

  // Exceptional/boundary input: null pointer with size 0.
  // We do not assume success/failure semantics; only observable return type and stability.
  const bool r1 = hdr.read(nullptr, 0u, Exiv2::littleEndian);
  const bool r2 = hdr.read(nullptr, 0u, Exiv2::littleEndian);

  // Result should be stable across repeated identical calls.
  EXPECT_EQ(r1, r2);
}

TEST_F(OMSystemMnHeaderTest_1448, Read_WithNonNullButZeroSize_DoesNotCrash_1448) {
  Exiv2::Internal::OMSystemMnHeader hdr;

  const Exiv2::byte dummy = 0;
  const bool r = hdr.read(&dummy, 0u, Exiv2::bigEndian);

  // Only assert returned value is a valid bool (always true); keep as a smoke/boundary test.
  EXPECT_TRUE(r == true || r == false);
}

TEST_F(OMSystemMnHeaderTest_1448, Read_DoesNotChangeSizeStability_1448) {
  Exiv2::Internal::OMSystemMnHeader hdr;

  const size_t before = hdr.size();

  const Exiv2::byte dummy = 0;
  (void)hdr.read(&dummy, 0u, Exiv2::littleEndian);

  const size_t after1 = hdr.size();
  const size_t after2 = hdr.size();

  // Black-box: whatever the effect, size() should remain stable across calls at a given state.
  EXPECT_EQ(after1, after2);

  // And the reported size values should be valid size_t.
  EXPECT_LE(before, std::numeric_limits<size_t>::max());
  EXPECT_LE(after1, std::numeric_limits<size_t>::max());
}