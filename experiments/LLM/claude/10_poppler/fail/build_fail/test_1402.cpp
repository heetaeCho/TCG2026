#include <gtest/gtest.h>
#include <QList>
#include <QPointF>
#include <memory>

#include "poppler-qt5.h"
#include "poppler-annotation.h"

using namespace Poppler;

class HighlightAnnotationTest_1402 : public ::testing::Test {
protected:
    void SetUp() override {
        annotation = std::make_unique<HighlightAnnotation>();
    }

    void TearDown() override {
        annotation.reset();
    }

    std::unique_ptr<HighlightAnnotation> annotation;

    HighlightAnnotation::Quad createQuad(QPointF p0, QPointF p1, QPointF p2, QPointF p3) {
        HighlightAnnotation::Quad q;
        q.points[0] = p0;
        q.points[1] = p1;
        q.points[2] = p2;
        q.points[3] = p3;
        q.capStart = false;
        q.capEnd = false;
        q.feather = 0.0;
        return q;
    }
};

TEST_F(HighlightAnnotationTest_1402, DefaultConstructor_1402) {
    ASSERT_NE(annotation, nullptr);
    EXPECT_EQ(annotation->subType(), Annotation::AHighlight);
}

TEST_F(HighlightAnnotationTest_1402, EmptyQuadsByDefault_1402) {
    QList<HighlightAnnotation::Quad> quads = annotation->highlightQuads();
    EXPECT_TRUE(quads.isEmpty());
}

TEST_F(HighlightAnnotationTest_1402, SetAndGetHighlightQuads_1402) {
    QList<HighlightAnnotation::Quad> quads;
    HighlightAnnotation::Quad q = createQuad(
        QPointF(0.0, 0.0), QPointF(1.0, 0.0),
        QPointF(1.0, 1.0), QPointF(0.0, 1.0)
    );
    quads.append(q);

    annotation->setHighlightQuads(quads);

    QList<HighlightAnnotation::Quad> result = annotation->highlightQuads();
    EXPECT_EQ(result.size(), 1);
}

TEST_F(HighlightAnnotationTest_1402, SetMultipleQuads_1402) {
    QList<HighlightAnnotation::Quad> quads;

    for (int i = 0; i < 5; i++) {
        HighlightAnnotation::Quad q = createQuad(
            QPointF(i * 0.1, 0.0), QPointF(i * 0.1 + 0.1, 0.0),
            QPointF(i * 0.1 + 0.1, 0.1), QPointF(i * 0.1, 0.1)
        );
        quads.append(q);
    }

    annotation->setHighlightQuads(quads);

    QList<HighlightAnnotation::Quad> result = annotation->highlightQuads();
    EXPECT_EQ(result.size(), 5);
}

TEST_F(HighlightAnnotationTest_1402, SetEmptyQuads_1402) {
    QList<HighlightAnnotation::Quad> quads;
    annotation->setHighlightQuads(quads);

    QList<HighlightAnnotation::Quad> result = annotation->highlightQuads();
    EXPECT_TRUE(result.isEmpty());
}

TEST_F(HighlightAnnotationTest_1402, QuadPointsPreserved_1402) {
    QList<HighlightAnnotation::Quad> quads;
    HighlightAnnotation::Quad q = createQuad(
        QPointF(0.1, 0.2), QPointF(0.3, 0.4),
        QPointF(0.5, 0.6), QPointF(0.7, 0.8)
    );
    quads.append(q);

    annotation->setHighlightQuads(quads);

    QList<HighlightAnnotation::Quad> result = annotation->highlightQuads();
    ASSERT_EQ(result.size(), 1);
    EXPECT_DOUBLE_EQ(result[0].points[0].x(), 0.1);
    EXPECT_DOUBLE_EQ(result[0].points[0].y(), 0.2);
    EXPECT_DOUBLE_EQ(result[0].points[1].x(), 0.3);
    EXPECT_DOUBLE_EQ(result[0].points[1].y(), 0.4);
    EXPECT_DOUBLE_EQ(result[0].points[2].x(), 0.5);
    EXPECT_DOUBLE_EQ(result[0].points[2].y(), 0.6);
    EXPECT_DOUBLE_EQ(result[0].points[3].x(), 0.7);
    EXPECT_DOUBLE_EQ(result[0].points[3].y(), 0.8);
}

TEST_F(HighlightAnnotationTest_1402, SubTypeIsHighlight_1402) {
    EXPECT_EQ(annotation->subType(), Annotation::AHighlight);
}

TEST_F(HighlightAnnotationTest_1402, SetHighlightType_1402) {
    annotation->setHighlightType(HighlightAnnotation::Highlight);
    EXPECT_EQ(annotation->highlightType(), HighlightAnnotation::Highlight);
}

