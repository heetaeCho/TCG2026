#include "gtest/gtest.h"
#include "tinyxml2.h"

using namespace tinyxml2;

// ============================================================
// Test Fixture
// ============================================================
class XMLDocumentTest_114 : public ::testing::Test {
protected:
    XMLDocument doc;
};

// ============================================================
// Constructor / Default State Tests
// ============================================================

TEST_F(XMLDocumentTest_114, DefaultConstructor_NoError_114) {
    EXPECT_EQ(doc.ErrorID(), XML_SUCCESS);
    EXPECT_FALSE(doc.Error());
    EXPECT_EQ(doc.ErrorLineNum(), 0);
    EXPECT_FALSE(doc.HasBOM());
}

TEST_F(XMLDocumentTest_114, ConstructorWithProcessEntities_114) {
    XMLDocument doc2(true, PRESERVE_WHITESPACE);
    EXPECT_TRUE(doc2.ProcessEntities());
    EXPECT_EQ(doc2.WhitespaceMode(), PRESERVE_WHITESPACE);
    EXPECT_EQ(doc2.ErrorID(), XML_SUCCESS);
}

TEST_F(XMLDocumentTest_114, ConstructorWithoutProcessEntities_114) {
    XMLDocument doc2(false, COLLAPSE_WHITESPACE);
    EXPECT_FALSE(doc2.ProcessEntities());
    EXPECT_EQ(doc2.WhitespaceMode(), COLLAPSE_WHITESPACE);
}

// ============================================================
// Parse Tests
// ============================================================

TEST_F(XMLDocumentTest_114, ParseValidXML_114) {
    const char* xml = "<root><child>text</child></root>";
    XMLError err = doc.Parse(xml);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_FALSE(doc.Error());
    EXPECT_EQ(doc.ErrorID(), XML_SUCCESS);
}

TEST_F(XMLDocumentTest_114, ParseEmptyString_114) {
    XMLError err = doc.Parse("");
    EXPECT_NE(err, XML_SUCCESS);
    EXPECT_TRUE(doc.Error());
}

TEST_F(XMLDocumentTest_114, ParseNullPointer_114) {
    XMLError err = doc.Parse(nullptr, 0);
    EXPECT_NE(err, XML_SUCCESS);
    EXPECT_TRUE(doc.Error());
}

TEST_F(XMLDocumentTest_114, ParseMalformedXML_114) {
    const char* xml = "<root><child></root>";
    XMLError err = doc.Parse(xml);
    EXPECT_NE(err, XML_SUCCESS);
    EXPECT_TRUE(doc.Error());
}

TEST_F(XMLDocumentTest_114, ParseWithExplicitLength_114) {
    const char* xml = "<root/>EXTRA_GARBAGE";
    XMLError err = doc.Parse(xml, 7); // only "<root/>"
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_FALSE(doc.Error());
}

TEST_F(XMLDocumentTest_114, ParseWithBOM_114) {
    const char* xml = "\xEF\xBB\xBF<root/>";
    XMLError err = doc.Parse(xml);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_TRUE(doc.HasBOM());
}

TEST_F(XMLDocumentTest_114, ParseXMLDeclaration_114) {
    const char* xml = "<?xml version=\"1.0\"?><root/>";
    XMLError err = doc.Parse(xml);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_FALSE(doc.Error());
}

TEST_F(XMLDocumentTest_114, ParseWithAttributes_114) {
    const char* xml = "<root attr1=\"value1\" attr2=\"value2\"/>";
    XMLError err = doc.Parse(xml);
    EXPECT_EQ(err, XML_SUCCESS);
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    EXPECT_STREQ(root->Attribute("attr1"), "value1");
    EXPECT_STREQ(root->Attribute("attr2"), "value2");
}

// ============================================================
// RootElement Tests
// ============================================================

