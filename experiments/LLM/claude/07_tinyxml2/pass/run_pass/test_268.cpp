#include "gtest/gtest.h"
#include "tinyxml2.h"

using namespace tinyxml2;

// ============================================================
// Test Fixture
// ============================================================
class XMLDocumentTest_268 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// ============================================================
// Construction Tests
// ============================================================
TEST_F(XMLDocumentTest_268, DefaultConstruction_268) {
    XMLDocument doc;
    EXPECT_FALSE(doc.Error());
    EXPECT_EQ(doc.ErrorID(), XML_SUCCESS);
    EXPECT_FALSE(doc.HasBOM());
    EXPECT_TRUE(doc.ProcessEntities());
    EXPECT_EQ(doc.RootElement(), nullptr);
}

TEST_F(XMLDocumentTest_268, ConstructWithProcessEntitiesFalse_268) {
    XMLDocument doc(false);
    EXPECT_TRUE(doc.ProcessEntities() == false);
    EXPECT_FALSE(doc.Error());
}

TEST_F(XMLDocumentTest_268, ConstructWithWhitespacePreserve_268) {
    XMLDocument doc(true, PRESERVE_WHITESPACE);
    EXPECT_EQ(doc.WhitespaceMode(), PRESERVE_WHITESPACE);
}

TEST_F(XMLDocumentTest_268, ConstructWithWhitespaceCollapse_268) {
    XMLDocument doc(true, COLLAPSE_WHITESPACE);
    EXPECT_EQ(doc.WhitespaceMode(), COLLAPSE_WHITESPACE);
}

// ============================================================
// Parse Tests
// ============================================================
TEST_F(XMLDocumentTest_268, ParseSimpleXML_268) {
    XMLDocument doc;
    XMLError err = doc.Parse("<root><child/></root>");
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_FALSE(doc.Error());
    EXPECT_NE(doc.RootElement(), nullptr);
    EXPECT_STREQ(doc.RootElement()->Name(), "root");
}

TEST_F(XMLDocumentTest_268, ParseEmptyString_268) {
    XMLDocument doc;
    XMLError err = doc.Parse("");
    EXPECT_NE(err, XML_SUCCESS);
    EXPECT_TRUE(doc.Error());
}

TEST_F(XMLDocumentTest_268, ParseNullPointer_268) {
    XMLDocument doc;
    XMLError err = doc.Parse(nullptr, 0);
    EXPECT_NE(err, XML_SUCCESS);
    EXPECT_TRUE(doc.Error());
}

TEST_F(XMLDocumentTest_268, ParseMalformedXML_268) {
    XMLDocument doc;
    XMLError err = doc.Parse("<root><unclosed>");
    EXPECT_NE(err, XML_SUCCESS);
    EXPECT_TRUE(doc.Error());
}

TEST_F(XMLDocumentTest_268, ParseWithNBytes_268) {
    XMLDocument doc;
    const char* xml = "<root/>EXTRADATA";
    XMLError err = doc.Parse(xml, 7); // only "<root/>"
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_NE(doc.RootElement(), nullptr);
    EXPECT_STREQ(doc.RootElement()->Name(), "root");
}

TEST_F(XMLDocumentTest_268, ParseXMLWithAttributes_268) {
    XMLDocument doc;
    XMLError err = doc.Parse("<root attr=\"value\"/>");
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_NE(doc.RootElement(), nullptr);
    EXPECT_STREQ(doc.RootElement()->Attribute("attr"), "value");
}

TEST_F(XMLDocumentTest_268, ParseXMLWithText_268) {
    XMLDocument doc;
    XMLError err = doc.Parse("<root>Hello World</root>");
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_NE(doc.RootElement(), nullptr);
    EXPECT_STREQ(doc.RootElement()->GetText(), "Hello World");
}

TEST_F(XMLDocumentTest_268, ParseXMLWithDeclaration_268) {
    XMLDocument doc;
    XMLError err = doc.Parse("<?xml version=\"1.0\"?><root/>");
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_NE(doc.RootElement(), nullptr);
}

