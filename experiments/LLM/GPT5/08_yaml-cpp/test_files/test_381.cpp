// TEST_ID: 381
// File: dragonbox_toward_plus_infinity_test_381.cpp

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "contrib/dragonbox.h"

namespace {

using ::testing::DoubleEq;
using ::testing::StrictMock;

// Minimal "SignedSignificandBits" test double (external to the policy).
struct SignedBitsStub_381 {
  bool negative = false;
  constexpr bool is_negative() const noexcept { return negative; }
};

// Mocked external collaborator to verify delegate() calls and parameters.
struct MockHandler_381 {
  MOCK_METHOD(int, OnLeft, (int a, double b), ());
  MOCK_METHOD(int, OnRight, (int a, double b), ());
};

// Functor passed into delegate(). It routes tag-dispatched calls to the mock.
struct DispatchingFunc_381 {
  MockHandler_381* handler = nullptr;

  int operator()(YAML::jkj::dragonbox::detail::left_closed_directed_t, int a, double b) const {
    return handler->OnLeft(a, b);
  }
  int operator()(YAML::jkj::dragonbox::detail::right_closed_directed_t, int a, double b) const {
    return handler->OnRight(a, b);
  }
};

class TowardPlusInfinityPolicyTest_381 : public ::testing::Test {};

TEST_F(TowardPlusInfinityPolicyTest_381, NegativeSignCallsLeftClosedDirected_381) {
  SignedBitsStub_381 s{true};

  StrictMock<MockHandler_381> handler;
  DispatchingFunc_381 func{&handler};

  EXPECT_CALL(handler, OnLeft(7, DoubleEq(3.5))).WillOnce(::testing::Return(123));
  // Ensure the "right" branch is not taken.
  EXPECT_CALL(handler, OnRight(::testing::_, ::testing::_)).Times(0);

  const int result =
      YAML::jkj::dragonbox::policy::decimal_to_binary_rounding::toward_plus_infinity_t::delegate(
          s, func, 7, 3.5);

  EXPECT_EQ(result, 123);
}

TEST_F(TowardPlusInfinityPolicyTest_381, NonNegativeSignCallsRightClosedDirected_381) {
  SignedBitsStub_381 s{false};

  StrictMock<MockHandler_381> handler;
  DispatchingFunc_381 func{&handler};

  EXPECT_CALL(handler, OnRight(42, DoubleEq(-1.25))).WillOnce(::testing::Return(-9));
  // Ensure the "left" branch is not taken.
  EXPECT_CALL(handler, OnLeft(::testing::_, ::testing::_)).Times(0);

  const int result =
      YAML::jkj::dragonbox::policy::decimal_to_binary_rounding::toward_plus_infinity_t::delegate(
          s, func, 42, -1.25);

  EXPECT_EQ(result, -9);
}

TEST_F(TowardPlusInfinityPolicyTest_381, ZeroTreatedAsNonNegativeCallsRightClosedDirected_381) {
  // Boundary-style check: our stub treats "negative=false" as non-negative (e.g., zero).
  SignedBitsStub_381 s{/*negative=*/false};

  StrictMock<MockHandler_381> handler;
  DispatchingFunc_381 func{&handler};

  EXPECT_CALL(handler, OnRight(0, DoubleEq(0.0))).WillOnce(::testing::Return(1));
  EXPECT_CALL(handler, OnLeft(::testing::_, ::testing::_)).Times(0);

  const int result =
      YAML::jkj::dragonbox::policy::decimal_to_binary_rounding::toward_plus_infinity_t::delegate(
          s, func, 0, 0.0);

  EXPECT_EQ(result, 1);
}

TEST_F(TowardPlusInfinityPolicyTest_381, IsNoexceptForGivenTypes_381) {
  SignedBitsStub_381 s{false};
  StrictMock<MockHandler_381> handler;
  DispatchingFunc_381 func{&handler};

  static_assert(
      noexcept(YAML::jkj::dragonbox::policy::decimal_to_binary_rounding::toward_plus_infinity_t::
                   delegate(s, func, 1, 2.0)),
      "delegate(...) should be noexcept for this instantiation");

  // Also do a runtime smoke call (no exception should be thrown).
  EXPECT_CALL(handler, OnRight(1, DoubleEq(2.0))).WillOnce(::testing::Return(5));
  EXPECT_EQ((YAML::jkj::dragonbox::policy::decimal_to_binary_rounding::toward_plus_infinity_t::
                 delegate(s, func, 1, 2.0)),
            5);
}

}  // namespace