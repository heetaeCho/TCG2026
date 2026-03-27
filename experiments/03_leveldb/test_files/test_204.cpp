#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "leveldb/write_batch.h"

#include "db/write_batch_internal.h"



using namespace leveldb;

using ::testing::_;

using ::testing::InvokeWithoutArgs;



class WriteBatchTest_204 : public ::testing::Test {

protected:

    WriteBatch write_batch;

};



TEST_F(WriteBatchTest_204, PutIncreasesCount_204) {

    int initial_count = WriteBatchInternal::Count(&write_batch);

    Slice key("key");

    Slice value("value");

    write_batch.Put(key, value);

    EXPECT_EQ(WriteBatchInternal::Count(&write_batch), initial_count + 1);

}



TEST_F(WriteBatchTest_204, DeleteIncreasesCount_204) {

    int initial_count = WriteBatchInternal::Count(&write_batch);

    Slice key("key");

    write_batch.Delete(key);

    EXPECT_EQ(WriteBatchInternal::Count(&write_batch), initial_count + 1);

}



TEST_F(WriteBatchTest_204, ClearResetsCount_204) {

    write_batch.Put(Slice("key"), Slice("value"));

    write_batch.Clear();

    EXPECT_EQ(WriteBatchInternal::Count(&write_batch), 0);

}



TEST_F(WriteBatchTest_204, ApproximateSizeNonEmpty_204) {

    write_batch.Put(Slice("key"), Slice("value"));

    EXPECT_GT(write_batch.ApproximateSize(), 0);

}



TEST_F(WriteBatchTest_204, ApproximateSizeEmpty_204) {

    EXPECT_EQ(write_batch.ApproximateSize(), 0);

}



TEST_F(WriteBatchTest_204, AppendIncreasesCount_204) {

    WriteBatch another_batch;

    another_batch.Put(Slice("key"), Slice("value"));

    int initial_count = WriteBatchInternal::Count(&write_batch);

    write_batch.Append(another_batch);

    EXPECT_EQ(WriteBatchInternal::Count(&write_batch), initial_count + 1);

}



TEST_F(WriteBatchTest_204, SetSequenceAndGetSequence_204) {

    SequenceNumber seq = 12345;

    WriteBatchInternal::SetSequence(&write_batch, seq);

    EXPECT_EQ(WriteBatchInternal::Sequence(&write_batch), seq);

}
