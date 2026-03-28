// File: TestProjects/tinyxml2/tests/XMLVisitor_26_test.cpp

#include <gtest/gtest.h>

#include "tinyxml2.h"

namespace {

class XMLVisitorTest_26 : public ::testing::Test {};

TEST_F(XMLVisitorTest_26, DefaultVisitEnterReturnsTrue_26) {
    tinyxml2::XMLVisitor v;
    tinyxml2::XMLDocument doc;

    EXPECT_TRUE(v.VisitEnter(doc));
}

TEST_F(XMLVisitorTest_26, DefaultVisitEnterWorksWithConstDocument_26) {
    tinyxml2::XMLVisitor v;
    const tinyxml2::XMLDocument doc;

    EXPECT_TRUE(v.VisitEnter(doc));
}

class FalseReturningVisitor_26 : public tinyxml2::XMLVisitor {
public:
    bool VisitEnter(const tinyxml2::XMLDocument& /*doc*/) override { return false; }
};

TEST_F(XMLVisitorTest_26, VisitEnterIsVirtualAndDispatchesToOverride_26) {
    FalseReturningVisitor_26 derived;
    tinyxml2::XMLVisitor* base = &derived;
    tinyxml2::XMLDocument doc;

    EXPECT_FALSE(base->VisitEnter(doc));
}

}  // namespace
