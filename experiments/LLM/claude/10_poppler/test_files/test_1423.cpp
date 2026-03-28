#include <gtest/gtest.h>
#include <QDomDocument>
#include <QDomNode>
#include <QDomElement>
#include <QString>

// Include the header for RichMediaAnnotation
// Based on the poppler qt5 structure
#include "poppler-annotation.h"

using namespace Poppler;

class RichMediaAnnotationTest_1423 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test that a default-constructed RichMediaAnnotation has the correct subType
TEST_F(RichMediaAnnotationTest_1423, SubTypeIsRichMedia_1423) {
    RichMediaAnnotation annotation;
    EXPECT_EQ(annotation.subType(), Annotation::ARichMedia);
}

// Test that store appends a richMedia element to the given node
TEST_F(RichMediaAnnotationTest_1423, StoreAppendsRichMediaElement_1423) {
    RichMediaAnnotation annotation;
    QDomDocument document;
    QDomElement root = document.createElement(QStringLiteral("root"));
    document.appendChild(root);

    QDomNode node = root;
    annotation.store(node, document);

    // Check that a child element named "richMedia" was appended
    QDomNodeList children = root.childNodes();
    bool foundRichMedia = false;
    for (int i = 0; i < children.count(); ++i) {
        QDomElement elem = children.at(i).toElement();
        if (!elem.isNull() && elem.tagName() == QStringLiteral("richMedia")) {
            foundRichMedia = true;
            break;
        }
    }
    EXPECT_TRUE(foundRichMedia);
}

// Test that settings is null by default
TEST_F(RichMediaAnnotationTest_1423, DefaultSettingsIsNull_1423) {
    RichMediaAnnotation annotation;
    EXPECT_EQ(annotation.settings(), nullptr);
}

// Test that content is null by default
TEST_F(RichMediaAnnotationTest_1423, DefaultContentIsNull_1423) {
    RichMediaAnnotation annotation;
    EXPECT_EQ(annotation.content(), nullptr);
}

// Test setSettings and settings getter
TEST_F(RichMediaAnnotationTest_1423, SetAndGetSettings_1423) {
    RichMediaAnnotation annotation;
    auto *settings = new RichMediaAnnotation::Settings();
    annotation.setSettings(settings);
    EXPECT_EQ(annotation.settings(), settings);
}

// Test setContent and content getter
TEST_F(RichMediaAnnotationTest_1423, SetAndGetContent_1423) {
    RichMediaAnnotation annotation;
    auto *content = new RichMediaAnnotation::Content();
    annotation.setContent(content);
    EXPECT_EQ(annotation.content(), content);
}

// Test that setting settings to nullptr works
TEST_F(RichMediaAnnotationTest_1423, SetSettingsToNull_1423) {
    RichMediaAnnotation annotation;
    auto *settings = new RichMediaAnnotation::Settings();
    annotation.setSettings(settings);
    EXPECT_NE(annotation.settings(), nullptr);
    annotation.setSettings(nullptr);
    EXPECT_EQ(annotation.settings(), nullptr);
}

// Test that setting content to nullptr works
TEST_F(RichMediaAnnotationTest_1423, SetContentToNull_1423) {
    RichMediaAnnotation annotation;
    auto *content = new RichMediaAnnotation::Content();
    annotation.setContent(content);
    EXPECT_NE(annotation.content(), nullptr);
    annotation.setContent(nullptr);
    EXPECT_EQ(annotation.content(), nullptr);
}

// Test constructing from a QDomNode (empty node)
TEST_F(RichMediaAnnotationTest_1423, ConstructFromEmptyDomNode_1423) {
    QDomDocument document;
    QDomElement root = document.createElement(QStringLiteral("annotation"));
    document.appendChild(root);

    QDomNode node = root;
    RichMediaAnnotation annotation(node);
    EXPECT_EQ(annotation.subType(), Annotation::ARichMedia);
}

// Test store on an empty document
TEST_F(RichMediaAnnotationTest_1423, StoreOnEmptyDocument_1423) {
    RichMediaAnnotation annotation;
    QDomDocument document;
    QDomElement root = document.createElement(QStringLiteral("annotations"));
    document.appendChild(root);

    QDomNode node = root;
    annotation.store(node, document);

    // Verify node now has children
    EXPECT_GT(root.childNodes().count(), 0);
}

// Test multiple store calls add multiple richMedia elements
TEST_F(RichMediaAnnotationTest_1423, MultipleStoreCalls_1423) {
    RichMediaAnnotation annotation;
    QDomDocument document;
    QDomElement root = document.createElement(QStringLiteral("root"));
    document.appendChild(root);

    QDomNode node = root;
    annotation.store(node, document);
    annotation.store(node, document);

    int richMediaCount = 0;
    QDomNodeList children = root.childNodes();
    for (int i = 0; i < children.count(); ++i) {
        QDomElement elem = children.at(i).toElement();
        if (!elem.isNull() && elem.tagName() == QStringLiteral("richMedia")) {
            richMediaCount++;
        }
    }
    EXPECT_GE(richMediaCount, 2);
}

// Test replacing settings
TEST_F(RichMediaAnnotationTest_1423, ReplaceSettings_1423) {
    RichMediaAnnotation annotation;
    auto *settings1 = new RichMediaAnnotation::Settings();
    auto *settings2 = new RichMediaAnnotation::Settings();
    annotation.setSettings(settings1);
    EXPECT_EQ(annotation.settings(), settings1);
    annotation.setSettings(settings2);
    EXPECT_EQ(annotation.settings(), settings2);
}

// Test replacing content
TEST_F(RichMediaAnnotationTest_1423, ReplaceContent_1423) {
    RichMediaAnnotation annotation;
    auto *content1 = new RichMediaAnnotation::Content();
    auto *content2 = new RichMediaAnnotation::Content();
    annotation.setContent(content1);
    EXPECT_EQ(annotation.content(), content1);
    annotation.setContent(content2);
    EXPECT_EQ(annotation.content(), content2);
}
