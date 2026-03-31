#include <gtest/gtest.h>
#include "tinyxml2.h"

using namespace tinyxml2;

// ============================================================
// XMLDocument Constructor Tests
// ============================================================

TEST(XMLDocumentTest_327, DefaultConstruction_327) {
    XMLDocument doc(true, PRESERVE_WHITESPACE);
    EXPECT_FALSE(doc.Error());
    EXPECT_EQ(doc.ErrorID(), XML_SUCCESS);
    EXPECT_TRUE(doc.ProcessEntities());
    EXPECT_EQ(doc.WhitespaceMode(), PRESERVE_WHITESPACE);
    EXPECT_FALSE(doc.HasBOM());
}

TEST(XMLDocumentTest_327, ConstructWithoutProcessEntities_327) {
    XMLDocument doc(false, COLLAPSE_WHITESPACE);
    EXPECT_FALSE(doc.ProcessEntities());
    EXPECT_EQ(doc.WhitespaceMode(), COLLAPSE_WHITESPACE);
    EXPECT_FALSE(doc.HasBOM());
    EXPECT_FALSE(doc.Error());
}

TEST(XMLDocumentTest_327, ConstructWithCollapseWhitespace_327) {
    XMLDocument doc(true, COLLAPSE_WHITESPACE);
    EXPECT_TRUE(doc.ProcessEntities());
    EXPECT_EQ(doc.WhitespaceMode(), COLLAPSE_WHITESPACE);
}

// ============================================================
// BOM Tests
// ============================================================

TEST(XMLDocumentTest_327, SetBOMTrue_327) {
    XMLDocument doc(true, PRESERVE_WHITESPACE);
    doc.SetBOM(true);
    EXPECT_TRUE(doc.HasBOM());
}

TEST(XMLDocumentTest_327, SetBOMFalse_327) {
    XMLDocument doc(true, PRESERVE_WHITESPACE);
    doc.SetBOM(true);
    EXPECT_TRUE(doc.HasBOM());
    doc.SetBOM(false);
    EXPECT_FALSE(doc.HasBOM());
}

// ============================================================
// Parse Tests
// ============================================================

TEST(XMLDocumentTest_327, ParseValidXML_327) {
    XMLDocument doc(true, PRESERVE_WHITESPACE);
    XMLError err = doc.Parse("<root><child/></root>");
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_FALSE(doc.Error());
}

TEST(XMLDocumentTest_327, ParseEmptyString_327) {
    XMLDocument doc(true, PRESERVE_WHITESPACE);
    XMLError err = doc.Parse("");
    EXPECT_NE(err, XML_SUCCESS);
    EXPECT_TRUE(doc.Error());
}

TEST(XMLDocumentTest_327, ParseNullString_327) {
    XMLDocument doc(true, PRESERVE_WHITESPACE);
    XMLError err = doc.Parse(nullptr, 0);
    EXPECT_NE(err, XML_SUCCESS);
    EXPECT_TRUE(doc.Error());
}

TEST(XMLDocumentTest_327, ParseInvalidXML_327) {
    XMLDocument doc(true, PRESERVE_WHITESPACE);
    XMLError err = doc.Parse("<root><unclosed>");
    EXPECT_NE(err, XML_SUCCESS);
    EXPECT_TRUE(doc.Error());
}

TEST(XMLDocumentTest_327, ParseWithNBytes_327) {
    XMLDocument doc(true, PRESERVE_WHITESPACE);
    const char* xml = "<root/>EXTRA_GARBAGE";
    XMLError err = doc.Parse(xml, 7); // only "<root/>"
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_FALSE(doc.Error());
}

TEST(XMLDocumentTest_327, ParseWithEntities_327) {
    XMLDocument doc(true, PRESERVE_WHITESPACE);
    XMLError err = doc.Parse("<root attr=\"&amp;\"/>");
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_FALSE(doc.Error());
}

// ============================================================
// RootElement Tests
// ============================================================

