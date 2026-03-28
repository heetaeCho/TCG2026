#include "gtest/gtest.h"
#include "tinyxml2.h"

using namespace tinyxml2;

// Helper to access StrPair through XMLDocument since StrPair might not be fully
// constructible standalone in all configurations. However, based on the interface,
// StrPair has a public default constructor, so we test it directly.

class StrPairTest_156 : public ::testing::Test {
protected:
    StrPair sp;
};

// Test that a freshly constructed StrPair is empty
TEST_F(StrPairTest_156, DefaultConstructorIsEmpty_156) {
    EXPECT_TRUE(sp.Empty());
}

// Test that GetStr on a default StrPair returns empty or null string
TEST_F(StrPairTest_156, DefaultGetStrReturnsEmptyOrNull_156) {
    const char* str = sp.GetStr();
    // Should return either nullptr or an empty string
    if (str != nullptr) {
        EXPECT_STREQ(str, "");
    }
}

// Test Reset on a default (empty) StrPair doesn't crash
TEST_F(StrPairTest_156, ResetOnDefaultDoesNotCrash_156) {
    sp.Reset();
    EXPECT_TRUE(sp.Empty());
}

// Test SetStr sets a string that can be retrieved with GetStr
TEST_F(StrPairTest_156, SetStrAndGetStr_156) {
    sp.SetStr("hello", 0);
    EXPECT_FALSE(sp.Empty());
    const char* result = sp.GetStr();
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "hello");
}

// Test SetStr with empty string
TEST_F(StrPairTest_156, SetStrEmptyString_156) {
    sp.SetStr("", 0);
    const char* result = sp.GetStr();
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "");
}

// Test Reset after SetStr clears the string
TEST_F(StrPairTest_156, ResetAfterSetStrClearsString_156) {
    sp.SetStr("world", 0);
    EXPECT_FALSE(sp.Empty());
    sp.Reset();
    EXPECT_TRUE(sp.Empty());
}

// Test that after Reset, GetStr returns empty or null
TEST_F(StrPairTest_156, GetStrAfterResetReturnsEmpty_156) {
    sp.SetStr("test", 0);
    sp.Reset();
    const char* result = sp.GetStr();
    if (result != nullptr) {
        EXPECT_STREQ(result, "");
    }
}

// Test SetStr can be called multiple times
TEST_F(StrPairTest_156, SetStrMultipleTimes_156) {
    sp.SetStr("first", 0);
    const char* r1 = sp.GetStr();
    ASSERT_NE(r1, nullptr);
    EXPECT_STREQ(r1, "first");

    sp.SetStr("second", 0);
    const char* r2 = sp.GetStr();
    ASSERT_NE(r2, nullptr);
    EXPECT_STREQ(r2, "second");
}

// Test Set with start and end pointers
TEST_F(StrPairTest_156, SetWithStartAndEnd_156) {
    char buffer[] = "hello world";
    sp.Set(buffer, buffer + 5, 0);
    EXPECT_FALSE(sp.Empty());
    const char* result = sp.GetStr();
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "hello");
}

// Test Set with empty range
TEST_F(StrPairTest_156, SetWithEmptyRange_156) {
    char buffer[] = "test";
    sp.Set(buffer, buffer, 0);
    const char* result = sp.GetStr();
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "");
}

// Test SetInternedStr
TEST_F(StrPairTest_156, SetInternedStr_156) {
    sp.SetInternedStr("interned");
    EXPECT_FALSE(sp.Empty());
    const char* result = sp.GetStr();
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "interned");
}

// Test SetInternedStr with empty string
TEST_F(StrPairTest_156, SetInternedStrEmpty_156) {
    sp.SetInternedStr("");
    const char* result = sp.GetStr();
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "");
}

// Test TransferTo moves data to another StrPair
TEST_F(StrPairTest_156, TransferToMovesData_156) {
    sp.SetStr("transfer_me", 0);
    StrPair target;
    sp.TransferTo(&target);
    
    // After transfer, source should be empty
    EXPECT_TRUE(sp.Empty());
    
    // Target should have the string
    const char* result = target.GetStr();
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "transfer_me");
}

// Test TransferTo with empty source
TEST_F(StrPairTest_156, TransferToFromEmpty_156) {
    StrPair target;
    target.SetStr("existing", 0);
    sp.TransferTo(&target);
    
    EXPECT_TRUE(sp.Empty());
    // target should now be reset/empty since source was empty
    EXPECT_TRUE(target.Empty());
}

// Test ParseText with a simple end tag
TEST_F(StrPairTest_156, ParseTextSimple_156) {
    char buffer[] = "some text<end";
    int lineNum = 1;
    char* result = sp.ParseText(buffer, "<end", 0, &lineNum);
    
    if (result != nullptr) {
        const char* str = sp.GetStr();
        ASSERT_NE(str, nullptr);
        EXPECT_STREQ(str, "some text");
    }
}

// Test ParseText with no matching end tag returns null
TEST_F(StrPairTest_156, ParseTextNoEndTag_156) {
    char buffer[] = "some text without end";
    int lineNum = 1;
    char* result = sp.ParseText(buffer, "<notfound>", 0, &lineNum);
    
    EXPECT_EQ(result, nullptr);
}

