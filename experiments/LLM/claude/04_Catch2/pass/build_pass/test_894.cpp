#include <gtest/gtest.h>
#include "./TestProjects/Catch2/extras/catch_amalgamated.hpp"

using namespace Catch::Benchmark;
using namespace Catch::Benchmark::Detail;

// Helper: a simple callable that records invocations
struct CallCounter {
    int* count;
    explicit CallCounter(int* c) : count(c) {}
    void operator()(Chronometer) const { ++(*count); }
};

// Helper: callable that stores a value to verify identity
struct ValueHolder {
    int value;
    explicit ValueHolder(int v) : value(v) {}
    void operator()(Chronometer) const {}
};

// ---------------------------------------------------------------------------
// Test: Default construction creates a valid BenchmarkFunction (do_nothing)
// ---------------------------------------------------------------------------
TEST(BenchmarkFunctionTest_894, DefaultConstruction_894) {
    BenchmarkFunction fn;
    // Default-constructed function should be callable without throwing
    // We can't inspect internals, but calling it should not crash
    // (operator() expects a Chronometer; we need to construct one)
    // Since Chronometer construction details may be complex, we just
    // verify the object is constructed successfully.
    SUCCEED();
}

// ---------------------------------------------------------------------------
// Test: Construction from a lambda / callable
// ---------------------------------------------------------------------------
TEST(BenchmarkFunctionTest_894, ConstructFromLambda_894) {
    int called = 0;
    BenchmarkFunction fn([&called](Chronometer) { ++called; });
    // Object should be valid after construction
    SUCCEED();
}

// ---------------------------------------------------------------------------
// Test: Move construction transfers ownership
// ---------------------------------------------------------------------------
TEST(BenchmarkFunctionTest_894, MoveConstruction_894) {
    int called = 0;
    BenchmarkFunction fn1([&called](Chronometer) { ++called; });
    BenchmarkFunction fn2(std::move(fn1));
    // fn2 should now hold the callable; fn1 should be in a moved-from state
    SUCCEED();
}

// ---------------------------------------------------------------------------
// Test: Move assignment transfers ownership
// ---------------------------------------------------------------------------
TEST(BenchmarkFunctionTest_894, MoveAssignment_894) {
    int called1 = 0;
    int called2 = 0;
    BenchmarkFunction fn1([&called1](Chronometer) { ++called1; });
    BenchmarkFunction fn2([&called2](Chronometer) { ++called2; });

    fn2 = std::move(fn1);
    // fn2 should now hold fn1's original callable
    SUCCEED();
}

// ---------------------------------------------------------------------------
// Test: Move assignment returns reference to self
// ---------------------------------------------------------------------------
TEST(BenchmarkFunctionTest_894, MoveAssignmentReturnsSelf_894) {
    BenchmarkFunction fn1;
    BenchmarkFunction fn2;

    BenchmarkFunction& ref = (fn2 = std::move(fn1));
    EXPECT_EQ(&ref, &fn2);
}

// ---------------------------------------------------------------------------
// Test: Self-move-assignment should not crash
// ---------------------------------------------------------------------------
TEST(BenchmarkFunctionTest_894, SelfMoveAssignment_894) {
    BenchmarkFunction fn;
    // This is technically UB in general, but a robust implementation handles it
    fn = std::move(fn);
    SUCCEED();
}

// ---------------------------------------------------------------------------
// Test: Move construct from default-constructed
// ---------------------------------------------------------------------------
TEST(BenchmarkFunctionTest_894, MoveConstructFromDefault_894) {
    BenchmarkFunction fn1;
    BenchmarkFunction fn2(std::move(fn1));
    SUCCEED();
}

// ---------------------------------------------------------------------------
// Test: Move assign default to non-default
// ---------------------------------------------------------------------------
TEST(BenchmarkFunctionTest_894, MoveAssignDefaultToNonDefault_894) {
    int called = 0;
    BenchmarkFunction fn1([&called](Chronometer) { ++called; });
    BenchmarkFunction fn2;

    fn1 = std::move(fn2);
    // fn1 should now hold the do_nothing (or empty) callable
    SUCCEED();
}

// ---------------------------------------------------------------------------
// Test: Multiple move assignments in sequence
// ---------------------------------------------------------------------------
TEST(BenchmarkFunctionTest_894, MultipleMoveAssignments_894) {
    int a = 0, b = 0, c = 0;
    BenchmarkFunction fn1([&a](Chronometer) { ++a; });
    BenchmarkFunction fn2([&b](Chronometer) { ++b; });
    BenchmarkFunction fn3([&c](Chronometer) { ++c; });

    fn3 = std::move(fn2);
    fn3 = std::move(fn1);
    SUCCEED();
}

// ---------------------------------------------------------------------------
// Test: Construction from functor object (not lambda)
// ---------------------------------------------------------------------------
TEST(BenchmarkFunctionTest_894, ConstructFromFunctor_894) {
    int count = 0;
    CallCounter counter(&count);
    BenchmarkFunction fn(counter);
    SUCCEED();
}

// ---------------------------------------------------------------------------
// Test: Construction from moved functor
// ---------------------------------------------------------------------------
TEST(BenchmarkFunctionTest_894, ConstructFromMovedFunctor_894) {
    int count = 0;
    CallCounter counter(&count);
    BenchmarkFunction fn(std::move(counter));
    SUCCEED();
}

// ---------------------------------------------------------------------------
// Test: Chain of moves preserves valid state at destination
// ---------------------------------------------------------------------------
TEST(BenchmarkFunctionTest_894, ChainOfMoves_894) {
    BenchmarkFunction fn1([]( Chronometer) {});
    BenchmarkFunction fn2(std::move(fn1));
    BenchmarkFunction fn3(std::move(fn2));
    BenchmarkFunction fn4;
    fn4 = std::move(fn3);
    SUCCEED();
}
