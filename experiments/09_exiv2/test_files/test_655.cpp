#include <gtest/gtest.h>

#include "exiv2/types.hpp"



using namespace Exiv2;

using namespace Exiv2::Internal;



// Helper function to create a DataBuf with specific content

DataBuf createDataBuf(const std::string& content) {

    return DataBuf(reinterpret_cast<const byte*>(content.data()), content.size());

}



TEST(dataIgnoreListTest_655, NormalOperation_Moov_655) {

    DataBuf buf = createDataBuf("moov");

    EXPECT_TRUE(dataIgnoreList(buf));

}



TEST(dataIgnoreListTest_655, NormalOperation_Mdia_655) {

    DataBuf buf = createDataBuf("mdia");

    EXPECT_TRUE(dataIgnoreList(buf));

}



TEST(dataIgnoreListTest_655, NormalOperation_Minf_655) {

    DataBuf buf = createDataBuf("minf");

    EXPECT_TRUE(dataIgnoreList(buf));

}



TEST(dataIgnoreListTest_655, NormalOperation_Dinf_655) {

    DataBuf buf = createDataBuf("dinf");

    EXPECT_TRUE(dataIgnoreList(buf));

}



TEST(dataIgnoreListTest_655, NormalOperation_Alis_655) {

    DataBuf buf = createDataBuf("alis");

    EXPECT_TRUE(dataIgnoreList(buf));

}



TEST(dataIgnoreListTest_655, NormalOperation_Stbl_655) {

    DataBuf buf = createDataBuf("stbl");

    EXPECT_TRUE(dataIgnoreList(buf));

}



TEST(dataIgnoreListTest_655, NormalOperation_Cmov_655) {

    DataBuf buf = createDataBuf("cmov");

    EXPECT_TRUE(dataIgnoreList(buf));

}



TEST(dataIgnoreListTest_655, NormalOperation_Meta_655) {

    DataBuf buf = createDataBuf("meta");

    EXPECT_TRUE(dataIgnoreList(buf));

}



TEST(dataIgnoreListTest_655, BoundaryCondition_EmptyString_655) {

    DataBuf buf = createDataBuf("");

    EXPECT_FALSE(dataIgnoreList(buf));

}



TEST(dataIgnoreListTest_655, BoundaryCondition_ShorterThanFourBytes_655) {

    DataBuf buf = createDataBuf("mov");

    EXPECT_FALSE(dataIgnoreList(buf));

}



TEST(dataIgnoreListTest_655, BoundaryCondition_LongerThanFourBytes_655) {

    DataBuf buf = createDataBuf("moovi");

    EXPECT_FALSE(dataIgnoreList(buf));

}



TEST(dataIgnoreListTest_655, ExceptionalCase_DifferentString_655) {

    DataBuf buf = createDataBuf("abcd");

    EXPECT_FALSE(dataIgnoreList(buf));

}
