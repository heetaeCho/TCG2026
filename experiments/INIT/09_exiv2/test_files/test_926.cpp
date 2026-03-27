// ============================================================================
// TEST_ID: 926
// File: test_canonmn_int_taglistfl_926.cpp
// Unit tests for Exiv2::Internal::CanonMakerNote::tagListFl()
// ============================================================================

#include <gtest/gtest.h>

#include <type_traits>
#include <utility>

#include "canonmn_int.hpp"

namespace {

// Helper: get a stable address for either pointers or references/values.
template <typename T>
constexpr const void* addr_of(const T& v) noexcept {
  return static_cast<const void*>(std::addressof(v));
}

template <typename T>
constexpr const void* addr_of_ptr(T p) noexcept {
  return static_cast<const void*>(p);
}

template <typename T>
constexpr const void* stable_address(const T& v) noexcept {
  if constexpr (std::is_pointer_v<std::decay_t<T>>) {
    return addr_of_ptr(v);
  } else {
    return addr_of(v);
  }
}

template <typename T>
constexpr bool is_null_like(const T& v) noexcept {
  if constexpr (std::is_pointer_v<std::decay_t<T>>) {
    return v == nullptr;
  } else {
    // For non-pointer return types, "null" doesn't apply.
    return false;
  }
}

}  // namespace

namespace Exiv2 {
namespace Internal {

class CanonMakerNoteTagListFlTest_926 : public ::testing::Test {};

TEST_F(CanonMakerNoteTagListFlTest_926, IsCallableStatically_926) {
  // Verifies the function is callable without an instance and returns a value.
  auto v = CanonMakerNote::tagListFl();
  (void)v;
  SUCCEED();
}

TEST_F(CanonMakerNoteTagListFlTest_926, ReturnsStableObjectAcrossCalls_926) {
  // Observable behavior: repeated calls should refer to the same underlying object.
  // (We do not assume its contents or size.)
  const auto a = CanonMakerNote::tagListFl();
  const auto b = CanonMakerNote::tagListFl();

  EXPECT_EQ(stable_address(a), stable_address(b));
}

TEST_F(CanonMakerNoteTagListFlTest_926, ReturnIsNotNullIfPointer_926) {
  // Boundary-style check: if the API returns a pointer type, it should be non-null.
  // For non-pointer return types, this test simply succeeds.
  const auto v = CanonMakerNote::tagListFl();

  if constexpr (std::is_pointer_v<std::decay_t<decltype(v)>>) {
    EXPECT_FALSE(is_null_like(v));
  } else {
    SUCCEED();
  }
}

TEST_F(CanonMakerNoteTagListFlTest_926, ReturnTypeIsConsistent_926) {
  // Ensures the return type is consistent and can be named/used in generic contexts.
  using Ret = decltype(CanonMakerNote::tagListFl());
  Ret v1 = CanonMakerNote::tagListFl();
  Ret v2 = CanonMakerNote::tagListFl();
  EXPECT_EQ(stable_address(v1), stable_address(v2));
}

}  // namespace Internal
}  // namespace Exiv2