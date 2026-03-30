// LinkDest_test_269.cpp
//
// Unit tests for LinkDest (poppler/Link.h)
// Constraints respected:
// - Treat LinkDest as a black box (no assumptions about internal parsing/logic).
// - Use only observable behavior via the public interface.
// - Avoid private/internal state access.

#include <gtest/gtest.h>

#include <type_traits>
#include <utility>

#include "Link.h"  // Adjust include path as needed for your build (e.g., <poppler/Link.h>)

namespace {

class LinkDestTest_269 : public ::testing::Test {};

template <typename T, typename = void>
struct has_isOk_const_bool : std::false_type {};

template <typename T>
struct has_isOk_const_bool<T, std::void_t<decltype(std::declval<const T&>().isOk())>>
    : std::bool_constant<std::is_same_v<decltype(std::declval<const T&>().isOk()), bool>> {};

}  // namespace

// ----------------------
// Compile-time interface checks
// ----------------------

TEST_F(LinkDestTest_269, Interface_IsOkIsConstAndReturnsBool_269) {
  static_assert(has_isOk_const_bool<LinkDest>::value,
                "LinkDest::isOk() must be callable on const and return bool");
  SUCCEED();
}

TEST_F(LinkDestTest_269, Interface_ConstructibleFromConstArrayRef_269) {
  static_assert(std::is_constructible_v<LinkDest, const Array&>,
                "LinkDest must be constructible from const Array&");
  SUCCEED();
}

TEST_F(LinkDestTest_269, Interface_CopyMoveTraitsAreWellFormed_269) {
  // We don't require any specific trait to be true/false; we just ensure queries are well-formed.
  // This is an interface-level check and does not infer internal logic.
  (void)std::is_copy_constructible_v<LinkDest>;
  (void)std::is_move_constructible_v<LinkDest>;
  (void)std::is_copy_assignable_v<LinkDest>;
  (void)std::is_move_assignable_v<LinkDest>;
  SUCCEED();
}

// ----------------------
// Runtime behavior checks (only when Array can be default-constructed)
// ----------------------

TEST_F(LinkDestTest_269, ConstructFromDefaultArray_IsOkIdempotent_269) {
  if constexpr (std::is_default_constructible_v<Array> &&
                std::is_constructible_v<LinkDest, const Array&>) {
    Array a;
    LinkDest d(a);

    // Black-box: we do not assert true/false; we only assert stable observable behavior.
    const bool first = d.isOk();
    const bool second = d.isOk();
    EXPECT_EQ(first, second);
  } else {
    GTEST_SKIP() << "Array is not default-constructible in this build; runtime construction skipped.";
  }
}

TEST_F(LinkDestTest_269, ConstructFromDefaultArray_IsOkCallableOnConst_269) {
  if constexpr (std::is_default_constructible_v<Array> &&
                std::is_constructible_v<LinkDest, const Array&>) {
    Array a;
    const LinkDest d(a);

    // Ensure const-call works at runtime too.
    EXPECT_NO_THROW({
      const bool v = d.isOk();
      (void)v;
    });
  } else {
    GTEST_SKIP() << "Array is not default-constructible in this build; runtime construction skipped.";
  }
}

TEST_F(LinkDestTest_269, TwoInstancesFromSameArray_ProduceConsistentOkFlag_269) {
  if constexpr (std::is_default_constructible_v<Array> &&
                std::is_constructible_v<LinkDest, const Array&>) {
    Array a;

    LinkDest d1(a);
    LinkDest d2(a);

    // Black-box: we do not infer what should be "ok"; only that identical inputs
    // yield consistent observable results.
    EXPECT_EQ(d1.isOk(), d2.isOk());
  } else {
    GTEST_SKIP() << "Array is not default-constructible in this build; runtime construction skipped.";
  }
}

TEST_F(LinkDestTest_269, IsOk_DoesNotThrow_269) {
  if constexpr (std::is_default_constructible_v<Array> &&
                std::is_constructible_v<LinkDest, const Array&>) {
    Array a;
    LinkDest d(a);

    EXPECT_NO_THROW({
      const bool v = d.isOk();
      (void)v;
    });
  } else {
    GTEST_SKIP() << "Array is not default-constructible in this build; runtime construction skipped.";
  }
}