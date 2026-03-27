#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-action.cc"

#include "Link.h"

#include "Page.h"

#include "XRef.h"

#include "Object.h"



using namespace ::testing;



class PopplerDocumentMock : public PopplerDocument {

public:

    MOCK_METHOD(XRef*, getXRef, (), (const));

};



class XRefMock : public XRef {

public:

    MOCK_METHOD(Object, fetch, (const Ref&), (const));

};



class PageMock : public Page {

public:

    MOCK_METHOD(Object, getAnnotsObject, (XRef* xrefA), (override));

};



class ObjectMock : public Object {

public:

    MOCK_METHOD(bool, isDict, (), (const));

    MOCK_METHOD(int, arrayGetLength, (), (const));

    MOCK_METHOD(Object, arrayGet, (int i, int recursion), (const));

    MOCK_METHOD(Object, dictLookup, (std::string_view key, int recursion), (const));

};



class AnnotMovieMock : public AnnotMovie {

public:

    using AnnotMovie::AnnotMovie;

    MOCK_METHOD(bool, isOk, (), (const) override);

};



TEST_F(TestFixture_2296, FindAnnotMovieForActionWithValidRef_2296) {

    PopplerDocumentMock document;

    XRefMock xref;

    LinkMovie linkMovie;

    ObjectMock annotObj;

    AnnotMovieMock* expectedAnnotMovie = new AnnotMovieMock(nullptr, std::move(annotObj), nullptr);



    Ref ref = {1, 0};

    EXPECT_CALL(linkMovie, hasAnnotRef()).WillOnce(Return(true));

    EXPECT_CALL(linkMovie, getAnnotRef()).WillOnce(Return(&ref));



    EXPECT_CALL(document, getXRef()).WillOnce(Return(&xref));

    EXPECT_CALL(xref, fetch(ref)).WillOnce(Return(annotObj));



    EXPECT_CALL(annotObj, isDict()).WillOnce(Return(true));



    Object tmp;

    AnnotMovie* result = find_annot_movie_for_action(&document, &linkMovie);



    ASSERT_NE(result, nullptr);

    delete result;

}



TEST_F(TestFixture_2296, FindAnnotMovieForActionWithInvalidRef_2296) {

    PopplerDocumentMock document;

    XRefMock xref;

    LinkMovie linkMovie;

    ObjectMock annotObj;



    Ref ref = {1, 0};

    EXPECT_CALL(linkMovie, hasAnnotRef()).WillOnce(Return(true));

    EXPECT_CALL(linkMovie, getAnnotRef()).WillOnce(Return(&ref));



    EXPECT_CALL(document, getXRef()).WillOnce(Return(&xref));

    EXPECT_CALL(xref, fetch(ref)).WillOnce(Return(annotObj));



    EXPECT_CALL(annotObj, isDict()).WillOnce(Return(false));



    AnnotMovie* result = find_annot_movie_for_action(&document, &linkMovie);



    ASSERT_EQ(result, nullptr);

}



TEST_F(TestFixture_2296, FindAnnotMovieForActionWithValidTitle_2296) {

    PopplerDocumentMock document;

    XRefMock xref;

    LinkMovie linkMovie;

    ObjectMock annotObj1, annotObj2, annotsArray, dict;



    EXPECT_CALL(linkMovie, hasAnnotRef()).WillOnce(Return(false));

    EXPECT_CALL(linkMovie, hasAnnotTitle()).WillOnce(Return(true));

    std::string title = "movie_title";

    EXPECT_CALL(linkMovie, getAnnotTitle()).WillOnce(Return(title));



    EXPECT_CALL(document, getXRef()).WillRepeatedly(Return(&xref));



    PageMock page1;

    Object pageObj1;

    EXPECT_CALL(page1, getPageObj()).WillOnce(ReturnRefOfCopy(pageObj1));

    EXPECT_CALL(page1, getAnnotsObject(&xref)).WillOnce(Return(annotsArray));



    EXPECT_CALL(document.doc->getPage(1)).WillOnce(Return(&page1));

    EXPECT_CALL(document.doc->getNumPages()).WillOnce(Return(2));



    EXPECT_CALL(annotsArray, isArray()).WillOnce(Return(true));

    EXPECT_CALL(annotsArray, arrayGetLength()).WillOnce(Return(2));

    EXPECT_CALL(annotsArray, arrayGet(0, _)).WillOnce(Return(dict));



    ObjectMock subtype;

    EXPECT_CALL(dict, dictLookup("Subtype", _)).WillOnce(Return(subtype));

    EXPECT_CALL(subtype, isName("Movie")).WillOnce(Return(true));



    ObjectMock annotTitleObj;

    EXPECT_CALL(dict, dictLookup("T", _)).WillOnce(Return(annotTitleObj));

    GooString gooTitle(title);

    EXPECT_CALL(annotTitleObj, getString()).WillOnce(Return(&gooTitle));



    AnnotMovie* result = find_annot_movie_for_action(&document, &linkMovie);



    ASSERT_NE(result, nullptr);

    delete result;

}



