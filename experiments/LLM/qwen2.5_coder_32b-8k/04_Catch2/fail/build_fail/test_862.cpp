#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/reporters/catch_reporter_cumulative_base.hpp"



using namespace Catch;

using namespace Catch::Detail;



class SectionNodeTest : public ::testing::Test {

protected:

    void SetUp() override {

        // Initialize a SectionNode with no assertions or benchmarks

        sectionStats = SectionStats();

        sectionNode = std::make_unique<SectionNode>(sectionStats);

    }



    SectionStats sectionStats;

    std::unique_ptr<SectionNode> sectionNode;

};



TEST_F(SectionNodeTest_862, NoAssertions_ReturnsFalse_862) {

    EXPECT_FALSE(sectionNode->hasAnyAssertions());

}



TEST_F(SectionNodeTest_862, SingleAssertion_ReturnsTrue_862) {

    AssertionStats assertionStats;

    sectionNode->assertionsAndBenchmarks.emplace_back(assertionStats);

    EXPECT_TRUE(sectionNode->hasAnyAssertions());

}



TEST_F(SectionNodeTest_862, MultipleAssertions_ReturnsTrue_862) {

    AssertionStats assertionStats1, assertionStats2;

    sectionNode->assertionsAndBenchmarks.emplace_back(assertionStats1);

    sectionNode->assertionsAndBenchmarks.emplace_back(assertionStats2);

    EXPECT_TRUE(sectionNode->hasAnyAssertions());

}



TEST_F(SectionNodeTest_862, SingleBenchmark_ReturnsFalse_862) {

    BenchmarkStats<> benchmarkStats;

    sectionNode->assertionsAndBenchmarks.emplace_back(benchmarkStats);

    EXPECT_FALSE(sectionNode->hasAnyAssertions());

}



TEST_F(SectionNodeTest_862, MixedAssertionsAndBenchmarks_ReturnsTrue_862) {

    AssertionStats assertionStats;

    BenchmarkStats<> benchmarkStats;

    sectionNode->assertionsAndBenchmarks.emplace_back(benchmarkStats);

    sectionNode->assertionsAndBenchmarks.emplace_back(assertionStats);

    EXPECT_TRUE(sectionNode->hasAnyAssertions());

}
