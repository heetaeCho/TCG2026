#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "tiffcomposite_int.hpp"



using namespace Exiv2::Internal;



class TiffComponentTest_325 : public ::testing::Test {

protected:

    TiffComponent* tiffComponent;

    

    void SetUp() override {

        tiffComponent = new TiffComponent(0x0100, IfdId::IFD0);

    }



    void TearDown() override {

        delete tiffComponent;

    }

};



TEST_F(TiffComponentTest_325, AddChild_ReturnsNonNullPtr_325) {

    auto child = std::make_shared<TiffComponent>(0x0101, IfdId::IFD0);

    EXPECT_NE(tiffComponent->addChild(child), nullptr);

}



TEST_F(TiffComponentTest_325, AddChild_IncreasesCount_325) {

    size_t initialCount = tiffComponent->count();

    auto child = std::make_shared<TiffComponent>(0x0101, IfdId::IFD0);

    tiffComponent->addChild(child);

    EXPECT_EQ(tiffComponent->count(), initialCount + 1);

}



TEST_F(TiffComponentTest_325, AddChild_MultipleChildren_IncreasesCount_325) {

    size_t initialCount = tiffComponent->count();

    auto child1 = std::make_shared<TiffComponent>(0x0101, IfdId::IFD0);

    auto child2 = std::make_shared<TiffComponent>(0x0102, IfdId::IFD0);

    tiffComponent->addChild(child1);

    tiffComponent->addChild(child2);

    EXPECT_EQ(tiffComponent->count(), initialCount + 2);

}



TEST_F(TiffComponentTest_325, AddChild_NullPtr_ReturnsNull_325) {

    TiffComponent::SharedPtr child = nullptr;

    EXPECT_EQ(tiffComponent->addChild(child), nullptr);

}



TEST_F(TiffComponentTest_325, Count_InitialValueIsZero_325) {

    EXPECT_EQ(tiffComponent->count(), 0);

}
