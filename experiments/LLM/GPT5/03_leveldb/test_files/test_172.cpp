// TEST_ID: 172
// Unit tests for VersionSet::MakeInputIterator

#include <gtest/gtest.h>
#include <gmock/gmock.h>

using ::testing::_;
using ::testing::Eq;
using ::testing::Return;
using ::testing::AllOf;
using ::testing::Field;
using ::testing::Property;
using ::testing::ElementsAre;

// ---- Minimal forward decls (interfaces only; no internal logic) ----
namespace leveldb {

struct ReadOptions {
  bool verify_checksums = false;
  bool fill_cache = true;
  const void* snapshot = nullptr;
};

struct FileMetaData {
  int refs = 0;
  int allowed_seeks = 1 << 30;
  uint64_t number = 0;
  uint64_t file_size = 0;
  // smallest/largest omitted (not observed by MakeInputIterator)
};

class Iterator { public: virtual ~Iterator() = default; };

struct Options {
  bool paranoid_checks = false;
  // Only fields used indirectly by MakeInputIterator are needed for tests
  void* env = nullptr;
};

struct InternalKeyComparator {};

// Forward decls to match usage in version_set.cc
class Version {
 public:
  class LevelFileNumIterator : public Iterator {
   public:
    LevelFileNumIterator(const InternalKeyComparator&, const std::vector<FileMetaData*>*) {}
  };
};

class TableCache {
 public:
  virtual ~TableCache() = default;
  virtual Iterator* NewIterator(const ReadOptions& options,
                                uint64_t file_number,
                                uint64_t file_size,
                                void** /*tableptr*/ = nullptr) = 0;
};

class Compaction {
 public:
  virtual ~Compaction() = default;
  virtual int level() const = 0;
  // Helpers to expose inputs for which=0/1 as observed behavior
  virtual const std::vector<FileMetaData*>& inputs(int which) const = 0;
};

class VersionSet {
 public:
  VersionSet(const std::string& /*dbname*/,
             const Options* options,
             TableCache* table_cache,
             const InternalKeyComparator* cmp)
      : options_(options), table_cache_(table_cache), icmp_(*cmp) {}

  Iterator* MakeInputIterator(Compaction* c); // defined in prod

 private:
  const Options* options_;
  TableCache* table_cache_;
  InternalKeyComparator icmp_;
};

} // namespace leveldb

// ---- Global seams for free helpers used by MakeInputIterator ----
// NOTE: We provide test doubles that record calls and return dummy iterators.
// Signatures are shaped to what VersionSet::MakeInputIterator uses.

namespace test_seams {
struct RecordedTwoLevelCall {
  int which; // 0 or 1 (we set this from our harness)
  // We can't introspect the internal iterator easily; we just count the call.
};

static std::vector<RecordedTwoLevelCall> g_two_level_calls;
static int g_merging_received_num = -1;

// A simple dummy iterator we can hand out
struct DummyIter : leveldb::Iterator {};

// Seam functions (ensure they match ODR names from prod build)
extern "C" leveldb::Iterator* NewTwoLevelIterator(
    leveldb::Iterator* /*index_iter*/,
    leveldb::Iterator* (*/*block_function*/)(void*, const leveldb::ReadOptions&),
    void* /*arg*/,
    const leveldb::ReadOptions& /*options*/) {
  g_two_level_calls.push_back({/*which=*/-1}); // marker; which is set by harness if desired
  static DummyIter k; return &k;
}

extern "C" leveldb::Iterator* NewMergingIterator(
    const leveldb::InternalKeyComparator* /*icmp*/,
    leveldb::Iterator** /*list*/,
    int num) {
  g_merging_received_num = num;
  static DummyIter k; return &k;
}
} // namespace test_seams

// ---- Mocks & fakes for collaborators ----
namespace leveldb {

class MockTableCache : public TableCache {
 public:
  MOCK_METHOD(Iterator*, NewIterator,
              (const ReadOptions& options, uint64_t file_number, uint64_t file_size, void** tableptr),
              (override));
};

// A concrete compaction test double exposing just what MakeInputIterator reads.
class FakeCompaction : public Compaction {
 public:
  explicit FakeCompaction(int lvl) : lvl_(lvl) {}
  int level() const override { return lvl_; }
  const std::vector<FileMetaData*>& inputs(int which) const override {
    return (which == 0) ? inputs0_ : inputs1_;
  }
  void addInput(int which, FileMetaData* f) {
    if (which == 0) inputs0_.push_back(f); else inputs1_.push_back(f);
  }
 private:
  int lvl_;
  std::vector<FileMetaData*> inputs0_;
  std::vector<FileMetaData*> inputs1_;
};

} // namespace leveldb

// ---- Test fixture ----
class MakeInputIteratorTest_172 : public ::testing::Test {
 protected:
  void SetUp() override {
    opts_.paranoid_checks = false; // default; tests flip as needed
    cmp_ = leveldb::InternalKeyComparator{};
    // reset seams
    test_seams::g_two_level_calls.clear();
    test_seams::g_merging_received_num = -1;
  }

  // Helpers to build file metadata quickly
  leveldb::FileMetaData* F(uint64_t num, uint64_t size) {
    auto* f = new leveldb::FileMetaData();
    f->number = num; f->file_size = size; return f;
  }

  leveldb::Options opts_;
  leveldb::InternalKeyComparator cmp_;
};

