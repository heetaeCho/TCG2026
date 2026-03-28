#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include <QString>
#include <QVector>
#include <QRectF>
#include <QList>

// Poppler includes
#include "poppler-qt5.h"
#include "poppler-page-private.h"
#include "poppler-private.h"
#include "TextOutputDev.h"

using namespace Poppler;

class PageDataTest_1441 : public ::testing::Test {
protected:
    void SetUp() override {
        // Try to load a simple PDF for testing
        doc = Poppler::Document::load(TESTDATADIR "/unittestcases/WithActualText.pdf");
        if (!doc) {
            doc = Poppler::Document::load("../test/unittestcases/WithActualText.pdf");
        }
    }

    void TearDown() override {
        delete doc;
        doc = nullptr;
    }

    Poppler::Document *doc = nullptr;
};

// Test that prepareTextSearch returns a non-null TextPage for valid input
TEST_F(PageDataTest_1441, PrepareTextSearchReturnsTextPage_1441) {
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    std::unique_ptr<Poppler::Page> page(doc->page(0));
    ASSERT_NE(page, nullptr);
    
    QVector<Unicode> u;
    auto textPage = page->d->prepareTextSearch(QString("test"), Page::Rotate0, &u);
    
    EXPECT_NE(textPage, nullptr);
}

// Test that prepareTextSearch populates the Unicode vector from input text
TEST_F(PageDataTest_1441, PrepareTextSearchPopulatesUnicodeVector_1441) {
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    std::unique_ptr<Poppler::Page> page(doc->page(0));
    ASSERT_NE(page, nullptr);
    
    QString searchText("Hello");
    QVector<Unicode> u;
    auto textPage = page->d->prepareTextSearch(searchText, Page::Rotate0, &u);
    
    EXPECT_EQ(u.size(), searchText.toUcs4().size());
    QVector<uint> expected = searchText.toUcs4();
    for (int i = 0; i < u.size(); i++) {
        EXPECT_EQ(u[i], expected[i]);
    }
}

// Test with empty search string
TEST_F(PageDataTest_1441, PrepareTextSearchEmptyString_1441) {
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    std::unique_ptr<Poppler::Page> page(doc->page(0));
    ASSERT_NE(page, nullptr);
    
    QVector<Unicode> u;
    auto textPage = page->d->prepareTextSearch(QString(""), Page::Rotate0, &u);
    
    EXPECT_NE(textPage, nullptr);
    EXPECT_EQ(u.size(), 0);
}

// Test with different rotations
TEST_F(PageDataTest_1441, PrepareTextSearchRotate90_1441) {
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    std::unique_ptr<Poppler::Page> page(doc->page(0));
    ASSERT_NE(page, nullptr);
    
    QVector<Unicode> u;
    auto textPage = page->d->prepareTextSearch(QString("test"), Page::Rotate90, &u);
    
    EXPECT_NE(textPage, nullptr);
}

TEST_F(PageDataTest_1441, PrepareTextSearchRotate180_1441) {
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    std::unique_ptr<Poppler::Page> page(doc->page(0));
    ASSERT_NE(page, nullptr);
    
    QVector<Unicode> u;
    auto textPage = page->d->prepareTextSearch(QString("test"), Page::Rotate180, &u);
    
    EXPECT_NE(textPage, nullptr);
}

TEST_F(PageDataTest_1441, PrepareTextSearchRotate270_1441) {
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    std::unique_ptr<Poppler::Page> page(doc->page(0));
    ASSERT_NE(page, nullptr);
    
    QVector<Unicode> u;
    auto textPage = page->d->prepareTextSearch(QString("test"), Page::Rotate270, &u);
    
    EXPECT_NE(textPage, nullptr);
}

// Test with Unicode characters
TEST_F(PageDataTest_1441, PrepareTextSearchUnicodeChars_1441) {
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    std::unique_ptr<Poppler::Page> page(doc->page(0));
    ASSERT_NE(page, nullptr);
    
    QString searchText = QString::fromUtf8("日本語");
    QVector<Unicode> u;
    auto textPage = page->d->prepareTextSearch(searchText, Page::Rotate0, &u);
    
    EXPECT_NE(textPage, nullptr);
    EXPECT_EQ(u.size(), searchText.toUcs4().size());
}

