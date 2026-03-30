#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <poppler/qt6/src/poppler-private.h>

#include <QFile>

#include <QByteArray>

#include <optional>

#include <GooString.h>



using namespace Poppler;

using namespace testing;



class DocumentDataTest : public ::testing::Test {

protected:

    std::optional<GooString> ownerPassword;

    std::optional<GooString> userPassword;

};



TEST_F(DocumentDataTest, ConstructorWithFilePath_NormalOperation_2760) {

    QString filePath = "path/to/document.pdf";

    DocumentData docData(filePath, ownerPassword, userPassword);

}



TEST_F(DocumentDataTest, ConstructorWithIODevice_NormalOperation_2760) {

    QByteArray data("dummy data");

    QBuffer buffer(&data);

    buffer.open(QIODevice::ReadOnly);

    DocumentData docData(&buffer, ownerPassword, userPassword);

}



TEST_F(DocumentDataTest, ConstructorWithQByteArray_NormalOperation_2760) {

    QByteArray data("dummy data");

    DocumentData docData(data, ownerPassword, userPassword);

}



TEST_F(DocumentDataTest, InitFunction_CallOnce_NoError_2760) {

    QString filePath = "path/to/document.pdf";

    DocumentData docData(filePath, ownerPassword, userPassword);

    docData.init();

}



TEST_F(DocumentDataTest, NotifyXRefReconstructedCallback_Invoke_CallbackCalled_2760) {

    QString filePath = "path/to/document.pdf";

    DocumentData docData(filePath, ownerPassword, userPassword);



    MockFunction<void()> mockCallback;

    EXPECT_CALL(mockCallback, Call()).Times(1);

    docData.xrefReconstructedCallback = mockCallback.AsStdFunction();



    docData.notifyXRefReconstructed();

}



TEST_F(DocumentDataTest, SetPaperColor_SetValidColor_NoError_2760) {

    QString filePath = "path/to/document.pdf";

    DocumentData docData(filePath, ownerPassword, userPassword);

    QColor color(Qt::red);

    docData.setPaperColor(color);

}
