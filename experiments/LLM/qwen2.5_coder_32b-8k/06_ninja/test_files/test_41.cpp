#include <gtest/gtest.h>

#include "graph.h"



class NodeTest_41 : public ::testing::Test {

protected:

    Node* node;



    void SetUp() override {

        node = new Node("test_path", 0);

    }



    void TearDown() override {

        delete node;

    }

};



TEST_F(NodeTest_41, MarkDirty_SetsDirtyFlagToTrue_41) {

    node->MarkDirty();

    EXPECT_TRUE(node->dirty());

}



TEST_F(NodeTest_41, DefaultDirty_IsFalse_41) {

    EXPECT_FALSE(node->dirty());

}



TEST_F(NodeTest_41, SetDirty_ChangesDirtyFlag_41) {

    node->set_dirty(true);

    EXPECT_TRUE(node->dirty());



    node->set_dirty(false);

    EXPECT_FALSE(node->dirty());

}



TEST_F(NodeTest_41, DefaultExistenceStatus_IsUnknown_41) {

    EXPECT_EQ(ExistenceStatusUnknown, node->exists());

}



TEST_F(NodeTest_41, DefaultStatusKnown_IsFalse_41) {

    EXPECT_FALSE(node->status_known());

}



TEST_F(NodeTest_41, Path_ReturnsCorrectPath_41) {

    EXPECT_EQ("test_path", node->path());

}



TEST_F(NodeTest_41, SlashBits_ReturnsCorrectSlashBits_41) {

    EXPECT_EQ(0, node->slash_bits());

}



TEST_F(NodeTest_41, DefaultMtime_IsMinusOne_41) {

    EXPECT_EQ(-1, node->mtime());

}



TEST_F(NodeTest_41, DefaultDyndepPending_IsFalse_41) {

    EXPECT_FALSE(node->dyndep_pending());

}



TEST_F(NodeTest_41, SetDyndepPending_ChangesDyndepFlag_41) {

    node->set_dyndep_pending(true);

    EXPECT_TRUE(node->dyndep_pending());



    node->set_dyndep_pending(false);

    EXPECT_FALSE(node->dyndep_pending());

}



TEST_F(NodeTest_41, DefaultInEdge_IsNullptr_41) {

    EXPECT_EQ(nullptr, node->in_edge());

}



TEST_F(NodeTest_41, SetInEdge_ChangesInEdge_41) {

    Edge* edge = new Edge();

    node->set_in_edge(edge);

    EXPECT_EQ(edge, node->in_edge());



    delete edge;

}



TEST_F(NodeTest_41, DefaultGeneratedByDepLoader_IsTrue_41) {

    EXPECT_TRUE(node->generated_by_dep_loader());

}



TEST_F(NodeTest_41, SetGeneratedByDepLoader_ChangesFlag_41) {

    node->set_generated_by_dep_loader(false);

    EXPECT_FALSE(node->generated_by_dep_loader());



    node->set_generated_by_dep_loader(true);

    EXPECT_TRUE(node->generated_by_dep_loader());

}



TEST_F(NodeTest_41, DefaultId_IsMinusOne_41) {

    EXPECT_EQ(-1, node->id());

}



TEST_F(NodeTest_41, SetId_ChangesId_41) {

    node->set_id(5);

    EXPECT_EQ(5, node->id());



    node->set_id(0);

    EXPECT_EQ(0, node->id());

}



TEST_F(NodeTest_41, DefaultOutEdges_IsEmpty_41) {

    EXPECT_TRUE(node->out_edges().empty());

}



TEST_F(NodeTest_41, AddOutEdge_AddsEdgeToOutEdges_41) {

    Edge* edge = new Edge();

    node->AddOutEdge(edge);

    EXPECT_EQ(1, node->out_edges().size());

    EXPECT_EQ(edge, node->out_edges()[0]);



    delete edge;

}



TEST_F(NodeTest_41, DefaultValidationOutEdges_IsEmpty_41) {

    EXPECT_TRUE(node->validation_out_edges().empty());

}



TEST_F(NodeTest_41, AddValidationOutEdge_AddsEdgeToValidationOutEdges_41) {

    Edge* edge = new Edge();

    node->AddValidationOutEdge(edge);

    EXPECT_EQ(1, node->validation_out_edges().size());

    EXPECT_EQ(edge, node->validation_out_edges()[0]);



    delete edge;

}
