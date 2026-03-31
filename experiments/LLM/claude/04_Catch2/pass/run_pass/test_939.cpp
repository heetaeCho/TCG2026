#include <gtest/gtest.h>
#include <vector>
#include <string>
#include <list>

// We need to include enough of Catch2 to get the IteratorGenerator
// Since we're testing against the amalgamated header, include it
#include "./TestProjects/Catch2/extras/catch_amalgamated.hpp"

using namespace Catch::Generators;

// Test: get() returns the first element after construction with a vector of ints
TEST(IteratorGeneratorTest_939, GetReturnsFirstElement_939) {
    std::vector<int> data = {10, 20, 30};
    IteratorGenerator<int> gen(data.begin(), data.end());
    EXPECT_EQ(gen.get(), 10);
}

// Test: get() returns the same element when called multiple times without next()
TEST(IteratorGeneratorTest_939, GetReturnsSameElementWithoutNext_939) {
    std::vector<int> data = {42, 99};
    IteratorGenerator<int> gen(data.begin(), data.end());
    EXPECT_EQ(gen.get(), 42);
    EXPECT_EQ(gen.get(), 42);
}

// Test: next() advances to the next element
TEST(IteratorGeneratorTest_939, NextAdvancesToNextElement_939) {
    std::vector<int> data = {1, 2, 3};
    IteratorGenerator<int> gen(data.begin(), data.end());
    EXPECT_EQ(gen.get(), 1);
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 2);
}

// Test: next() returns true when there are more elements
TEST(IteratorGeneratorTest_939, NextReturnsTrueWhenMoreElements_939) {
    std::vector<int> data = {1, 2, 3};
    IteratorGenerator<int> gen(data.begin(), data.end());
    EXPECT_TRUE(gen.next());
    EXPECT_TRUE(gen.next());
}

// Test: next() returns false when no more elements
TEST(IteratorGeneratorTest_939, NextReturnsFalseWhenExhausted_939) {
    std::vector<int> data = {1, 2};
    IteratorGenerator<int> gen(data.begin(), data.end());
    EXPECT_TRUE(gen.next());  // advance to element 2
    EXPECT_FALSE(gen.next()); // no more elements
}

// Test: Single element - get returns it, next returns false
TEST(IteratorGeneratorTest_939, SingleElementGetAndNext_939) {
    std::vector<int> data = {77};
    IteratorGenerator<int> gen(data.begin(), data.end());
    EXPECT_EQ(gen.get(), 77);
    EXPECT_FALSE(gen.next());
}

// Test: Iterate through all elements
TEST(IteratorGeneratorTest_939, IterateThroughAllElements_939) {
    std::vector<int> data = {10, 20, 30, 40, 50};
    IteratorGenerator<int> gen(data.begin(), data.end());

    for (int i = 0; i < 5; ++i) {
        EXPECT_EQ(gen.get(), data[i]);
        if (i < 4) {
            EXPECT_TRUE(gen.next());
        } else {
            EXPECT_FALSE(gen.next());
        }
    }
}

// Test: Works with string type
TEST(IteratorGeneratorTest_939, WorksWithStrings_939) {
    std::vector<std::string> data = {"hello", "world", "foo"};
    IteratorGenerator<std::string> gen(data.begin(), data.end());
    EXPECT_EQ(gen.get(), "hello");
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), "world");
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), "foo");
    EXPECT_FALSE(gen.next());
}

// Test: Works with double type
TEST(IteratorGeneratorTest_939, WorksWithDoubles_939) {
    std::vector<double> data = {1.5, 2.5, 3.5};
    IteratorGenerator<double> gen(data.begin(), data.end());
    EXPECT_DOUBLE_EQ(gen.get(), 1.5);
    EXPECT_TRUE(gen.next());
    EXPECT_DOUBLE_EQ(gen.get(), 2.5);
}

// Test: Constructed from a different iterator type (e.g., list iterators)
TEST(IteratorGeneratorTest_939, ConstructedFromListIterators_939) {
    std::list<int> data = {100, 200, 300};
    IteratorGenerator<int> gen(data.begin(), data.end());
    EXPECT_EQ(gen.get(), 100);
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 200);
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 300);
    EXPECT_FALSE(gen.next());
}

// Test: get() returns a const reference
TEST(IteratorGeneratorTest_939, GetReturnsConstReference_939) {
    std::vector<int> data = {5, 10};
    IteratorGenerator<int> gen(data.begin(), data.end());
    const int& ref1 = gen.get();
    const int& ref2 = gen.get();
    // Both calls should return a reference to the same internal element
    EXPECT_EQ(&ref1, &ref2);
    EXPECT_EQ(ref1, 5);
}

// Test: Two elements - verify transition
TEST(IteratorGeneratorTest_939, TwoElementsTransition_939) {
    std::vector<int> data = {1, 2};
    IteratorGenerator<int> gen(data.begin(), data.end());
    EXPECT_EQ(gen.get(), 1);
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 2);
    EXPECT_FALSE(gen.next());
}

// Test: Large number of elements
TEST(IteratorGeneratorTest_939, LargeNumberOfElements_939) {
    std::vector<int> data;
    for (int i = 0; i < 1000; ++i) {
        data.push_back(i);
    }
    IteratorGenerator<int> gen(data.begin(), data.end());
    for (int i = 0; i < 1000; ++i) {
        EXPECT_EQ(gen.get(), i);
        if (i < 999) {
            EXPECT_TRUE(gen.next());
        } else {
            EXPECT_FALSE(gen.next());
        }
    }
}

// Test: Works with pointer-based iterators (raw array)
TEST(IteratorGeneratorTest_939, WorksWithRawArrayPointers_939) {
    int arr[] = {11, 22, 33};
    IteratorGenerator<int> gen(std::begin(arr), std::end(arr));
    EXPECT_EQ(gen.get(), 11);
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 22);
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 33);
    EXPECT_FALSE(gen.next());
}

// Test: After exhaustion, get still returns the last element
TEST(IteratorGeneratorTest_939, GetAfterExhaustionReturnsLastElement_939) {
    std::vector<int> data = {5, 10, 15};
    IteratorGenerator<int> gen(data.begin(), data.end());
    gen.next();
    gen.next();
    // Now exhausted
    EXPECT_FALSE(gen.next());
    // get() should still return the last element
    EXPECT_EQ(gen.get(), 15);
}
