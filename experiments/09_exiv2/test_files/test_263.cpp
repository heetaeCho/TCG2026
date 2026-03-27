#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/exiv2/src/tiffcomposite_int.hpp"



using namespace Exiv2::Internal;



class TiffComponentTest_263 : public ::testing::Test {

protected:

    // No additional setup needed for this test as it's a static function

};



TEST_F(TiffComponentTest_263, NewTiffThumbData_ReturnsUniquePtr_263) {

    auto result = newTiffThumbData<0x1234, ifdExif>(0x1234, ifdExif);

    EXPECT_NE(result.get(), nullptr);

}



TEST_F(TiffComponentTest_263, NewTiffThumbData_CorrectTagAndGroup_263) {

    auto result = newTiffThumbData<0x1234, ifdExif>(0x5678, ifdGpsInfo);

    EXPECT_EQ(result->tag(), 0x5678);

    EXPECT_EQ(result->group(), ifdGpsInfo);

}



TEST_F(TiffComponentTest_263, NewTiffThumbData_TemplateParametersMatchFunctionArguments_263) {

    auto result = newTiffThumbData<0x1234, ifdExif>(0x1234, ifdExif);

    EXPECT_EQ(result->tag(), 0x1234);

    EXPECT_EQ(result->group(), ifdExif);

}



TEST_F(TiffComponentTest_263, NewTiffThumbData_DifferentTemplateParameters_263) {

    auto result = newTiffThumbData<0xABCD, ifdIop>(0x1234, ifdExif);

    EXPECT_EQ(result->tag(), 0x1234);

    EXPECT_EQ(result->group(), ifdExif);

}

```


