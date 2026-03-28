#include <gtest/gtest.h>

#include "tiffcomposite_int.hpp"



using namespace Exiv2::Internal;



class TiffDirectoryTest_334 : public ::testing::Test {

protected:

    TiffDirectoryTest_334() : tiffDir(1, IFD0, true) {}



    TiffDirectory tiffDir;

};



TEST_F(TiffDirectoryTest_334, DoAddNext_SuccessfulAddition_334) {

    auto component = std::make_unique<TiffComponent>(2, IFD0);

    EXPECT_NE(tiffDir.doAddNext(std::move(component)), nullptr);

}



TEST_F(TiffDirectoryTest_334, DoAddNext_SecondAdditionReturnsNullptr_334) {

    auto firstComponent = std::make_unique<TiffComponent>(2, IFD0);

    tiffDir.doAddNext(std::move(firstComponent));



    auto secondComponent = std::make_unique<TiffComponent>(3, IFD1);

    EXPECT_EQ(tiffDir.doAddNext(std::move(secondComponent)), nullptr);

}



TEST_F(TiffDirectoryTest_334, DoAddNext_NoNextAllowed_ReturnsNullptr_334) {

    TiffDirectory tiffDirNoNext(1, IFD0, false);

    auto component = std::make_unique<TiffComponent>(2, IFD0);

    EXPECT_EQ(tiffDirNoNext.doAddNext(std::move(component)), nullptr);

}



TEST_F(TiffDirectoryTest_334, DoAddNext_NullptrInput_ReturnsNullptr_334) {

    EXPECT_EQ(tiffDir.doAddNext(nullptr), nullptr);

}
