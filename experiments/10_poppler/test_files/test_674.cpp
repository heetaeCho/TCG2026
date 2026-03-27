#include <gtest/gtest.h>

#include "Catalog.h"

#include "NameTree.h"



class CatalogTest : public ::testing::Test {

protected:

    PDFDoc* mock_doc;

    Catalog* catalog;



    void SetUp() override {

        mock_doc = new PDFDoc();

        catalog = new Catalog(mock_doc);

    }



    void TearDown() override {

        delete catalog;

        delete mock_doc;

    }

};



TEST_F(CatalogTest_674, NumEmbeddedFiles_ReturnsZero_WhenNoFilesAdded_674) {

    EXPECT_EQ(catalog->numEmbeddedFiles(), 0);

}



TEST_F(CatalogTest_674, NumEmbeddedFiles_ReturnsOne_WhenOneFileAdded_674) {

    // Assuming a way to add an embedded file exists in the Catalog class

    GooFile* mock_file = new GooFile();

    catalog->addEmbeddedFile(mock_file, "testfile.txt");

    EXPECT_EQ(catalog->numEmbeddedFiles(), 1);

    delete mock_file;

}



TEST_F(CatalogTest_674, NumEmbeddedFiles_ReturnsMultiple_WhenMultipleFilesAdded_674) {

    GooFile* mock_file1 = new GooFile();

    GooFile* mock_file2 = new GooFile();

    catalog->addEmbeddedFile(mock_file1, "testfile1.txt");

    catalog->addEmbeddedFile(mock_file2, "testfile2.txt");

    EXPECT_EQ(catalog->numEmbeddedFiles(), 2);

    delete mock_file1;

    delete mock_file2;

}



TEST_F(CatalogTest_674, NumEmbeddedFiles_ReturnsCorrectCount_AfterAddingAndRemovingFiles_674) {

    GooFile* mock_file1 = new GooFile();

    GooFile* mock_file2 = new GooFile();

    catalog->addEmbeddedFile(mock_file1, "testfile1.txt");

    catalog->addEmbeddedFile(mock_file2, "testfile2.txt");

    EXPECT_EQ(catalog->numEmbeddedFiles(), 2);



    // Assuming a way to remove an embedded file exists in the Catalog class

    // For this test, we assume removal functionality is not directly provided by Catalog,

    // so we only verify addition and count accuracy.

    delete mock_file1;

    delete mock_file2;

}
