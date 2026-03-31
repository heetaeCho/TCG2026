#include "gtest/gtest.h"
#include "leveldb/c.h"

#include <cstring>
#include <string>

// External C API declarations
extern "C" {
// These are the C API functions we need
leveldb_comparator_t* leveldb_comparator_create(
    void* state,
    void (*destructor)(void*),
    int (*compare)(void*, const char* a, size_t alen, const char* b, size_t blen),
    const char* (*name)(void*));

void leveldb_comparator_destroy(leveldb_comparator_t* cmp);
}

// Test helper: track whether destructor was called
static bool g_destructor_called_268 = false;
static void* g_destructor_state_268 = nullptr;

static void TestDestructor_268(void* state) {
    g_destructor_called_268 = true;
    g_destructor_state_268 = state;
}

static int TestCompare_268(void* state, const char* a, size_t alen,
                           const char* b, size_t blen) {
    // Simple bytewise comparison
    size_t min_len = (alen < blen) ? alen : blen;
    int r = memcmp(a, b, min_len);
    if (r == 0) {
        if (alen < blen) return -1;
        if (alen > blen) return 1;
        return 0;
    }
    return r;
}

static const char* TestName_268(void* state) {
    return "test_comparator_268";
}

class LevelDBComparatorDestroyTest_268 : public ::testing::Test {
protected:
    void SetUp() override {
        g_destructor_called_268 = false;
        g_destructor_state_268 = nullptr;
    }
};

// Test that destroying a comparator calls the destructor callback
TEST_F(LevelDBComparatorDestroyTest_268, DestroyCallsDestructor_268) {
    int dummy_state = 42;
    leveldb_comparator_t* cmp = leveldb_comparator_create(
        &dummy_state,
        TestDestructor_268,
        TestCompare_268,
        TestName_268);

    ASSERT_NE(cmp, nullptr);
    EXPECT_FALSE(g_destructor_called_268);

    leveldb_comparator_destroy(cmp);

    EXPECT_TRUE(g_destructor_called_268);
    EXPECT_EQ(g_destructor_state_268, &dummy_state);
}

// Test that destroying a comparator with nullptr state still works
TEST_F(LevelDBComparatorDestroyTest_268, DestroyWithNullState_268) {
    leveldb_comparator_t* cmp = leveldb_comparator_create(
        nullptr,
        TestDestructor_268,
        TestCompare_268,
        TestName_268);

    ASSERT_NE(cmp, nullptr);
    EXPECT_FALSE(g_destructor_called_268);

    leveldb_comparator_destroy(cmp);

    EXPECT_TRUE(g_destructor_called_268);
    EXPECT_EQ(g_destructor_state_268, nullptr);
}

// Test that destroying a null comparator doesn't crash
// Note: This tests the behavior of delete on nullptr, which is defined in C++ as a no-op
TEST_F(LevelDBComparatorDestroyTest_268, DestroyNullComparator_268) {
    leveldb_comparator_destroy(nullptr);
    // If we reach here without crashing, the test passes
    EXPECT_FALSE(g_destructor_called_268);
}

// Test that destructor is called exactly once per destroy
TEST_F(LevelDBComparatorDestroyTest_268, DestructorCalledOncePerDestroy_268) {
    static int destructor_call_count_268 = 0;
    destructor_call_count_268 = 0;

    auto counting_destructor = [](void* state) {
        destructor_call_count_268++;
    };

    leveldb_comparator_t* cmp = leveldb_comparator_create(
        nullptr,
        counting_destructor,
        TestCompare_268,
        TestName_268);

    ASSERT_NE(cmp, nullptr);
    EXPECT_EQ(destructor_call_count_268, 0);

    leveldb_comparator_destroy(cmp);

    EXPECT_EQ(destructor_call_count_268, 1);
}

// Test that the state pointer is correctly passed to the destructor
TEST_F(LevelDBComparatorDestroyTest_268, DestructorReceivesCorrectState_268) {
    std::string state_string = "test_state_268";
    void* expected_state = &state_string;

    leveldb_comparator_t* cmp = leveldb_comparator_create(
        expected_state,
        TestDestructor_268,
        TestCompare_268,
        TestName_268);

    ASSERT_NE(cmp, nullptr);

    leveldb_comparator_destroy(cmp);

    EXPECT_TRUE(g_destructor_called_268);
    EXPECT_EQ(g_destructor_state_268, expected_state);
}

// Test creating and destroying multiple comparators independently
TEST_F(LevelDBComparatorDestroyTest_268, MultipleComparatorsDestroy_268) {
    static int destroy_count_268 = 0;
    destroy_count_268 = 0;

    auto counting_destructor = [](void* state) {
        destroy_count_268++;
    };

    int state1 = 1, state2 = 2, state3 = 3;

    leveldb_comparator_t* cmp1 = leveldb_comparator_create(
        &state1, counting_destructor, TestCompare_268, TestName_268);
    leveldb_comparator_t* cmp2 = leveldb_comparator_create(
        &state2, counting_destructor, TestCompare_268, TestName_268);
    leveldb_comparator_t* cmp3 = leveldb_comparator_create(
        &state3, counting_destructor, TestCompare_268, TestName_268);

    ASSERT_NE(cmp1, nullptr);
    ASSERT_NE(cmp2, nullptr);
    ASSERT_NE(cmp3, nullptr);

    leveldb_comparator_destroy(cmp1);
    EXPECT_EQ(destroy_count_268, 1);

    leveldb_comparator_destroy(cmp2);
    EXPECT_EQ(destroy_count_268, 2);

    leveldb_comparator_destroy(cmp3);
    EXPECT_EQ(destroy_count_268, 3);
}
