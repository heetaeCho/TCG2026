#include "gtest/gtest.h"
#include "tinyxml2.h"
#include <cstdio>
#include <cstring>
#include <string>

using namespace tinyxml2;

// ============================================================
// Test Fixture
// ============================================================
class XMLDocumentTest_284 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// ============================================================
// Construction / Default State
// ============================================================
TEST_F(XMLDocumentTest_284, DefaultConstruction_NoError_284) {
    XMLDocument doc;
    EXPECT_FALSE(doc.Error());
    EXPECT_EQ(doc.ErrorID(), XML_SUCCESS);
    EXPECT_EQ(doc.ErrorLineNum(), 0);
}

TEST_F(XMLDocumentTest_284, DefaultConstruction_NoBOM_284) {
    XMLDocument doc;
    EXPECT_FALSE(doc.HasBOM());
}

TEST_F(XMLDocumentTest_284, ConstructWithProcessEntitiesTrue_284) {
    XMLDocument doc(true);
    EXPECT_TRUE(doc.ProcessEntities());
}

TEST_F(XMLDocumentTest_284, ConstructWithProcessEntitiesFalse_284) {
    XMLDocument doc(false);
    EXPECT_FALSE(doc.ProcessEntities());
}

TEST_F(XMLDocumentTest_284, DefaultWhitespaceMode_284) {
    XMLDocument doc;
    EXPECT_EQ(doc.WhitespaceMode(), PRESERVE_WHITESPACE);
    // Default is PRESERVE_WHITESPACE or COLLAPSE_WHITESPACE depending on default arg
}

// ============================================================
// Parse
// ============================================================
TEST_F(XMLDocumentTest_284, ParseSimpleXML_284) {
    XMLDocument doc;
    XMLError err = doc.Parse("<root><child/></root>");
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_FALSE(doc.Error());
}

TEST_F(XMLDocumentTest_284, ParseWithSize_284) {
    XMLDocument doc;
    const char* xml = "<root/>";
    XMLError err = doc.Parse(xml, strlen(xml));
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_FALSE(doc.Error());
}

TEST_F(XMLDocumentTest_284, ParseEmptyString_284) {
    XMLDocument doc;
    XMLError err = doc.Parse("");
    EXPECT_NE(err, XML_SUCCESS);
    EXPECT_TRUE(doc.Error());
}

TEST_F(XMLDocumentTest_284, ParseNullPointer_284) {
    XMLDocument doc;
    XMLError err = doc.Parse(nullptr);
    EXPECT_NE(err, XML_SUCCESS);
    EXPECT_TRUE(doc.Error());
}

TEST_F(XMLDocumentTest_284, ParseMalformedXML_284) {
    XMLDocument doc;
    XMLError err = doc.Parse("<root><child></root>");
    EXPECT_NE(err, XML_SUCCESS);
    EXPECT_TRUE(doc.Error());
}

TEST_F(XMLDocumentTest_284, ParseUnclosedElement_284) {
    XMLDocument doc;
    XMLError err = doc.Parse("<root>");
    EXPECT_NE(err, XML_SUCCESS);
    EXPECT_TRUE(doc.Error());
}

TEST_F(XMLDocumentTest_284, ParseWithAttributes_284) {
    XMLDocument doc;
    XMLError err = doc.Parse("<root attr=\"value\"/>");
    EXPECT_EQ(err, XML_SUCCESS);
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    EXPECT_STREQ(root->Attribute("attr"), "value");
}

TEST_F(XMLDocumentTest_284, ParseWithText_284) {
    XMLDocument doc;
    XMLError err = doc.Parse("<root>hello</root>");
    EXPECT_EQ(err, XML_SUCCESS);
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    EXPECT_STREQ(root->GetText(), "hello");
}

TEST_F(XMLDocumentTest_284, ParseWithDeclaration_284) {
    XMLDocument doc;
    XMLError err = doc.Parse("<?xml version=\"1.0\"?><root/>");
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_FALSE(doc.Error());
}

