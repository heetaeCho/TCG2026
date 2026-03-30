#include <gtest/gtest.h>

#include "exiv2/properties.hpp"



using namespace Exiv2;



class XmpNsInfoTest_1240 : public ::testing::Test {

protected:

    XmpNsInfo xmpNsInfo;

    XmpNsInfo::Ns nsEqual = {"http://example.com/"};

    XmpNsInfo::Ns nsNotEqual = {"http://another-example.com/"};



    void SetUp() override {

        xmpNsInfo.ns_ = "http://example.com/";

        xmpNsInfo.prefix_ = "ex";

        xmpNsInfo.xmpPropertyInfo_ = nullptr;

    }

};



TEST_F(XmpNsInfoTest_1240, EqualityOperator_ReturnsTrueForEqualNamespace_1240) {

    EXPECT_TRUE(xmpNsInfo == nsEqual);

}



TEST_F(XmpNsInfoTest_1240, EqualityOperator_ReturnsFalseForNonEqualNamespace_1240) {

    EXPECT_FALSE(xmpNsInfo == nsNotEqual);

}
