#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <poppler-document.h>



class PopplerDocumentTest_2211 : public ::testing::Test {

protected:

    void SetUp() override {

        document = POPPLER_DOCUMENT(g_object_new(POPPLER_TYPE_DOCUMENT, nullptr));

    }



    void TearDown() override {

        g_clear_object(&document);

    }



    PopplerDocument* document;

};



TEST_F(PopplerDocumentTest_2211, TitleCanBeSetAndGet_2211) {

    const char* testTitle = "Sample Document";

    g_object_set(document, "title", testTitle, nullptr);



    gchar* title;

    g_object_get(document, "title", &title, nullptr);

    EXPECT_STREQ(title, testTitle);

    g_free(title);

}



TEST_F(PopplerDocumentTest_2211, FormatIsReadable_2211) {

    gchar* format;

    g_object_get(document, "format", &format, nullptr);

    ASSERT_NE(format, nullptr);

    g_free(format);

}



TEST_F(PopplerDocumentTest_2211, FormatMajorAndMinorAreReadable_2211) {

    guint major, minor;

    g_object_get(document, "format-major", &major, "format-minor", &minor, nullptr);

    EXPECT_LE(major, 99); // Assuming a reasonable upper bound for major version

    EXPECT_LE(minor, 99); // Assuming a reasonable upper bound for minor version

}



TEST_F(PopplerDocumentTest_2211, AuthorCanBeSetAndGet_2211) {

    const char* testAuthor = "John Doe";

    g_object_set(document, "author", testAuthor, nullptr);



    gchar* author;

    g_object_get(document, "author", &author, nullptr);

    EXPECT_STREQ(author, testAuthor);

    g_free(author);

}



TEST_F(PopplerDocumentTest_2211, SubjectCanBeSetAndGet_2211) {

    const char* testSubject = "Sample Subject";

    g_object_set(document, "subject", testSubject, nullptr);



    gchar* subject;

    g_object_get(document, "subject", &subject, nullptr);

    EXPECT_STREQ(subject, testSubject);

    g_free(subject);

}



TEST_F(PopplerDocumentTest_2211, KeywordsCanBeSetAndGet_2211) {

    const char* testKeywords = "keyword1 keyword2";

    g_object_set(document, "keywords", testKeywords, nullptr);



    gchar* keywords;

    g_object_get(document, "keywords", &keywords, nullptr);

    EXPECT_STREQ(keywords, testKeywords);

    g_free(keywords);

}



TEST_F(PopplerDocumentTest_2211, CreatorCanBeSetAndGet_2211) {

    const char* testCreator = "LibreOffice Writer";

    g_object_set(document, "creator", testCreator, nullptr);



    gchar* creator;

    g_object_get(document, "creator", &creator, nullptr);

    EXPECT_STREQ(creator, testCreator);

    g_free(creator);

}



TEST_F(PopplerDocumentTest_2211, ProducerCanBeSetAndGet_2211) {

    const char* testProducer = "LibreOffice PDF Export";

    g_object_set(document, "producer", testProducer, nullptr);



    gchar* producer;

    g_object_get(document, "producer", &producer, nullptr);

    EXPECT_STREQ(producer, testProducer);

    g_free(producer);

}



TEST_F(PopplerDocumentTest_2211, CreationDateCanBeSetAndGet_2211) {

    int testCreationDate = 1633075200; // Example timestamp

    g_object_set(document, "creation-date", testCreationDate, nullptr);



    int creationDate;

    g_object_get(document, "creation-date", &creationDate, nullptr);

    EXPECT_EQ(creationDate, testCreationDate);

}



TEST_F(PopplerDocumentTest_2211, ModDateCanBeSetAndGet_2211) {

    int testModDate = 1635753600; // Example timestamp

    g_object_set(document, "mod-date", testModDate, nullptr);



    int modDate;

    g_object_get(document, "mod-date", &modDate, nullptr);

    EXPECT_EQ(modDate, testModDate);

}



TEST_F(PopplerDocumentTest_2211, LinearizedIsReadable_2211) {

    gboolean linearized;

    g_object_get(document, "linearized", &linearized, nullptr);

    EXPECT_TRUE(linearized == TRUE || linearized == FALSE);

}



