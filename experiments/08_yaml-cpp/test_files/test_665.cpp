#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <yaml-cpp/node/detail/impl.h>

#include <vector>



using namespace YAML::detail;



TEST_F(RemoveTest_665, RemoveFromValidIndex_665) {

    std::vector<node*> sequence = {new node(), new node(), new node()};

    std::size_t seqSize = sequence.size();

    

    EXPECT_TRUE(remove(sequence, 1, seqSize));

    EXPECT_EQ(seqSize, 2);

    EXPECT_EQ(sequence.size(), 2);

}



TEST_F(RemoveTest_665, RemoveFromFirstIndex_665) {

    std::vector<node*> sequence = {new node(), new node(), new node()};

    std::size_t seqSize = sequence.size();

    

    EXPECT_TRUE(remove(sequence, 0, seqSize));

    EXPECT_EQ(seqSize, 2);

    EXPECT_EQ(sequence.size(), 2);

}



TEST_F(RemoveTest_665, RemoveFromLastIndex_665) {

    std::vector<node*> sequence = {new node(), new node(), new node()};

    std::size_t seqSize = sequence.size();

    

    EXPECT_TRUE(remove(sequence, 2, seqSize));

    EXPECT_EQ(seqSize, 2);

    EXPECT_EQ(sequence.size(), 2);

}



TEST_F(RemoveTest_665, RemoveFromInvalidIndex_665) {

    std::vector<node*> sequence = {new node(), new node(), new node()};

    std::size_t seqSize = sequence.size();

    

    EXPECT_FALSE(remove(sequence, 3, seqSize));

    EXPECT_EQ(seqSize, 3);

    EXPECT_EQ(sequence.size(), 3);

}



TEST_F(RemoveTest_665, RemoveFromEmptySequence_665) {

    std::vector<node*> sequence;

    std::size_t seqSize = sequence.size();

    

    EXPECT_FALSE(remove(sequence, 0, seqSize));

    EXPECT_EQ(seqSize, 0);

    EXPECT_EQ(sequence.size(), 0);

}



TEST_F(RemoveTest_665, RemoveWhenSeqSizeLessThanKey_665) {

    std::vector<node*> sequence = {new node(), new node(), new node()};

    std::size_t seqSize = 1;

    

    EXPECT_TRUE(remove(sequence, 0, seqSize));

    EXPECT_EQ(seqSize, 0);

    EXPECT_EQ(sequence.size(), 2);

}
