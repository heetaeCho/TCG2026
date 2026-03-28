#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-annotation.cc"

#include "Page.h"

#include "poppler-private.h"



using namespace Poppler;

using ::testing::NiceMock;

using ::testing::_;



class MockPage : public Page {

public:

    MOCK_METHOD(bool, addAnnot, (const std::shared_ptr<Annot>& annot), (override));

};



class MockDocumentData : public DocumentData {

public:

    MockDocumentData(const QString &filePath, const std::optional<GooString> &ownerPassword, const std::optional<GooString> &userPassword)

        : DocumentData(filePath, ownerPassword, userPassword) {}

};



class LineAnnotationPrivateTest : public ::testing::Test {

protected:

    void SetUp() override {

        page = std::make_unique<NiceMock<MockPage>>(nullptr, 0, Object(), Ref(), nullptr);

        documentData = std::make_shared<MockDocumentData>("dummy_path", std::nullopt, std::nullopt);

        lineAnnotationPrivate = std::make_unique<LineAnnotationPrivate>();

    }



    void TearDown() override {

        lineAnnotationPrivate.reset();

        page.reset();

        documentData.reset();

    }



    std::unique_ptr<NiceMock<MockPage>> page;

    std::shared_ptr<MockDocumentData> documentData;

    std::unique_ptr<LineAnnotationPrivate> lineAnnotationPrivate;

};



TEST_F(LineAnnotationPrivateTest, CreateNativeAnnot_ReturnsValidAnnot_1399) {

    auto annot = lineAnnotationPrivate->createNativeAnnot(page.get(), documentData.get());

    EXPECT_TRUE(annot != nullptr);

}



TEST_F(LineAnnotationPrivateTest, CreateNativeAnnot_StraightLineType_CreatesAnnotLine_1399) {

    lineAnnotationPrivate->lineType = LineAnnotation::StraightLine;

    auto annot = std::dynamic_pointer_cast<AnnotLine>(lineAnnotationPrivate->createNativeAnnot(page.get(), documentData.get()));

    EXPECT_TRUE(annot != nullptr);

}



TEST_F(LineAnnotationPrivateTest, CreateNativeAnnot_PolygonType_CreatesAnnotPolygon_1399) {

    lineAnnotationPrivate->lineType = LineAnnotation::Polygon;

    auto annot = std::dynamic_pointer_cast<AnnotPolygon>(lineAnnotationPrivate->createNativeAnnot(page.get(), documentData.get()));

    EXPECT_TRUE(annot != nullptr);

}



TEST_F(LineAnnotationPrivateTest, CreateNativeAnnot_PolygonClosed_CreatesAnnotWithPolygonType_1399) {

    lineAnnotationPrivate->lineType = LineAnnotation::Polygon;

    lineAnnotationPrivate->lineClosed = true;

    auto annot = std::dynamic_pointer_cast<AnnotPolygon>(lineAnnotationPrivate->createNativeAnnot(page.get(), documentData.get()));

    EXPECT_TRUE(annot != nullptr);

}



TEST_F(LineAnnotationPrivateTest, CreateNativeAnnot_PolygonOpen_CreatesAnnotWithPolyLineType_1399) {

    lineAnnotationPrivate->lineType = LineAnnotation::Polygon;

    lineAnnotationPrivate->lineClosed = false;

    auto annot = std::dynamic_pointer_cast<AnnotPolyLine>(lineAnnotationPrivate->createNativeAnnot(page.get(), documentData.get()));

    EXPECT_TRUE(annot != nullptr);

}



TEST_F(LineAnnotationPrivateTest, CreateNativeAnnot_SetsProperties_1399) {

    lineAnnotationPrivate->linePoints = {QPointF(0, 0), QPointF(1, 1)};

    lineAnnotationPrivate->lineStartStyle = LineAnnotation::Square;

    lineAnnotationPrivate->lineEndStyle = LineAnnotation::Circle;

    lineAnnotationPrivate->lineInnerColor = QColor("red");

    lineAnnotationPrivate->lineLeadingFwdPt = 5.0;

    lineAnnotationPrivate->lineLeadingBackPt = 10.0;

    lineAnnotationPrivate->lineShowCaption = true;

    lineAnnotationPrivate->lineIntent = "FreeText";



    auto annot = std::dynamic_pointer_cast<LineAnnotation>(lineAnnotationPrivate->createNativeAnnot(page.get(), documentData.get()));

    

    EXPECT_EQ(annot->linePoints(), lineAnnotationPrivate->linePoints);

    EXPECT_EQ(annot->lineStartStyle(), lineAnnotationPrivate->lineStartStyle);

    EXPECT_EQ(annot->lineEndStyle(), lineAnnotationPrivate->lineEndStyle);

    EXPECT_EQ(annot->lineInnerColor(), lineAnnotationPrivate->lineInnerColor);

    EXPECT_EQ(annot->lineLeadingForwardPoint(), lineAnnotationPrivate->lineLeadingFwdPt);

    EXPECT_EQ(annot->lineLeadingBackPoint(), lineAnnotationPrivate->lineLeadingBackPt);

    EXPECT_EQ(annot->lineShowCaption(), lineAnnotationPrivate->lineShowCaption);

    EXPECT_EQ(annot->lineIntent(), lineAnnotationPrivate->lineIntent);

}
