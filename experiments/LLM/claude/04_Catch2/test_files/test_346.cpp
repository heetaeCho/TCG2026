#include <gtest/gtest.h>
#include <cmath>
#include <set>
#include <limits>

// Include the header under test
#include "catch2/generators/catch_generators_random.hpp"

// Test fixture for RandomFloatingGenerator with float type
class RandomFloatingGeneratorFloatTest_346 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test fixture for RandomFloatingGenerator with double type
class RandomFloatingGeneratorDoubleTest_346 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test fixture for RandomFloatingGenerator with long double type
class RandomFloatingGeneratorLongDoubleTest_346 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// ============================================================
// Float tests
// ============================================================

TEST_F(RandomFloatingGeneratorFloatTest_346, GetReturnsValueInRange_346) {
    float a = 0.0f, b = 1.0f;
    std::uint32_t seed = 12345;
    Catch::Generators::RandomFloatingGenerator<float> gen(a, b, seed);

    float val = gen.get();
    EXPECT_GE(val, a);
    EXPECT_LE(val, b);
}

TEST_F(RandomFloatingGeneratorFloatTest_346, NextReturnsTrueAndProducesNewValue_346) {
    float a = 0.0f, b = 100.0f;
    std::uint32_t seed = 42;
    Catch::Generators::RandomFloatingGenerator<float> gen(a, b, seed);

    float first = gen.get();
    bool hasNext = gen.next();
    EXPECT_TRUE(hasNext);
    float second = gen.get();
    EXPECT_GE(second, a);
    EXPECT_LE(second, b);
}

TEST_F(RandomFloatingGeneratorFloatTest_346, MultipleNextCallsProduceValuesInRange_346) {
    float a = -50.0f, b = 50.0f;
    std::uint32_t seed = 99;
    Catch::Generators::RandomFloatingGenerator<float> gen(a, b, seed);

    for (int i = 0; i < 100; ++i) {
        float val = gen.get();
        EXPECT_GE(val, a);
        EXPECT_LE(val, b);
        gen.next();
    }
}

TEST_F(RandomFloatingGeneratorFloatTest_346, SameSeedProducesSameSequence_346) {
    float a = 0.0f, b = 1.0f;
    std::uint32_t seed = 777;

    Catch::Generators::RandomFloatingGenerator<float> gen1(a, b, seed);
    Catch::Generators::RandomFloatingGenerator<float> gen2(a, b, seed);

    for (int i = 0; i < 50; ++i) {
        EXPECT_FLOAT_EQ(gen1.get(), gen2.get());
        gen1.next();
        gen2.next();
    }
}

TEST_F(RandomFloatingGeneratorFloatTest_346, DifferentSeedsProduceDifferentSequences_346) {
    float a = 0.0f, b = 1000.0f;
    Catch::Generators::RandomFloatingGenerator<float> gen1(a, b, 1);
    Catch::Generators::RandomFloatingGenerator<float> gen2(a, b, 2);

    bool anyDifferent = false;
    for (int i = 0; i < 50; ++i) {
        if (gen1.get() != gen2.get()) {
            anyDifferent = true;
        }
        gen1.next();
        gen2.next();
    }
    EXPECT_TRUE(anyDifferent);
}

TEST_F(RandomFloatingGeneratorFloatTest_346, NarrowRangeProducesValuesInRange_346) {
    float a = 1.0f, b = 1.0f + std::numeric_limits<float>::epsilon();
    std::uint32_t seed = 123;
    Catch::Generators::RandomFloatingGenerator<float> gen(a, b, seed);

    for (int i = 0; i < 10; ++i) {
        float val = gen.get();
        EXPECT_GE(val, a);
        EXPECT_LE(val, b);
        gen.next();
    }
}

TEST_F(RandomFloatingGeneratorFloatTest_346, NegativeRangeProducesValuesInRange_346) {
    float a = -100.0f, b = -1.0f;
    std::uint32_t seed = 500;
    Catch::Generators::RandomFloatingGenerator<float> gen(a, b, seed);

    for (int i = 0; i < 50; ++i) {
        float val = gen.get();
        EXPECT_GE(val, a);
        EXPECT_LE(val, b);
        gen.next();
    }
}