TEST_F(XMLDocumentTest_114, RootElementAfterParse_114) {
    doc.Parse("<root/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    EXPECT_STREQ(root->Name(), "root");
}

TEST_F(XMLDocumentTest_114, RootElementOnEmptyDoc_114) {
    XMLElement* root = doc.RootElement();
    EXPECT_EQ(root, nullptr);
}

// ============================================================
// Error Handling Tests
// ============================================================

TEST_F(XMLDocumentTest_114, ClearError_114) {
    doc.Parse("<bad");
    EXPECT_TRUE(doc.Error());
    doc.ClearError();
    EXPECT_FALSE(doc.Error());
    EXPECT_EQ(doc.ErrorID(), XML_SUCCESS);
}

TEST_F(XMLDocumentTest_114, ErrorName_114) {
    doc.Parse("<root/>");
    const char* name = doc.ErrorName();
    ASSERT_NE(name, nullptr);
    EXPECT_STREQ(name, "XML_SUCCESS");
}

TEST_F(XMLDocumentTest_114, ErrorStr_AfterError_114) {
    doc.Parse("<bad");
    EXPECT_TRUE(doc.Error());
    const char* errStr = doc.ErrorStr();
    ASSERT_NE(errStr, nullptr);
    EXPECT_NE(strlen(errStr), 0u);
}

TEST_F(XMLDocumentTest_114, ErrorIDToName_Success_114) {
    const char* name = XMLDocument::ErrorIDToName(XML_SUCCESS);
    ASSERT_NE(name, nullptr);
    EXPECT_STREQ(name, "XML_SUCCESS");
}

TEST_F(XMLDocumentTest_114, ErrorIDToName_ErrorFileNotFound_114) {
    const char* name = XMLDocument::ErrorIDToName(XML_ERROR_FILE_NOT_FOUND);
    ASSERT_NE(name, nullptr);
    EXPECT_STRNE(name, "");
}

TEST_F(XMLDocumentTest_114, ErrorLineNum_114) {
    const char* xml = "<root>\n<child>\n</root>";
    doc.Parse(xml);
    EXPECT_TRUE(doc.Error());
    EXPECT_GT(doc.ErrorLineNum(), 0);
}

// ============================================================
// BOM Tests
// ============================================================

TEST_F(XMLDocumentTest_114, SetBOM_114) {
    EXPECT_FALSE(doc.HasBOM());
    doc.SetBOM(true);
    EXPECT_TRUE(doc.HasBOM());
    doc.SetBOM(false);
    EXPECT_FALSE(doc.HasBOM());
}

// ============================================================
// NewElement / NewComment / NewText / NewDeclaration / NewUnknown
// ============================================================

TEST_F(XMLDocumentTest_114, NewElement_114) {
    XMLElement* elem = doc.NewElement("test");
    ASSERT_NE(elem, nullptr);
    EXPECT_STREQ(elem->Name(), "test");
}

TEST_F(XMLDocumentTest_114, NewComment_114) {
    XMLComment* comment = doc.NewComment("this is a comment");
    ASSERT_NE(comment, nullptr);
    EXPECT_STREQ(comment->Value(), "this is a comment");
}

TEST_F(XMLDocumentTest_114, NewText_114) {
    XMLText* text = doc.NewText("hello world");
    ASSERT_NE(text, nullptr);
    EXPECT_STREQ(text->Value(), "hello world");
}

TEST_F(XMLDocumentTest_114, NewDeclaration_114) {
    XMLDeclaration* decl = doc.NewDeclaration("xml version=\"1.0\"");
    ASSERT_NE(decl, nullptr);
    EXPECT_STREQ(decl->Value(), "xml version=\"1.0\"");
}

TEST_F(XMLDocumentTest_114, NewDeclarationDefault_114) {
    XMLDeclaration* decl = doc.NewDeclaration();
    ASSERT_NE(decl, nullptr);
}

TEST_F(XMLDocumentTest_114, NewUnknown_114) {
    XMLUnknown* unknown = doc.NewUnknown("something");
    ASSERT_NE(unknown, nullptr);
    EXPECT_STREQ(unknown->Value(), "something");
}

// ============================================================
// DeleteNode Tests
// ============================================================

TEST_F(XMLDocumentTest_114, DeleteNode_114) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    ASSERT_NE(doc.RootElement(), nullptr);
    doc.DeleteNode(elem);
    EXPECT_EQ(doc.RootElement(), nullptr);
}

TEST_F(XMLDocumentTest_114, DeleteNodeNull_114) {
    // Should not crash
    doc.DeleteNode(nullptr);
}

// ============================================================
// Clear Tests
// ============================================================

TEST_F(XMLDocumentTest_114, Clear_114) {
    doc.Parse("<root><child/></root>");
    ASSERT_NE(doc.RootElement(), nullptr);
    doc.Clear();
    EXPECT_EQ(doc.RootElement(), nullptr);
    EXPECT_EQ(doc.ErrorID(), XML_SUCCESS);
}

// ============================================================
// DeepCopy Tests
// ============================================================

TEST_F(XMLDocumentTest_114, DeepCopy_114) {
    doc.Parse("<root attr=\"val\"><child>text</child></root>");
    ASSERT_FALSE(doc.Error());

    XMLDocument target;
    doc.DeepCopy(&target);
    ASSERT_FALSE(target.Error());

    XMLElement* root = target.RootElement();
    ASSERT_NE(root, nullptr);
    EXPECT_STREQ(root->Name(), "root");
    EXPECT_STREQ(root->Attribute("attr"), "val");

    XMLElement* child = root->FirstChildElement("child");
    ASSERT_NE(child, nullptr);
    EXPECT_STREQ(child->GetText(), "text");
}

