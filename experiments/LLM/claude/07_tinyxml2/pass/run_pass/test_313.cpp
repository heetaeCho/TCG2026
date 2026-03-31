#include "gtest/gtest.h"
#include "tinyxml2.h"
#include <cstring>
#include <string>

using namespace tinyxml2;

// Helper to get printer output as string
static std::string GetPrinterOutput(XMLPrinter& printer) {
    return std::string(printer.CStr());
}

// ==================== PushComment Tests ====================

TEST(XMLPrinterPushCommentTest_313, BasicComment_313) {
    XMLPrinter printer(nullptr, false, 0);
    printer.PushComment("This is a comment");
    std::string output = GetPrinterOutput(printer);
    EXPECT_NE(output.find("<!--This is a comment-->"), std::string::npos);
}

TEST(XMLPrinterPushCommentTest_313, EmptyComment_313) {
    XMLPrinter printer(nullptr, false, 0);
    printer.PushComment("");
    std::string output = GetPrinterOutput(printer);
    EXPECT_NE(output.find("<!---->"), std::string::npos);
}

TEST(XMLPrinterPushCommentTest_313, CommentWithSpecialChars_313) {
    XMLPrinter printer(nullptr, false, 0);
    printer.PushComment("Hello <world> & \"friends\"");
    std::string output = GetPrinterOutput(printer);
    EXPECT_NE(output.find("<!--Hello <world> & \"friends\"-->"), std::string::npos);
}

TEST(XMLPrinterPushCommentTest_313, CompactModeComment_313) {
    XMLPrinter printer(nullptr, true, 0);
    printer.PushComment("compact comment");
    std::string output = GetPrinterOutput(printer);
    EXPECT_NE(output.find("<!--compact comment-->"), std::string::npos);
}

TEST(XMLPrinterPushCommentTest_313, MultipleComments_313) {
    XMLPrinter printer(nullptr, false, 0);
    printer.PushComment("first");
    printer.PushComment("second");
    std::string output = GetPrinterOutput(printer);
    EXPECT_NE(output.find("<!--first-->"), std::string::npos);
    EXPECT_NE(output.find("<!--second-->"), std::string::npos);
}

TEST(XMLPrinterPushCommentTest_313, CommentInsideElement_313) {
    XMLPrinter printer(nullptr, false, 0);
    printer.OpenElement("root");
    printer.PushComment("inside element");
    printer.CloseElement();
    std::string output = GetPrinterOutput(printer);
    EXPECT_NE(output.find("<root>"), std::string::npos);
    EXPECT_NE(output.find("<!--inside element-->"), std::string::npos);
    EXPECT_NE(output.find("</root>"), std::string::npos);
}

TEST(XMLPrinterPushCommentTest_313, CommentWithDashes_313) {
    XMLPrinter printer(nullptr, false, 0);
    printer.PushComment("has -- dashes");
    std::string output = GetPrinterOutput(printer);
    EXPECT_NE(output.find("<!--has -- dashes-->"), std::string::npos);
}

// ==================== OpenElement / CloseElement Tests ====================

TEST(XMLPrinterElementTest_313, SimpleElement_313) {
    XMLPrinter printer(nullptr, false, 0);
    printer.OpenElement("root");
    printer.CloseElement();
    std::string output = GetPrinterOutput(printer);
    EXPECT_NE(output.find("root"), std::string::npos);
}

TEST(XMLPrinterElementTest_313, NestedElements_313) {
    XMLPrinter printer(nullptr, false, 0);
    printer.OpenElement("parent");
    printer.OpenElement("child");
    printer.CloseElement();
    printer.CloseElement();
    std::string output = GetPrinterOutput(printer);
    EXPECT_NE(output.find("parent"), std::string::npos);
    EXPECT_NE(output.find("child"), std::string::npos);
}

TEST(XMLPrinterElementTest_313, EmptyElementCompact_313) {
    XMLPrinter printer(nullptr, true, 0);
    printer.OpenElement("item", true);
    printer.CloseElement(true);
    std::string output = GetPrinterOutput(printer);
    EXPECT_NE(output.find("item"), std::string::npos);
}

TEST(XMLPrinterElementTest_313, SelfClosingElement_313) {
    XMLPrinter printer(nullptr, false, 0);
    printer.OpenElement("empty");
    printer.CloseElement();
    std::string output = GetPrinterOutput(printer);
    // Self-closing or open/close should contain the element name
    EXPECT_NE(output.find("empty"), std::string::npos);
}

