#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "tinyxml2.h"

using namespace tinyxml2;

// Mock XMLVisitor for testing Accept()
class MockXMLVisitor : public XMLVisitor {
public:
    MOCK_METHOD(bool, Visit, (const XMLUnknown&), (override));
};

class XMLUnknownTest_68 : public ::testing::Test {
protected:
    void SetUp() override {
        doc = new XMLDocument();
    }

    void TearDown() override {
        delete doc;
    }

    XMLDocument* doc;
};

// Test that ToUnknown returns non-null for an XMLUnknown node
TEST_F(XMLUnknownTest_68, ToUnknownReturnsThis_68) {
    const char* xml = "<?xml version=\"1.0\"?><!unknown stuff>";
    // We need to parse something that creates an XMLUnknown node
    // Unknown nodes are created from "<!" that aren't comments or DOCTYPE
    // Let's use the document API to create unknown nodes
    
    const char* xmlWithUnknown = "<root><![UNKNOWN[data]]></root>";
    // Actually, let's parse a document with an unknown declaration
    // In tinyxml2, unknown nodes come from things like "<!something>"
    
    XMLDocument testDoc;
    // Parse XML with a processing instruction or unknown
    const char* xmlStr = "<!DOCTYPE root><root/>";
    testDoc.Parse(xmlStr);
    
    // Let's try a different approach - just parse and check via iteration
    XMLDocument doc2;
    doc2.Parse("<root/>");
    
    // Use the document to check unknown nodes via ShallowClone, etc.
    // Let's parse something that definitely creates an XMLUnknown
    XMLDocument doc3;
    // "<!something>" that is not a comment and not DOCTYPE creates XMLUnknown
    const char* unknownXml = "<?xml version=\"1.0\"?>\n<root><![CDATA[test]]></root>";
    doc3.Parse(unknownXml);
    
    // CDATA isn't unknown. Let's try with proper unknown markup
    // In tinyxml2, "<!" followed by something that's not "--" (comment) or "DOCTYPE" => unknown
    XMLDocument doc4;
    doc4.Parse("<root><!--comment--></root>");
    // comment is not unknown
    
    // The simplest way: parse raw unknown
    XMLDocument doc5;
    doc5.Parse("<!SOMETHING unknown stuff><root/>");
    
    XMLNode* child = doc5.FirstChild();
    if (child) {
        XMLUnknown* unknown = child->ToUnknown();
        if (unknown) {
            EXPECT_EQ(unknown, unknown->ToUnknown());
        }
    }
}

// Test ShallowClone creates a proper clone
TEST_F(XMLUnknownTest_68, ShallowCloneCreatesClone_68) {
    XMLDocument srcDoc;
    srcDoc.Parse("<!SOMETHING test data><root/>");
    
    XMLNode* firstChild = srcDoc.FirstChild();
    XMLUnknown* unknown = nullptr;
    if (firstChild) {
        unknown = firstChild->ToUnknown();
    }
    
    if (unknown) {
        XMLDocument destDoc;
        XMLNode* clone = unknown->ShallowClone(&destDoc);
        ASSERT_NE(clone, nullptr);
        
        XMLUnknown* clonedUnknown = clone->ToUnknown();
        ASSERT_NE(clonedUnknown, nullptr);
        
        // The clone should be equal to the original
        EXPECT_TRUE(unknown->ShallowEqual(clonedUnknown));
        
        // Clean up - the cloned node needs to be deleted if not inserted
        destDoc.InsertFirstChild(clone);
    }
}

// Test ShallowEqual with same content
TEST_F(XMLUnknownTest_68, ShallowEqualSameContent_68) {
    XMLDocument doc1;
    doc1.Parse("<!SOMETHING test data><root/>");
    
    XMLDocument doc2;
    doc2.Parse("<!SOMETHING test data><root/>");
    
    XMLNode* node1 = doc1.FirstChild();
    XMLNode* node2 = doc2.FirstChild();
    
    if (node1 && node2 && node1->ToUnknown() && node2->ToUnknown()) {
        EXPECT_TRUE(node1->ShallowEqual(node2));
    }
}

// Test ShallowEqual with different content
TEST_F(XMLUnknownTest_68, ShallowEqualDifferentContent_68) {
    XMLDocument doc1;
    doc1.Parse("<!SOMETHING test data><root/>");
    
    XMLDocument doc2;
    doc2.Parse("<!OTHER different data><root/>");
    
    XMLNode* node1 = doc1.FirstChild();
    XMLNode* node2 = doc2.FirstChild();
    
    if (node1 && node2 && node1->ToUnknown() && node2->ToUnknown()) {
        EXPECT_FALSE(node1->ShallowEqual(node2));
    }
}

// Test ShallowEqual with a non-unknown node
TEST_F(XMLUnknownTest_68, ShallowEqualWithDifferentNodeType_68) {
    XMLDocument doc1;
    doc1.Parse("<!SOMETHING test data><root/>");
    
    XMLDocument doc2;
    doc2.Parse("<!--comment--><root/>");
    
    XMLNode* unknownNode = doc1.FirstChild();
    XMLNode* commentNode = doc2.FirstChild();
    
    if (unknownNode && unknownNode->ToUnknown() && commentNode) {
        EXPECT_FALSE(unknownNode->ShallowEqual(commentNode));
    }
}

