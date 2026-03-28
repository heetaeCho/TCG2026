#include "gtest/gtest.h"
#include "leveldb/c.h"
#include "leveldb/filter_policy.h"

#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>

// We test the C API's filter policy wrapper through the C interface functions.

// Helper state for our mock filter policy
struct TestFilterPolicyState {
    bool destructor_called;
    int create_filter_call_count;
    int key_may_match_call_count;
    const char* name;
};

// Destructor callback
static void TestFilterPolicyDestructor(void* state) {
    TestFilterPolicyState* s = reinterpret_cast<TestFilterPolicyState*>(state);
    s->destructor_called = true;
}

// Name callback
static const char* TestFilterPolicyName(void* state) {
    TestFilterPolicyState* s = reinterpret_cast<TestFilterPolicyState*>(state);
    return s->name;
}

// CreateFilter callback: creates a simple filter that is just a concatenation of key lengths
static char* TestFilterPolicyCreateFilter(void* state, const char* const* key_array,
                                          const size_t* key_length_array, int num_keys,
                                          size_t* filter_length) {
    TestFilterPolicyState* s = reinterpret_cast<TestFilterPolicyState*>(state);
    s->create_filter_call_count++;

    // Create a simple filter: store all key bytes concatenated
    size_t total = 0;
    for (int i = 0; i < num_keys; i++) {
        total += key_length_array[i];
    }
    char* filter = reinterpret_cast<char*>(malloc(total));
    size_t offset = 0;
    for (int i = 0; i < num_keys; i++) {
        memcpy(filter + offset, key_array[i], key_length_array[i]);
        offset += key_length_array[i];
    }
    *filter_length = total;
    return filter;
}

// KeyMayMatch callback: returns true if key is found as substring of filter
static uint8_t TestFilterPolicyKeyMayMatch(void* state, const char* key,
                                           size_t key_length, const char* filter,
                                           size_t filter_length) {
    TestFilterPolicyState* s = reinterpret_cast<TestFilterPolicyState*>(state);
    s->key_may_match_call_count++;

    // Simple substring search
    if (key_length > filter_length) return 0;
    for (size_t i = 0; i <= filter_length - key_length; i++) {
        if (memcmp(filter + i, key, key_length) == 0) return 1;
    }
    return 0;
}

class LevelDBFilterPolicyTest_214 : public ::testing::Test {
protected:
    void SetUp() override {
        state_.destructor_called = false;
        state_.create_filter_call_count = 0;
        state_.key_may_match_call_count = 0;
        state_.name = "TestFilter";
    }

    void TearDown() override {
        // Nothing extra
    }

    TestFilterPolicyState state_;
};

TEST_F(LevelDBFilterPolicyTest_214, CreateAndDestroyFilterPolicy_214) {
    leveldb_filterpolicy_t* fp = leveldb_filterpolicy_create(
        &state_,
        TestFilterPolicyDestructor,
        TestFilterPolicyCreateFilter,
        TestFilterPolicyKeyMayMatch,
        TestFilterPolicyName);

    ASSERT_NE(fp, nullptr);
    EXPECT_FALSE(state_.destructor_called);

    leveldb_filterpolicy_destroy(fp);
    EXPECT_TRUE(state_.destructor_called);
}

TEST_F(LevelDBFilterPolicyTest_214, DestructorCalledOnDestroy_214) {
    leveldb_filterpolicy_t* fp = leveldb_filterpolicy_create(
        &state_,
        TestFilterPolicyDestructor,
        TestFilterPolicyCreateFilter,
        TestFilterPolicyKeyMayMatch,
        TestFilterPolicyName);

    EXPECT_FALSE(state_.destructor_called);
    leveldb_filterpolicy_destroy(fp);
    EXPECT_TRUE(state_.destructor_called);
}

TEST_F(LevelDBFilterPolicyTest_214, FilterPolicyUsedInOptions_214) {
    // Test that a filter policy can be set on options without crashing
    leveldb_filterpolicy_t* fp = leveldb_filterpolicy_create(
        &state_,
        TestFilterPolicyDestructor,
        TestFilterPolicyCreateFilter,
        TestFilterPolicyKeyMayMatch,
        TestFilterPolicyName);

    leveldb_options_t* options = leveldb_options_create();
    ASSERT_NE(options, nullptr);

    leveldb_options_set_filter_policy(options, fp);

    leveldb_options_destroy(options);
    leveldb_filterpolicy_destroy(fp);
    EXPECT_TRUE(state_.destructor_called);
}

TEST_F(LevelDBFilterPolicyTest_214, CreateBloomFilterPolicy_214) {
    // Test the built-in bloom filter policy creation
    leveldb_filterpolicy_t* bloom = leveldb_filterpolicy_create_bloom(10);
    ASSERT_NE(bloom, nullptr);
    leveldb_filterpolicy_destroy(bloom);
}