// ============================================================
// RootElement
// ============================================================
TEST_F(XMLDocumentTest_284, RootElementReturnsCorrectElement_284) {
    XMLDocument doc;
    doc.Parse("<myroot/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    EXPECT_STREQ(root->Name(), "myroot");
}

TEST_F(XMLDocumentTest_284, RootElementNullOnEmptyDoc_284) {
    XMLDocument doc;
    EXPECT_EQ(doc.RootElement(), nullptr);
}

// ============================================================
// Error Handling
// ============================================================
TEST_F(XMLDocumentTest_284, ErrorIDReturnsSuccessOnGoodParse_284) {
    XMLDocument doc;
    doc.Parse("<root/>");
    EXPECT_EQ(doc.ErrorID(), XML_SUCCESS);
}

TEST_F(XMLDocumentTest_284, ErrorIDReturnsErrorOnBadParse_284) {
    XMLDocument doc;
    doc.Parse("<root");
    EXPECT_NE(doc.ErrorID(), XML_SUCCESS);
    EXPECT_TRUE(doc.Error());
}

TEST_F(XMLDocumentTest_284, ClearErrorResetsState_284) {
    XMLDocument doc;
    doc.Parse("<root");
    EXPECT_TRUE(doc.Error());
    doc.ClearError();
    EXPECT_FALSE(doc.Error());
    EXPECT_EQ(doc.ErrorID(), XML_SUCCESS);
}

TEST_F(XMLDocumentTest_284, ErrorNameReturnsNonNull_284) {
    XMLDocument doc;
    doc.Parse("<root");
    const char* name = doc.ErrorName();
    EXPECT_NE(name, nullptr);
}

TEST_F(XMLDocumentTest_284, ErrorStrReturnsNonNull_284) {
    XMLDocument doc;
    doc.Parse("<root");
    const char* str = doc.ErrorStr();
    EXPECT_NE(str, nullptr);
}

TEST_F(XMLDocumentTest_284, ErrorIDToName_Success_284) {
    const char* name = XMLDocument::ErrorIDToName(XML_SUCCESS);
    EXPECT_NE(name, nullptr);
    EXPECT_STREQ(name, "XML_SUCCESS");
}

TEST_F(XMLDocumentTest_284, ErrorIDToName_Various_284) {
    const char* name = XMLDocument::ErrorIDToName(XML_ERROR_FILE_NOT_FOUND);
    EXPECT_NE(name, nullptr);
}

TEST_F(XMLDocumentTest_284, ErrorLineNum_284) {
    XMLDocument doc;
    doc.Parse("<root>\n<child>\n</root>");
    EXPECT_TRUE(doc.Error());
    EXPECT_GT(doc.ErrorLineNum(), 0);
}

// ============================================================
// BOM
// ============================================================
TEST_F(XMLDocumentTest_284, SetBOMAndGet_284) {
    XMLDocument doc;
    doc.SetBOM(true);
    EXPECT_TRUE(doc.HasBOM());
    doc.SetBOM(false);
    EXPECT_FALSE(doc.HasBOM());
}

// ============================================================
// NewElement / NewComment / NewText / NewDeclaration / NewUnknown
// ============================================================
TEST_F(XMLDocumentTest_284, NewElementCreatesElement_284) {
    XMLDocument doc;
    XMLElement* elem = doc.NewElement("test");
    ASSERT_NE(elem, nullptr);
    EXPECT_STREQ(elem->Name(), "test");
    doc.DeleteNode(elem);
}

TEST_F(XMLDocumentTest_284, NewCommentCreatesComment_284) {
    XMLDocument doc;
    XMLComment* comment = doc.NewComment("a comment");
    ASSERT_NE(comment, nullptr);
    EXPECT_STREQ(comment->Value(), "a comment");
    doc.DeleteNode(comment);
}

TEST_F(XMLDocumentTest_284, NewTextCreatesText_284) {
    XMLDocument doc;
    XMLText* text = doc.NewText("hello");
    ASSERT_NE(text, nullptr);
    EXPECT_STREQ(text->Value(), "hello");
    doc.DeleteNode(text);
}

TEST_F(XMLDocumentTest_284, NewDeclarationCreatesDecl_284) {
    XMLDocument doc;
    XMLDeclaration* decl = doc.NewDeclaration();
    ASSERT_NE(decl, nullptr);
    doc.DeleteNode(decl);
}

TEST_F(XMLDocumentTest_284, NewDeclarationCustom_284) {
    XMLDocument doc;
    XMLDeclaration* decl = doc.NewDeclaration("xml version=\"1.0\"");
    ASSERT_NE(decl, nullptr);
    doc.DeleteNode(decl);
}

TEST_F(XMLDocumentTest_284, NewUnknownCreatesUnknown_284) {
    XMLDocument doc;
    XMLUnknown* unknown = doc.NewUnknown("something");
    ASSERT_NE(unknown, nullptr);
    EXPECT_STREQ(unknown->Value(), "something");
    doc.DeleteNode(unknown);
}

// ============================================================
// DeleteNode
// ============================================================
TEST_F(XMLDocumentTest_284, DeleteNodeRemovesChild_284) {
    XMLDocument doc;
    doc.Parse("<root><child/></root>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    XMLElement* child = root->FirstChildElement("child");
    ASSERT_NE(child, nullptr);
    doc.DeleteNode(child);
    EXPECT_EQ(root->FirstChildElement("child"), nullptr);
}

TEST_F(XMLDocumentTest_284, DeleteNodeNull_284) {
    XMLDocument doc;
    // Should not crash
    doc.DeleteNode(nullptr);
}

// ============================================================
// Clear
// ============================================================
TEST_F(XMLDocumentTest_284, ClearRemovesAllContent_284) {
    XMLDocument doc;
    doc.Parse("<root><child/></root>");
    EXPECT_NE(doc.RootElement(), nullptr);
    doc.Clear();
    EXPECT_EQ(doc.RootElement(), nullptr);
    EXPECT_FALSE(doc.Error());
}

// ============================================================
// DeepCopy
// ============================================================
TEST_F(XMLDocumentTest_284, DeepCopyProducesSameStructure_284) {
    XMLDocument src;
    src.Parse("<root attr=\"val\"><child>text</child></root>");
    EXPECT_FALSE(src.Error());

    XMLDocument dst;
    src.DeepCopy(&dst);
    EXPECT_FALSE(dst.Error());

    XMLElement* dstRoot = dst.RootElement();
    ASSERT_NE(dstRoot, nullptr);
    EXPECT_STREQ(dstRoot->Name(), "root");
    EXPECT_STREQ(dstRoot->Attribute("attr"), "val");

    XMLElement* dstChild = dstRoot->FirstChildElement("child");
    ASSERT_NE(dstChild, nullptr);
    EXPECT_STREQ(dstChild->GetText(), "text");
}

TEST_F(XMLDocumentTest_284, DeepCopyPreservesBOM_284) {
    XMLDocument src;
    src.Parse("<root/>");
    src.SetBOM(true);

    XMLDocument dst;
    src.DeepCopy(&dst);
    EXPECT_TRUE(dst.HasBOM());
}

// ============================================================
// Print with XMLPrinter
// ============================================================
TEST_F(XMLDocumentTest_284, PrintToXMLPrinter_284) {
    XMLDocument doc;
    doc.Parse("<root><child/></root>");
    EXPECT_FALSE(doc.Error());

    XMLPrinter printer(nullptr, false);
    doc.Print(&printer);
    const char* result = printer.CStr();
    ASSERT_NE(result, nullptr);
    EXPECT_NE(std::string(result).find("<root>"), std::string::npos);
    EXPECT_NE(std::string(result).find("</root>"), std::string::npos);
}

TEST_F(XMLDocumentTest_284, PrintCompactMode_284) {
    XMLDocument doc;
    doc.Parse("<root>\n  <child/>\n</root>");
    EXPECT_FALSE(doc.Error());

    XMLPrinter printer(nullptr, true);
    doc.Print(&printer);
    const char* result = printer.CStr();
    ASSERT_NE(result, nullptr);
    // In compact mode there should be no extra whitespace
    std::string output(result);
    EXPECT_NE(output.find("<root>"), std::string::npos);
}

TEST_F(XMLDocumentTest_284, PrintNullPrinterUsesStdout_284) {
    // This just tests it doesn't crash. Output goes to stdout.
    XMLDocument doc;
    doc.Parse("<root/>");
    // Passing nullptr should cause output to stdout (we just check no crash)
    doc.Print(nullptr);
}

// ============================================================
// Accept
// ============================================================
TEST_F(XMLDocumentTest_284, AcceptWithPrinter_284) {
    XMLDocument doc;
    doc.Parse("<root>text</root>");
    EXPECT_FALSE(doc.Error());

    XMLPrinter printer(nullptr, false);
    bool accepted = doc.Accept(&printer);
    EXPECT_TRUE(accepted);
    EXPECT_NE(std::string(printer.CStr()).find("<root>"), std::string::npos);
}

// ============================================================
// ToDocument
// ============================================================
TEST_F(XMLDocumentTest_284, ToDocumentReturnsSelf_284) {
    XMLDocument doc;
    EXPECT_EQ(doc.ToDocument(), &doc);
}

// ============================================================
// ShallowClone / ShallowEqual
// ============================================================
TEST_F(XMLDocumentTest_284, ShallowCloneReturnsNull_284) {
    XMLDocument doc;
    XMLNode* clone = doc.ShallowClone(&doc);
    EXPECT_EQ(clone, nullptr);
}

TEST_F(XMLDocumentTest_284, ShallowEqualReturnsFalse_284) {
    XMLDocument doc1;
    XMLDocument doc2;
    EXPECT_FALSE(doc1.ShallowEqual(&doc2));
}

// ============================================================
// SaveFile / LoadFile
// ============================================================
TEST_F(XMLDocumentTest_284, SaveAndLoadFile_284) {
    const char* tmpFile = "test_save_load_284.xml";

    {
        XMLDocument doc;
        doc.Parse("<root><child attr=\"1\"/></root>");
        EXPECT_FALSE(doc.Error());
        XMLError err = doc.SaveFile(tmpFile);
        EXPECT_EQ(err, XML_SUCCESS);
    }

    {
        XMLDocument doc;
        XMLError err = doc.LoadFile(tmpFile);
        EXPECT_EQ(err, XML_SUCCESS);
        EXPECT_FALSE(doc.Error());
        XMLElement* root = doc.RootElement();
        ASSERT_NE(root, nullptr);
        EXPECT_STREQ(root->Name(), "root");
    }

    std::remove(tmpFile);
}

TEST_F(XMLDocumentTest_284, SaveFileCompact_284) {
    const char* tmpFile = "test_save_compact_284.xml";

    XMLDocument doc;
    doc.Parse("<root>\n  <child/>\n</root>");
    EXPECT_FALSE(doc.Error());
    XMLError err = doc.SaveFile(tmpFile, true);
    EXPECT_EQ(err, XML_SUCCESS);

    std::remove(tmpFile);
}

TEST_F(XMLDocumentTest_284, LoadFileNonExistent_284) {
    XMLDocument doc;
    XMLError err = doc.LoadFile("nonexistent_file_284.xml");
    EXPECT_NE(err, XML_SUCCESS);
    EXPECT_TRUE(doc.Error());
}

TEST_F(XMLDocumentTest_284, SaveFileWithFILEPtr_284) {
    const char* tmpFile = "test_save_fp_284.xml";
    FILE* fp = fopen(tmpFile, "w");
    ASSERT_NE(fp, nullptr);

    XMLDocument doc;
    doc.Parse("<root/>");
    XMLError err = doc.SaveFile(fp, false);
    EXPECT_EQ(err, XML_SUCCESS);
    fclose(fp);

    // Verify by loading back
    XMLDocument doc2;
    err = doc2.LoadFile(tmpFile);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_STREQ(doc2.RootElement()->Name(), "root");

    std::remove(tmpFile);
}

TEST_F(XMLDocumentTest_284, LoadFileWithFILEPtr_284) {
    const char* tmpFile = "test_load_fp_284.xml";

    // First create the file
    {
        XMLDocument doc;
        doc.Parse("<root attr=\"hello\"/>");
        doc.SaveFile(tmpFile);
    }

    FILE* fp = fopen(tmpFile, "rb");
    ASSERT_NE(fp, nullptr);

    XMLDocument doc;
    XMLError err = doc.LoadFile(fp);
    fclose(fp);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_STREQ(doc.RootElement()->Name(), "root");
    EXPECT_STREQ(doc.RootElement()->Attribute("attr"), "hello");

    std::remove(tmpFile);
}

// ============================================================
// XMLPrinter Tests
// ============================================================
class XMLPrinterTest_284 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(XMLPrinterTest_284, OpenAndCloseElement_284) {
    XMLPrinter printer(nullptr, false);
    printer.OpenElement("test");
    printer.CloseElement();
    std::string output(printer.CStr());
    EXPECT_NE(output.find("<test"), std::string::npos);
    EXPECT_NE(output.find("</test>"), std::string::npos);
}

TEST_F(XMLPrinterTest_284, SelfClosingElement_284) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("test", true);
    printer.CloseElement(true);
    std::string output(printer.CStr());
    EXPECT_NE(output.find("<test/>"), std::string::npos);
}

TEST_F(XMLPrinterTest_284, PushAttributeString_284) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("elem", true);
    printer.PushAttribute("key", "value");
    printer.CloseElement(true);
    std::string output(printer.CStr());
    EXPECT_NE(output.find("key=\"value\""), std::string::npos);
}

