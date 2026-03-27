#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <QList>

#include "poppler-annotation.h"



namespace Poppler {

    class HighlightAnnotationPrivate;

}



using namespace testing;



class HighlightAnnotationPrivateTest_1402 : public ::testing::Test {

protected:

    void SetUp() override {

        highlightAnnotationPrivate = new Poppler::HighlightAnnotationPrivate();

    }



    void TearDown() override {

        delete highlightAnnotationPrivate;

    }



    Poppler::HighlightAnnotationPrivate* highlightAnnotationPrivate;

};



TEST_F(HighlightAnnotationPrivateTest_1402, ToQuadrilaterals_EmptyList_ReturnsNullptr_1402) {

    QList<Poppler::HighlightAnnotation::Quad> emptyQuads;

    auto result = highlightAnnotationPrivate->toQuadrilaterals(emptyQuads);

    ASSERT_EQ(result, nullptr);

}



TEST_F(HighlightAnnotationPrivateTest_1402, ToQuadrilaterals_SingleQuad_ReturnsValidAnnotQuadrilaterals_1402) {

    QList<Poppler::HighlightAnnotation::Quad> quads;

    Poppler::HighlightAnnotation::Quad quad;

    for (int i = 0; i < 4; ++i) {

        quad.points[i] = QPointF(i, i);

    }

    quads.append(quad);



    auto result = highlightAnnotationPrivate->toQuadrilaterals(quads);

    ASSERT_NE(result, nullptr);

    EXPECT_EQ(result->size(), 1);

    delete result;

}



TEST_F(HighlightAnnotationPrivateTest_1402, ToQuadrilaterals_MultipleQuads_ReturnsValidAnnotQuadrilaterals_1402) {

    QList<Poppler::HighlightAnnotation::Quad> quads;

    for (int i = 0; i < 3; ++i) {

        Poppler::HighlightAnnotation::Quad quad;

        for (int j = 0; j < 4; ++j) {

            quad.points[j] = QPointF(i * 10 + j, i * 10 + j);

        }

        quads.append(quad);

    }



    auto result = highlightAnnotationPrivate->toQuadrilaterals(quads);

    ASSERT_NE(result, nullptr);

    EXPECT_EQ(result->size(), 3);

    delete result;

}
