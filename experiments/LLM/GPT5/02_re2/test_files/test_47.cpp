// File: lazyre2_operator_arrow_test_47.cc
#include <gtest/gtest.h>
#include "re2/re2.h"  // Provides re2::LazyRE2 and re2::RE2

using re2::LazyRE2;
using re2::RE2;

class LazyRE2OperatorArrowTest_47 : public ::testing::Test {
protected:
  // Helper to make a LazyRE2 with a desired pattern via its public interface.
  static LazyRE2 MakeWithPattern(const char* pattern) {
    LazyRE2 lazy;
    // Use only public members / interface; no private access.
    lazy.pattern_ = pattern;
    return lazy;
  }
};

// Operator-> should forward to get() and return the exact same pointer.
TEST_F(LazyRE2OperatorArrowTest_47, OperatorArrowReturnsSamePointerAsGet_47) {
  auto lazy = MakeWithPattern("abc");
  RE2* via_arrow = lazy.operator->();
  RE2* via_get = lazy.get();
  ASSERT_NE(via_arrow, nullptr);
  EXPECT_EQ(via_arrow, via_get);
}

// Operator-> should allow member access on RE2 (observable behavior).
// Verify we can read the pattern string through the returned RE2*.
TEST_F(LazyRE2OperatorArrowTest_47, OperatorArrowAllowsMemberAccess_47) {
  const char* kPattern = "a|bc";
  auto lazy = MakeWithPattern(kPattern);
  RE2* re2_ptr = lazy.operator->();
  ASSERT_NE(re2_ptr, nullptr);
  EXPECT_EQ(re2_ptr->pattern(), std::string(kPattern));
  // RE2 exposes ok() to indicate compile success; this is observable.
  EXPECT_TRUE(re2_ptr->ok());
}

// Multiple calls to operator-> should be idempotent and return the same pointer.
// (No assumption on *how* initialization happens; just that the pointer stays stable.)
TEST_F(LazyRE2OperatorArrowTest_47, OperatorArrowIdempotentSamePointer_47) {
  auto lazy = MakeWithPattern("[A-Z]+\\d{2}");
  RE2* first = lazy.operator->();
  RE2* second = lazy.operator->();
  ASSERT_NE(first, nullptr);
  EXPECT_EQ(first, second);
  // Sanity check: pointer consistency with get() as well.
  EXPECT_EQ(first, lazy.get());
}

// Boundary case: empty pattern. RE2 accepts it; verify pointer is usable and pattern is empty.
TEST_F(LazyRE2OperatorArrowTest_47, OperatorArrowWithEmptyPattern_47) {
  auto lazy = MakeWithPattern("");
  RE2* re2_ptr = lazy.operator->();
  ASSERT_NE(re2_ptr, nullptr);
  EXPECT_EQ(re2_ptr->pattern(), std::string(""));
  // ok() is expected to be true for an empty pattern (observable behavior).
  EXPECT_TRUE(re2_ptr->ok());
}

// Error case: invalid regex should still yield a non-null RE2*, but ok() should be false.
// This tests observable error signaling via the public API.
TEST_F(LazyRE2OperatorArrowTest_47, OperatorArrowWithInvalidPattern_47) {
  auto lazy = MakeWithPattern("(");  // Unbalanced parenthesis: invalid
  RE2* re2_ptr = lazy.operator->();
  ASSERT_NE(re2_ptr, nullptr);
  EXPECT_FALSE(re2_ptr->ok());
}
