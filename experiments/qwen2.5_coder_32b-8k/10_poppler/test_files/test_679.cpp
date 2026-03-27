#include <gtest/gtest.h>

#include "Catalog.h"

#include <memory>



class CatalogTest : public ::testing::Test {

protected:

    void SetUp() override {

        // Assuming PDFDoc* docA can be nullptr for testing purposes

        catalog = std::make_unique<Catalog>(nullptr);

    }



    std::unique_ptr<Catalog> catalog;

};



TEST_F(CatalogTest_679, GetPDFMajorVersion_DefaultValue_679) {

    EXPECT_EQ(catalog->getPDFMajorVersion(), -1);

}



TEST_F(CatalogTest_679, GetPDFMinorVersion_DefaultValue_679) {

    EXPECT_EQ(catalog->getPDFMinorVersion(), -1);

}



TEST_F(CatalogTest_679, IsOk_ReturnsFalseByDefault_679) {

    EXPECT_FALSE(catalog->isOk());

}



TEST_F(CatalogTest_679, GetBaseURI_DefaultValue_679) {

    EXPECT_EQ(catalog->getBaseURI(), std::nullopt);

}
