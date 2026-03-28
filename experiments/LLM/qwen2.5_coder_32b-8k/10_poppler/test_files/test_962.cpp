#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler/PDFDoc.h"

#include "poppler/Catalog.h"

#include "poppler/goo/GooString.h"



using namespace ::testing;



// Mock Catalog class to control the behavior of findDest method.

class MockCatalog : public Catalog {

public:

    MOCK_METHOD1(findDest, std::unique_ptr<LinkDest>(const GooString*));

};



// Test fixture for PDFDoc tests.

class PDFDocTest_962 : public ::testing::Test {

protected:

    void SetUp() override {

        // Create a mock catalog and inject it into the PDFDoc instance.

        mock_catalog = std::make_unique<MockCatalog>();

        pdf_doc.catalog = mock_catalog.get();

    }



    void TearDown() override {

        // Reset the catalog pointer to nullptr after tests.

        pdf_doc.catalog = nullptr;

    }



    MockCatalog* mock_catalog;

    PDFDoc pdf_doc;  // This is a simplified PDFDoc instance for testing purposes.

};



// Test case: Normal operation - findDest returns a valid LinkDest when destination exists.

TEST_F(PDFDocTest_962, FindDest_ReturnsValidLinkDest_962) {

    GooString dest_name("DestinationName");

    auto mock_link_dest = std::make_unique<LinkDest>();

    EXPECT_CALL(*mock_catalog, findDest(&dest_name)).WillOnce(Return(ByMove(std::move(mock_link_dest))));



    auto result = pdf_doc.findDest(&dest_name);

    EXPECT_NE(result.get(), nullptr);

}



// Test case: Boundary condition - findDest returns nullptr when destination name is empty.

TEST_F(PDFDocTest_962, FindDest_EmptyDestinationName_ReturnsNullptr_962) {

    GooString dest_name("");

    EXPECT_CALL(*mock_catalog, findDest(&dest_name)).WillOnce(Return(ByMove(nullptr)));



    auto result = pdf_doc.findDest(&dest_name);

    EXPECT_EQ(result.get(), nullptr);

}



// Test case: Boundary condition - findDest returns nullptr when destination name is null.

TEST_F(PDFDocTest_962, FindDest_NullDestinationName_ReturnsNullptr_962) {

    GooString* dest_name = nullptr;

    EXPECT_CALL(*mock_catalog, findDest(dest_name)).WillOnce(Return(ByMove(nullptr)));



    auto result = pdf_doc.findDest(dest_name);

    EXPECT_EQ(result.get(), nullptr);

}



// Test case: Exceptional or error case - findDest returns nullptr when destination does not exist.

TEST_F(PDFDocTest_962, FindDest_DestinationNotFound_ReturnsNullptr_962) {

    GooString dest_name("NonExistentDestination");

    EXPECT_CALL(*mock_catalog, findDest(&dest_name)).WillOnce(Return(ByMove(nullptr)));



    auto result = pdf_doc.findDest(&dest_name);

    EXPECT_EQ(result.get(), nullptr);

}
