#include <gtest/gtest.h>

#include "XMPIterator.hpp"



class WXMPIteratorTest_1909 : public ::testing::Test {

protected:

    XMPIterator* iter;

    WXMP_Result wResult;



    void SetUp() override {

        iter = new XMPIterator("http://example.com/schema", "property", 0);

    }



    void TearDown() override {

        delete iter;

    }

};



TEST_F(WXMPIteratorTest_1909, IncrementRefCountIncreasesCount_1909) {

    int initialRefs = iter->clientRefs; // Assuming we can access clientRefs for testing purposes.

    WXMPIterator_IncrementRefCount_1(iter);

    EXPECT_EQ(iter->clientRefs, initialRefs + 1);

}



TEST_F(WXMPIteratorTest_1909, IncrementRefCountTwiceIncreasesCountByTwo_1909) {

    int initialRefs = iter->clientRefs; // Assuming we can access clientRefs for testing purposes.

    WXMPIterator_IncrementRefCount_1(iter);

    WXMPIterator_IncrementRefCount_1(iter);

    EXPECT_EQ(iter->clientRefs, initialRefs + 2);

}



TEST_F(WXMPIteratorTest_1909, IncrementRefCountDoesNotThrowException_1909) {

    EXPECT_NO_THROW(WXMPIterator_IncrementRefCount_1(iter));

}