// Test with single character search
TEST_F(PageDataTest_1441, PrepareTextSearchSingleChar_1441) {
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    std::unique_ptr<Poppler::Page> page(doc->page(0));
    ASSERT_NE(page, nullptr);
    
    QVector<Unicode> u;
    auto textPage = page->d->prepareTextSearch(QString("A"), Page::Rotate0, &u);
    
    EXPECT_NE(textPage, nullptr);
    EXPECT_EQ(u.size(), 1);
    EXPECT_EQ(u[0], static_cast<Unicode>('A'));
}

// Test with long search string
TEST_F(PageDataTest_1441, PrepareTextSearchLongString_1441) {
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    std::unique_ptr<Poppler::Page> page(doc->page(0));
    ASSERT_NE(page, nullptr);
    
    QString longText(1000, 'x');
    QVector<Unicode> u;
    auto textPage = page->d->prepareTextSearch(longText, Page::Rotate0, &u);
    
    EXPECT_NE(textPage, nullptr);
    EXPECT_EQ(u.size(), 1000);
}

// Test performSingleTextSearch with valid TextPage
TEST_F(PageDataTest_1441, PerformSingleTextSearchNotFound_1441) {
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    std::unique_ptr<Poppler::Page> page(doc->page(0));
    ASSERT_NE(page, nullptr);
    
    QString searchText("ZZZZNONEXISTENT");
    QVector<Unicode> u;
    auto textPage = page->d->prepareTextSearch(searchText, Page::Rotate0, &u);
    ASSERT_NE(textPage, nullptr);
    
    double sLeft = 0, sTop = 0, sRight = 0, sBottom = 0;
    bool found = PageData::performSingleTextSearch(
        textPage.get(), u, sLeft, sTop, sRight, sBottom,
        Page::FromTop, true, false, false, false);
    
    EXPECT_FALSE(found);
}

// Test performMultipleTextSearch with non-matching text
TEST_F(PageDataTest_1441, PerformMultipleTextSearchNoResults_1441) {
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    std::unique_ptr<Poppler::Page> page(doc->page(0));
    ASSERT_NE(page, nullptr);
    
    QString searchText("ZZZZNONEXISTENT");
    QVector<Unicode> u;
    auto textPage = page->d->prepareTextSearch(searchText, Page::Rotate0, &u);
    ASSERT_NE(textPage, nullptr);
    
    QList<QRectF> results = PageData::performMultipleTextSearch(
        textPage.get(), u, true, false, false, false);
    
    EXPECT_TRUE(results.isEmpty());
}

// Test that Unicode vector content matches expected UCS4 conversion
TEST_F(PageDataTest_1441, PrepareTextSearchUCS4Conversion_1441) {
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    std::unique_ptr<Poppler::Page> page(doc->page(0));
    ASSERT_NE(page, nullptr);
    
    QString searchText("ABC123");
    QVector<Unicode> u;
    page->d->prepareTextSearch(searchText, Page::Rotate0, &u);
    
    ASSERT_EQ(u.size(), 6);
    EXPECT_EQ(u[0], static_cast<Unicode>('A'));
    EXPECT_EQ(u[1], static_cast<Unicode>('B'));
    EXPECT_EQ(u[2], static_cast<Unicode>('C'));
    EXPECT_EQ(u[3], static_cast<Unicode>('1'));
    EXPECT_EQ(u[4], static_cast<Unicode>('2'));
    EXPECT_EQ(u[5], static_cast<Unicode>('3'));
}

// Test with special characters
TEST_F(PageDataTest_1441, PrepareTextSearchSpecialChars_1441) {
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    std::unique_ptr<Poppler::Page> page(doc->page(0));
    ASSERT_NE(page, nullptr);
    
    QString searchText("test\n\ttab");
    QVector<Unicode> u;
    auto textPage = page->d->prepareTextSearch(searchText, Page::Rotate0, &u);
    
    EXPECT_NE(textPage, nullptr);
    EXPECT_EQ(u.size(), searchText.toUcs4().size());
}

// Test that multiple calls to prepareTextSearch are independent
TEST_F(PageDataTest_1441, PrepareTextSearchMultipleCalls_1441) {
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    std::unique_ptr<Poppler::Page> page(doc->page(0));
    ASSERT_NE(page, nullptr);
    
    QVector<Unicode> u1, u2;
    auto textPage1 = page->d->prepareTextSearch(QString("first"), Page::Rotate0, &u1);
    auto textPage2 = page->d->prepareTextSearch(QString("second"), Page::Rotate0, &u2);
    
    EXPECT_NE(textPage1, nullptr);
    EXPECT_NE(textPage2, nullptr);
    EXPECT_EQ(u1.size(), 5);
    EXPECT_EQ(u2.size(), 6);
}
