#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <poppler-document.h>



// Mocking GValue for testing purposes

class MockGValue {

public:

    MOCK_METHOD1(set_string, void(const gchar*));

    MOCK_METHOD1(take_string, void(gchar*));

    MOCK_METHOD1(set_uint, void(guint));

    MOCK_METHOD1(set_int, void(gint));

    MOCK_METHOD2(set_enum, void(GType, gint));

    MOCK_METHOD2(set_flags, void(GType, guint));

    MOCK_METHOD2(take_boxed, void(GType, gpointer));

};



// Mocking GParamSpec for testing purposes

class MockGParamSpec {

public:

};



// Mocking GObject for testing purposes

class MockGObject {

public:

    MOCK_METHOD4(get_property, void(guint, GValue*, GParamSpec*));

};



// Mocking PopplerDocument for testing purposes

class MockPopplerDocument : public PopplerDocument {

public:

    using PopplerDocument::PopplerDocument;



    MOCK_METHOD0(get_title, gchar*());

    MOCK_METHOD0(get_pdf_version_string, gchar*());

    MOCK_METHOD2(get_pdf_version, void(guint*, guint*));

    MOCK_METHOD0(get_author, gchar*());

    MOCK_METHOD0(get_subject, gchar*());

    MOCK_METHOD0(get_keywords, gchar*());

    MOCK_METHOD0(get_creator, gchar*());

    MOCK_METHOD0(get_producer, gchar*());

    MOCK_METHOD0(get_creation_date, gint());

    MOCK_METHOD0(get_modification_date, gint());

    MOCK_METHOD0(is_linearized, gboolean());

    MOCK_METHOD0(get_page_layout, PopplerPageLayout());

    MOCK_METHOD0(get_page_mode, PopplerPageMode());

    MOCK_METHOD0(get_print_scaling, PopplerPrintScaling());

    MOCK_METHOD0(get_print_duplex, PopplerPrintDuplex());

    MOCK_METHOD0(get_print_n_copies, gint());

    MOCK_METHOD0(get_permissions, PopplerPermissions());

    MOCK_METHOD0(get_pdf_subtype, PopplerPdfSubtype());

    MOCK_METHOD0(get_pdf_subtype_string, gchar*());

    MOCK_METHOD0(get_pdf_part, PopplerPdfPart());

    MOCK_METHOD0(get_pdf_conformance, PopplerPdfConformance());

    MOCK_METHOD0(get_metadata, gchar*());

    MOCK_METHOD0(get_creation_date_time, gpointer());

    MOCK_METHOD0(get_modification_date_time, gpointer());

};



// Test Fixture

class PopplerDocumentTest_2209 : public ::testing::Test {

protected:

    MockPopplerDocument* mock_document;

    MockGObject* mock_object;

    GValue mock_value;

    GParamSpec mock_pspec;



    void SetUp() override {

        mock_document = new MockPopplerDocument();

        mock_object = new MockGObject();

    }



    void TearDown() override {

        delete mock_document;

        delete mock_object;

    }

};



// Test Normal Operation

TEST_F(PopplerDocumentTest_2209, GetTitle_ReturnsValidString_2209) {

    EXPECT_CALL(*mock_document, get_title()).WillOnce(::testing::Return(g_strdup("Sample Title")));

    poppler_document_get_property(G_OBJECT(mock_object), PROP_TITLE, &mock_value, &mock_pspec);

}



TEST_F(PopplerDocumentTest_2209, GetFormat_ReturnsValidString_2209) {

    EXPECT_CALL(*mock_document, get_pdf_version_string()).WillOnce(::testing::Return(g_strdup("1.7")));

    poppler_document_get_property(G_OBJECT(mock_object), PROP_FORMAT, &mock_value, &mock_pspec);

}



TEST_F(PopplerDocumentTest_2209, GetFormatMajor_ReturnsValidVersion_2209) {

    EXPECT_CALL(*mock_document, get_pdf_version(::testing::NotNull(), ::testing::_)).WillOnce(::testing::SetArgReferee<0>(1));

    poppler_document_get_property(G_OBJECT(mock_object), PROP_FORMAT_MAJOR, &mock_value, &mock_pspec);

}



