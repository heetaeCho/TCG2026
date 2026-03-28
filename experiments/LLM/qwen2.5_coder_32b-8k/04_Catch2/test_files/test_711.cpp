#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch_config.hpp"



using namespace Catch;

using ::testing::Eq;



TEST(ProcessedReporterSpecTest_711, EqualityOperator_SameValues_ReturnsTrue_711) {

    ProcessedReporterSpec spec1 = {"output.txt", ColourMode::Auto, {{"option1", "value1"}, {"option2", "value2"}}};

    ProcessedReporterSpec spec2 = {"output.txt", ColourMode::Auto, {{"option1", "value1"}, {"option2", "value2"}}};



    EXPECT_TRUE(spec1 == spec2);

}



TEST(ProcessedReporterSpecTest_711, EqualityOperator_DifferentOutputFilename_ReturnsFalse_711) {

    ProcessedReporterSpec spec1 = {"output.txt", ColourMode::Auto, {{"option1", "value1"}, {"option2", "value2"}}};

    ProcessedReporterSpec spec2 = {"different_output.txt", ColourMode::Auto, {{"option1", "value1"}, {"option2", "value2"}}};



    EXPECT_FALSE(spec1 == spec2);

}



TEST(ProcessedReporterSpecTest_711, EqualityOperator_DifferentColourMode_ReturnsFalse_711) {

    ProcessedReporterSpec spec1 = {"output.txt", ColourMode::Auto, {{"option1", "value1"}, {"option2", "value2"}}};

    ProcessedReporterSpec spec2 = {"output.txt", ColourMode::ForceOn, {{"option1", "value1"}, {"option2", "value2"}}};



    EXPECT_FALSE(spec1 == spec2);

}



TEST(ProcessedReporterSpecTest_711, EqualityOperator_DifferentCustomOptions_ReturnsFalse_711) {

    ProcessedReporterSpec spec1 = {"output.txt", ColourMode::Auto, {{"option1", "value1"}, {"option2", "value2"}}};

    ProcessedReporterSpec spec2 = {"output.txt", ColourMode::Auto, {{"option1", "different_value"}, {"option2", "value2"}}};



    EXPECT_FALSE(spec1 == spec2);

}



TEST(ProcessedReporterSpecTest_711, EqualityOperator_EmptyCustomOptions_ReturnsTrue_711) {

    ProcessedReporterSpec spec1 = {"output.txt", ColourMode::Auto, {}};

    ProcessedReporterSpec spec2 = {"output.txt", ColourMode::Auto, {}};



    EXPECT_TRUE(spec1 == spec2);

}
