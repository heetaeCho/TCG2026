// File: test_canonmn_int_taglistle_934.cpp
#include <gtest/gtest.h>

#include <type_traits>
#include <utility>

// Include the header under test
#include "canonmn_int.hpp"

namespace {

// Helper: detect if T supports operator==
template <typename T, typename = void>
struct is_equality_comparable : std::false_type {};
template <typename T>
struct is_equality_comparable<T, std::void_t<decltype(std::declval<const T&>() == std::declval<const T&>())>>
    : std::true_type {};
template <typename T>
inline constexpr bool is_equality_comparable_v = is_equality_comparable<T>::value;

// Helper: compare two values if possible, otherwise at least ensure both expressions are well-formed.
template <typename T>
void ExpectStableAcrossCalls(const T& a, const T& b) {
  if constexpr (std::is_pointer_v<T>) {
    // For pointer-like tag lists, stability means same address across calls.
    EXPECT_EQ(a, b);
  } else if constexpr (is_equality_comparable_v<T>) {
    // For value-like returns, stability means equality across calls.
    EXPECT_TRUE(a == b);
  } else {
    // If not comparable, just ensure both exist (compile-time / type-checking).
    SUCCEED();
    (void)a;
    (void)b;
  }
}

}  // namespace

// The TEST_ID is 934

TEST(CanonMakerNoteTest_934, TagListLe_IsCallable_934) {
  // Normal operation: callable and returns some object.
  auto tl = Exiv2::Internal::CanonMakerNote::tagListLe();
  (void)tl;
  SUCCEED();
}

TEST(CanonMakerNoteTest_934, TagListLe_StableAcrossMultipleCalls_934) {
  // Observable behavior: repeated calls should be stable (same pointer or equal value).
  const auto a = Exiv2::Internal::CanonMakerNote::tagListLe();
  const auto b = Exiv2::Internal::CanonMakerNote::tagListLe();
  ExpectStableAcrossCalls(a, b);
}

TEST(CanonMakerNoteTest_934, TagListLe_UsableInConstexprContext_934) {
  // Boundary/compile-time usability: the interface declares constexpr, so it should be
  // usable in a constant-evaluated context (at least initialization).
  constexpr auto tl = Exiv2::Internal::CanonMakerNote::tagListLe();
  (void)tl;
  SUCCEED();
}

TEST(CanonMakerNoteTest_934, TagListLe_TypeIsConsistent_934) {
  // Boundary: ensure the return type is consistent and matches itself across expressions.
  using ReturnT = decltype(Exiv2::Internal::CanonMakerNote::tagListLe());
  const ReturnT a = Exiv2::Internal::CanonMakerNote::tagListLe();
  const ReturnT b = Exiv2::Internal::CanonMakerNote::tagListLe();
  ExpectStableAcrossCalls(a, b);
}