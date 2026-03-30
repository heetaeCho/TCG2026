// File: ./TestProjects/yaml-cpp/test/dragonbox_nearest_toward_minus_infinity_static_boundary_test_380.cpp

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "contrib/dragonbox.h"

namespace {

namespace d2b = YAML::jkj::dragonbox::policy::decimal_to_binary_rounding;

struct FakeSignedSignificandBits {
  bool negative = false;
  constexpr bool is_negative() const noexcept { return negative; }
};

// A gMock-backed receiver so we can verify which overload was invoked and with what args.
class MockReceiver {
 public:
  MOCK_METHOD(int, CallTowardZero, (int a, int b), ());
  MOCK_METHOD(int, CallAwayFromZero, (int a, int b), ());
};

// Functor that matches the delegate's expected calling convention:
// f(nearest_toward_zero, args...) or f(nearest_away_from_zero, args...)
struct MockFunctor {
  explicit MockFunctor(MockReceiver* r) : receiver(r) {}

  int operator()(d2b::nearest_toward_zero_t, int a, int b) const {
    return receiver->CallTowardZero(a, b);
  }

  int operator()(d2b::nearest_away_from_zero_t, int a, int b) const {
    return receiver->CallAwayFromZero(a, b);
  }

  MockReceiver* receiver;
};

using Policy = d2b::nearest_toward_minus_infinity_static_boundary_t;

TEST(NearestTowardMinusInfinityStaticBoundaryTest_380,
     DelegatesToAwayFromZeroWhenNegative_380) {
  MockReceiver receiver;
  MockFunctor functor(&receiver);

  FakeSignedSignificandBits s;
  s.negative = true;

  EXPECT_CALL(receiver, CallAwayFromZero(11, 22)).WillOnce(::testing::Return(123));
  EXPECT_CALL(receiver, CallTowardZero(::testing::_, ::testing::_)).Times(0);

  const int result = Policy::delegate(s, functor, 11, 22);
  EXPECT_EQ(result, 123);
}

TEST(NearestTowardMinusInfinityStaticBoundaryTest_380,
     DelegatesToTowardZeroWhenNonNegative_380) {
  MockReceiver receiver;
  MockFunctor functor(&receiver);

  FakeSignedSignificandBits s;
  s.negative = false;

  EXPECT_CALL(receiver, CallTowardZero(7, 9)).WillOnce(::testing::Return(456));
  EXPECT_CALL(receiver, CallAwayFromZero(::testing::_, ::testing::_)).Times(0);

  const int result = Policy::delegate(s, functor, 7, 9);
  EXPECT_EQ(result, 456);
}

TEST(NearestTowardMinusInfinityStaticBoundaryTest_380,
     TreatsZeroAsNonNegativeAndDelegatesTowardZero_380) {
  MockReceiver receiver;
  MockFunctor functor(&receiver);

  // "Zero" is represented here as non-negative; we only verify observable behavior:
  // when is_negative() is false, delegate routes to nearest_toward_zero.
  FakeSignedSignificandBits s;
  s.negative = false;

  EXPECT_CALL(receiver, CallTowardZero(0, 0)).WillOnce(::testing::Return(1));
  EXPECT_CALL(receiver, CallAwayFromZero(::testing::_, ::testing::_)).Times(0);

  const int result = Policy::delegate(s, functor, 0, 0);
  EXPECT_EQ(result, 1);
}

TEST(NearestTowardMinusInfinityStaticBoundaryTest_380,
     IsNoexceptWhenFunctorCallsAreNoexcept_380) {
  struct NoexceptFunctor {
    int operator()(d2b::nearest_toward_zero_t, int, int) const noexcept { return 10; }
    int operator()(d2b::nearest_away_from_zero_t, int, int) const noexcept { return 20; }
  };

  constexpr FakeSignedSignificandBits neg{true};
  constexpr FakeSignedSignificandBits nonneg{false};
  constexpr NoexceptFunctor f{};

  static_assert(noexcept(Policy::delegate(neg, f, 1, 2)),
                "delegate() should be noexcept when the selected functor call is noexcept");
  static_assert(noexcept(Policy::delegate(nonneg, f, 1, 2)),
                "delegate() should be noexcept when the selected functor call is noexcept");
}

TEST(NearestTowardMinusInfinityStaticBoundaryTest_380,
     WorksInConstexprContextAndSelectsBranch_380) {
  struct ConstexprFunctor {
    // Return distinct values so selection is observable at compile time.
    constexpr int operator()(d2b::nearest_toward_zero_t, int x) const noexcept { return x + 1; }
    constexpr int operator()(d2b::nearest_away_from_zero_t, int x) const noexcept { return x + 100; }
  };

  constexpr ConstexprFunctor f{};

  constexpr FakeSignedSignificandBits neg{true};
  constexpr FakeSignedSignificandBits nonneg{false};

  static_assert(Policy::delegate(nonneg, f, 5) == 6, "Expected toward-zero branch");
  static_assert(Policy::delegate(neg, f, 5) == 105, "Expected away-from-zero branch");
}

}  // namespace