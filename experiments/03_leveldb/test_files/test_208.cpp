#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "db/write_batch_internal.h"

#include "db/memtable.h"

#include "leveldb/write_batch.h"

#include "leveldb/status.h"



using namespace leveldb;



class MockMemTable : public MemTable {

public:

    MOCK_METHOD(void, Add, (SequenceNumber seq, ValueType type, const Slice& key, const Slice& value), (override));

    MOCK_METHOD(bool, Get, (const LookupKey& key, std::string* value, Status* s), (override));

    MOCK_METHOD(size_t, ApproximateMemoryUsage, (), (override));

    MOCK_METHOD(Iterator*, NewIterator, (), (override));



    MockMemTable(const InternalKeyComparator& comparator) : MemTable(comparator) {}

};



class WriteBatchTest_208 : public ::testing::Test {

protected:

    WriteBatch batch;

    SequenceNumber seq = 12345;

    Slice key = "test_key";

    Slice value = "test_value";

    InternalKeyComparator comparator;

    MockMemTable mock_memtable;



    WriteBatchTest_208() : mock_memtable(comparator) {

        WriteBatchInternal::SetSequence(&batch, seq);

    }

};



TEST_F(WriteBatchTest_208, InsertInto_PutOperation_208) {

    batch.Put(key, value);



    EXPECT_CALL(mock_memtable, Add(seq, kTypeValue, key, value));



    Status status = WriteBatchInternal::InsertInto(&batch, &mock_memtable);

    EXPECT_TRUE(status.ok());

}



TEST_F(WriteBatchTest_208, InsertInto_DeleteOperation_208) {

    batch.Delete(key);



    EXPECT_CALL(mock_memtable, Add(seq, kTypeDeletion, key, _));



    Status status = WriteBatchInternal::InsertInto(&batch, &mock_memtable);

    EXPECT_TRUE(status.ok());

}



TEST_F(WriteBatchTest_208, InsertInto_EmptyBatch_208) {

    EXPECT_CALL(mock_memtable, Add(_, _, _, _)).Times(0);



    Status status = WriteBatchInternal::InsertInto(&batch, &mock_memtable);

    EXPECT_TRUE(status.ok());

}



TEST_F(WriteBatchTest_208, InsertInto_MultipleOperations_208) {

    batch.Put(key, value);

    batch.Delete(key);

    batch.Put(Slice("another_key"), Slice("another_value"));



    EXPECT_CALL(mock_memtable, Add(seq, kTypeValue, key, value));

    EXPECT_CALL(mock_memtable, Add(seq + 1, kTypeDeletion, key, _));

    EXPECT_CALL(mock_memtable, Add(seq + 2, kTypeValue, Slice("another_key"), Slice("another_value")));



    Status status = WriteBatchInternal::InsertInto(&batch, &mock_memtable);

    EXPECT_TRUE(status.ok());

}



TEST_F(WriteBatchTest_208, InsertInto_BoundarySequenceNumber_208) {

    WriteBatchInternal::SetSequence(&batch, 0);



    batch.Put(key, value);



    EXPECT_CALL(mock_memtable, Add(0, kTypeValue, key, value));



    Status status = WriteBatchInternal::InsertInto(&batch, &mock_memtable);

    EXPECT_TRUE(status.ok());

}
