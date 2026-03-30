#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/poppler/qt5/src/poppler-optcontent-private.h"

#include "poppler-optcontent.h"



using namespace Poppler;



class OptContentModelPrivateTest : public ::testing::Test {

protected:

    OptContentModelPrivateTest() 

        : model(nullptr), sut(model, nullptr) {}



    void SetUp() override {

        model = new OptContentModel();

        sut.q = model;

        sut.m_rootNode = nullptr;

    }



    void TearDown() override {

        delete sut.m_rootNode;

        delete model;

    }



    OptContentModel* model;

    OptContentModelPrivate sut;

};



TEST_F(OptContentModelPrivateTest_SetRootNode_1275, SetValidRootNode_1275) {

    OptContentItem* rootNode = new OptContentItem();

    sut.setRootNode(rootNode);

    EXPECT_EQ(sut.m_rootNode, rootNode);

}



TEST_F(OptContentModelPrivateTest_SetRootNode_1275, SetNullRootNode_1275) {

    sut.setRootNode(nullptr);

    EXPECT_EQ(sut.m_rootNode, nullptr);

}



TEST_F(OptContentModelPrivateTest_SetRootNode_1275, ReplaceExistingRootNode_1275) {

    OptContentItem* oldRootNode = new OptContentItem();

    sut.m_rootNode = oldRootNode;

    OptContentItem* newRootNode = new OptContentItem();

    sut.setRootNode(newRootNode);

    EXPECT_EQ(sut.m_rootNode, newRootNode);

    EXPECT_NE(oldRootNode, sut.m_rootNode);

}



TEST_F(OptContentModelPrivateTest_SetRootNode_1275, DeleteOldRootNodeOnSet_1275) {

    OptContentItem* oldRootNode = new OptContentItem();

    sut.m_rootNode = oldRootNode;

    EXPECT_CALL(*oldRootNode, ~OptContentItem()).Times(1);

    sut.setRootNode(nullptr);

}



TEST_F(OptContentModelPrivateTest_SetRootNode_1275, BeginResetModelCalledOnSet_1275) {

    OptContentItem* rootNode = new OptContentItem();

    EXPECT_CALL(*model, beginResetModel()).Times(1);

    sut.setRootNode(rootNode);

}



TEST_F(OptContentModelPrivateTest_SetRootNode_1275, EndResetModelCalledOnSet_1275) {

    OptContentItem* rootNode = new OptContentItem();

    EXPECT_CALL(*model, endResetModel()).Times(1);

    sut.setRootNode(rootNode);

}
