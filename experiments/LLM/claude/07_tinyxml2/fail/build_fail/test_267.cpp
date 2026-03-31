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

class XMLElementAcceptTest_267 : public ::testing::Test {
protected:
    XMLDocument doc;
};

// Test: Accept on element with no children, visitor enters and exits
TEST_F(XMLElementAcceptTest_267, AcceptNoChildren_VisitEnterAndExit_267) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertEndChild(elem);

    MockXMLVisitor visitor;
    EXPECT_CALL(visitor, VisitEnter(testing::Ref(*elem), _))
        .WillOnce(Return(true));
    EXPECT_CALL(visitor, VisitExit(testing::Ref(*elem)))
        .WillOnce(Return(true));

    bool result = elem->Accept(&visitor);
    EXPECT_TRUE(result);
}

// Test: Accept returns false when VisitExit returns false
TEST_F(XMLElementAcceptTest_267, AcceptReturnsFalseWhenVisitExitReturnsFalse_267) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertEndChild(elem);

    MockXMLVisitor visitor;
    EXPECT_CALL(visitor, VisitEnter(testing::Ref(*elem), _))
        .WillOnce(Return(true));
    EXPECT_CALL(visitor, VisitExit(testing::Ref(*elem)))
        .WillOnce(Return(false));

    bool result = elem->Accept(&visitor);
    EXPECT_FALSE(result);
}

// Test: Accept skips children when VisitEnter returns false
TEST_F(XMLElementAcceptTest_267, AcceptSkipsChildrenWhenVisitEnterReturnsFalse_267) {
    XMLElement* parent = doc.NewElement("parent");
    doc.InsertEndChild(parent);
    XMLElement* child = doc.NewElement("child");
    parent->InsertEndChild(child);

    MockXMLVisitor visitor;
    // VisitEnter for parent returns false — children should not be visited
    EXPECT_CALL(visitor, VisitEnter(testing::Ref(*parent), _))
        .WillOnce(Return(false));
    // Should NOT call VisitEnter on child
    EXPECT_CALL(visitor, VisitEnter(testing::Ref(*child), _))
        .Times(0);
    EXPECT_CALL(visitor, VisitExit(testing::Ref(*parent)))
        .WillOnce(Return(true));

    bool result = parent->Accept(&visitor);
    EXPECT_TRUE(result);
}

// Test: Accept visits all children when VisitEnter returns true
TEST_F(XMLElementAcceptTest_267, AcceptVisitsAllChildren_267) {
    XMLElement* parent = doc.NewElement("parent");
    doc.InsertEndChild(parent);
    XMLElement* child1 = doc.NewElement("child1");
    XMLElement* child2 = doc.NewElement("child2");
    parent->InsertEndChild(child1);
    parent->InsertEndChild(child2);

    MockXMLVisitor visitor;
    {
        InSequence seq;
        EXPECT_CALL(visitor, VisitEnter(testing::Ref(*parent), _))
            .WillOnce(Return(true));
        // child1
        EXPECT_CALL(visitor, VisitEnter(testing::Ref(*child1), _))
            .WillOnce(Return(true));
        EXPECT_CALL(visitor, VisitExit(testing::Ref(*child1)))
            .WillOnce(Return(true));
        // child2
        EXPECT_CALL(visitor, VisitEnter(testing::Ref(*child2), _))
            .WillOnce(Return(true));
        EXPECT_CALL(visitor, VisitExit(testing::Ref(*child2)))
            .WillOnce(Return(true));
        // parent exit
        EXPECT_CALL(visitor, VisitExit(testing::Ref(*parent)))
            .WillOnce(Return(true));
    }

    bool result = parent->Accept(&visitor);
    EXPECT_TRUE(result);
}

// Test: Accept stops visiting children when a child's Accept returns false
TEST_F(XMLElementAcceptTest_267, AcceptStopsOnChildAcceptFalse_267) {
    XMLElement* parent = doc.NewElement("parent");
    doc.InsertEndChild(parent);
    XMLElement* child1 = doc.NewElement("child1");
    XMLElement* child2 = doc.NewElement("child2");
    parent->InsertEndChild(child1);
    parent->InsertEndChild(child2);

    MockXMLVisitor visitor;
    {
        InSequence seq;
        EXPECT_CALL(visitor, VisitEnter(testing::Ref(*parent), _))
            .WillOnce(Return(true));
        // child1 — VisitExit returns false, so child1->Accept returns false
        EXPECT_CALL(visitor, VisitEnter(testing::Ref(*child1), _))
            .WillOnce(Return(true));
        EXPECT_CALL(visitor, VisitExit(testing::Ref(*child1)))
            .WillOnce(Return(false));
        // child2 should NOT be visited
        // parent exit still called
        EXPECT_CALL(visitor, VisitExit(testing::Ref(*parent)))
            .WillOnce(Return(true));
    }
    EXPECT_CALL(visitor, VisitEnter(testing::Ref(*child2), _))
        .Times(0);

    bool result = parent->Accept(&visitor);
    EXPECT_TRUE(result);
}

