#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/poppler/qt6/src/poppler-private.h"

#include <QByteArray>

#include <QColor>



using namespace Poppler;

using namespace testing;



class DocumentDataTest_2761 : public ::testing::Test {

protected:

    std::optional<GooString> ownerPassword;

    std::optional<GooString> userPassword;

};



TEST_F(DocumentDataTest_2761, ConstructorWithQByteArray_2761) {

    QByteArray data("Sample PDF Data");

    DocumentData docData(data, ownerPassword, userPassword);

}



TEST_F(DocumentDataTest_2761, SetPaperColor_2761) {

    QByteArray data("Sample PDF Data");

    DocumentData docData(data, ownerPassword, userPassword);

    QColor color(Qt::red);

    docData.setPaperColor(color);

}



TEST_F(DocumentDataTest_2761, CheckDocument_ReturnsValidPointer_2761) {

    QByteArray data("Sample PDF Data");

    DocumentData docData(data, ownerPassword, userPassword);

    EXPECT_NE(DocumentData::checkDocument(&docData), nullptr);

}



TEST_F(DocumentDataTest_2761, ConstructorWithFilePath_2761) {

    QString filePath = "path/to/document.pdf";

    DocumentData docData(filePath, ownerPassword, userPassword);

}



TEST_F(DocumentDataTest_2761, ConstructorWithDevice_2761) {

    QByteArray data("Sample PDF Data");

    QBuffer device(&data);

    device.open(QIODevice::ReadOnly);

    DocumentData docData(&device, ownerPassword, userPassword);

}



TEST_F(DocumentDataTest_2761, NotifyXRefReconstructed_CallbackCalled_2761) {

    QByteArray data("Sample PDF Data");

    DocumentData docData(data, ownerPassword, userPassword);

    bool callbackCalled = false;

    docData.xrefReconstructedCallback = [&callbackCalled] { callbackCalled = true; };

    docData.notifyXRefReconstructed();

    EXPECT_TRUE(callbackCalled);

}



TEST_F(DocumentDataTest_2761, ConstructorWithOwnerPassword_2761) {

    QByteArray data("Sample PDF Data");

    std::optional<GooString> ownerPassword = "ownerPass";

    DocumentData docData(data, ownerPassword, userPassword);

}



TEST_F(DocumentDataTest_2761, ConstructorWithUserPassword_2761) {

    QByteArray data("Sample PDF Data");

    std::optional<GooString> userPassword = "userPass";

    DocumentData docData(data, ownerPassword, userPassword);

}
