#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/poppler/poppler/Annot.h"



using namespace testing;



class AnnotMock : public Annot {

public:

    MOCK_METHOD(AnnotSubtype, getType, (), (const, override));

};



TEST_F(AnnotMock, annots_display_decide_cb_ShouldReturnTrueForMatchingFlag_2432) {

    AnnotMock mockAnnot;

    EXPECT_CALL(mockAnnot, getType()).WillOnce(Return(AnnotSubtype::text));



    PopplerRenderAnnotsFlags flags = static_cast<PopplerRenderAnnotsFlags>(1 << (static_cast<int>(AnnotSubtype::text) - 1));

    void* user_data = GUINT_TO_POINTER(flags);



    bool result = annots_display_decide_cb(&mockAnnot, user_data);

    EXPECT_TRUE(result);

}



TEST_F(AnnotMock, annots_display_decide_cb_ShouldReturnFalseForNonMatchingFlag_2432) {

    AnnotMock mockAnnot;

    EXPECT_CALL(mockAnnot, getType()).WillOnce(Return(AnnotSubtype::text));



    PopplerRenderAnnotsFlags flags = static_cast<PopplerRenderAnnotsFlags>(1 << (static_cast<int>(AnnotSubtype::link) - 1));

    void* user_data = GUINT_TO_POINTER(flags);



    bool result = annots_display_decide_cb(&mockAnnot, user_data);

    EXPECT_FALSE(result);

}



TEST_F(AnnotMock, annots_display_decide_cb_ShouldReturnTrueForAllFlags_2432) {

    AnnotMock mockAnnot;

    EXPECT_CALL(mockAnnot, getType()).WillOnce(Return(AnnotSubtype::text));



    PopplerRenderAnnotsFlags flags = static_cast<PopplerRenderAnnotsFlags>(0xFFFFFFFF);

    void* user_data = GUINT_TO_POINTER(flags);



    bool result = annots_display_decide_cb(&mockAnnot, user_data);

    EXPECT_TRUE(result);

}



TEST_F(AnnotMock, annots_display_decide_cb_ShouldReturnFalseForNoFlags_2432) {

    AnnotMock mockAnnot;

    EXPECT_CALL(mockAnnot, getType()).WillOnce(Return(AnnotSubtype::text));



    PopplerRenderAnnotsFlags flags = static_cast<PopplerRenderAnnotsFlags>(0);

    void* user_data = GUINT_TO_POINTER(flags);



    bool result = annots_display_decide_cb(&mockAnnot, user_data);

    EXPECT_FALSE(result);

}



TEST_F(AnnotMock, annots_display_decide_cb_ShouldHandleMaxSubtype_2432) {

    AnnotMock mockAnnot;

    EXPECT_CALL(mockAnnot, getType()).WillOnce(Return(static_cast<AnnotSubtype>(MAX_SUBTYPE)));



    PopplerRenderAnnotsFlags flags = static_cast<PopplerRenderAnnotsFlags>(1 << (static_cast<int>(MAX_SUBTYPE) - 1));

    void* user_data = GUINT_TO_POINTER(flags);



    bool result = annots_display_decide_cb(&mockAnnot, user_data);

    EXPECT_TRUE(result);

}



TEST_F(AnnotMock, annots_display_decide_cb_ShouldHandleMinSubtype_2432) {

    AnnotMock mockAnnot;

    EXPECT_CALL(mockAnnot, getType()).WillOnce(Return(static_cast<AnnotSubtype>(MIN_SUBTYPE)));



    PopplerRenderAnnotsFlags flags = static_cast<PopplerRenderAnnotsFlags>(1 << (static_cast<int>(MIN_SUBTYPE) - 1));

    void* user_data = GUINT_TO_POINTER(flags);



    bool result = annots_display_decide_cb(&mockAnnot, user_data);

    EXPECT_TRUE(result);

}
