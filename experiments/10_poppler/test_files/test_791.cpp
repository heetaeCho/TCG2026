#include <gtest/gtest.h>

#include "Annot.h"

#include "AnnotBorder.h"



// Test fixture for Annot class tests with TEST_ID 791

class AnnotTest_791 : public ::testing::Test {

protected:

    PDFDoc* doc;

    PDFRectangle rect;

    std::unique_ptr<Annot> annot;



    void SetUp() override {

        doc = new PDFDoc();

        annot.reset(new Annot(doc, &rect));

    }



    void TearDown() override {

        delete doc;

    }

};



// Test that getBorder returns a non-null pointer if border is set_791

TEST_F(AnnotTest_791, GetBorder_ReturnsNonNullPointer_791) {

    std::unique_ptr<AnnotBorder> border(new AnnotBorder());

    annot->setBorder(std::move(border));

    EXPECT_NE(annot->getBorder(), nullptr);

}



// Test that getBorder returns a null pointer if border is not set_791

TEST_F(AnnotTest_791, GetBorder_ReturnsNullPointer_791) {

    EXPECT_EQ(annot->getBorder(), nullptr);

}



// Test setting and getting the border with valid data_791

TEST_F(AnnotTest_791, SetAndGetBorder_ValidData_791) {

    std::unique_ptr<AnnotBorder> new_border(new AnnotBorder());

    annot->setBorder(std::move(new_border));

    EXPECT_NE(annot->getBorder(), nullptr);

}



// Test setting the border with null data_791

TEST_F(AnnotTest_791, SetBorder_NullData_791) {

    std::unique_ptr<AnnotBorder> new_border(nullptr);

    annot->setBorder(std::move(new_border));

    EXPECT_EQ(annot->getBorder(), nullptr);

}
