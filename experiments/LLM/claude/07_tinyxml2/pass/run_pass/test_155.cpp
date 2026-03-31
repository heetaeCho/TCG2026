#include <gtest/gtest.h>
#include "tinyxml2.h"

using namespace tinyxml2;

// Helper to access StrPair through its public interface
class StrPairTest_155 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test default construction results in empty StrPair
TEST_F(StrPairTest_155, DefaultConstructionIsEmpty_155) {
    StrPair sp;
    EXPECT_TRUE(sp.Empty());
}

// Test that GetStr on default-constructed StrPair returns empty or null-like string
TEST_F(StrPairTest_155, DefaultGetStrReturnsEmptyString_155) {
    StrPair sp;
    const char* result = sp.GetStr();
    EXPECT_NE(result, nullptr);
    EXPECT_STREQ(result, "");
}

// Test SetStr and GetStr round-trip
TEST_F(StrPairTest_155, SetStrAndGetStr_155) {
    StrPair sp;
    sp.SetStr("Hello, World!", 0);
    const char* result = sp.GetStr();
    EXPECT_NE(result, nullptr);
    EXPECT_STREQ(result, "Hello, World!");
}

// Test that after SetStr, Empty returns false
TEST_F(StrPairTest_155, SetStrMakesNonEmpty_155) {
    StrPair sp;
    sp.SetStr("test", 0);
    EXPECT_FALSE(sp.Empty());
}

// Test Reset clears the StrPair
TEST_F(StrPairTest_155, ResetMakesEmpty_155) {
    StrPair sp;
    sp.SetStr("some data", 0);
    EXPECT_FALSE(sp.Empty());
    sp.Reset();
    EXPECT_TRUE(sp.Empty());
}

// Test Reset then GetStr returns empty string
TEST_F(StrPairTest_155, ResetThenGetStrReturnsEmpty_155) {
    StrPair sp;
    sp.SetStr("data", 0);
    sp.Reset();
    const char* result = sp.GetStr();
    EXPECT_NE(result, nullptr);
    EXPECT_STREQ(result, "");
}

// Test TransferTo moves data from one StrPair to another
TEST_F(StrPairTest_155, TransferToMovesData_155) {
    StrPair source;
    StrPair dest;
    
    source.SetStr("transfer me", 0);
    source.TransferTo(&dest);
    
    // Source should be empty after transfer
    EXPECT_TRUE(source.Empty());
    
    // Destination should have the data
    const char* result = dest.GetStr();
    EXPECT_NE(result, nullptr);
    EXPECT_STREQ(result, "transfer me");
}

// Test TransferTo self does not crash or corrupt
TEST_F(StrPairTest_155, TransferToSelfIsNoOp_155) {
    StrPair sp;
    sp.SetStr("self transfer", 0);
    sp.TransferTo(&sp);
    
    // After self-transfer, data should still be intact
    const char* result = sp.GetStr();
    EXPECT_NE(result, nullptr);
    EXPECT_STREQ(result, "self transfer");
}

// Test TransferTo with source being empty
TEST_F(StrPairTest_155, TransferToFromEmptySource_155) {
    StrPair source;
    StrPair dest;
    
    source.TransferTo(&dest);
    
    EXPECT_TRUE(source.Empty());
    EXPECT_TRUE(dest.Empty());
}

// Test Set with explicit start, end, and flags
TEST_F(StrPairTest_155, SetWithStartAndEnd_155) {
    char buffer[] = "Hello World";
    StrPair sp;
    sp.Set(buffer, buffer + 5, 0);
    
    EXPECT_FALSE(sp.Empty());
    const char* result = sp.GetStr();
    EXPECT_NE(result, nullptr);
    EXPECT_STREQ(result, "Hello");
}

// Test SetInternedStr
TEST_F(StrPairTest_155, SetInternedStr_155) {
    StrPair sp;
    sp.SetInternedStr("interned");
    
    EXPECT_FALSE(sp.Empty());
    const char* result = sp.GetStr();
    EXPECT_NE(result, nullptr);
    EXPECT_STREQ(result, "interned");
}

// Test SetStr with empty string
TEST_F(StrPairTest_155, SetStrWithEmptyString_155) {
    StrPair sp;
    sp.SetStr("", 0);
    const char* result = sp.GetStr();
    EXPECT_NE(result, nullptr);
    EXPECT_STREQ(result, "");
}

// Test ParseText with a simple end tag
TEST_F(StrPairTest_155, ParseTextFindsEndTag_155) {
    char buffer[] = "some text<!-- end here";
    StrPair sp;
    int lineNum = 1;
    char* result = sp.ParseText(buffer, "<!--", 0, &lineNum);
    
    if (result != nullptr) {
        // ParseText found the end tag
        const char* str = sp.GetStr();
        EXPECT_NE(str, nullptr);
    }
}

