#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>
#include <catch2/generators/catch_generators_adapters.hpp>
#include <catch2/generators/catch_generators_random.hpp>

// We need to include the amalgamated header for RepeatGenerator
#include "catch_amalgamated.hpp"

#include <gtest/gtest.h>
#include <vector>
#include <string>

using namespace Catch::Generators;

// Helper: create a simple fixed generator wrapper
template <typename T>
GeneratorWrapper<T> makeFixedGenerator(std::initializer_list<T> values) {
    // Use Catch2's values/from_range approach
    std::vector<T> v(values);
    return GeneratorWrapper<T>(
        Catch::Detail::make_unique<Catch::Generators::FixedValuesGenerator<T>>(CATCH_MOVE(v))
    );
}

class RepeatGeneratorTest_1109 : public ::testing::Test {
protected:
};

// Test that RepeatGenerator returns the first value from the wrapped generator on get()
TEST_F(RepeatGeneratorTest_1109, InitialGetReturnsFirstValue_1109) {
    std::vector<int> vals = {10, 20, 30};
    auto gen = RepeatGenerator<int>(2, 
        GeneratorWrapper<int>(
            Catch::Detail::make_unique<FixedValuesGenerator<int>>(CATCH_MOVE(vals))
        )
    );
    
    EXPECT_EQ(gen.get(), 10);
}

// Test that next() advances through the inner generator values
TEST_F(RepeatGeneratorTest_1109, NextAdvancesThroughValues_1109) {
    std::vector<int> vals = {1, 2, 3};
    auto gen = RepeatGenerator<int>(1, 
        GeneratorWrapper<int>(
            Catch::Detail::make_unique<FixedValuesGenerator<int>>(CATCH_MOVE(vals))
        )
    );
    
    EXPECT_EQ(gen.get(), 1);
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 2);
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 3);
    EXPECT_FALSE(gen.next()); // Only 1 repeat, so done after exhausting values
}

// Test that RepeatGenerator repeats the sequence the specified number of times
TEST_F(RepeatGeneratorTest_1109, RepeatsSequenceMultipleTimes_1109) {
    std::vector<int> vals = {1, 2};
    auto gen = RepeatGenerator<int>(3, 
        GeneratorWrapper<int>(
            Catch::Detail::make_unique<FixedValuesGenerator<int>>(CATCH_MOVE(vals))
        )
    );
    
    std::vector<int> collected;
    collected.push_back(gen.get());
    while (gen.next()) {
        collected.push_back(gen.get());
    }
    
    // 2 values repeated 3 times = 6 total values
    ASSERT_EQ(collected.size(), 6u);
    EXPECT_EQ(collected[0], 1);
    EXPECT_EQ(collected[1], 2);
    EXPECT_EQ(collected[2], 1);
    EXPECT_EQ(collected[3], 2);
    EXPECT_EQ(collected[4], 1);
    EXPECT_EQ(collected[5], 2);
}

// Test with a single element repeated multiple times
TEST_F(RepeatGeneratorTest_1109, SingleElementRepeated_1109) {
    std::vector<int> vals = {42};
    auto gen = RepeatGenerator<int>(4, 
        GeneratorWrapper<int>(
            Catch::Detail::make_unique<FixedValuesGenerator<int>>(CATCH_MOVE(vals))
        )
    );
    
    std::vector<int> collected;
    collected.push_back(gen.get());
    while (gen.next()) {
        collected.push_back(gen.get());
    }
    
    ASSERT_EQ(collected.size(), 4u);
    for (auto& v : collected) {
        EXPECT_EQ(v, 42);
    }
}

// Test with repeat count of 1 (minimum valid repeat)
TEST_F(RepeatGeneratorTest_1109, SingleRepeatExhaustsNormally_1109) {
    std::vector<int> vals = {5, 10, 15};
    auto gen = RepeatGenerator<int>(1, 
        GeneratorWrapper<int>(
            Catch::Detail::make_unique<FixedValuesGenerator<int>>(CATCH_MOVE(vals))
        )
    );
    
    std::vector<int> collected;
    collected.push_back(gen.get());
    while (gen.next()) {
        collected.push_back(gen.get());
    }
    
    ASSERT_EQ(collected.size(), 3u);
    EXPECT_EQ(collected[0], 5);
    EXPECT_EQ(collected[1], 10);
    EXPECT_EQ(collected[2], 15);
}

