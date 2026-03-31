#include "gtest/gtest.h"
#include "tinyxml2.h"
#include <cstdio>
#include <cstring>
#include <string>

using namespace tinyxml2;

// ============================================================================
// Test Fixture
// ============================================================================
class XMLDocumentTest_108 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// ============================================================================
// Constructor Tests
// ============================================================================
TEST_F(XMLDocumentTest_108, DefaultConstructor_ProcessEntitiesTrue_108) {
    XMLDocument doc(true, PRESERVE_WHITESPACE);
    EXPECT_TRUE(doc.ProcessEntities());
}

TEST_F(XMLDocumentTest_108, DefaultConstructor_ProcessEntitiesFalse_108) {
    XMLDocument doc(false, PRESERVE_WHITESPACE);
    EXPECT_FALSE(doc.ProcessEntities());
}

TEST_F(XMLDocumentTest_108, DefaultConstructor_DefaultArgs_108) {
    XMLDocument doc;
    EXPECT_TRUE(doc.ProcessEntities());
}

TEST_F(XMLDocumentTest_108, WhitespaceMode_Preserve_108) {
    XMLDocument doc(true, PRESERVE_WHITESPACE);
    EXPECT_EQ(PRESERVE_WHITESPACE, doc.WhitespaceMode());
}

TEST_F(XMLDocumentTest_108, WhitespaceMode_Collapse_108) {
    XMLDocument doc(true, COLLAPSE_WHITESPACE);
    EXPECT_EQ(COLLAPSE_WHITESPACE, doc.WhitespaceMode());
}

// ============================================================================
// BOM Tests
// ============================================================================
TEST_F(XMLDocumentTest_108, HasBOM_DefaultFalse_108) {
    XMLDocument doc;
    EXPECT_FALSE(doc.HasBOM());
}

TEST_F(XMLDocumentTest_108, SetBOM_True_108) {
    XMLDocument doc;
    doc.SetBOM(true);
    EXPECT_TRUE(doc.HasBOM());
}

TEST_F(XMLDocumentTest_108, SetBOM_FalseAfterTrue_108) {
    XMLDocument doc;
    doc.SetBOM(true);
    EXPECT_TRUE(doc.HasBOM());
    doc.SetBOM(false);
    EXPECT_FALSE(doc.HasBOM());
}

// ============================================================================
// Error Tests
// ============================================================================
TEST_F(XMLDocumentTest_108, NoError_InitialState_108) {
    XMLDocument doc;
    EXPECT_FALSE(doc.Error());
    EXPECT_EQ(XML_SUCCESS, doc.ErrorID());
}

TEST_F(XMLDocumentTest_108, ErrorLineNum_InitiallyZero_108) {
    XMLDocument doc;
    EXPECT_EQ(0, doc.ErrorLineNum());
}

TEST_F(XMLDocumentTest_108, ClearError_AfterError_108) {
    XMLDocument doc;
    doc.Parse("<unclosed");
    EXPECT_TRUE(doc.Error());
    doc.ClearError();
    EXPECT_FALSE(doc.Error());
    EXPECT_EQ(XML_SUCCESS, doc.ErrorID());
}

// ============================================================================
// Parse Tests
// ============================================================================
TEST_F(XMLDocumentTest_108, Parse_ValidXML_108) {
    XMLDocument doc;
    XMLError err = doc.Parse("<root><child/></root>");
    EXPECT_EQ(XML_SUCCESS, err);
    EXPECT_FALSE(doc.Error());
}

TEST_F(XMLDocumentTest_108, Parse_EmptyString_108) {
    XMLDocument doc;
    XMLError err = doc.Parse("");
    EXPECT_NE(XML_SUCCESS, err);
    EXPECT_TRUE(doc.Error());
}

TEST_F(XMLDocumentTest_108, Parse_NullPointer_108) {
    XMLDocument doc;
    XMLError err = doc.Parse(nullptr, 0);
    EXPECT_NE(XML_SUCCESS, err);
    EXPECT_TRUE(doc.Error());
}

TEST_F(XMLDocumentTest_108, Parse_MalformedXML_108) {
    XMLDocument doc;
    XMLError err = doc.Parse("<root><child></root>");
    EXPECT_NE(XML_SUCCESS, err);
    EXPECT_TRUE(doc.Error());
}

