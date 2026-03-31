#include "gtest/gtest.h"
#include "tinyxml2.h"

using namespace tinyxml2;

// Test fixture
class XMLDocumentTest_112 : public ::testing::Test {
protected:
    XMLDocument doc;
};

// ==================== RootElement Tests ====================

TEST_F(XMLDocumentTest_112, RootElementReturnsNullForEmptyDocument_112) {
    EXPECT_EQ(nullptr, doc.RootElement());
}

TEST_F(XMLDocumentTest_112, RootElementReturnsFirstChildElement_112) {
    doc.Parse("<root/>");
    ASSERT_NE(nullptr, doc.RootElement());
    EXPECT_STREQ("root", doc.RootElement()->Value());
}

TEST_F(XMLDocumentTest_112, RootElementAfterParsingComplexXML_112) {
    doc.Parse("<root><child1/><child2/></root>");
    ASSERT_NE(nullptr, doc.RootElement());
    EXPECT_STREQ("root", doc.RootElement()->Value());
}

// ==================== Parse Tests ====================

TEST_F(XMLDocumentTest_112, ParseValidXML_112) {
    XMLError err = doc.Parse("<root><child/></root>");
    EXPECT_EQ(XML_SUCCESS, err);
    EXPECT_FALSE(doc.Error());
}

TEST_F(XMLDocumentTest_112, ParseInvalidXML_112) {
    XMLError err = doc.Parse("<root><child></root>");
    EXPECT_NE(XML_SUCCESS, err);
    EXPECT_TRUE(doc.Error());
}

TEST_F(XMLDocumentTest_112, ParseEmptyString_112) {
    XMLError err = doc.Parse("");
    EXPECT_NE(XML_SUCCESS, err);
    EXPECT_TRUE(doc.Error());
}

TEST_F(XMLDocumentTest_112, ParseNullPtr_112) {
    XMLError err = doc.Parse(nullptr, 0);
    EXPECT_NE(XML_SUCCESS, err);
    EXPECT_TRUE(doc.Error());
}

TEST_F(XMLDocumentTest_112, ParseWithExplicitLength_112) {
    const char* xml = "<root/>GARBAGE";
    XMLError err = doc.Parse(xml, 7);  // only "<root/>"
    EXPECT_EQ(XML_SUCCESS, err);
    ASSERT_NE(nullptr, doc.RootElement());
    EXPECT_STREQ("root", doc.RootElement()->Value());
}

TEST_F(XMLDocumentTest_112, ParseReplacesExistingContent_112) {
    doc.Parse("<first/>");
    ASSERT_NE(nullptr, doc.RootElement());
    EXPECT_STREQ("first", doc.RootElement()->Value());

    doc.Parse("<second/>");
    ASSERT_NE(nullptr, doc.RootElement());
    EXPECT_STREQ("second", doc.RootElement()->Value());
}

// ==================== Error Handling Tests ====================

TEST_F(XMLDocumentTest_112, ErrorIDInitiallySuccess_112) {
    EXPECT_EQ(XML_SUCCESS, doc.ErrorID());
    EXPECT_FALSE(doc.Error());
}

TEST_F(XMLDocumentTest_112, ErrorAfterBadParse_112) {
    doc.Parse("<unclosed");
    EXPECT_TRUE(doc.Error());
    EXPECT_NE(XML_SUCCESS, doc.ErrorID());
}

TEST_F(XMLDocumentTest_112, ClearErrorResetsErrorState_112) {
    doc.Parse("<unclosed");
    EXPECT_TRUE(doc.Error());
    doc.ClearError();
    EXPECT_FALSE(doc.Error());
    EXPECT_EQ(XML_SUCCESS, doc.ErrorID());
}

TEST_F(XMLDocumentTest_112, ErrorNameReturnsNonNull_112) {
    doc.Parse("<unclosed");
    const char* name = doc.ErrorName();
    EXPECT_NE(nullptr, name);
}

