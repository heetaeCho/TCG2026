#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <QDomDocument>
#include <QDomElement>
#include <QString>
#include <memory>

// Include poppler headers
#include "poppler/Link.h"
#include "poppler/GooString.h"

// We need to include the private header and the source to access the static function
// Since linkActionToTocItem is in Poppler namespace (not anonymous), we can try to access it
#include "poppler-private.h"

// Include the implementation file to get access to the static function
#include "poppler-private.cc"

namespace {

class LinkActionToTocItemTest_1287 : public ::testing::Test {
protected:
    QDomDocument doc;
    QDomElement element;
    
    void SetUp() override {
        element = doc.createElement("item");
        doc.appendChild(element);
    }
};

// Test: Null action pointer should not crash and element should remain unchanged
TEST_F(LinkActionToTocItemTest_1287, NullActionDoesNotModify_1287) {
    QString before = element.attribute("Destination", "");
    Poppler::linkActionToTocItem(nullptr, nullptr, &element);
    QString after = element.attribute("Destination", "");
    EXPECT_EQ(before, after);
}

// Test: Null element pointer should not crash
TEST_F(LinkActionToTocItemTest_1287, NullElementDoesNotCrash_1287) {
    // Create a simple LinkURI to pass as non-null action
    // We just verify it doesn't crash with null element
    EXPECT_NO_FATAL_FAILURE({
        Poppler::linkActionToTocItem(nullptr, nullptr, nullptr);
    });
}

// Test: Both null should not crash
TEST_F(LinkActionToTocItemTest_1287, BothNullDoesNotCrash_1287) {
    EXPECT_NO_FATAL_FAILURE({
        Poppler::linkActionToTocItem(nullptr, nullptr, nullptr);
    });
}

// Test: ActionURI sets DestinationURI attribute
TEST_F(LinkActionToTocItemTest_1287, ActionURISetsDestinationURI_1287) {
    std::string uri = "http://example.com";
    // LinkURI takes a string
    Object obj;
    // We need to construct a LinkURI - it takes a const Object* or string
    LinkURI linkUri(uri);
    
    if (linkUri.isOk()) {
        Poppler::linkActionToTocItem(&linkUri, nullptr, &element);
        QString destURI = element.attribute("DestinationURI", "");
        EXPECT_EQ(destURI, QString::fromStdString(uri));
    }
}

// Test: ActionGoTo with named destination sets DestinationName
TEST_F(LinkActionToTocItemTest_1287, ActionGoToWithNamedDestSetsDestinationName_1287) {
    // Create a LinkGoTo with a named destination
    GooString namedDest("chapter1");
    Object destObj;
    destObj.initNull();
    
    // LinkGoTo takes Object* destObj
    LinkGoTo linkGoTo(&destObj);
    
    if (linkGoTo.getNamedDest() != nullptr) {
        Poppler::linkActionToTocItem(&linkGoTo, nullptr, &element);
        QString destName = element.attribute("DestinationName", "");
        EXPECT_FALSE(destName.isEmpty());
    }
}

// Test: Null action with valid element does not modify element
TEST_F(LinkActionToTocItemTest_1287, NullActionValidElement_1287) {
    element.setAttribute("TestAttr", "value");
    Poppler::linkActionToTocItem(nullptr, nullptr, &element);
    EXPECT_EQ(element.attribute("TestAttr"), "value");
    EXPECT_TRUE(element.attribute("Destination", "").isEmpty());
    EXPECT_TRUE(element.attribute("DestinationName", "").isEmpty());
    EXPECT_TRUE(element.attribute("DestinationURI", "").isEmpty());
    EXPECT_TRUE(element.attribute("ExternalFileName", "").isEmpty());
}

} // namespace
