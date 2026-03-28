#include "gtest/gtest.h"
#include "tinyxml2.h"

using namespace tinyxml2;

class XMLPrinterTest_294 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// ===== PushHeader Tests =====

TEST_F(XMLPrinterTest_294, PushHeader_BOMAndDeclaration_294) {
    XMLPrinter printer(nullptr, false, 0);
    printer.PushHeader(true, true);
    const char* result = printer.CStr();
    ASSERT_NE(result, nullptr);
    // BOM bytes: 0xEF, 0xBB, 0xBF
    EXPECT_EQ(static_cast<unsigned char>(result[0]), 0xEF);
    EXPECT_EQ(static_cast<unsigned char>(result[1]), 0xBB);
    EXPECT_EQ(static_cast<unsigned char>(result[2]), 0xBF);
    // Should also contain the XML declaration
    std::string output(result);
    EXPECT_NE(output.find("<?xml version=\"1.0\"?>"), std::string::npos);
}

TEST_F(XMLPrinterTest_294, PushHeader_BOMOnly_294) {
    XMLPrinter printer(nullptr, false, 0);
    printer.PushHeader(true, false);
    const char* result = printer.CStr();
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(static_cast<unsigned char>(result[0]), 0xEF);
    EXPECT_EQ(static_cast<unsigned char>(result[1]), 0xBB);
    EXPECT_EQ(static_cast<unsigned char>(result[2]), 0xBF);
    std::string output(result);
    EXPECT_EQ(output.find("<?xml"), std::string::npos);
}

TEST_F(XMLPrinterTest_294, PushHeader_DeclarationOnly_294) {
    XMLPrinter printer(nullptr, false, 0);
    printer.PushHeader(false, true);
    const char* result = printer.CStr();
    ASSERT_NE(result, nullptr);
    std::string output(result);
    EXPECT_NE(output.find("<?xml version=\"1.0\"?>"), std::string::npos);
    // Should not start with BOM
    EXPECT_NE(static_cast<unsigned char>(result[0]), 0xEF);
}

TEST_F(XMLPrinterTest_294, PushHeader_NoBOMNoDeclaration_294) {
    XMLPrinter printer(nullptr, false, 0);
    printer.PushHeader(false, false);
    const char* result = printer.CStr();
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(printer.CStrSize(), 1u); // Just null terminator
}

// ===== OpenElement / CloseElement Tests =====

TEST_F(XMLPrinterTest_294, OpenAndCloseElement_294) {
    XMLPrinter printer(nullptr, false, 0);
    printer.OpenElement("root");
    printer.CloseElement();
    std::string output(printer.CStr());
    EXPECT_NE(output.find("<root"), std::string::npos);
    EXPECT_NE(output.find("</root>"), std::string::npos);
}

TEST_F(XMLPrinterTest_294, OpenAndCloseElementCompact_294) {
    XMLPrinter printer(nullptr, true, 0);
    printer.OpenElement("item", true);
    printer.CloseElement(true);
    std::string output(printer.CStr());
    EXPECT_NE(output.find("<item/>"), std::string::npos);
}

TEST_F(XMLPrinterTest_294, NestedElements_294) {
    XMLPrinter printer(nullptr, false, 0);
    printer.OpenElement("root");
    printer.OpenElement("child");
    printer.CloseElement();
    printer.CloseElement();
    std::string output(printer.CStr());
    EXPECT_NE(output.find("<root>"), std::string::npos);
    EXPECT_NE(output.find("<child/>"), std::string::npos);
    EXPECT_NE(output.find("</root>"), std::string::npos);
}

// ===== PushAttribute Tests =====

TEST_F(XMLPrinterTest_294, PushAttributeString_294) {
    XMLPrinter printer(nullptr, false, 0);
    printer.OpenElement("elem");
    printer.PushAttribute("name", "value");
    printer.CloseElement();
    std::string output(printer.CStr());
    EXPECT_NE(output.find("name=\"value\""), std::string::npos);
}

