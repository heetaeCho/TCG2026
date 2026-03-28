#include "gtest/gtest.h"
#include "tinyxml2.h"

using namespace tinyxml2;

// Test fixture for XMLPrinter tests
class XMLPrinterTest_149 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// ===== CStrSize Tests =====

TEST_F(XMLPrinterTest_149, CStrSizeInitiallyNonZero_149) {
    // A freshly constructed printer with no file should have buffer with at least null terminator
    XMLPrinter printer;
    // CStrSize includes the null terminator
    EXPECT_GE(printer.CStrSize(), 1u);
}

TEST_F(XMLPrinterTest_149, CStrSizeMatchesCStrLength_149) {
    XMLPrinter printer;
    printer.OpenElement("root");
    printer.CloseElement();
    const char* str = printer.CStr();
    ASSERT_NE(str, nullptr);
    // CStrSize should be strlen + 1 (for null terminator)
    EXPECT_EQ(printer.CStrSize(), strlen(str) + 1);
}

TEST_F(XMLPrinterTest_149, CStrSizeAfterPushText_149) {
    XMLPrinter printer;
    printer.OpenElement("node");
    printer.PushText("Hello World");
    printer.CloseElement();
    const char* str = printer.CStr();
    ASSERT_NE(str, nullptr);
    EXPECT_EQ(printer.CStrSize(), strlen(str) + 1);
}

TEST_F(XMLPrinterTest_149, CStrSizeAfterMultipleElements_149) {
    XMLPrinter printer;
    printer.OpenElement("root");
    printer.OpenElement("child1");
    printer.CloseElement();
    printer.OpenElement("child2");
    printer.CloseElement();
    printer.CloseElement();
    const char* str = printer.CStr();
    ASSERT_NE(str, nullptr);
    EXPECT_EQ(printer.CStrSize(), strlen(str) + 1);
}

TEST_F(XMLPrinterTest_149, CStrSizeAfterClearBuffer_149) {
    XMLPrinter printer;
    printer.OpenElement("root");
    printer.CloseElement();
    size_t sizeBeforeClear = printer.CStrSize();
    EXPECT_GT(sizeBeforeClear, 1u);

    printer.ClearBuffer();
    // After clearing, size should be back to minimal (just null terminator or similar)
    EXPECT_LE(printer.CStrSize(), sizeBeforeClear);
}

TEST_F(XMLPrinterTest_149, CStrSizeCompactMode_149) {
    XMLPrinter printer(nullptr, true); // compact mode
    printer.OpenElement("root");
    printer.OpenElement("child");
    printer.PushText("text");
    printer.CloseElement();
    printer.CloseElement();
    const char* str = printer.CStr();
    ASSERT_NE(str, nullptr);
    EXPECT_EQ(printer.CStrSize(), strlen(str) + 1);
}

TEST_F(XMLPrinterTest_149, CStrSizeNonCompactMode_149) {
    XMLPrinter printer(nullptr, false); // non-compact mode
    printer.OpenElement("root");
    printer.OpenElement("child");
    printer.PushText("text");
    printer.CloseElement();
    printer.CloseElement();
    const char* str = printer.CStr();
    ASSERT_NE(str, nullptr);
    EXPECT_EQ(printer.CStrSize(), strlen(str) + 1);
}

TEST_F(XMLPrinterTest_149, CStrSizeWithAttributes_149) {
    XMLPrinter printer;
    printer.OpenElement("element");
    printer.PushAttribute("name", "value");
    printer.PushAttribute("count", 42);
    printer.PushAttribute("flag", true);
    printer.PushAttribute("ratio", 3.14);
    printer.CloseElement();
    const char* str = printer.CStr();
    ASSERT_NE(str, nullptr);
    EXPECT_EQ(printer.CStrSize(), strlen(str) + 1);
}

