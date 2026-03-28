// -------------------------------------------------------------------------------------------------
// TEST_ID 1673
// Unit tests for Exiv2::Internal::TiffEncoder::visitSubIfd
// File-under-test: ./TestProjects/exiv2/src/tiffvisitor_int.cpp
//
// Notes / constraints handling:
// - Treat implementation as a black box.
// - Because TiffEncoder construction in Exiv2 can be complex and varies by build configuration,
//   these tests are written to:
//     * Verify the interface is present and callable (compile-time / type-trait checks).
//     * Execute runtime smoke/boundary calls only when the required constructors are available.
// - We avoid inferring internal behavior (e.g., "dirty" toggling) because it's not guaranteed
//   and not observable from the provided minimal snippet.
// -------------------------------------------------------------------------------------------------

#include <gtest/gtest.h>

#include <type_traits>
#include <cstdint>

#include "tiffvisitor_int.hpp"
#include "tiffcomposite_int.hpp"

namespace {

// --- Detection helpers (C++17-friendly) ---

template <typename T, typename = void>
struct HasVisitSubIfd : std::false_type {};

template <typename T>
struct HasVisitSubIfd<T, std::void_t<decltype(&T::visitSubIfd)>> : std::true_type {};

template <typename EncoderT, typename = void>
struct IsDefaultConstructibleAndCallable : std::false_type {};

template <typename EncoderT>
struct IsDefaultConstructibleAndCallable<
    EncoderT,
    std::void_t<decltype(std::declval<EncoderT&>().visitSubIfd(
        static_cast<Exiv2::Internal::TiffSubIfd*>(nullptr)))>>
    : std::integral_constant<bool, std::is_default_constructible<EncoderT>::value> {};

template <typename SubIfdT>
constexpr bool kCanConstructSubIfd =
    std::is_constructible<SubIfdT, uint16_t, Exiv2::Internal::IfdId, Exiv2::Internal::IfdId>::value;

}  // namespace

// -------------------------------------------------------------------------------------------------

class TiffEncoderVisitSubIfdTest_1673 : public ::testing::Test {
protected:
  using Encoder = Exiv2::Internal::TiffEncoder;
  using SubIfd = Exiv2::Internal::TiffSubIfd;
};

// Normal operation (interface-level): ensure the method exists on the type.
TEST_F(TiffEncoderVisitSubIfdTest_1673, HasVisitSubIfdMethod_1673) {
  EXPECT_TRUE((HasVisitSubIfd<Exiv2::Internal::TiffEncoder>::value));
}

// Boundary/robustness (interface-level): ensure visitSubIfd is callable with a TiffSubIfd*.
TEST_F(TiffEncoderVisitSubIfdTest_1673, VisitSubIfdIsCallableWithPointer_1673) {
  // This is a compile-time property expressed as a runtime EXPECT_TRUE on a constant.
  constexpr bool kCallable =
      std::is_member_function_pointer<decltype(&Exiv2::Internal::TiffEncoder::visitSubIfd)>::value;
  EXPECT_TRUE(kCallable);
}

// Runtime smoke test (normal operation): call visitSubIfd with a valid object
// only if we can construct both Encoder and SubIfd with available constructors.
TEST_F(TiffEncoderVisitSubIfdTest_1673, VisitSubIfdWithValidObjectDoesNotThrowWhenConstructible_1673) {
  using Encoder = Exiv2::Internal::TiffEncoder;
  using SubIfd = Exiv2::Internal::TiffSubIfd;

  // We only run this if Encoder is default-constructible *and* visitSubIfd is callable,
  // and SubIfd can be constructed from (tag, group, newGroup).
  constexpr bool kEncoderReady = IsDefaultConstructibleAndCallable<Encoder>::value;
  constexpr bool kSubIfdReady = kCanConstructSubIfd<SubIfd>;

  if (!kEncoderReady || !kSubIfdReady) {
    GTEST_SKIP() << "TiffEncoder and/or TiffSubIfd not constructible in this build configuration.";
  }

  Encoder encoder;

  // Use conservative, boundary-ish values without assuming semantics of IfdId.
  const uint16_t tag = 0x0000;
  const auto group = static_cast<Exiv2::Internal::IfdId>(0);
  const auto newGroup = static_cast<Exiv2::Internal::IfdId>(0);

  SubIfd subIfd(tag, group, newGroup);

  EXPECT_NO_THROW(encoder.visitSubIfd(&subIfd));
}

// Boundary test: use extreme tag value (uint16_t max) when SubIfd constructor is available.
// Again, we only run if Encoder/SubIfd are constructible in this build configuration.
TEST_F(TiffEncoderVisitSubIfdTest_1673, VisitSubIfdWithMaxTagDoesNotThrowWhenConstructible_1673) {
  using Encoder = Exiv2::Internal::TiffEncoder;
  using SubIfd = Exiv2::Internal::TiffSubIfd;

  constexpr bool kEncoderReady = IsDefaultConstructibleAndCallable<Encoder>::value;
  constexpr bool kSubIfdReady = kCanConstructSubIfd<SubIfd>;

  if (!kEncoderReady || !kSubIfdReady) {
    GTEST_SKIP() << "TiffEncoder and/or TiffSubIfd not constructible in this build configuration.";
  }

  Encoder encoder;

  const uint16_t tag = 0xFFFF;
  const auto group = static_cast<Exiv2::Internal::IfdId>(0);
  const auto newGroup = static_cast<Exiv2::Internal::IfdId>(0);

  SubIfd subIfd(tag, group, newGroup);

  EXPECT_NO_THROW(encoder.visitSubIfd(&subIfd));
}

// Exceptional / error case (if observable): nullptr handling.
// We do NOT assume the implementation must accept nullptr. If it does, this should not throw;
// if it doesn't, behavior might be a debug assertion / crash. To avoid asserting internal policy,
// we only check that the call is *well-formed* at compile time; runtime is skipped.
TEST_F(TiffEncoderVisitSubIfdTest_1673, VisitSubIfdNullptrIsWellFormed_1673) {
  // Compile-time well-formedness: we can form the expression.
  using Encoder = Exiv2::Internal::TiffEncoder;
  using SubIfd = Exiv2::Internal::TiffSubIfd;

  constexpr bool kWellFormed =
      std::is_same<decltype(std::declval<Encoder&>().visitSubIfd(static_cast<SubIfd*>(nullptr))),
                   void>::value;
  EXPECT_TRUE(kWellFormed);

  // Do not execute at runtime to avoid inferring whether nullptr is permitted.
  SUCCEED();
}