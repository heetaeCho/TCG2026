#include "gtest/gtest.h"
#include "tinyxml2.h"

using namespace tinyxml2;

// =============================================================================
// XMLPrinter::VisitEnter(const XMLDocument&) Tests
// =============================================================================

TEST(XMLPrinterVisitEnter_316, ReturnsTrue_NoBOM_316) {
    XMLDocument doc;
    doc.SetBOM(false);
    XMLPrinter printer;
    bool result = printer.VisitEnter(doc);
    EXPECT_TRUE(result);
}

TEST(XMLPrinterVisitEnter_316, ReturnsTrue_WithBOM_316) {
    XMLDocument doc;
    doc.SetBOM(true);
    XMLPrinter printer;
    bool result = printer.VisitEnter(doc);
    EXPECT_TRUE(result);
}

TEST(XMLPrinterVisitEnter_316, BOMWrittenWhenHasBOM_316) {
    XMLDocument doc;
    doc.SetBOM(true);
    XMLPrinter printer(nullptr, false);
    printer.VisitEnter(doc);
    const char* output = printer.CStr();
    ASSERT_NE(output, nullptr);
    // BOM is UTF-8 BOM: 0xEF, 0xBB, 0xBF
    EXPECT_GE(printer.CStrSize(), 3u);
    EXPECT_EQ(static_cast<unsigned char>(output[0]), 0xEF);
    EXPECT_EQ(static_cast<unsigned char>(output[1]), 0xBB);
    EXPECT_EQ(static_cast<unsigned char>(output[2]), 0xBF);
}

TEST(XMLPrinterVisitEnter_316, NoBOMWrittenWhenNoBOM_316) {
    XMLDocument doc;
    doc.SetBOM(false);
    XMLPrinter printer(nullptr, false);
    printer.VisitEnter(doc);
    const char* output = printer.CStr();
    // Should be empty or at least not start with BOM
    if (printer.CStrSize() > 0 && output != nullptr) {
        bool hasBOM = (printer.CStrSize() >= 3 &&
                       static_cast<unsigned char>(output[0]) == 0xEF &&
                       static_cast<unsigned char>(output[1]) == 0xBB &&
                       static_cast<unsigned char>(output[2]) == 0xBF);
        EXPECT_FALSE(hasBOM);
    }
}

TEST(XMLPrinterVisitEnter_316, ProcessEntitiesTrue_316) {
    XMLDocument doc(true);
    XMLPrinter printer;
    printer.VisitEnter(doc);
    EXPECT_TRUE(doc.ProcessEntities());
    // After VisitEnter, the printer should respect process entities.
    // We verify indirectly by printing text with entities.
    printer.OpenElement("root");
    printer.PushText("a&b");
    printer.CloseElement();
    const char* output = printer.CStr();
    ASSERT_NE(output, nullptr);
    // With process entities, '&' should be escaped to '&amp;'
    EXPECT_NE(std::string(output).find("&amp;"), std::string::npos);
}

TEST(XMLPrinterVisitEnter_316, ProcessEntitiesFalse_316) {
    XMLDocument doc(false);
    XMLPrinter printer;
    printer.VisitEnter(doc);
    EXPECT_FALSE(doc.ProcessEntities());
    // After VisitEnter with processEntities=false, entities should not be processed
    printer.OpenElement("root");
    printer.PushText("a&b");
    printer.CloseElement();
    const char* output = printer.CStr();
    ASSERT_NE(output, nullptr);
    // With process entities off, '&' might not be escaped (kept as-is)
    // Depending on implementation, check that raw '&' without 'amp;' exists
    std::string s(output);
    // The string should contain "a&b" literally (not "a&amp;b")
    EXPECT_NE(s.find("a&b"), std::string::npos);
}

TEST(XMLPrinterVisitEnter_316, CompactModePrinter_316) {
    XMLDocument doc;
    doc.SetBOM(true);
    XMLPrinter printer(nullptr, true);
    bool result = printer.VisitEnter(doc);
    EXPECT_TRUE(result);
    const char* output = printer.CStr();
    ASSERT_NE(output, nullptr);
    EXPECT_GE(printer.CStrSize(), 3u);
}

// =============================================================================
// XMLDocument Tests
// =============================================================================

TEST(XMLDocumentTest_316, DefaultConstruction_316) {
    XMLDocument doc;
    EXPECT_FALSE(doc.Error());
    EXPECT_EQ(doc.ErrorID(), XML_SUCCESS);
    EXPECT_TRUE(doc.ProcessEntities());
    EXPECT_FALSE(doc.HasBOM());
}

