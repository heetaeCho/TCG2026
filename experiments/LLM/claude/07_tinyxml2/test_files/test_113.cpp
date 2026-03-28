#include "gtest/gtest.h"
#include "./TestProjects/tinyxml2/tinyxml2.h"
#include <cstdio>
#include <cstring>
#include <string>

using namespace tinyxml2;

// ==================== Construction Tests ====================

TEST(XMLDocumentTest_113, DefaultConstruction_NoError_113) {
    XMLDocument doc;
    EXPECT_FALSE(doc.Error());
    EXPECT_EQ(doc.ErrorID(), XML_SUCCESS);
}

TEST(XMLDocumentTest_113, ConstructionWithProcessEntitiesTrue_113) {
    XMLDocument doc(true);
    EXPECT_TRUE(doc.ProcessEntities());
    EXPECT_FALSE(doc.Error());
}

TEST(XMLDocumentTest_113, ConstructionWithProcessEntitiesFalse_113) {
    XMLDocument doc(false);
    EXPECT_FALSE(doc.ProcessEntities());
    EXPECT_FALSE(doc.Error());
}

TEST(XMLDocumentTest_113, ConstructionWithWhitespacePreserve_113) {
    XMLDocument doc(true, PRESERVE_WHITESPACE);
    EXPECT_EQ(doc.WhitespaceMode(), PRESERVE_WHITESPACE);
}

TEST(XMLDocumentTest_113, ConstructionWithWhitespaceCollapse_113) {
    XMLDocument doc(true, COLLAPSE_WHITESPACE);
    EXPECT_EQ(doc.WhitespaceMode(), COLLAPSE_WHITESPACE);
}

// ==================== BOM Tests ====================

TEST(XMLDocumentTest_113, DefaultHasNoBOM_113) {
    XMLDocument doc;
    EXPECT_FALSE(doc.HasBOM());
}

TEST(XMLDocumentTest_113, SetBOMTrue_113) {
    XMLDocument doc;
    doc.SetBOM(true);
    EXPECT_TRUE(doc.HasBOM());
}

TEST(XMLDocumentTest_113, SetBOMFalse_113) {
    XMLDocument doc;
    doc.SetBOM(true);
    doc.SetBOM(false);
    EXPECT_FALSE(doc.HasBOM());
}

// ==================== Parse Tests ====================

TEST(XMLDocumentTest_113, ParseValidXML_113) {
    XMLDocument doc;
    XMLError err = doc.Parse("<root><child/></root>");
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_FALSE(doc.Error());
}

TEST(XMLDocumentTest_113, ParseEmptyString_113) {
    XMLDocument doc;
    XMLError err = doc.Parse("");
    EXPECT_NE(err, XML_SUCCESS);
    EXPECT_TRUE(doc.Error());
}

TEST(XMLDocumentTest_113, ParseNullPointer_113) {
    XMLDocument doc;
    XMLError err = doc.Parse(nullptr, 0);
    EXPECT_NE(err, XML_SUCCESS);
    EXPECT_TRUE(doc.Error());
}

TEST(XMLDocumentTest_113, ParseMalformedXML_113) {
    XMLDocument doc;
    XMLError err = doc.Parse("<root><child></root>");
    EXPECT_NE(err, XML_SUCCESS);
    EXPECT_TRUE(doc.Error());
}

TEST(XMLDocumentTest_113, ParseWithExplicitSize_113) {
    XMLDocument doc;
    const char* xml = "<root/>EXTRA_GARBAGE";
    XMLError err = doc.Parse(xml, 7); // only "<root/>"
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_FALSE(doc.Error());
}

TEST(XMLDocumentTest_113, ParseXMLDeclaration_113) {
    XMLDocument doc;
    XMLError err = doc.Parse("<?xml version=\"1.0\"?><root/>");
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_FALSE(doc.Error());
}

TEST(XMLDocumentTest_113, ParseXMLWithText_113) {
    XMLDocument doc;
    XMLError err = doc.Parse("<root>Hello World</root>");
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_FALSE(doc.Error());
    EXPECT_NE(doc.RootElement(), nullptr);
}

TEST(XMLDocumentTest_113, ParseXMLWithAttributes_113) {
    XMLDocument doc;
    XMLError err = doc.Parse("<root attr=\"value\"/>");
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_FALSE(doc.Error());
}

