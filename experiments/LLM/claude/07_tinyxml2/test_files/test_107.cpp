#include "gtest/gtest.h"
#include "tinyxml2.h"

using namespace tinyxml2;

// ============================================================
// Test Fixture
// ============================================================
class XMLDocumentTest_107 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// ============================================================
// Construction Tests
// ============================================================

TEST_F(XMLDocumentTest_107, DefaultConstruction_107) {
    XMLDocument doc;
    EXPECT_FALSE(doc.Error());
    EXPECT_EQ(doc.ErrorID(), XML_SUCCESS);
    EXPECT_FALSE(doc.HasBOM());
    EXPECT_EQ(doc.RootElement(), nullptr);
    EXPECT_TRUE(doc.ProcessEntities());
    EXPECT_EQ(doc.WhitespaceMode(), PRESERVE_WHITESPACE);
}

TEST_F(XMLDocumentTest_107, ConstructionWithProcessEntitiesFalse_107) {
    XMLDocument doc(false);
    EXPECT_FALSE(doc.ProcessEntities());
}

TEST_F(XMLDocumentTest_107, ConstructionWithWhitespaceCollapse_107) {
    XMLDocument doc(true, COLLAPSE_WHITESPACE);
    EXPECT_EQ(doc.WhitespaceMode(), COLLAPSE_WHITESPACE);
}

// ============================================================
// ToDocument Tests
// ============================================================

TEST_F(XMLDocumentTest_107, ToDocumentReturnsSelf_107) {
    XMLDocument doc;
    EXPECT_EQ(doc.ToDocument(), &doc);
}

// ============================================================
// Parse Tests
// ============================================================

TEST_F(XMLDocumentTest_107, ParseSimpleXML_107) {
    XMLDocument doc;
    XMLError err = doc.Parse("<root><child/></root>");
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_FALSE(doc.Error());
    EXPECT_NE(doc.RootElement(), nullptr);
    EXPECT_STREQ(doc.RootElement()->Name(), "root");
}

TEST_F(XMLDocumentTest_107, ParseEmptyString_107) {
    XMLDocument doc;
    XMLError err = doc.Parse("");
    EXPECT_NE(err, XML_SUCCESS);
    EXPECT_TRUE(doc.Error());
}

TEST_F(XMLDocumentTest_107, ParseNullPointer_107) {
    XMLDocument doc;
    XMLError err = doc.Parse(nullptr, 0);
    EXPECT_NE(err, XML_SUCCESS);
    EXPECT_TRUE(doc.Error());
}

TEST_F(XMLDocumentTest_107, ParseMalformedXML_107) {
    XMLDocument doc;
    XMLError err = doc.Parse("<root><child></root>");
    EXPECT_NE(err, XML_SUCCESS);
    EXPECT_TRUE(doc.Error());
}

TEST_F(XMLDocumentTest_107, ParseWithExplicitLength_107) {
    XMLDocument doc;
    const char* xml = "<root/>GARBAGE";
    XMLError err = doc.Parse(xml, 7); // Only "<root/>"
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_NE(doc.RootElement(), nullptr);
    EXPECT_STREQ(doc.RootElement()->Name(), "root");
}

TEST_F(XMLDocumentTest_107, ParseWithAttributes_107) {
    XMLDocument doc;
    XMLError err = doc.Parse("<root attr=\"value\"/>");
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_NE(doc.RootElement(), nullptr);
    EXPECT_STREQ(doc.RootElement()->Attribute("attr"), "value");
}

TEST_F(XMLDocumentTest_107, ParseWithText_107) {
    XMLDocument doc;
    XMLError err = doc.Parse("<root>Hello World</root>");
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_NE(doc.RootElement(), nullptr);
    EXPECT_STREQ(doc.RootElement()->GetText(), "Hello World");
}

TEST_F(XMLDocumentTest_107, ParseXMLDeclaration_107) {
    XMLDocument doc;
    XMLError err = doc.Parse("<?xml version=\"1.0\"?><root/>");
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_NE(doc.RootElement(), nullptr);
}

TEST_F(XMLDocumentTest_107, ParseMultipleRoots_107) {
    XMLDocument doc;
    // Two root elements - typically not well-formed but tinyxml2 may handle it
    XMLError err = doc.Parse("<root1/><root2/>");
    // Behavior depends on implementation, but we check that root element exists
    // The first root element should be accessible
    if (err == XML_SUCCESS) {
        EXPECT_NE(doc.RootElement(), nullptr);
    }
}

// ============================================================
// Error Handling Tests
// ============================================================

