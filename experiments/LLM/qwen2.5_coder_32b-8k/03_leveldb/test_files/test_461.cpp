#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "util/bloom.cc"



namespace leveldb {



class BloomFilterPolicyTest_461 : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup can be used to initialize common resources if needed.

    }



    void TearDown() override {

        // Cleanup can be handled here if necessary.

    }

};



TEST_F(BloomFilterPolicyTest_461, NewBloomFilterPolicy_ReturnsNonNullPointer_461) {

    const FilterPolicy* filter_policy = NewBloomFilterPolicy(10);

    EXPECT_NE(filter_policy, nullptr);

}



TEST_F(BloomFilterPolicyTest_461, NewBloomFilterPolicy_ZeroBitsPerKey_ReturnsNonNullPointer_461) {

    const FilterPolicy* filter_policy = NewBloomFilterPolicy(0);

    EXPECT_NE(filter_policy, nullptr);

}



TEST_F(BloomFilterPolicyTest_461, NewBloomFilterPolicy_NegativeBitsPerKey_ReturnsNonNullPointer_461) {

    const FilterPolicy* filter_policy = NewBloomFilterPolicy(-5);

    EXPECT_NE(filter_policy, nullptr);

}



// Assuming no exceptions are thrown for invalid inputs and the implementation is robust.

// If exceptions were possible, they would be tested here.



}  // namespace leveldb
