#include "gtest/gtest.h"
#include "tinyxml2.h"
#include <cstdio>
#include <cstring>
#include <string>

using namespace tinyxml2;

// ============================================================
// Test Fixture
// ============================================================
class XMLDocumentTest_115 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// ============================================================
// Construction and Default State
// ============================================================

TEST_F(XMLDocumentTest_115, DefaultConstructor_NoError_115) {
    XMLDocument doc;
    EXPECT_FALSE(doc.Error());
    EXPECT_EQ(doc.ErrorID(), XML_SUCCESS);
    EXPECT_EQ(doc.ErrorLineNum(), 0);
}

TEST_F(XMLDocumentTest_115, DefaultConstructor_ProcessEntitiesTrue_115) {
    XMLDocument doc(true);
    EXPECT_TRUE(doc.ProcessEntities());
}

TEST_F(XMLDocumentTest_115, DefaultConstructor_ProcessEntitiesFalse_115) {
    XMLDocument doc(false);
    EXPECT_FALSE(doc.ProcessEntities());
}

TEST_F(XMLDocumentTest_115, DefaultConstructor_HasBOMFalse_115) {
    XMLDocument doc;
    EXPECT_FALSE(doc.HasBOM());
}

TEST_F(XMLDocumentTest_115, DefaultConstructor_WhitespacePreserve_115) {
    XMLDocument doc(true, PRESERVE_WHITESPACE);
    EXPECT_EQ(doc.WhitespaceMode(), PRESERVE_WHITESPACE);
}

TEST_F(XMLDocumentTest_115, DefaultConstructor_WhitespaceCollapse_115) {
    XMLDocument doc(true, COLLAPSE_WHITESPACE);
    EXPECT_EQ(doc.WhitespaceMode(), COLLAPSE_WHITESPACE);
}

// ============================================================
// BOM
// ============================================================

TEST_F(XMLDocumentTest_115, SetBOM_True_115) {
    XMLDocument doc;
    doc.SetBOM(true);
    EXPECT_TRUE(doc.HasBOM());
}

TEST_F(XMLDocumentTest_115, SetBOM_False_115) {
    XMLDocument doc;
    doc.SetBOM(true);
    doc.SetBOM(false);
    EXPECT_FALSE(doc.HasBOM());
}

// ============================================================
// Parse
// ============================================================

TEST_F(XMLDocumentTest_115, Parse_ValidXML_115) {
    XMLDocument doc;
    XMLError err = doc.Parse("<root><child/></root>");
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_FALSE(doc.Error());
    EXPECT_EQ(doc.ErrorLineNum(), 0);
}

TEST_F(XMLDocumentTest_115, Parse_EmptyString_115) {
    XMLDocument doc;
    XMLError err = doc.Parse("");
    EXPECT_NE(err, XML_SUCCESS);
    EXPECT_TRUE(doc.Error());
}

TEST_F(XMLDocumentTest_115, Parse_NullPointer_115) {
    XMLDocument doc;
    XMLError err = doc.Parse(nullptr, 0);
    EXPECT_NE(err, XML_SUCCESS);
    EXPECT_TRUE(doc.Error());
}

TEST_F(XMLDocumentTest_115, Parse_MalformedXML_115) {
    XMLDocument doc;
    XMLError err = doc.Parse("<root><child></root>");
    EXPECT_NE(err, XML_SUCCESS);
    EXPECT_TRUE(doc.Error());
    EXPECT_NE(doc.ErrorLineNum(), 0);  // Should point to an error line
}

TEST_F(XMLDocumentTest_115, Parse_WithNBytes_115) {
    XMLDocument doc;
    const char* xml = "<root/>GARBAGE";
    XMLError err = doc.Parse(xml, 7);  // only "<root/>"
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_FALSE(doc.Error());
}

TEST_F(XMLDocumentTest_115, Parse_WithDeclaration_115) {
    XMLDocument doc;
    XMLError err = doc.Parse("<?xml version=\"1.0\"?><root/>");
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_FALSE(doc.Error());
}

TEST_F(XMLDocumentTest_115, Parse_MultiLineErrorReportsLineNum_115) {
    XMLDocument doc;
    const char* xml = "<root>\n<child>\n</root>";
    XMLError err = doc.Parse(xml);
    EXPECT_NE(err, XML_SUCCESS);
    EXPECT_TRUE(doc.Error());
    EXPECT_GT(doc.ErrorLineNum(), 0);
}

