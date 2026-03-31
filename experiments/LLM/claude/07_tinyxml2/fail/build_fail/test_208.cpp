#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "tinyxml2.h"

using namespace tinyxml2;

// Mock visitor to test XMLUnknown::Accept
class MockXMLVisitor : public XMLVisitor {
public:
    MOCK_METHOD(bool, Visit, (const XMLUnknown& unknown), (override));
    MOCK_METHOD(bool, Visit, (const XMLDeclaration& declaration), (override));
    MOCK_METHOD(bool, Visit, (const XMLText& text), (override));
    MOCK_METHOD(bool, Visit, (const XMLComment& comment), (override));
    MOCK_METHOD(bool, VisitEnter, (const XMLDocument& doc), (override));
    MOCK_METHOD(bool, VisitExit, (const XMLDocument& doc), (override));
    MOCK_METHOD(bool, VisitEnter, (const XMLElement& element, const XMLAttribute* firstAttribute), (override));
    MOCK_METHOD(bool, VisitExit, (const XMLElement& element), (override));
};

class XMLUnknownTest_208 : public ::testing::Test {
protected:
    XMLDocument doc;
};

// Test that Accept calls visitor->Visit with the XMLUnknown node and returns true when visitor returns true
TEST_F(XMLUnknownTest_208, AcceptCallsVisitorVisitReturnsTrue_208) {
    // Parse a document containing an unknown node
    const char* xml = "<?xml version=\"1.0\"?><!DOCTYPE foo>";
    // We need to create an XMLUnknown node. We can do this by parsing XML with unknown constructs
    // or using the document's internal mechanisms.
    // TinyXML2 treats processing instructions like "<?target data?>" as declarations,
    // and "<!something>" as unknown nodes.
    
    XMLDocument parseDoc;
    // "![" constructs or DTD-like things become XMLUnknown
    const char* xmlWithUnknown = "<root><!something weird></root>";
    XMLError err = parseDoc.Parse(xmlWithUnknown);
    
    if (err == XML_SUCCESS) {
        XMLElement* root = parseDoc.FirstChildElement("root");
        ASSERT_NE(root, nullptr);
        XMLNode* child = root->FirstChild();
        ASSERT_NE(child, nullptr);
        XMLUnknown* unknown = child->ToUnknown();
        if (unknown != nullptr) {
            MockXMLVisitor mockVisitor;
            EXPECT_CALL(mockVisitor, Visit(::testing::Ref(*unknown)))
                .Times(1)
                .WillOnce(::testing::Return(true));
            
            bool result = unknown->Accept(&mockVisitor);
            EXPECT_TRUE(result);
        }
    }
}

// Test that Accept returns false when visitor->Visit returns false
TEST_F(XMLUnknownTest_208, AcceptReturnsFalseWhenVisitorReturnsFalse_208) {
    XMLDocument parseDoc;
    const char* xmlWithUnknown = "<root><!something weird></root>";
    XMLError err = parseDoc.Parse(xmlWithUnknown);
    
    if (err == XML_SUCCESS) {
        XMLElement* root = parseDoc.FirstChildElement("root");
        ASSERT_NE(root, nullptr);
        XMLNode* child = root->FirstChild();
        ASSERT_NE(child, nullptr);
        XMLUnknown* unknown = child->ToUnknown();
        if (unknown != nullptr) {
            MockXMLVisitor mockVisitor;
            EXPECT_CALL(mockVisitor, Visit(::testing::Ref(*unknown)))
                .Times(1)
                .WillOnce(::testing::Return(false));
            
            bool result = unknown->Accept(&mockVisitor);
            EXPECT_FALSE(result);
        }
    }
}

// Test ToUnknown returns the correct pointer
TEST_F(XMLUnknownTest_208, ToUnknownReturnsSelf_208) {
    XMLDocument parseDoc;
    const char* xmlWithUnknown = "<root><!something></root>";
    XMLError err = parseDoc.Parse(xmlWithUnknown);
    
    if (err == XML_SUCCESS) {
        XMLElement* root = parseDoc.FirstChildElement("root");
        ASSERT_NE(root, nullptr);
        XMLNode* child = root->FirstChild();
        ASSERT_NE(child, nullptr);
        XMLUnknown* unknown = child->ToUnknown();
        // If it's an unknown node, ToUnknown should return non-null and point to itself
        if (unknown != nullptr) {
            EXPECT_EQ(static_cast<XMLNode*>(unknown), child);
        }
    }
}

// Test ShallowClone creates a copy in another document
TEST_F(XMLUnknownTest_208, ShallowCloneCreatesClone_208) {
    XMLDocument parseDoc;
    const char* xmlWithUnknown = "<root><!something></root>";
    XMLError err = parseDoc.Parse(xmlWithUnknown);
    ASSERT_EQ(err, XML_SUCCESS);
    
    XMLElement* root = parseDoc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    XMLNode* child = root->FirstChild();
    ASSERT_NE(child, nullptr);
    XMLUnknown* unknown = child->ToUnknown();
    
    if (unknown != nullptr) {
        XMLDocument targetDoc;
        XMLNode* cloned = unknown->ShallowClone(&targetDoc);
        ASSERT_NE(cloned, nullptr);
        
        XMLUnknown* clonedUnknown = cloned->ToUnknown();
        EXPECT_NE(clonedUnknown, nullptr);
        
        // The cloned node should be shallow-equal to the original
        EXPECT_TRUE(unknown->ShallowEqual(clonedUnknown));
        
        // Clean up: the cloned node belongs to targetDoc
        targetDoc.DeleteNode(cloned);
    }
}

