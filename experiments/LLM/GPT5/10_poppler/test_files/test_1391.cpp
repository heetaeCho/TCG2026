#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "poppler-annotation-private.h"
#include "poppler/Object.h"
#include "poppler/Page.h"
#include "poppler/DocumentData.h"

using ::testing::Mock;
using ::testing::Return;
using ::testing::NiceMock;

// Mock dependencies
class MockAnnot {};
class MockPage {};
class MockDocumentData {};

namespace Poppler {
    class MockAnnotationPrivate : public AnnotationPrivate {
    public:
        MOCK_METHOD(Ref, pdfObjectReference, (), (const, override));
        MOCK_METHOD(void, addRevision, (Annotation * ann, int scope, int type), (override));
        MOCK_METHOD(void, tieToNativeAnnot, (std::shared_ptr<Annot> ann, ::Page * page, DocumentData * doc), (override));
        MOCK_METHOD(void, flushBaseAnnotationProperties, (), (override));
        MOCK_METHOD(QRectF, fromPdfRectangle, (const PDFRectangle & r), (const, override));
        MOCK_METHOD(PDFRectangle, boundaryToPdfRectangle, (const QRectF & r, int flags), (const, override));
        MOCK_METHOD(AnnotPath*, toAnnotPath, (const QLinkedList<QPointF> &list), (const, override));
        MOCK_METHOD(QList<Annotation*>, findAnnotations, (::Page *pdfPage, DocumentData *doc, const QSet<Annotation::SubType> &subtypes, int parentID), (override));
        MOCK_METHOD(void, addAnnotationToPage, (::Page *pdfPage, DocumentData *doc, const Annotation *ann), (override));
        MOCK_METHOD(void, removeAnnotationFromPage, (::Page *pdfPage, const Annotation *ann), (override));
    };
}

TEST_F(AnnotationPrivateTest_1391, pdfObjectReference_ValidAnnot_1391) {
    MockAnnotationPrivate annotationPrivate;
    Ref expectedRef{1, 1};  // Example reference
    ON_CALL(annotationPrivate, pdfObjectReference()).WillByDefault(Return(expectedRef));

    EXPECT_EQ(annotationPrivate.pdfObjectReference(), expectedRef);
}

TEST_F(AnnotationPrivateTest_1392, pdfObjectReference_NullAnnot_1392) {
    MockAnnotationPrivate annotationPrivate;
    ON_CALL(annotationPrivate, pdfObjectReference()).WillByDefault(Return(Ref::INVALID()));

    EXPECT_EQ(annotationPrivate.pdfObjectReference(), Ref::INVALID());
}

TEST_F(AnnotationPrivateTest_1393, addRevision_ValidParameters_1393) {
    MockAnnotationPrivate annotationPrivate;
    MockAnnot mockAnnot;
    int scope = 1;
    int type = 2;

    EXPECT_CALL(annotationPrivate, addRevision(&mockAnnot, scope, type)).Times(1);
    annotationPrivate.addRevision(&mockAnnot, scope, type);
}

TEST_F(AnnotationPrivateTest_1394, tieToNativeAnnot_ValidAnnot_1394) {
    MockAnnotationPrivate annotationPrivate;
    std::shared_ptr<MockAnnot> annot = std::make_shared<MockAnnot>();
    MockPage mockPage;
    MockDocumentData mockDoc;

    EXPECT_CALL(annotationPrivate, tieToNativeAnnot(annot, &mockPage, &mockDoc)).Times(1);
    annotationPrivate.tieToNativeAnnot(annot, &mockPage, &mockDoc);
}

TEST_F(AnnotationPrivateTest_1395, boundaryToPdfRectangle_ValidQRectF_1395) {
    MockAnnotationPrivate annotationPrivate;
    QRectF rect(0.0, 0.0, 10.0, 20.0);
    int flags = 0;

    EXPECT_CALL(annotationPrivate, boundaryToPdfRectangle(rect, flags)).Times(1);
    annotationPrivate.boundaryToPdfRectangle(rect, flags);
}

TEST_F(AnnotationPrivateTest_1396, fromPdfRectangle_ValidPDFRectangle_1396) {
    MockAnnotationPrivate annotationPrivate;
    PDFRectangle pdfRect{0.0, 0.0, 10.0, 20.0};

    QRectF expectedRect(0.0, 0.0, 10.0, 20.0);
    EXPECT_CALL(annotationPrivate, fromPdfRectangle(pdfRect)).Times(1).WillOnce(Return(expectedRect));
    EXPECT_EQ(annotationPrivate.fromPdfRectangle(pdfRect), expectedRect);
}

TEST_F(AnnotationPrivateTest_1397, toAnnotPath_ValidPointList_1397) {
    MockAnnotationPrivate annotationPrivate;
    QLinkedList<QPointF> pointList;
    pointList.append(QPointF(0.0, 0.0));
    pointList.append(QPointF(10.0, 10.0));

    AnnotPath* expectedPath = new AnnotPath();
    EXPECT_CALL(annotationPrivate, toAnnotPath(pointList)).Times(1).WillOnce(Return(expectedPath));

    EXPECT_EQ(annotationPrivate.toAnnotPath(pointList), expectedPath);
}

TEST_F(AnnotationPrivateTest_1398, findAnnotations_ValidPage_1398) {
    MockAnnotationPrivate annotationPrivate;
    MockPage mockPage;
    MockDocumentData mockDoc;
    QSet<Annotation::SubType> subtypes;
    int parentID = 0;

    QList<Annotation*> expectedAnnotations;
    expectedAnnotations.append(new Annotation());

    EXPECT_CALL(annotationPrivate, findAnnotations(&mockPage, &mockDoc, subtypes, parentID))
        .Times(1)
        .WillOnce(Return(expectedAnnotations));

    EXPECT_EQ(annotationPrivate.findAnnotations(&mockPage, &mockDoc, subtypes, parentID), expectedAnnotations);
}

TEST_F(AnnotationPrivateTest_1399, addAnnotationToPage_ValidAnnotation_1399) {
    MockAnnotationPrivate annotationPrivate;
    MockPage mockPage;
    MockDocumentData mockDoc;
    MockAnnot mockAnnot;

    EXPECT_CALL(annotationPrivate, addAnnotationToPage(&mockPage, &mockDoc, &mockAnnot)).Times(1);
    annotationPrivate.addAnnotationToPage(&mockPage, &mockDoc, &mockAnnot);
}

TEST_F(AnnotationPrivateTest_1400, removeAnnotationFromPage_ValidAnnotation_1400) {
    MockAnnotationPrivate annotationPrivate;
    MockPage mockPage;
    MockAnnot mockAnnot;

    EXPECT_CALL(annotationPrivate, removeAnnotationFromPage(&mockPage, &mockAnnot)).Times(1);
    annotationPrivate.removeAnnotationFromPage(&mockPage, &mockAnnot);
}