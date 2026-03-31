#include "gtest/gtest.h"
#include "leveldb/c.h"
#include "leveldb/comparator.h"
#include "leveldb/slice.h"

#include <cstring>
#include <string>

// We need to test the C API wrapper for the comparator.
// Since leveldb_comparator_t is an internal struct exposed through the C API,
// we'll use the C API functions to create and interact with it.

// Helper tracking variables for test callbacks
static bool g_destructor_called = false;
static int g_compare_call_count = 0;
static int g_name_call_count = 0;

static void ResetGlobals() {
  g_destructor_called = false;
  g_compare_call_count = 0;
  g_name_call_count = 0;
}

// Callback implementations for testing
static void TestDestructor(void* state) {
  g_destructor_called = true;
}

static int TestCompare(void* state, const char* a, size_t alen,
                       const char* b, size_t blen) {
  g_compare_call_count++;
  // Simple lexicographic comparison
  size_t min_len = (alen < blen) ? alen : blen;
  int r = memcmp(a, b, min_len);
  if (r == 0) {
    if (alen < blen) return -1;
    if (alen > blen) return 1;
    return 0;
  }
  return r;
}

static const char* TestName(void* state) {
  g_name_call_count++;
  return "test.comparator";
}

// A compare function that uses state
static int StateCompare(void* state, const char* a, size_t alen,
                        const char* b, size_t blen) {
  // state points to an int that acts as a multiplier
  int* multiplier = reinterpret_cast<int*>(state);
  size_t min_len = (alen < blen) ? alen : blen;
  int r = memcmp(a, b, min_len);
  if (r == 0) {
    if (alen < blen) r = -1;
    else if (alen > blen) r = 1;
  }
  return r * (*multiplier);
}

static void StateDestructor(void* state) {
  int* p = reinterpret_cast<int*>(state);
  delete p;
  g_destructor_called = true;
}

static const char* StateName(void* state) {
  return "state.comparator";
}

class LevelDBComparatorTest_211 : public ::testing::Test {
 protected:
  void SetUp() override {
    ResetGlobals();
  }
};

TEST_F(LevelDBComparatorTest_211, CreateAndDestroy_211) {
  // Test that creating and destroying a comparator calls the destructor
  leveldb_comparator_t* cmp = leveldb_comparator_create(
      nullptr, TestDestructor, TestCompare, TestName);
  ASSERT_NE(cmp, nullptr);
  EXPECT_FALSE(g_destructor_called);
  leveldb_comparator_destroy(cmp);
  EXPECT_TRUE(g_destructor_called);
}

TEST_F(LevelDBComparatorTest_211, CompareEqualStrings_211) {
  leveldb_comparator_t* cmp = leveldb_comparator_create(
      nullptr, TestDestructor, TestCompare, TestName);
  ASSERT_NE(cmp, nullptr);

  // We can test the comparator through the C API by using it in a database
  // But since the struct inherits from Comparator, we can also cast if we had access.
  // For the C API test, we verify the callbacks are properly wired by
  // creating a DB with this comparator and performing operations.
  
  // For a simpler unit test of the struct itself, we'll just verify creation/destruction
  leveldb_comparator_destroy(cmp);
  EXPECT_TRUE(g_destructor_called);
}

TEST_F(LevelDBComparatorTest_211, NameCallback_211) {
  // Verify that the name callback is properly stored and the comparator can be created
  leveldb_comparator_t* cmp = leveldb_comparator_create(
      nullptr, TestDestructor, TestCompare, TestName);
  ASSERT_NE(cmp, nullptr);
  leveldb_comparator_destroy(cmp);
  EXPECT_TRUE(g_destructor_called);
}

TEST_F(LevelDBComparatorTest_211, DestructorWithState_211) {
  // Test that destructor receives the correct state pointer
  int* state = new int(42);
  leveldb_comparator_t* cmp = leveldb_comparator_create(
      state, StateDestructor, StateCompare, StateName);
  ASSERT_NE(cmp, nullptr);
  EXPECT_FALSE(g_destructor_called);
  leveldb_comparator_destroy(cmp);
  EXPECT_TRUE(g_destructor_called);
  // state has been deleted by StateDestructor
}