// --- Tests ---

// Level-0 inputs ⇒ one TableCache::NewIterator per file, merged together.
TEST_F(MakeInputIteratorTest_172, Level0_UsesDirectTableIterators_172) {
  using namespace leveldb;

  MockTableCache cache;
  VersionSet vs("db", &opts_, &cache, &cmp_);

  FakeCompaction c(/*level=*/0);
  auto* f1 = F(11, 100);
  auto* f2 = F(12, 200);
  c.addInput(0, f1);
  c.addInput(0, f2);

  // Captured ReadOptions must have fill_cache=false; verify_checksums==opts_.paranoid_checks.
  EXPECT_CALL(cache, NewIterator(
      AllOf(Field(&ReadOptions::fill_cache, Eq(false)),
            Field(&ReadOptions::verify_checksums, Eq(false))),
      /*file_number=*/11, /*file_size=*/100, _))
    .WillOnce(Return(new test_seams::DummyIter()));

  EXPECT_CALL(cache, NewIterator(
      AllOf(Field(&ReadOptions::fill_cache, Eq(false)),
            Field(&ReadOptions::verify_checksums, Eq(false))),
      /*file_number=*/12, /*file_size=*/200, _))
    .WillOnce(Return(new test_seams::DummyIter()));

  Iterator* out = vs.MakeInputIterator(&c);
  ASSERT_NE(out, nullptr);

  // For level-0, we expect exactly N (files) child iterators merged.
  EXPECT_EQ(test_seams::g_merging_received_num, 2);

  // No two-level iterator should be used for level-0.
  EXPECT_TRUE(test_seams::g_two_level_calls.empty());

  delete out;
  delete f1; delete f2;
}

// Non-zero level inputs (e.g., level=1) ⇒ one NewTwoLevelIterator per non-empty side.
TEST_F(MakeInputIteratorTest_172, NonZeroLevel_UsesTwoLevelIteratorsPerSide_172) {
  using namespace leveldb;

  MockTableCache cache;
  VersionSet vs("db", &opts_, &cache, &cmp_);

  FakeCompaction c(/*level=*/1);
  auto* f1 = F(21, 1000);
  auto* f2 = F(22, 1500);
  // Populate both sides; MakeInputIterator should NOT call TableCache::NewIterator directly.
  c.addInput(0, f1);
  c.addInput(1, f2);

  // Expect no direct table iterators for non-zero levels
  EXPECT_CALL(cache, NewIterator(_, _, _, _)).Times(0);

  Iterator* out = vs.MakeInputIterator(&c);
  ASSERT_NE(out, nullptr);

  // One two-level iterator per non-empty side => 2 merged
  EXPECT_EQ(test_seams::g_merging_received_num, 2);
  EXPECT_EQ(static_cast<int>(test_seams::g_two_level_calls.size()), 2);

  delete out;
  delete f1; delete f2;
}

// Level-0 across both sides (which=0 has files, which=1 empty) ⇒ correct count and params.
TEST_F(MakeInputIteratorTest_172, Level0_OnlyFirstSide_RespectsSpaceAndCount_172) {
  using namespace leveldb;

  MockTableCache cache;
  VersionSet vs("db", &opts_, &cache, &cmp_);

  FakeCompaction c(/*level=*/0);
  auto* f1 = F(31, 10);
  auto* f2 = F(32, 20);
  c.addInput(0, f1);
  c.addInput(0, f2);
  // which=1 empty

  EXPECT_CALL(cache, NewIterator(AllOf(Field(&ReadOptions::fill_cache, Eq(false)),
                                       Field(&ReadOptions::verify_checksums, Eq(false))),
                                 31, 10, _))
      .WillOnce(Return(new test_seams::DummyIter()));
  EXPECT_CALL(cache, NewIterator(AllOf(Field(&ReadOptions::fill_cache, Eq(false)),
                                       Field(&ReadOptions::verify_checksums, Eq(false))),
                                 32, 20, _))
      .WillOnce(Return(new test_seams::DummyIter()));

  Iterator* out = vs.MakeInputIterator(&c);
  ASSERT_NE(out, nullptr);

  // Exactly two children (for two files)
  EXPECT_EQ(test_seams::g_merging_received_num, 2);
  EXPECT_TRUE(test_seams::g_two_level_calls.empty());

  delete out;
  delete f1; delete f2;
}

// Paranoid checks on ⇒ verify_checksums=true passed to child iterators.
TEST_F(MakeInputIteratorTest_172, RespectsParanoidChecksInReadOptions_172) {
  using namespace leveldb;

  opts_.paranoid_checks = true; // flip on
  MockTableCache cache;
  VersionSet vs("db", &opts_, &cache, &cmp_);

  FakeCompaction c(/*level=*/0);
  auto* f1 = F(41, 101);
  c.addInput(0, f1);

  EXPECT_CALL(cache, NewIterator(
      AllOf(Field(&ReadOptions::fill_cache, Eq(false)),
            Field(&ReadOptions::verify_checksums, Eq(true))),
      41, 101, _))
    .WillOnce(Return(new test_seams::DummyIter()));

  Iterator* out = vs.MakeInputIterator(&c);
  ASSERT_NE(out, nullptr);

  EXPECT_EQ(test_seams::g_merging_received_num, 1);
  EXPECT_TRUE(test_seams::g_two_level_calls.empty());

  delete out;
  delete f1;
}