TEST_F(XMLPrinterTest_149, CStrSizeWithPushHeader_149) {
    XMLPrinter printer;
    printer.PushHeader(false, true);
    printer.OpenElement("root");
    printer.CloseElement();
    const char* str = printer.CStr();
    ASSERT_NE(str, nullptr);
    EXPECT_EQ(printer.CStrSize(), strlen(str) + 1);
}

TEST_F(XMLPrinterTest_149, CStrSizeWithBOM_149) {
    XMLPrinter printer;
    printer.PushHeader(true, true);
    printer.OpenElement("root");
    printer.CloseElement();
    const char* str = printer.CStr();
    ASSERT_NE(str, nullptr);
    EXPECT_EQ(printer.CStrSize(), strlen(str) + 1);
}

TEST_F(XMLPrinterTest_149, CStrSizeWithComment_149) {
    XMLPrinter printer;
    printer.OpenElement("root");
    printer.PushComment("This is a comment");
    printer.CloseElement();
    const char* str = printer.CStr();
    ASSERT_NE(str, nullptr);
    EXPECT_EQ(printer.CStrSize(), strlen(str) + 1);
}

TEST_F(XMLPrinterTest_149, CStrSizeWithDeclaration_149) {
    XMLPrinter printer;
    printer.PushDeclaration("xml version=\"1.0\"");
    printer.OpenElement("root");
    printer.CloseElement();
    const char* str = printer.CStr();
    ASSERT_NE(str, nullptr);
    EXPECT_EQ(printer.CStrSize(), strlen(str) + 1);
}

TEST_F(XMLPrinterTest_149, CStrSizeWithUnknown_149) {
    XMLPrinter printer;
    printer.OpenElement("root");
    printer.PushUnknown("ENTITY");
    printer.CloseElement();
    const char* str = printer.CStr();
    ASSERT_NE(str, nullptr);
    EXPECT_EQ(printer.CStrSize(), strlen(str) + 1);
}

TEST_F(XMLPrinterTest_149, CStrSizeWithCData_149) {
    XMLPrinter printer;
    printer.OpenElement("root");
    printer.PushText("some cdata content", true); // cdata = true
    printer.CloseElement();
    const char* str = printer.CStr();
    ASSERT_NE(str, nullptr);
    EXPECT_EQ(printer.CStrSize(), strlen(str) + 1);
}

TEST_F(XMLPrinterTest_149, CStrSizeIncrementsAsContentGrows_149) {
    XMLPrinter printer;
    size_t initialSize = printer.CStrSize();
    
    printer.OpenElement("root");
    size_t afterOpen = printer.CStrSize();
    EXPECT_GT(afterOpen, initialSize);

    printer.PushText("some text");
    size_t afterText = printer.CStrSize();
    EXPECT_GT(afterText, afterOpen);

    printer.CloseElement();
    size_t afterClose = printer.CStrSize();
    EXPECT_GT(afterClose, afterText);
}

TEST_F(XMLPrinterTest_149, CStrSizeWithPushTextInt_149) {
    XMLPrinter printer;
    printer.OpenElement("node");
    printer.PushText(12345);
    printer.CloseElement();
    const char* str = printer.CStr();
    ASSERT_NE(str, nullptr);
    EXPECT_EQ(printer.CStrSize(), strlen(str) + 1);
}

TEST_F(XMLPrinterTest_149, CStrSizeWithPushTextUnsigned_149) {
    XMLPrinter printer;
    printer.OpenElement("node");
    printer.PushText(42u);
    printer.CloseElement();
    const char* str = printer.CStr();
    ASSERT_NE(str, nullptr);
    EXPECT_EQ(printer.CStrSize(), strlen(str) + 1);
}

TEST_F(XMLPrinterTest_149, CStrSizeWithPushTextInt64_149) {
    XMLPrinter printer;
    printer.OpenElement("node");
    printer.PushText(static_cast<int64_t>(123456789012345LL));
    printer.CloseElement();
    const char* str = printer.CStr();
    ASSERT_NE(str, nullptr);
    EXPECT_EQ(printer.CStrSize(), strlen(str) + 1);
}