TEST_F(XMLPrinterTest_284, PushAttributeInt_284) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("elem", true);
    printer.PushAttribute("num", 42);
    printer.CloseElement(true);
    std::string output(printer.CStr());
    EXPECT_NE(output.find("num=\"42\""), std::string::npos);
}

TEST_F(XMLPrinterTest_284, PushAttributeBool_284) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("elem", true);
    printer.PushAttribute("flag", true);
    printer.CloseElement(true);
    std::string output(printer.CStr());
    EXPECT_NE(output.find("flag=\"true\""), std::string::npos);
}

TEST_F(XMLPrinterTest_284, PushAttributeDouble_284) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("elem", true);
    printer.PushAttribute("val", 3.14);
    printer.CloseElement(true);
    std::string output(printer.CStr());
    EXPECT_NE(output.find("val="), std::string::npos);
}

TEST_F(XMLPrinterTest_284, PushTextString_284) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("elem", true);
    printer.PushText("hello world");
    printer.CloseElement(true);
    std::string output(printer.CStr());
    EXPECT_NE(output.find("hello world"), std::string::npos);
}

TEST_F(XMLPrinterTest_284, PushTextInt_284) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("elem", true);
    printer.PushText(123);
    printer.CloseElement(true);
    std::string output(printer.CStr());
    EXPECT_NE(output.find("123"), std::string::npos);
}