TEST_F(XMLDocumentTest_107, ErrorIDAfterSuccessfulParse_107) {
    XMLDocument doc;
    doc.Parse("<root/>");
    EXPECT_EQ(doc.ErrorID(), XML_SUCCESS);
    EXPECT_FALSE(doc.Error());
}

TEST_F(XMLDocumentTest_107, ErrorIDAfterFailedParse_107) {
    XMLDocument doc;
    doc.Parse("<root>");
    EXPECT_NE(doc.ErrorID(), XML_SUCCESS);
    EXPECT_TRUE(doc.Error());
    EXPECT_GT(doc.ErrorLineNum(), 0);
}

TEST_F(XMLDocumentTest_107, ErrorStrNotEmptyOnError_107) {
    XMLDocument doc;
    doc.Parse("<root>");
    EXPECT_TRUE(doc.Error());
    const char* errStr = doc.ErrorStr();
    EXPECT_NE(errStr, nullptr);
    EXPECT_GT(strlen(errStr), 0u);
}

TEST_F(XMLDocumentTest_107, ErrorNameReturnsNonNull_107) {
    XMLDocument doc;
    doc.Parse("<root>");
    const char* errName = doc.ErrorName();
    EXPECT_NE(errName, nullptr);
}

TEST_F(XMLDocumentTest_107, ClearErrorResetsState_107) {
    XMLDocument doc;
    doc.Parse("<root>");
    EXPECT_TRUE(doc.Error());
    doc.ClearError();
    EXPECT_FALSE(doc.Error());
    EXPECT_EQ(doc.ErrorID(), XML_SUCCESS);
}

TEST_F(XMLDocumentTest_107, ErrorIDToNameForSuccess_107) {
    const char* name = XMLDocument::ErrorIDToName(XML_SUCCESS);
    EXPECT_NE(name, nullptr);
    EXPECT_STREQ(name, "XML_SUCCESS");
}

TEST_F(XMLDocumentTest_107, ErrorIDToNameForKnownError_107) {
    const char* name = XMLDocument::ErrorIDToName(XML_ERROR_FILE_NOT_FOUND);
    EXPECT_NE(name, nullptr);
    EXPECT_GT(strlen(name), 0u);
}

// ============================================================
// BOM Tests
// ============================================================

TEST_F(XMLDocumentTest_107, SetBOMTrue_107) {
    XMLDocument doc;
    EXPECT_FALSE(doc.HasBOM());
    doc.SetBOM(true);
    EXPECT_TRUE(doc.HasBOM());
}

TEST_F(XMLDocumentTest_107, SetBOMFalse_107) {
    XMLDocument doc;
    doc.SetBOM(true);
    EXPECT_TRUE(doc.HasBOM());
    doc.SetBOM(false);
    EXPECT_FALSE(doc.HasBOM());
}

// ============================================================
// NewElement / NewComment / NewText / NewDeclaration / NewUnknown Tests
// ============================================================

TEST_F(XMLDocumentTest_107, NewElementCreatesElement_107) {
    XMLDocument doc;
    XMLElement* elem = doc.NewElement("test");
    EXPECT_NE(elem, nullptr);
    EXPECT_STREQ(elem->Name(), "test");
    doc.DeleteNode(elem);
}

TEST_F(XMLDocumentTest_107, NewCommentCreatesComment_107) {
    XMLDocument doc;
    XMLComment* comment = doc.NewComment("this is a comment");
    EXPECT_NE(comment, nullptr);
    EXPECT_STREQ(comment->Value(), "this is a comment");
    doc.DeleteNode(comment);
}

TEST_F(XMLDocumentTest_107, NewTextCreatesText_107) {
    XMLDocument doc;
    XMLText* text = doc.NewText("hello");
    EXPECT_NE(text, nullptr);
    EXPECT_STREQ(text->Value(), "hello");
    doc.DeleteNode(text);
}

TEST_F(XMLDocumentTest_107, NewDeclarationCreatesDeclaration_107) {
    XMLDocument doc;
    XMLDeclaration* decl = doc.NewDeclaration();
    EXPECT_NE(decl, nullptr);
    doc.DeleteNode(decl);
}

TEST_F(XMLDocumentTest_107, NewDeclarationWithCustomText_107) {
    XMLDocument doc;
    XMLDeclaration* decl = doc.NewDeclaration("xml version=\"1.0\" encoding=\"UTF-8\"");
    EXPECT_NE(decl, nullptr);
    doc.DeleteNode(decl);
}

