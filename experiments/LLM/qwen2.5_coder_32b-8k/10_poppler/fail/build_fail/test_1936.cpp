#include <gtest/gtest.h>

#include "TestProjects/poppler/poppler/PageLabelInfo_p.h"

#include "TestProjects/poppler/goo/GooString.h"



class PageLabelInfoTest_1936 : public ::testing::Test {

protected:

    GooString *str;



    void SetUp() override {

        str = new GooString();

    }



    void TearDown() override {

        delete str;

    }

};



TEST_F(PageLabelInfoTest_1936, ConvertToLatinUppercaseNormal_1936) {

    PageLabelInfo_p::toLatin(1, str, true);

    EXPECT_EQ(str->toStr(), "A");



    PageLabelInfo_p::toLatin(27, str, true);

    EXPECT_EQ(str->toStr(), "AA");



    PageLabelInfo_p::toLatin(53, str, true);

    EXPECT_EQ(str->toStr(), "BA");

}



TEST_F(PageLabelInfoTest_1936, ConvertToLatinLowercaseNormal_1936) {

    PageLabelInfo_p::toLatin(1, str, false);

    EXPECT_EQ(str->toStr(), "a");



    PageLabelInfo_p::toLatin(27, str, false);

    EXPECT_EQ(str->toStr(), "aa");



    PageLabelInfo_p::toLatin(53, str, false);

    EXPECT_EQ(str->toStr(), "ba");

}



TEST_F(PageLabelInfoTest_1936, ConvertToLatinBoundaryConditions_1936) {

    PageLabelInfo_p::toLatin(0, str, true); // Edge case

    EXPECT_EQ(str->toStr(), "");



    PageLabelInfo_p::toLatin(26, str, true);

    EXPECT_EQ(str->toStr(), "Z");



    PageLabelInfo_p::toLatin(52, str, true);

    EXPECT_EQ(str->toStr(), "YZ");

}



TEST_F(PageLabelInfoTest_1936, ConvertToLatinLargeNumber_1936) {

    PageLabelInfo_p::toLatin(704, str, true); // Larger number

    EXPECT_EQ(str->toStr(), "AAZ");



    PageLabelInfo_p::toLatin(18279, str, false);

    EXPECT_EQ(str->toStr(), "zzz");

}