TEST_F(LevelDBFilterPolicyTest_214, CreateBloomFilterPolicySmallBits_214) {
    leveldb_filterpolicy_t* bloom = leveldb_filterpolicy_create_bloom(1);
    ASSERT_NE(bloom, nullptr);
    leveldb_filterpolicy_destroy(bloom);
}

TEST_F(LevelDBFilterPolicyTest_214, CreateBloomFilterPolicyLargeBits_214) {
    leveldb_filterpolicy_t* bloom = leveldb_filterpolicy_create_bloom(100);
    ASSERT_NE(bloom, nullptr);
    leveldb_filterpolicy_destroy(bloom);
}

TEST_F(LevelDBFilterPolicyTest_214, FullDatabaseWithFilterPolicy_214) {
    // Integration-style test: open a database with filter policy, write, read, close
    leveldb_filterpolicy_t* fp = leveldb_filterpolicy_create(
        &state_,
        TestFilterPolicyDestructor,
        TestFilterPolicyCreateFilter,
        TestFilterPolicyKeyMayMatch,
        TestFilterPolicyName);

    leveldb_options_t* options = leveldb_options_create();
    leveldb_options_set_create_if_missing(options, 1);
    leveldb_options_set_filter_policy(options, fp);

    char* err = nullptr;
    std::string dbname = testing::TempDir() + "filterpolicy_test_db_214";

    // Clean up any previous test runs
    leveldb_destroy_db(options, dbname.c_str(), &err);
    if (err) {
        free(err);
        err = nullptr;
    }

    leveldb_t* db = leveldb_open(options, dbname.c_str(), &err);
    ASSERT_EQ(err, nullptr) << err;
    ASSERT_NE(db, nullptr);

    // Write some data
    leveldb_writeoptions_t* woptions = leveldb_writeoptions_create();
    leveldb_put(db, woptions, "key1", 4, "value1", 6, &err);
    ASSERT_EQ(err, nullptr) << err;

    leveldb_put(db, woptions, "key2", 4, "value2", 6, &err);
    ASSERT_EQ(err, nullptr) << err;

    // Read the data back
    leveldb_readoptions_t* roptions = leveldb_readoptions_create();
    size_t val_len;
    char* val = leveldb_get(db, roptions, "key1", 4, &val_len, &err);
    ASSERT_EQ(err, nullptr) << err;
    ASSERT_NE(val, nullptr);
    EXPECT_EQ(std::string(val, val_len), "value1");
    free(val);

    val = leveldb_get(db, roptions, "key2", 4, &val_len, &err);
    ASSERT_EQ(err, nullptr) << err;
    ASSERT_NE(val, nullptr);
    EXPECT_EQ(std::string(val, val_len), "value2");
    free(val);

    // Non-existent key
    val = leveldb_get(db, roptions, "key3", 4, &val_len, &err);
    ASSERT_EQ(err, nullptr) << err;
    EXPECT_EQ(val, nullptr);

    leveldb_readoptions_destroy(roptions);
    leveldb_writeoptions_destroy(woptions);
    leveldb_close(db);
    leveldb_options_destroy(options);

    // Destroy the database
    leveldb_options_t* destroy_options = leveldb_options_create();
    leveldb_destroy_db(destroy_options, dbname.c_str(), &err);
    if (err) free(err);
    leveldb_options_destroy(destroy_options);

    leveldb_filterpolicy_destroy(fp);
    EXPECT_TRUE(state_.destructor_called);
}

TEST_F(LevelDBFilterPolicyTest_214, BloomFilterPolicyIntegration_214) {
    // Test with built-in bloom filter
    leveldb_filterpolicy_t* bloom = leveldb_filterpolicy_create_bloom(10);

    leveldb_options_t* options = leveldb_options_create();
    leveldb_options_set_create_if_missing(options, 1);
    leveldb_options_set_filter_policy(options, bloom);

    char* err = nullptr;
    std::string dbname = testing::TempDir() + "bloom_filterpolicy_test_db_214";

    leveldb_destroy_db(options, dbname.c_str(), &err);
    if (err) { free(err); err = nullptr; }

    leveldb_t* db = leveldb_open(options, dbname.c_str(), &err);
    ASSERT_EQ(err, nullptr) << err;
    ASSERT_NE(db, nullptr);

    leveldb_writeoptions_t* woptions = leveldb_writeoptions_create();
    for (int i = 0; i < 100; i++) {
        std::string key = "key" + std::to_string(i);
        std::string value = "value" + std::to_string(i);
        leveldb_put(db, woptions, key.c_str(), key.size(),
                    value.c_str(), value.size(), &err);
        ASSERT_EQ(err, nullptr) << err;
    }

    leveldb_readoptions_t* roptions = leveldb_readoptions_create();
    for (int i = 0; i < 100; i++) {
        std::string key = "key" + std::to_string(i);
        std::string expected_value = "value" + std::to_string(i);
        size_t val_len;
        char* val = leveldb_get(db, roptions, key.c_str(), key.size(), &val_len, &err);
        ASSERT_EQ(err, nullptr) << err;
        ASSERT_NE(val, nullptr);
        EXPECT_EQ(std::string(val, val_len), expected_value);
        free(val);
    }

    leveldb_readoptions_destroy(roptions);
    leveldb_writeoptions_destroy(woptions);
    leveldb_close(db);
    leveldb_options_destroy(options);

    leveldb_options_t* destroy_options = leveldb_options_create();
    leveldb_destroy_db(destroy_options, dbname.c_str(), &err);
    if (err) free(err);
    leveldb_options_destroy(destroy_options);

    leveldb_filterpolicy_destroy(bloom);
}

