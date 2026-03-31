#include "gtest/gtest.h"
#include "leveldb/c.h"
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>

// Helper callbacks for testing

static void TestDestructor(void* state) {
  int* flag = static_cast<int*>(state);
  *flag = 1;  // Mark that destructor was called
}

static const char* TestName(void* state) {
  return "test_filter_policy";
}

static char* TestCreateFilter(void* state, const char* const* key_array,
                               const size_t* key_length_array, int num_keys,
                               size_t* filter_length) {
  // Simple filter: concatenate all keys
  size_t total_length = 0;
  for (int i = 0; i < num_keys; i++) {
    total_length += key_length_array[i];
  }
  char* filter = static_cast<char*>(malloc(total_length));
  size_t offset = 0;
  for (int i = 0; i < num_keys; i++) {
    memcpy(filter + offset, key_array[i], key_length_array[i]);
    offset += key_length_array[i];
  }
  *filter_length = total_length;
  return filter;
}

static uint8_t TestKeyMayMatch(void* state, const char* key, size_t length,
                                const char* filter, size_t filter_length) {
  // Simple match: check if key appears in filter
  if (length > filter_length) return 0;
  for (size_t i = 0; i <= filter_length - length; i++) {
    if (memcmp(filter + i, key, length) == 0) {
      return 1;
    }
  }
  return 0;
}

// Tests for leveldb_filterpolicy_create

class FilterPolicyCreateTest_269 : public ::testing::Test {
 protected:
  void TearDown() override {
    // Clean up any filter policies created during tests
  }
};

TEST_F(FilterPolicyCreateTest_269, CreateReturnsNonNull_269) {
  int state = 0;
  leveldb_filterpolicy_t* fp = leveldb_filterpolicy_create(
      &state, TestDestructor, TestCreateFilter, TestKeyMayMatch, TestName);
  ASSERT_NE(fp, nullptr);
  leveldb_filterpolicy_destroy(fp);
}

TEST_F(FilterPolicyCreateTest_269, DestructorCalledOnDestroy_269) {
  int destructor_called = 0;
  leveldb_filterpolicy_t* fp = leveldb_filterpolicy_create(
      &destructor_called, TestDestructor, TestCreateFilter, TestKeyMayMatch,
      TestName);
  ASSERT_NE(fp, nullptr);
  EXPECT_EQ(destructor_called, 0);
  leveldb_filterpolicy_destroy(fp);
  EXPECT_EQ(destructor_called, 1);
}

TEST_F(FilterPolicyCreateTest_269, NameReturnsCorrectName_269) {
  int state = 0;
  leveldb_filterpolicy_t* fp = leveldb_filterpolicy_create(
      &state, TestDestructor, TestCreateFilter, TestKeyMayMatch, TestName);
  ASSERT_NE(fp, nullptr);
  const char* name = leveldb_filterpolicy_name(fp);
  EXPECT_STREQ(name, "test_filter_policy");
  leveldb_filterpolicy_destroy(fp);
}

TEST_F(FilterPolicyCreateTest_269, NullStateAccepted_269) {
  // Use lambdas-compatible static functions that handle null state
  static auto null_destructor = [](void* state) {};
  static auto null_name = [](void* state) -> const char* {
    return "null_state_policy";
  };

  leveldb_filterpolicy_t* fp = leveldb_filterpolicy_create(
      nullptr,
      [](void* s) {},
      [](void* s, const char* const* k, const size_t* kl, int n,
         size_t* fl) -> char* {
        *fl = 0;
        return static_cast<char*>(malloc(1));
      },
      [](void* s, const char* k, size_t kl, const char* f,
         size_t fl) -> uint8_t { return 0; },
      [](void* s) -> const char* { return "null_state_policy"; });
  ASSERT_NE(fp, nullptr);
  const char* name = leveldb_filterpolicy_name(fp);
  EXPECT_STREQ(name, "null_state_policy");
  leveldb_filterpolicy_destroy(fp);
}

