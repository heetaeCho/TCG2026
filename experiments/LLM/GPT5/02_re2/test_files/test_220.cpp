// File: regexp_mimics_pcre_test_220.cc

#include <gtest/gtest.h>

//
// Test double for PCREWalker
//
// We redirect the production code to use this fake at compile time,
// so we can (a) observe the call and (b) control the return value.
//
namespace re2 {
struct FakePCREWalker {
  // Observability
  static inline Regexp* last_re = nullptr;
  static inline bool     last_top_arg = false;
  static inline int      constructed = 0;

  // Control
  static inline bool     next_return = false;

  FakePCREWalker() { constructed++; }
  bool Walk(Regexp* re, bool top_arg) {
    last_re = re;
    last_top_arg = top_arg;
    return next_return;
  }
};
}  // namespace re2

// Redirect production identifier `PCREWalker` to our fake *only* for this TU.
#define PCREWalker FakePCREWalker

// Pull in the method under test. This file defines a minimal re2::Regexp with
// bool MimicsPCRE() { PCREWalker w; return w.Walk(this, true); }
#include "TestProjects/re2/re2/mimics_pcre.cc"

using namespace re2;

class RegexpMimicsPCRETest_220 : public ::testing::Test {
protected:
  void SetUp() override {
    // Reset fake's observation/control knobs before each test
    FakePCREWalker::last_re = nullptr;
    FakePCREWalker::last_top_arg = false;
    FakePCREWalker::constructed = 0;
    FakePCREWalker::next_return = false;
  }
};

// --- Tests ---

TEST_F(RegexpMimicsPCRETest_220, ReturnsTrueWhenWalkerReturnsTrue_220) {
  // Arrange
  Regexp re;
  FakePCREWalker::next_return = true;

  // Act
  bool ok = re.MimicsPCRE();

  // Assert: value mirrors walker
  EXPECT_TRUE(ok);
  // Assert: constructed exactly one walker instance
  EXPECT_EQ(FakePCREWalker::constructed, 1);
  // Assert: Walk was invoked with (this, true)
  EXPECT_EQ(FakePCREWalker::last_re, &re);
  EXPECT_TRUE(FakePCREWalker::last_top_arg);
}

TEST_F(RegexpMimicsPCRETest_220, ReturnsFalseWhenWalkerReturnsFalse_220) {
  // Arrange
  Regexp re;
  FakePCREWalker::next_return = false;

  // Act
  bool ok = re.MimicsPCRE();

  // Assert: value mirrors walker
  EXPECT_FALSE(ok);
  // Assert: constructed exactly one walker instance
  EXPECT_EQ(FakePCREWalker::constructed, 1);
  // Assert: Walk was invoked with (this, true)
  EXPECT_EQ(FakePCREWalker::last_re, &re);
  EXPECT_TRUE(FakePCREWalker::last_top_arg);
}

TEST_F(RegexpMimicsPCRETest_220, CreatesNewWalkerPerCall_220) {
  // Arrange
  Regexp re;

  // Act + Assert over two calls, ensuring a fresh walker each time
  FakePCREWalker::next_return = true;
  EXPECT_TRUE(re.MimicsPCRE());
  EXPECT_EQ(FakePCREWalker::constructed, 1);

  FakePCREWalker::next_return = false;
  EXPECT_FALSE(re.MimicsPCRE());
  EXPECT_EQ(FakePCREWalker::constructed, 2);
}