// ==================== PushAttribute Tests ====================

TEST(XMLPrinterAttributeTest_313, StringAttribute_313) {
    XMLPrinter printer(nullptr, false, 0);
    printer.OpenElement("elem");
    printer.PushAttribute("name", "value");
    printer.CloseElement();
    std::string output = GetPrinterOutput(printer);
    EXPECT_NE(output.find("name="), std::string::npos);
    EXPECT_NE(output.find("value"), std::string::npos);
}

TEST(XMLPrinterAttributeTest_313, IntAttribute_313) {
    XMLPrinter printer(nullptr, false, 0);
    printer.OpenElement("elem");
    printer.PushAttribute("count", 42);
    printer.CloseElement();
    std::string output = GetPrinterOutput(printer);
    EXPECT_NE(output.find("count="), std::string::npos);
    EXPECT_NE(output.find("42"), std::string::npos);
}

TEST(XMLPrinterAttributeTest_313, UnsignedAttribute_313) {
    XMLPrinter printer(nullptr, false, 0);
    printer.OpenElement("elem");
    printer.PushAttribute("val", (unsigned int)100);
    printer.CloseElement();
    std::string output = GetPrinterOutput(printer);
    EXPECT_NE(output.find("100"), std::string::npos);
}

TEST(XMLPrinterAttributeTest_313, Int64Attribute_313) {
    XMLPrinter printer(nullptr, false, 0);
    printer.OpenElement("elem");
    printer.PushAttribute("big", (int64_t)1234567890123LL);
    printer.CloseElement();
    std::string output = GetPrinterOutput(printer);
    EXPECT_NE(output.find("1234567890123"), std::string::npos);
}

TEST(XMLPrinterAttributeTest_313, Uint64Attribute_313) {
    XMLPrinter printer(nullptr, false, 0);
    printer.OpenElement("elem");
    printer.PushAttribute("ubig", (uint64_t)9876543210ULL);
    printer.CloseElement();
    std::string output = GetPrinterOutput(printer);
    EXPECT_NE(output.find("9876543210"), std::string::npos);
}

TEST(XMLPrinterAttributeTest_313, BoolAttributeTrue_313) {
    XMLPrinter printer(nullptr, false, 0);
    printer.OpenElement("elem");
    printer.PushAttribute("flag", true);
    printer.CloseElement();
    std::string output = GetPrinterOutput(printer);
    EXPECT_NE(output.find("flag="), std::string::npos);
    EXPECT_NE(output.find("true"), std::string::npos);
}

TEST(XMLPrinterAttributeTest_313, BoolAttributeFalse_313) {
    XMLPrinter printer(nullptr, false, 0);
    printer.OpenElement("elem");
    printer.PushAttribute("flag", false);
    printer.CloseElement();
    std::string output = GetPrinterOutput(printer);
    EXPECT_NE(output.find("false"), std::string::npos);
}

TEST(XMLPrinterAttributeTest_313, DoubleAttribute_313) {
    XMLPrinter printer(nullptr, false, 0);
    printer.OpenElement("elem");
    printer.PushAttribute("pi", 3.14);
    printer.CloseElement();
    std::string output = GetPrinterOutput(printer);
    EXPECT_NE(output.find("pi="), std::string::npos);
    EXPECT_NE(output.find("3.14"), std::string::npos);
}

TEST(XMLPrinterAttributeTest_313, MultipleAttributes_313) {
    XMLPrinter printer(nullptr, false, 0);
    printer.OpenElement("elem");
    printer.PushAttribute("a", "1");
    printer.PushAttribute("b", "2");
    printer.PushAttribute("c", "3");
    printer.CloseElement();
    std::string output = GetPrinterOutput(printer);
    EXPECT_NE(output.find("a="), std::string::npos);
    EXPECT_NE(output.find("b="), std::string::npos);
    EXPECT_NE(output.find("c="), std::string::npos);
}

// ==================== PushText Tests ====================

TEST(XMLPrinterTextTest_313, StringText_313) {
    XMLPrinter printer(nullptr, false, 0);
    printer.OpenElement("elem");
    printer.PushText("hello world");
    printer.CloseElement();
    std::string output = GetPrinterOutput(printer);
    EXPECT_NE(output.find("hello world"), std::string::npos);
}