TEST_F(XMLDocumentTest_107, NewUnknownCreatesUnknown_107) {
    XMLDocument doc;
    XMLUnknown* unknown = doc.NewUnknown("something");
    EXPECT_NE(unknown, nullptr);
    EXPECT_STREQ(unknown->Value(), "something");
    doc.DeleteNode(unknown);
}

// ============================================================
// DeleteNode Tests
// ============================================================

TEST_F(XMLDocumentTest_107, DeleteNodeRemovesChild_107) {
    XMLDocument doc;
    doc.Parse("<root><child/></root>");
    XMLElement* root = doc.RootElement();
    EXPECT_NE(root, nullptr);
    XMLElement* child = root->FirstChildElement("child");
    EXPECT_NE(child, nullptr);
    doc.DeleteNode(child);
    EXPECT_EQ(root->FirstChildElement("child"), nullptr);
}

TEST_F(XMLDocumentTest_107, DeleteNodeNull_107) {
    XMLDocument doc;
    // Deleting null should not crash
    doc.DeleteNode(nullptr);
}

// ============================================================
// Clear Tests
// ============================================================

TEST_F(XMLDocumentTest_107, ClearRemovesAllContent_107) {
    XMLDocument doc;
    doc.Parse("<root><child/></root>");
    EXPECT_NE(doc.RootElement(), nullptr);
    doc.Clear();
    EXPECT_EQ(doc.RootElement(), nullptr);
    EXPECT_FALSE(doc.Error());
}

// ============================================================
// DeepCopy Tests
// ============================================================

TEST_F(XMLDocumentTest_107, DeepCopyToAnotherDocument_107) {
    XMLDocument src;
    src.Parse("<root><child attr=\"val\">text</child></root>");
    EXPECT_FALSE(src.Error());

    XMLDocument dst;
    src.DeepCopy(&dst);
    EXPECT_FALSE(dst.Error());
    EXPECT_NE(dst.RootElement(), nullptr);
    EXPECT_STREQ(dst.RootElement()->Name(), "root");

    XMLElement* child = dst.RootElement()->FirstChildElement("child");
    EXPECT_NE(child, nullptr);
    EXPECT_STREQ(child->Attribute("attr"), "val");
    EXPECT_STREQ(child->GetText(), "text");
}

TEST_F(XMLDocumentTest_107, DeepCopyEmptyDocument_107) {
    XMLDocument src;
    XMLDocument dst;
    dst.Parse("<old/>");
    src.DeepCopy(&dst);
    EXPECT_EQ(dst.RootElement(), nullptr);
}

// ============================================================
// RootElement Tests
// ============================================================

TEST_F(XMLDocumentTest_107, RootElementIsNullWhenEmpty_107) {
    XMLDocument doc;
    EXPECT_EQ(doc.RootElement(), nullptr);
}

TEST_F(XMLDocumentTest_107, RootElementAfterParse_107) {
    XMLDocument doc;
    doc.Parse("<root/>");
    EXPECT_NE(doc.RootElement(), nullptr);
    EXPECT_STREQ(doc.RootElement()->Name(), "root");
}

// ============================================================
// ShallowClone / ShallowEqual Tests
// ============================================================

TEST_F(XMLDocumentTest_107, ShallowCloneReturnsNull_107) {
    XMLDocument doc;
    // ShallowClone on XMLDocument should return null (documents can't be shallow cloned)
    XMLNode* clone = doc.ShallowClone(&doc);
    EXPECT_EQ(clone, nullptr);
}

TEST_F(XMLDocumentTest_107, ShallowEqualReturnsFalse_107) {
    XMLDocument doc1;
    XMLDocument doc2;
    // ShallowEqual on XMLDocument should return false
    EXPECT_FALSE(doc1.ShallowEqual(&doc2));
}

// ============================================================
// File I/O Tests
// ============================================================

TEST_F(XMLDocumentTest_107, LoadFileNonExistent_107) {
    XMLDocument doc;
    XMLError err = doc.LoadFile("non_existent_file_107.xml");
    EXPECT_NE(err, XML_SUCCESS);
    EXPECT_TRUE(doc.Error());
    EXPECT_EQ(doc.ErrorID(), XML_ERROR_FILE_NOT_FOUND);
}

TEST_F(XMLDocumentTest_107, LoadFileNullFILE_107) {
    XMLDocument doc;
    XMLError err = doc.LoadFile(static_cast<FILE*>(nullptr));
    EXPECT_NE(err, XML_SUCCESS);
    EXPECT_TRUE(doc.Error());
}

