#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <QDomElement>
#include <QString>
#include <QChar>
#include <memory>
#include "poppler-private.h"  // Include the necessary header files

using namespace Poppler;
using ::testing::Return;
using ::testing::Mock;

// Mock classes to simulate dependencies
class MockLinkAction : public LinkAction {
public:
    MOCK_CONST_METHOD0(isOk, bool());
    MOCK_CONST_METHOD0(getKind, LinkActionKind());
};

class MockLinkDest : public LinkDest {
public:
    MOCK_METHOD0(isOk, bool());
};

class MockLinkGoTo : public LinkGoTo {
public:
    MOCK_CONST_METHOD0(getDest, const LinkDest*());
    MOCK_CONST_METHOD0(getNamedDest, const GooString*());
};

class MockLinkGoToR : public LinkGoToR {
public:
    MOCK_CONST_METHOD0(getDest, const LinkDest*());
    MOCK_CONST_METHOD0(getNamedDest, const GooString*());
    MOCK_CONST_METHOD0(getFileName, const GooString*());
};

// Unit tests
TEST_F(PopplerLinkActionTests_1287, linkActionToTocItem_NullAction_1287) {
    QDomElement element;
    linkActionToTocItem(nullptr, nullptr, &element);
    // Verifying no attributes set when null action
    EXPECT_EQ(element.attribute(QStringLiteral("DestinationName")), QString());
    EXPECT_EQ(element.attribute(QStringLiteral("Destination")), QString());
}

TEST_F(PopplerLinkActionTests_1288, linkActionToTocItem_InvalidKind_1288) {
    MockLinkAction action;
    QDomElement element;

    EXPECT_CALL(action, getKind())
        .WillOnce(Return(static_cast<LinkActionKind>(100)));  // Invalid kind

    linkActionToTocItem(&action, nullptr, &element);
    // Verifying no attributes set for invalid action kind
    EXPECT_EQ(element.attribute(QStringLiteral("DestinationName")), QString());
    EXPECT_EQ(element.attribute(QStringLiteral("Destination")), QString());
}

TEST_F(PopplerLinkActionTests_1289, linkActionToTocItem_GoTo_1289) {
    MockLinkGoTo action;
    QDomElement element;
    const LinkDest mockDest;

    EXPECT_CALL(action, getKind())
        .WillOnce(Return(actionGoTo));
    EXPECT_CALL(action, getDest())
        .WillOnce(Return(&mockDest));
    EXPECT_CALL(action, getNamedDest())
        .WillOnce(Return(nullptr));

    linkActionToTocItem(&action, nullptr, &element);
    // Verifying the destination is added to the element
    EXPECT_EQ(element.attribute(QStringLiteral("Destination")), QString());
}

TEST_F(PopplerLinkActionTests_1290, linkActionToTocItem_GoToR_1290) {
    MockLinkGoToR action;
    QDomElement element;
    const LinkDest mockDest;

    EXPECT_CALL(action, getKind())
        .WillOnce(Return(actionGoToR));
    EXPECT_CALL(action, getDest())
        .WillOnce(Return(&mockDest));
    EXPECT_CALL(action, getNamedDest())
        .WillOnce(Return(nullptr));
    EXPECT_CALL(action, getFileName())
        .WillOnce(Return(nullptr));

    linkActionToTocItem(&action, nullptr, &element);
    // Verifying the external file name and destination are added
    EXPECT_EQ(element.attribute(QStringLiteral("ExternalFileName")), QString());
    EXPECT_EQ(element.attribute(QStringLiteral("Destination")), QString());
}

TEST_F(PopplerLinkActionTests_1291, linkActionToTocItem_EmptyNamedDest_1291) {
    MockLinkGoTo action;
    QDomElement element;
    const GooString mockNamedDest("someDestination");

    EXPECT_CALL(action, getKind())
        .WillOnce(Return(actionGoTo));
    EXPECT_CALL(action, getDest())
        .WillOnce(Return(nullptr));
    EXPECT_CALL(action, getNamedDest())
        .WillOnce(Return(&mockNamedDest));

    linkActionToTocItem(&action, nullptr, &element);
    // Verifying the DestinationName attribute is set from namedDest
    EXPECT_EQ(element.attribute(QStringLiteral("DestinationName")), QString("someDestination"));
}

TEST_F(PopplerLinkActionTests_1292, linkActionToTocItem_InvalidDest_1292) {
    MockLinkGoTo action;
    QDomElement element;

    EXPECT_CALL(action, getKind())
        .WillOnce(Return(actionGoTo));
    EXPECT_CALL(action, getDest())
        .WillOnce(Return(nullptr));

    linkActionToTocItem(&action, nullptr, &element);
    // Verifying no attributes set when destination is invalid
    EXPECT_EQ(element.attribute(QStringLiteral("Destination")), QString());
}

TEST_F(PopplerLinkActionTests_1293, linkActionToTocItem_ValidURI_1293) {
    MockLinkAction action;
    QDomElement element;
    const std::string uri = "http://example.com";

    EXPECT_CALL(action, getKind())
        .WillOnce(Return(actionURI));
    EXPECT_CALL(action, getDest())
        .WillOnce(Return(nullptr));
    EXPECT_CALL(action, getNamedDest())
        .WillOnce(Return(nullptr));

    linkActionToTocItem(&action, nullptr, &element);
    // Verifying URI attribute is set
    EXPECT_EQ(element.attribute(QStringLiteral("DestinationURI")), QString::fromStdString(uri));
}