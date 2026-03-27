#include <gtest/gtest.h>

#include <QDomNode>

#include <QDomDocument>

#include <QString>

#include "poppler-annotation.h"



using namespace Poppler;



class RichMediaAnnotationTest_2772 : public ::testing::Test {

protected:

    QDomDocument doc;

    QDomElement richMediaElement;



    void SetUp() override {

        doc.setContent("<root><richMedia></richMedia></root>");

        richMediaElement = doc.firstChild().firstChild().toElement();

    }

};



TEST_F(RichMediaAnnotationTest_2772, ConstructorWithValidNode_2772) {

    QDomNode node(richMediaElement);

    RichMediaAnnotation annotation(node);



    EXPECT_EQ(annotation.subType(), Annotation::SubType::RichMedia);

}



TEST_F(RichMediaAnnotationTest_2772, ConstructorWithEmptyNode_2772) {

    QDomNode emptyNode;

    EXPECT_NO_THROW(RichMediaAnnotation annotation(emptyNode));

}



TEST_F(RichMediaAnnotationTest_2772, SubTypeReturnsCorrectValue_2772) {

    QDomNode node(richMediaElement);

    RichMediaAnnotation annotation(node);



    EXPECT_EQ(annotation.subType(), Annotation::SubType::RichMedia);

}



// Assuming settings and content are not initialized by default, thus should return nullptr

TEST_F(RichMediaAnnotationTest_2772, SettingsInitiallyNullptr_2772) {

    QDomNode node(richMediaElement);

    RichMediaAnnotation annotation(node);



    EXPECT_EQ(annotation.settings(), nullptr);

}



TEST_F(RichMediaAnnotationTest_2772, ContentInitiallyNullptr_2772) {

    QDomNode node(richMediaElement);

    RichMediaAnnotation annotation(node);



    EXPECT_EQ(annotation.content(), nullptr);

}



// Assuming store does not throw exceptions and behaves correctly with valid input

TEST_F(RichMediaAnnotationTest_2772, StoreDoesNotThrowWithValidInput_2772) {

    QDomNode node(richMediaElement);

    RichMediaAnnotation annotation(node);



    EXPECT_NO_THROW(annotation.store(richMediaElement, doc));

}



// Assuming store throws an exception with invalid input

TEST_F(RichMediaAnnotationTest_2772, StoreThrowsWithInvalidInput_2772) {

    QDomNode emptyNode;

    QDomDocument emptyDoc;



    RichMediaAnnotation annotation(emptyNode);



    EXPECT_THROW(annotation.store(emptyNode, emptyDoc), ...); // Placeholder for actual exception type

}

```


