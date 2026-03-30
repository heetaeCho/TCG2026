#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-page.h"

#include "poppler-private.h"



// Mocking the Page class to control its behavior in tests

class MockPage : public PopplerPage {

public:

    MOCK_METHOD(Annots*, getAnnots, (), (const));

    MOCK_METHOD(void, poppler_page_get_size, (double* width, double* height), (const));

    MOCK_METHOD(const PDFRectangle*, getCropBox, (), (const));

    MOCK_METHOD(int, getRotate, (), (const));



    MockPage() : PopplerPage(nullptr, 0, Object(), Ref(), std::make_unique<PageAttrs>()) {}

};



TEST_F(MockPage, poppler_page_get_annot_mapping_ReturnsNullForNoAnnotations_2455) {

    // Arrange

    MockPage page;

    EXPECT_CALL(page, getAnnots()).WillOnce(testing::Return(nullptr));



    // Act

    GList* result = poppler_page_get_annot_mapping(&page);



    // Assert

    ASSERT_EQ(result, nullptr);

}



TEST_F(MockPage, poppler_page_get_annot_mapping_ReturnsCorrectNumberOfMappings_2455) {

    // Arrange

    MockPage page;

    auto annots = std::make_unique<Annots>();

    for (int i = 0; i < 3; ++i) {

        annots->getAnnots().push_back(std::make_shared<Annot>(Annot::typeText));

    }

    EXPECT_CALL(page, getAnnots()).WillRepeatedly(testing::Return(annots.get()));

    double width = 100.0;

    double height = 200.0;

    EXPECT_CALL(page, poppler_page_get_size(testing::_, testing::_))

        .WillOnce(testing::DoAll(

            testing::SetArgReferee<0>(width),

            testing::SetArgReferee<1>(height)));

    PDFRectangle crop_box{10.0, 20.0, 90.0, 180.0};

    EXPECT_CALL(page, getCropBox()).WillRepeatedly(testing::Return(&crop_box));

    EXPECT_CALL(page, getRotate()).WillRepeatedly(testing::Return(0));



    // Act

    GList* result = poppler_page_get_annot_mapping(&page);



    // Assert

    ASSERT_EQ(g_list_length(result), 3);

    g_list_free_full(result, (GDestroyNotify)poppler_annot_mapping_free);

}



TEST_F(MockPage, poppler_page_get_annot_mapping_HandlesRotation90Correctly_2455) {

    // Arrange

    MockPage page;

    auto annots = std::make_unique<Annots>();

    PDFRectangle rect{10.0, 10.0, 30.0, 30.0};

    auto text_annot = std::make_shared<Annot>(Annot::typeText);

    text_annot->setRect(rect);

    annots->getAnnots().push_back(text_annot);

    EXPECT_CALL(page, getAnnots()).WillRepeatedly(testing::Return(annots.get()));

    double width = 200.0;

    double height = 100.0;

    EXPECT_CALL(page, poppler_page_get_size(testing::_, testing::_))

        .WillOnce(testing::DoAll(

            testing::SetArgReferee<0>(width),

            testing::SetArgReferee<1>(height)));

    PDFRectangle crop_box{0.0, 0.0, 200.0, 100.0};

    EXPECT_CALL(page, getCropBox()).WillRepeatedly(testing::Return(&crop_box));

    EXPECT_CALL(page, getRotate()).WillRepeatedly(testing::Return(90));



    // Act

    GList* result = poppler_page_get_annot_mapping(&page);



    // Assert

    ASSERT_EQ(g_list_length(result), 1);

    PopplerAnnotMapping* mapping = (PopplerAnnotMapping*)result->data;

    EXPECT_FLOAT_EQ(mapping->area.x1, 20.0); // rect.y2 - crop_box->y1

    EXPECT_FLOAT_EQ(mapping->area.y1, 70.0); // height - (rect.x1 + annot_height)

    EXPECT_FLOAT_EQ(mapping->area.x2, 40.0); // rect.y2 + annot_width

    EXPECT_FLOAT_EQ(mapping->area.y2, 90.0); // height - rect.x1



    g_list_free_full(result, (GDestroyNotify)poppler_annot_mapping_free);

}



