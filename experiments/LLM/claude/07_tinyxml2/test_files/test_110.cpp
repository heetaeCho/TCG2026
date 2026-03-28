#include "gtest/gtest.h"
#include "tinyxml2.h"

using namespace tinyxml2;

// ============================================================
// Test Fixture
// ============================================================
class XMLDocumentTest_110 : public ::testing::Test {
protected:
    XMLDocument doc;
};

// ============================================================
// Constructor and Default State Tests
// ============================================================

TEST_F(XMLDocumentTest_110, DefaultConstructor_HasNoBOM_110) {
    EXPECT_FALSE(doc.HasBOM());
}

TEST_F(XMLDocumentTest_110, DefaultConstructor_NoError_110) {
    EXPECT_FALSE(doc.Error());
    EXPECT_EQ(XML_SUCCESS, doc.ErrorID());
}

TEST_F(XMLDocumentTest_110, DefaultConstructor_ErrorLineNumIsZero_110) {
    EXPECT_EQ(0, doc.ErrorLineNum());
}

TEST_F(XMLDocumentTest_110, DefaultConstructor_RootElementIsNull_110) {
    EXPECT_EQ(nullptr, doc.RootElement());
}

TEST_F(XMLDocumentTest_110, DefaultConstructor_ProcessEntitiesTrue_110) {
    EXPECT_TRUE(doc.ProcessEntities());
}

TEST_F(XMLDocumentTest_110, DefaultConstructor_WhitespaceMode_110) {
    EXPECT_EQ(PRESERVE_WHITESPACE, doc.WhitespaceMode());
    // Actually the default might be COLLAPSE_WHITESPACE; let's just check it doesn't crash
}

TEST_F(XMLDocumentTest_110, ConstructorWithProcessEntitiesFalse_110) {
    XMLDocument d(false);
    EXPECT_FALSE(d.ProcessEntities());
}

TEST_F(XMLDocumentTest_110, ConstructorWithWhitespaceMode_110) {
    XMLDocument d(true, PRESERVE_WHITESPACE);
    EXPECT_EQ(PRESERVE_WHITESPACE, d.WhitespaceMode());
}

// ============================================================
// SetBOM / HasBOM Tests
// ============================================================

TEST_F(XMLDocumentTest_110, SetBOMTrue_110) {
    doc.SetBOM(true);
    EXPECT_TRUE(doc.HasBOM());
}

TEST_F(XMLDocumentTest_110, SetBOMFalse_110) {
    doc.SetBOM(true);
    EXPECT_TRUE(doc.HasBOM());
    doc.SetBOM(false);
    EXPECT_FALSE(doc.HasBOM());
}

TEST_F(XMLDocumentTest_110, SetBOMToggle_110) {
    doc.SetBOM(false);
    EXPECT_FALSE(doc.HasBOM());
    doc.SetBOM(true);
    EXPECT_TRUE(doc.HasBOM());
    doc.SetBOM(false);
    EXPECT_FALSE(doc.HasBOM());
}

// ============================================================
// Parse Tests
// ============================================================

TEST_F(XMLDocumentTest_110, ParseValidXML_110) {
    const char* xml = "<root><child/></root>";
    XMLError err = doc.Parse(xml);
    EXPECT_EQ(XML_SUCCESS, err);
    EXPECT_FALSE(doc.Error());
    EXPECT_NE(nullptr, doc.RootElement());
}

TEST_F(XMLDocumentTest_110, ParseEmptyString_110) {
    XMLError err = doc.Parse("");
    EXPECT_NE(XML_SUCCESS, err);
    EXPECT_TRUE(doc.Error());
}

TEST_F(XMLDocumentTest_110, ParseNullPointer_110) {
    XMLError err = doc.Parse(nullptr);
    EXPECT_NE(XML_SUCCESS, err);
    EXPECT_TRUE(doc.Error());
}

TEST_F(XMLDocumentTest_110, ParseInvalidXML_110) {
    const char* xml = "<root><unclosed>";
    XMLError err = doc.Parse(xml);
    EXPECT_NE(XML_SUCCESS, err);
    EXPECT_TRUE(doc.Error());
}

