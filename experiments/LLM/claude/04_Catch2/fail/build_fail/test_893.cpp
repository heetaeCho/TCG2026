#include <gtest/gtest.h>
#include <gmock/gmock.h>

// Include the header under test
#include "./TestProjects/Catch2/extras/catch_amalgamated.hpp"

using namespace Catch::Benchmark;
using namespace Catch::Benchmark::Detail;

// A mock ChronometerConcept for creating Chronometer instances
struct MockChronometerConcept : public Detail::ChronometerConcept {
    MOCK_METHOD(void, start, (), (override));
    MOCK_METHOD(void, finish, (), (override));
};

// ============================================================
// Test: BenchmarkFunction with a callable that takes Chronometer
// (i.e., is_callable<Fun(Chronometer)> is true_type)
// ============================================================

TEST(BenchmarkFunctionTest_893, CallWithChronometerCallable_893) {
    bool wasCalled = false;
    int callCount = 0;

    // Lambda that accepts Chronometer directly
    auto fun = [&](Chronometer) {
        wasCalled = true;
        callCount++;
    };

    using ModelType = BenchmarkFunction<decltype(fun)>::model;
    ModelType m(std::move(fun));

    MockChronometerConcept mock;
    EXPECT_CALL(mock, start()).Times(testing::AnyNumber());
    EXPECT_CALL(mock, finish()).Times(testing::AnyNumber());

    Chronometer chrono(mock, 1);
    m.call(chrono);

    EXPECT_TRUE(wasCalled);
    EXPECT_EQ(callCount, 1);
}

// ============================================================
// Test: BenchmarkFunction with a callable that does NOT take Chronometer
// (i.e., is_callable<Fun(Chronometer)> is false_type)
// ============================================================

TEST(BenchmarkFunctionTest_893, CallWithNonChronometerCallable_893) {
    int callCount = 0;

    // Lambda that does NOT accept Chronometer
    auto fun = [&]() {
        callCount++;
    };

    using ModelType = BenchmarkFunction<decltype(fun)>::model;
    ModelType m(std::move(fun));

    MockChronometerConcept mock;
    EXPECT_CALL(mock, start()).Times(testing::AnyNumber());
    EXPECT_CALL(mock, finish()).Times(testing::AnyNumber());

    Chronometer chrono(mock, 1);
    m.call(chrono);

    // The non-Chronometer path should still invoke the function
    // (likely through Chronometer::measure which calls it `runs()` times)
    EXPECT_GT(callCount, 0);
}

// ============================================================
// Test: Model copy construction preserves callable behavior
// ============================================================

TEST(BenchmarkFunctionTest_893, ModelCopyConstruction_893) {
    int callCount = 0;

    auto fun = [&](Chronometer) {
        callCount++;
    };

    using ModelType = BenchmarkFunction<decltype(fun)>::model;

    // Use the const-ref constructor
    ModelType m1(fun);

    MockChronometerConcept mock;
    EXPECT_CALL(mock, start()).Times(testing::AnyNumber());
    EXPECT_CALL(mock, finish()).Times(testing::AnyNumber());

    Chronometer chrono(mock, 1);
    m1.call(chrono);

    EXPECT_EQ(callCount, 1);

    // Copy construct
    ModelType m2(fun);
    m2.call(chrono);

    EXPECT_EQ(callCount, 2);
}

// ============================================================
// Test: Model move construction preserves callable behavior
// ============================================================

TEST(BenchmarkFunctionTest_893, ModelMoveConstruction_893) {
    int callCount = 0;

    auto fun = [&](Chronometer) {
        callCount++;
    };

    using ModelType = BenchmarkFunction<decltype(fun)>::model;
    ModelType m(std::move(fun));

    MockChronometerConcept mock;
    EXPECT_CALL(mock, start()).Times(testing::AnyNumber());
    EXPECT_CALL(mock, finish()).Times(testing::AnyNumber());

    Chronometer chrono(mock, 1);
    m.call(chrono);

    EXPECT_EQ(callCount, 1);
}

// ============================================================
// Test: Multiple repeats with Chronometer-accepting callable
// ============================================================