TEST_F(MockPage, poppler_page_get_annot_mapping_HandlesRotation180Correctly_2455) {

    // Arrange

    MockPage page;

    auto annots = std::make_unique<Annots>();

    PDFRectangle rect{10.0, 10.0, 30.0, 30.0};

    auto text_annot = std::make_shared<Annot>(Annot::typeText);

    text_annot->setRect(rect);

    annots->getAnnots().push_back(text_annot);

    EXPECT_CALL(page, getAnnots()).WillRepeatedly(testing::Return(annots.get()));

    double width = 200.0;

    double height = 100.0;

    EXPECT_CALL(page, poppler_page_get_size(testing::_, testing::_))

        .WillOnce(testing::DoAll(

            testing::SetArgReferee<0>(width),

            testing::SetArgReferee<1>(height)));

    PDFRectangle crop_box{0.0, 0.0, 200.0, 100.0};

    EXPECT_CALL(page, getCropBox()).WillRepeatedly(testing::Return(&crop_box));

    EXPECT_CALL(page, getRotate()).WillRepeatedly(testing::Return(180));



    // Act

    GList* result = poppler_page_get_annot_mapping(&page);



    // Assert

    ASSERT_EQ(g_list_length(result), 1);

    PopplerAnnotMapping* mapping = (PopplerAnnotMapping*)result->data;

    EXPECT_FLOAT_EQ(mapping->area.x1, 160.0); // width - rect.x2

    EXPECT_FLOAT_EQ(mapping->area.y1, 40.0); // height - rect.y2

    EXPECT_FLOAT_EQ(mapping->area.x2, 180.0); // MIN(mapping->area.x1 + annot_width, width)

    EXPECT_FLOAT_EQ(mapping->area.y2, 60.0); // MAX(0, mapping->area.y2 - annot_height)



    g_list_free_full(result, (GDestroyNotify)poppler_annot_mapping_free);

}



TEST_F(MockPage, poppler_page_get_annot_mapping_HandlesRotation270Correctly_2455) {

    // Arrange

    MockPage page;

    auto annots = std::make_unique<Annots>();

    PDFRectangle rect{10.0, 10.0, 30.0, 30.0};

    auto text_annot = std::make_shared<Annot>(Annot::typeText);

    text_annot->setRect(rect);

    annots->getAnnots().push_back(text_annot);

    EXPECT_CALL(page, getAnnots()).WillRepeatedly(testing::Return(annots.get()));

    double width = 200.0;

    double height = 100.0;

    EXPECT_CALL(page, poppler_page_get_size(testing::_, testing::_))

        .WillOnce(testing::DoAll(

            testing::SetArgReferee<0>(width),

            testing::SetArgReferee<1>(height)));

    PDFRectangle crop_box{0.0, 0.0, 200.0, 100.0};

    EXPECT_CALL(page, getCropBox()).WillRepeatedly(testing::Return(&crop_box));

    EXPECT_CALL(page, getRotate()).WillRepeatedly(testing::Return(270));



    // Act

    GList* result = poppler_page_get_annot_mapping(&page);



    // Assert

    ASSERT_EQ(g_list_length(result), 1);

    PopplerAnnotMapping* mapping = (PopplerAnnotMapping*)result->data;

    EXPECT_FLOAT_EQ(mapping->area.x1, 80.0); // width - rect.y2

    EXPECT_FLOAT_EQ(mapping->area.y1, 30.0); // rect.x1

    EXPECT_FLOAT_EQ(mapping->area.x2, 100.0); // MIN(mapping->area.x1 + annot_width, width)

    EXPECT_FLOAT_EQ(mapping->area.y2, 50.0); // MAX(0, mapping->area.y2 - annot_height)



    g_list_free_full(result, (GDestroyNotify)poppler_annot_mapping_free);

}



TEST_F(MockPage, poppler_page_get_annot_mapping_HandlesNoRotateFlagCorrectly_2455) {

    // Arrange

    MockPage page;

    auto annots = std::make_unique<Annots>();

    PDFRectangle rect{10.0, 10.0, 30.0, 30.0};

    auto text_annot = std::make_shared<Annot>(Annot::typeText);

    text_annot->setRect(rect);

    text_annot->setFlags(Annot::flagNoRotate);

    annots->getAnnots().push_back(text_annot);

    EXPECT_CALL(page, getAnnots()).WillRepeatedly(testing::Return(annots.get()));

    double width = 200.0;

    double height = 100.0;

    EXPECT_CALL(page, poppler_page_get_size(testing::_, testing::_))

        .WillOnce(testing::DoAll(

            testing::SetArgReferee<0>(width),

            testing::SetArgReferee<1>(height)));

    PDFRectangle crop_box{0.0, 0.0, 200.0, 100.0};

    EXPECT_CALL(page, getCropBox()).WillRepeatedly(testing::Return(&crop_box));

    EXPECT_CALL(page, getRotate()).WillRepeatedly(testing::Return(90));



    // Act

    GList* result = poppler_page_get_annot_mapping(&page);



    // Assert

    ASSERT_EQ(g_list_length(result), 1);

    PopplerAnnotMapping* mapping = (PopplerAnnotMapping*)result->data;

    EXPECT_FLOAT_EQ(mapping->area.x1, 20.0); // rect.y2 - crop_box->y1

    EXPECT_FLOAT_EQ(mapping->area.y1, 70.0); // height - (rect.x1 + annot_height)

    EXPECT_FLOAT_EQ(mapping->area.x2, 40.0); // rect.y2 + annot_width

    EXPECT_FLOAT_EQ(mapping->area.y2, 90.0); // height - rect.x1



    g_list_free_full(result, (GDestroyNotify)poppler_annot_mapping_free);

}