TEST(XMLDocumentTest_113, ParseXMLWithComment_113) {
    XMLDocument doc;
    XMLError err = doc.Parse("<!-- comment --><root/>");
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_FALSE(doc.Error());
}

TEST(XMLDocumentTest_113, ParseXMLWithCDATA_113) {
    XMLDocument doc;
    XMLError err = doc.Parse("<root><![CDATA[some data]]></root>");
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_FALSE(doc.Error());
}

// ==================== RootElement Tests ====================

TEST(XMLDocumentTest_113, RootElementAfterParse_113) {
    XMLDocument doc;
    doc.Parse("<root/>");
    XMLElement* root = doc.RootElement();
    EXPECT_NE(root, nullptr);
    EXPECT_STREQ(root->Name(), "root");
}

TEST(XMLDocumentTest_113, RootElementOnEmptyDocument_113) {
    XMLDocument doc;
    XMLElement* root = doc.RootElement();
    EXPECT_EQ(root, nullptr);
}

// ==================== Error Handling Tests ====================

TEST(XMLDocumentTest_113, ErrorIDAfterSuccessfulParse_113) {
    XMLDocument doc;
    doc.Parse("<root/>");
    EXPECT_EQ(doc.ErrorID(), XML_SUCCESS);
}

TEST(XMLDocumentTest_113, ErrorIDAfterFailedParse_113) {
    XMLDocument doc;
    doc.Parse("<root><unclosed>");
    EXPECT_NE(doc.ErrorID(), XML_SUCCESS);
}

TEST(XMLDocumentTest_113, ErrorLineNumAfterError_113) {
    XMLDocument doc;
    doc.Parse("<root>\n<unclosed>");
    if (doc.Error()) {
        // Error line number should be > 0 when there's a parsing error
        EXPECT_GT(doc.ErrorLineNum(), 0);
    }
}

TEST(XMLDocumentTest_113, ErrorNameReturnsNonNull_113) {
    XMLDocument doc;
    doc.Parse("<root/>");
    const char* name = doc.ErrorName();
    EXPECT_NE(name, nullptr);
}

TEST(XMLDocumentTest_113, ErrorStrOnNoError_113) {
    XMLDocument doc;
    doc.Parse("<root/>");
    // ErrorStr should return something (possibly empty string) when no error
    const char* errStr = doc.ErrorStr();
    EXPECT_NE(errStr, nullptr);
}

TEST(XMLDocumentTest_113, ErrorStrOnError_113) {
    XMLDocument doc;
    doc.Parse("");
    EXPECT_TRUE(doc.Error());
    const char* errStr = doc.ErrorStr();
    EXPECT_NE(errStr, nullptr);
    EXPECT_GT(strlen(errStr), 0u);
}

TEST(XMLDocumentTest_113, ClearError_113) {
    XMLDocument doc;
    doc.Parse("<malformed");
    EXPECT_TRUE(doc.Error());
    doc.ClearError();
    EXPECT_FALSE(doc.Error());
    EXPECT_EQ(doc.ErrorID(), XML_SUCCESS);
}

// ==================== ErrorIDToName Tests ====================

TEST(XMLDocumentTest_113, ErrorIDToNameSuccess_113) {
    const char* name = XMLDocument::ErrorIDToName(XML_SUCCESS);
    EXPECT_NE(name, nullptr);
    EXPECT_STREQ(name, "XML_SUCCESS");
}

TEST(XMLDocumentTest_113, ErrorIDToNameFileNotFound_113) {
    const char* name = XMLDocument::ErrorIDToName(XML_ERROR_FILE_NOT_FOUND);
    EXPECT_NE(name, nullptr);
    EXPECT_STREQ(name, "XML_ERROR_FILE_NOT_FOUND");
}

TEST(XMLDocumentTest_113, ErrorIDToNameAllValues_113) {
    for (int i = 0; i < XML_ERROR_COUNT; ++i) {
        const char* name = XMLDocument::ErrorIDToName(static_cast<XMLError>(i));
        EXPECT_NE(name, nullptr);
        EXPECT_GT(strlen(name), 0u);
    }
}

// ==================== NewElement / NewComment / NewText / NewDeclaration / NewUnknown Tests ====================

TEST(XMLDocumentTest_113, NewElement_113) {
    XMLDocument doc;
    XMLElement* elem = doc.NewElement("test");
    EXPECT_NE(elem, nullptr);
    EXPECT_STREQ(elem->Name(), "test");
    doc.DeleteNode(elem);
}

