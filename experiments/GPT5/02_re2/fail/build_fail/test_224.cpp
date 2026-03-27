// File: tostring_walker_shortvisit_test.cc

#include <gtest/gtest.h>
#include <string>

// Forward declarations matching the exposed interface we use.
// (Definitions are provided by the production code in re2/tostring.cc.)
namespace re2 {
  class Regexp;  // We don't construct or inspect this; pass nullptr only.
  class ToStringWalker {
   public:
    explicit ToStringWalker(std::string* t);
    virtual int ShortVisit(Regexp* re, int parent_arg);
  };
}  // namespace re2

using namespace re2;

class ToStringWalkerTest_224 : public ::testing::Test {
 protected:
  std::string out_;
};

// Normal operation: returns 0 when called with nullptr re and parent_arg = 0.
TEST_F(ToStringWalkerTest_224, ShortVisit_ReturnsZero_WithNullptrAndZeroParent_224) {
  ToStringWalker w(&out_);
  int result = w.ShortVisit(/*re=*/nullptr, /*parent_arg=*/0);
  EXPECT_EQ(result, 0);
}

// Boundary/robustness: ignores parent_arg sign (negative, positive) and still returns 0.
TEST_F(ToStringWalkerTest_224, ShortVisit_ReturnsZero_IgnoresParentArgSign_224) {
  ToStringWalker w(&out_);

  EXPECT_EQ(w.ShortVisit(nullptr, -123456789), 0);
  EXPECT_EQ(w.ShortVisit(nullptr,  123456789), 0);
}

// Idempotence/consistency: multiple calls leave the associated string untouched and return 0.
TEST_F(ToStringWalkerTest_224, ShortVisit_DoesNotModifyOutputString_AcrossCalls_224) {
  std::string original = out_;  // Expect no change.
  ToStringWalker w(&out_);

  EXPECT_EQ(w.ShortVisit(nullptr, 1), 0);
  EXPECT_EQ(w.ShortVisit(nullptr, 2), 0);
  EXPECT_EQ(w.ShortVisit(nullptr, 3), 0);

  EXPECT_EQ(out_, original);
}
