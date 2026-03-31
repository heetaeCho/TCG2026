#include <gtest/gtest.h>
#include "catch2/catch_config.hpp"
#include <string>
#include <map>

using namespace Catch;

class ProcessedReporterSpecTest_423 : public ::testing::Test {
protected:
    ProcessedReporterSpec createSpec(
        const std::string& name,
        const std::string& outputFilename,
        ColourMode colourMode,
        const std::map<std::string, std::string>& customOptions = {}
    ) {
        ProcessedReporterSpec spec;
        spec.name = name;
        spec.outputFilename = outputFilename;
        spec.colourMode = colourMode;
        spec.customOptions = customOptions;
        return spec;
    }
};

TEST_F(ProcessedReporterSpecTest_423, EqualityOfIdenticalSpecs_423) {
    ProcessedReporterSpec a;
    a.name = "console";
    a.outputFilename = "output.txt";
    a.colourMode = ColourMode::PlatformDefault;
    a.customOptions = {{"key1", "val1"}};

    ProcessedReporterSpec b;
    b.name = "console";
    b.outputFilename = "output.txt";
    b.colourMode = ColourMode::PlatformDefault;
    b.customOptions = {{"key1", "val1"}};

    EXPECT_TRUE(a == b);
    EXPECT_FALSE(a != b);
}

TEST_F(ProcessedReporterSpecTest_423, InequalityWhenNameDiffers_423) {
    ProcessedReporterSpec a;
    a.name = "console";
    a.outputFilename = "output.txt";
    a.colourMode = ColourMode::PlatformDefault;

    ProcessedReporterSpec b;
    b.name = "xml";
    b.outputFilename = "output.txt";
    b.colourMode = ColourMode::PlatformDefault;

    EXPECT_FALSE(a == b);
    EXPECT_TRUE(a != b);
}

TEST_F(ProcessedReporterSpecTest_423, InequalityWhenOutputFilenameDiffers_423) {
    ProcessedReporterSpec a;
    a.name = "console";
    a.outputFilename = "file1.txt";
    a.colourMode = ColourMode::PlatformDefault;

    ProcessedReporterSpec b;
    b.name = "console";
    b.outputFilename = "file2.txt";
    b.colourMode = ColourMode::PlatformDefault;

    EXPECT_FALSE(a == b);
    EXPECT_TRUE(a != b);
}

TEST_F(ProcessedReporterSpecTest_423, InequalityWhenColourModeDiffers_423) {
    ProcessedReporterSpec a;
    a.name = "console";
    a.outputFilename = "output.txt";
    a.colourMode = ColourMode::PlatformDefault;

    ProcessedReporterSpec b;
    b.name = "console";
    b.outputFilename = "output.txt";
    b.colourMode = ColourMode::None;

    EXPECT_FALSE(a == b);
    EXPECT_TRUE(a != b);
}

TEST_F(ProcessedReporterSpecTest_423, InequalityWhenCustomOptionsDiffer_423) {
    ProcessedReporterSpec a;
    a.name = "console";
    a.outputFilename = "output.txt";
    a.colourMode = ColourMode::PlatformDefault;
    a.customOptions = {{"key1", "val1"}};

    ProcessedReporterSpec b;
    b.name = "console";
    b.outputFilename = "output.txt";
    b.colourMode = ColourMode::PlatformDefault;
    b.customOptions = {{"key1", "val2"}};

    EXPECT_FALSE(a == b);
    EXPECT_TRUE(a != b);
}

TEST_F(ProcessedReporterSpecTest_423, EqualityWithEmptyCustomOptions_423) {
    ProcessedReporterSpec a;
    a.name = "console";
    a.outputFilename = "";
    a.colourMode = ColourMode::PlatformDefault;
    a.customOptions = {};

    ProcessedReporterSpec b;
    b.name = "console";
    b.outputFilename = "";
    b.colourMode = ColourMode::PlatformDefault;
    b.customOptions = {};

    EXPECT_TRUE(a == b);
    EXPECT_FALSE(a != b);
}

TEST_F(ProcessedReporterSpecTest_423, InequalityWhenOneHasCustomOptionsAndOtherDoesNot_423) {
    ProcessedReporterSpec a;
    a.name = "console";
    a.outputFilename = "";
    a.colourMode = ColourMode::PlatformDefault;
    a.customOptions = {{"key", "value"}};

    ProcessedReporterSpec b;
    b.name = "console";
    b.outputFilename = "";
    b.colourMode = ColourMode::PlatformDefault;
    b.customOptions = {};

    EXPECT_FALSE(a == b);
    EXPECT_TRUE(a != b);
}

TEST_F(ProcessedReporterSpecTest_423, EqualityWithEmptyStrings_423) {
    ProcessedReporterSpec a;
    a.name = "";
    a.outputFilename = "";
    a.colourMode = ColourMode::None;
    a.customOptions = {};

    ProcessedReporterSpec b;
    b.name = "";
    b.outputFilename = "";
    b.colourMode = ColourMode::None;
    b.customOptions = {};

    EXPECT_TRUE(a == b);
    EXPECT_FALSE(a != b);
}

TEST_F(ProcessedReporterSpecTest_423, EqualityWithMultipleCustomOptions_423) {
    ProcessedReporterSpec a;
    a.name = "xml";
    a.outputFilename = "report.xml";
    a.colourMode = ColourMode::ANSI;
    a.customOptions = {{"opt1", "a"}, {"opt2", "b"}, {"opt3", "c"}};

    ProcessedReporterSpec b;
    b.name = "xml";
    b.outputFilename = "report.xml";
    b.colourMode = ColourMode::ANSI;
    b.customOptions = {{"opt1", "a"}, {"opt2", "b"}, {"opt3", "c"}};

    EXPECT_TRUE(a == b);
    EXPECT_FALSE(a != b);
}

TEST_F(ProcessedReporterSpecTest_423, InequalityDifferentCustomOptionKeys_423) {
    ProcessedReporterSpec a;
    a.name = "console";
    a.outputFilename = "";
    a.colourMode = ColourMode::PlatformDefault;
    a.customOptions = {{"keyA", "val"}};

    ProcessedReporterSpec b;
    b.name = "console";
    b.outputFilename = "";
    b.colourMode = ColourMode::PlatformDefault;
    b.customOptions = {{"keyB", "val"}};

    EXPECT_FALSE(a == b);
    EXPECT_TRUE(a != b);
}

TEST_F(ProcessedReporterSpecTest_423, SelfEquality_423) {
    ProcessedReporterSpec a;
    a.name = "reporter";
    a.outputFilename = "file.txt";
    a.colourMode = ColourMode::PlatformDefault;
    a.customOptions = {{"x", "y"}};

    EXPECT_TRUE(a == a);
    EXPECT_FALSE(a != a);
}

TEST_F(ProcessedReporterSpecTest_423, NotEqualIsNegationOfEqual_423) {
    ProcessedReporterSpec a;
    a.name = "console";
    a.outputFilename = "a.txt";
    a.colourMode = ColourMode::PlatformDefault;

    ProcessedReporterSpec b;
    b.name = "console";
    b.outputFilename = "b.txt";
    b.colourMode = ColourMode::PlatformDefault;

    // Verify that != is exactly the negation of ==
    EXPECT_EQ((a != b), !(a == b));

    b.outputFilename = "a.txt";
    EXPECT_EQ((a != b), !(a == b));
}
