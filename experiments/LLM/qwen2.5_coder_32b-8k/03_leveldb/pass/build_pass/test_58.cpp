#include <gtest/gtest.h>

#include "db/dbformat.h"



using namespace leveldb;



class LookupKeyTest_58 : public ::testing::Test {

protected:

    Slice user_key = Slice("test_user_key");

    SequenceNumber sequence = 12345;

};



TEST_F(LookupKeyTest_58, InternalKeyReturnsValidSlice_58) {

    LookupKey lookup_key(user_key, sequence);

    Slice internal_key_slice = lookup_key.internal_key();

    EXPECT_FALSE(internal_key_slice.empty());

}



TEST_F(LookupKeyTest_58, UserKeyReturnsOriginalUserKey_58) {

    LookupKey lookup_key(user_key, sequence);

    Slice retrieved_user_key = lookup_key.user_key();

    EXPECT_EQ(retrieved_user_key.compare(user_key), 0);

}



TEST_F(LookupKeyTest_58, MemtableKeyReturnsValidSlice_58) {

    LookupKey lookup_key(user_key, sequence);

    Slice memtable_key_slice = lookup_key.memtable_key();

    EXPECT_FALSE(memtable_key_slice.empty());

}



// Boundary condition: Empty user key

TEST_F(LookupKeyTest_58, InternalKeyWithEmptyUserKey_58) {

    Slice empty_user_key = Slice("");

    LookupKey lookup_key(empty_user_key, sequence);

    Slice internal_key_slice = lookup_key.internal_key();

    EXPECT_FALSE(internal_key_slice.empty());

}



TEST_F(LookupKeyTest_58, UserKeyWithEmptyUserKey_58) {

    Slice empty_user_key = Slice("");

    LookupKey lookup_key(empty_user_key, sequence);

    Slice retrieved_user_key = lookup_key.user_key();

    EXPECT_EQ(retrieved_user_key.compare(empty_user_key), 0);

}



TEST_F(LookupKeyTest_58, MemtableKeyWithEmptyUserKey_58) {

    Slice empty_user_key = Slice("");

    LookupKey lookup_key(empty_user_key, sequence);

    Slice memtable_key_slice = lookup_key.memtable_key();

    EXPECT_FALSE(memtable_key_slice.empty());

}



// Exceptional case: Large user key

TEST_F(LookupKeyTest_58, InternalKeyWithLargeUserKey_58) {

    std::string large_user_key(1000, 'a'); // Larger than the internal buffer size (200)

    Slice large_slice(large_user_key);

    LookupKey lookup_key(large_slice, sequence);

    Slice internal_key_slice = lookup_key.internal_key();

    EXPECT_FALSE(internal_key_slice.empty());

}



TEST_F(LookupKeyTest_58, UserKeyWithLargeUserKey_58) {

    std::string large_user_key(1000, 'a'); // Larger than the internal buffer size (200)

    Slice large_slice(large_user_key);

    LookupKey lookup_key(large_slice, sequence);

    Slice retrieved_user_key = lookup_key.user_key();

    EXPECT_EQ(retrieved_user_key.compare(large_slice), 0);

}



TEST_F(LookupKeyTest_58, MemtableKeyWithLargeUserKey_58) {

    std::string large_user_key(1000, 'a'); // Larger than the internal buffer size (200)

    Slice large_slice(large_user_key);

    LookupKey lookup_key(large_slice, sequence);

    Slice memtable_key_slice = lookup_key.memtable_key();

    EXPECT_FALSE(memtable_key_slice.empty());

}
