// TEST_ID 918
// File: test_canonmn_int_taglistmc_918.cpp

#include <gtest/gtest.h>

#include <type_traits>

#include "canonmn_int.hpp"

namespace {

using Exiv2::Internal::CanonMakerNote;

// Helper: get a stable address we can compare across calls, regardless of whether
// tagListMc() returns a pointer or an array reference.
template <typename T>
constexpr const void* stableAddress(const T& v) {
  if constexpr (std::is_pointer_v<std::remove_reference_t<T>>) {
    return static_cast<const void*>(v);
  } else {
    return static_cast<const void*>(&v);
  }
}

class CanonMakerNoteTagListMcTest_918 : public ::testing::Test {};

TEST_F(CanonMakerNoteTagListMcTest_918, ReturnsStableStorageAcrossCalls_918) {
  const auto a = CanonMakerNote::tagListMc();
  const auto b = CanonMakerNote::tagListMc();

  EXPECT_EQ(stableAddress(a), stableAddress(b));
}

TEST_F(CanonMakerNoteTagListMcTest_918, ReturnedValueIsUsableInExpression_918) {
  // Boundary-ish: make sure the returned value can be materialized and addressed.
  const auto v = CanonMakerNote::tagListMc();
  EXPECT_NE(stableAddress(v), nullptr);
}

TEST_F(CanonMakerNoteTagListMcTest_918, TypeIsConsistentAcrossInvocations_918) {
  // Compile-time boundary: the return type should be stable.
  using Ret1 = decltype(CanonMakerNote::tagListMc());
  using Ret2 = decltype(CanonMakerNote::tagListMc());
  static_assert(std::is_same_v<Ret1, Ret2>, "tagListMc() return type must be consistent");
  SUCCEED();
}

}  // namespace