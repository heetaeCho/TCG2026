#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "db/dbformat.h"

#include "leveldb/slice.h"



using namespace leveldb;



class LookupKeyTest : public ::testing::Test {

protected:

    static constexpr SequenceNumber sequence = 12345;

    static constexpr char user_key_data[] = "testkey";

    Slice user_key{user_key_data};

};



TEST_F(LookupKeyTest_482, UserKeyIsCorrect_482) {

    LookupKey key(user_key, sequence);

    EXPECT_EQ(key.user_key().ToString(), user_key.ToString());

}



TEST_F(LookupKeyTest_482, InternalKeyIncludesUserKeyAndSequence_482) {

    LookupKey key(user_key, sequence);

    Slice internal = key.internal_key();

    EXPECT_TRUE(internal.starts_with(user_key));

    // Further checks on the sequence and type encoding can be added if necessary

}



TEST_F(LookupKeyTest_482, MemtableKeyIsSameAsInternalKey_482) {

    LookupKey key(user_key, sequence);

    EXPECT_EQ(key.memtable_key().ToString(), key.internal_key().ToString());

}



TEST_F(LookupKeyTest_482, EmptyUserKeyHandling_482) {

    Slice empty_user_key;

    LookupKey key(empty_user_key, sequence);

    EXPECT_TRUE(key.user_key().empty());

    EXPECT_TRUE(key.internal_key().starts_with(empty_user_key));

}



TEST_F(LookupKeyTest_482, LargeUserKeyHandling_482) {

    std::string large_key(1000, 'a'); // Larger than space_ buffer

    Slice large_user_key(large_key);

    LookupKey key(large_user_key, sequence);

    EXPECT_EQ(key.user_key().ToString(), large_key);

}



TEST_F(LookupKeyTest_482, SequenceNumberBoundary_482) {

    LookupKey key(user_key, 0); // Min boundary

    EXPECT_TRUE(key.internal_key().size() > 0);



    LookupKey max_sequence_key(user_key, std::numeric_limits<SequenceNumber>::max()); // Max boundary

    EXPECT_TRUE(max_sequence_key.internal_key().size() > 0);

}



TEST_F(LookupKeyTest_482, DeletedUserKeyHandling_482) {

    Slice deleted_user_key("deletedkey");

    LookupKey key(deleted_user_key, sequence);

    EXPECT_EQ(key.user_key().ToString(), "deletedkey");

    EXPECT_TRUE(key.internal_key().starts_with(deleted_user_key));

}
