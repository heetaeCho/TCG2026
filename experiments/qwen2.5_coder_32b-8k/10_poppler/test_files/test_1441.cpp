#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-page-private.h"

#include <QString>

#include <QVector>



using namespace Poppler;



class PageDataTest_1441 : public ::testing::Test {

protected:

    void SetUp() override {

        pageData = std::make_unique<PageData>();

        // Mocking parentDoc and its dependencies if necessary

    }



    void TearDown() override {

        pageData.reset();

    }



    std::unique_ptr<PageData> pageData;

};



TEST_F(PageDataTest_1441, PrepareTextSearch_ValidInput_ReturnsNonNull_1441) {

    QVector<Unicode> ucs4;

    QString text = "test";

    auto result = pageData->prepareTextSearch(text, Page::Rotation0, &ucs4);

    EXPECT_NE(result.get(), nullptr);

}



TEST_F(PageDataTest_1441, PrepareTextSearch_EmptyString_ReturnsNonNull_1441) {

    QVector<Unicode> ucs4;

    QString text = "";

    auto result = pageData->prepareTextSearch(text, Page::Rotation0, &ucs4);

    EXPECT_NE(result.get(), nullptr);

}



TEST_F(PageDataTest_1441, PrepareTextSearch_RotationBoundary_ReturnsNonNull_1441) {

    QVector<Unicode> ucs4;

    QString text = "test";

    for (int i = 0; i < 360; i += 90) {

        auto result = pageData->prepareTextSearch(text, static_cast<Page::Rotation>(i / 90), &ucs4);

        EXPECT_NE(result.get(), nullptr);

    }

}



TEST_F(PageDataTest_1441, PrepareTextSearch_UConversion_ChecksCorrectness_1441) {

    QVector<Unicode> ucs4;

    QString text = "test";

    pageData->prepareTextSearch(text, Page::Rotation0, &ucs4);

    QVector<Unicode> expectedUcs4 = text.toUcs4();

    EXPECT_EQ(ucs4, expectedUcs4);

}



TEST_F(PageDataTest_1441, PrepareTextSearch_NullPointer_ReturnsNonNull_1441) {

    QString text = "test";

    auto result = pageData->prepareTextSearch(text, Page::Rotation0, nullptr);

    EXPECT_NE(result.get(), nullptr);

}
