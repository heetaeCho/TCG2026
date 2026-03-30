#include <gtest/gtest.h>

#include <Catch2/src/catch2/catch_config.hpp>



using namespace Catch;



// Test fixture for Config class tests

class ConfigTest_732 : public ::testing::Test {

protected:

    ConfigData testData;

    Config config;



    void SetUp() override {

        // Initialize test data with some default values

        testData.rngSeed = 42;

        testData.listTests = false;

        testData.listTags = true;

        testData.reporterSpecifications = { ReporterSpec("console"), ReporterSpec("xml") };

        testData.testsOrTags = { "TestSuite1", "TestSuite2" };

        testData.sectionsToRun = { "Section1", "Section2" };



        config = Config(testData);

    }

};



// Test if rngSeed returns the correct value

TEST_F(ConfigTest_732, RngSeed_ReturnsCorrectValue_732) {

    EXPECT_EQ(config.rngSeed(), 42u);

}



// Test if listTests returns false when not set

TEST_F(ConfigTest_732, ListTests_ReturnsFalse_732) {

    EXPECT_FALSE(config.listTests());

}



// Test if listTags returns true when set

TEST_F(ConfigTest_732, ListTags_ReturnsTrue_732) {

    EXPECT_TRUE(config.listTags());

}



// Test if getReporterSpecs returns the correct vector

TEST_F(ConfigTest_732, GetReporterSpecs_ReturnsCorrectVector_732) {

    std::vector<ReporterSpec> expected = { ReporterSpec("console"), ReporterSpec("xml") };

    EXPECT_EQ(config.getReporterSpecs(), expected);

}



// Test if getTestsOrTags returns the correct vector

TEST_F(ConfigTest_732, GetTestsOrTags_ReturnsCorrectVector_732) {

    std::vector<std::string> expected = { "TestSuite1", "TestSuite2" };

    EXPECT_EQ(config.getTestsOrTags(), expected);

}



// Test if getSectionsToRun returns the correct vector

TEST_F(ConfigTest_732, GetSectionsToRun_ReturnsCorrectVector_732) {

    std::vector<std::string> expected = { "Section1", "Section2" };

    EXPECT_EQ(config.getSectionsToRun(), expected);

}



// Test boundary condition for rngSeed (minimum value)

TEST_F(ConfigTest_732, RngSeed_BoundaryMinimumValue_732) {

    testData.rngSeed = 0;

    Config configMin(testData);

    EXPECT_EQ(configMin.rngSeed(), 0u);

}



// Test boundary condition for rngSeed (maximum value)

TEST_F(ConfigTest_732, RngSeed_BoundaryMaximumValue_732) {

    testData.rngSeed = UINT32_MAX;

    Config configMax(testData);

    EXPECT_EQ(configMax.rngSeed(), UINT32_MAX);

}



// Test if hasTestFilters returns false when no filters are set

TEST_F(ConfigTest_732, HasTestFilters_ReturnsFalse_732) {

    EXPECT_FALSE(config.hasTestFilters());

}
