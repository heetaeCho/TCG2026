// File: make_test_invoker_fixture_tests_432.cpp
#include <gtest/gtest.h>
#include <atomic>

// Include the header under test
#include "catch2/internal/catch_test_registry.hpp"

// We rely only on the public ITestInvoker interface (invoke())
// and the factory function template makeTestInvokerFixture.

namespace {

struct ProbedA {
    // Use a global/static counter to observe side effects of a const method call
    static std::atomic<int> call_count;

    ProbedA() = default;
    void ConstTestMethod() const { ++call_count; }
};
std::atomic<int> ProbedA::call_count{0};

struct ProbedB {
    static std::atomic<int> call_count;

    ProbedB() = default;
    void Run() const { ++call_count; }
};
std::atomic<int> ProbedB::call_count{0};

} // namespace

// --- Tests ---

TEST(MakeTestInvokerFixture_432, ReturnsNonNull_432) {
    using Catch::makeTestInvokerFixture;

    auto invoker = makeTestInvokerFixture(&ProbedA::ConstTestMethod);
    ASSERT_NE(invoker, nullptr);  // Should create a valid invoker
}

TEST(MakeTestInvokerFixture_432, InvokeCallsConstMethodOnce_432) {
    using Catch::makeTestInvokerFixture;
    ProbedA::call_count = 0;

    auto invoker = makeTestInvokerFixture(&ProbedA::ConstTestMethod);

    // Observable behavior: invoking should result in exactly one call
    invoker->invoke();
    EXPECT_EQ(ProbedA::call_count.load(), 1);
}

TEST(MakeTestInvokerFixture_432, MultipleInvokesCallMethodMultipleTimes_432) {
    using Catch::makeTestInvokerFixture;
    ProbedA::call_count = 0;

    auto invoker = makeTestInvokerFixture(&ProbedA::ConstTestMethod);

    invoker->invoke();
    invoker->invoke();
    EXPECT_EQ(ProbedA::call_count.load(), 2);
}

TEST(MakeTestInvokerFixture_432, WorksWithDifferentFixtureTypes_432) {
    using Catch::makeTestInvokerFixture;
    ProbedA::call_count = 0;
    ProbedB::call_count = 0;

    // Verify template works with different classes & const member signatures
    auto invokerA = makeTestInvokerFixture(&ProbedA::ConstTestMethod);
    auto invokerB = makeTestInvokerFixture(&ProbedB::Run);

    invokerA->invoke();
    invokerB->invoke();

    EXPECT_EQ(ProbedA::call_count.load(), 1);
    EXPECT_EQ(ProbedB::call_count.load(), 1);
}
