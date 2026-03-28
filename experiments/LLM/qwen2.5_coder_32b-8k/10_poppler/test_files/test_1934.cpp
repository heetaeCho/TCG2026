#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/poppler/poppler/PageLabelInfo_p.h"

#include "./TestProjects/poppler/goo/GooString.h"

#include "./TestProjects/poppler/poppler/Error.h"



using namespace testing;



class PageLabelInfoTest_1934 : public ::testing::Test {

protected:

    GooString* gooString;

    void SetUp() override {

        gooString = new GooString();

    }



    void TearDown() override {

        delete gooString;

    }

};



TEST_F(PageLabelInfoTest_1934, NormalOperation_Uppercase_1934) {

    toRoman(1987, gooString, true);

    EXPECT_EQ(gooString->toStr(), "MCMLXXXVII");

}



TEST_F(PageLabelInfoTest_1934, NormalOperation_Lowercase_1934) {

    toRoman(1987, gooString, false);

    EXPECT_EQ(gooString->toStr(), "mcmlxxxvii");

}



TEST_F(PageLabelInfoTest_1934, BoundaryCondition_Min_1934) {

    toRoman(1, gooString, true);

    EXPECT_EQ(gooString->toStr(), "I");

}



TEST_F(PageLabelInfoTest_1934, BoundaryCondition_Max_1934) {

    toRoman(3999, gooString, true);

    EXPECT_EQ(gooString->toStr(), "MMMCMXCIX");

}



TEST_F(PageLabelInfoTest_1934, ExceptionalCase_OutOfBounds_1934) {

    EXPECT_THROW({

        try {

            toRoman(4000, gooString, true);

        } catch (const std::runtime_error& e) {

            EXPECT_EQ(e.what(), "Conversion to roman numerals of numbers >= 4000 not implemented");

            throw;

        }

    }, std::runtime_error);

}



TEST_F(PageLabelInfoTest_1934, ExceptionalCase_Zero_1934) {

    EXPECT_THROW({

        try {

            toRoman(0, gooString, true);

        } catch (const std::runtime_error& e) {

            EXPECT_EQ(e.what(), "Conversion to roman numerals of numbers >= 4000 not implemented");

            throw;

        }

    }, std::runtime_error);

}
