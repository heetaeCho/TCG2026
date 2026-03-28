#include <gtest/gtest.h>
#include "catch2/generators/catch_generators.hpp"

using namespace Catch::Generators;

// Test that a FixedValuesGenerator with a single value returns that value via get()
TEST(FixedValuesGeneratorTest_317, SingleValue_GetReturnsFirstValue_317) {
    FixedValuesGenerator<int> gen({42});
    EXPECT_EQ(gen.get(), 42);
}

// Test that next() returns false when there is only one value (no more values to advance to)
TEST(FixedValuesGeneratorTest_317, SingleValue_NextReturnsFalse_317) {
    FixedValuesGenerator<int> gen({42});
    EXPECT_FALSE(gen.next());
}

// Test that a generator with multiple values starts at the first value
TEST(FixedValuesGeneratorTest_317, MultipleValues_GetReturnsFirstValue_317) {
    FixedValuesGenerator<int> gen({1, 2, 3});
    EXPECT_EQ(gen.get(), 1);
}

// Test that next() advances to the second value and returns true when more values exist
TEST(FixedValuesGeneratorTest_317, MultipleValues_NextAdvancesAndReturnsTrue_317) {
    FixedValuesGenerator<int> gen({1, 2, 3});
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 2);
}

// Test iteration through all values
TEST(FixedValuesGeneratorTest_317, MultipleValues_IterateThroughAll_317) {
    FixedValuesGenerator<int> gen({10, 20, 30});
    
    EXPECT_EQ(gen.get(), 10);
    
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 20);
    
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 30);
    
    EXPECT_FALSE(gen.next());
}

// Test that next() returns false once all values are exhausted
TEST(FixedValuesGeneratorTest_317, MultipleValues_NextReturnsFalseAtEnd_317) {
    FixedValuesGenerator<int> gen({1, 2});
    
    EXPECT_TRUE(gen.next());   // advance to second
    EXPECT_FALSE(gen.next());  // no more values
}

// Test with string type
TEST(FixedValuesGeneratorTest_317, StringValues_IterateCorrectly_317) {
    FixedValuesGenerator<std::string> gen({"hello", "world"});
    
    EXPECT_EQ(gen.get(), "hello");
    
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), "world");
    
    EXPECT_FALSE(gen.next());
}

// Test with two values - boundary
TEST(FixedValuesGeneratorTest_317, TwoValues_BoundaryIteration_317) {
    FixedValuesGenerator<int> gen({100, 200});
    
    EXPECT_EQ(gen.get(), 100);
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 200);
    EXPECT_FALSE(gen.next());
}

// Test with double type
TEST(FixedValuesGeneratorTest_317, DoubleValues_WorkCorrectly_317) {
    FixedValuesGenerator<double> gen({1.5, 2.5, 3.5});
    
    EXPECT_DOUBLE_EQ(gen.get(), 1.5);
    
    EXPECT_TRUE(gen.next());
    EXPECT_DOUBLE_EQ(gen.get(), 2.5);
    
    EXPECT_TRUE(gen.next());
    EXPECT_DOUBLE_EQ(gen.get(), 3.5);
    
    EXPECT_FALSE(gen.next());
}

// Test that get() returns a const reference (doesn't change between calls without next())
TEST(FixedValuesGeneratorTest_317, GetIsStableWithoutNext_317) {
    FixedValuesGenerator<int> gen({7, 8, 9});
    
    EXPECT_EQ(gen.get(), 7);
    EXPECT_EQ(gen.get(), 7);  // calling get() again without next() should return same value
    
    gen.next();
    EXPECT_EQ(gen.get(), 8);
    EXPECT_EQ(gen.get(), 8);
}

// Test with many values to verify full iteration
TEST(FixedValuesGeneratorTest_317, ManyValues_FullIteration_317) {
    FixedValuesGenerator<int> gen({0, 1, 2, 3, 4, 5, 6, 7, 8, 9});
    
    for (int i = 0; i < 10; ++i) {
        EXPECT_EQ(gen.get(), i);
        if (i < 9) {
            EXPECT_TRUE(gen.next());
        } else {
            EXPECT_FALSE(gen.next());
        }
    }
}

// Test with negative values
TEST(FixedValuesGeneratorTest_317, NegativeValues_WorkCorrectly_317) {
    FixedValuesGenerator<int> gen({-3, -2, -1, 0, 1});
    
    EXPECT_EQ(gen.get(), -3);
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), -2);
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), -1);
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 0);
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 1);
    EXPECT_FALSE(gen.next());
}

// Test with duplicate values
TEST(FixedValuesGeneratorTest_317, DuplicateValues_AllPresent_317) {
    FixedValuesGenerator<int> gen({5, 5, 5});
    
    EXPECT_EQ(gen.get(), 5);
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 5);
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 5);
    EXPECT_FALSE(gen.next());
}