TEST_F(XMLDocumentTest_112, ErrorStrReturnsNonNullOnError_112) {
    doc.Parse("<unclosed");
    const char* str = doc.ErrorStr();
    EXPECT_NE(nullptr, str);
}

TEST_F(XMLDocumentTest_112, ErrorLineNumOnError_112) {
    doc.Parse("<root>\n<unclosed");
    EXPECT_TRUE(doc.Error());
    EXPECT_GT(doc.ErrorLineNum(), 0);
}

TEST_F(XMLDocumentTest_112, ErrorIDToNameReturnsNonNull_112) {
    const char* name = XMLDocument::ErrorIDToName(XML_SUCCESS);
    EXPECT_NE(nullptr, name);
}

TEST_F(XMLDocumentTest_112, ErrorIDToNameForError_112) {
    const char* name = XMLDocument::ErrorIDToName(XML_ERROR_FILE_NOT_FOUND);
    EXPECT_NE(nullptr, name);
}

// ==================== NewElement Tests ====================

TEST_F(XMLDocumentTest_112, NewElementCreatesElement_112) {
    XMLElement* elem = doc.NewElement("test");
    ASSERT_NE(nullptr, elem);
    EXPECT_STREQ("test", elem->Value());
    doc.DeleteNode(elem);
}

TEST_F(XMLDocumentTest_112, NewElementCanBeInserted_112) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertFirstChild(root);
    ASSERT_NE(nullptr, doc.RootElement());
    EXPECT_STREQ("root", doc.RootElement()->Value());
}

// ==================== NewComment Tests ====================

TEST_F(XMLDocumentTest_112, NewCommentCreatesComment_112) {
    XMLComment* comment = doc.NewComment("This is a comment");
    ASSERT_NE(nullptr, comment);
    EXPECT_STREQ("This is a comment", comment->Value());
    doc.DeleteNode(comment);
}

// ==================== NewText Tests ====================

TEST_F(XMLDocumentTest_112, NewTextCreatesText_112) {
    XMLText* text = doc.NewText("Hello World");
    ASSERT_NE(nullptr, text);
    EXPECT_STREQ("Hello World", text->Value());
    doc.DeleteNode(text);
}

// ==================== NewDeclaration Tests ====================

TEST_F(XMLDocumentTest_112, NewDeclarationCreatesDeclaration_112) {
    XMLDeclaration* decl = doc.NewDeclaration();
    ASSERT_NE(nullptr, decl);
    doc.DeleteNode(decl);
}

TEST_F(XMLDocumentTest_112, NewDeclarationWithCustomContent_112) {
    XMLDeclaration* decl = doc.NewDeclaration("xml version=\"1.0\"");
    ASSERT_NE(nullptr, decl);
    doc.DeleteNode(decl);
}

// ==================== NewUnknown Tests ====================

TEST_F(XMLDocumentTest_112, NewUnknownCreatesUnknown_112) {
    XMLUnknown* unknown = doc.NewUnknown("something");
    ASSERT_NE(nullptr, unknown);
    EXPECT_STREQ("something", unknown->Value());
    doc.DeleteNode(unknown);
}

// ==================== DeleteNode Tests ====================

