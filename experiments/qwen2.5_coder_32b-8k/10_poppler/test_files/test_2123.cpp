#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-annot.h"

#include "poppler-private.h"



// Mock class for Annot to verify interactions

class MockAnnot : public Annot {

public:

    MOCK_METHOD(void, setBorder, (std::unique_ptr<AnnotBorderArray>), (override));

};



TEST_F(PopplerAnnotTest_2123, SetBorderWidth_NormalOperation_2123) {

    auto mock_annot = std::make_shared<MockAnnot>();

    PopplerAnnot poppler_annot;

    poppler_annot.annot = mock_annot;



    EXPECT_CALL(*mock_annot, setBorder(::testing::_)).Times(1);



    double width = 5.0;

    poppler_annot_set_border_width(&poppler_annot, width);

}



TEST_F(PopplerAnnotTest_2123, SetBorderWidth_ZeroWidth_2123) {

    auto mock_annot = std::make_shared<MockAnnot>();

    PopplerAnnot poppler_annot;

    poppler_annot.annot = mock_annot;



    EXPECT_CALL(*mock_annot, setBorder(::testing::_)).Times(1);



    double width = 0.0;

    poppler_annot_set_border_width(&poppler_annot, width);

}



TEST_F(PopplerAnnotTest_2123, SetBorderWidth_NegativeWidth_2123) {

    auto mock_annot = std::make_shared<MockAnnot>();

    PopplerAnnot poppler_annot;

    poppler_annot.annot = mock_annot;



    EXPECT_CALL(*mock_annot, setBorder(::testing::_)).Times(1);



    double width = -5.0;

    poppler_annot_set_border_width(&poppler_annot, width);

}



TEST_F(PopplerAnnotTest_2123, SetBorderWidth_VeryLargeWidth_2123) {

    auto mock_annot = std::make_shared<MockAnnot>();

    PopplerAnnot poppler_annot;

    poppler_annot.annot = mock_annot;



    EXPECT_CALL(*mock_annot, setBorder(::testing::_)).Times(1);



    double width = 1e20;

    poppler_annot_set_border_width(&poppler_annot, width);

}



TEST_F(PopplerAnnotTest_2123, SetBorderWidth_NullPopplerAnnot_2123) {

    EXPECT_NO_THROW(poppler_annot_set_border_width(nullptr, 5.0));

}
