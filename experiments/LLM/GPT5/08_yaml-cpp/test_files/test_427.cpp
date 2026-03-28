// File: test/dragonbox_to_decimal_dispatcher_test_427.cpp

#include <gtest/gtest.h>

#include <cstdint>
#include <type_traits>

// The project includes dragonbox as src/contrib/dragonbox.h (per prompt).
// Most yaml-cpp builds also add src/ to include paths, so this form is typically valid.
#include "contrib/dragonbox.h"

namespace {

// A minimal FormatTraits type for exercising the dispatcher.
// signed_significand_bits<FormatTraits> requires FormatTraits::carrier_uint.
// The dispatcher signature requires FormatTraits::exponent_int.
struct TestFormatTraits_427 {
  using carrier_uint = std::uint32_t;
  using exponent_int = int;
};

// A minimal PolicyHolder that provides the nested policy type aliases used by to_decimal_dispatcher.
struct TestPolicyHolder_427 {
  struct sign_policy {};
  struct trailing_zero_policy {};
  struct binary_to_decimal_rounding_policy {};
  struct cache_policy {};
  struct preferred_integer_types_policy {};
};

// Interval type providers: the dispatcher branches only on IntervalTypeProvider::tag.
struct IntervalNearest_427 {
  static constexpr auto tag =
      YAML::jkj::dragonbox::policy::decimal_to_binary_rounding::tag_t::to_nearest;
};
struct IntervalLeftClosedDirected_427 {
  static constexpr auto tag = YAML::jkj::dragonbox::policy::decimal_to_binary_rounding::tag_t::
      left_closed_directed;
};
struct IntervalRightClosedDirected_427 {
  static constexpr auto tag = YAML::jkj::dragonbox::policy::decimal_to_binary_rounding::tag_t::
      right_closed_directed;
};

}  // namespace

// We specialize detail::impl for our TestFormatTraits_427 so the dispatcher’s choice is observable.
// This does NOT re-implement production logic: it only provides a test seam for a synthetic
// FormatTraits type (not used by the real codebase).
namespace YAML {
namespace jkj {
namespace dragonbox {
namespace detail {

template <>
struct impl<::TestFormatTraits_427> {
  template <class /*sign_policy*/, class /*trailing_zero_policy*/, class /*preferred_integer_types*/>
  using return_type = int;

  template <class /*sign_policy*/, class /*trailing_zero_policy*/, class /*IntervalTypeProvider*/,
            class /*binary_to_decimal_rounding_policy*/, class /*cache_policy*/,
            class /*preferred_integer_types_policy*/>
  static constexpr int compute_nearest(
      ::YAML::jkj::dragonbox::signed_significand_bits<::TestFormatTraits_427> /*s*/,
      typename ::TestFormatTraits_427::exponent_int /*exponent_bits*/) noexcept {
    return 11;
  }

  template <class /*sign_policy*/, class /*trailing_zero_policy*/, class /*cache_policy*/,
            class /*preferred_integer_types_policy*/>
  static constexpr int compute_left_closed_directed(
      ::YAML::jkj::dragonbox::signed_significand_bits<::TestFormatTraits_427> /*s*/,
      typename ::TestFormatTraits_427::exponent_int /*exponent_bits*/) noexcept {
    return 22;
  }

  template <class /*sign_policy*/, class /*trailing_zero_policy*/, class /*cache_policy*/,
            class /*preferred_integer_types_policy*/>
  static constexpr int compute_right_closed_directed(
      ::YAML::jkj::dragonbox::signed_significand_bits<::TestFormatTraits_427> /*s*/,
      typename ::TestFormatTraits_427::exponent_int /*exponent_bits*/) noexcept {
    return 33;
  }
};

}  // namespace detail
}  // namespace dragonbox
}  // namespace jkj
}  // namespace YAML

