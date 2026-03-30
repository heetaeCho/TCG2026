#include <gtest/gtest.h>

#include <QModelIndex>

#include "poppler-optcontent-private.h"



using namespace Poppler;



class OptContentModelPrivateTest : public ::testing::Test {

protected:

    OptContentModel model;

    const OCGs optContent;

    OptContentModelPrivate sut{&model, &optContent};

    OptContentItem* mockNode = new OptContentItem();

    QModelIndex validIndex;

    QModelIndex invalidIndex;



    void SetUp() override {

        validIndex = QModelIndex::fromInternalPointer(mockNode);

        invalidIndex.setModelIndexData(nullptr); // Ensure it's invalid

    }



    void TearDown() override {

        delete mockNode;

    }

};



TEST_F(OptContentModelPrivateTest_1277, NodeFromIndex_ReturnsValidNode_1277) {

    OptContentItem* result = sut.nodeFromIndex(validIndex, false);

    EXPECT_EQ(result, mockNode);

}



TEST_F(OptContentModelPrivateTest_1277, NodeFromIndex_ReturnsNullForInvalidIndexIfCanBeNull_1277) {

    OptContentItem* result = sut.nodeFromIndex(invalidIndex, true);

    EXPECT_EQ(result, nullptr);

}



TEST_F(OptContentModelPrivateTest_1277, NodeFromIndex_ReturnsRootNodeForInvalidIndexIfCannotBeNull_1277) {

    sut.m_rootNode = mockNode;

    OptContentItem* result = sut.nodeFromIndex(invalidIndex, false);

    EXPECT_EQ(result, mockNode);

}



TEST_F(OptContentModelPrivateTest_1277, NodeFromIndex_ReturnsRootNodeForNullInternalPointerIfCannotBeNull_1277) {

    QModelIndex nullPointerIndex;

    sut.m_rootNode = mockNode;

    OptContentItem* result = sut.nodeFromIndex(nullPointerIndex, false);

    EXPECT_EQ(result, mockNode);

}



TEST_F(OptContentModelPrivateTest_1277, NodeFromIndex_ReturnsNullForNullInternalPointerIfCanBeNull_1277) {

    QModelIndex nullPointerIndex;

    OptContentItem* result = sut.nodeFromIndex(nullPointerIndex, true);

    EXPECT_EQ(result, nullptr);

}
