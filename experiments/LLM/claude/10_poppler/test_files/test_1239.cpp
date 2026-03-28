#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "poppler-link.h"
#include "poppler-link-private.h"

#include <QRectF>
#include <QString>
#include <QUrl>
#include <memory>

using namespace Poppler;

class LinkPrivateTest_1239 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that LinkPrivate::get returns a non-null pointer for a valid Link object
TEST_F(LinkPrivateTest_1239, GetReturnsNonNullForValidLink_1239)
{
    // Create a LinkGoto as a concrete Link subclass
    LinkGoto link(QRectF(0, 0, 100, 100), QString(), LinkDestination("0;/Page;0;0;0;0;0;0;0;0;0"));
    LinkPrivate *priv = LinkPrivate::get(&link);
    EXPECT_NE(priv, nullptr);
}

// Test that LinkPrivate::get returns consistent pointer for the same Link
TEST_F(LinkPrivateTest_1239, GetReturnsSamePointerForSameLink_1239)
{
    LinkGoto link(QRectF(0, 0, 50, 50), QString(), LinkDestination("0;/Page;0;0;0;0;0;0;0;0;0"));
    LinkPrivate *priv1 = LinkPrivate::get(&link);
    LinkPrivate *priv2 = LinkPrivate::get(&link);
    EXPECT_EQ(priv1, priv2);
}

// Test that different Link objects have different private pointers
TEST_F(LinkPrivateTest_1239, DifferentLinksHaveDifferentPrivatePointers_1239)
{
    LinkGoto link1(QRectF(0, 0, 100, 100), QString(), LinkDestination("0;/Page;0;0;0;0;0;0;0;0;0"));
    LinkGoto link2(QRectF(10, 10, 200, 200), QString(), LinkDestination("0;/Page;0;0;0;0;0;0;0;0;0"));
    LinkPrivate *priv1 = LinkPrivate::get(&link1);
    LinkPrivate *priv2 = LinkPrivate::get(&link2);
    EXPECT_NE(priv1, priv2);
}

// Test with LinkBrowse as another concrete subclass
TEST_F(LinkPrivateTest_1239, GetWorksForLinkBrowse_1239)
{
    LinkBrowse link(QRectF(0, 0, 100, 100), "https://example.com");
    LinkPrivate *priv = LinkPrivate::get(&link);
    EXPECT_NE(priv, nullptr);
}

// Test with LinkExecute as another concrete subclass
TEST_F(LinkPrivateTest_1239, GetWorksForLinkExecute_1239)
{
    LinkExecute link(QRectF(0, 0, 100, 100), "test.exe", QStringList());
    LinkPrivate *priv = LinkPrivate::get(&link);
    EXPECT_NE(priv, nullptr);
}

// Test with LinkJavaScript as another concrete subclass
TEST_F(LinkPrivateTest_1239, GetWorksForLinkJavaScript_1239)
{
    LinkJavaScript link(QRectF(0, 0, 100, 100), "alert('test');");
    LinkPrivate *priv = LinkPrivate::get(&link);
    EXPECT_NE(priv, nullptr);
}

// Test with a link created with zero-area rectangle (boundary condition)
TEST_F(LinkPrivateTest_1239, GetWorksForZeroAreaLink_1239)
{
    LinkBrowse link(QRectF(0, 0, 0, 0), "https://example.com");
    LinkPrivate *priv = LinkPrivate::get(&link);
    EXPECT_NE(priv, nullptr);
}

// Test with negative coordinates in rectangle (boundary condition)
TEST_F(LinkPrivateTest_1239, GetWorksForNegativeCoordinates_1239)
{
    LinkBrowse link(QRectF(-10, -20, 100, 200), "https://example.com");
    LinkPrivate *priv = LinkPrivate::get(&link);
    EXPECT_NE(priv, nullptr);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
