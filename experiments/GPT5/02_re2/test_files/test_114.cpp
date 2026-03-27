// File: prog_start_unanchored_test.cc
#include <gtest/gtest.h>
#include <limits>
#include "re2/prog.h"

namespace re2 {

class ProgStartUnanchoredTest_114 : public ::testing::Test {
protected:
  Prog prog_;
};

// Normal operation: default-constructed value.
// (Relies only on observable return value of the getter.)
TEST_F(ProgStartUnanchoredTest_114, DefaultIsZero_114) {
  // Expectation derived from public construction behavior visible via the getter.
  EXPECT_EQ(0, prog_.start_unanchored());
}

// Normal operation: setting arbitrary values is reflected by the getter.
TEST_F(ProgStartUnanchoredTest_114, SetAndGetRoundTrip_114) {
  prog_.set_start_unanchored(7);
  EXPECT_EQ(7, prog_.start_unanchored());

  prog_.set_start_unanchored(-3);
  EXPECT_EQ(-3, prog_.start_unanchored());

  prog_.set_start_unanchored(0);
  EXPECT_EQ(0, prog_.start_unanchored());
}

// Boundary conditions: extreme integer values are accepted and returned.
TEST_F(ProgStartUnanchoredTest_114, HandlesIntBoundaries_114) {
  prog_.set_start_unanchored(std::numeric_limits<int>::min());
  EXPECT_EQ(std::numeric_limits<int>::min(), prog_.start_unanchored());

  prog_.set_start_unanchored(std::numeric_limits<int>::max());
  EXPECT_EQ(std::numeric_limits<int>::max(), prog_.start_unanchored());
}

// Normal operation: multiple updates reflect the latest set value.
TEST_F(ProgStartUnanchoredTest_114, MultipleUpdatesReflectLatest_114) {
  prog_.set_start_unanchored(1);
  prog_.set_start_unanchored(2);
  prog_.set_start_unanchored(3);
  EXPECT_EQ(3, prog_.start_unanchored());
}

// Interaction check (still black-box): changing start() does not
// implicitly alter start_unanchored() and vice versa, as observed via getters.
TEST_F(ProgStartUnanchoredTest_114, IndependentFromStartField_114) {
  // Set distinct values for clarity.
  prog_.set_start_unanchored(42);
  prog_.set_start(100);

  // Verify both getters reflect their own last-set values.
  EXPECT_EQ(42, prog_.start_unanchored());
  EXPECT_EQ(100, prog_.start());

  // Change one again and ensure the other remains unchanged.
  prog_.set_start(5);
  EXPECT_EQ(42, prog_.start_unanchored());
  EXPECT_EQ(5, prog_.start());

  prog_.set_start_unanchored(-8);
  EXPECT_EQ(-8, prog_.start_unanchored());
  EXPECT_EQ(5, prog_.start());
}

}  // namespace re2
