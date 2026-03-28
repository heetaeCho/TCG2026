// File: tests/invoke_deoptimized_tests_887.cpp
#include <gtest/gtest.h>
#include <type_traits>
#include <string>
#include "Catch2/extras/catch_amalgamated.hpp"

namespace C = Catch::Benchmark;

class InvokeDeoptimizedTest_887 : public ::testing::Test {};

// ---------- Helper detection idiom (for SFINAE checks) ----------
template <typename, typename = void>
struct can_call_invoke_deoptimized_887 : std::false_type {};

template <typename F, typename... Args>
struct can_call_invoke_deoptimized_887<
    void(F, Args...),
    std::void_t<decltype(C::invoke_deoptimized(std::declval<F>(), std::declval<Args>()...))>
> : std::true_type {};

// ---------- Test 1: callable is invoked for non-void-returning callables ----------
TEST_F(InvokeDeoptimizedTest_887, CallsCallable_NonVoidReturn_887) {
    int side_effect = 0;
    auto fn = [&side_effect]() -> int {
        ++side_effect;
        return 42; // return value should be consumed internally
    };

    // Should compile and run; observable behavior: side_effect increments
    C::invoke_deoptimized(fn);
    EXPECT_EQ(side_effect, 1);
}

// ---------- Test 2: return type of invoke_deoptimized is void for non-void callees ----------
TEST_F(InvokeDeoptimizedTest_887, ReturnTypeIsVoid_ForNonVoidCallable_887) {
    auto fn = []() -> int { return 7; };
    // decltype(...) of a call expression yields the function's return type
    static_assert(std::is_void_v<decltype(C::invoke_deoptimized(fn))>,
                  "invoke_deoptimized must return void when callee returns non-void");
    SUCCEED();
}

// ---------- Test 3: SFINAE disables this overload for void-returning callables ----------
TEST_F(InvokeDeoptimizedTest_887, SFINAEDisabled_ForVoidReturningCallable_887) {
    int counter = 0;

    auto void_fn = [&counter]() -> void { ++counter; };
    auto nonvoid_fn = [&counter]() -> int { ++counter; return 1; };

    // Detection: non-void should be invocable; void should not select this overload
    static_assert(
        can_call_invoke_deoptimized_887<void(decltype(nonvoid_fn))>::value,
        "Should be invocable for non-void-returning callable"
    );
    static_assert(
        !can_call_invoke_deoptimized_887<void(decltype(void_fn))>::value,
        "This overload should not be viable for void-returning callable"
    );

    // Runtime: confirm behavior still sane for the non-void case
    C::invoke_deoptimized(nonvoid_fn);
    EXPECT_EQ(counter, 1);
}

// ---------- Test 4: perfect-forwarding preserves value category (lvalue vs rvalue) ----------
namespace {
struct MoveOnly_887 {
    MoveOnly_887() = default;
    MoveOnly_887(const MoveOnly_887&) = delete;
    MoveOnly_887& operator=(const MoveOnly_887&) = delete;
    MoveOnly_887(MoveOnly_887&&) noexcept = default;
    MoveOnly_887& operator=(MoveOnly_887&&) noexcept = default;
};
} // namespace

TEST_F(InvokeDeoptimizedTest_887, PerfectForwarding_PreservesValueCategory_887) {
    // Functor with overload set to observe which overload was selected
    struct OverloadProbe {
        int called_lvalue = 0;
        int called_rvalue = 0;

        int operator()(MoveOnly_887&) {
            ++called_lvalue;
            return 1;
        }
        int operator()(MoveOnly_887&&) {
            ++called_rvalue;
            return 2;
        }
    } probe;

    MoveOnly_887 obj;

    // Call with lvalue
    C::invoke_deoptimized(probe, obj);
    EXPECT_EQ(probe.called_lvalue, 1);
    EXPECT_EQ(probe.called_rvalue, 0);

    // Call with rvalue
    C::invoke_deoptimized(probe, std::move(obj));
    EXPECT_EQ(probe.called_lvalue, 1);
    EXPECT_EQ(probe.called_rvalue, 1);
}

// ---------- Test 5: forwards multiple arguments correctly ----------
TEST_F(InvokeDeoptimizedTest_887, ForwardsMultipleArguments_887) {
    int count = 0;
    auto fn = [&count](int a, std::string s) -> std::size_t {
        ++count;
        // Observable outcome: returns something non-void; count increment shows we ran.
        return static_cast<std::size_t>(a + static_cast<int>(s.size()));
    };

    C::invoke_deoptimized(fn, 3, std::string("abc"));
    EXPECT_EQ(count, 1);
}
