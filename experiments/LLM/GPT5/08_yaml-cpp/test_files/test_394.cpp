// TEST_ID: 394
#include <gtest/gtest.h>

#include <type_traits>
#include <utility>

#include "TestProjects/yaml-cpp/src/contrib/dragonbox.h"

namespace {

// The function under test lives in:
// YAML::jkj::dragonbox::jkj::dragonbox::compute_mul_parity(...)
namespace uut = YAML::jkj::dragonbox::jkj::dragonbox;

class ComputeMulParityTest_394 : public ::testing::Test {};

TEST_F(ComputeMulParityTest_394, IsNoexcept_394) {
  // Verify the interface contract (noexcept) without constructing any values.
  static_assert(
      noexcept(uut::compute_mul_parity(std::declval<uut::carrier_uint>(),
                                       std::declval<uut::cache_entry_type const&>(),
                                       std::declval<int>())),
      "compute_mul_parity must be noexcept");
}

TEST_F(ComputeMulParityTest_394, ReturnTypeIsComputeMulParityResult_394) {
  using Ret = decltype(uut::compute_mul_parity(std::declval<uut::carrier_uint>(),
                                              std::declval<uut::cache_entry_type const&>(),
                                              std::declval<int>()));
  static_assert(std::is_same_v<Ret, uut::compute_mul_parity_result>,
                "compute_mul_parity must return compute_mul_parity_result");
}

TEST_F(ComputeMulParityTest_394, AcceptsDifferentShiftAmountTypes_394) {
  uut::carrier_uint two_f{};
  uut::cache_entry_type cache{};

  // ShiftAmountType = int
  {
    auto res = uut::compute_mul_parity(two_f, cache, int{1});
    auto [b0, b1] = res;
    (void)b0;
    (void)b1;
    static_assert(std::is_same_v<decltype(b0), bool>);
    static_assert(std::is_same_v<decltype(b1), bool>);
  }

  // ShiftAmountType = unsigned
  {
    auto res = uut::compute_mul_parity(two_f, cache, unsigned{1});
    auto [b0, b1] = res;
    (void)b0;
    (void)b1;
  }

  // ShiftAmountType = std::uint8_t (small integer type)
  {
    auto res = uut::compute_mul_parity(two_f, cache, static_cast<std::uint8_t>(1));
    auto [b0, b1] = res;
    (void)b0;
    (void)b1;
  }
}

TEST_F(ComputeMulParityTest_394, BoundaryBetaValuesDoNotCrash_394) {
  uut::carrier_uint two_f{};
  uut::cache_entry_type cache{};

  // The implementation asserts: 1 <= beta <= 32.
  // Boundary calls should be valid.
  {
    auto res = uut::compute_mul_parity(two_f, cache, int{1});
    auto [b0, b1] = res;
    (void)b0;
    (void)b1;
  }
  {
    auto res = uut::compute_mul_parity(two_f, cache, int{32});
    auto [b0, b1] = res;
    (void)b0;
    (void)b1;
  }
}

#ifndef NDEBUG
TEST_F(ComputeMulParityTest_394, InvalidBetaDiesWithAssert_394) {
  uut::carrier_uint two_f{};
  uut::cache_entry_type cache{};

  // The implementation uses assert(beta >= 1) and assert(beta <= 32).
  EXPECT_DEATH({ (void)uut::compute_mul_parity(two_f, cache, int{0}); }, ".*");
  EXPECT_DEATH({ (void)uut::compute_mul_parity(two_f, cache, int{33}); }, ".*");
}
#endif

TEST_F(ComputeMulParityTest_394, RepeatedCallsAreStableForSameInputs_394) {
  uut::carrier_uint two_f{};
  uut::cache_entry_type cache{};

  const int beta = 7;

  auto r1 = uut::compute_mul_parity(two_f, cache, beta);
  auto r2 = uut::compute_mul_parity(two_f, cache, beta);

  auto [p1, z1] = r1;
  auto [p2, z2] = r2;

  // Determinism for identical inputs is an observable contract for a pure function.
  EXPECT_EQ(p1, p2);
  EXPECT_EQ(z1, z2);
}

}  // namespace