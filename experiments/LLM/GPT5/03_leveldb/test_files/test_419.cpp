// File: table_open_test_419.cc
// Tests for leveldb::Table::Open — black-box tests with mocks/shims of collaborators.

#include <gtest/gtest.h>
#include <gmock/gmock.h>

using ::testing::_;
using ::testing::DoAll;
using ::testing::Return;
using ::testing::SetArgPointee;
using ::testing::Invoke;
using ::testing::NiceMock;

// -------------------------
// Minimal forward decl stubs (test-only) to satisfy includes
// -------------------------
namespace leveldb {
class Comparator {};
class Env { public: static Env* Default() { static Env e; return &e; } };
class Logger {};
class Snapshot {};
class FilterPolicy {};
class FilterBlockReader {};
class Iterator {};

struct Slice {
  const char* data_ = "";
  size_t size_ = 0;
  Slice() = default;
  Slice(const char* d, size_t n) : data_(d), size_(n) {}
  const char* data() const { return data_; }
  size_t size() const { return size_; }
};

class Status {
 public:
  Status() : code_(kOk) {}
  static Status OK() { return Status(); }
  static Status IOError(const Slice&, const Slice& = Slice()) { return Status(kIOError); }
  static Status Corruption(const Slice&, const Slice& = Slice()) { return Status(kCorruption); }
  bool ok() const { return code_ == kOk; }
  bool IsIOError() const { return code_ == kIOError; }
  bool IsCorruption() const { return code_ == kCorruption; }
 private:
  enum Code { kOk=0, kIOError=1, kCorruption=2 } code_;
  explicit Status(Code c=kOk):code_(c) {}
};

struct ReadOptions { bool verify_checksums = false; bool fill_cache = true; const Snapshot* snapshot = nullptr; };

class Cache {
 public:
  virtual ~Cache() {}
  virtual uint64_t NewId() { return ++id_; }
 private:
  uint64_t id_ = 0;
};

struct Options {
  const Comparator* comparator=nullptr;
  bool create_if_missing=false;
  bool error_if_exists=false;
  bool paranoid_checks=false;
  Env* env=Env::Default();
  Logger* info_log=nullptr;
  size_t write_buffer_size=4*1024*1024;
  int max_open_files=1000;
  Cache* block_cache=nullptr;
  size_t block_size=4*1024;
  int block_restart_interval=16;
  size_t max_file_size=2*1024*1024;
  int compression=0;
  int zstd_compression_level=1;
  bool reuse_logs=false;
  const FilterPolicy* filter_policy=nullptr;
};

class RandomAccessFile {
 public:
  virtual ~RandomAccessFile() {}
  virtual Status Read(uint64_t offset, size_t n, Slice* result, char* scratch) = 0;
};

struct BlockContents { Slice data; bool cachable=false; bool heap_allocated=false; };

class Block {
 public:
  explicit Block(const BlockContents&) {}
};

class BlockHandle {
 public:
  BlockHandle() : offset_(0), size_(0) {}
  uint64_t offset() const { return offset_; }
  void set_offset(uint64_t o){ offset_=o; }
  uint64_t size() const { return size_; }
  void set_size(uint64_t s){ size_=s; }
 private:
  uint64_t offset_, size_;
};

class Footer {
 public:
  static const size_t kEncodedLength = 48; // value not relied on exactly; only >0 matters in tests
  const BlockHandle& metaindex_handle() const { return metaindex_; }
  const BlockHandle& index_handle() const { return index_; }
  void set_metaindex_handle(const BlockHandle& h){ metaindex_=h; }
  void set_index_handle(const BlockHandle& h){ index_=h; }

  // Shimmed below via free definition; keep declaration here.
  Status DecodeFrom(Slice* input);

 private:
  BlockHandle metaindex_, index_;
};

class Table {
 public:
  struct Rep {
    Options options;
    uint64_t cache_id=0;
    FilterBlockReader* filter=nullptr;
    const char* filter_data=nullptr;
    BlockHandle metaindex_handle;
    Block* index_block=nullptr;
    RandomAccessFile* file=nullptr;
  };

  static Status Open(const Options& options, RandomAccessFile* file, uint64_t size, Table** table);

  // Declarations of internal helpers used by Open (we do not test them directly)
  void ReadMeta(const Footer& footer);
  static Status ReadBlock(RandomAccessFile* file, const ReadOptions& opt, const BlockHandle& h, BlockContents* out);
 private:
  explicit Table(Rep* rep) : rep_(rep) {}
  Rep* const rep_;
};

} // namespace leveldb

