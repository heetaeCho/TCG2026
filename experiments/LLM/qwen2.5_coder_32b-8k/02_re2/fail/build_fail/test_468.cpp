#include "gtest/gtest.h"

#include "gmock/gmock.h"

#include "./TestProjects/re2/re2/prefilter.h"



using namespace re2;



// Test fixture for PrefilterTree and related classes

class PrefilterTreeTest_468 : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup code if needed

    }



    void TearDown() override {

        // Teardown code if needed

    }

};



TEST_F(PrefilterTreeTest_468, HashDifferentPrefilterObjects_468) {

    Prefilter* prefilter1 = new Prefilter(Op::kOpLiteral);

    Prefilter* prefilter2 = new Prefilter(Op::kOpLiteral);



    prefilter1->set_unique_id(1);

    prefilter2->set_unique_id(2);



    PrefilterTree::PrefilterHash hash_function;



    EXPECT_NE(hash_function(prefilter1), hash_function(prefilter2));



    delete prefilter1;

    delete prefilter2;

}



TEST_F(PrefilterTreeTest_468, HashSamePrefilterObject_468) {

    Prefilter* prefilter = new Prefilter(Op::kOpLiteral);

    prefilter->set_unique_id(1);



    PrefilterTree::PrefilterHash hash_function;



    EXPECT_EQ(hash_function(prefilter), hash_function(prefilter));



    delete prefilter;

}



TEST_F(PrefilterTreeTest_468, HashNullPtr_ShouldFail_468) {

    Prefilter* prefilter = nullptr;

    PrefilterTree::PrefilterHash hash_function;



    // ABSL_DCHECK should fail here if enabled

    EXPECT_DEATH(hash_function(prefilter), ".*a != NULL.*");

}



TEST_F(PrefilterTreeTest_468, HashSameUniqueIdDifferentObjects_468) {

    Prefilter* prefilter1 = new Prefilter(Op::kOpLiteral);

    Prefilter* prefilter2 = new Prefilter(Op::kOpLiteral);



    prefilter1->set_unique_id(1);

    prefilter2->set_unique_id(1);



    PrefilterTree::PrefilterHash hash_function;



    // Hash might still be different because of other internal states

    EXPECT_NE(hash_function(prefilter1), hash_function(prefilter2));



    delete prefilter1;

    delete prefilter2;

}



TEST_F(PrefilterTreeTest_468, HashDifferentUniqueIdsSameObjects_468) {

    Prefilter* prefilter = new Prefilter(Op::kOpLiteral);



    prefilter->set_unique_id(1);

    size_t hash1 = PrefilterTree::PrefilterHash()(prefilter);



    prefilter->set_unique_id(2);

    size_t hash2 = PrefilterTree::PrefilterHash()(prefilter);



    // Hash might still be different because of other internal states

    EXPECT_NE(hash1, hash2);



    delete prefilter;

}
