// -----------------------------------------------------------------------------
// TEST_ID 921
// Unit tests for Exiv2::Internal::CanonMakerNote::tagListCo()
// File: ./TestProjects/exiv2/src/canonmn_int.hpp
// -----------------------------------------------------------------------------

#include <gtest/gtest.h>

#include <type_traits>

#include "canonmn_int.hpp"

namespace {

// Compile-time sanity checks (not counted as gtest "tests", but validate interface properties).
static_assert(std::is_same_v<decltype(Exiv2::Internal::CanonMakerNote::tagListCo()),
                            decltype(Exiv2::Internal::CanonMakerNote::tagListCo())>,
              "tagListCo() must be a stable, well-formed expression type.");

class CanonMakerNoteTest_921 : public ::testing::Test {};

}  // namespace

TEST_F(CanonMakerNoteTest_921, TagListCo_ReturnsStableValueAcrossCalls_921) {
  const auto v1 = Exiv2::Internal::CanonMakerNote::tagListCo();
  const auto v2 = Exiv2::Internal::CanonMakerNote::tagListCo();

  // Observable behavior: repeated calls should return an identical value (same underlying tag list).
  EXPECT_EQ(v1, v2);
}

TEST_F(CanonMakerNoteTest_921, TagListCo_IsUsableInConstexprContext_921) {
  // The interface declares this function as constexpr; validate it can be used to initialize
  // a constexpr variable (observable at compile-time).
  constexpr auto v = Exiv2::Internal::CanonMakerNote::tagListCo();

  // At runtime, just ensure the value is consistent with a non-constexpr call.
  const auto runtime_v = Exiv2::Internal::CanonMakerNote::tagListCo();
  EXPECT_EQ(v, runtime_v);
}

TEST_F(CanonMakerNoteTest_921, TagListCo_ReturnTypeIsNotVoid_921) {
  // Basic interface/property check: the function returns something usable.
  using RetT = decltype(Exiv2::Internal::CanonMakerNote::tagListCo());
  EXPECT_FALSE((std::is_void_v<RetT>));
}