TEST_F(XMLDocumentTest_112, DeleteNodeRemovesChild_112) {
    doc.Parse("<root><child/></root>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(nullptr, root);
    XMLElement* child = root->FirstChildElement("child");
    ASSERT_NE(nullptr, child);
    doc.DeleteNode(child);
    EXPECT_EQ(nullptr, root->FirstChildElement("child"));
}

// ==================== Clear Tests ====================

TEST_F(XMLDocumentTest_112, ClearRemovesAllContent_112) {
    doc.Parse("<root><child/></root>");
    ASSERT_NE(nullptr, doc.RootElement());
    doc.Clear();
    EXPECT_EQ(nullptr, doc.RootElement());
    EXPECT_FALSE(doc.Error());
}

// ==================== DeepCopy Tests ====================

TEST_F(XMLDocumentTest_112, DeepCopyCopiesEntireDocument_112) {
    doc.Parse("<root><child attr=\"val\">text</child></root>");
    ASSERT_FALSE(doc.Error());

    XMLDocument target;
    doc.DeepCopy(&target);

    ASSERT_NE(nullptr, target.RootElement());
    EXPECT_STREQ("root", target.RootElement()->Value());
    XMLElement* child = target.RootElement()->FirstChildElement("child");
    ASSERT_NE(nullptr, child);
    EXPECT_STREQ("val", child->Attribute("attr"));
}

TEST_F(XMLDocumentTest_112, DeepCopyToEmptyDocFromEmpty_112) {
    XMLDocument target;
    doc.DeepCopy(&target);
    EXPECT_EQ(nullptr, target.RootElement());
}

// ==================== BOM Tests ====================

TEST_F(XMLDocumentTest_112, DefaultHasBOMIsFalse_112) {
    EXPECT_FALSE(doc.HasBOM());
}

TEST_F(XMLDocumentTest_112, SetBOMTrue_112) {
    doc.SetBOM(true);
    EXPECT_TRUE(doc.HasBOM());
}

TEST_F(XMLDocumentTest_112, SetBOMFalse_112) {
    doc.SetBOM(true);
    doc.SetBOM(false);
    EXPECT_FALSE(doc.HasBOM());
}

// ==================== ProcessEntities Tests ====================

TEST_F(XMLDocumentTest_112, ProcessEntitiesDefaultTrue_112) {
    EXPECT_TRUE(doc.ProcessEntities());
}

TEST_F(XMLDocumentTest_112, ProcessEntitiesFalseWhenConstructedSo_112) {
    XMLDocument docNoEntities(false);
    EXPECT_FALSE(docNoEntities.ProcessEntities());
}

// ==================== WhitespaceMode Tests ====================

TEST_F(XMLDocumentTest_112, WhitespaceModeDefaultPreserve_112) {
    // Default is PRESERVE_WHITESPACE or COLLAPSE_WHITESPACE depending on impl
    // Just test it returns a valid value
    Whitespace mode = doc.WhitespaceMode();
    EXPECT_TRUE(mode == PRESERVE_WHITESPACE || mode == COLLAPSE_WHITESPACE);
}

TEST_F(XMLDocumentTest_112, WhitespaceModeCollapse_112) {
    XMLDocument collapseDoc(true, COLLAPSE_WHITESPACE);
    EXPECT_EQ(COLLAPSE_WHITESPACE, collapseDoc.WhitespaceMode());
}

// ==================== ToDocument Tests ====================

TEST_F(XMLDocumentTest_112, ToDocumentReturnsThis_112) {
    EXPECT_EQ(&doc, doc.ToDocument());
}

// ==================== ShallowClone Tests ====================

TEST_F(XMLDocumentTest_112, ShallowCloneReturnsNull_112) {
    // XMLDocument::ShallowClone always returns null
    XMLDocument other;
    EXPECT_EQ(nullptr, doc.ShallowClone(&other));
}

// ==================== ShallowEqual Tests ====================

TEST_F(XMLDocumentTest_112, ShallowEqualReturnsFalse_112) {
    // XMLDocument::ShallowEqual always returns false
    XMLDocument other;
    EXPECT_FALSE(doc.ShallowEqual(&other));
}

// ==================== LoadFile / SaveFile Tests ====================

TEST_F(XMLDocumentTest_112, LoadFileNonExistent_112) {
    XMLError err = doc.LoadFile("nonexistent_file_that_does_not_exist.xml");
    EXPECT_NE(XML_SUCCESS, err);
    EXPECT_TRUE(doc.Error());
}

TEST_F(XMLDocumentTest_112, SaveFileAndLoadFile_112) {
    doc.Parse("<root><child attr=\"value\"/></root>");
    ASSERT_FALSE(doc.Error());

    const char* filename = "test_output_112.xml";
    XMLError saveErr = doc.SaveFile(filename, false);
    EXPECT_EQ(XML_SUCCESS, saveErr);

    XMLDocument loaded;
    XMLError loadErr = loaded.LoadFile(filename);
    EXPECT_EQ(XML_SUCCESS, loadErr);
    ASSERT_NE(nullptr, loaded.RootElement());
    EXPECT_STREQ("root", loaded.RootElement()->Value());

    // Cleanup
    std::remove(filename);
}

TEST_F(XMLDocumentTest_112, SaveFileCompact_112) {
    doc.Parse("<root> <child/> </root>");
    ASSERT_FALSE(doc.Error());

    const char* filename = "test_output_compact_112.xml";
    XMLError saveErr = doc.SaveFile(filename, true);
    EXPECT_EQ(XML_SUCCESS, saveErr);

    XMLDocument loaded;
    XMLError loadErr = loaded.LoadFile(filename);
    EXPECT_EQ(XML_SUCCESS, loadErr);
    ASSERT_NE(nullptr, loaded.RootElement());

    std::remove(filename);
}

TEST_F(XMLDocumentTest_112, LoadFileFromFILE_112) {
    // First save a file
    doc.Parse("<test/>");
    const char* filename = "test_file_ptr_112.xml";
    doc.SaveFile(filename);

    FILE* fp = fopen(filename, "rb");
    ASSERT_NE(nullptr, fp);

    XMLDocument loaded;
    XMLError err = loaded.LoadFile(fp);
    fclose(fp);
    EXPECT_EQ(XML_SUCCESS, err);
    ASSERT_NE(nullptr, loaded.RootElement());
    EXPECT_STREQ("test", loaded.RootElement()->Value());

    std::remove(filename);
}

TEST_F(XMLDocumentTest_112, SaveFileToFILE_112) {
    doc.Parse("<filetest/>");
    const char* filename = "test_file_save_ptr_112.xml";

    FILE* fp = fopen(filename, "w");
    ASSERT_NE(nullptr, fp);
    XMLError err = doc.SaveFile(fp, false);
    fclose(fp);
    EXPECT_EQ(XML_SUCCESS, err);

    XMLDocument loaded;
    loaded.LoadFile(filename);
    ASSERT_NE(nullptr, loaded.RootElement());
    EXPECT_STREQ("filetest", loaded.RootElement()->Value());

    std::remove(filename);
}

// ==================== Print Tests ====================

TEST_F(XMLDocumentTest_112, PrintToXMLPrinter_112) {
    doc.Parse("<root><child/></root>");
    ASSERT_FALSE(doc.Error());

    XMLPrinter printer;
    doc.Print(&printer);
    const char* result = printer.CStr();
    ASSERT_NE(nullptr, result);
    EXPECT_NE(nullptr, strstr(result, "root"));
    EXPECT_NE(nullptr, strstr(result, "child"));
}

TEST_F(XMLDocumentTest_112, PrintWithNullPrinter_112) {
    doc.Parse("<root/>");
    // Print with null should use stdout (just verify no crash)
    // This may output to stdout, which is acceptable in test
    doc.Print(nullptr);
}

// ==================== Accept Tests ====================

TEST_F(XMLDocumentTest_112, AcceptWithPrinter_112) {
    doc.Parse("<root>text</root>");
    ASSERT_FALSE(doc.Error());

    XMLPrinter printer;
    bool result = doc.Accept(&printer);
    EXPECT_TRUE(result);
    const char* output = printer.CStr();
    ASSERT_NE(nullptr, output);
    EXPECT_NE(nullptr, strstr(output, "root"));
}

// ==================== XMLNode Interaction Tests ====================

TEST_F(XMLDocumentTest_112, InsertEndChild_112) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);
    ASSERT_NE(nullptr, doc.RootElement());
    EXPECT_STREQ("root", doc.RootElement()->Value());
}

