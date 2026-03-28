#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-page.h"

#include "poppler-private.h"



using namespace testing;



class PopplerPageTest_2462 : public Test {

protected:

    std::shared_ptr<PopplerAnnot> mock_annot;

    MockedPDFDoc* mock_doc; // Assuming MockedPDFDoc is a mock class for PDFDoc

    PopplerPage* poppler_page;



    void SetUp() override {

        mock_annot = std::make_shared<PopplerAnnot>();

        mock_annot->annot = std::make_shared<Annot>(); // Assuming Annot has a default constructor



        mock_doc = new MockedPDFDoc(); // Assuming MockedPDFDoc is a mock class for PDFDoc

        poppler_page = reinterpret_cast<PopplerPage*>(g_slice_alloc0(sizeof(PopplerPage)));

        poppler_page->page = std::make_shared<Page>(mock_doc, 1, Object(), Ref(), PageAttrs()).release();

    }



    void TearDown() override {

        g_slice_free1(sizeof(PopplerPage), poppler_page);

        delete mock_doc;

    }

};



TEST_F(PopplerPageTest_2462, RemoveAnnot_Success_2462) {

    EXPECT_CALL(*mock_doc, removeAnnot(mock_annot->annot)).Times(1);



    poppler_page_remove_annot(poppler_page, mock_annot.get());

}



TEST_F(PopplerPageTest_2462, RemoveAnnot_NullPage_2462) {

    PopplerPage* null_page = nullptr;

    EXPECT_DEATH_IF_SUPPORTED({poppler_page_remove_annot(null_page, mock_annot.get());}, "");

}



TEST_F(PopplerPageTest_2462, RemoveAnnot_NullAnnot_2462) {

    PopplerAnnot* null_annot = nullptr;

    EXPECT_DEATH_IF_SUPPORTED({poppler_page_remove_annot(poppler_page, null_annot);}, "");

}

```



In this code:

- We define a test fixture `PopplerPageTest_2462` that sets up and tears down the necessary objects for testing.

- We write three test cases:

  - `RemoveAnnot_Success_2462`: Verifies that `poppler_page_remove_annot` calls the internal `removeAnnot` method on the `Page` object when given valid arguments.

  - `RemoveAnnot_NullPage_2462`: Ensures that passing a null `PopplerPage*` causes the function to abort, using `EXPECT_DEATH_IF_SUPPORTED`.

  - `RemoveAnnot_NullAnnot_2462`: Ensures that passing a null `PopplerAnnot*` causes the function to abort, using `EXPECT_DEATH_IF_SUPPORTED`.


