#include <gtest/gtest.h>

#include "util/comparator.h"

#include "util/no_destructor.h"



namespace leveldb {



class ComparatorTest_426 : public ::testing::Test {

protected:

    const Comparator* comparator_;

    

    void SetUp() override {

        comparator_ = BytewiseComparator();

    }

};



TEST_F(ComparatorTest_426, ReturnSameInstanceOnMultipleCalls_426) {

    const Comparator* first_call = BytewiseComparator();

    const Comparator* second_call = BytewiseComparator();

    EXPECT_EQ(first_call, second_call);

}



TEST_F(ComparatorTest_426, NonNullPointerReturned_426) {

    EXPECT_NE(comparator_, nullptr);

}



// Since the interface does not provide more functions to test,

// we cannot write additional tests for normal operation, boundary conditions, or error cases.



} // namespace leveldb
