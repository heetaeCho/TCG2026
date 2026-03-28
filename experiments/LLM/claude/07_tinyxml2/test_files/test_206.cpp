#include "gtest/gtest.h"
#include "tinyxml2.h"

using namespace tinyxml2;

class XMLUnknownTest_206 : public ::testing::Test {
protected:
    XMLDocument doc;
    
    void SetUp() override {
    }
    
    void TearDown() override {
    }
};

// Test that ShallowClone with nullptr uses the same document
TEST_F(XMLUnknownTest_206, ShallowCloneWithNullDocUsesSameDocument_206) {
    XMLUnknown* unknown = doc.NewUnknown("some unknown content");
    ASSERT_NE(unknown, nullptr);
    
    XMLNode* clone = unknown->ShallowClone(nullptr);
    ASSERT_NE(clone, nullptr);
    
    // The clone should belong to the same document
    EXPECT_EQ(clone->GetDocument(), unknown->GetDocument());
    
    // The clone should have the same value
    EXPECT_STREQ(clone->Value(), "some unknown content");
    
    // The clone should be an XMLUnknown
    EXPECT_NE(clone->ToUnknown(), nullptr);
    
    doc.DeleteNode(clone);
}

// Test that ShallowClone with a different document creates clone in that document
TEST_F(XMLUnknownTest_206, ShallowCloneWithDifferentDocument_206) {
    XMLUnknown* unknown = doc.NewUnknown("test unknown");
    ASSERT_NE(unknown, nullptr);
    
    XMLDocument otherDoc;
    XMLNode* clone = unknown->ShallowClone(&otherDoc);
    ASSERT_NE(clone, nullptr);
    
    // The clone should belong to the other document
    EXPECT_EQ(clone->GetDocument(), &otherDoc);
    
    // The clone should have the same value
    EXPECT_STREQ(clone->Value(), "test unknown");
    
    // The clone should be an XMLUnknown
    EXPECT_NE(clone->ToUnknown(), nullptr);
    
    otherDoc.DeleteNode(clone);
}

// Test that ShallowClone with the same document works
TEST_F(XMLUnknownTest_206, ShallowCloneWithSameDocument_206) {
    XMLUnknown* unknown = doc.NewUnknown("same doc unknown");
    ASSERT_NE(unknown, nullptr);
    
    XMLNode* clone = unknown->ShallowClone(&doc);
    ASSERT_NE(clone, nullptr);
    
    EXPECT_EQ(clone->GetDocument(), &doc);
    EXPECT_STREQ(clone->Value(), "same doc unknown");
    EXPECT_NE(clone->ToUnknown(), nullptr);
    
    doc.DeleteNode(clone);
}

// Test ShallowClone with empty string value
TEST_F(XMLUnknownTest_206, ShallowCloneWithEmptyValue_206) {
    XMLUnknown* unknown = doc.NewUnknown("");
    ASSERT_NE(unknown, nullptr);
    
    XMLNode* clone = unknown->ShallowClone(nullptr);
    ASSERT_NE(clone, nullptr);
    
    EXPECT_STREQ(clone->Value(), "");
    EXPECT_NE(clone->ToUnknown(), nullptr);
    
    doc.DeleteNode(clone);
}

// Test that ShallowClone creates an independent copy (not the same pointer)
TEST_F(XMLUnknownTest_206, ShallowCloneCreatesNewNode_206) {
    XMLUnknown* unknown = doc.NewUnknown("original");
    ASSERT_NE(unknown, nullptr);
    
    XMLNode* clone = unknown->ShallowClone(nullptr);
    ASSERT_NE(clone, nullptr);
    
    // Clone should be a different node
    EXPECT_NE(clone, static_cast<XMLNode*>(unknown));
    
    doc.DeleteNode(clone);
}

// Test ShallowClone preserves value with special characters
TEST_F(XMLUnknownTest_206, ShallowClonePreservesSpecialCharacters_206) {
    XMLUnknown* unknown = doc.NewUnknown("!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML\"");
    ASSERT_NE(unknown, nullptr);
    
    XMLNode* clone = unknown->ShallowClone(nullptr);
    ASSERT_NE(clone, nullptr);
    
    EXPECT_STREQ(clone->Value(), "!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML\"");
    
    doc.DeleteNode(clone);
}

// Test ShallowClone does not copy children (shallow behavior)
TEST_F(XMLUnknownTest_206, ShallowCloneDoesNotCopyChildren_206) {
    // Parse a document with an unknown node
    const char* xml = "<?xml version=\"1.0\"?><root>text</root>";
    doc.Parse(xml);
    
    XMLUnknown* unknown = doc.NewUnknown("some unknown");
    ASSERT_NE(unknown, nullptr);
    
    XMLNode* clone = unknown->ShallowClone(nullptr);
    ASSERT_NE(clone, nullptr);
    
    // Unknown nodes typically don't have children, but verify clone has none
    EXPECT_TRUE(clone->NoChildren());
    
    doc.DeleteNode(clone);
}

