// TEST_ID: 563
#include <gtest/gtest.h>

#include <string>

// Prefer the project’s public header if available.
// If your build uses a different include path, adjust accordingly.
#include "yaml-cpp/node/node.h"

namespace {

class NodeAssignTest_563 : public ::testing::Test {
 protected:
  YAML::Node node_;
};

TEST_F(NodeAssignTest_563, ReturnsSelfReference_563) {
  YAML::Node& ret = (node_ = 123);
  EXPECT_EQ(&ret, &node_);
}

TEST_F(NodeAssignTest_563, IntAssignmentObservableViaAs_563) {
  node_ = 42;

  EXPECT_TRUE(node_.IsDefined());
  EXPECT_EQ(node_.as<int>(), 42);
}

TEST_F(NodeAssignTest_563, DoubleAssignmentObservableViaAs_563) {
  node_ = 3.14159;

  EXPECT_TRUE(node_.IsDefined());
  EXPECT_DOUBLE_EQ(node_.as<double>(), 3.14159);
}

TEST_F(NodeAssignTest_563, BoolAssignmentObservableViaAs_563) {
  node_ = true;

  EXPECT_TRUE(node_.IsDefined());
  EXPECT_EQ(node_.as<bool>(), true);
}

TEST_F(NodeAssignTest_563, StdStringAssignmentObservableViaScalarAndAs_563) {
  const std::string s = "hello";
  node_ = s;

  EXPECT_TRUE(node_.IsDefined());
  EXPECT_EQ(node_.as<std::string>(), "hello");
  // Scalar() should be meaningful for scalar assignments.
  EXPECT_EQ(node_.Scalar(), "hello");
}

TEST_F(NodeAssignTest_563, ConstCharPointerAssignmentObservableViaScalarAndAs_563) {
  node_ = "world";

  EXPECT_TRUE(node_.IsDefined());
  EXPECT_EQ(node_.as<std::string>(), "world");
  EXPECT_EQ(node_.Scalar(), "world");
}

TEST_F(NodeAssignTest_563, NonConstCharPointerAssignmentObservableViaScalarAndAs_563) {
  char buf[] = "mutable";
  char* p = buf;

  node_ = p;

  EXPECT_TRUE(node_.IsDefined());
  EXPECT_EQ(node_.as<std::string>(), "mutable");
  EXPECT_EQ(node_.Scalar(), "mutable");
}

TEST_F(NodeAssignTest_563, ChainedAssignmentUsesReturnedReference_563) {
  // Verifies operator= returns Node& and can be used in a chain.
  (node_ = 1) = 2;
  EXPECT_EQ(node_.as<int>(), 2);
}

TEST_F(NodeAssignTest_563, ReassignmentOverwritesPreviousValue_563) {
  node_ = 10;
  EXPECT_EQ(node_.as<int>(), 10);

  node_ = 99;
  EXPECT_EQ(node_.as<int>(), 99);
}

TEST_F(NodeAssignTest_563, Boundary_EmptyStringAssignment_563) {
  node_ = std::string{};

  EXPECT_TRUE(node_.IsDefined());
  EXPECT_EQ(node_.as<std::string>(), "");
  EXPECT_EQ(node_.Scalar(), "");
}

TEST_F(NodeAssignTest_563, Boundary_LongStringAssignment_563) {
  const std::string long_str(4096, 'x');
  node_ = long_str;

  EXPECT_TRUE(node_.IsDefined());
  EXPECT_EQ(node_.as<std::string>(), long_str);
  EXPECT_EQ(node_.Scalar(), long_str);
}

TEST_F(NodeAssignTest_563, ErrorCase_AsWrongTypeMayThrowOrFallback_563) {
  node_ = "not_an_int";

  // The interface provides both as<T>() and as<T>(fallback).
  // We avoid assuming whether as<int>() throws; instead we assert the fallback path is usable.
  EXPECT_EQ(node_.as<int>(-7), -7);
}

}  // namespace