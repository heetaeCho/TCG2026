#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "makernote_int.hpp"



namespace Exiv2 { namespace Internal {



class TiffMnRegistryTest : public ::testing::Test {

protected:

    TiffMnRegistry registry;

};



TEST_F(TiffMnRegistryTest_1430, OperatorEqual_StringView_Match_1430) {

    registry.make_ = "Canon";

    EXPECT_TRUE(registry == std::string_view("Canon"));

}



TEST_F(TiffMnRegistryTest_1430, OperatorEqual_StringView_NotMatch_1430) {

    registry.make_ = "Canon";

    EXPECT_FALSE(registry == std::string_view("Nikon"));

}



TEST_F(TiffMnRegistryTest_1430, OperatorEqual_IfdId_Match_1430) {

    registry.mnGroup_ = 5;

    EXPECT_TRUE(registry == IfdId(5));

}



TEST_F(TiffMnRegistryTest_1430, OperatorEqual_IfdId_NotMatch_1430) {

    registry.mnGroup_ = 5;

    EXPECT_FALSE(registry == IfdId(6));

}



TEST_F(TiffMnRegistryTest_1430, OperatorEqual_StringView_EmptyString_1430) {

    registry.make_ = "";

    EXPECT_TRUE(registry == std::string_view(""));

}



TEST_F(TiffMnRegistryTest_1430, OperatorEqual_IfdId_ZeroValue_1430) {

    registry.mnGroup_ = 0;

    EXPECT_TRUE(registry == IfdId(0));

}



}} // namespace Exiv2::Internal