TEST_F(HighlightAnnotationTest_1402, SetHighlightTypeUnderline_1402) {
    annotation->setHighlightType(HighlightAnnotation::Underline);
    EXPECT_EQ(annotation->highlightType(), HighlightAnnotation::Underline);
}

TEST_F(HighlightAnnotationTest_1402, SetHighlightTypeSquiggly_1402) {
    annotation->setHighlightType(HighlightAnnotation::Squiggly);
    EXPECT_EQ(annotation->highlightType(), HighlightAnnotation::Squiggly);
}

TEST_F(HighlightAnnotationTest_1402, SetHighlightTypeStrikeOut_1402) {
    annotation->setHighlightType(HighlightAnnotation::StrikeOut);
    EXPECT_EQ(annotation->highlightType(), HighlightAnnotation::StrikeOut);
}

TEST_F(HighlightAnnotationTest_1402, OverwriteQuads_1402) {
    QList<HighlightAnnotation::Quad> quads1;
    quads1.append(createQuad(
        QPointF(0.0, 0.0), QPointF(1.0, 0.0),
        QPointF(1.0, 1.0), QPointF(0.0, 1.0)
    ));
    annotation->setHighlightQuads(quads1);
    EXPECT_EQ(annotation->highlightQuads().size(), 1);

    QList<HighlightAnnotation::Quad> quads2;
    quads2.append(createQuad(
        QPointF(0.0, 0.0), QPointF(0.5, 0.0),
        QPointF(0.5, 0.5), QPointF(0.0, 0.5)
    ));
    quads2.append(createQuad(
        QPointF(0.5, 0.0), QPointF(1.0, 0.0),
        QPointF(1.0, 0.5), QPointF(0.5, 0.5)
    ));
    annotation->setHighlightQuads(quads2);
    EXPECT_EQ(annotation->highlightQuads().size(), 2);
}

TEST_F(HighlightAnnotationTest_1402, QuadCapStartAndCapEnd_1402) {
    HighlightAnnotation::Quad q;
    q.points[0] = QPointF(0.0, 0.0);
    q.points[1] = QPointF(1.0, 0.0);
    q.points[2] = QPointF(1.0, 1.0);
    q.points[3] = QPointF(0.0, 1.0);
    q.capStart = true;
    q.capEnd = true;
    q.feather = 0.5;

    QList<HighlightAnnotation::Quad> quads;
    quads.append(q);
    annotation->setHighlightQuads(quads);

    QList<HighlightAnnotation::Quad> result = annotation->highlightQuads();
    ASSERT_EQ(result.size(), 1);
    EXPECT_TRUE(result[0].capStart);
    EXPECT_TRUE(result[0].capEnd);
    EXPECT_DOUBLE_EQ(result[0].feather, 0.5);
}

TEST_F(HighlightAnnotationTest_1402, SingleQuadAtOrigin_1402) {
    QList<HighlightAnnotation::Quad> quads;
    quads.append(createQuad(
        QPointF(0.0, 0.0), QPointF(0.0, 0.0),
        QPointF(0.0, 0.0), QPointF(0.0, 0.0)
    ));
    annotation->setHighlightQuads(quads);

    QList<HighlightAnnotation::Quad> result = annotation->highlightQuads();
    ASSERT_EQ(result.size(), 1);
    for (int i = 0; i < 4; i++) {
        EXPECT_DOUBLE_EQ(result[0].points[i].x(), 0.0);
        EXPECT_DOUBLE_EQ(result[0].points[i].y(), 0.0);
    }
}

TEST_F(HighlightAnnotationTest_1402, LargeNumberOfQuads_1402) {
    QList<HighlightAnnotation::Quad> quads;
    for (int i = 0; i < 100; i++) {
        double offset = i * 0.01;
        quads.append(createQuad(
            QPointF(offset, 0.0), QPointF(offset + 0.01, 0.0),
            QPointF(offset + 0.01, 0.01), QPointF(offset, 0.01)
        ));
    }
    annotation->setHighlightQuads(quads);

    QList<HighlightAnnotation::Quad> result = annotation->highlightQuads();
    EXPECT_EQ(result.size(), 100);
}

TEST_F(HighlightAnnotationTest_1402, QuadWithNegativeCoordinates_1402) {
    QList<HighlightAnnotation::Quad> quads;
    quads.append(createQuad(
        QPointF(-1.0, -1.0), QPointF(1.0, -1.0),
        QPointF(1.0, 1.0), QPointF(-1.0, 1.0)
    ));
    annotation->setHighlightQuads(quads);

    QList<HighlightAnnotation::Quad> result = annotation->highlightQuads();
    ASSERT_EQ(result.size(), 1);
    EXPECT_DOUBLE_EQ(result[0].points[0].x(), -1.0);
    EXPECT_DOUBLE_EQ(result[0].points[0].y(), -1.0);
}
