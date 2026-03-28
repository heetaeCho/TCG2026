// File: walker_copy_test_213.cc
#include <gtest/gtest.h>
#include <string>
#include <vector>
#include "re2/walker-inl.h"

namespace {

using namespace re2;

// A simple fixture (not strictly required, but keeps naming consistent).
class WalkerCopyTest_213 : public ::testing::Test {};

TEST(WalkerCopyTest_213, CopyInt_ReturnsSame_213) {
  Regexp::Walker<int> w;
  int x = 42;
  EXPECT_EQ(x, w.Copy(x));
}

TEST(WalkerCopyTest_213, CopyZeroInt_Boundary_213) {
  Regexp::Walker<int> w;
  int x = 0;  // boundary
  EXPECT_EQ(x, w.Copy(x));
}

TEST(WalkerCopyTest_213, CopyString_EmptyAndNonEmpty_213) {
  Regexp::Walker<std::string> w;

  std::string empty;
  EXPECT_EQ(empty, w.Copy(empty));  // empty boundary

  std::string s = "hello re2";
  EXPECT_EQ(s, w.Copy(s));          // normal case
}

TEST(WalkerCopyTest_213, CopyPointer_NullAndNonNull_213) {
  Regexp::Walker<const char*> w;

  const char* pnull = nullptr;                // boundary
  EXPECT_EQ(pnull, w.Copy(pnull));

  const char* p = "abc";
  EXPECT_EQ(p, w.Copy(p));                    // same address expected
}

TEST(WalkerCopyTest_213, CopyVector_ValueSemantics_213) {
  Regexp::Walker<std::vector<int>> w;

  std::vector<int> v{1, 2, 3};
  auto copied = w.Copy(v);

  // Output equals input at call time.
  EXPECT_EQ(v, copied);

  // Subsequent mutations to the original do not retroactively change the returned value.
  v[0] = 99;
  EXPECT_NE(v, copied);
  EXPECT_EQ(1, copied[0]);
}

}  // namespace