TEST_F(FilterPolicyCreateTest_269, StatePassedToCallbacks_269) {
  // We verify state is properly passed by using a custom state value
  struct TestState {
    int create_filter_called;
    int key_may_match_called;
    int destructor_called;
    int name_called;
  };

  TestState ts = {0, 0, 0, 0};

  leveldb_filterpolicy_t* fp = leveldb_filterpolicy_create(
      &ts,
      [](void* s) {
        static_cast<TestState*>(s)->destructor_called++;
      },
      [](void* s, const char* const* k, const size_t* kl, int n,
         size_t* fl) -> char* {
        static_cast<TestState*>(s)->create_filter_called++;
        *fl = 1;
        char* result = static_cast<char*>(malloc(1));
        result[0] = 'x';
        return result;
      },
      [](void* s, const char* k, size_t kl, const char* f,
         size_t fl) -> uint8_t {
        static_cast<TestState*>(s)->key_may_match_called++;
        return 1;
      },
      [](void* s) -> const char* {
        static_cast<TestState*>(s)->name_called++;
        return "state_test_policy";
      });

  ASSERT_NE(fp, nullptr);

  // Calling name should increment name_called
  const char* name = leveldb_filterpolicy_name(fp);
  EXPECT_STREQ(name, "state_test_policy");
  EXPECT_GE(ts.name_called, 1);

  // Destroy should call destructor
  leveldb_filterpolicy_destroy(fp);
  EXPECT_EQ(ts.destructor_called, 1);
}

TEST_F(FilterPolicyCreateTest_269, DifferentNameFunctions_269) {
  int state = 0;

  auto name_fn1 = [](void* s) -> const char* { return "policy_alpha"; };
  auto name_fn2 = [](void* s) -> const char* { return "policy_beta"; };

  leveldb_filterpolicy_t* fp1 = leveldb_filterpolicy_create(
      &state, [](void* s) {}, TestCreateFilter, TestKeyMayMatch, name_fn1);
  leveldb_filterpolicy_t* fp2 = leveldb_filterpolicy_create(
      &state, [](void* s) {}, TestCreateFilter, TestKeyMayMatch, name_fn2);

  EXPECT_STREQ(leveldb_filterpolicy_name(fp1), "policy_alpha");
  EXPECT_STREQ(leveldb_filterpolicy_name(fp2), "policy_beta");

  leveldb_filterpolicy_destroy(fp1);
  leveldb_filterpolicy_destroy(fp2);
}

TEST_F(FilterPolicyCreateTest_269, MultipleCreateAndDestroy_269) {
  int counter = 0;

  auto counting_destructor = [](void* s) {
    int* c = static_cast<int*>(s);
    (*c)++;
  };

  std::vector<leveldb_filterpolicy_t*> policies;
  for (int i = 0; i < 5; i++) {
    leveldb_filterpolicy_t* fp = leveldb_filterpolicy_create(
        &counter, counting_destructor, TestCreateFilter, TestKeyMayMatch,
        TestName);
    ASSERT_NE(fp, nullptr);
    policies.push_back(fp);
  }

  for (auto* fp : policies) {
    leveldb_filterpolicy_destroy(fp);
  }
  EXPECT_EQ(counter, 5);
}

// Integration test using the filter policy with a database
TEST_F(FilterPolicyCreateTest_269, UsedWithBloomFilterPattern_269) {
  // Test that the built-in bloom filter creation works
  leveldb_filterpolicy_t* bloom = leveldb_filterpolicy_create_bloom(10);
  ASSERT_NE(bloom, nullptr);

  const char* name = leveldb_filterpolicy_name(bloom);
  ASSERT_NE(name, nullptr);
  // Bloom filter has a specific name
  EXPECT_TRUE(strlen(name) > 0);

  leveldb_filterpolicy_destroy(bloom);
}

TEST_F(FilterPolicyCreateTest_269, EmptyNameFunction_269) {
  int state = 0;
  leveldb_filterpolicy_t* fp = leveldb_filterpolicy_create(
      &state, [](void* s) {},
      TestCreateFilter, TestKeyMayMatch,
      [](void* s) -> const char* { return ""; });
  ASSERT_NE(fp, nullptr);
  EXPECT_STREQ(leveldb_filterpolicy_name(fp), "");
  leveldb_filterpolicy_destroy(fp);
}
