#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/Catch2/src/catch2/internal/catch_reporter_spec_parser.hpp"

#include <map>



using namespace Catch;

using ::testing::Eq;



class ReporterSpecTest_422 : public ::testing::Test {

protected:

    std::string name = "testReporter";

    Optional<std::string> outputFileName = "output.txt";

    Optional<ColourMode> colourMode = ColourMode::Default;

    std::map<std::string, std::string> customOptions = {{"option1", "value1"}, {"option2", "value2"}};

    ReporterSpec spec = ReporterSpec(name, outputFileName, colourMode, customOptions);

};



TEST_F(ReporterSpecTest_422, CustomOptions_ReturnsCorrectMap_422) {

    EXPECT_EQ(spec.customOptions(), customOptions);

}



TEST_F(ReporterSpecTest_422, Name_ReturnsCorrectName_422) {

    EXPECT_EQ(spec.name(), name);

}



TEST_F(ReporterSpecTest_422, OutputFile_ReturnsCorrectFileName_422) {

    EXPECT_EQ(spec.outputFile(), outputFileName);

}



TEST_F(ReporterSpecTest_422, ColourMode_ReturnsCorrectColourMode_422) {

    EXPECT_EQ(spec.colourMode(), colourMode);

}



TEST_F(ReporterSpecTest_422, CustomOptions_EmptyMap_422) {

    ReporterSpec specEmpty("empty", Optional<std::string>(), Optional<ColourMode>(), std::map<std::string, std::string>());

    EXPECT_TRUE(specEmpty.customOptions().empty());

}



TEST_F(ReporterSpecTest_422, OutputFile_NotSet_ReturnsEmptyOptional_422) {

    ReporterSpec specNoOutput("noOutput", Optional<std::string>(), Optional<ColourMode>(), customOptions);

    EXPECT_FALSE(specNoOutput.outputFile());

}



TEST_F(ReporterSpecTest_422, ColourMode_NotSet_ReturnsEmptyOptional_422) {

    ReporterSpec specNoColour("noColour", outputFileName, Optional<ColourMode>(), customOptions);

    EXPECT_FALSE(specNoColour.colourMode());

}
