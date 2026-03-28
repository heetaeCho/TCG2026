#include <gtest/gtest.h>
#include "catch2/internal/catch_clara.hpp"
#include "catch2/internal/catch_stringref.hpp"
#include <string>

using Catch::Clara::Opt;
using Catch::StringRef;

class OptIsMatchTest_663 : public ::testing::Test {
protected:
    // Helper to create an Opt with a bool ref (simplest constructor)
    bool flag = false;
};

TEST_F(OptIsMatchTest_663, MatchesExactShortOption_663) {
    Opt opt(flag);
    opt["-v"];
    EXPECT_TRUE(opt.isMatch("-v"));
}

TEST_F(OptIsMatchTest_663, MatchesExactLongOption_663) {
    Opt opt(flag);
    opt["--verbose"];
    EXPECT_TRUE(opt.isMatch("--verbose"));
}

TEST_F(OptIsMatchTest_663, DoesNotMatchDifferentOption_663) {
    Opt opt(flag);
    opt["-v"];
    EXPECT_FALSE(opt.isMatch("-x"));
}

TEST_F(OptIsMatchTest_663, DoesNotMatchWhenNoNamesRegistered_663) {
    Opt opt(flag);
    EXPECT_FALSE(opt.isMatch("-v"));
}

TEST_F(OptIsMatchTest_663, MatchesOneOfMultipleRegisteredNames_663) {
    Opt opt(flag);
    opt["-v"]["--verbose"];
    EXPECT_TRUE(opt.isMatch("-v"));
    EXPECT_TRUE(opt.isMatch("--verbose"));
}

TEST_F(OptIsMatchTest_663, DoesNotMatchUnregisteredAmongMultiple_663) {
    Opt opt(flag);
    opt["-v"]["--verbose"];
    EXPECT_FALSE(opt.isMatch("-x"));
    EXPECT_FALSE(opt.isMatch("--debug"));
}

TEST_F(OptIsMatchTest_663, MatchesWithStringRefInput_663) {
    Opt opt(flag);
    opt["--help"];
    StringRef token("--help");
    EXPECT_TRUE(opt.isMatch(token));
}

TEST_F(OptIsMatchTest_663, DoesNotMatchEmptyToken_663) {
    Opt opt(flag);
    opt["-v"];
    EXPECT_FALSE(opt.isMatch(""));
}

TEST_F(OptIsMatchTest_663, DoesNotMatchPartialOption_663) {
    Opt opt(flag);
    opt["--verbose"];
    EXPECT_FALSE(opt.isMatch("--verb"));
}

TEST_F(OptIsMatchTest_663, DoesNotMatchSupersetOption_663) {
    Opt opt(flag);
    opt["--verb"];
    EXPECT_FALSE(opt.isMatch("--verbose"));
}

TEST_F(OptIsMatchTest_663, MatchesShortOptionAmongMixed_663) {
    Opt opt(flag);
    opt["-h"]["--help"];
    EXPECT_TRUE(opt.isMatch("-h"));
}

TEST_F(OptIsMatchTest_663, MatchesLongOptionAmongMixed_663) {
    Opt opt(flag);
    opt["-h"]["--help"];
    EXPECT_TRUE(opt.isMatch("--help"));
}

TEST_F(OptIsMatchTest_663, DoesNotMatchSingleDashWithLongName_663) {
    Opt opt(flag);
    opt["--verbose"];
    EXPECT_FALSE(opt.isMatch("-verbose"));
}

TEST_F(OptIsMatchTest_663, MatchesSingleCharShortOption_663) {
    Opt opt(flag);
    opt["-a"];
    EXPECT_TRUE(opt.isMatch("-a"));
    EXPECT_FALSE(opt.isMatch("-b"));
}

TEST_F(OptIsMatchTest_663, MultipleOptionsThirdMatch_663) {
    Opt opt(flag);
    opt["-a"]["-b"]["-c"];
    EXPECT_TRUE(opt.isMatch("-c"));
}

TEST_F(OptIsMatchTest_663, CaseSensitivity_663) {
    Opt opt(flag);
    opt["-V"];
    // Assuming case-sensitive matching (standard CLI behavior)
    EXPECT_TRUE(opt.isMatch("-V"));
    // -v should not match -V if case-sensitive
    // This tests observable behavior
    EXPECT_FALSE(opt.isMatch("-v"));
}

TEST_F(OptIsMatchTest_663, MatchesWithStdStringInput_663) {
    Opt opt(flag);
    opt["--output"];
    std::string token = "--output";
    EXPECT_TRUE(opt.isMatch(StringRef(token)));
}