TEST_F(XMLPrinterTest_294, PushAttributeInt_294) {
    XMLPrinter printer(nullptr, false, 0);
    printer.OpenElement("elem");
    printer.PushAttribute("count", 42);
    printer.CloseElement();
    std::string output(printer.CStr());
    EXPECT_NE(output.find("count=\"42\""), std::string::npos);
}

TEST_F(XMLPrinterTest_294, PushAttributeUnsigned_294) {
    XMLPrinter printer(nullptr, false, 0);
    printer.OpenElement("elem");
    printer.PushAttribute("val", (unsigned int)100);
    printer.CloseElement();
    std::string output(printer.CStr());
    EXPECT_NE(output.find("val=\"100\""), std::string::npos);
}

TEST_F(XMLPrinterTest_294, PushAttributeInt64_294) {
    XMLPrinter printer(nullptr, false, 0);
    printer.OpenElement("elem");
    printer.PushAttribute("big", (int64_t)1234567890123LL);
    printer.CloseElement();
    std::string output(printer.CStr());
    EXPECT_NE(output.find("big=\"1234567890123\""), std::string::npos);
}

TEST_F(XMLPrinterTest_294, PushAttributeUint64_294) {
    XMLPrinter printer(nullptr, false, 0);
    printer.OpenElement("elem");
    printer.PushAttribute("ubig", (uint64_t)9876543210ULL);
    printer.CloseElement();
    std::string output(printer.CStr());
    EXPECT_NE(output.find("ubig=\"9876543210\""), std::string::npos);
}

TEST_F(XMLPrinterTest_294, PushAttributeBoolTrue_294) {
    XMLPrinter printer(nullptr, false, 0);
    printer.OpenElement("elem");
    printer.PushAttribute("flag", true);
    printer.CloseElement();
    std::string output(printer.CStr());
    EXPECT_NE(output.find("flag=\"true\""), std::string::npos);
}

TEST_F(XMLPrinterTest_294, PushAttributeBoolFalse_294) {
    XMLPrinter printer(nullptr, false, 0);
    printer.OpenElement("elem");
    printer.PushAttribute("flag", false);
    printer.CloseElement();
    std::string output(printer.CStr());
    EXPECT_NE(output.find("flag=\"false\""), std::string::npos);
}

TEST_F(XMLPrinterTest_294, PushAttributeDouble_294) {
    XMLPrinter printer(nullptr, false, 0);
    printer.OpenElement("elem");
    printer.PushAttribute("pi", 3.14);
    printer.CloseElement();
    std::string output(printer.CStr());
    EXPECT_NE(output.find("pi="), std::string::npos);
}

// ===== PushText Tests =====

TEST_F(XMLPrinterTest_294, PushTextString_294) {
    XMLPrinter printer(nullptr, false, 0);
    printer.OpenElement("elem");
    printer.PushText("Hello World");
    printer.CloseElement();
    std::string output(printer.CStr());
    EXPECT_NE(output.find("Hello World"), std::string::npos);
}

TEST_F(XMLPrinterTest_294, PushTextCData_294) {
    XMLPrinter printer(nullptr, false, 0);
    printer.OpenElement("elem");
    printer.PushText("some data", true);
    printer.CloseElement();
    std::string output(printer.CStr());
    EXPECT_NE(output.find("<![CDATA[some data]]>"), std::string::npos);
}

TEST_F(XMLPrinterTest_294, PushTextInt_294) {
    XMLPrinter printer(nullptr, false, 0);
    printer.OpenElement("elem");
    printer.PushText(123);
    printer.CloseElement();
    std::string output(printer.CStr());
    EXPECT_NE(output.find("123"), std::string::npos);
}

TEST_F(XMLPrinterTest_294, PushTextUnsigned_294) {
    XMLPrinter printer(nullptr, false, 0);
    printer.OpenElement("elem");
    printer.PushText((unsigned int)456);
    printer.CloseElement();
    std::string output(printer.CStr());
    EXPECT_NE(output.find("456"), std::string::npos);
}

