// File: db/version_set_releaseinputs_test.cc

#include "gtest/gtest.h"

// Rely on the production headers only; treat implementation as a black box.
#include "db/version_set.h"

namespace leveldb {

// Some codebases expose a CompactionTestPeer for tests. If it exists in your
// tree as indicated in prior test prompts, include the header instead.
// Here we forward-declare the minimal API we need, matching the earlier snippet:
//
//   class CompactionTestPeer {
//    public:
//     static std::unique_ptr<Compaction> Make(const Options* opts, int level);
//     static void SetInputVersion(Compaction* c, Version* v);
//   };
//
// If your project already provides this class in a header (e.g., db/version_set.h
// under a test guard), simply include it and remove this forward declaration.

class CompactionTestPeer {
 public:
  static std::unique_ptr<Compaction> Make(const Options* opts, int level);
  static void SetInputVersion(Compaction* c, Version* v);
};

}  // namespace leveldb

using namespace leveldb;

// ---------- Test Fixture ----------

class CompactionReleaseInputsTest_183 : public ::testing::Test {
 protected:
  leveldb::Options opts_;  // Use default options as a placeholder.

  std::unique_ptr<Compaction> MakeCompactionAtLevel(int level) {
    return CompactionTestPeer::Make(&opts_, level);
  }
};

// ---------- Tests ----------

// [Behavior] Safe no-op when input_version_ is nullptr.
TEST_F(CompactionReleaseInputsTest_183, ReleaseInputs_NoInputVersion_NoCrash_183) {
  auto c = MakeCompactionAtLevel(0);

  // Do not set any input version (remains nullptr).
  // Call ReleaseInputs; should be a safe no-op (no crash / no throw).
  c->ReleaseInputs();

  // Call it again to ensure repeated no-ops are fine.
  c->ReleaseInputs();

  SUCCEED();  // If we reached here without crash, behavior is as expected.
}

// [Behavior] Idempotency when called multiple times.
// Even if ReleaseInputs() cleared internal ownership once, repeated calls must be safe.
TEST_F(CompactionReleaseInputsTest_183, ReleaseInputs_Idempotent_WhenCalledTwice_183) {
  auto c = MakeCompactionAtLevel(1);

  // Explicitly ensure nullptr is set via the test peer (if supported).
  CompactionTestPeer::SetInputVersion(c.get(), nullptr);

  // Two consecutive calls should not fail.
  c->ReleaseInputs();
  c->ReleaseInputs();

  SUCCEED();
}

// [Behavior] Safe after external lifecycle ends.
// If the test harness (peer) reassigns the input to nullptr after a release,
// subsequent ReleaseInputs() calls are still safe.
// (We don’t assert internal state; we only assert that calling it does not crash.)
TEST_F(CompactionReleaseInputsTest_183, ReleaseInputs_SafeAfterReset_183) {
  auto c = MakeCompactionAtLevel(2);

  // First release with no input set.
  c->ReleaseInputs();

  // Reset explicitly to nullptr again via peer and call release again.
  CompactionTestPeer::SetInputVersion(c.get(), nullptr);
  c->ReleaseInputs();

  SUCCEED();
}
