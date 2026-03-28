#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-document.h"

#include "Outline.h"



using ::testing::_;

using ::testing::NiceMock;

using ::testing::Return;



class MockPopplerAction {

public:

    MOCK_METHOD(void, someMethod, (), (const));

};



TEST_F(PopplerIndexIterTest_2217, GetAction_NormalOperation_2217) {

    // Arrange

    OutlineItem item;

    const LinkAction link_action;

    std::vector<Unicode> title = {0x54, 0x65, 0x73, 0x74}; // "Test"

    item.setTitle("Test");

    EXPECT_CALL(item, getAction()).WillOnce(Return(&link_action));

    EXPECT_CALL(item, getTitle()).WillRepeatedly(ReturnRef(title));



    PopplerIndexIter iter = {nullptr, 0};

    iter.items = new const int*[1];

    iter.items[0] = reinterpret_cast<const int*>(&item);



    // Act

    PopplerAction* action = poppler_index_iter_get_action(&iter);



    // Assert

    ASSERT_NE(action, nullptr);

}



TEST_F(PopplerIndexIterTest_2217, GetAction_BoundaryCondition_EmptyTitle_2217) {

    // Arrange

    OutlineItem item;

    const LinkAction link_action;

    std::vector<Unicode> title = {};

    item.setTitle("");

    EXPECT_CALL(item, getAction()).WillOnce(Return(&link_action));

    EXPECT_CALL(item, getTitle()).WillRepeatedly(ReturnRef(title));



    PopplerIndexIter iter = {nullptr, 0};

    iter.items = new const int*[1];

    iter.items[0] = reinterpret_cast<const int*>(&item);



    // Act

    PopplerAction* action = poppler_index_iter_get_action(&iter);



    // Assert

    ASSERT_NE(action, nullptr);

}



TEST_F(PopplerIndexIterTest_2217, GetAction_ExceptionalCase_NullIterator_2217) {

    // Arrange

    PopplerIndexIter * iter = nullptr;



    // Act & Assert

    EXPECT_EQ(poppler_index_iter_get_action(iter), nullptr);

}



TEST_F(PopplerIndexIterTest_2217, GetAction_BoundaryCondition_EndOfItems_2217) {

    // Arrange

    OutlineItem item;

    const LinkAction link_action;

    std::vector<Unicode> title = {0x54, 0x65, 0x73, 0x74}; // "Test"

    item.setTitle("Test");

    EXPECT_CALL(item, getAction()).WillOnce(Return(&link_action));

    EXPECT_CALL(item, getTitle()).WillRepeatedly(ReturnRef(title));



    PopplerIndexIter iter = {nullptr, 1};

    iter.items = new const int*[1];

    iter.items[0] = reinterpret_cast<const int*>(&item);



    // Act

    PopplerAction* action = poppler_index_iter_get_action(&iter);



    // Assert

    EXPECT_EQ(action, nullptr);

}
