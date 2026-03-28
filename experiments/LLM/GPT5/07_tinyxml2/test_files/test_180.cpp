// File: test_xmldocument_accept_180.cpp

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "tinyxml2.h"

using ::testing::_;
using ::testing::InSequence;
using ::testing::Return;
using ::testing::StrictMock;

namespace {

class MockVisitor_180 : public tinyxml2::XMLVisitor {
public:
    MOCK_METHOD(bool, VisitEnter, (const tinyxml2::XMLDocument& doc), (override));
    MOCK_METHOD(bool, VisitExit, (const tinyxml2::XMLDocument& doc), (override));

    MOCK_METHOD(bool, VisitEnter,
                (const tinyxml2::XMLElement& element, const tinyxml2::XMLAttribute* firstAttribute),
                (override));
    MOCK_METHOD(bool, VisitExit, (const tinyxml2::XMLElement& element), (override));

    // Keep other overloads available (not necessarily used in these tests)
    MOCK_METHOD(bool, Visit, (const tinyxml2::XMLDeclaration&), (override));
    MOCK_METHOD(bool, Visit, (const tinyxml2::XMLText&), (override));
    MOCK_METHOD(bool, Visit, (const tinyxml2::XMLComment&), (override));
    MOCK_METHOD(bool, Visit, (const tinyxml2::XMLUnknown&), (override));
};

class XMLDocumentAcceptTest_180 : public ::testing::Test {
protected:
    // Use defaults if available; otherwise pick common enum values from tinyxml2.
    // This matches typical tinyxml2 API: XMLDocument(bool, Whitespace)
    tinyxml2::XMLDocument doc_{true, tinyxml2::PRESERVE_WHITESPACE};

    void AddTwoTopLevelElements() {
        tinyxml2::XMLElement* e1 = doc_.NewElement("a");
        tinyxml2::XMLElement* e2 = doc_.NewElement("b");
        ASSERT_NE(e1, nullptr);
        ASSERT_NE(e2, nullptr);

        doc_.LinkEndChild(e1);
        doc_.LinkEndChild(e2);
    }
};

} // namespace

TEST_F(XMLDocumentAcceptTest_180, EmptyDocument_CallsEnterThenExitAndReturnsExit_180) {
    StrictMock<MockVisitor_180> visitor;

    {
        InSequence s;
        EXPECT_CALL(visitor, VisitEnter(::testing::Ref(doc_))).WillOnce(Return(true));
        EXPECT_CALL(visitor, VisitExit(::testing::Ref(doc_))).WillOnce(Return(true));
    }

    EXPECT_TRUE(doc_.Accept(&visitor));
}

TEST_F(XMLDocumentAcceptTest_180, VisitEnterFalse_SkipsChildrenButStillCallsExitAndReturnsExit_180) {
    AddTwoTopLevelElements();

    StrictMock<MockVisitor_180> visitor;

    {
        InSequence s;
        EXPECT_CALL(visitor, VisitEnter(::testing::Ref(doc_))).WillOnce(Return(false));
        // No element visits expected because XMLDocument::Accept only traverses children if VisitEnter(doc) is true.
        EXPECT_CALL(visitor, VisitExit(::testing::Ref(doc_))).WillOnce(Return(false));
    }

    EXPECT_FALSE(doc_.Accept(&visitor));
}

TEST_F(XMLDocumentAcceptTest_180, VisitEnterTrue_TraversesAllTopLevelChildrenAndReturnsExit_180) {
    AddTwoTopLevelElements();

    StrictMock<MockVisitor_180> visitor;

    {
        InSequence s;

        EXPECT_CALL(visitor, VisitEnter(::testing::Ref(doc_))).WillOnce(Return(true));

        // First element: enter/exit
        EXPECT_CALL(visitor, VisitEnter(::testing::A<const tinyxml2::XMLElement&>(), _))
            .WillOnce(Return(true));
        EXPECT_CALL(visitor, VisitExit(::testing::A<const tinyxml2::XMLElement&>()))
            .WillOnce(Return(true));

        // Second element: enter/exit
        EXPECT_CALL(visitor, VisitEnter(::testing::A<const tinyxml2::XMLElement&>(), _))
            .WillOnce(Return(true));
        EXPECT_CALL(visitor, VisitExit(::testing::A<const tinyxml2::XMLElement&>()))
            .WillOnce(Return(true));

        // Document exit decides final return
        EXPECT_CALL(visitor, VisitExit(::testing::Ref(doc_))).WillOnce(Return(true));
    }

    EXPECT_TRUE(doc_.Accept(&visitor));
}

TEST_F(XMLDocumentAcceptTest_180, ChildAcceptReturnsFalse_StopsTraversingFurtherChildrenButStillCallsDocExit_180) {
    AddTwoTopLevelElements();

    StrictMock<MockVisitor_180> visitor;

    {
        InSequence s;

        EXPECT_CALL(visitor, VisitEnter(::testing::Ref(doc_))).WillOnce(Return(true));

        // Make the first element's Accept() evaluate to false by having its VisitExit return false.
        EXPECT_CALL(visitor, VisitEnter(::testing::A<const tinyxml2::XMLElement&>(), _))
            .WillOnce(Return(true));
        EXPECT_CALL(visitor, VisitExit(::testing::A<const tinyxml2::XMLElement&>()))
            .WillOnce(Return(false));

        // Because the first child's Accept returned false, traversal should stop:
        // no calls for the second element.
        EXPECT_CALL(visitor, VisitExit(::testing::Ref(doc_))).WillOnce(Return(true));
    }

    EXPECT_TRUE(doc_.Accept(&visitor)); // XMLDocument::Accept returns VisitExit(doc), not child status.
}

TEST_F(XMLDocumentAcceptTest_180, DocExitReturnValue_IsReturnedEvenIfChildrenTraverse_180) {
    AddTwoTopLevelElements();

    StrictMock<MockVisitor_180> visitor;

    {
        InSequence s;

        EXPECT_CALL(visitor, VisitEnter(::testing::Ref(doc_))).WillOnce(Return(true));

        EXPECT_CALL(visitor, VisitEnter(::testing::A<const tinyxml2::XMLElement&>(), _))
            .WillOnce(Return(true));
        EXPECT_CALL(visitor, VisitExit(::testing::A<const tinyxml2::XMLElement&>()))
            .WillOnce(Return(true));

        EXPECT_CALL(visitor, VisitEnter(::testing::A<const tinyxml2::XMLElement&>(), _))
            .WillOnce(Return(true));
        EXPECT_CALL(visitor, VisitExit(::testing::A<const tinyxml2::XMLElement&>()))
            .WillOnce(Return(true));

        // Force the overall return to be false
        EXPECT_CALL(visitor, VisitExit(::testing::Ref(doc_))).WillOnce(Return(false));
    }

    EXPECT_FALSE(doc_.Accept(&visitor));
}

#if GTEST_HAS_DEATH_TEST
TEST_F(XMLDocumentAcceptTest_180, NullVisitor_TriggersAssertionInDebugBuild_180) {
    // tinyxml2 uses TIXMLASSERT(visitor). In many builds, this aborts; in some release builds it may be compiled out.
    // This test is intentionally conservative: it only asserts death when assertions are active.
#if !defined(NDEBUG)
    EXPECT_DEATH({ (void)doc_.Accept(nullptr); }, ".*");
#else
    GTEST_SKIP() << "Assertions appear disabled (NDEBUG); null-visitor behavior may not death/abort in this build.";
#endif
}
#endif
