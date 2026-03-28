#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <QList>

#include <QSet>

#include "poppler-annotation.cc"

#include "Page.h"



using namespace Poppler;

using testing::NiceMock;

using testing::_;



class MockPage : public Page {

public:

    MOCK_METHOD(Annots*, getAnnots, (), (override));

};



class MockAnnots : public Annots {

public:

    MOCK_CONST_METHOD0(getAnnots, const QList<std::shared_ptr<Annot>>());

};



class AnnotationPrivateTest_1390 : public testing::Test {

protected:

    void SetUp() override {

        mockPage = new NiceMock<MockPage>();

        mockAnnots = new MockAnnots();

        documentData = new DocumentData(QString(), std::optional<GooString>(), std::optional<GooString>());

    }



    void TearDown() override {

        delete mockPage;

        delete mockAnnots;

        delete documentData;

    }



    MockPage* mockPage;

    MockAnnots* mockAnnots;

    DocumentData* documentData;

};



TEST_F(AnnotationPrivateTest_1390, FindAnnotations_ReturnsEmptyListWhenNoAnnotations_1390) {

    EXPECT_CALL(*mockPage, getAnnots()).WillOnce(testing::Return(mockAnnots));

    EXPECT_CALL(*mockAnnots, getAnnots()).WillOnce(testing::Return(QList<std::shared_ptr<Annot>>()));



    QSet<Annotation::SubType> subtypes;

    QList<Annotation*> result = AnnotationPrivate().findAnnotations(mockPage, documentData, subtypes, -1);



    EXPECT_TRUE(result.isEmpty());

}



TEST_F(AnnotationPrivateTest_1390, FindAnnotations_ReturnsTextAnnotationWhenRequested_1390) {

    auto mockAnnot = std::make_shared<NiceMock<Annot>>();

    ON_CALL(*mockAnnot, getType()).WillByDefault(testing::Return(Annot::typeText));



    EXPECT_CALL(*mockPage, getAnnots()).WillOnce(testing::Return(mockAnnots));

    EXPECT_CALL(*mockAnnots, getAnnots()).WillOnce(testing::Return(QList<std::shared_ptr<Annot>>{ mockAnnot }));



    QSet<Annotation::SubType> subtypes;

    subtypes.insert(Annotation::AText);

    QList<Annotation*> result = AnnotationPrivate().findAnnotations(mockPage, documentData, subtypes, -1);



    EXPECT_EQ(result.size(), 1);

    EXPECT_TRUE(qobject_cast<TextAnnotation*>(result.first()) != nullptr);

}



TEST_F(AnnotationPrivateTest_1390, FindAnnotations_ReturnsEmptyListWhenSubtypeNotRequested_1390) {

    auto mockAnnot = std::make_shared<NiceMock<Annot>>();

    ON_CALL(*mockAnnot, getType()).WillByDefault(testing::Return(Annot::typeText));



    EXPECT_CALL(*mockPage, getAnnots()).WillOnce(testing::Return(mockAnnots));

    EXPECT_CALL(*mockAnnots, getAnnots()).WillOnce(testing::Return(QList<std::shared_ptr<Annot>>{ mockAnnot }));



    QSet<Annotation::SubType> subtypes;

    QList<Annotation*> result = AnnotationPrivate().findAnnotations(mockPage, documentData, subtypes, -1);



    EXPECT_TRUE(result.isEmpty());

}



TEST_F(AnnotationPrivateTest_1390, FindAnnotations_SkipsNullAnnotations_1390) {

    auto mockAnnot = std::make_shared<NiceMock<Annot>>();

    ON_CALL(*mockAnnot, getType()).WillByDefault(testing::Return(Annot::typeText));



    EXPECT_CALL(*mockPage, getAnnots()).WillOnce(testing::Return(mockAnnots));

    EXPECT_CALL(*mockAnnots, getAnnots())

        .WillOnce(testing::Return(QList<std::shared_ptr<Annot>>{ nullptr, mockAnnot }));



    QSet<Annotation::SubType> subtypes;

    subtypes.insert(Annotation::AText);

    QList<Annotation*> result = AnnotationPrivate().findAnnotations(mockPage, documentData, subtypes, -1);



    EXPECT_EQ(result.size(), 1);

    EXPECT_TRUE(qobject_cast<TextAnnotation*>(result.first()) != nullptr);

}



