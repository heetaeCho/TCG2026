#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/exiv2/src/crwimage_int.hpp"



using namespace Exiv2::Internal;

using ::testing::_;



class CiffComponentTest_1795 : public ::testing::Test {

protected:

    CiffComponent component;

};



TEST_F(CiffComponentTest_1795, DefaultConstructorInitializesSizeToZero_1795) {

    EXPECT_TRUE(component.empty());

}



TEST_F(CiffComponentTest_1795, EmptyReturnsTrueWhenSizeIsZero_1795) {

    CiffComponent emptyComponent;

    EXPECT_TRUE(emptyComponent.empty());

}



TEST_F(CiffComponentTest_1795, EmptyReturnsFalseWhenSizeIsNonZero_1795) {

    CiffComponent nonEmptyComponent;

    nonEmptyComponent.setSize(1);

    EXPECT_FALSE(nonEmptyComponent.empty());

}



TEST_F(CiffComponentTest_1795, DoEmptyDelegatesToPublicEmptyMethod_1795) {

    EXPECT_EQ(component.doEmpty(), component.empty());

}



TEST_F(CiffComponentTest_1795, SetSizeUpdatesSizeCorrectly_1795) {

    size_t newSize = 10;

    component.setSize(newSize);

    EXPECT_EQ(component.size(), newSize);

}



TEST_F(CiffComponentTest_1795, SetOffsetUpdatesOffsetCorrectly_1795) {

    size_t newOffset = 20;

    component.setOffset(newOffset);

    EXPECT_EQ(component.offset(), newOffset);

}