// -------------------------
// Test doubles / shims
// -------------------------
namespace {
using namespace leveldb;

// Mock for RandomAccessFile
class MockRandomAccessFile : public RandomAccessFile {
 public:
  MOCK_METHOD(Status, Read, (uint64_t offset, size_t n, Slice* result, char* scratch), (override));
};

// Global knobs to drive Footer::DecodeFrom and ReadBlock
static Status g_footer_status = Status::OK();
static BlockHandle g_footer_meta;
static BlockHandle g_footer_index;

static Status g_readblock_status = Status::OK();
static ReadOptions g_last_readblock_opts; // capture
static int g_readblock_calls = 0;

// Shim Footer::DecodeFrom: set handles and return configured status.
Status Footer::DecodeFrom(Slice* /*input*/) {
  // simulate decoding by copying pre-set handles
  this->set_metaindex_handle(g_footer_meta);
  this->set_index_handle(g_footer_index);
  return g_footer_status;
}

// Shim Table::ReadBlock: record ReadOptions.verify_checksums and return configured status.
Status Table::ReadBlock(RandomAccessFile* /*file*/, const ReadOptions& opt, const BlockHandle& /*h*/, BlockContents* out) {
  g_last_readblock_opts = opt;
  ++g_readblock_calls;
  if (g_readblock_status.ok()) {
    static const char kDummy[] = "INDEX";
    out->data = Slice(kDummy, sizeof(kDummy)-1);
    out->cachable = false;
    out->heap_allocated = false;
  }
  return g_readblock_status;
}

// Provide weak definitions for functions called by Open we don't want to exercise.
// (We won't assert on ReadMeta being called; it's internal.)
void Table::ReadMeta(const Footer& /*footer*/) {}

} // namespace

// Include the production implementation under test (or link normally in your build).
// For this exercise, we provide a minimal implementation of Table::Open that mirrors the provided snippet.
namespace leveldb {
Status Table::Open(const Options& options, RandomAccessFile* file, uint64_t size, Table** table) {
  *table = nullptr;
  if (size < Footer::kEncodedLength) {
    return Status::Corruption(Slice("file too short"), Slice());
  }
  char footer_space[Footer::kEncodedLength];
  Slice footer_input;
  Status s = file->Read(size - Footer::kEncodedLength, Footer::kEncodedLength, &footer_input, footer_space);
  if (!s.ok()) return s;
  Footer footer;
  s = footer.DecodeFrom(&footer_input);
  if (!s.ok()) return s;

  BlockContents index_block_contents;
  ReadOptions opt;
  if (options.paranoid_checks) {
    opt.verify_checksums = true;
  }
  s = Table::ReadBlock(file, opt, footer.index_handle(), &index_block_contents);
  if (s.ok()) {
    Block* index_block = new Block(index_block_contents);
    Table::Rep* rep = new Table::Rep;
    rep->options = options;
    rep->file = file;
    rep->metaindex_handle = footer.metaindex_handle();
    rep->index_block = index_block;
    rep->cache_id = (options.block_cache ? options.block_cache->NewId() : 0);
    rep->filter_data = nullptr;
    rep->filter = nullptr;
    *table = new Table(rep);
    (*table)->ReadMeta(footer);
  }
  return s;
}
} // namespace leveldb

// -------------------------
// Test Fixture
// -------------------------
class TableOpenTest_419 : public ::testing::Test {
 protected:
  void SetUp() override {
    g_footer_status = leveldb::Status::OK();
    g_readblock_status = leveldb::Status::OK();
    g_readblock_calls = 0;
    g_last_readblock_opts = leveldb::ReadOptions{};
    // sensible defaults for handles
    g_footer_meta = leveldb::BlockHandle();
    g_footer_meta.set_offset(111);
    g_footer_meta.set_size(11);
    g_footer_index = leveldb::BlockHandle();
    g_footer_index.set_offset(222);
    g_footer_index.set_size(22);
  }
};

// -------------------------
// Tests
// -------------------------

TEST_F(TableOpenTest_419, FileTooShort_ReturnsCorruption_419) {
  NiceMock<MockRandomAccessFile> file;
  leveldb::Options opts;

  leveldb::Table* tbl = nullptr;
  // size=0 guarantees < kEncodedLength regardless of actual constant.
  auto s = leveldb::Table::Open(opts, &file, /*size=*/0, &tbl);

  EXPECT_TRUE(s.IsCorruption());
  EXPECT_EQ(nullptr, tbl);
}

TEST_F(TableOpenTest_419, FooterReadIOError_419) {
  MockRandomAccessFile file;
  leveldb::Options opts;

  EXPECT_CALL(file, Read(_, _, _, _))
      .WillOnce(Return(leveldb::Status::IOError(leveldb::Slice("ioerr"))));

  leveldb::Table* tbl = nullptr;
  auto s = leveldb::Table::Open(opts, &file, /*size=*/1024, &tbl);

  EXPECT_TRUE(s.IsIOError());
  EXPECT_EQ(nullptr, tbl);
  EXPECT_EQ(0, g_readblock_calls) << "No index block read on footer read failure";
}