TEST_F(PopplerDocumentTest_2209, GetFormatMinor_ReturnsValidVersion_2209) {

    EXPECT_CALL(*mock_document, get_pdf_version(::testing::_, ::testing::NotNull())).WillOnce(::testing::SetArgReferee<1>(7));

    poppler_document_get_property(G_OBJECT(mock_object), PROP_FORMAT_MINOR, &mock_value, &mock_pspec);

}



TEST_F(PopplerDocumentTest_2209, GetAuthor_ReturnsValidString_2209) {

    EXPECT_CALL(*mock_document, get_author()).WillOnce(::testing::Return(g_strdup("John Doe")));

    poppler_document_get_property(G_OBJECT(mock_object), PROP_AUTHOR, &mock_value, &mock_pspec);

}



TEST_F(PopplerDocumentTest_2209, GetSubject_ReturnsValidString_2209) {

    EXPECT_CALL(*mock_document, get_subject()).WillOnce(::testing::Return(g_strdup("Sample Subject")));

    poppler_document_get_property(G_OBJECT(mock_object), PROP_SUBJECT, &mock_value, &mock_pspec);

}



TEST_F(PopplerDocumentTest_2209, GetKeywords_ReturnsValidString_2209) {

    EXPECT_CALL(*mock_document, get_keywords()).WillOnce(::testing::Return(g_strdup("keyword1 keyword2")));

    poppler_document_get_property(G_OBJECT(mock_object), PROP_KEYWORDS, &mock_value, &mock_pspec);

}



TEST_F(PopplerDocumentTest_2209, GetCreator_ReturnsValidString_2209) {

    EXPECT_CALL(*mock_document, get_creator()).WillOnce(::testing::Return(g_strdup("Creator Name")));

    poppler_document_get_property(G_OBJECT(mock_object), PROP_CREATOR, &mock_value, &mock_pspec);

}



TEST_F(PopplerDocumentTest_2209, GetProducer_ReturnsValidString_2209) {

    EXPECT_CALL(*mock_document, get_producer()).WillOnce(::testing::Return(g_strdup("Producer Name")));

    poppler_document_get_property(G_OBJECT(mock_object), PROP_PRODUCER, &mock_value, &mock_pspec);

}



TEST_F(PopplerDocumentTest_2209, GetCreationDate_ReturnsValidInt_2209) {

    EXPECT_CALL(*mock_document, get_creation_date()).WillOnce(::testing::Return(1633075200));

    poppler_document_get_property(G_OBJECT(mock_object), PROP_CREATION_DATE, &mock_value, &mock_pspec);

}



TEST_F(PopplerDocumentTest_2209, GetModificationDate_ReturnsValidInt_2209) {

    EXPECT_CALL(*mock_document, get_modification_date()).WillOnce(::testing::Return(1635753600));

    poppler_document_get_property(G_OBJECT(mock_object), PROP_MOD_DATE, &mock_value, &mock_pspec);

}



TEST_F(PopplerDocumentTest_2209, IsLinearized_ReturnsTrue_2209) {

    EXPECT_CALL(*mock_document, is_linearized()).WillOnce(::testing::Return(TRUE));

    poppler_document_get_property(G_OBJECT(mock_object), PROP_LINEARIZED, &mock_value, &mock_pspec);

}



TEST_F(PopplerDocumentTest_2209, GetPageLayout_ReturnsValidEnum_2209) {

    EXPECT_CALL(*mock_document, get_page_layout()).WillOnce(::testing::Return(POPPLER_PAGE_LAYOUT_SINGLE_PAGE));

    poppler_document_get_property(G_OBJECT(mock_object), PROP_PAGE_LAYOUT, &mock_value, &mock_pspec);

}



TEST_F(PopplerDocumentTest_2209, GetPageMode_ReturnsValidEnum_2209) {

    EXPECT_CALL(*mock_document, get_page_mode()).WillOnce(::testing::Return(POPPLER_PAGE_MODE_USE_NONE));

    poppler_document_get_property(G_OBJECT(mock_object), PROP_PAGE_MODE, &mock_value, &mock_pspec);

}



TEST_F(PopplerDocumentTest_2209, GetPrintScaling_ReturnsValidEnum_2209) {

    EXPECT_CALL(*mock_document, get_print_scaling()).WillOnce(::testing::Return(POPPLER_PRINT_SCALING_APP_DEFAULT));

    poppler_document_get_property(G_OBJECT(mock_object), PROP_PRINT_SCALING, &mock_value, &mock_pspec);

}



