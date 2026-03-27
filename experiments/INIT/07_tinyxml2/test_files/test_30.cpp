// TEST_ID: 30
#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "tinyxml2.h"

using namespace tinyxml2;
using ::testing::StrictMock;

namespace {

class MockXMLVisitor_30 : public XMLVisitor {
public:
  using XMLVisitor::Visit;  // keep other overloads visible (avoid hiding warnings)

  MOCK_METHOD(bool, Visit, (const XMLDeclaration& declaration), (override));
};

class XMLVisitorTest_30 : public ::testing::Test {
protected:
  XMLDocument doc;

  XMLDeclaration* NewDecl(const char* text) {
    // tinyxml2 creates declarations via the document factory.
    return doc.NewDeclaration(text);
  }
};

}  // namespace

TEST_F(XMLVisitorTest_30, DefaultVisitReturnsTrue_30) {
  XMLDeclaration* decl = NewDecl("xml version=\"1.0\" encoding=\"UTF-8\"");
  ASSERT_NE(decl, nullptr);

  XMLVisitor visitor;
  EXPECT_TRUE(visitor.Visit(*decl));
}

TEST_F(XMLVisitorTest_30, OverriddenVisitReturnPropagates_30) {
  XMLDeclaration* decl = NewDecl("xml version=\"1.0\"");
  ASSERT_NE(decl, nullptr);

  struct FalseVisitor_30 : public XMLVisitor {
    bool Visit(const XMLDeclaration&) override { return false; }
  } visitor;

  EXPECT_FALSE(visitor.Visit(*decl));
}

TEST_F(XMLVisitorTest_30, XMLDeclarationAcceptInvokesVisitor_30) {
  XMLDeclaration* decl = NewDecl("xml version=\"1.0\"");
  ASSERT_NE(decl, nullptr);

  StrictMock<MockXMLVisitor_30> visitor;
  EXPECT_CALL(visitor, Visit(::testing::Ref(*decl))).WillOnce(::testing::Return(true));

  EXPECT_TRUE(decl->Accept(&visitor));
}

TEST_F(XMLVisitorTest_30, XMLDeclarationAcceptReturnsFalseWhenVisitorReturnsFalse_30) {
  XMLDeclaration* decl = NewDecl("xml version=\"1.0\"");
  ASSERT_NE(decl, nullptr);

  StrictMock<MockXMLVisitor_30> visitor;
  EXPECT_CALL(visitor, Visit(::testing::Ref(*decl))).WillOnce(::testing::Return(false));

  EXPECT_FALSE(decl->Accept(&visitor));
}
