// File: ./TestProjects/ninja/tests/pool_current_use_test_77.cc

#include "gtest/gtest.h"
#include "state.h"  // Path may need adjustment depending on your project layout

// Basic fixture for Pool tests focused on current_use().
class PoolCurrentUseTest_77 : public ::testing::Test {
protected:
  PoolCurrentUseTest_77()
      : pool_("test_pool", 3) {  // depth is arbitrary for these tests
  }

  Pool pool_;
};

// Verifies that a newly constructed Pool reports zero current use.
// This checks the observable post-construction state.
TEST_F(PoolCurrentUseTest_77, InitialCurrentUseIsZero_77) {
  EXPECT_EQ(0, pool_.current_use());
}

// Verifies that current_use() is stable and does not change simply by being
// called multiple times (no side effects).
TEST_F(PoolCurrentUseTest_77, CurrentUseIsIdempotent_77) {
  int first = pool_.current_use();
  int second = pool_.current_use();
  int third = pool_.current_use();

  EXPECT_EQ(first, second);
  EXPECT_EQ(second, third);
}

// Verifies that Pools constructed with different names and depths
// start with the same observable current_use() value, i.e. the
// constructor parameters other than those related to current use
// do not affect the initial usage.
TEST(PoolCurrentUseStandalone_77, InitialCurrentUseIndependentOfCtorArgs_77) {
  Pool pool_a("pool_a", 1);
  Pool pool_b("pool_b", 10);

  EXPECT_EQ(0, pool_a.current_use());
  EXPECT_EQ(0, pool_b.current_use());
  EXPECT_EQ(pool_a.current_use(), pool_b.current_use());
}