// ============================================================
// LoadFile / SaveFile Tests
// ============================================================

TEST_F(XMLDocumentTest_114, LoadFileNotFound_114) {
    XMLError err = doc.LoadFile("nonexistent_file_that_should_not_exist_12345.xml");
    EXPECT_NE(err, XML_SUCCESS);
    EXPECT_TRUE(doc.Error());
}

TEST_F(XMLDocumentTest_114, SaveFileAndLoadFile_114) {
    doc.Parse("<root><child>data</child></root>");
    ASSERT_FALSE(doc.Error());

    const char* tmpFile = "test_save_load_114.xml";
    XMLError saveErr = doc.SaveFile(tmpFile, false);
    EXPECT_EQ(saveErr, XML_SUCCESS);

    XMLDocument doc2;
    XMLError loadErr = doc2.LoadFile(tmpFile);
    EXPECT_EQ(loadErr, XML_SUCCESS);
    ASSERT_NE(doc2.RootElement(), nullptr);
    EXPECT_STREQ(doc2.RootElement()->Name(), "root");

    // Cleanup
    std::remove(tmpFile);
}

TEST_F(XMLDocumentTest_114, SaveFileCompact_114) {
    doc.Parse("<root>\n  <child>data</child>\n</root>");
    ASSERT_FALSE(doc.Error());

    const char* tmpFile = "test_save_compact_114.xml";
    XMLError saveErr = doc.SaveFile(tmpFile, true);
    EXPECT_EQ(saveErr, XML_SUCCESS);

    XMLDocument doc2;
    XMLError loadErr = doc2.LoadFile(tmpFile);
    EXPECT_EQ(loadErr, XML_SUCCESS);
    ASSERT_NE(doc2.RootElement(), nullptr);

    std::remove(tmpFile);
}

TEST_F(XMLDocumentTest_114, LoadFileFromFILE_114) {
    const char* tmpFile = "test_file_ptr_114.xml";
    {
        XMLDocument tmp;
        tmp.Parse("<root/>");
        tmp.SaveFile(tmpFile, false);
    }

    FILE* fp = fopen(tmpFile, "rb");
    ASSERT_NE(fp, nullptr);
    XMLError err = doc.LoadFile(fp);
    fclose(fp);
    EXPECT_EQ(err, XML_SUCCESS);
    ASSERT_NE(doc.RootElement(), nullptr);
    EXPECT_STREQ(doc.RootElement()->Name(), "root");

    std::remove(tmpFile);
}

TEST_F(XMLDocumentTest_114, SaveFileToFILE_114) {
    doc.Parse("<root/>");
    ASSERT_FALSE(doc.Error());

    const char* tmpFile = "test_file_ptr_save_114.xml";
    FILE* fp = fopen(tmpFile, "w");
    ASSERT_NE(fp, nullptr);
    XMLError err = doc.SaveFile(fp, false);
    fclose(fp);
    EXPECT_EQ(err, XML_SUCCESS);

    XMLDocument doc2;
    EXPECT_EQ(doc2.LoadFile(tmpFile), XML_SUCCESS);
    ASSERT_NE(doc2.RootElement(), nullptr);

    std::remove(tmpFile);
}

// ============================================================
// ToDocument Tests
// ============================================================

TEST_F(XMLDocumentTest_114, ToDocument_114) {
    XMLDocument* d = doc.ToDocument();
    EXPECT_EQ(d, &doc);
}

// ============================================================
// ShallowClone / ShallowEqual Tests
// ============================================================

TEST_F(XMLDocumentTest_114, ShallowClone_ReturnsNull_114) {
    // XMLDocument::ShallowClone should return nullptr
    XMLNode* clone = doc.ShallowClone(&doc);
    EXPECT_EQ(clone, nullptr);
}

TEST_F(XMLDocumentTest_114, ShallowEqual_ReturnsFalse_114) {
    XMLDocument doc2;
    EXPECT_FALSE(doc.ShallowEqual(&doc2));
}

// ============================================================
// Print Tests
// ============================================================

TEST_F(XMLDocumentTest_114, PrintToXMLPrinter_114) {
    doc.Parse("<root><child/></root>");
    ASSERT_FALSE(doc.Error());

    XMLPrinter printer;
    doc.Print(&printer);
    const char* result = printer.CStr();
    ASSERT_NE(result, nullptr);
    EXPECT_NE(std::string(result).find("root"), std::string::npos);
    EXPECT_NE(std::string(result).find("child"), std::string::npos);
}

