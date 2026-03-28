// File: table_newiterator_test_423.cc

#include <gtest/gtest.h>
#include <gmock/gmock.h>

using ::testing::Eq;
using ::testing::IsNull;
using ::testing::NotNull;
using ::testing::Pointer;

// ---- Minimal public interfaces & dummies (external deps only) ----
namespace leveldb {

// Forward decls to match signatures used by Table::NewIterator
struct Slice { };
struct Status { };
struct Snapshot { };
struct Comparator { virtual ~Comparator() = default; };
struct Env { static Env* Default() { static Env e; return &e; } };
struct Logger { };
struct Cache { };
enum CompressionType { kSnappyCompression };

struct Options {
  const Comparator* comparator;
  bool create_if_missing = false;
  bool error_if_exists = false;
  bool paranoid_checks = false;
  Env* env;
  Logger* info_log = nullptr;
  size_t write_buffer_size = 4 * 1024 * 1024;
  int max_open_files = 1000;
  Cache* block_cache = nullptr;
  size_t block_size = 4 * 1024;
  int block_restart_interval = 16;
  size_t max_file_size = 2 * 1024 * 1024;
  CompressionType compression = kSnappyCompression;
  int zstd_compression_level = 1;
  bool reuse_logs = false;
  const void* filter_policy = nullptr;  // not used here

  // Minimal ctor per provided interface
  Options() : comparator(nullptr), env(Env::Default()) {}
};

struct ReadOptions {
  bool verify_checksums = false;
  bool fill_cache = true;
  const Snapshot* snapshot = nullptr;
};

// Minimal Iterator interface used by NewTwoLevelIterator & friends.
class Iterator {
 public:
  virtual ~Iterator() = default;
};

// Minimal BlockContents & Block to satisfy construction and call site.
struct BlockContents {
  std::string data;
  bool cachable = false;
  bool heap_allocated = false;
};

class Block {
 public:
  explicit Block(const BlockContents& contents) : contents_(contents) {}
  Iterator* NewIterator(const Comparator* /*comparator*/) {
    // Return the pre-configured iterator (can be nullptr to test boundary).
    return configured_iter_;
  }
  void SetIteratorToReturn(Iterator* it) { configured_iter_ = it; }
 private:
  BlockContents contents_;
  Iterator* configured_iter_ = nullptr;
};

// Forward declaration of Table for use in NewTwoLevelIterator signature.
class Table;

// ---- Link-time fake for the external factory: NewTwoLevelIterator ----
// Signature: Iterator* NewTwoLevelIterator(Iterator* index_iter,
//                                          Iterator* (*block_reader)(void*, const ReadOptions&, const Slice&),
//                                          void* arg,
//                                          const ReadOptions& options);
using BlockReaderFn = Iterator* (*)(void*, const ReadOptions&, const Slice&);

// Capture struct to assert the arguments that Table::NewIterator forwards.
struct NewTwoLevelCallCapture {
  Iterator* passed_index_iter = nullptr;
  BlockReaderFn passed_reader = nullptr;
  void* passed_arg = nullptr;
  ReadOptions passed_options{};
  Iterator* iterator_to_return = nullptr;
};

// Global capture used by tests (since we’re substituting a free function).
static NewTwoLevelCallCapture g_capture;

// The *fake* implementation that our tests will link against.
Iterator* NewTwoLevelIterator(Iterator* index_iter,
                              BlockReaderFn reader,
                              void* arg,
                              const ReadOptions& options) {
  g_capture.passed_index_iter = index_iter;
  g_capture.passed_reader = reader;
  g_capture.passed_arg = arg;
  g_capture.passed_options = options;
  return g_capture.iterator_to_return;  // tests control the returned Iterator*
}

// ---- Minimal Table bits needed to test NewIterator delegation ----
class Table {
 public:
  // Rep as provided (public fields suffice to set up dependencies)
  struct Rep {
    Options options;
    uint64_t cache_id = 0;
    void* filter = nullptr;
    const char* filter_data = nullptr;
    // (metaindex_handle omitted since unused here)
    Block* index_block = nullptr;
    ~Rep() = default;
  };

  // Provide a tiny, test-only constructor to supply Rep*
  explicit Table(Rep* rep) : rep_(rep) {}

  // The block reader symbol (we only need its address; body never called here)
  static Iterator* BlockReader(void*, const ReadOptions&, const Slice&) {
    return nullptr;
  }

  // The function under test (per provided code)
  Iterator* NewIterator(const ReadOptions& options) const {
    return NewTwoLevelIterator(
        rep_->index_block->NewIterator(rep_->options.comparator),
        &Table::BlockReader,
        const_cast<Table*>(this),
        options);
  }

 private:
  Rep* const rep_;
};

}  // namespace leveldb

// ------------------------------ Tests ------------------------------

namespace {

struct DummyComparator : public leveldb::Comparator {};

// A simple dummy Iterator we can identify in assertions
struct DummyIter : public leveldb::Iterator {};

// Test fixture to share setup
class TableNewIteratorTest_423 : public ::testing::Test {
 protected:
  void SetUp() override {
    // Fresh capture before each test
    g_capture = leveldb::NewTwoLevelCallCapture{};
  }

