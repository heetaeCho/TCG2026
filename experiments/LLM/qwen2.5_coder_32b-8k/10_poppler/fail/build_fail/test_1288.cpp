#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-private.h"

#include <QString>

#include <QColor>



using namespace Poppler;

using ::testing::_;

using ::testing::InvokeWithoutArgs;



class DocumentDataTest_1288 : public ::testing::Test {

protected:

    DocumentData* documentData;



    void SetUp() override {

        QString filePath = "dummyFilePath";

        documentData = new DocumentData(filePath, std::nullopt, std::nullopt);

    }



    void TearDown() override {

        delete documentData;

    }

};



TEST_F(DocumentDataTest_1288, InitSetsCorrectDefaults_1288) {

    documentData->init();

    EXPECT_EQ(documentData->m_backend, Document::SplashBackend);

    EXPECT_EQ(documentData->paperColor, static_cast<int>(Qt::white));

    EXPECT_EQ(documentData->m_hints, 0);

    EXPECT_EQ(documentData->m_optContentModel, nullptr);

    EXPECT_FALSE(documentData->xrefReconstructed);

}



TEST_F(DocumentDataTest_1288, SetPaperColorUpdatesColor_1288) {

    QColor newColor(Qt::red);

    documentData->setPaperColor(newColor);

    EXPECT_EQ(documentData->paperColor, static_cast<int>(newColor));

}



TEST_F(DocumentDataTest_1288, NotifyXRefReconstructedSetsFlag_1288) {

    documentData->notifyXRefReconstructed();

    EXPECT_TRUE(documentData->xrefReconstructed);

}



// Assuming xrefReconstructedCallback is called when notifyXRefReconstructed is invoked

class MockDocumentData : public DocumentData {

public:

    MOCK_METHOD(void, notifyXRefReconstructed, (), (override));

};



TEST_F(DocumentDataTest_1288, NotifyXRefReconstructedInvokesCallback_1288) {

    std::function<void(void)> mockCallback = []() {};

    documentData->xrefReconstructedCallback = mockCallback;

    EXPECT_CALL(*documentData, notifyXRefReconstructed()).WillOnce(InvokeWithoutArgs(documentData, &DocumentData::notifyXRefReconstructed));

    documentData->notifyXRefReconstructed();

}



// Since the DocumentData class does not provide a clear interface to set m_optContentModel or other members,

// we can only test the observable behavior through public methods.

```


