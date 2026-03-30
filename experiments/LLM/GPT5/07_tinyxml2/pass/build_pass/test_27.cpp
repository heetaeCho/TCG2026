// File: xmlvisitor_unittest_27.cpp

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "tinyxml2.h"

using ::testing::_;
using ::testing::Return;
using ::testing::StrictMock;

namespace {

class MockXMLVisitor_27 : public tinyxml2::XMLVisitor {
public:
  MOCK_METHOD(bool, VisitExit, (const tinyxml2::XMLDocument& doc), (override));
};

}  // namespace

TEST(XMLVisitorTest_27, DefaultVisitExitReturnsTrue_27) {
  tinyxml2::XMLVisitor visitor;
  tinyxml2::XMLDocument doc;

  EXPECT_TRUE(visitor.VisitExit(doc));
}

TEST(XMLVisitorTest_27, DefaultVisitExitWorksWithConstDocument_27) {
  tinyxml2::XMLVisitor visitor;
  const tinyxml2::XMLDocument doc;

  EXPECT_TRUE(visitor.VisitExit(doc));
}

TEST(XMLVisitorTest_27, VisitExitIsVirtualAndDispatchesToOverride_27) {
  StrictMock<MockXMLVisitor_27> mockVisitor;
  tinyxml2::XMLDocument doc;

  EXPECT_CALL(mockVisitor, VisitExit(_)).WillOnce(Return(false));

  tinyxml2::XMLVisitor& baseRef = mockVisitor;
  EXPECT_FALSE(baseRef.VisitExit(doc));
}

TEST(XMLVisitorTest_27, VisitExitCanBeCalledThroughPointer_27) {
  StrictMock<MockXMLVisitor_27> mockVisitor;
  tinyxml2::XMLDocument doc;

  EXPECT_CALL(mockVisitor, VisitExit(_)).WillOnce(Return(true));

  tinyxml2::XMLVisitor* basePtr = &mockVisitor;
  EXPECT_TRUE(basePtr->VisitExit(doc));
}