TEST_F(PopplerDocumentTest_2211, PageLayoutIsReadable_2211) {

    PopplerPageLayout pageLayout;

    g_object_get(document, "page-layout", &pageLayout, nullptr);

    EXPECT_GE(pageLayout, POPPLER_PAGE_LAYOUT_UNSET);

    EXPECT_LE(pageLayout, POPPLER_N_PAGE_LAYOUTS - 1);

}



TEST_F(PopplerDocumentTest_2211, PageModeIsReadable_2211) {

    PopplerPageMode pageMode;

    g_object_get(document, "page-mode", &pageMode, nullptr);

    EXPECT_GE(pageMode, POPPLER_PAGE_MODE_UNSET);

    EXPECT_LE(pageMode, POPPLER_N_PAGE_MODES - 1);

}



TEST_F(PopplerDocumentTest_2211, ViewerPreferencesIsReadable_2211) {

    PopplerViewerPreferences viewerPreferences;

    g_object_get(document, "viewer-preferences", &viewerPreferences, nullptr);

    EXPECT_TRUE(viewerPreferences >= POPPLER_VIEWER_PREFERENCES_UNSET);

}



TEST_F(PopplerDocumentTest_2211, PrintScalingIsReadable_2211) {

    PopplerPrintScaling printScaling;

    g_object_get(document, "print-scaling", &printScaling, nullptr);

    EXPECT_TRUE(printScaling >= POPPLER_PRINT_SCALING_APP_DEFAULT && printScaling <= POPPLER_PRINT_SCALING_NONE);

}



TEST_F(PopplerDocumentTest_2211, PrintDuplexIsReadable_2211) {

    PopplerPrintDuplex printDuplex;

    g_object_get(document, "print-duplex", &printDuplex, nullptr);

    EXPECT_TRUE(printDuplex >= POPPLER_PRINT_DUPLEX_NONE && printDuplex <= POPPLER_PRINT_DUPLEX_TWO_SIDED_LONG_EDGE);

}



TEST_F(PopplerDocumentTest_2211, PrintNCopiesIsReadable_2211) {

    int printNCopies;

    g_object_get(document, "print-n-copies", &printNCopies, nullptr);

    EXPECT_GE(printNCopies, 1);

}



TEST_F(PopplerDocumentTest_2211, PermissionsIsReadable_2211) {

    PopplerPermissions permissions;

    g_object_get(document, "permissions", &permissions, nullptr);

    EXPECT_TRUE(permissions >= POPPLER_PERMISSIONS_UNSET);

}



TEST_F(PopplerDocumentTest_2211, SubtypeIsReadable_2211) {

    PopplerPdfSubtype subtype;

    g_object_get(document, "subtype", &subtype, nullptr);

    EXPECT_TRUE(subtype >= POPPLER_PDF_SUBTYPE_UNSET && subtype <= POPPLER_N_PDF_SUBTYPES - 1);

}



TEST_F(PopplerDocumentTest_2211, SubtypeStringIsReadable_2211) {

    gchar* subtypeString;

    g_object_get(document, "subtype-string", &subtypeString, nullptr);

    EXPECT_TRUE(subtypeString == nullptr || strlen(subtypeString) > 0);

    g_free(subtypeString);

}



TEST_F(PopplerDocumentTest_2211, SubtypePartIsReadable_2211) {

    PopplerPdfPart subtypePart;

    g_object_get(document, "subtype-part", &subtypePart, nullptr);

    EXPECT_TRUE(subtypePart >= POPPLER_PDF_SUBTYPE_PART_UNSET && subtypePart <= POPPLER_N_PDF_PARTS - 1);

}



TEST_F(PopplerDocumentTest_2211, SubtypeConformanceIsReadable_2211) {

    PopplerPdfConformance subtypeConf;

    g_object_get(document, "subtype-conformance", &subtypeConf, nullptr);

    EXPECT_TRUE(subtypeConf >= POPPLER_PDF_SUBTYPE_CONF_UNSET && subtypeConf <= POPPLER_N_PDF_CONFORMANCES - 1);

}



TEST_F(PopplerDocumentTest_2211, MetadataIsReadable_2211) {

    gchar* metadata;

    g_object_get(document, "metadata", &metadata, nullptr);

    EXPECT_TRUE(metadata == nullptr || strlen(metadata) > 0);

    g_free(metadata);

}
