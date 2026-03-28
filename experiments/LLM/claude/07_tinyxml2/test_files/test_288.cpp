#include "gtest/gtest.h"
#include "tinyxml2.h"

using namespace tinyxml2;

// ============================================================
// Test Fixture
// ============================================================

class XMLDocumentTest_288 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// ============================================================
// Construction Tests
// ============================================================

TEST_F(XMLDocumentTest_288, DefaultConstruction_288) {
    XMLDocument doc;
    EXPECT_FALSE(doc.Error());
    EXPECT_EQ(doc.ErrorID(), XML_SUCCESS);
    EXPECT_FALSE(doc.HasBOM());
    EXPECT_TRUE(doc.ProcessEntities());
    EXPECT_EQ(doc.RootElement(), nullptr);
    EXPECT_EQ(doc.ErrorLineNum(), 0);
}

TEST_F(XMLDocumentTest_288, ConstructWithoutProcessEntities_288) {
    XMLDocument doc(false);
    EXPECT_FALSE(doc.ProcessEntities());
    EXPECT_FALSE(doc.Error());
}

TEST_F(XMLDocumentTest_288, ConstructWithWhitespaceMode_288) {
    XMLDocument doc(true, PRESERVE_WHITESPACE);
    EXPECT_EQ(doc.WhitespaceMode(), PRESERVE_WHITESPACE);
}

TEST_F(XMLDocumentTest_288, ConstructWithCollapseWhitespace_288) {
    XMLDocument doc(true, COLLAPSE_WHITESPACE);
    EXPECT_EQ(doc.WhitespaceMode(), COLLAPSE_WHITESPACE);
}

// ============================================================
// Parse Tests
// ============================================================

TEST_F(XMLDocumentTest_288, ParseSimpleXML_288) {
    XMLDocument doc;
    XMLError err = doc.Parse("<root/>");
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_FALSE(doc.Error());
    EXPECT_NE(doc.RootElement(), nullptr);
    EXPECT_STREQ(doc.RootElement()->Name(), "root");
}

TEST_F(XMLDocumentTest_288, ParseXMLWithChildren_288) {
    XMLDocument doc;
    XMLError err = doc.Parse("<root><child/></root>");
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_NE(doc.RootElement(), nullptr);
    EXPECT_NE(doc.RootElement()->FirstChildElement("child"), nullptr);
}

TEST_F(XMLDocumentTest_288, ParseXMLWithAttributes_288) {
    XMLDocument doc;
    XMLError err = doc.Parse("<root attr=\"value\"/>");
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_NE(doc.RootElement(), nullptr);
    EXPECT_STREQ(doc.RootElement()->Attribute("attr"), "value");
}

TEST_F(XMLDocumentTest_288, ParseXMLWithText_288) {
    XMLDocument doc;
    XMLError err = doc.Parse("<root>Hello World</root>");
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_NE(doc.RootElement(), nullptr);
    EXPECT_STREQ(doc.RootElement()->GetText(), "Hello World");
}

TEST_F(XMLDocumentTest_288, ParseEmptyString_288) {
    XMLDocument doc;
    XMLError err = doc.Parse("");
    EXPECT_NE(err, XML_SUCCESS);
    EXPECT_TRUE(doc.Error());
}

TEST_F(XMLDocumentTest_288, ParseNullString_288) {
    XMLDocument doc;
    XMLError err = doc.Parse(nullptr);
    EXPECT_NE(err, XML_SUCCESS);
    EXPECT_TRUE(doc.Error());
}

TEST_F(XMLDocumentTest_288, ParseMalformedXML_288) {
    XMLDocument doc;
    XMLError err = doc.Parse("<root><unclosed>");
    EXPECT_NE(err, XML_SUCCESS);
    EXPECT_TRUE(doc.Error());
}

TEST_F(XMLDocumentTest_288, ParseWithSpecificLength_288) {
    XMLDocument doc;
    const char* xml = "<root/>extra garbage";
    XMLError err = doc.Parse(xml, 7); // only "<root/>"
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_NE(doc.RootElement(), nullptr);
    EXPECT_STREQ(doc.RootElement()->Name(), "root");
}

TEST_F(XMLDocumentTest_288, ParseWithDeclaration_288) {
    XMLDocument doc;
    XMLError err = doc.Parse("<?xml version=\"1.0\"?><root/>");
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_NE(doc.RootElement(), nullptr);
}

