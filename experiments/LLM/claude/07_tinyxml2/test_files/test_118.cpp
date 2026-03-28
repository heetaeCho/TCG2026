#include "gtest/gtest.h"
#include "tinyxml2.h"
#include <cstdio>
#include <cstring>
#include <string>

using namespace tinyxml2;

// =============================================================================
// Basic Construction and Default State Tests
// =============================================================================

TEST(XMLDocumentTest_118, DefaultConstruction_118) {
    XMLDocument doc;
    EXPECT_FALSE(doc.Error());
    EXPECT_EQ(doc.ErrorID(), XML_SUCCESS);
    EXPECT_EQ(doc.ErrorLineNum(), 0);
    EXPECT_EQ(doc.RootElement(), nullptr);
    EXPECT_FALSE(doc.HasBOM());
}

TEST(XMLDocumentTest_118, ConstructionWithProcessEntitiesFalse_118) {
    XMLDocument doc(false);
    EXPECT_FALSE(doc.ProcessEntities());
}

TEST(XMLDocumentTest_118, ConstructionWithProcessEntitiesTrue_118) {
    XMLDocument doc(true);
    EXPECT_TRUE(doc.ProcessEntities());
}

TEST(XMLDocumentTest_118, DefaultWhitespaceMode_118) {
    XMLDocument doc;
    EXPECT_EQ(doc.WhitespaceMode(), PRESERVE_WHITESPACE);
    // Default is PRESERVE_WHITESPACE based on typical defaults;
    // If not, let's just check it's a valid mode
}

TEST(XMLDocumentTest_118, ConstructionWithCollapseWhitespace_118) {
    XMLDocument doc(true, COLLAPSE_WHITESPACE);
    EXPECT_EQ(doc.WhitespaceMode(), COLLAPSE_WHITESPACE);
}

// =============================================================================
// Parse Tests
// =============================================================================

TEST(XMLDocumentTest_118, ParseValidXML_118) {
    XMLDocument doc;
    XMLError err = doc.Parse("<root><child/></root>");
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_FALSE(doc.Error());
    EXPECT_NE(doc.RootElement(), nullptr);
    EXPECT_STREQ(doc.RootElement()->Name(), "root");
}

TEST(XMLDocumentTest_118, ParseEmptyString_118) {
    XMLDocument doc;
    XMLError err = doc.Parse("");
    EXPECT_NE(err, XML_SUCCESS);
    EXPECT_TRUE(doc.Error());
}

TEST(XMLDocumentTest_118, ParseNullPointer_118) {
    XMLDocument doc;
    XMLError err = doc.Parse(nullptr, 0);
    EXPECT_NE(err, XML_SUCCESS);
    EXPECT_TRUE(doc.Error());
}

TEST(XMLDocumentTest_118, ParseMalformedXML_118) {
    XMLDocument doc;
    XMLError err = doc.Parse("<root><child></root>");
    EXPECT_NE(err, XML_SUCCESS);
    EXPECT_TRUE(doc.Error());
}

TEST(XMLDocumentTest_118, ParseWithSizeLimit_118) {
    XMLDocument doc;
    const char* xml = "<root>hello</root>";
    XMLError err = doc.Parse(xml, strlen(xml));
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_FALSE(doc.Error());
    EXPECT_NE(doc.RootElement(), nullptr);
}

TEST(XMLDocumentTest_118, ParseWithPartialSizeLimit_118) {
    XMLDocument doc;
    const char* xml = "<root>hello</root>extra garbage";
    // Parse only the first part
    XMLError err = doc.Parse(xml, 18); // length of "<root>hello</root>"
    EXPECT_EQ(err, XML_SUCCESS);
}

TEST(XMLDocumentTest_118, ParseXMLWithDeclaration_118) {
    XMLDocument doc;
    XMLError err = doc.Parse("<?xml version=\"1.0\"?><root/>");
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_NE(doc.RootElement(), nullptr);
    EXPECT_STREQ(doc.RootElement()->Name(), "root");
}

