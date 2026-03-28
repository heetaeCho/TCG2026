// File: db_c_iter_seek_to_last_test.cc

#include <gtest/gtest.h>
#include <gmock/gmock.h>

// ---- Minimal surface needed for testing (no internal logic) ----
// Forward-declare just enough of the production types to compile the test.
namespace leveldb {

// We only need SeekToLast for these tests.
// Keep this as small as possible to avoid re-implementing internal logic.
class Iterator {
public:
  virtual ~Iterator() = default;
  virtual void SeekToLast() = 0;
};

}  // namespace leveldb

// Mirror the C wrapper struct shape used by the function under test.
extern "C" {
struct leveldb_iterator_t { leveldb::Iterator* rep; };

// Declare the function under test.
void leveldb_iter_seek_to_last(leveldb_iterator_t* iter);
}

// ---- Mock collaborator ----
class MockIterator : public leveldb::Iterator {
public:
  ~MockIterator() override = default;
  MOCK_METHOD(void, SeekToLast, (), (override));
};

// ---- Tests ----

// Normal operation: one call leads to exactly one underlying SeekToLast call.
TEST(LevelDB_CIterSeekToLast_237, CallsSeekToLastOnce_237) {
  ::testing::StrictMock<MockIterator> mock;
  leveldb_iterator_t it{&mock};

  EXPECT_CALL(mock, SeekToLast()).Times(1);

  leveldb_iter_seek_to_last(&it);
}

// Boundary-ish observable behavior: calling the wrapper twice should forward twice.
TEST(LevelDB_CIterSeekToLast_237, CallsSeekToLastTwiceWhenInvokedTwice_237) {
  ::testing::StrictMock<MockIterator> mock;
  leveldb_iterator_t it{&mock};

  EXPECT_CALL(mock, SeekToLast()).Times(2);

  leveldb_iter_seek_to_last(&it);
  leveldb_iter_seek_to_last(&it);
}

// Defensive note on exceptional case surface:
// Passing nullptr (for iter or iter->rep) would be undefined behavior for this API.
// We document it with a disabled test to avoid intentional crashes.
TEST(LevelDB_CIterSeekToLast_237, DISABLED_NullIteratorIsUndefinedBehavior_237) {
  // This test is intentionally disabled because the function dereferences
  // its pointer arguments directly and would crash; there is no observable,
  // testable error channel exposed by the interface.
  // Example (do NOT enable):
  // leveldb_iter_seek_to_last(nullptr);
}