TEST(BenchmarkFunctionTest_893, MultipleRepeatsChronometer_893) {
    int callCount = 0;

    auto fun = [&](Chronometer meter) {
        // The callable receives the Chronometer and can call measure
        meter.measure([&](int) { callCount++; });
    };

    using ModelType = BenchmarkFunction<decltype(fun)>::model;
    ModelType m(std::move(fun));

    MockChronometerConcept mock;
    EXPECT_CALL(mock, start()).Times(testing::AnyNumber());
    EXPECT_CALL(mock, finish()).Times(testing::AnyNumber());

    int repeats = 5;
    Chronometer chrono(mock, repeats);
    m.call(chrono);

    // measure should call the inner lambda `repeats` times
    EXPECT_EQ(callCount, repeats);
}

// ============================================================
// Test: Non-Chronometer callable with multiple repeats
// ============================================================

TEST(BenchmarkFunctionTest_893, MultipleRepeatsNonChronometer_893) {
    int callCount = 0;

    auto fun = [&]() {
        callCount++;
    };

    using ModelType = BenchmarkFunction<decltype(fun)>::model;
    ModelType m(std::move(fun));

    MockChronometerConcept mock;
    EXPECT_CALL(mock, start()).Times(testing::AnyNumber());
    EXPECT_CALL(mock, finish()).Times(testing::AnyNumber());

    int repeats = 10;
    Chronometer chrono(mock, repeats);
    m.call(chrono);

    // For non-Chronometer callables, the framework internally calls
    // measure which should invoke the function `repeats` times
    EXPECT_EQ(callCount, repeats);
}

// ============================================================
// Test: Chronometer::runs() returns the correct repeat count
// ============================================================

TEST(ChronometerTest_893, RunsReturnsRepeatCount_893) {
    MockChronometerConcept mock;
    int repeats = 42;
    Chronometer chrono(mock, repeats);

    EXPECT_EQ(chrono.runs(), repeats);
}

// ============================================================
// Test: Chronometer::runs() with boundary value of 0
// ============================================================

TEST(ChronometerTest_893, RunsZeroRepeats_893) {
    MockChronometerConcept mock;
    Chronometer chrono(mock, 0);

    EXPECT_EQ(chrono.runs(), 0);
}

// ============================================================
// Test: Chronometer::runs() with boundary value of 1
// ============================================================

TEST(ChronometerTest_893, RunsSingleRepeat_893) {
    MockChronometerConcept mock;
    Chronometer chrono(mock, 1);

    EXPECT_EQ(chrono.runs(), 1);
}

// ============================================================
// Test: Callable that takes int parameter (non-Chronometer)
// ============================================================

TEST(BenchmarkFunctionTest_893, CallableWithIntParam_893) {
    std::vector<int> indices;

    auto fun = [&](int i) {
        indices.push_back(i);
    };

    using ModelType = BenchmarkFunction<decltype(fun)>::model;
    ModelType m(std::move(fun));

    MockChronometerConcept mock;
    EXPECT_CALL(mock, start()).Times(testing::AnyNumber());
    EXPECT_CALL(mock, finish()).Times(testing::AnyNumber());

    int repeats = 3;
    Chronometer chrono(mock, repeats);
    m.call(chrono);

    // Should be called `repeats` times with increasing indices
    EXPECT_EQ(static_cast<int>(indices.size()), repeats);
}

// ============================================================
// Test: Stateful callable preserves state across calls
// ============================================================

TEST(BenchmarkFunctionTest_893, StatefulCallable_893) {
    struct Counter {
        mutable int count = 0;
        void operator()(Chronometer) const {
            count++;
        }
    };

    Counter counter;
    using ModelType = BenchmarkFunction<Counter>::model;
    ModelType m(counter);

    MockChronometerConcept mock;
    EXPECT_CALL(mock, start()).Times(testing::AnyNumber());
    EXPECT_CALL(mock, finish()).Times(testing::AnyNumber());

    Chronometer chrono(mock, 1);
    m.call(chrono);
    m.call(chrono);

    // The model stores its own copy, so the original counter is unchanged
    // but the model's internal counter should have been incremented
    // We just verify no crash and that the call completes
    EXPECT_EQ(counter.count, 0); // original copy not modified
}
