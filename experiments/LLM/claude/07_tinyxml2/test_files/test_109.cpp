#include <gtest/gtest.h>
#include <cstdio>
#include <cstring>
#include <string>
#include "tinyxml2.h"

using namespace tinyxml2;

// =============================================================================
// Test Fixture
// =============================================================================
class XMLDocumentTest_109 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// =============================================================================
// Constructor and Default State Tests
// =============================================================================

TEST_F(XMLDocumentTest_109, DefaultConstructor_NoError_109) {
    XMLDocument doc;
    EXPECT_FALSE(doc.Error());
    EXPECT_EQ(doc.ErrorID(), XML_SUCCESS);
}

TEST_F(XMLDocumentTest_109, DefaultConstructor_WhitespacePreserve_109) {
    XMLDocument doc(true, PRESERVE_WHITESPACE);
    EXPECT_EQ(doc.WhitespaceMode(), PRESERVE_WHITESPACE);
}

TEST_F(XMLDocumentTest_109, DefaultConstructor_WhitespaceCollapse_109) {
    XMLDocument doc(true, COLLAPSE_WHITESPACE);
    EXPECT_EQ(doc.WhitespaceMode(), COLLAPSE_WHITESPACE);
}

TEST_F(XMLDocumentTest_109, DefaultConstructor_ProcessEntitiesTrue_109) {
    XMLDocument doc(true);
    EXPECT_TRUE(doc.ProcessEntities());
}

TEST_F(XMLDocumentTest_109, DefaultConstructor_ProcessEntitiesFalse_109) {
    XMLDocument doc(false);
    EXPECT_FALSE(doc.ProcessEntities());
}

TEST_F(XMLDocumentTest_109, DefaultConstructor_NoBOM_109) {
    XMLDocument doc;
    EXPECT_FALSE(doc.HasBOM());
}

TEST_F(XMLDocumentTest_109, DefaultConstructor_NoRootElement_109) {
    XMLDocument doc;
    EXPECT_EQ(doc.RootElement(), nullptr);
}

TEST_F(XMLDocumentTest_109, DefaultConstructor_ErrorLineNumZero_109) {
    XMLDocument doc;
    EXPECT_EQ(doc.ErrorLineNum(), 0);
}

// =============================================================================
// Parse Tests
// =============================================================================

TEST_F(XMLDocumentTest_109, ParseSimpleXML_109) {
    XMLDocument doc;
    XMLError err = doc.Parse("<root/>");
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_FALSE(doc.Error());
    EXPECT_NE(doc.RootElement(), nullptr);
    EXPECT_STREQ(doc.RootElement()->Name(), "root");
}

TEST_F(XMLDocumentTest_109, ParseXMLWithChildren_109) {
    XMLDocument doc;
    XMLError err = doc.Parse("<root><child/></root>");
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_NE(doc.RootElement(), nullptr);
    EXPECT_NE(doc.RootElement()->FirstChildElement("child"), nullptr);
}

TEST_F(XMLDocumentTest_109, ParseXMLWithAttributes_109) {
    XMLDocument doc;
    XMLError err = doc.Parse("<root attr=\"value\"/>");
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_NE(doc.RootElement(), nullptr);
    EXPECT_STREQ(doc.RootElement()->Attribute("attr"), "value");
}

TEST_F(XMLDocumentTest_109, ParseXMLWithText_109) {
    XMLDocument doc;
    XMLError err = doc.Parse("<root>Hello World</root>");
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_NE(doc.RootElement(), nullptr);
    EXPECT_STREQ(doc.RootElement()->GetText(), "Hello World");
}

TEST_F(XMLDocumentTest_109, ParseEmptyString_109) {
    XMLDocument doc;
    XMLError err = doc.Parse("");
    EXPECT_NE(err, XML_SUCCESS);
    EXPECT_TRUE(doc.Error());
}

TEST_F(XMLDocumentTest_109, ParseNullPointer_109) {
    XMLDocument doc;
    XMLError err = doc.Parse(nullptr, 0);
    EXPECT_NE(err, XML_SUCCESS);
    EXPECT_TRUE(doc.Error());
}

TEST_F(XMLDocumentTest_109, ParseMalformedXML_109) {
    XMLDocument doc;
    XMLError err = doc.Parse("<root><unclosed>");
    EXPECT_NE(err, XML_SUCCESS);
    EXPECT_TRUE(doc.Error());
}

