#include <gtest/gtest.h>

#include "tiffvisitor_int.hpp"

#include "exif.hpp"



using namespace Exiv2;

using namespace Exiv2::Internal;



class TiffEncoderTest_1681 : public ::testing::Test {

protected:

    TiffBinaryElement tiffBinaryElement;

    Exifdatum exifdatum {ExifKey("Sample"), nullptr};



    void SetUp() override {

        // Setup code if needed

    }



    void TearDown() override {

        // Teardown code if needed

    }

};



TEST_F(TiffEncoderTest_1681, EncodeBinaryElement_NormalOperation_1681) {

    TiffEncoder encoder({}, {}, {}, nullptr, false, PrimaryGroups::all, nullptr, nullptr);

    EXPECT_NO_THROW(encoder.encodeBinaryElement(&tiffBinaryElement, &exifdatum));

}



TEST_F(TiffEncoderTest_1681, EncodeBinaryElement_NullObject_1681) {

    TiffEncoder encoder({}, {}, {}, nullptr, false, PrimaryGroups::all, nullptr, nullptr);

    EXPECT_NO_THROW(encoder.encodeBinaryElement(nullptr, &exifdatum));

}



TEST_F(TiffEncoderTest_1681, EncodeBinaryElement_NullDatum_1681) {

    TiffEncoder encoder({}, {}, {}, nullptr, false, PrimaryGroups::all, nullptr, nullptr);

    EXPECT_NO_THROW(encoder.encodeBinaryElement(&tiffBinaryElement, nullptr));

}



TEST_F(TiffEncoderTest_1681, EncodeBinaryElement_NullObjectAndDatum_1681) {

    TiffEncoder encoder({}, {}, {}, nullptr, false, PrimaryGroups::all, nullptr, nullptr);

    EXPECT_NO_THROW(encoder.encodeBinaryElement(nullptr, nullptr));

}
