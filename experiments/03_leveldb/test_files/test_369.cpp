#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "leveldb/db.h"

#include "db/db_impl.h"

#include "leveldb/iterator.h"

#include "leveldb/comparator.h"



using namespace leveldb;

using testing::_;

using testing::Return;



class DBIterTest_369 : public ::testing::Test {

protected:

    void SetUp() override {

        db = new MockDBImpl();

        comparator = new ComparatorMock();

        internal_iter = new IteratorMock();

    }



    void TearDown() override {

        delete db;

        delete comparator;

        delete internal_iter;

    }



    MockDBImpl* db;

    ComparatorMock* comparator;

    IteratorMock* internal_iter;



    class MockDBImpl : public DBImpl {

    public:

        MOCK_METHOD(Iterator*, NewInternalIterator, (const ReadOptions &, SequenceNumber *, uint32_t *), override);

    };



    class ComparatorMock : public Comparator {

    public:

        MOCK_METHOD(const int, Compare, (const Slice &, const Slice &), override);

        MOCK_METHOD(const char *, Name, (), override);

        MOCK_METHOD(void, FindShortestSeparator, (std::string *, const Slice &), override);

        MOCK_METHOD(void, FindShortSuccessor, (std::string *), override);

    };



    class IteratorMock : public Iterator {

    public:

        MOCK_METHOD(bool, Valid, (), override);

        MOCK_METHOD(void, SeekToFirst, (), override);

        MOCK_METHOD(void, SeekToLast, (), override);

        MOCK_METHOD(void, Seek, (const Slice &), override);

        MOCK_METHOD(void, Next, (), override);

        MOCK_METHOD(void, Prev, (), override);

        MOCK_METHOD(Slice, key, (), const override);

        MOCK_METHOD(Slice, value, (), const override);

        MOCK_METHOD(Status, status, (), const override);

    };

};



TEST_F(DBIterTest_369, NewDBIterator_ReturnsValidIterator_369) {

    SequenceNumber sequence = 0;

    uint32_t seed = 0;



    EXPECT_CALL(*db, NewInternalIterator(_, _, _)).WillOnce(Return(internal_iter));

    Iterator* iter = NewDBIterator(db, comparator, internal_iter, sequence, seed);



    EXPECT_NE(iter, nullptr);

    delete iter;

}



TEST_F(DBIterTest_369, SeekToFirst_DelegatesToInternalIterator_369) {

    SequenceNumber sequence = 0;

    uint32_t seed = 0;



    EXPECT_CALL(*db, NewInternalIterator(_, _, _)).WillOnce(Return(internal_iter));

    Iterator* iter = NewDBIterator(db, comparator, internal_iter, sequence, seed);



    EXPECT_CALL(*internal_iter, SeekToFirst());

    iter->SeekToFirst();



    delete iter;

}



TEST_F(DBIterTest_369, Seek_DelegatesToInternalIterator_369) {

    SequenceNumber sequence = 0;

    uint32_t seed = 0;

    Slice target("target");



    EXPECT_CALL(*db, NewInternalIterator(_, _, _)).WillOnce(Return(internal_iter));

    Iterator* iter = NewDBIterator(db, comparator, internal_iter, sequence, seed);



    EXPECT_CALL(*internal_iter, Seek(target));

    iter->Seek(target);



    delete iter;

}



TEST_F(DBIterTest_369, Valid_DelegatesToInternalIterator_369) {

    SequenceNumber sequence = 0;

    uint32_t seed = 0;



    EXPECT_CALL(*db, NewInternalIterator(_, _, _)).WillOnce(Return(internal_iter));

    Iterator* iter = NewDBIterator(db, comparator, internal_iter, sequence, seed);



    EXPECT_CALL(*internal_iter, Valid()).WillOnce(Return(true));

    bool result = iter->Valid();



    EXPECT_TRUE(result);

    delete iter;

}



TEST_F(DBIterTest_369, Status_DelegatesToInternalIterator_369) {

    SequenceNumber sequence = 0;

    uint32_t seed = 0;



    EXPECT_CALL(*db, NewInternalIterator(_, _, _)).WillOnce(Return(internal_iter));

    Iterator* iter = NewDBIterator(db, comparator, internal_iter, sequence, seed);



    Status expected_status;

    EXPECT_CALL(*internal_iter, status()).WillOnce(Return(expected_status));

    Status result = iter->status();



    EXPECT_EQ(result, expected_status);

    delete iter;

}



TEST_F(DBIterTest_369, Destructor_CleansUp_369) {

    SequenceNumber sequence = 0;

    uint32_t seed = 0;



    EXPECT_CALL(*db, NewInternalIterator(_, _, _)).WillOnce(Return(internal_iter));

    Iterator* iter = NewDBIterator(db, comparator, internal_iter, sequence, seed);



    delete iter;

}
