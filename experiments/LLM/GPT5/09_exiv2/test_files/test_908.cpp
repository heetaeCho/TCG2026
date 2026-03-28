// ============================================================================
// TEST_ID: 908
// File: test_canonmn_int_taglist_908.cpp
// ============================================================================

#include <gtest/gtest.h>

#include <type_traits>
#include <utility>

#include "canonmn_int.hpp"

namespace {

using Exiv2::Internal::CanonMakerNote;

template <typename T>
constexpr bool is_pointer_v = std::is_pointer<T>::value;

template <typename T>
void expectSameTagListIdentity(const T& a, const T& b) {
  if constexpr (is_pointer_v<T>) {
    // Most common in Exiv2: TagInfo* / const TagInfo*
    EXPECT_EQ(a, b);
  } else {
    // If tagList() returns a reference to an array or other object,
    // compare identity via address.
    EXPECT_EQ(std::addressof(a), std::addressof(b));
  }
}

}  // namespace

class CanonMakerNoteTest_908 : public ::testing::Test {};

TEST_F(CanonMakerNoteTest_908, TagList_IsCallableAndStableAcrossCalls_908) {
  // Normal operation: callable and returns a stable identity across calls.
  const auto t1 = CanonMakerNote::tagList();
  const auto t2 = CanonMakerNote::tagList();

  expectSameTagListIdentity(t1, t2);
}

TEST_F(CanonMakerNoteTest_908, TagList_DoesNotThrow_908) {
  // Boundary/error-safety: should be safe to call repeatedly.
  EXPECT_NO_THROW({
    (void)CanonMakerNote::tagList();
    (void)CanonMakerNote::tagList();
  });
}

TEST_F(CanonMakerNoteTest_908, TagList_IsUsableInConstantExpression_WhenPossible_908) {
  // Boundary: verify the interface supports constexpr evaluation if the
  // underlying definition allows it (it is declared constexpr in the interface).
  //
  // If the return type is a pointer or literal-type value, this should compile
  // and run. If it returns a non-literal type, the constexpr variable may fail
  // to compile in some environments; Exiv2 typically returns a pointer.
  constexpr auto tl = CanonMakerNote::tagList();
  (void)tl;

  // Runtime sanity: repeated calls refer to the same identity.
  const auto rt = CanonMakerNote::tagList();
  expectSameTagListIdentity(tl, rt);
}