TEST_F(XMLPrinterTest_294, PushTextInt64_294) {
    XMLPrinter printer(nullptr, false, 0);
    printer.OpenElement("elem");
    printer.PushText((int64_t)9876543210LL);
    printer.CloseElement();
    std::string output(printer.CStr());
    EXPECT_NE(output.find("9876543210"), std::string::npos);
}

TEST_F(XMLPrinterTest_294, PushTextUint64_294) {
    XMLPrinter printer(nullptr, false, 0);
    printer.OpenElement("elem");
    printer.PushText((uint64_t)1234567890123ULL);
    printer.CloseElement();
    std::string output(printer.CStr());
    EXPECT_NE(output.find("1234567890123"), std::string::npos);
}

TEST_F(XMLPrinterTest_294, PushTextBoolTrue_294) {
    XMLPrinter printer(nullptr, false, 0);
    printer.OpenElement("elem");
    printer.PushText(true);
    printer.CloseElement();
    std::string output(printer.CStr());
    EXPECT_NE(output.find("true"), std::string::npos);
}

TEST_F(XMLPrinterTest_294, PushTextBoolFalse_294) {
    XMLPrinter printer(nullptr, false, 0);
    printer.OpenElement("elem");
    printer.PushText(false);
    printer.CloseElement();
    std::string output(printer.CStr());
    EXPECT_NE(output.find("false"), std::string::npos);
}

TEST_F(XMLPrinterTest_294, PushTextFloat_294) {
    XMLPrinter printer(nullptr, false, 0);
    printer.OpenElement("elem");
    printer.PushText(1.5f);
    printer.CloseElement();
    std::string output(printer.CStr());
    EXPECT_NE(output.find("1.5"), std::string::npos);
}

TEST_F(XMLPrinterTest_294, PushTextDouble_294) {
    XMLPrinter printer(nullptr, false, 0);
    printer.OpenElement("elem");
    printer.PushText(2.718);
    printer.CloseElement();
    std::string output(printer.CStr());
    EXPECT_NE(output.find("2.718"), std::string::npos);
}

// ===== PushComment Tests =====

TEST_F(XMLPrinterTest_294, PushComment_294) {
    XMLPrinter printer(nullptr, false, 0);
    printer.PushComment("This is a comment");
    std::string output(printer.CStr());
    EXPECT_NE(output.find("<!--This is a comment-->"), std::string::npos);
}

// ===== PushDeclaration Tests =====

TEST_F(XMLPrinterTest_294, PushDeclaration_294) {
    XMLPrinter printer(nullptr, false, 0);
    printer.PushDeclaration("xml version=\"1.0\" encoding=\"UTF-8\"");
    std::string output(printer.CStr());
    EXPECT_NE(output.find("<?xml version=\"1.0\" encoding=\"UTF-8\"?>"), std::string::npos);
}

// ===== PushUnknown Tests =====

TEST_F(XMLPrinterTest_294, PushUnknown_294) {
    XMLPrinter printer(nullptr, false, 0);
    printer.PushUnknown("DOCTYPE html");
    std::string output(printer.CStr());
    EXPECT_NE(output.find("<!DOCTYPE html>"), std::string::npos);
}

// ===== CStr / CStrSize Tests =====

TEST_F(XMLPrinterTest_294, CStrInitiallyEmpty_294) {
    XMLPrinter printer(nullptr, false, 0);
    const char* result = printer.CStr();
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(printer.CStrSize(), 1u); // null terminator
}

TEST_F(XMLPrinterTest_294, CStrSizeGrowsAfterContent_294) {
    XMLPrinter printer(nullptr, false, 0);
    size_t initialSize = printer.CStrSize();
    printer.OpenElement("test");
    printer.CloseElement();
    EXPECT_GT(printer.CStrSize(), initialSize);
}

// ===== ClearBuffer Tests =====

TEST_F(XMLPrinterTest_294, ClearBufferResetsContent_294) {
    XMLPrinter printer(nullptr, false, 0);
    printer.OpenElement("test");
    printer.CloseElement();
    EXPECT_GT(printer.CStrSize(), 1u);
    printer.ClearBuffer();
    EXPECT_EQ(printer.CStrSize(), 1u);
}

