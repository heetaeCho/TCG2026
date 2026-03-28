// File: version_set_find_largest_key_test_174.cc

#include "db/dbformat.h"          // InternalKey, InternalKeyComparator, ValueType, SequenceNumber
#include "db/version_edit.h"      // FileMetaData
#include "gtest/gtest.h"

#include "leveldb/comparator.h"   // leveldb::Comparator, leveldb::BytewiseComparator
#include <memory>
#include <vector>

namespace {

// Simple helper to construct an InternalKey from a user key string.
inline leveldb::InternalKey MakeIKey(const std::string& user_key,
                                     leveldb::SequenceNumber seq = 1,
                                     leveldb::ValueType vt = leveldb::kTypeValue) {
  return leveldb::InternalKey(leveldb::Slice(user_key), seq, vt);
}

// Allocate a FileMetaData with its largest key set.
// NOTE: We only set the fields that are observable through the interface under test.
inline leveldb::FileMetaData* MakeFileWithLargest(const std::string& user_key) {
  auto* f = new leveldb::FileMetaData();
  f->largest = MakeIKey(user_key);
  return f;
}

// A user comparator that orders user keys in REVERSE bytewise order.
// This is an external collaborator for InternalKeyComparator and is allowed to be customized in tests.
class ReverseBytewiseComparator : public leveldb::Comparator {
 public:
  const char* Name() const override { return "test.ReverseBytewiseComparator"; }
  int Compare(const leveldb::Slice& a, const leveldb::Slice& b) const override {
    // Reverse of lexicographic: return positive when a < b lexicographically.
    if (a.compare(b) < 0) return 1;
    if (a.compare(b) > 0) return -1;
    return 0;
  }
  void FindShortestSeparator(std::string*, const leveldb::Slice&) const override {}
  void FindShortSuccessor(std::string*) const override {}
};

}  // namespace

// ---------- Tests ----------

TEST(FindLargestKeyTest_174, EmptyInputReturnsFalseAndLeavesOutputUnchanged_174) {
  // Setup
  leveldb::InternalKeyComparator icmp(leveldb::BytewiseComparator());
  std::vector<leveldb::FileMetaData*> files;

  // Prepare a sentinel value and keep a copy to check that it stays unchanged.
  leveldb::InternalKey original = MakeIKey("sentinel");
  leveldb::InternalKey largest_key = original;

  // Exercise
  bool ok = leveldb::FindLargestKey(icmp, files, &largest_key);

  // Verify
  EXPECT_FALSE(ok);
  // Since InternalKey doesn't have operator==, compare via DebugString (public, observable).
  EXPECT_EQ(largest_key.DebugString(), original.DebugString());

  // Teardown: none (no allocations)
}

TEST(FindLargestKeyTest_174, SingleElementReturnsTrueAndSetsLargest_174) {
  leveldb::InternalKeyComparator icmp(leveldb::BytewiseComparator());
  std::vector<leveldb::FileMetaData*> files;

  // Create one file with largest key "k1".
  std::unique_ptr<leveldb::FileMetaData> f1(MakeFileWithLargest("k1"));
  files.push_back(f1.get());

  leveldb::InternalKey out;

  bool ok = leveldb::FindLargestKey(icmp, files, &out);

  EXPECT_TRUE(ok);
  EXPECT_EQ(out.DebugString(), f1->largest.DebugString());
}

TEST(FindLargestKeyTest_174, PicksMaximumAmongMultipleUnsorted_174) {
  leveldb::InternalKeyComparator icmp(leveldb::BytewiseComparator());
  std::vector<leveldb::FileMetaData*> files;

  // Intentionally unsorted by user key.
  std::unique_ptr<leveldb::FileMetaData> fA(MakeFileWithLargest("a"));
  std::unique_ptr<leveldb::FileMetaData> fC(MakeFileWithLargest("c"));
  std::unique_ptr<leveldb::FileMetaData> fB(MakeFileWithLargest("b"));
  files.push_back(fB.get());  // "b"
  files.push_back(fA.get());  // "a"
  files.push_back(fC.get());  // "c" -> expected largest under bytewise comparator

  leveldb::InternalKey out;
  bool ok = leveldb::FindLargestKey(icmp, files, &out);

  EXPECT_TRUE(ok);
  EXPECT_EQ(out.DebugString(), fC->largest.DebugString());  // should pick "c"
}

TEST(FindLargestKeyTest_174, HandlesEqualLargestKeys_174) {
  leveldb::InternalKeyComparator icmp(leveldb::BytewiseComparator());
  std::vector<leveldb::FileMetaData*> files;

  // Two files whose 'largest' share the same user key. Either way, result's user key should be "x".
  std::unique_ptr<leveldb::FileMetaData> f1(MakeFileWithLargest("x"));
  std::unique_ptr<leveldb::FileMetaData> f2(MakeFileWithLargest("x"));
  files.push_back(f1.get());
  files.push_back(f2.get());

  leveldb::InternalKey out;
  bool ok = leveldb::FindLargestKey(icmp, files, &out);

  EXPECT_TRUE(ok);
  // Validate by observable user key equality via DebugString.
  EXPECT_EQ(out.user_key().ToString(), "x");
}

TEST(FindLargestKeyTest_174, MaxAtFirstPositionStillSelected_174) {
  leveldb::InternalKeyComparator icmp(leveldb::BytewiseComparator());
  std::vector<leveldb::FileMetaData*> files;

  // First element has the largest key to ensure implementation isn't biased to later elements.
  std::unique_ptr<leveldb::FileMetaData> fZ(MakeFileWithLargest("z")); // largest
  std::unique_ptr<leveldb::FileMetaData> fM(MakeFileWithLargest("m"));
  std::unique_ptr<leveldb::FileMetaData> fA(MakeFileWithLargest("a"));
  files.push_back(fZ.get());
  files.push_back(fM.get());
  files.push_back(fA.get());

  leveldb::InternalKey out;
  bool ok = leveldb::FindLargestKey(icmp, files, &out);

  EXPECT_TRUE(ok);
  EXPECT_EQ(out.DebugString(), fZ->largest.DebugString());
}

TEST(FindLargestKeyTest_174, RespectsUserComparatorOrdering_174) {
  // Use a reverse user comparator so that "a" is considered LARGER than "b" and "c".
  ReverseBytewiseComparator reverse_user_cmp;
  leveldb::InternalKeyComparator icmp(&reverse_user_cmp);

  std::vector<leveldb::FileMetaData*> files;
  std::unique_ptr<leveldb::FileMetaData> fA(MakeFileWithLargest("a")); // reverse-largest
  std::unique_ptr<leveldb::FileMetaData> fB(MakeFileWithLargest("b"));
  std::unique_ptr<leveldb::FileMetaData> fC(MakeFileWithLargest("c"));
  files.push_back(fB.get());
  files.push_back(fC.get());
  files.push_back(fA.get());

  leveldb::InternalKey out;
  bool ok = leveldb::FindLargestKey(icmp, files, &out);

  EXPECT_TRUE(ok);
  // Under reverse comparator, "a" should be the largest user key.
  EXPECT_EQ(out.user_key().ToString(), "a");
}
