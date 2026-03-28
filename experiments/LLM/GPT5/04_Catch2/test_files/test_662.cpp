#include <gtest/gtest.h>
#include <string>

// Headers under test
#include "catch2/internal/catch_clara.hpp"

using Catch::Clara::Opt;
using Catch::StringRef;

// Fixture (kept minimal — we only exercise public API)
class OptGetHelpColumnsTest_662 : public ::testing::Test {};

// Multiple names + hint + description -> names joined by ", " and " <hint>" appended
TEST_F(OptGetHelpColumnsTest_662, MultipleNamesWithHintAndDescription_662) {
    int outVal = 0;                        // value-bound option so we can provide a hint
    Opt opt(outVal, StringRef("FILE"));    // sets the hint
    opt["-o"]["--output"]("write to file");// add names + set description

    auto cols = opt.getHelpColumns();

    EXPECT_EQ(cols.left, "-o, --output <FILE>");
    EXPECT_TRUE(cols.descriptions == StringRef("write to file"));
}

// Single name, no hint -> no angle brackets appended; description preserved
TEST_F(OptGetHelpColumnsTest_662, SingleNameNoHint_FormatsCorrectly_662) {
    bool verbose = false;
    Opt opt(verbose);                // flag-style, no hint
    opt["-v"]("enable verbose output");

    auto cols = opt.getHelpColumns();

    EXPECT_EQ(cols.left, "-v");
    EXPECT_TRUE(cols.descriptions == StringRef("enable verbose output"));
}

// No names but hint present -> left begins with a space then "<hint>"
TEST_F(OptGetHelpColumnsTest_662, NoNamesButHint_LeavesLeadingSpaceBeforeHint_662) {
    int value = 0;
    Opt opt(value, StringRef("VALUE")); // set hint but do not add any names
    opt("some description");

    auto cols = opt.getHelpColumns();

    EXPECT_EQ(cols.left, " <VALUE>"); // leading space is observable behavior
    EXPECT_TRUE(cols.descriptions == StringRef("some description"));
}

// Ordering & separator correctness with 3 names, no hint
TEST_F(OptGetHelpColumnsTest_662, JoinsThreeNamesWithCommaAndSpace_Exact_662) {
    bool flag = false;
    Opt opt(flag);
    opt["-a"]["-b"]["--all"]("all the things");

    auto cols = opt.getHelpColumns();

    EXPECT_EQ(cols.left, "-a, -b, --all"); // exact order & separators
    EXPECT_TRUE(cols.descriptions == StringRef("all the things"));
}

// Default description when none set -> empty
TEST_F(OptGetHelpColumnsTest_662, DefaultDescriptionIsEmpty_662) {
    bool f = false;
    Opt opt(f);
    opt["--flag"];                 // names only, no description()

    auto cols = opt.getHelpColumns();

    EXPECT_EQ(cols.left, "--flag");
    EXPECT_TRUE(cols.descriptions.empty());
}
