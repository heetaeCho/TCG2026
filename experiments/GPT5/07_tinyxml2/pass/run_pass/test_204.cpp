// TEST_ID: 204
#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "tinyxml2.h"

using ::testing::Return;
using ::testing::Truly;

namespace tinyxml2 {
namespace {

class MockVisitor_204 : public XMLVisitor {
public:
    MOCK_METHOD(bool, Visit, (const XMLDeclaration& declaration), (override));
};

// SFINAE helper to support both XMLDocument::NewDeclaration() and XMLDocument::NewDeclaration(const char*)
static XMLDeclaration* NewDecl_204(XMLDocument& doc, int) {
    return doc.NewDeclaration();
}
static XMLDeclaration* NewDecl_204(XMLDocument& doc, long) {
    return doc.NewDeclaration("");
}
static XMLDeclaration* MakeDeclaration_204(XMLDocument& doc) {
    return NewDecl_204(doc, 0);
}

class XMLDeclarationAcceptTest_204 : public ::testing::Test {
protected:
    XMLDocument doc_;
    XMLDeclaration* decl_ = nullptr;

    void SetUp() override {
        decl_ = MakeDeclaration_204(doc_);
        ASSERT_NE(decl_, nullptr);
    }
};

TEST_F(XMLDeclarationAcceptTest_204, AcceptCallsVisitAndReturnsTrue_204) {
    MockVisitor_204 visitor;

    EXPECT_CALL(visitor, Visit(Truly([&](const XMLDeclaration& d) {
        return &d == decl_;
    }))).WillOnce(Return(true));

    EXPECT_TRUE(decl_->Accept(&visitor));
}

TEST_F(XMLDeclarationAcceptTest_204, AcceptCallsVisitAndReturnsFalse_204) {
    MockVisitor_204 visitor;

    EXPECT_CALL(visitor, Visit(Truly([&](const XMLDeclaration& d) {
        return &d == decl_;
    }))).WillOnce(Return(false));

    EXPECT_FALSE(decl_->Accept(&visitor));
}

TEST_F(XMLDeclarationAcceptTest_204, AcceptCanBeCalledMultipleTimesAndDelegatesEachTime_204) {
    MockVisitor_204 visitor;

    EXPECT_CALL(visitor, Visit(Truly([&](const XMLDeclaration& d) {
        return &d == decl_;
    })))
        .Times(2)
        .WillRepeatedly(Return(true));

    EXPECT_TRUE(decl_->Accept(&visitor));
    EXPECT_TRUE(decl_->Accept(&visitor));
}

TEST_F(XMLDeclarationAcceptTest_204, AcceptWithNullVisitorDiesInDebugBuilds_204) {
#if GTEST_HAS_DEATH_TEST
    // TIXMLASSERT(visitor) is typically active in debug builds (assert enabled).
    // In release builds, the assert may be compiled out, so we skip rather than assume behavior.
    #if !defined(NDEBUG)
        ASSERT_DEATH({ (void)decl_->Accept(nullptr); }, "");
    #else
        GTEST_SKIP() << "Death behavior is only expected when assertions are enabled (debug builds).";
    #endif
#else
    GTEST_SKIP() << "Death tests are not supported on this platform/toolchain.";
#endif
}

}  // namespace
}  // namespace tinyxml2
