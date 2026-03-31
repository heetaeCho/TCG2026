#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "tinyxml2.h"

using namespace tinyxml2;
using ::testing::_;
using ::testing::Return;
using ::testing::Sequence;
using ::testing::InSequence;

// Mock XMLVisitor for testing Accept behavior
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

class XMLDocumentAcceptTest_180 : public ::testing::Test {
protected:
    void SetUp() override {
    }
    void TearDown() override {
    }
};

// Test that Accept calls VisitEnter and VisitExit on an empty document
TEST_F(XMLDocumentAcceptTest_180, EmptyDocumentCallsVisitEnterAndVisitExit_180) {
    XMLDocument doc;
    MockXMLVisitor visitor;

    {
        InSequence seq;
        EXPECT_CALL(visitor, VisitEnter(testing::Ref(doc))).WillOnce(Return(true));
        EXPECT_CALL(visitor, VisitExit(testing::Ref(doc))).WillOnce(Return(true));
    }

    bool result = doc.Accept(&visitor);
    EXPECT_TRUE(result);
}

// Test that Accept returns false when VisitExit returns false
TEST_F(XMLDocumentAcceptTest_180, AcceptReturnsFalseWhenVisitExitReturnsFalse_180) {
    XMLDocument doc;
    MockXMLVisitor visitor;

    EXPECT_CALL(visitor, VisitEnter(testing::Ref(doc))).WillOnce(Return(true));
    EXPECT_CALL(visitor, VisitExit(testing::Ref(doc))).WillOnce(Return(false));

    bool result = doc.Accept(&visitor);
    EXPECT_FALSE(result);
}

// Test that Accept skips children when VisitEnter returns false
TEST_F(XMLDocumentAcceptTest_180, SkipsChildrenWhenVisitEnterReturnsFalse_180) {
    XMLDocument doc;
    doc.Parse("<root><child/></root>");
    ASSERT_FALSE(doc.Error());

    MockXMLVisitor visitor;

    // VisitEnter returns false, so children should not be visited
    EXPECT_CALL(visitor, VisitEnter(testing::Ref(doc))).WillOnce(Return(false));
    // No child visits expected
    EXPECT_CALL(visitor, VisitEnter(testing::An<const XMLElement&>(), _)).Times(0);
    EXPECT_CALL(visitor, VisitExit(testing::An<const XMLElement&>())).Times(0);
    EXPECT_CALL(visitor, VisitExit(testing::Ref(doc))).WillOnce(Return(true));

    bool result = doc.Accept(&visitor);
    EXPECT_TRUE(result);
}

// Test that Accept visits child elements of the document
TEST_F(XMLDocumentAcceptTest_180, VisitsChildElements_180) {
    XMLDocument doc;
    doc.Parse("<root/>");
    ASSERT_FALSE(doc.Error());

    MockXMLVisitor visitor;

    {
        InSequence seq;
        EXPECT_CALL(visitor, VisitEnter(testing::Ref(doc))).WillOnce(Return(true));
        EXPECT_CALL(visitor, VisitEnter(testing::An<const XMLElement&>(), _)).WillOnce(Return(true));
        EXPECT_CALL(visitor, VisitExit(testing::An<const XMLElement&>())).WillOnce(Return(true));
        EXPECT_CALL(visitor, VisitExit(testing::Ref(doc))).WillOnce(Return(true));
    }

    bool result = doc.Accept(&visitor);
    EXPECT_TRUE(result);
}

// Test that Accept stops visiting children when a child's Accept returns false
TEST_F(XMLDocumentAcceptTest_180, StopsVisitingChildrenOnFalseReturn_180) {
    XMLDocument doc;
    // Two top-level nodes: declaration + root element
    doc.Parse("<?xml version=\"1.0\"?><root/>");
    ASSERT_FALSE(doc.Error());

    MockXMLVisitor visitor;

    EXPECT_CALL(visitor, VisitEnter(testing::Ref(doc))).WillOnce(Return(true));
    // First child is the declaration - return false to stop iteration
    EXPECT_CALL(visitor, Visit(testing::An<const XMLDeclaration&>())).WillOnce(Return(false));
    // The root element should NOT be visited since iteration was stopped
    EXPECT_CALL(visitor, VisitEnter(testing::An<const XMLElement&>(), _)).Times(0);
    EXPECT_CALL(visitor, VisitExit(testing::Ref(doc))).WillOnce(Return(true));

    bool result = doc.Accept(&visitor);
    EXPECT_TRUE(result);
}

