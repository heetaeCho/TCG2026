#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "tinyxml2.h"

using namespace tinyxml2;

// Mock XMLVisitor to test Accept behavior
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

class XMLDeclarationTest_204 : public ::testing::Test {
protected:
    void SetUp() override {
        doc = new XMLDocument();
    }

    void TearDown() override {
        delete doc;
    }

    XMLDocument* doc;
};

// Test that Accept calls Visit on the visitor with the declaration and returns true when visitor returns true
TEST_F(XMLDeclarationTest_204, AcceptCallsVisitAndReturnsTrue_204) {
    // Parse a document with a declaration to get an XMLDeclaration node
    const char* xml = "<?xml version=\"1.0\" encoding=\"UTF-8\"?><root/>";
    doc->Parse(xml);
    
    const XMLDeclaration* decl = doc->FirstChild()->ToDeclaration();
    ASSERT_NE(decl, nullptr);

    MockXMLVisitor mockVisitor;
    EXPECT_CALL(mockVisitor, Visit(testing::Ref(*decl)))
        .Times(1)
        .WillOnce(testing::Return(true));

    bool result = decl->Accept(&mockVisitor);
    EXPECT_TRUE(result);
}

// Test that Accept returns false when visitor's Visit returns false
TEST_F(XMLDeclarationTest_204, AcceptReturnsFalseWhenVisitorReturnsFalse_204) {
    const char* xml = "<?xml version=\"1.0\"?><root/>";
    doc->Parse(xml);
    
    const XMLDeclaration* decl = doc->FirstChild()->ToDeclaration();
    ASSERT_NE(decl, nullptr);

    MockXMLVisitor mockVisitor;
    EXPECT_CALL(mockVisitor, Visit(testing::Ref(*decl)))
        .Times(1)
        .WillOnce(testing::Return(false));

    bool result = decl->Accept(&mockVisitor);
    EXPECT_FALSE(result);
}

// Test ToDeclaration returns non-null for a declaration node
TEST_F(XMLDeclarationTest_204, ToDeclarationReturnsNonNull_204) {
    const char* xml = "<?xml version=\"1.0\"?><root/>";
    doc->Parse(xml);
    
    XMLNode* firstChild = doc->FirstChild();
    ASSERT_NE(firstChild, nullptr);
    
    XMLDeclaration* decl = firstChild->ToDeclaration();
    EXPECT_NE(decl, nullptr);
}

// Test that a non-declaration node's ToDeclaration returns null
TEST_F(XMLDeclarationTest_204, NonDeclarationNodeToDeclarationReturnsNull_204) {
    const char* xml = "<root/>";
    doc->Parse(xml);
    
    XMLNode* firstChild = doc->FirstChild();
    ASSERT_NE(firstChild, nullptr);
    
    XMLDeclaration* decl = firstChild->ToDeclaration();
    EXPECT_EQ(decl, nullptr);
}

// Test ShallowClone creates a copy in another document
TEST_F(XMLDeclarationTest_204, ShallowCloneCreatesDeclarationInNewDoc_204) {
    const char* xml = "<?xml version=\"1.0\" encoding=\"UTF-8\"?><root/>";
    doc->Parse(xml);
    
    const XMLDeclaration* decl = doc->FirstChild()->ToDeclaration();
    ASSERT_NE(decl, nullptr);

    XMLDocument targetDoc;
    XMLNode* cloned = decl->ShallowClone(&targetDoc);
    ASSERT_NE(cloned, nullptr);
    
    XMLDeclaration* clonedDecl = cloned->ToDeclaration();
    EXPECT_NE(clonedDecl, nullptr);
    
    targetDoc.InsertFirstChild(cloned);
}

// Test ShallowClone creates a copy in the same document
TEST_F(XMLDeclarationTest_204, ShallowCloneInSameDoc_204) {
    const char* xml = "<?xml version=\"1.0\"?><root/>";
    doc->Parse(xml);
    
    const XMLDeclaration* decl = doc->FirstChild()->ToDeclaration();
    ASSERT_NE(decl, nullptr);

    XMLNode* cloned = decl->ShallowClone(doc);
    ASSERT_NE(cloned, nullptr);
    
    XMLDeclaration* clonedDecl = cloned->ToDeclaration();
    EXPECT_NE(clonedDecl, nullptr);
}