TEST_F(RandomFloatingGeneratorFloatTest_346, GetWithoutNextReturnsConsistentValue_346) {
    float a = 0.0f, b = 10.0f;
    std::uint32_t seed = 321;
    Catch::Generators::RandomFloatingGenerator<float> gen(a, b, seed);

    float val1 = gen.get();
    float val2 = gen.get();
    EXPECT_FLOAT_EQ(val1, val2);
}

// ============================================================
// Double tests
// ============================================================

TEST_F(RandomFloatingGeneratorDoubleTest_346, GetReturnsValueInRange_346) {
    double a = 0.0, b = 1.0;
    std::uint32_t seed = 12345;
    Catch::Generators::RandomFloatingGenerator<double> gen(a, b, seed);

    double val = gen.get();
    EXPECT_GE(val, a);
    EXPECT_LE(val, b);
}

TEST_F(RandomFloatingGeneratorDoubleTest_346, NextReturnsTrueAndProducesNewValue_346) {
    double a = 0.0, b = 100.0;
    std::uint32_t seed = 42;
    Catch::Generators::RandomFloatingGenerator<double> gen(a, b, seed);

    double first = gen.get();
    bool hasNext = gen.next();
    EXPECT_TRUE(hasNext);
    double second = gen.get();
    EXPECT_GE(second, a);
    EXPECT_LE(second, b);
}

TEST_F(RandomFloatingGeneratorDoubleTest_346, MultipleNextCallsProduceValuesInRange_346) {
    double a = -1000.0, b = 1000.0;
    std::uint32_t seed = 55;
    Catch::Generators::RandomFloatingGenerator<double> gen(a, b, seed);

    for (int i = 0; i < 100; ++i) {
        double val = gen.get();
        EXPECT_GE(val, a);
        EXPECT_LE(val, b);
        gen.next();
    }
}

TEST_F(RandomFloatingGeneratorDoubleTest_346, SameSeedProducesSameSequence_346) {
    double a = -10.0, b = 10.0;
    std::uint32_t seed = 888;

    Catch::Generators::RandomFloatingGenerator<double> gen1(a, b, seed);
    Catch::Generators::RandomFloatingGenerator<double> gen2(a, b, seed);

    for (int i = 0; i < 50; ++i) {
        EXPECT_DOUBLE_EQ(gen1.get(), gen2.get());
        gen1.next();
        gen2.next();
    }
}

TEST_F(RandomFloatingGeneratorDoubleTest_346, GetWithoutNextReturnsConsistentValue_346) {
    double a = 0.0, b = 10.0;
    std::uint32_t seed = 321;
    Catch::Generators::RandomFloatingGenerator<double> gen(a, b, seed);

    double val1 = gen.get();
    double val2 = gen.get();
    EXPECT_DOUBLE_EQ(val1, val2);
}

TEST_F(RandomFloatingGeneratorDoubleTest_346, LargeRangeProducesValuesInRange_346) {
    double a = -1e15, b = 1e15;
    std::uint32_t seed = 999;
    Catch::Generators::RandomFloatingGenerator<double> gen(a, b, seed);

    for (int i = 0; i < 100; ++i) {
        double val = gen.get();
        EXPECT_GE(val, a);
        EXPECT_LE(val, b);
        gen.next();
    }
}

// ============================================================
// Long double tests
// ============================================================

TEST_F(RandomFloatingGeneratorLongDoubleTest_346, GetReturnsValueInRange_346) {
    long double a = 0.0L, b = 1.0L;
    std::uint32_t seed = 12345;
    Catch::Generators::RandomFloatingGenerator<long double> gen(a, b, seed);

    long double val = gen.get();
    EXPECT_GE(val, a);
    EXPECT_LE(val, b);
}

TEST_F(RandomFloatingGeneratorLongDoubleTest_346, NextReturnsTrueAndProducesNewValue_346) {
    long double a = 0.0L, b = 100.0L;
    std::uint32_t seed = 42;
    Catch::Generators::RandomFloatingGenerator<long double> gen(a, b, seed);

    long double first = gen.get();
    bool hasNext = gen.next();
    EXPECT_TRUE(hasNext);
    long double second = gen.get();
    EXPECT_GE(second, a);
    EXPECT_LE(second, b);
}

