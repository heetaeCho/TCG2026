#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/Catch2/src/catch2/catch_config.hpp"



using namespace Catch;



// Mock for the ColourMode enum if needed, but since it's an enum, we don't need to mock it.

// Assuming ColourMode is already defined somewhere.



class ProcessedReporterSpecTest : public ::testing::Test {

protected:

    ProcessedReporterSpec lhs;

    ProcessedReporterSpec rhs;

};



TEST_F(ProcessedReporterSpecTest_423, EqualityOperatorReturnsTrueForIdenticalObjects_423) {

    lhs.outputFilename = "output.txt";

    lhs.colourMode = ColourMode::Auto;

    lhs.customOptions = {{"option1", "value1"}, {"option2", "value2"}};



    rhs.outputFilename = "output.txt";

    rhs.colourMode = ColourMode::Auto;

    rhs.customOptions = {{"option1", "value1"}, {"option2", "value2"}};



    EXPECT_TRUE(lhs == rhs);

}



TEST_F(ProcessedReporterSpecTest_423, EqualityOperatorReturnsFalseForDifferentOutputFilename_423) {

    lhs.outputFilename = "output.txt";

    rhs.outputFilename = "different_output.txt";



    EXPECT_FALSE(lhs == rhs);

}



TEST_F(ProcessedReporterSpecTest_423, EqualityOperatorReturnsFalseForDifferentColourMode_423) {

    lhs.colourMode = ColourMode::Auto;

    rhs.colourMode = ColourMode::ForceOff;



    EXPECT_FALSE(lhs == rhs);

}



TEST_F(ProcessedReporterSpecTest_423, EqualityOperatorReturnsFalseForDifferentCustomOptions_423) {

    lhs.customOptions = {{"option1", "value1"}};

    rhs.customOptions = {{"option1", "different_value1"}};



    EXPECT_FALSE(lhs == rhs);

}



TEST_F(ProcessedReporterSpecTest_423, InequalityOperatorReturnsTrueForDifferentObjects_423) {

    lhs.outputFilename = "output.txt";

    lhs.colourMode = ColourMode::Auto;

    lhs.customOptions = {{"option1", "value1"}};



    rhs.outputFilename = "different_output.txt";

    rhs.colourMode = ColourMode::ForceOff;

    rhs.customOptions = {{"option1", "different_value1"}};



    EXPECT_TRUE(lhs != rhs);

}



TEST_F(ProcessedReporterSpecTest_423, InequalityOperatorReturnsFalseForIdenticalObjects_423) {

    lhs.outputFilename = "output.txt";

    lhs.colourMode = ColourMode::Auto;

    lhs.customOptions = {{"option1", "value1"}, {"option2", "value2"}};



    rhs.outputFilename = "output.txt";

    rhs.colourMode = ColourMode::Auto;

    rhs.customOptions = {{"option1", "value1"}, {"option2", "value2"}};



    EXPECT_FALSE(lhs != rhs);

}