TEST(XMLDocumentTest_316, ConstructionWithProcessEntitiesFalse_316) {
    XMLDocument doc(false);
    EXPECT_FALSE(doc.ProcessEntities());
}

TEST(XMLDocumentTest_316, SetBOMTrue_316) {
    XMLDocument doc;
    doc.SetBOM(true);
    EXPECT_TRUE(doc.HasBOM());
}

TEST(XMLDocumentTest_316, SetBOMFalse_316) {
    XMLDocument doc;
    doc.SetBOM(true);
    doc.SetBOM(false);
    EXPECT_FALSE(doc.HasBOM());
}

TEST(XMLDocumentTest_316, ParseSimpleXML_316) {
    XMLDocument doc;
    XMLError err = doc.Parse("<root><child/></root>");
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_FALSE(doc.Error());
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    EXPECT_STREQ(root->Name(), "root");
}

TEST(XMLDocumentTest_316, ParseEmptyString_316) {
    XMLDocument doc;
    XMLError err = doc.Parse("");
    EXPECT_NE(err, XML_SUCCESS);
    EXPECT_TRUE(doc.Error());
}

TEST(XMLDocumentTest_316, ParseNullString_316) {
    XMLDocument doc;
    XMLError err = doc.Parse(nullptr, 0);
    EXPECT_NE(err, XML_SUCCESS);
}

TEST(XMLDocumentTest_316, ParseInvalidXML_316) {
    XMLDocument doc;
    XMLError err = doc.Parse("<root><unclosed>");
    EXPECT_NE(err, XML_SUCCESS);
    EXPECT_TRUE(doc.Error());
}

TEST(XMLDocumentTest_316, ClearError_316) {
    XMLDocument doc;
    doc.Parse("<invalid");
    EXPECT_TRUE(doc.Error());
    doc.ClearError();
    EXPECT_FALSE(doc.Error());
    EXPECT_EQ(doc.ErrorID(), XML_SUCCESS);
}

TEST(XMLDocumentTest_316, ErrorName_316) {
    XMLDocument doc;
    doc.Parse("<root></root>");
    const char* name = doc.ErrorName();
    ASSERT_NE(name, nullptr);
    EXPECT_STREQ(name, "XML_SUCCESS");
}

TEST(XMLDocumentTest_316, ErrorIDToName_316) {
    const char* name = XMLDocument::ErrorIDToName(XML_SUCCESS);
    ASSERT_NE(name, nullptr);
    EXPECT_STREQ(name, "XML_SUCCESS");

    const char* errName = XMLDocument::ErrorIDToName(XML_ERROR_FILE_NOT_FOUND);
    ASSERT_NE(errName, nullptr);
}

TEST(XMLDocumentTest_316, NewElement_316) {
    XMLDocument doc;
    XMLElement* elem = doc.NewElement("test");
    ASSERT_NE(elem, nullptr);
    EXPECT_STREQ(elem->Name(), "test");
    doc.InsertEndChild(elem);
    EXPECT_EQ(doc.RootElement(), elem);
}

TEST(XMLDocumentTest_316, NewComment_316) {
    XMLDocument doc;
    XMLComment* comment = doc.NewComment("a comment");
    ASSERT_NE(comment, nullptr);
    doc.InsertEndChild(comment);
}

TEST(XMLDocumentTest_316, NewText_316) {
    XMLDocument doc;
    XMLText* text = doc.NewText("hello");
    ASSERT_NE(text, nullptr);
}

TEST(XMLDocumentTest_316, NewDeclaration_316) {
    XMLDocument doc;
    XMLDeclaration* decl = doc.NewDeclaration();
    ASSERT_NE(decl, nullptr);
}

TEST(XMLDocumentTest_316, NewUnknown_316) {
    XMLDocument doc;
    XMLUnknown* unk = doc.NewUnknown("something");
    ASSERT_NE(unk, nullptr);
}

TEST(XMLDocumentTest_316, DeleteNode_316) {
    XMLDocument doc;
    XMLElement* elem = doc.NewElement("test");
    doc.InsertEndChild(elem);
    EXPECT_NE(doc.RootElement(), nullptr);
    doc.DeleteNode(elem);
    EXPECT_EQ(doc.RootElement(), nullptr);
}