TEST_F(XMLDocumentTest_268, ParseXMLWithComment_268) {
    XMLDocument doc;
    XMLError err = doc.Parse("<!-- comment --><root/>");
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_NE(doc.RootElement(), nullptr);
}

TEST_F(XMLDocumentTest_268, ParseXMLWithEntities_268) {
    XMLDocument doc(true);
    XMLError err = doc.Parse("<root>&amp;&lt;&gt;</root>");
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_NE(doc.RootElement(), nullptr);
    EXPECT_STREQ(doc.RootElement()->GetText(), "&<>");
}

TEST_F(XMLDocumentTest_268, ParseXMLWithoutProcessingEntities_268) {
    XMLDocument doc(false);
    XMLError err = doc.Parse("<root>&amp;</root>");
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_NE(doc.RootElement(), nullptr);
    // Without entity processing, &amp; should remain as-is
    EXPECT_STREQ(doc.RootElement()->GetText(), "&amp;");
}

// ============================================================
// BOM Tests
// ============================================================
TEST_F(XMLDocumentTest_268, SetBOMTrue_268) {
    XMLDocument doc;
    doc.SetBOM(true);
    EXPECT_TRUE(doc.HasBOM());
}

TEST_F(XMLDocumentTest_268, SetBOMFalse_268) {
    XMLDocument doc;
    doc.SetBOM(false);
    EXPECT_FALSE(doc.HasBOM());
}

// ============================================================
// Error Handling Tests
// ============================================================
TEST_F(XMLDocumentTest_268, ClearErrorAfterParseFail_268) {
    XMLDocument doc;
    doc.Parse("<broken");
    EXPECT_TRUE(doc.Error());
    doc.ClearError();
    EXPECT_FALSE(doc.Error());
    EXPECT_EQ(doc.ErrorID(), XML_SUCCESS);
}

TEST_F(XMLDocumentTest_268, ErrorNameNotNull_268) {
    XMLDocument doc;
    doc.Parse("<broken");
    EXPECT_TRUE(doc.Error());
    const char* errName = doc.ErrorName();
    EXPECT_NE(errName, nullptr);
    EXPECT_GT(strlen(errName), 0u);
}

TEST_F(XMLDocumentTest_268, ErrorStrNotNull_268) {
    XMLDocument doc;
    doc.Parse("<broken");
    EXPECT_TRUE(doc.Error());
    const char* errStr = doc.ErrorStr();
    EXPECT_NE(errStr, nullptr);
}

TEST_F(XMLDocumentTest_268, ErrorLineNumOnError_268) {
    XMLDocument doc;
    doc.Parse("<root>\n<broken");
    EXPECT_TRUE(doc.Error());
    EXPECT_GT(doc.ErrorLineNum(), 0);
}

TEST_F(XMLDocumentTest_268, ErrorIDToNameSuccess_268) {
    const char* name = XMLDocument::ErrorIDToName(XML_SUCCESS);
    EXPECT_NE(name, nullptr);
    EXPECT_STREQ(name, "XML_SUCCESS");
}

TEST_F(XMLDocumentTest_268, ErrorIDToNameVariousErrors_268) {
    const char* name1 = XMLDocument::ErrorIDToName(XML_ERROR_FILE_NOT_FOUND);
    EXPECT_NE(name1, nullptr);
    EXPECT_GT(strlen(name1), 0u);

    const char* name2 = XMLDocument::ErrorIDToName(XML_ERROR_PARSING);
    EXPECT_NE(name2, nullptr);
    EXPECT_GT(strlen(name2), 0u);
}

TEST_F(XMLDocumentTest_268, PrintErrorDoesNotCrash_268) {
    XMLDocument doc;
    doc.Parse("<broken");
    EXPECT_TRUE(doc.Error());
    // Should not crash
    doc.PrintError();
}

