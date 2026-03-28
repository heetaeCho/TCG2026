#include <gtest/gtest.h>

#include "exiv2/properties.hpp"

#include <string>



namespace {



class XmpPropertyInfoTest_1242 : public ::testing::Test {

protected:

    Exiv2::XmpPropertyInfo xmpPropertyInfo;

};



TEST_F(XmpPropertyInfoTest_1242, OperatorEqual_SameName_ReturnsTrue_1242) {

    const std::string name = "example";

    xmpPropertyInfo.name_ = name; // Assuming we can set this for testing purposes

    EXPECT_TRUE(xmpPropertyInfo == name);

}



TEST_F(XmpPropertyInfoTest_1242, OperatorEqual_DifferentName_ReturnsFalse_1242) {

    const std::string name = "example";

    xmpPropertyInfo.name_ = "different";

    EXPECT_FALSE(xmpPropertyInfo == name);

}



TEST_F(XmpPropertyInfoTest_1242, OperatorEqual_EmptyString_ReturnsFalse_1242) {

    const std::string name = "";

    xmpPropertyInfo.name_ = "non-empty";

    EXPECT_FALSE(xmpPropertyInfo == name);

}



TEST_F(XmpPropertyInfoTest_1242, OperatorEqual_NonEmptyAgainstEmpty_ReturnsFalse_1242) {

    const std::string name = "example";

    xmpPropertyInfo.name_ = "";

    EXPECT_FALSE(xmpPropertyInfo == name);

}



} // namespace