// Test with string type to verify template works for non-integer types
TEST_F(RepeatGeneratorTest_1109, WorksWithStringType_1109) {
    std::vector<std::string> vals = {"hello", "world"};
    auto gen = RepeatGenerator<std::string>(2, 
        GeneratorWrapper<std::string>(
            Catch::Detail::make_unique<FixedValuesGenerator<std::string>>(CATCH_MOVE(vals))
        )
    );
    
    std::vector<std::string> collected;
    collected.push_back(gen.get());
    while (gen.next()) {
        collected.push_back(gen.get());
    }
    
    ASSERT_EQ(collected.size(), 4u);
    EXPECT_EQ(collected[0], "hello");
    EXPECT_EQ(collected[1], "world");
    EXPECT_EQ(collected[2], "hello");
    EXPECT_EQ(collected[3], "world");
}

// Test that next() returns false after all repeats are exhausted
TEST_F(RepeatGeneratorTest_1109, NextReturnsFalseWhenExhausted_1109) {
    std::vector<int> vals = {1};
    auto gen = RepeatGenerator<int>(2, 
        GeneratorWrapper<int>(
            Catch::Detail::make_unique<FixedValuesGenerator<int>>(CATCH_MOVE(vals))
        )
    );
    
    EXPECT_EQ(gen.get(), 1);
    EXPECT_TRUE(gen.next());  // Second repeat
    EXPECT_EQ(gen.get(), 1);
    EXPECT_FALSE(gen.next()); // Exhausted
}

// Test get() returns consistent value without calling next()
TEST_F(RepeatGeneratorTest_1109, GetIsIdempotent_1109) {
    std::vector<int> vals = {99};
    auto gen = RepeatGenerator<int>(1, 
        GeneratorWrapper<int>(
            Catch::Detail::make_unique<FixedValuesGenerator<int>>(CATCH_MOVE(vals))
        )
    );
    
    EXPECT_EQ(gen.get(), 99);
    EXPECT_EQ(gen.get(), 99);
    EXPECT_EQ(gen.get(), 99);
}

// Test with large repeat count
TEST_F(RepeatGeneratorTest_1109, LargeRepeatCount_1109) {
    std::vector<int> vals = {7};
    auto gen = RepeatGenerator<int>(1000, 
        GeneratorWrapper<int>(
            Catch::Detail::make_unique<FixedValuesGenerator<int>>(CATCH_MOVE(vals))
        )
    );
    
    size_t count = 1; // initial get
    while (gen.next()) {
        EXPECT_EQ(gen.get(), 7);
        count++;
    }
    EXPECT_EQ(count, 1000u);
}

// Test boundary: repeat count of 0 should trigger assertion (death test)
TEST_F(RepeatGeneratorTest_1109, ZeroRepeatsAssertion_1109) {
    EXPECT_DEATH({
        std::vector<int> vals = {1};
        RepeatGenerator<int>(0, 
            GeneratorWrapper<int>(
                Catch::Detail::make_unique<FixedValuesGenerator<int>>(CATCH_MOVE(vals))
            )
        );
    }, "");
}

// Test with multiple elements and two repeats ensuring order
TEST_F(RepeatGeneratorTest_1109, MultipleElementsOrderPreserved_1109) {
    std::vector<int> vals = {100, 200, 300, 400};
    auto gen = RepeatGenerator<int>(2, 
        GeneratorWrapper<int>(
            Catch::Detail::make_unique<FixedValuesGenerator<int>>(CATCH_MOVE(vals))
        )
    );
    
    std::vector<int> collected;
    collected.push_back(gen.get());
    while (gen.next()) {
        collected.push_back(gen.get());
    }
    
    std::vector<int> expected = {100, 200, 300, 400, 100, 200, 300, 400};
    ASSERT_EQ(collected.size(), expected.size());
    for (size_t i = 0; i < expected.size(); ++i) {
        EXPECT_EQ(collected[i], expected[i]) << "Mismatch at index " << i;
    }
}