TEST_F(PopplerDocumentTest_2209, GetPrintDuplex_ReturnsValidEnum_2209) {

    EXPECT_CALL(*mock_document, get_print_duplex()).WillOnce(::testing::Return(POPPLER_PRINT_DUPLEX_SIMPLEX));

    poppler_document_get_property(G_OBJECT(mock_object), PROP_PRINT_DUPLEX, &mock_value, &mock_pspec);

}



TEST_F(PopplerDocumentTest_2209, GetPrintNCopies_ReturnsValidInt_2209) {

    EXPECT_CALL(*mock_document, get_print_n_copies()).WillOnce(::testing::Return(1));

    poppler_document_get_property(G_OBJECT(mock_object), PROP_PRINT_N_COPIES, &mock_value, &mock_pspec);

}



TEST_F(PopplerDocumentTest_2209, GetPermissions_ReturnsValidFlags_2209) {

    EXPECT_CALL(*mock_document, get_permissions()).WillOnce(::testing::Return(POPPLER_PERMISSIONS_OK_TO_PRINT));

    poppler_document_get_property(G_OBJECT(mock_object), PROP_PERMISSIONS, &mock_value, &mock_pspec);

}



TEST_F(PopplerDocumentTest_2209, GetSubtype_ReturnsValidEnum_2209) {

    EXPECT_CALL(*mock_document, get_pdf_subtype()).WillOnce(::testing::Return(POPPLER_SUBTYPE_STANDARD));

    poppler_document_get_property(G_OBJECT(mock_object), PROP_SUBTYPE, &mock_value, &mock_pspec);

}



TEST_F(PopplerDocumentTest_2209, GetSubtypeString_ReturnsValidString_2209) {

    EXPECT_CALL(*mock_document, get_pdf_subtype_string()).WillOnce(::testing::Return(g_strdup("Standard")));

    poppler_document_get_property(G_OBJECT(mock_object), PROP_SUBTYPE_STRING, &mock_value, &mock_pspec);

}



TEST_F(PopplerDocumentTest_2209, GetSubtypePart_ReturnsValidEnum_2209) {

    EXPECT_CALL(*mock_document, get_pdf_part()).WillOnce(::testing::Return(POPPLER_PART_XFA_FULL));

    poppler_document_get_property(G_OBJECT(mock_object), PROP_SUBTYPE_PART, &mock_value, &mock_pspec);

}



TEST_F(PopplerDocumentTest_2209, GetSubtypeConf_ReturnsValidEnum_2209) {

    EXPECT_CALL(*mock_document, get_pdf_conformance()).WillOnce(::testing::Return(POPPLER_CONFORMANCE_PDF_X1_A));

    poppler_document_get_property(G_OBJECT(mock_object), PROP_SUBTYPE_CONF, &mock_value, &mock_pspec);

}



TEST_F(PopplerDocumentTest_2209, GetMetadata_ReturnsValidString_2209) {

    EXPECT_CALL(*mock_document, get_metadata()).WillOnce(::testing::Return(g_strdup("Sample Metadata")));

    poppler_document_get_property(G_OBJECT(mock_object), PROP_METADATA, &mock_value, &mock_pspec);

}



TEST_F(PopplerDocumentTest_2209, GetCreationDateTime_ReturnsValidBoxed_2209) {

    EXPECT_CALL(*mock_document, get_creation_date_time()).WillOnce(::testing::Return(reinterpret_cast<gpointer>(1)));

    poppler_document_get_property(G_OBJECT(mock_object), PROP_CREATION_DATETIME, &mock_value, &mock_pspec);

}



TEST_F(PopplerDocumentTest_2209, GetModificationDateTime_ReturnsValidBoxed_2209) {

    EXPECT_CALL(*mock_document, get_modification_date_time()).WillOnce(::testing::Return(reinterpret_cast<gpointer>(1)));

    poppler_document_get_property(G_OBJECT(mock_object), PROP_MOD_DATETIME, &mock_value, &mock_pspec);

}



// Test Boundary Conditions

TEST_F(PopplerDocumentTest_2209, GetTitle_ReturnsEmptyString_2209) {

    EXPECT_CALL(*mock_document, get_title()).WillOnce(::testing::Return(g_strdup("")));

    poppler_document_get_property(G_OBJECT(mock_object), PROP_TITLE, &mock_value, &mock_pspec);

}



