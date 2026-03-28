// version_ref_test_factory.cc (in your test target)
#include "db/version_set.h"

leveldb::Version* MakeVersionForTest() {
  // Example sketch — replace with your real construction path.
  // std::unique_ptr<leveldb::VersionSet> vs = CreateRealVersionSetForTests(...);
  // return vs->current(); // or a newly appended Version created by VersionSet
  return nullptr; // Return nullptr if not available to let tests GTEST_SKIP gracefully.
}

void ReleaseVersionForTest(leveldb::Version* v) {
  // If your codebase expects balanced Unref() to manage lifetime, you may not need to do anything here.
  // Otherwise, release through the real owning component as appropriate.
}