// Test Accept with a document containing nested elements
TEST_F(XMLDocumentAcceptTest_180, VisitsNestedElements_180) {
    XMLDocument doc;
    doc.Parse("<root><child><grandchild/></child></root>");
    ASSERT_FALSE(doc.Error());

    MockXMLVisitor visitor;

    {
        InSequence seq;
        EXPECT_CALL(visitor, VisitEnter(testing::Ref(doc))).WillOnce(Return(true));
        // root element enter
        EXPECT_CALL(visitor, VisitEnter(testing::An<const XMLElement&>(), _)).WillOnce(Return(true));
        // child element enter
        EXPECT_CALL(visitor, VisitEnter(testing::An<const XMLElement&>(), _)).WillOnce(Return(true));
        // grandchild element enter
        EXPECT_CALL(visitor, VisitEnter(testing::An<const XMLElement&>(), _)).WillOnce(Return(true));
        // grandchild element exit
        EXPECT_CALL(visitor, VisitExit(testing::An<const XMLElement&>())).WillOnce(Return(true));
        // child element exit
        EXPECT_CALL(visitor, VisitExit(testing::An<const XMLElement&>())).WillOnce(Return(true));
        // root element exit
        EXPECT_CALL(visitor, VisitExit(testing::An<const XMLElement&>())).WillOnce(Return(true));
        EXPECT_CALL(visitor, VisitExit(testing::Ref(doc))).WillOnce(Return(true));
    }

    bool result = doc.Accept(&visitor);
    EXPECT_TRUE(result);
}

// Test Accept with a document containing text content
TEST_F(XMLDocumentAcceptTest_180, VisitsTextContent_180) {
    XMLDocument doc;
    doc.Parse("<root>Hello World</root>");
    ASSERT_FALSE(doc.Error());

    MockXMLVisitor visitor;

    {
        InSequence seq;
        EXPECT_CALL(visitor, VisitEnter(testing::Ref(doc))).WillOnce(Return(true));
        EXPECT_CALL(visitor, VisitEnter(testing::An<const XMLElement&>(), _)).WillOnce(Return(true));
        EXPECT_CALL(visitor, Visit(testing::An<const XMLText&>())).WillOnce(Return(true));
        EXPECT_CALL(visitor, VisitExit(testing::An<const XMLElement&>())).WillOnce(Return(true));
        EXPECT_CALL(visitor, VisitExit(testing::Ref(doc))).WillOnce(Return(true));
    }

    bool result = doc.Accept(&visitor);
    EXPECT_TRUE(result);
}

// Test Accept with a document containing a comment
TEST_F(XMLDocumentAcceptTest_180, VisitsCommentNode_180) {
    XMLDocument doc;
    doc.Parse("<!-- This is a comment --><root/>");
    ASSERT_FALSE(doc.Error());

    MockXMLVisitor visitor;

    {
        InSequence seq;
        EXPECT_CALL(visitor, VisitEnter(testing::Ref(doc))).WillOnce(Return(true));
        EXPECT_CALL(visitor, Visit(testing::An<const XMLComment&>())).WillOnce(Return(true));
        EXPECT_CALL(visitor, VisitEnter(testing::An<const XMLElement&>(), _)).WillOnce(Return(true));
        EXPECT_CALL(visitor, VisitExit(testing::An<const XMLElement&>())).WillOnce(Return(true));
        EXPECT_CALL(visitor, VisitExit(testing::Ref(doc))).WillOnce(Return(true));
    }

    bool result = doc.Accept(&visitor);
    EXPECT_TRUE(result);
}

