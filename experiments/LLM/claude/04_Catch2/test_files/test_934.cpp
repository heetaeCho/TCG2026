#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>
#include <catch2/generators/catch_generators_adapters.hpp>
#include <catch2/generators/catch_generators_random.hpp>

// Since we need to test with Google Test framework, we include the amalgamated header
// and use gtest
#include "catch_amalgamated.hpp"
#include <gtest/gtest.h>
#include <vector>
#include <string>

using namespace Catch::Generators;

class ChunkGeneratorTest_934 : public ::testing::Test {
protected:
};

TEST_F(ChunkGeneratorTest_934, ChunkOfSizeOneProducesSingleElementVectors_934) {
    // Create a generator that yields values 1, 2, 3
    auto gen = chunk(1, values<int>({1, 2, 3}));
    
    std::vector<int> expected1 = {1};
    EXPECT_EQ(gen.get(), expected1);
    
    EXPECT_TRUE(gen.next());
    std::vector<int> expected2 = {2};
    EXPECT_EQ(gen.get(), expected2);
    
    EXPECT_TRUE(gen.next());
    std::vector<int> expected3 = {3};
    EXPECT_EQ(gen.get(), expected3);
    
    EXPECT_FALSE(gen.next());
}

TEST_F(ChunkGeneratorTest_934, ChunkOfSizeTwoGroupsElementsInPairs_934) {
    auto gen = chunk(2, values<int>({1, 2, 3, 4}));
    
    std::vector<int> expected1 = {1, 2};
    EXPECT_EQ(gen.get(), expected1);
    
    EXPECT_TRUE(gen.next());
    std::vector<int> expected2 = {3, 4};
    EXPECT_EQ(gen.get(), expected2);
    
    EXPECT_FALSE(gen.next());
}

TEST_F(ChunkGeneratorTest_934, ChunkOfSizeThreeGroupsElements_934) {
    auto gen = chunk(3, values<int>({1, 2, 3, 4, 5, 6}));
    
    std::vector<int> expected1 = {1, 2, 3};
    EXPECT_EQ(gen.get(), expected1);
    
    EXPECT_TRUE(gen.next());
    std::vector<int> expected2 = {4, 5, 6};
    EXPECT_EQ(gen.get(), expected2);
    
    EXPECT_FALSE(gen.next());
}

TEST_F(ChunkGeneratorTest_934, ChunkSizeEqualsNumberOfElements_934) {
    auto gen = chunk(4, values<int>({10, 20, 30, 40}));
    
    std::vector<int> expected = {10, 20, 30, 40};
    EXPECT_EQ(gen.get(), expected);
    
    EXPECT_FALSE(gen.next());
}

TEST_F(ChunkGeneratorTest_934, ChunkWithStringType_934) {
    auto gen = chunk(2, values<std::string>({"hello", "world", "foo", "bar"}));
    
    std::vector<std::string> expected1 = {"hello", "world"};
    EXPECT_EQ(gen.get(), expected1);
    
    EXPECT_TRUE(gen.next());
    std::vector<std::string> expected2 = {"foo", "bar"};
    EXPECT_EQ(gen.get(), expected2);
    
    EXPECT_FALSE(gen.next());
}

TEST_F(ChunkGeneratorTest_934, ChunkFirstGetReturnsFirstChunk_934) {
    auto gen = chunk(2, values<int>({5, 10, 15, 20}));
    
    // Calling get() multiple times without next() should return same value
    std::vector<int> expected = {5, 10};
    EXPECT_EQ(gen.get(), expected);
    EXPECT_EQ(gen.get(), expected);
}

TEST_F(ChunkGeneratorTest_934, ChunkWithSingleElement_934) {
    auto gen = chunk(1, values<int>({42}));
    
    std::vector<int> expected = {42};
    EXPECT_EQ(gen.get(), expected);
    
    EXPECT_FALSE(gen.next());
}

TEST_F(ChunkGeneratorTest_934, ChunkWithDoubleType_934) {
    auto gen = chunk(2, values<double>({1.5, 2.5, 3.5, 4.5}));
    
    std::vector<double> expected1 = {1.5, 2.5};
    EXPECT_EQ(gen.get(), expected1);
    
    EXPECT_TRUE(gen.next());
    std::vector<double> expected2 = {3.5, 4.5};
    EXPECT_EQ(gen.get(), expected2);
    
    EXPECT_FALSE(gen.next());
}