TEST_F(PopplerDocumentTest_2209, GetFormat_ReturnsEmptyString_2209) {

    EXPECT_CALL(*mock_document, get_pdf_version_string()).WillOnce(::testing::Return(g_strdup("")));

    poppler_document_get_property(G_OBJECT(mock_object), PROP_FORMAT, &mock_value, &mock_pspec);

}



TEST_F(PopplerDocumentTest_2209, GetAuthor_ReturnsEmptyString_2209) {

    EXPECT_CALL(*mock_document, get_author()).WillOnce(::testing::Return(g_strdup("")));

    poppler_document_get_property(G_OBJECT(mock_object), PROP_AUTHOR, &mock_value, &mock_pspec);

}



TEST_F(PopplerDocumentTest_2209, GetSubject_ReturnsEmptyString_2209) {

    EXPECT_CALL(*mock_document, get_subject()).WillOnce(::testing::Return(g_strdup("")));

    poppler_document_get_property(G_OBJECT(mock_object), PROP_SUBJECT, &mock_value, &mock_pspec);

}



TEST_F(PopplerDocumentTest_2209, GetKeywords_ReturnsEmptyString_2209) {

    EXPECT_CALL(*mock_document, get_keywords()).WillOnce(::testing::Return(g_strdup("")));

    poppler_document_get_property(G_OBJECT(mock_object), PROP_KEYWORDS, &mock_value, &mock_pspec);

}



TEST_F(PopplerDocumentTest_2209, GetCreator_ReturnsEmptyString_2209) {

    EXPECT_CALL(*mock_document, get_creator()).WillOnce(::testing::Return(g_strdup("")));

    poppler_document_get_property(G_OBJECT(mock_object), PROP_CREATOR, &mock_value, &mock_pspec);

}



TEST_F(PopplerDocumentTest_2209, GetProducer_ReturnsEmptyString_2209) {

    EXPECT_CALL(*mock_document, get_producer()).WillOnce(::testing::Return(g_strdup("")));

    poppler_document_get_property(G_OBJECT(mock_object), PROP_PRODUCER, &mock_value, &mock_pspec);

}



TEST_F(PopplerDocumentTest_2209, GetCreationDate_ReturnsZero_2209) {

    EXPECT_CALL(*mock_document, get_creation_date()).WillOnce(::testing::Return(0));

    poppler_document_get_property(G_OBJECT(mock_object), PROP_CREATION_DATE, &mock_value, &mock_pspec);

}



TEST_F(PopplerDocumentTest_2209, GetModificationDate_ReturnsZero_2209) {

    EXPECT_CALL(*mock_document, get_modification_date()).WillOnce(::testing::Return(0));

    poppler_document_get_property(G_OBJECT(mock_object), PROP_MOD_DATE, &mock_value, &mock_pspec);

}



TEST_F(PopplerDocumentTest_2209, GetSubtypeString_ReturnsEmptyString_2209) {

    EXPECT_CALL(*mock_document, get_pdf_subtype_string()).WillOnce(::testing::Return(g_strdup("")));

    poppler_document_get_property(G_OBJECT(mock_object), PROP_SUBTYPE_STRING, &mock_value, &mock_pspec);

}



TEST_F(PopplerDocumentTest_2209, GetMetadata_ReturnsEmptyString_2209) {

    EXPECT_CALL(*mock_document, get_metadata()).WillOnce(::testing::Return(g_strdup("")));

    poppler_document_get_property(G_OBJECT(mock_object), PROP_METADATA, &mock_value, &mock_pspec);

}



// Test Exceptional or Error Cases

TEST_F(PopplerDocumentTest_2209, GetPropertyWithInvalidPropId_LogsWarning_2209) {

    EXPECT_CALL(*mock_object, get_property(::testing::Ne(PROP_0), ::testing::_, ::testing::_))

        .WillOnce([](guint prop_id, GValue* value, GParamSpec* pspec){

            G_OBJECT_WARN_INVALID_PROPERTY_ID(G_OBJECT(mock_object), prop_id, pspec);

        });

    poppler_document_get_property(G_OBJECT(mock_object), 9999, &mock_value, &mock_pspec);

}
