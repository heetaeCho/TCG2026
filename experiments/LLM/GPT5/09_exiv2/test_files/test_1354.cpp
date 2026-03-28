// SPDX-License-Identifier: GPL-2.0-or-later

#include <gtest/gtest.h>

#include <type_traits>
#include <utility>
#include <iterator>   // std::begin, std::end, std::size (C++17)
#include <cstddef>    // std::size_t

#include "samsungmn_int.hpp"

namespace {

// Detection: std::size(x)
template <typename T, typename = void>
struct HasStdSize : std::false_type {};
template <typename T>
struct HasStdSize<T, std::void_t<decltype(std::size(std::declval<T>()))>> : std::true_type {};
template <typename T>
inline constexpr bool HasStdSizeV = HasStdSize<T>::value;

// Detection: std::begin/std::end
template <typename T, typename = void>
struct HasStdBeginEnd : std::false_type {};
template <typename T>
struct HasStdBeginEnd<T,
                      std::void_t<decltype(std::begin(std::declval<T>())),
                                  decltype(std::end(std::declval<T>()))>> : std::true_type {};
template <typename T>
inline constexpr bool HasStdBeginEndV = HasStdBeginEnd<T>::value;

template <typename T>
void ExpectNonEmptyOrNonNull(const T& v) {
  using D = std::decay_t<T>;
  if constexpr (std::is_pointer_v<D>) {
    EXPECT_NE(v, nullptr);
  } else if constexpr (HasStdSizeV<D>) {
    EXPECT_GT(std::size(v), static_cast<std::size_t>(0));
  } else if constexpr (HasStdBeginEndV<D>) {
    EXPECT_NE(std::begin(v), std::end(v));
  } else {
    // If the return type has no obvious "emptiness" concept, we can only verify callability.
    SUCCEED();
  }
}

}  // namespace

namespace Exiv2::Internal {

class Samsung2MakerNoteTest_1354 : public ::testing::Test {};

TEST_F(Samsung2MakerNoteTest_1354, TagListIsCallableAndLooksValid_1354) {
  const auto tl = Samsung2MakerNote::tagList();
  ExpectNonEmptyOrNonNull(tl);
}

TEST_F(Samsung2MakerNoteTest_1354, TagListPwIsCallableAndLooksValid_1354) {
  const auto tlpw = Samsung2MakerNote::tagListPw();
  ExpectNonEmptyOrNonNull(tlpw);
}

TEST_F(Samsung2MakerNoteTest_1354, TagListAndTagListPwReturnSameType_1354) {
  using TagListT = decltype(Samsung2MakerNote::tagList());
  using TagListPwT = decltype(Samsung2MakerNote::tagListPw());
  static_assert(std::is_same<TagListT, TagListPwT>::value, "tagList() and tagListPw() must return the same type");
  SUCCEED();
}

TEST_F(Samsung2MakerNoteTest_1354, TagListIsUsableInConstexprContext_1354) {
  // Observable requirement: the function is declared constexpr-capable; this verifies it can be used as such.
  constexpr auto tl = Samsung2MakerNote::tagList();
  constexpr auto tlpw = Samsung2MakerNote::tagListPw();
  (void)tl;
  (void)tlpw;
  SUCCEED();
}

TEST_F(Samsung2MakerNoteTest_1354, TagListRepeatedCallsAreConsistentWhenPointer_1354) {
  const auto a = Samsung2MakerNote::tagList();
  const auto b = Samsung2MakerNote::tagList();

  using D = std::decay_t<decltype(a)>;
  if constexpr (std::is_pointer_v<D>) {
    // If a pointer is returned, repeated calls should consistently point to the same list.
    EXPECT_EQ(a, b);
  } else {
    // For non-pointer return types, we only assert callability (no extra assumptions).
    SUCCEED();
  }
}

TEST_F(Samsung2MakerNoteTest_1354, TagListPwRepeatedCallsAreConsistentWhenPointer_1354) {
  const auto a = Samsung2MakerNote::tagListPw();
  const auto b = Samsung2MakerNote::tagListPw();

  using D = std::decay_t<decltype(a)>;
  if constexpr (std::is_pointer_v<D>) {
    EXPECT_EQ(a, b);
  } else {
    SUCCEED();
  }
}

}  // namespace Exiv2::Internal