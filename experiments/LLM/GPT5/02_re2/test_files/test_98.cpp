// File: prog_inst_id_test_98.cc
#include <gtest/gtest.h>
#include "re2/prog.h"

namespace {

using re2::Prog;
using re2::Prog::Inst;

// Test fixture kept minimal: construct a fresh Prog for each test.
class ProgInstIdTest_98 : public ::testing::Test {
protected:
  Prog prog_; // default-constructed program
};

// Verifies that for a few small indices (as available), inst(i)->id(&prog) == i.
TEST_F(ProgInstIdTest_98, IdMatchesSmallIndices_98) {
  const int sz = prog_.size();
  if (sz == 0) {
    GTEST_SKIP() << "Prog has no instructions; cannot validate Inst::id.";
  }

  // Check up to first 3 indices (or as many as available).
  const int limit = std::min(3, sz);
  for (int i = 0; i < limit; ++i) {
    Inst* ins = prog_.inst(i);
    ASSERT_NE(ins, nullptr) << "inst(" << i << ") returned nullptr";
    EXPECT_EQ(ins->id(&prog_), i) << "Inst::id should equal its index";
  }
}

// Verifies the last valid index maps back to itself.
TEST_F(ProgInstIdTest_98, IdMatchesLastIndex_98) {
  const int sz = prog_.size();
  if (sz == 0) {
    GTEST_SKIP() << "Prog has no instructions; cannot validate last index.";
  }
  const int last = sz - 1;

  Inst* ins = prog_.inst(last);
  ASSERT_NE(ins, nullptr) << "inst(last) returned nullptr";
  EXPECT_EQ(ins->id(&prog_), last);
}

// Round-trip check: inst(i) -> id(&prog) -> inst(id) should return the same pointer.
TEST_F(ProgInstIdTest_98, PointerRoundTripConsistency_98) {
  const int sz = prog_.size();
  if (sz == 0) {
    GTEST_SKIP() << "Prog has no instructions; cannot verify round-trip.";
  }

  // Try up to first 5 (or as many as available).
  const int limit = std::min(5, sz);
  for (int i = 0; i < limit; ++i) {
    Inst* ins = prog_.inst(i);
    ASSERT_NE(ins, nullptr);

    const int id = ins->id(&prog_);
    ASSERT_GE(id, 0);
    ASSERT_LT(id, sz) << "Returned id out of bounds";

    Inst* back = prog_.inst(id);
    // Same object identity expected because id computes position within the same Prog.
    EXPECT_EQ(back, ins) << "inst(id(inst)) should return the same pointer";
  }
}

// Sanity across multiple distinct indices (when available).
TEST_F(ProgInstIdTest_98, DistinctIndicesHaveDistinctIds_98) {
  const int sz = prog_.size();
  if (sz < 2) {
    GTEST_SKIP() << "Need at least 2 instructions to compare distinct ids.";
  }

  Inst* a = prog_.inst(0);
  Inst* b = prog_.inst(1);
  ASSERT_NE(a, nullptr);
  ASSERT_NE(b, nullptr);
  const int ida = a->id(&prog_);
  const int idb = b->id(&prog_);
  EXPECT_NE(ida, idb) << "Different instructions should have different ids";
  EXPECT_EQ(ida, 0);
  EXPECT_EQ(idb, 1);
}

}  // namespace
