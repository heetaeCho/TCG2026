#include <gtest/gtest.h>
#include <cmath>
#include <set>
#include <limits>

// Include the header under test
#include "catch2/generators/catch_generators_random.hpp"

using namespace Catch::Generators;

// ============================================================
// Tests for RandomFloatingGenerator<float>
// ============================================================

class RandomFloatingGeneratorFloatTest_347 : public ::testing::Test {
protected:
    // Helper to create a generator with a given range and seed
    std::unique_ptr<RandomFloatingGenerator<float>> makeGenerator(float a, float b, std::uint32_t seed) {
        return std::make_unique<RandomFloatingGenerator<float>>(a, b, seed);
    }
};

TEST_F(RandomFloatingGeneratorFloatTest_347, NextAlwaysReturnsTrue_347) {
    auto gen = makeGenerator(0.0f, 1.0f, 42);
    for (int i = 0; i < 100; ++i) {
        EXPECT_TRUE(gen->next());
    }
}

TEST_F(RandomFloatingGeneratorFloatTest_347, GetReturnsValueInRange_347) {
    float a = 0.0f;
    float b = 1.0f;
    auto gen = makeGenerator(a, b, 12345);
    // Check initial value
    float val = gen->get();
    EXPECT_GE(val, a);
    EXPECT_LE(val, b);

    // Check after several next() calls
    for (int i = 0; i < 100; ++i) {
        gen->next();
        val = gen->get();
        EXPECT_GE(val, a);
        EXPECT_LE(val, b);
    }
}

TEST_F(RandomFloatingGeneratorFloatTest_347, NegativeRange_347) {
    float a = -10.0f;
    float b = -1.0f;
    auto gen = makeGenerator(a, b, 99);
    float val = gen->get();
    EXPECT_GE(val, a);
    EXPECT_LE(val, b);

    for (int i = 0; i < 50; ++i) {
        gen->next();
        val = gen->get();
        EXPECT_GE(val, a);
        EXPECT_LE(val, b);
    }
}

TEST_F(RandomFloatingGeneratorFloatTest_347, RangeSpanningZero_347) {
    float a = -5.0f;
    float b = 5.0f;
    auto gen = makeGenerator(a, b, 777);

    for (int i = 0; i < 100; ++i) {
        gen->next();
        float val = gen->get();
        EXPECT_GE(val, a);
        EXPECT_LE(val, b);
    }
}

TEST_F(RandomFloatingGeneratorFloatTest_347, SameSeedProducesSameSequence_347) {
    auto gen1 = makeGenerator(0.0f, 100.0f, 42);
    auto gen2 = makeGenerator(0.0f, 100.0f, 42);

    // Initial values should be the same
    EXPECT_FLOAT_EQ(gen1->get(), gen2->get());

    for (int i = 0; i < 50; ++i) {
        gen1->next();
        gen2->next();
        EXPECT_FLOAT_EQ(gen1->get(), gen2->get());
    }
}

TEST_F(RandomFloatingGeneratorFloatTest_347, DifferentSeedsProduceDifferentSequences_347) {
    auto gen1 = makeGenerator(0.0f, 1000.0f, 42);
    auto gen2 = makeGenerator(0.0f, 1000.0f, 43);

    // It's highly unlikely that two different seeds produce identical sequences
    bool allSame = true;
    for (int i = 0; i < 20; ++i) {
        if (gen1->get() != gen2->get()) {
            allSame = false;
            break;
        }
        gen1->next();
        gen2->next();
    }
    EXPECT_FALSE(allSame);
}

TEST_F(RandomFloatingGeneratorFloatTest_347, GeneratesVariedValues_347) {
    auto gen = makeGenerator(0.0f, 1.0f, 12345);
    std::set<float> values;
    values.insert(gen->get());
    for (int i = 0; i < 100; ++i) {
        gen->next();
        values.insert(gen->get());
    }
    // Expect many distinct values
    EXPECT_GT(values.size(), 50u);
}

TEST_F(RandomFloatingGeneratorFloatTest_347, SmallRange_347) {
    float a = 1.0f;
    float b = 1.0f + std::numeric_limits<float>::epsilon();
    auto gen = makeGenerator(a, b, 42);
    float val = gen->get();
    EXPECT_GE(val, a);
    EXPECT_LE(val, b);
}