// ============================================================
// NewElement / NewComment / NewText / NewDeclaration / NewUnknown
// ============================================================
TEST_F(XMLDocumentTest_268, NewElementCreatesElement_268) {
    XMLDocument doc;
    XMLElement* elem = doc.NewElement("test");
    EXPECT_NE(elem, nullptr);
    EXPECT_STREQ(elem->Name(), "test");
    doc.DeleteNode(elem);
}

TEST_F(XMLDocumentTest_268, NewCommentCreatesComment_268) {
    XMLDocument doc;
    XMLComment* comment = doc.NewComment("this is a comment");
    EXPECT_NE(comment, nullptr);
    EXPECT_STREQ(comment->Value(), "this is a comment");
    doc.DeleteNode(comment);
}

TEST_F(XMLDocumentTest_268, NewTextCreatesText_268) {
    XMLDocument doc;
    XMLText* text = doc.NewText("hello");
    EXPECT_NE(text, nullptr);
    EXPECT_STREQ(text->Value(), "hello");
    doc.DeleteNode(text);
}

TEST_F(XMLDocumentTest_268, NewDeclarationCreatesDeclaration_268) {
    XMLDocument doc;
    XMLDeclaration* decl = doc.NewDeclaration();
    EXPECT_NE(decl, nullptr);
    doc.DeleteNode(decl);
}

TEST_F(XMLDocumentTest_268, NewDeclarationWithCustomText_268) {
    XMLDocument doc;
    XMLDeclaration* decl = doc.NewDeclaration("xml version=\"1.0\" encoding=\"UTF-8\"");
    EXPECT_NE(decl, nullptr);
    doc.DeleteNode(decl);
}

TEST_F(XMLDocumentTest_268, NewUnknownCreatesUnknown_268) {
    XMLDocument doc;
    XMLUnknown* unknown = doc.NewUnknown("something");
    EXPECT_NE(unknown, nullptr);
    EXPECT_STREQ(unknown->Value(), "something");
    doc.DeleteNode(unknown);
}

// ============================================================
// Clear Tests
// ============================================================
TEST_F(XMLDocumentTest_268, ClearRemovesAllChildren_268) {
    XMLDocument doc;
    doc.Parse("<root><child1/><child2/></root>");
    EXPECT_NE(doc.RootElement(), nullptr);
    doc.Clear();
    EXPECT_EQ(doc.RootElement(), nullptr);
    EXPECT_FALSE(doc.Error());
}

TEST_F(XMLDocumentTest_268, ClearOnEmptyDocument_268) {
    XMLDocument doc;
    doc.Clear();
    EXPECT_EQ(doc.RootElement(), nullptr);
    EXPECT_FALSE(doc.Error());
}

// ============================================================
// DeepCopy Tests
// ============================================================
TEST_F(XMLDocumentTest_268, DeepCopySimpleDocument_268) {
    XMLDocument source;
    source.Parse("<root attr=\"val\"><child>text</child></root>");
    EXPECT_FALSE(source.Error());

    XMLDocument target;
    source.DeepCopy(&target);
    EXPECT_FALSE(target.Error());
    EXPECT_NE(target.RootElement(), nullptr);
    EXPECT_STREQ(target.RootElement()->Name(), "root");
    EXPECT_STREQ(target.RootElement()->Attribute("attr"), "val");
    
    XMLElement* child = target.RootElement()->FirstChildElement("child");
    EXPECT_NE(child, nullptr);
    EXPECT_STREQ(child->GetText(), "text");
}

TEST_F(XMLDocumentTest_268, DeepCopyEmptyDocument_268) {
    XMLDocument source;
    XMLDocument target;
    source.DeepCopy(&target);
    EXPECT_EQ(target.RootElement(), nullptr);
}

TEST_F(XMLDocumentTest_268, DeepCopyOverwritesTarget_268) {
    XMLDocument source;
    source.Parse("<source/>");
    
    XMLDocument target;
    target.Parse("<target/>");
    EXPECT_STREQ(target.RootElement()->Name(), "target");

    source.DeepCopy(&target);
    EXPECT_NE(target.RootElement(), nullptr);
    EXPECT_STREQ(target.RootElement()->Name(), "source");
}

