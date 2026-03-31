#include <gtest/gtest.h>
#include <string>
#include "Link.h"

// Test that getKind returns actionUnknown
TEST(LinkUnknownTest_344, GetKindReturnsActionUnknown_344) {
    LinkUnknown link(std::string("someAction"));
    EXPECT_EQ(link.getKind(), actionUnknown);
}

// Test that isOk returns true for a valid action string
TEST(LinkUnknownTest_344, IsOkReturnsTrueForValidAction_344) {
    LinkUnknown link(std::string("validAction"));
    EXPECT_TRUE(link.isOk());
}

// Test that getAction returns the action string passed in constructor
TEST(LinkUnknownTest_344, GetActionReturnsCorrectString_344) {
    std::string actionStr = "testAction";
    LinkUnknown link(std::string(actionStr));
    EXPECT_EQ(link.getAction(), actionStr);
}

// Test with empty action string
TEST(LinkUnknownTest_344, EmptyActionString_344) {
    LinkUnknown link(std::string(""));
    EXPECT_EQ(link.getAction(), "");
}

// Test that getKind always returns actionUnknown regardless of action string
TEST(LinkUnknownTest_344, GetKindAlwaysReturnsUnknown_344) {
    LinkUnknown link1(std::string("action1"));
    LinkUnknown link2(std::string("anotherAction"));
    LinkUnknown link3(std::string(""));
    
    EXPECT_EQ(link1.getKind(), actionUnknown);
    EXPECT_EQ(link2.getKind(), actionUnknown);
    EXPECT_EQ(link3.getKind(), actionUnknown);
}

// Test that actionUnknown has the expected enum value of 13
TEST(LinkUnknownTest_344, ActionUnknownEnumValue_344) {
    LinkUnknown link(std::string("test"));
    EXPECT_EQ(link.getKind(), 13);
}

// Test with a long action string
TEST(LinkUnknownTest_344, LongActionString_344) {
    std::string longAction(10000, 'x');
    LinkUnknown link(std::string(longAction));
    EXPECT_EQ(link.getAction(), longAction);
    EXPECT_EQ(link.getKind(), actionUnknown);
}

// Test with special characters in action string
TEST(LinkUnknownTest_344, SpecialCharactersInAction_344) {
    std::string specialAction = "action with spaces & special <chars> \"quotes\"";
    LinkUnknown link(std::string(specialAction));
    EXPECT_EQ(link.getAction(), specialAction);
}

// Test that the action string is preserved exactly (no trimming, etc.)
TEST(LinkUnknownTest_344, ActionStringPreservedExactly_344) {
    std::string actionWithWhitespace = "  leading and trailing spaces  ";
    LinkUnknown link(std::string(actionWithWhitespace));
    EXPECT_EQ(link.getAction(), actionWithWhitespace);
}

// Test with a URI-like action string
TEST(LinkUnknownTest_344, URILikeActionString_344) {
    std::string uriAction = "http://example.com/somepage";
    LinkUnknown link(std::string(uriAction));
    EXPECT_EQ(link.getAction(), uriAction);
    EXPECT_EQ(link.getKind(), actionUnknown);
}

// Test multiple calls to getAction return same result
TEST(LinkUnknownTest_344, MultipleGetActionCallsConsistent_344) {
    LinkUnknown link(std::string("consistentAction"));
    EXPECT_EQ(link.getAction(), "consistentAction");
    EXPECT_EQ(link.getAction(), "consistentAction");
    EXPECT_EQ(link.getAction(), "consistentAction");
}

// Test multiple calls to getKind return same result
TEST(LinkUnknownTest_344, MultipleGetKindCallsConsistent_344) {
    LinkUnknown link(std::string("test"));
    EXPECT_EQ(link.getKind(), actionUnknown);
    EXPECT_EQ(link.getKind(), actionUnknown);
}
