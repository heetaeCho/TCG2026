#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "db/version_set.h"
#include "db/version_edit.h"
#include "db/dbformat.h"

using ::testing::ElementsAre;
using ::testing::UnorderedElementsAre;

namespace leveldb {

// A minimal user comparator: bytewise (typical for LevelDB tests).
// We rely only on its observable Compare behavior through interfaces.
class BytewiseComparator : public Comparator {
 public:
  const char* Name() const override { return "test.BytewiseComparator"; }
  int Compare(const Slice& a, const Slice& b) const override {
    const int r = a.compare(b);
    return (r < 0) ? -1 : (r > 0 ? +1 : 0);
  }
  void FindShortestSeparator(std::string*, const Slice&) const override {}
  void FindShortSuccessor(std::string*) const override {}
};

// Small helper to build InternalKeys via the public constructor.
static InternalKey MakeInternalKey(const std::string& user_key,
                                   SequenceNumber seq = 1,
                                   ValueType t = kTypeValue) {
  return InternalKey(Slice(user_key), seq, t);
}

// Test fixture sets up an InternalKeyComparator we can hand into BySmallestKey.
class BuilderComparatorTest_160 : public ::testing::Test {
 protected:
  BytewiseComparator user_;
  InternalKeyComparator icmp_{&user_};

  // Convenience alias to the comparator-under-test.
  using BySmallestKey = VersionSet::Builder::BySmallestKey;

  // Wrap a pair of freshly allocated FileMetaData* with chosen smallest/largest.
  static FileMetaData* NewFile(uint64_t number,
                               const InternalKey& smallest,
                               const InternalKey& largest) {
    auto* f = new FileMetaData();
    f->number = number;
    f->smallest = smallest;
    f->largest = largest;
    return f;
  }

  // Clean up heap-allocated FileMetaData in a container of raw pointers.
  template <typename Container>
  static void FreeAll(const Container& c) {
    for (auto* p : c) delete p;
  }
};

// Orders by smallest internal key ascending.
TEST_F(BuilderComparatorTest_160, BySmallestKey_OrdersAscending_160) {
  BuilderComparatorTest_160::BySmallestKey cmp;
  cmp.internal_comparator = &icmp_;

  // f1: [a..b], f2: [c..d]
  auto* f1 = NewFile(/*number=*/1, MakeInternalKey("a"), MakeInternalKey("b"));
  auto* f2 = NewFile(/*number=*/2, MakeInternalKey("c"), MakeInternalKey("d"));

  // Direct comparator behavior
  EXPECT_TRUE(cmp(f1, f2));
  EXPECT_FALSE(cmp(f2, f1));

  // And inside a FileSet (std::set with our comparator instance)
  std::set<FileMetaData*, BuilderComparatorTest_160::BySmallestKey> files(cmp);
  files.insert(f2);
  files.insert(f1);

  // Iterate to confirm order: f1 first, then f2.
  std::vector<uint64_t> order;
  for (auto* f : files) order.push_back(f->number);
  EXPECT_THAT(order, ElementsAre(1, 2));

  FreeAll(files);
}

// Equal smallest keys should still form a strict-weak-order (both can exist).
// We don't assume a specific tiebreak; we only require the set can hold both.
TEST_F(BuilderComparatorTest_160, BySmallestKey_AllowsDistinctFilesWithEqualSmallest_160) {
  BuilderComparatorTest_160::BySmallestKey cmp;
  cmp.internal_comparator = &icmp_;

  // Two files with identical smallest user keys but different file numbers/ranges.
  auto* f1 = NewFile(/*number=*/11, MakeInternalKey("m"), MakeInternalKey("p"));
  auto* f2 = NewFile(/*number=*/22, MakeInternalKey("m"), MakeInternalKey("z"));

  std::set<FileMetaData*, BuilderComparatorTest_160::BySmallestKey> files(cmp);
  files.insert(f1);
  files.insert(f2);

  // Both should be present; order is unspecified for equal smallest.
  std::vector<uint64_t> ids;
  for (auto* f : files) ids.push_back(f->number);

  EXPECT_EQ(files.size(), 2u);
  EXPECT_THAT(ids, UnorderedElementsAre(11, 22));

  FreeAll(files);
}

// Verifies the set respects transitive ordering across multiple files.
// This mirrors the precondition SaveTo relies on for merging with upper_bound.
TEST_F(BuilderComparatorTest_160, BySmallestKey_TransitiveOrdering_160) {
  BuilderComparatorTest_160::BySmallestKey cmp;
  cmp.internal_comparator = &icmp_;

  auto* f1 = NewFile(1, MakeInternalKey("a"), MakeInternalKey("b"));
  auto* f2 = NewFile(2, MakeInternalKey("m"), MakeInternalKey("n"));
  auto* f3 = NewFile(3, MakeInternalKey("x"), MakeInternalKey("y"));

  std::set<FileMetaData*, BuilderComparatorTest_160::BySmallestKey> files(cmp);
  files.insert(f2);
  files.insert(f3);
  files.insert(f1);

  std::vector<uint64_t> order;
  for (auto* f : files) order.push_back(f->number);

  EXPECT_THAT(order, ElementsAre(1, 2, 3));

  FreeAll(files);
}

}  // namespace leveldb
