// TEST_ID: 299
#include <gtest/gtest.h>

#include <limits>
#include <type_traits>
#include <utility>

#include "contrib/dragonbox.h"

namespace {

template <class Traits>
using FloatBits = YAML::jkj::dragonbox::float_bits<Traits>;

template <class Traits>
constexpr typename Traits::carrier_uint MaxCarrier() {
  return (std::numeric_limits<typename Traits::carrier_uint>::max)();
}

template <class Traits>
void RunIsFiniteConsistencyChecks() {
  using FB = FloatBits<Traits>;
  using carrier_uint = typename Traits::carrier_uint;

  static_assert(noexcept(std::declval<const FB&>().is_finite()),
                "is_finite() must be noexcept");

  // A small set of representative patterns (including boundary-ish values for the carrier type).
  const carrier_uint patterns[] = {
      carrier_uint{0},
      carrier_uint{1},
      carrier_uint{2},
      carrier_uint{3},
      MaxCarrier<Traits>(),
      carrier_uint{MaxCarrier<Traits>() - carrier_uint{1}},
      // Sign-bit-ish probe (for unsigned carrier_uint, shift is well-defined if within width).
      carrier_uint{carrier_uint{1} << (std::numeric_limits<carrier_uint>::digits - 1)},
  };

  for (carrier_uint p : patterns) {
    const FB fb(p);

    // No exceptions should ever be thrown (interface says noexcept).
    EXPECT_NO_THROW((void)fb.is_finite());

    // Core observable behavior: is_finite() must match the format_traits decision
    // applied to the exponent bits exposed by the public interface.
    const auto exp_bits = fb.extract_exponent_bits();

    EXPECT_EQ(fb.is_finite(), Traits::is_finite(exp_bits));
    EXPECT_EQ(fb.is_finite(), fb.is_finite(exp_bits));

    // Calling repeatedly should be stable/consistent.
    const bool v1 = fb.is_finite();
    const bool v2 = fb.is_finite();
    EXPECT_EQ(v1, v2);
  }

  // Also ensure constexpr evaluation works for a simple value (if supported by the library).
  {
    constexpr FB z(carrier_uint{0});
    constexpr bool finite = z.is_finite();
    (void)finite;
  }
}

}  // namespace

TEST(FloatBitsIsFiniteTest_299, Binary32_IsFiniteMatchesTraitsAndOverload_299) {
  RunIsFiniteConsistencyChecks<YAML::jkj::dragonbox::ieee754_binary32>();
}

TEST(FloatBitsIsFiniteTest_299, Binary64_IsFiniteMatchesTraitsAndOverload_299) {
  RunIsFiniteConsistencyChecks<YAML::jkj::dragonbox::ieee754_binary64>();
}