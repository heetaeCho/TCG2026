#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "PDFDoc.h"

#include "GooString.h"



class PDFDocTest_977 : public ::testing::Test {

protected:

    std::unique_ptr<PDFDoc> pdfDoc;



    void SetUp() override {

        // Assuming a default constructor is available for testing purposes

        pdfDoc = std::make_unique<PDFDoc>();

    }

};



TEST_F(PDFDocTest_977, SetDocInfoSubject_NormalOperation_977) {

    auto subject = std::make_unique<GooString>("Test Subject");

    EXPECT_NO_THROW(pdfDoc->setDocInfoSubject(std::move(subject)));

}



TEST_F(PDFDocTest_977, GetDocInfoSubject_AfterSet_977) {

    auto subject = std::make_unique<GooString>("Test Subject");

    pdfDoc->setDocInfoSubject(std::move(subject));

    auto retrievedSubject = pdfDoc->getDocInfoSubject();

    ASSERT_NE(retrievedSubject.get(), nullptr);

    EXPECT_STREQ("Test Subject", retrievedSubject->getCString());

}



TEST_F(PDFDocTest_977, SetDocInfoSubject_EmptyString_977) {

    auto subject = std::make_unique<GooString>("");

    EXPECT_NO_THROW(pdfDoc->setDocInfoSubject(std::move(subject)));

    auto retrievedSubject = pdfDoc->getDocInfoSubject();

    ASSERT_NE(retrievedSubject.get(), nullptr);

    EXPECT_STREQ("", retrievedSubject->getCString());

}



TEST_F(PDFDocTest_977, SetDocInfoSubject_LargeString_977) {

    std::string largeStr(1024, 'A'); // Large string of 1024 characters

    auto subject = std::make_unique<GooString>(largeStr.c_str());

    EXPECT_NO_THROW(pdfDoc->setDocInfoSubject(std::move(subject)));

    auto retrievedSubject = pdfDoc->getDocInfoSubject();

    ASSERT_NE(retrievedSubject.get(), nullptr);

    EXPECT_STREQ(largeStr.c_str(), retrievedSubject->getCString());

}



TEST_F(PDFDocTest_977, GetDocInfoSubject_DefaultConstructor_977) {

    auto subject = pdfDoc->getDocInfoSubject();

    EXPECT_EQ(subject.get(), nullptr); // Assuming no default subject is set

}
