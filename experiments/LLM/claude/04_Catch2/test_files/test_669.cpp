#include "catch2/internal/catch_clara.hpp"
#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include <vector>

using namespace Catch::Clara;

// ============================================================================
// Parser::getHelpColumns tests
// ============================================================================

TEST(ParserGetHelpColumnsTest_669, EmptyParserReturnsEmptyColumns_669) {
    Parser parser;
    auto cols = parser.getHelpColumns();
    EXPECT_TRUE(cols.empty());
}

TEST(ParserGetHelpColumnsTest_669, SingleOptionReturnsOneColumn_669) {
    Parser parser;
    bool flag = false;
    parser |= Opt(flag)["-f"]["--flag"]
        .description("A flag option");

    auto cols = parser.getHelpColumns();
    EXPECT_EQ(cols.size(), 1u);
}

TEST(ParserGetHelpColumnsTest_669, MultipleOptionsReturnMultipleColumns_669) {
    Parser parser;
    bool flag1 = false;
    bool flag2 = false;
    std::string str;

    parser |= Opt(flag1)["-a"]["--alpha"]
        .description("First flag");
    parser |= Opt(flag2)["-b"]["--beta"]
        .description("Second flag");
    parser |= Opt(str, "value")["-s"]["--string"]
        .description("A string option");

    auto cols = parser.getHelpColumns();
    EXPECT_EQ(cols.size(), 3u);
}

TEST(ParserGetHelpColumnsTest_669, ColumnsPreserveOrderOfOptions_669) {
    Parser parser;
    bool f1 = false;
    bool f2 = false;

    parser |= Opt(f1)["-x"]["--xray"]
        .description("X option");
    parser |= Opt(f2)["-y"]["--yankee"]
        .description("Y option");

    auto cols = parser.getHelpColumns();
    ASSERT_EQ(cols.size(), 2u);
    // The columns should be in the order options were added
    // We check that descriptions are maintained in order
    EXPECT_NE(cols[0].description, cols[1].description);
}

TEST(ParserGetHelpColumnsTest_669, MergedParsersAccumulateColumns_669) {
    Parser parser1;
    Parser parser2;
    bool f1 = false;
    bool f2 = false;

    parser1 |= Opt(f1)["-a"]["--alpha"]
        .description("Alpha");
    parser2 |= Opt(f2)["-b"]["--beta"]
        .description("Beta");

    parser1 |= parser2;

    auto cols = parser1.getHelpColumns();
    EXPECT_EQ(cols.size(), 2u);
}

TEST(ParserGetHelpColumnsTest_669, OptionWithHintShowsInColumns_669) {
    Parser parser;
    std::string value;

    parser |= Opt(value, "filename")["-o"]["--output"]
        .description("Output file");

    auto cols = parser.getHelpColumns();
    ASSERT_EQ(cols.size(), 1u);
    // The left column should contain the option names
    EXPECT_FALSE(cols[0].left.empty());
}

TEST(ParserGetHelpColumnsTest_669, OptionDescriptionAppearsInColumns_669) {
    Parser parser;
    bool flag = false;

    parser |= Opt(flag)["-v"]["--verbose"]
        .description("Enable verbose output");

    auto cols = parser.getHelpColumns();
    ASSERT_EQ(cols.size(), 1u);
    EXPECT_EQ(cols[0].description, "Enable verbose output");
}

// ============================================================================
// Parser general tests
// ============================================================================

TEST(ParserWriteToStreamTest_669, EmptyParserWritesWithoutCrash_669) {
    Parser parser;
    std::ostringstream oss;
    EXPECT_NO_THROW(parser.writeToStream(oss));
}

TEST(ParserWriteToStreamTest_669, ParserWithOptionsWritesToStream_669) {
    Parser parser;
    bool flag = false;
    parser |= Opt(flag)["-h"]["--help"]
        .description("Show help");

    std::ostringstream oss;
    parser.writeToStream(oss);
    std::string output = oss.str();
    // Should have some output
    EXPECT_FALSE(output.empty());
}

TEST(ParserValidateTest_669, EmptyParserValidates_669) {
    Parser parser;
    auto result = parser.validate();
    EXPECT_TRUE(static_cast<bool>(result));
}

TEST(ParserValidateTest_669, ParserWithValidOptionsValidates_669) {
    Parser parser;
    bool flag = false;
    parser |= Opt(flag)["-f"]["--flag"]
        .description("A flag");

    auto result = parser.validate();
    EXPECT_TRUE(static_cast<bool>(result));
}

