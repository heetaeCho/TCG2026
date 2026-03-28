#include <gtest/gtest.h>
#include <string>
#include "Link.h"

class LinkUnknownTest_345 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(LinkUnknownTest_345, ConstructWithAction_345) {
    std::string actionStr = "SomeUnknownAction";
    LinkUnknown link(std::string(actionStr));
    EXPECT_EQ(link.getAction(), actionStr);
}

TEST_F(LinkUnknownTest_345, GetActionReturnsCorrectString_345) {
    LinkUnknown link(std::string("TestAction"));
    const std::string &action = link.getAction();
    EXPECT_EQ(action, "TestAction");
}

TEST_F(LinkUnknownTest_345, EmptyAction_345) {
    LinkUnknown link(std::string(""));
    EXPECT_EQ(link.getAction(), "");
}

TEST_F(LinkUnknownTest_345, GetKindReturnsUnknown_345) {
    LinkUnknown link(std::string("SomeAction"));
    EXPECT_EQ(link.getKind(), actionUnknown);
}

TEST_F(LinkUnknownTest_345, IsOkReturnsTrueForNonEmptyAction_345) {
    LinkUnknown link(std::string("ValidAction"));
    EXPECT_TRUE(link.isOk());
}

TEST_F(LinkUnknownTest_345, LongActionString_345) {
    std::string longAction(10000, 'x');
    LinkUnknown link(std::string(longAction));
    EXPECT_EQ(link.getAction(), longAction);
}

TEST_F(LinkUnknownTest_345, ActionWithSpecialCharacters_345) {
    std::string specialAction = "Action/With:Special#Characters?&=";
    LinkUnknown link(std::string(specialAction));
    EXPECT_EQ(link.getAction(), specialAction);
}

TEST_F(LinkUnknownTest_345, ActionWithWhitespace_345) {
    std::string wsAction = "  action with spaces  ";
    LinkUnknown link(std::string(wsAction));
    EXPECT_EQ(link.getAction(), wsAction);
}

TEST_F(LinkUnknownTest_345, ActionWithNewlines_345) {
    std::string nlAction = "action\nwith\nnewlines";
    LinkUnknown link(std::string(nlAction));
    EXPECT_EQ(link.getAction(), nlAction);
}

TEST_F(LinkUnknownTest_345, GetActionReturnsReference_345) {
    LinkUnknown link(std::string("RefTest"));
    const std::string &ref1 = link.getAction();
    const std::string &ref2 = link.getAction();
    EXPECT_EQ(&ref1, &ref2);
}

TEST_F(LinkUnknownTest_345, ActionWithNullCharacters_345) {
    std::string nullAction("action\0with\0nulls", 17);
    LinkUnknown link(std::string(nullAction));
    EXPECT_EQ(link.getAction(), nullAction);
    EXPECT_EQ(link.getAction().size(), 17u);
}

TEST_F(LinkUnknownTest_345, ActionWithUnicodeCharacters_345) {
    std::string unicodeAction = "действие"; // UTF-8 encoded
    LinkUnknown link(std::string(unicodeAction));
    EXPECT_EQ(link.getAction(), unicodeAction);
}

TEST_F(LinkUnknownTest_345, MoveConstructionPreservesAction_345) {
    std::string actionStr = "MoveTest";
    LinkUnknown link(std::move(actionStr));
    EXPECT_EQ(link.getAction(), "MoveTest");
}
