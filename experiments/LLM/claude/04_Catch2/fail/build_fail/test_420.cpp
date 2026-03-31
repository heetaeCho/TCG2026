#include "catch2/internal/catch_reporter_spec_parser.hpp"
#include <gtest/gtest.h>
#include <string>
#include <map>

using namespace Catch;

class ReporterSpecTest_420 : public ::testing::Test {
protected:
};

TEST_F(ReporterSpecTest_420, ConstructWithAllParameters_420) {
    std::string name = "console";
    Optional<std::string> outputFile = std::string("output.txt");
    Optional<ColourMode> colourMode = ColourMode::ANSI;
    std::map<std::string, std::string> customOptions = {{"key1", "value1"}};

    ReporterSpec spec(name, outputFile, colourMode, customOptions);

    EXPECT_EQ(spec.name(), "console");
    EXPECT_TRUE(spec.outputFile().has_value());
    EXPECT_EQ(*spec.outputFile(), "output.txt");
    EXPECT_TRUE(spec.colourMode().has_value());
    EXPECT_EQ(*spec.colourMode(), ColourMode::ANSI);
    EXPECT_EQ(spec.customOptions().size(), 1u);
    EXPECT_EQ(spec.customOptions().at("key1"), "value1");
}

TEST_F(ReporterSpecTest_420, ConstructWithEmptyOptionals_420) {
    std::string name = "xml";
    Optional<std::string> outputFile;
    Optional<ColourMode> colourMode;
    std::map<std::string, std::string> customOptions;

    ReporterSpec spec(name, outputFile, colourMode, customOptions);

    EXPECT_EQ(spec.name(), "xml");
    EXPECT_FALSE(spec.outputFile().has_value());
    EXPECT_FALSE(spec.colourMode().has_value());
    EXPECT_TRUE(spec.customOptions().empty());
}

TEST_F(ReporterSpecTest_420, NameReturnsCorrectValue_420) {
    ReporterSpec spec("junit", {}, {}, {});
    EXPECT_EQ(spec.name(), "junit");
}

TEST_F(ReporterSpecTest_420, OutputFileReturnsCorrectValue_420) {
    ReporterSpec spec("console", std::string("result.xml"), {}, {});
    ASSERT_TRUE(spec.outputFile().has_value());
    EXPECT_EQ(*spec.outputFile(), "result.xml");
}

TEST_F(ReporterSpecTest_420, OutputFileReturnsEmptyOptionalWhenNotSet_420) {
    ReporterSpec spec("console", {}, {}, {});
    EXPECT_FALSE(spec.outputFile().has_value());
}

TEST_F(ReporterSpecTest_420, ColourModeReturnsCorrectValue_420) {
    ReporterSpec spec("console", {}, ColourMode::ANSI, {});
    ASSERT_TRUE(spec.colourMode().has_value());
    EXPECT_EQ(*spec.colourMode(), ColourMode::ANSI);
}

TEST_F(ReporterSpecTest_420, ColourModeReturnsEmptyOptionalWhenNotSet_420) {
    ReporterSpec spec("console", {}, {}, {});
    EXPECT_FALSE(spec.colourMode().has_value());
}

TEST_F(ReporterSpecTest_420, CustomOptionsReturnsCorrectMap_420) {
    std::map<std::string, std::string> opts = {{"opt1", "val1"}, {"opt2", "val2"}};
    ReporterSpec spec("console", {}, {}, opts);

    auto const& returned = spec.customOptions();
    EXPECT_EQ(returned.size(), 2u);
    EXPECT_EQ(returned.at("opt1"), "val1");
    EXPECT_EQ(returned.at("opt2"), "val2");
}

TEST_F(ReporterSpecTest_420, CustomOptionsEmptyWhenNoneProvided_420) {
    ReporterSpec spec("console", {}, {}, {});
    EXPECT_TRUE(spec.customOptions().empty());
}