TEST(XMLDocumentTest_118, ParseXMLWithBOM_118) {
    XMLDocument doc;
    // UTF-8 BOM: 0xEF, 0xBB, 0xBF
    std::string xml = "\xEF\xBB\xBF<?xml version=\"1.0\"?><root/>";
    XMLError err = doc.Parse(xml.c_str());
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_TRUE(doc.HasBOM());
}

TEST(XMLDocumentTest_118, ParseXMLWithComments_118) {
    XMLDocument doc;
    XMLError err = doc.Parse("<!-- comment --><root/>");
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_NE(doc.RootElement(), nullptr);
}

TEST(XMLDocumentTest_118, ParseXMLWithAttributes_118) {
    XMLDocument doc;
    XMLError err = doc.Parse("<root attr=\"value\"/>");
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_NE(doc.RootElement(), nullptr);
    EXPECT_STREQ(doc.RootElement()->Attribute("attr"), "value");
}

TEST(XMLDocumentTest_118, ParseXMLWithText_118) {
    XMLDocument doc;
    XMLError err = doc.Parse("<root>Hello World</root>");
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_NE(doc.RootElement(), nullptr);
    EXPECT_STREQ(doc.RootElement()->GetText(), "Hello World");
}

TEST(XMLDocumentTest_118, ParseXMLWithEntities_118) {
    XMLDocument doc(true);
    XMLError err = doc.Parse("<root>&amp;&lt;&gt;</root>");
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_NE(doc.RootElement(), nullptr);
    EXPECT_STREQ(doc.RootElement()->GetText(), "&<>");
}

TEST(XMLDocumentTest_118, ParseXMLWithoutProcessingEntities_118) {
    XMLDocument doc(false);
    XMLError err = doc.Parse("<root>&amp;</root>");
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_NE(doc.RootElement(), nullptr);
    // When entities are not processed, the raw text should be preserved
    EXPECT_STREQ(doc.RootElement()->GetText(), "&amp;");
}

// =============================================================================
// BOM Tests
// =============================================================================

TEST(XMLDocumentTest_118, SetBOM_118) {
    XMLDocument doc;
    EXPECT_FALSE(doc.HasBOM());
    doc.SetBOM(true);
    EXPECT_TRUE(doc.HasBOM());
    doc.SetBOM(false);
    EXPECT_FALSE(doc.HasBOM());
}

// =============================================================================
// Error Handling Tests
// =============================================================================

TEST(XMLDocumentTest_118, ErrorIDOnSuccess_118) {
    XMLDocument doc;
    doc.Parse("<root/>");
    EXPECT_EQ(doc.ErrorID(), XML_SUCCESS);
    EXPECT_FALSE(doc.Error());
}

TEST(XMLDocumentTest_118, ErrorIDOnFailure_118) {
    XMLDocument doc;
    doc.Parse("<root>");
    EXPECT_NE(doc.ErrorID(), XML_SUCCESS);
    EXPECT_TRUE(doc.Error());
}

TEST(XMLDocumentTest_118, ClearError_118) {
    XMLDocument doc;
    doc.Parse("<root>"); // malformed
    EXPECT_TRUE(doc.Error());
    doc.ClearError();
    EXPECT_FALSE(doc.Error());
    EXPECT_EQ(doc.ErrorID(), XML_SUCCESS);
}

TEST(XMLDocumentTest_118, ErrorName_118) {
    XMLDocument doc;
    doc.Parse("<root/>");
    const char* name = doc.ErrorName();
    EXPECT_NE(name, nullptr);
    EXPECT_STREQ(name, "XML_SUCCESS");
}

TEST(XMLDocumentTest_118, ErrorIDToNameSuccess_118) {
    const char* name = XMLDocument::ErrorIDToName(XML_SUCCESS);
    EXPECT_NE(name, nullptr);
    EXPECT_STREQ(name, "XML_SUCCESS");
}

TEST(XMLDocumentTest_118, ErrorIDToNameVariousErrors_118) {
    const char* name = XMLDocument::ErrorIDToName(XML_ERROR_FILE_NOT_FOUND);
    EXPECT_NE(name, nullptr);
    // Just verify it returns a non-null, non-empty string
    EXPECT_GT(strlen(name), 0u);
}