// Test ShallowEqual with identical declarations
TEST_F(XMLDeclarationTest_204, ShallowEqualWithIdenticalDeclaration_204) {
    const char* xml = "<?xml version=\"1.0\"?><root/>";
    doc->Parse(xml);
    
    const XMLDeclaration* decl = doc->FirstChild()->ToDeclaration();
    ASSERT_NE(decl, nullptr);

    XMLNode* cloned = decl->ShallowClone(doc);
    ASSERT_NE(cloned, nullptr);

    EXPECT_TRUE(decl->ShallowEqual(cloned));
}

// Test ShallowEqual with different node types
TEST_F(XMLDeclarationTest_204, ShallowEqualWithDifferentNodeType_204) {
    const char* xml = "<?xml version=\"1.0\"?><!-- comment --><root/>";
    doc->Parse(xml);
    
    const XMLDeclaration* decl = doc->FirstChild()->ToDeclaration();
    ASSERT_NE(decl, nullptr);
    
    // Find the comment node
    const XMLNode* comment = decl->NextSibling();
    // The comment might be next or the root element
    while (comment && !comment->ToComment()) {
        comment = comment->NextSibling();
    }
    
    if (comment) {
        EXPECT_FALSE(decl->ShallowEqual(comment));
    }
}

// Test ShallowEqual with different declaration content
TEST_F(XMLDeclarationTest_204, ShallowEqualWithDifferentDeclaration_204) {
    XMLDocument doc1;
    const char* xml1 = "<?xml version=\"1.0\"?><root/>";
    doc1.Parse(xml1);
    
    XMLDocument doc2;
    const char* xml2 = "<?xml version=\"2.0\"?><root/>";
    doc2.Parse(xml2);
    
    const XMLDeclaration* decl1 = doc1.FirstChild()->ToDeclaration();
    const XMLDeclaration* decl2 = doc2.FirstChild()->ToDeclaration();
    
    ASSERT_NE(decl1, nullptr);
    ASSERT_NE(decl2, nullptr);
    
    EXPECT_FALSE(decl1->ShallowEqual(decl2));
}

// Test that Accept is called exactly once per invocation
TEST_F(XMLDeclarationTest_204, AcceptCallsVisitExactlyOnce_204) {
    const char* xml = "<?xml version=\"1.0\"?><root/>";
    doc->Parse(xml);
    
    const XMLDeclaration* decl = doc->FirstChild()->ToDeclaration();
    ASSERT_NE(decl, nullptr);

    MockXMLVisitor mockVisitor;
    EXPECT_CALL(mockVisitor, Visit(testing::An<const XMLDeclaration&>()))
        .Times(1)
        .WillOnce(testing::Return(true));

    decl->Accept(&mockVisitor);
}

// Test declaration value/content through the node interface
TEST_F(XMLDeclarationTest_204, DeclarationValueIsAccessible_204) {
    const char* xml = "<?xml version=\"1.0\" encoding=\"UTF-8\"?><root/>";
    doc->Parse(xml);
    
    const XMLDeclaration* decl = doc->FirstChild()->ToDeclaration();
    ASSERT_NE(decl, nullptr);
    
    // The value of a declaration node should contain the declaration content
    const char* value = decl->Value();
    ASSERT_NE(value, nullptr);
    EXPECT_TRUE(strlen(value) > 0);
}

// Test multiple accepts on the same declaration
TEST_F(XMLDeclarationTest_204, MultipleAcceptCalls_204) {
    const char* xml = "<?xml version=\"1.0\"?><root/>";
    doc->Parse(xml);
    
    const XMLDeclaration* decl = doc->FirstChild()->ToDeclaration();
    ASSERT_NE(decl, nullptr);

    MockXMLVisitor mockVisitor;
    EXPECT_CALL(mockVisitor, Visit(testing::An<const XMLDeclaration&>()))
        .Times(3)
        .WillRepeatedly(testing::Return(true));

    EXPECT_TRUE(decl->Accept(&mockVisitor));
    EXPECT_TRUE(decl->Accept(&mockVisitor));
    EXPECT_TRUE(decl->Accept(&mockVisitor));
}

// Test ShallowEqual with itself
TEST_F(XMLDeclarationTest_204, ShallowEqualWithItself_204) {
    const char* xml = "<?xml version=\"1.0\"?><root/>";
    doc->Parse(xml);
    
    const XMLDeclaration* decl = doc->FirstChild()->ToDeclaration();
    ASSERT_NE(decl, nullptr);
    
    EXPECT_TRUE(decl->ShallowEqual(decl));
}
