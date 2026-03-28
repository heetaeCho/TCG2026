// ***************************************************************** -*- C++ -*-
// Unit tests for Exiv2::Internal::Olympus2MnHeader
// File: test_olympus2_mnheader_1442.cpp
// *****************************************************************

#include <gtest/gtest.h>

#include <cstddef>
#include <cstdint>
#include <type_traits>
#include <vector>

#include "makernote_int.hpp"   // Exiv2::Internal::Olympus2MnHeader
#include "types.hpp"           // Exiv2::byte, Exiv2::ByteOrder (per project)

namespace {

// ---- Detection helpers (avoid assuming exact const/non-const overload set) ----
template <typename T>
auto CallSize(T& t, int) -> decltype(t.size()) {
  return t.size();
}
template <typename T>
auto CallSize(T& t, long) -> decltype(t.size() const_cast<const T&>(t).size(), std::declval<size_t>()) {
  return static_cast<const T&>(t).size();
}
template <typename T>
size_t SizeOf(T& t) {
  return static_cast<size_t>(CallSize(t, 0));
}

template <typename T>
auto CallSizeConst(const T& t, int) -> decltype(t.size()) {
  return t.size();
}
template <typename T>
size_t SizeOfConst(const T& t) {
  return static_cast<size_t>(CallSizeConst(t, 0));
}

template <typename T>
auto CallIfdOffset(const T& t, int) -> decltype(t.ifdOffset()) {
  return t.ifdOffset();
}
template <typename T>
size_t IfdOffsetOf(const T& t) {
  return static_cast<size_t>(CallIfdOffset(t, 0));
}

template <typename T>
auto CallBaseOffset(const T& t, size_t mnOffset, int) -> decltype(t.baseOffset(mnOffset)) {
  return t.baseOffset(mnOffset);
}
template <typename T>
size_t BaseOffsetOf(const T& t, size_t mnOffset) {
  return static_cast<size_t>(CallBaseOffset(t, mnOffset, 0));
}

}  // namespace

namespace Exiv2::Internal {

class Olympus2MnHeaderTest_1442 : public ::testing::Test {
 protected:
  Olympus2MnHeader header_;
};

TEST_F(Olympus2MnHeaderTest_1442, DefaultConstruction_AllowsBasicQueries_1442) {
  // Basic smoke test: public queries should be callable and stable (no throws).
  EXPECT_NO_THROW((void)SizeOf(header_));
  EXPECT_NO_THROW((void)SizeOfConst(static_cast<const Olympus2MnHeader&>(header_)));

  const Olympus2MnHeader& cref = header_;
  EXPECT_NO_THROW((void)IfdOffsetOf(cref));
  EXPECT_NO_THROW((void)BaseOffsetOf(cref, 0u));
  EXPECT_NO_THROW((void)BaseOffsetOf(cref, 1u));
  EXPECT_NO_THROW((void)BaseOffsetOf(cref, static_cast<size_t>(-1)));
}

TEST_F(Olympus2MnHeaderTest_1442, Size_IsStableAcrossRepeatedCalls_1442) {
  const size_t s1 = SizeOf(header_);
  const size_t s2 = SizeOf(header_);
  const size_t s3 = SizeOf(header_);
  EXPECT_EQ(s1, s2);
  EXPECT_EQ(s2, s3);

  const Olympus2MnHeader& cref = header_;
  const size_t cs1 = SizeOfConst(cref);
  const size_t cs2 = SizeOfConst(cref);
  EXPECT_EQ(cs1, cs2);
}

TEST_F(Olympus2MnHeaderTest_1442, Size_ConsistentBetweenConstAndNonConstViews_1442) {
  const size_t nonconst_size = SizeOf(header_);
  const Olympus2MnHeader& cref = header_;
  const size_t const_size = SizeOfConst(cref);
  EXPECT_EQ(nonconst_size, const_size);
}

TEST_F(Olympus2MnHeaderTest_1442, StaticSizeOfSignature_IsDeterministic_1442) {
  const size_t a = Olympus2MnHeader::sizeOfSignature();
  const size_t b = Olympus2MnHeader::sizeOfSignature();
  const size_t c = Olympus2MnHeader::sizeOfSignature();
  EXPECT_EQ(a, b);
  EXPECT_EQ(b, c);
}

TEST_F(Olympus2MnHeaderTest_1442, Read_NullptrAndZeroSize_DoesNotThrowAndIsDeterministic_1442) {
  // Boundary input: nullptr with size 0. We avoid assuming success/failure,
  // but require determinism and no exceptions.
  const size_t size_before = SizeOf(header_);

  bool r1 = false;
  bool r2 = false;
  EXPECT_NO_THROW(r1 = header_.read(nullptr, 0u, Exiv2::littleEndian));
  EXPECT_NO_THROW(r2 = header_.read(nullptr, 0u, Exiv2::littleEndian));
  EXPECT_EQ(r1, r2);

  // If the read indicates failure, size should not change (observable stability).
  const size_t size_after = SizeOf(header_);
  if (!r1) {
    EXPECT_EQ(size_before, size_after);
  }
}

TEST_F(Olympus2MnHeaderTest_1442, Read_SmallBuffer_BoundaryDoesNotThrow_1442) {
  // Boundary: very small non-null buffer.
  std::vector<Exiv2::byte> buf(1, static_cast<Exiv2::byte>(0));

  const size_t size_before = SizeOf(header_);

  bool r_le = false;
  bool r_be = false;
  EXPECT_NO_THROW(r_le = header_.read(buf.data(), buf.size(), Exiv2::littleEndian));
  EXPECT_NO_THROW(r_be = header_.read(buf.data(), buf.size(), Exiv2::bigEndian));

  // Deterministic for same inputs.
  bool r_le2 = true;
  EXPECT_NO_THROW(r_le2 = header_.read(buf.data(), buf.size(), Exiv2::littleEndian));
  EXPECT_EQ(r_le, r_le2);

  // If read fails for a given input, size should remain stable for that failure path.
  const size_t size_after = SizeOf(header_);
  if (!r_le) {
    EXPECT_EQ(size_before, size_after);
  }
}

TEST_F(Olympus2MnHeaderTest_1442, IfdOffset_And_BaseOffset_AreStableAcrossCalls_1442) {
  const Olympus2MnHeader& cref = header_;

  const size_t ifd1 = IfdOffsetOf(cref);
  const size_t ifd2 = IfdOffsetOf(cref);
  EXPECT_EQ(ifd1, ifd2);

  const size_t b0_1 = BaseOffsetOf(cref, 0u);
  const size_t b0_2 = BaseOffsetOf(cref, 0u);
  EXPECT_EQ(b0_1, b0_2);

  const size_t b1_1 = BaseOffsetOf(cref, 1u);
  const size_t b1_2 = BaseOffsetOf(cref, 1u);
  EXPECT_EQ(b1_1, b1_2);
}

}  // namespace Exiv2::Internal