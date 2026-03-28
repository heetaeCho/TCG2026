#include "catch2/internal/catch_reporter_spec_parser.hpp"
#include <gtest/gtest.h>
#include <string>
#include <map>

using namespace Catch;

class ReporterSpecTest_421 : public ::testing::Test {
protected:
};

TEST_F(ReporterSpecTest_421, ConstructorSetsName_421) {
    ReporterSpec spec("console", {}, {}, {});
    EXPECT_EQ(spec.name(), "console");
}

TEST_F(ReporterSpecTest_421, ConstructorSetsEmptyName_421) {
    ReporterSpec spec("", {}, {}, {});
    EXPECT_EQ(spec.name(), "");
}

TEST_F(ReporterSpecTest_421, ConstructorSetsOutputFile_421) {
    Optional<std::string> outputFile("output.txt");
    ReporterSpec spec("console", outputFile, {}, {});
    ASSERT_TRUE(spec.outputFile().has_value());
    EXPECT_EQ(*spec.outputFile(), "output.txt");
}

TEST_F(ReporterSpecTest_421, ConstructorSetsNoOutputFile_421) {
    ReporterSpec spec("console", {}, {}, {});
    EXPECT_FALSE(spec.outputFile().has_value());
}

TEST_F(ReporterSpecTest_421, ConstructorSetsColourMode_421) {
    Optional<ColourMode> colour(ColourMode::ANSI);
    ReporterSpec spec("console", {}, colour, {});
    ASSERT_TRUE(spec.colourMode().has_value());
    EXPECT_EQ(*spec.colourMode(), ColourMode::ANSI);
}

TEST_F(ReporterSpecTest_421, ConstructorSetsNoColourMode_421) {
    ReporterSpec spec("console", {}, {}, {});
    EXPECT_FALSE(spec.colourMode().has_value());
}

TEST_F(ReporterSpecTest_421, ConstructorSetsCustomOptions_421) {
    std::map<std::string, std::string> options;
    options["key1"] = "value1";
    options["key2"] = "value2";
    ReporterSpec spec("console", {}, {}, options);
    EXPECT_EQ(spec.customOptions().size(), 2u);
    EXPECT_EQ(spec.customOptions().at("key1"), "value1");
    EXPECT_EQ(spec.customOptions().at("key2"), "value2");
}

TEST_F(ReporterSpecTest_421, ConstructorSetsEmptyCustomOptions_421) {
    ReporterSpec spec("console", {}, {}, {});
    EXPECT_TRUE(spec.customOptions().empty());
}

TEST_F(ReporterSpecTest_421, ColourModeNone_421) {
    Optional<ColourMode> colour(ColourMode::None);
    ReporterSpec spec("xml", {}, colour, {});
    ASSERT_TRUE(spec.colourMode().has_value());
    EXPECT_EQ(*spec.colourMode(), ColourMode::None);
}

TEST_F(ReporterSpecTest_421, ColourModePlatformDefault_421) {
    Optional<ColourMode> colour(ColourMode::PlatformDefault);
    ReporterSpec spec("xml", {}, colour, {});
    ASSERT_TRUE(spec.colourMode().has_value());
    EXPECT_EQ(*spec.colourMode(), ColourMode::PlatformDefault);
}

TEST_F(ReporterSpecTest_421, EqualityOperatorSameSpecs_421) {
    std::map<std::string, std::string> opts = {{"k", "v"}};
    ReporterSpec spec1("console", Optional<std::string>("file.txt"), Optional<ColourMode>(ColourMode::ANSI), opts);
    ReporterSpec spec2("console", Optional<std::string>("file.txt"), Optional<ColourMode>(ColourMode::ANSI), opts);
    EXPECT_TRUE(spec1 == spec2);
}

TEST_F(ReporterSpecTest_421, EqualityOperatorDifferentName_421) {
    ReporterSpec spec1("console", {}, {}, {});
    ReporterSpec spec2("xml", {}, {}, {});
    EXPECT_FALSE(spec1 == spec2);
}

