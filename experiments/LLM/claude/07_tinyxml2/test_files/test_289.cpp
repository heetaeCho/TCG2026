#include <gtest/gtest.h>
#include <cstdio>
#include <cstring>
#include <string>
#include "tinyxml2.h"

using namespace tinyxml2;

// ============================================================
// Test Fixture
// ============================================================
class XMLDocumentTest_289 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// ============================================================
// Construction Tests
// ============================================================

TEST_F(XMLDocumentTest_289, DefaultConstruction_NoError_289) {
    XMLDocument doc;
    EXPECT_FALSE(doc.Error());
    EXPECT_EQ(doc.ErrorID(), XML_SUCCESS);
    EXPECT_EQ(doc.ErrorLineNum(), 0);
}

TEST_F(XMLDocumentTest_289, ConstructionWithProcessEntities_289) {
    XMLDocument doc(true, COLLAPSE_WHITESPACE);
    EXPECT_TRUE(doc.ProcessEntities());
    EXPECT_EQ(doc.WhitespaceMode(), COLLAPSE_WHITESPACE);
}

TEST_F(XMLDocumentTest_289, ConstructionWithoutProcessEntities_289) {
    XMLDocument doc(false, PRESERVE_WHITESPACE);
    EXPECT_FALSE(doc.ProcessEntities());
    EXPECT_EQ(doc.WhitespaceMode(), PRESERVE_WHITESPACE);
}

TEST_F(XMLDocumentTest_289, DefaultBOMIsFalse_289) {
    XMLDocument doc;
    EXPECT_FALSE(doc.HasBOM());
}

TEST_F(XMLDocumentTest_289, SetBOMTrue_289) {
    XMLDocument doc;
    doc.SetBOM(true);
    EXPECT_TRUE(doc.HasBOM());
}

TEST_F(XMLDocumentTest_289, SetBOMFalse_289) {
    XMLDocument doc;
    doc.SetBOM(true);
    doc.SetBOM(false);
    EXPECT_FALSE(doc.HasBOM());
}

// ============================================================
// ErrorName / ErrorIDToName Tests
// ============================================================

TEST_F(XMLDocumentTest_289, ErrorNameOnSuccess_289) {
    XMLDocument doc;
    const char* name = doc.ErrorName();
    ASSERT_NE(name, nullptr);
    EXPECT_STREQ(name, "XML_SUCCESS");
}

TEST_F(XMLDocumentTest_289, ErrorIDToNameSuccess_289) {
    const char* name = XMLDocument::ErrorIDToName(XML_SUCCESS);
    ASSERT_NE(name, nullptr);
    EXPECT_STREQ(name, "XML_SUCCESS");
}

TEST_F(XMLDocumentTest_289, ErrorIDToNameFileNotFound_289) {
    const char* name = XMLDocument::ErrorIDToName(XML_ERROR_FILE_NOT_FOUND);
    ASSERT_NE(name, nullptr);
    EXPECT_STREQ(name, "XML_ERROR_FILE_NOT_FOUND");
}

TEST_F(XMLDocumentTest_289, ErrorIDToNameEmptyDocument_289) {
    const char* name = XMLDocument::ErrorIDToName(XML_ERROR_EMPTY_DOCUMENT);
    ASSERT_NE(name, nullptr);
    EXPECT_STREQ(name, "XML_ERROR_EMPTY_DOCUMENT");
}

TEST_F(XMLDocumentTest_289, ErrorIDToNameParsing_289) {
    const char* name = XMLDocument::ErrorIDToName(XML_ERROR_PARSING);
    ASSERT_NE(name, nullptr);
    EXPECT_STREQ(name, "XML_ERROR_PARSING");
}

// ============================================================
// Parse Tests
// ============================================================

TEST_F(XMLDocumentTest_289, ParseValidXML_289) {
    XMLDocument doc;
    XMLError err = doc.Parse("<root><child/></root>");
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_FALSE(doc.Error());
}

TEST_F(XMLDocumentTest_289, ParseEmptyString_289) {
    XMLDocument doc;
    XMLError err = doc.Parse("");
    EXPECT_NE(err, XML_SUCCESS);
    EXPECT_TRUE(doc.Error());
}

TEST_F(XMLDocumentTest_289, ParseNullptr_289) {
    XMLDocument doc;
    XMLError err = doc.Parse(nullptr);
    EXPECT_NE(err, XML_SUCCESS);
    EXPECT_TRUE(doc.Error());
}

