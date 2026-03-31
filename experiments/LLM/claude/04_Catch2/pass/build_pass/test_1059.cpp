#include <gtest/gtest.h>
#include <cstdint>
#include <set>
#include <cmath>
#include <limits>

// Include the header under test
#include "catch2/generators/catch_generators_random.hpp"

using namespace Catch::Generators;

// ==================== float tests ====================

class RandomFloatingGeneratorFloatTest_1059 : public ::testing::Test {
protected:
    static constexpr float low = 0.0f;
    static constexpr float high = 1.0f;
    static constexpr std::uint32_t seed = 12345u;
};

TEST_F(RandomFloatingGeneratorFloatTest_1059, ConstructionSucceeds_1059) {
    EXPECT_NO_THROW({
        RandomFloatingGenerator<float> gen(low, high, seed);
    });
}

TEST_F(RandomFloatingGeneratorFloatTest_1059, GetReturnsValueInRange_1059) {
    RandomFloatingGenerator<float> gen(low, high, seed);
    float val = gen.get();
    EXPECT_GE(val, low);
    EXPECT_LE(val, high);
}

TEST_F(RandomFloatingGeneratorFloatTest_1059, NextReturnsTrueAndUpdatesValue_1059) {
    RandomFloatingGenerator<float> gen(low, high, seed);
    float first = gen.get();
    bool hasNext = gen.next();
    EXPECT_TRUE(hasNext);
    float second = gen.get();
    EXPECT_GE(second, low);
    EXPECT_LE(second, high);
}

TEST_F(RandomFloatingGeneratorFloatTest_1059, MultipleNextCallsProduceValuesInRange_1059) {
    RandomFloatingGenerator<float> gen(low, high, seed);
    for (int i = 0; i < 100; ++i) {
        float val = gen.get();
        EXPECT_GE(val, low);
        EXPECT_LE(val, high);
        gen.next();
    }
}

TEST_F(RandomFloatingGeneratorFloatTest_1059, SameSeedProducesSameSequence_1059) {
    RandomFloatingGenerator<float> gen1(low, high, seed);
    RandomFloatingGenerator<float> gen2(low, high, seed);

    for (int i = 0; i < 50; ++i) {
        EXPECT_FLOAT_EQ(gen1.get(), gen2.get());
        gen1.next();
        gen2.next();
    }
}

TEST_F(RandomFloatingGeneratorFloatTest_1059, DifferentSeedsProduceDifferentSequences_1059) {
    RandomFloatingGenerator<float> gen1(low, high, 111u);
    RandomFloatingGenerator<float> gen2(low, high, 222u);

    bool allSame = true;
    for (int i = 0; i < 20; ++i) {
        if (gen1.get() != gen2.get()) {
            allSame = false;
        }
        gen1.next();
        gen2.next();
    }
    EXPECT_FALSE(allSame);
}

TEST_F(RandomFloatingGeneratorFloatTest_1059, NegativeRange_1059) {
    RandomFloatingGenerator<float> gen(-10.0f, -1.0f, seed);
    for (int i = 0; i < 50; ++i) {
        float val = gen.get();
        EXPECT_GE(val, -10.0f);
        EXPECT_LE(val, -1.0f);
        gen.next();
    }
}

TEST_F(RandomFloatingGeneratorFloatTest_1059, RangeSpanningZero_1059) {
    RandomFloatingGenerator<float> gen(-5.0f, 5.0f, seed);
    for (int i = 0; i < 50; ++i) {
        float val = gen.get();
        EXPECT_GE(val, -5.0f);
        EXPECT_LE(val, 5.0f);
        gen.next();
    }
}

TEST_F(RandomFloatingGeneratorFloatTest_1059, EqualBounds_1059) {
    RandomFloatingGenerator<float> gen(3.0f, 3.0f, seed);
    float val = gen.get();
    EXPECT_FLOAT_EQ(val, 3.0f);
    gen.next();
    val = gen.get();
    EXPECT_FLOAT_EQ(val, 3.0f);
}

TEST_F(RandomFloatingGeneratorFloatTest_1059, LargeRange_1059) {
    float lo = -1e30f;
    float hi = 1e30f;
    RandomFloatingGenerator<float> gen(lo, hi, seed);
    for (int i = 0; i < 50; ++i) {
        float val = gen.get();
        EXPECT_GE(val, lo);
        EXPECT_LE(val, hi);
        EXPECT_FALSE(std::isnan(val));
        EXPECT_FALSE(std::isinf(val));
        gen.next();
    }
}

TEST_F(RandomFloatingGeneratorFloatTest_1059, GetIsConstAndRepeatable_1059) {
    RandomFloatingGenerator<float> gen(low, high, seed);
    float v1 = gen.get();
    float v2 = gen.get();
    EXPECT_FLOAT_EQ(v1, v2);
}

// ==================== double tests ====================

