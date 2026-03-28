// db_impl_compact_memtable_test.cc
#include <gtest/gtest.h>
#include <functional>
#include "db/db_impl.h"        // DBImpl
#include "leveldb/status.h"    // Status
#include "leveldb/write_batch.h" // WriteBatch (decl only; not used directly but included for signature)
#include "leveldb/options.h"   // Options, WriteOptions

using namespace leveldb;

namespace {

class TestableDBImpl : public DBImpl {
 public:
  explicit TestableDBImpl(const Options& opt, const std::string& name)
      : DBImpl(opt, name) {}

  // Test hook to control Write()'s returned Status.
  void SetWriteStub(std::function<Status(const WriteOptions&, WriteBatch*)> stub) {
    write_stub_ = std::move(stub);
  }

  // Observation getters for assertions.
  int write_call_count() const { return write_call_count_; }
  WriteBatch* last_updates_arg() const { return last_updates_arg_; }

 protected:
  // Override the public virtual method to observe the call and return a controlled Status.
  Status Write(const WriteOptions& options, WriteBatch* updates) override {
    ++write_call_count_;
    last_updates_arg_ = updates;
    if (write_stub_) {
      return write_stub_(options, updates);
    }
    return Status::OK();
  }

 private:
  std::function<Status(const WriteOptions&, WriteBatch*)> write_stub_;
  int write_call_count_ = 0;
  WriteBatch* last_updates_arg_ = reinterpret_cast<WriteBatch*>(0xDEADBEEF); // sentinel to ensure it changes
};

Options MakeDefaultOptions() {
  Options o;
  // Keep defaults; we don’t rely on any particular option values.
  return o;
}

}  // namespace

// Verifies: TEST_CompactMemTable invokes Write exactly once with nullptr updates.
TEST(DBImpl_CompactMemTableTest_303, CallsWriteOnceWithNullUpdates_303) {
  Options opt = MakeDefaultOptions();
  TestableDBImpl db(opt, "testdb_calls_once");

  db.SetWriteStub([](const WriteOptions&, WriteBatch* updates) {
    // Ensure TEST_CompactMemTable passes nullptr for 'updates'.
    EXPECT_EQ(updates, nullptr);
    return Status::OK();
  });

  Status s = db.TEST_CompactMemTable();

  EXPECT_TRUE(s.ok());
  EXPECT_EQ(db.write_call_count(), 1);
  EXPECT_EQ(db.last_updates_arg(), nullptr);
}

// Verifies: When Write returns an IOError, TEST_CompactMemTable propagates that error.
TEST(DBImpl_CompactMemTableTest_303, ReturnsWriteError_303) {
  Options opt = MakeDefaultOptions();
  TestableDBImpl db(opt, "testdb_error_propagation");

  db.SetWriteStub([](const WriteOptions&, WriteBatch* updates) {
    EXPECT_EQ(updates, nullptr);
    return Status::IOError("forced error");
  });

  Status s = db.TEST_CompactMemTable();

  EXPECT_TRUE(s.IsIOError());
  EXPECT_EQ(db.write_call_count(), 1);
  EXPECT_EQ(db.last_updates_arg(), nullptr);
}

// Verifies: When Write returns OK and no immutable memtable exists (constructor default),
// TEST_CompactMemTable returns OK without blocking or altering the status.
TEST(DBImpl_CompactMemTableTest_303, ReturnsOkWhenWriteOkAndNoImm_303) {
  Options opt = MakeDefaultOptions();
  TestableDBImpl db(opt, "testdb_ok_path");

  db.SetWriteStub([](const WriteOptions&, WriteBatch* updates) {
    EXPECT_EQ(updates, nullptr);
    return Status::OK();
  });

  Status s = db.TEST_CompactMemTable();

  EXPECT_TRUE(s.ok());
  EXPECT_EQ(db.write_call_count(), 1);
  EXPECT_EQ(db.last_updates_arg(), nullptr);
}
