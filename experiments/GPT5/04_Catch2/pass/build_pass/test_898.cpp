// File: tests/CompleteInvokerTests_898.cpp

#include <gtest/gtest.h>
#include <memory>
#include <stdexcept>
#include <string>

// Include the amalgamated header that contains CompleteInvoker
#include "Catch2/extras/catch_amalgamated.hpp"

using Catch::Benchmark::Detail::CompleteInvoker;

TEST(CompleteInvokerTest_898, Invoke_ReturnsValue_898) {
    auto add = [](int a, int b) { return a + b; };
    int out = CompleteInvoker<int>::invoke(add, 3, 4);
    EXPECT_EQ(out, 7);
}

TEST(CompleteInvokerTest_898, Invoke_NoArgs_898) {
    auto fortyTwo = []() { return 42; };
    int out = CompleteInvoker<int>::invoke(fortyTwo);
    EXPECT_EQ(out, 42);
}

TEST(CompleteInvokerTest_898, Invoke_VoidFunctionSideEffect_898) {
    int counter = 0;
    auto incBy = [](int& x, int delta) { x += delta; }; // side-effect on reference
    // Expecting void return — just that side-effect is visible after the call
    CompleteInvoker<void>::invoke(incBy, counter, 5);
    EXPECT_EQ(counter, 5);
}

TEST(CompleteInvokerTest_898, Invoke_ThrowsException_898) {
    auto willThrow = []() -> int {
        throw std::runtime_error("boom");
    };
    EXPECT_THROW(
        (void)CompleteInvoker<int>::invoke(willThrow),
        std::runtime_error
    );
}

TEST(CompleteInvokerTest_898, Invoke_ForwardsLvalueReference_898) {
    int value = 5;
    auto setTo = [](int& ref, int v) { ref = v; };
    CompleteInvoker<void>::invoke(setTo, value, 10);
    EXPECT_EQ(value, 10);
}

TEST(CompleteInvokerTest_898, Invoke_ForwardsConstReference_898) {
    const std::string s = "hello";
    auto length = [](const std::string& ref) { return ref.size(); };
    auto out = CompleteInvoker<std::size_t>::invoke(length, s);
    EXPECT_EQ(out, s.size());
}

TEST(CompleteInvokerTest_898, Invoke_ForwardsMoveOnly_898) {
    auto consume = [](std::unique_ptr<int> p) {
        return *p + 1; // observable: uses moved-in ownership
    };
    std::unique_ptr<int> up = std::make_unique<int>(3);

    int result = CompleteInvoker<int>::invoke(consume, std::move(up));
    EXPECT_EQ(result, 4);
    // After move, the original unique_ptr should be empty (observable effect)
    EXPECT_EQ(up.get(), nullptr);
}

TEST(CompleteInvokerTest_898, Invoke_MultipleArgTypes_898) {
    auto formatter = [](int n, const std::string& tag, double scale) {
        return tag + ":" + std::to_string(static_cast<int>(n * scale));
    };
    auto out = CompleteInvoker<std::string>::invoke(formatter, 8, std::string("X"), 1.5);
    EXPECT_EQ(out, "X:12");
}
