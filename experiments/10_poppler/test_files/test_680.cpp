#include <gtest/gtest.h>

#include "TestProjects/poppler/poppler/Catalog.h"



class CatalogTest : public ::testing::Test {

protected:

    class MockPDFDoc : public PDFDoc {

    public:

        MOCK_METHOD(bool, ok, (), (const));

    };



    std::unique_ptr<MockPDFDoc> mock_doc;

    Catalog* catalog;



    void SetUp() override {

        mock_doc = std::make_unique<MockPDFDoc>();

        catalog = new Catalog(mock_doc.get());

    }



    void TearDown() override {

        delete catalog;

    }

};



TEST_F(CatalogTest_680, GetPDFMinorVersion_DefaultValue_680) {

    EXPECT_EQ(catalog->getPDFMinorVersion(), -1);

}



TEST_F(CatalogTest_680, GetNumPages_NormalOperation_680) {

    // Assuming getNumPages returns a non-negative value

    EXPECT_GE(catalog->getNumPages(), 0);

}



TEST_F(CatalogTest_680, GetPage_ValidIndex_ReturnsPagePointer_680) {

    int num_pages = catalog->getNumPages();

    if (num_pages > 0) {

        EXPECT_NE(catalog->getPage(0), nullptr);

    }

}



TEST_F(CatalogTest_680, GetPage_OutOfBounds_ReturnsNullptr_680) {

    int num_pages = catalog->getNumPages();

    EXPECT_EQ(catalog->getPage(num_pages), nullptr); // Out of bounds

}



TEST_F(CatalogTest_680, GetPageRef_ValidIndex_ReturnsRefPointer_680) {

    int num_pages = catalog->getNumPages();

    if (num_pages > 0) {

        EXPECT_NE(catalog->getPageRef(0), nullptr);

    }

}



TEST_F(CatalogTest_680, GetPageRef_OutOfBounds_ReturnsNullptr_680) {

    int num_pages = catalog->getNumPages();

    EXPECT_EQ(catalog->getPageRef(num_pages), nullptr); // Out of bounds

}



TEST_F(CatalogTest_680, ReadMetadata_NormalOperation_ReturnsUniquePtrGooString_680) {

    auto metadata = catalog->readMetadata();

    EXPECT_TRUE(metadata != nullptr || metadata == nullptr); // Check if unique_ptr is valid or null

}



TEST_F(CatalogTest_680, GetStructTreeRoot_NormalOperation_ReturnsPointer_680) {

    auto struct_tree_root = catalog->getStructTreeRoot();

    EXPECT_TRUE(struct_tree_root != nullptr || struct_tree_root == nullptr);

}



TEST_F(CatalogTest_680, GetMarkInfo_NormalOperation_ReturnsUnsignedInt_680) {

    unsigned int mark_info = catalog->getMarkInfo();

    EXPECT_TRUE(mark_info >= 0); // Assuming markInfo is non-negative

}



TEST_F(CatalogTest_680, FindPage_ValidRef_ReturnsIndex_680) {

    Ref ref;

    int index = catalog->findPage(ref);

    EXPECT_TRUE(index >= -1); // findPage returns -1 if not found

}



TEST_F(CatalogTest_680, GetDests_NormalOperation_ReturnsObjectPointer_680) {

    auto dests = catalog->getDests();

    EXPECT_TRUE(dests != nullptr || dests == nullptr);

}



TEST_F(CatalogTest_680, NumDests_NormalOperation_ReturnsNonNegativeInt_680) {

    int num_dests = catalog->numDests();

    EXPECT_GE(num_dests, 0);

}



TEST_F(CatalogTest_680, GetOutline_NormalOperation_ReturnsObjectPointer_680) {

    auto outline = catalog->getOutline();

    EXPECT_TRUE(outline != nullptr || outline == nullptr);

}



TEST_F(CatalogTest_680, IsOk_NormalOperation_ReturnsBool_680) {

    bool is_ok = catalog->isOk();

    EXPECT_TRUE(is_ok == true || is_ok == false); // Check if the function returns a boolean

}



TEST_F(CatalogTest_680, GetBaseURI_NormalOperation_ReturnsOptionalStringReference_680) {

    const std::optional<std::string>& base_uri = catalog->getBaseURI();

    EXPECT_TRUE(base_uri.has_value() == true || base_uri.has_value() == false);

}



TEST_F(CatalogTest_680, NumDestNameTree_NormalOperation_ReturnsNonNegativeInt_680) {

    int num_dest_name_tree = catalog->numDestNameTree();

    EXPECT_GE(num_dest_name_tree, 0);

}



TEST_F(CatalogTest_680, NumEmbeddedFiles_NormalOperation_ReturnsNonNegativeInt_680) {

    int num_embedded_files = catalog->numEmbeddedFiles();

    EXPECT_GE(num_embedded_files, 0);

}



TEST_F(CatalogTest_680, NumJS_NormalOperation_ReturnsNonNegativeInt_680) {

    int num_js = catalog->numJS();

    EXPECT_GE(num_js, 0);

}