TEST(XMLDocumentTest_316, Clear_316) {
    XMLDocument doc;
    doc.Parse("<root><child/></root>");
    EXPECT_NE(doc.RootElement(), nullptr);
    doc.Clear();
    EXPECT_EQ(doc.RootElement(), nullptr);
}

TEST(XMLDocumentTest_316, DeepCopy_316) {
    XMLDocument doc;
    doc.Parse("<root><child attr=\"val\">text</child></root>");
    ASSERT_FALSE(doc.Error());

    XMLDocument target;
    doc.DeepCopy(&target);
    ASSERT_NE(target.RootElement(), nullptr);
    EXPECT_STREQ(target.RootElement()->Name(), "root");
}

TEST(XMLDocumentTest_316, ToDocument_316) {
    XMLDocument doc;
    EXPECT_EQ(doc.ToDocument(), &doc);
}

TEST(XMLDocumentTest_316, ShallowCloneReturnsNull_316) {
    XMLDocument doc;
    XMLNode* clone = doc.ShallowClone(&doc);
    EXPECT_EQ(clone, nullptr);
}

TEST(XMLDocumentTest_316, ShallowEqualReturnsFalse_316) {
    XMLDocument doc;
    XMLDocument doc2;
    EXPECT_FALSE(doc.ShallowEqual(&doc2));
}

TEST(XMLDocumentTest_316, PrintToXMLPrinter_316) {
    XMLDocument doc;
    doc.Parse("<root>hello</root>");
    ASSERT_FALSE(doc.Error());

    XMLPrinter printer;
    doc.Print(&printer);
    const char* output = printer.CStr();
    ASSERT_NE(output, nullptr);
    EXPECT_NE(std::string(output).find("root"), std::string::npos);
    EXPECT_NE(std::string(output).find("hello"), std::string::npos);
}

TEST(XMLDocumentTest_316, AcceptVisitor_316) {
    XMLDocument doc;
    doc.Parse("<root/>");
    ASSERT_FALSE(doc.Error());

    XMLPrinter printer;
    bool result = doc.Accept(&printer);
    EXPECT_TRUE(result);
    const char* output = printer.CStr();
    ASSERT_NE(output, nullptr);
    EXPECT_NE(std::string(output).find("root"), std::string::npos);
}

TEST(XMLDocumentTest_316, ErrorLineNum_316) {
    XMLDocument doc;
    doc.Parse("<root>\n<unclosed>");
    EXPECT_TRUE(doc.Error());
    EXPECT_GT(doc.ErrorLineNum(), 0);
}

TEST(XMLDocumentTest_316, ErrorStr_316) {
    XMLDocument doc;
    doc.Parse("<root><");
    EXPECT_TRUE(doc.Error());
    const char* errStr = doc.ErrorStr();
    ASSERT_NE(errStr, nullptr);
    EXPECT_GT(strlen(errStr), 0u);
}

TEST(XMLDocumentTest_316, LoadFileNonexistent_316) {
    XMLDocument doc;
    XMLError err = doc.LoadFile("nonexistent_file_that_does_not_exist.xml");
    EXPECT_NE(err, XML_SUCCESS);
    EXPECT_TRUE(doc.Error());
}

// =============================================================================
// XMLPrinter standalone Tests
// =============================================================================

TEST(XMLPrinterTest_316, DefaultConstruction_316) {
    XMLPrinter printer;
    const char* output = printer.CStr();
    ASSERT_NE(output, nullptr);
    EXPECT_EQ(printer.CStrSize(), 1u); // Just the null terminator
}

TEST(XMLPrinterTest_316, PushHeaderBOMOnly_316) {
    XMLPrinter printer;
    printer.PushHeader(true, false);
    const char* output = printer.CStr();
    ASSERT_NE(output, nullptr);
    EXPECT_GE(printer.CStrSize(), 3u);
    EXPECT_EQ(static_cast<unsigned char>(output[0]), 0xEF);
    EXPECT_EQ(static_cast<unsigned char>(output[1]), 0xBB);
    EXPECT_EQ(static_cast<unsigned char>(output[2]), 0xBF);
}

TEST(XMLPrinterTest_316, PushHeaderDeclarationOnly_316) {
    XMLPrinter printer;
    printer.PushHeader(false, true);
    const char* output = printer.CStr();
    ASSERT_NE(output, nullptr);
    std::string s(output);
    EXPECT_NE(s.find("<?xml"), std::string::npos);
}