TEST_F(XMLDocumentTest_109, ParseWithExplicitLength_109) {
    XMLDocument doc;
    const char* xml = "<root/>EXTRAGARBAGE";
    XMLError err = doc.Parse(xml, 7); // Only "<root/>"
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_NE(doc.RootElement(), nullptr);
}

TEST_F(XMLDocumentTest_109, ParseXMLDeclaration_109) {
    XMLDocument doc;
    XMLError err = doc.Parse("<?xml version=\"1.0\"?><root/>");
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_NE(doc.RootElement(), nullptr);
}

TEST_F(XMLDocumentTest_109, ParseXMLWithComment_109) {
    XMLDocument doc;
    XMLError err = doc.Parse("<!-- comment --><root/>");
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_NE(doc.RootElement(), nullptr);
}

TEST_F(XMLDocumentTest_109, ParseOverwritesPreviousContent_109) {
    XMLDocument doc;
    doc.Parse("<first/>");
    EXPECT_STREQ(doc.RootElement()->Name(), "first");
    doc.Parse("<second/>");
    EXPECT_STREQ(doc.RootElement()->Name(), "second");
}

// =============================================================================
// BOM Tests
// =============================================================================

TEST_F(XMLDocumentTest_109, SetBOMTrue_109) {
    XMLDocument doc;
    doc.SetBOM(true);
    EXPECT_TRUE(doc.HasBOM());
}

TEST_F(XMLDocumentTest_109, SetBOMFalse_109) {
    XMLDocument doc;
    doc.SetBOM(true);
    doc.SetBOM(false);
    EXPECT_FALSE(doc.HasBOM());
}

// =============================================================================
// Error Handling Tests
// =============================================================================

TEST_F(XMLDocumentTest_109, ClearErrorAfterParseFailure_109) {
    XMLDocument doc;
    doc.Parse("<invalid");
    EXPECT_TRUE(doc.Error());
    doc.ClearError();
    EXPECT_FALSE(doc.Error());
    EXPECT_EQ(doc.ErrorID(), XML_SUCCESS);
}

TEST_F(XMLDocumentTest_109, ErrorNameForSuccess_109) {
    XMLDocument doc;
    doc.Parse("<root/>");
    EXPECT_NE(doc.ErrorName(), nullptr);
}

TEST_F(XMLDocumentTest_109, ErrorIDToName_Success_109) {
    const char* name = XMLDocument::ErrorIDToName(XML_SUCCESS);
    EXPECT_NE(name, nullptr);
    EXPECT_STRNE(name, "");
}

TEST_F(XMLDocumentTest_109, ErrorIDToName_ErrorFileNotFound_109) {
    const char* name = XMLDocument::ErrorIDToName(XML_ERROR_FILE_NOT_FOUND);
    EXPECT_NE(name, nullptr);
    EXPECT_STRNE(name, "");
}

TEST_F(XMLDocumentTest_109, ErrorStr_NoError_109) {
    XMLDocument doc;
    doc.Parse("<root/>");
    // ErrorStr should return something (possibly empty or "No error")
    const char* errStr = doc.ErrorStr();
    EXPECT_NE(errStr, nullptr);
}

TEST_F(XMLDocumentTest_109, ErrorStr_WithError_109) {
    XMLDocument doc;
    doc.Parse("<invalid");
    const char* errStr = doc.ErrorStr();
    EXPECT_NE(errStr, nullptr);
    EXPECT_STRNE(errStr, "");
}

TEST_F(XMLDocumentTest_109, ErrorLineNumOnParseError_109) {
    XMLDocument doc;
    doc.Parse("<root>\n<unclosed>");
    EXPECT_TRUE(doc.Error());
    EXPECT_GT(doc.ErrorLineNum(), 0);
}

// =============================================================================
// NewElement / NewComment / NewText / NewDeclaration / NewUnknown
// =============================================================================

TEST_F(XMLDocumentTest_109, NewElement_109) {
    XMLDocument doc;
    XMLElement* elem = doc.NewElement("test");
    EXPECT_NE(elem, nullptr);
    EXPECT_STREQ(elem->Name(), "test");
    doc.DeleteNode(elem);
}

TEST_F(XMLDocumentTest_109, NewComment_109) {
    XMLDocument doc;
    XMLComment* comment = doc.NewComment("This is a comment");
    EXPECT_NE(comment, nullptr);
    EXPECT_STREQ(comment->Value(), "This is a comment");
    doc.DeleteNode(comment);
}

