// File: walker_postvisit_test_212.cc
#include <gtest/gtest.h>
#include <string>

// Include the provided partial headers under test.
#include "re2/walker-inl.h"
#include "re2/regexp.h"

namespace {

using namespace re2;

// A small helper struct to verify behavior with user-defined (non-primitive) types.
struct Box {
  int v;
  bool operator==(const Box& other) const { return v == other.v; }
};

TEST(WalkerPostVisit_212, ReturnsPreArg_WithInts_212) {
  // Arrange
  Regexp::Walker<int> walker;
  Regexp* re = nullptr;              // Not used by PostVisit per interface behavior here.
  const int parent_arg = -1;         // Intentionally different from pre_arg.
  const int pre_arg = 42;
  int* child_args = nullptr;         // No children
  const int nchild_args = 0;

  // Act
  int out = walker.PostVisit(re, parent_arg, pre_arg, child_args, nchild_args);

  // Assert
  EXPECT_EQ(out, pre_arg);
}

TEST(WalkerPostVisit_212, IgnoresParentArgAndChildren_Int_212) {
  // Arrange
  Regexp::Walker<int> walker;
  Regexp* re = nullptr;
  const int parent_arg = 999;        // Different from pre_arg; should be ignored.
  const int pre_arg = -123;
  int kids[] = {7, 8, 9};            // Provide some child args; content should be irrelevant.
  const int nchild_args = static_cast<int>(sizeof(kids) / sizeof(kids[0]));

  // Act
  int out = walker.PostVisit(re, parent_arg, pre_arg, kids, nchild_args);

  // Assert
  EXPECT_EQ(out, pre_arg);
}

TEST(WalkerPostVisit_212, WorksWithStdString_212) {
  // Arrange
  Regexp::Walker<std::string> walker;
  Regexp* re = nullptr;
  const std::string parent_arg = "parent";
  const std::string pre_arg = "pre_value";
  std::string* child_args = nullptr;
  const int nchild_args = 0;

  // Act
  std::string out = walker.PostVisit(re, parent_arg, pre_arg, child_args, nchild_args);

  // Assert
  EXPECT_EQ(out, pre_arg);
}

TEST(WalkerPostVisit_212, WorksWithUserDefinedType_212) {
  // Arrange
  Regexp::Walker<Box> walker;
  Regexp* re = nullptr;
  const Box parent_arg{111};
  const Box pre_arg{777};
  Box kids[] = {{1}, {2}};
  const int nchild_args = 2;

  // Act
  Box out = walker.PostVisit(re, parent_arg, pre_arg, kids, nchild_args);

  // Assert
  EXPECT_EQ(out, pre_arg);
}

TEST(WalkerPostVisit_212, NullChildrenPointerWithPositiveCount_DoesNotAffectReturn_212) {
  // This test verifies that, regardless of children pointer/count values supplied through
  // the public interface, the observable behavior remains returning pre_arg.
  // (We do not assert on internal safety; only on the returned value.)
  Regexp::Walker<int> walker;
  Regexp* re = nullptr;
  const int parent_arg = 0;
  const int pre_arg = 314159;

  // Deliberately pass a null child pointer with a positive count; since the function’s
  // observable behavior is to return pre_arg, we only assert on that behavior.
  int* child_args = nullptr;
  const int nchild_args = 10;

  int out = walker.PostVisit(re, parent_arg, pre_arg, child_args, nchild_args);

  EXPECT_EQ(out, pre_arg);
}

}  // namespace