TEST(XMLPrinterTextTest_313, CDataText_313) {
    XMLPrinter printer(nullptr, false, 0);
    printer.OpenElement("elem");
    printer.PushText("cdata content", true);
    printer.CloseElement();
    std::string output = GetPrinterOutput(printer);
    EXPECT_NE(output.find("<![CDATA[cdata content]]>"), std::string::npos);
}

TEST(XMLPrinterTextTest_313, IntText_313) {
    XMLPrinter printer(nullptr, false, 0);
    printer.OpenElement("num");
    printer.PushText(42);
    printer.CloseElement();
    std::string output = GetPrinterOutput(printer);
    EXPECT_NE(output.find("42"), std::string::npos);
}

TEST(XMLPrinterTextTest_313, NegativeIntText_313) {
    XMLPrinter printer(nullptr, false, 0);
    printer.OpenElement("num");
    printer.PushText(-99);
    printer.CloseElement();
    std::string output = GetPrinterOutput(printer);
    EXPECT_NE(output.find("-99"), std::string::npos);
}

TEST(XMLPrinterTextTest_313, UnsignedText_313) {
    XMLPrinter printer(nullptr, false, 0);
    printer.OpenElement("num");
    printer.PushText((unsigned)500);
    printer.CloseElement();
    std::string output = GetPrinterOutput(printer);
    EXPECT_NE(output.find("500"), std::string::npos);
}

TEST(XMLPrinterTextTest_313, Int64Text_313) {
    XMLPrinter printer(nullptr, false, 0);
    printer.OpenElement("num");
    printer.PushText((int64_t)9999999999LL);
    printer.CloseElement();
    std::string output = GetPrinterOutput(printer);
    EXPECT_NE(output.find("9999999999"), std::string::npos);
}

TEST(XMLPrinterTextTest_313, Uint64Text_313) {
    XMLPrinter printer(nullptr, false, 0);
    printer.OpenElement("num");
    printer.PushText((uint64_t)18446744073709551615ULL);
    printer.CloseElement();
    std::string output = GetPrinterOutput(printer);
    EXPECT_NE(output.find("18446744073709551615"), std::string::npos);
}

TEST(XMLPrinterTextTest_313, BoolTextTrue_313) {
    XMLPrinter printer(nullptr, false, 0);
    printer.OpenElement("b");
    printer.PushText(true);
    printer.CloseElement();
    std::string output = GetPrinterOutput(printer);
    EXPECT_NE(output.find("true"), std::string::npos);
}

TEST(XMLPrinterTextTest_313, BoolTextFalse_313) {
    XMLPrinter printer(nullptr, false, 0);
    printer.OpenElement("b");
    printer.PushText(false);
    printer.CloseElement();
    std::string output = GetPrinterOutput(printer);
    EXPECT_NE(output.find("false"), std::string::npos);
}

TEST(XMLPrinterTextTest_313, FloatText_313) {
    XMLPrinter printer(nullptr, false, 0);
    printer.OpenElement("f");
    printer.PushText(1.5f);
    printer.CloseElement();
    std::string output = GetPrinterOutput(printer);
    EXPECT_NE(output.find("1.5"), std::string::npos);
}

TEST(XMLPrinterTextTest_313, DoubleText_313) {
    XMLPrinter printer(nullptr, false, 0);
    printer.OpenElement("d");
    printer.PushText(2.718281828);
    printer.CloseElement();
    std::string output = GetPrinterOutput(printer);
    EXPECT_NE(output.find("2.71828"), std::string::npos);
}

TEST(XMLPrinterTextTest_313, EmptyStringText_313) {
    XMLPrinter printer(nullptr, false, 0);
    printer.OpenElement("elem");
    printer.PushText("");
    printer.CloseElement();
    std::string output = GetPrinterOutput(printer);
    EXPECT_NE(output.find("<elem>"), std::string::npos);
    EXPECT_NE(output.find("</elem>"), std::string::npos);
}

// ==================== PushDeclaration Tests ====================

TEST(XMLPrinterDeclarationTest_313, BasicDeclaration_313) {
    XMLPrinter printer(nullptr, false, 0);
    printer.PushDeclaration("xml version=\"1.0\"");
    std::string output = GetPrinterOutput(printer);
    EXPECT_NE(output.find("<?xml version=\"1.0\"?>"), std::string::npos);
}

