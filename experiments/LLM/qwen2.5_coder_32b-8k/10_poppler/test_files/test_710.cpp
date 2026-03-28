#include <gtest/gtest.h>

#include "poppler/Page.h"

#include "poppler/PageAttrs.h"



class PageTest_710 : public ::testing::Test {

protected:

    PDFDoc* doc;

    int num;

    Object pageDict;

    Ref pageRef;

    std::unique_ptr<PageAttrs> attrs;



    void SetUp() override {

        // Initialize necessary objects for testing

        doc = new PDFDoc();

        num = 1; // Example page number

        pageDict.initNull(); // Placeholder for actual page dictionary object

        pageRef.set(1, 0); // Example reference

        attrs = std::make_unique<PageAttrs>(nullptr, nullptr); // Example attributes

    }



    void TearDown() override {

        delete doc;

    }

};



TEST_F(PageTest_710, GetBleedBox_ReturnsNonNullPointer_710) {

    Page page(doc, num, std::move(pageDict), pageRef, std::move(attrs));

    EXPECT_NE(nullptr, page.getBleedBox());

}



TEST_F(PageTest_710, GetBleedBox_ConsistentAcrossCalls_710) {

    Page page(doc, num, std::move(pageDict), pageRef, std::move(attrs));

    const PDFRectangle* bleedBox1 = page.getBleedBox();

    const PDFRectangle* bleedBox2 = page.getBleedBox();

    EXPECT_EQ(bleedBox1, bleedBox2);

}



// Assuming getBleedBox returns a valid pointer with specific values can be tested

// if those values are observable or known from external sources.

// For now, we test for non-null and consistency.



TEST_F(PageTest_710, GetBleedBox_NotModifiedByOtherMethods_710) {

    Page page(doc, num, std::move(pageDict), pageRef, std::move(attrs));

    const PDFRectangle* bleedBoxBefore = page.getBleedBox();

    // Call some other methods that might affect the state of the object

    page.getMediaBox(); 

    page.getCropBox();

    const PDFRectangle* bleedBoxAfter = page.getBleedBox();

    EXPECT_EQ(bleedBoxBefore, bleedBoxAfter);

}
