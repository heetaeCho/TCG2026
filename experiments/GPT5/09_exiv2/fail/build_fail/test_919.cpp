// File: test_canonmn_int_taglistfcd3_919.cpp
// Unit tests for Exiv2::Internal::CanonMakerNote::tagListFcd3()
// TEST_ID: 919

#include <gtest/gtest.h>

#include <type_traits>
#include <utility>
#include <memory>

#include "canonmn_int.hpp"

namespace {

using Exiv2::Internal::CanonMakerNote;

template <typename T>
constexpr bool kIsEqualityComparableV = requires(const T& a, const T& b) {
  { a == b } -> std::convertible_to<bool>;
};

template <typename T>
void ExpectStableReturnAcrossCalls(const T& a, const T& b) {
  using Decayed = std::decay_t<T>;
  if constexpr (kIsEqualityComparableV<Decayed>) {
    EXPECT_TRUE(a == b);
  } else {
    // Fallback: if the returned object isn't equality comparable, at least
    // verify the address of the returned object is stable across calls.
    EXPECT_EQ(std::addressof(a), std::addressof(b));
  }
}

class CanonMakerNoteTagListFcd3Test_919 : public ::testing::Test {};

}  // namespace

TEST_F(CanonMakerNoteTagListFcd3Test_919, CallableAndReturnsSomething_919) {
  // Black-box: verify the function is callable and returns a value.
  auto list = CanonMakerNote::tagListFcd3();
  (void)list;
  SUCCEED();
}

TEST_F(CanonMakerNoteTagListFcd3Test_919, ReturnIsStableAcrossCalls_919) {
  // Black-box: repeated calls should be stable (typically returning the same
  // static table / view).
  auto a = CanonMakerNote::tagListFcd3();
  auto b = CanonMakerNote::tagListFcd3();
  ExpectStableReturnAcrossCalls(a, b);
}

TEST_F(CanonMakerNoteTagListFcd3Test_919, NotNullWhenPointerLike_919) {
  // Black-box: if the API returns a pointer-like value, it should be non-null.
  // If it is not pointer-like, this test simply documents that fact.
  auto list = CanonMakerNote::tagListFcd3();
  using T = std::decay_t<decltype(list)>;

  if constexpr (std::is_pointer_v<T>) {
    ASSERT_NE(list, nullptr);
  } else {
    SUCCEED();
  }
}