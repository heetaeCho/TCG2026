#include "gtest/gtest.h"
#include "./TestProjects/tinyxml2/tinyxml2.h"

using namespace tinyxml2;

class StrPairTest_2 : public ::testing::Test {
protected:
    StrPair sp;
};

// ==================== Empty() Tests ====================

TEST_F(StrPairTest_2, DefaultConstructedIsEmpty_2) {
    EXPECT_TRUE(sp.Empty());
}

TEST_F(StrPairTest_2, AfterSetStrNotEmpty_2) {
    sp.SetStr("hello", 0);
    EXPECT_FALSE(sp.Empty());
}

TEST_F(StrPairTest_2, AfterResetIsEmpty_2) {
    sp.SetStr("hello", 0);
    sp.Reset();
    EXPECT_TRUE(sp.Empty());
}

TEST_F(StrPairTest_2, SetEmptyStringIsEmpty_2) {
    sp.SetStr("", 0);
    // An empty string may or may not be considered empty depending on implementation
    // We observe behavior here
    const char* result = sp.GetStr();
    EXPECT_NE(result, nullptr);
    EXPECT_STREQ(result, "");
}

// ==================== SetStr() / GetStr() Tests ====================

TEST_F(StrPairTest_2, SetStrAndGetStr_2) {
    sp.SetStr("test string", 0);
    const char* result = sp.GetStr();
    EXPECT_NE(result, nullptr);
    EXPECT_STREQ(result, "test string");
}

TEST_F(StrPairTest_2, SetStrOverwritesPrevious_2) {
    sp.SetStr("first", 0);
    sp.SetStr("second", 0);
    const char* result = sp.GetStr();
    EXPECT_STREQ(result, "second");
}

TEST_F(StrPairTest_2, GetStrOnDefaultConstructed_2) {
    const char* result = sp.GetStr();
    // Default constructed should return empty or null-like string
    EXPECT_NE(result, nullptr);
    EXPECT_STREQ(result, "");
}

TEST_F(StrPairTest_2, SetStrWithSpecialCharacters_2) {
    sp.SetStr("hello\nworld\ttab", 0);
    const char* result = sp.GetStr();
    EXPECT_STREQ(result, "hello\nworld\ttab");
}

TEST_F(StrPairTest_2, SetStrWithUnicodeContent_2) {
    sp.SetStr("café", 0);
    const char* result = sp.GetStr();
    EXPECT_STREQ(result, "café");
}

// ==================== Set() Tests ====================

TEST_F(StrPairTest_2, SetWithCharPointers_2) {
    char buffer[] = "hello world";
    sp.Set(buffer, buffer + 5, 0);
    EXPECT_FALSE(sp.Empty());
}

TEST_F(StrPairTest_2, SetWithSameStartAndEnd_2) {
    char buffer[] = "hello";
    sp.Set(buffer, buffer, 0);
    EXPECT_TRUE(sp.Empty());
}

// ==================== SetInternedStr() Tests ====================

TEST_F(StrPairTest_2, SetInternedStr_2) {
    sp.SetInternedStr("interned");
    const char* result = sp.GetStr();
    EXPECT_NE(result, nullptr);
    EXPECT_STREQ(result, "interned");
}

TEST_F(StrPairTest_2, SetInternedStrNotEmpty_2) {
    sp.SetInternedStr("interned");
    EXPECT_FALSE(sp.Empty());
}

TEST_F(StrPairTest_2, SetInternedStrEmptyString_2) {
    sp.SetInternedStr("");
    const char* result = sp.GetStr();
    EXPECT_NE(result, nullptr);
    EXPECT_STREQ(result, "");
}

// ==================== Reset() Tests ====================

TEST_F(StrPairTest_2, ResetClearsSetStr_2) {
    sp.SetStr("data", 0);
    sp.Reset();
    EXPECT_TRUE(sp.Empty());
    const char* result = sp.GetStr();
    EXPECT_STREQ(result, "");
}

TEST_F(StrPairTest_2, ResetOnDefaultConstructed_2) {
    sp.Reset();
    EXPECT_TRUE(sp.Empty());
}

TEST_F(StrPairTest_2, ResetMultipleTimes_2) {
    sp.SetStr("hello", 0);
    sp.Reset();
    sp.Reset();
    EXPECT_TRUE(sp.Empty());
}

// ==================== TransferTo() Tests ====================

TEST_F(StrPairTest_2, TransferToMovesContent_2) {
    sp.SetStr("transfer me", 0);
    StrPair destination;
    sp.TransferTo(&destination);
    
    const char* destResult = destination.GetStr();
    EXPECT_STREQ(destResult, "transfer me");
}

TEST_F(StrPairTest_2, TransferToEmptiesSource_2) {
    sp.SetStr("transfer me", 0);
    StrPair destination;
    sp.TransferTo(&destination);
    
    // Source should be reset after transfer
    EXPECT_TRUE(sp.Empty());
}

TEST_F(StrPairTest_2, TransferToFromEmpty_2) {
    StrPair destination;
    destination.SetStr("existing", 0);
    sp.TransferTo(&destination);
    
    const char* destResult = destination.GetStr();
    EXPECT_STREQ(destResult, "");
}

// ==================== ParseText() Tests ====================

TEST_F(StrPairTest_2, ParseTextFindsEndTag_2) {
    char buffer[] = "hello world</end>remaining";
    int lineNum = 1;
    char* result = sp.ParseText(buffer, "</end>", 0, &lineNum);
    EXPECT_NE(result, nullptr);
    // result should point past the end tag
}

