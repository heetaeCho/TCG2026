#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-document.cc"  // Adjust the include path as necessary



using namespace testing;



// Test fixture for _poppler_dest_compare_keys function

class PopplerDestCompareKeysTest_2160 : public ::testing::Test {

protected:

    const gchar* keyA;

    const gchar* keyB;



    void SetUp() override {

        keyA = "destinationA";

        keyB = "destinationB";

    }

};



// Test normal operation where keys are different

TEST_F(PopplerDestCompareKeysTest_2160, DifferentKeys_2160) {

    gint result = _poppler_dest_compare_keys(keyA, keyB, nullptr);

    EXPECT_NE(result, 0);  // Expecting non-zero as keys are different

}



// Test normal operation where keys are the same

TEST_F(PopplerDestCompareKeysTest_2160, SameKeys_2160) {

    gint result = _poppler_dest_compare_keys(keyA, keyA, nullptr);

    EXPECT_EQ(result, 0);  // Expecting zero as keys are the same

}



// Test boundary condition with null keys

TEST_F(PopplerDestCompareKeysTest_2160, NullKeys_2160) {

    gint result = _poppler_dest_compare_keys(nullptr, nullptr, nullptr);

    EXPECT_EQ(result, 0);  // Expecting zero as both keys are null



    result = _poppler_dest_compare_keys(keyA, nullptr, nullptr);

    EXPECT_GT(result, 0);  // Expecting positive value as first key is not null and second is null



    result = _poppler_dest_compare_keys(nullptr, keyB, nullptr);

    EXPECT_LT(result, 0);  // Expecting negative value as first key is null and second is not null

}



// Test boundary condition with empty keys

TEST_F(PopplerDestCompareKeysTest_2160, EmptyKeys_2160) {

    const gchar* emptyKey = "";

    gint result = _poppler_dest_compare_keys(emptyKey, emptyKey, nullptr);

    EXPECT_EQ(result, 0);  // Expecting zero as both keys are empty



    result = _poppler_dest_compare_keys(keyA, emptyKey, nullptr);

    EXPECT_GT(result, 0);  // Expecting positive value as first key is not empty and second is empty



    result = _poppler_dest_compare_keys(emptyKey, keyB, nullptr);

    EXPECT_LT(result, 0);  // Expecting negative value as first key is empty and second is not empty

}