TEST_F(XMLDocumentTest_289, ParseMalformedXML_289) {
    XMLDocument doc;
    XMLError err = doc.Parse("<root><child></root>");
    EXPECT_NE(err, XML_SUCCESS);
    EXPECT_TRUE(doc.Error());
}

TEST_F(XMLDocumentTest_289, ParseWithExplicitLength_289) {
    XMLDocument doc;
    const char* xml = "<root/>extradata";
    XMLError err = doc.Parse(xml, 7); // only "<root/>"
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_FALSE(doc.Error());
}

TEST_F(XMLDocumentTest_289, ParseWithDeclaration_289) {
    XMLDocument doc;
    XMLError err = doc.Parse("<?xml version=\"1.0\"?><root/>");
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_FALSE(doc.Error());
}

TEST_F(XMLDocumentTest_289, ParseWithAttributes_289) {
    XMLDocument doc;
    XMLError err = doc.Parse("<root attr=\"value\"/>");
    EXPECT_EQ(err, XML_SUCCESS);
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    EXPECT_STREQ(root->Attribute("attr"), "value");
}

TEST_F(XMLDocumentTest_289, ParseWithText_289) {
    XMLDocument doc;
    XMLError err = doc.Parse("<root>Hello</root>");
    EXPECT_EQ(err, XML_SUCCESS);
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    EXPECT_STREQ(root->GetText(), "Hello");
}

// ============================================================
// RootElement Tests
// ============================================================

