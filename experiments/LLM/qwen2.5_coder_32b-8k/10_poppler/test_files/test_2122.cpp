#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/poppler/glib/poppler-annot.cc"

#include "./TestProjects/poppler/poppler/Annot.h"

#include "./TestProjects/poppler/glib/poppler-private.h"



using namespace testing;



class PopplerAnnotTest_2122 : public Test {

protected:

    std::shared_ptr<Annot> annot;

    std::shared_ptr<AnnotBorder> border;

    PopplerAnnot poppler_annot;



    void SetUp() override {

        annot = std::make_shared<Annot>();

        border = std::make_shared<AnnotBorder>();

        poppler_annot.annot = annot;

        ON_CALL(*border, getWidth()).WillByDefault(Return(0.0));

        EXPECT_CALL(*annot, getBorder()).WillRepeatedly(Return(border.get()));

    }

};



TEST_F(PopplerAnnotTest_2122, GetBorderWidth_ReturnsZeroWhenNoBorder_2122) {

    border.reset(); // No border

    double width = -1.0;

    gboolean result = poppler_annot_get_border_width(&poppler_annot, &width);

    EXPECT_FALSE(result);

    EXPECT_DOUBLE_EQ(width, 0.0);

}



TEST_F(PopplerAnnotTest_2122, GetBorderWidth_ReturnsCorrectWidthWhenBorderExists_2122) {

    double expected_width = 3.5;

    EXPECT_CALL(*border, getWidth()).WillOnce(Return(expected_width));

    double width = -1.0;

    gboolean result = poppler_annot_get_border_width(&poppler_annot, &width);

    EXPECT_TRUE(result);

    EXPECT_DOUBLE_EQ(width, expected_width);

}



TEST_F(PopplerAnnotTest_2122, GetBorderWidth_SetsZeroWhenNoBorder_2122) {

    border.reset(); // No border

    double width = -1.0;

    poppler_annot_get_border_width(&poppler_annot, &width);

    EXPECT_DOUBLE_EQ(width, 0.0);

}



TEST_F(PopplerAnnotTest_2122, GetBorderWidth_DoesNotModifyWidthWhenBorderExists_2122) {

    double initial_width = 4.0;

    EXPECT_CALL(*border, getWidth()).WillOnce(Return(5.0));

    poppler_annot_get_border_width(&poppler_annot, &initial_width);

    EXPECT_DOUBLE_EQ(initial_width, 5.0);

}
