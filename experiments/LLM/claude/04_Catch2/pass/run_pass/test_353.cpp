#include <gtest/gtest.h>
#include "catch2/generators/catch_generators_random.hpp"

using namespace Catch::Generators;

// Test that RandomFloatingGenerator<float> produces values within range
TEST(RandomFloatingGeneratorTest_353, FloatGeneratesWithinRange_353) {
    float low = 0.0f;
    float high = 1.0f;
    std::uint32_t seed = 12345;
    
    RandomFloatingGenerator<float> gen(low, high, seed);
    
    // Check initial value
    float val = gen.get();
    EXPECT_GE(val, low);
    EXPECT_LE(val, high);
    
    // Check subsequent values
    for (int i = 0; i < 100; ++i) {
        EXPECT_TRUE(gen.next());
        val = gen.get();
        EXPECT_GE(val, low);
        EXPECT_LE(val, high);
    }
}

// Test that RandomFloatingGenerator<double> produces values within range
TEST(RandomFloatingGeneratorTest_353, DoubleGeneratesWithinRange_353) {
    double low = -10.0;
    double high = 10.0;
    std::uint32_t seed = 54321;
    
    RandomFloatingGenerator<double> gen(low, high, seed);
    
    double val = gen.get();
    EXPECT_GE(val, low);
    EXPECT_LE(val, high);
    
    for (int i = 0; i < 100; ++i) {
        EXPECT_TRUE(gen.next());
        val = gen.get();
        EXPECT_GE(val, low);
        EXPECT_LE(val, high);
    }
}

// Test that RandomFloatingGenerator<long double> produces values within range
TEST(RandomFloatingGeneratorTest_353, LongDoubleGeneratesWithinRange_353) {
    long double low = -100.0L;
    long double high = 100.0L;
    std::uint32_t seed = 99999;
    
    RandomFloatingGenerator<long double> gen(low, high, seed);
    
    long double val = gen.get();
    EXPECT_GE(val, low);
    EXPECT_LE(val, high);
    
    for (int i = 0; i < 100; ++i) {
        EXPECT_TRUE(gen.next());
        val = gen.get();
        EXPECT_GE(val, low);
        EXPECT_LE(val, high);
    }
}

// Test that next() always returns true
TEST(RandomFloatingGeneratorTest_353, NextAlwaysReturnsTrue_353) {
    RandomFloatingGenerator<float> gen(0.0f, 1.0f, 42);
    
    for (int i = 0; i < 1000; ++i) {
        EXPECT_TRUE(gen.next());
    }
}

// Test that next() always returns true for long double specialization
TEST(RandomFloatingGeneratorTest_353, LongDoubleNextAlwaysReturnsTrue_353) {
    RandomFloatingGenerator<long double> gen(0.0L, 1.0L, 42);
    
    for (int i = 0; i < 1000; ++i) {
        EXPECT_TRUE(gen.next());
    }
}

// Test deterministic behavior: same seed produces same sequence
TEST(RandomFloatingGeneratorTest_353, SameSeedProducesSameSequenceFloat_353) {
    std::uint32_t seed = 12345;
    
    RandomFloatingGenerator<float> gen1(0.0f, 100.0f, seed);
    RandomFloatingGenerator<float> gen2(0.0f, 100.0f, seed);
    
    EXPECT_FLOAT_EQ(gen1.get(), gen2.get());
    
    for (int i = 0; i < 50; ++i) {
        gen1.next();
        gen2.next();
        EXPECT_FLOAT_EQ(gen1.get(), gen2.get());
    }
}

// Test deterministic behavior for double
TEST(RandomFloatingGeneratorTest_353, SameSeedProducesSameSequenceDouble_353) {
    std::uint32_t seed = 67890;
    
    RandomFloatingGenerator<double> gen1(-50.0, 50.0, seed);
    RandomFloatingGenerator<double> gen2(-50.0, 50.0, seed);
    
    EXPECT_DOUBLE_EQ(gen1.get(), gen2.get());
    
    for (int i = 0; i < 50; ++i) {
        gen1.next();
        gen2.next();
        EXPECT_DOUBLE_EQ(gen1.get(), gen2.get());
    }
}

// Test deterministic behavior for long double
TEST(RandomFloatingGeneratorTest_353, SameSeedProducesSameSequenceLongDouble_353) {
    std::uint32_t seed = 11111;
    
    RandomFloatingGenerator<long double> gen1(0.0L, 1.0L, seed);
    RandomFloatingGenerator<long double> gen2(0.0L, 1.0L, seed);
    
    EXPECT_DOUBLE_EQ(static_cast<double>(gen1.get()), static_cast<double>(gen2.get()));
    
    for (int i = 0; i < 50; ++i) {
        gen1.next();
        gen2.next();
        EXPECT_DOUBLE_EQ(static_cast<double>(gen1.get()), static_cast<double>(gen2.get()));
    }
}

