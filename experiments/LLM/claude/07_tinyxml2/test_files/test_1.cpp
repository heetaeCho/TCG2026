#include "gtest/gtest.h"
#include "tinyxml2.h"

using namespace tinyxml2;

class StrPairTest_1 : public ::testing::Test {
protected:
    StrPair sp;
};

// ============================================================
// Tests for Default Construction
// ============================================================

TEST_F(StrPairTest_1, DefaultConstructionIsEmpty_1) {
    EXPECT_TRUE(sp.Empty());
}

TEST_F(StrPairTest_1, DefaultConstructionGetStrReturnsEmpty_1) {
    const char* result = sp.GetStr();
    EXPECT_STREQ(result, "");
}

// ============================================================
// Tests for Set()
// ============================================================

TEST_F(StrPairTest_1, SetMakesNonEmpty_1) {
    char buf[] = "Hello";
    sp.Set(buf, buf + 5, 0);
    EXPECT_FALSE(sp.Empty());
}

TEST_F(StrPairTest_1, SetAndGetStr_1) {
    char buf[] = "Hello";
    sp.Set(buf, buf + 5, 0);
    const char* result = sp.GetStr();
    EXPECT_STREQ(result, "Hello");
}

TEST_F(StrPairTest_1, SetWithZeroLengthRange_1) {
    char buf[] = "Hello";
    sp.Set(buf, buf, 0);
    const char* result = sp.GetStr();
    EXPECT_STREQ(result, "");
}

TEST_F(StrPairTest_1, SetOverwritesPreviousSet_1) {
    char buf1[] = "First";
    sp.Set(buf1, buf1 + 5, 0);
    EXPECT_STREQ(sp.GetStr(), "First");

    char buf2[] = "Second";
    sp.Set(buf2, buf2 + 6, 0);
    EXPECT_STREQ(sp.GetStr(), "Second");
}

TEST_F(StrPairTest_1, SetPartialString_1) {
    char buf[] = "Hello World";
    sp.Set(buf, buf + 5, 0);
    const char* result = sp.GetStr();
    EXPECT_STREQ(result, "Hello");
}

// ============================================================
// Tests for SetStr()
// ============================================================

TEST_F(StrPairTest_1, SetStrBasic_1) {
    sp.SetStr("TestString", 0);
    const char* result = sp.GetStr();
    EXPECT_STREQ(result, "TestString");
}

TEST_F(StrPairTest_1, SetStrMakesNonEmpty_1) {
    sp.SetStr("Something", 0);
    EXPECT_FALSE(sp.Empty());
}

TEST_F(StrPairTest_1, SetStrEmptyString_1) {
    sp.SetStr("", 0);
    const char* result = sp.GetStr();
    EXPECT_STREQ(result, "");
}

TEST_F(StrPairTest_1, SetStrOverwritesPrevious_1) {
    sp.SetStr("First", 0);
    EXPECT_STREQ(sp.GetStr(), "First");
    sp.SetStr("Second", 0);
    EXPECT_STREQ(sp.GetStr(), "Second");
}

// ============================================================
// Tests for SetInternedStr()
// ============================================================

TEST_F(StrPairTest_1, SetInternedStrBasic_1) {
    sp.SetInternedStr("Interned");
    const char* result = sp.GetStr();
    EXPECT_STREQ(result, "Interned");
}

TEST_F(StrPairTest_1, SetInternedStrMakesNonEmpty_1) {
    sp.SetInternedStr("NotEmpty");
    EXPECT_FALSE(sp.Empty());
}

TEST_F(StrPairTest_1, SetInternedStrEmptyString_1) {
    sp.SetInternedStr("");
    const char* result = sp.GetStr();
    EXPECT_STREQ(result, "");
}

// ============================================================
// Tests for Reset()
// ============================================================

TEST_F(StrPairTest_1, ResetMakesEmpty_1) {
    sp.SetStr("Something", 0);
    EXPECT_FALSE(sp.Empty());
    sp.Reset();
    EXPECT_TRUE(sp.Empty());
}

TEST_F(StrPairTest_1, ResetOnDefaultIsOk_1) {
    sp.Reset();
    EXPECT_TRUE(sp.Empty());
}

TEST_F(StrPairTest_1, ResetAfterSetMakesGetStrReturnEmpty_1) {
    char buf[] = "Hello";
    sp.Set(buf, buf + 5, 0);
    sp.Reset();
    const char* result = sp.GetStr();
    EXPECT_STREQ(result, "");
}

// ============================================================
// Tests for Empty()
// ============================================================

TEST_F(StrPairTest_1, EmptyOnDefault_1) {
    EXPECT_TRUE(sp.Empty());
}

TEST_F(StrPairTest_1, EmptyAfterSet_1) {
    char buf[] = "X";
    sp.Set(buf, buf + 1, 0);
    EXPECT_FALSE(sp.Empty());
}

TEST_F(StrPairTest_1, EmptyAfterSetStr_1) {
    sp.SetStr("X", 0);
    EXPECT_FALSE(sp.Empty());
}

