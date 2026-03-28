// File: tests/complete_invoke_tests_900.cpp

#include <gtest/gtest.h>
#include <memory>
#include <stdexcept>
#include <string>
#include <utility>

#include "Catch2/extras/catch_amalgamated.hpp"

using Catch::Benchmark::Detail::complete_invoke;

namespace {

// ---- Helper callables used only to observe behavior (no peeking at internals) ----

// Simple adder: observable return value
int add_fn(int a, int b) { return a + b; }

// Void callable: observable via side-effect on reference
void set_to_value(int& target, int value) { target = value; }

// Overload set to detect lvalue vs rvalue forwarding
const char* lvrv_tag(int&)  { return "lvalue"; }
const char* lvrv_tag(int&&) { return "rvalue"; }

// Zero-arg callable
int forty_two() { return 42; }

// Exception-throwing callable
[[noreturn]] int throws_runtime() { throw std::runtime_error("boom"); }

// Movable-only argument consumer (verifies perfect-forwarding/move)
int consume_unique(std::unique_ptr<int> p) {
    // observable behavior via returned value
    return p ? *p : -1;
}

} // namespace

// -----------------------------------------------------------------------------
// TEST SUITE
// -----------------------------------------------------------------------------

// Normal operation: returns value for a plain function
TEST(CompleteInvokeTest_900, ReturnsValue_900) {
    const int result = complete_invoke(add_fn, 7, 5);
    EXPECT_EQ(result, 12);
}

// Normal operation: void callable’s side effect is observable through reference
TEST(CompleteInvokeTest_900, VoidCallable_SideEffect_900) {
    int x = 0;
    complete_invoke(set_to_value, x, 123);
    EXPECT_EQ(x, 123);
}

// Boundary-ish / forwarding check: lvalue vs rvalue overload is selected correctly
TEST(CompleteInvokeTest_900, ForwardsLvalueVsRvalue_900) {
    int i = 10;
    // Pass lvalue
    EXPECT_STREQ(complete_invoke(lvrv_tag, i), "lvalue");
    // Pass rvalue
    EXPECT_STREQ(complete_invoke(lvrv_tag, 10), "rvalue");
}

// Exceptional case: exceptions propagate unchanged
TEST(CompleteInvokeTest_900, PropagatesExceptions_900) {
    EXPECT_THROW({
        // Return value is irrelevant; we just expect the throw to escape
        (void)complete_invoke(throws_runtime);
    }, std::runtime_error);
}

// Normal operation: zero-argument callable works
TEST(CompleteInvokeTest_900, HandlesZeroArgCallable_900) {
    EXPECT_EQ(complete_invoke(forty_two), 42);
}

// Boundary / forwarding: movable-only argument is moved (caller becomes empty)
TEST(CompleteInvokeTest_900, MovesMovableOnlyArgument_900) {
    std::unique_ptr<int> p(new int(42));
    // After perfect-forwarding with std::move, the callee can consume ownership
    const int result = complete_invoke(consume_unique, std::move(p));
    EXPECT_EQ(result, 42);
    // Observable effect: source has been moved-from (no ownership)
    EXPECT_EQ(p.get(), nullptr);
}

// Normal operation with lambda & capture: verifies generic callables work
TEST(CompleteInvokeTest_900, WorksWithLambdasAndCaptures_900) {
    std::string prefix = "hello ";
    auto concat = [&prefix](const std::string& name) { return prefix + name; };

    const auto out = complete_invoke(concat, std::string("world"));
    EXPECT_EQ(out, "hello world");
}
