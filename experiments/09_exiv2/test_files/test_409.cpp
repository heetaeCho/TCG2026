#include <gtest/gtest.h>

#include "tiffcomposite_int.hpp"

#include "value.hpp"



using namespace Exiv2::Internal;

using namespace Exiv2;



class TiffImageEntryTest_409 : public ::testing::Test {

protected:

    TiffImageEntryTest_409() {

        // Initialize any necessary objects here

        tiffImageEntry = std::make_unique<TiffImageEntry>(1, IfdId::IFD0, TiffType::unsignedByte);

    }



    std::unique_ptr<TiffImageEntry> tiffImageEntry;

};



TEST_F(TiffImageEntryTest_409, DoSizeImage_ReturnsZeroWhenNoValueSet_409) {

    EXPECT_EQ(tiffImageEntry->doSizeImage(), 0U);

}



TEST_F(TiffImageEntryTest_409, DoSizeImage_ReturnsSizeDataAreaWhenNonZero_409) {

    auto mockValue = std::make_unique<Value>(TypeId::unsignedByte);

    ON_CALL(*mockValue, sizeDataArea()).WillByDefault(::testing::Return(1024U));

    tiffImageEntry->setValue(std::move(mockValue));



    EXPECT_EQ(tiffImageEntry->doSizeImage(), 1024U);

}



TEST_F(TiffImageEntryTest_409, DoSizeImage_ReturnsSumOfStripSizesWhenNoDataArea_409) {

    auto mockValue = std::make_unique<Value>(TypeId::unsignedByte);

    ON_CALL(*mockValue, sizeDataArea()).WillByDefault(::testing::Return(0U));

    tiffImageEntry->setValue(std::move(mockValue));



    Strips strips{{1, 512}, {2, 512}};

    tiffImageEntry->setStrips(nullptr, nullptr, 0, 0);



    EXPECT_EQ(tiffImageEntry->doSizeImage(), 1024U);

}



TEST_F(TiffImageEntryTest_409, DoSizeImage_HandlesEmptyStripsCorrectly_409) {

    auto mockValue = std::make_unique<Value>(TypeId::unsignedByte);

    ON_CALL(*mockValue, sizeDataArea()).WillByDefault(::testing::Return(0U));

    tiffImageEntry->setValue(std::move(mockValue));



    Strips strips;

    tiffImageEntry->setStrips(nullptr, nullptr, 0, 0);



    EXPECT_EQ(tiffImageEntry->doSizeImage(), 0U);

}



TEST_F(TiffImageEntryTest_409, DoSizeImage_HandlesNullValueCorrectly_409) {

    Strips strips{{1, 512}, {2, 512}};

    tiffImageEntry->setStrips(nullptr, nullptr, 0, 0);



    EXPECT_EQ(tiffImageEntry->doSizeImage(), 1024U);

}



TEST_F(TiffImageEntryTest_409, DoSizeImage_HandlesMixedCasesCorrectly_409) {

    auto mockValue = std::make_unique<Value>(TypeId::unsignedByte);

    ON_CALL(*mockValue, sizeDataArea()).WillByDefault(::testing::Return(512U));

    tiffImageEntry->setValue(std::move(mockValue));



    Strips strips{{1, 256}, {2, 256}};

    tiffImageEntry->setStrips(nullptr, nullptr, 0, 0);



    EXPECT_EQ(tiffImageEntry->doSizeImage(), 512U);

}