class ToDecimalDispatcherTest_427 : public ::testing::Test {
 protected:
  using Dispatcher =
      YAML::jkj::dragonbox::detail::to_decimal_dispatcher<TestFormatTraits_427, TestPolicyHolder_427>;
  using SigBits = YAML::jkj::dragonbox::signed_significand_bits<TestFormatTraits_427>;
};

TEST_F(ToDecimalDispatcherTest_427, ReturnTypeAliasIsFromImpl_427) {
  using Dispatcher = ToDecimalDispatcherTest_427::Dispatcher;
  using Expected = int;
  static_assert(std::is_same_v<typename Dispatcher::return_type, Expected>,
                "Dispatcher::return_type should match impl<FormatTraits>::return_type<...>.");

  SUCCEED();
}

TEST_F(ToDecimalDispatcherTest_427, DispatchesToNearestWhenTagToNearest_427) {
  Dispatcher dispatcher{};
  const SigBits s{/*bit_pattern=*/0u};

  const auto out = dispatcher(IntervalNearest_427{}, s, /*exponent_bits=*/0);
  EXPECT_EQ(out, 11);
}

TEST_F(ToDecimalDispatcherTest_427, DispatchesToLeftClosedDirectedWhenTagLeftClosedDirected_427) {
  Dispatcher dispatcher{};
  const SigBits s{/*bit_pattern=*/0u};

  const auto out = dispatcher(IntervalLeftClosedDirected_427{}, s, /*exponent_bits=*/0);
  EXPECT_EQ(out, 22);
}

TEST_F(ToDecimalDispatcherTest_427, DispatchesToRightClosedDirectedWhenTagRightClosedDirected_427) {
  Dispatcher dispatcher{};
  const SigBits s{/*bit_pattern=*/0u};

  const auto out = dispatcher(IntervalRightClosedDirected_427{}, s, /*exponent_bits=*/0);
  EXPECT_EQ(out, 33);
}

TEST_F(ToDecimalDispatcherTest_427, NoexceptForAllSupportedTags_427) {
  Dispatcher dispatcher{};
  const SigBits s{/*bit_pattern=*/0u};

  static_assert(noexcept(dispatcher(IntervalNearest_427{}, s, 0)));
  static_assert(noexcept(dispatcher(IntervalLeftClosedDirected_427{}, s, 0)));
  static_assert(noexcept(dispatcher(IntervalRightClosedDirected_427{}, s, 0)));

  // Also verify at runtime (in case noexcept is macro-conditional somewhere).
  EXPECT_NO_THROW((void)dispatcher(IntervalNearest_427{}, s, 0));
  EXPECT_NO_THROW((void)dispatcher(IntervalLeftClosedDirected_427{}, s, 0));
  EXPECT_NO_THROW((void)dispatcher(IntervalRightClosedDirected_427{}, s, 0));
}

TEST_F(ToDecimalDispatcherTest_427, WorksWithBoundaryValuesForInputs_427) {
  Dispatcher dispatcher{};

  // Boundary-ish bit patterns for carrier_uint.
  const SigBits s0{0u};
  const SigBits smax{static_cast<TestFormatTraits_427::carrier_uint>(~0u)};

  // Boundary-ish exponent values for exponent_int.
  const TestFormatTraits_427::exponent_int emin = std::numeric_limits<int>::min();
  const TestFormatTraits_427::exponent_int emax = std::numeric_limits<int>::max();

  // Dispatcher choice should depend only on the tag; values are forwarded.
  EXPECT_EQ(dispatcher(IntervalNearest_427{}, s0, emin), 11);
  EXPECT_EQ(dispatcher(IntervalNearest_427{}, smax, emax), 11);

  EXPECT_EQ(dispatcher(IntervalLeftClosedDirected_427{}, s0, emin), 22);
  EXPECT_EQ(dispatcher(IntervalLeftClosedDirected_427{}, smax, emax), 22);

  EXPECT_EQ(dispatcher(IntervalRightClosedDirected_427{}, s0, emin), 33);
  EXPECT_EQ(dispatcher(IntervalRightClosedDirected_427{}, smax, emax), 33);
}