TEST_F(XMLPrinterTest_284, PushTextBool_284) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("elem", true);
    printer.PushText(true);
    printer.CloseElement(true);
    std::string output(printer.CStr());
    EXPECT_NE(output.find("true"), std::string::npos);
}

TEST_F(XMLPrinterTest_284, PushComment_284) {
    XMLPrinter printer(nullptr, false);
    printer.PushComment("this is a comment");
    std::string output(printer.CStr());
    EXPECT_NE(output.find("<!--this is a comment-->"), std::string::npos);
}

TEST_F(XMLPrinterTest_284, PushDeclaration_284) {
    XMLPrinter printer(nullptr, false);
    printer.PushDeclaration("xml version=\"1.0\"");
    std::string output(printer.CStr());
    EXPECT_NE(output.find("<?xml version=\"1.0\"?>"), std::string::npos);
}

TEST_F(XMLPrinterTest_284, PushUnknown_284) {
    XMLPrinter printer(nullptr, false);
    printer.PushUnknown("DOCTYPE html");
    std::string output(printer.CStr());
    EXPECT_NE(output.find("<!DOCTYPE html>"), std::string::npos);
}

TEST_F(XMLPrinterTest_284, CStrSizeNonZero_284) {
    XMLPrinter printer(nullptr, false);
    printer.OpenElement("test");
    printer.CloseElement();
    EXPECT_GT(printer.CStrSize(), static_cast<size_t>(0));
}

