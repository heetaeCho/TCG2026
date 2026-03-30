#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-private.cc"

#include "Link.h"



using namespace Poppler;

using testing::NiceMock;

using testing::_;



class MockDocumentData : public DocumentData {

public:

    MOCK_METHOD(void, notifyXRefReconstructed, (), (override));

};



class MockLinkAction : public LinkAction {

public:

    MOCK_CONST_METHOD0(isOk, bool());

    MOCK_CONST_METHOD0(getKind, LinkActionKind());

};



class MockLinkDest : public LinkDest {

public:

    MOCK_CONST_METHOD0(isOk, bool());

};



class MockLinkGoTo : public LinkGoTo {

public:

    using LinkGoTo::LinkGoTo;

    MOCK_CONST_METHOD0(getDest, const LinkDest*());

    MOCK_CONST_METHOD0(getNamedDest, const GooString*());

};



class MockLinkGoToR : public LinkGoToR {

public:

    using LinkGoToR::LinkGoToR;

    MOCK_CONST_METHOD0(getFileName, const GooString*());

    MOCK_CONST_METHOD0(getDest, const LinkDest*());

    MOCK_CONST_METHOD0(getNamedDest, const GooString*());

};



class MockGooString : public GooString {

public:

    using GooString::GooString;

    MOCK_CONST_METHOD0(c_str, char*());

    MOCK_CONST_METHOD0(size, size_t());

    MOCK_CONST_METHOD0(toStr, std::string());

};



class LinkActionToTocItemTest : public ::testing::Test {

protected:

    QDomElement element;

    DocumentData docData;



    void SetUp() override {

        element = QDomDocument().createElement("test");

        element.clearAttributes();

    }

};



TEST_F(LinkActionToTocItemTest, NullLinkAction_1287) {

    linkActionToTocItem(nullptr, &docData, &element);

    EXPECT_TRUE(element.attributes().isEmpty());

}



TEST_F(LinkActionToTocItemTest, NullElement_1287) {

    MockLinkAction mockLinkAction;

    linkActionToTocItem(&mockLinkAction, &docData, nullptr);

    // No expectation on element since it's null

}



TEST_F(LinkActionToTocItemTest, InvalidLinkActionKind_1287) {

    MockLinkAction mockLinkAction;

    ON_CALL(mockLinkAction, getKind()).WillByDefault(testing::Return(actionUnknown));

    linkActionToTocItem(&mockLinkAction, &docData, &element);

    EXPECT_TRUE(element.attributes().isEmpty());

}



TEST_F(LinkActionToTocItemTest, ActionGoTo_WithNamedDest_1287) {

    MockLinkGoTo mockLinkGoTo(nullptr);

    MockGooString mockNamedDest("named_dest");

    ON_CALL(mockLinkGoTo, getKind()).WillByDefault(testing::Return(actionGoTo));

    ON_CALL(mockLinkGoTo, getNamedDest()).WillByDefault(testing::Return(&mockNamedDest));

    ON_CALL(mockNamedDest, c_str()).WillByDefault(testing::Return("named_dest"));

    ON_CALL(mockNamedDest, size()).WillByDefault(testing::Return(10));



    linkActionToTocItem(&mockLinkGoTo, &docData, &element);

    EXPECT_EQ(element.attribute(QStringLiteral("DestinationName")), QStringLiteral("named_dest"));

}



TEST_F(LinkActionToTocItemTest, ActionGoTo_WithValidDest_1287) {

    MockLinkGoTo mockLinkGoTo(nullptr);

    MockLinkDest mockDest;

    ON_CALL(mockLinkGoTo, getKind()).WillByDefault(testing::Return(actionGoTo));

    ON_CALL(mockLinkGoTo, getNamedDest()).WillByDefault(testing::Return(nullptr));

    ON_CALL(mockLinkGoTo, getDest()).WillByDefault(testing::Return(&mockDest));

    ON_CALL(mockDest, isOk()).WillByDefault(testing::Return(true));



    linkActionToTocItem(&mockLinkGoTo, &docData, &element);

    EXPECT_FALSE(element.attribute(QStringLiteral("Destination")).isEmpty());

}



TEST_F(LinkActionToTocItemTest, ActionGoToR_WithNamedDest_1287) {

    MockLinkGoToR mockLinkGoToR(nullptr, nullptr);

    MockGooString mockFileName("file_name.pdf");

    MockGooString mockNamedDest("named_dest");

    ON_CALL(mockLinkGoToR, getKind()).WillByDefault(testing::Return(actionGoToR));

    ON_CALL(mockLinkGoToR, getNamedDest()).WillByDefault(testing::Return(&mockNamedDest));

    ON_CALL(mockLinkGoToR, getFileName()).WillByDefault(testing::Return(&mockFileName));

    ON_CALL(mockNamedDest, c_str()).WillByDefault(testing::Return("named_dest"));

    ON_CALL(mockNamedDest, size()).WillByDefault(testing::Return(10));

    ON_CALL(mockFileName, toStr()).WillByDefault(testing::Return("file_name.pdf"));



    linkActionToTocItem(&mockLinkGoToR, &docData, &element);

    EXPECT_EQ(element.attribute(QStringLiteral("DestinationName")), QStringLiteral("named_dest"));

    EXPECT_EQ(element.attribute(QStringLiteral("ExternalFileName")), QStringLiteral("file_name.pdf"));

}



TEST_F(LinkActionToTocItemTest, ActionGoToR_WithValidDest_1287) {

    MockLinkGoToR mockLinkGoToR(nullptr, nullptr);

    MockGooString mockFileName("file_name.pdf");

    MockLinkDest mockDest;

    ON_CALL(mockLinkGoToR, getKind()).WillByDefault(testing::Return(actionGoToR));

    ON_CALL(mockLinkGoToR, getNamedDest()).WillByDefault(testing::Return(nullptr));

    ON_CALL(mockLinkGoToR, getFileName()).WillByDefault(testing::Return(&mockFileName));

    ON_CALL(mockLinkGoToR, getDest()).WillByDefault(testing::Return(&mockDest));

    ON_CALL(mockDest, isOk()).WillByDefault(testing::Return(true));

    ON_CALL(mockFileName, toStr()).WillByDefault(testing::Return("file_name.pdf"));



    linkActionToTocItem(&mockLinkGoToR, &docData, &element);

    EXPECT_FALSE(element.attribute(QStringLiteral("Destination")).isEmpty());

    EXPECT_EQ(element.attribute(QStringLiteral("ExternalFileName")), QStringLiteral("file_name.pdf"));

}



TEST_F(LinkActionToTocItemTest, ActionURI_1287) {

    MockLinkAction mockLinkURI;

    MockGooString mockURI("http://example.com");

    ON_CALL(mockLinkURI, getKind()).WillByDefault(testing::Return(actionURI));

    EXPECT_CALL(mockLinkURI, toStr()).WillOnce(testing::ReturnRefOfCopy(mockURI));



    linkActionToTocItem(&mockLinkURI, &docData, &element);

    EXPECT_EQ(element.attribute(QStringLiteral("DestinationURI")), QStringLiteral("http://example.com"));

}
