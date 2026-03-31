#include "gtest/gtest.h"
#include "tinyxml2.h"

using namespace tinyxml2;

// Helper to access StrPair since it's part of tinyxml2 namespace
// We test only through the public interface.

class StrPairTest_154 : public ::testing::Test {
protected:
    StrPair sp;
};

// ==================== Construction / Empty ====================

TEST_F(StrPairTest_154, DefaultConstructedIsEmpty_154) {
    EXPECT_TRUE(sp.Empty());
}

TEST_F(StrPairTest_154, DefaultConstructedGetStrReturnsEmpty_154) {
    const char* result = sp.GetStr();
    EXPECT_NE(result, nullptr);
    EXPECT_STREQ(result, "");
}

// ==================== Set ====================

TEST_F(StrPairTest_154, SetMakesNonEmpty_154) {
    char buf[] = "hello";
    sp.Set(buf, buf + 5, 0);
    EXPECT_FALSE(sp.Empty());
}

TEST_F(StrPairTest_154, SetAndGetStr_154) {
    char buf[] = "hello world";
    sp.Set(buf, buf + 5, 0);
    const char* result = sp.GetStr();
    EXPECT_STREQ(result, "hello");
}

TEST_F(StrPairTest_154, SetEmptyRange_154) {
    char buf[] = "hello";
    sp.Set(buf, buf, 0);
    const char* result = sp.GetStr();
    EXPECT_STREQ(result, "");
}

// ==================== SetStr ====================

TEST_F(StrPairTest_154, SetStrBasic_154) {
    sp.SetStr("test string", 0);
    EXPECT_FALSE(sp.Empty());
    const char* result = sp.GetStr();
    EXPECT_STREQ(result, "test string");
}

TEST_F(StrPairTest_154, SetStrEmptyString_154) {
    sp.SetStr("", 0);
    const char* result = sp.GetStr();
    EXPECT_STREQ(result, "");
}

TEST_F(StrPairTest_154, SetStrOverwritesPrevious_154) {
    sp.SetStr("first", 0);
    EXPECT_STREQ(sp.GetStr(), "first");
    sp.SetStr("second", 0);
    EXPECT_STREQ(sp.GetStr(), "second");
}

// ==================== SetInternedStr ====================

TEST_F(StrPairTest_154, SetInternedStrBasic_154) {
    sp.SetInternedStr("interned");
    EXPECT_FALSE(sp.Empty());
    const char* result = sp.GetStr();
    EXPECT_STREQ(result, "interned");
}

TEST_F(StrPairTest_154, SetInternedStrEmpty_154) {
    sp.SetInternedStr("");
    const char* result = sp.GetStr();
    EXPECT_STREQ(result, "");
}

// ==================== Reset ====================

TEST_F(StrPairTest_154, ResetMakesEmpty_154) {
    sp.SetStr("something", 0);
    EXPECT_FALSE(sp.Empty());
    sp.Reset();
    EXPECT_TRUE(sp.Empty());
}

TEST_F(StrPairTest_154, ResetOnEmptyIsNoOp_154) {
    sp.Reset();
    EXPECT_TRUE(sp.Empty());
}

TEST_F(StrPairTest_154, ResetThenGetStrReturnsEmpty_154) {
    sp.SetStr("data", 0);
    sp.Reset();
    const char* result = sp.GetStr();
    EXPECT_STREQ(result, "");
}

// ==================== TransferTo ====================

TEST_F(StrPairTest_154, TransferToMovesData_154) {
    sp.SetStr("transfer me", 0);
    StrPair other;
    sp.TransferTo(&other);
    EXPECT_STREQ(other.GetStr(), "transfer me");
    EXPECT_TRUE(sp.Empty());
}

TEST_F(StrPairTest_154, TransferToEmptyPair_154) {
    StrPair other;
    other.SetStr("existing", 0);
    sp.TransferTo(&other);
    // After transferring empty sp to other, other should be reset/empty
    EXPECT_TRUE(other.Empty());
}

TEST_F(StrPairTest_154, TransferToOverwritesDestination_154) {
    sp.SetStr("source", 0);
    StrPair dest;
    dest.SetStr("destination", 0);
    sp.TransferTo(&dest);
    EXPECT_STREQ(dest.GetStr(), "source");
    EXPECT_TRUE(sp.Empty());
}

// ==================== ParseName ====================

TEST_F(StrPairTest_154, ParseNameValidName_154) {
    char buf[] = "validName rest";
    char* result = sp.ParseName(buf);
    EXPECT_NE(result, nullptr);
    // After parsing, the name should be stored
    const char* name = sp.GetStr();
    EXPECT_STREQ(name, "validName");
}

TEST_F(StrPairTest_154, ParseNameWithDigitsAndDots_154) {
    char buf[] = "name123.suffix rest";
    // XML names can contain digits and certain chars after first char
    char* result = sp.ParseName(buf);
    EXPECT_NE(result, nullptr);
}

TEST_F(StrPairTest_154, ParseNameStartingWithDigit_154) {
    char buf[] = "123invalid";
    char* result = sp.ParseName(buf);
    // Names cannot start with digits in XML, should return null
    EXPECT_EQ(result, nullptr);
}

