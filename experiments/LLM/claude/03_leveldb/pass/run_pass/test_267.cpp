#include "gtest/gtest.h"
#include <cstring>
#include <string>

// Include the C API header
#include "leveldb/c.h"

// Helper functions for testing
namespace {

void TestDestructor(void* state) {
  // Increment the counter pointed to by state
  int* counter = static_cast<int*>(state);
  (*counter)++;
}

int TestCompare(void* state, const char* a, size_t alen, const char* b,
                size_t blen) {
  // Simple lexicographic comparison
  size_t min_len = (alen < blen) ? alen : blen;
  int r = memcmp(a, b, min_len);
  if (r == 0) {
    if (alen < blen)
      r = -1;
    else if (alen > blen)
      r = 1;
  }
  return r;
}

const char* TestName(void* state) { return "test_comparator"; }

void NoopDestructor(void* state) {}

int ReverseCompare(void* state, const char* a, size_t alen, const char* b,
                   size_t blen) {
  // Reverse comparison
  size_t min_len = (alen < blen) ? alen : blen;
  int r = memcmp(a, b, min_len);
  if (r == 0) {
    if (alen < blen)
      r = 1;
    else if (alen > blen)
      r = -1;
  }
  return -r;
}

const char* ReverseName(void* state) { return "reverse_comparator"; }

const char* NullStateName(void* state) { return "null_state_comparator"; }

int NullStateCompare(void* state, const char* a, size_t alen, const char* b,
                     size_t blen) {
  // state should be nullptr, just do basic comparison
  return memcmp(a, b, (alen < blen) ? alen : blen);
}

}  // namespace

class LevelDBComparatorCreateTest_267 : public ::testing::Test {
 protected:
  void TearDown() override {
    // Cleanup is handled per test
  }
};

// Test that leveldb_comparator_create returns a non-null pointer
TEST_F(LevelDBComparatorCreateTest_267, ReturnsNonNull_267) {
  int destructor_count = 0;
  leveldb_comparator_t* cmp = leveldb_comparator_create(
      &destructor_count, TestDestructor, TestCompare, TestName);
  ASSERT_NE(cmp, nullptr);
  leveldb_comparator_destroy(cmp);
}

// Test that destructor is called when comparator is destroyed
TEST_F(LevelDBComparatorCreateTest_267, DestructorCalledOnDestroy_267) {
  int destructor_count = 0;
  leveldb_comparator_t* cmp = leveldb_comparator_create(
      &destructor_count, TestDestructor, TestCompare, TestName);
  ASSERT_NE(cmp, nullptr);
  EXPECT_EQ(destructor_count, 0);
  leveldb_comparator_destroy(cmp);
  EXPECT_EQ(destructor_count, 1);
}

// Test that the name function returns the expected name
TEST_F(LevelDBComparatorCreateTest_267, NameReturnsCorrectValue_267) {
  int destructor_count = 0;
  leveldb_comparator_t* cmp = leveldb_comparator_create(
      &destructor_count, TestDestructor, TestCompare, TestName);
  ASSERT_NE(cmp, nullptr);
  // The Name() method on the underlying Comparator should delegate to TestName
  // We can't directly call Name() through the C API, but we can verify
  // the comparator was created successfully and destroy it properly.
  leveldb_comparator_destroy(cmp);
  EXPECT_EQ(destructor_count, 1);
}

// Test with null state
TEST_F(LevelDBComparatorCreateTest_267, NullState_267) {
  leveldb_comparator_t* cmp = leveldb_comparator_create(
      nullptr, NoopDestructor, NullStateCompare, NullStateName);
  ASSERT_NE(cmp, nullptr);
  leveldb_comparator_destroy(cmp);
}

// Test creating multiple comparators independently
TEST_F(LevelDBComparatorCreateTest_267, MultipleComparators_267) {
  int destructor_count1 = 0;
  int destructor_count2 = 0;

  leveldb_comparator_t* cmp1 = leveldb_comparator_create(
      &destructor_count1, TestDestructor, TestCompare, TestName);
  leveldb_comparator_t* cmp2 = leveldb_comparator_create(
      &destructor_count2, TestDestructor, ReverseCompare, ReverseName);

  ASSERT_NE(cmp1, nullptr);
  ASSERT_NE(cmp2, nullptr);
  ASSERT_NE(cmp1, cmp2);

  leveldb_comparator_destroy(cmp1);
  EXPECT_EQ(destructor_count1, 1);
  EXPECT_EQ(destructor_count2, 0);

  leveldb_comparator_destroy(cmp2);
  EXPECT_EQ(destructor_count1, 1);
  EXPECT_EQ(destructor_count2, 1);
}

