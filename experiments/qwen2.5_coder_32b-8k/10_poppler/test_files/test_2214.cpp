#include <gtest/gtest.h>

#include "TestProjects/poppler/glib/poppler-document.h"



// Mocking OutlineItem to simulate behavior for testing poppler_index_iter_get_child

class MockOutlineItem : public OutlineItem {

public:

    MOCK_METHOD(bool, hasKids, (), (const));

    MOCK_METHOD(const std::vector<OutlineItem*>*, getKids, (), (const));

    MOCK_METHOD(void, open, (), ());

};



// Test fixture class for PopplerIndexIter tests

class PopplerIndexIterTest_2214 : public ::testing::Test {

protected:

    void SetUp() override {

        parent = new MockOutlineItem();

        parent->items = &children;

        indexIter.parent = (PopplerDocument*)parent;

        indexIter.items = &children;

        indexIter.index = 0;

    }



    void TearDown() override {

        delete parent;

    }



    std::vector<MockOutlineItem*> children;

    MockOutlineItem* parent;

    PopplerIndexIter indexIter;

};



// Test normal operation where a child exists

TEST_F(PopplerIndexIterTest_2214, HasChild_ReturnsValidPointer_2214) {

    auto* mockChild = new MockOutlineItem();

    children.push_back(mockChild);



    EXPECT_CALL(*parent, hasKids()).WillOnce(::testing::Return(true));

    EXPECT_CALL(*parent, getKids()).WillOnce(::testing::Return(&children));



    PopplerIndexIter* childIter = poppler_index_iter_get_child(&indexIter);

    ASSERT_NE(childIter, nullptr);

    delete childIter;

}



// Test boundary condition where index is out of range

TEST_F(PopplerIndexIterTest_2214, IndexOutOfRange_ReturnsNull_2214) {

    indexIter.index = 1; // Assuming children vector is empty



    EXPECT_CALL(*parent, hasKids()).WillOnce(::testing::Return(false));

    EXPECT_CALL(*parent, getKids()).Times(0);



    PopplerIndexIter* childIter = poppler_index_iter_get_child(&indexIter);

    ASSERT_EQ(childIter, nullptr);

}



// Test no children case

TEST_F(PopplerIndexIterTest_2214, NoChildren_ReturnsNull_2214) {

    EXPECT_CALL(*parent, hasKids()).WillOnce(::testing::Return(false));

    EXPECT_CALL(*parent, getKids()).Times(0);



    PopplerIndexIter* childIter = poppler_index_iter_get_child(&indexIter);

    ASSERT_EQ(childIter, nullptr);

}



// Test when parent is null

TEST_F(PopplerIndexIterTest_2214, NullParent_ReturnsNull_2214) {

    indexIter.parent = nullptr;



    PopplerIndexIter* childIter = poppler_index_iter_get_child(&indexIter);

    ASSERT_EQ(childIter, nullptr);

}
