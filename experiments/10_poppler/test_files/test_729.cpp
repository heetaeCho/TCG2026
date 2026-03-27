#include <gtest/gtest.h>

#include "TestProjects/poppler/poppler/Page.h"



class PageTest_729 : public ::testing::Test {

protected:

    // Mock dependencies if needed here



    PDFDoc* mockDoc;

    Ref mockPageRef;

    std::unique_ptr<PageAttrs> mockAttrs;



    void SetUp() override {

        mockDoc = nullptr; // Assuming no specific setup is required for the doc pointer in tests

        mockPageRef.num = 1;

        mockPageRef.gen = 0;

        mockAttrs = nullptr; // Assuming no specific setup is required for attrs

    }



    Page* createPageWithStandaloneFields(bool hasFields) {

        auto page = new Page(mockDoc, 1, Object(), mockPageRef, std::move(mockAttrs));

        if (hasFields) {

            page->standaloneFields.push_back(std::make_unique<FormField>());

        }

        return page;

    }



    void TearDown() override {

        // Cleanup if needed

    }

};



TEST_F(PageTest_729, HasStandaloneFields_ReturnsTrueWhenFieldsExist_729) {

    Page* page = createPageWithStandaloneFields(true);

    EXPECT_TRUE(page->hasStandaloneFields());

    delete page;

}



TEST_F(PageTest_729, HasStandaloneFields_ReturnsFalseWhenNoFieldsExist_729) {

    Page* page = createPageWithStandaloneFields(false);

    EXPECT_FALSE(page->hasStandaloneFields());

    delete page;

}
