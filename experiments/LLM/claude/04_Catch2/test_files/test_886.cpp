#include <gtest/gtest.h>

// Include the header under test
#include "./TestProjects/Catch2/extras/catch_amalgamated.hpp"

// Test that optimizer_barrier can be called without crashing
TEST(OptimizerBarrierTest_886, CallDoesNotThrow_886) {
    EXPECT_NO_THROW(Catch::Benchmark::Detail::optimizer_barrier());
}

// Test that optimizer_barrier can be called multiple times without issues
TEST(OptimizerBarrierTest_886, MultipleCallsDoNotThrow_886) {
    EXPECT_NO_THROW({
        Catch::Benchmark::Detail::optimizer_barrier();
        Catch::Benchmark::Detail::optimizer_barrier();
        Catch::Benchmark::Detail::optimizer_barrier();
    });
}

// Test that optimizer_barrier returns void (compiles correctly as a void function)
TEST(OptimizerBarrierTest_886, ReturnsVoid_886) {
    // This test verifies the function signature returns void
    // If it returned something else, this would fail to compile
    Catch::Benchmark::Detail::optimizer_barrier();
    SUCCEED();
}

// Test calling optimizer_barrier in a loop (simulating benchmark usage)
TEST(OptimizerBarrierTest_886, CalledInLoop_886) {
    EXPECT_NO_THROW({
        for (int i = 0; i < 1000; ++i) {
            Catch::Benchmark::Detail::optimizer_barrier();
        }
    });
}

// Test that keep_memory (called internally by optimizer_barrier) doesn't corrupt state
TEST(OptimizerBarrierTest_886, DoesNotCorruptSurroundingState_886) {
    volatile int before = 42;
    volatile int after = 99;
    
    Catch::Benchmark::Detail::optimizer_barrier();
    
    EXPECT_EQ(before, 42);
    EXPECT_EQ(after, 99);
}

// Test that optimizer_barrier can be called from different contexts
TEST(OptimizerBarrierTest_886, CallableFromDifferentContexts_886) {
    // Call directly
    Catch::Benchmark::Detail::optimizer_barrier();
    
    // Call via function pointer
    void (*func_ptr)() = &Catch::Benchmark::Detail::optimizer_barrier;
    EXPECT_NO_THROW(func_ptr());
}
