#include "catch2/internal/catch_reporter_spec_parser.hpp"
#include <gtest/gtest.h>
#include <string>
#include <map>

using namespace Catch;

class ReporterSpecTest_690 : public ::testing::Test {
protected:
    // Helper to create a basic ReporterSpec
    ReporterSpec makeSpec(
        std::string name,
        Optional<std::string> outputFileName = {},
        Optional<ColourMode> colourMode = {},
        std::map<std::string, std::string> customOptions = {}
    ) {
        return ReporterSpec(
            std::move(name),
            std::move(outputFileName),
            std::move(colourMode),
            std::move(customOptions)
        );
    }
};

// Test that the constructor correctly sets the name
TEST_F(ReporterSpecTest_690, ConstructorSetsName_690) {
    ReporterSpec spec = makeSpec("console");
    EXPECT_EQ(spec.name(), "console");
}

// Test that the constructor correctly sets the output file name
TEST_F(ReporterSpecTest_690, ConstructorSetsOutputFileName_690) {
    ReporterSpec spec = makeSpec("console", std::string("output.txt"));
    ASSERT_TRUE(spec.outputFile().has_value());
    EXPECT_EQ(*spec.outputFile(), "output.txt");
}

// Test that the constructor correctly handles no output file name
TEST_F(ReporterSpecTest_690, ConstructorNoOutputFileName_690) {
    ReporterSpec spec = makeSpec("console");
    EXPECT_FALSE(spec.outputFile().has_value());
}

// Test that the constructor correctly sets the colour mode
TEST_F(ReporterSpecTest_690, ConstructorSetsColourMode_690) {
    ReporterSpec spec = makeSpec("console", {}, ColourMode::ANSI);
    ASSERT_TRUE(spec.colourMode().has_value());
    EXPECT_EQ(*spec.colourMode(), ColourMode::ANSI);
}

// Test that the constructor correctly handles no colour mode
TEST_F(ReporterSpecTest_690, ConstructorNoColourMode_690) {
    ReporterSpec spec = makeSpec("console");
    EXPECT_FALSE(spec.colourMode().has_value());
}

// Test that the constructor correctly sets custom options
TEST_F(ReporterSpecTest_690, ConstructorSetsCustomOptions_690) {
    std::map<std::string, std::string> opts = {{"key1", "val1"}, {"key2", "val2"}};
    ReporterSpec spec = makeSpec("console", {}, {}, opts);
    EXPECT_EQ(spec.customOptions().size(), 2u);
    EXPECT_EQ(spec.customOptions().at("key1"), "val1");
    EXPECT_EQ(spec.customOptions().at("key2"), "val2");
}

// Test that custom options is empty when none provided
TEST_F(ReporterSpecTest_690, ConstructorEmptyCustomOptions_690) {
    ReporterSpec spec = makeSpec("console");
    EXPECT_TRUE(spec.customOptions().empty());
}

// Test equality of two identical ReporterSpecs
TEST_F(ReporterSpecTest_690, EqualityIdenticalSpecs_690) {
    ReporterSpec spec1 = makeSpec("console", std::string("out.txt"), ColourMode::ANSI, {{"k", "v"}});
    ReporterSpec spec2 = makeSpec("console", std::string("out.txt"), ColourMode::ANSI, {{"k", "v"}});
    EXPECT_TRUE(spec1 == spec2);
}

// Test equality with all defaults
TEST_F(ReporterSpecTest_690, EqualityDefaultSpecs_690) {
    ReporterSpec spec1 = makeSpec("xml");
    ReporterSpec spec2 = makeSpec("xml");
    EXPECT_TRUE(spec1 == spec2);
}

// Test inequality when names differ
TEST_F(ReporterSpecTest_690, InequalityDifferentNames_690) {
    ReporterSpec spec1 = makeSpec("console");
    ReporterSpec spec2 = makeSpec("xml");
    EXPECT_FALSE(spec1 == spec2);
}

// Test inequality when output file names differ
TEST_F(ReporterSpecTest_690, InequalityDifferentOutputFileNames_690) {
    ReporterSpec spec1 = makeSpec("console", std::string("out1.txt"));
    ReporterSpec spec2 = makeSpec("console", std::string("out2.txt"));
    EXPECT_FALSE(spec1 == spec2);
}

