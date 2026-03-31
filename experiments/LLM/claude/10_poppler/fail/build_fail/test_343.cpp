#include <gtest/gtest.h>
#include "Link.h"
#include <string>

// Test that LinkUnknown constructed with a valid action string is OK
TEST(LinkUnknownTest_343, IsOkReturnsTrue_343) {
    LinkUnknown link(std::string("someUnknownAction"));
    EXPECT_TRUE(link.isOk());
}

// Test that getKind returns the correct kind for LinkUnknown
TEST(LinkUnknownTest_343, GetKindReturnsCorrectType_343) {
    LinkUnknown link(std::string("testAction"));
    EXPECT_EQ(link.getKind(), actionUnknown);
}

// Test that getAction returns the action string that was passed in
TEST(LinkUnknownTest_343, GetActionReturnsCorrectString_343) {
    std::string actionStr = "customAction";
    LinkUnknown link(std::string(actionStr));
    EXPECT_EQ(link.getAction(), actionStr);
}

// Test with an empty action string
TEST(LinkUnknownTest_343, EmptyActionString_343) {
    LinkUnknown link(std::string(""));
    EXPECT_TRUE(link.isOk());
    EXPECT_EQ(link.getAction(), "");
    EXPECT_EQ(link.getKind(), actionUnknown);
}

// Test with a very long action string
TEST(LinkUnknownTest_343, LongActionString_343) {
    std::string longStr(10000, 'x');
    LinkUnknown link(std::string(longStr));
    EXPECT_TRUE(link.isOk());
    EXPECT_EQ(link.getAction(), longStr);
}

// Test with special characters in action string
TEST(LinkUnknownTest_343, SpecialCharactersInAction_343) {
    std::string specialStr = "action:with/special?chars&more=stuff#fragment";
    LinkUnknown link(std::string(specialStr));
    EXPECT_TRUE(link.isOk());
    EXPECT_EQ(link.getAction(), specialStr);
}

// Test that action is properly moved (original string should be moved from)
TEST(LinkUnknownTest_343, ActionIsMovedCorrectly_343) {
    std::string actionStr = "moveTest";
    std::string expected = actionStr;
    LinkUnknown link(std::move(actionStr));
    EXPECT_EQ(link.getAction(), expected);
    EXPECT_EQ(link.getKind(), actionUnknown);
}

// Test with whitespace-only action string
TEST(LinkUnknownTest_343, WhitespaceActionString_343) {
    LinkUnknown link(std::string("   "));
    EXPECT_TRUE(link.isOk());
    EXPECT_EQ(link.getAction(), "   ");
}

// Test with null character embedded in action string
TEST(LinkUnknownTest_343, NullCharacterInAction_343) {
    std::string strWithNull("abc\0def", 7);
    LinkUnknown link(std::string(strWithNull));
    EXPECT_TRUE(link.isOk());
    EXPECT_EQ(link.getAction(), strWithNull);
}

// Test getAction returns a const reference (multiple calls return same value)
TEST(LinkUnknownTest_343, GetActionConsistency_343) {
    LinkUnknown link(std::string("consistentAction"));
    const std::string &ref1 = link.getAction();
    const std::string &ref2 = link.getAction();
    EXPECT_EQ(ref1, ref2);
    EXPECT_EQ(&ref1, &ref2);
}