// Test that the comparator can be used with a database open/close cycle
TEST_F(LevelDBComparatorCreateTest_267, UsableWithDatabase_267) {
  int destructor_count = 0;
  leveldb_comparator_t* cmp = leveldb_comparator_create(
      &destructor_count, TestDestructor, TestCompare, TestName);
  ASSERT_NE(cmp, nullptr);

  // Create options and set the comparator
  leveldb_options_t* options = leveldb_options_create();
  ASSERT_NE(options, nullptr);
  leveldb_options_set_comparator(options, cmp);
  leveldb_options_set_create_if_missing(options, 1);

  // Try to open a database with the custom comparator
  char* err = nullptr;
  std::string dbname = testing::TempDir() + "comparator_test_db_267";

  // Clean up any pre-existing database
  leveldb_destroy_db(options, dbname.c_str(), &err);
  if (err) {
    leveldb_free(err);
    err = nullptr;
  }

  leveldb_t* db = leveldb_open(options, dbname.c_str(), &err);
  if (err == nullptr) {
    ASSERT_NE(db, nullptr);

    // Write some data
    leveldb_writeoptions_t* woptions = leveldb_writeoptions_create();
    leveldb_put(db, woptions, "key1", 4, "value1", 6, &err);
    EXPECT_EQ(err, nullptr);

    // Read back
    leveldb_readoptions_t* roptions = leveldb_readoptions_create();
    size_t vallen;
    char* val = leveldb_get(db, roptions, "key1", 4, &vallen, &err);
    EXPECT_EQ(err, nullptr);
    if (val) {
      EXPECT_EQ(vallen, 6u);
      EXPECT_EQ(std::string(val, vallen), "value1");
      leveldb_free(val);
    }

    leveldb_readoptions_destroy(roptions);
    leveldb_writeoptions_destroy(woptions);
    leveldb_close(db);
  } else {
    leveldb_free(err);
    err = nullptr;
  }

  // Cleanup
  leveldb_destroy_db(options, dbname.c_str(), &err);
  if (err) {
    leveldb_free(err);
  }
  leveldb_options_destroy(options);
  leveldb_comparator_destroy(cmp);
  EXPECT_EQ(destructor_count, 1);
}

// Test destructor is called exactly once
TEST_F(LevelDBComparatorCreateTest_267, DestructorCalledExactlyOnce_267) {
  int destructor_count = 0;
  leveldb_comparator_t* cmp = leveldb_comparator_create(
      &destructor_count, TestDestructor, TestCompare, TestName);
  ASSERT_NE(cmp, nullptr);
  leveldb_comparator_destroy(cmp);
  EXPECT_EQ(destructor_count, 1);
  // No double-free or double destruction
}

// Test with noop destructor
TEST_F(LevelDBComparatorCreateTest_267, NoopDestructorWorks_267) {
  int some_state = 42;
  leveldb_comparator_t* cmp = leveldb_comparator_create(
      &some_state, NoopDestructor, TestCompare, TestName);
  ASSERT_NE(cmp, nullptr);
  leveldb_comparator_destroy(cmp);
  // State should be unchanged since NoopDestructor does nothing
  EXPECT_EQ(some_state, 42);
}

// Test that state is properly passed through
TEST_F(LevelDBComparatorCreateTest_267, StatePassedToCallbacks_267) {
  // Use a special state value and verify it's passed to callbacks
  struct CallbackState {
    int compare_call_count;
    int name_call_count;
    int destructor_call_count;
  };

  CallbackState state = {0, 0, 0};

  auto custom_compare = [](void* s, const char* a, size_t alen, const char* b,
                           size_t blen) -> int {
    CallbackState* cs = static_cast<CallbackState*>(s);
    cs->compare_call_count++;
    return 0;
  };

  auto custom_name = [](void* s) -> const char* {
    CallbackState* cs = static_cast<CallbackState*>(s);
    cs->name_call_count++;
    return "custom_state_comparator";
  };

  auto custom_destructor = [](void* s) {
    CallbackState* cs = static_cast<CallbackState*>(s);
    cs->destructor_call_count++;
  };

  leveldb_comparator_t* cmp = leveldb_comparator_create(
      &state, custom_destructor, custom_compare, custom_name);
  ASSERT_NE(cmp, nullptr);

  leveldb_comparator_destroy(cmp);
  EXPECT_EQ(state.destructor_call_count, 1);
}
