#include "gtest/gtest.h"
#include "tinyxml2.h"

using namespace tinyxml2;

// ===== Construction and Default State Tests =====

TEST(XMLDocumentTest_111, DefaultConstruction_111) {
    XMLDocument doc;
    EXPECT_FALSE(doc.HasBOM());
    EXPECT_FALSE(doc.Error());
    EXPECT_EQ(doc.ErrorID(), XML_SUCCESS);
    EXPECT_EQ(doc.ErrorLineNum(), 0);
    EXPECT_TRUE(doc.ProcessEntities());
    EXPECT_EQ(doc.WhitespaceMode(), PRESERVE_WHITESPACE);
}

TEST(XMLDocumentTest_111, ConstructionWithProcessEntitiesFalse_111) {
    XMLDocument doc(false);
    EXPECT_FALSE(doc.ProcessEntities());
}

TEST(XMLDocumentTest_111, ConstructionWithProcessEntitiesTrue_111) {
    XMLDocument doc(true);
    EXPECT_TRUE(doc.ProcessEntities());
}

TEST(XMLDocumentTest_111, ConstructionWithCollapseWhitespace_111) {
    XMLDocument doc(true, COLLAPSE_WHITESPACE);
    EXPECT_EQ(doc.WhitespaceMode(), COLLAPSE_WHITESPACE);
}

// ===== SetBOM / HasBOM Tests =====

TEST(XMLDocumentTest_111, SetBOMTrue_111) {
    XMLDocument doc;
    doc.SetBOM(true);
    EXPECT_TRUE(doc.HasBOM());
}

TEST(XMLDocumentTest_111, SetBOMFalse_111) {
    XMLDocument doc;
    doc.SetBOM(true);
    EXPECT_TRUE(doc.HasBOM());
    doc.SetBOM(false);
    EXPECT_FALSE(doc.HasBOM());
}

TEST(XMLDocumentTest_111, SetBOMToggle_111) {
    XMLDocument doc;
    EXPECT_FALSE(doc.HasBOM());
    doc.SetBOM(true);
    EXPECT_TRUE(doc.HasBOM());
    doc.SetBOM(false);
    EXPECT_FALSE(doc.HasBOM());
    doc.SetBOM(true);
    EXPECT_TRUE(doc.HasBOM());
}

// ===== Parse Tests =====

TEST(XMLDocumentTest_111, ParseValidXML_111) {
    XMLDocument doc;
    XMLError err = doc.Parse("<root><child/></root>");
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_FALSE(doc.Error());
}

TEST(XMLDocumentTest_111, ParseEmptyString_111) {
    XMLDocument doc;
    XMLError err = doc.Parse("");
    EXPECT_NE(err, XML_SUCCESS);
    EXPECT_TRUE(doc.Error());
}

TEST(XMLDocumentTest_111, ParseNullPointer_111) {
    XMLDocument doc;
    XMLError err = doc.Parse(nullptr, 0);
    EXPECT_NE(err, XML_SUCCESS);
    EXPECT_TRUE(doc.Error());
}

TEST(XMLDocumentTest_111, ParseMalformedXML_111) {
    XMLDocument doc;
    XMLError err = doc.Parse("<root><unclosed>");
    EXPECT_NE(err, XML_SUCCESS);
    EXPECT_TRUE(doc.Error());
}

TEST(XMLDocumentTest_111, ParseWithNBytes_111) {
    XMLDocument doc;
    const char* xml = "<root/>GARBAGE";
    XMLError err = doc.Parse(xml, 7);  // Only parse "<root/>"
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_FALSE(doc.Error());
}

TEST(XMLDocumentTest_111, ParseWithDeclaration_111) {
    XMLDocument doc;
    XMLError err = doc.Parse("<?xml version=\"1.0\"?><root/>");
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_FALSE(doc.Error());
}

// ===== RootElement Tests =====

