#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler/PDFDoc.h"



using namespace testing;



class PDFDocTest : public ::testing::Test {

protected:

    MockCatalog* mock_catalog;

    PDFDoc* pdf_doc;



    class MockCatalog : public Catalog {

    public:

        MOCK_METHOD(const StructTreeRoot*, getStructTreeRoot, (), (const, override));

    };



    void SetUp() override {

        mock_catalog = new MockCatalog();

        pdf_doc = new PDFDoc();

        // Simulate setting the catalog pointer

        pdf_doc->catalog = mock_catalog;

    }



    void TearDown() override {

        delete pdf_doc;

        delete mock_catalog;

    }

};



TEST_F(PDFDocTest_960, GetStructTreeRoot_ReturnsNonNull_960) {

    const StructTreeRoot* expected_struct_tree_root = reinterpret_cast<const StructTreeRoot*>(0x1);

    EXPECT_CALL(*mock_catalog, getStructTreeRoot()).WillOnce(Return(expected_struct_tree_root));

    

    const StructTreeRoot* actual_struct_tree_root = pdf_doc->getStructTreeRoot();

    

    EXPECT_EQ(actual_struct_tree_root, expected_struct_tree_root);

}



TEST_F(PDFDocTest_960, GetStructTreeRoot_ReturnsNull_960) {

    EXPECT_CALL(*mock_catalog, getStructTreeRoot()).WillOnce(Return(nullptr));

    

    const StructTreeRoot* actual_struct_tree_root = pdf_doc->getStructTreeRoot();

    

    EXPECT_EQ(actual_struct_tree_root, nullptr);

}
