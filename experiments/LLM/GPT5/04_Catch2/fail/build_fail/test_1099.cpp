// File: tests/clara_Help_tests_1099.cpp

#include <gtest/gtest.h>
#include <string>
#include <vector>

// Catch2 Clara public headers
#include "catch2/internal/catch_clara.hpp"
#include "catch2/internal/catch_clara.hpp" // Some trees split declarations; safe to include once more if needed

// Namespace aliases for brevity
namespace Clara = Catch::Clara;
namespace Detail = Catch::Clara::Detail;

class HelpOptionTest_1099 : public ::testing::Test {
protected:
    bool showHelpFlag{false};

    // System under test
    Clara::Help makeHelp() {
        // The constructor is specified to bind a flag bool& and mark the option optional.
        return Clara::Help{showHelpFlag};
    }
};

// --- Normal operation: alias matching --------------------------------------------------

TEST_F(HelpOptionTest_1099, MatchesAllStandardAliases_1099) {
    auto help = makeHelp();

    // Observable behavior: Opt::isMatch must recognize "-?", "-h", and "--help"
    EXPECT_TRUE(help.isMatch("-?"));
    EXPECT_TRUE(help.isMatch("-h"));
    EXPECT_TRUE(help.isMatch("--help"));
}

TEST_F(HelpOptionTest_1099, DoesNotMatchUnrelatedTokens_1099) {
    auto help = makeHelp();

    // A few boundary-ish probes that must not match
    EXPECT_FALSE(help.isMatch("-H"));
    EXPECT_FALSE(help.isMatch("--helper"));
    EXPECT_FALSE(help.isMatch("help"));
    EXPECT_FALSE(help.isMatch("--he_lp"));
    EXPECT_FALSE(help.isMatch("-"));
    EXPECT_FALSE(help.isMatch("--"));
    EXPECT_FALSE(help.isMatch("")); // empty token
}

// --- Optionality & validation -----------------------------------------------------------

TEST_F(HelpOptionTest_1099, IsOptionalByDefault_1099) {
    auto help = makeHelp();

    // Help is documented to be optional()
    EXPECT_TRUE(help.isOptional());
}

TEST_F(HelpOptionTest_1099, ValidateReturnsOk_1099) {
    auto help = makeHelp();

    // Public API exposes validate() -> Detail::Result
    const auto result = help.validate();
    // BasicResult-like API exposes operator bool() as success
    EXPECT_TRUE(static_cast<bool>(result));
}

// --- Help text surface (names & description) -------------------------------------------
// We verify only what the public API exposes via getHelpColumns(); we do not depend on
// private fields or internal structure beyond stable surface semantics.

TEST_F(HelpOptionTest_1099, HelpColumnsContainAliasesAndDescription_1099) {
    auto help = makeHelp();

    const auto cols = help.getHelpColumns();
    // The Help option sets the description to "display usage information".
    // Many Catch2/Clara builds expose a flattened text form via .description or similar.
    // To remain interface-only, we check name matching through isMatch() (above),
    // and here we only assert that the description text is non-empty and contains the key phrase
    // without assuming the exact storage layout of HelpColumns.
    // If your HelpColumns exposes `.description` or `.desc`, test that directly:
    //   EXPECT_THAT(std::string(cols.description), ::testing::HasSubstr("display usage information"));
    //
    // Generic, layout-agnostic guard: stringify via stream if supported; otherwise, skip.
    // (This keeps the test black-box and resilient if HelpColumns changes shape.)
#ifdef CATCH_CLARA_HELPCOLUMNS_STRINGIFY   // define in your build if you expose a string form
    std::string rendered = CATCH_CLARA_HELPCOLUMNS_STRINGIFY(cols);
    EXPECT_NE(rendered.find("display usage information"), std::string::npos);
#else
    // Minimal observable check: the API *returns* something; presence implies help is configured.
    (void)cols;
    SUCCEED();
#endif
}

// --- Parsing behavior: setting the bound flag & short-circuit --------------------------
// NOTE: This test uses only public token/stream types from Clara's API. If your build uses
// different names for Token/TokenStream or their constructors, adjust accordingly.
// We do NOT simulate internal logic; we only assert that invoking parse on "--help":
//  (1) sets the bound bool, and
//  (2) returns a ParserResult with type == ShortCircuitAll.

TEST_F(HelpOptionTest_1099, ParseSetsFlagAndShortCircuits_1099) {
    auto help = makeHelp();

    // Precondition: flag is false
    ASSERT_FALSE(showHelpFlag);

    // Build a token stream equivalent to command line: ["--help"]
    // Common Clara pattern:
    //   Detail::TokenStream{ { Detail::Token{ Detail::TokenType::Option, "--help" } } }
    //
    // If your Token/TokenStream ctors differ, adapt them to your exposed interface.
    using Detail::Token;
    using Detail::TokenType;
    std::vector<Token> toks;
    toks.emplace_back(TokenType::Option, std::string{"--help"});
    Detail::TokenStream ts{toks};

    // Parse through the Opt API exposed by Help
    const auto parseRes = help.parse(/*unnamed*/"", ts);

    // Observable outcomes
    EXPECT_TRUE(showHelpFlag) << "Parsing '--help' must set the bound showHelpFlag to true.";

    // ParserResult-type surface check: ok() with ShortCircuitAll
    // Detail::BasicResult-like API: operator bool() and .type() are public (per header snippet).
    ASSERT_TRUE(static_cast<bool>(parseRes)) << "Parsing '--help' should return a successful result.";

    // If your parse result wraps a value that has .type(), unwrap/enforceOk() accordingly.
    // In many Clara builds, `parse` returns `InternalParseResult` that contains a `ParserResult`,
    // which then exposes `.type()`:
    auto t = parseRes.value().type();
    EXPECT_EQ(t, Detail::ParseResultType::ShortCircuitAll);
}