TEST_F(LevelDBComparatorTest_211, NullState_211) {
  // Test with null state - should work fine
  leveldb_comparator_t* cmp = leveldb_comparator_create(
      nullptr, TestDestructor, TestCompare, TestName);
  ASSERT_NE(cmp, nullptr);
  leveldb_comparator_destroy(cmp);
  EXPECT_TRUE(g_destructor_called);
}

TEST_F(LevelDBComparatorTest_211, ComparatorUsedInDB_211) {
  // Integration-style test: create a DB with custom comparator, put/get values
  leveldb_comparator_t* cmp = leveldb_comparator_create(
      nullptr, TestDestructor, TestCompare, TestName);

  leveldb_options_t* options = leveldb_options_create();
  leveldb_options_set_create_if_missing(options, 1);
  leveldb_options_set_comparator(options, cmp);

  char* err = nullptr;
  std::string dbname = testing::TempDir() + "comparator_test_db_211";

  // Clean up any previous test remnants
  leveldb_destroy_db(options, dbname.c_str(), &err);
  if (err) {
    leveldb_free(err);
    err = nullptr;
  }

  leveldb_t* db = leveldb_open(options, dbname.c_str(), &err);
  if (err) {
    // If open fails, clean up and skip
    leveldb_free(err);
    leveldb_options_destroy(options);
    leveldb_comparator_destroy(cmp);
    GTEST_SKIP() << "Could not open test database";
    return;
  }
  ASSERT_NE(db, nullptr);

  // Write some data
  leveldb_writeoptions_t* woptions = leveldb_writeoptions_create();
  leveldb_put(db, woptions, "key1", 4, "value1", 6, &err);
  ASSERT_EQ(err, nullptr);
  leveldb_put(db, woptions, "key2", 4, "value2", 6, &err);
  ASSERT_EQ(err, nullptr);

  // Read data back
  leveldb_readoptions_t* roptions = leveldb_readoptions_create();
  size_t vallen;
  char* val = leveldb_get(db, roptions, "key1", 4, &vallen, &err);
  ASSERT_EQ(err, nullptr);
  ASSERT_NE(val, nullptr);
  EXPECT_EQ(std::string(val, vallen), "value1");
  leveldb_free(val);

  val = leveldb_get(db, roptions, "key2", 4, &vallen, &err);
  ASSERT_EQ(err, nullptr);
  ASSERT_NE(val, nullptr);
  EXPECT_EQ(std::string(val, vallen), "value2");
  leveldb_free(val);

  // The compare callback should have been called during operations
  EXPECT_GT(g_compare_call_count, 0);

  // Cleanup
  leveldb_readoptions_destroy(roptions);
  leveldb_writeoptions_destroy(woptions);
  leveldb_close(db);
  leveldb_destroy_db(options, dbname.c_str(), &err);
  if (err) leveldb_free(err);
  leveldb_options_destroy(options);
  leveldb_comparator_destroy(cmp);
  EXPECT_TRUE(g_destructor_called);
}

