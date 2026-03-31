#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "tinyxml2.h"

using namespace tinyxml2;

// Mock XMLVisitor for testing Accept
class MockXMLVisitor : public XMLVisitor {
public:
    MOCK_METHOD(bool, Visit, (const XMLDeclaration&), (override));
};

class XMLDeclarationTest_67 : public ::testing::Test {
protected:
    void SetUp() override {
        doc = new XMLDocument();
    }

    void TearDown() override {
        delete doc;
    }

    XMLDocument* doc;
};

// Test that parsing a declaration and retrieving it via ToDeclaration works
TEST_F(XMLDeclarationTest_67, ToDeclarationReturnsNonNull_67) {
    const char* xml = "<?xml version=\"1.0\" encoding=\"UTF-8\"?><root/>";
    doc->Parse(xml);
    XMLNode* firstChild = doc->FirstChild();
    ASSERT_NE(firstChild, nullptr);
    XMLDeclaration* decl = firstChild->ToDeclaration();
    ASSERT_NE(decl, nullptr);
}

// Test that ToDeclaration returns this pointer
TEST_F(XMLDeclarationTest_67, ToDeclarationReturnsSelf_67) {
    const char* xml = "<?xml version=\"1.0\"?><root/>";
    doc->Parse(xml);
    XMLNode* firstChild = doc->FirstChild();
    ASSERT_NE(firstChild, nullptr);
    XMLDeclaration* decl = firstChild->ToDeclaration();
    EXPECT_EQ(static_cast<XMLNode*>(decl), firstChild);
}

// Test that non-declaration nodes return nullptr for ToDeclaration
TEST_F(XMLDeclarationTest_67, NonDeclarationNodeReturnsNullForToDeclaration_67) {
    const char* xml = "<root/>";
    doc->Parse(xml);
    XMLNode* firstChild = doc->FirstChild();
    ASSERT_NE(firstChild, nullptr);
    XMLDeclaration* decl = firstChild->ToDeclaration();
    EXPECT_EQ(decl, nullptr);
}

// Test ShallowClone creates a new declaration in another document
TEST_F(XMLDeclarationTest_67, ShallowCloneCreatesDeclarationInNewDocument_67) {
    const char* xml = "<?xml version=\"1.0\" encoding=\"UTF-8\"?><root/>";
    doc->Parse(xml);
    XMLNode* firstChild = doc->FirstChild();
    ASSERT_NE(firstChild, nullptr);
    XMLDeclaration* decl = firstChild->ToDeclaration();
    ASSERT_NE(decl, nullptr);

    XMLDocument doc2;
    XMLNode* cloned = decl->ShallowClone(&doc2);
    ASSERT_NE(cloned, nullptr);
    XMLDeclaration* clonedDecl = cloned->ToDeclaration();
    ASSERT_NE(clonedDecl, nullptr);
}

// Test ShallowClone preserves the value
TEST_F(XMLDeclarationTest_67, ShallowClonePreservesValue_67) {
    const char* xml = "<?xml version=\"1.0\" encoding=\"UTF-8\"?><root/>";
    doc->Parse(xml);
    XMLNode* firstChild = doc->FirstChild();
    ASSERT_NE(firstChild, nullptr);
    XMLDeclaration* decl = firstChild->ToDeclaration();
    ASSERT_NE(decl, nullptr);

    XMLDocument doc2;
    XMLNode* cloned = decl->ShallowClone(&doc2);
    ASSERT_NE(cloned, nullptr);

    EXPECT_STREQ(decl->Value(), cloned->Value());
}

// Test ShallowEqual with identical declarations
TEST_F(XMLDeclarationTest_67, ShallowEqualWithIdenticalDeclaration_67) {
    const char* xml = "<?xml version=\"1.0\" encoding=\"UTF-8\"?><root/>";
    doc->Parse(xml);
    XMLNode* firstChild = doc->FirstChild();
    ASSERT_NE(firstChild, nullptr);
    XMLDeclaration* decl = firstChild->ToDeclaration();
    ASSERT_NE(decl, nullptr);

    XMLDocument doc2;
    XMLNode* cloned = decl->ShallowClone(&doc2);
    ASSERT_NE(cloned, nullptr);

    EXPECT_TRUE(decl->ShallowEqual(cloned));
}

// Test ShallowEqual with different declarations
TEST_F(XMLDeclarationTest_67, ShallowEqualWithDifferentDeclaration_67) {
    const char* xml1 = "<?xml version=\"1.0\"?><root/>";
    doc->Parse(xml1);
    XMLNode* firstChild = doc->FirstChild();
    ASSERT_NE(firstChild, nullptr);
    XMLDeclaration* decl1 = firstChild->ToDeclaration();
    ASSERT_NE(decl1, nullptr);

    XMLDocument doc2;
    const char* xml2 = "<?xml version=\"2.0\"?><root/>";
    doc2.Parse(xml2);
    XMLNode* firstChild2 = doc2.FirstChild();
    ASSERT_NE(firstChild2, nullptr);
    XMLDeclaration* decl2 = firstChild2->ToDeclaration();
    ASSERT_NE(decl2, nullptr);

    EXPECT_FALSE(decl1->ShallowEqual(decl2));
}