TEST(XMLDocumentTest_113, NewComment_113) {
    XMLDocument doc;
    XMLComment* comment = doc.NewComment("this is a comment");
    EXPECT_NE(comment, nullptr);
    EXPECT_STREQ(comment->Value(), "this is a comment");
    doc.DeleteNode(comment);
}

TEST(XMLDocumentTest_113, NewText_113) {
    XMLDocument doc;
    XMLText* text = doc.NewText("hello");
    EXPECT_NE(text, nullptr);
    EXPECT_STREQ(text->Value(), "hello");
    doc.DeleteNode(text);
}

TEST(XMLDocumentTest_113, NewDeclaration_113) {
    XMLDocument doc;
    XMLDeclaration* decl = doc.NewDeclaration();
    EXPECT_NE(decl, nullptr);
    doc.DeleteNode(decl);
}

TEST(XMLDocumentTest_113, NewDeclarationWithText_113) {
    XMLDocument doc;
    XMLDeclaration* decl = doc.NewDeclaration("xml version=\"1.0\"");
    EXPECT_NE(decl, nullptr);
    doc.DeleteNode(decl);
}

TEST(XMLDocumentTest_113, NewUnknown_113) {
    XMLDocument doc;
    XMLUnknown* unknown = doc.NewUnknown("something");
    EXPECT_NE(unknown, nullptr);
    EXPECT_STREQ(unknown->Value(), "something");
    doc.DeleteNode(unknown);
}

// ==================== DeleteNode Tests ====================

TEST(XMLDocumentTest_113, DeleteNodeElement_113) {
    XMLDocument doc;
    doc.Parse("<root><child/></root>");
    XMLElement* root = doc.RootElement();
    EXPECT_NE(root, nullptr);
    XMLElement* child = root->FirstChildElement("child");
    EXPECT_NE(child, nullptr);
    doc.DeleteNode(child);
    EXPECT_EQ(root->FirstChildElement("child"), nullptr);
}

// ==================== Clear Tests ====================

TEST(XMLDocumentTest_113, ClearResetsDocument_113) {
    XMLDocument doc;
    doc.Parse("<root><child/></root>");
    EXPECT_NE(doc.RootElement(), nullptr);
    doc.Clear();
    EXPECT_EQ(doc.RootElement(), nullptr);
    EXPECT_FALSE(doc.Error());
}

// ==================== DeepCopy Tests ====================

TEST(XMLDocumentTest_113, DeepCopy_113) {
    XMLDocument source;
    source.Parse("<root><child attr=\"val\">text</child></root>");
    EXPECT_FALSE(source.Error());

    XMLDocument target;
    source.DeepCopy(&target);
    EXPECT_FALSE(target.Error());
    EXPECT_NE(target.RootElement(), nullptr);
    EXPECT_STREQ(target.RootElement()->Name(), "root");

    XMLElement* childTarget = target.RootElement()->FirstChildElement("child");
    EXPECT_NE(childTarget, nullptr);
    EXPECT_STREQ(childTarget->Attribute("attr"), "val");
}

TEST(XMLDocumentTest_113, DeepCopyIsIndependent_113) {
    XMLDocument source;
    source.Parse("<root/>");

    XMLDocument target;
    source.DeepCopy(&target);

    // Modify source, target should remain unchanged
    source.Clear();
    EXPECT_EQ(source.RootElement(), nullptr);
    EXPECT_NE(target.RootElement(), nullptr);
}

// ==================== ToDocument Tests ====================

TEST(XMLDocumentTest_113, ToDocument_113) {
    XMLDocument doc;
    XMLDocument* result = doc.ToDocument();
    EXPECT_EQ(result, &doc);
}

// ==================== ShallowClone/ShallowEqual Tests ====================

TEST(XMLDocumentTest_113, ShallowCloneReturnsNull_113) {
    XMLDocument doc;
    XMLNode* clone = doc.ShallowClone(&doc);
    EXPECT_EQ(clone, nullptr);
}

TEST(XMLDocumentTest_113, ShallowEqualReturnsFalse_113) {
    XMLDocument doc1;
    XMLDocument doc2;
    EXPECT_FALSE(doc1.ShallowEqual(&doc2));
}

// ==================== LoadFile Tests ====================

