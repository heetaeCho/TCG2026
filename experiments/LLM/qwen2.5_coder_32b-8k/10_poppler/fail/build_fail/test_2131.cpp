#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-annot.h"

#include "poppler-private.h"



using namespace testing;



class PopplerAnnotInkTest : public Test {

protected:

    void SetUp() override {

        annot = static_cast<PopplerAnnotInk*>(g_malloc0(sizeof(PopplerAnnotInk)));

        page = static_cast<_Page*>(g_malloc0(sizeof(_Page)));

    }



    void TearDown() override {

        g_free(annot);

        g_free(page);

    }



    PopplerAnnotInk* annot;

    _Page* page;

};



TEST_F(PopplerAnnotInkTest_2131, SetInkList_NormalOperation_2131) {

    // Arrange

    PopplerPoint points[] = {{1.0, 1.0}, {2.0, 2.0}};

    PopplerPath path = {points, 2};

    PopplerPath* ink_list[] = {&path};

    gsize n_paths = 1;



    // Act

    poppler_annot_ink_set_ink_list(annot, ink_list, n_paths);



    // Assert

    // Since the implementation is a black box, we cannot assert internal state.

    // We can only verify that no errors occur and possibly mock external interactions if needed.

}



TEST_F(PopplerAnnotInkTest_2131, SetInkList_EmptyPathList_2131) {

    // Arrange

    PopplerPath* ink_list[] = {};

    gsize n_paths = 0;



    // Act

    poppler_annot_ink_set_ink_list(annot, ink_list, n_paths);



    // Assert

    // Since the implementation is a black box, we cannot assert internal state.

}



TEST_F(PopplerAnnotInkTest_2131, SetInkList_NullPath_2131) {

    // Arrange

    PopplerPath* ink_list[] = {nullptr};

    gsize n_paths = 1;



    // Act & Assert

    EXPECT_DEATH(poppler_annot_ink_set_ink_list(annot, ink_list, n_paths), ".*");

}



TEST_F(PopplerAnnotInkTest_2131, SetInkList_PageIsNull_2131) {

    // Arrange

    PopplerPoint points[] = {{1.0, 1.0}, {2.0, 2.0}};

    PopplerPath path = {points, 2};

    PopplerPath* ink_list[] = {&path};

    gsize n_paths = 1;



    // Mock the function to return null page

    EXPECT_CALL(*this, _poppler_annot_get_cropbox_and_page(POPPLER_ANNOT(annot), &page))

        .WillOnce(Return(nullptr));



    // Act

    poppler_annot_ink_set_ink_list(annot, ink_list, n_paths);



    // Assert

    // Since the implementation is a black box, we cannot assert internal state.

}



TEST_F(PopplerAnnotInkTest_2131, SetInkList_BoundaryConditions_2131) {

    // Arrange

    PopplerPoint points[] = {{G_MAXDOUBLE, G_MAXDOUBLE}, {0, 0}};

    PopplerPath path = {points, 2};

    PopplerPath* ink_list[] = {&path};

    gsize n_paths = 1;



    // Act

    poppler_annot_ink_set_ink_list(annot, ink_list, n_paths);



    // Assert

    // Since the implementation is a black box, we cannot assert internal state.

}



TEST_F(PopplerAnnotInkTest_2131, SetInkList_LargeNumberOfPoints_2131) {

    // Arrange

    const gsize n_points = 100;

    PopplerPoint points[n_points];

    for (gsize i = 0; i < n_points; ++i) {

        points[i] = {static_cast<double>(i), static_cast<double>(i)};

    }

    PopplerPath path = {points, n_points};

    PopplerPath* ink_list[] = {&path};

    gsize n_paths = 1;



    // Act

    poppler_annot_ink_set_ink_list(annot, ink_list, n_paths);



    // Assert

    // Since the implementation is a black box, we cannot assert internal state.

}



TEST_F(PopplerAnnotInkTest_2131, SetInkList_NegativeCoordinates_2131) {

    // Arrange

    PopplerPoint points[] = {{-1.0, -1.0}, {-2.0, -2.0}};

    PopplerPath path = {points, 2};

    PopplerPath* ink_list[] = {&path};

    gsize n_paths = 1;



    // Act

    poppler_annot_ink_set_ink_list(annot, ink_list, n_paths);



    // Assert

    // Since the implementation is a black box, we cannot assert internal state.

}

```