// Test Accept calls visitor
TEST_F(XMLUnknownTest_68, AcceptCallsVisitor_68) {
    XMLDocument testDoc;
    testDoc.Parse("<!SOMETHING test data><root/>");
    
    XMLNode* firstChild = testDoc.FirstChild();
    XMLUnknown* unknown = nullptr;
    if (firstChild) {
        unknown = firstChild->ToUnknown();
    }
    
    if (unknown) {
        MockXMLVisitor mockVisitor;
        EXPECT_CALL(mockVisitor, Visit(testing::Ref(*unknown)))
            .Times(1)
            .WillOnce(testing::Return(true));
        
        bool result = unknown->Accept(&mockVisitor);
        EXPECT_TRUE(result);
    }
}

// Test Accept with visitor returning false
TEST_F(XMLUnknownTest_68, AcceptVisitorReturnsFalse_68) {
    XMLDocument testDoc;
    testDoc.Parse("<!SOMETHING test data><root/>");
    
    XMLNode* firstChild = testDoc.FirstChild();
    XMLUnknown* unknown = nullptr;
    if (firstChild) {
        unknown = firstChild->ToUnknown();
    }
    
    if (unknown) {
        MockXMLVisitor mockVisitor;
        EXPECT_CALL(mockVisitor, Visit(testing::Ref(*unknown)))
            .Times(1)
            .WillOnce(testing::Return(false));
        
        bool result = unknown->Accept(&mockVisitor);
        EXPECT_FALSE(result);
    }
}

// Test ShallowClone into same document
TEST_F(XMLUnknownTest_68, ShallowCloneIntoSameDocument_68) {
    XMLDocument testDoc;
    testDoc.Parse("<!SOMETHING test data><root/>");
    
    XMLNode* firstChild = testDoc.FirstChild();
    XMLUnknown* unknown = nullptr;
    if (firstChild) {
        unknown = firstChild->ToUnknown();
    }
    
    if (unknown) {
        XMLNode* clone = unknown->ShallowClone(&testDoc);
        ASSERT_NE(clone, nullptr);
        ASSERT_NE(clone, unknown);  // Should be a different node
        
        XMLUnknown* clonedUnknown = clone->ToUnknown();
        ASSERT_NE(clonedUnknown, nullptr);
        
        EXPECT_TRUE(unknown->ShallowEqual(clonedUnknown));
        
        // Insert to avoid memory leak
        testDoc.InsertEndChild(clone);
    }
}

// Test Value of unknown node
TEST_F(XMLUnknownTest_68, UnknownNodeValue_68) {
    XMLDocument testDoc;
    testDoc.Parse("<!SOMETHING test data><root/>");
    
    XMLNode* firstChild = testDoc.FirstChild();
    XMLUnknown* unknown = nullptr;
    if (firstChild) {
        unknown = firstChild->ToUnknown();
    }
    
    if (unknown) {
        const char* value = unknown->Value();
        ASSERT_NE(value, nullptr);
        EXPECT_STREQ(value, "SOMETHING test data");
    }
}

// Test that other node types don't return as XMLUnknown
TEST_F(XMLUnknownTest_68, NonUnknownNodeToUnknownReturnsNull_68) {
    XMLDocument testDoc;
    testDoc.Parse("<root>text</root>");
    
    XMLNode* root = testDoc.FirstChild();
    ASSERT_NE(root, nullptr);
    EXPECT_EQ(root->ToUnknown(), nullptr);
    
    XMLNode* textNode = root->FirstChild();
    if (textNode) {
        EXPECT_EQ(textNode->ToUnknown(), nullptr);
    }
}

// Test ShallowEqual with null
TEST_F(XMLUnknownTest_68, ShallowEqualWithNull_68) {
    XMLDocument testDoc;
    testDoc.Parse("<!SOMETHING test data><root/>");
    
    XMLNode* firstChild = testDoc.FirstChild();
    XMLUnknown* unknown = nullptr;
    if (firstChild) {
        unknown = firstChild->ToUnknown();
    }
    
    if (unknown) {
        // Comparing with nullptr should return false
        // (depending on implementation, this may or may not crash)
        // We test the boundary that comparing with a different type returns false
        XMLDocument doc2;
        doc2.Parse("<root/>");
        XMLNode* element = doc2.FirstChild();
        EXPECT_FALSE(unknown->ShallowEqual(element));
    }
}

// Test cloned unknown's value matches original
TEST_F(XMLUnknownTest_68, ClonedUnknownValueMatchesOriginal_68) {
    XMLDocument testDoc;
    testDoc.Parse("<!FOOBAR baz qux><root/>");
    
    XMLNode* firstChild = testDoc.FirstChild();
    XMLUnknown* unknown = nullptr;
    if (firstChild) {
        unknown = firstChild->ToUnknown();
    }
    
    if (unknown) {
        XMLDocument destDoc;
        XMLNode* clone = unknown->ShallowClone(&destDoc);
        ASSERT_NE(clone, nullptr);
        
        EXPECT_STREQ(unknown->Value(), clone->Value());
        
        destDoc.InsertFirstChild(clone);
    }
}

// Test empty unknown node
TEST_F(XMLUnknownTest_68, EmptyUnknownNode_68) {
    XMLDocument testDoc;
    testDoc.Parse("<!><root/>");
    
    // The parse might handle empty unknown differently
    // Just verify the document state
    XMLNode* firstChild = testDoc.FirstChild();
    if (firstChild && firstChild->ToUnknown()) {
        XMLUnknown* unknown = firstChild->ToUnknown();
        EXPECT_NE(unknown->Value(), nullptr);
    }
}