TEST_F(XMLDocumentTest_108, Parse_WithNBytes_108) {
    XMLDocument doc;
    const char* xml = "<root/>EXTRA_GARBAGE";
    XMLError err = doc.Parse(xml, 7); // Only "<root/>"
    EXPECT_EQ(XML_SUCCESS, err);
    EXPECT_FALSE(doc.Error());
}

TEST_F(XMLDocumentTest_108, Parse_WithDeclaration_108) {
    XMLDocument doc;
    XMLError err = doc.Parse("<?xml version=\"1.0\"?><root/>");
    EXPECT_EQ(XML_SUCCESS, err);
    EXPECT_FALSE(doc.Error());
}

TEST_F(XMLDocumentTest_108, Parse_WithEntities_108) {
    XMLDocument doc(true, PRESERVE_WHITESPACE);
    XMLError err = doc.Parse("<root attr=\"&amp;\"/>");
    EXPECT_EQ(XML_SUCCESS, err);
    EXPECT_FALSE(doc.Error());
}

TEST_F(XMLDocumentTest_108, Parse_WithoutProcessEntities_108) {
    XMLDocument doc(false, PRESERVE_WHITESPACE);
    XMLError err = doc.Parse("<root attr=\"&amp;\"/>");
    EXPECT_EQ(XML_SUCCESS, err);
    EXPECT_FALSE(doc.Error());
}

