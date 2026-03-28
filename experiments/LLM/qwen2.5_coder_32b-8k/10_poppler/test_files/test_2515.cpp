#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <gtk/gtk.h>

#include "poppler-document.h"



using ::testing::_;

using ::testing::NiceMock;

using ::testing::Return;



class MockPopplerDocument : public PopplerDocument {

public:

    MOCK_METHOD(void, get_property, (const char *property_name, gpointer value), (override));

    MOCK_METHOD(gboolean, poppler_document_get_id, (gchar **perm_id, gchar **up_id), (override));

};



class InfoWidgetTest_2515 : public ::testing::Test {

protected:

    void SetUp() override {

        document = new NiceMock<MockPopplerDocument>();

        gtk_init(nullptr, nullptr);

    }



    void TearDown() override {

        delete document;

    }



    MockPopplerDocument* document;

};



TEST_F(InfoWidgetTest_2515, CreateWidgetReturnsNonnullptr_2515) {

    GtkWidget *widget = pgd_info_create_widget(document);

    EXPECT_NE(widget, nullptr);

}



TEST_F(InfoWidgetTest_2515, DocumentPropertiesAreDisplayed_2515) {

    EXPECT_CALL(*document, get_property("title", _)).Times(1);

    EXPECT_CALL(*document, get_property("format", _)).Times(1);

    EXPECT_CALL(*document, get_property("author", _)).Times(1);

    EXPECT_CALL(*document, get_property("subject", _)).Times(1);

    EXPECT_CALL(*document, get_property("keywords", _)).Times(1);

    EXPECT_CALL(*document, get_property("creation-datetime", _)).Times(1);

    EXPECT_CALL(*document, get_property("mod-datetime", _)).Times(1);

    EXPECT_CALL(*document, get_property("creator", _)).Times(1);

    EXPECT_CALL(*document, get_property("producer", _)).Times(1);

    EXPECT_CALL(*document, get_property("linearized", _)).Times(1);

    EXPECT_CALL(*document, get_property("page-mode", _)).Times(1);

    EXPECT_CALL(*document, get_property("page-layout", _)).Times(1);

    EXPECT_CALL(*document, get_property("permissions", _)).Times(1);

    EXPECT_CALL(*document, get_property("viewer-preferences", _)).Times(1);

    EXPECT_CALL(*document, get_property("metadata", _)).Times(1);



    GtkWidget *widget = pgd_info_create_widget(document);

    EXPECT_NE(widget, nullptr);

}



TEST_F(InfoWidgetTest_2515, DocumentIdsAreDisplayedWhenAvailable_2515) {

    gchar perm_id[] = "permanent-id";

    gchar up_id[] = "update-id";



    EXPECT_CALL(*document, poppler_document_get_id(_, _)).WillOnce(DoAll(SetArgPointee<0>(perm_id), SetArgPointee<1>(up_id), Return(TRUE)));



    GtkWidget *widget = pgd_info_create_widget(document);

    EXPECT_NE(widget, nullptr);

}



TEST_F(InfoWidgetTest_2515, DocumentIdsAreNotDisplayedWhenNotAvailable_2515) {

    EXPECT_CALL(*document, poppler_document_get_id(_, _)).WillOnce(Return(FALSE));



    GtkWidget *widget = pgd_info_create_widget(document);

    EXPECT_NE(widget, nullptr);

}
