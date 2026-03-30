// File: ./TestProjects/yaml-cpp/test/dragonbox_nearest_to_odd_static_boundary_test_378.cpp

#include <gtest/gtest.h>

#include <limits>
#include <type_traits>

#include "contrib/dragonbox.h"

namespace {

using Policy =
    YAML::jkj::dragonbox::policy::decimal_to_binary_rounding::nearest_to_odd_static_boundary_t;
using OpenTag = YAML::jkj::dragonbox::detail::nearest_always_open_t;
using ClosedTag = YAML::jkj::dragonbox::detail::nearest_always_closed_t;

struct FakeSignedBitsEven {
  constexpr bool has_even_significand_bits() const noexcept { return true; }
};

struct FakeSignedBitsOdd {
  constexpr bool has_even_significand_bits() const noexcept { return false; }
};

struct CallRecorder {
  int open_calls = 0;
  int closed_calls = 0;
  long long last_sum = 0;
};

struct Func2Args {
  CallRecorder* rec = nullptr;

  // Must be default-constructible because delegate's return type uses Func{} in decltype.
  constexpr Func2Args() = default;
  constexpr explicit Func2Args(CallRecorder* r) : rec(r) {}

  constexpr long long operator()(OpenTag, int a, int b) const noexcept {
    if (rec) {
      ++rec->open_calls;
      rec->last_sum = static_cast<long long>(a) + static_cast<long long>(b);
    }
    return 1000LL + static_cast<long long>(a) + static_cast<long long>(b);
  }

  constexpr long long operator()(ClosedTag, int a, int b) const noexcept {
    if (rec) {
      ++rec->closed_calls;
      rec->last_sum = static_cast<long long>(a) + static_cast<long long>(b);
    }
    return 2000LL + static_cast<long long>(a) + static_cast<long long>(b);
  }
};

struct Func3Args {
  CallRecorder* rec = nullptr;

  constexpr Func3Args() = default;
  constexpr explicit Func3Args(CallRecorder* r) : rec(r) {}

  constexpr long long operator()(OpenTag, int a, int b, int c) const noexcept {
    if (rec) {
      ++rec->open_calls;
      rec->last_sum =
          static_cast<long long>(a) + static_cast<long long>(b) + static_cast<long long>(c);
    }
    return 3000LL + static_cast<long long>(a) + static_cast<long long>(b) + static_cast<long long>(c);
  }