// ============================================================
// DeleteNode Tests
// ============================================================
TEST_F(XMLDocumentTest_268, DeleteNodeRemovesChild_268) {
    XMLDocument doc;
    doc.Parse("<root><child1/><child2/></root>");
    XMLElement* root = doc.RootElement();
    EXPECT_NE(root, nullptr);
    
    XMLElement* child1 = root->FirstChildElement("child1");
    EXPECT_NE(child1, nullptr);
    
    doc.DeleteNode(child1);
    EXPECT_EQ(root->FirstChildElement("child1"), nullptr);
    EXPECT_NE(root->FirstChildElement("child2"), nullptr);
}

TEST_F(XMLDocumentTest_268, DeleteNodeOnUnlinkedNode_268) {
    XMLDocument doc;
    XMLElement* elem = doc.NewElement("orphan");
    EXPECT_NE(elem, nullptr);
    doc.DeleteNode(elem);
    // Should not crash
}

// ============================================================
// ToDocument Tests
// ============================================================
TEST_F(XMLDocumentTest_268, ToDocumentReturnsSelf_268) {
    XMLDocument doc;
    EXPECT_EQ(doc.ToDocument(), &doc);
}

// ============================================================
// ShallowClone / ShallowEqual Tests
// ============================================================
TEST_F(XMLDocumentTest_268, ShallowCloneReturnsNull_268) {
    XMLDocument doc;
    // XMLDocument's ShallowClone should return nullptr
    XMLNode* clone = doc.ShallowClone(&doc);
    EXPECT_EQ(clone, nullptr);
}

TEST_F(XMLDocumentTest_268, ShallowEqualReturnsFalse_268) {
    XMLDocument doc1;
    XMLDocument doc2;
    EXPECT_FALSE(doc1.ShallowEqual(&doc2));
}

// ============================================================
// LoadFile / SaveFile Tests
// ============================================================
TEST_F(XMLDocumentTest_268, LoadFileNonExistent_268) {
    XMLDocument doc;
    XMLError err = doc.LoadFile("nonexistent_file_12345.xml");
    EXPECT_NE(err, XML_SUCCESS);
    EXPECT_TRUE(doc.Error());
    EXPECT_EQ(doc.ErrorID(), XML_ERROR_FILE_NOT_FOUND);
}

TEST_F(XMLDocumentTest_268, SaveAndLoadFile_268) {
    const char* filename = "test_output_268.xml";
    
    // Save
    {
        XMLDocument doc;
        doc.Parse("<root><child attr=\"1\">text</child></root>");
        EXPECT_FALSE(doc.Error());
        XMLError err = doc.SaveFile(filename, false);
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
        
        XMLElement* child = doc.RootElement()->FirstChildElement("child");
        EXPECT_NE(child, nullptr);
        EXPECT_STREQ(child->Attribute("attr"), "1");
        EXPECT_STREQ(child->GetText(), "text");
    }
    
    // Cleanup
    std::remove(filename);
}

TEST_F(XMLDocumentTest_268, SaveFileCompact_268) {
    const char* filename = "test_compact_268.xml";
    
    XMLDocument doc;
    doc.Parse("<root><child/></root>");
    EXPECT_FALSE(doc.Error());
    XMLError err = doc.SaveFile(filename, true);
    EXPECT_EQ(err, XML_SUCCESS);
    
    std::remove(filename);
}

TEST_F(XMLDocumentTest_268, LoadFileFromFILE_268) {
    const char* filename = "test_file_ptr_268.xml";
    
    // Write file first
    {
        XMLDocument doc;
        doc.Parse("<root/>");
        doc.SaveFile(filename, false);
    }
    
    // Load from FILE*
    {
        FILE* fp = fopen(filename, "rb");
        ASSERT_NE(fp, nullptr);
        
        XMLDocument doc;
        XMLError err = doc.LoadFile(fp);
        fclose(fp);
        
        EXPECT_EQ(err, XML_SUCCESS);
        EXPECT_NE(doc.RootElement(), nullptr);
        EXPECT_STREQ(doc.RootElement()->Name(), "root");
    }
    
    std::remove(filename);
}