TEST_F(ReporterSpecTest_420, EqualityOperatorSameSpecs_420) {
    std::map<std::string, std::string> opts = {{"key", "value"}};
    ReporterSpec spec1("console", std::string("out.txt"), ColourMode::ANSI, opts);
    ReporterSpec spec2("console", std::string("out.txt"), ColourMode::ANSI, opts);

    EXPECT_TRUE(spec1 == spec2);
}

TEST_F(ReporterSpecTest_420, EqualityOperatorDifferentNames_420) {
    ReporterSpec spec1("console", {}, {}, {});
    ReporterSpec spec2("xml", {}, {}, {});

    EXPECT_FALSE(spec1 == spec2);
}

TEST_F(ReporterSpecTest_420, EqualityOperatorDifferentOutputFiles_420) {
    ReporterSpec spec1("console", std::string("file1.txt"), {}, {});
    ReporterSpec spec2("console", std::string("file2.txt"), {}, {});

    EXPECT_FALSE(spec1 == spec2);
}

TEST_F(ReporterSpecTest_420, EqualityOperatorOneWithOutputFileOneWithout_420) {
    ReporterSpec spec1("console", std::string("file1.txt"), {}, {});
    ReporterSpec spec2("console", {}, {}, {});

    EXPECT_FALSE(spec1 == spec2);
}

TEST_F(ReporterSpecTest_420, EqualityOperatorDifferentColourModes_420) {
    ReporterSpec spec1("console", {}, ColourMode::ANSI, {});
    ReporterSpec spec2("console", {}, ColourMode::None, {});

    EXPECT_FALSE(spec1 == spec2);
}

TEST_F(ReporterSpecTest_420, EqualityOperatorDifferentCustomOptions_420) {
    ReporterSpec spec1("console", {}, {}, {{"k1", "v1"}});
    ReporterSpec spec2("console", {}, {}, {{"k2", "v2"}});

    EXPECT_FALSE(spec1 == spec2);
}

TEST_F(ReporterSpecTest_420, EqualityOperatorBothEmpty_420) {
    ReporterSpec spec1("", {}, {}, {});
    ReporterSpec spec2("", {}, {}, {});

    EXPECT_TRUE(spec1 == spec2);
}

TEST_F(ReporterSpecTest_420, NameWithEmptyString_420) {
    ReporterSpec spec("", {}, {}, {});
    EXPECT_EQ(spec.name(), "");
}

TEST_F(ReporterSpecTest_420, OutputFileWithEmptyString_420) {
    ReporterSpec spec("console", std::string(""), {}, {});
    ASSERT_TRUE(spec.outputFile().has_value());
    EXPECT_EQ(*spec.outputFile(), "");
}

TEST_F(ReporterSpecTest_420, MultipleCustomOptions_420) {
    std::map<std::string, std::string> opts;
    for (int i = 0; i < 100; ++i) {
        opts["key" + std::to_string(i)] = "value" + std::to_string(i);
    }
    ReporterSpec spec("console", {}, {}, opts);
    EXPECT_EQ(spec.customOptions().size(), 100u);
}

TEST_F(ReporterSpecTest_420, ConstRefReturnTypes_420) {
    ReporterSpec spec("console", std::string("out.txt"), ColourMode::ANSI, {{"k", "v"}});

    // Verify that returned references are stable
    auto const& nameRef = spec.name();
    auto const& outputRef = spec.outputFile();
    auto const& colourRef = spec.colourMode();
    auto const& optsRef = spec.customOptions();

    EXPECT_EQ(&nameRef, &spec.name());
    EXPECT_EQ(&outputRef, &spec.outputFile());
    EXPECT_EQ(&colourRef, &spec.colourMode());
    EXPECT_EQ(&optsRef, &spec.customOptions());
}

TEST_F(ReporterSpecTest_420, ColourModeNone_420) {
    ReporterSpec spec("console", {}, ColourMode::None, {});
    ASSERT_TRUE(spec.colourMode().has_value());
    EXPECT_EQ(*spec.colourMode(), ColourMode::None);
}
