#include <gtest/gtest.h>
#include <string>
#include <map>
#include "catch2/internal/catch_reporter_spec_parser.hpp"

using namespace Catch;

class ReporterSpecTest_422 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test construction with all parameters and name accessor
TEST_F(ReporterSpecTest_422, ConstructorAndNameAccessor_422) {
    ReporterSpec spec("console", Optional<std::string>(), Optional<ColourMode>(), {});
    EXPECT_EQ(spec.name(), "console");
}

// Test name with non-trivial string
TEST_F(ReporterSpecTest_422, NameWithComplexString_422) {
    ReporterSpec spec("my-custom-reporter", Optional<std::string>(), Optional<ColourMode>(), {});
    EXPECT_EQ(spec.name(), "my-custom-reporter");
}

// Test empty name
TEST_F(ReporterSpecTest_422, EmptyName_422) {
    ReporterSpec spec("", Optional<std::string>(), Optional<ColourMode>(), {});
    EXPECT_EQ(spec.name(), "");
}

// Test outputFile when not set
TEST_F(ReporterSpecTest_422, OutputFileNotSet_422) {
    ReporterSpec spec("console", Optional<std::string>(), Optional<ColourMode>(), {});
    EXPECT_FALSE(spec.outputFile().has_value());
}

// Test outputFile when set
TEST_F(ReporterSpecTest_422, OutputFileSet_422) {
    ReporterSpec spec("console", Optional<std::string>("output.txt"), Optional<ColourMode>(), {});
    ASSERT_TRUE(spec.outputFile().has_value());
    EXPECT_EQ(*spec.outputFile(), "output.txt");
}

// Test colourMode when not set
TEST_F(ReporterSpecTest_422, ColourModeNotSet_422) {
    ReporterSpec spec("console", Optional<std::string>(), Optional<ColourMode>(), {});
    EXPECT_FALSE(spec.colourMode().has_value());
}

// Test colourMode when set
TEST_F(ReporterSpecTest_422, ColourModeSet_422) {
    ReporterSpec spec("console", Optional<std::string>(), Optional<ColourMode>(ColourMode::ANSI), {});
    ASSERT_TRUE(spec.colourMode().has_value());
    EXPECT_EQ(*spec.colourMode(), ColourMode::ANSI);
}

// Test customOptions when empty
TEST_F(ReporterSpecTest_422, CustomOptionsEmpty_422) {
    ReporterSpec spec("console", Optional<std::string>(), Optional<ColourMode>(), {});
    EXPECT_TRUE(spec.customOptions().empty());
}

// Test customOptions with values
TEST_F(ReporterSpecTest_422, CustomOptionsWithValues_422) {
    std::map<std::string, std::string> options;
    options["key1"] = "value1";
    options["key2"] = "value2";
    ReporterSpec spec("console", Optional<std::string>(), Optional<ColourMode>(), options);
    
    const auto& resultOptions = spec.customOptions();
    EXPECT_EQ(resultOptions.size(), 2u);
    EXPECT_EQ(resultOptions.at("key1"), "value1");
    EXPECT_EQ(resultOptions.at("key2"), "value2");
}

// Test customOptions with single entry
TEST_F(ReporterSpecTest_422, CustomOptionsSingleEntry_422) {
    std::map<std::string, std::string> options;
    options["verbose"] = "true";
    ReporterSpec spec("xml", Optional<std::string>(), Optional<ColourMode>(), options);
    
    const auto& resultOptions = spec.customOptions();
    EXPECT_EQ(resultOptions.size(), 1u);
    EXPECT_EQ(resultOptions.at("verbose"), "true");
}

// Test equality operator - equal specs
TEST_F(ReporterSpecTest_422, EqualityOperatorEqual_422) {
    std::map<std::string, std::string> options;
    options["key"] = "value";
    
    ReporterSpec spec1("console", Optional<std::string>("out.txt"), Optional<ColourMode>(ColourMode::ANSI), options);
    ReporterSpec spec2("console", Optional<std::string>("out.txt"), Optional<ColourMode>(ColourMode::ANSI), options);
    
    EXPECT_TRUE(spec1 == spec2);
}

// Test equality operator - different names
TEST_F(ReporterSpecTest_422, EqualityOperatorDifferentName_422) {
    ReporterSpec spec1("console", Optional<std::string>(), Optional<ColourMode>(), {});
    ReporterSpec spec2("xml", Optional<std::string>(), Optional<ColourMode>(), {});
    
    EXPECT_FALSE(spec1 == spec2);
}

