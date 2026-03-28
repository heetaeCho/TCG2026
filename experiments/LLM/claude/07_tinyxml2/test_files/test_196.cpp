#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "tinyxml2.h"

using namespace tinyxml2;

// Mock visitor to test XMLText::Accept behavior
class MockXMLVisitor : public XMLVisitor {
public:
    MOCK_METHOD(bool, VisitEnter, (const XMLDocument&), (override));
    MOCK_METHOD(bool, VisitExit, (const XMLDocument&), (override));
    MOCK_METHOD(bool, VisitEnter, (const XMLElement&, const XMLAttribute*), (override));
    MOCK_METHOD(bool, VisitExit, (const XMLElement&), (override));
    MOCK_METHOD(bool, Visit, (const XMLDeclaration&), (override));
    MOCK_METHOD(bool, Visit, (const XMLText&), (override));
    MOCK_METHOD(bool, Visit, (const XMLComment&), (override));
    MOCK_METHOD(bool, Visit, (const XMLUnknown&), (override));
};

class XMLTextTest_196 : public ::testing::Test {
protected:
    void SetUp() override {
        doc = new XMLDocument();
    }

    void TearDown() override {
        delete doc;
    }

    XMLDocument* doc;
};

// Test that Accept calls Visit on the visitor with the XMLText node and returns true when visitor returns true
TEST_F(XMLTextTest_196, AcceptCallsVisitorVisitReturnsTrue_196) {
    // Create an XMLText node via the document
    XMLElement* root = doc->NewElement("root");
    doc->InsertFirstChild(root);
    XMLText* textNode = doc->NewText("Hello World");
    root->InsertFirstChild(textNode);

    MockXMLVisitor mockVisitor;
    EXPECT_CALL(mockVisitor, Visit(testing::Ref(*textNode)))
        .Times(1)
        .WillOnce(testing::Return(true));

    bool result = textNode->Accept(&mockVisitor);
    EXPECT_TRUE(result);
}

// Test that Accept returns false when visitor's Visit returns false
TEST_F(XMLTextTest_196, AcceptCallsVisitorVisitReturnsFalse_196) {
    XMLElement* root = doc->NewElement("root");
    doc->InsertFirstChild(root);
    XMLText* textNode = doc->NewText("Some text");
    root->InsertFirstChild(textNode);

    MockXMLVisitor mockVisitor;
    EXPECT_CALL(mockVisitor, Visit(testing::Ref(*textNode)))
        .Times(1)
        .WillOnce(testing::Return(false));

    bool result = textNode->Accept(&mockVisitor);
    EXPECT_FALSE(result);
}

// Test that ToText returns the XMLText pointer itself
TEST_F(XMLTextTest_196, ToTextReturnsSelf_196) {
    XMLText* textNode = doc->NewText("test");
    XMLElement* root = doc->NewElement("root");
    doc->InsertFirstChild(root);
    root->InsertFirstChild(textNode);

    EXPECT_EQ(textNode->ToText(), textNode);
}

// Test CData default is false
TEST_F(XMLTextTest_196, CDataDefaultIsFalse_196) {
    XMLText* textNode = doc->NewText("test");
    XMLElement* root = doc->NewElement("root");
    doc->InsertFirstChild(root);
    root->InsertFirstChild(textNode);

    EXPECT_FALSE(textNode->CData());
}

// Test SetCData sets CData to true
TEST_F(XMLTextTest_196, SetCDataTrue_196) {
    XMLText* textNode = doc->NewText("test");
    XMLElement* root = doc->NewElement("root");
    doc->InsertFirstChild(root);
    root->InsertFirstChild(textNode);

    textNode->SetCData(true);
    EXPECT_TRUE(textNode->CData());
}

// Test SetCData can toggle back to false
TEST_F(XMLTextTest_196, SetCDataToggle_196) {
    XMLText* textNode = doc->NewText("test");
    XMLElement* root = doc->NewElement("root");
    doc->InsertFirstChild(root);
    root->InsertFirstChild(textNode);

    textNode->SetCData(true);
    EXPECT_TRUE(textNode->CData());
    textNode->SetCData(false);
    EXPECT_FALSE(textNode->CData());
}

// Test ShallowClone creates a copy with same text value
TEST_F(XMLTextTest_196, ShallowCloneCreatesEquivalentNode_196) {
    XMLElement* root = doc->NewElement("root");
    doc->InsertFirstChild(root);
    XMLText* textNode = doc->NewText("Hello Clone");
    root->InsertFirstChild(textNode);

    XMLNode* cloned = textNode->ShallowClone(doc);
    ASSERT_NE(cloned, nullptr);
    ASSERT_NE(cloned->ToText(), nullptr);
    EXPECT_STREQ(cloned->Value(), textNode->Value());

    // Clean up - cloned node is not yet in the tree
    delete cloned;
}

