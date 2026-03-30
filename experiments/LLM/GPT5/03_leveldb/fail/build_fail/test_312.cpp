// db_impl_delete_test.cc
#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "leveldb/db.h"
#include "leveldb/options.h"
#include "leveldb/slice.h"
// If your build splits WriteBatch header out, include it as needed:
// #include "leveldb/write_batch.h"
#include "db/db_impl.h"

using ::testing::_;
using ::testing::DoAll;
using ::testing::Invoke;
using ::testing::Return;
using ::testing::SaveArgPointee;

namespace leveldb {

// A partial mock to observe the virtual Write() that DB::Delete() uses internally.
// We are NOT simulating DBImpl internals; we only verify the external interaction
// (that Delete results in a Write with a non-null batch) and the returned Status.
class DBImplWriteSpy : public DBImpl {
 public:
  // Reuse the real DBImpl constructors — if your test harness needs a helper
  // to construct Options, wire it here as appropriate for your repo.
  using DBImpl::DBImpl;

  MOCK_METHOD(Status, Write,
              (const WriteOptions& options, WriteBatch* updates),
              (override));
};

// A very small helper to produce a constructed DBImplWriteSpy.
// Adapt the Options fields as your environment requires; we avoid relying on
// any hidden behavior.
static std::unique_ptr<DBImplWriteSpy> MakeSpyDB(const std::string& name = "deletemock-db") {
  Options opts;               // default options are fine for black-box tests
  DBImplWriteSpy* raw = new DBImplWriteSpy(opts, name);
  return std::unique_ptr<DBImplWriteSpy>(raw);
}

class DBImpl_DeleteTest_312 : public ::testing::Test {
 protected:
  WriteOptions wopt_;  // default: sync=false
};

// Normal operation: Delete forwards and returns OK when Write succeeds.
TEST_F(DBImpl_DeleteTest_312, Delete_ForwardsAndReturnsOk_312) {
  auto db = MakeSpyDB();

  // Capture that a non-null batch is passed through DB::Delete -> Write.
  // We don't inspect batch contents (keeps to black-box rules).
  EXPECT_CALL(*db, Write(::testing::Ref(wopt_), _))
      .WillOnce(Invoke([](const WriteOptions& /*opt*/, WriteBatch* wb) -> Status {
        EXPECT_NE(wb, nullptr) << "Delete should construct and pass a non-null WriteBatch";
        return Status::OK();
      }));

  Slice key("k1");
  Status s = db->Delete(wopt_, key);
  EXPECT_TRUE(s.ok());
}

// Error propagation: if Write fails, Delete should return the same failure.
TEST_F(DBImpl_DeleteTest_312, Delete_PropagatesErrorStatus_312) {
  auto db = MakeSpyDB();

  const Status injected = Status::Corruption("injected write failure");

  EXPECT_CALL(*db, Write(::testing::Ref(wopt_), _))
      .WillOnce(Return(injected));

  Slice key("any");
  Status s = db->Delete(wopt_, key);
  EXPECT_EQ(s.code(), injected.code());
  EXPECT_EQ(s.ToString(), injected.ToString());
}

// Boundary: empty key is still routed to Write with a non-null batch;
// we only assert the observable call and returned Status.
TEST_F(DBImpl_DeleteTest_312, Delete_EmptyKeyStillWrites_312) {
  auto db = MakeSpyDB();

  EXPECT_CALL(*db, Write(::testing::Ref(wopt_), _))
      .WillOnce(Invoke([](const WriteOptions&, WriteBatch* wb) -> Status {
        EXPECT_NE(wb, nullptr);
        return Status::OK();
      }));

  Slice empty_key;  // default-constructed -> empty
  Status s = db->Delete(wopt_, empty_key);
  EXPECT_TRUE(s.ok());
}

// Option passthrough: when sync=true, the same options object reaches Write().
TEST_F(DBImpl_DeleteTest_312, Delete_PassesThroughOptions_312) {
  auto db = MakeSpyDB();

  WriteOptions sync_opt;
  sync_opt.sync = true;

  EXPECT_CALL(*db, Write(::testing::Ref(sync_opt), _))
      .WillOnce(Invoke([](const WriteOptions& opt, WriteBatch* wb) -> Status {
        EXPECT_TRUE(opt.sync);
        EXPECT_NE(wb, nullptr);
        return Status::OK();
      }));

  Slice key("k");
  Status s = db->Delete(sync_opt, key);
  EXPECT_TRUE(s.ok());
}

}  // namespace leveldb