TEST_F(RandomFloatingGeneratorFloatTest_347, LargeRange_347) {
    float a = -1e30f;
    float b = 1e30f;
    auto gen = makeGenerator(a, b, 42);
    for (int i = 0; i < 50; ++i) {
        float val = gen->get();
        EXPECT_GE(val, a);
        EXPECT_LE(val, b);
        gen->next();
    }
}

// ============================================================
// Tests for RandomFloatingGenerator<double>
// ============================================================

class RandomFloatingGeneratorDoubleTest_347 : public ::testing::Test {
protected:
    std::unique_ptr<RandomFloatingGenerator<double>> makeGenerator(double a, double b, std::uint32_t seed) {
        return std::make_unique<RandomFloatingGenerator<double>>(a, b, seed);
    }
};

TEST_F(RandomFloatingGeneratorDoubleTest_347, NextAlwaysReturnsTrue_347) {
    auto gen = makeGenerator(0.0, 1.0, 42);
    for (int i = 0; i < 100; ++i) {
        EXPECT_TRUE(gen->next());
    }
}

TEST_F(RandomFloatingGeneratorDoubleTest_347, GetReturnsValueInRange_347) {
    double a = 0.0;
    double b = 1.0;
    auto gen = makeGenerator(a, b, 54321);
    double val = gen->get();
    EXPECT_GE(val, a);
    EXPECT_LE(val, b);

    for (int i = 0; i < 100; ++i) {
        gen->next();
        val = gen->get();
        EXPECT_GE(val, a);
        EXPECT_LE(val, b);
    }
}

TEST_F(RandomFloatingGeneratorDoubleTest_347, SameSeedProducesSameSequence_347) {
    auto gen1 = makeGenerator(0.0, 100.0, 42);
    auto gen2 = makeGenerator(0.0, 100.0, 42);

    EXPECT_DOUBLE_EQ(gen1->get(), gen2->get());

    for (int i = 0; i < 50; ++i) {
        gen1->next();
        gen2->next();
        EXPECT_DOUBLE_EQ(gen1->get(), gen2->get());
    }
}

TEST_F(RandomFloatingGeneratorDoubleTest_347, NegativeRange_347) {
    double a = -100.0;
    double b = -0.001;
    auto gen = makeGenerator(a, b, 7);

    for (int i = 0; i < 100; ++i) {
        double val = gen->get();
        EXPECT_GE(val, a);
        EXPECT_LE(val, b);
        gen->next();
    }
}

TEST_F(RandomFloatingGeneratorDoubleTest_347, GeneratesVariedValues_347) {
    auto gen = makeGenerator(0.0, 1.0, 9999);
    std::set<double> values;
    values.insert(gen->get());
    for (int i = 0; i < 100; ++i) {
        gen->next();
        values.insert(gen->get());
    }
    EXPECT_GT(values.size(), 50u);
}

TEST_F(RandomFloatingGeneratorDoubleTest_347, GetIsConsistentWithoutNext_347) {
    auto gen = makeGenerator(0.0, 1.0, 42);
    double val1 = gen->get();
    double val2 = gen->get();
    // Without calling next(), get() should return the same value
    EXPECT_DOUBLE_EQ(val1, val2);
}

TEST_F(RandomFloatingGeneratorDoubleTest_347, GetChangesAfterNext_347) {
    auto gen = makeGenerator(0.0, 1000.0, 42);
    double val1 = gen->get();
    gen->next();
    double val2 = gen->get();
    // It's extremely unlikely to get the same value in a large range
    EXPECT_NE(val1, val2);
}

// ============================================================
// Tests for RandomFloatingGenerator<long double>
// ============================================================

class RandomFloatingGeneratorLongDoubleTest_347 : public ::testing::Test {
protected:
    std::unique_ptr<RandomFloatingGenerator<long double>> makeGenerator(long double a, long double b, std::uint32_t seed) {
        return std::make_unique<RandomFloatingGenerator<long double>>(a, b, seed);
    }
};

TEST_F(RandomFloatingGeneratorLongDoubleTest_347, NextAlwaysReturnsTrue_347) {
    auto gen = makeGenerator(0.0L, 1.0L, 42);
    for (int i = 0; i < 100; ++i) {
        EXPECT_TRUE(gen->next());
    }
}