TEST(XMLPrinterTest_316, PushHeaderBOMAndDeclaration_316) {
    XMLPrinter printer;
    printer.PushHeader(true, true);
    const char* output = printer.CStr();
    ASSERT_NE(output, nullptr);
    EXPECT_EQ(static_cast<unsigned char>(output[0]), 0xEF);
    EXPECT_EQ(static_cast<unsigned char>(output[1]), 0xBB);
    EXPECT_EQ(static_cast<unsigned char>(output[2]), 0xBF);
    std::string s(output);
    EXPECT_NE(s.find("<?xml"), std::string::npos);
}

TEST(XMLPrinterTest_316, OpenAndCloseElement_316) {
    XMLPrinter printer;
    printer.OpenElement("test");
    printer.CloseElement();
    const char* output = printer.CStr();
    ASSERT_NE(output, nullptr);
    std::string s(output);
    EXPECT_NE(s.find("<test"), std::string::npos);
}

TEST(XMLPrinterTest_316, PushAttributeString_316) {
    XMLPrinter printer;
    printer.OpenElement("elem");
    printer.PushAttribute("key", "value");
    printer.CloseElement();
    const char* output = printer.CStr();
    std::string s(output);
    EXPECT_NE(s.find("key=\"value\""), std::string::npos);
}

TEST(XMLPrinterTest_316, PushAttributeInt_316) {
    XMLPrinter printer;
    printer.OpenElement("elem");
    printer.PushAttribute("num", 42);
    printer.CloseElement();
    const char* output = printer.CStr();
    std::string s(output);
    EXPECT_NE(s.find("num=\"42\""), std::string::npos);
}

TEST(XMLPrinterTest_316, PushAttributeBool_316) {
    XMLPrinter printer;
    printer.OpenElement("elem");
    printer.PushAttribute("flag", true);
    printer.CloseElement();
    const char* output = printer.CStr();
    std::string s(output);
    EXPECT_NE(s.find("flag=\"true\""), std::string::npos);
}

TEST(XMLPrinterTest_316, PushAttributeDouble_316) {
    XMLPrinter printer;
    printer.OpenElement("elem");
    printer.PushAttribute("val", 3.14);
    printer.CloseElement();
    const char* output = printer.CStr();
    std::string s(output);
    EXPECT_NE(s.find("val="), std::string::npos);
}

TEST(XMLPrinterTest_316, PushTextString_316) {
    XMLPrinter printer;
    printer.OpenElement("elem");
    printer.PushText("hello world");
    printer.CloseElement();
    const char* output = printer.CStr();
    std::string s(output);
    EXPECT_NE(s.find("hello world"), std::string::npos);
}

TEST(XMLPrinterTest_316, PushTextInt_316) {
    XMLPrinter printer;
    printer.OpenElement("elem");
    printer.PushText(123);
    printer.CloseElement();
    const char* output = printer.CStr();
    std::string s(output);
    EXPECT_NE(s.find("123"), std::string::npos);
}

TEST(XMLPrinterTest_316, PushTextBool_316) {
    XMLPrinter printer;
    printer.OpenElement("elem");
    printer.PushText(true);
    printer.CloseElement();
    const char* output = printer.CStr();
    std::string s(output);
    EXPECT_NE(s.find("true"), std::string::npos);
}

TEST(XMLPrinterTest_316, PushTextCDATA_316) {
    XMLPrinter printer;
    printer.OpenElement("elem");
    printer.PushText("data", true);
    printer.CloseElement();
    const char* output = printer.CStr();
    std::string s(output);
    EXPECT_NE(s.find("<![CDATA[data]]>"), std::string::npos);
}

TEST(XMLPrinterTest_316, PushComment_316) {
    XMLPrinter printer;
    printer.PushComment("my comment");
    const char* output = printer.CStr();
    std::string s(output);
    EXPECT_NE(s.find("<!--my comment-->"), std::string::npos);
}

TEST(XMLPrinterTest_316, PushDeclaration_316) {
    XMLPrinter printer;
    printer.PushDeclaration("xml version=\"1.0\"");
    const char* output = printer.CStr();
    std::string s(output);
    EXPECT_NE(s.find("<?xml version=\"1.0\"?>"), std::string::npos);
}

TEST(XMLPrinterTest_316, PushUnknown_316) {
    XMLPrinter printer;
    printer.PushUnknown("DOCTYPE html");
    const char* output = printer.CStr();
    std::string s(output);
    EXPECT_NE(s.find("<!DOCTYPE html>"), std::string::npos);
}