TEST_F(AnnotationPrivateTest_1390, FindAnnotations_ReturnsLineAnnotationWhenParentIDMatches_1390) {

    auto mockAnnot = std::make_shared<NiceMock<Annot>>();

    ON_CALL(*mockAnnot, getType()).WillByDefault(testing::Return(Annot::typeLine));

    auto mockMarkupAnnot = dynamic_cast<NiceMock<AnnotMarkup*>*>(mockAnnot.get());

    EXPECT_CALL(*mockMarkupAnnot, getInReplyToID()).WillRepeatedly(testing::Return(1));



    EXPECT_CALL(*mockPage, getAnnots()).WillOnce(testing::Return(mockAnnots));

    EXPECT_CALL(*mockAnnots, getAnnots()).WillOnce(testing::Return(QList<std::shared_ptr<Annot>>{ mockAnnot }));



    QSet<Annotation::SubType> subtypes;

    subtypes.insert(Annotation::ALine);

    QList<Annotation*> result = AnnotationPrivate().findAnnotations(mockPage, documentData, subtypes, 1);



    EXPECT_EQ(result.size(), 1);

    EXPECT_TRUE(qobject_cast<LineAnnotation*>(result.first()) != nullptr);

}



TEST_F(AnnotationPrivateTest_1390, FindAnnotations_SkipsAnnotationsWithDifferentParentID_1390) {

    auto mockAnnot = std::make_shared<NiceMock<Annot>>();

    ON_CALL(*mockAnnot, getType()).WillByDefault(testing::Return(Annot::typeLine));

    auto mockMarkupAnnot = dynamic_cast<NiceMock<AnnotMarkup*>*>(mockAnnot.get());

    EXPECT_CALL(*mockMarkupAnnot, getInReplyToID()).WillRepeatedly(testing::Return(2));



    EXPECT_CALL(*mockPage, getAnnots()).WillOnce(testing::Return(mockAnnots));

    EXPECT_CALL(*mockAnnots, getAnnots()).WillOnce(testing::Return(QList<std::shared_ptr<Annot>>{ mockAnnot }));



    QSet<Annotation::SubType> subtypes;

    subtypes.insert(Annotation::ALine);

    QList<Annotation*> result = AnnotationPrivate().findAnnotations(mockPage, documentData, subtypes, 1);



    EXPECT_TRUE(result.isEmpty());

}



TEST_F(AnnotationPrivateTest_1390, FindAnnotations_ReturnsMultipleAnnotationsWhenMatchingSubtypes_1390) {

    auto mockAnnotText = std::make_shared<NiceMock<Annot>>();

    ON_CALL(*mockAnnotText, getType()).WillByDefault(testing::Return(Annot::typeText));



    auto mockAnnotLine = std::make_shared<NiceMock<Annot>>();

    ON_CALL(*mockAnnotLine, getType()).WillByDefault(testing::Return(Annot::typeLine));



    EXPECT_CALL(*mockPage, getAnnots()).WillOnce(testing::Return(mockAnnots));

    EXPECT_CALL(*mockAnnots, getAnnots())

        .WillOnce(testing::Return(QList<std::shared_ptr<Annot>>{ mockAnnotText, mockAnnotLine }));



    QSet<Annotation::SubType> subtypes;

    subtypes.insert(Annotation::AText);

    subtypes.insert(Annotation::ALine);

    QList<Annotation*> result = AnnotationPrivate().findAnnotations(mockPage, documentData, subtypes, -1);



    EXPECT_EQ(result.size(), 2);

    EXPECT_TRUE(qobject_cast<TextAnnotation*>(result[0]) != nullptr);

    EXPECT_TRUE(qobject_cast<LineAnnotation*>(result[1]) != nullptr);

}



TEST_F(AnnotationPrivateTest_1390, FindAnnotations_ReturnsEmptyListWhenUnsupportedSubtype_1390) {

    auto mockAnnot = std::make_shared<NiceMock<Annot>>();

    ON_CALL(*mockAnnot, getType()).WillByDefault(testing::Return(static_cast<Annot::AnnotSubtype>(50)));



    EXPECT_CALL(*mockPage, getAnnots()).WillOnce(testing::Return(mockAnnots));

    EXPECT_CALL(*mockAnnots, getAnnots())

        .WillOnce(testing::Return(QList<std::shared_ptr<Annot>>{ mockAnnot }));



    QSet<Annotation::SubType> subtypes;

    subtypes.insert(static_cast<Annotation::SubType>(50));

    QList<Annotation*> result = AnnotationPrivate().findAnnotations(mockPage, documentData, subtypes, -1);



    EXPECT_TRUE(result.isEmpty());

}
