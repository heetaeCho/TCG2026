#include <gtest/gtest.h>

#include "poppler/Annot.h"



class AnnotWidgetTest_862 : public ::testing::Test {

protected:

    PDFDoc* doc;

    Object dictObject;

    Object obj;

    AnnotWidget* annotWidget;



    void SetUp() override {

        // Initialize the necessary objects for testing

        doc = new PDFDoc();

        annotWidget = new AnnotWidget(doc, std::move(dictObject), &obj);

    }



    void TearDown() override {

        delete annotWidget;

        delete doc;

    }

};



TEST_F(AnnotWidgetTest_862, GetParentReturnsNonNullPointer_862) {

    // Test that getParent returns a non-null pointer

    EXPECT_NE(nullptr, annotWidget->getParent());

}



// Assuming there are no boundary conditions or exceptional/error cases directly observable from the interface for getParent()

```


