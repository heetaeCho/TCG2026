#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "db/c.cc"

#include "leveldb/iterator.h"



using namespace leveldb;

using ::testing::_;

using ::testing::Invoke;

using ::testing::Return;



class MockIterator : public Iterator {

public:

    MOCK_METHOD(void, Seek, (const Slice& target), (override));

    MOCK_METHOD(bool, Valid, (), (const, override));

};



class LeveldbIterSeekTest_238 : public ::testing::Test {

protected:

    void SetUp() override {

        mock_iter = new MockIterator();

        iter_t.rep = mock_iter;

    }



    void TearDown() override {

        delete mock_iter;

    }



    leveldb_iterator_t iter_t;

    MockIterator* mock_iter;

};



TEST_F(LeveldbIterSeekTest_238, SeekCallsInternalSeek_238) {

    const char* key = "test_key";

    size_t klen = 8;



    EXPECT_CALL(*mock_iter, Seek(Slice(key, klen))).Times(1);



    leveldb_iter_seek(&iter_t, key, klen);

}



TEST_F(LeveldbIterSeekTest_238, SeekWithEmptyKey_238) {

    const char* key = "";

    size_t klen = 0;



    EXPECT_CALL(*mock_iter, Seek(Slice(key, klen))).Times(1);



    leveldb_iter_seek(&iter_t, key, klen);

}



TEST_F(LeveldbIterSeekTest_238, SeekWithMaxSizeKey_238) {

    const char* key = "a_very_long_key_that_might_test_boundary_conditions_in_the_implementation";

    size_t klen = strlen(key);



    EXPECT_CALL(*mock_iter, Seek(Slice(key, klen))).Times(1);



    leveldb_iter_seek(&iter_t, key, klen);

}
