#include "gtest/gtest.h"
#include "tinyxml2.h"

using namespace tinyxml2;

// Test fixture for XMLPrinter ClearBuffer tests
class XMLPrinterClearBufferTest_150 : public ::testing::Test {
protected:
    void SetUp() override {
    }
    void TearDown() override {
    }
};

// Test that ClearBuffer on a fresh printer results in an empty CStr
TEST_F(XMLPrinterClearBufferTest_150, ClearBufferOnFreshPrinter_150) {
    XMLPrinter printer(nullptr, false, 0);
    printer.ClearBuffer();
    const char* result = printer.CStr();
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "");
}

// Test that ClearBuffer clears content after writing elements
TEST_F(XMLPrinterClearBufferTest_150, ClearBufferAfterContent_150) {
    XMLPrinter printer(nullptr, false, 0);
    printer.OpenElement("root");
    printer.CloseElement();
    
    // Verify there is content before clearing
    EXPECT_GT(printer.CStrSize(), 1u);
    
    printer.ClearBuffer();
    const char* result = printer.CStr();
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "");
}

// Test that ClearBuffer with default parameter resets firstElement so next element has no leading newline
TEST_F(XMLPrinterClearBufferTest_150, ClearBufferResetsFirstElement_150) {
    XMLPrinter printer(nullptr, false, 0);
    printer.OpenElement("first");
    printer.CloseElement();
    
    printer.ClearBuffer();
    
    // After clearing with resetToFirstElement=true (default), the next element should behave as first
    printer.OpenElement("second");
    printer.CloseElement();
    
    const char* result = printer.CStr();
    ASSERT_NE(result, nullptr);
    // The first element should not have a leading newline
    EXPECT_NE(result[0], '\n');
}

// Test that ClearBuffer(false) does not reset firstElement flag
TEST_F(XMLPrinterClearBufferTest_150, ClearBufferWithoutResetFirstElement_150) {
    XMLPrinter printer(nullptr, false, 0);
    printer.OpenElement("first");
    printer.CloseElement();
    
    // Clear but do NOT reset firstElement
    printer.ClearBuffer(false);
    
    const char* result = printer.CStr();
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "");
}

// Test that ClearBuffer results in CStrSize of 1 (just the null terminator)
TEST_F(XMLPrinterClearBufferTest_150, ClearBufferCStrSizeIsOne_150) {
    XMLPrinter printer(nullptr, false, 0);
    printer.OpenElement("test");
    printer.PushAttribute("attr", "value");
    printer.CloseElement();
    
    printer.ClearBuffer();
    // CStrSize includes the null terminator
    EXPECT_EQ(printer.CStrSize(), 1u);
}

// Test that after ClearBuffer, new content can be written successfully
TEST_F(XMLPrinterClearBufferTest_150, ClearBufferThenWriteNewContent_150) {
    XMLPrinter printer(nullptr, true, 0);
    printer.OpenElement("old");
    printer.PushText("old text");
    printer.CloseElement();
    
    printer.ClearBuffer();
    
    printer.OpenElement("new");
    printer.PushText("new text");
    printer.CloseElement();
    
    const char* result = printer.CStr();
    ASSERT_NE(result, nullptr);
    // Should contain the new content, not the old
    EXPECT_STRNE(result, "");
    EXPECT_NE(strstr(result, "new"), nullptr);
    EXPECT_EQ(strstr(result, "old"), nullptr);
}

// Test ClearBuffer multiple times in succession
TEST_F(XMLPrinterClearBufferTest_150, ClearBufferMultipleTimes_150) {
    XMLPrinter printer(nullptr, false, 0);
    printer.OpenElement("a");
    printer.CloseElement();
    printer.ClearBuffer();
    
    printer.OpenElement("b");
    printer.CloseElement();
    printer.ClearBuffer();
    
    printer.OpenElement("c");
    printer.CloseElement();
    printer.ClearBuffer();
    
    EXPECT_STREQ(printer.CStr(), "");
    EXPECT_EQ(printer.CStrSize(), 1u);
}

// Test ClearBuffer after PushHeader
TEST_F(XMLPrinterClearBufferTest_150, ClearBufferAfterPushHeader_150) {
    XMLPrinter printer(nullptr, false, 0);
    printer.PushHeader(true, true);
    
    EXPECT_GT(printer.CStrSize(), 1u);
    
    printer.ClearBuffer();
    EXPECT_STREQ(printer.CStr(), "");
    EXPECT_EQ(printer.CStrSize(), 1u);
}

// Test ClearBuffer after PushComment
TEST_F(XMLPrinterClearBufferTest_150, ClearBufferAfterPushComment_150) {
    XMLPrinter printer(nullptr, false, 0);
    printer.PushComment("This is a comment");
    
    EXPECT_GT(printer.CStrSize(), 1u);
    
    printer.ClearBuffer();
    EXPECT_STREQ(printer.CStr(), "");
}

// Test ClearBuffer after PushDeclaration
TEST_F(XMLPrinterClearBufferTest_150, ClearBufferAfterPushDeclaration_150) {
    XMLPrinter printer(nullptr, false, 0);
    printer.PushDeclaration("xml version=\"1.0\"");
    
    EXPECT_GT(printer.CStrSize(), 1u);
    
    printer.ClearBuffer();
    EXPECT_STREQ(printer.CStr(), "");
}