TEST_F(StrPairTest_2, ParseTextNoEndTagReturnsNull_2) {
    char buffer[] = "hello world without end tag";
    int lineNum = 1;
    char* result = sp.ParseText(buffer, "</missing>", 0, &lineNum);
    EXPECT_EQ(result, nullptr);
}

TEST_F(StrPairTest_2, ParseTextEmptyBuffer_2) {
    char buffer[] = "";
    int lineNum = 1;
    char* result = sp.ParseText(buffer, "</end>", 0, &lineNum);
    EXPECT_EQ(result, nullptr);
}

TEST_F(StrPairTest_2, ParseTextCountsNewlines_2) {
    char buffer[] = "line1\nline2\nline3</end>after";
    int lineNum = 1;
    char* result = sp.ParseText(buffer, "</end>", 0, &lineNum);
    EXPECT_NE(result, nullptr);
    EXPECT_EQ(lineNum, 3);
}

TEST_F(StrPairTest_2, ParseTextEndTagAtBeginning_2) {
    char buffer[] = "</end>after";
    int lineNum = 1;
    char* result = sp.ParseText(buffer, "</end>", 0, &lineNum);
    EXPECT_NE(result, nullptr);
}

// ==================== ParseName() Tests ====================

TEST_F(StrPairTest_2, ParseNameValidName_2) {
    char buffer[] = "validName rest";
    char* result = sp.ParseName(buffer);
    EXPECT_NE(result, nullptr);
}

TEST_F(StrPairTest_2, ParseNameStartsWithDigit_2) {
    char buffer[] = "123invalid";
    char* result = sp.ParseName(buffer);
    // Names in XML cannot start with a digit
    EXPECT_EQ(result, nullptr);
}

TEST_F(StrPairTest_2, ParseNameEmpty_2) {
    char buffer[] = "";
    char* result = sp.ParseName(buffer);
    EXPECT_EQ(result, nullptr);
}

TEST_F(StrPairTest_2, ParseNameWithUnderscore_2) {
    char buffer[] = "_name rest";
    char* result = sp.ParseName(buffer);
    EXPECT_NE(result, nullptr);
}

TEST_F(StrPairTest_2, ParseNameWithColon_2) {
    char buffer[] = "ns:name rest";
    char* result = sp.ParseName(buffer);
    EXPECT_NE(result, nullptr);
}

TEST_F(StrPairTest_2, ParseNameStartsWithSpace_2) {
    char buffer[] = " invalid";
    char* result = sp.ParseName(buffer);
    EXPECT_EQ(result, nullptr);
}

TEST_F(StrPairTest_2, ParseNameSingleCharacter_2) {
    char buffer[] = "a";
    char* result = sp.ParseName(buffer);
    EXPECT_NE(result, nullptr);
}

// ==================== Lifecycle / Destructor Tests ====================

TEST_F(StrPairTest_2, DestructorAfterSetStr_2) {
    // Ensure no crash on destruction after SetStr
    StrPair* local = new StrPair();
    local->SetStr("allocated string", 0);
    delete local; // Should not leak or crash
}

TEST_F(StrPairTest_2, DestructorAfterDefault_2) {
    StrPair* local = new StrPair();
    delete local; // Should not crash
}

// ==================== Combination Tests ====================

TEST_F(StrPairTest_2, SetThenTransferThenSetAgain_2) {
    sp.SetStr("first", 0);
    StrPair other;
    sp.TransferTo(&other);
    sp.SetStr("second", 0);
    
    EXPECT_STREQ(sp.GetStr(), "second");
    EXPECT_STREQ(other.GetStr(), "first");
}

TEST_F(StrPairTest_2, MultipleResetAndSet_2) {
    for (int i = 0; i < 10; ++i) {
        sp.SetStr("repeated", 0);
        EXPECT_FALSE(sp.Empty());
        sp.Reset();
        EXPECT_TRUE(sp.Empty());
    }
}

TEST_F(StrPairTest_2, SetInternedThenReset_2) {
    sp.SetInternedStr("interned");
    EXPECT_FALSE(sp.Empty());
    sp.Reset();
    EXPECT_TRUE(sp.Empty());
}

TEST_F(StrPairTest_2, ParseTextThenGetStr_2) {
    char buffer[] = "content</tag>rest";
    int lineNum = 1;
    char* result = sp.ParseText(buffer, "</tag>", 0, &lineNum);
    EXPECT_NE(result, nullptr);
    
    const char* str = sp.GetStr();
    EXPECT_NE(str, nullptr);
    EXPECT_STREQ(str, "content");
}

TEST_F(StrPairTest_2, ParseNameThenGetStr_2) {
    char buffer[] = "elementName>";
    char* result = sp.ParseName(buffer);
    EXPECT_NE(result, nullptr);
    
    const char* str = sp.GetStr();
    EXPECT_NE(str, nullptr);
    EXPECT_STREQ(str, "elementName");
}

TEST_F(StrPairTest_2, SetWithNullptrNullTerminated_2) {
    // ParseText with null pointer - should handle gracefully
    char* result = sp.ParseText(nullptr, "</end>", 0, nullptr);
    EXPECT_EQ(result, nullptr);
}

TEST_F(StrPairTest_2, ParseNameNullptr_2) {
    char* result = sp.ParseName(nullptr);
    EXPECT_EQ(result, nullptr);
}

TEST_F(StrPairTest_2, LongString_2) {
    std::string longStr(10000, 'x');
    sp.SetStr(longStr.c_str(), 0);
    const char* result = sp.GetStr();
    EXPECT_STREQ(result, longStr.c_str());
}
