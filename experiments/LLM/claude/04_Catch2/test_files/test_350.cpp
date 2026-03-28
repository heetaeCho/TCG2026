#include <gtest/gtest.h>
#include <cstdint>
#include <set>
#include <limits>

// Include the header under test
#include "catch2/generators/catch_generators_random.hpp"

using namespace Catch::Generators;

// Test that RandomIntegerGenerator can be constructed with valid int range
TEST(RandomIntegerGeneratorTest_350, ConstructWithValidIntRange_350) {
    RandomIntegerGenerator<int> gen(1, 10, 42);
    // Should be constructible without throwing
    int val = gen.get();
    EXPECT_GE(val, 1);
    EXPECT_LE(val, 10);
}

// Test that get() returns a value within the specified range
TEST(RandomIntegerGeneratorTest_350, GetReturnsValueInRange_350) {
    RandomIntegerGenerator<int> gen(0, 100, 12345);
    int val = gen.get();
    EXPECT_GE(val, 0);
    EXPECT_LE(val, 100);
}

// Test that next() always returns true
TEST(RandomIntegerGeneratorTest_350, NextAlwaysReturnsTrue_350) {
    RandomIntegerGenerator<int> gen(1, 100, 99);
    for (int i = 0; i < 100; ++i) {
        EXPECT_TRUE(gen.next());
    }
}

// Test that after calling next(), get() returns a value in range
TEST(RandomIntegerGeneratorTest_350, AfterNextGetReturnsValueInRange_350) {
    RandomIntegerGenerator<int> gen(10, 20, 777);
    for (int i = 0; i < 50; ++i) {
        gen.next();
        int val = gen.get();
        EXPECT_GE(val, 10);
        EXPECT_LE(val, 20);
    }
}

// Test with single value range (a == b)
TEST(RandomIntegerGeneratorTest_350, SingleValueRange_350) {
    RandomIntegerGenerator<int> gen(5, 5, 42);
    int val = gen.get();
    EXPECT_EQ(val, 5);

    gen.next();
    val = gen.get();
    EXPECT_EQ(val, 5);
}

// Test with negative range
TEST(RandomIntegerGeneratorTest_350, NegativeRange_350) {
    RandomIntegerGenerator<int> gen(-100, -1, 42);
    for (int i = 0; i < 50; ++i) {
        int val = gen.get();
        EXPECT_GE(val, -100);
        EXPECT_LE(val, -1);
        gen.next();
    }
}

// Test with range crossing zero
TEST(RandomIntegerGeneratorTest_350, RangeCrossingZero_350) {
    RandomIntegerGenerator<int> gen(-50, 50, 42);
    for (int i = 0; i < 100; ++i) {
        int val = gen.get();
        EXPECT_GE(val, -50);
        EXPECT_LE(val, 50);
        gen.next();
    }
}

// Test that different seeds produce different sequences (statistical test)
TEST(RandomIntegerGeneratorTest_350, DifferentSeedsProduceDifferentValues_350) {
    RandomIntegerGenerator<int> gen1(0, 1000000, 1);
    RandomIntegerGenerator<int> gen2(0, 1000000, 2);

    bool any_different = false;
    for (int i = 0; i < 20; ++i) {
        if (gen1.get() != gen2.get()) {
            any_different = true;
            break;
        }
        gen1.next();
        gen2.next();
    }
    EXPECT_TRUE(any_different);
}

// Test that same seed produces same sequence (deterministic)
TEST(RandomIntegerGeneratorTest_350, SameSeedProducesSameSequence_350) {
    RandomIntegerGenerator<int> gen1(0, 1000, 42);
    RandomIntegerGenerator<int> gen2(0, 1000, 42);

    for (int i = 0; i < 50; ++i) {
        EXPECT_EQ(gen1.get(), gen2.get());
        gen1.next();
        gen2.next();
    }
}