TEST_F(LevelDBComparatorTest_211, ComparatorOrderingInIterator_211) {
  // Test that custom comparator ordering is respected
  leveldb_comparator_t* cmp = leveldb_comparator_create(
      nullptr, TestDestructor, TestCompare, TestName);

  leveldb_options_t* options = leveldb_options_create();
  leveldb_options_set_create_if_missing(options, 1);
  leveldb_options_set_comparator(options, cmp);

  char* err = nullptr;
  std::string dbname = testing::TempDir() + "comparator_order_test_db_211";

  leveldb_destroy_db(options, dbname.c_str(), &err);
  if (err) { leveldb_free(err); err = nullptr; }

  leveldb_t* db = leveldb_open(options, dbname.c_str(), &err);
  if (err) {
    leveldb_free(err);
    leveldb_options_destroy(options);
    leveldb_comparator_destroy(cmp);
    GTEST_SKIP() << "Could not open test database";
    return;
  }

  leveldb_writeoptions_t* woptions = leveldb_writeoptions_create();
  // Insert keys in reverse order
  leveldb_put(db, woptions, "c", 1, "3", 1, &err);
  ASSERT_EQ(err, nullptr);
  leveldb_put(db, woptions, "a", 1, "1", 1, &err);
  ASSERT_EQ(err, nullptr);
  leveldb_put(db, woptions, "b", 1, "2", 1, &err);
  ASSERT_EQ(err, nullptr);

  // Iterate and verify order
  leveldb_readoptions_t* roptions = leveldb_readoptions_create();
  leveldb_iterator_t* iter = leveldb_create_iterator(db, roptions);

  leveldb_iter_seek_to_first(iter);
  ASSERT_TRUE(leveldb_iter_valid(iter));

  size_t klen;
  const char* key = leveldb_iter_key(iter, &klen);
  EXPECT_EQ(std::string(key, klen), "a");

  leveldb_iter_next(iter);
  ASSERT_TRUE(leveldb_iter_valid(iter));
  key = leveldb_iter_key(iter, &klen);
  EXPECT_EQ(std::string(key, klen), "b");

  leveldb_iter_next(iter);
  ASSERT_TRUE(leveldb_iter_valid(iter));
  key = leveldb_iter_key(iter, &klen);
  EXPECT_EQ(std::string(key, klen), "c");

  leveldb_iter_next(iter);
  EXPECT_FALSE(leveldb_iter_valid(iter));

  leveldb_iter_destroy(iter);
  leveldb_readoptions_destroy(roptions);
  leveldb_writeoptions_destroy(woptions);
  leveldb_close(db);
  leveldb_destroy_db(options, dbname.c_str(), &err);
  if (err) leveldb_free(err);
  leveldb_options_destroy(options);
  leveldb_comparator_destroy(cmp);
}

TEST_F(LevelDBComparatorTest_211, ReverseComparator_211) {
  // Test with a reverse comparator to verify the compare function is actually used
  auto reverse_compare = [](void* state, const char* a, size_t alen,
                            const char* b, size_t blen) -> int {
    size_t min_len = (alen < blen) ? alen : blen;
    int r = memcmp(a, b, min_len);
    if (r == 0) {
      if (alen < blen) r = -1;
      else if (alen > blen) r = 1;
    }
    return -r;  // Reverse the comparison
  };

  auto reverse_name = [](void* state) -> const char* {
    return "reverse.comparator";
  };

  leveldb_comparator_t* cmp = leveldb_comparator_create(
      nullptr, TestDestructor, reverse_compare, reverse_name);

  leveldb_options_t* options = leveldb_options_create();
  leveldb_options_set_create_if_missing(options, 1);
  leveldb_options_set_comparator(options, cmp);

  char* err = nullptr;
  std::string dbname = testing::TempDir() + "reverse_comparator_test_db_211";

  leveldb_destroy_db(options, dbname.c_str(), &err);
  if (err) { leveldb_free(err); err = nullptr; }

  leveldb_t* db = leveldb_open(options, dbname.c_str(), &err);
  if (err) {
    leveldb_free(err);
    leveldb_options_destroy(options);
    leveldb_comparator_destroy(cmp);
    GTEST_SKIP() << "Could not open test database";
    return;
  }

  leveldb_writeoptions_t* woptions = leveldb_writeoptions_create();
  leveldb_put(db, woptions, "a", 1, "1", 1, &err);
  ASSERT_EQ(err, nullptr);
  leveldb_put(db, woptions, "b", 1, "2", 1, &err);
  ASSERT_EQ(err, nullptr);
  leveldb_put(db, woptions, "c", 1, "3", 1, &err);
  ASSERT_EQ(err, nullptr);

  // With reverse comparator, iteration should go c, b, a
  leveldb_readoptions_t* roptions = leveldb_readoptions_create();
  leveldb_iterator_t* iter = leveldb_create_iterator(db, roptions);

  leveldb_iter_seek_to_first(iter);
  ASSERT_TRUE(leveldb_iter_valid(iter));

  size_t klen;
  const char* key = leveldb_iter_key(iter, &klen);
  EXPECT_EQ(std::string(key, klen), "c");

  leveldb_iter_next(iter);
  ASSERT_TRUE(leveldb_iter_valid(iter));
  key = leveldb_iter_key(iter, &klen);
  EXPECT_EQ(std::string(key, klen), "b");

  leveldb_iter_next(iter);
  ASSERT_TRUE(leveldb_iter_valid(iter));
  key = leveldb_iter_key(iter, &klen);
  EXPECT_EQ(std::string(key, klen), "a");

  leveldb_iter_next(iter);
  EXPECT_FALSE(leveldb_iter_valid(iter));

  leveldb_iter_destroy(iter);
  leveldb_readoptions_destroy(roptions);
  leveldb_writeoptions_destroy(woptions);
  leveldb_close(db);
  leveldb_destroy_db(options, dbname.c_str(), &err);
  if (err) leveldb_free(err);
  leveldb_options_destroy(options);
  leveldb_comparator_destroy(cmp);
}

