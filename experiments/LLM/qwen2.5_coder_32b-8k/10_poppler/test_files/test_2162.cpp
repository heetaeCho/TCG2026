#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-document.h"

#include "Catalog.h"



using ::testing::Return;

using ::testing::NiceMock;



class MockCatalog : public Catalog {

public:

    MOCK_METHOD(int, numDests, (), (const));

    MOCK_METHOD(const char*, getDestsName, (int), (const));

    MOCK_METHOD(std::unique_ptr<LinkDest>, getDestsDest, (int), (const));

    MOCK_METHOD(int, numDestNameTree, (), (const));

    MOCK_METHOD(const GooString*, getDestNameTreeName, (int), (const));

    MOCK_METHOD(std::unique_ptr<LinkDest>, getDestNameTreeDest, (int), (const));

};



class PopplerDocumentTest_2162 : public ::testing::Test {

protected:

    NiceMock<MockCatalog> mock_catalog;

    PopplerDocument document{nullptr};

    

    virtual void SetUp() {

        document.doc = &mock_catalog;

    }

};



TEST_F(PopplerDocumentTest_2162, CreateDestsTree_ReturnsNullptrIfDocumentIsNull_2162) {

    EXPECT_EQ(poppler_document_create_dests_tree(nullptr), nullptr);

}



TEST_F(PopplerDocumentTest_2162, CreateDestsTree_ReturnsNullptrIfCatalogIsNull_2162) {

    ON_CALL(mock_catalog, numDests()).WillByDefault(Return(0));

    document.doc = nullptr;

    EXPECT_EQ(poppler_document_create_dests_tree(&document), nullptr);

}



TEST_F(PopplerDocumentTest_2162, CreateDestsTree_ReturnsEmptyTreeIfNoDestinations_2162) {

    ON_CALL(mock_catalog, numDests()).WillByDefault(Return(0));

    ON_CALL(mock_catalog, numDestNameTree()).WillByDefault(Return(0));



    GTree* tree = poppler_document_create_dests_tree(&document);

    EXPECT_NE(tree, nullptr);

    EXPECT_EQ(g_tree_nnodes(tree), 0);

    g_tree_destroy(tree);

}



TEST_F(PopplerDocumentTest_2162, CreateDestsTree_InsertsDestinationsFromCatalog_2162) {

    const char* name = "test_dest";

    auto mock_dest = std::make_unique<LinkDest>();



    ON_CALL(mock_catalog, numDests()).WillByDefault(Return(1));

    ON_CALL(mock_catalog, getDestsName(0)).WillByDefault(Return(name));

    ON_CALL(mock_catalog, getDestsDest(0)).WillByDefault(testing::Return(ByMove(std::move(mock_dest))));



    GTree* tree = poppler_document_create_dests_tree(&document);

    EXPECT_NE(tree, nullptr);

    EXPECT_EQ(g_tree_nnodes(tree), 1);

    g_tree_destroy(tree);

}



TEST_F(PopplerDocumentTest_2162, CreateDestsTree_InsertsDestinationsFromNameTree_2162) {

    GooString name("test_dest");

    auto mock_dest = std::make_unique<LinkDest>();



    ON_CALL(mock_catalog, numDests()).WillByDefault(Return(0));

    ON_CALL(mock_catalog, numDestNameTree()).WillByDefault(Return(1));

    ON_CALL(mock_catalog, getDestNameTreeName(0)).WillByDefault(Return(&name));

    ON_CALL(mock_catalog, getDestNameTreeDest(0)).WillByDefault(testing::Return(ByMove(std::move(mock_dest))));



    GTree* tree = poppler_document_create_dests_tree(&document);

    EXPECT_NE(tree, nullptr);

    EXPECT_EQ(g_tree_nnodes(tree), 1);

    g_tree_destroy(tree);

}



TEST_F(PopplerDocumentTest_2162, CreateDestsTree_InsertsMultipleDestinationsFromCatalogAndNameTree_2162) {

    const char* name_catalog = "test_dest_catalog";

    GooString name_name_tree("test_dest_name_tree");

    

    auto mock_dest_catalog = std::make_unique<LinkDest>();

    auto mock_dest_name_tree = std::make_unique<LinkDest>();



    ON_CALL(mock_catalog, numDests()).WillByDefault(Return(1));

    ON_CALL(mock_catalog, getDestsName(0)).WillByDefault(Return(name_catalog));

    ON_CALL(mock_catalog, getDestsDest(0)).WillByDefault(testing::Return(ByMove(std::move(mock_dest_catalog))));



    ON_CALL(mock_catalog, numDestNameTree()).WillByDefault(Return(1));

    ON_CALL(mock_catalog, getDestNameTreeName(0)).WillByDefault(Return(&name_name_tree));

    ON_CALL(mock_catalog, getDestNameTreeDest(0)).WillByDefault(testing::Return(ByMove(std::move(mock_dest_name_tree))));



    GTree* tree = poppler_document_create_dests_tree(&document);

    EXPECT_NE(tree, nullptr);

    EXPECT_EQ(g_tree_nnodes(tree), 2);

    g_tree_destroy(tree);

}



TEST_F(PopplerDocumentTest_2162, CreateDestsTree_HandlesNullDestinationsGracefully_2162) {

    ON_CALL(mock_catalog, numDests()).WillByDefault(Return(1));

    ON_CALL(mock_catalog, getDestsName(0)).WillByDefault(Return("test_dest"));

    ON_CALL(mock_catalog, getDestsDest(0)).WillByDefault(testing::Return(ByMove(nullptr)));



    GTree* tree = poppler_document_create_dests_tree(&document);

    EXPECT_NE(tree, nullptr);

    EXPECT_EQ(g_tree_nnodes(tree), 0);

    g_tree_destroy(tree);

}