TEST(XMLDocumentTest_118, ErrorStr_118) {
    XMLDocument doc;
    doc.Parse("not xml at all <<<>>>");
    EXPECT_TRUE(doc.Error());
    const char* errStr = doc.ErrorStr();
    EXPECT_NE(errStr, nullptr);
    EXPECT_GT(strlen(errStr), 0u);
}

TEST(XMLDocumentTest_118, ErrorLineNum_118) {
    XMLDocument doc;
    doc.Parse("<root>\n<child>\n</root>");
    EXPECT_TRUE(doc.Error());
    EXPECT_GT(doc.ErrorLineNum(), 0);
}

// =============================================================================
// New Node Creation Tests
// =============================================================================

TEST(XMLDocumentTest_118, NewElement_118) {
    XMLDocument doc;
    XMLElement* elem = doc.NewElement("test");
    EXPECT_NE(elem, nullptr);
    EXPECT_STREQ(elem->Name(), "test");
    doc.InsertFirstChild(elem);
    EXPECT_EQ(doc.RootElement(), elem);
}

TEST(XMLDocumentTest_118, NewComment_118) {
    XMLDocument doc;
    XMLComment* comment = doc.NewComment("this is a comment");
    EXPECT_NE(comment, nullptr);
    doc.InsertFirstChild(comment);
}

TEST(XMLDocumentTest_118, NewText_118) {
    XMLDocument doc;
    XMLText* text = doc.NewText("hello");
    EXPECT_NE(text, nullptr);
}

TEST(XMLDocumentTest_118, NewDeclaration_118) {
    XMLDocument doc;
    XMLDeclaration* decl = doc.NewDeclaration();
    EXPECT_NE(decl, nullptr);
}

TEST(XMLDocumentTest_118, NewDeclarationWithCustomText_118) {
    XMLDocument doc;
    XMLDeclaration* decl = doc.NewDeclaration("xml version=\"1.0\" encoding=\"UTF-8\"");
    EXPECT_NE(decl, nullptr);
}

TEST(XMLDocumentTest_118, NewUnknown_118) {
    XMLDocument doc;
    XMLUnknown* unknown = doc.NewUnknown("some unknown stuff");
    EXPECT_NE(unknown, nullptr);
}

// =============================================================================
// DeleteNode Tests
// =============================================================================

TEST(XMLDocumentTest_118, DeleteNode_118) {
    XMLDocument doc;
    doc.Parse("<root><child/></root>");
    XMLElement* root = doc.RootElement();
    EXPECT_NE(root, nullptr);
    XMLElement* child = root->FirstChildElement("child");
    EXPECT_NE(child, nullptr);
    doc.DeleteNode(child);
    EXPECT_EQ(root->FirstChildElement("child"), nullptr);
}

TEST(XMLDocumentTest_118, DeleteNullNode_118) {
    XMLDocument doc;
    // Should not crash
    doc.DeleteNode(nullptr);
}

// =============================================================================
// Clear Tests
// =============================================================================

TEST(XMLDocumentTest_118, Clear_118) {
    XMLDocument doc;
    doc.Parse("<root><child/></root>");
    EXPECT_NE(doc.RootElement(), nullptr);
    doc.Clear();
    EXPECT_EQ(doc.RootElement(), nullptr);
    EXPECT_FALSE(doc.Error());
}

TEST(XMLDocumentTest_118, ClearOnEmptyDocument_118) {
    XMLDocument doc;
    doc.Clear();
    EXPECT_EQ(doc.RootElement(), nullptr);
    EXPECT_FALSE(doc.Error());
}

// =============================================================================
// DeepCopy Tests
// =============================================================================