// ============================================================
// RootElement
// ============================================================

TEST_F(XMLDocumentTest_115, RootElement_AfterParse_115) {
    XMLDocument doc;
    doc.Parse("<root/>");
    XMLElement* root = doc.RootElement();
    EXPECT_NE(root, nullptr);
    EXPECT_STREQ(root->Name(), "root");
}

TEST_F(XMLDocumentTest_115, RootElement_EmptyDocument_115) {
    XMLDocument doc;
    XMLElement* root = doc.RootElement();
    EXPECT_EQ(root, nullptr);
}

// ============================================================
// Error functions
// ============================================================

TEST_F(XMLDocumentTest_115, ErrorID_AfterSuccessfulParse_115) {
    XMLDocument doc;
    doc.Parse("<root/>");
    EXPECT_EQ(doc.ErrorID(), XML_SUCCESS);
}

TEST_F(XMLDocumentTest_115, ErrorID_AfterFailedParse_115) {
    XMLDocument doc;
    doc.Parse("<root>");
    EXPECT_NE(doc.ErrorID(), XML_SUCCESS);
}

TEST_F(XMLDocumentTest_115, ErrorName_AfterSuccess_115) {
    XMLDocument doc;
    doc.Parse("<root/>");
    const char* name = doc.ErrorName();
    EXPECT_NE(name, nullptr);
    EXPECT_STREQ(name, "XML_SUCCESS");
}

TEST_F(XMLDocumentTest_115, ErrorStr_AfterError_115) {
    XMLDocument doc;
    doc.Parse("<root>");
    const char* errStr = doc.ErrorStr();
    EXPECT_NE(errStr, nullptr);
    EXPECT_GT(strlen(errStr), 0u);
}

TEST_F(XMLDocumentTest_115, ErrorLineNum_NoError_IsZero_115) {
    XMLDocument doc;
    EXPECT_EQ(doc.ErrorLineNum(), 0);
}

TEST_F(XMLDocumentTest_115, ErrorLineNum_AfterSuccessfulParse_115) {
    XMLDocument doc;
    doc.Parse("<root/>");
    EXPECT_EQ(doc.ErrorLineNum(), 0);
}

TEST_F(XMLDocumentTest_115, ClearError_ResetsError_115) {
    XMLDocument doc;
    doc.Parse("<root>");
    EXPECT_TRUE(doc.Error());
    doc.ClearError();
    EXPECT_FALSE(doc.Error());
    EXPECT_EQ(doc.ErrorID(), XML_SUCCESS);
    EXPECT_EQ(doc.ErrorLineNum(), 0);
}

TEST_F(XMLDocumentTest_115, ErrorIDToName_Success_115) {
    const char* name = XMLDocument::ErrorIDToName(XML_SUCCESS);
    EXPECT_NE(name, nullptr);
    EXPECT_STREQ(name, "XML_SUCCESS");
}

TEST_F(XMLDocumentTest_115, ErrorIDToName_ErrorFileNotFound_115) {
    const char* name = XMLDocument::ErrorIDToName(XML_ERROR_FILE_NOT_FOUND);
    EXPECT_NE(name, nullptr);
    EXPECT_STRNE(name, "XML_SUCCESS");
}

// ============================================================
// NewElement / NewComment / NewText / NewDeclaration / NewUnknown
// ============================================================

TEST_F(XMLDocumentTest_115, NewElement_ReturnsNonNull_115) {
    XMLDocument doc;
    XMLElement* elem = doc.NewElement("test");
    EXPECT_NE(elem, nullptr);
    EXPECT_STREQ(elem->Name(), "test");
    doc.DeleteNode(elem);
}

TEST_F(XMLDocumentTest_115, NewComment_ReturnsNonNull_115) {
    XMLDocument doc;
    XMLComment* comment = doc.NewComment("a comment");
    EXPECT_NE(comment, nullptr);
    EXPECT_STREQ(comment->Value(), "a comment");
    doc.DeleteNode(comment);
}

TEST_F(XMLDocumentTest_115, NewText_ReturnsNonNull_115) {
    XMLDocument doc;
    XMLText* text = doc.NewText("hello");
    EXPECT_NE(text, nullptr);
    EXPECT_STREQ(text->Value(), "hello");
    doc.DeleteNode(text);
}

