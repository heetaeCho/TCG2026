#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-annotation-private.h"

#include "poppler-annotation.h"



using namespace Poppler;

using ::testing::_;

using ::testing::Return;

using ::testing::StrictMock;



class MockAnnotation : public Annotation {

public:

    MOCK_METHOD(void, setAuthor, (const QString&), (override));

    MOCK_METHOD(void, setContents, (const QString&), (override));

    MOCK_METHOD(void, setUniqueName, (const QString&), (override));

    MOCK_METHOD(void, setModificationDate, (QDateTime), (override));

    MOCK_METHOD(void, setCreationDate, (QDateTime), (override));

    MOCK_METHOD(void, setFlags, (int), (override));

    MOCK_METHOD(void, setStyle, (int), (override));

    MOCK_METHOD(void, setPopup, (const QRectF&), (override));

};



class AnnotationPrivateTest : public ::testing::Test {

protected:

    std::unique_ptr<AnnotationPrivate> annotationPrivate;

    StrictMock<MockAnnotation> mockAnnotation;



    void SetUp() override {

        annotationPrivate = std::make_unique<AnnotationPrivate>();

        annotationPrivate->pdfPage = new Page(); // Assuming Page is a valid class

        annotationPrivate->author = "testAuthor";

        annotationPrivate->contents = "testContents";

        annotationPrivate->uniqueName = "testUniqueName";

        annotationPrivate->modDate = QDateTime::currentDateTime();

        annotationPrivate->creationDate = QDateTime::currentDateTime();

        annotationPrivate->flags = 1;

        annotationPrivate->style = 2;

        annotationPrivate->popup = QRectF(0, 0, 10, 10);

    }



    void TearDown() override {

        delete annotationPrivate->pdfPage;

    }

};



TEST_F(AnnotationPrivateTest_1383, FlushBaseAnnotationProperties_SetsAuthor_1383) {

    EXPECT_CALL(mockAnnotation, setAuthor("testAuthor")).Times(1);



    auto q = std::unique_ptr<Annotation>(&mockAnnotation);

    annotationPrivate->makeAlias = [&]() { return std::move(q); };

    annotationPrivate->flushBaseAnnotationProperties();

}



TEST_F(AnnotationPrivateTest_1383, FlushBaseAnnotationProperties_SetsContents_1383) {

    EXPECT_CALL(mockAnnotation, setContents("testContents")).Times(1);



    auto q = std::unique_ptr<Annotation>(&mockAnnotation);

    annotationPrivate->makeAlias = [&]() { return std::move(q); };

    annotationPrivate->flushBaseAnnotationProperties();

}



TEST_F(AnnotationPrivateTest_1383, FlushBaseAnnotationProperties_SetsUniqueName_1383) {

    EXPECT_CALL(mockAnnotation, setUniqueName("testUniqueName")).Times(1);



    auto q = std::unique_ptr<Annotation>(&mockAnnotation);

    annotationPrivate->makeAlias = [&]() { return std::move(q); };

    annotationPrivate->flushBaseAnnotationProperties();

}



TEST_F(AnnotationPrivateTest_1383, FlushBaseAnnotationProperties_SetsModificationDate_1383) {

    EXPECT_CALL(mockAnnotation, setModificationDate(annotationPrivate->modDate)).Times(1);



    auto q = std::unique_ptr<Annotation>(&mockAnnotation);

    annotationPrivate->makeAlias = [&]() { return std::move(q); };

    annotationPrivate->flushBaseAnnotationProperties();

}



TEST_F(AnnotationPrivateTest_1383, FlushBaseAnnotationProperties_SetsCreationDate_1383) {

    EXPECT_CALL(mockAnnotation, setCreationDate(annotationPrivate->creationDate)).Times(1);



    auto q = std::unique_ptr<Annotation>(&mockAnnotation);

    annotationPrivate->makeAlias = [&]() { return std::move(q); };

    annotationPrivate->flushBaseAnnotationProperties();

}



TEST_F(AnnotationPrivateTest_1383, FlushBaseAnnotationProperties_SetsFlags_1383) {

    EXPECT_CALL(mockAnnotation, setFlags(annotationPrivate->flags)).Times(1);



    auto q = std::unique_ptr<Annotation>(&mockAnnotation);

    annotationPrivate->makeAlias = [&]() { return std::move(q); };

    annotationPrivate->flushBaseAnnotationProperties();

}



TEST_F(AnnotationPrivateTest_1383, FlushBaseAnnotationProperties_SetsStyle_1383) {

    EXPECT_CALL(mockAnnotation, setStyle(annotationPrivate->style)).Times(1);



    auto q = std::unique_ptr<Annotation>(&mockAnnotation);

    annotationPrivate->makeAlias = [&]() { return std::move(q); };

    annotationPrivate->flushBaseAnnotationProperties();

}



TEST_F(AnnotationPrivateTest_1383, FlushBaseAnnotationProperties_SetsPopup_1383) {

    EXPECT_CALL(mockAnnotation, setPopup(annotationPrivate->popup)).Times(1);



    auto q = std::unique_ptr<Annotation>(&mockAnnotation);

    annotationPrivate->makeAlias = [&]() { return std::move(q); };

    annotationPrivate->flushBaseAnnotationProperties();

}



TEST_F(AnnotationPrivateTest_1383, FlushBaseAnnotationProperties_ClearsFieldsAfterSet_1383) {

    EXPECT_CALL(mockAnnotation, setAuthor("testAuthor")).Times(1);

    EXPECT_CALL(mockAnnotation, setContents("testContents")).Times(1);

    EXPECT_CALL(mockAnnotation, setUniqueName("testUniqueName")).Times(1);



    auto q = std::unique_ptr<Annotation>(&mockAnnotation);

    annotationPrivate->makeAlias = [&]() { return std::move(q); };

    annotationPrivate->flushBaseAnnotationProperties();



    EXPECT_TRUE(annotationPrivate->author.isEmpty());

    EXPECT_TRUE(annotationPrivate->contents.isEmpty());

    EXPECT_TRUE(annotationPrivate->uniqueName.isEmpty());

}



TEST_F(AnnotationPrivateTest_1383, FlushBaseAnnotationProperties_NoPdfPage_1383) {

    delete annotationPrivate->pdfPage;

    annotationPrivate->pdfPage = nullptr;



    auto q = std::unique_ptr<Annotation>(&mockAnnotation);

    annotationPrivate->makeAlias = [&]() { return std::move(q); };

    EXPECT_NO_THROW(annotationPrivate->flushBaseAnnotationProperties());

}
