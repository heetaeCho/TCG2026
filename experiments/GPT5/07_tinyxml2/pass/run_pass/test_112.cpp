#include "gtest/gtest.h"
#include "tinyxml2.h"

using namespace tinyxml2;

// Test fixture for XMLDocument tests
class XMLDocumentTest_112 : public ::testing::Test {
protected:
    void SetUp() override {
        // No special setup required; document is empty initially
    }

    void TearDown() override {
        // Cleanup if needed
    }

    XMLDocument doc_;
};

// Test normal operation: no children, RootElement() should return nullptr
TEST_F(XMLDocumentTest_112, RootElementReturnsNullForEmptyDocument_112) {
    EXPECT_EQ(doc_.RootElement(), nullptr);
}

// Test normal operation: single root element
TEST_F(XMLDocumentTest_112, RootElementReturnsFirstChildElement_112) {
    XMLElement* element = doc_.NewElement("Root");
    doc_.InsertEndChild(element);

    XMLElement* root = doc_.RootElement();
    ASSERT_NE(root, nullptr);
    EXPECT_STREQ(root->Value(), "Root");
}

// Test with multiple child elements: RootElement() should return first child element
TEST_F(XMLDocumentTest_112, RootElementReturnsFirstOfMultipleChildren_112) {
    XMLElement* first = doc_.NewElement("First");
    XMLElement* second = doc_.NewElement("Second");
    doc_.InsertEndChild(first);
    doc_.InsertEndChild(second);

    XMLElement* root = doc_.RootElement();
    ASSERT_NE(root, nullptr);
    EXPECT_STREQ(root->Value(), "First");
}

// Test behavior when the first child is a comment: RootElement() should skip non-element nodes
TEST_F(XMLDocumentTest_112, RootElementSkipsNonElementNodes_112) {
    doc_.NewComment("This is a comment");
    XMLElement* elem = doc_.NewElement("ActualRoot");
    doc_.InsertEndChild(doc_.NewComment("Ignore me"));
    doc_.InsertEndChild(elem);

    XMLElement* root = doc_.RootElement();
    ASSERT_NE(root, nullptr);
    EXPECT_STREQ(root->Value(), "ActualRoot");
}

// Test after deleting all children: RootElement() should return nullptr
TEST_F(XMLDocumentTest_112, RootElementReturnsNullAfterDeletingChildren_112) {
    XMLElement* elem = doc_.NewElement("Root");
    doc_.InsertEndChild(elem);

    doc_.DeleteChildren();

    EXPECT_EQ(doc_.RootElement(), nullptr);
}

// Test RootElement() consistency: calling multiple times returns same pointer if document unchanged
TEST_F(XMLDocumentTest_112, RootElementConsistentOnMultipleCalls_112) {
    XMLElement* elem = doc_.NewElement("Root");
    doc_.InsertEndChild(elem);

    XMLElement* firstCall = doc_.RootElement();
    XMLElement* secondCall = doc_.RootElement();

    EXPECT_EQ(firstCall, secondCall);
}
