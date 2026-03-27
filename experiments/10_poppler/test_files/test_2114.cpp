#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-annot.cc"

#include "poppler-page.h"

#include "poppler-private.h"



class PopplerAnnotTest : public ::testing::Test {

protected:

    void SetUp() override {

        poppler_annot = new _PopplerAnnot();

        poppler_color = new _PopplerColor();

        poppler_annot->annot = std::make_shared<Annot>();

    }



    void TearDown() override {

        delete poppler_annot;

        delete poppler_color;

    }



    _PopplerAnnot* poppler_annot;

    _PopplerColor* poppler_color;

};



TEST_F(PopplerAnnotTest_NormalOperation_2114, SetInteriorColor_ValidColor_2114) {

    poppler_color->red = 255;

    poppler_color->green = 0;

    poppler_color->blue = 0;



    EXPECT_NO_THROW(poppler_annot_geometry_set_interior_color(reinterpret_cast<PopplerAnnot*>(poppler_annot), reinterpret_cast<PopplerColor*>(poppler_color)));

}



TEST_F(PopplerAnnotTest_BoundaryConditions_2114, SetInteriorColor_ZeroValues_2114) {

    poppler_color->red = 0;

    poppler_color->green = 0;

    poppler_color->blue = 0;



    EXPECT_NO_THROW(poppler_annot_geometry_set_interior_color(reinterpret_cast<PopplerAnnot*>(poppler_annot), reinterpret_cast<PopplerColor*>(poppler_color)));

}



TEST_F(PopplerAnnotTest_BoundaryConditions_2114, SetInteriorColor_MaxValues_2114) {

    poppler_color->red = 65535;

    poppler_color->green = 65535;

    poppler_color->blue = 65535;



    EXPECT_NO_THROW(poppler_annot_geometry_set_interior_color(reinterpret_cast<PopplerAnnot*>(poppler_annot), reinterpret_cast<PopplerColor*>(poppler_color)));

}



TEST_F(PopplerAnnotTest_ErrorCases_2114, SetInteriorColor_NullAnnot_2114) {

    EXPECT_THROW(poppler_annot_geometry_set_interior_color(nullptr, reinterpret_cast<PopplerColor*>(poppler_color)), std::exception);

}



TEST_F(PopplerAnnotTest_ErrorCases_2114, SetInteriorColor_NullColor_2114) {

    EXPECT_THROW(poppler_annot_geometry_set_interior_color(reinterpret_cast<PopplerAnnot*>(poppler_annot), nullptr), std::exception);

}