TEST_F(XMLDocumentTest_288, ParseWithComment_288) {
    XMLDocument doc;
    XMLError err = doc.Parse("<!-- comment --><root/>");
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_NE(doc.RootElement(), nullptr);
}

TEST_F(XMLDocumentTest_288, ParseMismatchedTags_288) {
    XMLDocument doc;
    XMLError err = doc.Parse("<root></mismatch>");
    EXPECT_NE(err, XML_SUCCESS);
    EXPECT_TRUE(doc.Error());
}

// ============================================================
// Error Handling Tests
// ============================================================

TEST_F(XMLDocumentTest_288, ErrorIDAfterSuccessfulParse_288) {
    XMLDocument doc;
    doc.Parse("<root/>");
    EXPECT_EQ(doc.ErrorID(), XML_SUCCESS);
}

TEST_F(XMLDocumentTest_288, ErrorIDAfterFailedParse_288) {
    XMLDocument doc;
    doc.Parse("<>");
    EXPECT_NE(doc.ErrorID(), XML_SUCCESS);
    EXPECT_TRUE(doc.Error());
}

TEST_F(XMLDocumentTest_288, ClearError_288) {
    XMLDocument doc;
    doc.Parse("<>");
    EXPECT_TRUE(doc.Error());
    doc.ClearError();
    EXPECT_FALSE(doc.Error());
    EXPECT_EQ(doc.ErrorID(), XML_SUCCESS);
}

TEST_F(XMLDocumentTest_288, ErrorStr_288) {
    XMLDocument doc;
    doc.Parse("<>");
    EXPECT_TRUE(doc.Error());
    const char* errStr = doc.ErrorStr();
    EXPECT_NE(errStr, nullptr);
    EXPECT_GT(strlen(errStr), 0u);
}

TEST_F(XMLDocumentTest_288, ErrorName_288) {
    XMLDocument doc;
    doc.Parse("<>");
    const char* errName = doc.ErrorName();
    EXPECT_NE(errName, nullptr);
    EXPECT_GT(strlen(errName), 0u);
}

TEST_F(XMLDocumentTest_288, ErrorLineNum_288) {
    XMLDocument doc;
    doc.Parse("<root>\n<></root>");
    EXPECT_TRUE(doc.Error());
    EXPECT_GT(doc.ErrorLineNum(), 0);
}

TEST_F(XMLDocumentTest_288, ErrorIDToName_288) {
    const char* name = XMLDocument::ErrorIDToName(XML_SUCCESS);
    EXPECT_NE(name, nullptr);
    EXPECT_STREQ(name, "XML_SUCCESS");
}

TEST_F(XMLDocumentTest_288, ErrorIDToNameForError_288) {
    const char* name = XMLDocument::ErrorIDToName(XML_ERROR_FILE_NOT_FOUND);
    EXPECT_NE(name, nullptr);
    EXPECT_GT(strlen(name), 0u);
}

// ============================================================
// BOM Tests
// ============================================================

TEST_F(XMLDocumentTest_288, SetBOMTrue_288) {
    XMLDocument doc;
    doc.SetBOM(true);
    EXPECT_TRUE(doc.HasBOM());
}

TEST_F(XMLDocumentTest_288, SetBOMFalse_288) {
    XMLDocument doc;
    doc.SetBOM(false);
    EXPECT_FALSE(doc.HasBOM());
}

// ============================================================
// NewElement Tests
// ============================================================

TEST_F(XMLDocumentTest_288, NewElement_288) {
    XMLDocument doc;
    XMLElement* elem = doc.NewElement("test");
    EXPECT_NE(elem, nullptr);
    EXPECT_STREQ(elem->Name(), "test");
}

TEST_F(XMLDocumentTest_288, NewElementAndInsert_288) {
    XMLDocument doc;
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);
    EXPECT_NE(doc.RootElement(), nullptr);
    EXPECT_STREQ(doc.RootElement()->Name(), "root");
}

// ============================================================
// NewComment Tests
// ============================================================

TEST_F(XMLDocumentTest_288, NewComment_288) {
    XMLDocument doc;
    XMLComment* comment = doc.NewComment("This is a comment");
    EXPECT_NE(comment, nullptr);
}