TEST_F(XMLDocumentTest_268, SaveFileToFILE_268) {
    const char* filename = "test_save_fp_268.xml";
    
    XMLDocument doc;
    doc.Parse("<root><item/></root>");
    EXPECT_FALSE(doc.Error());
    
    FILE* fp = fopen(filename, "w");
    ASSERT_NE(fp, nullptr);
    XMLError err = doc.SaveFile(fp, false);
    fclose(fp);
    EXPECT_EQ(err, XML_SUCCESS);
    
    // Verify by loading back
    XMLDocument doc2;
    EXPECT_EQ(doc2.LoadFile(filename), XML_SUCCESS);
    EXPECT_STREQ(doc2.RootElement()->Name(), "root");
    
    std::remove(filename);
}

// ============================================================
// Print Tests
// ============================================================
TEST_F(XMLDocumentTest_268, PrintToDefaultPrinter_268) {
    XMLDocument doc;
    doc.Parse("<root><child/></root>");
    EXPECT_FALSE(doc.Error());
    
    XMLPrinter printer;
    doc.Print(&printer);
    const char* result = printer.CStr();
    EXPECT_NE(result, nullptr);
    EXPECT_NE(strstr(result, "root"), nullptr);
    EXPECT_NE(strstr(result, "child"), nullptr);
}

TEST_F(XMLDocumentTest_268, PrintCompact_268) {
    XMLDocument doc;
    doc.Parse("<root><child/></root>");
    EXPECT_FALSE(doc.Error());
    
    XMLPrinter printer(nullptr, true); // compact mode
    doc.Print(&printer);
    const char* result = printer.CStr();
    EXPECT_NE(result, nullptr);
    EXPECT_NE(strstr(result, "<root>"), nullptr);
}

TEST_F(XMLDocumentTest_268, PrintNullPrinter_268) {
    XMLDocument doc;
    doc.Parse("<root/>");
    // Passing nullptr should print to stdout; should not crash
    doc.Print(nullptr);
}

// ============================================================
// Accept Tests
// ============================================================
TEST_F(XMLDocumentTest_268, AcceptVisitor_268) {
    XMLDocument doc;
    doc.Parse("<root><child/></root>");
    EXPECT_FALSE(doc.Error());
    
    XMLPrinter printer;
    bool result = doc.Accept(&printer);
    EXPECT_TRUE(result);
    EXPECT_NE(printer.CStr(), nullptr);
}

// ============================================================
// RootElement Tests
// ============================================================
TEST_F(XMLDocumentTest_268, RootElementOnEmptyDoc_268) {
    XMLDocument doc;
    EXPECT_EQ(doc.RootElement(), nullptr);
}

TEST_F(XMLDocumentTest_268, RootElementAfterInsert_268) {
    XMLDocument doc;
    XMLElement* elem = doc.NewElement("myroot");
    doc.InsertFirstChild(elem);
    EXPECT_EQ(doc.RootElement(), elem);
    EXPECT_STREQ(doc.RootElement()->Name(), "myroot");
}

// ============================================================
// Multiple Parse Tests
// ============================================================
TEST_F(XMLDocumentTest_268, ReParseOverwritesPrevious_268) {
    XMLDocument doc;
    doc.Parse("<first/>");
    EXPECT_STREQ(doc.RootElement()->Name(), "first");
    
    doc.Parse("<second/>");
    EXPECT_STREQ(doc.RootElement()->Name(), "second");
}

