#include "gtest/gtest.h"
#include "./TestProjects/tinyxml2/tinyxml2.h"

using namespace tinyxml2;

// Test fixture for StrPair tests
class StrPairTest_3 : public ::testing::Test {
protected:
    StrPair sp;
};

// ===== Default Construction Tests =====

TEST_F(StrPairTest_3, DefaultConstructionIsEmpty_3) {
    EXPECT_TRUE(sp.Empty());
}

TEST_F(StrPairTest_3, DefaultConstructionGetStrReturnsEmptyString_3) {
    const char* result = sp.GetStr();
    EXPECT_STREQ(result, "");
}

// ===== SetInternedStr Tests =====

TEST_F(StrPairTest_3, SetInternedStrSetsString_3) {
    sp.SetInternedStr("hello");
    const char* result = sp.GetStr();
    EXPECT_STREQ(result, "hello");
}

TEST_F(StrPairTest_3, SetInternedStrNotEmpty_3) {
    sp.SetInternedStr("test");
    EXPECT_FALSE(sp.Empty());
}

TEST_F(StrPairTest_3, SetInternedStrEmptyString_3) {
    sp.SetInternedStr("");
    const char* result = sp.GetStr();
    EXPECT_STREQ(result, "");
}

TEST_F(StrPairTest_3, SetInternedStrOverwritesPrevious_3) {
    sp.SetInternedStr("first");
    sp.SetInternedStr("second");
    const char* result = sp.GetStr();
    EXPECT_STREQ(result, "second");
}

TEST_F(StrPairTest_3, SetInternedStrLongString_3) {
    const char* longStr = "This is a relatively long string to test that SetInternedStr handles it correctly";
    sp.SetInternedStr(longStr);
    EXPECT_STREQ(sp.GetStr(), longStr);
}

// ===== Set Tests =====

TEST_F(StrPairTest_3, SetWithStartAndEnd_3) {
    char buf[] = "hello world";
    sp.Set(buf, buf + 5, 0);
    EXPECT_FALSE(sp.Empty());
}

TEST_F(StrPairTest_3, SetEmptyRange_3) {
    char buf[] = "test";
    sp.Set(buf, buf, 0);
    // Empty range
    const char* result = sp.GetStr();
    EXPECT_STREQ(result, "");
}

// ===== Reset Tests =====

TEST_F(StrPairTest_3, ResetMakesEmpty_3) {
    sp.SetInternedStr("hello");
    sp.Reset();
    EXPECT_TRUE(sp.Empty());
}

TEST_F(StrPairTest_3, ResetThenGetStrReturnsEmpty_3) {
    sp.SetInternedStr("hello");
    sp.Reset();
    EXPECT_STREQ(sp.GetStr(), "");
}

// ===== SetStr Tests =====

TEST_F(StrPairTest_3, SetStrCopiesString_3) {
    sp.SetStr("hello", 0);
    EXPECT_STREQ(sp.GetStr(), "hello");
}

TEST_F(StrPairTest_3, SetStrEmptyString_3) {
    sp.SetStr("", 0);
    EXPECT_STREQ(sp.GetStr(), "");
}

TEST_F(StrPairTest_3, SetStrNotEmpty_3) {
    sp.SetStr("data", 0);
    EXPECT_FALSE(sp.Empty());
}

TEST_F(StrPairTest_3, SetStrOverwritesPrevious_3) {
    sp.SetStr("first", 0);
    sp.SetStr("second", 0);
    EXPECT_STREQ(sp.GetStr(), "second");
}

// ===== TransferTo Tests =====

TEST_F(StrPairTest_3, TransferToMovesData_3) {
    sp.SetInternedStr("transfer_me");
    StrPair target;
    sp.TransferTo(&target);
    EXPECT_STREQ(target.GetStr(), "transfer_me");
}

TEST_F(StrPairTest_3, TransferToEmptiesSource_3) {
    sp.SetInternedStr("transfer_me");
    StrPair target;
    sp.TransferTo(&target);
    EXPECT_TRUE(sp.Empty());
}

TEST_F(StrPairTest_3, TransferToOverwritesTarget_3) {
    sp.SetInternedStr("source");
    StrPair target;
    target.SetInternedStr("target_original");
    sp.TransferTo(&target);
    EXPECT_STREQ(target.GetStr(), "source");
}

// ===== Empty Tests =====

