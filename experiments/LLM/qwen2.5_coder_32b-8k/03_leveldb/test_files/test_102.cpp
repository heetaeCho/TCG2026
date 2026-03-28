#include "gtest/gtest.h"

#include "db/skiplist.h"

#include <string>



// Mock Comparator for testing

class MockComparator {

public:

    MOCK_CONST_METHOD2(Compare, int(const std::string&, const std::string&));

};



// Test fixture

class SkipListTest_102 : public ::testing::Test {

protected:

    Arena arena;

    MockComparator comparator;

    leveldb::SkipList<std::string, MockComparator> skip_list;



    SkipListTest_102() : skip_list(comparator, &arena) {}

};



// Test normal operation: Insert and Contains

TEST_F(SkipListTest_102, InsertAndContainsNormal_102) {

    std::string key = "test_key";

    EXPECT_CALL(comparator, Compare(::testing::_, ::testing::_)).Times(2);



    skip_list.Insert(key);

    EXPECT_TRUE(skip_list.Contains(key));

}



// Test boundary condition: Contains with empty list

TEST_F(SkipListTest_102, ContainsEmptyList_102) {

    std::string key = "test_key";

    EXPECT_CALL(comparator, Compare(::testing::_, ::testing::_)).Times(0);



    EXPECT_FALSE(skip_list.Contains(key));

}



// Test boundary condition: Insert multiple keys and Contains

TEST_F(SkipListTest_102, InsertMultipleAndContains_102) {

    std::string key1 = "key1";

    std::string key2 = "key2";

    std::string key3 = "key3";



    EXPECT_CALL(comparator, Compare(::testing::_, ::testing::_)).Times(6);



    skip_list.Insert(key1);

    skip_list.Insert(key2);

    skip_list.Insert(key3);



    EXPECT_TRUE(skip_list.Contains(key1));

    EXPECT_TRUE(skip_list.Contains(key2));

    EXPECT_TRUE(skip_list.Contains(key3));

}



// Test exceptional case: Insert duplicate key and Contains

TEST_F(SkipListTest_102, InsertDuplicateKey_102) {

    std::string key = "duplicate_key";



    EXPECT_CALL(comparator, Compare(::testing::_, ::testing::_)).Times(4);



    skip_list.Insert(key);

    skip_list.Insert(key); // Duplicate insertion



    EXPECT_TRUE(skip_list.Contains(key));

}



// Test boundary condition: Contains with non-existent key

TEST_F(SkipListTest_102, ContainsNonExistentKey_102) {

    std::string existing_key = "existing_key";

    std::string non_existent_key = "non_existent_key";



    EXPECT_CALL(comparator, Compare(::testing::_, ::testing::_)).Times(3);



    skip_list.Insert(existing_key);

    EXPECT_FALSE(skip_list.Contains(non_existent_key));

}
