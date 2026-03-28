// TEST_ID: 396
#include <gtest/gtest.h>

#include <cstdint>
#include <type_traits>

#include "contrib/dragonbox.h"

namespace {

// The function lives inside duplicated namespaces in the provided header snippet.
namespace uut = ::YAML::jkj::dragonbox::jkj::dragonbox;

class ComputeRightEndpointForShorterIntervalCaseTest_396 : public ::testing::Test {};

template <class ShiftAmountType>
constexpr uut::carrier_uint CallComputeRightEndpoint_396(uut::cache_entry_type cache,
                                                        ShiftAmountType beta) {
  return uut::compute_right_endpoint_for_shorter_interval_case<ShiftAmountType>(cache, beta);
}

}  // namespace

TEST_F(ComputeRightEndpointForShorterIntervalCaseTest_396, IsNoexceptAndReturnsCarrierUint_396) {
  using BetaT = int;

  static_assert(noexcept(CallComputeRightEndpoint_396<BetaT>(
      static_cast<uut::cache_entry_type>(0), BetaT{0})));
  static_assert(std::is_same_v<
                decltype(CallComputeRightEndpoint_396<BetaT>(
                    static_cast<uut::cache_entry_type>(0), BetaT{0})),
                uut::carrier_uint>);

  // Also verify at runtime (should still compile even if static_asserts are removed).
  EXPECT_NO_THROW({
    (void)CallComputeRightEndpoint_396<BetaT>(static_cast<uut::cache_entry_type>(0), BetaT{0});
  });
}

TEST_F(ComputeRightEndpointForShorterIntervalCaseTest_396, ConstexprEvaluationMatchesRuntime_396) {
  using BetaT = std::uint32_t;

  constexpr uut::cache_entry_type kCache = static_cast<uut::cache_entry_type>(123456789u);
  constexpr BetaT kBeta = BetaT{0};

  // Compile-time evaluation.
  constexpr uut::carrier_uint kConstexprResult = CallComputeRightEndpoint_396<BetaT>(kCache, kBeta);

  // Runtime evaluation should match for the same inputs.
  const uut::carrier_uint runtime_result = CallComputeRightEndpoint_396<BetaT>(kCache, kBeta);
  EXPECT_EQ(runtime_result, kConstexprResult);
}

TEST_F(ComputeRightEndpointForShorterIntervalCaseTest_396, SupportsMultipleShiftAmountTypes_396) {
  const uut::cache_entry_type cache = static_cast<uut::cache_entry_type>(42);

  const auto r_int = CallComputeRightEndpoint_396<int>(cache, 0);
  const auto r_uint = CallComputeRightEndpoint_396<unsigned>(cache, 0u);
  const auto r_u32 = CallComputeRightEndpoint_396<std::uint32_t>(cache, std::uint32_t{0});

  // We don't assume any relationship between results beyond being well-formed calls.
  (void)r_int;
  (void)r_uint;
  (void)r_u32;

  SUCCEED();
}

TEST_F(ComputeRightEndpointForShorterIntervalCaseTest_396, BoundaryBetasAreCallable_396) {
  // Boundary-style tests: verify calls are well-formed at beta=0 and at a "shift-to-zero" style
  // boundary derived from public constants (no assumptions about internal math beyond availability
  // of these constants).
  const uut::cache_entry_type cache = static_cast<uut::cache_entry_type>(0xFFFFFFFFu);

  constexpr int kBetaZero = 0;

  // If these constants exist (as expected in dragonbox), using them avoids guessing values.
  // The expression is intentionally kept simple: it should be within the representable range of int.
  const int beta_shift_to_zero =
      static_cast<int>(uut::cache_bits - uut::significand_bits - 1);

  EXPECT_NO_THROW({
    (void)CallComputeRightEndpoint_396<int>(cache, kBetaZero);
    (void)CallComputeRightEndpoint_396<int>(cache, beta_shift_to_zero);
  });
}

TEST_F(ComputeRightEndpointForShorterIntervalCaseTest_396, DeterministicForSameInputs_396) {
  using BetaT = int;

  const uut::cache_entry_type cache = static_cast<uut::cache_entry_type>(987654321u);
  const BetaT beta = 1;

  const auto a = CallComputeRightEndpoint_396<BetaT>(cache, beta);
  const auto b = CallComputeRightEndpoint_396<BetaT>(cache, beta);
  const auto c = CallComputeRightEndpoint_396<BetaT>(cache, beta);

  EXPECT_EQ(a, b);
  EXPECT_EQ(b, c);
}