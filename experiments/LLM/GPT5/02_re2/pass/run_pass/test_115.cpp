// File: prog_set_start_unanchored_test_115.cc
#include <limits>
#include "gtest/gtest.h"
#include "re2/prog.h"

using re2::Prog;

class ProgSetStartUnanchoredTest_115 : public ::testing::Test {
protected:
  Prog p_;
};

// [Normal] Setting a typical positive value is observable via the getter.
TEST_F(ProgSetStartUnanchoredTest_115, SetPositiveValue_115) {
  p_.set_start_unanchored(42);
  EXPECT_EQ(42, p_.start_unanchored());
}

// [Boundary] Default-constructed value is observable via the getter.
TEST_F(ProgSetStartUnanchoredTest_115, DefaultIsZero_115) {
  // Rely only on observable behavior via the getter.
  EXPECT_EQ(0, p_.start_unanchored());
}

// [Boundary] Setting zero should be reflected by the getter.
TEST_F(ProgSetStartUnanchoredTest_115, SetZero_115) {
  p_.set_start_unanchored(0);
  EXPECT_EQ(0, p_.start_unanchored());
}

// [Boundary] Setting INT_MAX should be reflected by the getter.
TEST_F(ProgSetStartUnanchoredTest_115, SetIntMax_115) {
  int v = std::numeric_limits<int>::max();
  p_.set_start_unanchored(v);
  EXPECT_EQ(v, p_.start_unanchored());
}

// [Boundary] Setting a negative value (if accepted by the interface) is observable via the getter.
TEST_F(ProgSetStartUnanchoredTest_115, SetNegativeValue_115) {
  p_.set_start_unanchored(-1);
  EXPECT_EQ(-1, p_.start_unanchored());
}

// [Normal] Re-setting should overwrite the previous value.
TEST_F(ProgSetStartUnanchoredTest_115, OverwritePreviousValue_115) {
  p_.set_start_unanchored(10);
  EXPECT_EQ(10, p_.start_unanchored());
  p_.set_start_unanchored(20);
  EXPECT_EQ(20, p_.start_unanchored());
}

// [Interaction] Changing the anchored start (via set_start) does not change the unanchored start,
// as observed through their respective getters.
TEST_F(ProgSetStartUnanchoredTest_115, ChangingStartDoesNotAffectStartUnanchored_115) {
  // Set and verify unanchored start
  p_.set_start_unanchored(7);
  EXPECT_EQ(7, p_.start_unanchored());

  // Change the (anchored) start via the public API
  p_.set_start(3);

  // Verify unanchored start remains what was set
  EXPECT_EQ(7, p_.start_unanchored());
}