TEST_F(XMLDocumentTest_289, RootElementAfterParse_289) {
    XMLDocument doc;
    doc.Parse("<root/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    EXPECT_STREQ(root->Name(), "root");
}

TEST_F(XMLDocumentTest_289, RootElementWhenEmpty_289) {
    XMLDocument doc;
    XMLElement* root = doc.RootElement();
    EXPECT_EQ(root, nullptr);
}

// ============================================================
// NewElement / NewComment / NewText / NewDeclaration / NewUnknown
// ============================================================

TEST_F(XMLDocumentTest_289, NewElementCreation_289) {
    XMLDocument doc;
    XMLElement* elem = doc.NewElement("test");
    ASSERT_NE(elem, nullptr);
    EXPECT_STREQ(elem->Name(), "test");
    doc.DeleteNode(elem);
}

TEST_F(XMLDocumentTest_289, NewCommentCreation_289) {
    XMLDocument doc;
    XMLComment* comment = doc.NewComment("a comment");
    ASSERT_NE(comment, nullptr);
    EXPECT_STREQ(comment->Value(), "a comment");
    doc.DeleteNode(comment);
}

TEST_F(XMLDocumentTest_289, NewTextCreation_289) {
    XMLDocument doc;
    XMLText* text = doc.NewText("hello");
    ASSERT_NE(text, nullptr);
    EXPECT_STREQ(text->Value(), "hello");
    doc.DeleteNode(text);
}

TEST_F(XMLDocumentTest_289, NewDeclarationCreation_289) {
    XMLDocument doc;
    XMLDeclaration* decl = doc.NewDeclaration();
    ASSERT_NE(decl, nullptr);
    doc.DeleteNode(decl);
}

TEST_F(XMLDocumentTest_289, NewDeclarationWithText_289) {
    XMLDocument doc;
    XMLDeclaration* decl = doc.NewDeclaration("xml version=\"1.0\"");
    ASSERT_NE(decl, nullptr);
    doc.DeleteNode(decl);
}

TEST_F(XMLDocumentTest_289, NewUnknownCreation_289) {
    XMLDocument doc;
    XMLUnknown* unknown = doc.NewUnknown("something");
    ASSERT_NE(unknown, nullptr);
    EXPECT_STREQ(unknown->Value(), "something");
    doc.DeleteNode(unknown);
}

// ============================================================
// Clear Tests
// ============================================================

TEST_F(XMLDocumentTest_289, ClearRemovesAllContent_289) {
    XMLDocument doc;
    doc.Parse("<root><child/></root>");
    EXPECT_NE(doc.RootElement(), nullptr);
    doc.Clear();
    EXPECT_EQ(doc.RootElement(), nullptr);
    EXPECT_FALSE(doc.Error());
}

// ============================================================
// ClearError Tests
// ============================================================

TEST_F(XMLDocumentTest_289, ClearErrorResetsError_289) {
    XMLDocument doc;
    doc.Parse("<unclosed");
    EXPECT_TRUE(doc.Error());
    doc.ClearError();
    EXPECT_FALSE(doc.Error());
    EXPECT_EQ(doc.ErrorID(), XML_SUCCESS);
}

// ============================================================
// ErrorStr Tests
// ============================================================

TEST_F(XMLDocumentTest_289, ErrorStrOnSuccess_289) {
    XMLDocument doc;
    doc.Parse("<root/>");
    const char* errStr = doc.ErrorStr();
    ASSERT_NE(errStr, nullptr);
}

TEST_F(XMLDocumentTest_289, ErrorStrOnError_289) {
    XMLDocument doc;
    doc.Parse("<broken");
    EXPECT_TRUE(doc.Error());
    const char* errStr = doc.ErrorStr();
    ASSERT_NE(errStr, nullptr);
    // The error string should contain something meaningful
    EXPECT_GT(strlen(errStr), 0u);
}

// ============================================================
// ErrorLineNum Tests
// ============================================================

TEST_F(XMLDocumentTest_289, ErrorLineNumOnSuccess_289) {
    XMLDocument doc;
    doc.Parse("<root/>");
    EXPECT_EQ(doc.ErrorLineNum(), 0);
}

TEST_F(XMLDocumentTest_289, ErrorLineNumOnMultilineError_289) {
    XMLDocument doc;
    doc.Parse("<root>\n<child>\n</root>");
    if (doc.Error()) {
        EXPECT_GT(doc.ErrorLineNum(), 0);
    }
}

// ============================================================
// DeepCopy Tests
// ============================================================

TEST_F(XMLDocumentTest_289, DeepCopyCreatesIdenticalDocument_289) {
    XMLDocument source;
    source.Parse("<root><child attr=\"val\">text</child></root>");
    ASSERT_FALSE(source.Error());

    XMLDocument target;
    source.DeepCopy(&target);

    ASSERT_NE(target.RootElement(), nullptr);
    EXPECT_STREQ(target.RootElement()->Name(), "root");

    XMLElement* child = target.RootElement()->FirstChildElement("child");
    ASSERT_NE(child, nullptr);
    EXPECT_STREQ(child->Attribute("attr"), "val");
    EXPECT_STREQ(child->GetText(), "text");
}

TEST_F(XMLDocumentTest_289, DeepCopyEmptyDocument_289) {
    XMLDocument source;
    XMLDocument target;
    target.Parse("<existing/>");
    source.DeepCopy(&target);
    EXPECT_EQ(target.RootElement(), nullptr);
}

// ============================================================
// ToDocument Tests
// ============================================================

TEST_F(XMLDocumentTest_289, ToDocumentReturnsSelf_289) {
    XMLDocument doc;
    EXPECT_EQ(doc.ToDocument(), &doc);
}

// ============================================================
// ShallowClone / ShallowEqual Tests
// ============================================================

TEST_F(XMLDocumentTest_289, ShallowCloneReturnsNull_289) {
    XMLDocument doc;
    XMLNode* clone = doc.ShallowClone(&doc);
    EXPECT_EQ(clone, nullptr);
}

TEST_F(XMLDocumentTest_289, ShallowEqualReturnsFalse_289) {
    XMLDocument doc1;
    XMLDocument doc2;
    EXPECT_FALSE(doc1.ShallowEqual(&doc2));
}

// ============================================================
// DeleteNode Tests
// ============================================================

TEST_F(XMLDocumentTest_289, DeleteNodeRemovesChild_289) {
    XMLDocument doc;
    doc.Parse("<root><child1/><child2/></root>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);

    XMLElement* child1 = root->FirstChildElement("child1");
    ASSERT_NE(child1, nullptr);

    doc.DeleteNode(child1);

    EXPECT_EQ(root->FirstChildElement("child1"), nullptr);
    EXPECT_NE(root->FirstChildElement("child2"), nullptr);
}

TEST_F(XMLDocumentTest_289, DeleteNodeNull_289) {
    XMLDocument doc;
    // Should not crash
    doc.DeleteNode(nullptr);
}

// ============================================================
// LoadFile / SaveFile Tests
// ============================================================

TEST_F(XMLDocumentTest_289, LoadFileNonExistent_289) {
    XMLDocument doc;
    XMLError err = doc.LoadFile("nonexistent_file_that_does_not_exist.xml");
    EXPECT_NE(err, XML_SUCCESS);
    EXPECT_TRUE(doc.Error());
    EXPECT_EQ(doc.ErrorID(), XML_ERROR_FILE_NOT_FOUND);
}

TEST_F(XMLDocumentTest_289, SaveFileAndLoadFile_289) {
    const char* filename = "test_save_load_289.xml";

    {
        XMLDocument doc;
        doc.Parse("<root><item>data</item></root>");
        ASSERT_FALSE(doc.Error());
        XMLError err = doc.SaveFile(filename);
        EXPECT_EQ(err, XML_SUCCESS);
    }

    {
        XMLDocument doc;
        XMLError err = doc.LoadFile(filename);
        EXPECT_EQ(err, XML_SUCCESS);
        ASSERT_FALSE(doc.Error());
        XMLElement* root = doc.RootElement();
        ASSERT_NE(root, nullptr);
        EXPECT_STREQ(root->Name(), "root");
        XMLElement* item = root->FirstChildElement("item");
        ASSERT_NE(item, nullptr);
        EXPECT_STREQ(item->GetText(), "data");
    }

    std::remove(filename);
}

TEST_F(XMLDocumentTest_289, SaveFileWithFILEPointer_289) {
    const char* filename = "test_save_fp_289.xml";

    {
        XMLDocument doc;
        doc.Parse("<root/>");
        FILE* fp = fopen(filename, "w");
        ASSERT_NE(fp, nullptr);
        XMLError err = doc.SaveFile(fp);
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
        EXPECT_STREQ(doc.RootElement()->Name(), "root");
    }

    std::remove(filename);
}

TEST_F(XMLDocumentTest_289, LoadFileNullFILEPointer_289) {
    XMLDocument doc;
    XMLError err = doc.LoadFile((FILE*)nullptr);
    EXPECT_NE(err, XML_SUCCESS);
    EXPECT_TRUE(doc.Error());
}

// ============================================================
// Print Tests
// ============================================================

TEST_F(XMLDocumentTest_289, PrintToXMLPrinter_289) {
    XMLDocument doc;
    doc.Parse("<root><child/></root>");
    ASSERT_FALSE(doc.Error());

    XMLPrinter printer;
    doc.Print(&printer);
    const char* result = printer.CStr();
    ASSERT_NE(result, nullptr);
    EXPECT_NE(std::string(result).find("root"), std::string::npos);
    EXPECT_NE(std::string(result).find("child"), std::string::npos);
}

TEST_F(XMLDocumentTest_289, PrintCompactMode_289) {
    XMLDocument doc;
    doc.Parse("<root>  <child/>  </root>");
    ASSERT_FALSE(doc.Error());

    XMLPrinter printerCompact(nullptr, true);
    doc.Print(&printerCompact);
    const char* compact = printerCompact.CStr();
    ASSERT_NE(compact, nullptr);

    XMLPrinter printerNormal(nullptr, false);
    doc.Print(&printerNormal);
    const char* normal = printerNormal.CStr();
    ASSERT_NE(normal, nullptr);

    // Compact output should generally be shorter or equal
    EXPECT_LE(strlen(compact), strlen(normal));
}

// ============================================================
// Accept (Visitor) Tests
// ============================================================

TEST_F(XMLDocumentTest_289, AcceptVisitor_289) {
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

// ============================================================
// Process Entities Tests
// ============================================================

TEST_F(XMLDocumentTest_289, ProcessEntitiesEnabled_289) {
    XMLDocument doc(true);
    doc.Parse("<root>&amp;</root>");
    ASSERT_FALSE(doc.Error());
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    EXPECT_STREQ(root->GetText(), "&");
}

TEST_F(XMLDocumentTest_289, ProcessEntitiesDisabled_289) {
    XMLDocument doc(false);
    doc.Parse("<root>&amp;</root>");
    ASSERT_FALSE(doc.Error());
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    // When entities are not processed, the raw text should be preserved
    EXPECT_STREQ(root->GetText(), "&amp;");
}

// ============================================================
// Whitespace Mode Tests
// ============================================================

TEST_F(XMLDocumentTest_289, CollapseWhitespaceMode_289) {
    XMLDocument doc(true, COLLAPSE_WHITESPACE);
    EXPECT_EQ(doc.WhitespaceMode(), COLLAPSE_WHITESPACE);
}

TEST_F(XMLDocumentTest_289, PreserveWhitespaceMode_289) {
    XMLDocument doc(true, PRESERVE_WHITESPACE);
    EXPECT_EQ(doc.WhitespaceMode(), PRESERVE_WHITESPACE);
}

// ============================================================
// Multiple Parse Calls
// ============================================================

TEST_F(XMLDocumentTest_289, ReparseReplacesContent_289) {
    XMLDocument doc;
    doc.Parse("<first/>");
    ASSERT_FALSE(doc.Error());
    EXPECT_STREQ(doc.RootElement()->Name(), "first");

    doc.Parse("<second/>");
    ASSERT_FALSE(doc.Error());
    EXPECT_STREQ(doc.RootElement()->Name(), "second");
}

// ============================================================
// Error After Clear
// ============================================================

TEST_F(XMLDocumentTest_289, ClearAfterError_289) {
    XMLDocument doc;
    doc.Parse("<broken");
    EXPECT_TRUE(doc.Error());
    doc.Clear();
    EXPECT_FALSE(doc.Error());
    EXPECT_EQ(doc.RootElement(), nullptr);
}

// ============================================================
// NewElement Attached to Document
// ============================================================

TEST_F(XMLDocumentTest_289, NewElementInsertedAsChild_289) {
    XMLDocument doc;
    XMLElement* root = doc.NewElement("root");
    doc.InsertFirstChild(root);

    XMLElement* child = doc.NewElement("child");
    root->InsertFirstChild(child);

    EXPECT_NE(doc.RootElement(), nullptr);
    EXPECT_STREQ(doc.RootElement()->Name(), "root");
    EXPECT_NE(doc.RootElement()->FirstChildElement("child"), nullptr);
}

// ============================================================
// Complex XML Parse
// ============================================================

TEST_F(XMLDocumentTest_289, ParseComplexXML_289) {
    const char* xml =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>"
        "<library>"
        "  <book id=\"1\">"
        "    <title>Test Book</title>"
        "    <author>Author Name</author>"
        "  </book>"
        "  <book id=\"2\">"
        "    <title>Another Book</title>"
        "  </book>"
        "</library>";

    XMLDocument doc;
    XMLError err = doc.Parse(xml);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_FALSE(doc.Error());

    XMLElement* library = doc.RootElement();
    ASSERT_NE(library, nullptr);
    EXPECT_STREQ(library->Name(), "library");

    XMLElement* book1 = library->FirstChildElement("book");
    ASSERT_NE(book1, nullptr);
    EXPECT_STREQ(book1->Attribute("id"), "1");

    XMLElement* title1 = book1->FirstChildElement("title");
    ASSERT_NE(title1, nullptr);
    EXPECT_STREQ(title1->GetText(), "Test Book");

    XMLElement* book2 = book1->NextSiblingElement("book");
    ASSERT_NE(book2, nullptr);
    EXPECT_STREQ(book2->Attribute("id"), "2");
}

// ============================================================
// ErrorName after error
// ============================================================

TEST_F(XMLDocumentTest_289, ErrorNameAfterParseError_289) {
    XMLDocument doc;
    doc.Parse("");
    EXPECT_TRUE(doc.Error());
    const char* name = doc.ErrorName();
    ASSERT_NE(name, nullptr);
    // Should not be "XML_SUCCESS"
    EXPECT_STRNE(name, "XML_SUCCESS");
}

// ============================================================
// CDATA parsing
// ============================================================

TEST_F(XMLDocumentTest_289, ParseCDATA_289) {
    XMLDocument doc;
    XMLError err = doc.Parse("<root><![CDATA[some <data>]]></root>");
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_FALSE(doc.Error());
}

// ============================================================
// Comment in document
// ============================================================

TEST_F(XMLDocumentTest_289, ParseWithComment_289) {
    XMLDocument doc;
    XMLError err = doc.Parse("<!-- comment --><root/>");
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_FALSE(doc.Error());
    EXPECT_NE(doc.RootElement(), nullptr);
}

// ============================================================
// SaveFile compact flag
// ============================================================

TEST_F(XMLDocumentTest_289, SaveFileCompact_289) {
    const char* filename = "test_compact_289.xml";
    XMLDocument doc;
    doc.Parse("<root>\n  <child/>\n</root>");
    ASSERT_FALSE(doc.Error());

    XMLError err = doc.SaveFile(filename, true);
    EXPECT_EQ(err, XML_SUCCESS);

    std::remove(filename);
}

TEST_F(XMLDocumentTest_289, SaveFileNotCompact_289) {
    const char* filename = "test_not_compact_289.xml";
    XMLDocument doc;
    doc.Parse("<root><child/></root>");
    ASSERT_FALSE(doc.Error());

    XMLError err = doc.SaveFile(filename, false);
    EXPECT_EQ(err, XML_SUCCESS);

    std::remove(filename);
}
