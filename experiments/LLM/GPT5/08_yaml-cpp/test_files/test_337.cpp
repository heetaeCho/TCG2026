// TEST_ID: 337
// File: ./TestProjects/yaml-cpp/test/dragonbox_trailing_zero_remove_test_337.cpp

#include <gtest/gtest.h>
#include <cstdint>
#include <limits>
#include <type_traits>

#include "contrib/dragonbox.h"

// These tests treat remove_t as a black box and only verify observable behavior:
// - Returned unsigned_decimal_fp contains the (possibly modified) significand/exponent
// - External interaction: remove_trailing_zeros_traits<...>::remove_trailing_zeros is invoked
//
// We do this by providing a *test-only* specialization of remove_trailing_zeros_traits for a
// test Format type, and recording/modifying the arguments.

namespace YAML { namespace jkj { namespace dragonbox { namespace policy { namespace trailing_zero {

namespace test_337 {

struct DummyFormat337 {};

// Simple recorder that our specialization uses.
struct Recorder337 {
  static inline int call_count = 0;

  // Store "before" values observed by the trait.
  static inline std::uint64_t last_sig_u64 = 0;
  static inline std::int32_t  last_exp_i32 = 0;

  static void Reset() {
    call_count = 0;
    last_sig_u64 = 0;
    last_exp_i32 = 0;
  }
};

}  // namespace test_337

// --- Test-only specialization of remove_trailing_zeros_traits ---
// The production code calls:
//   remove_trailing_zeros_traits<remove_t, Format, S, E>::remove_trailing_zeros(significand, exponent);
//
// We specialize for our DummyFormat337. We intentionally take arguments by non-const ref so we can
// demonstrate that any changes here are observable in the returned unsigned_decimal_fp.
template <class DecimalSignificand, class DecimalExponentType>
struct remove_trailing_zeros_traits<remove_t, test_337::DummyFormat337, DecimalSignificand, DecimalExponentType> {
  static void remove_trailing_zeros(DecimalSignificand& significand, DecimalExponentType& exponent) noexcept {
    ++test_337::Recorder337::call_count;

    // Record "before" (best-effort; only record when types are compatible with our storage)
    if constexpr (std::is_integral_v<DecimalSignificand> && sizeof(DecimalSignificand) <= sizeof(std::uint64_t)) {
      test_337::Recorder337::last_sig_u64 = static_cast<std::uint64_t>(significand);
    }
    if constexpr (std::is_integral_v<DecimalExponentType> && sizeof(DecimalExponentType) <= sizeof(std::int32_t)) {
      test_337::Recorder337::last_exp_i32 = static_cast<std::int32_t>(exponent);
    }

    // Mutate to sentinel values so the caller's observable return changes if passed by reference.
    // (We are NOT asserting any real "trailing zero removal" logic—only that the external hook
    // is called and its effects are observable through the public return value.)
    significand = static_cast<DecimalSignificand>(12345);
    exponent    = static_cast<DecimalExponentType>(-7);
  }
};

}}}}} // namespace YAML::jkj::dragonbox::policy::trailing_zero

namespace YAML { namespace jkj { namespace dragonbox { namespace policy { namespace trailing_zero {

class TrailingZeroRemoveTest_337 : public ::testing::Test {
protected:
  void SetUp() override {
    test_337::Recorder337::Reset();
  }
};

TEST_F(TrailingZeroRemoveTest_337, NoTrailingZerosReturnsInputUnchanged_337) {
  using S = std::uint64_t;
  using E = std::int32_t;

  const S sig = 900;
  const E exp = 12;

  const auto out = remove_t::no_trailing_zeros<test_337::DummyFormat337>(sig, exp);

  // Observable behavior: returned fp contains the inputs.
  EXPECT_EQ(out.significand, sig);
  EXPECT_EQ(out.exponent, exp);

  // External interaction: no_trailing_zeros should not need to call the trait hook.
  EXPECT_EQ(test_337::Recorder337::call_count, 0);
}

TEST_F(TrailingZeroRemoveTest_337, OnTrailingZerosInvokesTraitOnce_337) {
  using S = std::uint64_t;
  using E = std::int32_t;

  const S sig = 1000;
  const E exp = 5;

  (void)remove_t::on_trailing_zeros<test_337::DummyFormat337>(sig, exp);

  EXPECT_EQ(test_337::Recorder337::call_count, 1);
  EXPECT_EQ(test_337::Recorder337::last_sig_u64, sig);
  EXPECT_EQ(test_337::Recorder337::last_exp_i32, exp);
}

TEST_F(TrailingZeroRemoveTest_337, OnTrailingZerosReturnsValuesAfterTraitMutation_337) {
  using S = std::uint64_t;
  using E = std::int32_t;

  const auto out = remove_t::on_trailing_zeros<test_337::DummyFormat337>(S{777}, E{3});

  // Because our test specialization mutates the args, the returned value should reflect that.
  EXPECT_EQ(out.significand, static_cast<S>(12345));
  EXPECT_EQ(out.exponent, static_cast<E>(-7));
  EXPECT_EQ(test_337::Recorder337::call_count, 1);
}

TEST_F(TrailingZeroRemoveTest_337, OnTrailingZerosHandlesBoundaryValues_337) {
  using S = std::uint64_t;
  using E = std::int32_t;

  const S sig = std::numeric_limits<S>::max();
  const E exp = std::numeric_limits<E>::min();

  const auto out = remove_t::on_trailing_zeros<test_337::DummyFormat337>(sig, exp);

  // Still must invoke the external hook and return whatever it produces.
  EXPECT_EQ(test_337::Recorder337::call_count, 1);
  EXPECT_EQ(test_337::Recorder337::last_sig_u64, sig);
  EXPECT_EQ(test_337::Recorder337::last_exp_i32, exp);
  EXPECT_EQ(out.significand, static_cast<S>(12345));
  EXPECT_EQ(out.exponent, static_cast<E>(-7));
}

TEST_F(TrailingZeroRemoveTest_337, OnTrailingZerosIsNoexcept_337) {
  using S = std::uint64_t;
  using E = std::int32_t;

  static_assert(noexcept(remove_t::on_trailing_zeros<test_337::DummyFormat337>(S{1}, E{1})),
                "remove_t::on_trailing_zeros must be noexcept per interface");
}

}}}}} // namespace YAML::jkj::dragonbox::policy::trailing_zero