TEST_F(ReporterSpecTest_421, EqualityOperatorDifferentOutputFile_421) {
    ReporterSpec spec1("console", Optional<std::string>("file1.txt"), {}, {});
    ReporterSpec spec2("console", Optional<std::string>("file2.txt"), {}, {});
    EXPECT_FALSE(spec1 == spec2);
}

TEST_F(ReporterSpecTest_421, EqualityOperatorDifferentColourMode_421) {
    ReporterSpec spec1("console", {}, Optional<ColourMode>(ColourMode::ANSI), {});
    ReporterSpec spec2("console", {}, Optional<ColourMode>(ColourMode::None), {});
    EXPECT_FALSE(spec1 == spec2);
}

TEST_F(ReporterSpecTest_421, EqualityOperatorDifferentCustomOptions_421) {
    ReporterSpec spec1("console", {}, {}, {{"k1", "v1"}});
    ReporterSpec spec2("console", {}, {}, {{"k2", "v2"}});
    EXPECT_FALSE(spec1 == spec2);
}

TEST_F(ReporterSpecTest_421, EqualityOperatorOneWithOutputFileOneWithout_421) {
    ReporterSpec spec1("console", Optional<std::string>("file.txt"), {}, {});
    ReporterSpec spec2("console", {}, {}, {});
    EXPECT_FALSE(spec1 == spec2);
}

TEST_F(ReporterSpecTest_421, EqualityOperatorOneWithColourModeOneWithout_421) {
    ReporterSpec spec1("console", {}, Optional<ColourMode>(ColourMode::ANSI), {});
    ReporterSpec spec2("console", {}, {}, {});
    EXPECT_FALSE(spec1 == spec2);
}

TEST_F(ReporterSpecTest_421, EqualityOperatorBothEmpty_421) {
    ReporterSpec spec1("", {}, {}, {});
    ReporterSpec spec2("", {}, {}, {});
    EXPECT_TRUE(spec1 == spec2);
}

TEST_F(ReporterSpecTest_421, FullyPopulatedSpec_421) {
    std::map<std::string, std::string> opts = {{"verbose", "true"}, {"format", "json"}};
    ReporterSpec spec("junit", Optional<std::string>("results.xml"), Optional<ColourMode>(ColourMode::ANSI), opts);

    EXPECT_EQ(spec.name(), "junit");
    ASSERT_TRUE(spec.outputFile().has_value());
    EXPECT_EQ(*spec.outputFile(), "results.xml");
    ASSERT_TRUE(spec.colourMode().has_value());
    EXPECT_EQ(*spec.colourMode(), ColourMode::ANSI);
    EXPECT_EQ(spec.customOptions().size(), 2u);
    EXPECT_EQ(spec.customOptions().at("verbose"), "true");
    EXPECT_EQ(spec.customOptions().at("format"), "json");
}

TEST_F(ReporterSpecTest_421, NameWithSpecialCharacters_421) {
    ReporterSpec spec("my-custom::reporter/v2", {}, {}, {});
    EXPECT_EQ(spec.name(), "my-custom::reporter/v2");
}

TEST_F(ReporterSpecTest_421, OutputFileEmptyString_421) {
    Optional<std::string> outputFile("");
    ReporterSpec spec("console", outputFile, {}, {});
    ASSERT_TRUE(spec.outputFile().has_value());
    EXPECT_EQ(*spec.outputFile(), "");
}

TEST_F(ReporterSpecTest_421, CustomOptionsWithEmptyKeyAndValue_421) {
    std::map<std::string, std::string> opts = {{"", ""}};
    ReporterSpec spec("console", {}, {}, opts);
    EXPECT_EQ(spec.customOptions().size(), 1u);
    EXPECT_EQ(spec.customOptions().at(""), "");
}
