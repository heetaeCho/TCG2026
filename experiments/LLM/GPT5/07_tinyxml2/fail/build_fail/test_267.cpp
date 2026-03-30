// TEST_ID: 267
// File: XMLElementAcceptTest_267.cpp

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "TestProjects/tinyxml2/tinyxml2.h"

using namespace tinyxml2;
using ::testing::_;
using ::testing::InSequence;
using ::testing::NiceMock;
using ::testing::Return;
using ::testing::StrictMock;

namespace {

class MockVisitor_267 : public XMLVisitor {
public:
    MOCK_METHOD(bool, VisitEnter, (const XMLElement& element, const XMLAttribute* firstAttribute), (override));
    MOCK_METHOD(bool, VisitExit, (const XMLElement& element), (override));

    // For non-element node types that may appear as children (e.g., XMLText, XMLComment, etc.).
    MOCK_METHOD(bool, Visit, (const XMLText&), (override));
    MOCK_METHOD(bool, Visit, (const XMLComment&), (override));
    MOCK_METHOD(bool, Visit, (const XMLDeclaration&), (override));
    MOCK_METHOD(bool, Visit, (const XMLUnknown&), (override));
    MOCK_METHOD(bool, VisitEnter, (const XMLDocument&), (override));
    MOCK_METHOD(bool, VisitExit, (const XMLDocument&), (override));
};

static XMLElement* ParseAndGetRoot_267(XMLDocument& doc, const char* xml, const char* rootName) {
    EXPECT_EQ(doc.Parse(xml), XML_SUCCESS);
    XMLElement* root = doc.FirstChildElement(rootName);
    EXPECT_NE(root, nullptr);
    return root;
}

}  // namespace

TEST(XMLElementAcceptTest_267, AcceptWithNullVisitorDies_267) {
    XMLDocument doc;
    XMLElement* root = ParseAndGetRoot_267(doc, "<root/>", "root");
    ASSERT_NE(root, nullptr);

    // Accept asserts visitor != nullptr. Death-test when supported.
    EXPECT_DEATH_IF_SUPPORTED({ (void)root->Accept(nullptr); }, "");
}

TEST(XMLElementAcceptTest_267, NoChildren_VisitEnterThenVisitExit_ReturnsVisitExit_267) {
    XMLDocument doc;
    XMLElement* root = ParseAndGetRoot_267(doc, "<root/>", "root");
    ASSERT_NE(root, nullptr);

    StrictMock<MockVisitor_267> visitor;

    {
        InSequence seq;
        EXPECT_CALL(visitor, VisitEnter(::testing::Ref(*root), _)).WillOnce(Return(true));
        EXPECT_CALL(visitor, VisitExit(::testing::Ref(*root))).WillOnce(Return(false));
    }

    EXPECT_FALSE(root->Accept(&visitor));
}

TEST(XMLElementAcceptTest_267, VisitEnterFalse_SkipsChildrenButStillCallsVisitExit_267) {
    XMLDocument doc;
    XMLElement* root = ParseAndGetRoot_267(doc, "<root><child/></root>", "root");
    ASSERT_NE(root, nullptr);
    ASSERT_NE(root->FirstChildElement("child"), nullptr);

    StrictMock<MockVisitor_267> visitor;

    EXPECT_CALL(visitor, VisitEnter(::testing::Ref(*root), _)).WillOnce(Return(false));
    EXPECT_CALL(visitor, VisitExit(::testing::Ref(*root))).WillOnce(Return(true));

    // Child should not be visited at all when VisitEnter(root, ...) returns false.
    EXPECT_CALL(visitor, VisitEnter(::testing::Ref(*root->FirstChildElement("child")), _)).Times(0);
    EXPECT_CALL(visitor, VisitExit(::testing::Ref(*root->FirstChildElement("child")))).Times(0);

    EXPECT_TRUE(root->Accept(&visitor));
}

TEST(XMLElementAcceptTest_267, VisitEnterReceivesFirstAttributePointer_267) {
    XMLDocument doc;
    XMLElement* root = ParseAndGetRoot_267(doc, "<root/>", "root");
    ASSERT_NE(root, nullptr);

    root->SetAttribute("a", "1");
    const XMLAttribute* expectedFirst = root->FirstAttribute();
    ASSERT_NE(expectedFirst, nullptr);

    StrictMock<MockVisitor_267> visitor;

    EXPECT_CALL(visitor, VisitEnter(::testing::Ref(*root), expectedFirst)).WillOnce(Return(true));
    EXPECT_CALL(visitor, VisitExit(::testing::Ref(*root))).WillOnce(Return(true));

    EXPECT_TRUE(root->Accept(&visitor));
}