// Test Accept with multiple sibling elements at the root level (declaration + element)
TEST_F(XMLDocumentAcceptTest_180, VisitsMultipleTopLevelNodes_180) {
    XMLDocument doc;
    doc.Parse("<?xml version=\"1.0\"?><!-- comment --><root/>");
    ASSERT_FALSE(doc.Error());

    MockXMLVisitor visitor;

    {
        InSequence seq;
        EXPECT_CALL(visitor, VisitEnter(testing::Ref(doc))).WillOnce(Return(true));
        EXPECT_CALL(visitor, Visit(testing::An<const XMLDeclaration&>())).WillOnce(Return(true));
        EXPECT_CALL(visitor, Visit(testing::An<const XMLComment&>())).WillOnce(Return(true));
        EXPECT_CALL(visitor, VisitEnter(testing::An<const XMLElement&>(), _)).WillOnce(Return(true));
        EXPECT_CALL(visitor, VisitExit(testing::An<const XMLElement&>())).WillOnce(Return(true));
        EXPECT_CALL(visitor, VisitExit(testing::Ref(doc))).WillOnce(Return(true));
    }

    bool result = doc.Accept(&visitor);
    EXPECT_TRUE(result);
}

// Test Accept return value depends on VisitExit
TEST_F(XMLDocumentAcceptTest_180, ReturnValueDependsOnVisitExit_180) {
    XMLDocument doc;
    doc.Parse("<root/>");
    ASSERT_FALSE(doc.Error());

    MockXMLVisitor visitorTrue;
    EXPECT_CALL(visitorTrue, VisitEnter(testing::Ref(doc))).WillOnce(Return(true));
    EXPECT_CALL(visitorTrue, VisitEnter(testing::An<const XMLElement&>(), _)).WillOnce(Return(true));
    EXPECT_CALL(visitorTrue, VisitExit(testing::An<const XMLElement&>())).WillOnce(Return(true));
    EXPECT_CALL(visitorTrue, VisitExit(testing::Ref(doc))).WillOnce(Return(true));
    EXPECT_TRUE(doc.Accept(&visitorTrue));

    MockXMLVisitor visitorFalse;
    EXPECT_CALL(visitorFalse, VisitEnter(testing::Ref(doc))).WillOnce(Return(true));
    EXPECT_CALL(visitorFalse, VisitEnter(testing::An<const XMLElement&>(), _)).WillOnce(Return(true));
    EXPECT_CALL(visitorFalse, VisitExit(testing::An<const XMLElement&>())).WillOnce(Return(true));
    EXPECT_CALL(visitorFalse, VisitExit(testing::Ref(doc))).WillOnce(Return(false));
    EXPECT_FALSE(doc.Accept(&visitorFalse));
}

// Test that VisitEnter false skips children but VisitExit is still called
TEST_F(XMLDocumentAcceptTest_180, VisitEnterFalseSkipsChildrenButCallsVisitExit_180) {
    XMLDocument doc;
    doc.Parse("<root><a/><b/><c/></root>");
    ASSERT_FALSE(doc.Error());

    MockXMLVisitor visitor;

    EXPECT_CALL(visitor, VisitEnter(testing::Ref(doc))).WillOnce(Return(false));
    // No children should be visited
    EXPECT_CALL(visitor, VisitEnter(testing::An<const XMLElement&>(), _)).Times(0);
    EXPECT_CALL(visitor, VisitExit(testing::An<const XMLElement&>())).Times(0);
    EXPECT_CALL(visitor, VisitExit(testing::Ref(doc))).WillOnce(Return(true));

    bool result = doc.Accept(&visitor);
    EXPECT_TRUE(result);
}

// Test Accept on a document after Clear
TEST_F(XMLDocumentAcceptTest_180, AcceptAfterClear_180) {
    XMLDocument doc;
    doc.Parse("<root><child/></root>");
    ASSERT_FALSE(doc.Error());
    doc.Clear();

    MockXMLVisitor visitor;

    EXPECT_CALL(visitor, VisitEnter(testing::Ref(doc))).WillOnce(Return(true));
    // After clear, no children
    EXPECT_CALL(visitor, VisitEnter(testing::An<const XMLElement&>(), _)).Times(0);
    EXPECT_CALL(visitor, VisitExit(testing::Ref(doc))).WillOnce(Return(true));

    bool result = doc.Accept(&visitor);
    EXPECT_TRUE(result);
}