// ============================================================================
// RootElement Tests
// ============================================================================
TEST_F(XMLDocumentTest_108, RootElement_AfterParse_108) {
    XMLDocument doc;
    doc.Parse("<root/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(nullptr, root);
    EXPECT_STREQ("root", root->Name());
}

TEST_F(XMLDocumentTest_108, RootElement_EmptyDoc_108) {
    XMLDocument doc;
    XMLElement* root = doc.RootElement();
    EXPECT_EQ(nullptr, root);
}

// ============================================================================
// NewElement Tests
// ============================================================================
TEST_F(XMLDocumentTest_108, NewElement_Valid_108) {
    XMLDocument doc;
    XMLElement* elem = doc.NewElement("test");
    ASSERT_NE(nullptr, elem);
    EXPECT_STREQ("test", elem->Name());
}

// ============================================================================
// NewComment Tests
// ============================================================================
TEST_F(XMLDocumentTest_108, NewComment_Valid_108) {
    XMLDocument doc;
    XMLComment* comment = doc.NewComment("This is a comment");
    ASSERT_NE(nullptr, comment);
    EXPECT_STREQ("This is a comment", comment->Value());
}

// ============================================================================
// NewText Tests
// ============================================================================
TEST_F(XMLDocumentTest_108, NewText_Valid_108) {
    XMLDocument doc;
    XMLText* text = doc.NewText("Hello World");
    ASSERT_NE(nullptr, text);
    EXPECT_STREQ("Hello World", text->Value());
}

// ============================================================================
// NewDeclaration Tests
// ============================================================================
TEST_F(XMLDocumentTest_108, NewDeclaration_Default_108) {
    XMLDocument doc;
    XMLDeclaration* decl = doc.NewDeclaration();
    ASSERT_NE(nullptr, decl);
}

TEST_F(XMLDocumentTest_108, NewDeclaration_Custom_108) {
    XMLDocument doc;
    XMLDeclaration* decl = doc.NewDeclaration("xml version=\"1.0\"");
    ASSERT_NE(nullptr, decl);
}

// ============================================================================
// NewUnknown Tests
// ============================================================================
TEST_F(XMLDocumentTest_108, NewUnknown_Valid_108) {
    XMLDocument doc;
    XMLUnknown* unknown = doc.NewUnknown("something");
    ASSERT_NE(nullptr, unknown);
    EXPECT_STREQ("something", unknown->Value());
}

// ============================================================================
// DeleteNode Tests
// ============================================================================
TEST_F(XMLDocumentTest_108, DeleteNode_Element_108) {
    XMLDocument doc;
    doc.Parse("<root><child/></root>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(nullptr, root);
    XMLElement* child = root->FirstChildElement("child");
    ASSERT_NE(nullptr, child);
    doc.DeleteNode(child);
    EXPECT_EQ(nullptr, root->FirstChildElement("child"));
}

TEST_F(XMLDocumentTest_108, DeleteNode_NullSafe_108) {
    XMLDocument doc;
    // Should not crash
    doc.DeleteNode(nullptr);
}

// ============================================================================
// Clear Tests
// ============================================================================
TEST_F(XMLDocumentTest_108, Clear_RemovesContent_108) {
    XMLDocument doc;
    doc.Parse("<root><child/></root>");
    EXPECT_NE(nullptr, doc.RootElement());
    doc.Clear();
    EXPECT_EQ(nullptr, doc.RootElement());
    EXPECT_FALSE(doc.Error());
}

// ============================================================================
// DeepCopy Tests
// ============================================================================
TEST_F(XMLDocumentTest_108, DeepCopy_CopiesTree_108) {
    XMLDocument source;
    source.Parse("<root><child attr=\"val\">text</child></root>");
    ASSERT_FALSE(source.Error());

    XMLDocument target;
    source.DeepCopy(&target);

    XMLElement* targetRoot = target.RootElement();
    ASSERT_NE(nullptr, targetRoot);
    EXPECT_STREQ("root", targetRoot->Name());

    XMLElement* targetChild = targetRoot->FirstChildElement("child");
    ASSERT_NE(nullptr, targetChild);
    EXPECT_STREQ("val", targetChild->Attribute("attr"));
}

// ============================================================================
// ToDocument Tests
// ============================================================================
TEST_F(XMLDocumentTest_108, ToDocument_ReturnsSelf_108) {
    XMLDocument doc;
    EXPECT_EQ(&doc, doc.ToDocument());
}

// ============================================================================
// ShallowClone Tests
// ============================================================================
TEST_F(XMLDocumentTest_108, ShallowClone_ReturnsNull_108) {
    XMLDocument doc;
    EXPECT_EQ(nullptr, doc.ShallowClone(&doc));
}

// ============================================================================
// ShallowEqual Tests
// ============================================================================
TEST_F(XMLDocumentTest_108, ShallowEqual_ReturnsFalse_108) {
    XMLDocument doc1;
    XMLDocument doc2;
    EXPECT_FALSE(doc1.ShallowEqual(&doc2));
}

// ============================================================================
// ErrorName / ErrorIDToName Tests
// ============================================================================
TEST_F(XMLDocumentTest_108, ErrorIDToName_Success_108) {
    const char* name = XMLDocument::ErrorIDToName(XML_SUCCESS);
    ASSERT_NE(nullptr, name);
    EXPECT_STREQ("XML_SUCCESS", name);
}

TEST_F(XMLDocumentTest_108, ErrorName_NoError_108) {
    XMLDocument doc;
    const char* name = doc.ErrorName();
    ASSERT_NE(nullptr, name);
    EXPECT_STREQ("XML_SUCCESS", name);
}

TEST_F(XMLDocumentTest_108, ErrorName_AfterError_108) {
    XMLDocument doc;
    doc.Parse("<unclosed");
    EXPECT_TRUE(doc.Error());
    const char* name = doc.ErrorName();
    ASSERT_NE(nullptr, name);
    // Should not be XML_SUCCESS
    EXPECT_STRNE("XML_SUCCESS", name);
}

TEST_F(XMLDocumentTest_108, ErrorStr_NoError_108) {
    XMLDocument doc;
    const char* errStr = doc.ErrorStr();
    ASSERT_NE(nullptr, errStr);
}

TEST_F(XMLDocumentTest_108, ErrorStr_AfterError_108) {
    XMLDocument doc;
    doc.Parse("<root><unclosed");
    EXPECT_TRUE(doc.Error());
    const char* errStr = doc.ErrorStr();
    ASSERT_NE(nullptr, errStr);
    EXPECT_GT(strlen(errStr), 0u);
}

// ============================================================================
// LoadFile / SaveFile Tests
// ============================================================================
TEST_F(XMLDocumentTest_108, LoadFile_NonExistent_108) {
    XMLDocument doc;
    XMLError err = doc.LoadFile("non_existent_file_108.xml");
    EXPECT_NE(XML_SUCCESS, err);
    EXPECT_TRUE(doc.Error());
}

TEST_F(XMLDocumentTest_108, SaveFile_AndLoadFile_Roundtrip_108) {
    const char* filename = "test_roundtrip_108.xml";

    // Save
    {
        XMLDocument doc;
        doc.Parse("<root><child attr=\"value\">text</child></root>");
        ASSERT_FALSE(doc.Error());
        XMLError err = doc.SaveFile(filename, false);
        EXPECT_EQ(XML_SUCCESS, err);
    }

    // Load
    {
        XMLDocument doc;
        XMLError err = doc.LoadFile(filename);
        EXPECT_EQ(XML_SUCCESS, err);
        EXPECT_FALSE(doc.Error());

        XMLElement* root = doc.RootElement();
        ASSERT_NE(nullptr, root);
        EXPECT_STREQ("root", root->Name());

        XMLElement* child = root->FirstChildElement("child");
        ASSERT_NE(nullptr, child);
        EXPECT_STREQ("value", child->Attribute("attr"));
    }

    // Cleanup
    std::remove(filename);
}

TEST_F(XMLDocumentTest_108, SaveFile_FILE_Roundtrip_108) {
    const char* filename = "test_file_ptr_108.xml";

    // Save using FILE*
    {
        XMLDocument doc;
        doc.Parse("<data>hello</data>");
        ASSERT_FALSE(doc.Error());

        FILE* fp = fopen(filename, "w");
        ASSERT_NE(nullptr, fp);
        XMLError err = doc.SaveFile(fp, false);
        fclose(fp);
        EXPECT_EQ(XML_SUCCESS, err);
    }

    // Load using FILE*
    {
        XMLDocument doc;
        FILE* fp = fopen(filename, "r");
        ASSERT_NE(nullptr, fp);
        XMLError err = doc.LoadFile(fp);
        fclose(fp);
        EXPECT_EQ(XML_SUCCESS, err);

        XMLElement* root = doc.RootElement();
        ASSERT_NE(nullptr, root);
        EXPECT_STREQ("data", root->Name());
    }

    std::remove(filename);
}

TEST_F(XMLDocumentTest_108, SaveFile_Compact_108) {
    const char* filename = "test_compact_108.xml";

    XMLDocument doc;
    doc.Parse("<root> <child/> </root>");
    ASSERT_FALSE(doc.Error());

    XMLError err = doc.SaveFile(filename, true);
    EXPECT_EQ(XML_SUCCESS, err);

    std::remove(filename);
}

// ============================================================================
// Print Tests
// ============================================================================
TEST_F(XMLDocumentTest_108, Print_DefaultPrinter_108) {
    XMLDocument doc;
    doc.Parse("<root><child/></root>");
    ASSERT_FALSE(doc.Error());

    XMLPrinter printer;
    doc.Print(&printer);
    const char* result = printer.CStr();
    ASSERT_NE(nullptr, result);
    EXPECT_NE(std::string::npos, std::string(result).find("root"));
    EXPECT_NE(std::string::npos, std::string(result).find("child"));
}

TEST_F(XMLDocumentTest_108, Print_NullPrinter_UsesStdout_108) {
    XMLDocument doc;
    doc.Parse("<root/>");
    ASSERT_FALSE(doc.Error());
    // Passing nullptr should print to stdout - just verify no crash
    doc.Print(nullptr);
}

// ============================================================================
// Accept (Visitor Pattern) Tests
// ============================================================================
TEST_F(XMLDocumentTest_108, Accept_WithVisitor_108) {
    XMLDocument doc;
    doc.Parse("<root/>");
    ASSERT_FALSE(doc.Error());

    XMLPrinter printer;
    bool result = doc.Accept(&printer);
    EXPECT_TRUE(result);
}

// ============================================================================
// Multiple Parse Calls
// ============================================================================
TEST_F(XMLDocumentTest_108, Parse_MultipleTimes_ReplacesContent_108) {
    XMLDocument doc;

    doc.Parse("<first/>");
    ASSERT_FALSE(doc.Error());
    ASSERT_NE(nullptr, doc.RootElement());
    EXPECT_STREQ("first", doc.RootElement()->Name());

    doc.Parse("<second/>");
    ASSERT_FALSE(doc.Error());
    ASSERT_NE(nullptr, doc.RootElement());
    EXPECT_STREQ("second", doc.RootElement()->Name());
}

// ============================================================================
// Complex XML Tests
// ============================================================================
TEST_F(XMLDocumentTest_108, Parse_ComplexXML_108) {
    const char* xml =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>"
        "<root>"
        "  <element attr1=\"val1\" attr2=\"val2\">"
        "    <nested>text content</nested>"
        "    <!-- comment -->"
        "  </element>"
        "  <empty/>"
        "</root>";

    XMLDocument doc;
    XMLError err = doc.Parse(xml);
    EXPECT_EQ(XML_SUCCESS, err);
    EXPECT_FALSE(doc.Error());

    XMLElement* root = doc.RootElement();
    ASSERT_NE(nullptr, root);
    EXPECT_STREQ("root", root->Name());

    XMLElement* element = root->FirstChildElement("element");
    ASSERT_NE(nullptr, element);
    EXPECT_STREQ("val1", element->Attribute("attr1"));
    EXPECT_STREQ("val2", element->Attribute("attr2"));

    XMLElement* nested = element->FirstChildElement("nested");
    ASSERT_NE(nullptr, nested);
    EXPECT_STREQ("text content", nested->GetText());

    XMLElement* empty = root->FirstChildElement("empty");
    ASSERT_NE(nullptr, empty);
}

// ============================================================================
// Error after Clear
// ============================================================================
TEST_F(XMLDocumentTest_108, Clear_ResetsError_108) {
    XMLDocument doc;
    doc.Parse("<bad");
    EXPECT_TRUE(doc.Error());
    doc.Clear();
    EXPECT_FALSE(doc.Error());
    EXPECT_EQ(XML_SUCCESS, doc.ErrorID());
}

// ============================================================================
// InsertNode and tree manipulation
// ============================================================================
TEST_F(XMLDocumentTest_108, InsertNewElementAsChild_108) {
    XMLDocument doc;
    doc.Parse("<root/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(nullptr, root);

    XMLElement* newElem = doc.NewElement("added");
    root->InsertEndChild(newElem);

    XMLElement* found = root->FirstChildElement("added");
    ASSERT_NE(nullptr, found);
    EXPECT_STREQ("added", found->Name());
}

TEST_F(XMLDocumentTest_108, InsertCommentInDocument_108) {
    XMLDocument doc;
    XMLComment* comment = doc.NewComment("test comment");
    doc.InsertFirstChild(comment);

    // Parse should still work after adding nodes manually, but let's verify
    // the comment is there
    XMLPrinter printer;
    doc.Print(&printer);
    std::string output = printer.CStr();
    EXPECT_NE(std::string::npos, output.find("test comment"));
}

// ============================================================================
// ErrorIDToName for various error codes
// ============================================================================
TEST_F(XMLDocumentTest_108, ErrorIDToName_FileNotFound_108) {
    const char* name = XMLDocument::ErrorIDToName(XML_ERROR_FILE_NOT_FOUND);
    ASSERT_NE(nullptr, name);
    EXPECT_GT(strlen(name), 0u);
}

TEST_F(XMLDocumentTest_108, ErrorIDToName_EmptyDocument_108) {
    const char* name = XMLDocument::ErrorIDToName(XML_ERROR_EMPTY_DOCUMENT);
    ASSERT_NE(nullptr, name);
    EXPECT_GT(strlen(name), 0u);
}

// ============================================================================
// Parse with whitespace modes
// ============================================================================
TEST_F(XMLDocumentTest_108, Parse_CollapseWhitespace_108) {
    XMLDocument doc(true, COLLAPSE_WHITESPACE);
    XMLError err = doc.Parse("<root>  hello   world  </root>");
    EXPECT_EQ(XML_SUCCESS, err);
    EXPECT_FALSE(doc.Error());
}

TEST_F(XMLDocumentTest_108, Parse_PreserveWhitespace_108) {
    XMLDocument doc(true, PRESERVE_WHITESPACE);
    XMLError err = doc.Parse("<root>  hello   world  </root>");
    EXPECT_EQ(XML_SUCCESS, err);
    EXPECT_FALSE(doc.Error());
}
