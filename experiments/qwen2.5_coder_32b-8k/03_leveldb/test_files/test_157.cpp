#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "db/version_set.cc"

#include "db/dbformat.h"

#include "db/version_edit.h"



namespace leveldb {



class MockInternalKeyComparator : public InternalKeyComparator {

public:

    MOCK_CONST_METHOD2(Compare, int(const Slice &a, const Slice &b));

};



class VersionSetTest_157 : public ::testing::Test {

protected:

    void SetUp() override {

        internal_comparator = new NiceMock<MockInternalKeyComparator>();

        by_smallest_key.internal_comparator = internal_comparator;

    }



    void TearDown() override {

        delete internal_comparator;

    }



    MockInternalKeyComparator* internal_comparator;

    VersionSet::Builder::BySmallestKey by_smallest_key;



    FileMetaData* CreateFileMetaData(uint64_t number, const InternalKey& smallest, const InternalKey& largest) {

        FileMetaData* file = new FileMetaData();

        file->number = number;

        file->smallest = smallest;

        file->largest = largest;

        return file;

    }

};



TEST_F(VersionSetTest_157, CompareDifferentSmallestKeys_157) {

    InternalKey key1("key1");

    InternalKey key2("key2");

    FileMetaData* f1 = CreateFileMetaData(1, key1, InternalKey());

    FileMetaData* f2 = CreateFileMetaData(2, key2, InternalKey());



    EXPECT_CALL(*internal_comparator, Compare(key1.Encode(), key2.Encode()))

        .WillOnce(::testing::Return(-1));



    EXPECT_TRUE(by_smallest_key(f1, f2));

}



TEST_F(VersionSetTest_157, CompareSameSmallestKeysDifferentNumbers_157) {

    InternalKey key("key");

    FileMetaData* f1 = CreateFileMetaData(1, key, InternalKey());

    FileMetaData* f2 = CreateFileMetaData(2, key, InternalKey());



    EXPECT_CALL(*internal_comparator, Compare(key.Encode(), key.Encode()))

        .WillOnce(::testing::Return(0));



    EXPECT_TRUE(by_smallest_key(f1, f2));

}



TEST_F(VersionSetTest_157, CompareSameSmallestKeysSameNumbers_157) {

    InternalKey key("key");

    FileMetaData* f1 = CreateFileMetaData(1, key, InternalKey());

    FileMetaData* f2 = CreateFileMetaData(1, key, InternalKey());



    EXPECT_CALL(*internal_comparator, Compare(key.Encode(), key.Encode()))

        .WillOnce(::testing::Return(0));



    EXPECT_FALSE(by_smallest_key(f1, f2));

}



TEST_F(VersionSetTest_157, CompareSmallestKeysInReverseOrder_157) {

    InternalKey key1("key1");

    InternalKey key2("key2");

    FileMetaData* f1 = CreateFileMetaData(1, key1, InternalKey());

    FileMetaData* f2 = CreateFileMetaData(2, key2, InternalKey());



    EXPECT_CALL(*internal_comparator, Compare(key2.Encode(), key1.Encode()))

        .WillOnce(::testing::Return(1));



    EXPECT_FALSE(by_smallest_key(f2, f1));

}



TEST_F(VersionSetTest_157, CompareSmallestKeysEqualNumbersEqualOrder_157) {

    InternalKey key("key");

    FileMetaData* f1 = CreateFileMetaData(1, key, InternalKey());

    FileMetaData* f2 = CreateFileMetaData(1, key, InternalKey());



    EXPECT_CALL(*internal_comparator, Compare(key.Encode(), key.Encode()))

        .WillOnce(::testing::Return(0));



    EXPECT_FALSE(by_smallest_key(f1, f2));

}



TEST_F(VersionSetTest_157, CompareSmallestKeysEqualNumbersDifferentOrder_157) {

    InternalKey key("key");

    FileMetaData* f1 = CreateFileMetaData(1, key, InternalKey());

    FileMetaData* f2 = CreateFileMetaData(1, key, InternalKey());



    EXPECT_CALL(*internal_comparator, Compare(key.Encode(), key.Encode()))

        .WillOnce(::testing::Return(0));



    EXPECT_FALSE(by_smallest_key(f2, f1));

}



}  // namespace leveldb
