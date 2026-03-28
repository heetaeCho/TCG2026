#include "catch2/internal/catch_reporter_spec_parser.hpp"
#include <gtest/gtest.h>
#include <string>
#include <map>

using namespace Catch;

class ReporterSpecTest_419 : public ::testing::Test {
protected:
};

TEST_F(ReporterSpecTest_419, ConstructorAndNameAccessor_419) {
    ReporterSpec spec("console", {}, {}, {});
    EXPECT_EQ(spec.name(), "console");
}

TEST_F(ReporterSpecTest_419, NameReturnsCorrectValue_419) {
    ReporterSpec spec("xml", {}, {}, {});
    EXPECT_EQ(spec.name(), "xml");
}

TEST_F(ReporterSpecTest_419, EmptyName_419) {
    ReporterSpec spec("", {}, {}, {});
    EXPECT_EQ(spec.name(), "");
}

TEST_F(ReporterSpecTest_419, OutputFileNone_419) {
    ReporterSpec spec("console", {}, {}, {});
    EXPECT_FALSE(spec.outputFile().has_value());
}

TEST_F(ReporterSpecTest_419, OutputFileWithValue_419) {
    ReporterSpec spec("console", Optional<std::string>("output.txt"), {}, {});
    ASSERT_TRUE(spec.outputFile().has_value());
    EXPECT_EQ(*spec.outputFile(), "output.txt");
}

TEST_F(ReporterSpecTest_419, ColourModeNone_419) {
    ReporterSpec spec("console", {}, {}, {});
    EXPECT_FALSE(spec.colourMode().has_value());
}

TEST_F(ReporterSpecTest_419, ColourModeWithValue_419) {
    ReporterSpec spec("console", {}, Optional<ColourMode>(ColourMode::ANSI), {});
    ASSERT_TRUE(spec.colourMode().has_value());
    EXPECT_EQ(*spec.colourMode(), ColourMode::ANSI);
}

TEST_F(ReporterSpecTest_419, ColourModeNone_Value_419) {
    ReporterSpec spec("console", {}, Optional<ColourMode>(ColourMode::None), {});
    ASSERT_TRUE(spec.colourMode().has_value());
    EXPECT_EQ(*spec.colourMode(), ColourMode::None);
}

TEST_F(ReporterSpecTest_419, CustomOptionsEmpty_419) {
    ReporterSpec spec("console", {}, {}, {});
    EXPECT_TRUE(spec.customOptions().empty());
}

TEST_F(ReporterSpecTest_419, CustomOptionsWithEntries_419) {
    std::map<std::string, std::string> options;
    options["key1"] = "value1";
    options["key2"] = "value2";
    ReporterSpec spec("console", {}, {}, options);
    EXPECT_EQ(spec.customOptions().size(), 2u);
    EXPECT_EQ(spec.customOptions().at("key1"), "value1");
    EXPECT_EQ(spec.customOptions().at("key2"), "value2");
}

TEST_F(ReporterSpecTest_419, EqualityOperatorSameSpecs_419) {
    std::map<std::string, std::string> options{{"k", "v"}};
    ReporterSpec spec1("console", Optional<std::string>("out.txt"), Optional<ColourMode>(ColourMode::ANSI), options);
    ReporterSpec spec2("console", Optional<std::string>("out.txt"), Optional<ColourMode>(ColourMode::ANSI), options);
    EXPECT_TRUE(spec1 == spec2);
}

TEST_F(ReporterSpecTest_419, EqualityOperatorDifferentName_419) {
    ReporterSpec spec1("console", {}, {}, {});
    ReporterSpec spec2("xml", {}, {}, {});
    EXPECT_FALSE(spec1 == spec2);
}

TEST_F(ReporterSpecTest_419, EqualityOperatorDifferentOutputFile_419) {
    ReporterSpec spec1("console", Optional<std::string>("a.txt"), {}, {});
    ReporterSpec spec2("console", Optional<std::string>("b.txt"), {}, {});
    EXPECT_FALSE(spec1 == spec2);
}