TEST_F(XMLDocumentTest_112, InsertFirstChild_112) {
    XMLElement* first = doc.NewElement("first");
    doc.InsertFirstChild(first);
    ASSERT_NE(nullptr, doc.RootElement());
    EXPECT_STREQ("first", doc.RootElement()->Value());
}

TEST_F(XMLDocumentTest_112, MultipleChildElements_112) {
    doc.Parse("<root><a/><b/><c/></root>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(nullptr, root);

    XMLElement* a = root->FirstChildElement("a");
    XMLElement* b = root->FirstChildElement("b");
    XMLElement* c = root->FirstChildElement("c");
    EXPECT_NE(nullptr, a);
    EXPECT_NE(nullptr, b);
    EXPECT_NE(nullptr, c);
}

TEST_F(XMLDocumentTest_112, ChildElementCount_112) {
    doc.Parse("<root><a/><b/><c/></root>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(nullptr, root);
    EXPECT_EQ(3, root->ChildElementCount());
}

TEST_F(XMLDocumentTest_112, ChildElementCountByName_112) {
    doc.Parse("<root><a/><b/><a/></root>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(nullptr, root);
    EXPECT_EQ(2, root->ChildElementCount("a"));
    EXPECT_EQ(1, root->ChildElementCount("b"));
    EXPECT_EQ(0, root->ChildElementCount("nonexistent"));
}

TEST_F(XMLDocumentTest_112, DeleteChildren_112) {
    doc.Parse("<root><a/><b/></root>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(nullptr, root);
    root->DeleteChildren();
    EXPECT_TRUE(root->NoChildren());
    EXPECT_EQ(0, root->ChildElementCount());
}

TEST_F(XMLDocumentTest_112, NoChildrenOnEmptyElement_112) {
    doc.Parse("<root/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(nullptr, root);
    EXPECT_TRUE(root->NoChildren());
}

TEST_F(XMLDocumentTest_112, LastChildElement_112) {
    doc.Parse("<root><a/><b/><c/></root>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(nullptr, root);
    XMLElement* last = root->LastChildElement();
    ASSERT_NE(nullptr, last);
    EXPECT_STREQ("c", last->Value());
}

TEST_F(XMLDocumentTest_112, NextSiblingElement_112) {
    doc.Parse("<root><a/><b/><c/></root>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(nullptr, root);
    XMLElement* a = root->FirstChildElement();
    ASSERT_NE(nullptr, a);
    EXPECT_STREQ("a", a->Value());
    XMLElement* b = a->NextSiblingElement();
    ASSERT_NE(nullptr, b);
    EXPECT_STREQ("b", b->Value());
    XMLElement* c = b->NextSiblingElement();
    ASSERT_NE(nullptr, c);
    EXPECT_STREQ("c", c->Value());
    EXPECT_EQ(nullptr, c->NextSiblingElement());
}

TEST_F(XMLDocumentTest_112, PreviousSiblingElement_112) {
    doc.Parse("<root><a/><b/><c/></root>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(nullptr, root);
    XMLElement* c = root->LastChildElement();
    ASSERT_NE(nullptr, c);
    EXPECT_STREQ("c", c->Value());
    XMLElement* b = c->PreviousSiblingElement();
    ASSERT_NE(nullptr, b);
    EXPECT_STREQ("b", b->Value());
}

TEST_F(XMLDocumentTest_112, InsertAfterChild_112) {
    doc.Parse("<root><a/><c/></root>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(nullptr, root);
    XMLElement* a = root->FirstChildElement("a");
    XMLElement* b = doc.NewElement("b");
    root->InsertAfterChild(a, b);

    XMLElement* afterA = a->NextSiblingElement();
    ASSERT_NE(nullptr, afterA);
    EXPECT_STREQ("b", afterA->Value());
}

// ==================== DeepClone Tests ====================

TEST_F(XMLDocumentTest_112, DeepCloneElement_112) {
    doc.Parse("<root><child attr=\"v\">text</child></root>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(nullptr, root);

    XMLDocument target;
    XMLNode* cloned = root->DeepClone(&target);
    ASSERT_NE(nullptr, cloned);
    target.InsertEndChild(cloned);

    ASSERT_NE(nullptr, target.RootElement());
    EXPECT_STREQ("root", target.RootElement()->Value());
    XMLElement* clonedChild = target.RootElement()->FirstChildElement("child");
    ASSERT_NE(nullptr, clonedChild);
    EXPECT_STREQ("v", clonedChild->Attribute("attr"));
}

// ==================== UserData Tests ====================

TEST_F(XMLDocumentTest_112, UserDataDefaultNull_112) {
    EXPECT_EQ(nullptr, doc.GetUserData());
}

TEST_F(XMLDocumentTest_112, SetAndGetUserData_112) {
    int data = 42;
    doc.SetUserData(&data);
    EXPECT_EQ(&data, doc.GetUserData());
}

TEST_F(XMLDocumentTest_112, SetUserDataNull_112) {
    int data = 42;
    doc.SetUserData(&data);
    doc.SetUserData(nullptr);
    EXPECT_EQ(nullptr, doc.GetUserData());
}

// ==================== Value Tests ====================

TEST_F(XMLDocumentTest_112, ElementValueMatchesParsedName_112) {
    doc.Parse("<myroot/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(nullptr, root);
    EXPECT_STREQ("myroot", root->Value());
}

TEST_F(XMLDocumentTest_112, SetValueOnElement_112) {
    doc.Parse("<root/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(nullptr, root);
    root->SetValue("newname", false);
    EXPECT_STREQ("newname", root->Value());
}

// ==================== GetDocument Tests ====================

TEST_F(XMLDocumentTest_112, GetDocumentFromElement_112) {
    doc.Parse("<root/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(nullptr, root);
    EXPECT_EQ(&doc, root->GetDocument());
}

// ==================== Parent Tests ====================

TEST_F(XMLDocumentTest_112, ParentOfRootIsDocument_112) {
    doc.Parse("<root/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(nullptr, root);
    EXPECT_EQ(&doc, root->Parent());
}

// ==================== ToElement Tests ====================

TEST_F(XMLDocumentTest_112, ToElementOnElement_112) {
    doc.Parse("<root/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(nullptr, root);
    EXPECT_NE(nullptr, root->ToElement());
}

TEST_F(XMLDocumentTest_112, ToDocumentOnDocumentNode_112) {
    EXPECT_NE(nullptr, doc.ToDocument());
    EXPECT_EQ(nullptr, doc.ToElement());
}

// ==================== XML with Declaration ====================

TEST_F(XMLDocumentTest_112, ParseWithDeclaration_112) {
    const char* xml = "<?xml version=\"1.0\" encoding=\"UTF-8\"?><root/>";
    XMLError err = doc.Parse(xml);
    EXPECT_EQ(XML_SUCCESS, err);
    ASSERT_NE(nullptr, doc.RootElement());
    EXPECT_STREQ("root", doc.RootElement()->Value());
}

// ==================== Complex XML Tests ====================

TEST_F(XMLDocumentTest_112, ParseNestedElements_112) {
    const char* xml = "<a><b><c><d/></c></b></a>";
    XMLError err = doc.Parse(xml);
    EXPECT_EQ(XML_SUCCESS, err);

    XMLElement* a = doc.RootElement();
    ASSERT_NE(nullptr, a);
    EXPECT_STREQ("a", a->Value());

    XMLElement* b = a->FirstChildElement("b");
    ASSERT_NE(nullptr, b);

    XMLElement* c = b->FirstChildElement("c");
    ASSERT_NE(nullptr, c);

    XMLElement* d = c->FirstChildElement("d");
    ASSERT_NE(nullptr, d);
}

TEST_F(XMLDocumentTest_112, ParseWithAttributes_112) {
    doc.Parse("<root name=\"test\" id=\"1\"/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(nullptr, root);
    EXPECT_STREQ("test", root->Attribute("name"));
    EXPECT_STREQ("1", root->Attribute("id"));
}

TEST_F(XMLDocumentTest_112, ParseWithTextContent_112) {
    doc.Parse("<root>Hello World</root>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(nullptr, root);
    EXPECT_STREQ("Hello World", root->GetText());
}

// ==================== GetLineNum Tests ====================

TEST_F(XMLDocumentTest_112, GetLineNumForElements_112) {
    doc.Parse("<root>\n<child/>\n</root>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(nullptr, root);
    EXPECT_EQ(1, root->GetLineNum());

    XMLElement* child = root->FirstChildElement("child");
    ASSERT_NE(nullptr, child);
    EXPECT_EQ(2, child->GetLineNum());
}

// ==================== Entity Processing Tests ====================

TEST_F(XMLDocumentTest_112, EntityProcessingEnabled_112) {
    doc.Parse("<root>&amp;</root>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(nullptr, root);
    EXPECT_STREQ("&", root->GetText());
}

TEST_F(XMLDocumentTest_112, EntityProcessingDisabled_112) {
    XMLDocument noEntity(false);
    noEntity.Parse("<root>&amp;</root>");
    XMLElement* root = noEntity.RootElement();
    ASSERT_NE(nullptr, root);
    EXPECT_STREQ("&amp;", root->GetText());
}

// ==================== PrintError Tests ====================

TEST_F(XMLDocumentTest_112, PrintErrorOnError_112) {
    doc.Parse("<unclosed");
    EXPECT_TRUE(doc.Error());
    // Just verify it doesn't crash
    doc.PrintError();
}

TEST_F(XMLDocumentTest_112, PrintErrorNoError_112) {
    doc.Parse("<root/>");
    EXPECT_FALSE(doc.Error());
    // Just verify it doesn't crash
    doc.PrintError();
}

// ==================== MarkInUse Tests ====================

TEST_F(XMLDocumentTest_112, MarkInUsePreventsDeletion_112) {
    XMLElement* elem = doc.NewElement("test");
    doc.MarkInUse(elem);
    // Insert after marking in use should work
    doc.InsertEndChild(elem);
    ASSERT_NE(nullptr, doc.RootElement());
    EXPECT_STREQ("test", doc.RootElement()->Value());
}

// ==================== LinkEndChild Tests ====================

TEST_F(XMLDocumentTest_112, LinkEndChildSameAsInsertEndChild_112) {
    XMLElement* root = doc.NewElement("root");
    XMLNode* result = doc.LinkEndChild(root);
    EXPECT_EQ(root, result);
    ASSERT_NE(nullptr, doc.RootElement());
    EXPECT_STREQ("root", doc.RootElement()->Value());
}

// ==================== NextSiblingElement with name ====================

TEST_F(XMLDocumentTest_112, NextSiblingElementByName_112) {
    doc.Parse("<root><a/><b/><a/><c/></root>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(nullptr, root);
    XMLElement* firstA = root->FirstChildElement("a");
    ASSERT_NE(nullptr, firstA);
    XMLElement* secondA = firstA->NextSiblingElement("a");
    ASSERT_NE(nullptr, secondA);
    // secondA should be the second 'a', not 'b'
    EXPECT_STREQ("a", secondA->Value());
    EXPECT_NE(firstA, secondA);
}

TEST_F(XMLDocumentTest_112, PreviousSiblingElementByName_112) {
    doc.Parse("<root><a/><b/><a/><c/></root>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(nullptr, root);
    XMLElement* c = root->LastChildElement("c");
    ASSERT_NE(nullptr, c);
    XMLElement* prevA = c->PreviousSiblingElement("a");
    ASSERT_NE(nullptr, prevA);
    EXPECT_STREQ("a", prevA->Value());
}