TEST_F(XMLDocumentTest_115, NewDeclaration_ReturnsNonNull_115) {
    XMLDocument doc;
    XMLDeclaration* decl = doc.NewDeclaration();
    EXPECT_NE(decl, nullptr);
    doc.DeleteNode(decl);
}

TEST_F(XMLDocumentTest_115, NewDeclaration_CustomText_115) {
    XMLDocument doc;
    XMLDeclaration* decl = doc.NewDeclaration("xml version=\"1.0\"");
    EXPECT_NE(decl, nullptr);
    doc.DeleteNode(decl);
}

TEST_F(XMLDocumentTest_115, NewUnknown_ReturnsNonNull_115) {
    XMLDocument doc;
    XMLUnknown* unknown = doc.NewUnknown("something");
    EXPECT_NE(unknown, nullptr);
    EXPECT_STREQ(unknown->Value(), "something");
    doc.DeleteNode(unknown);
}

// ============================================================
// DeleteNode
// ============================================================

TEST_F(XMLDocumentTest_115, DeleteNode_UnlinkedElement_115) {
    XMLDocument doc;
    XMLElement* elem = doc.NewElement("todelete");
    EXPECT_NE(elem, nullptr);
    doc.DeleteNode(elem);
    // No crash = pass
}

TEST_F(XMLDocumentTest_115, DeleteNode_LinkedElement_115) {
    XMLDocument doc;
    doc.Parse("<root><child/></root>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    XMLElement* child = root->FirstChildElement("child");
    ASSERT_NE(child, nullptr);
    doc.DeleteNode(child);
    EXPECT_EQ(root->FirstChildElement("child"), nullptr);
}

// ============================================================
// Clear
// ============================================================

TEST_F(XMLDocumentTest_115, Clear_RemovesAllContent_115) {
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

TEST_F(XMLDocumentTest_115, DeepCopy_CopiesContent_115) {
    XMLDocument doc;
    doc.Parse("<root><child attr=\"val\">text</child></root>");
    ASSERT_FALSE(doc.Error());

    XMLDocument target;
    doc.DeepCopy(&target);

    EXPECT_NE(target.RootElement(), nullptr);
    EXPECT_STREQ(target.RootElement()->Name(), "root");
    XMLElement* child = target.RootElement()->FirstChildElement("child");
    ASSERT_NE(child, nullptr);
    EXPECT_STREQ(child->Attribute("attr"), "val");
    EXPECT_STREQ(child->GetText(), "text");
}

TEST_F(XMLDocumentTest_115, DeepCopy_EmptyDocument_115) {
    XMLDocument doc;
    XMLDocument target;
    target.Parse("<old/>");
    doc.DeepCopy(&target);
    EXPECT_EQ(target.RootElement(), nullptr);
}

// ============================================================
// ToDocument
// ============================================================

TEST_F(XMLDocumentTest_115, ToDocument_ReturnsSelf_115) {
    XMLDocument doc;
    EXPECT_EQ(doc.ToDocument(), &doc);
}

// ============================================================
// ShallowClone / ShallowEqual
// ============================================================

TEST_F(XMLDocumentTest_115, ShallowClone_ReturnsNull_115) {
    XMLDocument doc;
    XMLNode* clone = doc.ShallowClone(&doc);
    EXPECT_EQ(clone, nullptr);
}

TEST_F(XMLDocumentTest_115, ShallowEqual_ReturnsFalse_115) {
    XMLDocument doc1;
    XMLDocument doc2;
    EXPECT_FALSE(doc1.ShallowEqual(&doc2));
}

// ============================================================
// SaveFile / LoadFile (file-based)
// ============================================================

TEST_F(XMLDocumentTest_115, SaveAndLoadFile_ByName_115) {
    const char* filename = "test_save_load_115.xml";
    {
        XMLDocument doc;
        doc.Parse("<root><item>data</item></root>");
        ASSERT_FALSE(doc.Error());
        XMLError err = doc.SaveFile(filename, false);
        EXPECT_EQ(err, XML_SUCCESS);
    }
    {
        XMLDocument doc;
        XMLError err = doc.LoadFile(filename);
        EXPECT_EQ(err, XML_SUCCESS);
        EXPECT_FALSE(doc.Error());
        ASSERT_NE(doc.RootElement(), nullptr);
        EXPECT_STREQ(doc.RootElement()->Name(), "root");
    }
    std::remove(filename);
}

TEST_F(XMLDocumentTest_115, SaveAndLoadFile_ByFILE_115) {
    const char* filename = "test_save_load_fp_115.xml";
    {
        XMLDocument doc;
        doc.Parse("<root>content</root>");
        ASSERT_FALSE(doc.Error());
        FILE* fp = fopen(filename, "w");
        ASSERT_NE(fp, nullptr);
        XMLError err = doc.SaveFile(fp, false);
        fclose(fp);
        EXPECT_EQ(err, XML_SUCCESS);
    }
    {
        XMLDocument doc;
        FILE* fp = fopen(filename, "r");
        ASSERT_NE(fp, nullptr);
        XMLError err = doc.LoadFile(fp);
        fclose(fp);
        EXPECT_EQ(err, XML_SUCCESS);
        ASSERT_NE(doc.RootElement(), nullptr);
        EXPECT_STREQ(doc.RootElement()->Name(), "root");
    }
    std::remove(filename);
}

TEST_F(XMLDocumentTest_115, SaveFile_Compact_115) {
    const char* filename = "test_compact_115.xml";
    XMLDocument doc;
    doc.Parse("<root> <child/> </root>");
    ASSERT_FALSE(doc.Error());
    XMLError err = doc.SaveFile(filename, true);
    EXPECT_EQ(err, XML_SUCCESS);
    std::remove(filename);
}

TEST_F(XMLDocumentTest_115, LoadFile_NonExistent_115) {
    XMLDocument doc;
    XMLError err = doc.LoadFile("non_existent_file_115.xml");
    EXPECT_NE(err, XML_SUCCESS);
    EXPECT_TRUE(doc.Error());
    EXPECT_EQ(doc.ErrorID(), XML_ERROR_FILE_NOT_FOUND);
}

TEST_F(XMLDocumentTest_115, LoadFile_NullFILE_115) {
    XMLDocument doc;
    XMLError err = doc.LoadFile((FILE*)nullptr);
    EXPECT_NE(err, XML_SUCCESS);
    EXPECT_TRUE(doc.Error());
}

// ============================================================
// Print
// ============================================================

TEST_F(XMLDocumentTest_115, Print_DefaultPrinter_115) {
    XMLDocument doc;
    doc.Parse("<root><child/></root>");
    ASSERT_FALSE(doc.Error());

    XMLPrinter printer;
    doc.Print(&printer);
    const char* result = printer.CStr();
    EXPECT_NE(result, nullptr);
    EXPECT_NE(std::string(result).find("root"), std::string::npos);
    EXPECT_NE(std::string(result).find("child"), std::string::npos);
}

TEST_F(XMLDocumentTest_115, Print_NullPrinter_UsesStdout_115) {
    XMLDocument doc;
    doc.Parse("<root/>");
    ASSERT_FALSE(doc.Error());
    // Passing null should print to stdout (no crash)
    doc.Print(nullptr);
}

// ============================================================
// Accept
// ============================================================

TEST_F(XMLDocumentTest_115, Accept_WithPrinter_115) {
    XMLDocument doc;
    doc.Parse("<root attr=\"1\"/>");
    ASSERT_FALSE(doc.Error());

    XMLPrinter printer;
    bool result = doc.Accept(&printer);
    EXPECT_TRUE(result);
    const char* output = printer.CStr();
    EXPECT_NE(output, nullptr);
    EXPECT_NE(std::string(output).find("root"), std::string::npos);
}

// ============================================================
// Process Entities
// ============================================================

TEST_F(XMLDocumentTest_115, ParseWithEntities_115) {
    XMLDocument doc(true);
    doc.Parse("<root>&amp;</root>");
    ASSERT_FALSE(doc.Error());
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    EXPECT_STREQ(root->GetText(), "&");
}

TEST_F(XMLDocumentTest_115, ParseWithoutEntities_115) {
    XMLDocument doc(false);
    doc.Parse("<root>&amp;</root>");
    ASSERT_FALSE(doc.Error());
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    EXPECT_STREQ(root->GetText(), "&amp;");
}

// ============================================================
// Whitespace handling
// ============================================================

TEST_F(XMLDocumentTest_115, PreserveWhitespace_115) {
    XMLDocument doc(true, PRESERVE_WHITESPACE);
    doc.Parse("<root>  text  </root>");
    ASSERT_FALSE(doc.Error());
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    const char* text = root->GetText();
    ASSERT_NE(text, nullptr);
    EXPECT_NE(std::string(text).find("  text  "), std::string::npos);
}

// ============================================================
// Repeated Parse
// ============================================================

TEST_F(XMLDocumentTest_115, RepeatedParse_ClearsPrevious_115) {
    XMLDocument doc;
    doc.Parse("<first/>");
    ASSERT_FALSE(doc.Error());
    EXPECT_STREQ(doc.RootElement()->Name(), "first");

    doc.Parse("<second/>");
    ASSERT_FALSE(doc.Error());
    EXPECT_STREQ(doc.RootElement()->Name(), "second");
}

// ============================================================
// Complex document
// ============================================================

TEST_F(XMLDocumentTest_115, Parse_ComplexDocument_115) {
    const char* xml =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<root>\n"
        "  <child1 attr1=\"value1\" attr2=\"value2\">\n"
        "    <grandchild>Text content</grandchild>\n"
        "  </child1>\n"
        "  <child2/>\n"
        "  <!-- A comment -->\n"
        "</root>";
    XMLDocument doc;
    XMLError err = doc.Parse(xml);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_FALSE(doc.Error());
    EXPECT_EQ(doc.ErrorLineNum(), 0);

    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    EXPECT_STREQ(root->Name(), "root");

    XMLElement* child1 = root->FirstChildElement("child1");
    ASSERT_NE(child1, nullptr);
    EXPECT_STREQ(child1->Attribute("attr1"), "value1");
    EXPECT_STREQ(child1->Attribute("attr2"), "value2");

    XMLElement* grandchild = child1->FirstChildElement("grandchild");
    ASSERT_NE(grandchild, nullptr);
    EXPECT_STREQ(grandchild->GetText(), "Text content");

    XMLElement* child2 = root->FirstChildElement("child2");
    EXPECT_NE(child2, nullptr);
}

// ============================================================
// PrintError (just ensure no crash)
// ============================================================

TEST_F(XMLDocumentTest_115, PrintError_NoError_115) {
    XMLDocument doc;
    doc.Parse("<root/>");
    doc.PrintError();
    // No crash = pass
}

TEST_F(XMLDocumentTest_115, PrintError_WithError_115) {
    XMLDocument doc;
    doc.Parse("<root>");
    ASSERT_TRUE(doc.Error());
    doc.PrintError();
    // No crash = pass
}

// ============================================================
// Edge cases
// ============================================================

TEST_F(XMLDocumentTest_115, Parse_OnlyWhitespace_115) {
    XMLDocument doc;
    XMLError err = doc.Parse("   \n\t  ");
    EXPECT_NE(err, XML_SUCCESS);
    EXPECT_TRUE(doc.Error());
}

TEST_F(XMLDocumentTest_115, Parse_JustDeclaration_115) {
    XMLDocument doc;
    XMLError err = doc.Parse("<?xml version=\"1.0\"?>");
    // A document with only a declaration and no root element
    // Depends on implementation, but root should be null
    EXPECT_EQ(doc.RootElement(), nullptr);
}

TEST_F(XMLDocumentTest_115, Parse_MultipleRootElements_115) {
    XMLDocument doc;
    XMLError err = doc.Parse("<a/><b/>");
    // tinyxml2 allows this - second element is a sibling
    // Just check it doesn't crash and first root is accessible
    if (err == XML_SUCCESS) {
        EXPECT_NE(doc.RootElement(), nullptr);
    }
}

TEST_F(XMLDocumentTest_115, NewElement_NullName_115) {
    XMLDocument doc;
    XMLElement* elem = doc.NewElement(nullptr);
    // Should handle gracefully (implementation-dependent)
    // Just check we can delete it without crash
    if (elem) {
        doc.DeleteNode(elem);
    }
}

TEST_F(XMLDocumentTest_115, MarkInUse_NodesAreProtected_115) {
    XMLDocument doc;
    doc.Parse("<root><child/></root>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    // MarkInUse should not crash
    doc.MarkInUse(root);
}