// Test inequality when one has output file and other doesn't
TEST_F(ReporterSpecTest_690, InequalityOneHasOutputFile_690) {
    ReporterSpec spec1 = makeSpec("console", std::string("out.txt"));
    ReporterSpec spec2 = makeSpec("console");
    EXPECT_FALSE(spec1 == spec2);
}

// Test inequality when colour modes differ
TEST_F(ReporterSpecTest_690, InequalityDifferentColourModes_690) {
    ReporterSpec spec1 = makeSpec("console", {}, ColourMode::ANSI);
    ReporterSpec spec2 = makeSpec("console", {}, ColourMode::None);
    EXPECT_FALSE(spec1 == spec2);
}

// Test inequality when one has colour mode and other doesn't
TEST_F(ReporterSpecTest_690, InequalityOneHasColourMode_690) {
    ReporterSpec spec1 = makeSpec("console", {}, ColourMode::ANSI);
    ReporterSpec spec2 = makeSpec("console");
    EXPECT_FALSE(spec1 == spec2);
}

// Test inequality when custom options differ
TEST_F(ReporterSpecTest_690, InequalityDifferentCustomOptions_690) {
    ReporterSpec spec1 = makeSpec("console", {}, {}, {{"k1", "v1"}});
    ReporterSpec spec2 = makeSpec("console", {}, {}, {{"k2", "v2"}});
    EXPECT_FALSE(spec1 == spec2);
}

// Test inequality when one has custom options and other doesn't
TEST_F(ReporterSpecTest_690, InequalityOneHasCustomOptions_690) {
    ReporterSpec spec1 = makeSpec("console", {}, {}, {{"k", "v"}});
    ReporterSpec spec2 = makeSpec("console");
    EXPECT_FALSE(spec1 == spec2);
}

// Test with empty name
TEST_F(ReporterSpecTest_690, EmptyName_690) {
    ReporterSpec spec = makeSpec("");
    EXPECT_EQ(spec.name(), "");
}

// Test equality with empty names
TEST_F(ReporterSpecTest_690, EqualityEmptyNames_690) {
    ReporterSpec spec1 = makeSpec("");
    ReporterSpec spec2 = makeSpec("");
    EXPECT_TRUE(spec1 == spec2);
}

// Test with all fields populated
TEST_F(ReporterSpecTest_690, AllFieldsPopulated_690) {
    std::map<std::string, std::string> opts = {{"opt1", "val1"}, {"opt2", "val2"}};
    ReporterSpec spec = makeSpec("junit", std::string("results.xml"), ColourMode::ANSI, opts);
    
    EXPECT_EQ(spec.name(), "junit");
    ASSERT_TRUE(spec.outputFile().has_value());
    EXPECT_EQ(*spec.outputFile(), "results.xml");
    ASSERT_TRUE(spec.colourMode().has_value());
    EXPECT_EQ(*spec.colourMode(), ColourMode::ANSI);
    EXPECT_EQ(spec.customOptions().size(), 2u);
}

// Test that custom options with same keys but different values are not equal
TEST_F(ReporterSpecTest_690, InequalitySameKeysDifferentValues_690) {
    ReporterSpec spec1 = makeSpec("console", {}, {}, {{"key", "value1"}});
    ReporterSpec spec2 = makeSpec("console", {}, {}, {{"key", "value2"}});
    EXPECT_FALSE(spec1 == spec2);
}

// Test equality with multiple custom options in same order
TEST_F(ReporterSpecTest_690, EqualityMultipleCustomOptionsSameOrder_690) {
    std::map<std::string, std::string> opts = {{"a", "1"}, {"b", "2"}, {"c", "3"}};
    ReporterSpec spec1 = makeSpec("console", {}, {}, opts);
    ReporterSpec spec2 = makeSpec("console", {}, {}, opts);
    EXPECT_TRUE(spec1 == spec2);
}

// Test with special characters in name
TEST_F(ReporterSpecTest_690, SpecialCharactersInName_690) {
    ReporterSpec spec = makeSpec("my-reporter_v2.0");
    EXPECT_EQ(spec.name(), "my-reporter_v2.0");
}

// Test with special characters in output file
TEST_F(ReporterSpecTest_690, SpecialCharactersInOutputFile_690) {
    ReporterSpec spec = makeSpec("console", std::string("/path/to/file with spaces.txt"));
    ASSERT_TRUE(spec.outputFile().has_value());
    EXPECT_EQ(*spec.outputFile(), "/path/to/file with spaces.txt");
}
