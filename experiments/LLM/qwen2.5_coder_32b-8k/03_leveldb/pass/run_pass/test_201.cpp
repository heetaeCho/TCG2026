#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "leveldb/write_batch.h"

#include "db/write_batch_internal.h"



using namespace leveldb;

using ::testing::_;

using ::testing::InvokeWithoutArgs;



class WriteBatchTest_201 : public ::testing::Test {

protected:

    WriteBatch write_batch;

};



TEST_F(WriteBatchTest_201, InitialCountIsZero_201) {

    EXPECT_EQ(WriteBatchInternal::Count(&write_batch), 0);

}



TEST_F(WriteBatchTest_201, PutIncreasesCount_201) {

    Slice key("key");

    Slice value("value");

    write_batch.Put(key, value);

    EXPECT_EQ(WriteBatchInternal::Count(&write_batch), 1);

}



TEST_F(WriteBatchTest_201, DeleteIncreasesCount_201) {

    Slice key("key");

    write_batch.Delete(key);

    EXPECT_EQ(WriteBatchInternal::Count(&write_batch), 1);

}



TEST_F(WriteBatchTest_201, ClearResetsCount_201) {

    Slice key("key");

    Slice value("value");

    write_batch.Put(key, value);

    write_batch.Clear();

    EXPECT_EQ(WriteBatchInternal::Count(&write_batch), 0);

}



TEST_F(WriteBatchTest_201, AppendIncreasesCount_201) {

    WriteBatch source;

    Slice key("key");

    Slice value("value");

    source.Put(key, value);

    write_batch.Append(source);

    EXPECT_EQ(WriteBatchInternal::Count(&write_batch), 1);

}



TEST_F(WriteBatchTest_201, ApproximateSizeNonZeroAfterPut_201) {

    Slice key("key");

    Slice value("value");

    write_batch.Put(key, value);

    EXPECT_GT(write_batch.ApproximateSize(), 0);

}



TEST_F(WriteBatchTest_201, ApproximateSizeNonZeroAfterDelete_201) {

    Slice key("key");

    write_batch.Delete(key);

    EXPECT_GT(write_batch.ApproximateSize(), 0);

}



TEST_F(WriteBatchTest_201, ApproximateSizeZeroInitially_201) {

    EXPECT_EQ(write_batch.ApproximateSize(), 0);

}
