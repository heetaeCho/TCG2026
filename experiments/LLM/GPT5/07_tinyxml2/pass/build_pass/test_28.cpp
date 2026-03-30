// File: ./TestProjects/tinyxml2/tests/XMLVisitor_28_test.cpp

#include <gtest/gtest.h>

#include "tinyxml2.h"

using namespace tinyxml2;

namespace {

class XMLVisitorTest_28 : public ::testing::Test {
protected:
    XMLDocument doc_;

    const XMLElement* ParseAndGetRoot(const char* xml) {
        const XMLError err = doc_.Parse(xml);
        EXPECT_EQ(err, XML_SUCCESS);
        const XMLElement* root = doc_.RootElement();
        EXPECT_NE(root, nullptr);
        return root;
    }
};

class ReturningFalseVisitor_28 : public XMLVisitor {
public:
    bool VisitEnter(const XMLElement& /*element*/, const XMLAttribute* /*firstAttribute*/) override {
        return false;
    }
};

}  // namespace

TEST_F(XMLVisitorTest_28, VisitEnter_DefaultReturnsTrue_NoAttributes_28) {
    const XMLElement* root = ParseAndGetRoot("<root/>");
    ASSERT_NE(root, nullptr);

    XMLVisitor visitor;
    EXPECT_TRUE(visitor.VisitEnter(*root, nullptr));
}

TEST_F(XMLVisitorTest_28, VisitEnter_DefaultReturnsTrue_WithAttributesPointer_28) {
    const XMLElement* root = ParseAndGetRoot("<root a='1' b='2'/>");
    ASSERT_NE(root, nullptr);

    const XMLAttribute* firstAttr = root->FirstAttribute();
    ASSERT_NE(firstAttr, nullptr);  // Ensure we actually have an attribute to pass.

    XMLVisitor visitor;
    EXPECT_TRUE(visitor.VisitEnter(*root, firstAttr));
}

TEST_F(XMLVisitorTest_28, VisitEnter_VirtualDispatch_CallsDerivedOverride_28) {
    const XMLElement* root = ParseAndGetRoot("<root a='1'/>");
    ASSERT_NE(root, nullptr);

    const XMLAttribute* firstAttr = root->FirstAttribute();
    ASSERT_NE(firstAttr, nullptr);

    ReturningFalseVisitor_28 derived;
    XMLVisitor* asBase = &derived;

    // Verifies observable behavior via virtual dispatch through base pointer.
    EXPECT_FALSE(asBase->VisitEnter(*root, firstAttr));
}