  // Helpers to build a Table wired with a Block that returns `iter_to_return_from_block`
  std::unique_ptr<leveldb::Table> MakeTable(leveldb::Iterator* iter_to_return_from_block,
                                            const leveldb::Comparator* cmp = nullptr) {
    // Build the Rep with options and index block
    rep_ = std::make_unique<leveldb::Table::Rep>();
    rep_->options.comparator = cmp;  // may be nullptr (boundary case)
    // Configure a Block whose NewIterator returns our desired iterator
    block_ = std::make_unique<leveldb::Block>(leveldb::BlockContents{});
    block_->SetIteratorToReturn(iter_to_return_from_block);
    rep_->index_block = block_.get();
    return std::make_unique<leveldb::Table>(rep_.get());
  }

  std::unique_ptr<leveldb::Table::Rep> rep_;
  std::unique_ptr<leveldb::Block> block_;
};

}  // namespace

// ---- Normal operation: forwards args & returns factory result
TEST_F(TableNewIteratorTest_423, ForwardsToNewTwoLevelIterator_AndReturnsFactoryResult_423) {
  using namespace leveldb;

  DummyComparator cmp;
  DummyIter index_iter_from_block;     // what Block::NewIterator will hand back
  DummyIter factory_return_iter;       // what NewTwoLevelIterator fake will return

  // Build a table that yields `index_iter_from_block`
  auto table = MakeTable(&index_iter_from_block, &cmp);

  // Set the fake factory's return value
  g_capture.iterator_to_return = &factory_return_iter;

  // Prepare ReadOptions with distinct values to verify forwarding
  ReadOptions ro;
  ro.verify_checksums = true;
  ro.fill_cache = false;
  ro.snapshot = reinterpret_cast<const Snapshot*>(0x1234);

  Iterator* got = table->NewIterator(ro);

  // Returned iterator is exactly the factory's return
  EXPECT_THAT(got, Eq(&factory_return_iter));

  // Verify the forwarded parameters captured by our fake factory
  EXPECT_THAT(g_capture.passed_index_iter, Eq(&index_iter_from_block)) << "Index iterator should come from Block::NewIterator";
  EXPECT_THAT(g_capture.passed_reader, Eq(&Table::BlockReader)) << "Must pass &Table::BlockReader";
  EXPECT_THAT(g_capture.passed_arg, Eq(static_cast<void*>(table.get()))) << "`arg` must be `this` (const_cast<Table*>)";
  EXPECT_TRUE(g_capture.passed_options.verify_checksums);
  EXPECT_FALSE(g_capture.passed_options.fill_cache);
  EXPECT_THAT(g_capture.passed_options.snapshot, Eq(ro.snapshot));
}

// ---- Boundary: comparator may be nullptr; still should forward correctly
TEST_F(TableNewIteratorTest_423, WorksWhenComparatorIsNull_423) {
  using namespace leveldb;

  DummyIter index_iter_from_block;
  DummyIter factory_return_iter;
  auto table = MakeTable(&index_iter_from_block, /*cmp=*/nullptr);
  g_capture.iterator_to_return = &factory_return_iter;

  ReadOptions ro;  // default options
  Iterator* got = table->NewIterator(ro);

  EXPECT_THAT(got, Eq(&factory_return_iter));
  EXPECT_THAT(g_capture.passed_index_iter, Eq(&index_iter_from_block));
  EXPECT_THAT(g_capture.passed_reader, Eq(&Table::BlockReader));
  EXPECT_THAT(g_capture.passed_arg, Eq(static_cast<void*>(table.get())));
  // Options defaults forwarded
  EXPECT_FALSE(g_capture.passed_options.verify_checksums);
  EXPECT_TRUE(g_capture.passed_options.fill_cache);
  EXPECT_THAT(g_capture.passed_options.snapshot, IsNull());
}

// ---- Boundary: Block::NewIterator returns nullptr; ensure it is passed through unmodified
TEST_F(TableNewIteratorTest_423, PassesThroughNullIndexIteratorFromBlock_423) {
  using namespace leveldb;

  // Configure Block to return nullptr
  auto table = MakeTable(/*iter_to_return_from_block=*/nullptr, /*cmp=*/nullptr);

  DummyIter factory_return_iter;
  g_capture.iterator_to_return = &factory_return_iter;

  ReadOptions ro;
  Iterator* got = table->NewIterator(ro);

  EXPECT_THAT(got, Eq(&factory_return_iter));
  EXPECT_THAT(g_capture.passed_index_iter, IsNull()) << "Should forward nullptr index iterator to factory";
  EXPECT_THAT(g_capture.passed_reader, Eq(&Table::BlockReader));
  EXPECT_THAT(g_capture.passed_arg, Eq(static_cast<void*>(table.get())));
}

// ---- Options variety: toggling fields should be forwarded exactly
TEST_F(TableNewIteratorTest_423, ForwardsReadOptionsExactly_423) {
  using namespace leveldb;

  DummyComparator cmp;
  DummyIter index_iter_from_block;
  DummyIter factory_return_iter;
  auto table = MakeTable(&index_iter_from_block, &cmp);
  g_capture.iterator_to_return = &factory_return_iter;

  ReadOptions ro;
  ro.verify_checksums = false;
  ro.fill_cache = true;
  ro.snapshot = nullptr;

  Iterator* got = table->NewIterator(ro);
  EXPECT_THAT(got, Eq(&factory_return_iter));

  EXPECT_FALSE(g_capture.passed_options.verify_checksums);
  EXPECT_TRUE(g_capture.passed_options.fill_cache);
  EXPECT_THAT(g_capture.passed_options.snapshot, IsNull());
}