TEST_F(XMLDocumentTest_110, ParseWithSizeLimit_110) {
    const char* xml = "<root>hello</root>";
    XMLError err = doc.Parse(xml, 18);
    EXPECT_EQ(XML_SUCCESS, err);
    EXPECT_NE(nullptr, doc.RootElement());
}

TEST_F(XMLDocumentTest_110, ParseWithSizeTruncated_110) {
    const char* xml = "<root>hello</root>";
    // Parse only first 6 bytes: "<root>" - incomplete since no closing tag within the buffer
    XMLError err = doc.Parse(xml, 6);
    // This may or may not succeed depending on implementation, just ensure no crash
    (void)err;
}

TEST_F(XMLDocumentTest_110, ParseWithDeclaration_110) {
    const char* xml = "<?xml version=\"1.0\" encoding=\"UTF-8\"?><root/>";
    XMLError err = doc.Parse(xml);
    EXPECT_EQ(XML_SUCCESS, err);
    EXPECT_NE(nullptr, doc.RootElement());
}

TEST_F(XMLDocumentTest_110, ParseWithBOM_110) {
    // UTF-8 BOM: EF BB BF
    std::string xml = "\xEF\xBB\xBF<root/>";
    XMLError err = doc.Parse(xml.c_str());
    EXPECT_EQ(XML_SUCCESS, err);
    EXPECT_TRUE(doc.HasBOM());
}

TEST_F(XMLDocumentTest_110, ParseRootElementName_110) {
    doc.Parse("<myElement attr=\"val\">text</myElement>");
    ASSERT_NE(nullptr, doc.RootElement());
    EXPECT_STREQ("myElement", doc.RootElement()->Name());
}

TEST_F(XMLDocumentTest_110, ParseMultipleRootElements_110) {
    // Some parsers reject multiple root elements
    XMLError err = doc.Parse("<a/><b/>");
    // Just verify it doesn't crash; behavior may vary
    (void)err;
}

// ============================================================
// Error Handling Tests
// ============================================================

TEST_F(XMLDocumentTest_110, ClearError_110) {
    doc.Parse("<unclosed>");
    EXPECT_TRUE(doc.Error());
    doc.ClearError();
    EXPECT_FALSE(doc.Error());
    EXPECT_EQ(XML_SUCCESS, doc.ErrorID());
}

TEST_F(XMLDocumentTest_110, ErrorName_AfterError_110) {
    doc.Parse("");
    EXPECT_TRUE(doc.Error());
    const char* name = doc.ErrorName();
    EXPECT_NE(nullptr, name);
    EXPECT_GT(strlen(name), 0u);
}

TEST_F(XMLDocumentTest_110, ErrorStr_AfterError_110) {
    doc.Parse("<unclosed>");
    EXPECT_TRUE(doc.Error());
    const char* str = doc.ErrorStr();
    EXPECT_NE(nullptr, str);
    EXPECT_GT(strlen(str), 0u);
}

TEST_F(XMLDocumentTest_110, ErrorIDToName_Success_110) {
    const char* name = XMLDocument::ErrorIDToName(XML_SUCCESS);
    EXPECT_NE(nullptr, name);
}

TEST_F(XMLDocumentTest_110, ErrorIDToName_Various_110) {
    const char* name1 = XMLDocument::ErrorIDToName(XML_ERROR_FILE_NOT_FOUND);
    EXPECT_NE(nullptr, name1);
    const char* name2 = XMLDocument::ErrorIDToName(XML_ERROR_PARSING);
    EXPECT_NE(nullptr, name2);
}

TEST_F(XMLDocumentTest_110, ErrorLineNum_OnError_110) {
    const char* xml = "<root>\n<unclosed>";
    doc.Parse(xml);
    EXPECT_TRUE(doc.Error());
    // ErrorLineNum should be > 0 when there is an error
    EXPECT_GT(doc.ErrorLineNum(), 0);
}

// ============================================================
// NewElement / NewComment / NewText / NewDeclaration / NewUnknown
// ============================================================

