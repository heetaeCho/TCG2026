#include <gtest/gtest.h>

#include "poppler-optcontent-private.h"

#include <QModelIndex>



using namespace Poppler;



class OptContentModelPrivateTest : public ::testing::Test {

protected:

    OptContentModelPrivate *m_optContentModelPrivate;

    OptContentItem *m_rootNode;

    OptContentItem *m_childNode1;

    OptContentItem *m_childNode2;



    void SetUp() override {

        m_optContentModelPrivate = new OptContentModelPrivate(nullptr, nullptr);

        m_rootNode = new OptContentItem();

        m_childNode1 = new OptContentItem();

        m_childNode2 = new OptContentItem();



        m_rootNode->addChild(m_childNode1);

        m_rootNode->addChild(m_childNode2);



        m_optContentModelPrivate->setRootNode(m_rootNode);

    }



    void TearDown() override {

        delete m_optContentModelPrivate;

        delete m_rootNode;

        delete m_childNode1;

        delete m_childNode2;

    }

};



TEST_F(OptContentModelPrivateTest_1276, IndexFromItem_NullNode_ReturnsInvalidIndex_1276) {

    QModelIndex index = m_optContentModelPrivate->indexFromItem(nullptr, 0);

    EXPECT_FALSE(index.isValid());

}



TEST_F(OptContentModelPrivateTest_1276, IndexFromItem_RootNode_ReturnsInvalidIndex_1276) {

    QModelIndex index = m_optContentModelPrivate->indexFromItem(m_rootNode, 0);

    EXPECT_FALSE(index.isValid());

}



TEST_F(OptContentModelPrivateTest_1276, IndexFromItem_ValidChildNode_ColumnZero_ReturnsValidIndex_1276) {

    QModelIndex index = m_optContentModelPrivate->indexFromItem(m_childNode1, 0);

    EXPECT_TRUE(index.isValid());

    EXPECT_EQ(index.row(), 0);

    EXPECT_EQ(index.column(), 0);

}



TEST_F(OptContentModelPrivateTest_1276, IndexFromItem_ValidChildNode_ColumnOne_ReturnsValidIndex_1276) {

    QModelIndex index = m_optContentModelPrivate->indexFromItem(m_childNode1, 1);

    EXPECT_TRUE(index.isValid());

    EXPECT_EQ(index.row(), 0);

    EXPECT_EQ(index.column(), 1);

}



TEST_F(OptContentModelPrivateTest_1276, IndexFromItem_SecondChildNode_ReturnsCorrectRow_1276) {

    QModelIndex index = m_optContentModelPrivate->indexFromItem(m_childNode2, 0);

    EXPECT_TRUE(index.isValid());

    EXPECT_EQ(index.row(), 1);

    EXPECT_EQ(index.column(), 0);

}



TEST_F(OptContentModelPrivateTest_1276, IndexFromItem_UnparentedNode_ReturnsInvalidIndex_1276) {

    OptContentItem *unparentedNode = new OptContentItem();

    QModelIndex index = m_optContentModelPrivate->indexFromItem(unparentedNode, 0);

    EXPECT_FALSE(index.isValid());

    delete unparentedNode;

}
