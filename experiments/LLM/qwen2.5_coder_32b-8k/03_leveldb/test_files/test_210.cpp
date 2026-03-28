#include <gtest/gtest.h>

#include "leveldb/write_batch.h"

#include "db/write_batch_internal.h"



using namespace leveldb;



class WriteBatchTest_210 : public ::testing::Test {

protected:

    WriteBatch batch;

};



TEST_F(WriteBatchTest_210, AppendIncreasesCount_210) {

    WriteBatch src;

    src.Put(Slice("key"), Slice("value"));

    int initial_count = WriteBatchInternal::Count(&batch);

    batch.Append(src);

    EXPECT_EQ(WriteBatchInternal::Count(&batch), initial_count + 1);

}



TEST_F(WriteBatchTest_210, AppendEmptyBatch_210) {

    WriteBatch src;

    int initial_count = WriteBatchInternal::Count(&batch);

    batch.Append(src);

    EXPECT_EQ(WriteBatchInternal::Count(&batch), initial_count);

}



TEST_F(WriteBatchTest_210, PutIncreasesCount_210) {

    int initial_count = WriteBatchInternal::Count(&batch);

    batch.Put(Slice("key"), Slice("value"));

    EXPECT_EQ(WriteBatchInternal::Count(&batch), initial_count + 1);

}



TEST_F(WriteBatchTest_210, DeleteIncreasesCount_210) {

    int initial_count = WriteBatchInternal::Count(&batch);

    batch.Delete(Slice("key"));

    EXPECT_EQ(WriteBatchInternal::Count(&batch), initial_count + 1);

}



TEST_F(WriteBatchTest_210, ClearResetsCount_210) {

    batch.Put(Slice("key"), Slice("value"));

    batch.Clear();

    EXPECT_EQ(WriteBatchInternal::Count(&batch), 0);

}



TEST_F(WriteBatchTest_210, ApproximateSizeNonEmpty_210) {

    batch.Put(Slice("key"), Slice("value"));

    EXPECT_GT(batch.ApproximateSize(), kHeader);

}



TEST_F(WriteBatchTest_210, ApproximateSizeEmpty_210) {

    EXPECT_EQ(batch.ApproximateSize(), kHeader);

}