// Test equality operator - different output files
TEST_F(ReporterSpecTest_422, EqualityOperatorDifferentOutputFile_422) {
    ReporterSpec spec1("console", Optional<std::string>("a.txt"), Optional<ColourMode>(), {});
    ReporterSpec spec2("console", Optional<std::string>("b.txt"), Optional<ColourMode>(), {});
    
    EXPECT_FALSE(spec1 == spec2);
}

// Test equality operator - one with output file, one without
TEST_F(ReporterSpecTest_422, EqualityOperatorOneWithOutputFile_422) {
    ReporterSpec spec1("console", Optional<std::string>("a.txt"), Optional<ColourMode>(), {});
    ReporterSpec spec2("console", Optional<std::string>(), Optional<ColourMode>(), {});
    
    EXPECT_FALSE(spec1 == spec2);
}

// Test equality operator - different colour modes
TEST_F(ReporterSpecTest_422, EqualityOperatorDifferentColourMode_422) {
    ReporterSpec spec1("console", Optional<std::string>(), Optional<ColourMode>(ColourMode::ANSI), {});
    ReporterSpec spec2("console", Optional<std::string>(), Optional<ColourMode>(ColourMode::None), {});
    
    EXPECT_FALSE(spec1 == spec2);
}

// Test equality operator - different custom options
TEST_F(ReporterSpecTest_422, EqualityOperatorDifferentCustomOptions_422) {
    std::map<std::string, std::string> options1{{"key", "value1"}};
    std::map<std::string, std::string> options2{{"key", "value2"}};
    
    ReporterSpec spec1("console", Optional<std::string>(), Optional<ColourMode>(), options1);
    ReporterSpec spec2("console", Optional<std::string>(), Optional<ColourMode>(), options2);
    
    EXPECT_FALSE(spec1 == spec2);
}

// Test full construction with all fields populated
TEST_F(ReporterSpecTest_422, FullConstruction_422) {
    std::map<std::string, std::string> options{{"opt1", "val1"}, {"opt2", "val2"}};
    ReporterSpec spec("junit", Optional<std::string>("report.xml"), Optional<ColourMode>(ColourMode::ANSI), options);
    
    EXPECT_EQ(spec.name(), "junit");
    ASSERT_TRUE(spec.outputFile().has_value());
    EXPECT_EQ(*spec.outputFile(), "report.xml");
    ASSERT_TRUE(spec.colourMode().has_value());
    EXPECT_EQ(*spec.colourMode(), ColourMode::ANSI);
    EXPECT_EQ(spec.customOptions().size(), 2u);
}

// Test that accessors return const references (stability of returned references)
TEST_F(ReporterSpecTest_422, AccessorReturnConstReference_422) {
    std::map<std::string, std::string> options{{"a", "b"}};
    ReporterSpec spec("test", Optional<std::string>("file.txt"), Optional<ColourMode>(), options);
    
    const std::string& nameRef = spec.name();
    const auto& outputRef = spec.outputFile();
    const auto& colourRef = spec.colourMode();
    const auto& optionsRef = spec.customOptions();
    
    // Call again and verify same values
    EXPECT_EQ(nameRef, spec.name());
    EXPECT_EQ(&nameRef, &spec.name());
    EXPECT_EQ(&outputRef, &spec.outputFile());
    EXPECT_EQ(&colourRef, &spec.colourMode());
    EXPECT_EQ(&optionsRef, &spec.customOptions());
}

// Test custom options with empty key and value
TEST_F(ReporterSpecTest_422, CustomOptionsEmptyKeyAndValue_422) {
    std::map<std::string, std::string> options{{"", ""}};
    ReporterSpec spec("reporter", Optional<std::string>(), Optional<ColourMode>(), options);
    
    const auto& resultOptions = spec.customOptions();
    EXPECT_EQ(resultOptions.size(), 1u);
    EXPECT_EQ(resultOptions.at(""), "");
}

// Test equality of two default-like specs
TEST_F(ReporterSpecTest_422, EqualityDefaultLikeSpecs_422) {
    ReporterSpec spec1("", Optional<std::string>(), Optional<ColourMode>(), {});
    ReporterSpec spec2("", Optional<std::string>(), Optional<ColourMode>(), {});
    
    EXPECT_TRUE(spec1 == spec2);
}