class RandomFloatingGeneratorDoubleTest_1059 : public ::testing::Test {
protected:
    static constexpr double low = 0.0;
    static constexpr double high = 1.0;
    static constexpr std::uint32_t seed = 54321u;
};

TEST_F(RandomFloatingGeneratorDoubleTest_1059, ConstructionSucceeds_1059) {
    EXPECT_NO_THROW({
        RandomFloatingGenerator<double> gen(low, high, seed);
    });
}

TEST_F(RandomFloatingGeneratorDoubleTest_1059, GetReturnsValueInRange_1059) {
    RandomFloatingGenerator<double> gen(low, high, seed);
    double val = gen.get();
    EXPECT_GE(val, low);
    EXPECT_LE(val, high);
}

TEST_F(RandomFloatingGeneratorDoubleTest_1059, NextReturnsTrueAndUpdatesValue_1059) {
    RandomFloatingGenerator<double> gen(low, high, seed);
    double first = gen.get();
    bool hasNext = gen.next();
    EXPECT_TRUE(hasNext);
    double second = gen.get();
    EXPECT_GE(second, low);
    EXPECT_LE(second, high);
}

TEST_F(RandomFloatingGeneratorDoubleTest_1059, MultipleNextCallsProduceValuesInRange_1059) {
    RandomFloatingGenerator<double> gen(low, high, seed);
    for (int i = 0; i < 100; ++i) {
        double val = gen.get();
        EXPECT_GE(val, low);
        EXPECT_LE(val, high);
        gen.next();
    }
}

TEST_F(RandomFloatingGeneratorDoubleTest_1059, SameSeedProducesSameSequence_1059) {
    RandomFloatingGenerator<double> gen1(low, high, seed);
    RandomFloatingGenerator<double> gen2(low, high, seed);

    for (int i = 0; i < 50; ++i) {
        EXPECT_DOUBLE_EQ(gen1.get(), gen2.get());
        gen1.next();
        gen2.next();
    }
}

TEST_F(RandomFloatingGeneratorDoubleTest_1059, DifferentSeedsProduceDifferentSequences_1059) {
    RandomFloatingGenerator<double> gen1(low, high, 333u);
    RandomFloatingGenerator<double> gen2(low, high, 444u);

    bool allSame = true;
    for (int i = 0; i < 20; ++i) {
        if (gen1.get() != gen2.get()) {
            allSame = false;
        }
        gen1.next();
        gen2.next();
    }
    EXPECT_FALSE(allSame);
}

TEST_F(RandomFloatingGeneratorDoubleTest_1059, NegativeRange_1059) {
    RandomFloatingGenerator<double> gen(-100.0, -1.0, seed);
    for (int i = 0; i < 50; ++i) {
        double val = gen.get();
        EXPECT_GE(val, -100.0);
        EXPECT_LE(val, -1.0);
        gen.next();
    }
}

TEST_F(RandomFloatingGeneratorDoubleTest_1059, EqualBounds_1059) {
    RandomFloatingGenerator<double> gen(7.5, 7.5, seed);
    double val = gen.get();
    EXPECT_DOUBLE_EQ(val, 7.5);
    gen.next();
    val = gen.get();
    EXPECT_DOUBLE_EQ(val, 7.5);
}

TEST_F(RandomFloatingGeneratorDoubleTest_1059, GetIsConstAndRepeatable_1059) {
    RandomFloatingGenerator<double> gen(low, high, seed);
    double v1 = gen.get();
    double v2 = gen.get();
    EXPECT_DOUBLE_EQ(v1, v2);
}

TEST_F(RandomFloatingGeneratorDoubleTest_1059, VerySmallRange_1059) {
    double lo = 1.0;
    double hi = 1.0 + 1e-10;
    RandomFloatingGenerator<double> gen(lo, hi, seed);
    for (int i = 0; i < 50; ++i) {
        double val = gen.get();
        EXPECT_GE(val, lo);
        EXPECT_LE(val, hi);
        gen.next();
    }
}

// ==================== long double tests ====================

class RandomFloatingGeneratorLongDoubleTest_1059 : public ::testing::Test {
protected:
    static constexpr long double low = 0.0L;
    static constexpr long double high = 1.0L;
    static constexpr std::uint32_t seed = 99999u;
};

TEST_F(RandomFloatingGeneratorLongDoubleTest_1059, ConstructionSucceeds_1059) {
    EXPECT_NO_THROW({
        RandomFloatingGenerator<long double> gen(low, high, seed);
    });
}

TEST_F(RandomFloatingGeneratorLongDoubleTest_1059, GetReturnsValueInRange_1059) {
    RandomFloatingGenerator<long double> gen(low, high, seed);
    long double val = gen.get();
    EXPECT_GE(val, low);
    EXPECT_LE(val, high);
}

TEST_F(RandomFloatingGeneratorLongDoubleTest_1059, NextReturnsTrueAndUpdatesValue_1059) {
    RandomFloatingGenerator<long double> gen(low, high, seed);
    long double first = gen.get();
    bool hasNext = gen.next();
    EXPECT_TRUE(hasNext);
    long double second = gen.get();
    EXPECT_GE(second, low);
    EXPECT_LE(second, high);
}

