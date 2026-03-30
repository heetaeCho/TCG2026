// Copyright ...
#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "db/version_set.h"   // Declares leveldb::Version, VersionSet, etc.
#include "leveldb/slice.h"    // Declares leveldb::Slice

using ::testing::Eq;
using ::testing::Ne;

namespace leveldb {

// ======= Test seam for the external collaborator ============================
// We provide a test-side definition that the production code will call.
// Signature must match the one used in Version::OverlapInLevel's TU.
// In LevelDB, this typically looks like:
//   bool SomeFileOverlapsRange(const InternalKeyComparator& icmp,
//                              bool disjoint_sorted_files,
//                              const std::vector<FileMetaData*>& files,
//                              const Slice* smallest_user_key,
//                              const Slice* largest_user_key);

struct OverlapsProbe {
  // Captured args from the most recent call:
  bool last_disjoint_sorted = false;
  const Slice* last_smallest = nullptr;
  const Slice* last_largest = nullptr;

  // The value we want the seam to return for the next call:
  bool next_return = false;

  // Reset helper
  void Reset() {
    last_disjoint_sorted = false;
    last_smallest = nullptr;
    last_largest = nullptr;
    next_return = false;
  }
};

static OverlapsProbe g_overlaps_probe;

// Define the seam in the same namespace so the real method resolves to this.
bool SomeFileOverlapsRange(const InternalKeyComparator& /*icmp*/,
                           bool disjoint_sorted_files,
                           const std::vector<FileMetaData*>& /*files*/,
                           const Slice* smallest_user_key,
                           const Slice* largest_user_key) {
  g_overlaps_probe.last_disjoint_sorted = disjoint_sorted_files;
  g_overlaps_probe.last_smallest = smallest_user_key;
  g_overlaps_probe.last_largest = largest_user_key;
  return g_overlaps_probe.next_return;
}

// ======= Fixture ============================================================

class VersionOverlapInLevelTest_153 : public ::testing::Test {
protected:
  // Minimal harness to obtain a Version* without touching internals.
  // Use your repository’s normal test construction path.
  //
  // In many LevelDB setups, VersionSet::current() returns a usable Version.
  // Provide real Options/Env/TableCache/Comparator as your repo expects.
  //
  // Replace the body of SetUp() with your existing test infra. The key
  // constraint is: we DO NOT mutate version internals; we just call the API.
  void SetUp() override {
    // --- BEGIN: Example scaffolding you should adapt to your repo -----------
    // These declarations exist in real LevelDB; adjust headers if paths differ.
    options_ = Options{};
    options_.env = Env::Default();           // from your env
    // Create comparator and table cache per your test infra:
    internal_cmp_ = new InternalKeyComparator(BytewiseComparator());
    table_cache_ = new TableCache("dummy-dbname", &options_, 10);

    vset_ = new VersionSet("dummy-dbname", &options_, table_cache_, internal_cmp_);
    // In stock LevelDB, VersionSet constructor wires a dummy/current version.
    version_ = vset_->current();
    // --- END: Example scaffolding ------------------------------------------

    g_overlaps_probe.Reset();
  }

  void TearDown() override {
    // --- BEGIN: cleanup to match your repo’s ownership rules ----------------
    delete vset_;         // Usually owns current()/dummy version.
    delete table_cache_;
    delete internal_cmp_;
    // --- END: cleanup -------------------------------------------------------
  }

