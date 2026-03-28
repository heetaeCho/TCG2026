// memtable_get_test_368.cc
#include <gtest/gtest.h>
#include <string>

#include "db/memtable.h"
#include "db/dbformat.h"
#include "leveldb/comparator.h"
#include "leveldb/slice.h"
#include "leveldb/status.h"

namespace {

// A minimal user Comparator used only as an external collaborator.
// It compares user keys lexicographically using Slice::compare.
// (We are NOT re-implementing any MemTable logic.)
class LexicographicUserComparator : public leveldb::Comparator {
public:
  // Name is required by the interface; exact value doesn't matter for these tests.
  const char* Name() const override { return "test.lexicographic"; }

  int Compare(const leveldb::Slice& a, const leveldb::Slice& b) const override {
    return a.compare(b);
  }

  void FindShortestSeparator(std::string*, const leveldb::Slice&) const override {}
  void FindShortSuccessor(std::string*) const override {}

  ~LexicographicUserComparator() override = default;
};

class MemTableGetTest_368 : public ::testing::Test {
protected:
  LexicographicUserComparator user_cmp_;
  leveldb::InternalKeyComparator ikey_cmp_{&user_cmp_};
  leveldb::MemTable* mem_ = nullptr;

  void SetUp() override {
    mem_ = new leveldb::MemTable(ikey_cmp_);
    // Follow LevelDB pattern: MemTable is ref-counted.
    mem_->Ref();
  }

  void TearDown() override {
    mem_->Unref(); // Deletes when ref-count hits zero.
    mem_ = nullptr;
  }

  // Helper to add one entry.
  void Put(leveldb::SequenceNumber seq,
           const leveldb::Slice& user_key,
           const leveldb::Slice& value) {
    mem_->Add(seq, leveldb::kTypeValue, user_key, value);
  }

  // Helper to add a deletion marker.
  void Del(leveldb::SequenceNumber seq, const leveldb::Slice& user_key) {
    mem_->Add(seq, leveldb::kTypeDeletion, user_key, /*value*/ leveldb::Slice());
  }

  // Helper to perform a Get with a LookupKey built from the user key and sequence.
  bool Get(leveldb::SequenceNumber seq,
           const leveldb::Slice& user_key,
           std::string* out,
           leveldb::Status* s) {
    leveldb::LookupKey lk(user_key, seq);
    return mem_->Get(lk, out, s);
  }
};

} // namespace

// Normal case: present key with value -> returns true and writes the value.
TEST_F(MemTableGetTest_368, ReturnsTrueAndSetsValueWhenPresent_368) {
  const leveldb::SequenceNumber seq = 100;
  Put(seq, "alpha", "v1");

  std::string result;
  leveldb::Status s; // Initial state is unspecified by Get; we only check observable outcomes.
  bool found = Get(seq, "alpha", &result, &s);

  EXPECT_TRUE(found);
  EXPECT_EQ(result, "v1");
  // No guarantee about status on value case by the interface; we don't assert it.
}

// Deletion case: present key with kTypeDeletion -> returns true and sets Status::NotFound.
TEST_F(MemTableGetTest_368, ReturnsTrueAndSetsStatusNotFoundOnDeletion_368) {
  const leveldb::SequenceNumber seq = 200;
  Del(seq, "gone");

  std::string result = "should_not_matter";
  leveldb::Status s;
  bool found = Get(seq, "gone", &result, &s);

  EXPECT_TRUE(found);
  EXPECT_TRUE(s.IsNotFound());
  // Value content is unspecified on deletion-path; do not assert on 'result'.
}

// Absent key: returns false and does not produce a value.
TEST_F(MemTableGetTest_368, ReturnsFalseWhenKeyAbsent_368) {
  const leveldb::SequenceNumber seq = 300;
  // No insertion for "missing"

  std::string result;
  leveldb::Status s;
  bool found = Get(seq, "missing", &result, &s);

  EXPECT_FALSE(found);
  // Interface does not specify status mutation on "not found in memtable" path; avoid asserting it.
}

// Boundary: empty value should be retrievable and preserved exactly.
TEST_F(MemTableGetTest_368, RetrievesEmptyValueExactly_368) {
  const leveldb::SequenceNumber seq = 400;
  Put(seq, "empty-val", leveldb::Slice("")); // zero-length value

  std::string result = "will_be_cleared";
  leveldb::Status s;
  bool found = Get(seq, "empty-val", &result, &s);

  EXPECT_TRUE(found);
  EXPECT_EQ(result, ""); // exact empty
}

// Boundary: empty user key should work (as long as the interface accepts it).
TEST_F(MemTableGetTest_368, WorksWithEmptyUserKey_368) {
  const leveldb::SequenceNumber seq = 500;
  const leveldb::Slice empty_key("");

  Put(seq, empty_key, "val");
  std::string result;
  leveldb::Status s;
  bool found = Get(seq, empty_key, &result, &s);

  EXPECT_TRUE(found);
  EXPECT_EQ(result, "val");
}

// Multiple entries note:
// We intentionally avoid asserting sequence-precedence or internal ordering,
// since that would infer internal logic beyond the exposed interface.

