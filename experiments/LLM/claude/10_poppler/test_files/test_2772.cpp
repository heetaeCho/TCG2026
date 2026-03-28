#include <gtest/gtest.h>
#include <QDomDocument>
#include <QDomNode>
#include <QDomElement>
#include <QString>

// Include the header for Poppler annotations
#include "poppler-annotation.h"

using namespace Poppler;

class RichMediaAnnotationTest_2772 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }

    QDomDocument createDocument() {
        QDomDocument doc;
        return doc;
    }

    QDomNode createEmptyNode() {
        QDomDocument doc;
        QDomElement root = doc.createElement("annotation");
        doc.appendChild(root);
        return doc.documentElement();
    }

    QDomNode createNodeWithRichMedia() {
        QDomDocument doc;
        QDomElement root = doc.createElement("annotation");
        doc.appendChild(root);

        QDomElement richMedia = doc.createElement("richMedia");
        root.appendChild(richMedia);

        return doc.documentElement();
    }

    QDomNode createNodeWithNonRichMediaChildren() {
        QDomDocument doc;
        QDomElement root = doc.createElement("annotation");
        doc.appendChild(root);

        QDomElement child1 = doc.createElement("otherTag1");
        root.appendChild(child1);
        QDomElement child2 = doc.createElement("otherTag2");
        root.appendChild(child2);

        return doc.documentElement();
    }

    QDomNode createNodeWithMixedChildren() {
        QDomDocument doc;
        QDomElement root = doc.createElement("annotation");
        doc.appendChild(root);

        QDomElement child1 = doc.createElement("someOtherTag");
        root.appendChild(child1);
        QDomElement richMedia = doc.createElement("richMedia");
        root.appendChild(richMedia);
        QDomElement child3 = doc.createElement("anotherTag");
        root.appendChild(child3);

        return doc.documentElement();
    }
};

// Test default constructor
TEST_F(RichMediaAnnotationTest_2772, DefaultConstructor_2772) {
    RichMediaAnnotation annotation;
    EXPECT_EQ(annotation.subType(), Annotation::ARichMedia);
}

// Test construction with empty QDomNode
TEST_F(RichMediaAnnotationTest_2772, ConstructWithEmptyDomNode_2772) {
    QDomNode emptyNode;
    RichMediaAnnotation annotation(emptyNode);
    EXPECT_EQ(annotation.subType(), Annotation::ARichMedia);
}

// Test construction with a node that has no children
TEST_F(RichMediaAnnotationTest_2772, ConstructWithNoChildren_2772) {
    QDomNode node = createEmptyNode();
    RichMediaAnnotation annotation(node);
    EXPECT_EQ(annotation.subType(), Annotation::ARichMedia);
}

// Test construction with a node that has a richMedia child
TEST_F(RichMediaAnnotationTest_2772, ConstructWithRichMediaChild_2772) {
    QDomNode node = createNodeWithRichMedia();
    RichMediaAnnotation annotation(node);
    EXPECT_EQ(annotation.subType(), Annotation::ARichMedia);
}

// Test construction with a node that has non-richMedia children only
TEST_F(RichMediaAnnotationTest_2772, ConstructWithNonRichMediaChildren_2772) {
    QDomNode node = createNodeWithNonRichMediaChildren();
    RichMediaAnnotation annotation(node);
    EXPECT_EQ(annotation.subType(), Annotation::ARichMedia);
}

// Test construction with mixed children (richMedia among others)
TEST_F(RichMediaAnnotationTest_2772, ConstructWithMixedChildren_2772) {
    QDomNode node = createNodeWithMixedChildren();
    RichMediaAnnotation annotation(node);
    EXPECT_EQ(annotation.subType(), Annotation::ARichMedia);
}

// Test subType returns ARichMedia
TEST_F(RichMediaAnnotationTest_2772, SubTypeReturnsARichMedia_2772) {
    RichMediaAnnotation annotation;
    EXPECT_EQ(annotation.subType(), Annotation::ARichMedia);
}

// Test settings default is null
TEST_F(RichMediaAnnotationTest_2772, SettingsDefaultIsNull_2772) {
    RichMediaAnnotation annotation;
    EXPECT_EQ(annotation.settings(), nullptr);
}

// Test content default is null
TEST_F(RichMediaAnnotationTest_2772, ContentDefaultIsNull_2772) {
    RichMediaAnnotation annotation;
    EXPECT_EQ(annotation.content(), nullptr);
}