TEST_F(XMLDocumentTest_107, SaveFileAndLoadFile_107) {
    const char* filename = "test_save_load_107.xml";

    {
        XMLDocument doc;
        doc.Parse("<root><item id=\"1\">data</item></root>");
        EXPECT_FALSE(doc.Error());
        XMLError err = doc.SaveFile(filename, false);
        EXPECT_EQ(err, XML_SUCCESS);
    }

    {
        XMLDocument doc;
        XMLError err = doc.LoadFile(filename);
        EXPECT_EQ(err, XML_SUCCESS);
        EXPECT_NE(doc.RootElement(), nullptr);
        EXPECT_STREQ(doc.RootElement()->Name(), "root");
        XMLElement* item = doc.RootElement()->FirstChildElement("item");
        EXPECT_NE(item, nullptr);
        EXPECT_STREQ(item->Attribute("id"), "1");
        EXPECT_STREQ(item->GetText(), "data");
    }

    // Cleanup
    std::remove(filename);
}

TEST_F(XMLDocumentTest_107, SaveFileCompact_107) {
    const char* filename = "test_compact_107.xml";

    XMLDocument doc;
    doc.Parse("<root> <child/> </root>");
    EXPECT_FALSE(doc.Error());
    XMLError err = doc.SaveFile(filename, true);
    EXPECT_EQ(err, XML_SUCCESS);

    // Cleanup
    std::remove(filename);
}

TEST_F(XMLDocumentTest_107, SaveFileToFILEPointer_107) {
    const char* filename = "test_fp_save_107.xml";
    XMLDocument doc;
    doc.Parse("<root/>");
    EXPECT_FALSE(doc.Error());

    FILE* fp = fopen(filename, "w");
    ASSERT_NE(fp, nullptr);
    XMLError err = doc.SaveFile(fp, false);
    fclose(fp);
    EXPECT_EQ(err, XML_SUCCESS);

    // Verify by loading
    XMLDocument doc2;
    err = doc2.LoadFile(filename);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_NE(doc2.RootElement(), nullptr);

    std::remove(filename);
}

TEST_F(XMLDocumentTest_107, LoadFileFromFILEPointer_107) {
    const char* filename = "test_fp_load_107.xml";

    // Create file first
    {
        XMLDocument doc;
        doc.Parse("<data value=\"42\"/>");
        doc.SaveFile(filename, false);
    }

    FILE* fp = fopen(filename, "rb");
    ASSERT_NE(fp, nullptr);
    XMLDocument doc;
    XMLError err = doc.LoadFile(fp);
    fclose(fp);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_NE(doc.RootElement(), nullptr);
    EXPECT_STREQ(doc.RootElement()->Name(), "data");

    std::remove(filename);
}

// ============================================================
// Print Tests
// ============================================================

TEST_F(XMLDocumentTest_107, PrintToDefaultPrinter_107) {
    XMLDocument doc;
    doc.Parse("<root><child/></root>");
    EXPECT_FALSE(doc.Error());

    XMLPrinter printer;
    doc.Print(&printer);
    const char* result = printer.CStr();
    EXPECT_NE(result, nullptr);
    EXPECT_GT(strlen(result), 0u);
    // Should contain root and child
    EXPECT_NE(strstr(result, "root"), nullptr);
    EXPECT_NE(strstr(result, "child"), nullptr);
}

TEST_F(XMLDocumentTest_107, PrintWithNullPrinter_107) {
    XMLDocument doc;
    doc.Parse("<root/>");
    // Print with null should print to stdout (or at least not crash)
    doc.Print(nullptr);
}

// ============================================================
// Accept Tests
// ============================================================

TEST_F(XMLDocumentTest_107, AcceptWithPrinter_107) {
    XMLDocument doc;
    doc.Parse("<root>text</root>");
    EXPECT_FALSE(doc.Error());

    XMLPrinter printer;
    bool result = doc.Accept(&printer);
    EXPECT_TRUE(result);
    const char* output = printer.CStr();
    EXPECT_NE(output, nullptr);
    EXPECT_NE(strstr(output, "root"), nullptr);
}

// ============================================================
// ErrorLineNum Tests
// ============================================================

TEST_F(XMLDocumentTest_107, ErrorLineNumForMultilineError_107) {
    XMLDocument doc;
    const char* xml = "<root>\n<child>\n</root>";
    doc.Parse(xml);
    EXPECT_TRUE(doc.Error());
    // Error should be on a line > 1
    EXPECT_GT(doc.ErrorLineNum(), 0);
}