TEST_F(XMLDocumentTest_109, NewText_109) {
    XMLDocument doc;
    XMLText* text = doc.NewText("Hello");
    EXPECT_NE(text, nullptr);
    EXPECT_STREQ(text->Value(), "Hello");
    doc.DeleteNode(text);
}

TEST_F(XMLDocumentTest_109, NewDeclaration_109) {
    XMLDocument doc;
    XMLDeclaration* decl = doc.NewDeclaration("xml version=\"1.0\"");
    EXPECT_NE(decl, nullptr);
    doc.DeleteNode(decl);
}

TEST_F(XMLDocumentTest_109, NewDeclarationDefault_109) {
    XMLDocument doc;
    XMLDeclaration* decl = doc.NewDeclaration();
    EXPECT_NE(decl, nullptr);
    doc.DeleteNode(decl);
}

TEST_F(XMLDocumentTest_109, NewUnknown_109) {
    XMLDocument doc;
    XMLUnknown* unknown = doc.NewUnknown("something");
    EXPECT_NE(unknown, nullptr);
    EXPECT_STREQ(unknown->Value(), "something");
    doc.DeleteNode(unknown);
}

// =============================================================================
// DeleteNode Tests
// =============================================================================

TEST_F(XMLDocumentTest_109, DeleteNodeRemovesChild_109) {
    XMLDocument doc;
    doc.Parse("<root><child/></root>");
    XMLElement* child = doc.RootElement()->FirstChildElement("child");
    EXPECT_NE(child, nullptr);
    doc.DeleteNode(child);
    EXPECT_EQ(doc.RootElement()->FirstChildElement("child"), nullptr);
}

// =============================================================================
// Clear Tests
// =============================================================================

TEST_F(XMLDocumentTest_109, ClearRemovesAllContent_109) {
    XMLDocument doc;
    doc.Parse("<root><child/></root>");
    EXPECT_NE(doc.RootElement(), nullptr);
    doc.Clear();
    EXPECT_EQ(doc.RootElement(), nullptr);
}

TEST_F(XMLDocumentTest_109, ClearResetsError_109) {
    XMLDocument doc;
    doc.Parse("<invalid");
    EXPECT_TRUE(doc.Error());
    doc.Clear();
    EXPECT_FALSE(doc.Error());
}

// =============================================================================
// DeepCopy Tests
// =============================================================================

TEST_F(XMLDocumentTest_109, DeepCopy_109) {
    XMLDocument source;
    source.Parse("<root><child attr=\"val\">text</child></root>");
    EXPECT_FALSE(source.Error());

    XMLDocument target;
    source.DeepCopy(&target);
    EXPECT_FALSE(target.Error());
    EXPECT_NE(target.RootElement(), nullptr);
    EXPECT_STREQ(target.RootElement()->Name(), "root");
    XMLElement* child = target.RootElement()->FirstChildElement("child");
    EXPECT_NE(child, nullptr);
    EXPECT_STREQ(child->Attribute("attr"), "val");
    EXPECT_STREQ(child->GetText(), "text");
}

TEST_F(XMLDocumentTest_109, DeepCopyEmptyDocument_109) {
    XMLDocument source;
    XMLDocument target;
    target.Parse("<existing/>");
    source.DeepCopy(&target);
    EXPECT_EQ(target.RootElement(), nullptr);
}

// =============================================================================
// ToDocument Tests
// =============================================================================

TEST_F(XMLDocumentTest_109, ToDocument_109) {
    XMLDocument doc;
    EXPECT_EQ(doc.ToDocument(), &doc);
}

// =============================================================================
// ShallowClone / ShallowEqual Tests
// =============================================================================

TEST_F(XMLDocumentTest_109, ShallowCloneReturnsNull_109) {
    XMLDocument doc;
    XMLNode* cloned = doc.ShallowClone(&doc);
    EXPECT_EQ(cloned, nullptr);
}

TEST_F(XMLDocumentTest_109, ShallowEqualReturnsFalse_109) {
    XMLDocument doc1;
    XMLDocument doc2;
    EXPECT_FALSE(doc1.ShallowEqual(&doc2));
}

// =============================================================================
// File I/O Tests
// =============================================================================

TEST_F(XMLDocumentTest_109, LoadFileNonExistent_109) {
    XMLDocument doc;
    XMLError err = doc.LoadFile("this_file_does_not_exist_12345.xml");
    EXPECT_NE(err, XML_SUCCESS);
    EXPECT_TRUE(doc.Error());
    EXPECT_EQ(doc.ErrorID(), XML_ERROR_FILE_NOT_FOUND);
}

