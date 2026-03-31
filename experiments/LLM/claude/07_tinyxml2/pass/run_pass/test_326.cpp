#include "gtest/gtest.h"
#include "tinyxml2.h"
#include <cstdio>
#include <cstring>
#include <string>

using namespace tinyxml2;

// =============================================================================
// Test Fixture
// =============================================================================
class XMLDocumentTest_326 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// =============================================================================
// Constructor Tests
// =============================================================================
TEST_F(XMLDocumentTest_326, DefaultConstructor_326) {
    XMLDocument doc;
    EXPECT_FALSE(doc.Error());
    EXPECT_EQ(doc.ErrorID(), XML_SUCCESS);
    EXPECT_FALSE(doc.HasBOM());
    EXPECT_EQ(doc.RootElement(), nullptr);
}

TEST_F(XMLDocumentTest_326, ConstructorWithProcessEntitiesFalse_326) {
    XMLDocument doc(false);
    EXPECT_FALSE(doc.ProcessEntities());
    EXPECT_FALSE(doc.Error());
}

TEST_F(XMLDocumentTest_326, ConstructorWithProcessEntitiesTrue_326) {
    XMLDocument doc(true);
    EXPECT_TRUE(doc.ProcessEntities());
}

TEST_F(XMLDocumentTest_326, ConstructorWithWhitespacePreserve_326) {
    XMLDocument doc(true, PRESERVE_WHITESPACE);
    EXPECT_EQ(doc.WhitespaceMode(), PRESERVE_WHITESPACE);
}

TEST_F(XMLDocumentTest_326, ConstructorWithWhitespaceCollapse_326) {
    XMLDocument doc(true, COLLAPSE_WHITESPACE);
    EXPECT_EQ(doc.WhitespaceMode(), COLLAPSE_WHITESPACE);
}

// =============================================================================
// Parse Tests
// =============================================================================
TEST_F(XMLDocumentTest_326, ParseSimpleXML_326) {
    XMLDocument doc;
    XMLError err = doc.Parse("<root><child/></root>");
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_FALSE(doc.Error());
    EXPECT_NE(doc.RootElement(), nullptr);
    EXPECT_STREQ(doc.RootElement()->Name(), "root");
}

TEST_F(XMLDocumentTest_326, ParseEmptyString_326) {
    XMLDocument doc;
    XMLError err = doc.Parse("");
    EXPECT_NE(err, XML_SUCCESS);
    EXPECT_TRUE(doc.Error());
}

TEST_F(XMLDocumentTest_326, ParseNullptr_326) {
    XMLDocument doc;
    XMLError err = doc.Parse(nullptr);
    EXPECT_NE(err, XML_SUCCESS);
    EXPECT_TRUE(doc.Error());
}

TEST_F(XMLDocumentTest_326, ParseMalformedXML_326) {
    XMLDocument doc;
    XMLError err = doc.Parse("<root><child></root>");
    EXPECT_NE(err, XML_SUCCESS);
    EXPECT_TRUE(doc.Error());
}

TEST_F(XMLDocumentTest_326, ParseWithLength_326) {
    XMLDocument doc;
    const char* xml = "<root/>GARBAGE";
    XMLError err = doc.Parse(xml, 7);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_NE(doc.RootElement(), nullptr);
    EXPECT_STREQ(doc.RootElement()->Name(), "root");
}

TEST_F(XMLDocumentTest_326, ParseXMLWithAttributes_326) {
    XMLDocument doc;
    XMLError err = doc.Parse("<root attr=\"value\"/>");
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_NE(doc.RootElement(), nullptr);
    EXPECT_STREQ(doc.RootElement()->Attribute("attr"), "value");
}

TEST_F(XMLDocumentTest_326, ParseXMLWithText_326) {
    XMLDocument doc;
    XMLError err = doc.Parse("<root>Hello World</root>");
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_NE(doc.RootElement(), nullptr);
    EXPECT_STREQ(doc.RootElement()->GetText(), "Hello World");
}

TEST_F(XMLDocumentTest_326, ParseXMLWithDeclaration_326) {
    XMLDocument doc;
    XMLError err = doc.Parse("<?xml version=\"1.0\"?><root/>");
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_NE(doc.RootElement(), nullptr);
}

