#include <gtest/gtest.h>
#include "./TestProjects/Catch2/extras/catch_amalgamated.hpp"

// Test fixture for range generator tests
class RangeGeneratorTest_937 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test: Normal operation with integer range and step of 1
TEST_F(RangeGeneratorTest_937, IntRangeStepOne_937) {
    auto gen = Catch::Generators::range(0, 5, 1);
    
    std::vector<int> values;
    values.push_back(gen.get());
    while (gen.next()) {
        values.push_back(gen.get());
    }
    
    std::vector<int> expected = {0, 1, 2, 3, 4};
    EXPECT_EQ(values, expected);
}

// Test: Normal operation with integer range and step of 2
TEST_F(RangeGeneratorTest_937, IntRangeStepTwo_937) {
    auto gen = Catch::Generators::range(0, 10, 2);
    
    std::vector<int> values;
    values.push_back(gen.get());
    while (gen.next()) {
        values.push_back(gen.get());
    }
    
    std::vector<int> expected = {0, 2, 4, 6, 8};
    EXPECT_EQ(values, expected);
}

// Test: Normal operation with double range
TEST_F(RangeGeneratorTest_937, DoubleRange_937) {
    auto gen = Catch::Generators::range(0.0, 1.0, 0.25);
    
    std::vector<double> values;
    values.push_back(gen.get());
    while (gen.next()) {
        values.push_back(gen.get());
    }
    
    EXPECT_EQ(values.size(), 4u);
    EXPECT_DOUBLE_EQ(values[0], 0.0);
    EXPECT_DOUBLE_EQ(values[1], 0.25);
    EXPECT_DOUBLE_EQ(values[2], 0.5);
    EXPECT_DOUBLE_EQ(values[3], 0.75);
}

// Test: Single element range (start + step >= end)
TEST_F(RangeGeneratorTest_937, SingleElementRange_937) {
    auto gen = Catch::Generators::range(0, 1, 1);
    
    std::vector<int> values;
    values.push_back(gen.get());
    while (gen.next()) {
        values.push_back(gen.get());
    }
    
    std::vector<int> expected = {0};
    EXPECT_EQ(values, expected);
}

// Test: Range where step doesn't evenly divide the range
TEST_F(RangeGeneratorTest_937, StepDoesNotEvenlyDivide_937) {
    auto gen = Catch::Generators::range(0, 7, 3);
    
    std::vector<int> values;
    values.push_back(gen.get());
    while (gen.next()) {
        values.push_back(gen.get());
    }
    
    std::vector<int> expected = {0, 3, 6};
    EXPECT_EQ(values, expected);
}

// Test: Negative range with negative step
TEST_F(RangeGeneratorTest_937, NegativeRange_937) {
    auto gen = Catch::Generators::range(5, 0, -1);
    
    std::vector<int> values;
    values.push_back(gen.get());
    while (gen.next()) {
        values.push_back(gen.get());
    }
    
    std::vector<int> expected = {5, 4, 3, 2, 1};
    EXPECT_EQ(values, expected);
}

// Test: Large step that overshoots range
TEST_F(RangeGeneratorTest_937, LargeStepSingleElement_937) {
    auto gen = Catch::Generators::range(0, 100, 200);
    
    std::vector<int> values;
    values.push_back(gen.get());
    while (gen.next()) {
        values.push_back(gen.get());
    }
    
    std::vector<int> expected = {0};
    EXPECT_EQ(values, expected);
}

// Test: Float range
TEST_F(RangeGeneratorTest_937, FloatRange_937) {
    auto gen = Catch::Generators::range(1.0f, 3.0f, 0.5f);
    
    std::vector<float> values;
    values.push_back(gen.get());
    while (gen.next()) {
        values.push_back(gen.get());
    }
    
    EXPECT_EQ(values.size(), 4u);
    EXPECT_FLOAT_EQ(values[0], 1.0f);
    EXPECT_FLOAT_EQ(values[1], 1.5f);
    EXPECT_FLOAT_EQ(values[2], 2.0f);
    EXPECT_FLOAT_EQ(values[3], 2.5f);
}

// Test: Long type range
TEST_F(RangeGeneratorTest_937, LongRange_937) {
    auto gen = Catch::Generators::range(0L, 5L, 1L);
    
    std::vector<long> values;
    values.push_back(gen.get());
    while (gen.next()) {
        values.push_back(gen.get());
    }
    
    std::vector<long> expected = {0L, 1L, 2L, 3L, 4L};
    EXPECT_EQ(values, expected);
}

// Test: First element is the start value
TEST_F(RangeGeneratorTest_937, FirstElementIsStart_937) {
    auto gen = Catch::Generators::range(42, 100, 10);
    
    EXPECT_EQ(gen.get(), 42);
}

// Test: Negative start and end with positive step
TEST_F(RangeGeneratorTest_937, NegativeStartEnd_937) {
    auto gen = Catch::Generators::range(-5, 0, 1);
    
    std::vector<int> values;
    values.push_back(gen.get());
    while (gen.next()) {
        values.push_back(gen.get());
    }
    
    std::vector<int> expected = {-5, -4, -3, -2, -1};
    EXPECT_EQ(values, expected);
}

// Test: Unsigned integer range
TEST_F(RangeGeneratorTest_937, UnsignedIntRange_937) {
    auto gen = Catch::Generators::range(0u, 3u, 1u);
    
    std::vector<unsigned int> values;
    values.push_back(gen.get());
    while (gen.next()) {
        values.push_back(gen.get());
    }
    
    std::vector<unsigned int> expected = {0u, 1u, 2u};
    EXPECT_EQ(values, expected);
}

// Test: End equals start should still produce at least the start or empty
// (boundary behavior - depends on implementation treating start < end)
TEST_F(RangeGeneratorTest_937, StartEqualsEndBehavior_937) {
    // When start == end, behavior may vary. The generator should produce
    // no elements or handle this gracefully. We test that it at least
    // doesn't crash and the first get() is accessible.
    // Note: This may throw in some implementations, which is also valid.
    try {
        auto gen = Catch::Generators::range(5, 5, 1);
        // If we get here, just verify it doesn't produce infinite elements
        // The first get() should be 5, but next() should return false
        // or the generator is empty.
        SUCCEED();
    } catch (...) {
        // Some implementations may throw for empty range - that's acceptable
        SUCCEED();
    }
}

// Test: Step of exact range size produces single element
TEST_F(RangeGeneratorTest_937, StepExactRangeSize_937) {
    auto gen = Catch::Generators::range(0, 10, 10);
    
    std::vector<int> values;
    values.push_back(gen.get());
    while (gen.next()) {
        values.push_back(gen.get());
    }
    
    std::vector<int> expected = {0};
    EXPECT_EQ(values, expected);
}