// Test setSettings and settings getter
TEST_F(RichMediaAnnotationTest_2772, SetAndGetSettings_2772) {
    RichMediaAnnotation annotation;
    auto *settings = new RichMediaAnnotation::Settings;
    annotation.setSettings(settings);
    EXPECT_EQ(annotation.settings(), settings);
}

// Test setContent and content getter
TEST_F(RichMediaAnnotationTest_2772, SetAndGetContent_2772) {
    RichMediaAnnotation annotation;
    auto *content = new RichMediaAnnotation::Content;
    annotation.setContent(content);
    EXPECT_EQ(annotation.content(), content);
}

// Test setting settings to nullptr
TEST_F(RichMediaAnnotationTest_2772, SetSettingsToNull_2772) {
    RichMediaAnnotation annotation;
    auto *settings = new RichMediaAnnotation::Settings;
    annotation.setSettings(settings);
    EXPECT_EQ(annotation.settings(), settings);
    annotation.setSettings(nullptr);
    EXPECT_EQ(annotation.settings(), nullptr);
}

// Test setting content to nullptr
TEST_F(RichMediaAnnotationTest_2772, SetContentToNull_2772) {
    RichMediaAnnotation annotation;
    auto *content = new RichMediaAnnotation::Content;
    annotation.setContent(content);
    EXPECT_EQ(annotation.content(), content);
    annotation.setContent(nullptr);
    EXPECT_EQ(annotation.content(), nullptr);
}

// Test store method does not crash with empty node
TEST_F(RichMediaAnnotationTest_2772, StoreWithEmptyDocument_2772) {
    RichMediaAnnotation annotation;
    QDomDocument doc;
    QDomElement root = doc.createElement("annotation");
    doc.appendChild(root);
    QDomNode node = root;
    EXPECT_NO_FATAL_FAILURE(annotation.store(node, doc));
}

// Test store method with settings and content set
TEST_F(RichMediaAnnotationTest_2772, StoreWithSettingsAndContent_2772) {
    RichMediaAnnotation annotation;
    auto *settings = new RichMediaAnnotation::Settings;
    auto *content = new RichMediaAnnotation::Content;
    annotation.setSettings(settings);
    annotation.setContent(content);

    QDomDocument doc;
    QDomElement root = doc.createElement("annotation");
    doc.appendChild(root);
    QDomNode node = root;
    EXPECT_NO_FATAL_FAILURE(annotation.store(node, doc));
}

// Test replacing settings
TEST_F(RichMediaAnnotationTest_2772, ReplaceSettings_2772) {
    RichMediaAnnotation annotation;
    auto *settings1 = new RichMediaAnnotation::Settings;
    auto *settings2 = new RichMediaAnnotation::Settings;
    annotation.setSettings(settings1);
    EXPECT_EQ(annotation.settings(), settings1);
    annotation.setSettings(settings2);
    EXPECT_EQ(annotation.settings(), settings2);
}

// Test replacing content
TEST_F(RichMediaAnnotationTest_2772, ReplaceContent_2772) {
    RichMediaAnnotation annotation;
    auto *content1 = new RichMediaAnnotation::Content;
    auto *content2 = new RichMediaAnnotation::Content;
    annotation.setContent(content1);
    EXPECT_EQ(annotation.content(), content1);
    annotation.setContent(content2);
    EXPECT_EQ(annotation.content(), content2);
}

// Test construction with node having richMedia as first child
TEST_F(RichMediaAnnotationTest_2772, ConstructWithRichMediaAsFirstChild_2772) {
    QDomDocument doc;
    QDomElement root = doc.createElement("annotation");
    doc.appendChild(root);
    QDomElement richMedia = doc.createElement("richMedia");
    root.appendChild(richMedia);
    QDomElement other = doc.createElement("other");
    root.appendChild(other);

    RichMediaAnnotation annotation(root);
    EXPECT_EQ(annotation.subType(), Annotation::ARichMedia);
}

// Test construction with deeply nested structure
TEST_F(RichMediaAnnotationTest_2772, ConstructWithDeeplyNestedRichMedia_2772) {
    QDomDocument doc;
    QDomElement root = doc.createElement("annotation");
    doc.appendChild(root);

    // richMedia as direct child, with nested elements
    QDomElement richMedia = doc.createElement("richMedia");
    QDomElement innerElement = doc.createElement("innerConfig");
    richMedia.appendChild(innerElement);
    root.appendChild(richMedia);

    RichMediaAnnotation annotation(root);
    EXPECT_EQ(annotation.subType(), Annotation::ARichMedia);
}
