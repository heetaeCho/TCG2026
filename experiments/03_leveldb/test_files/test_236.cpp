#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "leveldb/iterator.h"

#include "db/c.cc"



using namespace leveldb;

using ::testing::_;

using ::testing::InvokeWithoutArgs;



class IteratorMock : public Iterator {

public:

    MOCK_METHOD(void, SeekToFirst, (), (override));

};



struct CInterfaceTest : public ::testing::Test {

protected:

    void SetUp() override {

        mock_iterator = new IteratorMock();

        c_iter.rep = mock_iterator;

    }



    void TearDown() override {

        delete c_iter.rep;

    }



    leveldb_iterator_t c_iter;

    IteratorMock* mock_iterator;

};



TEST_F(CInterfaceTest_SeekToFirst_NegativeCases_236, SeekToFirstCalledOnce_236) {

    EXPECT_CALL(*mock_iterator, SeekToFirst()).Times(1);

    leveldb_iter_seek_to_first(&c_iter);

}



// Assuming there are no boundary conditions or exceptional cases specific to the C interface function provided,

// as the function itself does not return a value and its effects are internal to the iterator.
