#include <gtest/gtest.h>

#include "db/dbformat.h"

#include "leveldb/slice.h"



using namespace leveldb;



class LookupKeyTest_60 : public ::testing::Test {

protected:

    static constexpr SequenceNumber kSeq = 123;

    Slice user_key_;

    LookupKey* lookup_key_;



    void SetUp() override {

        const char* key_data = "testkey";

        user_key_ = Slice(key_data, strlen(key_data));

        lookup_key_ = new LookupKey(user_key_, kSeq);

    }



    void TearDown() override {

        delete lookup_key_;

    }

};



TEST_F(LookupKeyTest_60, ConstructorAndGetters_60) {

    EXPECT_EQ(lookup_key_->user_key().ToString(), "testkey");

}



TEST_F(LookupKeyTest_60, MemtableKey_ReturnsValidSlice_60) {

    Slice memtable_key = lookup_key_->memtable_key();

    EXPECT_FALSE(memtable_key.empty());

    // Assuming memtable key length is greater than user key length due to sequence number encoding

    EXPECT_GT(memtable_key.size(), user_key_.size());

}



TEST_F(LookupKeyTest_60, InternalKey_ReturnsValidSlice_60) {

    Slice internal_key = lookup_key_->internal_key();

    EXPECT_FALSE(internal_key.empty());

    // Assuming internal key length is greater than user key length due to sequence number and type encoding

    EXPECT_GT(internal_key.size(), user_key_.size());

}



TEST_F(LookupKeyTest_60, CopyConstructor_IsDeleted_60) {

    static_assert(!std::is_copy_constructible<LookupKey>::value, "Copy constructor should be deleted");

}



TEST_F(LookupKeyTest_60, AssignmentOperator_IsDeleted_60) {

    static_assert(!std::is_assignable<LookupKey, LookupKey>::value, "Assignment operator should be deleted");

}
