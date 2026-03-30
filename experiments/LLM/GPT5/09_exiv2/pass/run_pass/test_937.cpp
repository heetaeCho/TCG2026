// =================================================================================================
// TEST_ID: 937
// File: test_canonmn_int_taglistfil_937.cpp
// Unit tests for Exiv2::Internal::CanonMakerNote::tagListFil()
// =================================================================================================

#include <gtest/gtest.h>

#include <type_traits>

#include "canonmn_int.hpp"

namespace {

using Exiv2::Internal::CanonMakerNote;

class CanonMakerNoteTagListFilTest_937 : public ::testing::Test {};

TEST_F(CanonMakerNoteTagListFilTest_937, IsCallableInConstexprContext_937) {
  // This verifies the function can be used in a constant-evaluated context.
  // We do not assume anything about list contents.
  constexpr auto list = CanonMakerNote::tagListFil();
  (void)list;
  SUCCEED();
}

TEST_F(CanonMakerNoteTagListFilTest_937, ReturnsNonNullPointer_937) {
  // Observable behavior: function returns something usable as an address/pointer-like value.
  const auto list = CanonMakerNote::tagListFil();

  // In Exiv2, tag lists are typically returned as pointers. We only assert non-null.
  ASSERT_NE(list, nullptr);
}

TEST_F(CanonMakerNoteTagListFilTest_937, ReturnsStableValueAcrossCalls_937) {
  // Observable behavior: repeated calls should produce the same returned value for a static tag list.
  const auto list1 = CanonMakerNote::tagListFil();
  const auto list2 = CanonMakerNote::tagListFil();

  // If it is a pointer (typical), equality is well-defined and should be stable.
  EXPECT_EQ(list1, list2);
}

TEST_F(CanonMakerNoteTagListFilTest_937, ReturnedValueIsUsableAtRuntime_937) {
  // Boundary-ish: ensure the returned value can be copied, compared, and stored without side effects.
  const auto list = CanonMakerNote::tagListFil();
  ASSERT_NE(list, nullptr);

  // Copy / assign should be fine for a pointer-like return.
  const auto copy = list;
  EXPECT_EQ(copy, list);
}

}  // namespace