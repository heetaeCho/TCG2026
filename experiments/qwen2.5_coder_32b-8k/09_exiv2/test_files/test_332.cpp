#include <gtest/gtest.h>

#include "tiffcomposite_int.hpp"



using namespace Exiv2::Internal;



class TiffComponentTest_332 : public ::testing::Test {

protected:

    std::unique_ptr<TiffComponent> tiffComponent;



    void SetUp() override {

        tiffComponent = std::make_unique<TiffComponent>(1, IfdId::IFD0);

    }

};



TEST_F(TiffComponentTest_332, AddNext_ReturnsNonNullPointer_332) {

    auto nextComponent = std::make_unique<TiffComponent>(2, IfdId::IFD0);

    EXPECT_NE(tiffComponent->addNext(std::move(nextComponent)), nullptr);

}



TEST_F(TiffComponentTest_332, AddNext_TransfersOwnership_332) {

    auto nextComponent = std::make_unique<TiffComponent>(2, IfdId::IFD0);

    auto rawPtr = nextComponent.get();

    tiffComponent->addNext(std::move(nextComponent));

    EXPECT_EQ(nextComponent.get(), nullptr); // Ownership transferred

}



TEST_F(TiffComponentTest_332, AddNext_MultipleComponents_332) {

    auto next1 = std::make_unique<TiffComponent>(2, IfdId::IFD0);

    auto next2 = std::make_unique<TiffComponent>(3, IfdId::IFD0);

    tiffComponent->addNext(std::move(next1));

    tiffComponent->addNext(std::move(next2));

    EXPECT_TRUE(true); // No crash or exception indicates success

}



TEST_F(TiffComponentTest_332, AddNext_NullPointer_332) {

    TiffComponent* result = tiffComponent->addNext(nullptr);

    EXPECT_EQ(result, nullptr);

}
