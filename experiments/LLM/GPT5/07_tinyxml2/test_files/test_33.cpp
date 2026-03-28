// File: test_xmlvisitor_33.cpp

#include <gtest/gtest.h>

#include "TestProjects/tinyxml2/tinyxml2.h"

// The provided partial header references tinyxml2::XMLUnknown but doesn't define it.
// For this unit-test TU, provide a minimal definition so we can create an instance
// to pass by reference. If the real codebase already defines XMLUnknown, this test
// file should be compiled against that real header instead of the partial one.
namespace tinyxml2 {
class XMLUnknown {};
}  // namespace tinyxml2

namespace {

class XMLVisitorTest_33 : public ::testing::Test {};

TEST_F(XMLVisitorTest_33, DefaultVisitUnknownReturnsTrue_33) {
  tinyxml2::XMLVisitor v;
  tinyxml2::XMLUnknown unknown;

  EXPECT_TRUE(v.Visit(unknown));
}

class FalseReturningVisitor_33 : public tinyxml2::XMLVisitor {
 public:
  bool Visit(const tinyxml2::XMLUnknown& /*unknown*/) override { return false; }
};

TEST_F(XMLVisitorTest_33, OverriddenVisitCanReturnFalse_33) {
  FalseReturningVisitor_33 v;
  tinyxml2::XMLUnknown unknown;

  EXPECT_FALSE(v.Visit(unknown));
}

TEST_F(XMLVisitorTest_33, VirtualDispatchCallsDerivedOverrideThroughBasePtr_33) {
  FalseReturningVisitor_33 derived;
  tinyxml2::XMLVisitor* base_ptr = &derived;
  tinyxml2::XMLUnknown unknown;

  EXPECT_FALSE(base_ptr->Visit(unknown));
}

}  // namespace
