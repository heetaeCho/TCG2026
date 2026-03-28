#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <yaml-cpp/node/detail/impl.h>

#include <vector>



using namespace YAML::detail;



class RemoveFunctionTest_666 : public ::testing::Test {

protected:

    std::vector<node*> sequence;

    std::size_t seqSize = 0;

};



TEST_F(RemoveFunctionTest_666, RemoveValidIndex_666) {

    node* dummyNode = new node();

    sequence.push_back(dummyNode);

    seqSize = sequence.size();



    EXPECT_TRUE(remove(sequence, 0, seqSize));

    EXPECT_EQ(seqSize, 0);

    EXPECT_TRUE(sequence.empty());

}



TEST_F(RemoveFunctionTest_666, RemoveInvalidIndex_666) {

    node* dummyNode = new node();

    sequence.push_back(dummyNode);

    seqSize = sequence.size();



    EXPECT_FALSE(remove(sequence, 1, seqSize));

    EXPECT_EQ(seqSize, 1);

    EXPECT_EQ(sequence.size(), 1);



    delete sequence[0];

}



TEST_F(RemoveFunctionTest_666, RemoveNegativeIndex_666) {

    node* dummyNode = new node();

    sequence.push_back(dummyNode);

    seqSize = sequence.size();



    EXPECT_FALSE(remove(sequence, -1, seqSize));

    EXPECT_EQ(seqSize, 1);

    EXPECT_EQ(sequence.size(), 1);



    delete sequence[0];

}



TEST_F(RemoveFunctionTest_666, RemoveFromEmptySequence_666) {

    seqSize = sequence.size();



    EXPECT_FALSE(remove(sequence, 0, seqSize));

    EXPECT_EQ(seqSize, 0);

    EXPECT_TRUE(sequence.empty());

}
