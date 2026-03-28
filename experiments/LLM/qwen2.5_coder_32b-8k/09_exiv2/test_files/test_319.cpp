#include <gtest/gtest.h>

#include "TestProjects/exiv2/src/tiffcomposite_int.cpp"



using namespace Exiv2::Internal;



class TiffComponentTest_319 : public ::testing::Test {

protected:

    TiffComponent component;

    uint16_t tag = 0x0112; // Example tag

    TiffPath tiffPath; // Assuming TiffPath has a default constructor

    TiffComponent* pRoot = nullptr;

    TiffComponent::UniquePtr object = std::make_unique<TiffComponent>();

};



TEST_F(TiffComponentTest_319, DoAddPath_ReturnsThisPointer_319) {

    TiffComponent* result = component.doAddPath(tag, tiffPath, pRoot, std::move(object));

    EXPECT_EQ(result, &component);

}



// Boundary condition: Test with minimal tag value

TEST_F(TiffComponentTest_319, DoAddPath_MinimalTagValue_ReturnsThisPointer_319) {

    uint16_t minTag = 0x0000;

    TiffComponent* result = component.doAddPath(minTag, tiffPath, pRoot, std::move(object));

    EXPECT_EQ(result, &component);

}



// Boundary condition: Test with maximal tag value

TEST_F(TiffComponentTest_319, DoAddPath_MaximalTagValue_ReturnsThisPointer_319) {

    uint16_t maxTag = 0xFFFF;

    TiffComponent* result = component.doAddPath(maxTag, tiffPath, pRoot, std::move(object));

    EXPECT_EQ(result, &component);

}



// Exceptional case: Test with null root pointer (assuming no exception is thrown)

TEST_F(TiffComponentTest_319, DoAddPath_NullRootPointer_ReturnsThisPointer_319) {

    TiffComponent* result = component.doAddPath(tag, tiffPath, nullptr, std::move(object));

    EXPECT_EQ(result, &component);

}



// Exceptional case: Test with null object (assuming no exception is thrown)

TEST_F(TiffComponentTest_319, DoAddPath_NullObject_ReturnsThisPointer_319) {

    TiffComponent* result = component.doAddPath(tag, tiffPath, pRoot, nullptr);

    EXPECT_EQ(result, &component);

}
