#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "TestProjects/poppler/poppler/Annot.h"

#include "TestProjects/poppler/poppler/PDFRectangle.h"



class AnnotCaretTest_852 : public ::testing::Test {

protected:

    std::unique_ptr<PDFDoc> doc;

    std::unique_ptr<PDFRectangle> rect;

    std::unique_ptr<AnnotCaret> annotCaret;



    void SetUp() override {

        doc = std::make_unique<PDFDoc>();

        rect = std::make_unique<PDFRectangle>(0, 0, 100, 100);

        annotCaret = std::make_unique<AnnotCaret>(doc.get(), rect.get());

    }

};



TEST_F(AnnotCaretTest_852, GetCaretRect_ReturnsCorrectPointer_852) {

    EXPECT_EQ(annotCaret->getCaretRect(), rect.get());

}



TEST_F(AnnotCaretTest_852, GetCaretRect_ReturnsNullWhenRectNotSet_852) {

    annotCaret.reset(new AnnotCaret(doc.get(), static_cast<PDFRectangle*>(nullptr)));

    EXPECT_EQ(annotCaret->getCaretRect(), nullptr);

}



// Assuming there are no observable exceptional cases or error states for getCaretRect

// as per the provided interface and constraints.
