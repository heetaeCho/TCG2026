#include <gtest/gtest.h>
#include <cstdint>
#include <set>
#include <cmath>
#include <limits>

// Include necessary Catch2 headers
#include "catch2/generators/catch_generators_random.hpp"
#include "catch2/generators/catch_generators.hpp"

using namespace Catch::Generators;

// ============================================================================
// Tests for RandomFloatingGenerator<float>
// ============================================================================

class RandomFloatingGeneratorFloatTest_1061 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(RandomFloatingGeneratorFloatTest_1061, ConstructionAndGetReturnsValueInRange_1061) {
    float a = 0.0f;
    float b = 1.0f;
    std::uint32_t seed = 12345;
    RandomFloatingGenerator<float> gen(a, b, seed);

    float value = gen.get();
    EXPECT_GE(value, a);
    EXPECT_LE(value, b);
}

TEST_F(RandomFloatingGeneratorFloatTest_1061, NextReturnsTrueAndProducesNewValue_1061) {
    float a = 0.0f;
    float b = 100.0f;
    std::uint32_t seed = 42;
    RandomFloatingGenerator<float> gen(a, b, seed);

    float first = gen.get();
    bool hasNext = gen.next();
    EXPECT_TRUE(hasNext);
    float second = gen.get();
    EXPECT_GE(second, a);
    EXPECT_LE(second, b);
}

TEST_F(RandomFloatingGeneratorFloatTest_1061, MultipleNextCallsProduceValuesInRange_1061) {
    float a = -10.0f;
    float b = 10.0f;
    std::uint32_t seed = 99;
    RandomFloatingGenerator<float> gen(a, b, seed);

    for (int i = 0; i < 100; ++i) {
        float value = gen.get();
        EXPECT_GE(value, a);
        EXPECT_LE(value, b);
        gen.next();
    }
}

TEST_F(RandomFloatingGeneratorFloatTest_1061, SameSeedProducesSameSequence_1061) {
    float a = 0.0f;
    float b = 1.0f;
    std::uint32_t seed = 54321;

    RandomFloatingGenerator<float> gen1(a, b, seed);
    RandomFloatingGenerator<float> gen2(a, b, seed);

    for (int i = 0; i < 50; ++i) {
        EXPECT_FLOAT_EQ(gen1.get(), gen2.get());
        gen1.next();
        gen2.next();
    }
}

TEST_F(RandomFloatingGeneratorFloatTest_1061, DifferentSeedsProduceDifferentSequences_1061) {
    float a = 0.0f;
    float b = 1000.0f;
    RandomFloatingGenerator<float> gen1(a, b, 1);
    RandomFloatingGenerator<float> gen2(a, b, 2);

    bool anyDifferent = false;
    for (int i = 0; i < 20; ++i) {
        if (gen1.get() != gen2.get()) {
            anyDifferent = true;
            break;
        }
        gen1.next();
        gen2.next();
    }
    EXPECT_TRUE(anyDifferent);
}

TEST_F(RandomFloatingGeneratorFloatTest_1061, EqualRangeBoundaries_1061) {
    float a = 5.0f;
    float b = 5.0f;
    std::uint32_t seed = 100;
    RandomFloatingGenerator<float> gen(a, b, seed);

    float value = gen.get();
    EXPECT_FLOAT_EQ(value, 5.0f);

    gen.next();
    value = gen.get();
    EXPECT_FLOAT_EQ(value, 5.0f);
}

TEST_F(RandomFloatingGeneratorFloatTest_1061, NegativeRange_1061) {
    float a = -100.0f;
    float b = -1.0f;
    std::uint32_t seed = 777;
    RandomFloatingGenerator<float> gen(a, b, seed);

    for (int i = 0; i < 50; ++i) {
        float value = gen.get();
        EXPECT_GE(value, a);
        EXPECT_LE(value, b);
        gen.next();
    }
}

TEST_F(RandomFloatingGeneratorFloatTest_1061, VerySmallRange_1061) {
    float a = 1.0f;
    float b = 1.0f + std::numeric_limits<float>::epsilon();
    std::uint32_t seed = 333;
    RandomFloatingGenerator<float> gen(a, b, seed);

    float value = gen.get();
    EXPECT_GE(value, a);
    EXPECT_LE(value, b);
}

// ============================================================================
// Tests for RandomFloatingGenerator<double>
// ============================================================================

class RandomFloatingGeneratorDoubleTest_1061 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(RandomFloatingGeneratorDoubleTest_1061, ConstructionAndGetReturnsValueInRange_1061) {
    double a = 0.0;
    double b = 1.0;
    std::uint32_t seed = 12345;
    RandomFloatingGenerator<double> gen(a, b, seed);

