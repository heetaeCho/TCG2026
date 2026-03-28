#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/poppler/glib/poppler-page.cc"

#include "./TestProjects/poppler/poppler/Page.h"



using namespace testing;



class PopplerPageTest_2424 : public ::testing::Test {

protected:

    void SetUp() override {

        document = reinterpret_cast<PopplerDocument*>(g_object_new(POPPLER_TYPE_DOCUMENT, nullptr));

        page = new Page(nullptr, 0, std::move(Object()), Ref(), std::make_unique<PageAttrs>());

        index = 1;

    }



    void TearDown() override {

        g_object_unref(document);

        delete page;

    }



    PopplerDocument *document;

    Page *page;

    int index;

};



TEST_F(PopplerPageTest_2424, NewPageValidDocument_2424) {

    PopplerPage* poppler_page = _poppler_page_new(document, page, index);

    ASSERT_NE(poppler_page, nullptr);

    EXPECT_EQ(poppler_page->document, document);

    EXPECT_EQ(poppler_page->page, page);

    EXPECT_EQ(poppler_page->index, index);

    g_object_unref(poppler_page);

}



TEST_F(PopplerPageTest_2424, NewPageInvalidDocument_2424) {

    PopplerPage* poppler_page = _poppler_page_new(nullptr, page, index);

    EXPECT_EQ(poppler_page, nullptr);

}



TEST_F(PopplerPageTest_2424, NewPageBoundaryIndexZero_2424) {

    int boundary_index = 0;

    PopplerPage* poppler_page = _poppler_page_new(document, page, boundary_index);

    ASSERT_NE(poppler_page, nullptr);

    EXPECT_EQ(poppler_page->index, boundary_index);

    g_object_unref(poppler_page);

}



TEST_F(PopplerPageTest_2424, NewPageBoundaryIndexNegative_2424) {

    int boundary_index = -1;

    PopplerPage* poppler_page = _poppler_page_new(document, page, boundary_index);

    ASSERT_NE(poppler_page, nullptr);

    EXPECT_EQ(poppler_page->index, boundary_index);

    g_object_unref(poppler_page);

}