TEST_F(XMLPrinterTest_284, ClearBuffer_284) {
    XMLPrinter printer(nullptr, false);
    printer.OpenElement("test");
    printer.CloseElement();
    EXPECT_GT(printer.CStrSize(), static_cast<size_t>(0));
    printer.ClearBuffer();
    // After clearing, CStr should be essentially empty (or minimal)
    // CStrSize includes the null terminator
    EXPECT_LE(printer.CStrSize(), static_cast<size_t>(1));
}

TEST_F(XMLPrinterTest_284, PushHeader_284) {
    XMLPrinter printer(nullptr, false);
    printer.PushHeader(false, true);
    std::string output(printer.CStr());
    EXPECT_NE(output.find("<?xml"), std::string::npos);
}

TEST_F(XMLPrinterTest_284, PushHeaderWithBOM_284) {
    XMLPrinter printer(nullptr, false);
    printer.PushHeader(true, true);
    const char* result = printer.CStr();
    ASSERT_NE(result, nullptr);
    // BOM is 3 bytes: 0xEF, 0xBB, 0xBF
    EXPECT_EQ(static_cast<unsigned char>(result[0]), 0xEF);
    EXPECT_EQ(static_cast<unsigned char>(result[1]), 0xBB);
    EXPECT_EQ(static_cast<unsigned char>(result[2]), 0xBF);
}

