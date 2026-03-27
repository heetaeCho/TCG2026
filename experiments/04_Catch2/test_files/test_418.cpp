#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/Catch2/src/catch2/internal/catch_reporter_spec_parser.hpp"



using namespace Catch;

using ::testing::Eq;



class ReporterSpecTest : public ::testing::Test {

protected:

    std::string name = "test_name";

    Optional<std::string> outputFileName = "output.txt";

    Optional<ColourMode> colourMode = ColourMode::Auto;

    std::map<std::string, std::string> customOptions = {{"option1", "value1"}, {"option2", "value2"}};



    ReporterSpec spec = ReporterSpec(name, outputFileName, colourMode, customOptions);

    ReporterSpec defaultSpec = ReporterSpec("default_name", Optional<std::string>(), Optional<ColourMode>(), std::map<std::string, std::string>());

};



TEST_F(ReporterSpecTest_418, ConstructorInitializesFields_418) {

    EXPECT_EQ(spec.name(), name);

    EXPECT_EQ(spec.outputFile(), outputFileName);

    EXPECT_EQ(spec.colourMode(), colourMode);

    EXPECT_EQ(spec.customOptions(), customOptions);

}



TEST_F(ReporterSpecTest_418, DefaultConstructorInitializesDefaultValues_418) {

    EXPECT_EQ(defaultSpec.name(), "default_name");

    EXPECT_EQ(defaultSpec.outputFile(), Optional<std::string>());

    EXPECT_EQ(defaultSpec.colourMode(), Optional<ColourMode>());

    EXPECT_TRUE(defaultSpec.customOptions().empty());

}



TEST_F(ReporterSpecTest_418, EqualityOperatorReturnsTrueForEqualObjects_418) {

    ReporterSpec anotherSpec = ReporterSpec(name, outputFileName, colourMode, customOptions);

    EXPECT_EQ(spec, anotherSpec);

}



TEST_F(ReporterSpecTest_418, EqualityOperatorReturnsFalseForDifferentName_418) {

    ReporterSpec differentNameSpec = ReporterSpec("different_name", outputFileName, colourMode, customOptions);

    EXPECT_NE(spec, differentNameSpec);

}



TEST_F(ReporterSpecTest_418, EqualityOperatorReturnsFalseForDifferentOutputFile_418) {

    ReporterSpec differentOutputFileSpec = ReporterSpec(name, "different_output.txt", colourMode, customOptions);

    EXPECT_NE(spec, differentOutputFileSpec);

}



TEST_F(ReporterSpecTest_418, EqualityOperatorReturnsFalseForDifferentColourMode_418) {

    ReporterSpec differentColourModeSpec = ReporterSpec(name, outputFileName, ColourMode::AlwaysOn, customOptions);

    EXPECT_NE(spec, differentColourModeSpec);

}



TEST_F(ReporterSpecTest_418, EqualityOperatorReturnsFalseForDifferentCustomOptions_418) {

    std::map<std::string, std::string> differentCustomOptions = {{"option1", "different_value"}};

    ReporterSpec differentCustomOptionsSpec = ReporterSpec(name, outputFileName, colourMode, differentCustomOptions);

    EXPECT_NE(spec, differentCustomOptionsSpec);

}
