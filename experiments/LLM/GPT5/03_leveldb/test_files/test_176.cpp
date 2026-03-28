// AddBoundaryInputs_test.cc
#include <gtest/gtest.h>
#include <vector>
#include <deque>

#include "db/version_edit.h"   // leveldb::FileMetaData
#include "db/dbformat.h"       // leveldb::InternalKeyComparator, leveldb::InternalKey

namespace leveldb {

// ---- Forward declarations from the production unit ----
// (We provide test doubles for these free functions below.)
bool FindLargestKey(const InternalKeyComparator& icmp,
                    const std::vector<FileMetaData*>& compaction_files,
                    InternalKey* largest_key);

FileMetaData* FindSmallestBoundaryFile(const InternalKeyComparator& icmp,
                                       const std::vector<FileMetaData*>& level_files,
                                       const InternalKey& largest_key);

// ---- Function under test ----
void AddBoundaryInputs(const InternalKeyComparator& icmp,
                       const std::vector<FileMetaData*>& level_files,
                       std::vector<FileMetaData*>* compaction_files);

}  // namespace leveldb

using namespace leveldb;

// ====================== Test doubles / global controls ======================
// These are intentionally very small and only control/observe *external*
// interactions. They DO NOT simulate internal logic of AddBoundaryInputs.

namespace {

struct StubControls {
  // Controls for FindLargestKey
  bool find_largest_return = false;
  InternalKey find_largest_out_key;  // value copied to *largest_key when returning true

  // Controls/observations for FindSmallestBoundaryFile
  std::deque<FileMetaData*> boundary_return_queue;  // sequence of returns; then nullptr
  int boundary_call_count = 0;                       // how many times it was called
} g_stub;

// Minimal helper to get a non-null comparator reference without relying on any
// concrete comparator behavior (we never dereference it in our stubs).
// NOTE: We are not asserting anything about comparison behavior in these tests.
const InternalKeyComparator& DummyICmp() {
  // Reuse a static object with a dummy pointer; it will never be used by our stubs.
  static InternalKeyComparator* kDummy = reinterpret_cast<InternalKeyComparator*>(0x1);
  return *kDummy;
}

}  // namespace

// ---------------------------- Stub Implementations --------------------------
namespace leveldb {

bool FindLargestKey(const InternalKeyComparator& /*icmp*/,
                    const std::vector<FileMetaData*>& /*compaction_files*/,
                    InternalKey* largest_key) {
  if (g_stub.find_largest_return) {
    // Provide the caller with the starting largest key value (opaque to tests).
    *largest_key = g_stub.find_largest_out_key;
    return true;
  }
  return false;
}

FileMetaData* FindSmallestBoundaryFile(const InternalKeyComparator& /*icmp*/,
                                       const std::vector<FileMetaData*>& /*level_files*/,
                                       const InternalKey& /*largest_key*/) {
  g_stub.boundary_call_count++;
  if (g_stub.boundary_return_queue.empty()) return nullptr;
  FileMetaData* next = g_stub.boundary_return_queue.front();
  g_stub.boundary_return_queue.pop_front();
  return next;
}

}  // namespace leveldb

// ================================= Fixture ==================================
class AddBoundaryInputsTest_176 : public ::testing::Test {
 protected:
  void SetUp() override {
    g_stub.find_largest_return = false;
    g_stub.find_largest_out_key = InternalKey();  // default; content irrelevant to black-box tests
    g_stub.boundary_return_queue.clear();
    g_stub.boundary_call_count = 0;
    level_files_.clear();
    compaction_files_.clear();
  }

  // Utility to allocate a FileMetaData* with default keys; we only care about identity.
  FileMetaData* NewFile(uint64_t number = 0) {
    auto* f = new FileMetaData();
    f->number = number;
    return f;
  }

  void TearDown() override {
    for (auto* f : owned_) delete f;
    owned_.clear();
  }

  FileMetaData* Own(FileMetaData* f) { owned_.push_back(f); return f; }

  std::vector<FileMetaData*> level_files_;
  std::vector<FileMetaData*> compaction_files_;

 private:
  std::vector<FileMetaData*> owned_;
};

// ================================ Test Cases ================================

// 1) If FindLargestKey returns false, function should return immediately and
//    not call FindSmallestBoundaryFile or modify compaction_files.
TEST_F(AddBoundaryInputsTest_176, ReturnsImmediatelyWhenNoLargestKey_176) {
  // Arrange
  g_stub.find_largest_return = false;  // immediate return
  compaction_files_.push_back(Own(NewFile(1)));  // pre-existing content to prove unchanged

  // Act
  AddBoundaryInputs(DummyICmp(), level_files_, &compaction_files_);

  // Assert
  EXPECT_EQ(1u, compaction_files_.size());      // unchanged
  EXPECT_EQ(0, g_stub.boundary_call_count);     // no boundary search calls
}