TEST_F(XMLPrinterTest_284, NestedElements_284) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("parent", true);
    printer.OpenElement("child", true);
    printer.PushText("data");
    printer.CloseElement(true);
    printer.CloseElement(true);
    std::string output(printer.CStr());
    EXPECT_NE(output.find("<parent>"), std::string::npos);
    EXPECT_NE(output.find("<child>"), std::string::npos);
    EXPECT_NE(output.find("data"), std::string::npos);
    EXPECT_NE(output.find("</child>"), std::string::npos);
    EXPECT_NE(output.find("</parent>"), std::string::npos);
}

// ============================================================
// Complex Document Tests
// ============================================================
TEST_F(XMLDocumentTest_284, ParseComplexDocument_284) {
    const char* xml =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>"
        "<catalog>"
        "  <book id=\"1\">"
        "    <title>Test Book</title>"
        "    <author>Author Name</author>"
        "  </book>"
        "  <book id=\"2\">"
        "    <title>Another Book</title>"
        "  </book>"
        "</catalog>";

    XMLDocument doc;
    XMLError err = doc.Parse(xml);
    EXPECT_EQ(err, XML_SUCCESS);

    XMLElement* catalog = doc.RootElement();
    ASSERT_NE(catalog, nullptr);
    EXPECT_STREQ(catalog->Name(), "catalog");

    XMLElement* book1 = catalog->FirstChildElement("book");
    ASSERT_NE(book1, nullptr);
    EXPECT_STREQ(book1->Attribute("id"), "1");

    XMLElement* title1 = book1->FirstChildElement("title");
    ASSERT_NE(title1, nullptr);
    EXPECT_STREQ(title1->GetText(), "Test Book");

    XMLElement* book2 = book1->NextSiblingElement("book");
    ASSERT_NE(book2, nullptr);
    EXPECT_STREQ(book2->Attribute("id"), "2");
}

TEST_F(XMLDocumentTest_284, ParseMultipleTimesResets_284) {
    XMLDocument doc;
    doc.Parse("<first/>");
    EXPECT_STREQ(doc.RootElement()->Name(), "first");

    doc.Parse("<second/>");
    EXPECT_STREQ(doc.RootElement()->Name(), "second");
}