// Test with unsigned integer type
TEST(RandomIntegerGeneratorTest_350, UnsignedIntType_350) {
    RandomIntegerGenerator<unsigned int> gen(0u, 100u, 42);
    for (int i = 0; i < 50; ++i) {
        unsigned int val = gen.get();
        EXPECT_GE(val, 0u);
        EXPECT_LE(val, 100u);
        gen.next();
    }
}

// Test with int64_t type
TEST(RandomIntegerGeneratorTest_350, Int64Type_350) {
    RandomIntegerGenerator<int64_t> gen(0, 1000000LL, 42);
    for (int i = 0; i < 50; ++i) {
        int64_t val = gen.get();
        EXPECT_GE(val, 0);
        EXPECT_LE(val, 1000000LL);
        gen.next();
    }
}

// Test with short type
TEST(RandomIntegerGeneratorTest_350, ShortType_350) {
    RandomIntegerGenerator<short> gen(static_cast<short>(-100), static_cast<short>(100), 42);
    for (int i = 0; i < 50; ++i) {
        short val = gen.get();
        EXPECT_GE(val, -100);
        EXPECT_LE(val, 100);
        gen.next();
    }
}

// Test that get() is const and returns const reference
TEST(RandomIntegerGeneratorTest_350, GetReturnsConstReference_350) {
    RandomIntegerGenerator<int> gen(1, 10, 42);
    const int& ref1 = gen.get();
    const int& ref2 = gen.get();
    // Multiple calls to get() without next() should return same value
    EXPECT_EQ(ref1, ref2);
}

// Test multiple calls to get() without next() return same value
TEST(RandomIntegerGeneratorTest_350, GetWithoutNextReturnsSameValue_350) {
    RandomIntegerGenerator<int> gen(1, 1000, 42);
    int val1 = gen.get();
    int val2 = gen.get();
    int val3 = gen.get();
    EXPECT_EQ(val1, val2);
    EXPECT_EQ(val2, val3);
}

// Test that next() changes the value (statistical - over many iterations, at least one should differ)
TEST(RandomIntegerGeneratorTest_350, NextChangesValue_350) {
    RandomIntegerGenerator<int> gen(0, 1000000, 42);
    int initial = gen.get();
    bool changed = false;
    for (int i = 0; i < 100; ++i) {
        gen.next();
        if (gen.get() != initial) {
            changed = true;
            break;
        }
    }
    EXPECT_TRUE(changed);
}

// Test with large range
TEST(RandomIntegerGeneratorTest_350, LargeRange_350) {
    RandomIntegerGenerator<int> gen(std::numeric_limits<int>::min(), std::numeric_limits<int>::max(), 42);
    // Should not crash, and get() should return valid int
    int val = gen.get();
    (void)val; // Just ensure it doesn't crash
    gen.next();
    val = gen.get();
    (void)val;
}

// Test distribution coverage - values should not all be the same over many iterations
TEST(RandomIntegerGeneratorTest_350, DistributionCoverage_350) {
    RandomIntegerGenerator<int> gen(1, 10, 42);
    std::set<int> seen;
    for (int i = 0; i < 1000; ++i) {
        seen.insert(gen.get());
        gen.next();
    }
    // With range [1,10] and 1000 iterations, we should see multiple distinct values
    EXPECT_GT(seen.size(), 1u);
}

// Test with uint32_t seed of 0
TEST(RandomIntegerGeneratorTest_350, ZeroSeed_350) {
    RandomIntegerGenerator<int> gen(1, 100, 0);
    int val = gen.get();
    EXPECT_GE(val, 1);
    EXPECT_LE(val, 100);
    EXPECT_TRUE(gen.next());
}

// Test with max uint32_t seed
TEST(RandomIntegerGeneratorTest_350, MaxSeed_350) {
    RandomIntegerGenerator<int> gen(1, 100, std::numeric_limits<std::uint32_t>::max());
    int val = gen.get();
    EXPECT_GE(val, 1);
    EXPECT_LE(val, 100);
    EXPECT_TRUE(gen.next());
}
