#include <gtest/gtest.h>

#include "poppler-optcontent-private.h"



using namespace Poppler;



class OptContentItemTest : public ::testing::Test {

protected:

    OptionalContentGroup mockGroup;

    OptContentItem itemWithGroup;

    OptContentItem defaultItem;



    OptContentItemTest() : itemWithGroup(&mockGroup) {}

};



TEST_F(OptContentItemTest_1268, GroupReturnsCorrectPointer_1268) {

    EXPECT_EQ(itemWithGroup.group(), &mockGroup);

}



TEST_F(OptContentItemTest_1268, DefaultConstructorSetsNullGroup_1268) {

    EXPECT_EQ(defaultItem.group(), nullptr);

}



TEST_F(OptContentItemTest_1268, GroupDoesNotChangeAfterConstruction_1268) {

    OptionalContentGroup anotherMockGroup;

    itemWithGroup.setState(ItemState::On, true, 0);

    EXPECT_EQ(itemWithGroup.group(), &mockGroup); // Ensure group pointer remains unchanged

}



TEST_F(OptContentItemTest_1268, GroupIsConst_1268) {

    const OptContentItem& constItem = itemWithGroup;

    EXPECT_EQ(constItem.group(), &mockGroup);

}
