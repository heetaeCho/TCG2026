#include <gtest/gtest.h>

#include "leveldb/write_batch.h"

#include "db/c.cc"



class WriteBatchTest_248 : public ::testing::Test {

protected:

    leveldb_writebatch_t* batch;



    void SetUp() override {

        batch = new leveldb_writebatch_t();

    }



    void TearDown() override {

        delete batch;

    }

};



TEST_F(WriteBatchTest_248, DeleteNormalOperation_248) {

    const char* key = "test_key";

    size_t klen = strlen(key);

    EXPECT_NO_THROW(leveldb_writebatch_delete(batch, key, klen));

}



TEST_F(WriteBatchTest_248, DeleteEmptyKey_248) {

    const char* key = "";

    size_t klen = 0;

    EXPECT_NO_THROW(leveldb_writebatch_delete(batch, key, klen));

}



TEST_F(WriteBatchTest_248, DeleteNullKey_248) {

    const char* key = nullptr;

    size_t klen = 0;

    EXPECT_THROW(leveldb_writebatch_delete(batch, key, klen), std::exception);

}
