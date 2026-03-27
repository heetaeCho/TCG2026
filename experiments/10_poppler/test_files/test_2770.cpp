#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-private.h"

#include <QString>

#include <QFile>

#include <optional>

#include <GooString.h>



using namespace Poppler;

using ::testing::_;

using ::testing::MockFunction;



class DocumentDataTest_2770 : public ::testing::Test {

protected:

    std::optional<GooString> ownerPassword;

    std::optional<GooString> userPassword;

};



TEST_F(DocumentDataTest_2770, ConstructorWithFilePath_2770) {

    QString filePath = "test.pdf";

    DocumentData docData(filePath, ownerPassword, userPassword);

}



TEST_F(DocumentDataTest_2770, ConstructorWithEmptyFilePath_2770) {

    QString filePath = "";

    DocumentData docData(filePath, ownerPassword, userPassword);

}



TEST_F(DocumentDataTest_2770, ConstructorWithOwnerPassword_2770) {

    QString filePath = "test.pdf";

    GooString password("owner123");

    ownerPassword = std::make_optional(password);

    DocumentData docData(filePath, ownerPassword, userPassword);

}



TEST_F(DocumentDataTest_2770, ConstructorWithUserPassword_2770) {

    QString filePath = "test.pdf";

    GooString password("user123");

    userPassword = std::make_optional(password);

    DocumentData docData(filePath, ownerPassword, userPassword);

}



TEST_F(DocumentDataTest_2770, NotifyXRefReconstructedCallback_2770) {

    QString filePath = "test.pdf";

    MockFunction<void()> mockCallback;

    DocumentData* docData = new DocumentData(filePath, ownerPassword, userPassword);



    EXPECT_CALL(mockCallback, Call()).Times(1);

    docData->xrefReconstructedCallback = [&mockCallback]() { mockCallback.Call(); };

    docData->notifyXRefReconstructed();



    delete docData;

}



TEST_F(DocumentDataTest_2770, SetPaperColorValidColor_2770) {

    QString filePath = "test.pdf";

    DocumentData docData(filePath, ownerPassword, userPassword);

    QColor color(255, 0, 0); // Red

    docData.setPaperColor(color);

}



TEST_F(DocumentDataTest_2770, SetPaperColorInvalidColor_2770) {

    QString filePath = "test.pdf";

    DocumentData docData(filePath, ownerPassword, userPassword);

    QColor color(-1, -1, -1); // Invalid

    docData.setPaperColor(color);

}