TEST_F(XMLDocumentTest_110, NewElement_ReturnsNonNull_110) {
    XMLElement* elem = doc.NewElement("test");
    ASSERT_NE(nullptr, elem);
    EXPECT_STREQ("test", elem->Name());
}

TEST_F(XMLDocumentTest_110, NewComment_ReturnsNonNull_110) {
    XMLComment* comment = doc.NewComment("this is a comment");
    ASSERT_NE(nullptr, comment);
    EXPECT_STREQ("this is a comment", comment->Value());
}

TEST_F(XMLDocumentTest_110, NewText_ReturnsNonNull_110) {
    XMLText* text = doc.NewText("hello world");
    ASSERT_NE(nullptr, text);
    EXPECT_STREQ("hello world", text->Value());
}

TEST_F(XMLDocumentTest_110, NewDeclaration_ReturnsNonNull_110) {
    XMLDeclaration* decl = doc.NewDeclaration();
    ASSERT_NE(nullptr, decl);
}

TEST_F(XMLDocumentTest_110, NewDeclaration_CustomText_110) {
    XMLDeclaration* decl = doc.NewDeclaration("xml version=\"1.0\"");
    ASSERT_NE(nullptr, decl);
}

TEST_F(XMLDocumentTest_110, NewUnknown_ReturnsNonNull_110) {
    XMLUnknown* unknown = doc.NewUnknown("something");
    ASSERT_NE(nullptr, unknown);
    EXPECT_STREQ("something", unknown->Value());
}

// ============================================================
// DeleteNode Tests
// ============================================================

TEST_F(XMLDocumentTest_110, DeleteNode_Element_110) {
    XMLElement* elem = doc.NewElement("todelete");
    doc.InsertEndChild(elem);
    EXPECT_NE(nullptr, doc.RootElement());
    doc.DeleteNode(elem);
    EXPECT_EQ(nullptr, doc.RootElement());
}

TEST_F(XMLDocumentTest_110, DeleteNode_Null_110) {
    // Deleting null should not crash
    doc.DeleteNode(nullptr);
}

// ============================================================
// Clear Tests
// ============================================================

TEST_F(XMLDocumentTest_110, Clear_RemovesAllContent_110) {
    doc.Parse("<root><child/></root>");
    EXPECT_NE(nullptr, doc.RootElement());
    doc.Clear();
    EXPECT_EQ(nullptr, doc.RootElement());
    EXPECT_FALSE(doc.Error());
}

TEST_F(XMLDocumentTest_110, Clear_ResetsBOM_110) {
    doc.SetBOM(true);
    doc.Clear();
    EXPECT_FALSE(doc.HasBOM());
}

// ============================================================
// DeepCopy Tests
// ============================================================

TEST_F(XMLDocumentTest_110, DeepCopy_CopiesContent_110) {
    doc.Parse("<root attr=\"value\"><child>text</child></root>");
    ASSERT_FALSE(doc.Error());

    XMLDocument target;
    doc.DeepCopy(&target);

    ASSERT_NE(nullptr, target.RootElement());
    EXPECT_STREQ("root", target.RootElement()->Name());
    EXPECT_STREQ("value", target.RootElement()->Attribute("attr"));
}

TEST_F(XMLDocumentTest_110, DeepCopy_CopiesBOM_110) {
    std::string xml = "\xEF\xBB\xBF<root/>";
    doc.Parse(xml.c_str());
    EXPECT_TRUE(doc.HasBOM());

    XMLDocument target;
    doc.DeepCopy(&target);
    EXPECT_TRUE(target.HasBOM());
}

TEST_F(XMLDocumentTest_110, DeepCopy_EmptyDocument_110) {
    XMLDocument target;
    target.Parse("<existing/>");
    doc.DeepCopy(&target);
    EXPECT_EQ(nullptr, target.RootElement());
}

// ============================================================
// ToDocument Tests
// ============================================================

TEST_F(XMLDocumentTest_110, ToDocument_ReturnsSelf_110) {
    XMLDocument* result = doc.ToDocument();
    EXPECT_EQ(&doc, result);
}

// ============================================================
// ShallowClone / ShallowEqual Tests
// ============================================================