TEST_F(StrPairTest_3, EmptyAfterReset_3) {
    sp.SetStr("test", 0);
    sp.Reset();
    EXPECT_TRUE(sp.Empty());
}

TEST_F(StrPairTest_3, NotEmptyAfterSetStr_3) {
    sp.SetStr("notempty", 0);
    EXPECT_FALSE(sp.Empty());
}

// ===== ParseName Tests =====

TEST_F(StrPairTest_3, ParseNameValidName_3) {
    char buf[] = "validName rest";
    char* result = sp.ParseName(buf);
    EXPECT_NE(result, nullptr);
}

TEST_F(StrPairTest_3, ParseNameEmptyInput_3) {
    char buf[] = "";
    char* result = sp.ParseName(buf);
    // Empty input should not produce a valid name
    EXPECT_EQ(result, nullptr);
}

TEST_F(StrPairTest_3, ParseNameStartingWithDigit_3) {
    char buf[] = "123invalid";
    char* result = sp.ParseName(buf);
    // Names cannot start with digits in XML
    EXPECT_EQ(result, nullptr);
}

TEST_F(StrPairTest_3, ParseNameWithUnderscorePrefix_3) {
    char buf[] = "_validName>";
    char* result = sp.ParseName(buf);
    EXPECT_NE(result, nullptr);
}

TEST_F(StrPairTest_3, ParseNameStopsAtSpecialChar_3) {
    char buf[] = "name=value";
    char* result = sp.ParseName(buf);
    EXPECT_NE(result, nullptr);
    // Should stop at '='
    EXPECT_EQ(*result, '=');
}

// ===== ParseText Tests =====

TEST_F(StrPairTest_3, ParseTextFindsEndTag_3) {
    char buf[] = "some text<end";
    int lineNum = 1;
    char* result = sp.ParseText(buf, "<", 0, &lineNum);
    EXPECT_NE(result, nullptr);
}

TEST_F(StrPairTest_3, ParseTextNoEndTag_3) {
    char buf[] = "some text without end";
    int lineNum = 1;
    char* result = sp.ParseText(buf, ">>>", 0, &lineNum);
    // If end tag not found, should return null
    EXPECT_EQ(result, nullptr);
}

TEST_F(StrPairTest_3, ParseTextEmptyInput_3) {
    char buf[] = "";
    int lineNum = 1;
    char* result = sp.ParseText(buf, "<", 0, &lineNum);
    EXPECT_EQ(result, nullptr);
}

TEST_F(StrPairTest_3, ParseTextCountsNewlines_3) {
    char buf[] = "line1\nline2\nline3<end";
    int lineNum = 1;
    char* result = sp.ParseText(buf, "<", 0, &lineNum);
    EXPECT_NE(result, nullptr);
    EXPECT_EQ(lineNum, 3);
}

TEST_F(StrPairTest_3, ParseTextImmediateEndTag_3) {
    char buf[] = "<!end";
    int lineNum = 1;
    char* result = sp.ParseText(buf, "<!", 0, &lineNum);
    EXPECT_NE(result, nullptr);
}

// ===== GetStr after various operations =====

TEST_F(StrPairTest_3, GetStrMultipleCalls_3) {
    sp.SetInternedStr("consistent");
    EXPECT_STREQ(sp.GetStr(), "consistent");
    EXPECT_STREQ(sp.GetStr(), "consistent");
}

TEST_F(StrPairTest_3, GetStrAfterSetThenReset_3) {
    sp.SetInternedStr("temp");
    EXPECT_STREQ(sp.GetStr(), "temp");
    sp.Reset();
    EXPECT_STREQ(sp.GetStr(), "");
}

// ===== Destruction / Lifecycle =====

TEST_F(StrPairTest_3, DestructionAfterSetStr_3) {
    // Test that destruction works without crash after SetStr
    StrPair* dynamic = new StrPair();
    dynamic->SetStr("allocated", 0);
    EXPECT_NO_FATAL_FAILURE(delete dynamic);
}

TEST_F(StrPairTest_3, DestructionAfterSetInternedStr_3) {
    StrPair* dynamic = new StrPair();
    dynamic->SetInternedStr("interned");
    EXPECT_NO_FATAL_FAILURE(delete dynamic);
}

TEST_F(StrPairTest_3, DestructionDefault_3) {
    StrPair* dynamic = new StrPair();
    EXPECT_NO_FATAL_FAILURE(delete dynamic);
}
