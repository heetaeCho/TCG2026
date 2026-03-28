// File: db/c_readoptions_set_snapshot_test.cc

#include <gtest/gtest.h>

// --- Minimal interface shims to compile tests if real headers aren't included.
// In your repo, prefer including the actual headers instead of these shims.
namespace leveldb {
  class Snapshot;  // opaque, we never instantiate/dereference
  struct ReadOptions {
    bool verify_checksums = false;
    bool fill_cache = true;
    const Snapshot* snapshot = nullptr;
  };
}

struct leveldb_snapshot_t { const leveldb::Snapshot* rep; };
struct leveldb_readoptions_t { leveldb::ReadOptions rep; };

// Function under test (provided by production code; not implemented here).
extern "C" {
void leveldb_readoptions_set_snapshot(leveldb_readoptions_t* opt,
                                      const leveldb_snapshot_t* snap);
}

// --- Test fixture
class ReadOptionsSetSnapshotTest_276 : public ::testing::Test {
protected:
  leveldb_readoptions_t opt{};
};

// Normal operation: sets to a non-null snapshot pointer
TEST_F(ReadOptionsSetSnapshotTest_276, SetsNonNullSnapshotPointer_276) {
  // Arrange: distinct, non-null opaque addresses; never dereferenced.
  const auto* snap_addr = reinterpret_cast<const leveldb::Snapshot*>(0x1A2B3C);
  leveldb_snapshot_t snap{snap_addr};

  // Precondition: different initial pointer
  opt.rep.snapshot = reinterpret_cast<const leveldb::Snapshot*>(0xDEADBEEF);

  // Act
  leveldb_readoptions_set_snapshot(&opt, &snap);

  // Assert
  EXPECT_EQ(opt.rep.snapshot, snap_addr);
}

// Boundary: passing nullptr clears snapshot to nullptr
TEST_F(ReadOptionsSetSnapshotTest_276, PassingNullClearsSnapshot_276) {
  // Arrange: start with a non-null pointer
  opt.rep.snapshot = reinterpret_cast<const leveldb::Snapshot*>(0xABCD);

  // Act
  leveldb_readoptions_set_snapshot(&opt, /*snap=*/nullptr);

  // Assert
  EXPECT_EQ(opt.rep.snapshot, nullptr);
}

// Idempotence/overwrite: subsequent call replaces previous snapshot
TEST_F(ReadOptionsSetSnapshotTest_276, OverwritesExistingSnapshot_276) {
  const auto* first_addr  = reinterpret_cast<const leveldb::Snapshot*>(0x1111);
  const auto* second_addr = reinterpret_cast<const leveldb::Snapshot*>(0x2222);
  leveldb_snapshot_t first{first_addr};
  leveldb_snapshot_t second{second_addr};

  // Act 1: set first
  leveldb_readoptions_set_snapshot(&opt, &first);
  // Act 2: set second (overwrite)
  leveldb_readoptions_set_snapshot(&opt, &second);

  // Assert: latest pointer is in effect
  EXPECT_EQ(opt.rep.snapshot, second_addr);
}

// Non-interference: other ReadOptions fields remain unchanged
TEST_F(ReadOptionsSetSnapshotTest_276, DoesNotModifyOtherReadOptionsFields_276) {
  // Arrange: set non-default values to make accidental changes visible
  opt.rep.verify_checksums = true;
  opt.rep.fill_cache = false;

  const auto* snap_addr = reinterpret_cast<const leveldb::Snapshot*>(0x7777);
  leveldb_snapshot_t snap{snap_addr};

  // Act
  leveldb_readoptions_set_snapshot(&opt, &snap);

  // Assert: only 'snapshot' may change; other fields must remain intact
  EXPECT_TRUE(opt.rep.verify_checksums);
  EXPECT_FALSE(opt.rep.fill_cache);
  EXPECT_EQ(opt.rep.snapshot, snap_addr);
}