TEST(XMLDocumentTest_118, DeepCopy_118) {
    XMLDocument source;
    source.Parse("<root><child attr=\"val\">text</child></root>");
    EXPECT_FALSE(source.Error());

    XMLDocument target;
    source.DeepCopy(&target);

    EXPECT_NE(target.RootElement(), nullptr);
    EXPECT_STREQ(target.RootElement()->Name(), "root");

    XMLElement* childCopy = target.RootElement()->FirstChildElement("child");
    EXPECT_NE(childCopy, nullptr);
    EXPECT_STREQ(childCopy->Attribute("attr"), "val");
    EXPECT_STREQ(childCopy->GetText(), "text");
}

TEST(XMLDocumentTest_118, DeepCopyPreservesBOM_118) {
    XMLDocument source;
    std::string xml = "\xEF\xBB\xBF<?xml version=\"1.0\"?><root/>";
    source.Parse(xml.c_str());
    EXPECT_TRUE(source.HasBOM());

    XMLDocument target;
    source.DeepCopy(&target);
    EXPECT_TRUE(target.HasBOM());
}

TEST(XMLDocumentTest_118, DeepCopyEmptyDocument_118) {
    XMLDocument source;
    XMLDocument target;
    target.Parse("<root/>");
    EXPECT_NE(target.RootElement(), nullptr);

    source.DeepCopy(&target);
    EXPECT_EQ(target.RootElement(), nullptr);
}

// =============================================================================
// ToDocument Tests
// =============================================================================

TEST(XMLDocumentTest_118, ToDocument_118) {
    XMLDocument doc;
    EXPECT_EQ(doc.ToDocument(), &doc);
}

// =============================================================================
// ShallowClone / ShallowEqual Tests
// =============================================================================

TEST(XMLDocumentTest_118, ShallowCloneReturnsNull_118) {
    XMLDocument doc;
    XMLNode* clone = doc.ShallowClone(&doc);
    EXPECT_EQ(clone, nullptr);
}

TEST(XMLDocumentTest_118, ShallowEqualReturnsFalse_118) {
    XMLDocument doc1;
    XMLDocument doc2;
    EXPECT_FALSE(doc1.ShallowEqual(&doc2));
}

// =============================================================================
// File I/O Tests
// =============================================================================

TEST(XMLDocumentTest_118, LoadFileNonExistent_118) {
    XMLDocument doc;
    XMLError err = doc.LoadFile("nonexistent_file_that_does_not_exist.xml");
    EXPECT_NE(err, XML_SUCCESS);
    EXPECT_TRUE(doc.Error());
    EXPECT_EQ(doc.ErrorID(), XML_ERROR_FILE_NOT_FOUND);
}

TEST(XMLDocumentTest_118, SaveAndLoadFile_118) {
    const char* filename = "test_save_load_118.xml";

    // Save
    {
        XMLDocument doc;
        doc.Parse("<root><child>value</child></root>");
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
    }

    // Cleanup
    std::remove(filename);
}

TEST(XMLDocumentTest_118, SaveFileCompact_118) {
    const char* filename = "test_save_compact_118.xml";

    XMLDocument doc;
    doc.Parse("<root> <child> value </child> </root>");
    EXPECT_FALSE(doc.Error());
    XMLError err = doc.SaveFile(filename, true);
    EXPECT_EQ(err, XML_SUCCESS);

    // Cleanup
    std::remove(filename);
}

TEST(XMLDocumentTest_118, LoadFileFromFILE_118) {
    const char* filename = "test_load_fp_118.xml";

    // Create a file first
    {
        XMLDocument doc;
        doc.Parse("<root>test</root>");
        doc.SaveFile(filename, false);
    }

    FILE* fp = fopen(filename, "rb");
    ASSERT_NE(fp, nullptr);

    XMLDocument doc;
    XMLError err = doc.LoadFile(fp);
    fclose(fp);

    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_NE(doc.RootElement(), nullptr);

    std::remove(filename);
}

