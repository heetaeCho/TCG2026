#include "catch2/internal/catch_reporter_spec_parser.hpp"
#include "catch2/internal/catch_stringref.hpp"
#include "catch2/internal/catch_optional.hpp"
#include <gtest/gtest.h>
#include <string>

using namespace Catch;

class ParseReporterSpecTest_691 : public ::testing::Test {
protected:
};

// Normal operation: simple reporter name with no options
TEST_F(ParseReporterSpecTest_691, SimpleReporterName_691) {
    auto result = parseReporterSpec("console");
    ASSERT_TRUE(result.some());
    EXPECT_EQ(result->name(), "console");
    EXPECT_TRUE(!result->outputFile());
    EXPECT_TRUE(!result->colourMode());
    EXPECT_TRUE(result->customOptions().empty());
}

// Normal operation: reporter with output file
TEST_F(ParseReporterSpecTest_691, ReporterWithOutputFile_691) {
    auto result = parseReporterSpec("console::out=output.txt");
    ASSERT_TRUE(result.some());
    EXPECT_EQ(result->name(), "console");
    ASSERT_TRUE(result->outputFile().some());
    EXPECT_EQ(*result->outputFile(), "output.txt");
}

// Normal operation: reporter with colour-mode
TEST_F(ParseReporterSpecTest_691, ReporterWithColourModeAnsi_691) {
    auto result = parseReporterSpec("console::colour-mode=ansi");
    ASSERT_TRUE(result.some());
    EXPECT_EQ(result->name(), "console");
    ASSERT_TRUE(result->colourMode().some());
}

// Normal operation: reporter with colour-mode=none
TEST_F(ParseReporterSpecTest_691, ReporterWithColourModeNone_691) {
    auto result = parseReporterSpec("console::colour-mode=none");
    ASSERT_TRUE(result.some());
    EXPECT_EQ(result->name(), "console");
    ASSERT_TRUE(result->colourMode().some());
}

// Normal operation: reporter with colour-mode=default
TEST_F(ParseReporterSpecTest_691, ReporterWithColourModeDefault_691) {
    auto result = parseReporterSpec("console::colour-mode=default");
    ASSERT_TRUE(result.some());
    ASSERT_TRUE(result->colourMode().some());
}

// Normal operation: reporter with custom key-value pairs (X-prefixed keys)
TEST_F(ParseReporterSpecTest_691, ReporterWithCustomKVPair_691) {
    auto result = parseReporterSpec("console::Xcustom=value");
    ASSERT_TRUE(result.some());
    EXPECT_EQ(result->name(), "console");
    auto const& kvPairs = result->customOptions();
    ASSERT_EQ(kvPairs.size(), 1u);
    auto it = kvPairs.find("Xcustom");
    ASSERT_NE(it, kvPairs.end());
    EXPECT_EQ(it->second, "value");
}

// Normal operation: reporter with multiple options
TEST_F(ParseReporterSpecTest_691, ReporterWithMultipleOptions_691) {
    auto result = parseReporterSpec("console::out=file.txt::colour-mode=ansi::Xfoo=bar");
    ASSERT_TRUE(result.some());
    EXPECT_EQ(result->name(), "console");
    ASSERT_TRUE(result->outputFile().some());
    EXPECT_EQ(*result->outputFile(), "file.txt");
    ASSERT_TRUE(result->colourMode().some());
    auto const& kvPairs = result->customOptions();
    ASSERT_EQ(kvPairs.size(), 1u);
    auto it = kvPairs.find("Xfoo");
    ASSERT_NE(it, kvPairs.end());
    EXPECT_EQ(it->second, "bar");
}

// Error case: unknown key (not out, not colour-mode, not X-prefixed)
TEST_F(ParseReporterSpecTest_691, UnknownKeyReturnsEmpty_691) {
    auto result = parseReporterSpec("console::unknown=value");
    EXPECT_TRUE(result.none());
}

// Error case: empty key in key-value pair
TEST_F(ParseReporterSpecTest_691, EmptyKeyReturnsEmpty_691) {
    auto result = parseReporterSpec("console::=value");
    EXPECT_TRUE(result.none());
}