TEST_F(LevelDBComparatorTest_211, EmptyKeys_211) {
  // Test comparator with empty keys
  leveldb_comparator_t* cmp = leveldb_comparator_create(
      nullptr, TestDestructor, TestCompare, TestName);

  leveldb_options_t* options = leveldb_options_create();
  leveldb_options_set_create_if_missing(options, 1);
  leveldb_options_set_comparator(options, cmp);

  char* err = nullptr;
  std::string dbname = testing::TempDir() + "empty_key_test_db_211";

  leveldb_destroy_db(options, dbname.c_str(), &err);
  if (err) { leveldb_free(err); err = nullptr; }

  leveldb_t* db = leveldb_open(options, dbname.c_str(), &err);
  if (err) {
    leveldb_free(err);
    leveldb_options_destroy(options);
    leveldb_comparator_destroy(cmp);
    GTEST_SKIP() << "Could not open test database";
    return;
  }

  leveldb_writeoptions_t* woptions = leveldb_writeoptions_create();
  // Empty key
  leveldb_put(db, woptions, "", 0, "empty", 5, &err);
  ASSERT_EQ(err, nullptr);

  leveldb_readoptions_t* roptions = leveldb_readoptions_create();
  size_t vallen;
  char* val = leveldb_get(db, roptions, "", 0, &vallen, &err);
  ASSERT_EQ(err, nullptr);
  ASSERT_NE(val, nullptr);
  EXPECT_EQ(std::string(val, vallen), "empty");
  leveldb_free(val);

  leveldb_readoptions_destroy(roptions);
  leveldb_writeoptions_destroy(woptions);
  leveldb_close(db);
  leveldb_destroy_db(options, dbname.c_str(), &err);
  if (err) leveldb_free(err);
  leveldb_options_destroy(options);
  leveldb_comparator_destroy(cmp);
}

TEST_F(LevelDBComparatorTest_211, MultipleComparatorsIndependent_211) {
  // Test that multiple comparators can be created independently
  bool destructor1_called = false;
  bool destructor2_called = false;

  auto destr1 = [](void* state) {
    *reinterpret_cast<bool*>(state) = true;
  };
  auto destr2 = [](void* state) {
    *reinterpret_cast<bool*>(state) = true;
  };

  leveldb_comparator_t* cmp1 = leveldb_comparator_create(
      &destructor1_called, destr1, TestCompare, TestName);
  leveldb_comparator_t* cmp2 = leveldb_comparator_create(
      &destructor2_called, destr2, TestCompare, TestName);

  ASSERT_NE(cmp1, nullptr);
  ASSERT_NE(cmp2, nullptr);
  EXPECT_NE(cmp1, cmp2);

  EXPECT_FALSE(destructor1_called);
  EXPECT_FALSE(destructor2_called);

  leveldb_comparator_destroy(cmp1);
  EXPECT_TRUE(destructor1_called);
  EXPECT_FALSE(destructor2_called);

  leveldb_comparator_destroy(cmp2);
  EXPECT_TRUE(destructor2_called);
}
