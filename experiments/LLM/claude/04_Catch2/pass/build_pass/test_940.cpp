#include <gtest/gtest.h>
#include <vector>
#include <string>
#include <list>

// We need to include the header that defines IteratorGenerator
#include "./TestProjects/Catch2/extras/catch_amalgamated.hpp"

using namespace Catch::Generators;

// Test with integer elements - basic construction and get
TEST(IteratorGeneratorTest_940, ConstructFromVectorAndGetFirst_940) {
    std::vector<int> v = {10, 20, 30};
    IteratorGenerator<int> gen(v.begin(), v.end());
    EXPECT_EQ(gen.get(), 10);
}

// Test next() returns true when there are more elements
TEST(IteratorGeneratorTest_940, NextReturnsTrueWhenMoreElements_940) {
    std::vector<int> v = {1, 2, 3};
    IteratorGenerator<int> gen(v.begin(), v.end());
    EXPECT_TRUE(gen.next());
}

// Test next() advances to second element
TEST(IteratorGeneratorTest_940, NextAdvancesToSecondElement_940) {
    std::vector<int> v = {10, 20, 30};
    IteratorGenerator<int> gen(v.begin(), v.end());
    gen.next();
    EXPECT_EQ(gen.get(), 20);
}

// Test next() returns false when reaching the end
TEST(IteratorGeneratorTest_940, NextReturnsFalseAtEnd_940) {
    std::vector<int> v = {1, 2};
    IteratorGenerator<int> gen(v.begin(), v.end());
    EXPECT_TRUE(gen.next());   // move to element index 1
    EXPECT_FALSE(gen.next());  // move past last element
}

// Test single element - get returns that element
TEST(IteratorGeneratorTest_940, SingleElementGetReturnsIt_940) {
    std::vector<int> v = {42};
    IteratorGenerator<int> gen(v.begin(), v.end());
    EXPECT_EQ(gen.get(), 42);
}

// Test single element - next returns false immediately
TEST(IteratorGeneratorTest_940, SingleElementNextReturnsFalse_940) {
    std::vector<int> v = {42};
    IteratorGenerator<int> gen(v.begin(), v.end());
    EXPECT_FALSE(gen.next());
}

// Test iterating through all elements
TEST(IteratorGeneratorTest_940, IterateThroughAllElements_940) {
    std::vector<int> v = {1, 2, 3, 4, 5};
    IteratorGenerator<int> gen(v.begin(), v.end());
    
    EXPECT_EQ(gen.get(), 1);
    
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 2);
    
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 3);
    
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 4);
    
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 5);
    
    EXPECT_FALSE(gen.next());
}

// Test with string type
TEST(IteratorGeneratorTest_940, WorksWithStrings_940) {
    std::vector<std::string> v = {"hello", "world", "test"};
    IteratorGenerator<std::string> gen(v.begin(), v.end());
    
    EXPECT_EQ(gen.get(), "hello");
    
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), "world");
    
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), "test");
    
    EXPECT_FALSE(gen.next());
}

// Test with double type
TEST(IteratorGeneratorTest_940, WorksWithDoubles_940) {
    std::vector<double> v = {1.5, 2.5, 3.5};
    IteratorGenerator<double> gen(v.begin(), v.end());
    
    EXPECT_DOUBLE_EQ(gen.get(), 1.5);
    
    EXPECT_TRUE(gen.next());
    EXPECT_DOUBLE_EQ(gen.get(), 2.5);
    
    EXPECT_TRUE(gen.next());
    EXPECT_DOUBLE_EQ(gen.get(), 3.5);
    
    EXPECT_FALSE(gen.next());
}

// Test construction from a different container type (list iterators)
TEST(IteratorGeneratorTest_940, ConstructFromListIterators_940) {
    std::list<int> lst = {100, 200, 300};
    IteratorGenerator<int> gen(lst.begin(), lst.end());
    
    EXPECT_EQ(gen.get(), 100);
    
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 200);
    
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 300);
    
    EXPECT_FALSE(gen.next());
}

// Test get() returns const reference - verify it returns same value on multiple calls
TEST(IteratorGeneratorTest_940, GetReturnsConsistentValue_940) {
    std::vector<int> v = {7, 8, 9};
    IteratorGenerator<int> gen(v.begin(), v.end());
    
    EXPECT_EQ(gen.get(), 7);
    EXPECT_EQ(gen.get(), 7);  // calling get again without next should return same value
}

// Test two elements
TEST(IteratorGeneratorTest_940, TwoElements_940) {
    std::vector<int> v = {10, 20};
    IteratorGenerator<int> gen(v.begin(), v.end());
    
    EXPECT_EQ(gen.get(), 10);
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 20);
    EXPECT_FALSE(gen.next());
}

// Test with larger number of elements
TEST(IteratorGeneratorTest_940, LargeNumberOfElements_940) {
    std::vector<int> v;
    for (int i = 0; i < 1000; ++i) {
        v.push_back(i);
    }
    IteratorGenerator<int> gen(v.begin(), v.end());
    
    EXPECT_EQ(gen.get(), 0);
    
    for (int i = 1; i < 1000; ++i) {
        EXPECT_TRUE(gen.next());
        EXPECT_EQ(gen.get(), i);
    }
    
    EXPECT_FALSE(gen.next());
}

// Test construction from array pointers
TEST(IteratorGeneratorTest_940, ConstructFromArrayPointers_940) {
    int arr[] = {5, 10, 15, 20};
    IteratorGenerator<int> gen(std::begin(arr), std::end(arr));
    
    EXPECT_EQ(gen.get(), 5);
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 10);
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 15);
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 20);
    EXPECT_FALSE(gen.next());
}

// Test with negative values
TEST(IteratorGeneratorTest_940, NegativeValues_940) {
    std::vector<int> v = {-3, -2, -1, 0, 1};
    IteratorGenerator<int> gen(v.begin(), v.end());
    
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
TEST(IteratorGeneratorTest_940, DuplicateValues_940) {
    std::vector<int> v = {5, 5, 5};
    IteratorGenerator<int> gen(v.begin(), v.end());
    
    EXPECT_EQ(gen.get(), 5);
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 5);
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 5);
    EXPECT_FALSE(gen.next());
}
