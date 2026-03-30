// File: version_set_somefileoverlapsrange_test_134.cc

#include <vector>
#include <memory>
#include "gtest/gtest.h"

#include "leveldb/comparator.h"      // Comparator, BytewiseComparator()
#include "db/dbformat.h"             // InternalKey, InternalKeyComparator, kMaxSequenceNumber, kValueTypeForSeek
#include "db/version_set.h"          // FileMetaData (public type)

namespace leveldb {

// Forward-declare the function under test if not declared in headers available to the test.
// If your build already exposes it via a header, you can remove this forward decl.
bool SomeFileOverlapsRange(const InternalKeyComparator& icmp,
                           bool disjoint_sorted_files,
                           const std::vector<FileMetaData*>& files,
                           const Slice* smallest_user_key,
                           const Slice* largest_user_key);

class SomeFileOverlapsRangeTest_134 : public ::testing::Test {
protected:
  const Comparator* ucmp_ = BytewiseComparator();
  InternalKeyComparator icmp_{ucmp_};

  // Helper: create a file with [smallest, largest] (user keys) inclusive.
  static FileMetaData* MakeFile(uint64_t number,
                                const std::string& smallest_user_key,
                                const std::string& largest_user_key) {
    auto* f = new FileMetaData();
    f->number = number;
    f->file_size = 0;
    f->smallest = InternalKey(Slice(smallest_user_key),
                              kMaxSequenceNumber,
                              kValueTypeForSeek);
    f->largest  = InternalKey(Slice(largest_user_key),
                              kMaxSequenceNumber,
                              kValueTypeForSeek);
    return f;
  }

  // Helper: RAII container to ensure we free FileMetaData* created by MakeFile.
  struct Files {
    std::vector<FileMetaData*> v;
    ~Files() {
      for (auto* p : v) delete p;
    }
    void push(FileMetaData* f) { v.push_back(f); }
    operator const std::vector<FileMetaData*>&() const { return v; }
  };
};

// ========== Tests for disjoint_sorted_files == false (linear scan path) ==========

// Overlap exists when at least one file is neither strictly "after" nor strictly "before" the query range.
TEST_F(SomeFileOverlapsRangeTest_134, NonDisjoint_OverlapFound_134) {
  Files files;
  files.push(MakeFile(1, "a", "c"));          // file covers [a, c]
  files.push(MakeFile(2, "e", "g"));          // file covers [e, g]

  Slice smallest("b");                         // query [b, d] overlaps file1
  Slice largest("d");

  const bool res = SomeFileOverlapsRange(icmp_, /*disjoint_sorted_files=*/false,
                                         files.v, &smallest, &largest);
  EXPECT_TRUE(res);
}

// No overlap when all files are strictly before or strictly after the query range.
TEST_F(SomeFileOverlapsRangeTest_134, NonDisjoint_NoOverlap_134) {
  Files files;
  files.push(MakeFile(1, "a", "b"));          // [a, b]
  files.push(MakeFile(2, "e", "f"));          // [e, f]

  Slice smallest("c");                         // query [c, d] falls between files
  Slice largest("d");

  const bool res = SomeFileOverlapsRange(icmp_, /*disjoint_sorted_files=*/false,
                                         files.v, &smallest, &largest);
  EXPECT_FALSE(res);
}

// ========== Tests for disjoint_sorted_files == true (binary-search path) ==========

// Overlap true when the file located by smallest_user_key is not "before" largest_user_key.
TEST_F(SomeFileOverlapsRangeTest_134, Disjoint_IndexWithin_Overlap_134) {
  Files files;
  files.push(MakeFile(1, "a", "b"));          // [a, b]
  files.push(MakeFile(2, "e", "f"));          // [e, f]

  Slice smallest("b");                         // query [b, b] should overlap file1
  Slice largest("b");

  const bool res = SomeFileOverlapsRange(icmp_, /*disjoint_sorted_files=*/true,
                                         files.v, &smallest, &largest);
  EXPECT_TRUE(res);
}

// If smallest_user_key maps to an index >= files.size(), function returns false.
TEST_F(SomeFileOverlapsRangeTest_134, Disjoint_SmallestPastEnd_ReturnsFalse_134) {
  Files files;
  files.push(MakeFile(1, "a", "b"));          // [a, b]
  files.push(MakeFile(2, "e", "f"));          // [e, f]

  Slice smallest("z");                         // past any file range
  Slice largest("z");

  const bool res = SomeFileOverlapsRange(icmp_, /*disjoint_sorted_files=*/true,
                                         files.v, &smallest, &largest);
  EXPECT_FALSE(res);
}

// With smallest_user_key == nullptr, index starts at 0; if largest_user_key is strictly before files[0], result is false.
TEST_F(SomeFileOverlapsRangeTest_134, Disjoint_NoSmallest_UsesIndex0_BeforeTrue_ReturnsFalse_134) {
  Files files;
  files.push(MakeFile(1, "m", "t"));          // [m, t], index 0 used when smallest==nullptr
  files.push(MakeFile(2, "x", "z"));          // [x, z]

  Slice* smallest_null = nullptr;
  Slice largest("a");                          // entirely before [m, t]

  const bool res = SomeFileOverlapsRange(icmp_, /*disjoint_sorted_files=*/true,
                                         files.v, smallest_null, &largest);
  EXPECT_FALSE(res);
}

// With smallest_user_key == nullptr, index 0; if largest_user_key is NOT strictly before files[0], we report overlap.
TEST_F(SomeFileOverlapsRangeTest_134, Disjoint_NoSmallest_UsesIndex0_OverlapTrue_134) {
  Files files;
  files.push(MakeFile(1, "m", "t"));          // [m, t]
  files.push(MakeFile(2, "x", "z"));          // [x, z]

  Slice* smallest_null = nullptr;
  Slice largest("q");                          // not strictly before [m, t] -> overlaps

  const bool res = SomeFileOverlapsRange(icmp_, /*disjoint_sorted_files=*/true,
                                         files.v, smallest_null, &largest);
  EXPECT_TRUE(res);
}

} // namespace leveldb
