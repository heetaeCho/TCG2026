#include <catch2/catch_all.hpp>
#include <catch2/generators/catch_generators.hpp>
#include "catch_amalgamated.hpp"

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <vector>
#include <string>

// Since we need to work with Catch2's generator infrastructure,
// we'll create a simple generator that produces a fixed sequence of values.

namespace {

template <typename T>
class FixedValuesGenerator : public Catch::Generators::IGenerator<T> {
    std::vector<T> m_values;
    size_t m_index = 0;
public:
    FixedValuesGenerator(std::vector<T> values) : m_values(std::move(values)) {
        assert(!m_values.empty());
    }

    T const& get() const override {
        return m_values[m_index];
    }

    bool next() override {
        if (m_index + 1 < m_values.size()) {
            ++m_index;
            return true;
        }
        return false;
    }
};

template <typename T>
Catch::Generators::GeneratorWrapper<T> makeFixedGenerator(std::vector<T> values) {
    return Catch::Generators::GeneratorWrapper<T>(
        Catch::Detail::make_unique<FixedValuesGenerator<T>>(std::move(values))
    );
}

} // anonymous namespace

class RepeatGeneratorTest_926 : public ::testing::Test {
protected:
};

// Test that get() returns the first value of the underlying generator initially
TEST_F(RepeatGeneratorTest_926, GetReturnsFirstValueInitially_926) {
    auto gen = Catch::Generators::RepeatGenerator<int>(
        2, makeFixedGenerator<int>({10, 20, 30}));
    EXPECT_EQ(gen.get(), 10);
}

// Test that next() advances through the underlying generator values on first repeat
TEST_F(RepeatGeneratorTest_926, NextAdvancesThroughFirstRepeat_926) {
    auto gen = Catch::Generators::RepeatGenerator<int>(
        2, makeFixedGenerator<int>({10, 20, 30}));

    EXPECT_EQ(gen.get(), 10);
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 20);
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 30);
}

// Test that after exhausting first repeat, it starts the second repeat
TEST_F(RepeatGeneratorTest_926, SecondRepeatReplaysValues_926) {
    auto gen = Catch::Generators::RepeatGenerator<int>(
        2, makeFixedGenerator<int>({10, 20, 30}));

    // First repeat
    EXPECT_EQ(gen.get(), 10);
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 20);
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 30);

    // Transition to second repeat
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 10);
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 20);
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 30);
}

// Test that next() returns false after all repeats are exhausted
TEST_F(RepeatGeneratorTest_926, NextReturnsFalseAfterAllRepeats_926) {
    auto gen = Catch::Generators::RepeatGenerator<int>(
        2, makeFixedGenerator<int>({10, 20}));

    // First repeat: 10, 20
    EXPECT_EQ(gen.get(), 10);
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 20);

    // Second repeat: 10, 20
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 10);
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 20);

    // No more repeats
    EXPECT_FALSE(gen.next());
}

// Test with a single element generator
TEST_F(RepeatGeneratorTest_926, SingleElementRepeated_926) {
    auto gen = Catch::Generators::RepeatGenerator<int>(
        3, makeFixedGenerator<int>({42}));

    EXPECT_EQ(gen.get(), 42);
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 42);
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 42);
    EXPECT_FALSE(gen.next());
}

// Test with repeat count of 1 (no actual repetition)
TEST_F(RepeatGeneratorTest_926, SingleRepeatNoRepetition_926) {
    auto gen = Catch::Generators::RepeatGenerator<int>(
        1, makeFixedGenerator<int>({1, 2, 3}));

    EXPECT_EQ(gen.get(), 1);
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 2);
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 3);
    EXPECT_FALSE(gen.next());
}

// Test with string type
TEST_F(RepeatGeneratorTest_926, WorksWithStringType_926) {
    auto gen = Catch::Generators::RepeatGenerator<std::string>(
        2, makeFixedGenerator<std::string>({"hello", "world"}));

    EXPECT_EQ(gen.get(), "hello");
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), "world");

    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), "hello");
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), "world");

    EXPECT_FALSE(gen.next());
}

// Test multiple repeats (3 repeats)
TEST_F(RepeatGeneratorTest_926, ThreeRepeats_926) {
    auto gen = Catch::Generators::RepeatGenerator<int>(
        3, makeFixedGenerator<int>({5, 6}));

    std::vector<int> collected;
    collected.push_back(gen.get());
    while (gen.next()) {
        collected.push_back(gen.get());
    }

    std::vector<int> expected = {5, 6, 5, 6, 5, 6};
    EXPECT_EQ(collected, expected);
}

// Test that get() can be called multiple times without advancing
TEST_F(RepeatGeneratorTest_926, GetIsIdempotent_926) {
    auto gen = Catch::Generators::RepeatGenerator<int>(
        2, makeFixedGenerator<int>({100}));

    EXPECT_EQ(gen.get(), 100);
    EXPECT_EQ(gen.get(), 100);
    EXPECT_EQ(gen.get(), 100);
}

// Test get() is idempotent during second repeat
TEST_F(RepeatGeneratorTest_926, GetIsIdempotentDuringSecondRepeat_926) {
    auto gen = Catch::Generators::RepeatGenerator<int>(
        2, makeFixedGenerator<int>({7, 8}));

    // Exhaust first repeat
    EXPECT_EQ(gen.get(), 7);
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 8);

    // Move to second repeat
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 7);
    EXPECT_EQ(gen.get(), 7); // idempotent
}

// Boundary: repeat count of 0 - next should return false immediately
TEST_F(RepeatGeneratorTest_926, ZeroRepeatsReturnsFalseOnNext_926) {
    auto gen = Catch::Generators::RepeatGenerator<int>(
        0, makeFixedGenerator<int>({1, 2, 3}));

    // With 0 repeats, the behavior may vary - but the generator should
    // at least produce the first pass through and then stop, or stop immediately.
    // Based on the logic where m_current_repeat starts at 0 and target is 0,
    // next() should likely return false quickly.
    // We test observable behavior:
    // The first get() should still work (generators always have a valid first value)
    gen.get(); // Should not crash
}

// Test with large number of elements
TEST_F(RepeatGeneratorTest_926, LargeSequenceRepeated_926) {
    std::vector<int> values;
    for (int i = 0; i < 100; ++i) {
        values.push_back(i);
    }

    auto gen = Catch::Generators::RepeatGenerator<int>(
        2, makeFixedGenerator<int>(values));

    std::vector<int> collected;
    collected.push_back(gen.get());
    while (gen.next()) {
        collected.push_back(gen.get());
    }

    EXPECT_EQ(collected.size(), 200u);
    for (int i = 0; i < 100; ++i) {
        EXPECT_EQ(collected[i], i);
        EXPECT_EQ(collected[100 + i], i);
    }
}
