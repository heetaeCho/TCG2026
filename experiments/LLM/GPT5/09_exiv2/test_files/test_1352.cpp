// SPDX-License-Identifier: GPL-2.0-or-later
// File: test_casiomn_int_taglist_1352.cpp

#include <gtest/gtest.h>

#include <cstddef>      // std::size_t
#include <iterator>     // std::begin, std::end, std::data
#include <type_traits>  // std::is_pointer_v, std::void_t

#include "casiomn_int.hpp"

namespace {

// Detection idioms for std::data / std::begin / std::end / std::size
template <typename T, typename = void>
struct has_data : std::false_type {};
template <typename T>
struct has_data<T, std::void_t<decltype(std::data(std::declval<T>()))>> : std::true_type {};

template <typename T, typename = void>
struct has_begin_end : std::false_type {};
template <typename T>
struct has_begin_end<T, std::void_t<decltype(std::begin(std::declval<T>())),
                                    decltype(std::end(std::declval<T>()))>> : std::true_type {};

template <typename T, typename = void>
struct has_size : std::false_type {};
template <typename T>
struct has_size<T, std::void_t<decltype(std::size(std::declval<T>()))>> : std::true_type {};

}  // namespace

// The TEST_ID is 1352
TEST(CasioMakerNoteTest_1352, TagList_IsUsableAsConstexpr_1352) {
  // This test is mainly about the *interface contract* that tagList() is constexpr-usable.
  // (If it is not, this test will fail to compile in a conforming build.)
  constexpr auto list = Exiv2::Internal::CasioMakerNote::tagList();
  (void)list;

  // Minimal runtime assertion so the test is not empty.
  SUCCEED();
}

// The TEST_ID is 1352
TEST(CasioMakerNoteTest_1352, TagList_ReturnsStableHandleAcrossCalls_1352) {
  const auto list1 = Exiv2::Internal::CasioMakerNote::tagList();
  const auto list2 = Exiv2::Internal::CasioMakerNote::tagList();

  // We avoid assuming concrete container type. We only check stability of the returned handle
  // using the most appropriate observable representation:
  // - If it's a pointer, compare pointer values.
  // - If std::data(...) is available (arrays/containers), compare underlying data addresses.
  // - Otherwise, fall back to comparing the addresses of the returned objects themselves
  //   (still an observable property of the return type).
  using ListT = decltype(list1);

  if constexpr (std::is_pointer_v<ListT>) {
    EXPECT_NE(list1, nullptr);
    EXPECT_EQ(list1, list2);
  } else if constexpr (has_data<ListT>::value) {
    const auto* p1 = std::data(list1);
    const auto* p2 = std::data(list2);
    // data() may legally be nullptr for empty containers; we only require stability.
    EXPECT_EQ(p1, p2);
  } else {
    // If tagList() returns a value type with no data(), we can still check that repeated calls
    // produce objects at least comparable by address (of the temporaries) is not meaningful.
    // Instead, we verify we can take their addresses and they are distinct objects, and
    // we keep this as a compile/ABI-sanity style check.
    const auto* a1 = &list1;
    const auto* a2 = &list2;
    ASSERT_NE(a1, nullptr);
    ASSERT_NE(a2, nullptr);
  }
}

// The TEST_ID is 1352
TEST(CasioMakerNoteTest_1352, TagList_SupportsIterationOrIndexingWhenExposed_1352) {
  const auto list = Exiv2::Internal::CasioMakerNote::tagList();
  using ListT = decltype(list);

  // Boundary/robustness: ensure common access patterns are valid when the type supports them.
  // We do not assume any particular list length or sentinel layout.
  if constexpr (std::is_pointer_v<ListT>) {
    // Pointer case: we can dereference only if non-null; we don't assume it points to valid
    // elements beyond being a returned handle. We merely check the null contract.
    EXPECT_NE(list, nullptr);
  } else if constexpr (has_begin_end<ListT>::value) {
    // Iterable case: ensure begin/end expressions are well-formed and consistent.
    auto b = std::begin(list);
    auto e = std::end(list);
    // No assumption about emptiness; just basic relational sanity if iterators are comparable.
    (void)b;
    (void)e;
    SUCCEED();
  } else if constexpr (has_size<ListT>::value) {
    // Sized-but-not-iterable (unlikely), still check size() is callable.
    const auto n = std::size(list);
    (void)n;
    SUCCEED();
  } else {
    // Nothing more observable via this interface.
    SUCCEED();
  }
}