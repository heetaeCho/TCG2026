// File: ./TestProjects/yaml-cpp/test/dragonbox_toward_zero_policy_test_383.cpp

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <memory>
#include <string>
#include <type_traits>
#include <utility>

#include "contrib/dragonbox.h"

namespace {

using TowardZero =
    YAML::jkj::dragonbox::policy::decimal_to_binary_rounding::toward_zero;
using Tag = YAML::jkj::dragonbox::detail::left_closed_directed_t;

// --- Compile-time checks (observable interface properties) ---

struct ConstexprNoArgsFunc {
  constexpr int operator()(Tag) const { return 42; }
};

static_assert(TowardZero::delegate(0, ConstexprNoArgsFunc{}) == 42,
              "delegate should be usable in constexpr context and propagate return value");
static_assert(noexcept(TowardZero::delegate(0, ConstexprNoArgsFunc{})),
              "delegate should be noexcept");

// --- Helpers for runtime behavioral verification ---

struct RecordingFunc {
  // Records the values it receives.
  int* called = nullptr;
  int* got_int = nullptr;
  std::string* got_str = nullptr;

  int operator()(Tag, int a, std::string s) const {
    if (called) *called = 1;
    if (got_int) *got_int = a;
    if (got_str) *got_str = std::move(s);
    return a + 7;
  }
};

class TowardZeroPolicyTest_383 : public ::testing::Test {};

// --- Google Mock collaborator pattern ---
// We mock an external collaborator (a handler) and use a thin functor wrapper.
class MockHandler_383 {
 public:
  MOCK_METHOD(int, Call, (Tag, int, std::string), ());
  MOCK_METHOD(std::unique_ptr<int>, CallMoveOnly, (Tag, std::unique_ptr<int>), ());
};

struct HandlerFunctor_383 {
  MockHandler_383* h = nullptr;

  int operator()(Tag t, int a, std::string s) const { return h->Call(t, a, std::move(s)); }

  std::unique_ptr<int> operator()(Tag t, std::unique_ptr<int> p) const {
    return h->CallMoveOnly(t, std::move(p));
  }
};

TEST_F(TowardZeroPolicyTest_383, DelegateCallsFunctionWithTagOnly_383) {
  struct Func {
    int operator()(Tag) const { return 123; }
  };

  const int out = TowardZero::delegate(0, Func{});
  EXPECT_EQ(out, 123);
}

TEST_F(TowardZeroPolicyTest_383, DelegateForwardsArgsAndPropagatesReturn_383) {
  int called = 0;
  int got_int = 0;
  std::string got_str;

  RecordingFunc f;
  f.called = &called;
  f.got_int = &got_int;
  f.got_str = &got_str;

  const int out = TowardZero::delegate(999, f, 35, std::string("hello"));
  EXPECT_EQ(called, 1);
  EXPECT_EQ(got_int, 35);
  EXPECT_EQ(got_str, "hello");
  EXPECT_EQ(out, 42);  // 35 + 7 from RecordingFunc
}

TEST_F(TowardZeroPolicyTest_383, DelegateWorksWithDifferentSignedSignificandBitsTypes_383) {
  struct Func {
    int operator()(Tag, int v) const { return v * 2; }
  };

  // Observable behavior: delegate is callable with different SignedSignificandBits argument types.
  EXPECT_EQ(TowardZero::delegate(0, Func{}, 11), 22);
  EXPECT_EQ(TowardZero::delegate(static_cast<unsigned>(123), Func{}, 11), 22);
  EXPECT_EQ(TowardZero::delegate(static_cast<long long>(-7), Func{}, 11), 22);
}

TEST_F(TowardZeroPolicyTest_383, DelegateInvokesProvidedFunctorInstance_383) {
  // Verifies the passed-in functor instance is the one invoked (external interaction).
  struct StatefulFunc {
    int* counter = nullptr;
    int operator()(Tag, int x) const {
      ++(*counter);
      return x;
    }
  };

  int counter = 0;
  StatefulFunc f{&counter};

  EXPECT_EQ(TowardZero::delegate(0, f, 5), 5);
  EXPECT_EQ(counter, 1);

  EXPECT_EQ(TowardZero::delegate(0, f, 6), 6);
  EXPECT_EQ(counter, 2);
}

TEST_F(TowardZeroPolicyTest_383, DelegateCallsMockHandlerWithExpectedParameters_383) {
  MockHandler_383 mock;
  HandlerFunctor_383 f{&mock};

  EXPECT_CALL(mock, Call(::testing::_, 7, std::string("abc"))).WillOnce(::testing::Return(99));

  const int out = TowardZero::delegate(0, f, 7, std::string("abc"));
  EXPECT_EQ(out, 99);
}

TEST_F(TowardZeroPolicyTest_383, DelegateSupportsMoveOnlyArgumentsAndReturn_383) {
  MockHandler_383 mock;
  HandlerFunctor_383 f{&mock};

  auto in = std::make_unique<int>(123);
  auto out_ret = std::make_unique<int>(456);

  EXPECT_CALL(mock, CallMoveOnly(::testing::_, ::testing::_))
      .WillOnce([&](Tag, std::unique_ptr<int> p) {
        // Observable: argument arrives and can be consumed by callee.
        EXPECT_NE(p, nullptr);
        EXPECT_EQ(*p, 123);
        return out_ret.release();  // return raw, will be wrapped by unique_ptr below
      });

  std::unique_ptr<int> out = TowardZero::delegate(0, f, std::move(in));
  ASSERT_NE(out, nullptr);
  EXPECT_EQ(*out, 456);
}

}  // namespace