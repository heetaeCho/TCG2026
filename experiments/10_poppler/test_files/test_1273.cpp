#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-optcontent-private.h"



using namespace Poppler;



class OptContentModelPrivateTest : public ::testing::Test {

protected:

    class MockOptContentItem : public OptContentItem {

    public:

        MOCK_METHOD(void, someMethod, (), (override));

    };



    class MockOCGs : public OCGs {

    public:

        MOCK_CONST_METHOD0(someMethod, void());

    };



    class MockArray : public Array {

    public:

        MOCK_CONST_METHOD0(size, int()) const;

        MOCK_CONST_METHOD1(get, Object*(int)) const;

    };



    class MockQModelIndex : public QModelIndex {

    public:

        MOCK_CONST_METHOD0(isValid, bool()) const;

    };



    OptContentModel mockOptContentModel;

    NiceMock<MockOCGs> mockOcg;

    std::unique_ptr<OptContentModelPrivate> sut;



    void SetUp() override {

        sut = std::make_unique<OptContentModelPrivate>(&mockOptContentModel, &mockOcg);

    }

};



TEST_F(OptContentModelPrivateTest_1273, DestructorDeletesItems_1273) {

    MockOptContentItem* mockItem1 = new MockOptContentItem();

    MockOptContentItem* mockItem2 = new MockOptContentItem();

    sut->m_optContentItems.push_back(mockItem1);

    sut->m_headerOptContentItems.push_back(mockItem2);



    EXPECT_CALL(*mockItem1, someMethod()).Times(1); // Destructing will call destructor of OptContentItem

    EXPECT_CALL(*mockItem2, someMethod()).Times(1); // Destructing will call destructor of OptContentItem



    sut.reset();

}



TEST_F(OptContentModelPrivateTest_1273, SetRootNodeSetsCorrectly_1273) {

    MockOptContentItem* mockRootNode = new MockOptContentItem();

    sut->setRootNode(mockRootNode);



    EXPECT_EQ(sut->m_rootNode, mockRootNode);

}



TEST_F(OptContentModelPrivateTest_1273, IndexFromItemReturnsValidIndex_1273) {

    MockOptContentItem* mockItem = new MockOptContentItem();

    int column = 0;

    QModelIndex index = sut->indexFromItem(mockItem, column);



    EXPECT_TRUE(index.isValid());

}



TEST_F(OptContentModelPrivateTest_1273, NodeFromIndexReturnsNullIfInvalid_1273) {

    NiceMock<MockQModelIndex> mockIndex;

    ON_CALL(mockIndex, isValid()).WillByDefault(testing::Return(false));



    const OptContentItem* node = sut->nodeFromIndex(mockIndex, true);



    EXPECT_EQ(node, nullptr);

}



TEST_F(OptContentModelPrivateTest_1273, ItemFromRefReturnsNullIfNotFound_1273) {

    int ref = 999;

    const OptContentItem* item = sut->itemFromRef(ref);



    EXPECT_EQ(item, nullptr);

}
