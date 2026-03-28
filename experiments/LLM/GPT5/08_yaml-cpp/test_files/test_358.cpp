// TEST_ID: 358
#include <gtest/gtest.h>

#include <memory>
#include <string>
#include <type_traits>
#include <utility>

#include "contrib/dragonbox.h"

namespace {

using Tag358 =
    YAML::jkj::dragonbox::policy::decimal_to_binary_rounding::nearest_to_odd_t;

// SFINAE helper: can we form the expression Tag358::delegate(bits, f, args...)?
template <class Bits, class F, class... Args>
class is_delegate_invocable_358 {
  template <class B, class Fn, class... As>
  static auto test(int)
      -> decltype(Tag358::delegate(std::declval<B>(), std::declval<Fn>(),
                                   std::declval<As>()...),
                  std::true_type{});

  template <class, class, class...>
  static auto test(...) -> std::false_type;

 public:
  static constexpr bool value = decltype(test<Bits, F, Args...>(0))::value;
};

template <class Bits, class F, class... Args>
inline constexpr bool is_delegate_invocable_v_358 =
    is_delegate_invocable_358<Bits, F, Args...>::value;

class NearestToOddDelegateTest_358 : public ::testing::Test {};

struct OverloadedFunctor_358 {
  int operator()(Tag358, int) const { return 111; }
  int operator()(int, int) const { return 222; }  // should NOT be selected
};

struct ZeroArgFunctor_358 {
  constexpr int operator()(Tag358) const { return 7; }
};

struct ConcatFunctor_358 {
  std::shared_ptr<int> calls;
  std::string operator()(Tag358, int n, const std::string& s) const {
    ++(*calls);
    return s + std::to_string(n);
  }
};

struct ReturnsDoubleFunctor_358 {
  double operator()(Tag358, int x) const { return x + 0.25; }
};

struct NotCallableWithTag_358 {
  int operator()(int) const { return 1; }  // no overload taking Tag358
};

TEST_F(NearestToOddDelegateTest_358, DelegatesToOverloadTakingTagFirst_358) {
  // If delegate correctly injects Tag358 as the first parameter, it should pick
  // operator()(Tag358, int) and return 111.
  EXPECT_EQ(Tag358::delegate(0, OverloadedFunctor_358{}, 5), 111);
}

TEST_F(NearestToOddDelegateTest_358, SupportsZeroAdditionalArguments_358) {
  // Args... can be empty; functor should be called with only Tag358.
  EXPECT_EQ(Tag358::delegate(0, ZeroArgFunctor_358{}), 7);
}

TEST_F(NearestToOddDelegateTest_358, ForwardsArgumentsAndReturnsValue_358) {
  auto calls = std::make_shared<int>(0);
  ConcatFunctor_358 f{calls};

  const std::string out = Tag358::delegate(123, f, 42, std::string("v="));
  EXPECT_EQ(out, "v=42");
  EXPECT_EQ(*calls, 1);
}

TEST_F(NearestToOddDelegateTest_358, ReturnTypeMatchesFunctorReturnType_358) {
  using Ret = decltype(Tag358::delegate(0, ReturnsDoubleFunctor_358{}, 3));
  static_assert(std::is_same<Ret, double>::value,
                "delegate() should preserve the functor's return type");
  EXPECT_DOUBLE_EQ(Tag358::delegate(0, ReturnsDoubleFunctor_358{}, 3), 3.25);
}

TEST_F(NearestToOddDelegateTest_358, IsConstexprUsableAndNoexcept_358) {
  // constexpr usability
  constexpr int v = Tag358::delegate(0, ZeroArgFunctor_358{});
  static_assert(v == 7, "constexpr delegate() should evaluate correctly");

  // noexcept is part of the interface
  static_assert(noexcept(Tag358::delegate(0, ZeroArgFunctor_358{})),
                "delegate() is declared noexcept");
}

TEST_F(NearestToOddDelegateTest_358, NotInvocableWhenFunctorCannotAcceptTag_358) {
  // Observable (compile-time) error case: delegate expression is not formable
  // if the provided functor can't be called as f(Tag358{}, args...).
  static_assert(!is_delegate_invocable_v_358<int, NotCallableWithTag_358, int>,
                "delegate() should not be invocable with an incompatible functor");

  EXPECT_TRUE((is_delegate_invocable_v_358<int, ReturnsDoubleFunctor_358, int>));
}

}  // namespace