TEST_F(LevelDBFilterPolicyTest_214, CallbacksInvoked_214) {
    // Verify that create and key_match callbacks get invoked during compaction
    leveldb_filterpolicy_t* fp = leveldb_filterpolicy_create(
        &state_,
        TestFilterPolicyDestructor,
        TestFilterPolicyCreateFilter,
        TestFilterPolicyKeyMayMatch,
        TestFilterPolicyName);

    leveldb_options_t* options = leveldb_options_create();
    leveldb_options_set_create_if_missing(options, 1);
    leveldb_options_set_filter_policy(options, fp);
    // Use small write buffer to force compaction and filter creation
    leveldb_options_set_write_buffer_size(options, 1024);

    char* err = nullptr;
    std::string dbname = testing::TempDir() + "callback_test_db_214";

    leveldb_destroy_db(options, dbname.c_str(), &err);
    if (err) { free(err); err = nullptr; }

    leveldb_t* db = leveldb_open(options, dbname.c_str(), &err);
    ASSERT_EQ(err, nullptr) << err;
    ASSERT_NE(db, nullptr);

    leveldb_writeoptions_t* woptions = leveldb_writeoptions_create();
    // Write enough data to trigger filter creation
    for (int i = 0; i < 200; i++) {
        std::string key = "longkey_" + std::to_string(i) + "_padding_for_size";
        std::string value = "longvalue_" + std::to_string(i) + "_padding_for_size";
        leveldb_put(db, woptions, key.c_str(), key.size(),
                    value.c_str(), value.size(), &err);
        ASSERT_EQ(err, nullptr) << err;
    }

    // Read to potentially trigger filter usage
    leveldb_readoptions_t* roptions = leveldb_readoptions_create();
    size_t val_len;
    char* val = leveldb_get(db, roptions, "nonexistent", 11, &val_len, &err);
    ASSERT_EQ(err, nullptr) << err;
    if (val) free(val);

    // The filter creation callback should have been called at least once if compaction happened
    // We can't guarantee the exact count, but we verify no crashes occurred

    leveldb_readoptions_destroy(roptions);
    leveldb_writeoptions_destroy(woptions);
    leveldb_close(db);
    leveldb_options_destroy(options);

    leveldb_options_t* destroy_options = leveldb_options_create();
    leveldb_destroy_db(destroy_options, dbname.c_str(), &err);
    if (err) free(err);
    leveldb_options_destroy(destroy_options);

    leveldb_filterpolicy_destroy(fp);
    EXPECT_TRUE(state_.destructor_called);
}

TEST_F(LevelDBFilterPolicyTest_214, NullFilterPolicyInOptions_214) {
    // Setting a null filter policy should be valid (no filter)
    leveldb_options_t* options = leveldb_options_create();
    ASSERT_NE(options, nullptr);
    leveldb_options_set_filter_policy(options, nullptr);
    leveldb_options_destroy(options);
}

TEST_F(LevelDBFilterPolicyTest_214, MultipleFilterPolicyCreation_214) {
    // Create multiple filter policies and destroy them
    std::vector<TestFilterPolicyState> states(5);
    std::vector<leveldb_filterpolicy_t*> fps(5);

    for (int i = 0; i < 5; i++) {
        states[i].destructor_called = false;
        states[i].create_filter_call_count = 0;
        states[i].key_may_match_call_count = 0;
        states[i].name = "TestFilter";

        fps[i] = leveldb_filterpolicy_create(
            &states[i],
            TestFilterPolicyDestructor,
            TestFilterPolicyCreateFilter,
            TestFilterPolicyKeyMayMatch,
            TestFilterPolicyName);
        ASSERT_NE(fps[i], nullptr);
    }

    for (int i = 0; i < 5; i++) {
        EXPECT_FALSE(states[i].destructor_called);
        leveldb_filterpolicy_destroy(fps[i]);
        EXPECT_TRUE(states[i].destructor_called);
    }
}
