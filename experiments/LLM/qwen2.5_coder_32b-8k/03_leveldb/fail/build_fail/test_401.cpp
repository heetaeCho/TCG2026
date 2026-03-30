#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "leveldb/iterator.h"



using namespace leveldb;

using ::testing::_;

using ::testing::InvokeWithoutArgs;



class MockCleanupFunction {

public:

    MOCK_METHOD0(Call, void());

};



void CleanupAdapter(void* arg1, void*) {

    static_cast<MockCleanupFunction*>(arg1)->Call();

}



class IteratorTest : public ::testing::Test {

protected:

    Iterator* iterator;



    void SetUp() override {

        iterator = new Iterator();

    }



    void TearDown() override {

        delete iterator;

    }

};



TEST_F(IteratorTest_401, Valid_ReturnsFalseOnConstruction_401) {

    EXPECT_FALSE(iterator->Valid());

}



TEST_F(IteratorTest_401, SeekToFirst_DoesNotCrash_401) {

    iterator->SeekToFirst();

}



TEST_F(IteratorTest_401, SeekToLast_DoesNotCrash_401) {

    iterator->SeekToLast();

}



TEST_F(IteratorTest_401, Seek_DoesNotCrash_401) {

    Slice target("test");

    iterator->Seek(target);

}



TEST_F(IteratorTest_401, Next_DoesNotCrash_401) {

    iterator->Next();

}



TEST_F(IteratorTest_401, Prev_DoesNotCrash_401) {

    iterator->Prev();

}



TEST_F(IteratorTest_401, Key_ReturnsEmptySliceWhenInvalid_401) {

    EXPECT_EQ(iterator->key().size(), 0);

}



TEST_F(IteratorTest_401, Value_ReturnsEmptySliceWhenInvalid_401) {

    EXPECT_EQ(iterator->value().size(), 0);

}



TEST_F(IteratorTest_401, Status_ReturnsOkOnConstruction_401) {

    EXPECT_TRUE(iterator->status().ok());

}



TEST_F(IteratorTest_401, RegisterCleanup_FunctionIsCalledOnDestruction_401) {

    MockCleanupFunction mock_cleanup;

    EXPECT_CALL(mock_cleanup, Call()).Times(1);

    iterator->RegisterCleanup(CleanupAdapter, &mock_cleanup, nullptr);

}