TEST(XMLDocumentTest_118, SaveFileToFILE_118) {
    const char* filename = "test_save_fp_118.xml";

    XMLDocument doc;
    doc.Parse("<root>test</root>");

    FILE* fp = fopen(filename, "w");
    ASSERT_NE(fp, nullptr);

    XMLError err = doc.SaveFile(fp, false);
    fclose(fp);

    EXPECT_EQ(err, XML_SUCCESS);

    // Verify by loading
    XMLDocument doc2;
    EXPECT_EQ(doc2.LoadFile(filename), XML_SUCCESS);
    EXPECT_STREQ(doc2.RootElement()->GetText(), "test");

    std::remove(filename);
}

TEST(XMLDocumentTest_118, LoadFileNullFP_118) {
    XMLDocument doc;
    XMLError err = doc.LoadFile((FILE*)nullptr);
    EXPECT_NE(err, XML_SUCCESS);
    EXPECT_TRUE(doc.Error());
}

// =============================================================================
// Print Tests
// =============================================================================

TEST(XMLDocumentTest_118, PrintToStreamer_118) {
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

TEST(XMLDocumentTest_118, PrintWithNullStreamer_118) {
    XMLDocument doc;
    doc.Parse("<root/>");
    // Print with nullptr should print to stdout (not crash)
    doc.Print(nullptr);
}

// =============================================================================
// Accept (Visitor) Tests
// =============================================================================

TEST(XMLDocumentTest_118, AcceptVisitor_118) {
    XMLDocument doc;
    doc.Parse("<root><child/></root>");
    EXPECT_FALSE(doc.Error());

    XMLPrinter printer;
    bool result = doc.Accept(&printer);
    EXPECT_TRUE(result);

    const char* output = printer.CStr();
    EXPECT_NE(output, nullptr);
    EXPECT_NE(strstr(output, "root"), nullptr);
}

// =============================================================================
// Re-parse (overwrite) Tests
// =============================================================================

TEST(XMLDocumentTest_118, ReparseOverwritesPreviousContent_118) {
    XMLDocument doc;
    doc.Parse("<first/>");
    EXPECT_STREQ(doc.RootElement()->Name(), "first");

    doc.Parse("<second/>");
    EXPECT_STREQ(doc.RootElement()->Name(), "second");
}

// =============================================================================
// Complex XML Tests
// =============================================================================

TEST(XMLDocumentTest_118, ParseComplexXML_118) {
    const char* xml =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<library>\n"
        "  <book id=\"1\">\n"
        "    <title>Test Book</title>\n"
        "    <author>Author Name</author>\n"
        "  </book>\n"
        "  <book id=\"2\">\n"
        "    <title>Another Book</title>\n"
        "    <author>Other Author</author>\n"
        "  </book>\n"
        "</library>";

    XMLDocument doc;
    XMLError err = doc.Parse(xml);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_FALSE(doc.Error());

    XMLElement* root = doc.RootElement();
    EXPECT_NE(root, nullptr);
    EXPECT_STREQ(root->Name(), "library");

    XMLElement* book1 = root->FirstChildElement("book");
    EXPECT_NE(book1, nullptr);
    EXPECT_STREQ(book1->Attribute("id"), "1");

    XMLElement* title1 = book1->FirstChildElement("title");
    EXPECT_NE(title1, nullptr);
    EXPECT_STREQ(title1->GetText(), "Test Book");

    XMLElement* book2 = book1->NextSiblingElement("book");
    EXPECT_NE(book2, nullptr);
    EXPECT_STREQ(book2->Attribute("id"), "2");
}

// =============================================================================
// MarkInUse Tests  
// =============================================================================

TEST(XMLDocumentTest_118, MarkInUseUnlinkedNode_118) {
    XMLDocument doc;
    XMLElement* elem = doc.NewElement("test");
    // MarkInUse should not crash for an unlinked node
    doc.MarkInUse(elem);
    // Insert it after marking
    doc.InsertFirstChild(elem);
    EXPECT_STREQ(doc.RootElement()->Name(), "test");
}

// =============================================================================
// Multiple Root Elements (invalid XML) Tests
// =============================================================================

TEST(XMLDocumentTest_118, ParseMultipleRootElements_118) {
    XMLDocument doc;
    // Multiple root elements - behavior may vary
    XMLError err = doc.Parse("<root1/><root2/>");
    // tinyxml2 typically allows this silently - first element is root
    if (err == XML_SUCCESS) {
        EXPECT_NE(doc.RootElement(), nullptr);
        EXPECT_STREQ(doc.RootElement()->Name(), "root1");
    }
}

// =============================================================================
// PrintError Tests
// =============================================================================

TEST(XMLDocumentTest_118, PrintErrorOnErrorDoc_118) {
    XMLDocument doc;
    doc.Parse("<malformed");
    EXPECT_TRUE(doc.Error());
    // Should not crash; prints to stderr
    doc.PrintError();
}

TEST(XMLDocumentTest_118, PrintErrorOnCleanDoc_118) {
    XMLDocument doc;
    doc.Parse("<root/>");
    EXPECT_FALSE(doc.Error());
    // Should not crash even without error
    doc.PrintError();
}

// =============================================================================
// Edge Case: Very Deeply Nested XML
// =============================================================================

TEST(XMLDocumentTest_118, DeeplyNestedXML_118) {
    // Build a deeply nested XML string
    std::string xml;
    int depth = 100;
    for (int i = 0; i < depth; ++i) {
        xml += "<n>";
    }
    for (int i = 0; i < depth; ++i) {
        xml += "</n>";
    }

    XMLDocument doc;
    XMLError err = doc.Parse(xml.c_str());
    // Depending on implementation limits, this might succeed or fail
    // We just verify no crash and consistent state
    if (err == XML_SUCCESS) {
        EXPECT_FALSE(doc.Error());
        EXPECT_NE(doc.RootElement(), nullptr);
    } else {
        EXPECT_TRUE(doc.Error());
    }
}

// =============================================================================
// Edge Case: XML with CDATA
// =============================================================================

TEST(XMLDocumentTest_118, ParseXMLWithCDATA_118) {
    XMLDocument doc;
    XMLError err = doc.Parse("<root><![CDATA[Some <special> text & more]]></root>");
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_NE(doc.RootElement(), nullptr);
}

// =============================================================================
// Edge Case: Empty root element
// =============================================================================

TEST(XMLDocumentTest_118, ParseEmptyRootElement_118) {
    XMLDocument doc;
    XMLError err = doc.Parse("<root/>");
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_NE(doc.RootElement(), nullptr);
    EXPECT_STREQ(doc.RootElement()->Name(), "root");
    EXPECT_EQ(doc.RootElement()->FirstChild(), nullptr);
}

// =============================================================================
// New nodes not yet inserted
// =============================================================================

TEST(XMLDocumentTest_118, NewElementNotInserted_118) {
    XMLDocument doc;
    doc.Parse("<root/>");
    XMLElement* elem = doc.NewElement("orphan");
    // The element exists but is not part of the tree
    EXPECT_NE(elem, nullptr);
    EXPECT_STREQ(elem->Name(), "orphan");
    // Root should still be "root"
    EXPECT_STREQ(doc.RootElement()->Name(), "root");
    // Clean up: Clear should handle it
    doc.Clear();
}

// =============================================================================
// Whitespace handling
// =============================================================================

TEST(XMLDocumentTest_118, CollapseWhitespace_118) {
    XMLDocument doc(true, COLLAPSE_WHITESPACE);
    doc.Parse("<root>  hello   world  </root>");
    EXPECT_FALSE(doc.Error());
    EXPECT_NE(doc.RootElement(), nullptr);
    // With collapse whitespace, leading/trailing/multiple spaces should be collapsed
    const char* text = doc.RootElement()->GetText();
    EXPECT_NE(text, nullptr);
}

TEST(XMLDocumentTest_118, PreserveWhitespace_118) {
    XMLDocument doc(true, PRESERVE_WHITESPACE);
    doc.Parse("<root>  hello   world  </root>");
    EXPECT_FALSE(doc.Error());
    EXPECT_NE(doc.RootElement(), nullptr);
    const char* text = doc.RootElement()->GetText();
    EXPECT_NE(text, nullptr);
    EXPECT_STREQ(text, "  hello   world  ");
}
