#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>

// Include necessary headers
#include "Annot.h"
#include "PDFDoc.h"
#include "Movie.h"
#include "GooString.h"
#include "PDFDocFactory.h"
#include "GlobalParams.h"

class AnnotMovieTest_810 : public ::testing::Test {
protected:
    void SetUp() override {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }

    void TearDown() override {
    }
};

// Test that getMovie returns a non-null Movie pointer when AnnotMovie is constructed with a Movie
TEST_F(AnnotMovieTest_810, GetMovieReturnsNonNullWhenConstructedWithMovie_810) {
    // Create a minimal PDF document for the annotation
    GooString fileName("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    auto doc = std::unique_ptr<PDFDoc>(new PDFDoc(&fileName));
    
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not open test PDF file";
    }

    // Create a Movie object
    Object movieObj = Object(new Dict(doc->getXRef()));
    auto movie = std::make_unique<Movie>(movieObj.getDict());

    PDFRectangle rect(0, 0, 100, 100);
    
    auto annot = std::make_unique<AnnotMovie>(doc.get(), &rect, movie.release());
    
    EXPECT_NE(annot->getMovie(), nullptr);
}

// Test that getTitle returns a value (possibly null) when constructed from dict
TEST_F(AnnotMovieTest_810, GetTitleAccessible_810) {
    GooString fileName("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    auto doc = std::unique_ptr<PDFDoc>(new PDFDoc(&fileName));
    
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not open test PDF file";
    }

    Object movieObj = Object(new Dict(doc->getXRef()));
    auto movie = std::make_unique<Movie>(movieObj.getDict());

    PDFRectangle rect(0, 0, 100, 100);
    
    auto annot = std::make_unique<AnnotMovie>(doc.get(), &rect, movie.release());
    
    // getTitle may return nullptr if no title was set, which is valid behavior
    const GooString* title = annot->getTitle();
    // Just verify we can call it without crashing
    SUCCEED();
}

// Test that getMovie returns the Movie that was passed during construction
TEST_F(AnnotMovieTest_810, GetMovieReturnsSameMovieAsConstructed_810) {
    GooString fileName("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    auto doc = std::unique_ptr<PDFDoc>(new PDFDoc(&fileName));
    
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not open test PDF file";
    }

    Object movieObj = Object(new Dict(doc->getXRef()));
    auto movie = std::make_unique<Movie>(movieObj.getDict());
    Movie* moviePtr = movie.get();

    PDFRectangle rect(0, 0, 100, 100);
    
    auto annot = std::make_unique<AnnotMovie>(doc.get(), &rect, movie.release());
    
    // The movie returned should be the same one we passed in
    EXPECT_EQ(annot->getMovie(), moviePtr);
}

// Test with different rectangle dimensions (boundary: zero-size rect)
TEST_F(AnnotMovieTest_810, ConstructWithZeroSizeRect_810) {
    GooString fileName("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    auto doc = std::unique_ptr<PDFDoc>(new PDFDoc(&fileName));
    
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not open test PDF file";
    }

    Object movieObj = Object(new Dict(doc->getXRef()));
    auto movie = std::make_unique<Movie>(movieObj.getDict());

    PDFRectangle rect(0, 0, 0, 0);
    
    auto annot = std::make_unique<AnnotMovie>(doc.get(), &rect, movie.release());
    
    EXPECT_NE(annot->getMovie(), nullptr);
}

// Test multiple calls to getMovie return the same pointer (consistency)
TEST_F(AnnotMovieTest_810, GetMovieConsistentAcrossMultipleCalls_810) {
    GooString fileName("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    auto doc = std::unique_ptr<PDFDoc>(new PDFDoc(&fileName));
    
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not open test PDF file";
    }

    Object movieObj = Object(new Dict(doc->getXRef()));
    auto movie = std::make_unique<Movie>(movieObj.getDict());

    PDFRectangle rect(0, 0, 100, 100);
    
    auto annot = std::make_unique<AnnotMovie>(doc.get(), &rect, movie.release());
    
    Movie* firstCall = annot->getMovie();
    Movie* secondCall = annot->getMovie();
    Movie* thirdCall = annot->getMovie();
    
    EXPECT_EQ(firstCall, secondCall);
    EXPECT_EQ(secondCall, thirdCall);
}

// Test with negative coordinates in rectangle
TEST_F(AnnotMovieTest_810, ConstructWithNegativeRectCoords_810) {
    GooString fileName("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    auto doc = std::unique_ptr<PDFDoc>(new PDFDoc(&fileName));
    
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not open test PDF file";
    }

    Object movieObj = Object(new Dict(doc->getXRef()));
    auto movie = std::make_unique<Movie>(movieObj.getDict());

    PDFRectangle rect(-50, -50, 100, 100);
    
    auto annot = std::make_unique<AnnotMovie>(doc.get(), &rect, movie.release());
    
    EXPECT_NE(annot->getMovie(), nullptr);
}
