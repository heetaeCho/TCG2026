#include <gtest/gtest.h>

#include "db/c.cc"

#include "leveldb/write_batch.h"



class WriteBatchTest_247 : public ::testing::Test {

protected:

    leveldb_writebatch_t* batch;



    void SetUp() override {

        batch = new leveldb_writebatch_t();

    }



    void TearDown() override {

        delete batch;

    }

};



TEST_F(WriteBatchTest_247, PutSingleEntry_247) {

    const char* key = "key1";

    const char* value = "value1";

    size_t klen = strlen(key);

    size_t vlen = strlen(value);



    leveldb_writebatch_put(batch, key, klen, value, vlen);



    // Since we can't access internal state, we rely on ApproximateSize to infer something was added.

    EXPECT_GT(batch->rep.ApproximateSize(), 0U);

}



TEST_F(WriteBatchTest_247, PutMultipleEntries_247) {

    const char* key1 = "key1";

    const char* value1 = "value1";

    size_t klen1 = strlen(key1);

    size_t vlen1 = strlen(value1);



    const char* key2 = "key2";

    const char* value2 = "value2";

    size_t klen2 = strlen(key2);

    size_t vlen2 = strlen(value2);



    leveldb_writebatch_put(batch, key1, klen1, value1, vlen1);

    leveldb_writebatch_put(batch, key2, klen2, value2, vlen2);



    // Since we can't access internal state, we rely on ApproximateSize to infer something was added.

    EXPECT_GT(batch->rep.ApproximateSize(), 0U);

}



TEST_F(WriteBatchTest_247, PutEmptyKey_247) {

    const char* key = "";

    const char* value = "value1";

    size_t klen = strlen(key);

    size_t vlen = strlen(value);



    leveldb_writebatch_put(batch, key, klen, value, vlen);



    // Since we can't access internal state, we rely on ApproximateSize to infer something was added.

    EXPECT_GT(batch->rep.ApproximateSize(), 0U);

}



TEST_F(WriteBatchTest_247, PutEmptyValue_247) {

    const char* key = "key1";

    const char* value = "";

    size_t klen = strlen(key);

    size_t vlen = strlen(value);



    leveldb_writebatch_put(batch, key, klen, value, vlen);



    // Since we can't access internal state, we rely on ApproximateSize to infer something was added.

    EXPECT_GT(batch->rep.ApproximateSize(), 0U);

}



TEST_F(WriteBatchTest_247, PutLargeValue_247) {

    const char* key = "key1";

    std::string large_value(1024, 'a'); // Large value of size 1024

    size_t klen = strlen(key);

    size_t vlen = large_value.size();



    leveldb_writebatch_put(batch, key, klen, large_value.c_str(), vlen);



    // Since we can't access internal state, we rely on ApproximateSize to infer something was added.

    EXPECT_GT(batch->rep.ApproximateSize(), 0U);

}



TEST_F(WriteBatchTest_247, ClearAfterPut_247) {

    const char* key = "key1";

    const char* value = "value1";

    size_t klen = strlen(key);

    size_t vlen = strlen(value);



    leveldb_writebatch_put(batch, key, klen, value, vlen);

    batch->rep.Clear();



    EXPECT_EQ(batch->rep.ApproximateSize(), 0U);

}
