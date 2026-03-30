#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/src/tiffcomposite_int.hpp"

#include "exiv2/error.hpp"



using namespace Exiv2::Internal;

using ::testing::_;



class TiffSubIfdTest_328 : public ::testing::Test {

protected:

    std::unique_ptr<TiffDirectory> tiffDir;

    TiffComponent::SharedPtr tiffComponent;



    void SetUp() override {

        tiffDir = std::make_unique<TiffDirectory>(0, IfdId(), IfdId());

        tiffComponent = TiffComponent::SharedPtr(tiffDir.release());

    }

};



TEST_F(TiffSubIfdTest_328, AddChildReturnsValidPointer_328) {

    TiffSubIfd subIfd(0, IfdId(), IfdId());

    TiffComponent* result = subIfd.doAddChild(tiffComponent);

    EXPECT_NE(result, nullptr);

}



TEST_F(TiffSubIfdTest_328, AddChildThrowsOnInvalidCast_328) {

    TiffSubIfd subIfd(0, IfdId(), IfdId());

    auto invalidComponent = std::make_shared<TiffEntryBase>(0, IfdId(), TiffDataType::ttUnsignedLong);

    EXPECT_THROW(subIfd.doAddChild(invalidComponent), Exiv2::Error);

}



TEST_F(TiffSubIfdTest_328, AddChildAddsToInternalList_328) {

    TiffSubIfd subIfd(0, IfdId(), IfdId());

    subIfd.doAddChild(tiffComponent);

    EXPECT_EQ(subIfd.ifds_.size(), 1U);

}



TEST_F(TiffSubIfdTest_328, AddChildReturnsSamePointer_328) {

    TiffSubIfd subIfd(0, IfdId(), IfdId());

    TiffComponent* result = subIfd.doAddChild(tiffComponent);

    EXPECT_EQ(result, tiffComponent.get());

}
