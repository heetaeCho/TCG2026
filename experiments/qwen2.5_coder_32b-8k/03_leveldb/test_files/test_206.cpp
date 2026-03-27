#include <gtest/gtest.h>

#include "leveldb/write_batch.h"

#include "leveldb/slice.h"



using namespace leveldb;



class WriteBatchTest_206 : public ::testing::Test {

protected:

    WriteBatch batch;

};



TEST_F(WriteBatchTest_206, DeleteIncreasesCount_206) {

    Slice key("test_key");

    int initial_count = WriteBatchInternal::Count(&batch);

    batch.Delete(key);

    int final_count = WriteBatchInternal::Count(&batch);

    EXPECT_EQ(final_count, initial_count + 1);

}



TEST_F(WriteBatchTest_206, DeleteWithEmptyKey_206) {

    Slice empty_key("");

    int initial_count = WriteBatchInternal::Count(&batch);

    batch.Delete(empty_key);

    int final_count = WriteBatchInternal::Count(&batch);

    EXPECT_EQ(final_count, initial_count + 1);

}



TEST_F(WriteBatchTest_206, DeleteWithLongKey_206) {

    std::string long_key(1000, 'a');

    Slice key(long_key);

    int initial_count = WriteBatchInternal::Count(&batch);

    batch.Delete(key);

    int final_count = WriteBatchInternal::Count(&batch);

    EXPECT_EQ(final_count, initial_count + 1);

}



TEST_F(WriteBatchTest_206, ClearResetsCount_206) {

    Slice key("test_key");

    batch.Delete(key);

    batch.Clear();

    int count = WriteBatchInternal::Count(&batch);

    EXPECT_EQ(count, 0);

}
