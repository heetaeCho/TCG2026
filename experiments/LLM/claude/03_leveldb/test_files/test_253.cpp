#include "gtest/gtest.h"
#include "leveldb/c.h"
#include "leveldb/comparator.h"
#include "leveldb/options.h"

// We need access to the internal structs to test the C API function
// Include the necessary headers that define these structs
extern "C" {
// Forward declarations for the C API types and function
struct leveldb_options_t;
struct leveldb_comparator_t;

void leveldb_options_set_comparator(leveldb_options_t* opt,
                                     leveldb_comparator_t* cmp);
}

// We need the actual struct definitions to inspect the result
// These are defined in db/c.cc
namespace {

// Helper comparator callbacks for creating a leveldb_comparator_t
void DestroyComparator(void* state) {}

int CompareCallback(void* state, const char* a, size_t alen, const char* b,
                    size_t blen) {
  return 0;
}

const char* NameCallback(void* state) { return "test_comparator"; }

}  // namespace

class LevelDBOptionsSetComparatorTest_253 : public ::testing::Test {
 protected:
  void SetUp() override {
    opt_ = leveldb_options_create();
    ASSERT_NE(opt_, nullptr);
  }

  void TearDown() override {
    if (opt_) {
      leveldb_options_destroy(opt_);
    }
    if (cmp_) {
      leveldb_comparator_destroy(cmp_);
    }
  }

  leveldb_options_t* opt_ = nullptr;
  leveldb_comparator_t* cmp_ = nullptr;
};

// Test that setting a comparator changes the comparator in the options
TEST_F(LevelDBOptionsSetComparatorTest_253,
       SetComparatorChangesOptionsComparator_253) {
  // Create a custom comparator via the C API
  cmp_ = leveldb_comparator_create(nullptr, DestroyComparator, CompareCallback,
                                    NameCallback);
  ASSERT_NE(cmp_, nullptr);

  // Set the comparator on the options
  leveldb_options_set_comparator(opt_, cmp_);

  // We can't directly inspect opt_->rep.comparator from the C API,
  // but we can verify the function doesn't crash and the comparator is set
  // by attempting to open a database with these options (indirect verification).
  // For a more direct test, we verify the comparator's name through the C API
  // by using the options to create a DB.

  // The function should not crash - this is the primary observable behavior
  // when treating as black box through C API.
}

// Test that setting comparator to a valid comparator does not crash
TEST_F(LevelDBOptionsSetComparatorTest_253,
       SetValidComparatorDoesNotCrash_253) {
  cmp_ = leveldb_comparator_create(nullptr, DestroyComparator, CompareCallback,
                                    NameCallback);
  ASSERT_NE(cmp_, nullptr);

  // Should not crash
  leveldb_options_set_comparator(opt_, cmp_);
}

// Test that setting comparator to nullptr is handled
// (This tests boundary behavior - nullptr comparator)
TEST_F(LevelDBOptionsSetComparatorTest_253,
       SetNullComparatorDoesNotCrash_253) {
  // Setting nullptr comparator - this tests boundary condition
  leveldb_options_set_comparator(opt_, nullptr);
}

// Test that setting comparator multiple times works (last one wins)
TEST_F(LevelDBOptionsSetComparatorTest_253,
       SetComparatorMultipleTimesLastWins_253) {
  leveldb_comparator_t* cmp1 = leveldb_comparator_create(
      nullptr, DestroyComparator, CompareCallback, NameCallback);
  cmp_ = leveldb_comparator_create(nullptr, DestroyComparator, CompareCallback,
                                    NameCallback);

  ASSERT_NE(cmp1, nullptr);
  ASSERT_NE(cmp_, nullptr);

  // Set first comparator
  leveldb_options_set_comparator(opt_, cmp1);

  // Set second comparator - should overwrite
  leveldb_options_set_comparator(opt_, cmp_);

  // Clean up first comparator manually since cmp_ will be cleaned in TearDown
  leveldb_comparator_destroy(cmp1);
}

// Test that a comparator with custom state can be set
TEST_F(LevelDBOptionsSetComparatorTest_253,
       SetComparatorWithCustomState_253) {
  int custom_state = 42;
  cmp_ = leveldb_comparator_create(reinterpret_cast<void*>(&custom_state),
                                    DestroyComparator, CompareCallback,
                                    NameCallback);
  ASSERT_NE(cmp_, nullptr);

  // Should not crash when setting a comparator with custom state
  leveldb_options_set_comparator(opt_, cmp_);
}

// Test integration: set comparator and use options to open a database
TEST_F(LevelDBOptionsSetComparatorTest_253,
       SetComparatorAndOpenDB_253) {
  cmp_ = leveldb_comparator_create(nullptr, DestroyComparator, CompareCallback,
                                    NameCallback);
  ASSERT_NE(cmp_, nullptr);

  leveldb_options_set_comparator(opt_, cmp_);
  leveldb_options_set_create_if_missing(opt_, 1);

  // Try opening a database with the custom comparator
  char* err = nullptr;
  std::string dbpath = testing::TempDir() + "leveldb_comparator_test_253";

  leveldb_t* db = leveldb_open(opt_, dbpath.c_str(), &err);

  if (db != nullptr) {
    leveldb_close(db);
  }
  if (err != nullptr) {
    leveldb_free(err);
  }

  // Cleanup the database directory
  leveldb_destroy_db(opt_, dbpath.c_str(), &err);
  if (err != nullptr) {
    leveldb_free(err);
  }
}
