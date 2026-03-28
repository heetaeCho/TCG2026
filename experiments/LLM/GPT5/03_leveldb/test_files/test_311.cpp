// db_impl_put_test.cc

#include <gtest/gtest.h>
#include <string>

// ---- Minimal public interfaces from the prompt ----
namespace leveldb {

// From leveldb/options.h (prompt)
struct WriteOptions {
  bool sync = false;
  WriteOptions() = default;
};

// From leveldb/slice.h (prompt – only what we need in tests)
class Slice {
 public:
  Slice() : data_(""), size_(0) {}
  Slice(const char* d, size_t n) : data_(d), size_(n) {}
  Slice(const std::string& s) : data_(s.data()), size_(s.size()) {}
  Slice(const char* s) : data_(s), size_(strlen(s)) {}
  const char* data() const { return data_; }
  size_t size() const { return size_; }
  std::string ToString() const { return std::string(data_, size_); }
 private:
  const char* data_;
  size_t size_;
};

// We rely on common LevelDB Status API shape: OK(), ok(), and an error factory.
// If your actual Status differs, adjust the two places marked with "Status adapter".
class Status {
 public:
  static Status OK() { return Status(true, ""); }
  static Status Corruption(const std::string& msg) { return Status(false, "Corruption: " + msg); }
  bool ok() const { return ok_; }
  std::string ToString() const { return msg_.empty() ? "OK" : msg_; }
 private:
  bool ok_;
  std::string msg_;
  Status(bool ok, std::string msg) : ok_(ok), msg_(std::move(msg)) {}
};

// From leveldb/db.h (prompt – only what we need)
class DB {
 public:
  DB() = default;
  DB(const DB&) = delete;
  virtual ~DB() {}
  virtual Status Put(const WriteOptions& options, const Slice& key, const Slice& value);
};

}  // namespace leveldb

// ---- Code under test: include the provided implementation snippet ----
// File: db/db_impl.cc (prompt)
namespace leveldb { class DBImpl { public: Status Put(const WriteOptions& o, const Slice& key, const Slice& val) { return DB::Put(o, key, val); } }; }

// ---- Test-only seam: define DB::Put to record calls and return a configurable Status ----
namespace {
using namespace leveldb;

int g_put_call_count = 0;
WriteOptions g_last_options{};
Slice g_last_key;
Slice g_last_value;
Status g_next_status = Status::OK();  // Status adapter: default to OK

}  // namespace

namespace leveldb {
Status DB::Put(const WriteOptions& options, const Slice& key, const Slice& value) {
  // Record observable interaction
  ++g_put_call_count;
  g_last_options = options;
  g_last_key = key;
  g_last_value = value;
  // Return whatever the test configured
  return g_next_status;  // Status adapter
}
}  // namespace leveldb

// ---- Tests ----

class DBImplPutTest_311 : public ::testing::Test {
 protected:
  void SetUp() override {
    g_put_call_count = 0;
    g_last_options = leveldb::WriteOptions{};
    g_last_key = leveldb::Slice();
    g_last_value = leveldb::Slice();
    g_next_status = leveldb::Status::OK();  // Status adapter
  }
};

TEST_F(DBImplPutTest_311, ForwardsArgsAndReturnsOk_311) {
  leveldb::DBImpl dbimpl;

  leveldb::WriteOptions opts;
  opts.sync = true;
  leveldb::Slice key("alpha");
  leveldb::Slice val("beta");

  g_next_status = leveldb::Status::OK();  // expect success

  leveldb::Status s = dbimpl.Put(opts, key, val);

  EXPECT_TRUE(s.ok());                            // Status adapter
  EXPECT_EQ(1, g_put_call_count);                 // called exactly once
  EXPECT_EQ(std::string("alpha"), g_last_key.ToString());
  EXPECT_EQ(std::string("beta"), g_last_value.ToString());
  EXPECT_TRUE(g_last_options.sync);               // options forwarded
}

TEST_F(DBImplPutTest_311, PropagatesErrorFromBase_311) {
  leveldb::DBImpl dbimpl;

  leveldb::WriteOptions opts;  // default sync=false
  leveldb::Slice key("k1");
  leveldb::Slice val("v1");

  g_next_status = leveldb::Status::Corruption("boom");  // simulate base error (Status adapter)

  leveldb::Status s = dbimpl.Put(opts, key, val);

  EXPECT_FALSE(s.ok());                          // error should propagate
  EXPECT_EQ(1, g_put_call_count);                // base called
  EXPECT_EQ(std::string("k1"), g_last_key.ToString());
  EXPECT_EQ(std::string("v1"), g_last_value.ToString());
  EXPECT_FALSE(g_last_options.sync);
}

TEST_F(DBImplPutTest_311, HandlesEmptyKeyAndValue_311) {
  leveldb::DBImpl dbimpl;

  leveldb::WriteOptions opts;
  leveldb::Slice empty_key;   // ""
  leveldb::Slice empty_val;   // ""

  g_next_status = leveldb::Status::OK();  // Status adapter

  leveldb::Status s = dbimpl.Put(opts, empty_key, empty_val);

  EXPECT_TRUE(s.ok());                            // still OK
  EXPECT_EQ(1, g_put_call_count);                 // base called
  EXPECT_EQ(std::string(""), g_last_key.ToString());
  EXPECT_EQ(std::string(""), g_last_value.ToString());
}

// Optional: non-ASCII / binary-ish content to ensure pass-through (no re-encoding assumptions)
TEST_F(DBImplPutTest_311, ForwardsBinaryLikeContent_311) {
  leveldb::DBImpl dbimpl;

  const char kData[] = {'\0', 'A', '\n', 'Z'};
  leveldb::Slice key("bin");
  leveldb::Slice val(kData, sizeof(kData));  // includes NULs

  g_next_status = leveldb::Status::OK();  // Status adapter

  leveldb::Status s = dbimpl.Put(leveldb::WriteOptions{}, key, val);
  EXPECT_TRUE(s.ok());
  EXPECT_EQ(1, g_put_call_count);
  EXPECT_EQ(std::string("bin"), g_last_key.ToString());
  ASSERT_EQ(sizeof(kData), g_last_value.size());
  // Compare as strings constructed from size to keep embedded NULs
  EXPECT_EQ(std::string(kData, sizeof(kData)), g_last_value.ToString());
}