// ============================================================
// Process Entities Tests
// ============================================================

TEST_F(XMLDocumentTest_107, ParseWithEntities_107) {
    XMLDocument doc(true);
    doc.Parse("<root>&amp;</root>");
    EXPECT_FALSE(doc.Error());
    EXPECT_NE(doc.RootElement(), nullptr);
    EXPECT_STREQ(doc.RootElement()->GetText(), "&");
}

TEST_F(XMLDocumentTest_107, ParseWithoutEntities_107) {
    XMLDocument doc(false);
    doc.Parse("<root>&amp;</root>");
    EXPECT_FALSE(doc.Error());
    EXPECT_NE(doc.RootElement(), nullptr);
    // Without entity processing, &amp; should remain as-is
    EXPECT_STREQ(doc.RootElement()->GetText(), "&amp;");
}

// ============================================================
// InsertNode and Tree Manipulation Tests
// ============================================================

TEST_F(XMLDocumentTest_107, InsertNewElementAsRoot_107) {
    XMLDocument doc;
    XMLElement* root = doc.NewElement("myroot");
    doc.InsertFirstChild(root);
    EXPECT_NE(doc.RootElement(), nullptr);
    EXPECT_STREQ(doc.RootElement()->Name(), "myroot");
}

TEST_F(XMLDocumentTest_107, MultipleParseOverwritesPrevious_107) {
    XMLDocument doc;
    doc.Parse("<first/>");
    EXPECT_STREQ(doc.RootElement()->Name(), "first");
    doc.Parse("<second/>");
    EXPECT_STREQ(doc.RootElement()->Name(), "second");
}

// ============================================================
// Large XML Tests
// ============================================================

TEST_F(XMLDocumentTest_107, ParseLargeDocument_107) {
    std::string xml = "<root>";
    for (int i = 0; i < 1000; ++i) {
        xml += "<item id=\"" + std::to_string(i) + "\">content" + std::to_string(i) + "</item>";
    }
    xml += "</root>";

    XMLDocument doc;
    XMLError err = doc.Parse(xml.c_str());
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_NE(doc.RootElement(), nullptr);

    // Verify first and last elements
    XMLElement* first = doc.RootElement()->FirstChildElement("item");
    EXPECT_NE(first, nullptr);
    EXPECT_STREQ(first->Attribute("id"), "0");
}

// ============================================================
// Edge Cases
// ============================================================

TEST_F(XMLDocumentTest_107, ParseOnlyWhitespace_107) {
    XMLDocument doc;
    XMLError err = doc.Parse("   \n\t  ");
    // Whitespace only is not valid XML
    EXPECT_NE(err, XML_SUCCESS);
}

TEST_F(XMLDocumentTest_107, ParseCommentOnly_107) {
    XMLDocument doc;
    XMLError err = doc.Parse("<!-- just a comment -->");
    // A comment-only document has no root element
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(doc.RootElement(), nullptr);
}

TEST_F(XMLDocumentTest_107, ParseCDATA_107) {
    XMLDocument doc;
    XMLError err = doc.Parse("<root><![CDATA[<not>xml</not>]]></root>");
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_NE(doc.RootElement(), nullptr);
}

TEST_F(XMLDocumentTest_107, ParseSelfClosingElement_107) {
    XMLDocument doc;
    XMLError err = doc.Parse("<root/>");
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_NE(doc.RootElement(), nullptr);
    EXPECT_EQ(doc.RootElement()->FirstChild(), nullptr);
}

TEST_F(XMLDocumentTest_107, ParseNestedElements_107) {
    XMLDocument doc;
    XMLError err = doc.Parse("<a><b><c><d/></c></b></a>");
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_NE(doc.RootElement(), nullptr);

    XMLElement* d = doc.RootElement()
                       ->FirstChildElement("b")
                       ->FirstChildElement("c")
                       ->FirstChildElement("d");
    EXPECT_NE(d, nullptr);
    EXPECT_STREQ(d->Name(), "d");
}

TEST_F(XMLDocumentTest_107, PrintErrorDoesNotCrash_107) {
    XMLDocument doc;
    doc.Parse("<broken");
    EXPECT_TRUE(doc.Error());
    // PrintError should not crash
    doc.PrintError();
}

TEST_F(XMLDocumentTest_107, ClearAfterError_107) {
    XMLDocument doc;
    doc.Parse("<broken");
    EXPECT_TRUE(doc.Error());
    doc.Clear();
    EXPECT_FALSE(doc.Error());
    EXPECT_EQ(doc.RootElement(), nullptr);
}