// Test ParseText with empty input
TEST_F(StrPairTest_156, ParseTextEmptyInput_156) {
    char buffer[] = "";
    int lineNum = 1;
    char* result = sp.ParseText(buffer, "end", 0, &lineNum);
    
    EXPECT_EQ(result, nullptr);
}

// Test ParseText with immediate end tag
TEST_F(StrPairTest_156, ParseTextImmediateEndTag_156) {
    char buffer[] = "-->rest";
    int lineNum = 1;
    char* result = sp.ParseText(buffer, "-->", 0, &lineNum);
    
    ASSERT_NE(result, nullptr);
    const char* str = sp.GetStr();
    ASSERT_NE(str, nullptr);
    EXPECT_STREQ(str, "");
}

// Test ParseText tracks line numbers through newlines
TEST_F(StrPairTest_156, ParseTextTracksLineNumbers_156) {
    char buffer[] = "line1\nline2\nline3-->after";
    int lineNum = 1;
    char* result = sp.ParseText(buffer, "-->", 0, &lineNum);
    
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(lineNum, 3);
}

// Test ParseName with a valid name
TEST_F(StrPairTest_156, ParseNameValid_156) {
    char buffer[] = "myName rest";
    char* result = sp.ParseName(buffer);
    
    ASSERT_NE(result, nullptr);
    const char* str = sp.GetStr();
    ASSERT_NE(str, nullptr);
    EXPECT_STREQ(str, "myName");
}

// Test ParseName with empty input
TEST_F(StrPairTest_156, ParseNameEmpty_156) {
    char buffer[] = "";
    char* result = sp.ParseName(buffer);
    
    EXPECT_EQ(result, nullptr);
}

// Test ParseName with invalid starting character (digit)
TEST_F(StrPairTest_156, ParseNameInvalidStart_156) {
    char buffer[] = "123abc";
    char* result = sp.ParseName(buffer);
    
    EXPECT_EQ(result, nullptr);
}

// Test ParseName with name containing colon and underscore
TEST_F(StrPairTest_156, ParseNameWithSpecialChars_156) {
    char buffer[] = "_my:name>";
    char* result = sp.ParseName(buffer);
    
    ASSERT_NE(result, nullptr);
    const char* str = sp.GetStr();
    ASSERT_NE(str, nullptr);
    EXPECT_STREQ(str, "_my:name");
}

// Test ParseName with single character name
TEST_F(StrPairTest_156, ParseNameSingleChar_156) {
    char buffer[] = "a ";
    char* result = sp.ParseName(buffer);
    
    ASSERT_NE(result, nullptr);
    const char* str = sp.GetStr();
    ASSERT_NE(str, nullptr);
    EXPECT_STREQ(str, "a");
}

// Test multiple Reset calls don't cause issues
TEST_F(StrPairTest_156, MultipleResets_156) {
    sp.SetStr("test", 0);
    sp.Reset();
    sp.Reset();
    sp.Reset();
    EXPECT_TRUE(sp.Empty());
}

// Test SetStr with long string
TEST_F(StrPairTest_156, SetStrLongString_156) {
    std::string longStr(10000, 'x');
    sp.SetStr(longStr.c_str(), 0);
    const char* result = sp.GetStr();
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, longStr.c_str());
}

// Test Set followed by Reset
TEST_F(StrPairTest_156, SetThenReset_156) {
    char buffer[] = "hello world";
    sp.Set(buffer, buffer + 5, 0);
    EXPECT_FALSE(sp.Empty());
    sp.Reset();
    EXPECT_TRUE(sp.Empty());
}

// Test TransferTo followed by SetStr on source
TEST_F(StrPairTest_156, TransferToThenReuse_156) {
    sp.SetStr("original", 0);
    StrPair target;
    sp.TransferTo(&target);
    
    sp.SetStr("new_value", 0);
    const char* srcStr = sp.GetStr();
    ASSERT_NE(srcStr, nullptr);
    EXPECT_STREQ(srcStr, "new_value");
    
    const char* tgtStr = target.GetStr();
    ASSERT_NE(tgtStr, nullptr);
    EXPECT_STREQ(tgtStr, "original");
}

// Test ParseName with null input
TEST_F(StrPairTest_156, ParseNameNull_156) {
    char* result = sp.ParseName(nullptr);
    EXPECT_EQ(result, nullptr);
}

// Test ParseText with null input
TEST_F(StrPairTest_156, ParseTextNull_156) {
    int lineNum = 1;
    char* result = sp.ParseText(nullptr, "end", 0, &lineNum);
    EXPECT_EQ(result, nullptr);
}

// Test SetStr with NEEDS_DELETE flag and then Reset (ensures no memory leak/crash)
TEST_F(StrPairTest_156, SetStrWithNeedsDeleteFlag_156) {
    sp.SetStr("allocated_string", 512); // NEEDS_DELETE = 512
    const char* result = sp.GetStr();
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "allocated_string");
    sp.Reset();
    EXPECT_TRUE(sp.Empty());
}

// Test Empty on a StrPair that had SetInternedStr then Reset
TEST_F(StrPairTest_156, EmptyAfterInternedAndReset_156) {
    sp.SetInternedStr("interned_value");
    EXPECT_FALSE(sp.Empty());
    sp.Reset();
    EXPECT_TRUE(sp.Empty());
}
