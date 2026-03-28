#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>

// Include poppler-qt5 headers
#include "poppler-qt5.h"
#include "poppler-annotation.h"

namespace {

class MovieAnnotationTest_1417 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test that a MovieAnnotation can be constructed
TEST_F(MovieAnnotationTest_1417, DefaultConstruction_1417) {
    Poppler::MovieAnnotation annot;
    // A default-constructed MovieAnnotation should have subType AMovie
    EXPECT_EQ(annot.subType(), Poppler::Annotation::AMovie);
}

// Test that movie() returns nullptr by default since movie member is initialized to nullptr
TEST_F(MovieAnnotationTest_1417, DefaultMovieIsNull_1417) {
    Poppler::MovieAnnotation annot;
    EXPECT_EQ(annot.movie(), nullptr);
}

// Test that movieTitle returns empty string by default
TEST_F(MovieAnnotationTest_1417, DefaultMovieTitleIsEmpty_1417) {
    Poppler::MovieAnnotation annot;
    EXPECT_TRUE(annot.movieTitle().isEmpty());
}

// Test setting and getting movie title
TEST_F(MovieAnnotationTest_1417, SetAndGetMovieTitle_1417) {
    Poppler::MovieAnnotation annot;
    QString title = QStringLiteral("TestMovie");
    annot.setMovieTitle(title);
    EXPECT_EQ(annot.movieTitle(), title);
}

// Test setting movie title to empty string
TEST_F(MovieAnnotationTest_1417, SetEmptyMovieTitle_1417) {
    Poppler::MovieAnnotation annot;
    annot.setMovieTitle(QStringLiteral("SomeTitle"));
    annot.setMovieTitle(QString());
    EXPECT_TRUE(annot.movieTitle().isEmpty());
}

// Test that destruction works without crash when movie is nullptr
TEST_F(MovieAnnotationTest_1417, DestructionWithNullMovie_1417) {
    // Should not crash - movie is nullptr by default, delete nullptr is safe
    auto annot = std::make_unique<Poppler::MovieAnnotation>();
    EXPECT_NO_THROW(annot.reset());
}

// Test subType returns AMovie
TEST_F(MovieAnnotationTest_1417, SubTypeIsAMovie_1417) {
    Poppler::MovieAnnotation annot;
    EXPECT_EQ(annot.subType(), Poppler::Annotation::AMovie);
}

// Test setting movie title with special characters
TEST_F(MovieAnnotationTest_1417, SetMovieTitleWithSpecialChars_1417) {
    Poppler::MovieAnnotation annot;
    QString specialTitle = QStringLiteral("Movie with spaces & special chars: éàü");
    annot.setMovieTitle(specialTitle);
    EXPECT_EQ(annot.movieTitle(), specialTitle);
}

// Test setting movie title with very long string
TEST_F(MovieAnnotationTest_1417, SetMovieTitleLongString_1417) {
    Poppler::MovieAnnotation annot;
    QString longTitle(10000, QChar('A'));
    annot.setMovieTitle(longTitle);
    EXPECT_EQ(annot.movieTitle(), longTitle);
}

// Test multiple MovieAnnotation instances are independent
TEST_F(MovieAnnotationTest_1417, MultipleInstancesIndependent_1417) {
    Poppler::MovieAnnotation annot1;
    Poppler::MovieAnnotation annot2;
    
    annot1.setMovieTitle(QStringLiteral("Title1"));
    annot2.setMovieTitle(QStringLiteral("Title2"));
    
    EXPECT_EQ(annot1.movieTitle(), QStringLiteral("Title1"));
    EXPECT_EQ(annot2.movieTitle(), QStringLiteral("Title2"));
}

} // namespace