TEST_F(XMLDocumentTest_114, PrintWithNullPrinter_114) {
    doc.Parse("<root/>");
    // Passing nullptr should use stdout (or default) - should not crash
    doc.Print(nullptr);
}

// ============================================================
// Accept Tests
// ============================================================

TEST_F(XMLDocumentTest_114, AcceptVisitor_114) {
    doc.Parse("<root/>");
    ASSERT_FALSE(doc.Error());

    XMLPrinter printer;
    bool result = doc.Accept(&printer);
    EXPECT_TRUE(result);
    const char* output = printer.CStr();
    ASSERT_NE(output, nullptr);
    EXPECT_NE(std::string(output).find("root"), std::string::npos);
}

// ============================================================
// ProcessEntities Tests
// ============================================================

TEST_F(XMLDocumentTest_114, ProcessEntitiesDefault_114) {
    // Default constructor should have process entities true
    EXPECT_TRUE(doc.ProcessEntities());
}

TEST_F(XMLDocumentTest_114, ProcessEntitiesFalse_114) {
    XMLDocument doc2(false);
    EXPECT_FALSE(doc2.ProcessEntities());
}

// ============================================================
// WhitespaceMode Tests
// ============================================================

TEST_F(XMLDocumentTest_114, WhitespaceModeDefault_114) {
    EXPECT_EQ(doc.WhitespaceMode(), PRESERVE_WHITESPACE);
}

// ============================================================
// Complex XML Parsing
// ============================================================

TEST_F(XMLDocumentTest_114, ParseComplexXML_114) {
    const char* xml =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>"
        "<root>"
        "  <item id=\"1\">First</item>"
        "  <item id=\"2\">Second</item>"
        "  <!-- comment -->"
        "  <empty/>"
        "</root>";
    XMLError err = doc.Parse(xml);
    EXPECT_EQ(err, XML_SUCCESS);

    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    EXPECT_STREQ(root->Name(), "root");

    XMLElement* item1 = root->FirstChildElement("item");
    ASSERT_NE(item1, nullptr);
    EXPECT_STREQ(item1->Attribute("id"), "1");
    EXPECT_STREQ(item1->GetText(), "First");

    XMLElement* item2 = item1->NextSiblingElement("item");
    ASSERT_NE(item2, nullptr);
    EXPECT_STREQ(item2->Attribute("id"), "2");
    EXPECT_STREQ(item2->GetText(), "Second");

    XMLElement* empty = root->FirstChildElement("empty");
    ASSERT_NE(empty, nullptr);
}

TEST_F(XMLDocumentTest_114, ParseRepeatedly_114) {
    doc.Parse("<first/>");
    EXPECT_FALSE(doc.Error());
    EXPECT_STREQ(doc.RootElement()->Name(), "first");

    doc.Parse("<second/>");
    EXPECT_FALSE(doc.Error());
    EXPECT_STREQ(doc.RootElement()->Name(), "second");
}

// ============================================================
// Entity processing tests
// ============================================================

TEST_F(XMLDocumentTest_114, EntityProcessing_114) {
    const char* xml = "<root>&amp;&lt;&gt;&apos;&quot;</root>";
    doc.Parse(xml);
    ASSERT_FALSE(doc.Error());
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    const char* text = root->GetText();
    ASSERT_NE(text, nullptr);
    EXPECT_STREQ(text, "&<>'\"");
}

TEST_F(XMLDocumentTest_114, EntityProcessingDisabled_114) {
    XMLDocument doc2(false);
    const char* xml = "<root>&amp;</root>";
    doc2.Parse(xml);
    ASSERT_FALSE(doc2.Error());
    XMLElement* root = doc2.RootElement();
    ASSERT_NE(root, nullptr);
    const char* text = root->GetText();
    ASSERT_NE(text, nullptr);
    // Without entity processing, &amp; should remain as is
    EXPECT_STREQ(text, "&amp;");
}

// ============================================================
// MarkInUse tests
// ============================================================

TEST_F(XMLDocumentTest_114, MarkInUse_DoesNotCrash_114) {
    XMLElement* elem = doc.NewElement("test");
    ASSERT_NE(elem, nullptr);
    // Should not crash
    doc.MarkInUse(elem);
    doc.DeleteNode(elem);
}

// ============================================================
// PrintError test
// ============================================================

TEST_F(XMLDocumentTest_114, PrintError_DoesNotCrash_114) {
    doc.Parse("<bad");
    EXPECT_TRUE(doc.Error());
    // Should not crash, just prints to stderr/stdout
    doc.PrintError();
}

TEST_F(XMLDocumentTest_114, PrintErrorNoError_DoesNotCrash_114) {
    doc.Parse("<root/>");
    EXPECT_FALSE(doc.Error());
    doc.PrintError();
}