TEST_F(XMLDocumentTest_288, NewCommentInserted_288) {
    XMLDocument doc;
    XMLComment* comment = doc.NewComment("test comment");
    doc.InsertEndChild(comment);
    EXPECT_NE(doc.FirstChild(), nullptr);
}

// ============================================================
// NewText Tests
// ============================================================

TEST_F(XMLDocumentTest_288, NewText_288) {
    XMLDocument doc;
    XMLText* text = doc.NewText("Hello");
    EXPECT_NE(text, nullptr);
}

// ============================================================
// NewDeclaration Tests
// ============================================================

TEST_F(XMLDocumentTest_288, NewDeclaration_288) {
    XMLDocument doc;
    XMLDeclaration* decl = doc.NewDeclaration();
    EXPECT_NE(decl, nullptr);
}

TEST_F(XMLDocumentTest_288, NewDeclarationWithText_288) {
    XMLDocument doc;
    XMLDeclaration* decl = doc.NewDeclaration("xml version=\"1.0\"");
    EXPECT_NE(decl, nullptr);
}

// ============================================================
// NewUnknown Tests
// ============================================================

TEST_F(XMLDocumentTest_288, NewUnknown_288) {
    XMLDocument doc;
    XMLUnknown* unknown = doc.NewUnknown("something");
    EXPECT_NE(unknown, nullptr);
}

// ============================================================
// DeleteNode Tests
// ============================================================

TEST_F(XMLDocumentTest_288, DeleteNode_288) {
    XMLDocument doc;
    XMLElement* elem = doc.NewElement("test");
    doc.InsertEndChild(elem);
    EXPECT_NE(doc.RootElement(), nullptr);
    doc.DeleteNode(elem);
    EXPECT_EQ(doc.RootElement(), nullptr);
}

TEST_F(XMLDocumentTest_288, DeleteNullNode_288) {
    XMLDocument doc;
    // Deleting null should not crash
    doc.DeleteNode(nullptr);
    EXPECT_FALSE(doc.Error());
}

// ============================================================
// Clear Tests
// ============================================================

TEST_F(XMLDocumentTest_288, Clear_288) {
    XMLDocument doc;
    doc.Parse("<root><child/></root>");
    EXPECT_NE(doc.RootElement(), nullptr);
    doc.Clear();
    EXPECT_EQ(doc.RootElement(), nullptr);
    EXPECT_FALSE(doc.Error());
}

TEST_F(XMLDocumentTest_288, ClearAfterError_288) {
    XMLDocument doc;
    doc.Parse("<>");
    EXPECT_TRUE(doc.Error());
    doc.Clear();
    EXPECT_FALSE(doc.Error());
    EXPECT_EQ(doc.ErrorID(), XML_SUCCESS);
}

// ============================================================
// DeepCopy Tests
// ============================================================

TEST_F(XMLDocumentTest_288, DeepCopy_288) {
    XMLDocument source;
    source.Parse("<root><child attr=\"val\">text</child></root>");
    EXPECT_FALSE(source.Error());

    XMLDocument target;
    source.DeepCopy(&target);
    EXPECT_FALSE(target.Error());
    EXPECT_NE(target.RootElement(), nullptr);
    EXPECT_STREQ(target.RootElement()->Name(), "root");
    EXPECT_NE(target.RootElement()->FirstChildElement("child"), nullptr);
    EXPECT_STREQ(target.RootElement()->FirstChildElement("child")->Attribute("attr"), "val");
    EXPECT_STREQ(target.RootElement()->FirstChildElement("child")->GetText(), "text");
}

TEST_F(XMLDocumentTest_288, DeepCopyEmptyDocument_288) {
    XMLDocument source;
    XMLDocument target;
    target.Parse("<root/>");
    EXPECT_NE(target.RootElement(), nullptr);

    source.DeepCopy(&target);
    EXPECT_EQ(target.RootElement(), nullptr);
}

// ============================================================
// ToDocument Tests
// ============================================================

TEST_F(XMLDocumentTest_288, ToDocument_288) {
    XMLDocument doc;
    EXPECT_EQ(doc.ToDocument(), &doc);
}

// ============================================================
// ShallowClone and ShallowEqual Tests
// ============================================================

TEST_F(XMLDocumentTest_288, ShallowCloneReturnsNull_288) {
    XMLDocument doc;
    EXPECT_EQ(doc.ShallowClone(&doc), nullptr);
}