TEST_F(XMLPrinterTest_149, CStrSizeWithPushTextUint64_149) {
    XMLPrinter printer;
    printer.OpenElement("node");
    printer.PushText(static_cast<uint64_t>(123456789012345ULL));
    printer.CloseElement();
    const char* str = printer.CStr();
    ASSERT_NE(str, nullptr);
    EXPECT_EQ(printer.CStrSize(), strlen(str) + 1);
}

TEST_F(XMLPrinterTest_149, CStrSizeWithPushTextBool_149) {
    XMLPrinter printer;
    printer.OpenElement("node");
    printer.PushText(true);
    printer.CloseElement();
    const char* str = printer.CStr();
    ASSERT_NE(str, nullptr);
    EXPECT_EQ(printer.CStrSize(), strlen(str) + 1);
}

TEST_F(XMLPrinterTest_149, CStrSizeWithPushTextFloat_149) {
    XMLPrinter printer;
    printer.OpenElement("node");
    printer.PushText(3.14f);
    printer.CloseElement();
    const char* str = printer.CStr();
    ASSERT_NE(str, nullptr);
    EXPECT_EQ(printer.CStrSize(), strlen(str) + 1);
}

TEST_F(XMLPrinterTest_149, CStrSizeWithPushTextDouble_149) {
    XMLPrinter printer;
    printer.OpenElement("node");
    printer.PushText(2.71828);
    printer.CloseElement();
    const char* str = printer.CStr();
    ASSERT_NE(str, nullptr);
    EXPECT_EQ(printer.CStrSize(), strlen(str) + 1);
}

TEST_F(XMLPrinterTest_149, CStrSizeWithAttributeInt64_149) {
    XMLPrinter printer;
    printer.OpenElement("node");
    printer.PushAttribute("bignum", static_cast<int64_t>(9999999999LL));
    printer.CloseElement();
    const char* str = printer.CStr();
    ASSERT_NE(str, nullptr);
    EXPECT_EQ(printer.CStrSize(), strlen(str) + 1);
}

TEST_F(XMLPrinterTest_149, CStrSizeWithAttributeUint64_149) {
    XMLPrinter printer;
    printer.OpenElement("node");
    printer.PushAttribute("ubignum", static_cast<uint64_t>(9999999999ULL));
    printer.CloseElement();
    const char* str = printer.CStr();
    ASSERT_NE(str, nullptr);
    EXPECT_EQ(printer.CStrSize(), strlen(str) + 1);
}

// Test with XMLDocument printing via visitor pattern
TEST_F(XMLPrinterTest_149, CStrSizeWithDocumentPrint_149) {
    XMLDocument doc;
    doc.Parse("<root><child>text</child></root>");
    ASSERT_FALSE(doc.Error());

    XMLPrinter printer;
    doc.Print(&printer);
    const char* str = printer.CStr();
    ASSERT_NE(str, nullptr);
    EXPECT_EQ(printer.CStrSize(), strlen(str) + 1);
    EXPECT_GT(printer.CStrSize(), 1u);
}

TEST_F(XMLPrinterTest_149, CStrSizeWithEmptyDocument_149) {
    XMLDocument doc;
    XMLPrinter printer;
    doc.Print(&printer);
    // Even an empty document should produce something
    EXPECT_GE(printer.CStrSize(), 1u);
}

TEST_F(XMLPrinterTest_149, CStrSizeAfterMultipleClearAndWrite_149) {
    XMLPrinter printer;
    printer.OpenElement("first");
    printer.CloseElement();
    size_t firstSize = printer.CStrSize();
    EXPECT_GT(firstSize, 1u);

    printer.ClearBuffer();

    printer.OpenElement("second");
    printer.CloseElement();
    size_t secondSize = printer.CStrSize();
    EXPECT_GT(secondSize, 1u);
}

