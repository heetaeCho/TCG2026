#include <gtest/gtest.h>

#include "poppler-page.h"

#include "poppler-private.h"

#include "Form.h"

#include "Page.h"



using namespace std;



class PopplerPageTest : public ::testing::Test {

protected:

    void SetUp() override {

        // Initialize necessary objects and mocks if needed

        document = make_shared<PDFDoc>();

        page = new PopplerPage();

        page->page = make_unique<Page>(document.get(), 1, Object(ObjectType::nullObj), Ref(), nullptr);

        poppler_page = reinterpret_cast<PopplerPage*>(page);

    }



    void TearDown() override {

        g_list_free_full(poppler_page_get_form_field_mapping(poppler_page), [](gpointer data) { delete static_cast<PopplerFormFieldMapping*>(data); });

        delete page;

    }



    shared_ptr<PDFDoc> document;

    PopplerPage* poppler_page;

    Page* page;

};



TEST_F(PopplerPageTest, GetFormFieldMapping_ReturnsNull_WhenNoWidgetsExist_2454) {

    EXPECT_EQ(poppler_page_get_form_field_mapping(poppler_page), nullptr);

}



TEST_F(PopplerPageTest, GetFormFieldMapping_ReturnsNonEmptyList_WhenOneWidgetExists_2454) {

    auto form_widgets = make_unique<FormPageWidgets>();

    FormWidget* widget = new FormWidget(document.get(), nullptr, 1, Ref(), nullptr);

    form_widgets->addWidget(widget);

    page->page->setFormWidgets(move(form_widgets));



    GList *result = poppler_page_get_form_field_mapping(poppler_page);

    EXPECT_NE(result, nullptr);

    g_list_free_full(result, [](gpointer data) { delete static_cast<PopplerFormFieldMapping*>(data); });

}



TEST_F(PopplerPageTest, GetFormFieldMapping_ReturnsNonEmptyList_WhenMultipleWidgetsExist_2454) {

    auto form_widgets = make_unique<FormPageWidgets>();

    FormWidget* widget1 = new FormWidget(document.get(), nullptr, 1, Ref(), nullptr);

    FormWidget* widget2 = new FormWidget(document.get(), nullptr, 2, Ref(), nullptr);

    form_widgets->addWidget(widget1);

    form_widgets->addWidget(widget2);

    page->page->setFormWidgets(move(form_widgets));



    GList *result = poppler_page_get_form_field_mapping(poppler_page);

    EXPECT_NE(result, nullptr);

    EXPECT_EQ(g_list_length(result), 2);

    g_list_free_full(result, [](gpointer data) { delete static_cast<PopplerFormFieldMapping*>(data); });

}



TEST_F(PopplerPageTest, GetFormFieldMapping_CorrectlyMapsWidgetCoordinates_WhenWidgetsExist_2454) {

    auto form_widgets = make_unique<FormPageWidgets>();

    FormWidget* widget = new FormWidget(document.get(), nullptr, 1, Ref(), nullptr);

    double x1 = 10.0, y1 = 20.0, x2 = 30.0, y2 = 40.0;

    ON_CALL(*widget, getRect(testing::_, testing::_, testing::_, testing::_))

        .WillByDefault(testing::Invoke([&](double* px1, double* py1, double* px2, double* py2) {

            *px1 = x1; *py1 = y1; *px2 = x2; *py2 = y2;

        }));

    form_widgets->addWidget(widget);

    page->page->setFormWidgets(move(form_widgets));



    const PDFRectangle crop_box(5.0, 6.0, 7.0, 8.0);

    EXPECT_CALL(*page->page, getCropBox()).WillRepeatedly(testing::Return(&crop_box));



    GList *result = poppler_page_get_form_field_mapping(poppler_page);

    ASSERT_NE(result, nullptr);

    PopplerFormFieldMapping* mapping = static_cast<PopplerFormFieldMapping*>(g_list_nth_data(result, 0));

    EXPECT_DOUBLE_EQ(mapping->area.x1, x1 - crop_box.x1);

    EXPECT_DOUBLE_EQ(mapping->area.y1, y1 - crop_box.y1);

    EXPECT_DOUBLE_EQ(mapping->area.x2, x2 - crop_box.x1);

    EXPECT_DOUBLE_EQ(mapping->area.y2, y2 - crop_box.y1);



    g_list_free_full(result, [](gpointer data) { delete static_cast<PopplerFormFieldMapping*>(data); });

}



TEST_F(PopplerPageTest, GetFormFieldMapping_ReturnsNull_WhenFormsIsNull_2454) {

    page->page->setFormWidgets(nullptr);

    EXPECT_EQ(poppler_page_get_form_field_mapping(poppler_page), nullptr);

}
