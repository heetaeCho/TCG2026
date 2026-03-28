// File: prefilter_test_459.cc
#include <gtest/gtest.h>
#include <climits>
#include <vector>
#include <string>

#include "re2/prefilter.h"

namespace re2 {

class PrefilterTest_459 : public ::testing::Test {};

// --- Normal operation: constructor + op() round-trip ---
TEST_F(PrefilterTest_459, ConstructThenOpReturnsSameValue_459) {
  // Use two distinct Op values without assuming the named enumerators.
  Prefilter::Op op0 = static_cast<Prefilter::Op>(0);
  Prefilter::Op op1 = static_cast<Prefilter::Op>(1);

  Prefilter p0(op0);
  Prefilter p1(op1);

  EXPECT_EQ(p0.op(), op0);
  EXPECT_EQ(p1.op(), op1);
  EXPECT_NE(p0.op(), p1.op());
}

// --- Normal operation: subs pointer round-trip via setter/getter ---
TEST_F(PrefilterTest_459, SubsSetterGetterRoundTrip_459) {
  Prefilter::Op op_any = static_cast<Prefilter::Op>(0);
  Prefilter pf(op_any);

  std::vector<Prefilter*> vec;
  pf.set_subs(&vec);
  EXPECT_EQ(pf.subs(), &vec);

  // Changing to another pointer should be observable as well.
  std::vector<Prefilter*> vec2;
  pf.set_subs(&vec2);
  EXPECT_EQ(pf.subs(), &vec2);
  EXPECT_NE(pf.subs(), &vec);
}

// --- Boundary/exceptional behavior that is observable: nullptr for subs ---
TEST_F(PrefilterTest_459, SubsCanBeSetToNullptr_459) {
  Prefilter::Op op_any = static_cast<Prefilter::Op>(0);
  Prefilter pf(op_any);

  pf.set_subs(nullptr);
  EXPECT_EQ(pf.subs(), nullptr);
}

// --- Normal operation: unique_id round-trip via setter/getter ---
TEST_F(PrefilterTest_459, UniqueIdRoundTrip_459) {
  Prefilter::Op op_any = static_cast<Prefilter::Op>(0);
  Prefilter pf(op_any);

  pf.set_unique_id(0);
  EXPECT_EQ(pf.unique_id(), 0);

  pf.set_unique_id(12345);
  EXPECT_EQ(pf.unique_id(), 12345);
}

// --- Boundary conditions for unique_id: extremes of int ---
TEST_F(PrefilterTest_459, UniqueIdBoundaryValues_459) {
  Prefilter::Op op_any = static_cast<Prefilter::Op>(0);
  Prefilter pf(op_any);

  pf.set_unique_id(INT_MAX);
  EXPECT_EQ(pf.unique_id(), INT_MAX);

  // INT_MIN is an observable input if negative IDs are allowed by the interface type (int).
  pf.set_unique_id(INT_MIN);
  EXPECT_EQ(pf.unique_id(), INT_MIN);
}

// --- Op stability: setting other fields should not change op() ---
TEST_F(PrefilterTest_459, OpIsStableWhenOtherFieldsChange_459) {
  Prefilter::Op op_initial = static_cast<Prefilter::Op>(2);
  Prefilter pf(op_initial);

  // Mutate other observable fields
  std::vector<Prefilter*> vec;
  pf.set_subs(&vec);
  pf.set_unique_id(777);

  // op() should remain whatever was provided to the constructor.
  EXPECT_EQ(pf.op(), op_initial);

  // Further changes still shouldn't affect op()
  pf.set_subs(nullptr);
  pf.set_unique_id(0);
  EXPECT_EQ(pf.op(), op_initial);
}

}  // namespace re2
