// =================================================================================================
// TEST_ID: 1527
// File: ./TestProjects/exiv2/src/makernote_int.cpp
// Interface under test:
//   Exiv2::Internal::newSamsungMn2(uint16_t tag, IfdId group, IfdId mnGroup)
//
// Constraints:
// - Treat implementation as black box: verify only observable behavior via public interface.
// - No access to private state.
// - Use gtest (and gmock only if needed).
// =================================================================================================

#include <gtest/gtest.h>

#include <cstdint>
#include <memory>
#include <type_traits>

#include "makernote_int.hpp"  // Provides Exiv2::Internal::newSamsungMn2
#include "tiffcomposite_int.hpp"  // Typically provides TiffIfdMakernote (and related types)
#include "types.hpp"  // Typically provides IfdId (location may vary in Exiv2 tree)

namespace {

// A helper that compiles only if T is complete.
template <typename T>
constexpr bool IsCompleteType() {
  return sizeof(T) > 0;
}

}  // namespace

namespace Exiv2 {
namespace Internal {

class NewSamsungMn2Test_1527 : public ::testing::Test {};

// Normal operation: returns a non-null unique_ptr.
TEST_F(NewSamsungMn2Test_1527, ReturnsNonNullUniquePtr_1527) {
  // Use representative values. We intentionally do not assume any semantic meaning.
  const uint16_t tag = 0x0001;
  const IfdId group = static_cast<IfdId>(0);
  const IfdId mnGroup = static_cast<IfdId>(0);

  auto mn = newSamsungMn2(tag, group, mnGroup);

  ASSERT_NE(mn, nullptr);
}

// Normal operation: pointer owns a complete type and can be destroyed safely.
// (This is an observable property: the returned unique_ptr is well-formed and deletable.)
TEST_F(NewSamsungMn2Test_1527, ReturnedPointerIsDeletable_1527) {
  const uint16_t tag = 0x1234;
  const IfdId group = static_cast<IfdId>(1);
  const IfdId mnGroup = static_cast<IfdId>(2);

  static_assert(IsCompleteType<TiffIfdMakernote>(),
                "TiffIfdMakernote must be a complete type in this TU to delete via unique_ptr.");

  auto mn = newSamsungMn2(tag, group, mnGroup);
  ASSERT_NE(mn, nullptr);

  // Destruction at end of scope is the test: should not crash / throw.
}

// Boundary: minimum tag value.
TEST_F(NewSamsungMn2Test_1527, HandlesMinTagValue_1527) {
  const uint16_t tag = std::numeric_limits<uint16_t>::min();
  const IfdId group = static_cast<IfdId>(0);
  const IfdId mnGroup = static_cast<IfdId>(0);

  auto mn = newSamsungMn2(tag, group, mnGroup);
  ASSERT_NE(mn, nullptr);
}

// Boundary: maximum tag value.
TEST_F(NewSamsungMn2Test_1527, HandlesMaxTagValue_1527) {
  const uint16_t tag = std::numeric_limits<uint16_t>::max();
  const IfdId group = static_cast<IfdId>(0);
  const IfdId mnGroup = static_cast<IfdId>(0);

  auto mn = newSamsungMn2(tag, group, mnGroup);
  ASSERT_NE(mn, nullptr);
}

// Boundary: exercise a few different group/mnGroup values without assuming enum domain.
// This stays within "observable behavior": construction returns a non-null object.
TEST_F(NewSamsungMn2Test_1527, HandlesVariousGroupValues_1527) {
  const uint16_t tag = 0x00FF;

  const IfdId groups[] = {
      static_cast<IfdId>(0),
      static_cast<IfdId>(1),
      static_cast<IfdId>(-1),  // if underlying type permits; still just a value
      static_cast<IfdId>(42),
  };

  for (const auto g : groups) {
    for (const auto mg : groups) {
      auto mn = newSamsungMn2(tag, g, mg);
      ASSERT_NE(mn, nullptr) << "Expected non-null for group=" << static_cast<long long>(g)
                             << " mnGroup=" << static_cast<long long>(mg);
    }
  }
}

// Normal operation: each call returns a distinct object (unique ownership).
TEST_F(NewSamsungMn2Test_1527, EachCallReturnsDistinctObject_1527) {
  const uint16_t tag = 0x0A0B;
  const IfdId group = static_cast<IfdId>(3);
  const IfdId mnGroup = static_cast<IfdId>(4);

  auto a = newSamsungMn2(tag, group, mnGroup);
  auto b = newSamsungMn2(tag, group, mnGroup);

  ASSERT_NE(a, nullptr);
  ASSERT_NE(b, nullptr);
  EXPECT_NE(a.get(), b.get());
}

// Exceptional / error cases (observable):
// This factory allocates; the only generally observable failure is allocation failure.
// We avoid trying to force std::bad_alloc (non-deterministic, environment-dependent).
// Instead, we at least document via a compile-time check that the function is callable
// and returns the expected type.
TEST_F(NewSamsungMn2Test_1527, HasExpectedReturnType_1527) {
  using Ret = decltype(newSamsungMn2(std::declval<uint16_t>(), std::declval<IfdId>(),
                                    std::declval<IfdId>()));
  static_assert(std::is_same<Ret, std::unique_ptr<TiffIfdMakernote>>::value,
                "newSamsungMn2 must return std::unique_ptr<TiffIfdMakernote>");
}

}  // namespace Internal
}  // namespace Exiv2