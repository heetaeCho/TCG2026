#include <gtest/gtest.h>

#include <gmock/gmock.h>



// Include necessary headers for the classes under test

#include "./TestProjects/poppler/qt5/src/poppler-optcontent.cc"

#include "./TestProjects/poppler/poppler/OptionalContent.h"



using namespace Poppler;



class MockOptionalContentGroup : public OptionalContentGroup {

public:

    MOCK_CONST_METHOD0(getName, const GooString*());

    MOCK_CONST_METHOD0(getState, State());

};



class OptContentItemTest_2767 : public ::testing::Test {

protected:

    NiceMock<MockOptionalContentGroup> mockGroup;



    void SetUp() override {

        // Set up default expectations for the mock

        EXPECT_CALL(mockGroup, getName()).WillRepeatedly(testing::Return(new GooString("GroupName")));

        EXPECT_CALL(mockGroup, getState()).WillRepeatedly(testing::Return(OptionalContentGroup::On));

    }

};



TEST_F(OptContentItemTest_2767, ConstructorWithGroup_OnState_2767) {

    OptContentItem item(&mockGroup);

    EXPECT_EQ(item.state(), OptContentItem::On);

}



TEST_F(OptContentItemTest_2767, ConstructorWithGroup_OffState_2767) {

    EXPECT_CALL(mockGroup, getState()).WillRepeatedly(testing::Return(OptionalContentGroup::Off));

    OptContentItem item(&mockGroup);

    EXPECT_EQ(item.state(), OptContentItem::Off);

}



TEST_F(OptContentItemTest_2767, ConstructorWithGroup_NameSet_2767) {

    EXPECT_CALL(mockGroup, getName()).WillRepeatedly(testing::Return(new GooString("GroupName")));

    OptContentItem item(&mockGroup);

    EXPECT_EQ(item.name(), "GroupName");

}



TEST_F(OptContentItemTest_2767, ConstructorWithGroup_EnabledByDefault_2767) {

    OptContentItem item(&mockGroup);

    EXPECT_TRUE(item.isEnabled());

}



TEST_F(OptContentItemTest_2767, GroupAccess_2767) {

    OptContentItem item(&mockGroup);

    EXPECT_EQ(item.group(), &mockGroup);

}
