#include <gtest/gtest.h>

#include "leveldb/iterator.h"

#include "leveldb/status.h"



using namespace leveldb;



class IteratorTest_404 : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup code if needed

    }



    void TearDown() override {

        // Teardown code if needed

    }

};



TEST_F(IteratorTest_404, NewErrorIterator_ReturnsNonOkStatus_404) {

    Status error_status = NotFound("Test not found");

    Iterator* it = NewErrorIterator(error_status);

    EXPECT_FALSE(it->status().ok());

    delete it;

}



TEST_F(IteratorTest_404, NewErrorIterator_StatusMatchesInput_404) {

    Status error_status = Corruption("Test corruption");

    Iterator* it = NewErrorIterator(error_status);

    EXPECT_EQ(it->status().ToString(), error_status.ToString());

    delete it;

}



TEST_F(IteratorTest_404, NewErrorIterator_IsCorruption_ReturnsTrueForCorruption_404) {

    Status error_status = Corruption("Test corruption");

    Iterator* it = NewErrorIterator(error_status);

    EXPECT_TRUE(it->status().IsCorruption());

    delete it;

}



TEST_F(IteratorTest_404, NewErrorIterator_IsNotFound_ReturnsTrueForNotFound_404) {

    Status error_status = NotFound("Test not found");

    Iterator* it = NewErrorIterator(error_status);

    EXPECT_TRUE(it->status().IsNotFound());

    delete it;

}



TEST_F(IteratorTest_404, NewErrorIterator_IsIOError_ReturnsFalseForOtherErrors_404) {

    Status error_status = Corruption("Test corruption");

    Iterator* it = NewErrorIterator(error_status);

    EXPECT_FALSE(it->status().IsIOError());

    delete it;

}



TEST_F(IteratorTest_404, NewErrorIterator_IsNotSupportedError_ReturnsFalseForOtherErrors_404) {

    Status error_status = Corruption("Test corruption");

    Iterator* it = NewErrorIterator(error_status);

    EXPECT_FALSE(it->status().IsNotSupportedError());

    delete it;

}



TEST_F(IteratorTest_404, NewErrorIterator_IsInvalidArgument_ReturnsFalseForOtherErrors_404) {

    Status error_status = Corruption("Test corruption");

    Iterator* it = NewErrorIterator(error_status);

    EXPECT_FALSE(it->status().IsInvalidArgument());

    delete it;

}
