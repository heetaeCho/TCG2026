#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/Catch2/src/catch2/internal/catch_reporter_spec_parser.hpp"



using namespace Catch;

using ::testing::Eq;



class ReporterSpecTest_420 : public ::testing::Test {

protected:

    std::string name = "dummy_name";

    Optional<std::string> outputFileName = "dummy_output.txt";

    Optional<ColourMode> colourMode = ColourMode::Auto;

    std::map<std::string, std::string> customOptions = {{"option1", "value1"}};



    ReporterSpec reporterSpec;



    ReporterSpecTest_420() 

        : reporterSpec(name, outputFileName, colourMode, customOptions) {}

};



TEST_F(ReporterSpecTest_420, OutputFile_ReturnsCorrectValue_420) {

    EXPECT_EQ(reporterSpec.outputFile(), outputFileName);

}



TEST_F(ReporterSpecTest_420, Name_ReturnsCorrectValue_420) {

    EXPECT_EQ(reporterSpec.name(), name);

}



TEST_F(ReporterSpecTest_420, ColourMode_ReturnsCorrectValue_420) {

    EXPECT_EQ(reporterSpec.colourMode(), colourMode);

}



TEST_F(ReporterSpecTest_420, CustomOptions_ReturnsCorrectValue_420) {

    EXPECT_EQ(reporterSpec.customOptions(), customOptions);

}



TEST_F(ReporterSpecTest_420, OutputFile_NotSet_ReturnsEmptyOptional_420) {

    ReporterSpec specWithoutOutput(name, Optional<std::string>{}, colourMode, customOptions);

    EXPECT_TRUE(!specWithoutOutput.outputFile());

}



TEST_F(ReporterSpecTest_420, EqualityOperator_IdenticalObjects_ReturnTrue_420) {

    ReporterSpec otherSpec(name, outputFileName, colourMode, customOptions);

    EXPECT_TRUE(reporterSpec == otherSpec);

}



TEST_F(ReporterSpecTest_420, EqualityOperator_DifferentName_ReturnFalse_420) {

    ReporterSpec otherSpec("different_name", outputFileName, colourMode, customOptions);

    EXPECT_FALSE(reporterSpec == otherSpec);

}



TEST_F(ReporterSpecTest_420, EqualityOperator_DifferentOutputFile_ReturnFalse_420) {

    ReporterSpec otherSpec(name, Optional<std::string>("other_output.txt"), colourMode, customOptions);

    EXPECT_FALSE(reporterSpec == otherSpec);

}



TEST_F(ReporterSpecTest_420, EqualityOperator_DifferentColourMode_ReturnFalse_420) {

    ReporterSpec otherSpec(name, outputFileName, ColourMode::AlwaysOn, customOptions);

    EXPECT_FALSE(reporterSpec == otherSpec);

}



TEST_F(ReporterSpecTest_420, EqualityOperator_DifferentCustomOptions_ReturnFalse_420) {

    std::map<std::string, std::string> differentOptions = {{"option1", "different_value"}};

    ReporterSpec otherSpec(name, outputFileName, colourMode, differentOptions);

    EXPECT_FALSE(reporterSpec == otherSpec);

}