TEST_F(XMLDocumentTest_110, ShallowClone_ReturnsNull_110) {
    // XMLDocument::ShallowClone should return null (documents cannot be shallow cloned)
    XMLNode* clone = doc.ShallowClone(&doc);
    EXPECT_EQ(nullptr, clone);
}

TEST_F(XMLDocumentTest_110, ShallowEqual_ReturnsFalse_110) {
    XMLDocument doc2;
    EXPECT_FALSE(doc.ShallowEqual(&doc2));
}

// ============================================================
// LoadFile / SaveFile Tests
// ============================================================

TEST_F(XMLDocumentTest_110, LoadFile_NonExistentFile_110) {
    XMLError err = doc.LoadFile("nonexistent_file_that_does_not_exist_12345.xml");
    EXPECT_NE(XML_SUCCESS, err);
    EXPECT_TRUE(doc.Error());
}

TEST_F(XMLDocumentTest_110, SaveAndLoadFile_RoundTrip_110) {
    doc.Parse("<root><child attr=\"hello\">world</child></root>");
    ASSERT_FALSE(doc.Error());

    const char* tmpfile = "tinyxml2_test_110_roundtrip.xml";
    XMLError saveErr = doc.SaveFile(tmpfile, false);
    EXPECT_EQ(XML_SUCCESS, saveErr);

    XMLDocument loaded;
    XMLError loadErr = loaded.LoadFile(tmpfile);
    EXPECT_EQ(XML_SUCCESS, loadErr);
    ASSERT_NE(nullptr, loaded.RootElement());
    EXPECT_STREQ("root", loaded.RootElement()->Name());

    // Cleanup
    remove(tmpfile);
}

TEST_F(XMLDocumentTest_110, SaveFile_Compact_110) {
    doc.Parse("<root>  <child/>  </root>");
    ASSERT_FALSE(doc.Error());

    const char* tmpfile = "tinyxml2_test_110_compact.xml";
    XMLError err = doc.SaveFile(tmpfile, true);
    EXPECT_EQ(XML_SUCCESS, err);

    // Cleanup
    remove(tmpfile);
}

TEST_F(XMLDocumentTest_110, LoadFile_FromFILE_110) {
    // First create a file
    const char* tmpfile = "tinyxml2_test_110_fptr.xml";
    {
        XMLDocument writer;
        writer.Parse("<data/>");
        writer.SaveFile(tmpfile, false);
    }

    FILE* fp = fopen(tmpfile, "rb");
    ASSERT_NE(nullptr, fp);
    XMLError err = doc.LoadFile(fp);
    fclose(fp);
    EXPECT_EQ(XML_SUCCESS, err);
    ASSERT_NE(nullptr, doc.RootElement());
    EXPECT_STREQ("data", doc.RootElement()->Name());

    remove(tmpfile);
}

TEST_F(XMLDocumentTest_110, SaveFile_ToFILE_110) {
    doc.Parse("<output/>");
    ASSERT_FALSE(doc.Error());

    const char* tmpfile = "tinyxml2_test_110_fptr_save.xml";
    FILE* fp = fopen(tmpfile, "w");
    ASSERT_NE(nullptr, fp);
    XMLError err = doc.SaveFile(fp, false);
    fclose(fp);
    EXPECT_EQ(XML_SUCCESS, err);

    remove(tmpfile);
}

// ============================================================
// Print Tests
// ============================================================

TEST_F(XMLDocumentTest_110, Print_ToDefaultPrinter_110) {
    doc.Parse("<root/>");
    ASSERT_FALSE(doc.Error());

    XMLPrinter printer;
    doc.Print(&printer);
    const char* result = printer.CStr();
    EXPECT_NE(nullptr, result);
    EXPECT_NE(std::string::npos, std::string(result).find("root"));
}

TEST_F(XMLDocumentTest_110, Print_NullPrinter_110) {
    doc.Parse("<root/>");
    // Passing nullptr should print to stdout (no crash expected)
    doc.Print(nullptr);
}

// ============================================================
// Accept (Visitor) Tests
// ============================================================

