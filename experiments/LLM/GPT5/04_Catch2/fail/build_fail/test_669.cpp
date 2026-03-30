// File: tests/parser_get_help_columns_669_tests.cpp

#include <gtest/gtest.h>
#include <catch2/internal/catch_clara.hpp>  // adjust include path to your tree
#include <vector>
#include <string>

// Notes:
// - We only use public interfaces (Parser, Opt, operator|=, etc.).
// - We never inspect private state of Parser or Opt.
// - We assert observable behavior of Parser::getHelpColumns().

using Catch::Clara::Parser;
using Catch::Clara::Opt;

class ParserGetHelpColumnsTest_669 : public ::testing::Test {
protected:
    // Helper to build a boolean flag option with some distinct names,
    // using only public API. We do not assume anything about internal logic.
    static Opt makeBoolOptWithNames(bool& ref,
                                    Catch::StringRef n1,
                                    Catch::StringRef n2 = Catch::StringRef{}) {
        Opt o(ref);
        o[n1];
        if (!n2.empty()) {
            o[n2];
        }
        return o;
    }
};

// [Normal] Empty parser -> empty help columns
TEST_F(ParserGetHelpColumnsTest_669, EmptyParserReturnsEmpty_669) {
    Parser p;
    const auto cols = p.getHelpColumns();
    EXPECT_TRUE(cols.empty());
}

// [Normal] Single option -> size 1
TEST_F(ParserGetHelpColumnsTest_669, SingleOptionProducesOneRow_669) {
    Parser p;

    bool flagA = false;
    auto optA = makeBoolOptWithNames(flagA, "-a", "--alpha");
    p |= optA;  // Rely on public operator|= for composing parser options

    const auto cols = p.getHelpColumns();
    ASSERT_EQ(cols.size(), 1u);
}

// [Normal] Multiple options -> size equals number of options (order preserved by public API)
TEST_F(ParserGetHelpColumnsTest_669, MultipleOptionsProduceSameCount_669) {
    Parser p;

    bool flagA = false, flagB = false, flagC = false;
    auto optA = makeBoolOptWithNames(flagA, "-a", "--alpha");
    auto optB = makeBoolOptWithNames(flagB, "-b", "--beta");
    auto optC = makeBoolOptWithNames(flagC, "-c", "--gamma");

    p |= optA;
    p |= optB;
    p |= optC;

    const auto cols = p.getHelpColumns();
    ASSERT_EQ(cols.size(), 3u);
}

// [Boundary] Large number of options -> vector sized to option count
TEST_F(ParserGetHelpColumnsTest_669, ManyOptionsScaleLinearly_669) {
    Parser p;

    // Use a modest “large” value to keep the test fast and portable
    constexpr std::size_t N = 100;
    std::vector<bool> flags(N, false);

    for (std::size_t i = 0; i < N; ++i) {
        // Create distinct short names like -o0, -o1, ..., and long names --opt0, ...
        const std::string shortName = "-o" + std::to_string(i);
        const std::string longName  = "--opt" + std::to_string(i);

        auto opt = makeBoolOptWithNames(flags[i], shortName.c_str(), longName.c_str());
        p |= opt;
    }

    const auto cols = p.getHelpColumns();
    ASSERT_EQ(cols.size(), N);
}

// [Behavioral stability] Multiple calls do not change result size
TEST_F(ParserGetHelpColumnsTest_669, RepeatedCallsAreIdempotent_669) {
    Parser p;

    bool flagA = false, flagB = false;
    auto optA = makeBoolOptWithNames(flagA, "-a", "--alpha");
    auto optB = makeBoolOptWithNames(flagB, "-b", "--beta");

    p |= optA;
    p |= optB;

    const auto cols1 = p.getHelpColumns();
    const auto cols2 = p.getHelpColumns();

    ASSERT_EQ(cols1.size(), 2u);
    ASSERT_EQ(cols2.size(), 2u);
}

// [Boundary] Adding options after an initial call updates results on next call
TEST_F(ParserGetHelpColumnsTest_669, ReflectsNewOptionsOnSubsequentCall_669) {
    Parser p;

    bool flagA = false;
    auto optA = makeBoolOptWithNames(flagA, "-a", "--alpha");
    p |= optA;

    const auto initial = p.getHelpColumns();
    ASSERT_EQ(initial.size(), 1u);

    bool flagB = false;
    auto optB = makeBoolOptWithNames(flagB, "-b", "--beta");
    p |= optB;

    const auto after = p.getHelpColumns();
    ASSERT_EQ(after.size(), 2u);
}
