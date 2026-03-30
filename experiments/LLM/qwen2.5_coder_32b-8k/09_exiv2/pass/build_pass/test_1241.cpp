#include <gtest/gtest.h>

#include "exiv2/properties.hpp"



using namespace Exiv2;



class XmpNsInfoTest_1241 : public ::testing::Test {

protected:

    void SetUp() override {

        xmpNsInfo1 = XmpNsInfo{"http://example.com/ns", {"exif"}, nullptr};

        xmpNsInfo2 = XmpNsInfo{"http://example.com/another_ns", {"xmp"}, nullptr};

        prefixExif = XmpNsInfo::Prefix{"exif"};

        prefixXmp = XmpNsInfo::Prefix{"xmp"};

    }



    XmpNsInfo xmpNsInfo1;

    XmpNsInfo xmpNsInfo2;

    XmpNsInfo::Prefix prefixExif;

    XmpNsInfo::Prefix prefixXmp;

};



TEST_F(XmpNsInfoTest_1241, EqualOperatorSamePrefix_1241) {

    EXPECT_TRUE(xmpNsInfo1 == prefixExif);

}



TEST_F(XmpNsInfoTest_1241, EqualOperatorDifferentPrefix_1241) {

    EXPECT_FALSE(xmpNsInfo1 == prefixXmp);

}



TEST_F(XmpNsInfoTest_1241, EqualOperatorBoundaryEmptyString_1241) {

    XmpNsInfo::Prefix emptyPrefix{""};

    XmpNsInfo xmpNsInfoEmpty{"http://example.com/empty_ns", {""}, nullptr};



    EXPECT_TRUE(xmpNsInfoEmpty == emptyPrefix);

}



TEST_F(XmpNsInfoTest_1241, EqualOperatorBoundaryNullString_1241) {

    XmpNsInfo::Prefix nullPrefix{nullptr};

    XmpNsInfo xmpNsInfoNull{"http://example.com/null_ns", {nullptr}, nullptr};



    EXPECT_FALSE(xmpNsInfoNull == nullPrefix); // Assuming comparison with nullptr results in false

}



TEST_F(XmpNsInfoTest_1241, EqualOperatorBoundaryLongString_1241) {

    XmpNsInfo::Prefix longPrefix{"averylongprefixthatshouldstillworkwithoutissues"};

    XmpNsInfo xmpNsInfoLong{"http://example.com/long_ns", {"averylongprefixthatshouldstillworkwithoutissues"}, nullptr};



    EXPECT_TRUE(xmpNsInfoLong == longPrefix);

}