// 2) When a largest key exists but no boundary file is found at the first check,
//    nothing should be added, and the boundary function is called exactly once.
TEST_F(AddBoundaryInputsTest_176, NoBoundaryFileFound_AddsNothing_176) {
  // Arrange
  g_stub.find_largest_return = true;            // we will proceed past the early-return
  g_stub.find_largest_out_key = InternalKey();  // opaque; not asserted
  compaction_files_.push_back(Own(NewFile(10)));

  // boundary queue is empty -> FindSmallestBoundaryFile returns nullptr on first call
  // Act
  AddBoundaryInputs(DummyICmp(), level_files_, &compaction_files_);

  // Assert
  EXPECT_EQ(1u, compaction_files_.size());      // unchanged
  EXPECT_EQ(1, g_stub.boundary_call_count);     // loop checked once and stopped
}

// 3) When boundary search yields a single file, it should be appended exactly once.
//    Boundary function should be called twice: one hit, then a nullptr to stop.
TEST_F(AddBoundaryInputsTest_176, SingleBoundaryFileIsAppended_176) {
  // Arrange
  g_stub.find_largest_return = true;
  g_stub.find_largest_out_key = InternalKey();

  auto* start = Own(NewFile(100));
  auto* boundary1 = Own(NewFile(200));

  compaction_files_.push_back(start);
  g_stub.boundary_return_queue.push_back(boundary1);  // then implicit nullptr

  // Act
  AddBoundaryInputs(DummyICmp(), level_files_, &compaction_files_);

  // Assert
  ASSERT_EQ(2u, compaction_files_.size());
  EXPECT_EQ(start,     compaction_files_[0]);
  EXPECT_EQ(boundary1, compaction_files_[1]);

  // Called once to get boundary1, once more to get nullptr and stop
  EXPECT_EQ(2, g_stub.boundary_call_count);
}

// 4) When boundary search yields multiple files (chained), they should all be appended
//    in order, and the boundary function is called (files+1) times to terminate.
TEST_F(AddBoundaryInputsTest_176, MultipleBoundaryFilesAreChainedAndAppended_176) {
  // Arrange
  g_stub.find_largest_return = true;
  g_stub.find_largest_out_key = InternalKey();

  auto* start = Own(NewFile(100));
  auto* b1 = Own(NewFile(201));
  auto* b2 = Own(NewFile(202));
  auto* b3 = Own(NewFile(203));

  compaction_files_.push_back(start);

  g_stub.boundary_return_queue.push_back(b1);
  g_stub.boundary_return_queue.push_back(b2);
  g_stub.boundary_return_queue.push_back(b3);
  // then implicit nullptr

  // Act
  AddBoundaryInputs(DummyICmp(), level_files_, &compaction_files_);

  // Assert
  ASSERT_EQ(4u, compaction_files_.size());
  EXPECT_EQ(start, compaction_files_[0]);
  EXPECT_EQ(b1,    compaction_files_[1]);
  EXPECT_EQ(b2,    compaction_files_[2]);
  EXPECT_EQ(b3,    compaction_files_[3]);

  // 3 files returned + 1 final nullptr to stop
  EXPECT_EQ(4, g_stub.boundary_call_count);
}

// 5) Pre-populated compaction_files remain intact; only new boundary files are appended.
//    This verifies the function does not replace or reorder existing entries.
TEST_F(AddBoundaryInputsTest_176, PreservesExistingOrderAndAppendsOnly_176) {
  // Arrange
  g_stub.find_largest_return = true;
  g_stub.find_largest_out_key = InternalKey();

  auto* existing1 = Own(NewFile(1));
  auto* existing2 = Own(NewFile(2));
  auto* b1 = Own(NewFile(3));

  compaction_files_.push_back(existing1);
  compaction_files_.push_back(existing2);
  g_stub.boundary_return_queue.push_back(b1);

  // Act
  AddBoundaryInputs(DummyICmp(), level_files_, &compaction_files_);

  // Assert
  ASSERT_EQ(3u, compaction_files_.size());
  EXPECT_EQ(existing1, compaction_files_[0]);
  EXPECT_EQ(existing2, compaction_files_[1]);
  EXPECT_EQ(b1,        compaction_files_[2]);
  EXPECT_EQ(2, g_stub.boundary_call_count);  // one hit + one nullptr to stop
}