// Test ShallowEqual with a non-declaration node
TEST_F(XMLDeclarationTest_67, ShallowEqualWithNonDeclarationReturnsFalse_67) {
    const char* xml = "<?xml version=\"1.0\"?><root/>";
    doc->Parse(xml);
    XMLNode* firstChild = doc->FirstChild();
    ASSERT_NE(firstChild, nullptr);
    XMLDeclaration* decl = firstChild->ToDeclaration();
    ASSERT_NE(decl, nullptr);

    // Get the element node
    XMLNode* element = firstChild->NextSibling();
    ASSERT_NE(element, nullptr);

    EXPECT_FALSE(decl->ShallowEqual(element));
}

// Test Accept calls the visitor
TEST_F(XMLDeclarationTest_67, AcceptCallsVisitor_67) {
    const char* xml = "<?xml version=\"1.0\"?><root/>";
    doc->Parse(xml);
    XMLNode* firstChild = doc->FirstChild();
    ASSERT_NE(firstChild, nullptr);
    XMLDeclaration* decl = firstChild->ToDeclaration();
    ASSERT_NE(decl, nullptr);

    MockXMLVisitor visitor;
    EXPECT_CALL(visitor, Visit(testing::Ref(*decl)))
        .Times(1)
        .WillOnce(testing::Return(true));

    bool result = decl->Accept(&visitor);
    EXPECT_TRUE(result);
}

// Test Accept returns false when visitor returns false
TEST_F(XMLDeclarationTest_67, AcceptReturnsFalseWhenVisitorReturnsFalse_67) {
    const char* xml = "<?xml version=\"1.0\"?><root/>";
    doc->Parse(xml);
    XMLNode* firstChild = doc->FirstChild();
    ASSERT_NE(firstChild, nullptr);
    XMLDeclaration* decl = firstChild->ToDeclaration();
    ASSERT_NE(decl, nullptr);

    MockXMLVisitor visitor;
    EXPECT_CALL(visitor, Visit(testing::Ref(*decl)))
        .Times(1)
        .WillOnce(testing::Return(false));

    bool result = decl->Accept(&visitor);
    EXPECT_FALSE(result);
}

// Test declaration value content
TEST_F(XMLDeclarationTest_67, DeclarationValueContent_67) {
    const char* xml = "<?xml version=\"1.0\" encoding=\"UTF-8\"?><root/>";
    doc->Parse(xml);
    XMLNode* firstChild = doc->FirstChild();
    ASSERT_NE(firstChild, nullptr);
    XMLDeclaration* decl = firstChild->ToDeclaration();
    ASSERT_NE(decl, nullptr);

    const char* value = decl->Value();
    ASSERT_NE(value, nullptr);
    // The value should contain version info
    EXPECT_NE(std::string(value).find("version"), std::string::npos);
}

// Test ShallowClone into same document
TEST_F(XMLDeclarationTest_67, ShallowCloneIntoSameDocument_67) {
    const char* xml = "<?xml version=\"1.0\"?><root/>";
    doc->Parse(xml);
    XMLNode* firstChild = doc->FirstChild();
    ASSERT_NE(firstChild, nullptr);
    XMLDeclaration* decl = firstChild->ToDeclaration();
    ASSERT_NE(decl, nullptr);

    XMLNode* cloned = decl->ShallowClone(doc);
    ASSERT_NE(cloned, nullptr);
    ASSERT_NE(cloned, static_cast<XMLNode*>(decl));
    XMLDeclaration* clonedDecl = cloned->ToDeclaration();
    ASSERT_NE(clonedDecl, nullptr);
    EXPECT_TRUE(decl->ShallowEqual(cloned));
}

// Test ShallowEqual with itself
TEST_F(XMLDeclarationTest_67, ShallowEqualWithSelf_67) {
    const char* xml = "<?xml version=\"1.0\"?><root/>";
    doc->Parse(xml);
    XMLNode* firstChild = doc->FirstChild();
    ASSERT_NE(firstChild, nullptr);
    XMLDeclaration* decl = firstChild->ToDeclaration();
    ASSERT_NE(decl, nullptr);

    EXPECT_TRUE(decl->ShallowEqual(decl));
}

// Test that the declaration is the first child of the document
TEST_F(XMLDeclarationTest_67, DeclarationIsFirstChildOfDocument_67) {
    const char* xml = "<?xml version=\"1.0\"?><root/>";
    doc->Parse(xml);
    XMLNode* firstChild = doc->FirstChild();
    ASSERT_NE(firstChild, nullptr);
    EXPECT_NE(firstChild->ToDeclaration(), nullptr);
}

// Test document with no declaration
TEST_F(XMLDeclarationTest_67, DocumentWithNoDeclaration_67) {
    const char* xml = "<root/>";
    doc->Parse(xml);
    XMLNode* firstChild = doc->FirstChild();
    ASSERT_NE(firstChild, nullptr);
    EXPECT_EQ(firstChild->ToDeclaration(), nullptr);
}

// Test declaration with minimal content
TEST_F(XMLDeclarationTest_67, MinimalDeclaration_67) {
    const char* xml = "<?xml?><root/>";
    doc->Parse(xml);
    XMLNode* firstChild = doc->FirstChild();
    ASSERT_NE(firstChild, nullptr);
    XMLDeclaration* decl = firstChild->ToDeclaration();
    EXPECT_NE(decl, nullptr);
}