TEST_F(XMLPrinterTest_149, CStrSizeDeeplyNestedElements_149) {
    XMLPrinter printer;
    const int depth = 50;
    for (int i = 0; i < depth; ++i) {
        printer.OpenElement("level");
    }
    for (int i = 0; i < depth; ++i) {
        printer.CloseElement();
    }
    const char* str = printer.CStr();
    ASSERT_NE(str, nullptr);
    EXPECT_EQ(printer.CStrSize(), strlen(str) + 1);
    EXPECT_GT(printer.CStrSize(), 1u);
}

TEST_F(XMLPrinterTest_149, CStrSizeEmptyElementName_149) {
    XMLPrinter printer;
    printer.OpenElement("");
    printer.CloseElement();
    const char* str = printer.CStr();
    ASSERT_NE(str, nullptr);
    EXPECT_EQ(printer.CStrSize(), strlen(str) + 1);
}

TEST_F(XMLPrinterTest_149, CStrSizeSpecialCharactersInText_149) {
    XMLPrinter printer;
    printer.OpenElement("root");
    printer.PushText("&<>\"'");
    printer.CloseElement();
    const char* str = printer.CStr();
    ASSERT_NE(str, nullptr);
    EXPECT_EQ(printer.CStrSize(), strlen(str) + 1);
}

TEST_F(XMLPrinterTest_149, CStrSizeWithFilePointerNull_149) {
    // When file is null, output goes to buffer
    XMLPrinter printer(nullptr, false, 0);
    printer.OpenElement("test");
    printer.CloseElement();
    EXPECT_GT(printer.CStrSize(), 1u);
    EXPECT_NE(printer.CStr(), nullptr);
}

TEST_F(XMLPrinterTest_149, CStrReturnsNonNull_149) {
    XMLPrinter printer;
    EXPECT_NE(printer.CStr(), nullptr);
}

TEST_F(XMLPrinterTest_149, CStrSizeConsistentWithCStr_149) {
    XMLPrinter printer;
    printer.OpenElement("data");
    printer.PushAttribute("id", 1);
    printer.PushAttribute("name", "test");
    printer.PushText("content");
    printer.CloseElement();
    
    const char* result = printer.CStr();
    size_t size = printer.CStrSize();
    
    ASSERT_NE(result, nullptr);
    // The size should account for the null terminator
    EXPECT_EQ(size, strlen(result) + 1);
    // Verify null terminator is actually there
    EXPECT_EQ(result[size - 1], '\0');
}

TEST_F(XMLPrinterTest_149, CStrSizeLargeContent_149) {
    XMLPrinter printer;
    printer.OpenElement("root");
    // Push a large amount of text to exceed initial buffer
    std::string largeText(1000, 'X');
    printer.PushText(largeText.c_str());
    printer.CloseElement();
    const char* str = printer.CStr();
    ASSERT_NE(str, nullptr);
    EXPECT_EQ(printer.CStrSize(), strlen(str) + 1);
    EXPECT_GT(printer.CStrSize(), 1000u);
}

TEST_F(XMLPrinterTest_149, ClearBufferResetToFirstElement_149) {
    XMLPrinter printer;
    printer.OpenElement("first");
    printer.CloseElement();
    
    printer.ClearBuffer(true);  // resetToFirstElement = true
    
    printer.OpenElement("second");
    printer.CloseElement();
    
    const char* str = printer.CStr();
    ASSERT_NE(str, nullptr);
    // Should only contain the second element
    EXPECT_TRUE(strstr(str, "second") != nullptr);
}

TEST_F(XMLPrinterTest_149, ClearBufferNoReset_149) {
    XMLPrinter printer;
    printer.OpenElement("first");
    printer.CloseElement();
    
    printer.ClearBuffer(false);  // resetToFirstElement = false
    
    printer.OpenElement("second");
    printer.CloseElement();
    
    const char* str = printer.CStr();
    ASSERT_NE(str, nullptr);
    EXPECT_EQ(printer.CStrSize(), strlen(str) + 1);
}