TEST(XMLPrinterTest_316, ClearBuffer_316) {
    XMLPrinter printer;
    printer.OpenElement("elem");
    printer.CloseElement();
    EXPECT_GT(printer.CStrSize(), 1u);
    printer.ClearBuffer();
    EXPECT_EQ(printer.CStrSize(), 1u); // Just null terminator
}

TEST(XMLPrinterTest_316, NestedElements_316) {
    XMLPrinter printer;
    printer.OpenElement("parent");
    printer.OpenElement("child");
    printer.PushText("content");
    printer.CloseElement();
    printer.CloseElement();
    const char* output = printer.CStr();
    std::string s(output);
    EXPECT_NE(s.find("<parent>"), std::string::npos);
    EXPECT_NE(s.find("<child>"), std::string::npos);
    EXPECT_NE(s.find("content"), std::string::npos);
    EXPECT_NE(s.find("</child>"), std::string::npos);
    EXPECT_NE(s.find("</parent>"), std::string::npos);
}

TEST(XMLPrinterTest_316, CompactModePrinter_316) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("root");
    printer.OpenElement("child");
    printer.PushText("text");
    printer.CloseElement();
    printer.CloseElement();
    const char* output = printer.CStr();
    std::string s(output);
    // In compact mode, there should be no extra whitespace/newlines between elements
    EXPECT_EQ(s.find('\n'), std::string::npos);
}

TEST(XMLPrinterTest_316, PushTextFloat_316) {
    XMLPrinter printer;
    printer.OpenElement("elem");
    printer.PushText(1.5f);
    printer.CloseElement();
    const char* output = printer.CStr();
    std::string s(output);
    EXPECT_NE(s.find("1.5"), std::string::npos);
}

TEST(XMLPrinterTest_316, PushTextDouble_316) {
    XMLPrinter printer;
    printer.OpenElement("elem");
    printer.PushText(2.5);
    printer.CloseElement();
    const char* output = printer.CStr();
    std::string s(output);
    EXPECT_NE(s.find("2.5"), std::string::npos);
}

TEST(XMLPrinterTest_316, PushAttributeInt64_316) {
    XMLPrinter printer;
    printer.OpenElement("elem");
    int64_t bigVal = 9223372036854775807LL;
    printer.PushAttribute("big", bigVal);
    printer.CloseElement();
    const char* output = printer.CStr();
    std::string s(output);
    EXPECT_NE(s.find("9223372036854775807"), std::string::npos);
}

TEST(XMLPrinterTest_316, PushAttributeUint64_316) {
    XMLPrinter printer;
    printer.OpenElement("elem");
    uint64_t val = 18446744073709551615ULL;
    printer.PushAttribute("uval", val);
    printer.CloseElement();
    const char* output = printer.CStr();
    std::string s(output);
    EXPECT_NE(s.find("18446744073709551615"), std::string::npos);
}

TEST(XMLPrinterTest_316, PushTextInt64_316) {
    XMLPrinter printer;
    printer.OpenElement("elem");
    printer.PushText(static_cast<int64_t>(-1234567890123LL));
    printer.CloseElement();
    const char* output = printer.CStr();
    std::string s(output);
    EXPECT_NE(s.find("-1234567890123"), std::string::npos);
}

TEST(XMLPrinterTest_316, PushTextUint64_316) {
    XMLPrinter printer;
    printer.OpenElement("elem");
    printer.PushText(static_cast<uint64_t>(9876543210ULL));
    printer.CloseElement();
    const char* output = printer.CStr();
    std::string s(output);
    EXPECT_NE(s.find("9876543210"), std::string::npos);
}

// =============================================================================
// Integration: XMLDocument with XMLPrinter via Accept
// =============================================================================

TEST(XMLIntegrationTest_316, DocumentWithBOMPrintsCorrectly_316) {
    XMLDocument doc;
    doc.Parse("<root/>");
    ASSERT_FALSE(doc.Error());
    doc.SetBOM(true);

    XMLPrinter printer;
    doc.Accept(&printer);
    const char* output = printer.CStr();
    ASSERT_NE(output, nullptr);
    // Should start with BOM
    EXPECT_EQ(static_cast<unsigned char>(output[0]), 0xEF);
    EXPECT_EQ(static_cast<unsigned char>(output[1]), 0xBB);
    EXPECT_EQ(static_cast<unsigned char>(output[2]), 0xBF);
}

