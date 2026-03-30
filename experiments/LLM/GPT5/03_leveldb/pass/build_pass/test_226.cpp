// File: db_c_create_iterator_test.cc

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <memory>

// ---- Minimal public interfaces from the provided snippets ----
namespace leveldb {
class Status;
class Slice;
class Iterator;           // forward-declared; we never call into it
struct ReadOptions {};    // treated as a simple struct for tests

class DB {
 public:
  DB() = default;
  DB(const DB&) = delete;
  virtual ~DB() = default;

  // We only need NewIterator for these tests.
  virtual Iterator* NewIterator(const ReadOptions& options) { return nullptr; }
  DB& operator=(const DB&) = delete;
};
}  // namespace leveldb

// C-API wrappers (from db/c.cc snippets)
struct leveldb_t { leveldb::DB* rep; };
struct leveldb_iterator_t { leveldb::Iterator* rep; };
struct leveldb_readoptions_t { leveldb::ReadOptions rep; };

// Function under test (from db/c.cc)
extern "C" leveldb_iterator_t* leveldb_create_iterator(leveldb_t* db,
                                                       const leveldb_readoptions_t* options);

// -------------------- Mocks & Test Fixture --------------------
using ::testing::_;
using ::testing::Ref;
using ::testing::Return;

class MockDB : public leveldb::DB {
 public:
  MOCK_METHOD(leveldb::Iterator*, NewIterator,
              (const leveldb::ReadOptions& options), (override));
};

class LeveldbCreateIteratorTest_226 : public ::testing::Test {
 protected:
  void SetUp() override {
    mock_db_ = std::make_unique<MockDB>();
    c_db_.rep = mock_db_.get();
  }

  void TearDown() override {
    // We only delete the wrapper produced by the function under test inside each test
    // when it’s safe (i.e., when the iterator pointer is nullptr or a sentinel we won’t delete).
    // The DB mock is owned here and cleaned up by unique_ptr.
  }

  std::unique_ptr<MockDB> mock_db_;
  leveldb_t c_db_{};
  leveldb_readoptions_t c_ro_{};
};

// ----------------------------- Tests -----------------------------

// Normal operation: forwards the ReadOptions by reference and returns a non-null wrapper with the same Iterator*.
TEST_F(LeveldbCreateIteratorTest_226, ReturnsWrapperAndForwardsIteratorFromDB_226) {
  // Use a distinct non-null sentinel pointer without constructing a real Iterator object.
  // We only compare pointer identity; we never dereference or delete it.
  auto* sentinel_iter = reinterpret_cast<leveldb::Iterator*>(0x1BADB002);

  EXPECT_CALL(*mock_db_, NewIterator(Ref(c_ro_.rep)))
      .Times(1)
      .WillOnce(Return(sentinel_iter));

  leveldb_iterator_t* it = leveldb_create_iterator(&c_db_, &c_ro_);
  ASSERT_NE(it, nullptr) << "Function should allocate and return a wrapper object";
  // Observable behavior: the wrapper holds whatever DB::NewIterator returned.
  EXPECT_EQ(it->rep, sentinel_iter);

  // Clean up only the wrapper struct allocated by the function under test.
  // Do NOT delete it->rep since it's a sentinel, not an actual object.
  delete it;
}

// Boundary: if DB::NewIterator returns nullptr, the wrapper still exists and contains nullptr.
TEST_F(LeveldbCreateIteratorTest_226, HandlesNullIteratorFromDB_226) {
  EXPECT_CALL(*mock_db_, NewIterator(Ref(c_ro_.rep)))
      .Times(1)
      .WillOnce(Return(nullptr));

  leveldb_iterator_t* it = leveldb_create_iterator(&c_db_, &c_ro_);
  ASSERT_NE(it, nullptr) << "Wrapper should still be allocated even if DB returns nullptr";
  EXPECT_EQ(it->rep, nullptr);

  delete it;
}

// Error case: null db pointer — dereference is undefined; we assert the call dies.
// (Death tests are appropriate for validating that invalid inputs are not handled.)
TEST_F(LeveldbCreateIteratorTest_226, NullDbPointerCausesDeath_226) {
#if GTEST_HAS_DEATH_TEST
  EXPECT_DEATH(
      {
        leveldb_iterator_t* it = leveldb_create_iterator(nullptr, &c_ro_);
        // Prevent unused variable warning (won't be reached).
        (void)it;
      },
      ".*");
#endif
}

// Error case: null options pointer — dereference is undefined; we assert the call dies.
TEST_F(LeveldbCreateIteratorTest_226, NullOptionsPointerCausesDeath_226) {
#if GTEST_HAS_DEATH_TEST
  EXPECT_DEATH(
      {
        leveldb_iterator_t* it = leveldb_create_iterator(&c_db_, nullptr);
        (void)it;
      },
      ".*");
#endif
}
