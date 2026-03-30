#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "leveldb/slice.h"

#include "leveldb/write_batch.h"



using namespace leveldb;

using ::testing::_;

using ::testing::Invoke;

using ::testing::InSequence;



struct MockHandler {

    MOCK_METHOD5(Put, void(void* state, const char* k, size_t klen, const char* v, size_t vlen));

    MOCK_METHOD3(Deleted, void(void* state, const char* k, size_t klen));

};



TEST_F(WriteBatchTest_249, PutOperationInvokesPutCallback_249) {

    leveldb_writebatch_t batch;

    batch.rep.Put(Slice("key1"), Slice("value1"));

    

    MockHandler mock_handler;

    EXPECT_CALL(mock_handler, Put(_, "key1", 4, "value1", 6));

    

    void* state = nullptr;

    leveldb_writebatch_iterate(&batch, state, 

        [](void* s, const char* k, size_t klen, const char* v, size_t vlen) {

            static_cast<MockHandler*>(s)->Put(s, k, klen, v, vlen);

        }, 

        [](void* s, const char* k, size_t klen) { /* No-op */ });

}



TEST_F(WriteBatchTest_249, DeleteOperationInvokesDeletedCallback_249) {

    leveldb_writebatch_t batch;

    batch.rep.Delete(Slice("key1"));

    

    MockHandler mock_handler;

    EXPECT_CALL(mock_handler, Deleted(_, "key1", 4));

    

    void* state = nullptr;

    leveldb_writebatch_iterate(&batch, state, 

        [](void*, const char*, size_t, const char*, size_t) { /* No-op */ }, 

        [](void* s, const char* k, size_t klen) {

            static_cast<MockHandler*>(s)->Deleted(s, k, klen);

        });

}



TEST_F(WriteBatchTest_249, MultipleOperationsInvokeCallbacksInOrder_249) {

    leveldb_writebatch_t batch;

    batch.rep.Put(Slice("key1"), Slice("value1"));

    batch.rep.Delete(Slice("key2"));

    batch.rep.Put(Slice("key3"), Slice("value3"));

    

    MockHandler mock_handler;

    InSequence seq;

    EXPECT_CALL(mock_handler, Put(_, "key1", 4, "value1", 6));

    EXPECT_CALL(mock_handler, Deleted(_, "key2", 4));

    EXPECT_CALL(mock_handler, Put(_, "key3", 4, "value3", 6));



    void* state = nullptr;

    leveldb_writebatch_iterate(&batch, state, 

        [](void* s, const char* k, size_t klen, const char* v, size_t vlen) {

            static_cast<MockHandler*>(s)->Put(s, k, klen, v, vlen);

        }, 

        [](void* s, const char* k, size_t klen) {

            static_cast<MockHandler*>(s)->Deleted(s, k, klen);

        });

}



TEST_F(WriteBatchTest_249, EmptyWriteBatchDoesNotInvokeCallbacks_249) {

    leveldb_writebatch_t batch;

    

    MockHandler mock_handler;

    EXPECT_CALL(mock_handler, Put(_, _, _, _, _)).Times(0);

    EXPECT_CALL(mock_handler, Deleted(_, _, _)).Times(0);



    void* state = nullptr;

    leveldb_writebatch_iterate(&batch, state, 

        [](void* s, const char* k, size_t klen, const char* v, size_t vlen) {

            static_cast<MockHandler*>(s)->Put(s, k, klen, v, vlen);

        }, 

        [](void* s, const char* k, size_t klen) {

            static_cast<MockHandler*>(s)->Deleted(s, k, klen);

        });

}