TEST(XMLPrinterDeclarationTest_313, EmptyDeclaration_313) {
    XMLPrinter printer(nullptr, false, 0);
    printer.PushDeclaration("");
    std::string output = GetPrinterOutput(printer);
    EXPECT_NE(output.find("<?"), std::string::npos);
    EXPECT_NE(output.find("?>"), std::string::npos);
}

// ==================== PushUnknown Tests ====================

TEST(XMLPrinterUnknownTest_313, BasicUnknown_313) {
    XMLPrinter printer(nullptr, false, 0);
    printer.PushUnknown("DOCTYPE html");
    std::string output = GetPrinterOutput(printer);
    EXPECT_NE(output.find("<!DOCTYPE html>"), std::string::npos);
}

TEST(XMLPrinterUnknownTest_313, EmptyUnknown_313) {
    XMLPrinter printer(nullptr, false, 0);
    printer.PushUnknown("");
    std::string output = GetPrinterOutput(printer);
    EXPECT_NE(output.find("<!"), std::string::npos);
    EXPECT_NE(output.find(">"), std::string::npos);
}

// ==================== PushHeader Tests ====================

TEST(XMLPrinterHeaderTest_313, DeclarationOnly_313) {
    XMLPrinter printer(nullptr, false, 0);
    printer.PushHeader(false, true);
    std::string output = GetPrinterOutput(printer);
    EXPECT_NE(output.find("<?xml"), std::string::npos);
}

TEST(XMLPrinterHeaderTest_313, NoHeaderAtAll_313) {
    XMLPrinter printer(nullptr, false, 0);
    printer.PushHeader(false, false);
    std::string output = GetPrinterOutput(printer);
    EXPECT_EQ(output.find("<?xml"), std::string::npos);
}

TEST(XMLPrinterHeaderTest_313, WithBOM_313) {
    XMLPrinter printer(nullptr, false, 0);
    printer.PushHeader(true, true);
    std::string output = GetPrinterOutput(printer);
    // BOM is \xEF\xBB\xBF
    EXPECT_EQ(output[0], '\xEF');
    EXPECT_EQ(output[1], '\xBB');
    EXPECT_EQ(output[2], '\xBF');
}

// ==================== CStr / CStrSize / ClearBuffer Tests ====================

TEST(XMLPrinterBufferTest_313, CStrReturnsNonNull_313) {
    XMLPrinter printer(nullptr, false, 0);
    EXPECT_NE(printer.CStr(), nullptr);
}

TEST(XMLPrinterBufferTest_313, CStrSizeInitial_313) {
    XMLPrinter printer(nullptr, false, 0);
    // Size should be at least 1 for null terminator or 0 if empty
    size_t size = printer.CStrSize();
    EXPECT_GE(size, 0u);
}

TEST(XMLPrinterBufferTest_313, CStrSizeAfterContent_313) {
    XMLPrinter printer(nullptr, false, 0);
    printer.OpenElement("test");
    printer.CloseElement();
    size_t size = printer.CStrSize();
    EXPECT_GT(size, 0u);
}

TEST(XMLPrinterBufferTest_313, ClearBufferResetsOutput_313) {
    XMLPrinter printer(nullptr, false, 0);
    printer.OpenElement("test");
    printer.CloseElement();
    EXPECT_GT(printer.CStrSize(), 0u);
    
    printer.ClearBuffer();
    // After clearing, CStr should be empty or minimal
    std::string output = GetPrinterOutput(printer);
    EXPECT_TRUE(output.empty() || output.size() == 0);
}

// ==================== Visitor Interface Tests ====================

TEST(XMLPrinterVisitorTest_313, VisitEnterDocument_313) {
    XMLDocument doc;
    doc.Parse("<root/>");
    
    XMLPrinter printer(nullptr, false, 0);
    bool result = printer.VisitEnter(doc);
    EXPECT_TRUE(result);
}

TEST(XMLPrinterVisitorTest_313, VisitExitDocument_313) {
    XMLDocument doc;
    doc.Parse("<root/>");
    
    XMLPrinter printer(nullptr, false, 0);
    bool result = printer.VisitExit(doc);
    EXPECT_TRUE(result);
}