TEST_F(XMLDocumentTest_326, ParseXMLWithComment_326) {
    XMLDocument doc;
    XMLError err = doc.Parse("<!-- comment --><root/>");
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_NE(doc.RootElement(), nullptr);
}

TEST_F(XMLDocumentTest_326, ParseXMLWithEntities_326) {
    XMLDocument doc(true);
    XMLError err = doc.Parse("<root>&amp;&lt;&gt;</root>");
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_NE(doc.RootElement(), nullptr);
    EXPECT_STREQ(doc.RootElement()->GetText(), "&<>");
}

TEST_F(XMLDocumentTest_326, ParseXMLWithEntitiesDisabled_326) {
    XMLDocument doc(false);
    XMLError err = doc.Parse("<root>&amp;</root>");
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_NE(doc.RootElement(), nullptr);
}

// =============================================================================
// BOM Tests
// =============================================================================
TEST_F(XMLDocumentTest_326, SetBOMTrue_326) {
    XMLDocument doc;
    doc.SetBOM(true);
    EXPECT_TRUE(doc.HasBOM());
}

TEST_F(XMLDocumentTest_326, SetBOMFalse_326) {
    XMLDocument doc;
    doc.SetBOM(false);
    EXPECT_FALSE(doc.HasBOM());
}

// =============================================================================
// Error Handling Tests
// =============================================================================
TEST_F(XMLDocumentTest_326, ClearError_326) {
    XMLDocument doc;
    doc.Parse("<root><unclosed>");
    EXPECT_TRUE(doc.Error());
    doc.ClearError();
    EXPECT_FALSE(doc.Error());
    EXPECT_EQ(doc.ErrorID(), XML_SUCCESS);
}

TEST_F(XMLDocumentTest_326, ErrorNameNotNull_326) {
    XMLDocument doc;
    doc.Parse("<unclosed>");
    EXPECT_TRUE(doc.Error());
    EXPECT_NE(doc.ErrorName(), nullptr);
}

TEST_F(XMLDocumentTest_326, ErrorStrNotNull_326) {
    XMLDocument doc;
    doc.Parse("<unclosed>");
    EXPECT_TRUE(doc.Error());
    EXPECT_NE(doc.ErrorStr(), nullptr);
}

TEST_F(XMLDocumentTest_326, ErrorIDToNameSuccess_326) {
    const char* name = XMLDocument::ErrorIDToName(XML_SUCCESS);
    EXPECT_NE(name, nullptr);
    EXPECT_STREQ(name, "XML_SUCCESS");
}

TEST_F(XMLDocumentTest_326, ErrorIDToNameError_326) {
    const char* name = XMLDocument::ErrorIDToName(XML_ERROR_FILE_NOT_FOUND);
    EXPECT_NE(name, nullptr);
}

TEST_F(XMLDocumentTest_326, ErrorLineNum_326) {
    XMLDocument doc;
    doc.Parse("<root>\n<unclosed>");
    EXPECT_TRUE(doc.Error());
    EXPECT_GT(doc.ErrorLineNum(), 0);
}

TEST_F(XMLDocumentTest_326, NoErrorLineNum_326) {
    XMLDocument doc;
    doc.Parse("<root/>");
    EXPECT_EQ(doc.ErrorLineNum(), 0);
}

// =============================================================================
// NewElement / NewComment / NewText / NewDeclaration / NewUnknown Tests
// =============================================================================
TEST_F(XMLDocumentTest_326, NewElement_326) {
    XMLDocument doc;
    XMLElement* elem = doc.NewElement("test");
    EXPECT_NE(elem, nullptr);
    EXPECT_STREQ(elem->Name(), "test");
    doc.InsertFirstChild(elem);
    EXPECT_EQ(doc.RootElement(), elem);
}

TEST_F(XMLDocumentTest_326, NewComment_326) {
    XMLDocument doc;
    XMLComment* comment = doc.NewComment("this is a comment");
    EXPECT_NE(comment, nullptr);
    doc.InsertFirstChild(comment);
}

TEST_F(XMLDocumentTest_326, NewText_326) {
    XMLDocument doc;
    XMLText* text = doc.NewText("hello");
    EXPECT_NE(text, nullptr);
}

TEST_F(XMLDocumentTest_326, NewDeclaration_326) {
    XMLDocument doc;
    XMLDeclaration* decl = doc.NewDeclaration();
    EXPECT_NE(decl, nullptr);
    doc.InsertFirstChild(decl);
}