TEST_F(RandomFloatingGeneratorLongDoubleTest_1059, MultipleNextCallsProduceValuesInRange_1059) {
    RandomFloatingGenerator<long double> gen(low, high, seed);
    for (int i = 0; i < 100; ++i) {
        long double val = gen.get();
        EXPECT_GE(val, low);
        EXPECT_LE(val, high);
        gen.next();
    }
}

TEST_F(RandomFloatingGeneratorLongDoubleTest_1059, SameSeedProducesSameSequence_1059) {
    RandomFloatingGenerator<long double> gen1(low, high, seed);
    RandomFloatingGenerator<long double> gen2(low, high, seed);

    for (int i = 0; i < 50; ++i) {
        EXPECT_EQ(gen1.get(), gen2.get());
        gen1.next();
        gen2.next();
    }
}

TEST_F(RandomFloatingGeneratorLongDoubleTest_1059, DifferentSeedsProduceDifferentSequences_1059) {
    RandomFloatingGenerator<long double> gen1(low, high, 555u);
    RandomFloatingGenerator<long double> gen2(low, high, 666u);

    bool allSame = true;
    for (int i = 0; i < 20; ++i) {
        if (gen1.get() != gen2.get()) {
            allSame = false;
        }
        gen1.next();
        gen2.next();
    }
    EXPECT_FALSE(allSame);
}

TEST_F(RandomFloatingGeneratorLongDoubleTest_1059, DestructionSucceeds_1059) {
    EXPECT_NO_THROW({
        auto gen = new RandomFloatingGenerator<long double>(low, high, seed);
        delete gen;
    });
}

TEST_F(RandomFloatingGeneratorLongDoubleTest_1059, EqualBounds_1059) {
    RandomFloatingGenerator<long double> gen(2.5L, 2.5L, seed);
    long double val = gen.get();
    EXPECT_DOUBLE_EQ(static_cast<double>(val), 2.5);
}

TEST_F(RandomFloatingGeneratorLongDoubleTest_1059, NegativeRange_1059) {
    RandomFloatingGenerator<long double> gen(-50.0L, -10.0L, seed);
    for (int i = 0; i < 50; ++i) {
        long double val = gen.get();
        EXPECT_GE(val, -50.0L);
        EXPECT_LE(val, -10.0L);
        gen.next();
    }
}

TEST_F(RandomFloatingGeneratorLongDoubleTest_1059, GetIsConstAndRepeatable_1059) {
    RandomFloatingGenerator<long double> gen(low, high, seed);
    long double v1 = gen.get();
    long double v2 = gen.get();
    EXPECT_EQ(v1, v2);
}

// ==================== Additional edge case tests ====================

TEST(RandomFloatingGeneratorEdge_1059, FloatSeedZero_1059) {
    RandomFloatingGenerator<float> gen(0.0f, 100.0f, 0u);
    float val = gen.get();
    EXPECT_GE(val, 0.0f);
    EXPECT_LE(val, 100.0f);
}

TEST(RandomFloatingGeneratorEdge_1059, DoubleSeedMaxUint32_1059) {
    RandomFloatingGenerator<double> gen(0.0, 100.0, std::numeric_limits<std::uint32_t>::max());
    double val = gen.get();
    EXPECT_GE(val, 0.0);
    EXPECT_LE(val, 100.0);
}

TEST(RandomFloatingGeneratorEdge_1059, FloatProducesVariety_1059) {
    RandomFloatingGenerator<float> gen(0.0f, 1.0f, 42u);
    std::set<float> values;
    for (int i = 0; i < 100; ++i) {
        values.insert(gen.get());
        gen.next();
    }
    // Expect at least some variety in 100 draws
    EXPECT_GT(values.size(), 1u);
}

TEST(RandomFloatingGeneratorEdge_1059, DoubleProducesVariety_1059) {
    RandomFloatingGenerator<double> gen(0.0, 1.0, 42u);
    std::set<double> values;
    for (int i = 0; i < 100; ++i) {
        values.insert(gen.get());
        gen.next();
    }
    EXPECT_GT(values.size(), 1u);
}

TEST(RandomFloatingGeneratorEdge_1059, FloatValuesAreFinite_1059) {
    RandomFloatingGenerator<float> gen(-1e10f, 1e10f, 777u);
    for (int i = 0; i < 100; ++i) {
        float val = gen.get();
        EXPECT_TRUE(std::isfinite(val));
        gen.next();
    }
}

TEST(RandomFloatingGeneratorEdge_1059, DoubleValuesAreFinite_1059) {
    RandomFloatingGenerator<double> gen(-1e100, 1e100, 888u);
    for (int i = 0; i < 100; ++i) {
        double val = gen.get();
        EXPECT_TRUE(std::isfinite(val));
        gen.next();
    }
}
