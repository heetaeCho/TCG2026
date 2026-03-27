#include <gtest/gtest.h>

#include "crwimage_int.hpp"



using namespace Exiv2::Internal;



class CiffComponentTest_1788 : public ::testing::Test {

protected:

    uint16_t tagId = 0x0100;

    uint16_t dirId = 0x0001;

    CiffComponent component {tagId, dirId};

};



TEST_F(CiffComponentTest_1788, FindComponentSameTagAndDir_1788) {

    auto result = component.findComponent(tagId, dirId);

    EXPECT_EQ(result, &component);

}



TEST_F(CiffComponentTest_1788, FindComponentDifferentTag_1788) {

    auto result = component.findComponent(tagId + 1, dirId);

    EXPECT_EQ(result, nullptr);

}



TEST_F(CiffComponentTest_1788, FindComponentDifferentDir_1788) {

    auto result = component.findComponent(tagId, dirId + 1);

    EXPECT_EQ(result, nullptr);

}



TEST_F(CiffComponentTest_1788, FindComponentDifferentTagAndDir_1788) {

    auto result = component.findComponent(tagId + 1, dirId + 1);

    EXPECT_EQ(result, nullptr);

}



TEST_F(CiffComponentTest_1788, GettersReturnInitializedValues_1788) {

    EXPECT_EQ(component.tagId(), tagId);

    EXPECT_EQ(component.dir(), dirId);

}



TEST_F(CiffComponentTest_1788, DefaultConstructorInitializesToZero_1788) {

    CiffComponent defaultComponent;

    EXPECT_EQ(defaultComponent.tagId(), 0);

    EXPECT_EQ(defaultComponent.dir(), 0);

}