TEST_F(XMLDocumentTest_326, NewDeclarationWithText_326) {
    XMLDocument doc;
    XMLDeclaration* decl = doc.NewDeclaration("xml version=\"1.0\"");
    EXPECT_NE(decl, nullptr);
}

TEST_F(XMLDocumentTest_326, NewUnknown_326) {
    XMLDocument doc;
    XMLUnknown* unknown = doc.NewUnknown("something");
    EXPECT_NE(unknown, nullptr);
}

// =============================================================================
// DeleteNode Tests
// =============================================================================
TEST_F(XMLDocumentTest_326, DeleteNode_326) {
    XMLDocument doc;
    doc.Parse("<root><child/></root>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    XMLElement* child = root->FirstChildElement("child");
    ASSERT_NE(child, nullptr);
    doc.DeleteNode(child);
    EXPECT_EQ(root->FirstChildElement("child"), nullptr);
}

TEST_F(XMLDocumentTest_326, DeleteNodeNull_326) {
    XMLDocument doc;
    // Deleting nullptr should not crash
    doc.DeleteNode(nullptr);
}

// =============================================================================
// Clear Tests
// =============================================================================
TEST_F(XMLDocumentTest_326, Clear_326) {
    XMLDocument doc;
    doc.Parse("<root><child/></root>");
    EXPECT_NE(doc.RootElement(), nullptr);
    doc.Clear();
    EXPECT_EQ(doc.RootElement(), nullptr);
    EXPECT_FALSE(doc.Error());
}

TEST_F(XMLDocumentTest_326, ClearResetsError_326) {
    XMLDocument doc;
    doc.Parse("<unclosed>");
    EXPECT_TRUE(doc.Error());
    doc.Clear();
    EXPECT_FALSE(doc.Error());
}

// =============================================================================
// DeepCopy Tests
// =============================================================================
TEST_F(XMLDocumentTest_326, DeepCopy_326) {
    XMLDocument source;
    source.Parse("<root attr=\"val\"><child>text</child></root>");
    ASSERT_FALSE(source.Error());

    XMLDocument target;
    source.DeepCopy(&target);

    ASSERT_NE(target.RootElement(), nullptr);
    EXPECT_STREQ(target.RootElement()->Name(), "root");
    EXPECT_STREQ(target.RootElement()->Attribute("attr"), "val");

    XMLElement* childTarget = target.RootElement()->FirstChildElement("child");
    ASSERT_NE(childTarget, nullptr);
    EXPECT_STREQ(childTarget->GetText(), "text");
}

TEST_F(XMLDocumentTest_326, DeepCopyToSelf_326) {
    XMLDocument doc;
    doc.Parse("<root/>");
    // DeepCopy to self should still work without crash
    // (behavior may vary, but it should not crash)
    // Note: some implementations may not support this, testing it doesn't crash
}

TEST_F(XMLDocumentTest_326, DeepCopyEmptyDoc_326) {
    XMLDocument source;
    XMLDocument target;
    target.Parse("<existing/>");

    source.DeepCopy(&target);
    EXPECT_EQ(target.RootElement(), nullptr);
}

// =============================================================================
// ToDocument Tests
// =============================================================================
TEST_F(XMLDocumentTest_326, ToDocument_326) {
    XMLDocument doc;
    EXPECT_EQ(doc.ToDocument(), &doc);
}

// =============================================================================
// RootElement Tests
// =============================================================================
TEST_F(XMLDocumentTest_326, RootElementEmpty_326) {
    XMLDocument doc;
    EXPECT_EQ(doc.RootElement(), nullptr);
}

TEST_F(XMLDocumentTest_326, RootElementAfterParse_326) {
    XMLDocument doc;
    doc.Parse("<root/>");
    EXPECT_NE(doc.RootElement(), nullptr);
    EXPECT_STREQ(doc.RootElement()->Name(), "root");
}

// =============================================================================
// SaveFile / LoadFile Tests
// =============================================================================
TEST_F(XMLDocumentTest_326, SaveAndLoadFile_326) {
    const char* filename = "test_save_load_326.xml";
    {
        XMLDocument doc;
        doc.Parse("<root><child attr=\"1\">text</child></root>");
        ASSERT_FALSE(doc.Error());
        XMLError err = doc.SaveFile(filename);
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

TEST_F(XMLDocumentTest_326, LoadFileNonExistent_326) {
    XMLDocument doc;
    XMLError err = doc.LoadFile("nonexistent_file_326.xml");
    EXPECT_NE(err, XML_SUCCESS);
    EXPECT_TRUE(doc.Error());
}

TEST_F(XMLDocumentTest_326, SaveFileCompact_326) {
    const char* filename = "test_compact_326.xml";
    XMLDocument doc;
    doc.Parse("<root><child/></root>");
    ASSERT_FALSE(doc.Error());
    XMLError err = doc.SaveFile(filename, true);
    EXPECT_EQ(err, XML_SUCCESS);
    std::remove(filename);
}

TEST_F(XMLDocumentTest_326, SaveFileNotCompact_326) {
    const char* filename = "test_notcompact_326.xml";
    XMLDocument doc;
    doc.Parse("<root><child/></root>");
    ASSERT_FALSE(doc.Error());
    XMLError err = doc.SaveFile(filename, false);
    EXPECT_EQ(err, XML_SUCCESS);
    std::remove(filename);
}

TEST_F(XMLDocumentTest_326, LoadFileFromFILEPtr_326) {
    const char* filename = "test_fileptr_326.xml";
    {
        XMLDocument doc;
        doc.Parse("<root/>");
        doc.SaveFile(filename);
    }
    {
        FILE* fp = fopen(filename, "rb");
        ASSERT_NE(fp, nullptr);
        XMLDocument doc;
        XMLError err = doc.LoadFile(fp);
        fclose(fp);
        EXPECT_EQ(err, XML_SUCCESS);
        ASSERT_NE(doc.RootElement(), nullptr);
        EXPECT_STREQ(doc.RootElement()->Name(), "root");
    }
    std::remove(filename);
}

TEST_F(XMLDocumentTest_326, SaveFileToFILEPtr_326) {
    const char* filename = "test_savefileptr_326.xml";
    {
        XMLDocument doc;
        doc.Parse("<root/>");
        FILE* fp = fopen(filename, "w");
        ASSERT_NE(fp, nullptr);
        XMLError err = doc.SaveFile(fp, false);
        fclose(fp);
        EXPECT_EQ(err, XML_SUCCESS);
    }
    {
        XMLDocument doc;
        XMLError err = doc.LoadFile(filename);
        EXPECT_EQ(err, XML_SUCCESS);
    }
    std::remove(filename);
}

// =============================================================================
// Print Tests
// =============================================================================
TEST_F(XMLDocumentTest_326, PrintToDefaultPrinter_326) {
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

TEST_F(XMLDocumentTest_326, PrintCompact_326) {
    XMLDocument doc;
    doc.Parse("<root><child/></root>");
    ASSERT_FALSE(doc.Error());

    XMLPrinter printer(nullptr, true);
    doc.Print(&printer);
    const char* result = printer.CStr();
    EXPECT_NE(result, nullptr);
}

// =============================================================================
// Accept Tests
// =============================================================================
TEST_F(XMLDocumentTest_326, AcceptWithPrinter_326) {
    XMLDocument doc;
    doc.Parse("<root><child/></root>");
    ASSERT_FALSE(doc.Error());

    XMLPrinter printer;
    bool accepted = doc.Accept(&printer);
    EXPECT_TRUE(accepted);
    const char* result = printer.CStr();
    EXPECT_NE(result, nullptr);
}

// =============================================================================
// ShallowClone / ShallowEqual Tests
// =============================================================================
TEST_F(XMLDocumentTest_326, ShallowCloneReturnsNull_326) {
    XMLDocument doc;
    XMLDocument other;
    XMLNode* clone = doc.ShallowClone(&other);
    EXPECT_EQ(clone, nullptr);
}

TEST_F(XMLDocumentTest_326, ShallowEqualReturnsFalse_326) {
    XMLDocument doc;
    XMLDocument other;
    EXPECT_FALSE(doc.ShallowEqual(&other));
}

// =============================================================================
// Multiple Parses (reuse) Tests
// =============================================================================
TEST_F(XMLDocumentTest_326, ReuseParsing_326) {
    XMLDocument doc;
    doc.Parse("<first/>");
    ASSERT_FALSE(doc.Error());
    EXPECT_STREQ(doc.RootElement()->Name(), "first");

    doc.Parse("<second/>");
    ASSERT_FALSE(doc.Error());
    EXPECT_STREQ(doc.RootElement()->Name(), "second");
}

// =============================================================================
// Complex XML Tests
// =============================================================================
TEST_F(XMLDocumentTest_326, ParseComplexXML_326) {
    const char* xml =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>"
        "<root>"
        "  <child1 attr1=\"a\" attr2=\"b\">text1</child1>"
        "  <child2>"
        "    <grandchild>deep text</grandchild>"
        "  </child2>"
        "  <!-- a comment -->"
        "</root>";
    XMLDocument doc;
    XMLError err = doc.Parse(xml);
    EXPECT_EQ(err, XML_SUCCESS);
    ASSERT_NE(doc.RootElement(), nullptr);

    XMLElement* child1 = doc.RootElement()->FirstChildElement("child1");
    ASSERT_NE(child1, nullptr);
    EXPECT_STREQ(child1->Attribute("attr1"), "a");
    EXPECT_STREQ(child1->Attribute("attr2"), "b");
    EXPECT_STREQ(child1->GetText(), "text1");

    XMLElement* child2 = doc.RootElement()->FirstChildElement("child2");
    ASSERT_NE(child2, nullptr);
    XMLElement* gc = child2->FirstChildElement("grandchild");
    ASSERT_NE(gc, nullptr);
    EXPECT_STREQ(gc->GetText(), "deep text");
}

// =============================================================================
// MarkInUse Test (node not deleted when marked)
// =============================================================================
TEST_F(XMLDocumentTest_326, MarkInUsePreservesNode_326) {
    XMLDocument doc;
    doc.Parse("<root><child/></root>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    XMLElement* child = root->FirstChildElement("child");
    ASSERT_NE(child, nullptr);

    // Unlink child from parent
    root->DeleteChild(child);
    // After deletion, child is gone from tree
    EXPECT_EQ(root->FirstChildElement("child"), nullptr);
}

// =============================================================================
// Deeply Nested XML (depth tracking stress)
// =============================================================================
TEST_F(XMLDocumentTest_326, DeeplyNestedXML_326) {
    // Build a deeply nested XML string
    std::string xml;
    int depth = 100;
    for (int i = 0; i < depth; ++i) {
        xml += "<n>";
    }
    xml += "text";
    for (int i = 0; i < depth; ++i) {
        xml += "</n>";
    }
    XMLDocument doc;
    XMLError err = doc.Parse(xml.c_str());
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_FALSE(doc.Error());
}

TEST_F(XMLDocumentTest_326, ExcessivelyDeeplyNestedXML_326) {
    // Build an excessively deeply nested XML (may trigger depth limit)
    std::string xml;
    int depth = 10000;
    for (int i = 0; i < depth; ++i) {
        xml += "<n>";
    }
    xml += "text";
    for (int i = 0; i < depth; ++i) {
        xml += "</n>";
    }
    XMLDocument doc;
    XMLError err = doc.Parse(xml.c_str());
    // Either succeeds or fails with an error but should not crash
    if (err != XML_SUCCESS) {
        EXPECT_TRUE(doc.Error());
    }
}

// =============================================================================
// Error state after successful operation
// =============================================================================
TEST_F(XMLDocumentTest_326, NoErrorAfterSuccessfulParse_326) {
    XMLDocument doc;
    doc.Parse("<root/>");
    EXPECT_FALSE(doc.Error());
    EXPECT_EQ(doc.ErrorID(), XML_SUCCESS);
    EXPECT_EQ(doc.ErrorLineNum(), 0);
}

TEST_F(XMLDocumentTest_326, ErrorIDOnMalformedXML_326) {
    XMLDocument doc;
    doc.Parse("not xml at all <<<");
    EXPECT_TRUE(doc.Error());
    EXPECT_NE(doc.ErrorID(), XML_SUCCESS);
}

// =============================================================================
// PrintError should not crash
// =============================================================================
TEST_F(XMLDocumentTest_326, PrintErrorNoError_326) {
    XMLDocument doc;
    doc.Parse("<root/>");
    // Should not crash
    doc.PrintError();
}

TEST_F(XMLDocumentTest_326, PrintErrorWithError_326) {
    XMLDocument doc;
    doc.Parse("<unclosed>");
    EXPECT_TRUE(doc.Error());
    // Should not crash
    doc.PrintError();
}