// Test ShallowEqual with same content returns true
TEST_F(XMLUnknownTest_208, ShallowEqualSameContentReturnsTrue_208) {
    XMLDocument doc1;
    const char* xml1 = "<root><!something></root>";
    ASSERT_EQ(doc1.Parse(xml1), XML_SUCCESS);
    
    XMLDocument doc2;
    const char* xml2 = "<root><!something></root>";
    ASSERT_EQ(doc2.Parse(xml2), XML_SUCCESS);
    
    XMLElement* root1 = doc1.FirstChildElement("root");
    XMLElement* root2 = doc2.FirstChildElement("root");
    ASSERT_NE(root1, nullptr);
    ASSERT_NE(root2, nullptr);
    
    XMLNode* child1 = root1->FirstChild();
    XMLNode* child2 = root2->FirstChild();
    
    if (child1 && child2 && child1->ToUnknown() && child2->ToUnknown()) {
        EXPECT_TRUE(child1->ToUnknown()->ShallowEqual(child2->ToUnknown()));
    }
}

// Test ShallowEqual with different content returns false
TEST_F(XMLUnknownTest_208, ShallowEqualDifferentContentReturnsFalse_208) {
    XMLDocument doc1;
    const char* xml1 = "<root><!something></root>";
    ASSERT_EQ(doc1.Parse(xml1), XML_SUCCESS);
    
    XMLDocument doc2;
    const char* xml2 = "<root><!other></root>";
    ASSERT_EQ(doc2.Parse(xml2), XML_SUCCESS);
    
    XMLElement* root1 = doc1.FirstChildElement("root");
    XMLElement* root2 = doc2.FirstChildElement("root");
    ASSERT_NE(root1, nullptr);
    ASSERT_NE(root2, nullptr);
    
    XMLNode* child1 = root1->FirstChild();
    XMLNode* child2 = root2->FirstChild();
    
    if (child1 && child2 && child1->ToUnknown() && child2->ToUnknown()) {
        EXPECT_FALSE(child1->ToUnknown()->ShallowEqual(child2->ToUnknown()));
    }
}

// Test ShallowEqual with a non-XMLUnknown node returns false
TEST_F(XMLUnknownTest_208, ShallowEqualWithDifferentNodeTypeReturnsFalse_208) {
    XMLDocument parseDoc;
    const char* xml = "<root><!something><!-- comment --></root>";
    ASSERT_EQ(parseDoc.Parse(xml), XML_SUCCESS);
    
    XMLElement* root = parseDoc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    
    XMLNode* firstChild = root->FirstChild();
    XMLNode* secondChild = firstChild ? firstChild->NextSibling() : nullptr;
    
    if (firstChild && firstChild->ToUnknown() && secondChild) {
        // Comparing XMLUnknown with XMLComment should return false
        EXPECT_FALSE(firstChild->ToUnknown()->ShallowEqual(secondChild));
    }
}

// Test Accept is called exactly once per visitor invocation
TEST_F(XMLUnknownTest_208, AcceptVisitorCalledExactlyOnce_208) {
    XMLDocument parseDoc;
    const char* xmlWithUnknown = "<root><!test data here></root>";
    XMLError err = parseDoc.Parse(xmlWithUnknown);
    
    if (err == XML_SUCCESS) {
        XMLElement* root = parseDoc.FirstChildElement("root");
        ASSERT_NE(root, nullptr);
        XMLNode* child = root->FirstChild();
        ASSERT_NE(child, nullptr);
        XMLUnknown* unknown = child->ToUnknown();
        
        if (unknown != nullptr) {
            MockXMLVisitor mockVisitor;
            EXPECT_CALL(mockVisitor, Visit(::testing::An<const XMLUnknown&>()))
                .Times(1)
                .WillOnce(::testing::Return(true));
            
            unknown->Accept(&mockVisitor);
        }
    }
}

// Test that ShallowClone to the same document works
TEST_F(XMLUnknownTest_208, ShallowCloneToSameDocument_208) {
    XMLDocument parseDoc;
    const char* xmlWithUnknown = "<root><!foobar></root>";
    ASSERT_EQ(parseDoc.Parse(xmlWithUnknown), XML_SUCCESS);
    
    XMLElement* root = parseDoc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    XMLNode* child = root->FirstChild();
    ASSERT_NE(child, nullptr);
    XMLUnknown* unknown = child->ToUnknown();
    
    if (unknown != nullptr) {
        XMLNode* cloned = unknown->ShallowClone(&parseDoc);
        ASSERT_NE(cloned, nullptr);
        ASSERT_NE(cloned, static_cast<XMLNode*>(unknown));
        
        XMLUnknown* clonedUnknown = cloned->ToUnknown();
        EXPECT_NE(clonedUnknown, nullptr);
        EXPECT_TRUE(unknown->ShallowEqual(clonedUnknown));
        
        parseDoc.DeleteNode(cloned);
    }
}

// Test that the document-level Accept traversal includes XMLUnknown
TEST_F(XMLUnknownTest_208, DocumentAcceptTraversesUnknown_208) {
    XMLDocument parseDoc;
    const char* xmlWithUnknown = "<!something weird>";
    XMLError err = parseDoc.Parse(xmlWithUnknown);
    
    if (err == XML_SUCCESS) {
        MockXMLVisitor mockVisitor;
        
        // Allow other visitor methods to be called
        ON_CALL(mockVisitor, VisitEnter(::testing::An<const XMLDocument&>()))
            .WillByDefault(::testing::Return(true));
        ON_CALL(mockVisitor, VisitExit(::testing::An<const XMLDocument&>()))
            .WillByDefault(::testing::Return(true));
        
        EXPECT_CALL(mockVisitor, Visit(::testing::An<const XMLUnknown&>()))
            .Times(::testing::AtLeast(1))
            .WillRepeatedly(::testing::Return(true));
        
        parseDoc.Accept(&mockVisitor);
    }
}
