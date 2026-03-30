#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "PDFDoc.h"

#include "Catalog.h"

#include "Object.h"



using ::testing::Return;



class MockCatalog : public Catalog {

public:

    MOCK_METHOD(int, findPage, (const Ref ref), (override));

};



class PDFDocTest_961 : public testing::Test {

protected:

    std::unique_ptr<MockCatalog> mockCatalog;

    PDFDoc pdfDoc;



    void SetUp() override {

        mockCatalog = std::make_unique<MockCatalog>();

        pdfDoc.catalog = mockCatalog.get();

    }

};



TEST_F(PDFDocTest_961, FindPage_ValidRef_ReturnsPageNumber_961) {

    Ref validRef{42, 0};

    EXPECT_CALL(*mockCatalog, findPage(validRef)).WillOnce(Return(5));



    int result = pdfDoc.findPage(validRef);

    EXPECT_EQ(result, 5);

}



TEST_F(PDFDocTest_961, FindPage_InvalidRef_ReturnsNegativeNumber_961) {

    Ref invalidRef = Ref::INVALID();

    EXPECT_CALL(*mockCatalog, findPage(invalidRef)).WillOnce(Return(-1));



    int result = pdfDoc.findPage(invalidRef);

    EXPECT_EQ(result, -1);

}



TEST_F(PDFDocTest_961, FindPage_UnregisteredRef_ReturnsNegativeNumber_961) {

    Ref unregisteredRef{999, 0};

    EXPECT_CALL(*mockCatalog, findPage(unregisteredRef)).WillOnce(Return(-1));



    int result = pdfDoc.findPage(unregisteredRef);

    EXPECT_EQ(result, -1);

}



TEST_F(PDFDocTest_961, FindPage_ValidRef_CallsCatalogFindPage_961) {

    Ref validRef{42, 0};

    EXPECT_CALL(*mockCatalog, findPage(validRef)).WillOnce(Return(5));



    pdfDoc.findPage(validRef);

}
