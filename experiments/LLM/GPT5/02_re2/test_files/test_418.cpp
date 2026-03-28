// File: ./TestProjects/re2/re2/tests/configure_prefix_accel_test.cc
#include "gtest/gtest.h"
#include "re2/prog.h"

namespace re2 {

TEST(ConfigurePrefixAccel_418, FoldcaseLeavesFrontBackAlone_418) {
  Prog p;

  // Set known sentinels for observable public fields.
  p.prefix_front_ = -12345;
  p.prefix_back_  = -54321;

  // Foldcase path should not touch front/back; it only prepares a shift-DFA.
  p.ConfigurePrefixAccel("HelloWorld", /*prefix_foldcase=*/true);

  EXPECT_EQ(p.prefix_front_, -12345);
  EXPECT_EQ(p.prefix_back_,  -54321);
}

TEST(ConfigurePrefixAccel_418, NonFoldcaseSetsFrontAndBack_418) {
  Prog p;

  // Initialize to sentinel values to ensure they actually change.
  p.prefix_front_ = -1;
  p.prefix_back_  = -1;

  // Non-foldcase with length > 1 => both front and back are set.
  p.ConfigurePrefixAccel("abc", /*prefix_foldcase=*/false);

  EXPECT_EQ(p.prefix_front_, static_cast<int>('a'));
  EXPECT_EQ(p.prefix_back_,  static_cast<int>('c'));
}

TEST(ConfigurePrefixAccel_418, NonFoldcaseSingleCharSetsOnlyFront_418) {
  Prog p;

  // Preload back with a sentinel. Only front should be updated for size==1.
  p.prefix_front_ = -1;
  p.prefix_back_  = 7777;

  p.ConfigurePrefixAccel("X", /*prefix_foldcase=*/false);

  EXPECT_EQ(p.prefix_front_, static_cast<int>('X'));
  // Must remain unchanged since the interface sets only front for size==1.
  EXPECT_EQ(p.prefix_back_,  7777);
}

TEST(ConfigurePrefixAccel_418, EmptyPrefixFoldcaseDoesNotTouchFrontBack_418) {
  Prog p;

  // Verify safe/observable behavior for empty prefix in foldcase path.
  p.prefix_front_ = 11;
  p.prefix_back_  = 22;

  p.ConfigurePrefixAccel("", /*prefix_foldcase=*/true);

  EXPECT_EQ(p.prefix_front_, 11);
  EXPECT_EQ(p.prefix_back_,  22);
}

}  // namespace re2