TEST_F(XMLDocumentTest_109, SaveAndLoadFile_109) {
    const char* filename = "test_output_109.xml";
    
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
        EXPECT_NE(doc.RootElement(), nullptr);
        EXPECT_STREQ(doc.RootElement()->Name(), "root");
    }
    
    std::remove(filename);
}

TEST_F(XMLDocumentTest_109, LoadFileFromFILE_109) {
    const char* filename = "test_load_fp_109.xml";
    
    // Write a file first
    {
        FILE* fp = fopen(filename, "w");
        ASSERT_NE(fp, nullptr);
        fprintf(fp, "<root/>");
        fclose(fp);
    }
    
    // Load from FILE*
    {
        XMLDocument doc;
        FILE* fp = fopen(filename, "rb");
        ASSERT_NE(fp, nullptr);
        XMLError err = doc.LoadFile(fp);
        fclose(fp);
        EXPECT_EQ(err, XML_SUCCESS);
        EXPECT_NE(doc.RootElement(), nullptr);
    }
    
    std::remove(filename);
}

TEST_F(XMLDocumentTest_109, SaveFileToFILE_109) {
    const char* filename = "test_save_fp_109.xml";
    
    XMLDocument doc;
    doc.Parse("<root attr=\"1\"/>");
    EXPECT_FALSE(doc.Error());
    
    FILE* fp = fopen(filename, "w");
    ASSERT_NE(fp, nullptr);
    XMLError err = doc.SaveFile(fp, false);
    fclose(fp);
    EXPECT_EQ(err, XML_SUCCESS);
    
    // Verify by loading back
    XMLDocument doc2;
    EXPECT_EQ(doc2.LoadFile(filename), XML_SUCCESS);
    EXPECT_NE(doc2.RootElement(), nullptr);
    EXPECT_STREQ(doc2.RootElement()->Attribute("attr"), "1");
    
    std::remove(filename);
}

TEST_F(XMLDocumentTest_109, SaveFileCompact_109) {
    const char* filename = "test_compact_109.xml";
    
    XMLDocument doc;
    doc.Parse("<root>  <child/>  </root>");
    EXPECT_FALSE(doc.Error());
    XMLError err = doc.SaveFile(filename, true);
    EXPECT_EQ(err, XML_SUCCESS);
    
    std::remove(filename);
}

// =============================================================================
// Print Tests
// =============================================================================

TEST_F(XMLDocumentTest_109, PrintToNullStreamer_109) {
    XMLDocument doc;
    doc.Parse("<root/>");
    // Print with null streamer should print to stdout (no crash)
    doc.Print(nullptr);
}

TEST_F(XMLDocumentTest_109, PrintToXMLPrinter_109) {
    XMLDocument doc;
    doc.Parse("<root><child/></root>");
    EXPECT_FALSE(doc.Error());
    
    XMLPrinter printer;
    doc.Print(&printer);
    
    const char* result = printer.CStr();
    EXPECT_NE(result, nullptr);
    EXPECT_NE(std::string(result).find("root"), std::string::npos);
    EXPECT_NE(std::string(result).find("child"), std::string::npos);
}

// =============================================================================
// Accept (Visitor) Tests
// =============================================================================

TEST_F(XMLDocumentTest_109, AcceptVisitor_109) {
    XMLDocument doc;
    doc.Parse("<root/>");
    
    XMLPrinter printer;
    bool result = doc.Accept(&printer);
    EXPECT_TRUE(result);
    
    const char* output = printer.CStr();
    EXPECT_NE(output, nullptr);
    EXPECT_NE(std::string(output).find("root"), std::string::npos);
}

// =============================================================================
// Process Entities Tests
// =============================================================================

TEST_F(XMLDocumentTest_109, ParseWithEntities_109) {
    XMLDocument doc(true);
    doc.Parse("<root>&amp;&lt;&gt;</root>");
    EXPECT_FALSE(doc.Error());
    EXPECT_NE(doc.RootElement(), nullptr);
    EXPECT_STREQ(doc.RootElement()->GetText(), "&<>");
}

