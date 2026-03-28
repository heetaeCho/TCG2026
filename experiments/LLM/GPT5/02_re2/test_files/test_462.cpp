// File: prefilter_unique_id_test_462.cc
#include "re2/prefilter.h"
#include <gtest/gtest.h>
#include <climits>

namespace {

using re2::Prefilter;

// Helper to construct a Prefilter without depending on specific Op values.
// We avoid inferring any semantics of Op by casting 0.
static Prefilter MakePrefilter() {
  return Prefilter(static_cast<Prefilter::Op>(0));
}

TEST(PrefilterTest_462, SetAndGetUniqueId_ReturnsSameValue_462) {
  Prefilter pf = MakePrefilter();
  pf.set_unique_id(42);
  EXPECT_EQ(pf.unique_id(), 42);
}

TEST(PrefilterTest_462, SetUniqueId_Overwrite_ReturnsLatest_462) {
  Prefilter pf = MakePrefilter();
  pf.set_unique_id(1);
  pf.set_unique_id(999);
  EXPECT_EQ(pf.unique_id(), 999);
}

TEST(PrefilterTest_462, UniqueId_ZeroBoundary_462) {
  Prefilter pf = MakePrefilter();
  pf.set_unique_id(0);
  EXPECT_EQ(pf.unique_id(), 0);
}

TEST(PrefilterTest_462, UniqueId_IntMaxBoundary_462) {
  Prefilter pf = MakePrefilter();
  pf.set_unique_id(INT_MAX);
  EXPECT_EQ(pf.unique_id(), INT_MAX);
}

TEST(PrefilterTest_462, UniqueId_NegativeValue_AllowedAndReturned_462) {
  Prefilter pf = MakePrefilter();
  pf.set_unique_id(-7);
  EXPECT_EQ(pf.unique_id(), -7);
}

TEST(PrefilterTest_462, UniqueId_CallOnConstObject_CompilesAndReturns_462) {
  Prefilter pf = MakePrefilter();
  pf.set_unique_id(1234);
  const Prefilter& cpf = pf;  // verify const-correct getter usage
  EXPECT_EQ(cpf.unique_id(), 1234);
}

}  // namespace