    double value = gen.get();
    EXPECT_GE(value, a);
    EXPECT_LE(value, b);
}

TEST_F(RandomFloatingGeneratorDoubleTest_1061, NextReturnsTrueAndProducesNewValue_1061) {
    double a = 0.0;
    double b = 100.0;
    std::uint32_t seed = 42;
    RandomFloatingGenerator<double> gen(a, b, seed);

    double first = gen.get();
    bool hasNext = gen.next();
    EXPECT_TRUE(hasNext);
    double second = gen.get();
    EXPECT_GE(second, a);
    EXPECT_LE(second, b);
}

TEST_F(RandomFloatingGeneratorDoubleTest_1061, MultipleNextCallsProduceValuesInRange_1061) {
    double a = -1000.0;
    double b = 1000.0;
    std::uint32_t seed = 55555;
    RandomFloatingGenerator<double> gen(a, b, seed);

    for (int i = 0; i < 200; ++i) {
        double value = gen.get();
        EXPECT_GE(value, a);
        EXPECT_LE(value, b);
        gen.next();
    }
}

TEST_F(RandomFloatingGeneratorDoubleTest_1061, SameSeedProducesSameSequence_1061) {
    double a = -50.0;
    double b = 50.0;
    std::uint32_t seed = 9999;

    RandomFloatingGenerator<double> gen1(a, b, seed);
    RandomFloatingGenerator<double> gen2(a, b, seed);

    for (int i = 0; i < 50; ++i) {
        EXPECT_DOUBLE_EQ(gen1.get(), gen2.get());
        gen1.next();
        gen2.next();
    }
}

TEST_F(RandomFloatingGeneratorDoubleTest_1061, EqualRangeBoundariesDouble_1061) {
    double a = 3.14;
    double b = 3.14;
    std::uint32_t seed = 100;
    RandomFloatingGenerator<double> gen(a, b, seed);

    double value = gen.get();
    EXPECT_DOUBLE_EQ(value, 3.14);
}

TEST_F(RandomFloatingGeneratorDoubleTest_1061, LargeRange_1061) {
    double a = -1e15;
    double b = 1e15;
    std::uint32_t seed = 42;
    RandomFloatingGenerator<double> gen(a, b, seed);

    for (int i = 0; i < 100; ++i) {
        double value = gen.get();
        EXPECT_GE(value, a);
        EXPECT_LE(value, b);
        gen.next();
    }
}

// ============================================================================
// Tests for RandomFloatingGenerator<long double>
// ============================================================================

class RandomFloatingGeneratorLongDoubleTest_1061 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(RandomFloatingGeneratorLongDoubleTest_1061, ConstructionAndGetReturnsValueInRange_1061) {
    long double a = 0.0L;
    long double b = 1.0L;
    std::uint32_t seed = 12345;
    RandomFloatingGenerator<long double> gen(a, b, seed);

    long double value = gen.get();
    EXPECT_GE(value, a);
    EXPECT_LE(value, b);
}

TEST_F(RandomFloatingGeneratorLongDoubleTest_1061, NextReturnsTrueAndProducesNewValue_1061) {
    long double a = 0.0L;
    long double b = 100.0L;
    std::uint32_t seed = 42;
    RandomFloatingGenerator<long double> gen(a, b, seed);

    long double first = gen.get();
    bool hasNext = gen.next();
    EXPECT_TRUE(hasNext);
    long double second = gen.get();
    EXPECT_GE(second, a);
    EXPECT_LE(second, b);
}

TEST_F(RandomFloatingGeneratorLongDoubleTest_1061, MultipleNextCallsProduceValuesInRange_1061) {
    long double a = -500.0L;
    long double b = 500.0L;
    std::uint32_t seed = 7777;
    RandomFloatingGenerator<long double> gen(a, b, seed);

    for (int i = 0; i < 100; ++i) {
        long double value = gen.get();
        EXPECT_GE(value, a);
        EXPECT_LE(value, b);
        gen.next();
    }
}

TEST_F(RandomFloatingGeneratorLongDoubleTest_1061, SameSeedProducesSameSequenceLongDouble_1061) {
    long double a = 0.0L;
    long double b = 1.0L;
    std::uint32_t seed = 54321;

    RandomFloatingGenerator<long double> gen1(a, b, seed);
    RandomFloatingGenerator<long double> gen2(a, b, seed);

    for (int i = 0; i < 50; ++i) {
        EXPECT_EQ(gen1.get(), gen2.get());
        gen1.next();
        gen2.next();
    }
}

