// File: c_api_release_snapshot_test.cc

#include <gtest/gtest.h>
#include <gmock/gmock.h>

// Minimal includes / forward declarations to treat the implementation as a black box.
namespace leveldb {
class Snapshot;  // opaque to us
class DB {
 public:
  virtual ~DB() = default;
  virtual void ReleaseSnapshot(const Snapshot* snapshot) { (void)snapshot; }
};
}  // namespace leveldb

// C API wrapper structs (mirroring the partial code)
struct leveldb_t { leveldb::DB* rep; };
struct leveldb_snapshot_t { const leveldb::Snapshot* rep; };

// Target under test (implemented in db/c.cc in the real codebase)
extern "C" void leveldb_release_snapshot(leveldb_t* db, const leveldb_snapshot_t* snapshot);

// ---- Mock ----
namespace {
using ::testing::_;
using ::testing::Exactly;

class MockDB : public leveldb::DB {
 public:
  ~MockDB() override = default;
  MOCK_METHOD(void, ReleaseSnapshot, (const leveldb::Snapshot* snapshot), (override));
};

// A small helper type whose address we’ll use as an opaque Snapshot identity.
// We never dereference it; we only pass the pointer through to DB::ReleaseSnapshot.
struct DummySnapshotTag { int unused = 0; };

}  // namespace

// ---- Tests ----

TEST(LeveldbReleaseSnapshotTest_228, ForwardsSnapshotAndDeletesWrapper_228) {
  // Arrange
  MockDB mock_db;
  leveldb_t db{&mock_db};

  DummySnapshotTag dummy;
  const leveldb::Snapshot* snap_rep = reinterpret_cast<const leveldb::Snapshot*>(&dummy);

  auto* snap_wrapper = new leveldb_snapshot_t{snap_rep};

  // Expect: DB::ReleaseSnapshot is called exactly once with the same pointer.
  EXPECT_CALL(mock_db, ReleaseSnapshot(snap_rep)).Times(Exactly(1));

  // Act
  leveldb_release_snapshot(&db, snap_wrapper);

  // Assert
  // No further assertions: the function is expected to delete snap_wrapper.
  // We intentionally do not touch snap_wrapper after the call to respect the black-box constraint.
}

TEST(LeveldbReleaseSnapshotTest_228, ForwardsNullSnapshotPointerToDB_228) {
  // Arrange
  MockDB mock_db;
  leveldb_t db{&mock_db};

  auto* snap_wrapper = new leveldb_snapshot_t{nullptr};

  // Expect: ReleaseSnapshot receives nullptr and is still called once.
  EXPECT_CALL(mock_db, ReleaseSnapshot(nullptr)).Times(Exactly(1));

  // Act
  leveldb_release_snapshot(&db, snap_wrapper);

  // Assert: as above, deletion of the wrapper is internal; we don't access it again.
}

#if GTEST_HAS_DEATH_TEST
TEST(LeveldbReleaseSnapshotTest_228, NullDbPointerCausesDeath_228) {
  // Arrange
  DummySnapshotTag dummy;
  const leveldb::Snapshot* snap_rep = reinterpret_cast<const leveldb::Snapshot*>(&dummy);
  auto* snap_wrapper = new leveldb_snapshot_t{snap_rep};

  // Act + Assert: dereferencing db->rep is UB; we verify it crashes in a death test.
  // The exact failure text is platform-dependent, so we use ".*" as a generic matcher.
  EXPECT_DEATH(
      {
        // NOLINTNEXTLINE(bugprone-use-after-move)
        leveldb_release_snapshot(nullptr, snap_wrapper);
      },
      ".*");

  // Cleanup only if the call didn't run (in death tests, the child process exits).
  // In the parent process, snap_wrapper still exists; delete it to avoid a leak here.
  delete snap_wrapper;
}

TEST(LeveldbReleaseSnapshotTest_228, NullSnapshotWrapperCausesDeath_228) {
  // Arrange
  MockDB mock_db;
  leveldb_t db{&mock_db};

  // Act + Assert: dereferencing snapshot->rep is UB; verify crash.
  EXPECT_DEATH(
      {
        leveldb_release_snapshot(&db, nullptr);
      },
      ".*");
}

TEST(LeveldbReleaseSnapshotTest_228, NullDbRepCausesDeath_228) {
  // Arrange
  leveldb_t db{nullptr};

  DummySnapshotTag dummy;
  const leveldb::Snapshot* snap_rep = reinterpret_cast<const leveldb::Snapshot*>(&dummy);
  auto* snap_wrapper = new leveldb_snapshot_t{snap_rep};

  // Act + Assert
  EXPECT_DEATH(
      {
        leveldb_release_snapshot(&db, snap_wrapper);
      },
      ".*");

  delete snap_wrapper;  // see note in previous death test about parent process cleanup
}
#endif  // GTEST_HAS_DEATH_TEST