TEST(XMLDocumentTest_113, LoadFileNonExistent_113) {
    XMLDocument doc;
    XMLError err = doc.LoadFile("non_existent_file_12345.xml");
    EXPECT_NE(err, XML_SUCCESS);
    EXPECT_TRUE(doc.Error());
    EXPECT_EQ(doc.ErrorID(), XML_ERROR_FILE_NOT_FOUND);
}

TEST(XMLDocumentTest_113, LoadFileNullFILE_113) {
    XMLDocument doc;
    FILE* fp = nullptr;
    XMLError err = doc.LoadFile(fp);
    EXPECT_NE(err, XML_SUCCESS);
    EXPECT_TRUE(doc.Error());
}

// ==================== SaveFile Tests ====================

TEST(XMLDocumentTest_113, SaveFileAndLoadFile_113) {
    const char* filename = "test_save_113.xml";
    {
        XMLDocument doc;
        doc.Parse("<root><child>text</child></root>");
        EXPECT_FALSE(doc.Error());
        XMLError err = doc.SaveFile(filename, false);
        EXPECT_EQ(err, XML_SUCCESS);
    }
    {
        XMLDocument doc;
        XMLError err = doc.LoadFile(filename);
        EXPECT_EQ(err, XML_SUCCESS);
        EXPECT_FALSE(doc.Error());
        EXPECT_NE(doc.RootElement(), nullptr);
        EXPECT_STREQ(doc.RootElement()->Name(), "root");
    }
    std::remove(filename);
}

TEST(XMLDocumentTest_113, SaveFileCompact_113) {
    const char* filename = "test_compact_113.xml";
    XMLDocument doc;
    doc.Parse("<root> <child /> </root>");
    EXPECT_FALSE(doc.Error());
    XMLError err = doc.SaveFile(filename, true);
    EXPECT_EQ(err, XML_SUCCESS);
    std::remove(filename);
}

TEST(XMLDocumentTest_113, SaveFileToFILE_113) {
    const char* filename = "test_fp_113.xml";
    XMLDocument doc;
    doc.Parse("<root/>");
    FILE* fp = fopen(filename, "w");
    ASSERT_NE(fp, nullptr);
    XMLError err = doc.SaveFile(fp, false);
    fclose(fp);
    EXPECT_EQ(err, XML_SUCCESS);
    std::remove(filename);
}

// ==================== Print Tests ====================

TEST(XMLDocumentTest_113, PrintToDefaultPrinter_113) {
    XMLDocument doc;
    doc.Parse("<root><child/></root>");
    EXPECT_FALSE(doc.Error());
    
    XMLPrinter printer;
    doc.Print(&printer);
    const char* result = printer.CStr();
    EXPECT_NE(result, nullptr);
    EXPECT_NE(std::string(result).find("root"), std::string::npos);
}

TEST(XMLDocumentTest_113, PrintWithNullPrinter_113) {
    XMLDocument doc;
    doc.Parse("<root/>");
    // Print with null streamer should use stdout (just verify no crash)
    // This might print to stdout, which is acceptable in tests
    doc.Print(nullptr);
}

// ==================== Accept Tests ====================

TEST(XMLDocumentTest_113, AcceptWithPrinter_113) {
    XMLDocument doc;
    doc.Parse("<root><child attr=\"v\"/></root>");
    EXPECT_FALSE(doc.Error());

    XMLPrinter printer;
    bool result = doc.Accept(&printer);
    EXPECT_TRUE(result);
    const char* output = printer.CStr();
    EXPECT_NE(output, nullptr);
    EXPECT_NE(std::string(output).find("root"), std::string::npos);
}

// ==================== Complex XML Tests ====================

TEST(XMLDocumentTest_113, ParseComplexXML_113) {
    const char* xml = 
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>"
        "<library>"
        "  <book id=\"1\">"
        "    <title>Test Book</title>"
        "    <author>Author Name</author>"
        "  </book>"
        "  <!-- A comment -->"
        "</library>";
    
    XMLDocument doc;
    XMLError err = doc.Parse(xml);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_FALSE(doc.Error());
    
    XMLElement* root = doc.RootElement();
    EXPECT_NE(root, nullptr);
    EXPECT_STREQ(root->Name(), "library");
    
    XMLElement* book = root->FirstChildElement("book");
    EXPECT_NE(book, nullptr);
    EXPECT_STREQ(book->Attribute("id"), "1");
}

