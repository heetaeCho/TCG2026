#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include <vector>

// Include necessary headers from the project
#include "Annot.h"
#include "PDFDoc.h"
#include "GlobalParams.h"
#include "Object.h"

class AnnotInkTest_853 : public ::testing::Test {
protected:
    void SetUp() override {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }

    void TearDown() override {
    }
};

// Test that getInkList returns an empty list for a freshly constructed AnnotInk
TEST_F(AnnotInkTest_853, GetInkListInitiallyEmpty_853) {
    // We need a PDFDoc and PDFRectangle to construct AnnotInk
    // Since constructing a real PDFDoc is complex, we test what we can
    // through the interface. We'll attempt to create a minimal setup.
    
    PDFRectangle rect(0, 0, 100, 100);
    
    // Create a minimal PDF document for testing
    // We need to use a valid PDF file or create one in memory
    GooString pdfContent("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    auto doc = std::make_unique<PDFDoc>(&pdfContent);
    
    if (doc->isOk()) {
        auto annot = std::make_unique<AnnotInk>(doc.get(), &rect);
        const auto &inkList = annot->getInkList();
        // A freshly created AnnotInk should have an empty ink list
        EXPECT_TRUE(inkList.empty());
    }
}

// Test setInkList and getInkList with a single path
TEST_F(AnnotInkTest_853, SetAndGetInkListSinglePath_853) {
    PDFRectangle rect(0, 0, 200, 200);
    
    GooString pdfContent("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    auto doc = std::make_unique<PDFDoc>(&pdfContent);
    
    if (doc->isOk()) {
        auto annot = std::make_unique<AnnotInk>(doc.get(), &rect);
        
        // Create a path with some coordinates
        std::vector<std::unique_ptr<AnnotPath>> paths;
        std::vector<AnnotCoord> coords;
        coords.emplace_back(10.0, 20.0);
        coords.emplace_back(30.0, 40.0);
        coords.emplace_back(50.0, 60.0);
        
        auto path = std::make_unique<AnnotPath>(std::move(coords));
        paths.push_back(std::move(path));
        
        annot->setInkList(paths);
        
        const auto &inkList = annot->getInkList();
        EXPECT_EQ(inkList.size(), 1u);
        
        if (!inkList.empty() && inkList[0]) {
            EXPECT_EQ(inkList[0]->getCoordsLength(), 3);
        }
    }
}

// Test setInkList and getInkList with multiple paths
TEST_F(AnnotInkTest_853, SetAndGetInkListMultiplePaths_853) {
    PDFRectangle rect(0, 0, 300, 300);
    
    GooString pdfContent("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    auto doc = std::make_unique<PDFDoc>(&pdfContent);
    
    if (doc->isOk()) {
        auto annot = std::make_unique<AnnotInk>(doc.get(), &rect);
        
        std::vector<std::unique_ptr<AnnotPath>> paths;
        
        // First path
        std::vector<AnnotCoord> coords1;
        coords1.emplace_back(0.0, 0.0);
        coords1.emplace_back(10.0, 10.0);
        paths.push_back(std::make_unique<AnnotPath>(std::move(coords1)));
        
        // Second path
        std::vector<AnnotCoord> coords2;
        coords2.emplace_back(20.0, 20.0);
        coords2.emplace_back(30.0, 30.0);
        coords2.emplace_back(40.0, 40.0);
        coords2.emplace_back(50.0, 50.0);
        paths.push_back(std::make_unique<AnnotPath>(std::move(coords2)));
        
        // Third path
        std::vector<AnnotCoord> coords3;
        coords3.emplace_back(60.0, 60.0);
        paths.push_back(std::make_unique<AnnotPath>(std::move(coords3)));
        
        annot->setInkList(paths);
        
        const auto &inkList = annot->getInkList();
        EXPECT_EQ(inkList.size(), 3u);
        
        if (inkList.size() >= 3) {
            EXPECT_EQ(inkList[0]->getCoordsLength(), 2);
            EXPECT_EQ(inkList[1]->getCoordsLength(), 4);
            EXPECT_EQ(inkList[2]->getCoordsLength(), 1);
        }
    }
}

// Test setInkList with empty paths vector
TEST_F(AnnotInkTest_853, SetInkListEmptyPaths_853) {
    PDFRectangle rect(0, 0, 100, 100);
    
    GooString pdfContent("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    auto doc = std::make_unique<PDFDoc>(&pdfContent);
    
    if (doc->isOk()) {
        auto annot = std::make_unique<AnnotInk>(doc.get(), &rect);
        
        std::vector<std::unique_ptr<AnnotPath>> emptyPaths;
        annot->setInkList(emptyPaths);
        
        const auto &inkList = annot->getInkList();
        EXPECT_TRUE(inkList.empty());
    }
}

// Test getInkList returns reference to internal data (const correctness)
TEST_F(AnnotInkTest_853, GetInkListReturnsConstReference_853) {
    PDFRectangle rect(0, 0, 100, 100);
    
    GooString pdfContent("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    auto doc = std::make_unique<PDFDoc>(&pdfContent);
    
    if (doc->isOk()) {
        auto annot = std::make_unique<AnnotInk>(doc.get(), &rect);
        
        std::vector<std::unique_ptr<AnnotPath>> paths;
        std::vector<AnnotCoord> coords;
        coords.emplace_back(5.0, 5.0);
        coords.emplace_back(15.0, 15.0);
        paths.push_back(std::make_unique<AnnotPath>(std::move(coords)));
        
        annot->setInkList(paths);
        
        // Get the reference twice and verify they point to the same data
        const auto &inkList1 = annot->getInkList();
        const auto &inkList2 = annot->getInkList();
        
        EXPECT_EQ(&inkList1, &inkList2);
        EXPECT_EQ(inkList1.size(), inkList2.size());
    }
}

// Test setInkList replaces existing ink list
TEST_F(AnnotInkTest_853, SetInkListReplacesExisting_853) {
    PDFRectangle rect(0, 0, 100, 100);
    
    GooString pdfContent("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    auto doc = std::make_unique<PDFDoc>(&pdfContent);
    
    if (doc->isOk()) {
        auto annot = std::make_unique<AnnotInk>(doc.get(), &rect);
        
        // Set first ink list with 2 paths
        {
            std::vector<std::unique_ptr<AnnotPath>> paths;
            std::vector<AnnotCoord> coords1;
            coords1.emplace_back(0.0, 0.0);
            paths.push_back(std::make_unique<AnnotPath>(std::move(coords1)));
            std::vector<AnnotCoord> coords2;
            coords2.emplace_back(1.0, 1.0);
            paths.push_back(std::make_unique<AnnotPath>(std::move(coords2)));
            annot->setInkList(paths);
        }
        EXPECT_EQ(annot->getInkList().size(), 2u);
        
        // Replace with 1 path
        {
            std::vector<std::unique_ptr<AnnotPath>> paths;
            std::vector<AnnotCoord> coords;
            coords.emplace_back(5.0, 5.0);
            coords.emplace_back(10.0, 10.0);
            coords.emplace_back(15.0, 15.0);
            paths.push_back(std::make_unique<AnnotPath>(std::move(coords)));
            annot->setInkList(paths);
        }
        
        const auto &inkList = annot->getInkList();
        EXPECT_EQ(inkList.size(), 1u);
        if (!inkList.empty() && inkList[0]) {
            EXPECT_EQ(inkList[0]->getCoordsLength(), 3);
        }
    }
}

// Test getDrawBelow and setDrawBelow
TEST_F(AnnotInkTest_853, SetAndGetDrawBelow_853) {
    PDFRectangle rect(0, 0, 100, 100);
    
    GooString pdfContent("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    auto doc = std::make_unique<PDFDoc>(&pdfContent);
    
    if (doc->isOk()) {
        auto annot = std::make_unique<AnnotInk>(doc.get(), &rect);
        
        annot->setDrawBelow(true);
        EXPECT_TRUE(annot->getDrawBelow());
        
        annot->setDrawBelow(false);
        EXPECT_FALSE(annot->getDrawBelow());
    }
}

// Test coordinate values are preserved in ink list
TEST_F(AnnotInkTest_853, InkListPreservesCoordinateValues_853) {
    PDFRectangle rect(0, 0, 500, 500);
    
    GooString pdfContent("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    auto doc = std::make_unique<PDFDoc>(&pdfContent);
    
    if (doc->isOk()) {
        auto annot = std::make_unique<AnnotInk>(doc.get(), &rect);
        
        std::vector<std::unique_ptr<AnnotPath>> paths;
        std::vector<AnnotCoord> coords;
        coords.emplace_back(100.5, 200.7);
        coords.emplace_back(300.3, 400.1);
        paths.push_back(std::make_unique<AnnotPath>(std::move(coords)));
        
        annot->setInkList(paths);
        
        const auto &inkList = annot->getInkList();
        ASSERT_EQ(inkList.size(), 1u);
        ASSERT_TRUE(inkList[0] != nullptr);
        ASSERT_EQ(inkList[0]->getCoordsLength(), 2);
        
        EXPECT_DOUBLE_EQ(inkList[0]->getX(0), 100.5);
        EXPECT_DOUBLE_EQ(inkList[0]->getY(0), 200.7);
        EXPECT_DOUBLE_EQ(inkList[0]->getX(1), 300.3);
        EXPECT_DOUBLE_EQ(inkList[0]->getY(1), 400.1);
    }
}
