#include <gtest/gtest.h>

#include "tiffcomposite_int.hpp"



using namespace Exiv2::Internal;



class TiffMappingInfoTest_281 : public ::testing::Test {

protected:

    TiffMappingInfo tiffMappingInfo;

    TiffMappingInfo::Key key;



    void SetUp() override {

        tiffMappingInfo.make_ = "*";

        tiffMappingInfo.extendedTag_ = Tag::all;

        tiffMappingInfo.group_ = IfdId(0);

        key.m_ = "exampleMake";

        key.e_ = 12345;

        key.g_ = IfdId(0);

    }

};



TEST_F(TiffMappingInfoTest_281, OperatorEqual_MakeWildcard_TagAll_GroupMatch_281) {

    EXPECT_TRUE(tiffMappingInfo == key);

}



TEST_F(TiffMappingInfoTest_281, OperatorEqual_MakeSpecific_TagAll_GroupMatch_281) {

    tiffMappingInfo.make_ = "exampleMake";

    EXPECT_TRUE(tiffMappingInfo == key);

}



TEST_F(TiffMappingInfoTest_281, OperatorEqual_MakeMismatch_TagAll_GroupMatch_281) {

    tiffMappingInfo.make_ = "differentMake";

    EXPECT_FALSE(tiffMappingInfo == key);

}



TEST_F(TiffMappingInfoTest_281, OperatorEqual_MakeWildcard_TagSpecific_GroupMatch_281) {

    tiffMappingInfo.extendedTag_ = Tag::pana;

    EXPECT_FALSE(tiffMappingInfo == key);

}



TEST_F(TiffMappingInfoTest_281, OperatorEqual_MakeWildcard_TagAll_GroupMismatch_281) {

    key.g_ = IfdId(1);

    EXPECT_FALSE(tiffMappingInfo == key);

}



TEST_F(TiffMappingInfoTest_281, OperatorEqual_BoundaryCondition_EmptyMake_TagAll_GroupMatch_281) {

    tiffMappingInfo.make_ = "";

    EXPECT_TRUE(tiffMappingInfo == key);

}



TEST_F(TiffMappingInfoTest_281, OperatorEqual_ExceptionalCase_EmptyKeyMembers_281) {

    key.m_ = "";

    key.e_ = 0;

    EXPECT_FALSE(tiffMappingInfo == key);

}
