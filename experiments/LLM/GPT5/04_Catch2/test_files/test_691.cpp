// File: parse_reporter_spec_tests_691.cpp
#include <gtest/gtest.h>

#include <catch2/internal/catch_reporter_spec_parser.hpp>   // parseReporterSpec + ReporterSpec
#include <catch2/internal/catch_console_colour.hpp>         // ColourMode (enum)

// We test only observable behavior via ReporterSpec's public API:
//   - name()
//   - outputFile() -> Optional<std::string>
//   - colourMode() -> Optional<ColourMode>
//   - customOptions() -> const std::map<std::string,std::string>&

using Catch::ColourMode;
using Catch::Optional;
using Catch::ReporterSpec;
using Catch::parseReporterSpec;

namespace {

TEST(ParseReporterSpecTest_691, ParsesNameOnly_691) {
    auto spec = parseReporterSpec("console");
    ASSERT_TRUE(spec); // engaged

    EXPECT_EQ(std::string(spec->name()), "console");
    EXPECT_FALSE(spec->outputFile());       // none
    EXPECT_FALSE(spec->colourMode());       // none
    EXPECT_TRUE(spec->customOptions().empty());
}

TEST(ParseReporterSpecTest_691, ParsesOutOnce_691) {
    auto spec = parseReporterSpec("console::out=result.txt");
    ASSERT_TRUE(spec);

    EXPECT_EQ(std::string(spec->name()), "console");
    ASSERT_TRUE(spec->outputFile());
    EXPECT_EQ(*spec->outputFile(), "result.txt");
    EXPECT_FALSE(spec->colourMode());
    EXPECT_TRUE(spec->customOptions().empty());
}

TEST(ParseReporterSpecTest_691, RejectsDuplicateOut_691) {
    auto spec = parseReporterSpec("console::out=a.txt::out=b.txt");
    EXPECT_FALSE(spec); // invalid -> empty Optional
}

TEST(ParseReporterSpecTest_691, ParsesColourModeOnce_691) {
    auto spec = parseReporterSpec("console::colour-mode=ansi");
    ASSERT_TRUE(spec);

    EXPECT_EQ(std::string(spec->name()), "console");
    EXPECT_FALSE(spec->outputFile());
    ASSERT_TRUE(spec->colourMode()); // value recognized
    // We don't assert the concrete enumerator to avoid depending on mapping,
    // but if desired, uncomment the line below:
    // EXPECT_EQ(*spec->colourMode(), ColourMode::ANSI);
    EXPECT_TRUE(spec->customOptions().empty());
}

TEST(ParseReporterSpecTest_691, RejectsInvalidColourMode_691) {
    auto spec = parseReporterSpec("console::colour-mode=rainbow");
    EXPECT_FALSE(spec);
}

TEST(ParseReporterSpecTest_691, RejectsDuplicateColourMode_691) {
    auto spec = parseReporterSpec("console::colour-mode=ansi::colour-mode=default");
    EXPECT_FALSE(spec);
}

TEST(ParseReporterSpecTest_691, AcceptsCustomXOptions_691) {
    auto spec = parseReporterSpec("console::Xfoo=bar::Xbaz=qux");
    ASSERT_TRUE(spec);

    const auto& opts = spec->customOptions();
    ASSERT_EQ(opts.size(), 2u);
    EXPECT_EQ(opts.at("Xfoo"), "bar");
    EXPECT_EQ(opts.at("Xbaz"), "qux");

    EXPECT_EQ(std::string(spec->name()), "console");
    EXPECT_FALSE(spec->outputFile());
    EXPECT_FALSE(spec->colourMode());
}

TEST(ParseReporterSpecTest_691, RejectsXWithoutKey_691) {
    // Key is exactly "X" -> invalid according to interface
    auto spec = parseReporterSpec("console::X=val");
    EXPECT_FALSE(spec);
}

TEST(ParseReporterSpecTest_691, RejectsDuplicateXKeys_691) {
    auto spec = parseReporterSpec("console::Xdup=1::Xdup=2");
    EXPECT_FALSE(spec);
}

TEST(ParseReporterSpecTest_691, RejectsEmptyValue_691) {
    // Any kv with empty value should be rejected
    auto spec1 = parseReporterSpec("console::out=");
    auto spec2 = parseReporterSpec("console::Xk=");
    EXPECT_FALSE(spec1);
    EXPECT_FALSE(spec2);
}

TEST(ParseReporterSpecTest_691, RejectsEmptyKey_691) {
    // Empty key before '=' should be rejected
    auto spec = parseReporterSpec("console::=oops");
    EXPECT_FALSE(spec);
}

TEST(ParseReporterSpecTest_691, RejectsUnknownKey_691) {
    auto spec = parseReporterSpec("console::unknown=value");
    EXPECT_FALSE(spec);
}

TEST(ParseReporterSpecTest_691, AcceptsCombinedValidParts_691) {
    auto spec = parseReporterSpec("junit::out=result-junit.xml::colour-mode=ansi::Xslow=true");
    ASSERT_TRUE(spec);

    EXPECT_EQ(std::string(spec->name()), "junit");
    ASSERT_TRUE(spec->outputFile());
    EXPECT_EQ(*spec->outputFile(), "result-junit.xml");
    ASSERT_TRUE(spec->colourMode());
    const auto& opts = spec->customOptions();
    ASSERT_EQ(opts.size(), 1u);
    EXPECT_EQ(opts.at("Xslow"), "true");
}

} // namespace
