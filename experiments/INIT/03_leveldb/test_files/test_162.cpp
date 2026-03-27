// File: version_set_dtor_test_162.cc
#include <gtest/gtest.h>

#include "db/version_set.h"
#include "db/dbformat.h"          // InternalKeyComparator
#include "leveldb/comparator.h"   // BytewiseComparator
#include "leveldb/env.h"          // Env
#include "leveldb/options.h"      // Options

using namespace leveldb;

namespace {

// Minimal helper to build a VersionSet using only public interfaces.
static VersionSet* MakeVersionSetForTest(const std::string& dbname = "version-set-dtor-test-162") {
  Options options;
  options.env = Env::Default();
  options.comparator = BytewiseComparator();

  // InternalKeyComparator requires a user comparator; use the one in options.
  InternalKeyComparator icmp(options.comparator);

  // TableCache* is not used by the constructor itself; we can pass nullptr here
  // since the tests only construct/destroy and don't call methods needing it.
  TableCache* table_cache = nullptr;

  // Construct via the public constructor signature shown in the header.
  auto* vs = new VersionSet(dbname, &options, table_cache, &icmp);
  return vs;
}

}  // namespace

// --- Tests ---

// [162] Normal operation: deleting a freshly constructed VersionSet should NOT crash.
TEST(VersionSetDtorTest_162, DestroyWithoutExternalRefs_NoCrash_162) {
  VersionSet* vs = MakeVersionSetForTest();
  ASSERT_NE(vs, nullptr);

  // Sanity: current() must be non-null per the public API expectations.
  ASSERT_NE(vs->current(), nullptr);

  // Should not assert or crash.
  delete vs;

  SUCCEED();
}

// [162] Boundary/error via observable behavior (debug only):
// If an external ref to current() is held, VersionSet dtor should assert that
// the version list is empty (the code asserts "List must be empty").
// This is observable by calling current()->Ref() and then deleting the set.
// We do NOT access internals; we only use public current() and Version::Ref().
#if GTEST_HAS_DEATH_TEST
TEST(VersionSetDtorTest_162, DestroyWithExternalRef_TriggersAssert_162) {
#ifndef NDEBUG  // assert() is active only in debug builds
  VersionSet* vs = MakeVersionSetForTest();
  ASSERT_NE(vs, nullptr);
  Version* cur = vs->current();
  ASSERT_NE(cur, nullptr);

  // Take an extra external reference so that VersionSet::~VersionSet()’s internal
  // Unref() won't drop the last reference, leaving the list non-empty.
  cur->Ref();

  // Expect the assertion in the destructor to fire.
  // Match the comment text shown in the snippet; death tests run in a child process,
  // so leaking the extra ref is fine here.
  EXPECT_DEATH(
      {
        delete vs;
      },
      "List must be empty");
#else
  GTEST_SKIP() << "Assertions disabled in release builds; skipping death test.";
#endif
}
#endif  // GTEST_HAS_DEATH_TEST
