#include <gtest/gtest.h>

#include "db/dbformat.h"



namespace leveldb {



class PackSequenceAndTypeTest_184 : public ::testing::Test {

protected:

    void TestPackSequenceAndType(uint64_t seq, ValueType t, uint64_t expected) {

        EXPECT_EQ(PackSequenceAndType(seq, t), expected);

    }

};



TEST_F(PackSequenceAndTypeTest_184, NormalOperation_184) {

    TestPackSequenceAndType(0x123456789ABCDEFULL >> 8, kTypeValue, 0x123456789ABCDEFULL);

}



TEST_F(PackSequenceAndTypeTest_184, SequenceZero_184) {

    TestPackSequenceAndType(0, kTypeValue, kTypeValue);

}



TEST_F(PackSequenceAndTypeTest_184, TypeZero_184) {

    TestPackSequenceAndType(kMaxSequenceNumber, static_cast<ValueType>(0), kMaxSequenceNumber << 8);

}



TEST_F(PackSequenceAndTypeTest_184, MaxValues_184) {

    TestPackSequenceAndType(kMaxSequenceNumber, kValueTypeForSeek, (kMaxSequenceNumber << 8) | kValueTypeForSeek);

}



TEST_F(PackSequenceAndTypeTest_184, BoundaryCondition_SequenceMaxMinusOne_184) {

    TestPackSequenceAndType(kMaxSequenceNumber - 1, kTypeValue, ((kMaxSequenceNumber - 1) << 8) | kTypeValue);

}



TEST_F(PackSequenceAndTypeTest_184, BoundaryCondition_TypeMaxMinusOne_184) {

    TestPackSequenceAndType(0, static_cast<ValueType>(kValueTypeForSeek - 1), kValueTypeForSeek - 1);

}



}  // namespace leveldb