TEST_F(RandomFloatingGeneratorLongDoubleTest_347, GetReturnsValueInRange_347) {
    long double a = 0.0L;
    long double b = 1.0L;
    auto gen = makeGenerator(a, b, 42);

    for (int i = 0; i < 100; ++i) {
        long double val = gen->get();
        EXPECT_GE(val, a);
        EXPECT_LE(val, b);
        gen->next();
    }
}

TEST_F(RandomFloatingGeneratorLongDoubleTest_347, SameSeedProducesSameSequence_347) {
    auto gen1 = makeGenerator(0.0L, 100.0L, 42);
    auto gen2 = makeGenerator(0.0L, 100.0L, 42);

    EXPECT_EQ(gen1->get(), gen2->get());

    for (int i = 0; i < 50; ++i) {
        gen1->next();
        gen2->next();
        EXPECT_EQ(gen1->get(), gen2->get());
    }
}

TEST_F(RandomFloatingGeneratorLongDoubleTest_347, GetIsConsistentWithoutNext_347) {
    auto gen = makeGenerator(0.0L, 1.0L, 42);
    long double val1 = gen->get();
    long double val2 = gen->get();
    EXPECT_EQ(val1, val2);
}

TEST_F(RandomFloatingGeneratorLongDoubleTest_347, NegativeRange_347) {
    long double a = -50.0L;
    long double b = -1.0L;
    auto gen = makeGenerator(a, b, 123);

    for (int i = 0; i < 100; ++i) {
        long double val = gen->get();
        EXPECT_GE(val, a);
        EXPECT_LE(val, b);
        gen->next();
    }
}

TEST_F(RandomFloatingGeneratorLongDoubleTest_347, GeneratesVariedValues_347) {
    auto gen = makeGenerator(0.0L, 1.0L, 55555);
    std::set<long double> values;
    values.insert(gen->get());
    for (int i = 0; i < 100; ++i) {
        gen->next();
        values.insert(gen->get());
    }
    EXPECT_GT(values.size(), 50u);
}

TEST_F(RandomFloatingGeneratorLongDoubleTest_347, DestructorDoesNotCrash_347) {
    // Simply create and destroy - verify no crash
    {
        auto gen = makeGenerator(0.0L, 1.0L, 42);
        gen->next();
        (void)gen->get();
    }
    SUCCEED();
}

TEST_F(RandomFloatingGeneratorLongDoubleTest_347, DifferentSeedsProduceDifferentSequences_347) {
    auto gen1 = makeGenerator(0.0L, 1000.0L, 42);
    auto gen2 = makeGenerator(0.0L, 1000.0L, 43);

    bool allSame = true;
    for (int i = 0; i < 20; ++i) {
        if (gen1->get() != gen2->get()) {
            allSame = false;
            break;
        }
        gen1->next();
        gen2->next();
    }
    EXPECT_FALSE(allSame);
}

// ============================================================
// Boundary / Edge case tests
// ============================================================

TEST(RandomFloatingGeneratorEdgeCases_347, ZeroSeed_347) {
    RandomFloatingGenerator<double> gen(0.0, 1.0, 0);
    EXPECT_TRUE(gen.next());
    double val = gen.get();
    EXPECT_GE(val, 0.0);
    EXPECT_LE(val, 1.0);
}

TEST(RandomFloatingGeneratorEdgeCases_347, MaxSeed_347) {
    RandomFloatingGenerator<double> gen(0.0, 1.0, std::numeric_limits<std::uint32_t>::max());
    EXPECT_TRUE(gen.next());
    double val = gen.get();
    EXPECT_GE(val, 0.0);
    EXPECT_LE(val, 1.0);
}

TEST(RandomFloatingGeneratorEdgeCases_347, VerySmallRangeDouble_347) {
    double a = 1.0;
    double b = 1.0 + std::numeric_limits<double>::epsilon();
    RandomFloatingGenerator<double> gen(a, b, 42);
    double val = gen.get();
    EXPECT_GE(val, a);
    EXPECT_LE(val, b);
}

TEST(RandomFloatingGeneratorEdgeCases_347, ManyIterationsStayInRange_347) {
    float a = -1.0f;
    float b = 1.0f;
    RandomFloatingGenerator<float> gen(a, b, 42);

    for (int i = 0; i < 10000; ++i) {
        float val = gen.get();
        ASSERT_GE(val, a) << "Out of range at iteration " << i;
        ASSERT_LE(val, b) << "Out of range at iteration " << i;
        gen.next();
    }
}
