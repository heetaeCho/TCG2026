#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler/PDFDoc.h"

#include "poppler/Object.h"

#include "poppler/Dict.h"

#include "poppler/UnicodeMap.h"

#include <memory>



using namespace testing;



class PDFInfoTest_2674 : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup the UnicodeMap mock

        uMap = std::make_unique<NiceMock<MockUnicodeMap>>();

        

        // Mock PDFDoc and Dict objects

        doc = std::make_unique<NiceMock<MockPDFDoc>>();

        dict = std::make_unique<NiceMock<MockDict>>();



        // Set up expectations for getDocInfo returning a dictionary

        ON_CALL(*doc, getDocInfo()).WillByDefault(Return(Object(dict.get())));

    }



    void TearDown() override {

        // Clean up resources if needed

    }



    std::unique_ptr<UnicodeMap> uMap;

    std::unique_ptr<PDFDoc> doc;

    std::unique_ptr<Dict> dict;



    // Mock classes for PDFDoc and Dict to isolate the test

    class MockPDFDoc : public PDFDoc {

    public:

        MOCK_METHOD(Object, getDocInfo, (), (const));

    };



    class MockDict : public Dict {

    public:

        MOCK_METHOD(int, getLength, (), (const));

        MOCK_METHOD(const char*, getKey, (int), (const));

        MOCK_METHOD(Object, lookup, (std::string_view key, int recursion), (const));

    };



    class MockUnicodeMap : public UnicodeMap {

    public:

        using UnicodeMap::UnicodeMap;

        MOCK_METHOD(int, mapUnicode, (Unicode u, char * buf, int bufSize), (const));

    };

};



TEST_F(PDFInfoTest_2674, NoCustomInfoEntries_2674) {

    // Arrange

    ON_CALL(*dict, getLength()).WillByDefault(Return(0));



    // Act & Assert

    EXPECT_NO_THROW(printCustomInfo(doc.get(), uMap.get()));

}



TEST_F(PDFInfoTest_2674, SingleNonTrappedKey_2674) {

    // Arrange

    ON_CALL(*dict, getLength()).WillByDefault(Return(1));

    ON_CALL(*dict, getKey(0)).WillByDefault(Return("Author"));

    Object authorObj("Author");

    ON_CALL(*dict, lookup("Author", _)).WillByDefault(Return(authorObj));



    // Act & Assert

    EXPECT_NO_THROW(printCustomInfo(doc.get(), uMap.get()));

}



TEST_F(PDFInfoTest_2674, CreationDateISO_2674) {

    // Arrange

    isoDates = true;

    rawDates = false;



    ON_CALL(*dict, getLength()).WillByDefault(Return(1));

    ON_CALL(*dict, getKey(0)).WillByDefault(Return("CreationDate"));

    Object creationDateObj("CreationDate");

    ON_CALL(*dict, lookup("CreationDate", _)).WillByDefault(Return(creationDateObj));



    // Act & Assert

    EXPECT_NO_THROW(printCustomInfo(doc.get(), uMap.get()));

}



TEST_F(PDFInfoTest_2674, ModDateRaw_2674) {

    // Arrange

    isoDates = false;

    rawDates = true;



    ON_CALL(*dict, getLength()).WillByDefault(Return(1));

    ON_CALL(*dict, getKey(0)).WillByDefault(Return("ModDate"));

    Object modDateObj("ModDate");

    ON_CALL(*dict, lookup("ModDate", _)).WillByDefault(Return(modDateObj));



    // Act & Assert

    EXPECT_NO_THROW(printCustomInfo(doc.get(), uMap.get()));

}



TEST_F(PDFInfoTest_2674, MultipleEntriesIncludingTrapped_2674) {

    // Arrange

    ON_CALL(*dict, getLength()).WillByDefault(Return(3));

    ON_CALL(*dict, getKey(0)).WillByDefault(Return("Author"));

    Object authorObj("Author");

    ON_CALL(*dict, lookup("Author", _)).WillByDefault(Return(authorObj));



    ON_CALL(*dict, getKey(1)).WillByDefault(Return("CreationDate"));

    Object creationDateObj("CreationDate");

    ON_CALL(*dict, lookup("CreationDate", _)).WillByDefault(Return(creationDateObj));



    ON_CALL(*dict, getKey(2)).WillByDefault(Return("Trapped"));



    // Act & Assert

    EXPECT_NO_THROW(printCustomInfo(doc.get(), uMap.get()));

}



TEST_F(PDFInfoTest_2674, InvalidObjectInDict_2674) {

    // Arrange

    ON_CALL(*dict, getLength()).WillByDefault(Return(1));

    ON_CALL(*dict, getKey(0)).WillByDefault(Return("Author"));

    Object authorObj; // Default constructed object, not a string

    ON_CALL(*dict, lookup("Author", _)).WillByDefault(Return(authorObj));



    // Act & Assert

    EXPECT_NO_THROW(printCustomInfo(doc.get(), uMap.get()));

}



TEST_F(PDFInfoTest_2674, EmptyDictEntries_2674) {

    // Arrange

    ON_CALL(*dict, getLength()).WillByDefault(Return(1));

    ON_CALL(*dict, getKey(0)).WillByDefault(Return("Author"));

    Object authorObj(""); // Empty string object

    ON_CALL(*dict, lookup("Author", _)).WillByDefault(Return(authorObj));



    // Act & Assert

    EXPECT_NO_THROW(printCustomInfo(doc.get(), uMap.get()));

}



TEST_F(PDFInfoTest_2674, LargeKeyInDict_2674) {

    // Arrange

    ON_CALL(*dict, getLength()).WillByDefault(Return(1));

    ON_CALL(*dict, getKey(0)).WillByDefault(Return("AVeryLongKeyNameThatExceedsTheNormalWidthExpectations"));

    Object authorObj("Value");

    ON_CALL(*dict, lookup("AVeryLongKeyNameThatExceedsTheNormalWidthExpectations", _)).WillByDefault(Return(authorObj));



    // Act & Assert

    EXPECT_NO_THROW(printCustomInfo(doc.get(), uMap.get()));

}



TEST_F(PDFInfoTest_2674, SpecialCharactersInKey_2674) {

    // Arrange

    ON_CALL(*dict, getLength()).WillByDefault(Return(1));

    ON_CALL(*dict, getKey(0)).WillByDefault(Return("Special_Characters!@#"));

    Object authorObj("Value");

    ON_CALL(*dict, lookup("Special_Characters!@#", _)).WillByDefault(Return(authorObj));



    // Act & Assert

    EXPECT_NO_THROW(printCustomInfo(doc.get(), uMap.get()));

}