// Test: Accept with element that has attributes passes first attribute to VisitEnter
TEST_F(XMLElementAcceptTest_267, AcceptPassesFirstAttribute_267) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertEndChild(elem);
    elem->SetAttribute("attr1", "value1");
    elem->SetAttribute("attr2", "value2");

    const XMLAttribute* firstAttr = elem->FirstAttribute();
    ASSERT_NE(firstAttr, nullptr);

    MockXMLVisitor visitor;
    EXPECT_CALL(visitor, VisitEnter(testing::Ref(*elem), firstAttr))
        .WillOnce(Return(true));
    EXPECT_CALL(visitor, VisitExit(testing::Ref(*elem)))
        .WillOnce(Return(true));

    bool result = elem->Accept(&visitor);
    EXPECT_TRUE(result);
}

// Test: Accept with element that has no attributes passes null to VisitEnter
TEST_F(XMLElementAcceptTest_267, AcceptPassesNullWhenNoAttributes_267) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertEndChild(elem);

    ASSERT_EQ(elem->FirstAttribute(), nullptr);

    MockXMLVisitor visitor;
    EXPECT_CALL(visitor, VisitEnter(testing::Ref(*elem), nullptr))
        .WillOnce(Return(true));
    EXPECT_CALL(visitor, VisitExit(testing::Ref(*elem)))
        .WillOnce(Return(true));

    bool result = elem->Accept(&visitor);
    EXPECT_TRUE(result);
}