  // Test-owned pointers; adapt types/ownership to your repo.
  Options options_;
  InternalKeyComparator* internal_cmp_ = nullptr;
  TableCache* table_cache_ = nullptr;
  VersionSet* vset_ = nullptr;
  Version* version_ = nullptr;
};

// ======= Tests ==============================================================

// Normal operation: level == 0 must pass disjoint_sorted_files == false
TEST_F(VersionOverlapInLevelTest_153, Level0_PassesDisjointFalse_153) {
  ASSERT_NE(version_, nullptr);

  // Make the seam return true so we can assert the forwarding of the return.
  g_overlaps_probe.next_return = true;

  Slice smallest("a"), largest("z");
  const bool ok = version_->OverlapInLevel(/*level=*/0, &smallest, &largest);

  EXPECT_TRUE(ok);  // returns collaborator’s value
  EXPECT_FALSE(g_overlaps_probe.last_disjoint_sorted);  // level 0 → false
  EXPECT_THAT(g_overlaps_probe.last_smallest, Eq(&smallest));
  EXPECT_THAT(g_overlaps_probe.last_largest,  Eq(&largest));
}

// Normal operation: level > 0 must pass disjoint_sorted_files == true
TEST_F(VersionOverlapInLevelTest_153, LevelPositive_PassesDisjointTrue_153) {
  ASSERT_NE(version_, nullptr);

  g_overlaps_probe.next_return = false;  // distinct value to verify passthrough

  Slice smallest("k1"), largest("k9");
  const bool ok = version_->OverlapInLevel(/*level=*/3, &smallest, &largest);

  EXPECT_FALSE(ok);  // collaborator’s value
  EXPECT_TRUE(g_overlaps_probe.last_disjoint_sorted);  // level > 0 → true
  EXPECT_THAT(g_overlaps_probe.last_smallest, Eq(&smallest));
  EXPECT_THAT(g_overlaps_probe.last_largest,  Eq(&largest));
}

// Boundary-ish check: level == 1 is the first positive level (still true)
TEST_F(VersionOverlapInLevelTest_153, LevelOne_PassesDisjointTrue_153) {
  ASSERT_NE(version_, nullptr);

  g_overlaps_probe.next_return = true;

  Slice s("lo"), l("up");
  const bool ok = version_->OverlapInLevel(/*level=*/1, &s, &l);

  EXPECT_TRUE(ok);
  EXPECT_TRUE(g_overlaps_probe.last_disjoint_sorted);  // must be true
}

// Exceptional/edge behavior that is still observable via the interface:
// Accepts nullptr keys and forwards them unchanged to the collaborator.
// (We don’t infer what “nullptr keys” means—just verify forwarding.)
TEST_F(VersionOverlapInLevelTest_153, NullKeyPointers_AreForwarded_153) {
  ASSERT_NE(version_, nullptr);

  g_overlaps_probe.next_return = false;

  const bool ok = version_->OverlapInLevel(/*level=*/2, /*smallest=*/nullptr, /*largest=*/nullptr);

  EXPECT_FALSE(ok);
  EXPECT_TRUE(g_overlaps_probe.last_disjoint_sorted);   // level > 0
  EXPECT_EQ(g_overlaps_probe.last_smallest, nullptr);
  EXPECT_EQ(g_overlaps_probe.last_largest,  nullptr);
}

// Sanity: independent calls don’t leak prior pointer values via the collaborator
TEST_F(VersionOverlapInLevelTest_153, SubsequentCalls_DoNotLeakPreviousArgs_153) {
  ASSERT_NE(version_, nullptr);

  Slice s1("a"), l1("b");
  g_overlaps_probe.next_return = true;
  (void)version_->OverlapInLevel(0, &s1, &l1);
  EXPECT_THAT(g_overlaps_probe.last_smallest, Eq(&s1));
  EXPECT_THAT(g_overlaps_probe.last_largest,  Eq(&l1));

  // Second call with different pointers; probe must reflect the new ones.
  Slice s2("c"), l2("d");
  g_overlaps_probe.next_return = false;
  (void)version_->OverlapInLevel(1, &s2, &l2);
  EXPECT_THAT(g_overlaps_probe.last_smallest, Eq(&s2));
  EXPECT_THAT(g_overlaps_probe.last_largest,  Eq(&l2));
  EXPECT_TRUE(g_overlaps_probe.last_disjoint_sorted);  // level 1 → true
}

}  // namespace leveldb
