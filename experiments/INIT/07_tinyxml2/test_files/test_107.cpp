#include "gtest/gtest.h"
#include "tinyxml2.h"

using namespace tinyxml2;

// Mock visitor to verify Accept() interactions
class MockVisitor : public XMLVisitor {
public:
    MOCK_METHOD(bool, VisitEnter, (const XMLElement* element, const XMLAttribute* firstAttribute), (override));
    MOCK_METHOD(bool, VisitExit, (const XMLElement* element), (override));
};

class XMLDocumentTest_107 : public ::testing::Test {
protected:
    XMLDocument doc{true, XMLDocument::Whitespace::PRESERVE};
};

// Test that ToDocument() returns the same document instance
TEST_F(XMLDocumentTest_107, ToDocumentReturnsSelf_107) {
    XMLDocument* result = doc.ToDocument();
    EXPECT_EQ(result, &doc);
}

// Test creating a new element
TEST_F(XMLDocumentTest_107, NewElementCreatesNonNull_107) {
    XMLElement* elem = doc.NewElement("Test");
    ASSERT_NE(elem, nullptr);
    EXPECT_STREQ(elem->Name(), "Test");
}

// Test creating a new comment
TEST_F(XMLDocumentTest_107, NewCommentCreatesNonNull_107) {
    XMLComment* comment = doc.NewComment("Hello");
    ASSERT_NE(comment, nullptr);
    EXPECT_STREQ(comment->Value(), "Hello");
}

// Test creating a new text node
TEST_F(XMLDocumentTest_107, NewTextCreatesNonNull_107) {
    XMLText* text = doc.NewText("Sample");
    ASSERT_NE(text, nullptr);
    EXPECT_STREQ(text->Value(), "Sample");
}

// Test creating a new declaration
TEST_F(XMLDocumentTest_107, NewDeclarationCreatesNonNull_107) {
    XMLDeclaration* decl = doc.NewDeclaration("xml version=\"1.0\"");
    ASSERT_NE(decl, nullptr);
    EXPECT_STREQ(decl->Value(), "xml version=\"1.0\"");
}

// Test creating a new unknown node
TEST_F(XMLDocumentTest_107, NewUnknownCreatesNonNull_107) {
    XMLUnknown* unknown = doc.NewUnknown("<?unknown?>");
    ASSERT_NE(unknown, nullptr);
    EXPECT_STREQ(unknown->Value(), "<?unknown?>");
}

// Test setting and checking BOM
TEST_F(XMLDocumentTest_107, SetBOMAndHasBOM_107) {
    doc.SetBOM(true);
    EXPECT_TRUE(doc.HasBOM());
    doc.SetBOM(false);
    EXPECT_FALSE(doc.HasBOM());
}

// Test RootElement returns nullptr for empty document
TEST_F(XMLDocumentTest_107, RootElementEmptyDocReturnsNull_107) {
    EXPECT_EQ(doc.RootElement(), nullptr);
}

// Test LoadFile with invalid filename returns error
TEST_F(XMLDocumentTest_107, LoadFileInvalidReturnsError_107) {
    XMLError err = doc.LoadFile("nonexistent_file.xml");
    EXPECT_NE(err, XML_SUCCESS);
    EXPECT_TRUE(doc.Error());
}

// Test Parse with empty string
TEST_F(XMLDocumentTest_107, ParseEmptyStringReturnsError_107) {
    XMLError err = doc.Parse("", 0);
    EXPECT_NE(err, XML_SUCCESS);
    EXPECT_TRUE(doc.Error());
}

// Test ClearError resets the error state
TEST_F(XMLDocumentTest_107, ClearErrorResetsError_107) {
    doc.Parse("Invalid<xml>", 12);
    EXPECT_TRUE(doc.Error());
    doc.ClearError();
    EXPECT_FALSE(doc.Error());
}

// Test Accept calls visitor methods
TEST_F(XMLDocumentTest_107, AcceptCallsVisitor_107) {
    XMLElement* elem = doc.NewElement("Root");
    doc.InsertEndChild(elem);

    MockVisitor visitor;
    // Since Accept returns a bool, it should propagate visitor results
    EXPECT_CALL(visitor, VisitEnter(elem, testing::_)).WillOnce(testing::Return(true));
    EXPECT_CALL(visitor, VisitExit(elem)).WillOnce(testing::Return(true));

    bool result = doc.Accept(&visitor);
    EXPECT_TRUE(result);
}

// Test DeleteNode removes a node
TEST_F(XMLDocumentTest_107, DeleteNodeRemovesNode_107) {
    XMLElement* elem = doc.NewElement("ToDelete");
    doc.InsertEndChild(elem);
    doc.DeleteNode(elem);
    EXPECT_EQ(doc.RootElement(), nullptr);
}

// Test ErrorIDToName returns non-null for known error
TEST_F(XMLDocumentTest_107, ErrorIDToNameReturnsValid_107) {
    const char* name = XMLDocument::ErrorIDToName(XML_ERROR_FILE_NOT_FOUND);
    EXPECT_NE(name, nullptr);
}

// Test DeepCopy creates a copy document
TEST_F(XMLDocumentTest_107, DeepCopyCopiesDocument_107) {
    XMLElement* elem = doc.NewElement("Root");
    doc.InsertEndChild(elem);

    XMLDocument copyDoc;
    doc.DeepCopy(&copyDoc);

    EXPECT_NE(copyDoc.RootElement(), nullptr);
    EXPECT_STREQ(copyDoc.RootElement()->Name(), "Root");
}