TEST_F(StrPairTest_1, EmptyAfterReset_1) {
    sp.SetStr("X", 0);
    sp.Reset();
    EXPECT_TRUE(sp.Empty());
}

// ============================================================
// Tests for TransferTo()
// ============================================================

TEST_F(StrPairTest_1, TransferToMovesContent_1) {
    sp.SetStr("Transfer", 0);
    StrPair target;
    sp.TransferTo(&target);
    EXPECT_STREQ(target.GetStr(), "Transfer");
}

TEST_F(StrPairTest_1, TransferToMakesSourceEmpty_1) {
    sp.SetStr("Transfer", 0);
    StrPair target;
    sp.TransferTo(&target);
    EXPECT_TRUE(sp.Empty());
}

TEST_F(StrPairTest_1, TransferToEmptySource_1) {
    StrPair target;
    target.SetStr("Existing", 0);
    sp.TransferTo(&target);
    // Source was empty, so target should now be empty too
    EXPECT_TRUE(target.Empty() || strlen(target.GetStr()) == 0);
}

TEST_F(StrPairTest_1, TransferToWithSetData_1) {
    char buf[] = "SetData";
    sp.Set(buf, buf + 7, 0);
    StrPair target;
    sp.TransferTo(&target);
    EXPECT_STREQ(target.GetStr(), "SetData");
    EXPECT_TRUE(sp.Empty());
}

// ============================================================
// Tests for ParseText()
// ============================================================

TEST_F(StrPairTest_1, ParseTextFindsEndTag_1) {
    char buf[] = "Hello<end>rest";
    int lineNum = 1;
    char* result = sp.ParseText(buf, "<end>", 0, &lineNum);
    EXPECT_NE(result, nullptr);
    EXPECT_STREQ(sp.GetStr(), "Hello");
}

TEST_F(StrPairTest_1, ParseTextNoEndTag_1) {
    char buf[] = "Hello there is no end";
    int lineNum = 1;
    char* result = sp.ParseText(buf, "<missing>", 0, &lineNum);
    EXPECT_EQ(result, nullptr);
}

TEST_F(StrPairTest_1, ParseTextEmptyInput_1) {
    char buf[] = "<end>";
    int lineNum = 1;
    char* result = sp.ParseText(buf, "<end>", 0, &lineNum);
    EXPECT_NE(result, nullptr);
    EXPECT_STREQ(sp.GetStr(), "");
}

TEST_F(StrPairTest_1, ParseTextCountsNewlines_1) {
    char buf[] = "line1\nline2\nline3<end>rest";
    int lineNum = 1;
    char* result = sp.ParseText(buf, "<end>", 0, &lineNum);
    EXPECT_NE(result, nullptr);
    EXPECT_EQ(lineNum, 3);
}

// ============================================================
// Tests for ParseName()
// ============================================================

TEST_F(StrPairTest_1, ParseNameBasic_1) {
    char buf[] = "elementName rest";
    char* result = sp.ParseName(buf);
    EXPECT_NE(result, nullptr);
    EXPECT_STREQ(sp.GetStr(), "elementName");
}

TEST_F(StrPairTest_1, ParseNameStartsWithNumber_1) {
    char buf[] = "123invalid";
    char* result = sp.ParseName(buf);
    EXPECT_EQ(result, nullptr);
}

TEST_F(StrPairTest_1, ParseNameEmptyInput_1) {
    char buf[] = "";
    char* result = sp.ParseName(buf);
    EXPECT_EQ(result, nullptr);
}

TEST_F(StrPairTest_1, ParseNameWithUnderscore_1) {
    char buf[] = "_validName rest";
    char* result = sp.ParseName(buf);
    EXPECT_NE(result, nullptr);
    EXPECT_STREQ(sp.GetStr(), "_validName");
}

TEST_F(StrPairTest_1, ParseNameWithColon_1) {
    char buf[] = "ns:name rest";
    char* result = sp.ParseName(buf);
    EXPECT_NE(result, nullptr);
    EXPECT_STREQ(sp.GetStr(), "ns:name");
}

TEST_F(StrPairTest_1, ParseNameStopsAtSpecialChar_1) {
    char buf[] = "name=value";
    char* result = sp.ParseName(buf);
    EXPECT_NE(result, nullptr);
    EXPECT_STREQ(sp.GetStr(), "name");
    EXPECT_EQ(*result, '=');
}

// ============================================================
// Tests for GetStr() consistency
// ============================================================

TEST_F(StrPairTest_1, GetStrCalledMultipleTimes_1) {
    sp.SetStr("Consistent", 0);
    const char* r1 = sp.GetStr();
    const char* r2 = sp.GetStr();
    EXPECT_STREQ(r1, "Consistent");
    EXPECT_STREQ(r2, "Consistent");
}

TEST_F(StrPairTest_1, GetStrAfterSetCalledMultipleTimes_1) {
    char buf[] = "Consistent";
    sp.Set(buf, buf + 10, 0);
    const char* r1 = sp.GetStr();
    const char* r2 = sp.GetStr();
    EXPECT_STREQ(r1, r2);
}
