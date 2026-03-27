#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "graph.h"



using ::testing::_;

using ::testing::Return;



class NodeTest_32 : public ::testing::Test {

protected:

    Node node;

    

    NodeTest_32() : node("test_path", 123) {}

};



TEST_F(NodeTest_32, MarkMissing_SetsExistenceToMissing_32) {

    EXPECT_TRUE(node.exists());

    EXPECT_FALSE(node.status_known());



    node.MarkMissing();



    EXPECT_EQ(node.exists(), false);

    EXPECT_TRUE(node.status_known());

}



TEST_F(NodeTest_32, MarkMissing_WithInitialMtimeNegative_OneSetsMtimeZero_32) {

    node.MarkMissing();

    EXPECT_EQ(node.mtime(), 0);

}



TEST_F(NodeTest_32, MarkMissing_WithInitialMtimePositive_MtimeUnchanged_32) {

    node.UpdatePhonyMtime(123456);

    node.MarkMissing();

    EXPECT_EQ(node.mtime(), 123456);

}



TEST_F(NodeTest_32, Exists_ReturnsFalseAfterMarkingMissing_32) {

    node.MarkMissing();

    EXPECT_FALSE(node.exists());

}



TEST_F(NodeTest_32, StatusKnown_ReturnsTrueAfterMarkingMissing_32) {

    node.MarkMissing();

    EXPECT_TRUE(node.status_known());

}



TEST_F(NodeTest_32, MarkMissing_MultipleTimes_IdempotentBehavior_32) {

    node.MarkMissing();

    TimeStamp firstMtime = node.mtime();



    node.MarkMissing();

    EXPECT_EQ(node.mtime(), firstMtime);

}
