// File: ./TestProjects/tinyxml2/test_xmlprinter_clearbuffer_150.cpp

#include <gtest/gtest.h>

#include <cstring>
#include <string>

#include "tinyxml2.h"

namespace tinyxml2 {

class XMLPrinterClearBufferTest_150 : public ::testing::Test {
protected:
    static EscapeAposCharsInAttributes DefaultAposMode() {
        // The enum values are not provided here; use a safe default value without
        // inferring internal behavior.
        return static_cast<EscapeAposCharsInAttributes>(0);
    }

    static XMLPrinter MakePrinter(bool compact = false, int depth = 0) {
        return XMLPrinter(/*file=*/nullptr, compact, depth, DefaultAposMode());
    }

    static std::string Str(const XMLPrinter& p) {
        const char* s = p.CStr();
        return s ? std::string(s) : std::string();
    }

    static size_t SafeStrLen(const XMLPrinter& p) {
        const char* s = p.CStr();
        return s ? std::strlen(s) : 0u;
    }

    static void WriteSimpleElement(XMLPrinter& p,
                                   const char* name,
                                   const char* text,
                                   bool compactMode = false) {
        p.OpenElement(name, compactMode);
        p.PushText(text, /*cdata=*/false);
        p.CloseElement(compactMode);
    }
};

TEST_F(XMLPrinterClearBufferTest_150, ClearsExistingContent_Default_150) {
    XMLPrinter p = MakePrinter(/*compact=*/false, /*depth=*/0);

    WriteSimpleElement(p, "root", "hello", /*compactMode=*/false);
    ASSERT_NE(p.CStr(), nullptr);
    EXPECT_GT(SafeStrLen(p), 0u);

    p.ClearBuffer();  // default: resetToFirstElement = true

    ASSERT_NE(p.CStr(), nullptr);
    EXPECT_EQ(p.CStr()[0], '\0');
    EXPECT_EQ(SafeStrLen(p), 0u);

    const size_t sz = p.CStrSize();
    const size_t len = SafeStrLen(p);
    EXPECT_TRUE(sz == len || sz == (len + 1));
}

TEST_F(XMLPrinterClearBufferTest_150, ClearsExistingContent_ResetToFirstElementFalse_150) {
    XMLPrinter p = MakePrinter(/*compact=*/false, /*depth=*/0);

    WriteSimpleElement(p, "root", "hello", /*compactMode=*/false);
    ASSERT_NE(p.CStr(), nullptr);
    EXPECT_GT(SafeStrLen(p), 0u);

    p.ClearBuffer(/*resetToFirstElement=*/false);

    ASSERT_NE(p.CStr(), nullptr);
    EXPECT_EQ(p.CStr()[0], '\0');
    EXPECT_EQ(SafeStrLen(p), 0u);

    const size_t sz = p.CStrSize();
    const size_t len = SafeStrLen(p);
    EXPECT_TRUE(sz == len || sz == (len + 1));
}

TEST_F(XMLPrinterClearBufferTest_150, AfterClearBuffer_CanWriteAgainAndOldContentNotPresent_150) {
    XMLPrinter p = MakePrinter(/*compact=*/false, /*depth=*/0);

    WriteSimpleElement(p, "first", "aaa", /*compactMode=*/false);
    const std::string before = Str(p);
    ASSERT_FALSE(before.empty());
    ASSERT_NE(before.find("first"), std::string::npos);

    p.ClearBuffer();
    EXPECT_EQ(SafeStrLen(p), 0u);

    WriteSimpleElement(p, "second", "bbb", /*compactMode=*/false);
    const std::string after = Str(p);

    EXPECT_FALSE(after.empty());
    EXPECT_NE(after.find("second"), std::string::npos);
    EXPECT_EQ(after.find("first"), std::string::npos) << "Old element name should not remain after ClearBuffer().";
}

TEST_F(XMLPrinterClearBufferTest_150, DefaultResetProducesSameOutputAsFreshPrinter_ForSameSubsequentWrites_150) {
    XMLPrinter p1 = MakePrinter(/*compact=*/false, /*depth=*/0);
    XMLPrinter p2 = MakePrinter(/*compact=*/false, /*depth=*/0);

    // Put some content into p1, then clear it.
    WriteSimpleElement(p1, "old", "data", /*compactMode=*/false);
    ASSERT_GT(SafeStrLen(p1), 0u);

    p1.ClearBuffer();  // resetToFirstElement = true

    // Now do the same writes on both p1 (post-clear) and p2 (fresh).
    WriteSimpleElement(p1, "root", "hello", /*compactMode=*/false);
    WriteSimpleElement(p2, "root", "hello", /*compactMode=*/false);

    EXPECT_EQ(Str(p1), Str(p2));
}

TEST_F(XMLPrinterClearBufferTest_150, ClearBuffer_IsIdempotentAcrossMultipleCalls_150) {
    XMLPrinter p = MakePrinter(/*compact=*/false, /*depth=*/0);

    WriteSimpleElement(p, "root", "hello", /*compactMode=*/false);
    ASSERT_GT(SafeStrLen(p), 0u);

    p.ClearBuffer();
    ASSERT_EQ(SafeStrLen(p), 0u);

    p.ClearBuffer();                 // again
    p.ClearBuffer(false);            // again with false
    p.ClearBuffer(true);             // explicitly true
    EXPECT_EQ(SafeStrLen(p), 0u);
    ASSERT_NE(p.CStr(), nullptr);
    EXPECT_EQ(p.CStr()[0], '\0');
}

}  // namespace tinyxml2