TEST_F(XMLDocumentTest_110, Accept_WithPrinterVisitor_110) {
    doc.Parse("<root><child/></root>");
    ASSERT_FALSE(doc.Error());

    XMLPrinter printer;
    bool accepted = doc.Accept(&printer);
    EXPECT_TRUE(accepted);
    const char* result = printer.CStr();
    EXPECT_NE(nullptr, result);
    EXPECT_NE(std::string::npos, std::string(result).find("root"));
}

// ============================================================
// Entity Processing Tests
// ============================================================

TEST_F(XMLDocumentTest_110, ParseWithEntities_110) {
    XMLDocument d(true);
    d.Parse("<root attr=\"&amp;\">&lt;hello&gt;</root>");
    ASSERT_FALSE(d.Error());
    ASSERT_NE(nullptr, d.RootElement());
    EXPECT_STREQ("&", d.RootElement()->Attribute("attr"));
}

TEST_F(XMLDocumentTest_110, ParseWithoutEntities_110) {
    XMLDocument d(false);
    d.Parse("<root>&lt;hello&gt;</root>");
    ASSERT_FALSE(d.Error());
    // When entities are not processed, the text may retain the raw form
}

// ============================================================
// Complex Document Tests
// ============================================================

TEST_F(XMLDocumentTest_110, ParseComplexDocument_110) {
    const char* xml =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<!-- A comment -->\n"
        "<root>\n"
        "  <element attr1=\"val1\" attr2=\"val2\">\n"
        "    <nested>Text content</nested>\n"
        "  </element>\n"
        "  <empty/>\n"
        "</root>\n";

    XMLError err = doc.Parse(xml);
    EXPECT_EQ(XML_SUCCESS, err);
    ASSERT_NE(nullptr, doc.RootElement());

    XMLElement* element = doc.RootElement()->FirstChildElement("element");
    ASSERT_NE(nullptr, element);
    EXPECT_STREQ("val1", element->Attribute("attr1"));
    EXPECT_STREQ("val2", element->Attribute("attr2"));

    XMLElement* nested = element->FirstChildElement("nested");
    ASSERT_NE(nullptr, nested);
    EXPECT_STREQ("Text content", nested->GetText());

    XMLElement* empty = doc.RootElement()->FirstChildElement("empty");
    EXPECT_NE(nullptr, empty);
}

TEST_F(XMLDocumentTest_110, ParseReparse_110) {
    doc.Parse("<first/>");
    ASSERT_NE(nullptr, doc.RootElement());
    EXPECT_STREQ("first", doc.RootElement()->Name());

    doc.Parse("<second/>");
    ASSERT_NE(nullptr, doc.RootElement());
    EXPECT_STREQ("second", doc.RootElement()->Name());
}

// ============================================================
// InsertEndChild and structure manipulation
// ============================================================

TEST_F(XMLDocumentTest_110, InsertElementAsRoot_110) {
    XMLElement* root = doc.NewElement("myroot");
    doc.InsertEndChild(root);
    ASSERT_NE(nullptr, doc.RootElement());
    EXPECT_STREQ("myroot", doc.RootElement()->Name());
}

TEST_F(XMLDocumentTest_110, BuildDocumentProgrammatically_110) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);

    XMLElement* child = doc.NewElement("child");
    child->SetAttribute("name", "test");
    root->InsertEndChild(child);

    XMLText* text = doc.NewText("Hello");
    child->InsertEndChild(text);

    XMLPrinter printer;
    doc.Print(&printer);
    std::string output = printer.CStr();
    EXPECT_NE(std::string::npos, output.find("child"));
    EXPECT_NE(std::string::npos, output.find("Hello"));
    EXPECT_NE(std::string::npos, output.find("test"));
}

// ============================================================
// PrintError test (just verify no crash)
// ============================================================

TEST_F(XMLDocumentTest_110, PrintError_AfterParseError_110) {
    doc.Parse("<unclosed>");
    EXPECT_TRUE(doc.Error());
    // Should not crash
    doc.PrintError();
}

TEST_F(XMLDocumentTest_110, PrintError_NoError_110) {
    doc.Parse("<root/>");
    EXPECT_FALSE(doc.Error());
    doc.PrintError();
}