TEST_F(TestFixture_2296, FindAnnotMovieForActionWithInvalidTitle_2296) {

    PopplerDocumentMock document;

    XRefMock xref;

    LinkMovie linkMovie;

    ObjectMock annotObj1, annotObj2, annotsArray, dict;



    EXPECT_CALL(linkMovie, hasAnnotRef()).WillOnce(Return(false));

    EXPECT_CALL(linkMovie, hasAnnotTitle()).WillOnce(Return(true));

    std::string title = "movie_title";

    EXPECT_CALL(linkMovie, getAnnotTitle()).WillOnce(Return(title));



    EXPECT_CALL(document, getXRef()).WillRepeatedly(Return(&xref));



    PageMock page1;

    Object pageObj1;

    EXPECT_CALL(page1, getPageObj()).WillOnce(ReturnRefOfCopy(pageObj1));

    EXPECT_CALL(page1, getAnnotsObject(&xref)).WillOnce(Return(annotsArray));



    EXPECT_CALL(document.doc->getPage(1)).WillOnce(Return(&page1));

    EXPECT_CALL(document.doc->getNumPages()).WillOnce(Return(2));



    EXPECT_CALL(annotsArray, isArray()).WillOnce(Return(true));

    EXPECT_CALL(annotsArray, arrayGetLength()).WillOnce(Return(2));

    EXPECT_CALL(annotsArray, arrayGet(0, _)).WillOnce(Return(dict));



    ObjectMock subtype;

    EXPECT_CALL(dict, dictLookup("Subtype", _)).WillOnce(Return(subtype));

    EXPECT_CALL(subtype, isName("Movie")).WillOnce(Return(false));



    AnnotMovie* result = find_annot_movie_for_action(&document, &linkMovie);



    ASSERT_EQ(result, nullptr);

}



TEST_F(TestFixture_2296, FindAnnotMovieForActionNoAnnotations_2296) {

    PopplerDocumentMock document;

    XRefMock xref;

    LinkMovie linkMovie;

    ObjectMock annotsArray;



    EXPECT_CALL(linkMovie, hasAnnotRef()).WillOnce(Return(false));

    EXPECT_CALL(linkMovie, hasAnnotTitle()).WillOnce(Return(true));

    std::string title = "movie_title";

    EXPECT_CALL(linkMovie, getAnnotTitle()).WillOnce(Return(title));



    EXPECT_CALL(document, getXRef()).WillRepeatedly(Return(&xref));



    PageMock page1;

    Object pageObj1;

    EXPECT_CALL(page1, getPageObj()).WillOnce(ReturnRefOfCopy(pageObj1));

    EXPECT_CALL(page1, getAnnotsObject(&xref)).WillOnce(Return(annotsArray));



    EXPECT_CALL(document.doc->getPage(1)).WillOnce(Return(&page1));

    EXPECT_CALL(document.doc->getNumPages()).WillOnce(Return(2));



    EXPECT_CALL(annotsArray, isArray()).WillOnce(Return(true));

    EXPECT_CALL(annotsArray, arrayGetLength()).WillOnce(Return(0));



    AnnotMovie* result = find_annot_movie_for_action(&document, &linkMovie);



    ASSERT_EQ(result, nullptr);

}
