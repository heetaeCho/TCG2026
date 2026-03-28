#include <gtest/gtest.h>

#include "exiv2/types.hpp"

#include "./TestProjects/exiv2/src/quicktimevideo.cpp"



using namespace Exiv2::Internal;



// Helper function to create a DataBuf with specific content

Exiv2::DataBuf CreateDataBuf(const char* data, size_t size) {

    return Exiv2::DataBuf(reinterpret_cast<const uint8_t*>(data), size);

}



class IgnoreListTest_654 : public ::testing::Test {

protected:

};



TEST_F(IgnoreListTest_654, NormalOperation_MdatTag_654) {

    Exiv2::DataBuf buf = CreateDataBuf("mdat", 4);

    EXPECT_TRUE(ignoreList(buf));

}



TEST_F(IgnoreListTest_654, NormalOperation_EdtsTag_654) {

    Exiv2::DataBuf buf = CreateDataBuf("edts", 4);

    EXPECT_TRUE(ignoreList(buf));

}



TEST_F(IgnoreListTest_654, NormalOperation_JunkTag_654) {

    Exiv2::DataBuf buf = CreateDataBuf("junk", 4);

    EXPECT_TRUE(ignoreList(buf));

}



TEST_F(IgnoreListTest_654, NormalOperation_IodsTag_654) {

    Exiv2::DataBuf buf = CreateDataBuf("iods", 4);

    EXPECT_TRUE(ignoreList(buf));

}



TEST_F(IgnoreListTest_654, NormalOperation_AlisTag_654) {

    Exiv2::DataBuf buf = CreateDataBuf("alis", 4);

    EXPECT_TRUE(ignoreList(buf));

}



TEST_F(IgnoreListTest_654, NormalOperation_StscTag_654) {

    Exiv2::DataBuf buf = CreateDataBuf("stsc", 4);

    EXPECT_TRUE(ignoreList(buf));

}



TEST_F(IgnoreListTest_654, NormalOperation_StszTag_654) {

    Exiv2::DataBuf buf = CreateDataBuf("stsz", 4);

    EXPECT_TRUE(ignoreList(buf));

}



TEST_F(IgnoreListTest_654, NormalOperation_StcoTag_654) {

    Exiv2::DataBuf buf = CreateDataBuf("stco", 4);

    EXPECT_TRUE(ignoreList(buf));

}



TEST_F(IgnoreListTest_654, NormalOperation_CttsTag_654) {

    Exiv2::DataBuf buf = CreateDataBuf("ctts", 4);

    EXPECT_TRUE(ignoreList(buf));

}



TEST_F(IgnoreListTest_654, NormalOperation_StssTag_654) {

    Exiv2::DataBuf buf = CreateDataBuf("stss", 4);

    EXPECT_TRUE(ignoreList(buf));

}



TEST_F(IgnoreListTest_654, NormalOperation_SkipTag_654) {

    Exiv2::DataBuf buf = CreateDataBuf("skip", 4);

    EXPECT_TRUE(ignoreList(buf));

}



TEST_F(IgnoreListTest_654, NormalOperation_WideTag_654) {

    Exiv2::DataBuf buf = CreateDataBuf("wide", 4);

    EXPECT_TRUE(ignoreList(buf));

}



TEST_F(IgnoreListTest_654, NormalOperation_CmvdTag_654) {

    Exiv2::DataBuf buf = CreateDataBuf("cmvd", 4);

    EXPECT_TRUE(ignoreList(buf));

}



TEST_F(IgnoreListTest_654, BoundaryCondition_EmptyBuffer_654) {

    Exiv2::DataBuf buf;

    EXPECT_FALSE(ignoreList(buf));

}



TEST_F(IgnoreListTest_654, BoundaryCondition_ShortBuffer_654) {

    Exiv2::DataBuf buf = CreateDataBuf("md", 2);

    EXPECT_FALSE(ignoreList(buf));

}



TEST_F(IgnoreListTest_654, BoundaryCondition_LongerBuffer_MatchStart_654) {

    Exiv2::DataBuf buf = CreateDataBuf("mdatextra", 9);

    EXPECT_TRUE(ignoreList(buf));

}



TEST_F(IgnoreListTest_654, BoundaryCondition_LongerBuffer_NoMatch_654) {

    Exiv2::DataBuf buf = CreateDataBuf("mdtextra", 8);

    EXPECT_FALSE(ignoreList(buf));

}



TEST_F(IgnoreListTest_654, ExceptionalCase_NullPointer_654) {

    Exiv2::DataBuf buf(nullptr, 0);

    EXPECT_FALSE(ignoreList(buf));

}



TEST_F(IgnoreListTest_654, NormalOperation_CaseSensitive_MdatTagLowercase_654) {

    Exiv2::DataBuf buf = CreateDataBuf("mdat", 4);

    EXPECT_TRUE(ignoreList(buf));



    Exiv2::DataBuf bufLower = CreateDataBuf("MDAT", 4);

    EXPECT_FALSE(ignoreList(bufLower));

}
