#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-annot.h"

#include "poppler-private.h"



class PopplerAnnotTest_2063 : public ::testing::Test {

protected:

    std::shared_ptr<Annot> mock_annot;

    PopplerAnnot poppler_annot;



    void SetUp() override {

        mock_annot = std::make_shared<Annot>();

        poppler_annot.annot = mock_annot;

    }

};



TEST_F(PopplerAnnotTest_2063, GetContents_ReturnsNullptrWhenContentsEmpty_2063) {

    EXPECT_CALL(*mock_annot, getContents()).WillOnce(::testing::Return(std::make_shared<GooString>("")));

    gchar *contents = poppler_annot_get_contents(&poppler_annot);

    ASSERT_EQ(contents, nullptr);

}



TEST_F(PopplerAnnotTest_2063, GetContents_ReturnsNullptrWhenContentsIsNull_2063) {

    EXPECT_CALL(*mock_annot, getContents()).WillOnce(::testing::Return(nullptr));

    gchar *contents = poppler_annot_get_contents(&poppler_annot);

    ASSERT_EQ(contents, nullptr);

}



TEST_F(PopplerAnnotTest_2063, GetContents_ReturnsUtf8StringWhenContentsNotEmpty_2063) {

    std::string test_string = "Sample Content";

    EXPECT_CALL(*mock_annot, getContents()).WillOnce(::testing::Return(std::make_shared<GooString>(test_string.c_str())));

    gchar *contents = poppler_annot_get_contents(&poppler_annot);

    ASSERT_STREQ(contents, test_string.c_str());

    g_free(contents); // Free the allocated memory

}



TEST_F(PopplerAnnotTest_2063, GetContents_ReturnsNullptrForInvalidPopplerAnnot_2063) {

    PopplerAnnot *invalid_poppler_annot = nullptr;

    gchar *contents = poppler_annot_get_contents(invalid_poppler_annot);

    ASSERT_EQ(contents, nullptr);

}
