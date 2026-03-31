#include <gtest/gtest.h>
#include "catch2/internal/catch_context.hpp"
#include "catch2/internal/catch_random_number_generator.hpp"

// Test that sharedRng returns a reference
TEST(SharedRngTest_645, ReturnsReference_645) {
    Catch::SimplePcg32& rng = Catch::sharedRng();
    // Just verify we can obtain a reference without crashing
    (void)rng;
}

// Test that sharedRng returns the same instance every time (static)
TEST(SharedRngTest_645, ReturnsSameInstance_645) {
    Catch::SimplePcg32& rng1 = Catch::sharedRng();
    Catch::SimplePcg32& rng2 = Catch::sharedRng();
    EXPECT_EQ(&rng1, &rng2);
}

// Test that the shared RNG can generate values
TEST(SharedRngTest_645, CanGenerateValues_645) {
    Catch::SimplePcg32& rng = Catch::sharedRng();
    auto val = rng();
    // Just verify it produces a value without crashing
    (void)val;
}

// Test that the shared RNG produces different values on successive calls
TEST(SharedRngTest_645, ProducesDifferentValuesOnSuccessiveCalls_645) {
    Catch::SimplePcg32& rng = Catch::sharedRng();
    // Seed to a known state first so we have deterministic behavior
    rng.seed(12345);
    auto val1 = rng();
    auto val2 = rng();
    // It's extremely unlikely (but theoretically possible) for a PCG to produce
    // the same value twice in a row. For practical testing this is fine.
    EXPECT_NE(val1, val2);
}

// Test SimplePcg32 default constructor
TEST(SimplePcg32Test_645, DefaultConstructor_645) {
    Catch::SimplePcg32 rng1;
    Catch::SimplePcg32 rng2;
    // Two default-constructed RNGs should be equal
    EXPECT_TRUE(rng1 == rng2);
}

// Test SimplePcg32 seeded constructor
TEST(SimplePcg32Test_645, SeededConstructor_645) {
    Catch::SimplePcg32 rng1(42);
    Catch::SimplePcg32 rng2(42);
    EXPECT_TRUE(rng1 == rng2);
}

// Test SimplePcg32 different seeds produce different states
TEST(SimplePcg32Test_645, DifferentSeedsProduceDifferentStates_645) {
    Catch::SimplePcg32 rng1(42);
    Catch::SimplePcg32 rng2(99);
    EXPECT_TRUE(rng1 != rng2);
}

// Test seed method resets state
TEST(SimplePcg32Test_645, SeedResetsState_645) {
    Catch::SimplePcg32 rng1(42);
    rng1(); // advance state
    rng1.seed(42); // reset
    Catch::SimplePcg32 rng2(42);
    EXPECT_TRUE(rng1 == rng2);
}

// Test that operator() changes state
TEST(SimplePcg32Test_645, OperatorCallChangesState_645) {
    Catch::SimplePcg32 rng1(100);
    Catch::SimplePcg32 rng2(100);
    rng1();
    EXPECT_TRUE(rng1 != rng2);
}

// Test that two identically seeded RNGs produce the same sequence
TEST(SimplePcg32Test_645, DeterministicSequence_645) {
    Catch::SimplePcg32 rng1(777);
    Catch::SimplePcg32 rng2(777);
    for (int i = 0; i < 100; ++i) {
        EXPECT_EQ(rng1(), rng2());
    }
}

// Test discard advances state equivalently to calling operator() n times
TEST(SimplePcg32Test_645, DiscardEquivalentToMultipleCalls_645) {
    Catch::SimplePcg32 rng1(55);
    Catch::SimplePcg32 rng2(55);
    
    rng1.discard(10);
    for (int i = 0; i < 10; ++i) {
        rng2();
    }
    EXPECT_TRUE(rng1 == rng2);
}

// Test discard with zero does not change state
TEST(SimplePcg32Test_645, DiscardZeroNoChange_645) {
    Catch::SimplePcg32 rng1(42);
    Catch::SimplePcg32 rng2(42);
    rng1.discard(0);
    EXPECT_TRUE(rng1 == rng2);
}

// Test min and max static methods
TEST(SimplePcg32Test_645, MinMaxValues_645) {
    auto minVal = (Catch::SimplePcg32::min)();
    auto maxVal = (Catch::SimplePcg32::max)();
    EXPECT_LT(minVal, maxVal);
    EXPECT_EQ(minVal, std::numeric_limits<Catch::SimplePcg32::result_type>::min());
    EXPECT_EQ(maxVal, std::numeric_limits<Catch::SimplePcg32::result_type>::max());
}

// Test equality operators
TEST(SimplePcg32Test_645, EqualityOperators_645) {
    Catch::SimplePcg32 rng1(10);
    Catch::SimplePcg32 rng2(10);
    Catch::SimplePcg32 rng3(20);
    
    EXPECT_TRUE(rng1 == rng2);
    EXPECT_FALSE(rng1 != rng2);
    EXPECT_FALSE(rng1 == rng3);
    EXPECT_TRUE(rng1 != rng3);
}

// Test that generated values are within valid range
TEST(SimplePcg32Test_645, GeneratedValuesInRange_645) {
    Catch::SimplePcg32 rng(123);
    for (int i = 0; i < 1000; ++i) {
        auto val = rng();
        EXPECT_GE(val, (Catch::SimplePcg32::min)());
        EXPECT_LE(val, (Catch::SimplePcg32::max)());
    }
}

// Test discard with large value
TEST(SimplePcg32Test_645, DiscardLargeValue_645) {
    Catch::SimplePcg32 rng1(42);
    Catch::SimplePcg32 rng2(42);
    
    rng1.discard(1000);
    for (uint64_t i = 0; i < 1000; ++i) {
        rng2();
    }
    EXPECT_TRUE(rng1 == rng2);
}

// Test seed with the default seed value
TEST(SimplePcg32Test_645, SeedWithDefaultValue_645) {
    Catch::SimplePcg32 rng1;
    Catch::SimplePcg32 rng2(999);
    rng2.seed(0xed743cc4U);
    EXPECT_TRUE(rng1 == rng2);
}
