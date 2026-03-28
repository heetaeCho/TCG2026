#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/internal/catch_reporter_spec_parser.hpp"



using namespace Catch;

using ::testing::Eq;



class ReporterSpecTest : public ::testing::Test {

protected:

    ReporterSpec specWithAllOptions;

    ReporterSpec specWithoutFileAndColour;



    ReporterSpecTest()

        : specWithAllOptions("specName", Optional<std::string>("output.txt"), Optional<ColourMode>(ColourMode::ANSI), std::map<std::string, std::string>{{"key1", "value1"}}),

          specWithoutFileAndColour("specName", Optional<std::string>{}, Optional<ColourMode>{}, std::map<std::string, std::string>{}) {}

};



TEST_F(ReporterSpecTest_Name_ReturnsCorrectValue_419) {

    EXPECT_THAT(specWithAllOptions.name(), Eq("specName"));

}



TEST_F(ReporterSpecTest_OutputFile_ReturnsProvidedValue_419) {

    EXPECT_THAT(*specWithAllOptions.outputFile(), Eq("output.txt"));

}



TEST_F(ReporterSpecTest_OutputFile_ReturnsEmptyWhenNotSet_419) {

    EXPECT_FALSE(specWithoutFileAndColour.outputFile());

}



TEST_F(ReporterSpecTest_ColourMode_ReturnsProvidedValue_419) {

    EXPECT_THAT(*specWithAllOptions.colourMode(), Eq(ColourMode::ANSI));

}



TEST_F(ReporterSpecTest_ColourMode_ReturnsEmptyWhenNotSet_419) {

    EXPECT_FALSE(specWithoutFileAndColour.colourMode());

}



TEST_F(ReporterSpecTest_CustomOptions_ReturnsProvidedMap_419) {

    std::map<std::string, std::string> expected = {{"key1", "value1"}};

    EXPECT_THAT(specWithAllOptions.customOptions(), Eq(expected));

}



TEST_F(ReporterSpecTest_CustomOptions_ReturnsEmptyWhenNotSet_419) {

    std::map<std::string, std::string> expected;

    EXPECT_THAT(specWithoutFileAndColour.customOptions(), Eq(expected));

}