TEST(XMLDocumentTest_327, RootElementAfterParse_327) {
    XMLDocument doc(true, PRESERVE_WHITESPACE);
    doc.Parse("<root><child/></root>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    EXPECT_STREQ(root->Value(), "root");
}

TEST(XMLDocumentTest_327, RootElementEmptyDoc_327) {
    XMLDocument doc(true, PRESERVE_WHITESPACE);
    XMLElement* root = doc.RootElement();
    EXPECT_EQ(root, nullptr);
}

// ============================================================
// NewElement / NewComment / NewText / NewDeclaration / NewUnknown Tests
// ============================================================

TEST(XMLDocumentTest_327, NewElement_327) {
    XMLDocument doc(true, PRESERVE_WHITESPACE);
    XMLElement* elem = doc.NewElement("test");
    ASSERT_NE(elem, nullptr);
    EXPECT_STREQ(elem->Value(), "test");
    doc.InsertEndChild(elem);
    EXPECT_EQ(doc.RootElement(), elem);
}

TEST(XMLDocumentTest_327, NewComment_327) {
    XMLDocument doc(true, PRESERVE_WHITESPACE);
    XMLComment* comment = doc.NewComment("this is a comment");
    ASSERT_NE(comment, nullptr);
    EXPECT_STREQ(comment->Value(), "this is a comment");
    doc.InsertEndChild(comment);
}

TEST(XMLDocumentTest_327, NewText_327) {
    XMLDocument doc(true, PRESERVE_WHITESPACE);
    XMLText* text = doc.NewText("hello");
    ASSERT_NE(text, nullptr);
    EXPECT_STREQ(text->Value(), "hello");
}

TEST(XMLDocumentTest_327, NewDeclaration_327) {
    XMLDocument doc(true, PRESERVE_WHITESPACE);
    XMLDeclaration* decl = doc.NewDeclaration("xml version=\"1.0\"");
    ASSERT_NE(decl, nullptr);
    doc.InsertFirstChild(decl);
}

TEST(XMLDocumentTest_327, NewUnknown_327) {
    XMLDocument doc(true, PRESERVE_WHITESPACE);
    XMLUnknown* unknown = doc.NewUnknown("something unknown");
    ASSERT_NE(unknown, nullptr);
    EXPECT_STREQ(unknown->Value(), "something unknown");
}

// ============================================================
// DeleteNode Tests
// ============================================================

TEST(XMLDocumentTest_327, DeleteNodeRemovesElement_327) {
    XMLDocument doc(true, PRESERVE_WHITESPACE);
    doc.Parse("<root><child1/><child2/></root>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    XMLElement* child1 = root->FirstChildElement("child1");
    ASSERT_NE(child1, nullptr);
    doc.DeleteNode(child1);
    EXPECT_EQ(root->FirstChildElement("child1"), nullptr);
}

// ============================================================
// Clear Tests
// ============================================================

TEST(XMLDocumentTest_327, ClearResetsDocument_327) {
    XMLDocument doc(true, PRESERVE_WHITESPACE);
    doc.Parse("<root><child/></root>");
    EXPECT_FALSE(doc.Error());
    EXPECT_NE(doc.RootElement(), nullptr);
    doc.Clear();
    EXPECT_EQ(doc.RootElement(), nullptr);
    EXPECT_FALSE(doc.Error());
}

// ============================================================
// Error Handling Tests
// ============================================================

TEST(XMLDocumentTest_327, ClearErrorResetsError_327) {
    XMLDocument doc(true, PRESERVE_WHITESPACE);
    doc.Parse("<unclosed>");
    EXPECT_TRUE(doc.Error());
    doc.ClearError();
    EXPECT_FALSE(doc.Error());
    EXPECT_EQ(doc.ErrorID(), XML_SUCCESS);
}

TEST(XMLDocumentTest_327, ErrorNameNonNull_327) {
    XMLDocument doc(true, PRESERVE_WHITESPACE);
    doc.Parse("<unclosed>");
    EXPECT_TRUE(doc.Error());
    const char* name = doc.ErrorName();
    EXPECT_NE(name, nullptr);
}

TEST(XMLDocumentTest_327, ErrorStrNonNull_327) {
    XMLDocument doc(true, PRESERVE_WHITESPACE);
    doc.Parse("<unclosed>");
    EXPECT_TRUE(doc.Error());
    const char* str = doc.ErrorStr();
    EXPECT_NE(str, nullptr);
}

TEST(XMLDocumentTest_327, ErrorIDToNameReturnsString_327) {
    const char* name = XMLDocument::ErrorIDToName(XML_SUCCESS);
    EXPECT_NE(name, nullptr);
    EXPECT_STREQ(name, "XML_SUCCESS");
}

TEST(XMLDocumentTest_327, ErrorLineNumDefault_327) {
    XMLDocument doc(true, PRESERVE_WHITESPACE);
    EXPECT_EQ(doc.ErrorLineNum(), 0);
}

TEST(XMLDocumentTest_327, ErrorLineNumAfterError_327) {
    XMLDocument doc(true, PRESERVE_WHITESPACE);
    doc.Parse("<root>\n<unclosed>");
    EXPECT_TRUE(doc.Error());
    // Error line should be >= 1 since the error occurs after first line
    EXPECT_GT(doc.ErrorLineNum(), 0);
}

// ============================================================
// DeepCopy Tests
// ============================================================

TEST(XMLDocumentTest_327, DeepCopyToAnotherDocument_327) {
    XMLDocument src(true, PRESERVE_WHITESPACE);
    src.Parse("<root><child attr=\"val\">text</child></root>");
    ASSERT_FALSE(src.Error());

    XMLDocument dst(true, PRESERVE_WHITESPACE);
    src.DeepCopy(&dst);

    XMLElement* dstRoot = dst.RootElement();
    ASSERT_NE(dstRoot, nullptr);
    EXPECT_STREQ(dstRoot->Value(), "root");
    XMLElement* dstChild = dstRoot->FirstChildElement("child");
    ASSERT_NE(dstChild, nullptr);
    EXPECT_STREQ(dstChild->Attribute("attr"), "val");
    EXPECT_STREQ(dstChild->GetText(), "text");
}

TEST(XMLDocumentTest_327, DeepCopyEmptyDocument_327) {
    XMLDocument src(true, PRESERVE_WHITESPACE);
    XMLDocument dst(true, PRESERVE_WHITESPACE);
    dst.Parse("<existing/>");
    ASSERT_NE(dst.RootElement(), nullptr);

    src.DeepCopy(&dst);
    EXPECT_EQ(dst.RootElement(), nullptr);
}

// ============================================================
// ToDocument Tests
// ============================================================

TEST(XMLDocumentTest_327, ToDocumentReturnsSelf_327) {
    XMLDocument doc(true, PRESERVE_WHITESPACE);
    EXPECT_EQ(doc.ToDocument(), &doc);
}

// ============================================================
// ShallowClone / ShallowEqual Tests
// ============================================================

TEST(XMLDocumentTest_327, ShallowCloneReturnsNull_327) {
    XMLDocument doc(true, PRESERVE_WHITESPACE);
    const XMLNode* clone = doc.ShallowClone(&doc);
    EXPECT_EQ(clone, nullptr);
}

TEST(XMLDocumentTest_327, ShallowEqualReturnsFalse_327) {
    XMLDocument doc1(true, PRESERVE_WHITESPACE);
    XMLDocument doc2(true, PRESERVE_WHITESPACE);
    EXPECT_FALSE(doc1.ShallowEqual(&doc2));
}

// ============================================================
// InsertEndChild / InsertFirstChild Tests
// ============================================================

TEST(XMLDocumentTest_327, InsertEndChild_327) {
    XMLDocument doc(true, PRESERVE_WHITESPACE);
    XMLElement* e1 = doc.NewElement("first");
    XMLElement* e2 = doc.NewElement("second");
    doc.InsertEndChild(e1);
    doc.InsertEndChild(e2);
    // first child of doc should be e1
    EXPECT_EQ(doc.FirstChild(), e1);
    // last child of doc should be e2
    EXPECT_EQ(doc.LastChild(), e2);
}

TEST(XMLDocumentTest_327, InsertFirstChild_327) {
    XMLDocument doc(true, PRESERVE_WHITESPACE);
    XMLElement* e1 = doc.NewElement("first");
    XMLElement* e2 = doc.NewElement("second");
    doc.InsertEndChild(e1);
    doc.InsertFirstChild(e2);
    EXPECT_EQ(doc.FirstChild(), e2);
}

// ============================================================
// NoChildren Tests
// ============================================================

TEST(XMLDocumentTest_327, NoChildrenOnEmptyDoc_327) {
    XMLDocument doc(true, PRESERVE_WHITESPACE);
    EXPECT_TRUE(doc.NoChildren());
}

TEST(XMLDocumentTest_327, NoChildrenAfterParse_327) {
    XMLDocument doc(true, PRESERVE_WHITESPACE);
    doc.Parse("<root/>");
    EXPECT_FALSE(doc.NoChildren());
}

// ============================================================
// DeleteChildren Tests
// ============================================================

TEST(XMLDocumentTest_327, DeleteChildrenClearsAllChildren_327) {
    XMLDocument doc(true, PRESERVE_WHITESPACE);
    doc.Parse("<root><a/><b/><c/></root>");
    EXPECT_FALSE(doc.NoChildren());
    doc.DeleteChildren();
    EXPECT_TRUE(doc.NoChildren());
}

// ============================================================
// SaveFile Tests
// ============================================================

TEST(XMLDocumentTest_327, SaveFileToInvalidPath_327) {
    XMLDocument doc(true, PRESERVE_WHITESPACE);
    doc.Parse("<root/>");
    XMLError err = doc.SaveFile("/invalid_path/nonexistent_dir/test.xml", false);
    EXPECT_NE(err, XML_SUCCESS);
}

TEST(XMLDocumentTest_327, LoadFileNonExistent_327) {
    XMLDocument doc(true, PRESERVE_WHITESPACE);
    XMLError err = doc.LoadFile("this_file_does_not_exist_12345.xml");
    EXPECT_NE(err, XML_SUCCESS);
    EXPECT_TRUE(doc.Error());
}

// ============================================================
// SaveFile / LoadFile roundtrip with FILE* 
// ============================================================

TEST(XMLDocumentTest_327, SaveAndLoadFilePointer_327) {
    const char* tmpfile = "test_327_temp.xml";
    {
        XMLDocument doc(true, PRESERVE_WHITESPACE);
        doc.Parse("<root><child>text</child></root>");
        ASSERT_FALSE(doc.Error());
        FILE* fp = fopen(tmpfile, "w");
        ASSERT_NE(fp, nullptr);
        XMLError err = doc.SaveFile(fp, false);
        fclose(fp);
        EXPECT_EQ(err, XML_SUCCESS);
    }
    {
        XMLDocument doc(true, PRESERVE_WHITESPACE);
        FILE* fp = fopen(tmpfile, "r");
        ASSERT_NE(fp, nullptr);
        XMLError err = doc.LoadFile(fp);
        fclose(fp);
        EXPECT_EQ(err, XML_SUCCESS);
        EXPECT_FALSE(doc.Error());
        XMLElement* root = doc.RootElement();
        ASSERT_NE(root, nullptr);
        EXPECT_STREQ(root->Value(), "root");
    }
    remove(tmpfile);
}

// ============================================================
// Print Tests
// ============================================================

TEST(XMLDocumentTest_327, PrintToNullPrinter_327) {
    XMLDocument doc(true, PRESERVE_WHITESPACE);
    doc.Parse("<root/>");
    // Passing null streamer should use default printing (stdout)
    // This should not crash
    XMLPrinter printer;
    doc.Print(&printer);
    const char* result = printer.CStr();
    EXPECT_NE(result, nullptr);
    // Should contain "root"
    EXPECT_NE(std::string(result).find("root"), std::string::npos);
}

// ============================================================
// Accept Tests
// ============================================================

TEST(XMLDocumentTest_327, AcceptWithVisitor_327) {
    XMLDocument doc(true, PRESERVE_WHITESPACE);
    doc.Parse("<root/>");
    XMLPrinter printer;
    bool accepted = doc.Accept(&printer);
    EXPECT_TRUE(accepted);
    const char* result = printer.CStr();
    EXPECT_NE(result, nullptr);
}

// ============================================================
// GetDocument Tests
// ============================================================

TEST(XMLDocumentTest_327, GetDocumentReturnsSelf_327) {
    XMLDocument doc(true, PRESERVE_WHITESPACE);
    EXPECT_EQ(doc.GetDocument(), &doc);
}

// ============================================================
// ChildElementCount Tests
// ============================================================

TEST(XMLDocumentTest_327, ChildElementCountEmpty_327) {
    XMLDocument doc(true, PRESERVE_WHITESPACE);
    EXPECT_EQ(doc.ChildElementCount(), 0);
}

TEST(XMLDocumentTest_327, ChildElementCountAfterParse_327) {
    XMLDocument doc(true, PRESERVE_WHITESPACE);
    doc.Parse("<root/>");
    EXPECT_EQ(doc.ChildElementCount(), 1);
}

TEST(XMLDocumentTest_327, ChildElementCountWithName_327) {
    XMLDocument doc(true, PRESERVE_WHITESPACE);
    doc.Parse("<root><a/><b/><a/></root>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    EXPECT_EQ(root->ChildElementCount("a"), 2);
    EXPECT_EQ(root->ChildElementCount("b"), 1);
    EXPECT_EQ(root->ChildElementCount("c"), 0);
}

// ============================================================
// UserData Tests
// ============================================================

TEST(XMLDocumentTest_327, UserDataDefaultNull_327) {
    XMLDocument doc(true, PRESERVE_WHITESPACE);
    EXPECT_EQ(doc.GetUserData(), nullptr);
}

TEST(XMLDocumentTest_327, SetAndGetUserData_327) {
    XMLDocument doc(true, PRESERVE_WHITESPACE);
    int data = 42;
    doc.SetUserData(&data);
    EXPECT_EQ(doc.GetUserData(), &data);
}

// ============================================================
// Complex Parse Tests
// ============================================================

TEST(XMLDocumentTest_327, ParseMultipleElements_327) {
    XMLDocument doc(true, PRESERVE_WHITESPACE);
    const char* xml = "<root>"
                      "  <item id=\"1\">First</item>"
                      "  <item id=\"2\">Second</item>"
                      "  <item id=\"3\">Third</item>"
                      "</root>";
    XMLError err = doc.Parse(xml);
    EXPECT_EQ(err, XML_SUCCESS);
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    EXPECT_EQ(root->ChildElementCount("item"), 3);
}

TEST(XMLDocumentTest_327, ParseDeclaration_327) {
    XMLDocument doc(true, PRESERVE_WHITESPACE);
    const char* xml = "<?xml version=\"1.0\" encoding=\"UTF-8\"?><root/>";
    XMLError err = doc.Parse(xml);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_FALSE(doc.Error());
    EXPECT_NE(doc.RootElement(), nullptr);
}

TEST(XMLDocumentTest_327, ParseComment_327) {
    XMLDocument doc(true, PRESERVE_WHITESPACE);
    const char* xml = "<!-- comment --><root/>";
    XMLError err = doc.Parse(xml);
    EXPECT_EQ(err, XML_SUCCESS);
}

// ============================================================
// Re-parse Tests
// ============================================================

TEST(XMLDocumentTest_327, ReparseOverwritesPrevious_327) {
    XMLDocument doc(true, PRESERVE_WHITESPACE);
    doc.Parse("<first/>");
    ASSERT_NE(doc.RootElement(), nullptr);
    EXPECT_STREQ(doc.RootElement()->Value(), "first");

    doc.Parse("<second/>");
    ASSERT_NE(doc.RootElement(), nullptr);
    EXPECT_STREQ(doc.RootElement()->Value(), "second");
}

// ============================================================
// InsertAfterChild Tests
// ============================================================

TEST(XMLDocumentTest_327, InsertAfterChild_327) {
    XMLDocument doc(true, PRESERVE_WHITESPACE);
    doc.Parse("<root><a/><c/></root>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    XMLElement* a = root->FirstChildElement("a");
    ASSERT_NE(a, nullptr);
    XMLElement* b = doc.NewElement("b");
    root->InsertAfterChild(a, b);
    
    // Order should be a, b, c
    XMLElement* first = root->FirstChildElement();
    ASSERT_NE(first, nullptr);
    EXPECT_STREQ(first->Value(), "a");
    XMLElement* second = first->NextSiblingElement();
    ASSERT_NE(second, nullptr);
    EXPECT_STREQ(second->Value(), "b");
    XMLElement* third = second->NextSiblingElement();
    ASSERT_NE(third, nullptr);
    EXPECT_STREQ(third->Value(), "c");
}

// ============================================================
// DeepClone on XMLNode Tests
// ============================================================

TEST(XMLDocumentTest_327, DeepCloneElement_327) {
    XMLDocument doc(true, PRESERVE_WHITESPACE);
    doc.Parse("<root><child attr=\"val\"><sub>text</sub></child></root>");
    XMLElement* child = doc.RootElement()->FirstChildElement("child");
    ASSERT_NE(child, nullptr);

    XMLDocument doc2(true, PRESERVE_WHITESPACE);
    XMLNode* cloned = child->DeepClone(&doc2);
    ASSERT_NE(cloned, nullptr);
    doc2.InsertEndChild(cloned);

    XMLElement* clonedElem = doc2.RootElement();
    ASSERT_NE(clonedElem, nullptr);
    EXPECT_STREQ(clonedElem->Value(), "child");
    EXPECT_STREQ(clonedElem->Attribute("attr"), "val");
    XMLElement* sub = clonedElem->FirstChildElement("sub");
    ASSERT_NE(sub, nullptr);
    EXPECT_STREQ(sub->GetText(), "text");
}

// ============================================================
// ErrorIDToName for various error codes
// ============================================================

TEST(XMLDocumentTest_327, ErrorIDToNameVariousCodes_327) {
    EXPECT_STREQ(XMLDocument::ErrorIDToName(XML_SUCCESS), "XML_SUCCESS");
    EXPECT_STREQ(XMLDocument::ErrorIDToName(XML_ERROR_FILE_NOT_FOUND), "XML_ERROR_FILE_NOT_FOUND");
    EXPECT_STREQ(XMLDocument::ErrorIDToName(XML_ERROR_EMPTY_DOCUMENT), "XML_ERROR_EMPTY_DOCUMENT");
}

// ============================================================
// Value Tests on Document
// ============================================================

TEST(XMLDocumentTest_327, DocumentValueIsEmpty_327) {
    XMLDocument doc(true, PRESERVE_WHITESPACE);
    // The document node typically has no value or empty value
    const char* val = doc.Value();
    // Just verify it doesn't crash; value may be empty or null-like
    (void)val;
}

// ============================================================
// Parent of Document is null
// ============================================================

TEST(XMLDocumentTest_327, ParentOfDocumentIsNull_327) {
    XMLDocument doc(true, PRESERVE_WHITESPACE);
    EXPECT_EQ(doc.Parent(), nullptr);
}

// ============================================================
// Sibling navigation on Document
// ============================================================

TEST(XMLDocumentTest_327, DocumentHasNoSiblings_327) {
    XMLDocument doc(true, PRESERVE_WHITESPACE);
    EXPECT_EQ(doc.PreviousSibling(), nullptr);
    EXPECT_EQ(doc.NextSibling(), nullptr);
    EXPECT_EQ(doc.PreviousSiblingElement(), nullptr);
    EXPECT_EQ(doc.NextSiblingElement(), nullptr);
}
