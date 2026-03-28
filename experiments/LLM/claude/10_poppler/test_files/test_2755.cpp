#include <gtest/gtest.h>
#include <memory>
#include <string>
#include "PopplerCache.h"

// A simple test item class
class TestItem {
public:
    explicit TestItem(int val) : value(val) {}
    int value;
};

// Test fixture
class PopplerCacheTest_2755 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that creating a cache with a given size does not crash
TEST_F(PopplerCacheTest_2755, ConstructorDoesNotCrash_2755) {
    EXPECT_NO_THROW({
        PopplerCache<int, TestItem> cache(10);
    });
}

// Test that creating a cache with size 0 does not crash
TEST_F(PopplerCacheTest_2755, ConstructorWithZeroSize_2755) {
    EXPECT_NO_THROW({
        PopplerCache<int, TestItem> cache(0);
    });
}

// Test that creating a cache with size 1 works
TEST_F(PopplerCacheTest_2755, ConstructorWithSizeOne_2755) {
    EXPECT_NO_THROW({
        PopplerCache<int, TestItem> cache(1);
    });
}

// Test that lookup on an empty cache returns nullptr
TEST_F(PopplerCacheTest_2755, LookupEmptyCacheReturnsNull_2755) {
    PopplerCache<int, TestItem> cache(10);
    TestItem *result = cache.lookup(42);
    EXPECT_EQ(result, nullptr);
}

// Test that after putting an item, lookup returns it
TEST_F(PopplerCacheTest_2755, PutAndLookupReturnsItem_2755) {
    PopplerCache<int, TestItem> cache(10);
    cache.put(1, std::make_unique<TestItem>(100));
    TestItem *result = cache.lookup(1);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->value, 100);
}

// Test that lookup for a non-existent key returns nullptr
TEST_F(PopplerCacheTest_2755, LookupNonExistentKeyReturnsNull_2755) {
    PopplerCache<int, TestItem> cache(10);
    cache.put(1, std::make_unique<TestItem>(100));
    TestItem *result = cache.lookup(2);
    EXPECT_EQ(result, nullptr);
}

// Test putting multiple items and looking them up
TEST_F(PopplerCacheTest_2755, PutMultipleAndLookup_2755) {
    PopplerCache<int, TestItem> cache(10);
    cache.put(1, std::make_unique<TestItem>(10));
    cache.put(2, std::make_unique<TestItem>(20));
    cache.put(3, std::make_unique<TestItem>(30));

    TestItem *r1 = cache.lookup(1);
    TestItem *r2 = cache.lookup(2);
    TestItem *r3 = cache.lookup(3);

    ASSERT_NE(r1, nullptr);
    EXPECT_EQ(r1->value, 10);
    ASSERT_NE(r2, nullptr);
    EXPECT_EQ(r2->value, 20);
    ASSERT_NE(r3, nullptr);
    EXPECT_EQ(r3->value, 30);
}

// Test that putting an item with an existing key updates the item
TEST_F(PopplerCacheTest_2755, PutDuplicateKeyUpdatesValue_2755) {
    PopplerCache<int, TestItem> cache(10);
    cache.put(1, std::make_unique<TestItem>(100));
    cache.put(1, std::make_unique<TestItem>(200));

    TestItem *result = cache.lookup(1);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->value, 200);
}

// Test cache eviction when cache is full (size = 1)
TEST_F(PopplerCacheTest_2755, CacheEvictionSizeOne_2755) {
    PopplerCache<int, TestItem> cache(1);
    cache.put(1, std::make_unique<TestItem>(100));
    
    TestItem *r1 = cache.lookup(1);
    ASSERT_NE(r1, nullptr);
    EXPECT_EQ(r1->value, 100);

    // Put a second item, should evict the first
    cache.put(2, std::make_unique<TestItem>(200));
    
    TestItem *r2 = cache.lookup(2);
    ASSERT_NE(r2, nullptr);
    EXPECT_EQ(r2->value, 200);

    // First item may have been evicted
    TestItem *r1_after = cache.lookup(1);
    // With size 1, the first should be evicted
    EXPECT_EQ(r1_after, nullptr);
}