TEST_F(XMLPrinterTest_294, ClearBufferWithResetFalse_294) {
    XMLPrinter printer(nullptr, false, 0);
    printer.OpenElement("test");
    printer.CloseElement();
    printer.ClearBuffer(false);
    EXPECT_EQ(printer.CStrSize(), 1u);
}

// ===== Visitor Tests with XMLDocument =====

TEST_F(XMLPrinterTest_294, VisitEnterDocument_294) {
    XMLDocument doc;
    doc.Parse("<root><child>text</child></root>");
    ASSERT_FALSE(doc.Error());

    XMLPrinter printer(nullptr, false, 0);
    doc.Accept(&printer);

    std::string output(printer.CStr());
    EXPECT_NE(output.find("<root>"), std::string::npos);
    EXPECT_NE(output.find("<child>"), std::string::npos);
    EXPECT_NE(output.find("text"), std::string::npos);
}

TEST_F(XMLPrinterTest_294, VisitDocumentWithDeclaration_294) {
    XMLDocument doc;
    doc.Parse("<?xml version=\"1.0\"?><root/>");
    ASSERT_FALSE(doc.Error());

    XMLPrinter printer(nullptr, false, 0);
    doc.Accept(&printer);

    std::string output(printer.CStr());
    EXPECT_NE(output.find("<?xml version=\"1.0\"?>"), std::string::npos);
    EXPECT_NE(output.find("<root/>"), std::string::npos);
}

TEST_F(XMLPrinterTest_294, VisitDocumentWithComment_294) {
    XMLDocument doc;
    doc.Parse("<root><!-- comment --></root>");
    ASSERT_FALSE(doc.Error());

    XMLPrinter printer(nullptr, false, 0);
    doc.Accept(&printer);

    std::string output(printer.CStr());
    EXPECT_NE(output.find("comment"), std::string::npos);
}

TEST_F(XMLPrinterTest_294, VisitDocumentWithAttributes_294) {
    XMLDocument doc;
    doc.Parse("<root attr=\"val\"/>");
    ASSERT_FALSE(doc.Error());

    XMLPrinter printer(nullptr, false, 0);
    doc.Accept(&printer);

    std::string output(printer.CStr());
    EXPECT_NE(output.find("attr=\"val\""), std::string::npos);
}

// ===== Compact Mode Tests =====

TEST_F(XMLPrinterTest_294, CompactModePrinter_294) {
    XMLPrinter printer(nullptr, true, 0);
    printer.OpenElement("root");
    printer.OpenElement("child");
    printer.PushText("data");
    printer.CloseElement();
    printer.CloseElement();
    std::string output(printer.CStr());
    // In compact mode, no extra whitespace/newlines between elements
    EXPECT_EQ(output.find('\n'), std::string::npos);
}

TEST_F(XMLPrinterTest_294, NonCompactModePrinter_294) {
    XMLPrinter printer(nullptr, false, 0);
    printer.OpenElement("root");
    printer.OpenElement("child");
    printer.CloseElement();
    printer.CloseElement();
    std::string output(printer.CStr());
    // In non-compact mode, should have newlines
    EXPECT_NE(output.find('\n'), std::string::npos);
}

// ===== Multiple attributes =====

TEST_F(XMLPrinterTest_294, MultipleAttributes_294) {
    XMLPrinter printer(nullptr, false, 0);
    printer.OpenElement("elem");
    printer.PushAttribute("a", "1");
    printer.PushAttribute("b", "2");
    printer.PushAttribute("c", "3");
    printer.CloseElement();
    std::string output(printer.CStr());
    EXPECT_NE(output.find("a=\"1\""), std::string::npos);
    EXPECT_NE(output.find("b=\"2\""), std::string::npos);
    EXPECT_NE(output.find("c=\"3\""), std::string::npos);
}

// ===== Empty element =====

TEST_F(XMLPrinterTest_294, EmptyElementSelfClosing_294) {
    XMLPrinter printer(nullptr, true, 0);
    printer.OpenElement("empty");
    printer.CloseElement();
    std::string output(printer.CStr());
    EXPECT_NE(output.find("<empty/>"), std::string::npos);
}

