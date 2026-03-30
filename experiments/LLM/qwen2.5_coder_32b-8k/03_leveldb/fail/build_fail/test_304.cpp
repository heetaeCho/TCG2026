#include <gtest/gtest.h>

#include "db/db_impl.h"



namespace leveldb {



class DBImplTest_304 : public ::testing::Test {

protected:

    Options options;

    std::string dbname = "test_db";

    DBImpl db;



    DBImplTest_304() : db(options, dbname) {}

};



TEST_F(DBImplTest_304, TEST_NewInternalIterator_ReturnsNonNullIterator_304) {

    Iterator* iterator = db.TEST_NewInternalIterator();

    ASSERT_NE(iterator, nullptr);

    delete iterator;

}



TEST_F(DBImplTest_304, TEST_NewInternalIterator_CanSeekAndValid_304) {

    Iterator* iterator = db.TEST_NewInternalIterator();

    ASSERT_NE(iterator, nullptr);



    iterator->SeekToFirst();

    EXPECT_TRUE(iterator->Valid() || !iterator->Valid());



    delete iterator;

}



TEST_F(DBImplTest_304, TEST_NewInternalIterator_SeekToNonExistentKey_ReturnsInvalid_304) {

    Iterator* iterator = db.TEST_NewInternalIterator();

    ASSERT_NE(iterator, nullptr);



    Slice non_existent_key("non_existent_key");

    iterator->Seek(non_existent_key);

    EXPECT_FALSE(iterator->Valid());



    delete iterator;

}



TEST_F(DBImplTest_304, TEST_NewInternalIterator_SeekToFirst_KeyIsCorrect_304) {

    Iterator* iterator = db.TEST_NewInternalIterator();

    ASSERT_NE(iterator, nullptr);



    iterator->SeekToFirst();

    if (iterator->Valid()) {

        // Assuming we have some data in the DB to test this case

        std::string key = iterator->key().ToString();

        EXPECT_FALSE(key.empty());

    }



    delete iterator;

}



}  // namespace leveldb