// Test cache eviction when cache is full (size = 3)
TEST_F(PopplerCacheTest_2755, CacheEvictionSizeThree_2755) {
    PopplerCache<int, TestItem> cache(3);
    cache.put(1, std::make_unique<TestItem>(10));
    cache.put(2, std::make_unique<TestItem>(20));
    cache.put(3, std::make_unique<TestItem>(30));

    // All three should be present
    EXPECT_NE(cache.lookup(1), nullptr);
    EXPECT_NE(cache.lookup(2), nullptr);
    EXPECT_NE(cache.lookup(3), nullptr);

    // Add a fourth item, which should evict one
    cache.put(4, std::make_unique<TestItem>(40));

    TestItem *r4 = cache.lookup(4);
    ASSERT_NE(r4, nullptr);
    EXPECT_EQ(r4->value, 40);

    // At least one of the earlier items should still be present (cache has size 3)
    int found_count = 0;
    if (cache.lookup(1) != nullptr) found_count++;
    if (cache.lookup(2) != nullptr) found_count++;
    if (cache.lookup(3) != nullptr) found_count++;
    // We expect exactly 2 of the original 3 to remain (plus the new one = 3 total)
    EXPECT_EQ(found_count, 2);
}

// Test with string keys
TEST_F(PopplerCacheTest_2755, StringKeyPutAndLookup_2755) {
    PopplerCache<std::string, TestItem> cache(5);
    cache.put("hello", std::make_unique<TestItem>(1));
    cache.put("world", std::make_unique<TestItem>(2));

    TestItem *r1 = cache.lookup(std::string("hello"));
    ASSERT_NE(r1, nullptr);
    EXPECT_EQ(r1->value, 1);

    TestItem *r2 = cache.lookup(std::string("world"));
    ASSERT_NE(r2, nullptr);
    EXPECT_EQ(r2->value, 2);

    TestItem *r3 = cache.lookup(std::string("missing"));
    EXPECT_EQ(r3, nullptr);
}

// Test put with raw pointer (if the raw pointer overload exists)
TEST_F(PopplerCacheTest_2755, PutRawPointerAndLookup_2755) {
    PopplerCache<int, TestItem> cache(5);
    cache.put(42, new TestItem(999));

    TestItem *result = cache.lookup(42);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->value, 999);
}

// Test large cache size
TEST_F(PopplerCacheTest_2755, LargeCacheSize_2755) {
    PopplerCache<int, TestItem> cache(1000);
    for (int i = 0; i < 1000; ++i) {
        cache.put(i, std::make_unique<TestItem>(i * 10));
    }
    for (int i = 0; i < 1000; ++i) {
        TestItem *result = cache.lookup(i);
        ASSERT_NE(result, nullptr) << "Key " << i << " should be present";
        EXPECT_EQ(result->value, i * 10);
    }
}

// Test that negative keys work
TEST_F(PopplerCacheTest_2755, NegativeKeys_2755) {
    PopplerCache<int, TestItem> cache(10);
    cache.put(-1, std::make_unique<TestItem>(111));
    cache.put(-100, std::make_unique<TestItem>(222));

    TestItem *r1 = cache.lookup(-1);
    ASSERT_NE(r1, nullptr);
    EXPECT_EQ(r1->value, 111);

    TestItem *r2 = cache.lookup(-100);
    ASSERT_NE(r2, nullptr);
    EXPECT_EQ(r2->value, 222);
}

// Test that the cache is non-copyable (compile-time check, just document it)
TEST_F(PopplerCacheTest_2755, CacheIsNonCopyable_2755) {
    EXPECT_FALSE(std::is_copy_constructible<PopplerCache<int, TestItem>>::value);
    EXPECT_FALSE(std::is_copy_assignable<PopplerCache<int, TestItem>>::value);
}

// Test repeated lookups return the same pointer
TEST_F(PopplerCacheTest_2755, RepeatedLookupReturnsSamePointer_2755) {
    PopplerCache<int, TestItem> cache(10);
    cache.put(5, std::make_unique<TestItem>(55));

    TestItem *r1 = cache.lookup(5);
    TestItem *r2 = cache.lookup(5);
    EXPECT_EQ(r1, r2);
}

// Test zero key
TEST_F(PopplerCacheTest_2755, ZeroKey_2755) {
    PopplerCache<int, TestItem> cache(5);
    cache.put(0, std::make_unique<TestItem>(0));

    TestItem *result = cache.lookup(0);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->value, 0);
}