// ===== Negative int attribute =====

TEST_F(XMLPrinterTest_294, PushAttributeNegativeInt_294) {
    XMLPrinter printer(nullptr, false, 0);
    printer.OpenElement("elem");
    printer.PushAttribute("neg", -42);
    printer.CloseElement();
    std::string output(printer.CStr());
    EXPECT_NE(output.find("neg=\"-42\""), std::string::npos);
}

// ===== Zero values =====

TEST_F(XMLPrinterTest_294, PushTextIntZero_294) {
    XMLPrinter printer(nullptr, false, 0);
    printer.OpenElement("elem");
    printer.PushText(0);
    printer.CloseElement();
    std::string output(printer.CStr());
    EXPECT_NE(output.find("0"), std::string::npos);
}

// ===== Deeply nested =====

TEST_F(XMLPrinterTest_294, DeeplyNestedElements_294) {
    XMLPrinter printer(nullptr, false, 0);
    for (int i = 0; i < 10; ++i) {
        printer.OpenElement("level");
    }
    for (int i = 0; i < 10; ++i) {
        printer.CloseElement();
    }
    std::string output(printer.CStr());
    EXPECT_NE(output.find("<level>"), std::string::npos);
    EXPECT_NE(output.find("</level>"), std::string::npos);
}

// ===== PushHeader multiple calls =====

TEST_F(XMLPrinterTest_294, PushHeaderTwice_294) {
    XMLPrinter printer(nullptr, false, 0);
    printer.PushHeader(false, true);
    printer.PushHeader(false, true);
    std::string output(printer.CStr());
    // Two declarations
    size_t firstPos = output.find("<?xml version=\"1.0\"?>");
    ASSERT_NE(firstPos, std::string::npos);
    size_t secondPos = output.find("<?xml version=\"1.0\"?>", firstPos + 1);
    EXPECT_NE(secondPos, std::string::npos);
}

// ===== Entity escaping in text =====

TEST_F(XMLPrinterTest_294, PushTextWithSpecialChars_294) {
    XMLPrinter printer(nullptr, false, 0);
    printer.OpenElement("elem");
    printer.PushText("<>&\"");
    printer.CloseElement();
    std::string output(printer.CStr());
    // Special characters should be escaped
    EXPECT_NE(output.find("&lt;"), std::string::npos);
    EXPECT_NE(output.find("&gt;"), std::string::npos);
    EXPECT_NE(output.find("&amp;"), std::string::npos);
}

// ===== Round-trip through XMLDocument =====

TEST_F(XMLPrinterTest_294, RoundTripParsePrint_294) {
    const char* xml = "<root><a x=\"1\">hello</a><b/></root>";
    XMLDocument doc;
    doc.Parse(xml);
    ASSERT_FALSE(doc.Error());

    XMLPrinter printer(nullptr, true, 0);
    doc.Accept(&printer);

    XMLDocument doc2;
    doc2.Parse(printer.CStr());
    ASSERT_FALSE(doc2.Error());

    XMLPrinter printer2(nullptr, true, 0);
    doc2.Accept(&printer2);

    EXPECT_STREQ(printer.CStr(), printer2.CStr());
}

// ===== Initial depth =====

TEST_F(XMLPrinterTest_294, InitialDepthNonZero_294) {
    XMLPrinter printer(nullptr, false, 2);
    printer.OpenElement("elem");
    printer.CloseElement();
    std::string output(printer.CStr());
    // With depth 2, there should be leading whitespace
    EXPECT_NE(output.find("        <elem/>"), std::string::npos);
}

// ===== PushText empty string =====

TEST_F(XMLPrinterTest_294, PushTextEmptyString_294) {
    XMLPrinter printer(nullptr, false, 0);
    printer.OpenElement("elem");
    printer.PushText("");
    printer.CloseElement();
    std::string output(printer.CStr());
    EXPECT_NE(output.find("<elem>"), std::string::npos);
    EXPECT_NE(output.find("</elem>"), std::string::npos);
}
