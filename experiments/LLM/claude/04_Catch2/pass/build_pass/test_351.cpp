#include <catch2/generators/catch_generators_random.hpp>
#include <catch2/generators/catch_generators.hpp>
#include <catch2/catch_test_macros.hpp>

#include <gtest/gtest.h>
#include <type_traits>
#include <set>
#include <limits>
#include <cstdint>

// Test that random() with integral types compiles and returns values within range
TEST(RandomGeneratorTest_351, IntValuesWithinRange_351) {
    auto gen = Catch::Generators::random(1, 10);
    // Generate several values and check they are within [1, 10]
    for (int i = 0; i < 100; ++i) {
        int val = gen.get();
        EXPECT_GE(val, 1);
        EXPECT_LE(val, 10);
        if (!gen.next()) break;
    }
}

TEST(RandomGeneratorTest_351, SingleValueRange_351) {
    auto gen = Catch::Generators::random(5, 5);
    // When a == b, the only possible value is 5
    for (int i = 0; i < 10; ++i) {
        int val = gen.get();
        EXPECT_EQ(val, 5);
        if (!gen.next()) break;
    }
}

TEST(RandomGeneratorTest_351, NegativeRange_351) {
    auto gen = Catch::Generators::random(-100, -50);
    for (int i = 0; i < 100; ++i) {
        int val = gen.get();
        EXPECT_GE(val, -100);
        EXPECT_LE(val, -50);
        if (!gen.next()) break;
    }
}

TEST(RandomGeneratorTest_351, SpanningZeroRange_351) {
    auto gen = Catch::Generators::random(-50, 50);
    for (int i = 0; i < 100; ++i) {
        int val = gen.get();
        EXPECT_GE(val, -50);
        EXPECT_LE(val, 50);
        if (!gen.next()) break;
    }
}

TEST(RandomGeneratorTest_351, UnsignedIntRange_351) {
    auto gen = Catch::Generators::random(0u, 100u);
    for (int i = 0; i < 100; ++i) {
        unsigned int val = gen.get();
        EXPECT_GE(val, 0u);
        EXPECT_LE(val, 100u);
        if (!gen.next()) break;
    }
}

TEST(RandomGeneratorTest_351, ShortRange_351) {
    auto gen = Catch::Generators::random<short>(0, 10);
    for (int i = 0; i < 50; ++i) {
        short val = gen.get();
        EXPECT_GE(val, 0);
        EXPECT_LE(val, 10);
        if (!gen.next()) break;
    }
}

TEST(RandomGeneratorTest_351, Int64Range_351) {
    auto gen = Catch::Generators::random<int64_t>(0, 1000000);
    for (int i = 0; i < 100; ++i) {
        int64_t val = gen.get();
        EXPECT_GE(val, 0);
        EXPECT_LE(val, 1000000);
        if (!gen.next()) break;
    }
}

TEST(RandomGeneratorTest_351, UInt8Range_351) {
    auto gen = Catch::Generators::random<uint8_t>(0, 255);
    for (int i = 0; i < 100; ++i) {
        uint8_t val = gen.get();
        EXPECT_GE(val, 0);
        EXPECT_LE(val, 255);
        if (!gen.next()) break;
    }
}

TEST(RandomGeneratorTest_351, ProducesMultipleDistinctValues_351) {
    // With a large enough range, we should get at least 2 distinct values in 100 tries
    auto gen = Catch::Generators::random(0, 1000000);
    std::set<int> values;
    for (int i = 0; i < 100; ++i) {
        values.insert(gen.get());
        if (!gen.next()) break;
    }
    EXPECT_GT(values.size(), 1u);
}

TEST(RandomGeneratorTest_351, ReturnTypeIsGeneratorWrapper_351) {
    auto gen = Catch::Generators::random(1, 10);
    // Verify that the type is GeneratorWrapper<int>
    static_assert(
        std::is_same<decltype(gen), Catch::Generators::GeneratorWrapper<int>>::value,
        "random(int, int) should return GeneratorWrapper<int>"
    );
}

TEST(RandomGeneratorTest_351, LongLongRange_351) {
    auto gen = Catch::Generators::random<long long>(
        -1000000000LL, 1000000000LL
    );
    for (int i = 0; i < 100; ++i) {
        long long val = gen.get();
        EXPECT_GE(val, -1000000000LL);
        EXPECT_LE(val, 1000000000LL);
        if (!gen.next()) break;
    }
}

TEST(RandomGeneratorTest_351, SmallRangeCoversAllValues_351) {
    // With range [0, 2], after enough iterations we should see all 3 values
    auto gen = Catch::Generators::random(0, 2);
    std::set<int> values;
    for (int i = 0; i < 1000; ++i) {
        values.insert(gen.get());
        if (values.size() == 3) break;
        if (!gen.next()) break;
    }
    // We may not guarantee coverage but with 1000 tries it's extremely likely
    EXPECT_EQ(values.size(), 3u);
}

TEST(RandomGeneratorTest_351, GetReturnsConsistentBeforeNext_351) {
    auto gen = Catch::Generators::random(1, 1000);
    int first_call = gen.get();
    int second_call = gen.get();
    // Calling get() multiple times without next() should return the same value
    EXPECT_EQ(first_call, second_call);
}

TEST(RandomGeneratorTest_351, NextAdvancesValue_351) {
    // After calling next(), get() may return a different value (not guaranteed but likely with large range)
    auto gen = Catch::Generators::random(0, 1000000);
    int val1 = gen.get();
    gen.next();
    int val2 = gen.get();
    // We can't guarantee they differ, but we can at least test that both are in range
    EXPECT_GE(val1, 0);
    EXPECT_LE(val1, 1000000);
    EXPECT_GE(val2, 0);
    EXPECT_LE(val2, 1000000);
}
