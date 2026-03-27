// File: test/emittermanip_test_12.cpp

#include <gtest/gtest.h>

// Include the header under test (adjust include path if your build uses a different root)
#include "yaml-cpp/emittermanip.h"

namespace {

TEST(EmitterManipTest_12, IndentReturnsIndentManipulator_12) {
  // Normal operation: constructing an indent manipulator should be possible.
  auto m = YAML::Indent(2);
  (void)m;

  // If YAML::Indent is not properly declared/defined, this test won't compile/link.
  SUCCEED();
}

TEST(EmitterManipTest_12, IndentAcceptsZero_12) {
  // Boundary condition: zero indent should be accepted (constructor-call must be well-formed).
  auto m = YAML::Indent(0);
  (void)m;
  SUCCEED();
}

TEST(EmitterManipTest_12, IndentAcceptsNegative_12) {
  // Boundary/error-adjacent input: negative values should still be accepted at the interface level
  // (we only verify the call is well-formed; behavior is internal/black-box).
  auto m = YAML::Indent(-1);
  (void)m;
  SUCCEED();
}

TEST(EmitterManipTest_12, IndentAcceptsLargeValue_12) {
  // Boundary condition: large indent value should be accepted at the interface level.
  auto m = YAML::Indent(1000000);
  (void)m;
  SUCCEED();
}

TEST(EmitterManipTest_12, IndentCallableInConstexprLikeContext_12) {
  // Not asserting constexpr-ness; just verifying the returned type is usable in normal C++ contexts.
  const int v = 4;
  auto m = YAML::Indent(v);
  (void)m;
  SUCCEED();
}

}  // namespace
