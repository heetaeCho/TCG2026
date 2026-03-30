// File: test_PentaxDngMnHeader_sizeOfSignature_1478.cpp

#include <gtest/gtest.h>

#include <type_traits>
#include <utility>

#include "makernote_int.hpp"

namespace {

using Exiv2::Internal::PentaxDngMnHeader;

// ---- Detection helpers (so tests compile even if some overloads aren't present) ----

template <typename T, typename = void>
struct HasMemberSizeOfSignature : std::false_type {};
template <typename T>
struct HasMemberSizeOfSignature<T, std::void_t<decltype(std::declval<T&>().sizeOfSignature())>>
    : std::true_type {};

template <typename T, typename = void>
struct HasStaticSizeOfSignature : std::false_type {};
template <typename T>
struct HasStaticSizeOfSignature<T, std::void_t<decltype(T::sizeOfSignature())>> : std::true_type {};

template <typename T, typename = void>
struct HasConstMemberSizeOfSignature : std::false_type {};
template <typename T>
struct HasConstMemberSizeOfSignature<T,
                                     std::void_t<decltype(std::declval<const T&>().sizeOfSignature())>>
    : std::true_type {};

}  // namespace

class PentaxDngMnHeaderTest_1478 : public ::testing::Test {};

TEST_F(PentaxDngMnHeaderTest_1478, MemberSizeOfSignature_IsStableAcrossCalls_1478) {
  PentaxDngMnHeader h{};

  if constexpr (HasMemberSizeOfSignature<PentaxDngMnHeader>::value) {
    const auto v1 = h.sizeOfSignature();
    const auto v2 = h.sizeOfSignature();
    EXPECT_EQ(v1, v2);
    EXPECT_GT(v1, 0u);
  } else if constexpr (HasConstMemberSizeOfSignature<PentaxDngMnHeader>::value) {
    const auto v1 = static_cast<const PentaxDngMnHeader&>(h).sizeOfSignature();
    const auto v2 = static_cast<const PentaxDngMnHeader&>(h).sizeOfSignature();
    EXPECT_EQ(v1, v2);
    EXPECT_GT(v1, 0u);
  } else {
    GTEST_SKIP() << "PentaxDngMnHeader::sizeOfSignature() member function is not available.";
  }
}

TEST_F(PentaxDngMnHeaderTest_1478, MemberSizeOfSignature_IsConsistentAcrossInstances_1478) {
  PentaxDngMnHeader a{};
  PentaxDngMnHeader b{};

  if constexpr (HasMemberSizeOfSignature<PentaxDngMnHeader>::value) {
    EXPECT_EQ(a.sizeOfSignature(), b.sizeOfSignature());
    EXPECT_GT(a.sizeOfSignature(), 0u);
  } else if constexpr (HasConstMemberSizeOfSignature<PentaxDngMnHeader>::value) {
    const auto av = static_cast<const PentaxDngMnHeader&>(a).sizeOfSignature();
    const auto bv = static_cast<const PentaxDngMnHeader&>(b).sizeOfSignature();
    EXPECT_EQ(av, bv);
    EXPECT_GT(av, 0u);
  } else {
    GTEST_SKIP() << "PentaxDngMnHeader::sizeOfSignature() member function is not available.";
  }
}

TEST_F(PentaxDngMnHeaderTest_1478, StaticAndMemberSizeOfSignature_MatchWhenBothExist_1478) {
  PentaxDngMnHeader h{};

  if constexpr (HasStaticSizeOfSignature<PentaxDngMnHeader>::value &&
                HasMemberSizeOfSignature<PentaxDngMnHeader>::value) {
    EXPECT_EQ(PentaxDngMnHeader::sizeOfSignature(), h.sizeOfSignature());
    EXPECT_GT(PentaxDngMnHeader::sizeOfSignature(), 0u);
  } else if constexpr (HasStaticSizeOfSignature<PentaxDngMnHeader>::value &&
                       HasConstMemberSizeOfSignature<PentaxDngMnHeader>::value) {
    EXPECT_EQ(PentaxDngMnHeader::sizeOfSignature(),
              static_cast<const PentaxDngMnHeader&>(h).sizeOfSignature());
    EXPECT_GT(PentaxDngMnHeader::sizeOfSignature(), 0u);
  } else {
    GTEST_SKIP() << "Static/member sizeOfSignature comparison not possible (missing one or both).";
  }
}

TEST_F(PentaxDngMnHeaderTest_1478, SizeOfSignature_ReturnTypeIsSizeTLike_1478) {
  // Boundary/contract-style check: verify the return type behaves like an unsigned size.
  // We avoid assuming exact typedefs across platforms; we only require comparability to size_t.
  if constexpr (HasStaticSizeOfSignature<PentaxDngMnHeader>::value) {
    using Ret = decltype(PentaxDngMnHeader::sizeOfSignature());
    static_assert(std::is_integral<Ret>::value, "sizeOfSignature() should return an integral type");
    static_assert(!std::is_signed<Ret>::value, "sizeOfSignature() should return an unsigned type");
  } else if constexpr (HasMemberSizeOfSignature<PentaxDngMnHeader>::value) {
    using Ret = decltype(std::declval<PentaxDngMnHeader&>().sizeOfSignature());
    static_assert(std::is_integral<Ret>::value, "sizeOfSignature() should return an integral type");
    static_assert(!std::is_signed<Ret>::value, "sizeOfSignature() should return an unsigned type");
  } else if constexpr (HasConstMemberSizeOfSignature<PentaxDngMnHeader>::value) {
    using Ret = decltype(std::declval<const PentaxDngMnHeader&>().sizeOfSignature());
    static_assert(std::is_integral<Ret>::value, "sizeOfSignature() should return an integral type");
    static_assert(!std::is_signed<Ret>::value, "sizeOfSignature() should return an unsigned type");
  } else {
    GTEST_SKIP() << "No accessible sizeOfSignature() found to validate return type.";
  }

  SUCCEED();
}