// Test ShallowEqual with matching XMLUnknown nodes
TEST_F(XMLUnknownTest_206, ShallowEqualWithMatchingNodes_206) {
    XMLUnknown* unknown1 = doc.NewUnknown("same content");
    XMLUnknown* unknown2 = doc.NewUnknown("same content");
    ASSERT_NE(unknown1, nullptr);
    ASSERT_NE(unknown2, nullptr);
    
    EXPECT_TRUE(unknown1->ShallowEqual(unknown2));
    
    doc.DeleteNode(unknown1);
    doc.DeleteNode(unknown2);
}

// Test ShallowEqual with different XMLUnknown nodes
TEST_F(XMLUnknownTest_206, ShallowEqualWithDifferentNodes_206) {
    XMLUnknown* unknown1 = doc.NewUnknown("content A");
    XMLUnknown* unknown2 = doc.NewUnknown("content B");
    ASSERT_NE(unknown1, nullptr);
    ASSERT_NE(unknown2, nullptr);
    
    EXPECT_FALSE(unknown1->ShallowEqual(unknown2));
    
    doc.DeleteNode(unknown1);
    doc.DeleteNode(unknown2);
}

// Test ToUnknown returns non-null for XMLUnknown
TEST_F(XMLUnknownTest_206, ToUnknownReturnsNonNull_206) {
    XMLUnknown* unknown = doc.NewUnknown("test");
    ASSERT_NE(unknown, nullptr);
    
    EXPECT_NE(unknown->ToUnknown(), nullptr);
    EXPECT_EQ(unknown->ToUnknown(), unknown);
    
    doc.DeleteNode(unknown);
}

// Test that XMLUnknown is not other node types
TEST_F(XMLUnknownTest_206, ToOtherTypesReturnsNull_206) {
    XMLUnknown* unknown = doc.NewUnknown("test");
    ASSERT_NE(unknown, nullptr);
    
    EXPECT_EQ(unknown->ToElement(), nullptr);
    EXPECT_EQ(unknown->ToText(), nullptr);
    EXPECT_EQ(unknown->ToComment(), nullptr);
    EXPECT_EQ(unknown->ToDocument(), nullptr);
    EXPECT_EQ(unknown->ToDeclaration(), nullptr);
    
    doc.DeleteNode(unknown);
}

// Test ShallowClone with long value string
TEST_F(XMLUnknownTest_206, ShallowCloneWithLongValue_206) {
    std::string longStr(1000, 'x');
    XMLUnknown* unknown = doc.NewUnknown(longStr.c_str());
    ASSERT_NE(unknown, nullptr);
    
    XMLNode* clone = unknown->ShallowClone(nullptr);
    ASSERT_NE(clone, nullptr);
    
    EXPECT_STREQ(clone->Value(), longStr.c_str());
    
    doc.DeleteNode(clone);
}

// Test parsing and cloning unknown node from XML
TEST_F(XMLUnknownTest_206, ParseAndCloneUnknownFromXML_206) {
    const char* xml = "<root><!unknown stuff></root>";
    XMLError err = doc.Parse(xml);
    
    // If parsing succeeds, find the unknown node
    if (err == XML_SUCCESS) {
        XMLElement* root = doc.RootElement();
        if (root) {
            const XMLNode* child = root->FirstChild();
            if (child && child->ToUnknown()) {
                XMLNode* clone = child->ShallowClone(nullptr);
                ASSERT_NE(clone, nullptr);
                EXPECT_NE(clone->ToUnknown(), nullptr);
                EXPECT_STREQ(clone->Value(), child->Value());
                doc.DeleteNode(clone);
            }
        }
    }
}

// Test multiple ShallowClone calls produce independent clones
TEST_F(XMLUnknownTest_206, MultipleShallowClonesAreIndependent_206) {
    XMLUnknown* unknown = doc.NewUnknown("multi clone");
    ASSERT_NE(unknown, nullptr);
    
    XMLNode* clone1 = unknown->ShallowClone(nullptr);
    XMLNode* clone2 = unknown->ShallowClone(nullptr);
    ASSERT_NE(clone1, nullptr);
    ASSERT_NE(clone2, nullptr);
    
    EXPECT_NE(clone1, clone2);
    EXPECT_STREQ(clone1->Value(), clone2->Value());
    EXPECT_STREQ(clone1->Value(), "multi clone");
    
    doc.DeleteNode(clone1);
    doc.DeleteNode(clone2);
}

// Test ShallowEqual with a non-XMLUnknown node
TEST_F(XMLUnknownTest_206, ShallowEqualWithDifferentNodeType_206) {
    XMLUnknown* unknown = doc.NewUnknown("some text");
    XMLComment* comment = doc.NewComment("some text");
    ASSERT_NE(unknown, nullptr);
    ASSERT_NE(comment, nullptr);
    
    EXPECT_FALSE(unknown->ShallowEqual(comment));
    
    doc.DeleteNode(unknown);
    doc.DeleteNode(comment);
}