// ============================================================
// Complex Structure Tests
// ============================================================
TEST_F(XMLDocumentTest_268, ParseDeepNestedXML_268) {
    XMLDocument doc;
    XMLError err = doc.Parse(
        "<a><b><c><d><e><f>deep</f></e></d></c></b></a>");
    EXPECT_EQ(err, XML_SUCCESS);
    
    XMLElement* e = doc.RootElement();
    EXPECT_STREQ(e->Name(), "a");
    e = e->FirstChildElement();
    EXPECT_STREQ(e->Name(), "b");
    e = e->FirstChildElement();
    EXPECT_STREQ(e->Name(), "c");
    e = e->FirstChildElement();
    EXPECT_STREQ(e->Name(), "d");
    e = e->FirstChildElement();
    EXPECT_STREQ(e->Name(), "e");
    e = e->FirstChildElement();
    EXPECT_STREQ(e->Name(), "f");
    EXPECT_STREQ(e->GetText(), "deep");
}

TEST_F(XMLDocumentTest_268, ParseXMLWithMultipleChildren_268) {
    XMLDocument doc;
    doc.Parse("<root><a/><b/><c/></root>");
    EXPECT_FALSE(doc.Error());
    
    XMLElement* root = doc.RootElement();
    EXPECT_NE(root, nullptr);
    
    int count = 0;
    for (XMLElement* child = root->FirstChildElement(); child; child = child->NextSiblingElement()) {
        count++;
    }
    EXPECT_EQ(count, 3);
}

TEST_F(XMLDocumentTest_268, ParseXMLWithCDATA_268) {
    XMLDocument doc;
    XMLError err = doc.Parse("<root><![CDATA[some <data>]]></root>");
    EXPECT_EQ(err, XML_SUCCESS);
}

// ============================================================
// MarkInUse test (via InsertEndChild of unlinked node)
// ============================================================
TEST_F(XMLDocumentTest_268, InsertNewElementAsChild_268) {
    XMLDocument doc;
    doc.Parse("<root/>");
    XMLElement* root = doc.RootElement();
    
    XMLElement* newElem = doc.NewElement("newchild");
    root->InsertEndChild(newElem);
    
    XMLElement* found = root->FirstChildElement("newchild");
    EXPECT_NE(found, nullptr);
    EXPECT_STREQ(found->Name(), "newchild");
}

// ============================================================
// Error after clear and reparse
// ============================================================
TEST_F(XMLDocumentTest_268, ClearAndReparse_268) {
    XMLDocument doc;
    doc.Parse("<broken");
    EXPECT_TRUE(doc.Error());
    
    doc.Clear();
    EXPECT_FALSE(doc.Error());
    
    XMLError err = doc.Parse("<valid/>");
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_FALSE(doc.Error());
    EXPECT_NE(doc.RootElement(), nullptr);
}

// ============================================================
// BOM Persistence through Save/Load
// ============================================================
TEST_F(XMLDocumentTest_268, BOMPersistsThroughSaveLoad_268) {
    const char* filename = "test_bom_268.xml";
    
    {
        XMLDocument doc;
        doc.Parse("<root/>");
        doc.SetBOM(true);
        EXPECT_TRUE(doc.HasBOM());
        doc.SaveFile(filename, false);
    }
    
    {
        XMLDocument doc;
        doc.LoadFile(filename);
        EXPECT_TRUE(doc.HasBOM());
    }
    
    std::remove(filename);
}

// ============================================================
// Null and edge cases for New* methods
// ============================================================
TEST_F(XMLDocumentTest_268, NewCommentWithEmptyString_268) {
    XMLDocument doc;
    XMLComment* comment = doc.NewComment("");
    EXPECT_NE(comment, nullptr);
    EXPECT_STREQ(comment->Value(), "");
    doc.DeleteNode(comment);
}

TEST_F(XMLDocumentTest_268, NewTextWithEmptyString_268) {
    XMLDocument doc;
    XMLText* text = doc.NewText("");
    EXPECT_NE(text, nullptr);
    EXPECT_STREQ(text->Value(), "");
    doc.DeleteNode(text);
}

TEST_F(XMLDocumentTest_268, NewElementWithEmptyString_268) {
    XMLDocument doc;
    XMLElement* elem = doc.NewElement("");
    EXPECT_NE(elem, nullptr);
    doc.DeleteNode(elem);
}
