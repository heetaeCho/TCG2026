// File: db/version_set_approximate_offset_of_test.cc

#include "gtest/gtest.h"
#include "db/version_set.h"
#include "db/version_edit.h"
#include "db/dbformat.h"
#include "db/table_cache.h"
#include "util/mutexlock.h"
#include "leveldb/comparator.h"
#include "leveldb/options.h"
#include "leveldb/env.h"

namespace leveldb {

namespace {

// Helper to build an InternalKey from a user key string.
static InternalKey IKey(const std::string& user, SequenceNumber s = 100,
                        ValueType t = kTypeValue) {
  return InternalKey(Slice(user), s, t);
}

// Minimal TableCache that won't be used (we avoid overlap paths).
// We still construct a real TableCache to satisfy VersionSet's ctor.
class DummyTableCache : public TableCache {
 public:
  DummyTableCache(const std::string& dbname, const Options& options, int entries)
      : TableCache(dbname, options, entries) {}
};

struct VSFixture {
  Env* env = Env::Default();
  Options options;
  std::string dbname = "/tmp/approx_offset_unittest";
  InternalKeyComparator icmp{BytewiseComparator()};
  std::unique_ptr<TableCache> tcache;
  std::unique_ptr<VersionSet> vset;

  VSFixture() {
    options.env = env;
    // Use a tiny cache; it shouldn't be touched in these tests.
    tcache.reset(new DummyTableCache(dbname, options, 16));
    vset.reset(new VersionSet(dbname, &options, tcache.get(), &icmp));
    // Install an initial empty version so that current() is valid.
    VersionEdit ve;
    port::Mutex mu;
    ASSERT_TRUE(vset->LogAndApply(&ve, &mu).ok());
  }

  // Adds a file [smallest, largest] with given size into the manifest via LogAndApply.
  void AddFile(int level, uint64_t number, uint64_t size,
               const InternalKey& smallest, const InternalKey& largest) {
    VersionEdit ve;
    ve.AddFile(level, number, smallest, largest, size);
    port::Mutex mu;
    ASSERT_TRUE(vset->LogAndApply(&ve, &mu).ok());
  }
};

}  // namespace

// ========================== TESTS ===============================

// Normal case: sums file_size for all files whose largest <= ikey (all in L0, non-overlap path)
TEST(VersionSet_ApproximateOffsetOf_168, SumsSizesForFilesBeforeKey_L0_168) {
  VSFixture fx;

  // Level-0 files with non-overlap relative to ikey "m"
  fx.AddFile(/*level=*/0, /*number=*/1, /*size=*/100, IKey("a"), IKey("b"));
  fx.AddFile(/*level=*/0, /*number=*/2, /*size=*/200, IKey("c"), IKey("h"));
  fx.AddFile(/*level=*/0, /*number=*/3, /*size=*/300, IKey("x"), IKey("z"));  // after ikey

  // ikey is "m" (between 'h' and 'x'), so first two file sizes should be counted: 100 + 200 = 300
  InternalKey target = IKey("m");
  uint64_t off = fx.vset->ApproximateOffsetOf(fx.vset->current(), target);
  EXPECT_EQ(off, 300u);
}

// Boundary behavior (level > 0): if smallest > ikey, iteration breaks for that level.
// We set L1 such that ikey < smallest of first file; nothing from L1 is counted even if
// later files could have largest <= ikey.
TEST(VersionSet_ApproximateOffsetOf_168, EarlyBreakOnHigherLevelWhenKeyBeforeFirstFile_168) {
  VSFixture fx;

  // Only Level-1 files. ikey = "0" lies before the first file's smallest "a".
  fx.AddFile(/*level=*/1, /*number=*/10, /*size=*/400, IKey("a"), IKey("b"));
  fx.AddFile(/*level=*/1, /*number=*/11, /*size=*/500, IKey("b"), IKey("c"));

  InternalKey target = IKey("0");  // strictly smaller than "a"
  uint64_t off = fx.vset->ApproximateOffsetOf(fx.vset->current(), target);

  // Since smallest("a") > ikey and level > 0, the code breaks and adds nothing.
  EXPECT_EQ(off, 0u);
}

// Mixed multi-level aggregation: counts qualifying files across levels,
// respects early-break per-level for higher levels, and still aggregates from other levels.
TEST(VersionSet_ApproximateOffsetOf_168, AggregatesAcrossLevelsWithPerLevelEarlyBreak_168) {
  VSFixture fx;

  // Level 0: some before, some after ikey = "m"
  fx.AddFile(/*level=*/0, /*number=*/1, /*size=*/120, IKey("a"), IKey("f"));   // before
  fx.AddFile(/*level=*/0, /*number=*/2, /*size=*/180, IKey("g"), IKey("k"));   // before
  fx.AddFile(/*level=*/0, /*number=*/3, /*size=*/250, IKey("x"), IKey("z"));   // after

  // Level 1: design it so we hit 'largest <= ikey' for one file and early-break for another case
  fx.AddFile(/*level=*/1, /*number=*/20, /*size=*/300, IKey("n"), IKey("q"));  // after (smallest > "m") -> break at L1
  // Put another file that would be <= ikey if not for early break; the break ensures it's ignored.
  fx.AddFile(/*level=*/1, /*number=*/21, /*size=*/90,  IKey("0"), IKey("0"));  // would have been before ('0' < 'm')

  InternalKey target = IKey("m");
  uint64_t off = fx.vset->ApproximateOffsetOf(fx.vset->current(), target);

  // Expected: sum only L0 files whose largest <= "m" (120 + 180 = 300).
  // L1 contributes nothing because the first L1 file has smallest > ikey, causing break.
  EXPECT_EQ(off, 300u);
}

}  // namespace leveldb