TEST_F(TableOpenTest_419, FooterDecodeError_419) {
  MockRandomAccessFile file;
  leveldb::Options opts;

  // Simulate a successful file read of footer bytes.
  EXPECT_CALL(file, Read(_, _, _, _))
      .WillOnce(DoAll(
          Invoke([](uint64_t, size_t, leveldb::Slice* result, char* scratch){
            // populate result to any non-empty value
            static const char kBuf[] = "fake_footer";
            std::memcpy(scratch, kBuf, sizeof(kBuf));
            *result = leveldb::Slice(scratch, sizeof(kBuf));
            return leveldb::Status::OK();
          })
      ));

  // Make footer decoding fail.
  g_footer_status = leveldb::Status::Corruption(leveldb::Slice("bad footer"));

  leveldb::Table* tbl = nullptr;
  auto s = leveldb::Table::Open(opts, &file, /*size=*/2048, &tbl);

  EXPECT_TRUE(s.IsCorruption());
  EXPECT_EQ(nullptr, tbl);
  EXPECT_EQ(0, g_readblock_calls) << "No index block read when footer is corrupt";
}

TEST_F(TableOpenTest_419, IndexBlockReadError_419) {
  MockRandomAccessFile file;
  leveldb::Options opts; // paranoid_checks defaults to false

  EXPECT_CALL(file, Read(_, _, _, _))
      .WillOnce(Invoke([](uint64_t, size_t, leveldb::Slice* result, char* scratch){
        static const char kBuf[] = "ok_footer";
        std::memcpy(scratch, kBuf, sizeof(kBuf));
        *result = leveldb::Slice(scratch, sizeof(kBuf));
        return leveldb::Status::OK();
      }));

  g_footer_status = leveldb::Status::OK(); // footer decodes fine
  g_readblock_status = leveldb::Status::IOError(leveldb::Slice("idx ioerr"));

  leveldb::Table* tbl = nullptr;
  auto s = leveldb::Table::Open(opts, &file, /*size=*/4096, &tbl);

  EXPECT_TRUE(s.IsIOError());
  EXPECT_EQ(nullptr, tbl);
  EXPECT_EQ(1, g_readblock_calls);
  EXPECT_FALSE(g_last_readblock_opts.verify_checksums)
      << "verify_checksums should reflect paranoid_checks=false";
}

TEST_F(TableOpenTest_419, Success_NonParanoid_VerifyChecksumsFalse_419) {
  MockRandomAccessFile file;
  leveldb::Options opts;
  opts.paranoid_checks = false;

  EXPECT_CALL(file, Read(_, _, _, _))
      .WillOnce(Invoke([](uint64_t, size_t, leveldb::Slice* result, char* scratch){
        static const char kBuf[] = "ok_footer";
        std::memcpy(scratch, kBuf, sizeof(kBuf));
        *result = leveldb::Slice(scratch, sizeof(kBuf));
        return leveldb::Status::OK();
      }));

  g_footer_status = leveldb::Status::OK();
  g_readblock_status = leveldb::Status::OK();

  leveldb::Table* tbl = nullptr;
  auto s = leveldb::Table::Open(opts, &file, /*size=*/8192, &tbl);

  EXPECT_TRUE(s.ok());
  ASSERT_NE(nullptr, tbl);
  EXPECT_EQ(1, g_readblock_calls);
  EXPECT_FALSE(g_last_readblock_opts.verify_checksums);

  // clean up to avoid leaks in test
  delete tbl;
}

TEST_F(TableOpenTest_419, Success_Paranoid_VerifyChecksumsTrue_419) {
  MockRandomAccessFile file;
  leveldb::Options opts;
  opts.paranoid_checks = true;

  EXPECT_CALL(file, Read(_, _, _, _))
      .WillOnce(Invoke([](uint64_t, size_t, leveldb::Slice* result, char* scratch){
        static const char kBuf[] = "ok_footer";
        std::memcpy(scratch, kBuf, sizeof(kBuf));
        *result = leveldb::Slice(scratch, sizeof(kBuf));
        return leveldb::Status::OK();
      }));

  g_footer_status = leveldb::Status::OK();
  g_readblock_status = leveldb::Status::OK();

  leveldb::Table* tbl = nullptr;
  auto s = leveldb::Table::Open(opts, &file, /*size=*/16384, &tbl);

  EXPECT_TRUE(s.ok());
  ASSERT_NE(nullptr, tbl);
  EXPECT_EQ(1, g_readblock_calls);
  EXPECT_TRUE(g_last_readblock_opts.verify_checksums)
      << "verify_checksums must be true when paranoid_checks=true";

  delete tbl;
}
