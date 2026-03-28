#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "leveldb/write_batch.h"

#include "db/write_batch_internal.h"



using namespace leveldb;

using ::testing::Return;



class WriteBatchTest_196 : public ::testing::Test {

protected:

    WriteBatch batch;

};



TEST_F(WriteBatchTest_196, PutIncreasesCount_196) {

    size_t initial_count = WriteBatchInternal::Count(&batch);

    batch.Put(Slice("key"), Slice("value"));

    EXPECT_EQ(WriteBatchInternal::Count(&batch), initial_count + 1);

}



TEST_F(WriteBatchTest_196, DeleteIncreasesCount_196) {

    size_t initial_count = WriteBatchInternal::Count(&batch);

    batch.Delete(Slice("key"));

    EXPECT_EQ(WriteBatchInternal::Count(&batch), initial_count + 1);

}



TEST_F(WriteBatchTest_196, ClearResetsCount_196) {

    batch.Put(Slice("key"), Slice("value"));

    batch.Clear();

    EXPECT_EQ(WriteBatchInternal::Count(&batch), 0);

}



TEST_F(WriteBatchTest_196, ApproximateSizeNonZeroAfterPut_196) {

    batch.Put(Slice("key"), Slice("value"));

    EXPECT_GT(batch.ApproximateSize(), 0u);

}



TEST_F(WriteBatchTest_196, AppendIncreasesCount_196) {

    WriteBatch another_batch;

    another_batch.Put(Slice("key"), Slice("value"));

    size_t initial_count = WriteBatchInternal::Count(&batch);

    batch.Append(another_batch);

    EXPECT_EQ(WriteBatchInternal::Count(&batch), initial_count + 1);

}



TEST_F(WriteBatchTest_196, ByteSizeMatchesApproximateSize_196) {

    batch.Put(Slice("key"), Slice("value"));

    EXPECT_EQ(WriteBatchInternal::ByteSize(&batch), batch.ApproximateSize());

}



TEST_F(WriteBatchTest_196, ClearResetsByteSize_196) {

    batch.Put(Slice("key"), Slice("value"));

    batch.Clear();

    EXPECT_EQ(WriteBatchInternal::ByteSize(&batch), 0u);

}
