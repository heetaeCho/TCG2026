#include <gtest/gtest.h>

#include "leveldb/write_batch.h"

#include "db/c.cc"



class WriteBatchTest_250 : public ::testing::Test {

protected:

    leveldb_writebatch_t* writeBatch1;

    leveldb_writebatch_t* writeBatch2;



    virtual void SetUp() {

        writeBatch1 = new leveldb_writebatch_t();

        writeBatch2 = new leveldb_writebatch_t();

    }



    virtual void TearDown() {

        delete writeBatch1;

        delete writeBatch2;

    }

};



TEST_F(WriteBatchTest_250, AppendIncreasesApproximateSize_250) {

    const std::string key1 = "key1";

    const std::string value1 = "value1";



    leveldb::Slice sliceKey1(key1);

    leveldb::Slice sliceValue1(value1);



    writeBatch1->rep.Put(sliceKey1, sliceValue1);



    size_t initialSize = writeBatch1->rep.ApproximateSize();



    leveldb_writebatch_append(writeBatch2, writeBatch1);



    EXPECT_GT(writeBatch2->rep.ApproximateSize(), initialSize);

}



TEST_F(WriteBatchTest_250, AppendPreservesOriginalBatch_250) {

    const std::string key1 = "key1";

    const std::string value1 = "value1";



    leveldb::Slice sliceKey1(key1);

    leveldb::Slice sliceValue1(value1);



    writeBatch1->rep.Put(sliceKey1, sliceValue1);



    size_t originalSize = writeBatch1->rep.ApproximateSize();



    leveldb_writebatch_append(writeBatch2, writeBatch1);



    EXPECT_EQ(writeBatch1->rep.ApproximateSize(), originalSize);

}



TEST_F(WriteBatchTest_250, AppendWithEmptySourceDoesNothing_250) {

    size_t initialSize = writeBatch1->rep.ApproximateSize();



    leveldb_writebatch_append(writeBatch1, writeBatch2);



    EXPECT_EQ(writeBatch1->rep.ApproximateSize(), initialSize);

}



TEST_F(WriteBatchTest_250, AppendMultipleTimesAccumulatesChanges_250) {

    const std::string key1 = "key1";

    const std::string value1 = "value1";



    leveldb::Slice sliceKey1(key1);

    leveldb::Slice sliceValue1(value1);



    writeBatch1->rep.Put(sliceKey1, sliceValue1);



    size_t initialSize = writeBatch2->rep.ApproximateSize();



    leveldb_writebatch_append(writeBatch2, writeBatch1);

    leveldb_writebatch_append(writeBatch2, writeBatch1);



    EXPECT_GT(writeBatch2->rep.ApproximateSize(), initialSize * 2);

}
