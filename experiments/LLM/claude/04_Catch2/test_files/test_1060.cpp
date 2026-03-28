#include <cstdint>
#include <set>
#include <catch2/generators/catch_generators_random.hpp>
#include <gtest/gtest.h>

using namespace Catch::Generators;

class RandomIntegerGeneratorTest_1060 : public ::testing::Test {
protected:
};

// Test that construction with valid range succeeds and get() returns a value in range
TEST_F(RandomIntegerGeneratorTest_1060, ConstructionWithValidRange_1060) {
    RandomIntegerGenerator<int> gen(1, 10, 42);
    int val = gen.get();
    EXPECT_GE(val, 1);
    EXPECT_LE(val, 10);
}

// Test that get() returns consistent value when called multiple times without next()
TEST_F(RandomIntegerGeneratorTest_1060, GetReturnsSameValueWithoutNext_1060) {
    RandomIntegerGenerator<int> gen(0, 100, 12345);
    int val1 = gen.get();
    int val2 = gen.get();
    EXPECT_EQ(val1, val2);
}

// Test that next() advances the generator and get() may return a different value
TEST_F(RandomIntegerGeneratorTest_1060, NextAdvancesGenerator_1060) {
    RandomIntegerGenerator<int> gen(0, 1000000, 99);
    int val1 = gen.get();
    gen.next();
    int val2 = gen.get();
    // With a large range and different seed steps, values are very likely different
    // but we mainly check they're in range
    EXPECT_GE(val2, 0);
    EXPECT_LE(val2, 1000000);
}

// Test that all generated values are within the specified range after multiple next() calls
TEST_F(RandomIntegerGeneratorTest_1060, AllValuesInRange_1060) {
    RandomIntegerGenerator<int> gen(-50, 50, 777);
    for (int i = 0; i < 100; ++i) {
        int val = gen.get();
        EXPECT_GE(val, -50);
        EXPECT_LE(val, 50);
        gen.next();
    }
}

// Test with single-element range (a == b)
TEST_F(RandomIntegerGeneratorTest_1060, SingleElementRange_1060) {
    RandomIntegerGenerator<int> gen(42, 42, 100);
    EXPECT_EQ(gen.get(), 42);
    gen.next();
    EXPECT_EQ(gen.get(), 42);
    gen.next();
    EXPECT_EQ(gen.get(), 42);
}

// Test determinism: same seed produces same sequence
TEST_F(RandomIntegerGeneratorTest_1060, DeterministicWithSameSeed_1060) {
    RandomIntegerGenerator<int> gen1(0, 10000, 54321);
    RandomIntegerGenerator<int> gen2(0, 10000, 54321);

    for (int i = 0; i < 50; ++i) {
        EXPECT_EQ(gen1.get(), gen2.get());
        gen1.next();
        gen2.next();
    }
}

// Test that different seeds produce different sequences
TEST_F(RandomIntegerGeneratorTest_1060, DifferentSeedsDifferentSequences_1060) {
    RandomIntegerGenerator<int> gen1(0, 1000000, 111);
    RandomIntegerGenerator<int> gen2(0, 1000000, 222);

    bool any_different = false;
    for (int i = 0; i < 20; ++i) {
        if (gen1.get() != gen2.get()) {
            any_different = true;
        }
        gen1.next();
        gen2.next();
    }
    EXPECT_TRUE(any_different);
}

// Test with unsigned integer type
TEST_F(RandomIntegerGeneratorTest_1060, UnsignedIntegerType_1060) {
    RandomIntegerGenerator<unsigned int> gen(0u, 100u, 42);
    for (int i = 0; i < 50; ++i) {
        unsigned int val = gen.get();
        EXPECT_GE(val, 0u);
        EXPECT_LE(val, 100u);
        gen.next();
    }
}

// Test with int64_t type
TEST_F(RandomIntegerGeneratorTest_1060, Int64Type_1060) {
    RandomIntegerGenerator<int64_t> gen(INT64_C(-1000000), INT64_C(1000000), 55);
    for (int i = 0; i < 50; ++i) {
        int64_t val = gen.get();
        EXPECT_GE(val, INT64_C(-1000000));
        EXPECT_LE(val, INT64_C(1000000));
        gen.next();
    }
}

// Test that next() returns bool (true means more values can be generated)
TEST_F(RandomIntegerGeneratorTest_1060, NextReturnsBool_1060) {
    RandomIntegerGenerator<int> gen(1, 100, 42);
    bool result = gen.next();
    // Random generators typically always return true (infinite generator)
    EXPECT_TRUE(result);
}

// Test boundary values of integer range
TEST_F(RandomIntegerGeneratorTest_1060, SmallRangeBoundary_1060) {
    RandomIntegerGenerator<int> gen(0, 1, 42);
    std::set<int> seen;
    for (int i = 0; i < 100; ++i) {
        int val = gen.get();
        EXPECT_GE(val, 0);
        EXPECT_LE(val, 1);
        seen.insert(val);
        gen.next();
    }
    // With 100 iterations over range [0,1], we should see both values
    EXPECT_EQ(seen.size(), 2u);
}

// Test with negative range
TEST_F(RandomIntegerGeneratorTest_1060, NegativeRange_1060) {
    RandomIntegerGenerator<int> gen(-100, -1, 42);
    for (int i = 0; i < 50; ++i) {
        int val = gen.get();
        EXPECT_GE(val, -100);
        EXPECT_LE(val, -1);
        gen.next();
    }
}

// Test that get() returns a const reference
TEST_F(RandomIntegerGeneratorTest_1060, GetReturnsConstReference_1060) {
    RandomIntegerGenerator<int> gen(0, 100, 42);
    const int& ref1 = gen.get();
    const int& ref2 = gen.get();
    // Both references should point to the same internal value
    EXPECT_EQ(&ref1, &ref2);
}

// Test with seed 0
TEST_F(RandomIntegerGeneratorTest_1060, SeedZero_1060) {
    RandomIntegerGenerator<int> gen(1, 1000, 0);
    int val = gen.get();
    EXPECT_GE(val, 1);
    EXPECT_LE(val, 1000);
}

// Test with max uint32 seed
TEST_F(RandomIntegerGeneratorTest_1060, MaxSeed_1060) {
    RandomIntegerGenerator<int> gen(1, 1000, UINT32_MAX);
    int val = gen.get();
    EXPECT_GE(val, 1);
    EXPECT_LE(val, 1000);
}

// Test that multiple next() calls continue to produce valid values
TEST_F(RandomIntegerGeneratorTest_1060, ManyNextCalls_1060) {
    RandomIntegerGenerator<int> gen(0, 255, 42);
    for (int i = 0; i < 1000; ++i) {
        EXPECT_GE(gen.get(), 0);
        EXPECT_LE(gen.get(), 255);
        bool hasMore = gen.next();
        EXPECT_TRUE(hasMore);
    }
}

// Test with short type
TEST_F(RandomIntegerGeneratorTest_1060, ShortType_1060) {
    RandomIntegerGenerator<short> gen(static_cast<short>(-100), static_cast<short>(100), 42);
    for (int i = 0; i < 50; ++i) {
        short val = gen.get();
        EXPECT_GE(val, static_cast<short>(-100));
        EXPECT_LE(val, static_cast<short>(100));
        gen.next();
    }
}
