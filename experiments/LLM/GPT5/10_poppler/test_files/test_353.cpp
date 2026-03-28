// SPDX-License-Identifier: GPL-2.0-or-later
// File: FunctionTest_353.cpp
//
// Unit tests for poppler::Function (black-box interface tests only)
//
// The TEST_ID is 353

#include <gtest/gtest.h>

#include <type_traits>
#include <memory>

#include "poppler/Function.h"

// If poppler headers place Function in a namespace, adapt via a using-decl.
// Many poppler builds use the global namespace for these core types; keep this
// alias to avoid rewriting tests if it is namespaced in your tree.
using ::Function;

namespace {

TEST(FunctionTypeTraitsTest_353, NotCopyConstructible_353) {
  EXPECT_FALSE((std::is_copy_constructible<Function>::value));
}

TEST(FunctionTypeTraitsTest_353, NotCopyAssignable_353) {
  EXPECT_FALSE((std::is_copy_assignable<Function>::value));
}

TEST(FunctionGetHasRangeTest_353, CallableOnConstObject_353) {
  const Function f;
  const bool v1 = f.getHasRange();
  const bool v2 = f.getHasRange();
  EXPECT_EQ(v1, v2);  // should be a stable query for the same object state
}

TEST(FunctionGetHasRangeTest_353, RepeatedCallsAreConsistent_353) {
  Function f;
  const bool first = f.getHasRange();
  const bool second = f.getHasRange();
  EXPECT_EQ(first, second);
}

TEST(FunctionGetHasRangeTest_353, CopyPreservesHasRangeWhenCopyIsProvided_353) {
  Function f;

  // copy() is virtual; for base Function it may return nullptr or a valid copy,
  // depending on the implementation. We only assert observable behavior.
  auto cloned = f.copy();
  if (cloned) {
    EXPECT_EQ(f.getHasRange(), cloned->getHasRange());
  } else {
    SUCCEED() << "Function::copy() returned nullptr; no clone behavior to verify.";
  }
}

}  // namespace