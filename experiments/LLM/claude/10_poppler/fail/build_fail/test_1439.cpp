#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <QRectF>
#include <QString>
#include <QVector>
#include <memory>

// Include necessary headers
#include "poppler-qt5.h"
#include "poppler-page-private.h"
#include "poppler-private.h"
#include "Link.h"

using namespace Poppler;

class PageDataTest_1439 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test that convertLinkActionToLink returns nullptr when given a null LinkAction
TEST_F(PageDataTest_1439, ConvertNullLinkActionReturnsNull_1439) {
    QRectF linkArea(0, 0, 100, 100);
    Link *result = PageData::convertLinkActionToLink(nullptr, nullptr, linkArea);
    EXPECT_EQ(result, nullptr);
}

// Test that convertLinkActionToLink static method with null parentDoc and null action returns nullptr
TEST_F(PageDataTest_1439, ConvertNullActionAndNullParentDocReturnsNull_1439) {
    QRectF linkArea(10, 20, 30, 40);
    Link *result = PageData::convertLinkActionToLink(nullptr, nullptr, linkArea);
    EXPECT_EQ(result, nullptr);
}

// Test instance method delegates to static method - null action should return null
TEST_F(PageDataTest_1439, InstanceMethodNullActionReturnsNull_1439) {
    PageData pageData;
    pageData.parentDoc = nullptr;
    QRectF linkArea(0, 0, 50, 50);
    const Link *result = pageData.convertLinkActionToLink(nullptr, linkArea);
    EXPECT_EQ(result, nullptr);
}

// Test with empty QRectF
TEST_F(PageDataTest_1439, ConvertWithEmptyRectAndNullAction_1439) {
    QRectF emptyRect;
    Link *result = PageData::convertLinkActionToLink(nullptr, nullptr, emptyRect);
    EXPECT_EQ(result, nullptr);
}

// Test with negative coordinates in QRectF
TEST_F(PageDataTest_1439, ConvertWithNegativeRectAndNullAction_1439) {
    QRectF negativeRect(-10, -20, 5, 5);
    Link *result = PageData::convertLinkActionToLink(nullptr, nullptr, negativeRect);
    EXPECT_EQ(result, nullptr);
}

// Test with zero-size QRectF
TEST_F(PageDataTest_1439, ConvertWithZeroSizeRectAndNullAction_1439) {
    QRectF zeroRect(0, 0, 0, 0);
    Link *result = PageData::convertLinkActionToLink(nullptr, nullptr, zeroRect);
    EXPECT_EQ(result, nullptr);
}

// Test instance method with parentDoc set to nullptr
TEST_F(PageDataTest_1439, InstanceMethodWithNullParentDoc_1439) {
    PageData pageData;
    pageData.parentDoc = nullptr;
    pageData.transition = nullptr;
    QRectF linkArea(0, 0, 100, 200);
    const Link *result = pageData.convertLinkActionToLink(nullptr, linkArea);
    EXPECT_EQ(result, nullptr);
}

// Test with large QRectF values
TEST_F(PageDataTest_1439, ConvertWithLargeRectAndNullAction_1439) {
    QRectF largeRect(0, 0, 1e6, 1e6);
    Link *result = PageData::convertLinkActionToLink(nullptr, nullptr, largeRect);
    EXPECT_EQ(result, nullptr);
}

// Test that the transition member can be initialized
TEST_F(PageDataTest_1439, PageDataDefaultTransitionIsAccessible_1439) {
    PageData pageData;
    pageData.parentDoc = nullptr;
    pageData.transition = nullptr;
    EXPECT_EQ(pageData.transition, nullptr);
    EXPECT_EQ(pageData.parentDoc, nullptr);
}
