#include <gtest/gtest.h>

#include "db/dbformat.h"



using namespace leveldb;



class LookupKeyTest_57 : public ::testing::Test {

protected:

    Slice user_key;

    SequenceNumber sequence_number;

    LookupKey* lookup_key;



    void SetUp() override {

        user_key = Slice("test_key");

        sequence_number = 123456;

        lookup_key = new LookupKey(user_key, sequence_number);

    }



    void TearDown() override {

        delete lookup_key;

    }

};



TEST_F(LookupKeyTest_57, MemtableKey_ReturnsValidSlice_57) {

    Slice memtable_slice = lookup_key->memtable_key();

    EXPECT_TRUE(!memtable_slice.empty());

}



TEST_F(LookupKeyTest_57, InternalKey_ReturnsValidSlice_57) {

    Slice internal_slice = lookup_key->internal_key();

    EXPECT_TRUE(!internal_slice.empty());

}



TEST_F(LookupKeyTest_57, UserKey_ReturnsOriginalUserKey_57) {

    Slice user_slice = lookup_key->user_key();

    EXPECT_EQ(user_slice.data(), user_key.data());

    EXPECT_EQ(user_slice.size(), user_key.size());

}



TEST_F(LookupKeyTest_57, DifferentSequenceNumbers_YieldDifferentMemtableKeys_57) {

    LookupKey different_sequence_key(user_key, sequence_number + 1);

    Slice original_memtable_slice = lookup_key->memtable_key();

    Slice different_memtable_slice = different_sequence_key.memtable_key();

    EXPECT_NE(original_memtable_slice.data(), different_memtable_slice.data());

}



TEST_F(LookupKeyTest_57, DifferentUserKeys_YieldDifferentMemtableKeys_57) {

    Slice different_user_key("different_test_key");

    LookupKey different_user_key_lookup(different_user_key, sequence_number);

    Slice original_memtable_slice = lookup_key->memtable_key();

    Slice different_memtable_slice = different_user_key_lookup.memtable_key();

    EXPECT_NE(original_memtable_slice.data(), different_memtable_slice.data());

}



TEST_F(LookupKeyTest_57, MemtableKey_SizeGreaterThanUserKey_57) {

    Slice memtable_slice = lookup_key->memtable_key();

    EXPECT_GT(memtable_slice.size(), user_key.size());

}