// Test ParseText when end tag is not found
TEST_F(StrPairTest_155, ParseTextEndTagNotFound_155) {
    char buffer[] = "some text without end tag";
    StrPair sp;
    int lineNum = 1;
    char* result = sp.ParseText(buffer, "<!--", 0, &lineNum);
    
    // When end tag is not found, should return null
    EXPECT_EQ(result, nullptr);
}

// Test ParseName with a valid name
TEST_F(StrPairTest_155, ParseNameValidName_155) {
    char buffer[] = "validName ";
    StrPair sp;
    char* result = sp.ParseName(buffer);
    
    EXPECT_NE(result, nullptr);
    const char* str = sp.GetStr();
    EXPECT_NE(str, nullptr);
    EXPECT_STREQ(str, "validName");
}

// Test ParseName with invalid start character
TEST_F(StrPairTest_155, ParseNameInvalidStartChar_155) {
    char buffer[] = "123invalid";
    StrPair sp;
    char* result = sp.ParseName(buffer);
    
    // Names cannot start with digits in XML
    EXPECT_EQ(result, nullptr);
}

// Test ParseName with empty buffer
TEST_F(StrPairTest_155, ParseNameEmptyBuffer_155) {
    char buffer[] = "";
    StrPair sp;
    char* result = sp.ParseName(buffer);
    
    EXPECT_EQ(result, nullptr);
}

// Test multiple SetStr calls (overwrite)
TEST_F(StrPairTest_155, MultipleSetStrOverwrites_155) {
    StrPair sp;
    sp.SetStr("first", 0);
    EXPECT_STREQ(sp.GetStr(), "first");
    
    sp.SetStr("second", 0);
    EXPECT_STREQ(sp.GetStr(), "second");
}

// Test Set with zero-length range
TEST_F(StrPairTest_155, SetWithZeroLengthRange_155) {
    char buffer[] = "Hello";
    StrPair sp;
    sp.Set(buffer, buffer, 0);
    
    const char* result = sp.GetStr();
    EXPECT_NE(result, nullptr);
    EXPECT_STREQ(result, "");
}

// Test ParseText with newlines increments line number
TEST_F(StrPairTest_155, ParseTextWithNewlinesIncrementsLineNum_155) {
    char buffer[] = "line1\nline2\nline3<!--end";
    StrPair sp;
    int lineNum = 1;
    char* result = sp.ParseText(buffer, "<!--", 0, &lineNum);
    
    if (result != nullptr) {
        // Line number should have been incremented for each newline
        EXPECT_GT(lineNum, 1);
    }
}

// Test TransferTo followed by operations on destination
TEST_F(StrPairTest_155, TransferToThenUseDestination_155) {
    StrPair source;
    StrPair dest;
    
    source.SetStr("transferred data", 0);
    source.TransferTo(&dest);
    
    // Verify source is empty
    EXPECT_STREQ(source.GetStr(), "");
    
    // Verify dest has the data
    EXPECT_STREQ(dest.GetStr(), "transferred data");
    
    // Reset dest
    dest.Reset();
    EXPECT_TRUE(dest.Empty());
}

// Test SetInternedStr with empty string
TEST_F(StrPairTest_155, SetInternedStrEmpty_155) {
    StrPair sp;
    sp.SetInternedStr("");
    
    const char* result = sp.GetStr();
    EXPECT_NE(result, nullptr);
    EXPECT_STREQ(result, "");
}

// Test ParseName with XML-valid name characters
TEST_F(StrPairTest_155, ParseNameWithColonAndDash_155) {
    char buffer[] = "ns:element-name>";
    StrPair sp;
    char* result = sp.ParseName(buffer);
    
    if (result != nullptr) {
        const char* str = sp.GetStr();
        EXPECT_NE(str, nullptr);
        // Should parse up to non-name character
    }
}

// Test ParseName with underscore start
TEST_F(StrPairTest_155, ParseNameStartsWithUnderscore_155) {
    char buffer[] = "_privateName ";
    StrPair sp;
    char* result = sp.ParseName(buffer);
    
    EXPECT_NE(result, nullptr);
    const char* str = sp.GetStr();
    EXPECT_STREQ(str, "_privateName");
}

// Test destruction after SetStr (no memory leak / crash)
TEST_F(StrPairTest_155, DestructionAfterSetStr_155) {
    StrPair* sp = new StrPair();
    sp->SetStr("allocated string", 0);
    // Should not crash on delete
    delete sp;
}

// Test destruction after TransferTo (no crash)
TEST_F(StrPairTest_155, DestructionAfterTransferTo_155) {
    StrPair* source = new StrPair();
    StrPair* dest = new StrPair();
    source->SetStr("to be transferred", 0);
    source->TransferTo(dest);
    delete source;
    
    EXPECT_STREQ(dest->GetStr(), "to be transferred");
    delete dest;
}
