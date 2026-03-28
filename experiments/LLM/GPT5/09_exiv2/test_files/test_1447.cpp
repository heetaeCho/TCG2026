// TEST_ID: 1447
// File: test_omsystem_mn_header_1447.cpp

#include <gtest/gtest.h>

#include <cstddef>
#include <type_traits>

#include "makernote_int.hpp"

namespace {

using Exiv2::Internal::OMSystemMnHeader;

// Detection helpers (keep tests compatible if the real header differs from the inferred snippet).
template <typename T>
concept HasMemberSizeOfSignature = requires(T t) {
  { t.sizeOfSignature() } -> std::convertible_to<std::size_t>;
};

template <typename T>
concept HasStaticSizeOfSignature = requires {
  { T::sizeOfSignature() } -> std::convertible_to<std::size_t>;
};

class OMSystemMnHeaderTest_1447 : public ::testing::Test {};

}  // namespace

TEST_F(OMSystemMnHeaderTest_1447, MemberSizeOfSignature_IsNonZero_1447) {
  if constexpr (!HasMemberSizeOfSignature<OMSystemMnHeader>) {
    GTEST_SKIP() << "OMSystemMnHeader::sizeOfSignature() member is not available in this build.";
  } else {
    OMSystemMnHeader hdr;
    const std::size_t n = hdr.sizeOfSignature();
    EXPECT_GT(n, 0u);
  }
}

TEST_F(OMSystemMnHeaderTest_1447, MemberSizeOfSignature_IsStableAcrossCalls_1447) {
  if constexpr (!HasMemberSizeOfSignature<OMSystemMnHeader>) {
    GTEST_SKIP() << "OMSystemMnHeader::sizeOfSignature() member is not available in this build.";
  } else {
    OMSystemMnHeader hdr;
    const std::size_t a = hdr.sizeOfSignature();
    const std::size_t b = hdr.sizeOfSignature();
    EXPECT_EQ(a, b);
  }
}

TEST_F(OMSystemMnHeaderTest_1447, MemberSizeOfSignature_ConsistentAcrossInstances_1447) {
  if constexpr (!HasMemberSizeOfSignature<OMSystemMnHeader>) {
    GTEST_SKIP() << "OMSystemMnHeader::sizeOfSignature() member is not available in this build.";
  } else {
    OMSystemMnHeader hdr1;
    OMSystemMnHeader hdr2;
    EXPECT_EQ(hdr1.sizeOfSignature(), hdr2.sizeOfSignature());
  }
}

TEST_F(OMSystemMnHeaderTest_1447, StaticAndMemberSizeOfSignature_MatchWhenBothExist_1447) {
  if constexpr (!(HasMemberSizeOfSignature<OMSystemMnHeader> && HasStaticSizeOfSignature<OMSystemMnHeader>)) {
    GTEST_SKIP() << "Both static and member sizeOfSignature() are not available in this build.";
  } else {
    OMSystemMnHeader hdr;
    const std::size_t member_n = hdr.sizeOfSignature();
    const std::size_t static_n = OMSystemMnHeader::sizeOfSignature();
    EXPECT_EQ(member_n, static_n);
  }
}

TEST_F(OMSystemMnHeaderTest_1447, SizeOfSignature_IsReasonable_1447) {
  // Boundary-style check: signature size should be a small positive constant (without assuming an exact value).
  std::size_t n = 0;

  if constexpr (HasMemberSizeOfSignature<OMSystemMnHeader>) {
    OMSystemMnHeader hdr;
    n = hdr.sizeOfSignature();
  } else if constexpr (HasStaticSizeOfSignature<OMSystemMnHeader>) {
    n = OMSystemMnHeader::sizeOfSignature();
  } else {
    GTEST_SKIP() << "No sizeOfSignature() API available in this build.";
  }

  EXPECT_GT(n, 0u);
  EXPECT_LT(n, 1024u);  // generous upper bound to avoid over-constraining.
}