TEST(XMLPrinterVisitorTest_313, AcceptPrintsDocument_313) {
    XMLDocument doc;
    doc.Parse("<root><child attr=\"val\">text</child></root>");
    ASSERT_EQ(doc.ErrorID(), XML_SUCCESS);
    
    XMLPrinter printer(nullptr, false, 0);
    doc.Accept(&printer);
    std::string output = GetPrinterOutput(printer);
    
    EXPECT_NE(output.find("root"), std::string::npos);
    EXPECT_NE(output.find("child"), std::string::npos);
    EXPECT_NE(output.find("attr"), std::string::npos);
    EXPECT_NE(output.find("val"), std::string::npos);
    EXPECT_NE(output.find("text"), std::string::npos);
}

TEST(XMLPrinterVisitorTest_313, AcceptWithComment_313) {
    XMLDocument doc;
    doc.Parse("<root><!--a comment--></root>");
    ASSERT_EQ(doc.ErrorID(), XML_SUCCESS);
    
    XMLPrinter printer(nullptr, false, 0);
    doc.Accept(&printer);
    std::string output = GetPrinterOutput(printer);
    
    EXPECT_NE(output.find("<!--a comment-->"), std::string::npos);
}

TEST(XMLPrinterVisitorTest_313, AcceptWithDeclaration_313) {
    XMLDocument doc;
    doc.Parse("<?xml version=\"1.0\"?><root/>");
    ASSERT_EQ(doc.ErrorID(), XML_SUCCESS);
    
    XMLPrinter printer(nullptr, false, 0);
    doc.Accept(&printer);
    std::string output = GetPrinterOutput(printer);
    
    EXPECT_NE(output.find("<?xml"), std::string::npos);
    EXPECT_NE(output.find("root"), std::string::npos);
}

// ==================== Compact Mode Tests ====================

TEST(XMLPrinterCompactTest_313, CompactModeSuppressesFormatting_313) {
    XMLPrinter compactPrinter(nullptr, true, 0);
    compactPrinter.OpenElement("root");
    compactPrinter.OpenElement("child");
    compactPrinter.PushText("text");
    compactPrinter.CloseElement();
    compactPrinter.CloseElement();
    std::string compactOutput = GetPrinterOutput(compactPrinter);
    
    XMLPrinter normalPrinter(nullptr, false, 0);
    normalPrinter.OpenElement("root");
    normalPrinter.OpenElement("child");
    normalPrinter.PushText("text");
    normalPrinter.CloseElement();
    normalPrinter.CloseElement();
    std::string normalOutput = GetPrinterOutput(normalPrinter);
    
    // Compact output should be shorter or equal (no whitespace/newlines)
    EXPECT_LE(compactOutput.size(), normalOutput.size());
}

TEST(XMLPrinterCompactTest_313, CompactModeNoNewlines_313) {
    XMLPrinter printer(nullptr, true, 0);
    printer.OpenElement("root");
    printer.OpenElement("child");
    printer.CloseElement();
    printer.CloseElement();
    std::string output = GetPrinterOutput(printer);
    
    EXPECT_EQ(output.find('\n'), std::string::npos);
}

// ==================== Complex Document Tests ====================

TEST(XMLPrinterComplexTest_313, FullDocument_313) {
    XMLPrinter printer(nullptr, false, 0);
    printer.PushHeader(false, true);
    printer.OpenElement("root");
    printer.PushAttribute("version", "1.0");
    printer.OpenElement("item");
    printer.PushAttribute("id", 1);
    printer.PushText("First item");
    printer.CloseElement();
    printer.OpenElement("item");
    printer.PushAttribute("id", 2);
    printer.PushText("Second item");
    printer.CloseElement();
    printer.PushComment("End of items");
    printer.CloseElement();
    
    std::string output = GetPrinterOutput(printer);
    EXPECT_NE(output.find("<?xml"), std::string::npos);
    EXPECT_NE(output.find("<root"), std::string::npos);
    EXPECT_NE(output.find("version="), std::string::npos);
    EXPECT_NE(output.find("First item"), std::string::npos);
    EXPECT_NE(output.find("Second item"), std::string::npos);
    EXPECT_NE(output.find("<!--End of items-->"), std::string::npos);
    EXPECT_NE(output.find("</root>"), std::string::npos);
}