TEST_F(RandomFloatingGeneratorLongDoubleTest_346, MultipleNextCallsProduceValuesInRange_346) {
    long double a = -500.0L, b = 500.0L;
    std::uint32_t seed = 77;
    Catch::Generators::RandomFloatingGenerator<long double> gen(a, b, seed);

    for (int i = 0; i < 100; ++i) {
        long double val = gen.get();
        EXPECT_GE(val, a);
        EXPECT_LE(val, b);
        gen.next();
    }
}

TEST_F(RandomFloatingGeneratorLongDoubleTest_346, SameSeedProducesSameSequence_346) {
    long double a = -10.0L, b = 10.0L;
    std::uint32_t seed = 444;

    Catch::Generators::RandomFloatingGenerator<long double> gen1(a, b, seed);
    Catch::Generators::RandomFloatingGenerator<long double> gen2(a, b, seed);

    for (int i = 0; i < 50; ++i) {
        EXPECT_EQ(gen1.get(), gen2.get());
        gen1.next();
        gen2.next();
    }
}

TEST_F(RandomFloatingGeneratorLongDoubleTest_346, GetWithoutNextReturnsConsistentValue_346) {
    long double a = 0.0L, b = 10.0L;
    std::uint32_t seed = 321;
    Catch::Generators::RandomFloatingGenerator<long double> gen(a, b, seed);

    long double val1 = gen.get();
    long double val2 = gen.get();
    EXPECT_EQ(val1, val2);
}

TEST_F(RandomFloatingGeneratorLongDoubleTest_346, DestructorDoesNotCrash_346) {
    // Ensure that the destructor of the long double specialization works correctly
    {
        long double a = 0.0L, b = 1.0L;
        std::uint32_t seed = 123;
        Catch::Generators::RandomFloatingGenerator<long double> gen(a, b, seed);
        gen.get();
        gen.next();
    }
    // If we reach here, the destructor didn't crash
    SUCCEED();
}

TEST_F(RandomFloatingGeneratorLongDoubleTest_346, DifferentSeedsProduceDifferentSequences_346) {
    long double a = 0.0L, b = 1000.0L;
    Catch::Generators::RandomFloatingGenerator<long double> gen1(a, b, 1);
    Catch::Generators::RandomFloatingGenerator<long double> gen2(a, b, 2);

    bool anyDifferent = false;
    for (int i = 0; i < 50; ++i) {
        if (gen1.get() != gen2.get()) {
            anyDifferent = true;
        }
        gen1.next();
        gen2.next();
    }
    EXPECT_TRUE(anyDifferent);
}

// ============================================================
// Variety / distribution tests
// ============================================================

TEST_F(RandomFloatingGeneratorDoubleTest_346, ProducesVarietyOfValues_346) {
    double a = 0.0, b = 1000.0;
    std::uint32_t seed = 54321;
    Catch::Generators::RandomFloatingGenerator<double> gen(a, b, seed);

    std::set<double> values;
    for (int i = 0; i < 100; ++i) {
        values.insert(gen.get());
        gen.next();
    }
    // We expect at least some variety
    EXPECT_GT(values.size(), 1u);
}

TEST_F(RandomFloatingGeneratorFloatTest_346, ZeroWidthRangeProducesSameValue_346) {
    float a = 5.0f, b = 5.0f;
    std::uint32_t seed = 100;
    Catch::Generators::RandomFloatingGenerator<float> gen(a, b, seed);

    for (int i = 0; i < 10; ++i) {
        float val = gen.get();
        EXPECT_FLOAT_EQ(val, 5.0f);
        gen.next();
    }
}

TEST_F(RandomFloatingGeneratorDoubleTest_346, ZeroWidthRangeProducesSameValue_346) {
    double a = 3.14, b = 3.14;
    std::uint32_t seed = 100;
    Catch::Generators::RandomFloatingGenerator<double> gen(a, b, seed);

    for (int i = 0; i < 10; ++i) {
        double val = gen.get();
        EXPECT_DOUBLE_EQ(val, 3.14);
        gen.next();
    }
}