// Test that stopping at a middle child element works
TEST_F(XMLDocumentAcceptTest_180, StopsAtMiddleChildElement_180) {
    XMLDocument doc;
    doc.Parse("<root><a/><b/><c/></root>");
    ASSERT_FALSE(doc.Error());

    MockXMLVisitor visitor;

    {
        InSequence seq;
        EXPECT_CALL(visitor, VisitEnter(testing::Ref(doc))).WillOnce(Return(true));
        // root element enter
        EXPECT_CALL(visitor, VisitEnter(testing::An<const XMLElement&>(), _)).WillOnce(Return(true));
        // child <a/> enter - return true
        EXPECT_CALL(visitor, VisitEnter(testing::An<const XMLElement&>(), _)).WillOnce(Return(true));
        // child <a/> exit - return true
        EXPECT_CALL(visitor, VisitExit(testing::An<const XMLElement&>())).WillOnce(Return(true));
        // child <b/> enter - return true
        EXPECT_CALL(visitor, VisitEnter(testing::An<const XMLElement&>(), _)).WillOnce(Return(true));
        // child <b/> exit - return false to stop
        EXPECT_CALL(visitor, VisitExit(testing::An<const XMLElement&>())).WillOnce(Return(false));
        // root element exit - should still be called
        EXPECT_CALL(visitor, VisitExit(testing::An<const XMLElement&>())).WillOnce(Return(false));
        // Document VisitExit still called
        EXPECT_CALL(visitor, VisitExit(testing::Ref(doc))).WillOnce(Return(true));
    }

    bool result = doc.Accept(&visitor);
    EXPECT_TRUE(result);
}

// Test Accept with a document containing unknown nodes
TEST_F(XMLDocumentAcceptTest_180, VisitsUnknownNode_180) {
    XMLDocument doc;
    // Create document with unknown node programmatically
    XMLUnknown* unknown = doc.NewUnknown("something unknown");
    doc.InsertEndChild(unknown);

    MockXMLVisitor visitor;

    {
        InSequence seq;
        EXPECT_CALL(visitor, VisitEnter(testing::Ref(doc))).WillOnce(Return(true));
        EXPECT_CALL(visitor, Visit(testing::An<const XMLUnknown&>())).WillOnce(Return(true));
        EXPECT_CALL(visitor, VisitExit(testing::Ref(doc))).WillOnce(Return(true));
    }

    bool result = doc.Accept(&visitor);
    EXPECT_TRUE(result);
}

// Test Accept on document with only a declaration
TEST_F(XMLDocumentAcceptTest_180, VisitsDeclarationOnly_180) {
    XMLDocument doc;
    XMLDeclaration* decl = doc.NewDeclaration();
    doc.InsertEndChild(decl);

    MockXMLVisitor visitor;

    {
        InSequence seq;
        EXPECT_CALL(visitor, VisitEnter(testing::Ref(doc))).WillOnce(Return(true));
        EXPECT_CALL(visitor, Visit(testing::An<const XMLDeclaration&>())).WillOnce(Return(true));
        EXPECT_CALL(visitor, VisitExit(testing::Ref(doc))).WillOnce(Return(true));
    }

    bool result = doc.Accept(&visitor);
    EXPECT_TRUE(result);
}

// Test Accept with default-constructed empty document
TEST_F(XMLDocumentAcceptTest_180, DefaultConstructedDocument_180) {
    XMLDocument doc;
    MockXMLVisitor visitor;

    EXPECT_CALL(visitor, VisitEnter(testing::Ref(doc))).WillOnce(Return(true));
    EXPECT_CALL(visitor, VisitExit(testing::Ref(doc))).WillOnce(Return(true));

    bool result = doc.Accept(&visitor);
    EXPECT_TRUE(result);
}
