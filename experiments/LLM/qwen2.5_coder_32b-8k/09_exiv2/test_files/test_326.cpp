#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "TestProjects/exiv2/src/tiffcomposite_int.cpp"



using namespace Exiv2::Internal;



class TiffComponentTest_326 : public ::testing::Test {

protected:

    SharedPtr<TiffComponent> child;

    TiffComponent tiffComponent;



    void SetUp() override {

        child.reset(new TiffComponent());

    }

};



TEST_F(TiffComponentTest_326, DoAddChild_ReturnsNullptr_326) {

    EXPECT_EQ(tiffComponent.doAddChild(child), nullptr);

}



TEST_F(TiffComponentTest_326, DoAddChild_NullChild_ReturnsNullptr_326) {

    SharedPtr<TiffComponent> nullChild;

    EXPECT_EQ(tiffComponent.doAddChild(nullChild), nullptr);

}
