#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-private.h"

#include <QString>

#include <QColor>

#include <optional>



using namespace Poppler;

using ::testing::_;

using ::testing::InvokeWithoutArgs;



class DocumentDataTest_2759 : public ::testing::Test {

protected:

    std::optional<GooString> ownerPassword;

    std::optional<GooString> userPassword;

    QString validFilePath = "valid_file_path.pdf";

};



TEST_F(DocumentDataTest_2759, ConstructorWithFilePath_2759) {

    DocumentData docData(validFilePath, ownerPassword, userPassword);

}



TEST_F(DocumentDataTest_2759, SetPaperColor_ValidColor_2759) {

    DocumentData docData(validFilePath, ownerPassword, userPassword);

    QColor color(Qt::red);

    EXPECT_NO_THROW(docData.setPaperColor(color));

}



TEST_F(DocumentDataTest_2759, NotifyXRefReconstructed_CallbackCalled_2759) {

    DocumentData docData(validFilePath, ownerPassword, userPassword);

    bool callbackCalled = false;

    docData.xrefReconstructedCallback = [&callbackCalled] { callbackCalled = true; };

    docData.notifyXRefReconstructed();

    EXPECT_TRUE(callbackCalled);

}



TEST_F(DocumentDataTest_2759, CheckDocument_ValidDoc_ReturnsNonNegative_2759) {

    DocumentData* docData = new DocumentData(validFilePath, ownerPassword, userPassword);

    int result = DocumentData::checkDocument(docData);

    delete docData;

    EXPECT_GE(result, 0);

}



TEST_F(DocumentDataTest_2759, CheckDocument_NullDoc_ReturnsNegative_2759) {

    DocumentData* nullDocData = nullptr;

    int result = DocumentData::checkDocument(nullDocData);

    EXPECT_LT(result, 0);

}
