#include <gtest/gtest.h>

#include <gmock/gmock.h>



// Mock dependencies if necessary

class MockFontInfoScanner {

public:

    MOCK_METHOD(void, deleteMock, (), ());

};



class MockPopplerDocument {

public:

    MOCK_METHOD(void, unrefMock, (), ());

};



// Externalize the finalize function for testing purposes

extern "C" void poppler_font_info_finalize(GObject *object);



using ::testing::StrictMock;



TEST(poppler_font_info_test_2234, FinalizeDeletesScanner_2234) {

    GType object_type = g_type_register_static_simple(

        G_TYPE_OBJECT,

        "PopplerFontInfo",

        sizeof(PopplerFontInfo),

        nullptr,

        sizeof(PopplerFontInfo),

        nullptr,

        0);



    GObject *object = g_object_new(object_type, nullptr);

    PopplerFontInfo *font_info = POPPLER_FONT_INFO(object);



    // Set up mocks

    StrictMock<MockFontInfoScanner> mock_scanner;

    font_info->scanner = reinterpret_cast<FontInfoScanner*>(&mock_scanner);



    EXPECT_CALL(mock_scanner, deleteMock()).Times(1);



    poppler_font_info_finalize(object);

}



TEST(poppler_font_info_test_2234, FinalizeUnrefsDocument_2234) {

    GType object_type = g_type_register_static_simple(

        G_TYPE_OBJECT,

        "PopplerFontInfo",

        sizeof(PopplerFontInfo),

        nullptr,

        sizeof(PopplerFontInfo),

        nullptr,

        0);



    GObject *object = g_object_new(object_type, nullptr);

    PopplerFontInfo *font_info = POPPLER_FONT_INFO(object);



    // Set up mocks

    StrictMock<MockPopplerDocument> mock_document;

    font_info->document = reinterpret_cast<PopplerDocument*>(&mock_document);



    EXPECT_CALL(mock_document, unrefMock()).Times(1);



    poppler_font_info_finalize(object);

}



TEST(poppler_font_info_test_2234, FinalizeCallsParentFinalize_2234) {

    GType object_type = g_type_register_static_simple(

        G_TYPE_OBJECT,

        "PopplerFontInfo",

        sizeof(PopplerFontInfo),

        nullptr,

        sizeof(PopplerFontInfo),

        nullptr,

        0);



    GObject *object = g_object_new(object_type, nullptr);

    PopplerFontInfo *font_info = POPPLER_FONT_INFO(object);



    // Set up mocks

    StrictMock<MockFontInfoScanner> mock_scanner;

    font_info->scanner = reinterpret_cast<FontInfoScanner*>(&mock_scanner);



    StrictMock<MockPopplerDocument> mock_document;

    font_info->document = reinterpret_cast<PopplerDocument*>(&mock_document);



    EXPECT_CALL(mock_scanner, deleteMock()).Times(1);

    EXPECT_CALL(mock_document, unrefMock()).Times(1);



    // Mock the parent finalize call

    G_OBJECT_CLASS(poppler_font_info_parent_class)->finalize = [](GObject *obj) {

        SUCCEED() << "Parent finalize called";

    };



    poppler_font_info_finalize(object);

}
