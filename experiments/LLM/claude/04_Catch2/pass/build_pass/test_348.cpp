#include <gtest/gtest.h>
#include <cmath>
#include <set>
#include <limits>

// Include the header under test
#include "catch2/generators/catch_generators_random.hpp"

// We need to include enough Catch2 infrastructure
#include "catch2/internal/catch_random_number_generator.hpp"

using namespace Catch::Generators;

// ============================================================
// Tests for RandomFloatingGenerator<float>
// ============================================================

class RandomFloatingGeneratorFloatTest_348 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(RandomFloatingGeneratorFloatTest_348, GetReturnsValueInRange_348) {
    float lo = 0.0f;
    float hi = 1.0f;
    RandomFloatingGenerator<float> gen(lo, hi, 42);

    float val = gen.get();
    EXPECT_GE(val, lo);
    EXPECT_LE(val, hi);
}

TEST_F(RandomFloatingGeneratorFloatTest_348, NextReturnsTrueAndProducesNewValue_348) {
    float lo = 0.0f;
    float hi = 100.0f;
    RandomFloatingGenerator<float> gen(lo, hi, 12345);

    float first = gen.get();
    bool result = gen.next();
    EXPECT_TRUE(result);

    // After next(), get() should still return a value in range
    float second = gen.get();
    EXPECT_GE(second, lo);
    EXPECT_LE(second, hi);
}

TEST_F(RandomFloatingGeneratorFloatTest_348, MultipleNextCallsProduceValuesInRange_348) {
    float lo = -50.0f;
    float hi = 50.0f;
    RandomFloatingGenerator<float> gen(lo, hi, 99);

    for (int i = 0; i < 100; ++i) {
        float val = gen.get();
        EXPECT_GE(val, lo);
        EXPECT_LE(val, hi);
        gen.next();
    }
}

TEST_F(RandomFloatingGeneratorFloatTest_348, SameSeedProducesSameSequence_348) {
    float lo = 0.0f;
    float hi = 1000.0f;
    std::uint32_t seed = 777;

    RandomFloatingGenerator<float> gen1(lo, hi, seed);
    RandomFloatingGenerator<float> gen2(lo, hi, seed);

    for (int i = 0; i < 50; ++i) {
        EXPECT_FLOAT_EQ(gen1.get(), gen2.get());
        gen1.next();
        gen2.next();
    }
}

TEST_F(RandomFloatingGeneratorFloatTest_348, DifferentSeedsProduceDifferentSequences_348) {
    float lo = 0.0f;
    float hi = 1000.0f;

    RandomFloatingGenerator<float> gen1(lo, hi, 1);
    RandomFloatingGenerator<float> gen2(lo, hi, 2);

    bool any_different = false;
    for (int i = 0; i < 50; ++i) {
        if (gen1.get() != gen2.get()) {
            any_different = true;
        }
        gen1.next();
        gen2.next();
    }
    EXPECT_TRUE(any_different);
}

TEST_F(RandomFloatingGeneratorFloatTest_348, NarrowRangeProducesValuesInRange_348) {
    float lo = 1.0f;
    float hi = 1.0001f;
    RandomFloatingGenerator<float> gen(lo, hi, 42);

    for (int i = 0; i < 50; ++i) {
        float val = gen.get();
        EXPECT_GE(val, lo);
        EXPECT_LE(val, hi);
        gen.next();
    }
}

TEST_F(RandomFloatingGeneratorFloatTest_348, NegativeRangeProducesValuesInRange_348) {
    float lo = -100.0f;
    float hi = -1.0f;
    RandomFloatingGenerator<float> gen(lo, hi, 42);

    for (int i = 0; i < 50; ++i) {
        float val = gen.get();
        EXPECT_GE(val, lo);
        EXPECT_LE(val, hi);
        gen.next();
    }
}

TEST_F(RandomFloatingGeneratorFloatTest_348, GetIsConsistentWithoutNext_348) {
    float lo = 0.0f;
    float hi = 10.0f;
    RandomFloatingGenerator<float> gen(lo, hi, 42);

    float val1 = gen.get();
    float val2 = gen.get();
    EXPECT_FLOAT_EQ(val1, val2);
}

// ============================================================
// Tests for RandomFloatingGenerator<double>
// ============================================================

class RandomFloatingGeneratorDoubleTest_348 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(RandomFloatingGeneratorDoubleTest_348, GetReturnsValueInRange_348) {
    double lo = 0.0;
    double hi = 1.0;
    RandomFloatingGenerator<double> gen(lo, hi, 42);

    double val = gen.get();
    EXPECT_GE(val, lo);
    EXPECT_LE(val, hi);
}

