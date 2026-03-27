#include <gtest/gtest.h>

#include "db/memtable.h"

#include "leveldb/slice.h"



using namespace leveldb;



class MemTableTest : public ::testing::Test {

protected:

    InternalKeyComparator comparator_;

    MemTable* memtable_;



    void SetUp() override {

        memtable_ = new MemTable(comparator_);

        memtable_->Ref();

    }



    void TearDown() override {

        memtable_->Unref();

    }

};



TEST_F(MemTableTest_367, AddNormalOperation_367) {

    Slice key("key1");

    Slice value("value1");

    memtable_->Add(0, kTypeValue, key, value);



    std::string result;

    Status status;

    bool found = memtable_->Get(LookupKey(key), &result, &status);

    EXPECT_TRUE(found);

    EXPECT_EQ(result, "value1");

}



TEST_F(MemTableTest_367, AddBoundaryEmptyKey_367) {

    Slice key("");

    Slice value("value1");

    memtable_->Add(0, kTypeValue, key, value);



    std::string result;

    Status status;

    bool found = memtable_->Get(LookupKey(key), &result, &status);

    EXPECT_TRUE(found);

    EXPECT_EQ(result, "value1");

}



TEST_F(MemTableTest_367, AddBoundaryEmptyValue_367) {

    Slice key("key1");

    Slice value("");

    memtable_->Add(0, kTypeValue, key, value);



    std::string result;

    Status status;

    bool found = memtable_->Get(LookupKey(key), &result, &status);

    EXPECT_TRUE(found);

    EXPECT_EQ(result, "");

}



TEST_F(MemTableTest_367, AddBoundaryLongKeyAndValue_367) {

    std::string long_key(1024, 'a');

    std::string long_value(1024, 'b');

    Slice key(long_key);

    Slice value(long_value);

    memtable_->Add(0, kTypeValue, key, value);



    std::string result;

    Status status;

    bool found = memtable_->Get(LookupKey(key), &result, &status);

    EXPECT_TRUE(found);

    EXPECT_EQ(result, long_value);

}



TEST_F(MemTableTest_367, GetNonExistentKey_367) {

    Slice key("non_existent_key");

    std::string result;

    Status status;

    bool found = memtable_->Get(LookupKey(key), &result, &status);

    EXPECT_FALSE(found);

}



TEST_F(MemTableTest_367, GetAfterMultipleAdds_367) {

    Slice key1("key1");

    Slice value1("value1");

    memtable_->Add(0, kTypeValue, key1, value1);



    Slice key2("key2");

    Slice value2("value2");

    memtable_->Add(1, kTypeValue, key2, value2);



    std::string result;

    Status status;



    bool found1 = memtable_->Get(LookupKey(key1), &result, &status);

    EXPECT_TRUE(found1);

    EXPECT_EQ(result, "value1");



    bool found2 = memtable_->Get(LookupKey(key2), &result, &status);

    EXPECT_TRUE(found2);

    EXPECT_EQ(result, "value2");

}



TEST_F(MemTableTest_367, ApproximateMemoryUsageAfterAdd_367) {

    size_t initial_usage = memtable_->ApproximateMemoryUsage();



    Slice key("key1");

    Slice value("value1");

    memtable_->Add(0, kTypeValue, key, value);



    size_t final_usage = memtable_->ApproximateMemoryUsage();

    EXPECT_GT(final_usage, initial_usage);

}



TEST_F(MemTableTest_367, NewIteratorAfterAdd_367) {

    Slice key("key1");

    Slice value("value1");

    memtable_->Add(0, kTypeValue, key, value);



    Iterator* iter = memtable_->NewIterator();

    iter->SeekToFirst();



    EXPECT_TRUE(iter->Valid());

    EXPECT_EQ(Slice(iter->key()), key);

    EXPECT_EQ(Slice(iter->value()), value);



    delete iter;

}