TEST_F(XMLDocumentTest_288, ShallowEqualReturnsFalse_288) {
    XMLDocument doc1;
    XMLDocument doc2;
    EXPECT_FALSE(doc1.ShallowEqual(&doc2));
}

// ============================================================
// Print Tests
// ============================================================

TEST_F(XMLDocumentTest_288, PrintToNull_288) {
    XMLDocument doc;
    doc.Parse("<root/>");
    // Print with null streamer should use internal default (stdout)
    // Just verify it doesn't crash
    XMLPrinter printer;
    doc.Print(&printer);
    const char* result = printer.CStr();
    EXPECT_NE(result, nullptr);
    EXPECT_NE(strstr(result, "root"), nullptr);
}

TEST_F(XMLDocumentTest_288, PrintCompact_288) {
    XMLDocument doc;
    doc.Parse("<root>\n  <child/>\n</root>");
    XMLPrinter printer(nullptr, true); // compact
    doc.Print(&printer);
    const char* result = printer.CStr();
    EXPECT_NE(result, nullptr);
    EXPECT_NE(strstr(result, "<root>"), nullptr);
}

// ============================================================
// Accept (Visitor) Tests
// ============================================================

TEST_F(XMLDocumentTest_288, AcceptVisitor_288) {
    XMLDocument doc;
    doc.Parse("<root/>");
    XMLPrinter printer;
    bool accepted = doc.Accept(&printer);
    EXPECT_TRUE(accepted);
    const char* result = printer.CStr();
    EXPECT_NE(result, nullptr);
}

// ============================================================
// File I/O Tests
// ============================================================

TEST_F(XMLDocumentTest_288, LoadFileNonExistent_288) {
    XMLDocument doc;
    XMLError err = doc.LoadFile("non_existent_file_that_should_not_exist.xml");
    EXPECT_NE(err, XML_SUCCESS);
    EXPECT_TRUE(doc.Error());
    EXPECT_EQ(doc.ErrorID(), XML_ERROR_FILE_NOT_FOUND);
}

TEST_F(XMLDocumentTest_288, LoadFileNullFilename_288) {
    XMLDocument doc;
    XMLError err = doc.LoadFile((const char*)nullptr);
    EXPECT_NE(err, XML_SUCCESS);
    EXPECT_TRUE(doc.Error());
}

TEST_F(XMLDocumentTest_288, SaveAndLoadFile_288) {
    const char* filename = "test_save_load_288.xml";
    
    // Save
    {
        XMLDocument doc;
        doc.Parse("<root><child>text</child></root>");
        EXPECT_FALSE(doc.Error());
        XMLError err = doc.SaveFile(filename);
        EXPECT_EQ(err, XML_SUCCESS);
    }
    
    // Load
    {
        XMLDocument doc;
        XMLError err = doc.LoadFile(filename);
        EXPECT_EQ(err, XML_SUCCESS);
        EXPECT_FALSE(doc.Error());
        EXPECT_NE(doc.RootElement(), nullptr);
        EXPECT_STREQ(doc.RootElement()->Name(), "root");
    }
    
    // Cleanup
    remove(filename);
}

TEST_F(XMLDocumentTest_288, SaveFileCompact_288) {
    const char* filename = "test_compact_288.xml";
    
    XMLDocument doc;
    doc.Parse("<root><child/></root>");
    XMLError err = doc.SaveFile(filename, true);
    EXPECT_EQ(err, XML_SUCCESS);
    
    remove(filename);
}

TEST_F(XMLDocumentTest_288, SaveToFILE_288) {
    const char* filename = "test_save_fp_288.xml";
    FILE* fp = fopen(filename, "w");
    ASSERT_NE(fp, nullptr);
    
    XMLDocument doc;
    doc.Parse("<root/>");
    XMLError err = doc.SaveFile(fp, false);
    EXPECT_EQ(err, XML_SUCCESS);
    fclose(fp);
    
    // Verify by loading
    XMLDocument doc2;
    err = doc2.LoadFile(filename);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_NE(doc2.RootElement(), nullptr);
    
    remove(filename);
}