TEST_F(XMLDocumentTest_284, InsertNewElementAsChild_284) {
    XMLDocument doc;
    doc.Parse("<root/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);

    XMLElement* child = doc.NewElement("child");
    root->InsertEndChild(child);

    XMLPrinter printer(nullptr, true);
    doc.Print(&printer);
    std::string output(printer.CStr());
    EXPECT_NE(output.find("<child/>"), std::string::npos);
}

TEST_F(XMLDocumentTest_284, PrintErrorDoesNotCrash_284) {
    XMLDocument doc;
    doc.Parse("<root");
    EXPECT_TRUE(doc.Error());
    // Just verify it doesn't crash
    doc.PrintError();
}

TEST_F(XMLDocumentTest_284, ClearErrorAfterBadParseThenReparse_284) {
    XMLDocument doc;
    doc.Parse("<bad");
    EXPECT_TRUE(doc.Error());
    
    XMLError err = doc.Parse("<good/>");
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_FALSE(doc.Error());
    EXPECT_STREQ(doc.RootElement()->Name(), "good");
}

TEST_F(XMLDocumentTest_284, PushTextCDATA_284) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("elem", true);
    printer.PushText("data with <special> chars", true);
    printer.CloseElement(true);
    std::string output(printer.CStr());
    EXPECT_NE(output.find("<![CDATA["), std::string::npos);
    EXPECT_NE(output.find("]]>"), std::string::npos);
}

TEST_F(XMLDocumentTest_284, PushAttributeInt64_284) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("elem", true);
    int64_t bigVal = 9223372036854775807LL;
    printer.PushAttribute("big", bigVal);
    printer.CloseElement(true);
    std::string output(printer.CStr());
    EXPECT_NE(output.find("9223372036854775807"), std::string::npos);
}

TEST_F(XMLDocumentTest_284, PushAttributeUnsigned_284) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("elem", true);
    printer.PushAttribute("val", (unsigned int)4294967295U);
    printer.CloseElement(true);
    std::string output(printer.CStr());
    EXPECT_NE(output.find("4294967295"), std::string::npos);
}

TEST_F(XMLDocumentTest_284, PushTextFloat_284) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("elem", true);
    printer.PushText(1.5f);
    printer.CloseElement(true);
    std::string output(printer.CStr());
    EXPECT_NE(output.find("1.5"), std::string::npos);
}

TEST_F(XMLDocumentTest_284, PushTextDouble_284) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("elem", true);
    printer.PushText(2.718281828);
    printer.CloseElement(true);
    std::string output(printer.CStr());
    EXPECT_NE(output.find("2.71"), std::string::npos);
}

TEST_F(XMLDocumentTest_284, MarkInUseDoesNotCrash_284) {
    XMLDocument doc;
    doc.Parse("<root><child/></root>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    // MarkInUse should not crash
    doc.MarkInUse(root);
}

TEST_F(XMLDocumentTest_284, DeepCopyEmptyDocument_284) {
    XMLDocument src;
    XMLDocument dst;
    src.DeepCopy(&dst);
    EXPECT_EQ(dst.RootElement(), nullptr);
    EXPECT_FALSE(dst.Error());
}

TEST_F(XMLDocumentTest_284, NewElementNullName_284) {
    XMLDocument doc;
    XMLElement* elem = doc.NewElement(nullptr);
    // Behavior may vary, just check no crash
    // Some implementations may return an element with empty name
    if (elem) {
        doc.DeleteNode(elem);
    }
}

TEST_F(XMLDocumentTest_284, ParseWithEntityProcessing_284) {
    XMLDocument doc(true);
    XMLError err = doc.Parse("<root>&amp;</root>");
    EXPECT_EQ(err, XML_SUCCESS);
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    EXPECT_STREQ(root->GetText(), "&");
}

TEST_F(XMLDocumentTest_284, ParseWithoutEntityProcessing_284) {
    XMLDocument doc(false);
    XMLError err = doc.Parse("<root>&amp;</root>");
    EXPECT_EQ(err, XML_SUCCESS);
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    // Without entity processing, the raw text should be preserved
    EXPECT_STREQ(root->GetText(), "&amp;");
}
