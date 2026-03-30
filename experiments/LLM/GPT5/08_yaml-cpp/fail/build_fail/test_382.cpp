// File: ./TestProjects/yaml-cpp/test/dragonbox_toward_minus_infinity_test_382.cpp

#include <gtest/gtest.h>

#include "contrib/dragonbox.h"

namespace {

using Policy =
    YAML::jkj::dragonbox::policy::decimal_to_binary_rounding::toward_minus_infinity_t;

using LeftTag  = YAML::jkj::dragonbox::detail::left_closed_directed_t;
using RightTag = YAML::jkj::dragonbox::detail::right_closed_directed_t;

struct FakeSignedSignificandBits {
  bool neg = false;
  constexpr bool is_negative() const noexcept { return neg; }
};

struct RecordingFunc {
  int* called_kind = nullptr;  // 0 = left, 1 = right
  int* seen_x = nullptr;
  int* seen_y = nullptr;

  int operator()(LeftTag, int x, int y) const {
    if (called_kind) *called_kind = 0;
    if (seen_x) *seen_x = x;
    if (seen_y) *seen_y = y;
    return 1000 + x + y;
  }

  int operator()(RightTag, int x, int y) const {
    if (called_kind) *called_kind = 1;
    if (seen_x) *seen_x = x;
    if (seen_y) *seen_y = y;
    return 2000 + x + y;
  }
};

class TowardMinusInfinityPolicyTest_382 : public ::testing::Test {};

}  // namespace

TEST_F(TowardMinusInfinityPolicyTest_382, NonNegativeUsesLeftClosedDirectedTag_382) {
  int called = -1, x = 0, y = 0;
  RecordingFunc f{&called, &x, &y};

  const int result = Policy::delegate(FakeSignedSignificandBits{false}, f, 3, 4);

  EXPECT_EQ(called, 0);
  EXPECT_EQ(x, 3);
  EXPECT_EQ(y, 4);
  EXPECT_EQ(result, 1000 + 3 + 4);
}

TEST_F(TowardMinusInfinityPolicyTest_382, NegativeUsesRightClosedDirectedTag_382) {
  int called = -1, x = 0, y = 0;
  RecordingFunc f{&called, &x, &y};

  const int result = Policy::delegate(FakeSignedSignificandBits{true}, f, 7, 9);

  EXPECT_EQ(called, 1);
  EXPECT_EQ(x, 7);
  EXPECT_EQ(y, 9);
  EXPECT_EQ(result, 2000 + 7 + 9);
}

TEST_F(TowardMinusInfinityPolicyTest_382, ZeroTreatedAsNonNegativeAndUsesLeftTag_382) {
  // Boundary case: "zero" here means "not negative" per the public is_negative() contract.
  int called = -1, x = 0, y = 0;
  RecordingFunc f{&called, &x, &y};

  const int result = Policy::delegate(FakeSignedSignificandBits{false}, f, 0, 0);

  EXPECT_EQ(called, 0);
  EXPECT_EQ(x, 0);
  EXPECT_EQ(y, 0);
  EXPECT_EQ(result, 1000);
}

TEST_F(TowardMinusInfinityPolicyTest_382, ForwardsArgumentsToCallable_382) {
  int called = -1, x = 0, y = 0;
  RecordingFunc f{&called, &x, &y};

  (void)Policy::delegate(FakeSignedSignificandBits{true}, f, -123, 456);

  EXPECT_EQ(called, 1);
  EXPECT_EQ(x, -123);
  EXPECT_EQ(y, 456);
}