  constexpr long long operator()(ClosedTag, int a, int b, int c) const noexcept {
    if (rec) {
      ++rec->closed_calls;
      rec->last_sum =
          static_cast<long long>(a) + static_cast<long long>(b) + static_cast<long long>(c);
    }
    return 4000LL + static_cast<long long>(a) + static_cast<long long>(b) + static_cast<long long>(c);
  }
};

class NearestToOddStaticBoundaryTest_378 : public ::testing::Test {};

TEST_F(NearestToOddStaticBoundaryTest_378, EvenSignificandBitsCallsNearestAlwaysOpen_378) {
  CallRecorder rec{};
  const auto ret = Policy::delegate(FakeSignedBitsEven{}, Func2Args{&rec}, 3, 4);

  EXPECT_EQ(ret, 1000LL + 3 + 4);
  EXPECT_EQ(rec.open_calls, 1);
  EXPECT_EQ(rec.closed_calls, 0);
  EXPECT_EQ(rec.last_sum, 7);
}

TEST_F(NearestToOddStaticBoundaryTest_378, OddSignificandBitsCallsNearestAlwaysClosed_378) {
  CallRecorder rec{};
  const auto ret = Policy::delegate(FakeSignedBitsOdd{}, Func2Args{&rec}, 3, 4);

  EXPECT_EQ(ret, 2000LL + 3 + 4);
  EXPECT_EQ(rec.open_calls, 0);
  EXPECT_EQ(rec.closed_calls, 1);
  EXPECT_EQ(rec.last_sum, 7);
}

TEST_F(NearestToOddStaticBoundaryTest_378, ForwardsArgumentValuesIncludingNegatives_378) {
  CallRecorder rec{};
  const int a = -10;
  const int b = 7;

  const auto ret_even = Policy::delegate(FakeSignedBitsEven{}, Func2Args{&rec}, a, b);
  EXPECT_EQ(ret_even, 1000LL + a + b);
  EXPECT_EQ(rec.open_calls, 1);
  EXPECT_EQ(rec.closed_calls, 0);
  EXPECT_EQ(rec.last_sum, static_cast<long long>(a) + b);

  const auto ret_odd = Policy::delegate(FakeSignedBitsOdd{}, Func2Args{&rec}, a, b);
  EXPECT_EQ(ret_odd, 2000LL + a + b);
  EXPECT_EQ(rec.open_calls, 1);
  EXPECT_EQ(rec.closed_calls, 1);
  EXPECT_EQ(rec.last_sum, static_cast<long long>(a) + b);
}

TEST_F(NearestToOddStaticBoundaryTest_378, SupportsVariadicArgs_378) {
  CallRecorder rec{};

  const auto ret_even = Policy::delegate(FakeSignedBitsEven{}, Func3Args{&rec}, 1, 2, 3);
  EXPECT_EQ(ret_even, 3000LL + 1 + 2 + 3);
  EXPECT_EQ(rec.open_calls, 1);
  EXPECT_EQ(rec.closed_calls, 0);
  EXPECT_EQ(rec.last_sum, 6);

  const auto ret_odd = Policy::delegate(FakeSignedBitsOdd{}, Func3Args{&rec}, 1, 2, 3);
  EXPECT_EQ(ret_odd, 4000LL + 1 + 2 + 3);
  EXPECT_EQ(rec.open_calls, 1);
  EXPECT_EQ(rec.closed_calls, 1);
  EXPECT_EQ(rec.last_sum, 6);
}

TEST_F(NearestToOddStaticBoundaryTest_378, NoexceptIsObservable_378) {
  static_assert(noexcept(Policy::delegate(FakeSignedBitsEven{}, Func2Args{}, 0, 0)),
                "delegate should be noexcept for this test configuration");
  static_assert(noexcept(Policy::delegate(FakeSignedBitsOdd{}, Func2Args{}, 0, 0)),
                "delegate should be noexcept for this test configuration");
}

TEST_F(NearestToOddStaticBoundaryTest_378, CanBeEvaluatedInConstantExpression_378) {
  // Recorder is null so the functor remains constexpr-friendly.
  constexpr long long even_ret = Policy::delegate(FakeSignedBitsEven{}, Func2Args{}, 1, 2);
  constexpr long long odd_ret = Policy::delegate(FakeSignedBitsOdd{}, Func2Args{}, 1, 2);

  static_assert(even_ret == 1000LL + 1 + 2, "constexpr even path result mismatch");
  static_assert(odd_ret == 2000LL + 1 + 2, "constexpr odd path result mismatch");

  EXPECT_EQ(even_ret, 1003LL);
  EXPECT_EQ(odd_ret, 2003LL);
}

TEST_F(NearestToOddStaticBoundaryTest_378, HandlesIntBoundaryValues_378) {
  CallRecorder rec{};
  const int a = std::numeric_limits<int>::min();
  const int b = std::numeric_limits<int>::max();

  const auto ret_even = Policy::delegate(FakeSignedBitsEven{}, Func2Args{&rec}, a, b);
  EXPECT_EQ(ret_even, 1000LL + static_cast<long long>(a) + static_cast<long long>(b));
  EXPECT_EQ(rec.open_calls, 1);
  EXPECT_EQ(rec.closed_calls, 0);

  const auto ret_odd = Policy::delegate(FakeSignedBitsOdd{}, Func2Args{&rec}, a, b);
  EXPECT_EQ(ret_odd, 2000LL + static_cast<long long>(a) + static_cast<long long>(b));
  EXPECT_EQ(rec.open_calls, 1);
  EXPECT_EQ(rec.closed_calls, 1);
}

}  // namespace