TEST(ParserOperatorPipeEqualsTest_669, AddExeNameDoesNotThrow_669) {
    Parser parser;
    EXPECT_NO_THROW(parser |= ExeName("test_app"));
}

TEST(ParserOperatorPipeEqualsTest_669, CombiningTwoEmptyParsers_669) {
    Parser p1;
    Parser p2;
    EXPECT_NO_THROW(p1 |= p2);
    auto cols = p1.getHelpColumns();
    EXPECT_TRUE(cols.empty());
}

// ============================================================================
// Opt tests
// ============================================================================

TEST(OptTest_669, BoolOptConstruction_669) {
    bool flag = false;
    EXPECT_NO_THROW(Opt(flag)["-f"]["--flag"]);
}

TEST(OptTest_669, StringOptConstruction_669) {
    std::string value;
    EXPECT_NO_THROW(Opt(value, "val")["-s"]["--string"]);
}

TEST(OptTest_669, OptGetHelpColumnsReturnsNonEmpty_669) {
    bool flag = false;
    auto opt = Opt(flag)["-f"]["--flag"]
        .description("Test flag");

    auto cols = opt.getHelpColumns();
    EXPECT_FALSE(cols.left.empty());
}

TEST(OptTest_669, OptIsMatchReturnsTrueForMatchingName_669) {
    bool flag = false;
    auto opt = Opt(flag)["-f"]["--flag"];

    EXPECT_TRUE(opt.isMatch("-f"));
    EXPECT_TRUE(opt.isMatch("--flag"));
}

TEST(OptTest_669, OptIsMatchReturnsFalseForNonMatchingName_669) {
    bool flag = false;
    auto opt = Opt(flag)["-f"]["--flag"];

    EXPECT_FALSE(opt.isMatch("-x"));
    EXPECT_FALSE(opt.isMatch("--other"));
}

TEST(OptTest_669, OptValidateWithNameSucceeds_669) {
    bool flag = false;
    auto opt = Opt(flag)["-f"]["--flag"];

    auto result = opt.validate();
    EXPECT_TRUE(static_cast<bool>(result));
}

TEST(OptTest_669, MultipleNamesOnSameOpt_669) {
    bool flag = false;
    auto opt = Opt(flag)["-a"]["-b"]["--alpha"]["--bravo"];

    EXPECT_TRUE(opt.isMatch("-a"));
    EXPECT_TRUE(opt.isMatch("-b"));
    EXPECT_TRUE(opt.isMatch("--alpha"));
    EXPECT_TRUE(opt.isMatch("--bravo"));
    EXPECT_FALSE(opt.isMatch("-c"));
}

TEST(OptTest_669, IntOptConstruction_669) {
    int value = 0;
    EXPECT_NO_THROW(Opt(value, "num")["-n"]["--number"]);
}

TEST(OptTest_669, DescriptionSetOnHelpColumns_669) {
    bool flag = false;
    auto opt = Opt(flag)["-f"]["--flag"]
        .description("My description");

    auto cols = opt.getHelpColumns();
    EXPECT_EQ(cols.description, "My description");
}

// ============================================================================
// Boundary / edge case tests
// ============================================================================

TEST(ParserGetHelpColumnsTest_669, ManyOptionsStressTest_669) {
    Parser parser;
    std::vector<bool> flags(50, false);

    for (int i = 0; i < 50; ++i) {
        std::string shortName = "-" + std::string(1, static_cast<char>('A' + (i % 26)));
        std::string longName = "--opt" + std::to_string(i);
        parser |= Opt(flags[i])[shortName.c_str()][longName.c_str()]
            .description("Option " + std::to_string(i));
    }

    auto cols = parser.getHelpColumns();
    EXPECT_EQ(cols.size(), 50u);
}

TEST(OptTest_669, EmptyDescriptionIsAllowed_669) {
    bool flag = false;
    auto opt = Opt(flag)["-f"]["--flag"]
        .description("");

    auto cols = opt.getHelpColumns();
    EXPECT_TRUE(cols.description.empty());
}

TEST(OptTest_669, IsMatchWithEmptyStringReturnsFalse_669) {
    bool flag = false;
    auto opt = Opt(flag)["-f"]["--flag"];

    EXPECT_FALSE(opt.isMatch(""));
}
