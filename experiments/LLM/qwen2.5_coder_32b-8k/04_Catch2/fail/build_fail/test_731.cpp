#include <gtest/gtest.h>

#include "catch2/catch_config.hpp"



using namespace Catch;



// Test Fixture for Config class

class ConfigTest_731 : public ::testing::Test {

protected:

    ConfigData data;

    Config config;



    void SetUp() override {

        // Initialize ConfigData with default values or specific values as needed

        data.runOrder = TestRunOrder::Declared;

        config = Config(data);

    }

};



// Test for normal operation of runOrder function

TEST_F(ConfigTest_731, RunOrder_ReturnsCorrectValue_731) {

    EXPECT_EQ(config.runOrder(), TestRunOrder::Declared);

}



// Test for boundary condition when runOrder is set to Random

TEST_F(ConfigTest_731, RunOrder_ReturnsRandomWhenSet_731) {

    data.runOrder = TestRunOrder::Random;

    Config configWithRandom(data);

    EXPECT_EQ(configWithRandom.runOrder(), TestRunOrder::Random);

}



// Test for normal operation of listTests function

TEST_F(ConfigTest_731, ListTests_ReturnsFalseByDefault_731) {

    EXPECT_FALSE(config.listTests());

}



// Test for boundary condition when listTests is set to true

TEST_F(ConfigTest_731, ListTests_ReturnsTrueWhenSet_731) {

    data.listTests = true;

    Config configWithListTests(data);

    EXPECT_TRUE(configWithListTests.listTests());

}



// Test for normal operation of getReporterSpecs function

TEST_F(ConfigTest_731, GetReporterSpecs_ReturnsEmptyVectorByDefault_731) {

    EXPECT_TRUE(config.getReporterSpecs().empty());

}



// Test for boundary condition when reporterSpecifications is not empty

TEST_F(ConfigTest_731, GetReporterSpecs_ReturnsNonEmptyVectorWhenSet_731) {

    ReporterSpec spec;

    data.reporterSpecifications.push_back(spec);

    Config configWithReporters(data);

    EXPECT_FALSE(configWithReporters.getReporterSpecs().empty());

}



// Test for normal operation of getTestsOrTags function

TEST_F(ConfigTest_731, GetTestsOrTags_ReturnsEmptyVectorByDefault_731) {

    EXPECT_TRUE(config.getTestsOrTags().empty());

}



// Test for boundary condition when testsOrTags is not empty

TEST_F(ConfigTest_731, GetTestsOrTags_ReturnsNonEmptyVectorWhenSet_731) {

    data.testsOrTags.push_back("test_case");

    Config configWithTests(data);

    EXPECT_FALSE(configWithTests.getTestsOrTags().empty());

}



// Test for normal operation of getSectionsToRun function

TEST_F(ConfigTest_731, GetSectionsToRun_ReturnsEmptyVectorByDefault_731) {

    EXPECT_TRUE(config.getSectionsToRun().empty());

}



// Test for boundary condition when sectionsToRun is not empty

TEST_F(ConfigTest_731, GetSectionsToRun_ReturnsNonEmptyVectorWhenSet_731) {

    data.sectionsToRun.push_back("section");

    Config configWithSections(data);

    EXPECT_FALSE(configWithSections.getSectionsToRun().empty());

}



// Test for normal operation of hasTestFilters function

TEST_F(ConfigTest_731, HasTestFilters_ReturnsFalseByDefault_731) {

    EXPECT_FALSE(config.hasTestFilters());

}



// Test for boundary condition when testsOrTags is not empty

TEST_F(ConfigTest_731, HasTestFilters_ReturnsTrueWhenTestsOrTagsSet_731) {

    data.testsOrTags.push_back("test_case");

    Config configWithTests(data);

    EXPECT_TRUE(configWithTests.hasTestFilters());

}



// Test for normal operation of showHelp function

TEST_F(ConfigTest_731, ShowHelp_ReturnsFalseByDefault_731) {

    EXPECT_FALSE(config.showHelp());

}



// Test for boundary condition when showHelp is set to true

TEST_F(ConfigTest_731, ShowHelp_ReturnsTrueWhenSet_731) {

    data.showHelp = true;

    Config configWithShowHelp(data);

    EXPECT_TRUE(configWithShowHelp.showHelp());

}



// Test for normal operation of allowThrows function

TEST_F(ConfigTest_731, AllowThrows_ReturnsFalseByDefault_731) {

    EXPECT_FALSE(config.allowThrows());

}



// Test for boundary condition when noThrow is set to false

TEST_F(ConfigTest_731, AllowThrows_ReturnsTrueWhenNoThrowIsFalse_731) {

    data.noThrow = false;

    Config configWithAllowThrows(data);

    EXPECT_TRUE(configWithAllowThrows.allowThrows());

}