// Test different seeds produce different sequences
TEST(RandomFloatingGeneratorTest_353, DifferentSeedsProduceDifferentSequences_353) {
    RandomFloatingGenerator<double> gen1(0.0, 1000.0, 1);
    RandomFloatingGenerator<double> gen2(0.0, 1000.0, 2);
    
    // It's extremely unlikely that two different seeds produce the same initial value
    // but to be safe, check a few values
    bool found_different = false;
    if (gen1.get() != gen2.get()) {
        found_different = true;
    }
    for (int i = 0; i < 10 && !found_different; ++i) {
        gen1.next();
        gen2.next();
        if (gen1.get() != gen2.get()) {
            found_different = true;
        }
    }
    EXPECT_TRUE(found_different);
}

// Test narrow range
TEST(RandomFloatingGeneratorTest_353, NarrowRangeFloat_353) {
    float low = 5.0f;
    float high = 5.0001f;
    
    RandomFloatingGenerator<float> gen(low, high, 42);
    
    float val = gen.get();
    EXPECT_GE(val, low);
    EXPECT_LE(val, high);
    
    for (int i = 0; i < 50; ++i) {
        gen.next();
        val = gen.get();
        EXPECT_GE(val, low);
        EXPECT_LE(val, high);
    }
}

// Test with negative range
TEST(RandomFloatingGeneratorTest_353, NegativeRangeDouble_353) {
    double low = -100.0;
    double high = -1.0;
    
    RandomFloatingGenerator<double> gen(low, high, 777);
    
    double val = gen.get();
    EXPECT_GE(val, low);
    EXPECT_LE(val, high);
    
    for (int i = 0; i < 100; ++i) {
        gen.next();
        val = gen.get();
        EXPECT_GE(val, low);
        EXPECT_LE(val, high);
    }
}

// Test with large range for long double
TEST(RandomFloatingGeneratorTest_353, LargeRangeLongDouble_353) {
    long double low = -1e18L;
    long double high = 1e18L;
    
    RandomFloatingGenerator<long double> gen(low, high, 333);
    
    long double val = gen.get();
    EXPECT_GE(val, low);
    EXPECT_LE(val, high);
    
    for (int i = 0; i < 100; ++i) {
        gen.next();
        val = gen.get();
        EXPECT_GE(val, low);
        EXPECT_LE(val, high);
    }
}

// Test get() returns const reference (consistency check - calling get multiple times without next)
TEST(RandomFloatingGeneratorTest_353, GetWithoutNextReturnsSameValue_353) {
    RandomFloatingGenerator<double> gen(0.0, 100.0, 42);
    
    double val1 = gen.get();
    double val2 = gen.get();
    EXPECT_DOUBLE_EQ(val1, val2);
}

// Test get() returns const reference for long double
TEST(RandomFloatingGeneratorTest_353, LongDoubleGetWithoutNextReturnsSameValue_353) {
    RandomFloatingGenerator<long double> gen(0.0L, 100.0L, 42);
    
    long double val1 = gen.get();
    long double val2 = gen.get();
    EXPECT_DOUBLE_EQ(static_cast<double>(val1), static_cast<double>(val2));
}

// Test that calling next changes the value (statistically very likely for a wide range)
TEST(RandomFloatingGeneratorTest_353, NextChangesValue_353) {
    RandomFloatingGenerator<double> gen(0.0, 1e10, 42);
    
    double initial = gen.get();
    gen.next();
    double after_next = gen.get();
    
    // Extremely unlikely to get the same value in such a wide range
    EXPECT_NE(initial, after_next);
}

// Test with seed 0
TEST(RandomFloatingGeneratorTest_353, SeedZeroWorks_353) {
    RandomFloatingGenerator<float> gen(0.0f, 1.0f, 0);
    
    float val = gen.get();
    EXPECT_GE(val, 0.0f);
    EXPECT_LE(val, 1.0f);
    
    EXPECT_TRUE(gen.next());
    val = gen.get();
    EXPECT_GE(val, 0.0f);
    EXPECT_LE(val, 1.0f);
}

// Test with max uint32_t seed
TEST(RandomFloatingGeneratorTest_353, MaxSeedWorks_353) {
    RandomFloatingGenerator<double> gen(0.0, 1.0, std::numeric_limits<std::uint32_t>::max());
    
    double val = gen.get();
    EXPECT_GE(val, 0.0);
    EXPECT_LE(val, 1.0);
    
    EXPECT_TRUE(gen.next());
    val = gen.get();
    EXPECT_GE(val, 0.0);
    EXPECT_LE(val, 1.0);
}

// Test range crossing zero
TEST(RandomFloatingGeneratorTest_353, RangeCrossingZero_353) {
    RandomFloatingGenerator<float> gen(-1.0f, 1.0f, 42);
    
    bool found_positive = false;
    bool found_negative = false;
    
    float val = gen.get();
    if (val > 0) found_positive = true;
    if (val < 0) found_negative = true;
    
    for (int i = 0; i < 1000; ++i) {
        gen.next();
        val = gen.get();
        EXPECT_GE(val, -1.0f);
        EXPECT_LE(val, 1.0f);
        if (val > 0) found_positive = true;
        if (val < 0) found_negative = true;
    }
    
    // With 1000 samples in [-1, 1], we should see both positive and negative
    EXPECT_TRUE(found_positive);
    EXPECT_TRUE(found_negative);
}
