#include <gtest/gtest.h>

#include "exiv2/image.hpp"



using namespace Exiv2;



class ImageTest : public ::testing::Test {

protected:

    std::unique_ptr<BasicIo> io = BasicIo::autoPtr();

    Image image{ImageType::unknown, 0, std::move(io)};

};



TEST_F(ImageTest_1055, IsPrintXMP_ReturnsTrueForType700AndKpsXMP_1055) {

    EXPECT_TRUE(image.isPrintXMP(700, kpsXMP));

}



TEST_F(ImageTest_1055, IsPrintXMP_ReturnsFalseForOtherTypes_1055) {

    EXPECT_FALSE(image.isPrintXMP(699, kpsXMP));

    EXPECT_FALSE(image.isPrintXMP(701, kpsXMP));

}



TEST_F(ImageTest_1055, IsPrintXMP_ReturnsFalseForType700AndOtherOptions_1055) {

    EXPECT_FALSE(image.isPrintXMP(700, kpsNone));

    EXPECT_FALSE(image.isPrintXMP(700, kpsBasic));

    EXPECT_FALSE(image.isPrintXMP(700, kpsRecursive));

    EXPECT_FALSE(image.isPrintXMP(700, kpsIccProfile));

    EXPECT_FALSE(image.isPrintXMP(700, kpsIptcErase));

}



TEST_F(ImageTest_1055, IsPrintXMP_ReturnsFalseForZeroTypeAndKpsXMP_1055) {

    EXPECT_FALSE(image.isPrintXMP(0, kpsXMP));

}



TEST_F(ImageTest_1055, IsPrintXMP_ReturnsFalseForMaxUint16TypeAndKpsXMP_1055) {

    EXPECT_FALSE(image.isPrintXMP(UINT16_MAX, kpsXMP));

}