TEST(XMLDocumentTest_113, ParseAndReparse_113) {
    XMLDocument doc;
    doc.Parse("<first/>");
    EXPECT_STREQ(doc.RootElement()->Name(), "first");
    
    // Re-parsing should replace old content
    doc.Parse("<second/>");
    EXPECT_STREQ(doc.RootElement()->Name(), "second");
}

// ==================== Entity Processing Tests ====================

TEST(XMLDocumentTest_113, ProcessEntitiesEnabled_113) {
    XMLDocument doc(true);
    doc.Parse("<root>&amp;</root>");
    EXPECT_FALSE(doc.Error());
    XMLElement* root = doc.RootElement();
    EXPECT_NE(root, nullptr);
    const char* text = root->GetText();
    EXPECT_NE(text, nullptr);
    EXPECT_STREQ(text, "&");
}

TEST(XMLDocumentTest_113, ProcessEntitiesDisabled_113) {
    XMLDocument doc(false);
    doc.Parse("<root>&amp;</root>");
    EXPECT_FALSE(doc.Error());
}

// ==================== Multiple Error Scenarios ====================

TEST(XMLDocumentTest_113, MismatchedElementError_113) {
    XMLDocument doc;
    XMLError err = doc.Parse("<root></wrong>");
    EXPECT_NE(err, XML_SUCCESS);
    EXPECT_TRUE(doc.Error());
    EXPECT_EQ(doc.ErrorID(), XML_ERROR_MISMATCHED_ELEMENT);
}

TEST(XMLDocumentTest_113, EmptyDocumentError_113) {
    XMLDocument doc;
    XMLError err = doc.Parse("   ");
    EXPECT_NE(err, XML_SUCCESS);
    EXPECT_TRUE(doc.Error());
}

// ==================== InsertNode and Structure Tests ====================

TEST(XMLDocumentTest_113, InsertNewElementAsRoot_113) {
    XMLDocument doc;
    XMLElement* root = doc.NewElement("root");
    doc.InsertFirstChild(root);
    EXPECT_NE(doc.RootElement(), nullptr);
    EXPECT_STREQ(doc.RootElement()->Name(), "root");
}

TEST(XMLDocumentTest_113, InsertMultipleChildren_113) {
    XMLDocument doc;
    XMLDeclaration* decl = doc.NewDeclaration();
    doc.InsertFirstChild(decl);
    
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);
    
    XMLElement* child = doc.NewElement("child");
    root->InsertEndChild(child);
    
    EXPECT_NE(doc.RootElement(), nullptr);
    EXPECT_STREQ(doc.RootElement()->Name(), "root");
    EXPECT_NE(root->FirstChildElement("child"), nullptr);
}

// ==================== PrintError Test ====================

TEST(XMLDocumentTest_113, PrintErrorNoError_113) {
    XMLDocument doc;
    doc.Parse("<root/>");
    // Should not crash when called with no error
    doc.PrintError();
}

TEST(XMLDocumentTest_113, PrintErrorWithError_113) {
    XMLDocument doc;
    doc.Parse("");
    EXPECT_TRUE(doc.Error());
    // Should not crash
    doc.PrintError();
}

// ==================== LoadFile with FILE* ====================

TEST(XMLDocumentTest_113, LoadFileFromValidFILE_113) {
    const char* filename = "test_load_fp_113.xml";
    // First create a file
    {
        FILE* fp = fopen(filename, "w");
        ASSERT_NE(fp, nullptr);
        fprintf(fp, "<root/>");
        fclose(fp);
    }
    // Then load from FILE*
    {
        FILE* fp = fopen(filename, "rb");
        ASSERT_NE(fp, nullptr);
        XMLDocument doc;
        XMLError err = doc.LoadFile(fp);
        fclose(fp);
        EXPECT_EQ(err, XML_SUCCESS);
        EXPECT_FALSE(doc.Error());
        EXPECT_NE(doc.RootElement(), nullptr);
    }
    std::remove(filename);
}

// ==================== MarkInUse Test ====================

TEST(XMLDocumentTest_113, MarkInUseCreatedNode_113) {
    XMLDocument doc;
    XMLElement* elem = doc.NewElement("test");
    // MarkInUse should not crash
    doc.MarkInUse(elem);
    doc.InsertEndChild(elem);
}