TEST_F(XMLDocumentTest_109, ParseWithoutEntities_109) {
    XMLDocument doc(false);
    doc.Parse("<root>&amp;</root>");
    EXPECT_FALSE(doc.Error());
    EXPECT_NE(doc.RootElement(), nullptr);
    // Without entity processing, the raw text should remain
    EXPECT_STREQ(doc.RootElement()->GetText(), "&amp;");
}

// =============================================================================
// Complex / Edge Cases
// =============================================================================

TEST_F(XMLDocumentTest_109, ParseDeeplyNestedXML_109) {
    std::string xml;
    int depth = 50;
    for (int i = 0; i < depth; i++) {
        xml += "<n" + std::to_string(i) + ">";
    }
    for (int i = depth - 1; i >= 0; i--) {
        xml += "</n" + std::to_string(i) + ">";
    }
    
    XMLDocument doc;
    XMLError err = doc.Parse(xml.c_str());
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_NE(doc.RootElement(), nullptr);
}

TEST_F(XMLDocumentTest_109, ParseMultipleRootElements_109) {
    XMLDocument doc;
    // XML standard says one root, but tinyxml2 may handle this
    XMLError err = doc.Parse("<root1/><root2/>");
    // RootElement should return the first element
    if (err == XML_SUCCESS) {
        EXPECT_NE(doc.RootElement(), nullptr);
    }
}

TEST_F(XMLDocumentTest_109, ParseWhitespaceOnly_109) {
    XMLDocument doc;
    XMLError err = doc.Parse("   \n\t  ");
    EXPECT_NE(err, XML_SUCCESS);
    EXPECT_TRUE(doc.Error());
}

TEST_F(XMLDocumentTest_109, NewElementAndInsert_109) {
    XMLDocument doc;
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);
    XMLElement* child = doc.NewElement("child");
    root->InsertEndChild(child);
    
    EXPECT_NE(doc.RootElement(), nullptr);
    EXPECT_STREQ(doc.RootElement()->Name(), "root");
    EXPECT_NE(doc.RootElement()->FirstChildElement("child"), nullptr);
}

TEST_F(XMLDocumentTest_109, ParseClearsOldDocument_109) {
    XMLDocument doc;
    doc.Parse("<old/>");
    EXPECT_STREQ(doc.RootElement()->Name(), "old");
    
    doc.Parse("<new/>");
    EXPECT_STREQ(doc.RootElement()->Name(), "new");
    // Ensure old root is gone
    EXPECT_EQ(doc.RootElement()->NextSiblingElement("old"), nullptr);
}

TEST_F(XMLDocumentTest_109, ErrorIDMultipleValues_109) {
    // Test different error IDs have different names
    const char* successName = XMLDocument::ErrorIDToName(XML_SUCCESS);
    const char* fileNotFoundName = XMLDocument::ErrorIDToName(XML_ERROR_FILE_NOT_FOUND);
    EXPECT_STRNE(successName, fileNotFoundName);
}

TEST_F(XMLDocumentTest_109, ParseWithCDATA_109) {
    XMLDocument doc;
    XMLError err = doc.Parse("<root><![CDATA[some <data> here]]></root>");
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_NE(doc.RootElement(), nullptr);
}

TEST_F(XMLDocumentTest_109, PreserveWhitespace_109) {
    XMLDocument doc(true, PRESERVE_WHITESPACE);
    doc.Parse("<root>  hello  </root>");
    EXPECT_FALSE(doc.Error());
    EXPECT_NE(doc.RootElement(), nullptr);
    const char* text = doc.RootElement()->GetText();
    EXPECT_NE(text, nullptr);
    EXPECT_STREQ(text, "  hello  ");
}

TEST_F(XMLDocumentTest_109, CollapseWhitespace_109) {
    XMLDocument doc(true, COLLAPSE_WHITESPACE);
    doc.Parse("<root>  hello  </root>");
    EXPECT_FALSE(doc.Error());
    EXPECT_NE(doc.RootElement(), nullptr);
    const char* text = doc.RootElement()->GetText();
    EXPECT_NE(text, nullptr);
    // Whitespace should be collapsed
}

TEST_F(XMLDocumentTest_109, PrintError_NoCrash_109) {
    XMLDocument doc;
    doc.Parse("<invalid");
    EXPECT_TRUE(doc.Error());
    // Should not crash
    doc.PrintError();
}

TEST_F(XMLDocumentTest_109, PrintError_NoError_NoCrash_109) {
    XMLDocument doc;
    doc.Parse("<root/>");
    EXPECT_FALSE(doc.Error());
    doc.PrintError();
}