// Test ClearBuffer after PushUnknown
TEST_F(XMLPrinterClearBufferTest_150, ClearBufferAfterPushUnknown_150) {
    XMLPrinter printer(nullptr, false, 0);
    printer.PushUnknown("DOCTYPE html");
    
    EXPECT_GT(printer.CStrSize(), 1u);
    
    printer.ClearBuffer();
    EXPECT_STREQ(printer.CStr(), "");
}

// Test that ClearBuffer in compact mode works
TEST_F(XMLPrinterClearBufferTest_150, ClearBufferCompactMode_150) {
    XMLPrinter printer(nullptr, true, 0);
    printer.OpenElement("root");
    printer.PushText(42);
    printer.CloseElement();
    
    printer.ClearBuffer();
    EXPECT_STREQ(printer.CStr(), "");
    EXPECT_EQ(printer.CStrSize(), 1u);
}

// Test ClearBuffer(true) explicitly
TEST_F(XMLPrinterClearBufferTest_150, ClearBufferExplicitTrue_150) {
    XMLPrinter printer(nullptr, false, 0);
    printer.OpenElement("elem");
    printer.CloseElement();
    
    printer.ClearBuffer(true);
    
    // Write after clear - should behave as first element
    printer.OpenElement("newelem");
    printer.CloseElement();
    
    const char* result = printer.CStr();
    ASSERT_NE(result, nullptr);
    EXPECT_NE(strstr(result, "newelem"), nullptr);
}

// Test that after ClearBuffer(false) and writing, behavior differs from ClearBuffer(true)
TEST_F(XMLPrinterClearBufferTest_150, ClearBufferFalseVsTrueBehavior_150) {
    // With resetToFirstElement = true
    XMLPrinter printerTrue(nullptr, false, 0);
    printerTrue.OpenElement("first");
    printerTrue.CloseElement();
    printerTrue.ClearBuffer(true);
    printerTrue.OpenElement("second");
    printerTrue.CloseElement();
    const char* resultTrue = printerTrue.CStr();
    
    // With resetToFirstElement = false
    XMLPrinter printerFalse(nullptr, false, 0);
    printerFalse.OpenElement("first");
    printerFalse.CloseElement();
    printerFalse.ClearBuffer(false);
    printerFalse.OpenElement("second");
    printerFalse.CloseElement();
    const char* resultFalse = printerFalse.CStr();
    
    // Both should contain "second" element
    EXPECT_NE(strstr(resultTrue, "second"), nullptr);
    EXPECT_NE(strstr(resultFalse, "second"), nullptr);
}

// Test ClearBuffer with nested elements written before
TEST_F(XMLPrinterClearBufferTest_150, ClearBufferAfterNestedElements_150) {
    XMLPrinter printer(nullptr, false, 0);
    printer.OpenElement("root");
    printer.OpenElement("child");
    printer.OpenElement("grandchild");
    printer.PushText("deep text");
    printer.CloseElement();
    printer.CloseElement();
    printer.CloseElement();
    
    EXPECT_GT(printer.CStrSize(), 1u);
    
    printer.ClearBuffer();
    EXPECT_STREQ(printer.CStr(), "");
    EXPECT_EQ(printer.CStrSize(), 1u);
}

// Test ClearBuffer with various attribute types before clearing
TEST_F(XMLPrinterClearBufferTest_150, ClearBufferAfterVariousAttributes_150) {
    XMLPrinter printer(nullptr, true, 0);
    printer.OpenElement("elem");
    printer.PushAttribute("str", "hello");
    printer.PushAttribute("int", 42);
    printer.PushAttribute("uint", (unsigned)100);
    printer.PushAttribute("bool", true);
    printer.PushAttribute("double", 3.14);
    printer.PushAttribute("int64", (int64_t)1234567890LL);
    printer.PushAttribute("uint64", (uint64_t)9876543210ULL);
    printer.CloseElement();
    
    EXPECT_GT(printer.CStrSize(), 1u);
    
    printer.ClearBuffer();
    EXPECT_STREQ(printer.CStr(), "");
    EXPECT_EQ(printer.CStrSize(), 1u);
}

// Test ClearBuffer with various PushText types
TEST_F(XMLPrinterClearBufferTest_150, ClearBufferAfterVariousPushTextTypes_150) {
    XMLPrinter printer(nullptr, true, 0);
    printer.OpenElement("elem");
    printer.PushText(42);
    printer.CloseElement();
    
    printer.ClearBuffer();
    
    printer.OpenElement("elem");
    printer.PushText((unsigned)99);
    printer.CloseElement();
    
    printer.ClearBuffer();
    
    printer.OpenElement("elem");
    printer.PushText(true);
    printer.CloseElement();
    
    printer.ClearBuffer();
    
    printer.OpenElement("elem");
    printer.PushText(3.14);
    printer.CloseElement();
    
    printer.ClearBuffer();
    
    printer.OpenElement("elem");
    printer.PushText(2.5f);
    printer.CloseElement();
    
    printer.ClearBuffer();
    
    EXPECT_STREQ(printer.CStr(), "");
}