TEST_F(XMLDocumentTest_288, LoadFromFILE_288) {
    const char* filename = "test_load_fp_288.xml";
    
    // Create file
    {
        XMLDocument doc;
        doc.Parse("<root attr=\"1\"/>");
        doc.SaveFile(filename);
    }
    
    FILE* fp = fopen(filename, "rb");
    ASSERT_NE(fp, nullptr);
    
    XMLDocument doc;
    XMLError err = doc.LoadFile(fp);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_NE(doc.RootElement(), nullptr);
    EXPECT_STREQ(doc.RootElement()->Attribute("attr"), "1");
    
    fclose(fp);
    remove(filename);
}

// ============================================================
// Multiple Parse Calls (Re-parse) Tests
// ============================================================

TEST_F(XMLDocumentTest_288, ReparseDocument_288) {
    XMLDocument doc;
    doc.Parse("<first/>");
    EXPECT_STREQ(doc.RootElement()->Name(), "first");
    
    doc.Parse("<second/>");
    EXPECT_STREQ(doc.RootElement()->Name(), "second");
}

// ============================================================
// Entity Processing Tests
// ============================================================

TEST_F(XMLDocumentTest_288, ParseWithEntities_288) {
    XMLDocument doc(true);
    doc.Parse("<root>&lt;&gt;&amp;</root>");
    EXPECT_FALSE(doc.Error());
    EXPECT_NE(doc.RootElement(), nullptr);
    EXPECT_STREQ(doc.RootElement()->GetText(), "<>&");
}

TEST_F(XMLDocumentTest_288, ParseWithoutEntityProcessing_288) {
    XMLDocument doc(false);
    doc.Parse("<root>&lt;</root>");
    EXPECT_FALSE(doc.Error());
    EXPECT_NE(doc.RootElement(), nullptr);
}

// ============================================================
// Complex Document Tests
// ============================================================

TEST_F(XMLDocumentTest_288, ParseNestedElements_288) {
    XMLDocument doc;
    doc.Parse("<a><b><c><d/></c></b></a>");
    EXPECT_FALSE(doc.Error());
    EXPECT_NE(doc.RootElement(), nullptr);
    EXPECT_NE(doc.RootElement()->FirstChildElement("b"), nullptr);
    EXPECT_NE(doc.RootElement()->FirstChildElement("b")->FirstChildElement("c"), nullptr);
    EXPECT_NE(doc.RootElement()->FirstChildElement("b")->FirstChildElement("c")->FirstChildElement("d"), nullptr);
}

TEST_F(XMLDocumentTest_288, ParseMultipleRootLevelNodes_288) {
    XMLDocument doc;
    doc.Parse("<?xml version=\"1.0\"?><!-- comment --><root/>");
    EXPECT_FALSE(doc.Error());
    EXPECT_NE(doc.RootElement(), nullptr);
}

TEST_F(XMLDocumentTest_288, ParseCDATA_288) {
    XMLDocument doc;
    doc.Parse("<root><![CDATA[some <data> here]]></root>");
    EXPECT_FALSE(doc.Error());
    EXPECT_NE(doc.RootElement(), nullptr);
}

// ============================================================
// RootElement Tests
// ============================================================

TEST_F(XMLDocumentTest_288, RootElementNull_288) {
    XMLDocument doc;
    EXPECT_EQ(doc.RootElement(), nullptr);
}

TEST_F(XMLDocumentTest_288, RootElementAfterParse_288) {
    XMLDocument doc;
    doc.Parse("<myroot/>");
    EXPECT_NE(doc.RootElement(), nullptr);
    EXPECT_STREQ(doc.RootElement()->Name(), "myroot");
}

// ============================================================
// MarkInUse Tests
// ============================================================

TEST_F(XMLDocumentTest_288, MarkInUseWithElement_288) {
    XMLDocument doc;
    XMLElement* elem = doc.NewElement("test");
    // Should not crash
    doc.MarkInUse(elem);
    doc.DeleteNode(elem);
}

// ============================================================
// PrintError Tests
// ============================================================

TEST_F(XMLDocumentTest_288, PrintErrorAfterParseFail_288) {
    XMLDocument doc;
    doc.Parse("<>");
    EXPECT_TRUE(doc.Error());
    // PrintError should not crash; it prints to stdout
    doc.PrintError();
}

TEST_F(XMLDocumentTest_288, PrintErrorNoError_288) {
    XMLDocument doc;
    doc.Parse("<root/>");
    EXPECT_FALSE(doc.Error());
    // Should not crash even when there's no error
    doc.PrintError();
}