// Test ShallowClone preserves CData flag
TEST_F(XMLTextTest_196, ShallowClonePreservesCData_196) {
    XMLElement* root = doc->NewElement("root");
    doc->InsertFirstChild(root);
    XMLText* textNode = doc->NewText("CData content");
    root->InsertFirstChild(textNode);
    textNode->SetCData(true);

    XMLNode* cloned = textNode->ShallowClone(doc);
    ASSERT_NE(cloned, nullptr);
    XMLText* clonedText = cloned->ToText();
    ASSERT_NE(clonedText, nullptr);
    EXPECT_TRUE(clonedText->CData());

    delete cloned;
}

// Test ShallowEqual with identical text nodes
TEST_F(XMLTextTest_196, ShallowEqualWithIdenticalNodes_196) {
    XMLElement* root = doc->NewElement("root");
    doc->InsertFirstChild(root);
    XMLText* textNode1 = doc->NewText("Same text");
    root->InsertFirstChild(textNode1);

    XMLText* textNode2 = doc->NewText("Same text");

    EXPECT_TRUE(textNode1->ShallowEqual(textNode2));

    delete textNode2;
}

// Test ShallowEqual with different text nodes
TEST_F(XMLTextTest_196, ShallowEqualWithDifferentNodes_196) {
    XMLElement* root = doc->NewElement("root");
    doc->InsertFirstChild(root);
    XMLText* textNode1 = doc->NewText("Text A");
    root->InsertFirstChild(textNode1);

    XMLText* textNode2 = doc->NewText("Text B");

    EXPECT_FALSE(textNode1->ShallowEqual(textNode2));

    delete textNode2;
}

// Test Accept with empty text
TEST_F(XMLTextTest_196, AcceptWithEmptyText_196) {
    XMLElement* root = doc->NewElement("root");
    doc->InsertFirstChild(root);
    XMLText* textNode = doc->NewText("");
    root->InsertFirstChild(textNode);

    MockXMLVisitor mockVisitor;
    EXPECT_CALL(mockVisitor, Visit(testing::Ref(*textNode)))
        .Times(1)
        .WillOnce(testing::Return(true));

    bool result = textNode->Accept(&mockVisitor);
    EXPECT_TRUE(result);
}

// Test ShallowClone to a different document
TEST_F(XMLTextTest_196, ShallowCloneToDifferentDocument_196) {
    XMLElement* root = doc->NewElement("root");
    doc->InsertFirstChild(root);
    XMLText* textNode = doc->NewText("Cross doc text");
    root->InsertFirstChild(textNode);

    XMLDocument otherDoc;
    XMLNode* cloned = textNode->ShallowClone(&otherDoc);
    ASSERT_NE(cloned, nullptr);
    ASSERT_NE(cloned->ToText(), nullptr);
    EXPECT_STREQ(cloned->Value(), "Cross doc text");

    delete cloned;
}

// Test that text node Value() returns the text content
TEST_F(XMLTextTest_196, ValueReturnsTextContent_196) {
    XMLElement* root = doc->NewElement("root");
    doc->InsertFirstChild(root);
    XMLText* textNode = doc->NewText("Expected content");
    root->InsertFirstChild(textNode);

    EXPECT_STREQ(textNode->Value(), "Expected content");
}

// Test Accept with CData text node
TEST_F(XMLTextTest_196, AcceptWithCDataNode_196) {
    XMLElement* root = doc->NewElement("root");
    doc->InsertFirstChild(root);
    XMLText* textNode = doc->NewText("CData text");
    root->InsertFirstChild(textNode);
    textNode->SetCData(true);

    MockXMLVisitor mockVisitor;
    EXPECT_CALL(mockVisitor, Visit(testing::Ref(*textNode)))
        .Times(1)
        .WillOnce(testing::Return(true));

    bool result = textNode->Accept(&mockVisitor);
    EXPECT_TRUE(result);
    EXPECT_TRUE(textNode->CData());
}

// Test ShallowEqual with nullptr (should not crash, likely returns false)
TEST_F(XMLTextTest_196, ShallowEqualWithNonTextNode_196) {
    XMLElement* root = doc->NewElement("root");
    doc->InsertFirstChild(root);
    XMLText* textNode = doc->NewText("text");
    root->InsertFirstChild(textNode);

    XMLComment* comment = doc->NewComment("a comment");
    EXPECT_FALSE(textNode->ShallowEqual(comment));

    delete comment;
}
