#include <gtest/gtest.h>

#include "leveldb/write_batch.h"

#include "leveldb/slice.h"



using namespace leveldb;



class WriteBatchTest_205 : public ::testing::Test {

protected:

    WriteBatch batch;

};



TEST_F(WriteBatchTest_205, PutIncreasesCount_205) {

    size_t initial_count = WriteBatchInternal::Count(&batch);

    Slice key("key");

    Slice value("value");

    batch.Put(key, value);

    EXPECT_EQ(WriteBatchInternal::Count(&batch), initial_count + 1);

}



TEST_F(WriteBatchTest_205, PutWithEmptyKey_205) {

    size_t initial_count = WriteBatchInternal::Count(&batch);

    Slice key("");

    Slice value("value");

    batch.Put(key, value);

    EXPECT_EQ(WriteBatchInternal::Count(&batch), initial_count + 1);

}



TEST_F(WriteBatchTest_205, PutWithEmptyValue_205) {

    size_t initial_count = WriteBatchInternal::Count(&batch);

    Slice key("key");

    Slice value("");

    batch.Put(key, value);

    EXPECT_EQ(WriteBatchInternal::Count(&batch), initial_count + 1);

}



TEST_F(WriteBatchTest_205, PutWithEmptyKeyAndValue_205) {

    size_t initial_count = WriteBatchInternal::Count(&batch);

    Slice key("");

    Slice value("");

    batch.Put(key, value);

    EXPECT_EQ(WriteBatchInternal::Count(&batch), initial_count + 1);

}



TEST_F(WriteBatchTest_205, ClearResetsCount_205) {

    Slice key("key");

    Slice value("value");

    batch.Put(key, value);

    batch.Clear();

    EXPECT_EQ(WriteBatchInternal::Count(&batch), 0);

}



TEST_F(WriteBatchTest_205, ApproximateSizeNonZeroAfterPut_205) {

    size_t initial_size = batch.ApproximateSize();

    Slice key("key");

    Slice value("value");

    batch.Put(key, value);

    EXPECT_GT(batch.ApproximateSize(), initial_size);

}



TEST_F(WriteBatchTest_205, ApproximateSizeZeroAfterClear_205) {

    Slice key("key");

    Slice value("value");

    batch.Put(key, value);

    batch.Clear();

    EXPECT_EQ(batch.ApproximateSize(), 0);

}