TEST_F(ReporterSpecTest_419, EqualityOperatorDifferentColourMode_419) {
    ReporterSpec spec1("console", {}, Optional<ColourMode>(ColourMode::ANSI), {});
    ReporterSpec spec2("console", {}, Optional<ColourMode>(ColourMode::None), {});
    EXPECT_FALSE(spec1 == spec2);
}

TEST_F(ReporterSpecTest_419, EqualityOperatorDifferentCustomOptions_419) {
    ReporterSpec spec1("console", {}, {}, {{"k1", "v1"}});
    ReporterSpec spec2("console", {}, {}, {{"k2", "v2"}});
    EXPECT_FALSE(spec1 == spec2);
}

TEST_F(ReporterSpecTest_419, EqualityOperatorBothEmpty_419) {
    ReporterSpec spec1("", {}, {}, {});
    ReporterSpec spec2("", {}, {}, {});
    EXPECT_TRUE(spec1 == spec2);
}

TEST_F(ReporterSpecTest_419, FullConstructionAllFields_419) {
    std::map<std::string, std::string> opts{{"verbose", "true"}, {"format", "json"}};
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

TEST_F(ReporterSpecTest_419, NameReturnsByConstReference_419) {
    ReporterSpec spec("myreporter", {}, {}, {});
    const std::string& nameRef = spec.name();
    EXPECT_EQ(nameRef, "myreporter");
    // Ensure the reference remains valid
    EXPECT_EQ(&nameRef, &spec.name());
}

TEST_F(ReporterSpecTest_419, OutputFileReturnsByConstReference_419) {
    ReporterSpec spec("r", Optional<std::string>("file.txt"), {}, {});
    const auto& ref = spec.outputFile();
    EXPECT_EQ(&ref, &spec.outputFile());
}

TEST_F(ReporterSpecTest_419, ColourModeReturnsByConstReference_419) {
    ReporterSpec spec("r", {}, Optional<ColourMode>(ColourMode::ANSI), {});
    const auto& ref = spec.colourMode();
    EXPECT_EQ(&ref, &spec.colourMode());
}

TEST_F(ReporterSpecTest_419, CustomOptionsReturnsByConstReference_419) {
    ReporterSpec spec("r", {}, {}, {{"a", "b"}});
    const auto& ref = spec.customOptions();
    EXPECT_EQ(&ref, &spec.customOptions());
}

TEST_F(ReporterSpecTest_419, LongNameString_419) {
    std::string longName(10000, 'x');
    ReporterSpec spec(longName, {}, {}, {});
    EXPECT_EQ(spec.name(), longName);
    EXPECT_EQ(spec.name().size(), 10000u);
}

TEST_F(ReporterSpecTest_419, SpecialCharactersInName_419) {
    ReporterSpec spec("reporter::with::colons", {}, {}, {});
    EXPECT_EQ(spec.name(), "reporter::with::colons");
}

TEST_F(ReporterSpecTest_419, EmptyOutputFileName_419) {
    ReporterSpec spec("console", Optional<std::string>(""), {}, {});
    ASSERT_TRUE(spec.outputFile().has_value());
    EXPECT_EQ(*spec.outputFile(), "");
}

TEST_F(ReporterSpecTest_419, EqualityWithOutputFilePresenceVsAbsence_419) {
    ReporterSpec spec1("console", Optional<std::string>("file.txt"), {}, {});
    ReporterSpec spec2("console", {}, {}, {});
    EXPECT_FALSE(spec1 == spec2);
}

TEST_F(ReporterSpecTest_419, EqualityWithColourModePresenceVsAbsence_419) {
    ReporterSpec spec1("console", {}, Optional<ColourMode>(ColourMode::ANSI), {});
    ReporterSpec spec2("console", {}, {}, {});
    EXPECT_FALSE(spec1 == spec2);
}
