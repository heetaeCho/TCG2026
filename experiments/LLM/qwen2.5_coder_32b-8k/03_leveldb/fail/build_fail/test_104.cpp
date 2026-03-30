#include <gtest/gtest.h>

#include "db/memtable.h"

#include "util/status.h"

#include "util/slice.h"



namespace leveldb {



class MemTableTest_104 : public ::testing::Test {

protected:

    InternalKeyComparator comparator;

    MemTable* mem_table;



    void SetUp() override {

        mem_table = new MemTable(comparator);

        mem_table->Ref();

    }



    void TearDown() override {

        mem_table->Unref();

    }

};



TEST_F(MemTableTest_104, ApproximateMemoryUsage_ReturnsNonZero_104) {

    size_t usage = mem_table->ApproximateMemoryUsage();

    EXPECT_GT(usage, 0);

}



TEST_F(MemTableTest_104, NewIterator_ReturnsValidPointer_104) {

    Iterator* it = mem_table->NewIterator();

    EXPECT_NE(it, nullptr);

    delete it;

}



TEST_F(MemTableTest_104, AddAndGet_NormalOperation_104) {

    Slice key("test_key");

    Slice value("test_value");

    Status status;



    mem_table->Add(1, kTypeValue, key, value);



    std::string result;

    bool found = mem_table->Get(LookupKey(key, 1), &result, &status);

    EXPECT_TRUE(found);

    EXPECT_EQ(result, "test_value");

}



TEST_F(MemTableTest_104, AddAndGet_NotFound_104) {

    Slice key("non_existent_key");

    Status status;



    std::string result;

    bool found = mem_table->Get(LookupKey(key, 1), &result, &status);

    EXPECT_FALSE(found);

}



TEST_F(MemTableTest_104, AddAndGet_MultipleEntries_104) {

    Slice key1("key1");

    Slice value1("value1");

    Slice key2("key2");

    Slice value2("value2");



    mem_table->Add(1, kTypeValue, key1, value1);

    mem_table->Add(2, kTypeValue, key2, value2);



    std::string result;

    Status status;



    bool found1 = mem_table->Get(LookupKey(key1, 1), &result, &status);

    EXPECT_TRUE(found1);

    EXPECT_EQ(result, "value1");



    bool found2 = mem_table->Get(LookupKey(key2, 2), &result, &status);

    EXPECT_TRUE(found2);

    EXPECT_EQ(result, "value2");

}



TEST_F(MemTableTest_104, RefAndUnref_Balance_104) {

    size_t initial_refs = mem_table->refs_;



    mem_table->Ref();

    EXPECT_EQ(mem_table->refs_, initial_refs + 1);



    mem_table->Unref();

    EXPECT_EQ(mem_table->refs_, initial_refs);

}



TEST_F(MemTableTest_104, RefAndUnref_DeleteOnZeroRefs_104) {

    mem_table->Unref(); // Decrease to 0 and delete

    EXPECT_DEATH(mem_table->Ref(), ".*"); // Attempting to reference a deleted object

}



} // namespace leveldb
