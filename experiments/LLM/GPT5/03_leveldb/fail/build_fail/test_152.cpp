// File: version_unref_test_152.cc

#include "db/version_set.h"
#include "db/version_edit.h"
#include "db/table_cache.h"
#include "util/testharness.h"  // If your project uses LevelDB's test harness
#include "util/logging.h"

#include "gtest/gtest.h"

#include "leveldb/env.h"
#include "leveldb/options.h"
#include "leveldb/comparator.h"

using namespace leveldb;

namespace {

class VersionUnrefTest_152 : public ::testing::Test {
protected:
  std::string dbname_;
  Options options_;
  InternalKeyComparator* icmp_;
  TableCache* table_cache_;
  VersionSet* vset_;

  void SetUp() override {
    dbname_ = "version_unref_test_152";
    options_.env = Env::Default();
    options_.comparator = BytewiseComparator();

    icmp_ = new InternalKeyComparator(options_.comparator);
    // Cache size is arbitrary for these tests since we don't read tables
    table_cache_ = new TableCache(dbname_, &options_, 1024);
    vset_ = new VersionSet(dbname_, &options_, table_cache_, icmp_);

    // We don't call Recover/LogAndApply because we only exercise Ref/Unref
    // via the current() Version pointer as a black box.
  }

  void TearDown() override {
    // Note: If tests accidentally delete the current() version (by unbalanced
    // Unref), destruction of vset_ might fail. Tests are written to avoid that,
    // except where explicitly doing a death test.
    delete vset_;
    delete table_cache_;
    delete icmp_;
  }
};

} // namespace

// Normal operation: acquiring a temporary reference and releasing it should be safe.
TEST_F(VersionUnrefTest_152, RefThenUnref_IsBalancedAndSafe_152) {
  Version* v = vset_->current();
  ASSERT_NE(v, nullptr) << "VersionSet::current() must not be null";

  // Take a temporary external ref and release it; should not crash or assert.
  v->Ref();
  v->Unref();

  // Still usable under VersionSet ownership for inspection (no manipulation).
  // We deliberately avoid dereferencing after any operation that would delete it.
  SUCCEED();
}

// Boundary/misuse: Calling Unref() without first calling Ref()
// can release the VersionSet-held reference and delete the object.
// The second Unref() on the same pointer should crash (use-after-free / assert).
// We gate it with death tests because the exact failure mode is build-dependent.
#if GTEST_HAS_DEATH_TEST
TEST_F(VersionUnrefTest_152, UnrefTwice_TriggersDeathOnSecondCall_152) {
  Version* v = vset_->current();
  ASSERT_NE(v, nullptr);

  // First Unref(): releases an existing reference (likely the one held
  // under VersionSet's management if you didn't add one). This may delete 'v'.
  v->Unref();

  // Second Unref() on the same pointer should crash (use-after-free or assert).
  // We don't assert the exact message because it can vary by build flags.
  ASSERT_DEATH({ v->Unref(); }, ".*");
}
#endif

// Another normal-path check: multiple temporary refs balanced back to baseline.
TEST_F(VersionUnrefTest_152, MultipleRefsThenUnrefs_AreSafeWhenBalanced_152) {
  Version* v = vset_->current();
  ASSERT_NE(v, nullptr);

  // Add two temporary refs
  v->Ref();
  v->Ref();

  // Release them both; should not crash
  v->Unref();
  v->Unref();

  SUCCEED();
}