// Test: Accept with text child visits the text node
TEST_F(XMLElementAcceptTest_267, AcceptVisitsTextChild_267) {
    doc.Parse("<root>Hello</root>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);

    MockXMLVisitor visitor;
    EXPECT_CALL(visitor, VisitEnter(testing::Ref(*root), _))
        .WillOnce(Return(true));
    EXPECT_CALL(visitor, Visit(testing::An<const XMLText&>()))
        .WillOnce(Return(true));
    EXPECT_CALL(visitor, VisitExit(testing::Ref(*root)))
        .WillOnce(Return(true));

    bool result = root->Accept(&visitor);
    EXPECT_TRUE(result);
}

// Test: Accept with comment child visits the comment node
TEST_F(XMLElementAcceptTest_267, AcceptVisitsCommentChild_267) {
    doc.Parse("<root><!-- a comment --></root>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);

    MockXMLVisitor visitor;
    EXPECT_CALL(visitor, VisitEnter(testing::Ref(*root), _))
        .WillOnce(Return(true));
    EXPECT_CALL(visitor, Visit(testing::An<const XMLComment&>()))
        .WillOnce(Return(true));
    EXPECT_CALL(visitor, VisitExit(testing::Ref(*root)))
        .WillOnce(Return(true));

    bool result = root->Accept(&visitor);
    EXPECT_TRUE(result);
}

// Test: Accept with nested elements (deep hierarchy)
TEST_F(XMLElementAcceptTest_267, AcceptDeepNesting_267) {
    doc.Parse("<a><b><c/></b></a>");
    XMLElement* a = doc.RootElement();
    ASSERT_NE(a, nullptr);
    XMLElement* b = a->FirstChildElement("b");
    ASSERT_NE(b, nullptr);
    XMLElement* c = b->FirstChildElement("c");
    ASSERT_NE(c, nullptr);

    MockXMLVisitor visitor;
    {
        InSequence seq;
        EXPECT_CALL(visitor, VisitEnter(testing::Ref(*a), _)).WillOnce(Return(true));
        EXPECT_CALL(visitor, VisitEnter(testing::Ref(*b), _)).WillOnce(Return(true));
        EXPECT_CALL(visitor, VisitEnter(testing::Ref(*c), _)).WillOnce(Return(true));
        EXPECT_CALL(visitor, VisitExit(testing::Ref(*c))).WillOnce(Return(true));
        EXPECT_CALL(visitor, VisitExit(testing::Ref(*b))).WillOnce(Return(true));
        EXPECT_CALL(visitor, VisitExit(testing::Ref(*a))).WillOnce(Return(true));
    }

    bool result = a->Accept(&visitor);
    EXPECT_TRUE(result);
}

// Test: Accept stops iterating siblings when middle child returns false
TEST_F(XMLElementAcceptTest_267, AcceptStopsAtMiddleChild_267) {
    XMLElement* parent = doc.NewElement("parent");
    doc.InsertEndChild(parent);
    XMLElement* child1 = doc.NewElement("c1");
    XMLElement* child2 = doc.NewElement("c2");
    XMLElement* child3 = doc.NewElement("c3");
    parent->InsertEndChild(child1);
    parent->InsertEndChild(child2);
    parent->InsertEndChild(child3);

    MockXMLVisitor visitor;
    {
        InSequence seq;
        EXPECT_CALL(visitor, VisitEnter(testing::Ref(*parent), _)).WillOnce(Return(true));
        // child1 ok
        EXPECT_CALL(visitor, VisitEnter(testing::Ref(*child1), _)).WillOnce(Return(true));
        EXPECT_CALL(visitor, VisitExit(testing::Ref(*child1))).WillOnce(Return(true));
        // child2 fails
        EXPECT_CALL(visitor, VisitEnter(testing::Ref(*child2), _)).WillOnce(Return(true));
        EXPECT_CALL(visitor, VisitExit(testing::Ref(*child2))).WillOnce(Return(false));
        // child3 should NOT be visited
        // parent exit
        EXPECT_CALL(visitor, VisitExit(testing::Ref(*parent))).WillOnce(Return(true));
    }
    EXPECT_CALL(visitor, VisitEnter(testing::Ref(*child3), _)).Times(0);

    bool result = parent->Accept(&visitor);
    EXPECT_TRUE(result);
}

// Test: VisitExit result of parent is the return value of Accept
TEST_F(XMLElementAcceptTest_267, AcceptReturnValueIsVisitExitResult_267) {
    XMLElement* elem = doc.NewElement("elem");
    doc.InsertEndChild(elem);

    MockXMLVisitor visitor;
    EXPECT_CALL(visitor, VisitEnter(testing::Ref(*elem), _)).WillOnce(Return(true));
    EXPECT_CALL(visitor, VisitExit(testing::Ref(*elem))).WillOnce(Return(false));

    EXPECT_FALSE(elem->Accept(&visitor));
}

// Test: Accept with mixed children (element + text)
TEST_F(XMLElementAcceptTest_267, AcceptMixedChildren_267) {
    doc.Parse("<root>text<child/></root>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);

    MockXMLVisitor visitor;
    XMLElement* child = root->FirstChildElement("child");
    ASSERT_NE(child, nullptr);

    EXPECT_CALL(visitor, VisitEnter(testing::Ref(*root), _)).WillOnce(Return(true));
    EXPECT_CALL(visitor, Visit(testing::An<const XMLText&>())).WillOnce(Return(true));
    EXPECT_CALL(visitor, VisitEnter(testing::Ref(*child), _)).WillOnce(Return(true));
    EXPECT_CALL(visitor, VisitExit(testing::Ref(*child))).WillOnce(Return(true));
    EXPECT_CALL(visitor, VisitExit(testing::Ref(*root))).WillOnce(Return(true));

    bool result = root->Accept(&visitor);
    EXPECT_TRUE(result);
}

// Test: Accept stops at text child returning false
TEST_F(XMLElementAcceptTest_267, AcceptStopsWhenTextChildReturnsFalse_267) {
    doc.Parse("<root>text<child/></root>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    XMLElement* child = root->FirstChildElement("child");
    ASSERT_NE(child, nullptr);

    MockXMLVisitor visitor;
    EXPECT_CALL(visitor, VisitEnter(testing::Ref(*root), _)).WillOnce(Return(true));
    EXPECT_CALL(visitor, Visit(testing::An<const XMLText&>())).WillOnce(Return(false));
    // child should not be visited
    EXPECT_CALL(visitor, VisitEnter(testing::Ref(*child), _)).Times(0);
    EXPECT_CALL(visitor, VisitExit(testing::Ref(*root))).WillOnce(Return(true));

    bool result = root->Accept(&visitor);
    EXPECT_TRUE(result);
}
