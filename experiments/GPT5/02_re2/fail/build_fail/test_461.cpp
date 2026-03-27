// File: prefilter_set_unique_id_test_461.cc

#include <gtest/gtest.h>
#include <limits>
#include "re2/prefilter.h"

namespace {

using re2::Prefilter;

class PrefilterTest_461 : public ::testing::Test {
protected:
  // Create a Prefilter with an arbitrary Op value without assuming semantics.
  static Prefilter MakePrefilter() {
    // We avoid inferring valid Op values; we just provide a placeholder.
    auto any_op = static_cast<Prefilter::Op>(0);
    return Prefilter(any_op);
  }
};

// Normal operation: value set is returned via getter.
TEST(PrefilterTest_461, SetUniqueId_ShouldReflectViaGetter_461) {
  Prefilter pf = PrefilterTest_461::MakePrefilter();

  pf.set_unique_id(12345);
  EXPECT_EQ(12345, pf.unique_id());
}

// Normal operation: subsequent sets overwrite the previous value.
TEST(PrefilterTest_461, SetUniqueId_OverwritesPreviousValue_461) {
  Prefilter pf = PrefilterTest_461::MakePrefilter();

  pf.set_unique_id(1);
  EXPECT_EQ(1, pf.unique_id());

  pf.set_unique_id(42);
  EXPECT_EQ(42, pf.unique_id());
}

// Boundary: zero is handled as a valid int.
TEST(PrefilterTest_461, SetUniqueId_HandlesZero_461) {
  Prefilter pf = PrefilterTest_461::MakePrefilter();

  pf.set_unique_id(0);
  EXPECT_EQ(0, pf.unique_id());
}

// Boundary: negative values are stored and returned unchanged.
TEST(PrefilterTest_461, SetUniqueId_HandlesNegative_461) {
  Prefilter pf = PrefilterTest_461::MakePrefilter();

  pf.set_unique_id(-9876);
  EXPECT_EQ(-9876, pf.unique_id());
}

// Boundary: int min/max round-trip correctly.
TEST(PrefilterTest_461, SetUniqueId_HandlesIntBounds_461) {
  Prefilter pf1 = PrefilterTest_461::MakePrefilter();
  pf1.set_unique_id(std::numeric_limits<int>::max());
  EXPECT_EQ(std::numeric_limits<int>::max(), pf1.unique_id());

  Prefilter pf2 = PrefilterTest_461::MakePrefilter();
  pf2.set_unique_id(std::numeric_limits<int>::min());
  EXPECT_EQ(std::numeric_limits<int>::min(), pf2.unique_id());
}

}  // namespace
