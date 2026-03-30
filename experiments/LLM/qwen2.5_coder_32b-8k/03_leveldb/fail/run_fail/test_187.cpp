#include <gtest/gtest.h>

#include "db/dbformat.h"

#include "leveldb/slice.h"



using namespace leveldb;



class InternalKeyTest_187 : public ::testing::Test {

protected:

    InternalKey key;

};



TEST_F(InternalKeyTest_187, DefaultConstructorDebugString_187) {

    EXPECT_EQ(key.DebugString(), "(bad)");

}



TEST_F(InternalKeyTest_187, InvalidRepDebugString_187) {

    key = InternalKey(Slice("invalid"), 0, kTypeValue);

    key.Clear();

    EXPECT_EQ(key.DebugString(), "(bad)");

}



TEST_F(InternalKeyTest_187, ValidRepDebugString_187) {

    Slice user_key("test");

    SequenceNumber seq = 42;

    ValueType type = kTypeDeletion;



    InternalKey valid_key(user_key, seq, type);

    EXPECT_EQ(valid_key.DebugString(), "test @ 42 : 1");

}



TEST_F(InternalKeyTest_187, BoundarySequenceNumberDebugString_187) {

    Slice user_key("boundary_test");

    SequenceNumber max_seq = std::numeric_limits<SequenceNumber>::max();

    ValueType type = kTypeValue;



    InternalKey boundary_key(user_key, max_seq, type);

    EXPECT_EQ(boundary_key.DebugString(), "boundary_test @ 18446744073709551615 : 0");

}



TEST_F(InternalKeyTest_187, EmptyUserKeyDebugString_187) {

    Slice empty_user_key;

    SequenceNumber seq = 123;

    ValueType type = kTypeValue;



    InternalKey empty_key(empty_user_key, seq, type);

    EXPECT_EQ(empty_key.DebugString(), " @ 123 : 0");

}



TEST_F(InternalKeyTest_187, DifferentValueTypeDebugString_187) {

    Slice user_key("value_types");

    SequenceNumber seq = 654;

    ValueType types[] = { kTypeValue, kTypeDeletion };



    for (auto type : types) {

        InternalKey value_type_key(user_key, seq, type);

        EXPECT_EQ(value_type_key.DebugString(), "value_types @ 654 : " + std::to_string(type));

    }

}