TEST_F(RandomFloatingGeneratorDoubleTest_348, NextReturnsTrueAndProducesNewValue_348) {
    double lo = 0.0;
    double hi = 100.0;
    RandomFloatingGenerator<double> gen(lo, hi, 12345);

    double first = gen.get();
    bool result = gen.next();
    EXPECT_TRUE(result);

    double second = gen.get();
    EXPECT_GE(second, lo);
    EXPECT_LE(second, hi);
}

TEST_F(RandomFloatingGeneratorDoubleTest_348, MultipleNextCallsProduceValuesInRange_348) {
    double lo = -1000.0;
    double hi = 1000.0;
    RandomFloatingGenerator<double> gen(lo, hi, 55);

    for (int i = 0; i < 100; ++i) {
        double val = gen.get();
        EXPECT_GE(val, lo);
        EXPECT_LE(val, hi);
        gen.next();
    }
}

TEST_F(RandomFloatingGeneratorDoubleTest_348, SameSeedProducesSameSequence_348) {
    double lo = -500.0;
    double hi = 500.0;
    std::uint32_t seed = 314;

    RandomFloatingGenerator<double> gen1(lo, hi, seed);
    RandomFloatingGenerator<double> gen2(lo, hi, seed);

    for (int i = 0; i < 50; ++i) {
        EXPECT_DOUBLE_EQ(gen1.get(), gen2.get());
        gen1.next();
        gen2.next();
    }
}

TEST_F(RandomFloatingGeneratorDoubleTest_348, GetIsConsistentWithoutNext_348) {
    double lo = 0.0;
    double hi = 10.0;
    RandomFloatingGenerator<double> gen(lo, hi, 42);

    double val1 = gen.get();
    double val2 = gen.get();
    EXPECT_DOUBLE_EQ(val1, val2);
}

TEST_F(RandomFloatingGeneratorDoubleTest_348, NegativeRangeProducesValuesInRange_348) {
    double lo = -1000.0;
    double hi = -0.001;
    RandomFloatingGenerator<double> gen(lo, hi, 42);

    for (int i = 0; i < 50; ++i) {
        double val = gen.get();
        EXPECT_GE(val, lo);
        EXPECT_LE(val, hi);
        gen.next();
    }
}

// ============================================================
// Tests for RandomFloatingGenerator<long double> (specialization)
// ============================================================

class RandomFloatingGeneratorLongDoubleTest_348 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(RandomFloatingGeneratorLongDoubleTest_348, GetReturnsValueInRange_348) {
    long double lo = 0.0L;
    long double hi = 1.0L;
    RandomFloatingGenerator<long double> gen(lo, hi, 42);

    long double val = gen.get();
    EXPECT_GE(val, lo);
    EXPECT_LE(val, hi);
}

TEST_F(RandomFloatingGeneratorLongDoubleTest_348, NextReturnsTrueAndProducesNewValue_348) {
    long double lo = 0.0L;
    long double hi = 100.0L;
    RandomFloatingGenerator<long double> gen(lo, hi, 12345);

    long double first = gen.get();
    bool result = gen.next();
    EXPECT_TRUE(result);

    long double second = gen.get();
    EXPECT_GE(second, lo);
    EXPECT_LE(second, hi);
}

TEST_F(RandomFloatingGeneratorLongDoubleTest_348, MultipleNextCallsProduceValuesInRange_348) {
    long double lo = -500.0L;
    long double hi = 500.0L;
    RandomFloatingGenerator<long double> gen(lo, hi, 88);

    for (int i = 0; i < 100; ++i) {
        long double val = gen.get();
        EXPECT_GE(val, lo);
        EXPECT_LE(val, hi);
        gen.next();
    }
}

TEST_F(RandomFloatingGeneratorLongDoubleTest_348, SameSeedProducesSameSequence_348) {
    long double lo = 0.0L;
    long double hi = 1000.0L;
    std::uint32_t seed = 999;

    RandomFloatingGenerator<long double> gen1(lo, hi, seed);
    RandomFloatingGenerator<long double> gen2(lo, hi, seed);

    for (int i = 0; i < 50; ++i) {
        EXPECT_EQ(gen1.get(), gen2.get());
        gen1.next();
        gen2.next();
    }
}

TEST_F(RandomFloatingGeneratorLongDoubleTest_348, GetIsConsistentWithoutNext_348) {
    long double lo = 0.0L;
    long double hi = 10.0L;
    RandomFloatingGenerator<long double> gen(lo, hi, 42);

    long double val1 = gen.get();
    long double val2 = gen.get();
    EXPECT_EQ(val1, val2);
}

