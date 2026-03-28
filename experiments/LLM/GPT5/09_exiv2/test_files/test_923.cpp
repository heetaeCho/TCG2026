// File: test_canonmn_int_taglistfcd1_923.cpp
#include <gtest/gtest.h>

#include <type_traits>
#include <utility>

#include "canonmn_int.hpp"

namespace {

template <typename T, typename = void>
struct HasEqual : std::false_type {};
template <typename T>
struct HasEqual<T, std::void_t<decltype(std::declval<T>() == std::declval<T>())>> : std::true_type {};

template <typename T, typename = void>
struct HasNotEqualNullptr : std::false_type {};
template <typename T>
struct HasNotEqualNullptr<T, std::void_t<decltype(std::declval<T>() != nullptr)>> : std::true_type {};

template <typename T, typename = void>
struct HasAddressOf : std::false_type {};
template <typename T>
struct HasAddressOf<T, std::void_t<decltype(std::addressof(std::declval<T&>()))>> : std::true_type {};

class CanonMakerNoteTagListFcd1Test_923 : public ::testing::Test {};

}  // namespace

TEST_F(CanonMakerNoteTagListFcd1Test_923, IsCallableAndReturnsSameValueOnRepeatedCalls_923) {
  using Exiv2::Internal::CanonMakerNote;

  auto r1 = CanonMakerNote::tagListFcd1();
  auto r2 = CanonMakerNote::tagListFcd1();

  using Ret = decltype(r1);

  if constexpr (HasEqual<Ret>::value) {
    // If the return type supports equality (e.g., pointers), verify stability across calls.
    EXPECT_TRUE(r1 == r2);
  } else if constexpr (HasAddressOf<Ret>::value) {
    // If equality isn't available (e.g., reference to an array), compare object identity.
    EXPECT_EQ(std::addressof(r1), std::addressof(r2));
  } else {
    // Minimal observable requirement: it compiles and runs.
    SUCCEED();
  }
}

TEST_F(CanonMakerNoteTagListFcd1Test_923, ReturnsNonNullWhenPointerLike_923) {
  using Exiv2::Internal::CanonMakerNote;

  auto r = CanonMakerNote::tagListFcd1();
  using Ret = decltype(r);

  if constexpr (HasNotEqualNullptr<Ret>::value) {
    EXPECT_NE(r, nullptr);
  } else {
    // Not pointer-like (e.g., reference/array): nothing null to check through interface.
    SUCCEED();
  }
}

TEST_F(CanonMakerNoteTagListFcd1Test_923, UsableInUnevaluatedContextDecltype_923) {
  using Exiv2::Internal::CanonMakerNote;

  // Observable, interface-only check: the symbol is usable and has a consistent type.
  using Ret1 = decltype(CanonMakerNote::tagListFcd1());
  using Ret2 = decltype(CanonMakerNote::tagListFcd1());
  EXPECT_TRUE((std::is_same_v<Ret1, Ret2>));
}