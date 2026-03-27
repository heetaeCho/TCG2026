#include <gtest/gtest.h>

#include "poppler/glib/poppler-annot.h"

#include "poppler/poppler/PDFRectangle.h"



// Mocking dependencies if needed (none in this case)



class PopplerAnnotTest_2054 : public ::testing::Test {

protected:

    void SetUp() override {

        // Initialize any necessary setup for the tests

        doc = new _PopplerDocument();

        rect = new _PopplerRectangle{0, 0, 100, 100};

        start = new _PopplerPoint{};

        end = new _PopplerPoint{};

    }



    void TearDown() override {

        // Clean up after each test

        delete doc;

        delete rect;

        delete start;

        delete end;

    }



    _PopplerDocument *doc;

    _PopplerRectangle *rect;

    _PopplerPoint *start;

    _PopplerPoint *end;

};



TEST_F(PopplerAnnotTest_2054, CreateLineAnnotation_NormalOperation_2054) {

    PopplerAnnot *annot = poppler_annot_line_new(doc, rect, start, end);

    EXPECT_NE(annot, nullptr);

}



TEST_F(PopplerAnnotTest_2054, CreateLineAnnotation_BoundaryConditions_2054) {

    _PopplerRectangle zeroRect{0, 0, 0, 0};

    PopplerAnnot *annot = poppler_annot_line_new(doc, &zeroRect, start, end);

    EXPECT_NE(annot, nullptr);



    _PopplerRectangle negativeRect{-100, -100, 0, 0};

    annot = poppler_annot_line_new(doc, &negativeRect, start, end);

    EXPECT_NE(annot, nullptr);

}



// Assuming no exceptional cases are observable through the interface for this function

```