TEST(XMLElementAcceptTest_267, TraversesChildrenInOrder_WhenVisitEnterTrue_267) {
    XMLDocument doc;
    XMLElement* root = ParseAndGetRoot_267(
        doc,
        "<root>"
        "  <a/>"
        "  <b/>"
        "</root>",
        "root");
    ASSERT_NE(root, nullptr);

    XMLElement* a = root->FirstChildElement("a");
    ASSERT_NE(a, nullptr);
    XMLElement* b = root->FirstChildElement("b");
    ASSERT_NE(b, nullptr);
    ASSERT_NE(a->NextSiblingElement("b"), nullptr);

    StrictMock<MockVisitor_267> visitor;

    {
        InSequence seq;
        EXPECT_CALL(visitor, VisitEnter(::testing::Ref(*root), _)).WillOnce(Return(true));

        EXPECT_CALL(visitor, VisitEnter(::testing::Ref(*a), _)).WillOnce(Return(true));
        EXPECT_CALL(visitor, VisitExit(::testing::Ref(*a))).WillOnce(Return(true));

        EXPECT_CALL(visitor, VisitEnter(::testing::Ref(*b), _)).WillOnce(Return(true));
        EXPECT_CALL(visitor, VisitExit(::testing::Ref(*b))).WillOnce(Return(true));

        EXPECT_CALL(visitor, VisitExit(::testing::Ref(*root))).WillOnce(Return(true));
    }

    EXPECT_TRUE(root->Accept(&visitor));
}

TEST(XMLElementAcceptTest_267, StopsVisitingSiblingsWhenAChildAcceptReturnsFalse_ButStillCallsVisitExitOnParent_267) {
    XMLDocument doc;
    XMLElement* root = ParseAndGetRoot_267(
        doc,
        "<root>"
        "  <a/>"
        "  <b/>"
        "  <c/>"
        "</root>",
        "root");
    ASSERT_NE(root, nullptr);

    XMLElement* a = root->FirstChildElement("a");
    XMLElement* b = root->FirstChildElement("b");
    XMLElement* c = root->FirstChildElement("c");
    ASSERT_NE(a, nullptr);
    ASSERT_NE(b, nullptr);
    ASSERT_NE(c, nullptr);

    StrictMock<MockVisitor_267> visitor;

    {
        InSequence seq;

        EXPECT_CALL(visitor, VisitEnter(::testing::Ref(*root), _)).WillOnce(Return(true));

        EXPECT_CALL(visitor, VisitEnter(::testing::Ref(*a), _)).WillOnce(Return(true));
        EXPECT_CALL(visitor, VisitExit(::testing::Ref(*a))).WillOnce(Return(true));

        // Make child <b> fail by returning false on VisitExit(b).
        EXPECT_CALL(visitor, VisitEnter(::testing::Ref(*b), _)).WillOnce(Return(true));
        EXPECT_CALL(visitor, VisitExit(::testing::Ref(*b))).WillOnce(Return(false));

        // Because <b>'s Accept returns false, parent loop breaks: <c> must not be visited.
        EXPECT_CALL(visitor, VisitEnter(::testing::Ref(*c), _)).Times(0);
        EXPECT_CALL(visitor, VisitExit(::testing::Ref(*c))).Times(0);

        // Parent VisitExit is still called and defines overall result.
        EXPECT_CALL(visitor, VisitExit(::testing::Ref(*root))).WillOnce(Return(true));
    }

    EXPECT_TRUE(root->Accept(&visitor));
}

TEST(XMLElementAcceptTest_267, MixedChildren_TextNodeVisitCanShortCircuitTraversal_267) {
    XMLDocument doc;
    XMLElement* root = ParseAndGetRoot_267(
        doc,
        "<root>"
        "  <a/>"
        "  hello"
        "  <b/>"
        "</root>",
        "root");
    ASSERT_NE(root, nullptr);

    XMLElement* a = root->FirstChildElement("a");
    XMLElement* b = root->FirstChildElement("b");
    ASSERT_NE(a, nullptr);
    ASSERT_NE(b, nullptr);

    // There should be a text node between <a/> and <b/>.
    const XMLNode* afterA = a->NextSibling();
    ASSERT_NE(afterA, nullptr);
    ASSERT_NE(afterA->ToText(), nullptr);

    StrictMock<MockVisitor_267> visitor;

    {
        InSequence seq;

        EXPECT_CALL(visitor, VisitEnter(::testing::Ref(*root), _)).WillOnce(Return(true));

        EXPECT_CALL(visitor, VisitEnter(::testing::Ref(*a), _)).WillOnce(Return(true));
        EXPECT_CALL(visitor, VisitExit(::testing::Ref(*a))).WillOnce(Return(true));

        // Fail on visiting the text node.
        EXPECT_CALL(visitor, Visit(::testing::Ref(*afterA->ToText()))).WillOnce(Return(false));

        // Since text Accept returns false, traversal stops; <b/> is not visited.
        EXPECT_CALL(visitor, VisitEnter(::testing::Ref(*b), _)).Times(0);
        EXPECT_CALL(visitor, VisitExit(::testing::Ref(*b))).Times(0);

        EXPECT_CALL(visitor, VisitExit(::testing::Ref(*root))).WillOnce(Return(true));
    }

    EXPECT_TRUE(root->Accept(&visitor));
}
