// File: ./TestProjects/tinyxml2/xmlunknown_accept_test_208.cpp

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "tinyxml2.h"

using ::testing::Return;
using ::testing::StrictMock;

namespace tinyxml2 {

// XMLUnknown has a protected constructor, so we expose it via a small test subclass.
// This does NOT re-implement any production logic; it only makes construction possible.
class TestableXMLUnknown_208 final : public XMLUnknown {
public:
    explicit TestableXMLUnknown_208(XMLDocument* doc) : XMLUnknown(doc) {}
    ~TestableXMLUnknown_208() override = default;
};

class MockVisitor_208 : public XMLVisitor {
public:
    MOCK_METHOD(bool, Visit, (const XMLUnknown& unknown), (override));
};

class XMLUnknownAcceptTest_208 : public ::testing::Test {
protected:
    XMLDocument doc_;
    TestableXMLUnknown_208 unknown_{&doc_};
};

TEST_F(XMLUnknownAcceptTest_208, AcceptCallsVisitorVisitAndReturnsTrue_208) {
    StrictMock<MockVisitor_208> visitor;

    EXPECT_CALL(visitor, Visit(::testing::Ref(unknown_)))
        .WillOnce(Return(true));

    const bool result = unknown_.Accept(&visitor);
    EXPECT_TRUE(result);
}

TEST_F(XMLUnknownAcceptTest_208, AcceptCallsVisitorVisitAndReturnsFalse_208) {
    StrictMock<MockVisitor_208> visitor;

    EXPECT_CALL(visitor, Visit(::testing::Ref(unknown_)))
        .WillOnce(Return(false));

    const bool result = unknown_.Accept(&visitor);
    EXPECT_FALSE(result);
}

TEST_F(XMLUnknownAcceptTest_208, AcceptCanBeCalledMultipleTimesAndEachTimeVisits_208) {
    StrictMock<MockVisitor_208> visitor;

    EXPECT_CALL(visitor, Visit(::testing::Ref(unknown_)))
        .Times(2)
        .WillRepeatedly(Return(true));

    EXPECT_TRUE(unknown_.Accept(&visitor));
    EXPECT_TRUE(unknown_.Accept(&visitor));
}

TEST_F(XMLUnknownAcceptTest_208, AcceptWithNullVisitorDeathIfSupported_208) {
    // The implementation asserts visitor != nullptr (via TIXMLASSERT(visitor)).
    // In builds where assertions are enabled, this should terminate; in others,
    // EXPECT_DEATH_IF_SUPPORTED will be skipped by the framework.
    EXPECT_DEATH_IF_SUPPORTED(
        {
            (void)unknown_.Accept(nullptr);
        },
        ".*");
}

}  // namespace tinyxml2