TEST_F(RandomFloatingGeneratorLongDoubleTest_348, NegativeRangeProducesValuesInRange_348) {
    long double lo = -200.0L;
    long double hi = -0.01L;
    RandomFloatingGenerator<long double> gen(lo, hi, 42);

    for (int i = 0; i < 50; ++i) {
        long double val = gen.get();
        EXPECT_GE(val, lo);
        EXPECT_LE(val, hi);
        gen.next();
    }
}

TEST_F(RandomFloatingGeneratorLongDoubleTest_348, DestructorDoesNotCrash_348) {
    // Test that the pimpl-based long double specialization cleans up properly
    {
        RandomFloatingGenerator<long double> gen(0.0L, 1.0L, 42);
        gen.next();
        // gen goes out of scope here
    }
    SUCCEED();
}

// ============================================================
// Tests for producing varied values (not just constant)
// ============================================================

TEST_F(RandomFloatingGeneratorFloatTest_348, ProducesVariedValues_348) {
    float lo = 0.0f;
    float hi = 1000.0f;
    RandomFloatingGenerator<float> gen(lo, hi, 42);

    std::set<float> values;
    for (int i = 0; i < 100; ++i) {
        values.insert(gen.get());
        gen.next();
    }
    // With 100 iterations over a wide range, we expect many distinct values
    EXPECT_GT(values.size(), 1u);
}

TEST_F(RandomFloatingGeneratorDoubleTest_348, ProducesVariedValues_348) {
    double lo = 0.0;
    double hi = 1000.0;
    RandomFloatingGenerator<double> gen(lo, hi, 42);

    std::set<double> values;
    for (int i = 0; i < 100; ++i) {
        values.insert(gen.get());
        gen.next();
    }
    EXPECT_GT(values.size(), 1u);
}

TEST_F(RandomFloatingGeneratorLongDoubleTest_348, ProducesVariedValues_348) {
    long double lo = 0.0L;
    long double hi = 1000.0L;
    RandomFloatingGenerator<long double> gen(lo, hi, 42);

    std::set<long double> values;
    for (int i = 0; i < 100; ++i) {
        values.insert(gen.get());
        gen.next();
    }
    EXPECT_GT(values.size(), 1u);
}

// ============================================================
// Boundary tests with equal range endpoints
// ============================================================

TEST_F(RandomFloatingGeneratorFloatTest_348, EqualEndpointsProduceSameValue_348) {
    float val = 5.0f;
    RandomFloatingGenerator<float> gen(val, val, 42);

    float result = gen.get();
    EXPECT_FLOAT_EQ(result, val);

    gen.next();
    result = gen.get();
    EXPECT_FLOAT_EQ(result, val);
}

TEST_F(RandomFloatingGeneratorDoubleTest_348, EqualEndpointsProduceSameValue_348) {
    double val = 5.0;
    RandomFloatingGenerator<double> gen(val, val, 42);

    double result = gen.get();
    EXPECT_DOUBLE_EQ(result, val);

    gen.next();
    result = gen.get();
    EXPECT_DOUBLE_EQ(result, val);
}

TEST_F(RandomFloatingGeneratorLongDoubleTest_348, EqualEndpointsProduceSameValue_348) {
    long double val = 5.0L;
    RandomFloatingGenerator<long double> gen(val, val, 42);

    long double result = gen.get();
    EXPECT_EQ(result, val);

    gen.next();
    result = gen.get();
    EXPECT_EQ(result, val);
}

// ============================================================
// Test with seed 0
// ============================================================

TEST_F(RandomFloatingGeneratorFloatTest_348, SeedZeroWorks_348) {
    float lo = 0.0f;
    float hi = 100.0f;
    RandomFloatingGenerator<float> gen(lo, hi, 0);

    float val = gen.get();
    EXPECT_GE(val, lo);
    EXPECT_LE(val, hi);
    EXPECT_TRUE(gen.next());
}

// ============================================================
// Test with large range
// ============================================================

TEST_F(RandomFloatingGeneratorDoubleTest_348, LargeRangeValuesInBounds_348) {
    double lo = -1e15;
    double hi = 1e15;
    RandomFloatingGenerator<double> gen(lo, hi, 42);

    for (int i = 0; i < 100; ++i) {
        double val = gen.get();
        EXPECT_GE(val, lo);
        EXPECT_LE(val, hi);
        gen.next();
    }
}

TEST_F(RandomFloatingGeneratorFloatTest_348, VerySmallRangeValuesInBounds_348) {
    float lo = 1.0f;
    float hi = std::nextafter(1.0f, 2.0f);
    RandomFloatingGenerator<float> gen(lo, hi, 42);

    for (int i = 0; i < 20; ++i) {
        float val = gen.get();
        EXPECT_GE(val, lo);
        EXPECT_LE(val, hi);
        gen.next();
    }
}