TEST(XMLDocumentTest_111, RootElementAfterParse_111) {
    XMLDocument doc;
    doc.Parse("<root><child/></root>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    EXPECT_STREQ(root->Name(), "root");
}

TEST(XMLDocumentTest_111, RootElementOnEmptyDoc_111) {
    XMLDocument doc;
    EXPECT_EQ(doc.RootElement(), nullptr);
}

// ===== Error Handling Tests =====

TEST(XMLDocumentTest_111, ErrorIDAfterParseFail_111) {
    XMLDocument doc;
    doc.Parse("<unclosed>");
    EXPECT_NE(doc.ErrorID(), XML_SUCCESS);
    EXPECT_TRUE(doc.Error());
}

TEST(XMLDocumentTest_111, ErrorNameNotNull_111) {
    XMLDocument doc;
    doc.Parse("<unclosed>");
    const char* name = doc.ErrorName();
    EXPECT_NE(name, nullptr);
}

TEST(XMLDocumentTest_111, ErrorStrNotNull_111) {
    XMLDocument doc;
    doc.Parse("<unclosed>");
    const char* errStr = doc.ErrorStr();
    EXPECT_NE(errStr, nullptr);
}

TEST(XMLDocumentTest_111, ErrorLineNumOnError_111) {
    XMLDocument doc;
    doc.Parse("<root>\n<unclosed>");
    EXPECT_TRUE(doc.Error());
    // ErrorLineNum should be > 0 if error was on a later line
    EXPECT_GT(doc.ErrorLineNum(), 0);
}

TEST(XMLDocumentTest_111, ClearError_111) {
    XMLDocument doc;
    doc.Parse("<unclosed>");
    EXPECT_TRUE(doc.Error());
    doc.ClearError();
    EXPECT_FALSE(doc.Error());
    EXPECT_EQ(doc.ErrorID(), XML_SUCCESS);
}

TEST(XMLDocumentTest_111, ErrorIDToNameForSuccess_111) {
    const char* name = XMLDocument::ErrorIDToName(XML_SUCCESS);
    EXPECT_NE(name, nullptr);
    EXPECT_STREQ(name, "XML_SUCCESS");
}

TEST(XMLDocumentTest_111, ErrorIDToNameForError_111) {
    const char* name = XMLDocument::ErrorIDToName(XML_ERROR_EMPTY_DOCUMENT);
    EXPECT_NE(name, nullptr);
}

// ===== NewElement Tests =====

TEST(XMLDocumentTest_111, NewElementCreatesElement_111) {
    XMLDocument doc;
    XMLElement* elem = doc.NewElement("test");
    ASSERT_NE(elem, nullptr);
    EXPECT_STREQ(elem->Name(), "test");
    doc.DeleteNode(elem);
}

// ===== NewComment Tests =====

TEST(XMLDocumentTest_111, NewCommentCreatesComment_111) {
    XMLDocument doc;
    XMLComment* comment = doc.NewComment("this is a comment");
    ASSERT_NE(comment, nullptr);
    EXPECT_STREQ(comment->Value(), "this is a comment");
    doc.DeleteNode(comment);
}

// ===== NewText Tests =====

TEST(XMLDocumentTest_111, NewTextCreatesText_111) {
    XMLDocument doc;
    XMLText* text = doc.NewText("hello world");
    ASSERT_NE(text, nullptr);
    EXPECT_STREQ(text->Value(), "hello world");
    doc.DeleteNode(text);
}

// ===== NewDeclaration Tests =====

TEST(XMLDocumentTest_111, NewDeclarationDefault_111) {
    XMLDocument doc;
    XMLDeclaration* decl = doc.NewDeclaration();
    ASSERT_NE(decl, nullptr);
    doc.DeleteNode(decl);
}

TEST(XMLDocumentTest_111, NewDeclarationCustom_111) {
    XMLDocument doc;
    XMLDeclaration* decl = doc.NewDeclaration("xml version=\"1.0\" encoding=\"UTF-8\"");
    ASSERT_NE(decl, nullptr);
    doc.DeleteNode(decl);
}

// ===== NewUnknown Tests =====

TEST(XMLDocumentTest_111, NewUnknownCreatesUnknown_111) {
    XMLDocument doc;
    XMLUnknown* unknown = doc.NewUnknown("something");
    ASSERT_NE(unknown, nullptr);
    EXPECT_STREQ(unknown->Value(), "something");
    doc.DeleteNode(unknown);
}

// ===== DeleteNode Tests =====

TEST(XMLDocumentTest_111, DeleteNodeRemovesFromTree_111) {
    XMLDocument doc;
    doc.Parse("<root><child/></root>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    XMLElement* child = root->FirstChildElement("child");
    ASSERT_NE(child, nullptr);
    doc.DeleteNode(child);
    EXPECT_EQ(root->FirstChildElement("child"), nullptr);
}

// ===== Clear Tests =====

TEST(XMLDocumentTest_111, ClearResetsDocument_111) {
    XMLDocument doc;
    doc.Parse("<root><child/></root>");
    EXPECT_NE(doc.RootElement(), nullptr);
    doc.Clear();
    EXPECT_EQ(doc.RootElement(), nullptr);
    EXPECT_FALSE(doc.Error());
}

// ===== DeepCopy Tests =====

TEST(XMLDocumentTest_111, DeepCopyCreatesIdenticalDocument_111) {
    XMLDocument doc;
    doc.Parse("<root><child attr=\"value\">text</child></root>");
    ASSERT_FALSE(doc.Error());

    XMLDocument target;
    doc.DeepCopy(&target);

    ASSERT_NE(target.RootElement(), nullptr);
    EXPECT_STREQ(target.RootElement()->Name(), "root");
    XMLElement* child = target.RootElement()->FirstChildElement("child");
    ASSERT_NE(child, nullptr);
    EXPECT_STREQ(child->Attribute("attr"), "value");
    EXPECT_STREQ(child->GetText(), "text");
}

TEST(XMLDocumentTest_111, DeepCopyPreservesBOM_111) {
    XMLDocument doc;
    doc.Parse("<root/>");
    doc.SetBOM(true);

    XMLDocument target;
    doc.DeepCopy(&target);
    EXPECT_TRUE(target.HasBOM());
}

// ===== ToDocument Tests =====

TEST(XMLDocumentTest_111, ToDocumentReturnsSelf_111) {
    XMLDocument doc;
    EXPECT_EQ(doc.ToDocument(), &doc);
}

// ===== ShallowClone Tests =====

TEST(XMLDocumentTest_111, ShallowCloneReturnsNull_111) {
    XMLDocument doc;
    XMLDocument other;
    // XMLDocument::ShallowClone should return nullptr
    EXPECT_EQ(doc.ShallowClone(&other), nullptr);
}

// ===== ShallowEqual Tests =====

TEST(XMLDocumentTest_111, ShallowEqualReturnsFalse_111) {
    XMLDocument doc1;
    XMLDocument doc2;
    // XMLDocument::ShallowEqual should return false
    EXPECT_FALSE(doc1.ShallowEqual(&doc2));
}

// ===== SaveFile / LoadFile Tests =====

TEST(XMLDocumentTest_111, SaveAndLoadFile_111) {
    const char* filename = "test_save_load_111.xml";
    
    // Save
    {
        XMLDocument doc;
        doc.Parse("<root><child/></root>");
        ASSERT_FALSE(doc.Error());
        XMLError err = doc.SaveFile(filename, false);
        EXPECT_EQ(err, XML_SUCCESS);
    }

    // Load
    {
        XMLDocument doc;
        XMLError err = doc.LoadFile(filename);
        EXPECT_EQ(err, XML_SUCCESS);
        EXPECT_FALSE(doc.Error());
        ASSERT_NE(doc.RootElement(), nullptr);
        EXPECT_STREQ(doc.RootElement()->Name(), "root");
    }

    // Cleanup
    std::remove(filename);
}

TEST(XMLDocumentTest_111, SaveFileCompact_111) {
    const char* filename = "test_compact_111.xml";
    
    XMLDocument doc;
    doc.Parse("<root>  <child/>  </root>");
    ASSERT_FALSE(doc.Error());
    XMLError err = doc.SaveFile(filename, true);
    EXPECT_EQ(err, XML_SUCCESS);

    std::remove(filename);
}

TEST(XMLDocumentTest_111, LoadFileNonExistent_111) {
    XMLDocument doc;
    XMLError err = doc.LoadFile("nonexistent_file_111.xml");
    EXPECT_NE(err, XML_SUCCESS);
    EXPECT_TRUE(doc.Error());
}

TEST(XMLDocumentTest_111, SaveAndLoadFileFP_111) {
    const char* filename = "test_fp_111.xml";

    // Save via FILE*
    {
        XMLDocument doc;
        doc.Parse("<root><item/></root>");
        ASSERT_FALSE(doc.Error());
        FILE* fp = fopen(filename, "w");
        ASSERT_NE(fp, nullptr);
        XMLError err = doc.SaveFile(fp, false);
        EXPECT_EQ(err, XML_SUCCESS);
        fclose(fp);
    }

    // Load via FILE*
    {
        XMLDocument doc;
        FILE* fp = fopen(filename, "rb");
        ASSERT_NE(fp, nullptr);
        XMLError err = doc.LoadFile(fp);
        EXPECT_EQ(err, XML_SUCCESS);
        EXPECT_FALSE(doc.Error());
        ASSERT_NE(doc.RootElement(), nullptr);
        EXPECT_STREQ(doc.RootElement()->Name(), "root");
        fclose(fp);
    }

    std::remove(filename);
}

// ===== Print Tests =====

TEST(XMLDocumentTest_111, PrintToDefaultPrinter_111) {
    XMLDocument doc;
    doc.Parse("<root><child/></root>");
    ASSERT_FALSE(doc.Error());

    XMLPrinter printer;
    doc.Print(&printer);
    const char* result = printer.CStr();
    EXPECT_NE(result, nullptr);
    EXPECT_NE(std::string(result).find("root"), std::string::npos);
}

TEST(XMLDocumentTest_111, PrintWithNullPrinter_111) {
    XMLDocument doc;
    doc.Parse("<root/>");
    ASSERT_FALSE(doc.Error());
    // Print with nullptr should still work (prints to stdout typically)
    doc.Print(nullptr);
}

// ===== Accept Tests =====

TEST(XMLDocumentTest_111, AcceptVisitor_111) {
    XMLDocument doc;
    doc.Parse("<root><child/></root>");
    ASSERT_FALSE(doc.Error());

    XMLPrinter printer;
    bool result = doc.Accept(&printer);
    EXPECT_TRUE(result);
    const char* output = printer.CStr();
    EXPECT_NE(output, nullptr);
}

// ===== Complex Parsing Tests =====

TEST(XMLDocumentTest_111, ParseWithAttributes_111) {
    XMLDocument doc;
    XMLError err = doc.Parse("<root attr1=\"val1\" attr2=\"val2\"/>");
    EXPECT_EQ(err, XML_SUCCESS);
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    EXPECT_STREQ(root->Attribute("attr1"), "val1");
    EXPECT_STREQ(root->Attribute("attr2"), "val2");
}

TEST(XMLDocumentTest_111, ParseWithEntities_111) {
    XMLDocument doc(true);
    XMLError err = doc.Parse("<root>&amp;&lt;&gt;</root>");
    EXPECT_EQ(err, XML_SUCCESS);
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    EXPECT_STREQ(root->GetText(), "&<>");
}

TEST(XMLDocumentTest_111, ParseWithoutEntityProcessing_111) {
    XMLDocument doc(false);
    XMLError err = doc.Parse("<root>&amp;</root>");
    EXPECT_EQ(err, XML_SUCCESS);
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    EXPECT_STREQ(root->GetText(), "&amp;");
}

TEST(XMLDocumentTest_111, ParseMultipleRootElements_111) {
    XMLDocument doc;
    // Only one root element is allowed; behavior may vary
    // but parse should handle it gracefully
    XMLError err = doc.Parse("<root1/><root2/>");
    // The document should have at least parsed the first root
    // This may or may not be an error depending on implementation
    // Just verify the first root is available
    if (err == XML_SUCCESS) {
        EXPECT_NE(doc.RootElement(), nullptr);
    }
}

TEST(XMLDocumentTest_111, ParseNestedElements_111) {
    XMLDocument doc;
    XMLError err = doc.Parse("<a><b><c><d/></c></b></a>");
    EXPECT_EQ(err, XML_SUCCESS);
    XMLElement* a = doc.RootElement();
    ASSERT_NE(a, nullptr);
    EXPECT_STREQ(a->Name(), "a");
    XMLElement* b = a->FirstChildElement("b");
    ASSERT_NE(b, nullptr);
    XMLElement* c = b->FirstChildElement("c");
    ASSERT_NE(c, nullptr);
    XMLElement* d = c->FirstChildElement("d");
    ASSERT_NE(d, nullptr);
}

// ===== Reparse Tests =====

TEST(XMLDocumentTest_111, ReparseOverwritesPreviousContent_111) {
    XMLDocument doc;
    doc.Parse("<first/>");
    ASSERT_NE(doc.RootElement(), nullptr);
    EXPECT_STREQ(doc.RootElement()->Name(), "first");

    doc.Parse("<second/>");
    ASSERT_NE(doc.RootElement(), nullptr);
    EXPECT_STREQ(doc.RootElement()->Name(), "second");
}

// ===== InsertNewElement and DeleteNode Tests =====

TEST(XMLDocumentTest_111, InsertNewElementIntoDocument_111) {
    XMLDocument doc;
    XMLElement* root = doc.NewElement("root");
    doc.InsertFirstChild(root);
    ASSERT_NE(doc.RootElement(), nullptr);
    EXPECT_STREQ(doc.RootElement()->Name(), "root");

    XMLElement* child = doc.NewElement("child");
    root->InsertEndChild(child);
    EXPECT_NE(root->FirstChildElement("child"), nullptr);
}

TEST(XMLDocumentTest_111, DeleteNodeNull_111) {
    XMLDocument doc;
    // Deleting null should not crash
    doc.DeleteNode(nullptr);
}

// ===== BOM in Parse/Print Tests =====

TEST(XMLDocumentTest_111, BOMDetectedInParse_111) {
    // UTF-8 BOM: EF BB BF
    const char bom_xml[] = "\xEF\xBB\xBF<?xml version=\"1.0\"?><root/>";
    XMLDocument doc;
    XMLError err = doc.Parse(bom_xml);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_TRUE(doc.HasBOM());
}

TEST(XMLDocumentTest_111, NoBOMInNormalParse_111) {
    XMLDocument doc;
    doc.Parse("<root/>");
    EXPECT_FALSE(doc.HasBOM());
}
