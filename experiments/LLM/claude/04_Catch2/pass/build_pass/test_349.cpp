#include <gtest/gtest.h>
#include <cstdint>
#include <set>
#include <limits>

// Include the header under test
#include "catch2/generators/catch_generators_random.hpp"

using namespace Catch::Generators;

// Test that RandomIntegerGenerator can be constructed and get() returns a value within range
TEST(RandomIntegerGeneratorTest_349, GetReturnsValueWithinRange_349) {
    RandomIntegerGenerator<int> gen(1, 10, 12345);
    int value = gen.get();
    EXPECT_GE(value, 1);
    EXPECT_LE(value, 10);
}

// Test that next() returns true (generator can produce more values)
TEST(RandomIntegerGeneratorTest_349, NextReturnsTrue_349) {
    RandomIntegerGenerator<int> gen(1, 100, 42);
    bool result = gen.next();
    EXPECT_TRUE(result);
}

// Test that after calling next(), get() still returns a value in range
TEST(RandomIntegerGeneratorTest_349, GetAfterNextReturnsValueWithinRange_349) {
    RandomIntegerGenerator<int> gen(0, 50, 99);
    for (int i = 0; i < 20; ++i) {
        int value = gen.get();
        EXPECT_GE(value, 0);
        EXPECT_LE(value, 50);
        gen.next();
    }
}

// Test with a single-element range (a == b)
TEST(RandomIntegerGeneratorTest_349, SingleElementRange_349) {
    RandomIntegerGenerator<int> gen(7, 7, 123);
    EXPECT_EQ(gen.get(), 7);
    gen.next();
    EXPECT_EQ(gen.get(), 7);
    gen.next();
    EXPECT_EQ(gen.get(), 7);
}

// Test with negative range
TEST(RandomIntegerGeneratorTest_349, NegativeRange_349) {
    RandomIntegerGenerator<int> gen(-100, -1, 555);
    for (int i = 0; i < 20; ++i) {
        int value = gen.get();
        EXPECT_GE(value, -100);
        EXPECT_LE(value, -1);
        gen.next();
    }
}

// Test with range spanning negative to positive
TEST(RandomIntegerGeneratorTest_349, NegativeToPositiveRange_349) {
    RandomIntegerGenerator<int> gen(-50, 50, 777);
    for (int i = 0; i < 30; ++i) {
        int value = gen.get();
        EXPECT_GE(value, -50);
        EXPECT_LE(value, 50);
        gen.next();
    }
}

// Test that same seed produces same sequence
TEST(RandomIntegerGeneratorTest_349, SameSeedSameSequence_349) {
    RandomIntegerGenerator<int> gen1(1, 1000, 42);
    RandomIntegerGenerator<int> gen2(1, 1000, 42);

    for (int i = 0; i < 50; ++i) {
        EXPECT_EQ(gen1.get(), gen2.get());
        gen1.next();
        gen2.next();
    }
}

// Test that different seeds produce different sequences (with high probability)
TEST(RandomIntegerGeneratorTest_349, DifferentSeedDifferentSequence_349) {
    RandomIntegerGenerator<int> gen1(1, 1000000, 42);
    RandomIntegerGenerator<int> gen2(1, 1000000, 99);

    bool at_least_one_different = false;
    for (int i = 0; i < 20; ++i) {
        if (gen1.get() != gen2.get()) {
            at_least_one_different = true;
            break;
        }
        gen1.next();
        gen2.next();
    }
    EXPECT_TRUE(at_least_one_different);
}

// Test with unsigned integer type
TEST(RandomIntegerGeneratorTest_349, UnsignedIntType_349) {
    RandomIntegerGenerator<unsigned int> gen(0, 100, 12345);
    for (int i = 0; i < 20; ++i) {
        unsigned int value = gen.get();
        EXPECT_GE(value, 0u);
        EXPECT_LE(value, 100u);
        gen.next();
    }
}