// Error case: empty value in key-value pair
TEST_F(ParseReporterSpecTest_691, EmptyValueReturnsEmpty_691) {
    auto result = parseReporterSpec("console::out=");
    EXPECT_TRUE(result.none());
}

// Error case: duplicate output file
TEST_F(ParseReporterSpecTest_691, DuplicateOutputFileReturnsEmpty_691) {
    auto result = parseReporterSpec("console::out=file1.txt::out=file2.txt");
    EXPECT_TRUE(result.none());
}

// Error case: duplicate colour-mode
TEST_F(ParseReporterSpecTest_691, DuplicateColourModeReturnsEmpty_691) {
    auto result = parseReporterSpec("console::colour-mode=ansi::colour-mode=none");
    EXPECT_TRUE(result.none());
}

// Error case: invalid colour-mode value
TEST_F(ParseReporterSpecTest_691, InvalidColourModeReturnsEmpty_691) {
    auto result = parseReporterSpec("console::colour-mode=invalid_value");
    EXPECT_TRUE(result.none());
}

// Error case: X key with only 'X' (no actual key name after X)
TEST_F(ParseReporterSpecTest_691, XKeyWithOnlyXReturnsEmpty_691) {
    auto result = parseReporterSpec("console::X=value");
    EXPECT_TRUE(result.none());
}

// Error case: duplicate custom X-prefixed key
TEST_F(ParseReporterSpecTest_691, DuplicateCustomKeyReturnsEmpty_691) {
    auto result = parseReporterSpec("console::Xfoo=bar::Xfoo=baz");
    EXPECT_TRUE(result.none());
}

// Boundary: reporter name only with trailing separator
TEST_F(ParseReporterSpecTest_691, ReporterNameWithTrailingSeparator_691) {
    // "console::" would split into ["console", ""] => empty key/value => should return empty
    auto result = parseReporterSpec("console::");
    EXPECT_TRUE(result.none());
}

// Normal: multiple custom X-prefixed keys with different names
TEST_F(ParseReporterSpecTest_691, MultipleDistinctCustomKeys_691) {
    auto result = parseReporterSpec("console::Xfoo=bar::Xbaz=qux");
    ASSERT_TRUE(result.some());
    auto const& kvPairs = result->customOptions();
    ASSERT_EQ(kvPairs.size(), 2u);
    EXPECT_EQ(kvPairs.at("Xfoo"), "bar");
    EXPECT_EQ(kvPairs.at("Xbaz"), "qux");
}

// Normal: different reporter name
TEST_F(ParseReporterSpecTest_691, XmlReporterName_691) {
    auto result = parseReporterSpec("xml");
    ASSERT_TRUE(result.some());
    EXPECT_EQ(result->name(), "xml");
}

// Boundary: key-value pair with no equals sign (missing value)
TEST_F(ParseReporterSpecTest_691, NoEqualsSignReturnsEmpty_691) {
    auto result = parseReporterSpec("console::outfile");
    EXPECT_TRUE(result.none());
}

// Normal: output file with path-like value
TEST_F(ParseReporterSpecTest_691, OutputFileWithPath_691) {
    auto result = parseReporterSpec("console::out=/tmp/report.xml");
    ASSERT_TRUE(result.some());
    ASSERT_TRUE(result->outputFile().some());
    EXPECT_EQ(*result->outputFile(), "/tmp/report.xml");
}

// Boundary: reporter spec that is just a single reporter name with no separators
TEST_F(ParseReporterSpecTest_691, JustReporterNameNoSeparators_691) {
    auto result = parseReporterSpec("junit");
    ASSERT_TRUE(result.some());
    EXPECT_EQ(result->name(), "junit");
    EXPECT_TRUE(!result->outputFile());
    EXPECT_TRUE(!result->colourMode());
    EXPECT_TRUE(result->customOptions().empty());
}

// Normal: custom key with longer X-prefixed name
TEST_F(ParseReporterSpecTest_691, CustomKeyLongerName_691) {
    auto result = parseReporterSpec("console::XmyCustomOption=myValue");
    ASSERT_TRUE(result.some());
    auto const& kvPairs = result->customOptions();
    ASSERT_EQ(kvPairs.size(), 1u);
    auto it = kvPairs.find("XmyCustomOption");
    ASSERT_NE(it, kvPairs.end());
    EXPECT_EQ(it->second, "myValue");
}
