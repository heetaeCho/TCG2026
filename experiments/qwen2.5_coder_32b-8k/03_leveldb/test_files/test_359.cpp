#include <gtest/gtest.h>

#include "db/memtable.h"



using namespace leveldb;



class MemTableIteratorTest_359 : public ::testing::Test {

protected:

    MemTable table;

    MemTableIterator* iterator;



    void SetUp() override {

        iterator = new MemTableIterator(&table);

    }



    void TearDown() override {

        delete iterator;

    }

};



TEST_F(MemTableIteratorTest_359, SeekToFirst_NonEmptyTable_359) {

    // Assuming there are elements in the table

    iterator->SeekToFirst();

    EXPECT_TRUE(iterator->Valid());

}



TEST_F(MemTableIteratorTest_359, SeekToFirst_EmptyTable_359) {

    // Assuming the table is empty

    iterator->SeekToFirst();

    EXPECT_FALSE(iterator->Valid());

}



// Additional tests for boundary conditions and exceptional cases



TEST_F(MemTableIteratorTest_359, Valid_AfterInitialization_359) {

    EXPECT_FALSE(iterator->Valid());

}



TEST_F(MemTableIteratorTest_359, Seek_ValidKey_359) {

    // Assuming "key" is a valid key in the table

    Slice key("test_key");

    iterator->Seek(key);

    EXPECT_TRUE(iterator->Valid());

}



TEST_F(MemTableIteratorTest_359, Seek_InvalidKey_359) {

    // Assuming "invalid_key" is not present in the table

    Slice invalid_key("non_existent_key");

    iterator->Seek(invalid_key);

    EXPECT_FALSE(iterator->Valid());

}



// Additional tests for external interactions if any



TEST_F(MemTableIteratorTest_359, Status_AfterSeekToFirst_359) {

    iterator->SeekToFirst();

    EXPECT_EQ(Status::OK(), iterator->status());

}



TEST_F(MemTableIteratorTest_359, Key_Value_Accessors_359) {

    // Assuming the table has at least one element

    Slice key("test_key");

    iterator->Seek(key);

    if (iterator->Valid()) {

        EXPECT_EQ("test_key", iterator->key().ToString());

        // Assuming we know the value for "test_key"

        EXPECT_EQ("expected_value", iterator->value().ToString());

    }

}
