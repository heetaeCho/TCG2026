#include <gtest/gtest.h>

#include "catch2/catch_config.hpp"

#include <vector>

#include <string>



using namespace Catch;



// Test Fixture for Config class

class ConfigTest_737 : public ::testing::Test {

protected:

    ConfigData data;

    Config config;



    void SetUp() override {

        // Initialize ConfigData with default values or specific test values

        data.abortAfter = 5; // Example non-default value for testing

        config = Config(data);

    }

};



// Test normal operation of abortAfter()

TEST_F(ConfigTest_737, AbortAfter_ReturnsCorrectValue_737) {

    EXPECT_EQ(config.abortAfter(), 5); // Match the set value in SetUp()

}



// Test boundary condition when abortAfter is set to default

TEST_F(ConfigTest_737, AbortAfter_DefaultValue_ReturnsNegativeOne_737) {

    ConfigData defaultData;

    Config defaultConfig(defaultData);

    EXPECT_EQ(defaultConfig.abortAfter(), -1); // Default value as per provided code

}



// Test normal operation of listTests()

TEST_F(ConfigTest_737, ListTests_ReturnsFalseByDefault_737) {

    EXPECT_FALSE(config.listTests());

}



// Test boundary condition when listTests is explicitly set to true

TEST_F(ConfigTest_737, ListTests_SetToTrue_ReturnsTrue_737) {

    data.listTests = true;

    Config configWithListTests(data);

    EXPECT_TRUE(configWithListTests.listTests());

}



// Test normal operation of showHelp()

TEST_F(ConfigTest_737, ShowHelp_ReturnsFalseByDefault_737) {

    EXPECT_FALSE(config.showHelp());

}



// Test boundary condition when showHelp is explicitly set to true

TEST_F(ConfigTest_737, ShowHelp_SetToTrue_ReturnsTrue_737) {

    data.showHelp = true;

    Config configWithShowHelp(data);

    EXPECT_TRUE(configWithShowHelp.showHelp());

}



// Test normal operation of getTestsOrTags()

TEST_F(ConfigTest_737, GetTestsOrTags_ReturnsEmptyVectorByDefault_737) {

    EXPECT_TRUE(config.getTestsOrTags().empty());

}



// Test boundary condition when testsOrTags is explicitly set

TEST_F(ConfigTest_737, GetTestsOrTags_SetToSpecificValue_ReturnsCorrectVector_737) {

    data.testsOrTags = {"test1", "test2"};

    Config configWithTestsOrTags(data);

    std::vector<std::string> expected = {"test1", "test2"};

    EXPECT_EQ(configWithTestsOrTags.getTestsOrTags(), expected);

}



// Test normal operation of getSectionsToRun()

TEST_F(ConfigTest_737, GetSectionsToRun_ReturnsEmptyVectorByDefault_737) {

    EXPECT_TRUE(config.getSectionsToRun().empty());

}



// Test boundary condition when sectionsToRun is explicitly set

TEST_F(ConfigTest_737, GetSectionsToRun_SetToSpecificValue_ReturnsCorrectVector_737) {

    data.sectionsToRun = {"section1", "section2"};

    Config configWithSectionsToRun(data);

    std::vector<std::string> expected = {"section1", "section2"};

    EXPECT_EQ(configWithSectionsToRun.getSectionsToRun(), expected);

}



// Test normal operation of getReporterSpecs()

TEST_F(ConfigTest_737, GetReporterSpecs_ReturnsEmptyVectorByDefault_737) {

    EXPECT_TRUE(config.getReporterSpecs().empty());

}



// Test normal operation of getProcessedReporterSpecs()

TEST_F(ConfigTest_737, GetProcessedReporterSpecs_ReturnsEmptyVectorByDefault_737) {

    EXPECT_TRUE(config.getProcessedReporterSpecs().empty());

}