TEST_F(StrPairTest_154, ParseNameEmptyString_154) {
    char buf[] = "";
    char* result = sp.ParseName(buf);
    EXPECT_EQ(result, nullptr);
}

TEST_F(StrPairTest_154, ParseNameNullInput_154) {
    char* result = sp.ParseName(nullptr);
    EXPECT_EQ(result, nullptr);
}

TEST_F(StrPairTest_154, ParseNameWithUnderscore_154) {
    char buf[] = "_myName ";
    char* result = sp.ParseName(buf);
    EXPECT_NE(result, nullptr);
    EXPECT_STREQ(sp.GetStr(), "_myName");
}

TEST_F(StrPairTest_154, ParseNameWithColon_154) {
    char buf[] = "ns:element ";
    char* result = sp.ParseName(buf);
    EXPECT_NE(result, nullptr);
}

// ==================== ParseText ====================

TEST_F(StrPairTest_154, ParseTextBasic_154) {
    char buf[] = "some text<end";
    int lineNum = 1;
    char* result = sp.ParseText(buf, "<", 0, &lineNum);
    EXPECT_NE(result, nullptr);
    EXPECT_STREQ(sp.GetStr(), "some text");
}

TEST_F(StrPairTest_154, ParseTextEndTagNotFound_154) {
    char buf[] = "no end tag here";
    int lineNum = 1;
    char* result = sp.ParseText(buf, "]]>", 0, &lineNum);
    EXPECT_EQ(result, nullptr);
}

TEST_F(StrPairTest_154, ParseTextEmptyContent_154) {
    char buf[] = "<immediately";
    int lineNum = 1;
    char* result = sp.ParseText(buf, "<", 0, &lineNum);
    EXPECT_NE(result, nullptr);
    EXPECT_STREQ(sp.GetStr(), "");
}

TEST_F(StrPairTest_154, ParseTextWithNewlines_154) {
    char buf[] = "line1\nline2\nline3<end";
    int lineNum = 1;
    char* result = sp.ParseText(buf, "<", 0, &lineNum);
    EXPECT_NE(result, nullptr);
    // Line number should have been incremented
    EXPECT_EQ(lineNum, 3);
}

TEST_F(StrPairTest_154, ParseTextNullInput_154) {
    int lineNum = 1;
    char* result = sp.ParseText(nullptr, "<", 0, &lineNum);
    EXPECT_EQ(result, nullptr);
}

TEST_F(StrPairTest_154, ParseTextMultiCharEndTag_154) {
    char buf[] = "content-->after";
    int lineNum = 1;
    char* result = sp.ParseText(buf, "-->", 0, &lineNum);
    EXPECT_NE(result, nullptr);
    EXPECT_STREQ(sp.GetStr(), "content");
}

// ==================== Multiple operations ====================

TEST_F(StrPairTest_154, SetThenResetThenSetAgain_154) {
    sp.SetStr("first", 0);
    EXPECT_STREQ(sp.GetStr(), "first");
    sp.Reset();
    EXPECT_TRUE(sp.Empty());
    sp.SetStr("second", 0);
    EXPECT_STREQ(sp.GetStr(), "second");
}

TEST_F(StrPairTest_154, SetInternedThenTransfer_154) {
    sp.SetInternedStr("interned value");
    StrPair dest;
    sp.TransferTo(&dest);
    EXPECT_STREQ(dest.GetStr(), "interned value");
    EXPECT_TRUE(sp.Empty());
}

TEST_F(StrPairTest_154, MultipleGetStrCallsReturnSame_154) {
    sp.SetStr("consistent", 0);
    const char* r1 = sp.GetStr();
    const char* r2 = sp.GetStr();
    EXPECT_STREQ(r1, "consistent");
    EXPECT_STREQ(r2, "consistent");
}

// ==================== Boundary: long strings ====================

TEST_F(StrPairTest_154, SetStrLongString_154) {
    std::string longStr(10000, 'x');
    sp.SetStr(longStr.c_str(), 0);
    const char* result = sp.GetStr();
    EXPECT_STREQ(result, longStr.c_str());
}

TEST_F(StrPairTest_154, ParseNameSingleChar_154) {
    char buf[] = "a ";
    char* result = sp.ParseName(buf);
    EXPECT_NE(result, nullptr);
    EXPECT_STREQ(sp.GetStr(), "a");
}

// ==================== Destructor safety ====================

TEST_F(StrPairTest_154, DestructorAfterSetStr_154) {
    // Create in a scope and let it destruct - no crash expected
    {
        StrPair local;
        local.SetStr("will be destroyed", 0);
    }
    SUCCEED();
}

TEST_F(StrPairTest_154, DestructorAfterSet_154) {
    {
        char buf[] = "temporary";
        StrPair local;
        local.Set(buf, buf + 4, 0);
    }
    SUCCEED();
}

TEST_F(StrPairTest_154, DestructorAfterReset_154) {
    {
        StrPair local;
        local.SetStr("data", 0);
        local.Reset();
    }
    SUCCEED();
}
