#include <gtest/gtest.h>
#include <vector>
#include <list>
#include <string>
#include <stdexcept>

// Include the header under test
#include "./TestProjects/Catch2/extras/catch_amalgamated.hpp"

using namespace Catch::Generators;

// Test: Construction with a non-empty vector of ints
TEST(IteratorGeneratorTest_1112, ConstructWithNonEmptyIntVector_1112) {
    std::vector<int> v = {1, 2, 3};
    EXPECT_NO_THROW(IteratorGenerator<int>(v.begin(), v.end()));
}

// Test: Construction with empty range throws exception
TEST(IteratorGeneratorTest_1112, ConstructWithEmptyRangeThrows_1112) {
    std::vector<int> v;
    EXPECT_THROW(IteratorGenerator<int>(v.begin(), v.end()), Catch::GeneratorException);
}

// Test: get() returns the first element after construction
TEST(IteratorGeneratorTest_1112, GetReturnsFirstElement_1112) {
    std::vector<int> v = {10, 20, 30};
    IteratorGenerator<int> gen(v.begin(), v.end());
    EXPECT_EQ(gen.get(), 10);
}

// Test: next() advances and get() returns subsequent elements
TEST(IteratorGeneratorTest_1112, NextAdvancesToNextElement_1112) {
    std::vector<int> v = {10, 20, 30};
    IteratorGenerator<int> gen(v.begin(), v.end());
    
    EXPECT_EQ(gen.get(), 10);
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 20);
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 30);
}

// Test: next() returns false when all elements are exhausted
TEST(IteratorGeneratorTest_1112, NextReturnsFalseWhenExhausted_1112) {
    std::vector<int> v = {42};
    IteratorGenerator<int> gen(v.begin(), v.end());
    
    EXPECT_EQ(gen.get(), 42);
    EXPECT_FALSE(gen.next());
}

// Test: Single element - get returns it, next returns false
TEST(IteratorGeneratorTest_1112, SingleElementBehavior_1112) {
    std::vector<int> v = {99};
    IteratorGenerator<int> gen(v.begin(), v.end());
    
    EXPECT_EQ(gen.get(), 99);
    EXPECT_FALSE(gen.next());
}

// Test: Multiple elements - iterate through all
TEST(IteratorGeneratorTest_1112, IterateThroughAllElements_1112) {
    std::vector<int> v = {1, 2, 3, 4, 5};
    IteratorGenerator<int> gen(v.begin(), v.end());
    
    for (int i = 0; i < 5; ++i) {
        EXPECT_EQ(gen.get(), i + 1);
        if (i < 4) {
            EXPECT_TRUE(gen.next());
        } else {
            EXPECT_FALSE(gen.next());
        }
    }
}

// Test: Construction with iterators from a list (not just vector)
TEST(IteratorGeneratorTest_1112, ConstructFromListIterators_1112) {
    std::list<int> lst = {100, 200, 300};
    IteratorGenerator<int> gen(lst.begin(), lst.end());
    
    EXPECT_EQ(gen.get(), 100);
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 200);
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 300);
    EXPECT_FALSE(gen.next());
}

// Test: Construction with string type
TEST(IteratorGeneratorTest_1112, ConstructWithStringType_1112) {
    std::vector<std::string> v = {"hello", "world"};
    IteratorGenerator<std::string> gen(v.begin(), v.end());
    
    EXPECT_EQ(gen.get(), "hello");
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), "world");
    EXPECT_FALSE(gen.next());
}

// Test: Empty list throws
TEST(IteratorGeneratorTest_1112, EmptyListThrows_1112) {
    std::list<double> lst;
    EXPECT_THROW(IteratorGenerator<double>(lst.begin(), lst.end()), Catch::GeneratorException);
}

// Test: Construction from array pointers
TEST(IteratorGeneratorTest_1112, ConstructFromArrayPointers_1112) {
    int arr[] = {7, 8, 9};
    IteratorGenerator<int> gen(std::begin(arr), std::end(arr));
    
    EXPECT_EQ(gen.get(), 7);
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 8);
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 9);
    EXPECT_FALSE(gen.next());
}

// Test: get() is const and returns const reference
TEST(IteratorGeneratorTest_1112, GetIsConst_1112) {
    std::vector<int> v = {5};
    const IteratorGenerator<int> gen(v.begin(), v.end());
    
    const int& val = gen.get();
    EXPECT_EQ(val, 5);
}

// Test: Two elements - next returns true once then false
TEST(IteratorGeneratorTest_1112, TwoElementsNextBehavior_1112) {
    std::vector<double> v = {1.5, 2.5};
    IteratorGenerator<double> gen(v.begin(), v.end());
    
    EXPECT_DOUBLE_EQ(gen.get(), 1.5);
    EXPECT_TRUE(gen.next());
    EXPECT_DOUBLE_EQ(gen.get(), 2.5);
    EXPECT_FALSE(gen.next());
}

// Test: get() returns same value when called multiple times without next()
TEST(IteratorGeneratorTest_1112, GetReturnsSameWithoutNext_1112) {
    std::vector<int> v = {42, 43};
    IteratorGenerator<int> gen(v.begin(), v.end());
    
    EXPECT_EQ(gen.get(), 42);
    EXPECT_EQ(gen.get(), 42);
    EXPECT_EQ(gen.get(), 42);
}

// Test: Partial range construction
TEST(IteratorGeneratorTest_1112, PartialRangeConstruction_1112) {
    std::vector<int> v = {10, 20, 30, 40, 50};
    IteratorGenerator<int> gen(v.begin() + 1, v.begin() + 4);
    
    EXPECT_EQ(gen.get(), 20);
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 30);
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 40);
    EXPECT_FALSE(gen.next());
}

// Test: Large number of elements
TEST(IteratorGeneratorTest_1112, LargeNumberOfElements_1112) {
    std::vector<int> v(1000);
    for (int i = 0; i < 1000; ++i) {
        v[i] = i;
    }
    IteratorGenerator<int> gen(v.begin(), v.end());
    
    for (int i = 0; i < 1000; ++i) {
        EXPECT_EQ(gen.get(), i);
        if (i < 999) {
            EXPECT_TRUE(gen.next());
        } else {
            EXPECT_FALSE(gen.next());
        }
    }
}