// Test with int64_t
TEST(RandomIntegerGeneratorTest_349, Int64Type_349) {
    RandomIntegerGenerator<std::int64_t> gen(-1000000LL, 1000000LL, 54321);
    for (int i = 0; i < 20; ++i) {
        std::int64_t value = gen.get();
        EXPECT_GE(value, -1000000LL);
        EXPECT_LE(value, 1000000LL);
        gen.next();
    }
}

// Test with short type
TEST(RandomIntegerGeneratorTest_349, ShortType_349) {
    RandomIntegerGenerator<short> gen(-100, 100, 111);
    for (int i = 0; i < 20; ++i) {
        short value = gen.get();
        EXPECT_GE(value, -100);
        EXPECT_LE(value, 100);
        gen.next();
    }
}

// Test that get() is idempotent (calling multiple times without next() returns same value)
TEST(RandomIntegerGeneratorTest_349, GetIsIdempotent_349) {
    RandomIntegerGenerator<int> gen(1, 100, 42);
    int first_call = gen.get();
    int second_call = gen.get();
    int third_call = gen.get();
    EXPECT_EQ(first_call, second_call);
    EXPECT_EQ(second_call, third_call);
}

// Test that calling next() many times doesn't crash and values stay in range
TEST(RandomIntegerGeneratorTest_349, ManyNextCalls_349) {
    RandomIntegerGenerator<int> gen(0, 10, 42);
    for (int i = 0; i < 1000; ++i) {
        int value = gen.get();
        EXPECT_GE(value, 0);
        EXPECT_LE(value, 10);
        gen.next();
    }
}

// Test that the generator produces some variety of values
TEST(RandomIntegerGeneratorTest_349, ProducesVariety_349) {
    RandomIntegerGenerator<int> gen(1, 100, 42);
    std::set<int> seen;
    for (int i = 0; i < 100; ++i) {
        seen.insert(gen.get());
        gen.next();
    }
    // With range 1..100 and 100 draws, we should see more than 1 distinct value
    EXPECT_GT(seen.size(), 1u);
}

// Test boundary: range (0, 0)
TEST(RandomIntegerGeneratorTest_349, ZeroRange_349) {
    RandomIntegerGenerator<int> gen(0, 0, 42);
    EXPECT_EQ(gen.get(), 0);
    gen.next();
    EXPECT_EQ(gen.get(), 0);
}

// Test with uint32_t seed of 0
TEST(RandomIntegerGeneratorTest_349, ZeroSeed_349) {
    RandomIntegerGenerator<int> gen(1, 100, 0);
    int value = gen.get();
    EXPECT_GE(value, 1);
    EXPECT_LE(value, 100);
}

// Test with max uint32_t seed
TEST(RandomIntegerGeneratorTest_349, MaxSeed_349) {
    RandomIntegerGenerator<int> gen(1, 100, std::numeric_limits<std::uint32_t>::max());
    int value = gen.get();
    EXPECT_GE(value, 1);
    EXPECT_LE(value, 100);
}

// Test with a == b for various values
TEST(RandomIntegerGeneratorTest_349, SingleValueNegative_349) {
    RandomIntegerGenerator<int> gen(-42, -42, 100);
    EXPECT_EQ(gen.get(), -42);
    gen.next();
    EXPECT_EQ(gen.get(), -42);
}

// Test range of size 2
TEST(RandomIntegerGeneratorTest_349, RangeOfTwo_349) {
    RandomIntegerGenerator<int> gen(0, 1, 42);
    std::set<int> seen;
    for (int i = 0; i < 100; ++i) {
        int val = gen.get();
        EXPECT_GE(val, 0);
        EXPECT_LE(val, 1);
        seen.insert(val);
        gen.next();
    }
    // Should see both 0 and 1 over 100 iterations
    EXPECT_EQ(seen.size(), 2u);
}
