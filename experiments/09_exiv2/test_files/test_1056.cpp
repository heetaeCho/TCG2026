#include <gtest/gtest.h>

#include "exiv2/image.hpp"



using namespace Exiv2;



class ImageTest_1056 : public ::testing::Test {

protected:

    std::unique_ptr<BasicIo> io = nullptr;

    Image image{ImageType::jpeg, 0x00ff, std::move(io)};

};



TEST_F(ImageTest_1056, IsPrintICCNegativeType_1056) {

    EXPECT_FALSE(image.isPrintICC(0x8772, kpsIccProfile));

}



TEST_F(ImageTest_1056, IsPrintICCNegativeOption_1056) {

    EXPECT_FALSE(image.isPrintICC(0x8773, kpsXMP));

}



TEST_F(ImageTest_1056, IsPrintICCValidInput_1056) {

    EXPECT_TRUE(image.isPrintICC(0x8773, kpsIccProfile));

}



TEST_F(ImageTest_1056, IsPrintICCBoundaryType_1056) {

    EXPECT_FALSE(image.isPrintICC(0x0000, kpsIccProfile));

    EXPECT_FALSE(image.isPrintICC(0xFFFF, kpsIccProfile));

}



TEST_F(ImageTest_1056, IsPrintICCBoundaryOption_1056) {

    EXPECT_FALSE(image.isPrintICC(0x8773, kpsNone));

    EXPECT_FALSE(image.isPrintICC(0x8773, static_cast<PrintStructureOption>(6)));

}



TEST_F(ImageTest_1056, IsPrintICCNegativeBoth_1056) {

    EXPECT_FALSE(image.isPrintICC(0x8772, kpsXMP));

}
