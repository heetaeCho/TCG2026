#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "QPainterOutputDev.h"

#include "poppler-page-private.h"



using namespace Poppler;

using ::testing::_;

using ::testing::Mock;



class QPainterMock : public QPainter {

public:

    MOCK_METHOD(void, save, (), (override));

    MOCK_METHOD(void, restore, (), (override));

    MOCK_METHOD(void, translate, (qreal dx, qreal dy), (override));

    MOCK_METHOD(void, setRenderHint, (QPainter::RenderHint hint, bool on = true), (override));

};



class PageDataMock : public PageData {

public:

    MOCK_CONST_METHOD3(prepareTextSearch, int(const QString &text, int rotate, QVector<Unicode> *u));

    MOCK_METHOD9(performSingleTextSearch, bool(TextPage *textPage, QVector<Unicode> &u, double &sLeft, double &sTop, double &sRight, double &sBottom, Page::SearchDirection direction, bool sCase, bool sWords, bool sDiacritics, bool sAcrossLines));

    MOCK_METHOD7(performMultipleTextSearch, QList<QRectF>(TextPage *textPage, QVector<Unicode> &u, bool sCase, bool sWords, bool sDiacritics, bool sAcrossLines));

};



class QImageDumpingQPainterOutputDevMock : public QImageDumpingQPainterOutputDev {

public:

    using QImageDumpingQPainterOutputDev::QImageDumpingQPainterOutputDev;

    MOCK_METHOD0(dump, void());

    MOCK_METHOD1(startDoc, void(PDFDoc *doc));

};



TEST_F(RenderToQPainterTest_1444, NormalOperation_1444) {

    QPainterMock painterMock;

    PageDataMock pageDataMock;

    QImageDumpingQPainterOutputDevMock qpainter_output(&painterMock, nullptr);



    EXPECT_CALL(painterMock, save()).Times(1);

    EXPECT_CALL(painterMock, restore()).Times(1);

    EXPECT_CALL(painterMock, translate(-0.0, -0.0)).Times(1);

    EXPECT_CALL(qpainter_output, startDoc(_)).Times(1);



    bool result = renderToQPainter(&qpainter_output, &painterMock, &pageDataMock, 300, 300, -1, -1, 800, 600, Page::Rotate0, Page::PainterFlags());



    EXPECT_TRUE(result);

}



TEST_F(RenderToQPainterTest_1444, BoundaryConditions_XY_1444) {

    QPainterMock painterMock;

    PageDataMock pageDataMock;

    QImageDumpingQPainterOutputDevMock qpainter_output(&painterMock, nullptr);



    EXPECT_CALL(painterMock, translate(0.0, 0.0)).Times(1);

    EXPECT_CALL(qpainter_output, startDoc(_)).Times(1);



    bool result = renderToQPainter(&qpainter_output, &painterMock, &pageDataMock, 300, 300, 0, 0, 800, 600, Page::Rotate0, Page::PainterFlags());



    EXPECT_TRUE(result);

}



TEST_F(RenderToQPainterTest_1444, BoundaryConditions_W_H_1444) {

    QPainterMock painterMock;

    PageDataMock pageDataMock;

    QImageDumpingQPainterOutputDevMock qpainter_output(&painterMock, nullptr);



    EXPECT_CALL(painterMock, translate(-0.0, -0.0)).Times(1);

    EXPECT_CALL(qpainter_output, startDoc(_)).Times(1);



    bool result = renderToQPainter(&qpainter_output, &painterMock, &pageDataMock, 300, 300, -1, -1, 0, 600, Page::Rotate0, Page::PainterFlags());



    EXPECT_TRUE(result);

}



TEST_F(RenderToQPainterTest_1444, AntialiasingEnabled_1444) {

    QPainterMock painterMock;

    PageDataMock pageDataMock;

    QImageDumpingQPainterOutputDevMock qpainter_output(&painterMock, nullptr);



    pageDataMock.parentDoc->m_hints = Document::Antialiasing;



    EXPECT_CALL(painterMock, save()).Times(1);

    EXPECT_CALL(painterMock, restore()).Times(1);

    EXPECT_CALL(painterMock, translate(-0.0, -0.0)).Times(1);

    EXPECT_CALL(qpainter_output, startDoc(_)).Times(1);

    EXPECT_CALL(painterMock, setRenderHint(QPainter::Antialiasing, true)).Times(1);



    bool result = renderToQPainter(&qpainter_output, &painterMock, &pageDataMock, 300, 300, -1, -1, 800, 600, Page::Rotate0, Page::PainterFlags());



    EXPECT_TRUE(result);

}



TEST_F(RenderToQPainterTest_1444, TextAntialiasingEnabled_1444) {

    QPainterMock painterMock;

    PageDataMock pageDataMock;

    QImageDumpingQPainterOutputDevMock qpainter_output(&painterMock, nullptr);



    pageDataMock.parentDoc->m_hints = Document::TextAntialiasing;



    EXPECT_CALL(painterMock, save()).Times(1);

    EXPECT_CALL(painterMock, restore()).Times(1);

    EXPECT_CALL(painterMock, translate(-0.0, -0.0)).Times(1);

    EXPECT_CALL(qpainter_output, startDoc(_)).Times(1);

    EXPECT_CALL(painterMock, setRenderHint(QPainter::TextAntialiasing, true)).Times(1);



    bool result = renderToQPainter(&qpainter_output, &painterMock, &pageDataMock, 300, 300, -1, -1, 800, 600, Page::Rotate0, Page::PainterFlags());



    EXPECT_TRUE(result);

}



TEST_F(RenderToQPainterTest_1444, HideAnnotationsEnabled_1444) {

    QPainterMock painterMock;

    PageDataMock pageDataMock;

    QImageDumpingQPainterOutputDevMock qpainter_output(&painterMock, nullptr);



    pageDataMock.parentDoc->m_hints = Document::HideAnnotations;



    EXPECT_CALL(painterMock, save()).Times(1);

    EXPECT_CALL(painterMock, restore()).Times(1);

    EXPECT_CALL(painterMock, translate(-0.0, -0.0)).Times(1);

    EXPECT_CALL(qpainter_output, startDoc(_)).Times(1);



    bool result = renderToQPainter(&qpainter_output, &painterMock, &pageDataMock, 300, 300, -1, -1, 800, 600, Page::Rotate0, Page::PainterFlags());



    EXPECT_TRUE(result);

}



TEST_F(RenderToQPainterTest_1444, NoSaveAndRestoreFlagSet_1444) {

    QPainterMock painterMock;

    PageDataMock pageDataMock;

    QImageDumpingQPainterOutputDevMock qpainter_output(&painterMock, nullptr);



    EXPECT_CALL(painterMock, save()).Times(0);

    EXPECT_CALL(painterMock, restore()).Times(0);

    EXPECT_CALL(painterMock, translate(-0.0, -0.0)).Times(1);

    EXPECT_CALL(qpainter_output, startDoc(_)).Times(1);



    bool result = renderToQPainter(&qpainter_output, &painterMock, &pageDataMock, 300, 300, -1, -1, 800, 600, Page::Rotate0, Page::DontSaveAndRestore);



    EXPECT_TRUE(result);

}