TEST_F(MockPage, poppler_page_get_annot_mapping_HandlesUnsupportedRotationCorrectly_2455) {

    // Arrange

    MockPage page;

    auto annots = std::make_unique<Annots>();

    PDFRectangle rect{10.0, 10.0, 30.0, 30.0};

    auto text_annot = std::make_shared<Annot>(Annot::typeText);

    text_annot->setRect(rect);

    annots->getAnnots().push_back(text_annot);

    EXPECT_CALL(page, getAnnots()).WillRepeatedly(testing::Return(annots.get()));

    double width = 100.0;

    double height = 200.0;

    EXPECT_CALL(page, poppler_page_get_size(testing::_, testing::_))

        .WillOnce(testing::DoAll(

            testing::SetArgReferee<0>(width),

            testing::SetArgReferee<1>(height)));

    PDFRectangle crop_box{10.0, 20.0, 90.0, 180.0};

    EXPECT_CALL(page, getCropBox()).WillRepeatedly(testing::Return(&crop_box));

    EXPECT_CALL(page, getRotate()).WillRepeatedly(testing::Return(45)); // Unsupported rotation



    // Act

    GList* result = poppler_page_get_annot_mapping(&page);



    // Assert

    ASSERT_EQ(g_list_length(result), 1);

    PopplerAnnotMapping* mapping = (PopplerAnnotMapping*)result->data;

    EXPECT_FLOAT_EQ(mapping->area.x1, 0.0); // rect.x1 - crop_box->x1

    EXPECT_FLOAT_EQ(mapping->area.y1, 0.0); // rect.y1 - crop_box->y1

    EXPECT_FLOAT_EQ(mapping->area.x2, 20.0); // rect.x2 - crop_box->x1

    EXPECT_FLOAT_EQ(mapping->area.y2, 10.0); // rect.y2 - crop_box->y1



    g_list_free_full(result, (GDestroyNotify)poppler_annot_mapping_free);

}



TEST_F(MockPage, poppler_page_get_annot_mapping_HandlesVariousAnnotationTypesCorrectly_2455) {

    // Arrange

    MockPage page;

    auto annots = std::make_unique<Annots>();

    PDFRectangle rect{10.0, 10.0, 30.0, 30.0};

    annots->getAnnots().push_back(std::make_shared<Annot>(Annot::typeText));

    annots->getAnnots().push_back(std::make_shared<Annot>(Annot::typeInk));

    annots->getAnnots().push_back(std::make_shared<Annot>(Annot::typeFreeText));

    annots->getAnnots().push_back(std::make_shared<Annot>(Annot::typeFileAttachment));

    annots->getAnnots().push_back(std::make_shared<Annot>(Annot::typeMovie));

    auto screen_annot = std::make_shared<Annot>(Annot::typeScreen);

    screen_annot->setDocument(nullptr); // Assuming a way to set document as nullptr for testing

    annots->getAnnots().push_back(screen_annot);

    annots->getAnnots().push_back(std::make_shared<Annot>(Annot::typeLine));

    annots->getAnnots().push_back(std::make_shared<Annot>(Annot::typeSquare));

    annots->getAnnots().push_back(std::make_shared<Annot>(Annot::typeCircle));

    for (auto& annot : annots->getAnnots()) {

        annot->setRect(rect);

    }

    EXPECT_CALL(page, getAnnots()).WillRepeatedly(testing::Return(annots.get()));

    double width = 100.0;

    double height = 200.0;

    EXPECT_CALL(page, poppler_page_get_size(testing::_, testing::_))

        .WillOnce(testing::DoAll(

            testing::SetArgReferee<0>(width),

            testing::SetArgReferee<1>(height)));

    PDFRectangle crop_box{0.0, 0.0, 100.0, 200.0};

    EXPECT_CALL(page, getCropBox()).WillRepeatedly(testing::Return(&crop_box));

    EXPECT_CALL(page, getRotate()).WillRepeatedly(testing::Return(0));



    // Act

    GList* result = poppler_page_get_annot_mapping(&page);



    // Assert

    ASSERT_EQ(g_list_length(result), 10);

    g_list_free_full(result, (GDestroyNotify)poppler_annot_mapping_free);

}
