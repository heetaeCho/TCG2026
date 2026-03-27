// File: db/db_iter_test.cc

#include "gtest/gtest.h"
#include "gmock/gmock.h"

// Forward declarations to avoid depending on internal headers.
// We only use the public interfaces/types.
#include <cstdint>

namespace leveldb {
  class Slice;
  class Status;
  class Comparator;
  class Iterator;
  class DBImpl;
  using SequenceNumber = uint64_t;

  // Factory under test (defined in db/db_iter.cc)
  Iterator* NewDBIterator(DBImpl* db,
                          const Comparator* user_key_comparator,
                          Iterator* internal_iter,
                          SequenceNumber sequence,
                          uint32_t seed);
}

// Provide lightweight mocks for collaborators (allowed by constraints).
// We do NOT simulate or assert on internal behavior of DBIter; these
// are only to satisfy the constructor’s dependencies.
namespace leveldb {

class MockComparator : public Comparator {
 public:
  MOCK_METHOD(int, Compare, (const Slice& a, const Slice& b), (const, override));
  MOCK_METHOD(const char*, Name, (), (const, override));
  MOCK_METHOD(void, FindShortestSeparator, (std::string* start, const Slice& limit), (const, override));
  MOCK_METHOD(void, FindShortSuccessor, (std::string* key), (const, override));
  // Ensure a virtual destructor is available from the base.
  ~MockComparator() override = default;
};

class MockIterator : public Iterator {
 public:
  // Iterator virtual API
  MOCK_METHOD(bool, Valid, (), (const, override));
  MOCK_METHOD(void, SeekToFirst, (), (override));
  MOCK_METHOD(void, SeekToLast, (), (override));
  MOCK_METHOD(void, Seek, (const Slice& target), (override));
  MOCK_METHOD(void, Next, (), (override));
  MOCK_METHOD(void, Prev, (), (override));
  MOCK_METHOD(Slice, key, (), (const, override));
  MOCK_METHOD(Slice, value, (), (const, override));
  MOCK_METHOD(Status, status, (), (const, override));
  ~MockIterator() override = default;
};

}  // namespace leveldb

using ::testing::NiceMock;

namespace {

class NewDBIteratorTest_369 : public ::testing::Test {
 protected:
  // NiceMock allows unexpected calls (if DBIter calls any collaborator
  // methods during construction) without failing tests.
  NiceMock<leveldb::MockComparator> cmp_;
  NiceMock<leveldb::MockIterator>   internal_iter_;
};

// --- Tests ---

// 1) Basic: Creating with reasonable parameters yields a non-null Iterator*
TEST_F(NewDBIteratorTest_369, ReturnsNonNullWithValidInputs_369) {
  // Do not assume DBImpl allocation/ownership; pass nullptr to respect black-box constraints.
  leveldb::Iterator* it = leveldb::NewDBIterator(
      /*db=*/nullptr, &cmp_, &internal_iter_, /*sequence=*/0, /*seed=*/123u);

  ASSERT_NE(it, nullptr) << "NewDBIterator should return a valid Iterator*";

  // The factory returns a NEW iterator; ensure pointer differs from the provided internal_iter.
  EXPECT_NE(it, &internal_iter_);

  // Safe destruction via base pointer (polymorphic delete).
  delete it;
}

// 2) Boundary: Extreme sequence/seed values should not crash during construction/destruction
TEST_F(NewDBIteratorTest_369, HandlesExtremeSequenceAndSeed_369) {
  const leveldb::SequenceNumber max_seq = std::numeric_limits<leveldb::SequenceNumber>::max();
  const uint32_t max_seed = std::numeric_limits<uint32_t>::max();

  leveldb::Iterator* it = nullptr;
  EXPECT_NO_THROW({
    it = leveldb::NewDBIterator(/*db=*/nullptr, &cmp_, &internal_iter_, max_seq, max_seed);
  });

  ASSERT_NE(it, nullptr);
  EXPECT_NE(it, &internal_iter_);
  EXPECT_NO_THROW({ delete it; });
}

// 3) Stability: Multiple creations yield distinct, independently deletable instances
TEST_F(NewDBIteratorTest_369, MultipleCreationsYieldDistinctInstances_369) {
  leveldb::Iterator* it1 = leveldb::NewDBIterator(nullptr, &cmp_, &internal_iter_, 42, 1u);
  leveldb::Iterator* it2 = leveldb::NewDBIterator(nullptr, &cmp_, &internal_iter_, 42, 2u);

  ASSERT_NE(it1, nullptr);
  ASSERT_NE(it2, nullptr);
  EXPECT_NE(it1, it2);           // Distinct allocations expected
  EXPECT_NE(it1, &internal_iter_);
  EXPECT_NE(it2, &internal_iter_);

  delete it1;
  delete it2;
}

}  // namespace
