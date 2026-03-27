#include <gtest/gtest.h>

#include "db/c.cc"

#include "leveldb/db.h"



using ::testing::Return;

using ::testing::_;



class LevelDBIteratorTest_226 : public ::testing::Test {

protected:

    void SetUp() override {

        db = new leveldb_t();

        read_options = new leveldb_readoptions_t();

        db->rep = new leveldb::DB();

        iterator = nullptr;

    }



    void TearDown() override {

        delete db->rep;

        delete db;

        delete read_options;

        if (iterator) {

            delete iterator->rep;

            delete iterator;

        }

    }



    leveldb_t* db;

    leveldb_readoptions_t* read_options;

    leveldb_iterator_t* iterator;

};



TEST_F(LevelDBIteratorTest_226, CreateIteratorSuccess_226) {

    EXPECT_NO_THROW(iterator = leveldb_create_iterator(db, read_options));

    ASSERT_NE(iterator, nullptr);

}



TEST_F(LevelDBIteratorTest_226, CreateIteratorNullDB_226) {

    delete db;

    db = nullptr;

    EXPECT_EQ(leveldb_create_iterator(db, read_options), nullptr);

}



TEST_F(LevelDBIteratorTest_226, CreateIteratorNullReadOptions_226) {

    delete read_options;

    read_options = nullptr;

    EXPECT_EQ(leveldb_create_iterator(db, read_options), nullptr);

}



TEST_F(LevelDBIteratorTest_226, CreateIteratorWithMockDB_226) {

    auto mock_db = std::make_unique<testing::NiceMock<leveldb::DB>>();

    db->rep = mock_db.get();

    EXPECT_CALL(*mock_db, NewIterator(_))

        .WillOnce(Return(new leveldb::Iterator()));



    iterator = leveldb_create_iterator(db, read_options);

    ASSERT_NE(iterator, nullptr);

}



TEST_F(LevelDBIteratorTest_226, CreateIteratorWithNullRepInMockDB_226) {

    auto mock_db = std::make_unique<testing::NiceMock<leveldb::DB>>();

    db->rep = mock_db.get();

    EXPECT_CALL(*mock_db, NewIterator(_))

        .WillOnce(Return(nullptr));



    iterator = leveldb_create_iterator(db, read_options);

    ASSERT_EQ(iterator, nullptr);

}