TEST_F(RandomFloatingGeneratorLongDoubleTest_1061, DifferentSeedsProduceDifferentSequencesLongDouble_1061) {
    long double a = 0.0L;
    long double b = 1000.0L;
    RandomFloatingGenerator<long double> gen1(a, b, 1);
    RandomFloatingGenerator<long double> gen2(a, b, 2);

    bool anyDifferent = false;
    for (int i = 0; i < 20; ++i) {
        if (gen1.get() != gen2.get()) {
            anyDifferent = true;
            break;
        }
        gen1.next();
        gen2.next();
    }
    EXPECT_TRUE(anyDifferent);
}

TEST_F(RandomFloatingGeneratorLongDoubleTest_1061, EqualRangeBoundariesLongDouble_1061) {
    long double a = 2.718L;
    long double b = 2.718L;
    std::uint32_t seed = 100;
    RandomFloatingGenerator<long double> gen(a, b, seed);

    long double value = gen.get();
    EXPECT_DOUBLE_EQ(static_cast<double>(value), static_cast<double>(2.718L));
}

TEST_F(RandomFloatingGeneratorLongDoubleTest_1061, NegativeRangeLongDouble_1061) {
    long double a = -1000.0L;
    long double b = -0.001L;
    std::uint32_t seed = 888;
    RandomFloatingGenerator<long double> gen(a, b, seed);

    for (int i = 0; i < 50; ++i) {
        long double value = gen.get();
        EXPECT_GE(value, a);
        EXPECT_LE(value, b);
        gen.next();
    }
}

TEST_F(RandomFloatingGeneratorLongDoubleTest_1061, DestructionDoesNotCrash_1061) {
    // Simply ensure that creating and destroying a long double generator doesn't crash
    {
        RandomFloatingGenerator<long double> gen(0.0L, 1.0L, 42);
        gen.get();
        gen.next();
    }
    SUCCEED();
}

// ============================================================================
// Additional edge case tests
// ============================================================================

class RandomFloatingGeneratorEdgeCases_1061 : public ::testing::Test {};

TEST_F(RandomFloatingGeneratorEdgeCases_1061, ZeroSeed_1061) {
    RandomFloatingGenerator<double> gen(0.0, 1.0, 0);
    double value = gen.get();
    EXPECT_GE(value, 0.0);
    EXPECT_LE(value, 1.0);
}

TEST_F(RandomFloatingGeneratorEdgeCases_1061, MaxSeed_1061) {
    RandomFloatingGenerator<double> gen(0.0, 1.0, std::numeric_limits<std::uint32_t>::max());
    double value = gen.get();
    EXPECT_GE(value, 0.0);
    EXPECT_LE(value, 1.0);
}

TEST_F(RandomFloatingGeneratorEdgeCases_1061, GetWithoutNextReturnsConsistentValue_1061) {
    RandomFloatingGenerator<double> gen(0.0, 100.0, 42);
    double first = gen.get();
    double second = gen.get();
    EXPECT_DOUBLE_EQ(first, second);
}

TEST_F(RandomFloatingGeneratorEdgeCases_1061, ManyIterationsStayInRange_1061) {
    double a = 0.0;
    double b = 1.0;
    RandomFloatingGenerator<double> gen(a, b, 12345);

    for (int i = 0; i < 10000; ++i) {
        double value = gen.get();
        EXPECT_GE(value, a) << "Value out of range at iteration " << i;
        EXPECT_LE(value, b) << "Value out of range at iteration " << i;
        gen.next();
    }
}

TEST_F(RandomFloatingGeneratorEdgeCases_1061, ProducesVariety_1061) {
    // Test that the generator produces at least some variety of values
    RandomFloatingGenerator<double> gen(0.0, 1000.0, 42);
    std::set<double> values;
    for (int i = 0; i < 100; ++i) {
        values.insert(gen.get());
        gen.next();
    }
    // We expect many distinct values from 100 iterations
    EXPECT_GT(values.size(), 50u);
}

TEST_F(RandomFloatingGeneratorEdgeCases_1061, FloatSmallNegativeToPositiveRange_1061) {
    float a = -0.001f;
    float b = 0.001f;
    RandomFloatingGenerator<float> gen(a, b, 42);

    for (int i = 0; i < 100; ++i) {
        float value = gen.get();
        EXPECT_GE(value, a);
        EXPECT_LE(value, b);
        gen.next();
    }
}
