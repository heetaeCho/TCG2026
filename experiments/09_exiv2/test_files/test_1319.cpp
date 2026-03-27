#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/exiv2/src/tags_int.hpp"



using namespace Exiv2::Internal;



class TagVocabularyTest_1319 : public ::testing::Test {

protected:

    TagVocabulary vocab;

    

    void SetUp() override {

        vocab.voc_ = "test_vocabulary";

    }

};



TEST_F(TagVocabularyTest_1319, OperatorEqual_MatchingKey_1319) {

    EXPECT_TRUE(vocab == "sample_test_vocabulary");

}



TEST_F(TagVocabularyTest_1319, OperatorEqual_NonMatchingKey_1319) {

    EXPECT_FALSE(vocab == "non_matching_key");

}



TEST_F(TagVocabularyTest_1319, OperatorEqual_EmptyKey_1319) {

    EXPECT_FALSE(vocab == "");

}



TEST_F(TagVocabularyTest_1319, OperatorEqual_PartialMatch_1319) {

    EXPECT_TRUE(vocab == "vocabulary");

}



TEST_F(TagVocabularyTest_1319, OperatorEqual_SameAsVoc_1319) {

    EXPECT_TRUE(vocab == "test_vocabulary");

}
