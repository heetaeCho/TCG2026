#include <gtest/gtest.h>

#include "re2/re2.h"



using namespace re2;



class RE2Test_250 : public ::testing::Test {

protected:

    RE2Test_250() {}

    virtual ~RE2Test_250() {}



    void SetUp() override {

        // Setup code, if any

    }



    void TearDown() override {

        // Teardown code, if any

    }

};



// Test normal operation with a pattern containing named capturing groups

TEST_F(RE2Test_250, NamedCapturingGroups_NormalOperation_250) {

    RE2 re("(?<first>abc)(?<second>def)");

    const std::map<std::string, int>& named_groups = re.NamedCapturingGroups();

    EXPECT_EQ(named_groups.size(), 2);

    EXPECT_EQ(named_groups.at("first"), 1);

    EXPECT_EQ(named_groups.at("second"), 2);

}



// Test boundary condition with an empty pattern

TEST_F(RE2Test_250, NamedCapturingGroups_EmptyPattern_250) {

    RE2 re("");

    const std::map<std::string, int>& named_groups = re.NamedCapturingGroups();

    EXPECT_EQ(named_groups.size(), 0);

}



// Test boundary condition with a pattern without named capturing groups

TEST_F(RE2Test_250, NamedCapturingGroups_NoNamedGroups_250) {

    RE2 re("abcdef");

    const std::map<std::string, int>& named_groups = re.NamedCapturingGroups();

    EXPECT_EQ(named_groups.size(), 0);

}



// Test boundary condition with a pattern containing only named capturing groups

TEST_F(RE2Test_250, NamedCapturingGroups_OnlyNamedGroups_250) {

    RE2 re("(?<first>abc)(?<second>def)(?<third>ghi)");

    const std::map<std::string, int>& named_groups = re.NamedCapturingGroups();

    EXPECT_EQ(named_groups.size(), 3);

    EXPECT_EQ(named_groups.at("first"), 1);

    EXPECT_EQ(named_groups.at("second"), 2);

    EXPECT_EQ(named_groups.at("third"), 3);

}



// Test exceptional case with an invalid pattern

TEST_F(RE2Test_250, NamedCapturingGroups_InvalidPattern_250) {

    RE2 re("(?<first>abc(?<second>def)");

    EXPECT_FALSE(re.ok());

}
