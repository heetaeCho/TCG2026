#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/exiv2/src/tiffcomposite_int.hpp"



using namespace Exiv2::Internal;

using testing::_;



class TiffMnEntryTest_335 : public ::testing::Test {

protected:

    std::unique_ptr<TiffComponent> component = std::make_unique<TiffComponent>(0, IfdId::rootIFD);

    TiffMnEntry tiffMnEntry{1, IfdId::rootIFD, IfdId::rootIFD};

};



TEST_F(TiffMnEntryTest_335, DoAddNextWithMnNotNull_335) {

    std::unique_ptr<TiffComponent> nextComponent = std::make_unique<TiffComponent>(2, IfdId::rootIFD);

    EXPECT_CALL(*component.get(), doAddNext(_)).WillOnce(testing::Return(nextComponent.get()));



    tiffMnEntry.mn_ = std::move(component);

    TiffComponent* result = tiffMnEntry.doAddNext(std::move(nextComponent));



    ASSERT_NE(result, nullptr);

}



TEST_F(TiffMnEntryTest_335, DoAddNextWithMnNull_335) {

    std::unique_ptr<TiffComponent> nextComponent = std::make_unique<TiffComponent>(2, IfdId::rootIFD);



    TiffComponent* result = tiffMnEntry.doAddNext(std::move(nextComponent));



    ASSERT_EQ(result, nullptr);

}
