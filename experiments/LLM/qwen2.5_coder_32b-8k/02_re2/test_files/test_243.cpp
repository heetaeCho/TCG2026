#include <gtest/gtest.h>

#include "re2/re2.h"



namespace re2 {



class RE2Test_243 : public ::testing::Test {

protected:

    RE2Test_243() {}

    ~RE2Test_243() override {}



    void SetUp() override {}

    void TearDown() override {}

};



TEST_F(RE2Test_243, ValidPatternConstruction_243) {

    RE2 re("abc");

    EXPECT_TRUE(re.ok());

}



TEST_F(RE2Test_243, InvalidPatternConstruction_243) {

    RE2 re("[z-a]");

    EXPECT_FALSE(re.ok());

}



TEST_F(RE2Test_243, FullMatchValidPattern_243) {

    RE2 re("abc");

    EXPECT_TRUE(RE2::FullMatch("abc", re));

}



TEST_F(RE2Test_243, FullMatchInvalidPattern_243) {

    RE2 re("abc");

    EXPECT_FALSE(RE2::FullMatch("abcd", re));

}



TEST_F(RE2Test_243, PartialMatchValidPattern_243) {

    RE2 re("abc");

    EXPECT_TRUE(RE2::PartialMatch("123abc456", re));

}



TEST_F(RE2Test_243, PartialMatchInvalidPattern_243) {

    RE2 re("xyz");

    EXPECT_FALSE(RE2::PartialMatch("123abc456", re));

}



TEST_F(RE2Test_243, ReplaceValidPattern_243) {

    std::string input = "abc";

    RE2 re("abc");

    bool result = RE2::Replace(&input, re, "xyz");

    EXPECT_TRUE(result);

    EXPECT_EQ(input, "xyz");

}



TEST_F(RE2Test_243, ReplaceInvalidPattern_243) {

    std::string input = "abc";

    RE2 re("def");

    bool result = RE2::Replace(&input, re, "xyz");

    EXPECT_FALSE(result);

    EXPECT_EQ(input, "abc");

}



TEST_F(RE2Test_243, ProgramSizeBoundaryCheck_243) {

    RE2 re("");

    int size = re.ProgramSize();

    EXPECT_GE(size, 0);

}



TEST_F(RE2Test_243, ReverseProgramSizeBoundaryCheck_243) {

    RE2 re("");

    int size = re.ReverseProgramSize();

    EXPECT_GE(size, 0);

}



TEST_F(RE2Test_243, NumberOfCapturingGroupsBoundaryCheck_243) {

    RE2 re("abc");

    int count = re.NumberOfCapturingGroups();

    EXPECT_GE(count, 0);

}



TEST_F(RE2Test_243, NamedCapturingGroupsValidPattern_243) {

    RE2 re("(?P<name>abc)");

    const std::map<std::string, int>& groups = re.NamedCapturingGroups();

    EXPECT_EQ(groups.size(), 1);

    EXPECT_EQ(groups.at("name"), 1);

}



TEST_F(RE2Test_243, CapturingGroupNamesValidPattern_243) {

    RE2 re("(?P<name>abc)");

    const std::map<int, std::string>& names = re.CapturingGroupNames();

    EXPECT_EQ(names.size(), 1);

    EXPECT_EQ(names.at(1), "name");

}



TEST_F(RE2Test_243, PatternAccess_243) {

    RE2 re("abc");

    const std::string& pattern = re.pattern();

    EXPECT_EQ(pattern, "abc");

}



TEST_F(RE2Test_243, ErrorAccess_243) {

    RE2 re("[z-a]");

    const std::string& error = re.error();

    EXPECT_FALSE(error.empty());

}



TEST_F(RE2Test_243, ErrorCodeAccess_243) {

    RE2 re("[z-a]");

    ErrorCode code = re.error_code();

    EXPECT_NE(code, kRegexpSuccess);

}



TEST_F(RE2Test_243, ErrorArgAccess_243) {

    RE2 re("[z-a]");

    const std::string& error_arg = re.error_arg();

    EXPECT_FALSE(error_arg.empty());

}



}  // namespace re2
