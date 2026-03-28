#include <gtest/gtest.h>

#include "TestProjects/exiv2/src/crwimage_int.hpp"



using namespace Exiv2::Internal;



// Test Fixture for CiffComponent

class CiffComponentTest_1760 : public ::testing::Test {

protected:

    CiffComponent component;

};



// Test to check the default constructor and size method

TEST_F(CiffComponentTest_1760, DefaultConstructorSizeCheck_1760) {

    EXPECT_EQ(component.size(), 0U);

}



// Test to check the parameterized constructor and size method

TEST_F(CiffComponentTest_1760, ParameterizedConstructorTagDir_1760) {

    CiffComponent comp(1, 2);

    EXPECT_EQ(comp.tag(), 1U);

    EXPECT_EQ(comp.dir(), 2U);

}



// Test to check the empty method on default constructed component

TEST_F(CiffComponentTest_1760, DefaultConstructorEmptyCheck_1760) {

    EXPECT_TRUE(component.empty());

}



// Test to check the tagId method

TEST_F(CiffComponentTest_1760, TagIdMethod_1760) {

    CiffComponent comp(3, 4);

    EXPECT_EQ(comp.tagId(), 3U);

}



// Test to check the typeId static method

TEST(CiffComponentStaticMethods_1760, TypeIdMethod_1760) {

    auto typeId = CiffComponent::typeId(5);

    // Assuming some valid TypeId is returned, we can't infer the exact value.

    EXPECT_NE(typeId, 0U); // This is a placeholder check

}



// Test to check the dataLocation static method

TEST(CiffComponentStaticMethods_1760, DataLocationMethod_1760) {

    auto dataLoc = CiffComponent::dataLocation(6);

    // Assuming some valid DataLocId is returned, we can't infer the exact value.

    EXPECT_NE(dataLoc, 0U); // This is a placeholder check

}



// Test to verify that setting size and getting it back works

TEST_F(CiffComponentTest_1760, SetSizeAndGetSize_1760) {

    component.setSize(42);

    EXPECT_EQ(component.size(), 42U);

}



// Test to verify that setting offset and getting it back works

TEST_F(CiffComponentTest_1760, SetOffsetAndGetOffset_1760) {

    component.setOffset(100);

    EXPECT_EQ(component.offset(), 100U);

}



// Test boundary conditions for size and offset

TEST_F(CiffComponentTest_1760, BoundaryConditionsSizeAndOffset_1760) {

    component.setSize(0);

    component.setOffset(0);

    EXPECT_EQ(component.size(), 0U);

    EXPECT_EQ(component.offset(), 0U);



    component.setSize(std::numeric_limits<size_t>::max());

    component.setOffset(std::numeric_limits<size_t>::max());

    EXPECT_EQ(component.size(), std::numeric_limits<size_t>::max());

    EXPECT_EQ(component.offset(), std::numeric_limits<size_t>::max());

}
