#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <QString>

#include "poppler-private.h"



namespace Poppler {



class QStringToGooStringTest_1285 : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup code if needed

    }



    void TearDown() override {

        // Teardown code if needed

    }

};



TEST_F(QStringToGooStringTest_1285, NormalOperation_1285) {

    QString testString = "HelloWorld";

    std::unique_ptr<GooString> gooString = QStringToGooString(testString);

    ASSERT_TRUE(gooString != nullptr);

    EXPECT_EQ(strcmp(gooString->getCString(), "HelloWorld"), 0);

}



TEST_F(QStringToGooStringTest_1285, EmptyString_1285) {

    QString testString = "";

    std::unique_ptr<GooString> gooString = QStringToGooString(testString);

    ASSERT_TRUE(gooString != nullptr);

    EXPECT_EQ(strcmp(gooString->getCString(), ""), 0);

}



TEST_F(QStringToGooStringTest_1285, SingleCharacter_1285) {

    QString testString = "A";

    std::unique_ptr<GooString> gooString = QStringToGooString(testString);

    ASSERT_TRUE(gooString != nullptr);

    EXPECT_EQ(strcmp(gooString->getCString(), "A"), 0);

}



TEST_F(QStringToGooStringTest_1285, UnicodeCharacters_1285) {

    QString testString = u"😊";

    std::unique_ptr<GooString> gooString = QStringToGooString(testString);

    ASSERT_TRUE(gooString != nullptr);

    // Note: GooString may not handle UTF-8 properly, this is a limitation

    EXPECT_EQ(gooString->getLength(), 2); // Assuming surrogate pairs

}



TEST_F(QStringToGooStringTest_1285, LongString_1285) {

    QString testString(1000, 'a');

    std::unique_ptr<GooString> gooString = QStringToGooString(testString);

    ASSERT_TRUE(gooString != nullptr);

    EXPECT_EQ(strcmp(gooString->getCString(), testString.toStdString().c_str()), 0);

}



} // namespace Poppler
