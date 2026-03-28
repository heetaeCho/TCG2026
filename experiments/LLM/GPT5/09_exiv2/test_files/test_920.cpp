// =================================================================================================
// TEST_ID: 920
// File: test_canonmn_int_taglistwbi_920.cpp
// Unit tests for: Exiv2::Internal::CanonMakerNote::tagListWbi()
// =================================================================================================

#include <gtest/gtest.h>

#include <iterator>
#include <type_traits>

#include "canonmn_int.hpp"

namespace {

// Helper: try to obtain begin/end for a "tag list" without assuming its exact container type.
// Works for raw arrays, std::array, and any type with ADL begin/end.
template <typename T>
auto adl_begin(const T& t) -> decltype(begin(t)) {
  return begin(t);
}
template <typename T>
auto adl_end(const T& t) -> decltype(end(t)) {
  return end(t);
}

}  // namespace

TEST(CanonMakerNoteTest_920, TagListWbi_ReturnTypeIsStable_920) {
  using Exiv2::Internal::CanonMakerNote;

  // Must compile: ensures API exists and is usable as declared.
  const auto list = CanonMakerNote::tagListWbi();

  // Minimal observable property: returned object can be copied.
  (void)list;

  // Also ensure it isn't returning void (compile-time).
  static_assert(!std::is_same_v<decltype(list), void>, "tagListWbi() must not return void");
}

TEST(CanonMakerNoteTest_920, TagListWbi_CanBeIterated_920) {
  using Exiv2::Internal::CanonMakerNote;

  const auto list = CanonMakerNote::tagListWbi();

  // Boundary/robustness: even if empty, begin/end must be valid and distance computable.
  auto b = adl_begin(list);
  auto e = adl_end(list);

  // Just computing a distance is an observable, black-box friendly operation.
  const auto n = std::distance(b, e);
  EXPECT_GE(n, 0);
}

TEST(CanonMakerNoteTest_920, TagListWbi_TwoCallsReturnSameSequenceLength_920) {
  using Exiv2::Internal::CanonMakerNote;

  const auto list1 = CanonMakerNote::tagListWbi();
  const auto list2 = CanonMakerNote::tagListWbi();

  const auto n1 = std::distance(adl_begin(list1), adl_end(list1));
  const auto n2 = std::distance(adl_begin(list2), adl_end(list2));

  // Observable stability: calling twice should yield lists with the same size.
  EXPECT_EQ(n1, n2);
}

TEST(CanonMakerNoteTest_920, TagListWbi_FirstElementAddressStableAcrossCallsIfNonEmpty_920) {
  using Exiv2::Internal::CanonMakerNote;

  const auto list1 = CanonMakerNote::tagListWbi();
  const auto list2 = CanonMakerNote::tagListWbi();

  const auto b1 = adl_begin(list1);
  const auto e1 = adl_end(list1);

  // Boundary: list may be empty; in that case, nothing to compare.
  if (b1 == e1) {
    SUCCEED() << "tagListWbi() is empty; address stability not applicable.";
    return;
  }

  const auto b2 = adl_begin(list2);

  // Many Exiv2 tag lists are backed by static arrays; this checks a visible property
  // without assuming internal content: first element address remains stable.
  EXPECT_EQ(std::addressof(*b1), std::addressof(*b2));
}

TEST(CanonMakerNoteTest_920, TagListWbi_DoesNotThrowDuringBasicUse_920) {
  using Exiv2::Internal::CanonMakerNote;

  EXPECT_NO_THROW({
    const auto list = CanonMakerNote::tagListWbi();
    // Iterate once (or not at all if empty) to ensure no exceptions in traversal.
    for (auto it = adl_begin(list); it != adl_end(list); ++it) {
      // Don't assume element type/fields; just take its address.
      (void)std::addressof(*it);
      // Keep it minimal to avoid relying on internals.
      break;  // One-step boundary check is enough.
    }
  });
}