TEST(XMLIntegrationTest_316, DocumentWithoutBOMPrintsCorrectly_316) {
    XMLDocument doc;
    doc.Parse("<root/>");
    ASSERT_FALSE(doc.Error());
    doc.SetBOM(false);

    XMLPrinter printer;
    doc.Accept(&printer);
    const char* output = printer.CStr();
    ASSERT_NE(output, nullptr);
    std::string s(output);
    // Should not start with BOM
    if (s.size() >= 3) {
        bool hasBOM = (static_cast<unsigned char>(output[0]) == 0xEF &&
                       static_cast<unsigned char>(output[1]) == 0xBB &&
                       static_cast<unsigned char>(output[2]) == 0xBF);
        EXPECT_FALSE(hasBOM);
    }
}

TEST(XMLIntegrationTest_316, ParseAndPrintRoundTrip_316) {
    const char* xml = "<root><child attr=\"val\">text</child></root>";
    XMLDocument doc;
    doc.Parse(xml);
    ASSERT_FALSE(doc.Error());

    XMLPrinter printer(nullptr, true);
    doc.Accept(&printer);
    const char* output = printer.CStr();
    ASSERT_NE(output, nullptr);

    // Reparse the output
    XMLDocument doc2;
    XMLError err = doc2.Parse(output);
    EXPECT_EQ(err, XML_SUCCESS);
    ASSERT_NE(doc2.RootElement(), nullptr);
    EXPECT_STREQ(doc2.RootElement()->Name(), "root");
}

TEST(XMLIntegrationTest_316, ParseWithDeclarationAndBOM_316) {
    const char* xml = "<?xml version=\"1.0\" encoding=\"UTF-8\"?><root/>";
    XMLDocument doc;
    doc.Parse(xml);
    ASSERT_FALSE(doc.Error());
    doc.SetBOM(true);

    XMLPrinter printer;
    doc.Accept(&printer);
    const char* output = printer.CStr();
    ASSERT_NE(output, nullptr);
    std::string s(output);
    EXPECT_NE(s.find("<?xml"), std::string::npos);
}

TEST(XMLDocumentTest_316, ParseWithSpecifiedLength_316) {
    const char* xml = "<root/>EXTRA_GARBAGE";
    XMLDocument doc;
    XMLError err = doc.Parse(xml, 7); // Only parse "<root/>"
    EXPECT_EQ(err, XML_SUCCESS);
    ASSERT_NE(doc.RootElement(), nullptr);
    EXPECT_STREQ(doc.RootElement()->Name(), "root");
}

TEST(XMLDocumentTest_316, WhitespaceMode_316) {
    XMLDocument doc(true, COLLAPSE_WHITESPACE);
    EXPECT_EQ(doc.WhitespaceMode(), COLLAPSE_WHITESPACE);
}

TEST(XMLDocumentTest_316, WhitespaceModePreserve_316) {
    XMLDocument doc(true, PRESERVE_WHITESPACE);
    EXPECT_EQ(doc.WhitespaceMode(), PRESERVE_WHITESPACE);
}

TEST(XMLPrinterTest_316, SelfClosingEmptyElement_316) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("empty");
    printer.CloseElement(true);
    const char* output = printer.CStr();
    std::string s(output);
    EXPECT_NE(s.find("<empty/>"), std::string::npos);
}

TEST(XMLPrinterTest_316, MultipleAttributes_316) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("elem");
    printer.PushAttribute("a", "1");
    printer.PushAttribute("b", "2");
    printer.PushAttribute("c", "3");
    printer.CloseElement();
    const char* output = printer.CStr();
    std::string s(output);
    EXPECT_NE(s.find("a=\"1\""), std::string::npos);
    EXPECT_NE(s.find("b=\"2\""), std::string::npos);
    EXPECT_NE(s.find("c=\"3\""), std::string::npos);
}

TEST(XMLPrinterTest_316, PushAttributeUnsigned_316) {
    XMLPrinter printer;
    printer.OpenElement("elem");
    printer.PushAttribute("u", static_cast<unsigned int>(4294967295U));
    printer.CloseElement();
    const char* output = printer.CStr();
    std::string s(output);
    EXPECT_NE(s.find("4294967295"), std::string::npos);
}

TEST(XMLPrinterTest_316, PushTextUnsigned_316) {
    XMLPrinter printer;
    printer.OpenElement("elem");
    printer.PushText(static_cast<unsigned int>(12345));
    printer.CloseElement();
    const char* output = printer.CStr();
    std::string s(output);
    EXPECT_NE(s.find("12345"), std::string::npos);
}
