// File: ./TestProjects/re2/re2/testing/prefilter_constructor_test_608.cc

#include <gtest/gtest.h>
#include "re2/prefilter.h"

namespace {

using ::re2::Prefilter;

class PrefilterConstructorTest_608 : public ::testing::Test {};

// Normal operation: AND should allocate subs()
TEST_F(PrefilterConstructorTest_608, AndOpAllocatesSubs_608) {
  Prefilter pf(Prefilter::AND);
  EXPECT_EQ(pf.op(), Prefilter::AND);
  EXPECT_NE(pf.subs(), nullptr) << "subs() must be allocated for AND";
}

// Normal operation: OR should allocate subs()
TEST_F(PrefilterConstructorTest_608, OrOpAllocatesSubs_608) {
  Prefilter pf(Prefilter::OR);
  EXPECT_EQ(pf.op(), Prefilter::OR);
  EXPECT_NE(pf.subs(), nullptr) << "subs() must be allocated for OR";
}

// Boundary: ATOM should NOT allocate subs()
TEST_F(PrefilterConstructorTest_608, AtomOpDoesNotAllocateSubs_608) {
  Prefilter pf(Prefilter::ATOM);
  EXPECT_EQ(pf.op(), Prefilter::ATOM);
  EXPECT_EQ(pf.subs(), nullptr) << "subs() should be null for non-AND/OR ops";
}

// Boundary: ALL should NOT allocate subs()
TEST_F(PrefilterConstructorTest_608, AllOpDoesNotAllocateSubs_608) {
  Prefilter pf(Prefilter::ALL);
  EXPECT_EQ(pf.op(), Prefilter::ALL);
  EXPECT_EQ(pf.subs(), nullptr);
}

// Boundary: NONE should NOT allocate subs()
TEST_F(PrefilterConstructorTest_608, NoneOpDoesNotAllocateSubs_608) {
  Prefilter pf(Prefilter::NONE);
  EXPECT_EQ(pf.op(), Prefilter::NONE);
  EXPECT_EQ(pf.subs(), nullptr);
}

// Observable attribute round-trip: unique_id setter/getter
TEST_F(PrefilterConstructorTest_608, UniqueIdRoundTrip_608) {
  Prefilter pf(Prefilter::ATOM);
  pf.set_unique_id(12345);
  EXPECT_EQ(pf.unique_id(), 12345);
}

// Setter/getter behavior for subs(): setting nullptr remains observable
TEST_F(PrefilterConstructorTest_608, SetSubsToNull_Observable_608) {
  Prefilter pf(Prefilter::ATOM);
  // Initially expected nullptr for ATOM
  ASSERT_EQ(pf.subs(), nullptr);
  pf.set_subs(nullptr);
  EXPECT_EQ(pf.subs(), nullptr);
}

}  // namespace
