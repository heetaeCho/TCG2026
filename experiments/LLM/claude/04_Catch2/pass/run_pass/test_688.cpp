#include "catch2/internal/catch_reporter_spec_parser.cpp"
#include "catch2/internal/catch_stringref.hpp"
#include <gtest/gtest.h>
#include <vector>
#include <string>

using Catch::Detail::splitReporterSpec;
using Catch::StringRef;

TEST(SplitReporterSpecTest_688, SinglePartNoSeparator_688) {
    auto result = splitReporterSpec(StringRef("console"));
    ASSERT_EQ(result.size(), 1u);
    EXPECT_EQ(result[0], "console");
}

TEST(SplitReporterSpecTest_688, TwoPartsSingleSeparator_688) {
    auto result = splitReporterSpec(StringRef("console::output.txt"));
    ASSERT_EQ(result.size(), 2u);
    EXPECT_EQ(result[0], "console");
    EXPECT_EQ(result[1], "output.txt");
}

TEST(SplitReporterSpecTest_688, ThreePartsMultipleSeparators_688) {
    auto result = splitReporterSpec(StringRef("console::output.txt::key=value"));
    ASSERT_EQ(result.size(), 3u);
    EXPECT_EQ(result[0], "console");
    EXPECT_EQ(result[1], "output.txt");
    EXPECT_EQ(result[2], "key=value");
}

TEST(SplitReporterSpecTest_688, EmptyString_688) {
    auto result = splitReporterSpec(StringRef(""));
    EXPECT_EQ(result.size(), 0u);
}

TEST(SplitReporterSpecTest_688, TrailingSeparatorProducesEmptyPart_688) {
    auto result = splitReporterSpec(StringRef("console::"));
    ASSERT_EQ(result.size(), 2u);
    EXPECT_EQ(result[0], "console");
    EXPECT_EQ(result[1], "");
}

TEST(SplitReporterSpecTest_688, LeadingSeparatorProducesEmptyFirstPart_688) {
    auto result = splitReporterSpec(StringRef("::console"));
    ASSERT_EQ(result.size(), 2u);
    EXPECT_EQ(result[0], "");
    EXPECT_EQ(result[1], "console");
}

TEST(SplitReporterSpecTest_688, OnlySeparator_688) {
    auto result = splitReporterSpec(StringRef("::"));
    ASSERT_EQ(result.size(), 2u);
    EXPECT_EQ(result[0], "");
    EXPECT_EQ(result[1], "");
}

TEST(SplitReporterSpecTest_688, MultipleSeparatorsConsecutive_688) {
    auto result = splitReporterSpec(StringRef("::::"));
    ASSERT_EQ(result.size(), 3u);
    EXPECT_EQ(result[0], "");
    EXPECT_EQ(result[1], "");
    EXPECT_EQ(result[2], "");
}

TEST(SplitReporterSpecTest_688, SingleColon_688) {
    auto result = splitReporterSpec(StringRef("console:output"));
    ASSERT_EQ(result.size(), 1u);
    EXPECT_EQ(result[0], "console:output");
}

TEST(SplitReporterSpecTest_688, SingleCharacter_688) {
    auto result = splitReporterSpec(StringRef("x"));
    ASSERT_EQ(result.size(), 1u);
    EXPECT_EQ(result[0], "x");
}

TEST(SplitReporterSpecTest_688, SingleColonOnly_688) {
    auto result = splitReporterSpec(StringRef(":"));
    ASSERT_EQ(result.size(), 1u);
    EXPECT_EQ(result[0], ":");
}

TEST(SplitReporterSpecTest_688, ColonAtEndNotSeparator_688) {
    auto result = splitReporterSpec(StringRef("console:"));
    ASSERT_EQ(result.size(), 1u);
    EXPECT_EQ(result[0], "console:");
}

TEST(SplitReporterSpecTest_688, ColonAtStartNotSeparator_688) {
    auto result = splitReporterSpec(StringRef(":console"));
    ASSERT_EQ(result.size(), 1u);
    EXPECT_EQ(result[0], ":console");
}

TEST(SplitReporterSpecTest_688, MixedColonsAndSeparators_688) {
    auto result = splitReporterSpec(StringRef("a:b::c:d"));
    ASSERT_EQ(result.size(), 2u);
    EXPECT_EQ(result[0], "a:b");
    EXPECT_EQ(result[1], "c:d");
}

TEST(SplitReporterSpecTest_688, ThreeColons_688) {
    auto result = splitReporterSpec(StringRef("a:::b"));
    ASSERT_EQ(result.size(), 2u);
    EXPECT_EQ(result[0], "a");
    EXPECT_EQ(result[1], ":b");
}

TEST(SplitReporterSpecTest_688, FourPartsThreeSeparators_688) {
    auto result = splitReporterSpec(StringRef("a::b::c::d"));
    ASSERT_EQ(result.size(), 4u);
    EXPECT_EQ(result[0], "a");
    EXPECT_EQ(result[1], "b");
    EXPECT_EQ(result[2], "c");
    EXPECT_EQ(result[3], "d");
}

TEST(SplitReporterSpecTest_688, LongReporterName_688) {
    std::string longName(1000, 'a');
    auto result = splitReporterSpec(StringRef(longName));
    ASSERT_EQ(result.size(), 1u);
    EXPECT_EQ(result[0], longName);
}

TEST(SplitReporterSpecTest_688, LongReporterNameWithSeparator_688) {
    std::string longName(500, 'a');
    std::string input = longName + "::" + longName;
    auto result = splitReporterSpec(StringRef(input));
    ASSERT_EQ(result.size(), 2u);
    EXPECT_EQ(result[0], longName);
    EXPECT_EQ(result[1], longName);
}

TEST(SplitReporterSpecTest_688, SeparatorAtVeryEnd_688) {
    auto result = splitReporterSpec(StringRef("abc::def::"));
    ASSERT_EQ(result.size(), 3u);
    EXPECT_EQ(result[0], "abc");
    EXPECT_EQ(result[1], "def");
    EXPECT_EQ(result[2], "");
}

TEST(SplitReporterSpecTest_688, AllEmptyParts_688) {
    auto result = splitReporterSpec(StringRef("::::::"));
    ASSERT_EQ(result.size(), 4u);
    for (const auto& part : result) {
        EXPECT_EQ(part, "");
    }
}

TEST(SplitReporterSpecTest_688, SpecialCharactersInParts_688) {
    auto result = splitReporterSpec(StringRef("report@1::file/path.txt::key=val&x"));
    ASSERT_EQ(result.size(), 3u);
    EXPECT_EQ(result[0], "report@1");
    EXPECT_EQ(result[1], "file/path.txt");
    EXPECT_EQ(result[2], "key=val&x");
}

TEST(SplitReporterSpecTest_688, SpacesInParts_688) {
    auto result = splitReporterSpec(StringRef("hello world::foo bar"));
    ASSERT_EQ(result.size(), 2u);
    EXPECT_EQ(result[0], "hello world");
    EXPECT_EQ(result[1], "foo bar");
}

TEST(SplitReporterSpecTest_688, StringRefFromStdString_688) {
    std::string input = "xml::output.xml";
    auto result = splitReporterSpec(StringRef(input));
    ASSERT_EQ(result.size(), 2u);
    EXPECT_EQ(result[0], "xml");
    EXPECT_EQ(result[1], "output.xml");
}
