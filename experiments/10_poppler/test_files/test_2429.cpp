#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-page.h"

#include "poppler-private.h"



// Mock class for PDFDoc to fulfill dependencies

class MockPDFDoc : public PDFDoc {

public:

    MOCK_METHOD(bool, isOk, (), (const));

};



TEST_F(PopplerPageTest_2429, GetDuration_NormalOperation_2429) {

    // Arrange

    MockPDFDoc mock_doc;

    Ref page_ref(1, 0);

    auto attrs = std::make_unique<PageAttrs>();

    Page* internal_page = new Page(&mock_doc, 1, Object(), page_ref, std::move(attrs));

    PopplerPage page;

    page.page.reset(internal_page);



    // Set the duration value directly in the internal Page object for testing

    internal_page->duration = 2.5;



    // Act & Assert

    EXPECT_EQ(poppler_page_get_duration(&page), 2.5);

}



TEST_F(PopplerPageTest_2429, GetDuration_PageIsNull_2429) {

    // Arrange

    PopplerPage* null_page = nullptr;



    // Act & Assert

    EXPECT_EQ(poppler_page_get_duration(null_page), -1);

}



TEST_F(PopplerPageTest_2429, GetDuration_DurationIsZero_2429) {

    // Arrange

    MockPDFDoc mock_doc;

    Ref page_ref(1, 0);

    auto attrs = std::make_unique<PageAttrs>();

    Page* internal_page = new Page(&mock_doc, 1, Object(), page_ref, std::move(attrs));

    PopplerPage page;

    page.page.reset(internal_page);



    // Set the duration value directly in the internal Page object for testing

    internal_page->duration = 0.0;



    // Act & Assert

    EXPECT_EQ(poppler_page_get_duration(&page), 0.0);

}



TEST_F(PopplerPageTest_2429, GetDuration_DurationIsNegative_2429) {

    // Arrange

    MockPDFDoc mock_doc;

    Ref page_ref(1, 0);

    auto attrs = std::make_unique<PageAttrs>();

    Page* internal_page = new Page(&mock_doc, 1, Object(), page_ref, std::move(attrs));

    PopplerPage page;

    page.page.reset(internal_page);



    // Set the duration value directly in the internal Page object for testing

    internal_page->duration = -1.0;



    // Act & Assert

    EXPECT_EQ(poppler_page_get_duration(&page), -1.0);

}



TEST_F(PopplerPageTest_2429, GetDuration_DurationIsMaxDouble_2429) {

    // Arrange

    MockPDFDoc mock_doc;

    Ref page_ref(1, 0);

    auto attrs = std::make_unique<PageAttrs>();

    Page* internal_page = new Page(&mock_doc, 1, Object(), page_ref, std::move(attrs));

    PopplerPage page;

    page.page.reset(internal_page);



    // Set the duration value directly in the internal Page object for testing

    internal_page->duration = std::numeric_limits<double>::max();



    // Act & Assert

    EXPECT_EQ(poppler_page_get_duration(&page), std::numeric_limits<double>::max());

}