TEST(XMLPrinterComplexTest_313, RoundTripParsePrint_313) {
    const char* xml = "<root><a x=\"1\">text</a><b/></root>";
    XMLDocument doc;
    doc.Parse(xml);
    ASSERT_EQ(doc.ErrorID(), XML_SUCCESS);
    
    XMLPrinter printer(nullptr, true, 0);
    doc.Accept(&printer);
    std::string output = GetPrinterOutput(printer);
    
    // Round trip: parse the output again
    XMLDocument doc2;
    doc2.Parse(output.c_str());
    ASSERT_EQ(doc2.ErrorID(), XML_SUCCESS);
    
    EXPECT_NE(doc2.FirstChildElement("root"), nullptr);
    EXPECT_NE(doc2.FirstChildElement("root")->FirstChildElement("a"), nullptr);
    EXPECT_NE(doc2.FirstChildElement("root")->FirstChildElement("b"), nullptr);
}

// ==================== Depth / Indentation Tests ====================

TEST(XMLPrinterDepthTest_313, InitialDepthAffectsOutput_313) {
    XMLPrinter printer0(nullptr, false, 0);
    printer0.OpenElement("root");
    printer0.CloseElement();
    std::string output0 = GetPrinterOutput(printer0);
    
    XMLPrinter printer2(nullptr, false, 2);
    printer2.OpenElement("root");
    printer2.CloseElement();
    std::string output2 = GetPrinterOutput(printer2);
    
    // With greater initial depth, the output should be at least as long (more indentation)
    EXPECT_GE(output2.size(), output0.size());
}

// ==================== Edge Cases ====================

TEST(XMLPrinterEdgeCaseTest_313, CommentWithAngleBrackets_313) {
    XMLPrinter printer(nullptr, false, 0);
    printer.PushComment("<not a tag>");
    std::string output = GetPrinterOutput(printer);
    EXPECT_NE(output.find("<!--<not a tag>-->"), std::string::npos);
}

TEST(XMLPrinterEdgeCaseTest_313, TextWithEntities_313) {
    XMLPrinter printer(nullptr, false, 0);
    printer.OpenElement("elem");
    printer.PushText("a < b & c > d");
    printer.CloseElement();
    std::string output = GetPrinterOutput(printer);
    // Entities should be escaped
    EXPECT_NE(output.find("&lt;"), std::string::npos);
    EXPECT_NE(output.find("&amp;"), std::string::npos);
    EXPECT_NE(output.find("&gt;"), std::string::npos);
}

TEST(XMLPrinterEdgeCaseTest_313, AttributeWithSpecialChars_313) {
    XMLPrinter printer(nullptr, false, 0);
    printer.OpenElement("elem");
    printer.PushAttribute("data", "a&b<c>d\"e");
    printer.CloseElement();
    std::string output = GetPrinterOutput(printer);
    // Should have escaped entities in attribute
    EXPECT_NE(output.find("&amp;"), std::string::npos);
    EXPECT_NE(output.find("&lt;"), std::string::npos);
}

TEST(XMLPrinterEdgeCaseTest_313, ZeroIntegerText_313) {
    XMLPrinter printer(nullptr, false, 0);
    printer.OpenElement("num");
    printer.PushText(0);
    printer.CloseElement();
    std::string output = GetPrinterOutput(printer);
    EXPECT_NE(output.find("0"), std::string::npos);
}

TEST(XMLPrinterEdgeCaseTest_313, LargeNegativeInt64_313) {
    XMLPrinter printer(nullptr, false, 0);
    printer.OpenElement("num");
    printer.PushText((int64_t)-9223372036854775807LL);
    printer.CloseElement();
    std::string output = GetPrinterOutput(printer);
    EXPECT_NE(output.find("-9223372036854775807"), std::string::npos);
}

TEST(XMLPrinterEdgeCaseTest_313, ClearBufferAndReuse_313) {
    XMLPrinter printer(nullptr, false, 0);
    printer.OpenElement("first");
    printer.CloseElement();
    
    std::string firstOutput = GetPrinterOutput(printer);
    EXPECT_NE(firstOutput.find("first"), std::string::npos);
    
    printer.ClearBuffer();
    
    printer.OpenElement("second");
    printer.CloseElement();
    
    std::string secondOutput = GetPrinterOutput(printer);
    EXPECT_NE(secondOutput.find("second"), std::string::npos);
    EXPECT_EQ(secondOutput.find("first"), std::string::npos);
}
