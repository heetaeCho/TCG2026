#include <gtest/gtest.h>

#include <QDomDocument>

#include <QDomNode>

#include "poppler-annotation.h"



using namespace Poppler;



class RichMediaAnnotationTest_1423 : public ::testing::Test {

protected:

    QDomDocument document;

    QDomNode node;

    RichMediaAnnotation annotation;



    void SetUp() override {

        document = QDomDocument();

        node = document.createProcessingInstruction("xml", "version=\"1.0\"");

        document.appendChild(node);

    }

};



TEST_F(RichMediaAnnotationTest_1423, StoreCreatesRichMediaElement_1423) {

    annotation.store(node, document);



    QDomNodeList richMediaElements = document.elementsByTagName(QStringLiteral("richMedia"));

    EXPECT_EQ(richMediaElements.count(), 1);

}



TEST_F(RichMediaAnnotationTest_1423, StoreAppendsToProvidedNode_1423) {

    annotation.store(node, document);



    QDomNode firstChild = node.firstChild();

    EXPECT_TRUE(firstChild.isElement());

    EXPECT_EQ(firstChild.toElement().tagName(), QStringLiteral("richMedia"));

}



TEST_F(RichMediaAnnotationTest_1423, StoreDoesNotModifyDocumentIfNoNodeProvided_1423) {

    QDomNode emptyNode;

    annotation.store(emptyNode, document);



    QDomNodeList richMediaElements = document.elementsByTagName(QStringLiteral("richMedia"));

    EXPECT_EQ(richMediaElements.count(), 0);

}



TEST_F(RichMediaAnnotationTest_1423, StoreHandlesEmptyDocument_1423) {

    QDomDocument emptyDocument;

    annotation.store(node, emptyDocument);



    QDomNodeList richMediaElements = emptyDocument.elementsByTagName(QStringLiteral("richMedia"));

    EXPECT_EQ(richMediaElements.count(), 1);

}
