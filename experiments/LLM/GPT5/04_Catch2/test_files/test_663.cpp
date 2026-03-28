// File: opt_is_match_tests_663.cpp
#include <gtest/gtest.h>

#include "catch2/internal/catch_clara.hpp"
#include "catch2/internal/catch_stringref.hpp"

using Catch::StringRef;
using Catch::Clara::Opt;

// -------------------------------------------------------------
// Basic behavior with no configured option names
// -------------------------------------------------------------
TEST(ClaraOptTest_663, NoNames_NoMatch_663) {
    bool flag = false;
    Opt opt(flag);

    EXPECT_FALSE(opt.isMatch(StringRef("-x")));
    EXPECT_FALSE(opt.isMatch(StringRef("--any")));
    EXPECT_FALSE(opt.isMatch(StringRef("")));
}

// -------------------------------------------------------------
// Adding a single name should allow exact token matches
// -------------------------------------------------------------
TEST(ClaraOptTest_663, SingleExactName_MatchesToken_663) {
    bool flag = false;
    Opt opt(flag);

    opt[StringRef("-x")];

    EXPECT_TRUE(opt.isMatch(StringRef("-x")));
    EXPECT_FALSE(opt.isMatch(StringRef("-y")));
    EXPECT_FALSE(opt.isMatch(StringRef("--other")));
}

// -------------------------------------------------------------
// Multiple names: match should succeed for any of the added names
// -------------------------------------------------------------
TEST(ClaraOptTest_663, MultipleNames_MatchAnyConfigured_663) {
    bool flag = false;
    Opt opt(flag);

    opt[StringRef("-h")][StringRef("--help")];

    EXPECT_TRUE(opt.isMatch(StringRef("-h")));
    EXPECT_TRUE(opt.isMatch(StringRef("--help")));
    EXPECT_FALSE(opt.isMatch(StringRef("--version")));
}

// -------------------------------------------------------------
// Operator[] should be chainable and return a reference to *this
// -------------------------------------------------------------
TEST(ClaraOptTest_663, BracketOperator_IsFluent_663) {
    bool flag = false;
    Opt opt(flag);

    Opt& ret = (opt[StringRef("-a")]);
    EXPECT_EQ(&ret, &opt);              // verify fluent API by reference identity
    EXPECT_TRUE(opt.isMatch(StringRef("-a")));
}

// -------------------------------------------------------------
// Empty token: unless an empty name was added explicitly, it should not match
// -------------------------------------------------------------
TEST(ClaraOptTest_663, EmptyToken_DoesNotMatchByDefault_663) {
    bool flag = false;
    Opt opt(flag);

    opt[StringRef("-n")];

    EXPECT_FALSE(opt.isMatch(StringRef("")));
}

// -------------------------------------------------------------
// Very long option names should be handled as ordinary inputs
// -------------------------------------------------------------
TEST(ClaraOptTest_663, VeryLongOptionName_Matches_663) {
    bool flag = false;
    Opt opt(flag);

    std::string longCore(1000, 'a');        // 1000 'a's
    std::string longOpt = std::string("--") + longCore;

    opt[StringRef(longOpt)];
    EXPECT_TRUE(opt.isMatch(StringRef(longOpt)));
}

// -------------------------------------------------------------
// Adding duplicate names should not break matching semantics
// -------------------------------------------------------------
TEST(ClaraOptTest_663, DuplicateNames_StillMatch_663) {
    bool flag = false;
    Opt opt(flag);

    opt[StringRef("-dup")][StringRef("-dup")];

    EXPECT_TRUE(opt.isMatch(StringRef("-dup")));
    EXPECT_FALSE(opt.isMatch(StringRef("-other")));
}

// -------------------------------------------------------------
// isMatch should be callable on a const-qualified object
// -------------------------------------------------------------
TEST(ClaraOptTest_663, IsMatch_OnConstObject_663) {
    bool flag = false;
    Opt opt(flag);
    opt[StringRef("-c")];

    const Opt& copt = opt;
    EXPECT_TRUE(copt.isMatch(StringRef("-c")));
    EXPECT_FALSE(copt.isMatch(StringRef("--nope")));
}
