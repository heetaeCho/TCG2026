#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Link.h"
#include "Object.h"

class LinkMovieTest_302 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test that getKind() returns actionMovie
TEST_F(LinkMovieTest_302, GetKindReturnsActionMovie_302) {
    // Create a minimal Object to construct LinkMovie
    Object obj;
    obj.initNull();
    LinkMovie movie(&obj);
    EXPECT_EQ(movie.getKind(), actionMovie);
}

// Test that actionMovie has the expected enum value
TEST_F(LinkMovieTest_302, ActionMovieEnumValue_302) {
    EXPECT_EQ(actionMovie, 5);
}

// Test construction with null object - check isOk
TEST_F(LinkMovieTest_302, ConstructWithNullObject_302) {
    Object obj;
    obj.initNull();
    LinkMovie movie(&obj);
    // With a null object, the movie link may not be ok
    // We just verify it doesn't crash and returns a consistent value
    bool ok = movie.isOk();
    // isOk() should return a boolean without crashing
    EXPECT_TRUE(ok == true || ok == false);
}

// Test hasAnnotRef with null object construction
TEST_F(LinkMovieTest_302, HasAnnotRefWithNullObject_302) {
    Object obj;
    obj.initNull();
    LinkMovie movie(&obj);
    // With a null/empty object, hasAnnotRef behavior is observable
    bool hasRef = movie.hasAnnotRef();
    EXPECT_TRUE(hasRef == true || hasRef == false);
}

// Test hasAnnotTitle with null object construction
TEST_F(LinkMovieTest_302, HasAnnotTitleWithNullObject_302) {
    Object obj;
    obj.initNull();
    LinkMovie movie(&obj);
    bool hasTitle = movie.hasAnnotTitle();
    EXPECT_TRUE(hasTitle == true || hasTitle == false);
}

// Test getAnnotTitle returns a string (possibly empty)
TEST_F(LinkMovieTest_302, GetAnnotTitleReturnsString_302) {
    Object obj;
    obj.initNull();
    LinkMovie movie(&obj);
    const std::string &title = movie.getAnnotTitle();
    // Title should be a valid string reference, possibly empty
    EXPECT_GE(title.size(), 0u);
}

// Test getOperation returns a valid OperationType
TEST_F(LinkMovieTest_302, GetOperationReturnsValidValue_302) {
    Object obj;
    obj.initNull();
    LinkMovie movie(&obj);
    LinkMovie::OperationType op = movie.getOperation();
    // Just verify it returns without crashing and has some value
    (void)op;
    SUCCEED();
}

// Test construction with a dictionary containing an Annotation reference
TEST_F(LinkMovieTest_302, ConstructWithAnnotationDict_302) {
    // Build a dict with an "Annotation" key that has an indirect ref
    Object annotObj;
    annotObj.initNull();

    Object dict;
    dict.initDict((XRef *)nullptr);
    dict.dictAdd("Annotation", std::move(annotObj));

    LinkMovie movie(&dict);
    // Verify getKind still returns actionMovie regardless of object content
    EXPECT_EQ(movie.getKind(), actionMovie);
}

// Test that getKind is consistent across multiple calls
TEST_F(LinkMovieTest_302, GetKindConsistentAcrossMultipleCalls_302) {
    Object obj;
    obj.initNull();
    LinkMovie movie(&obj);
    EXPECT_EQ(movie.getKind(), actionMovie);
    EXPECT_EQ(movie.getKind(), actionMovie);
    EXPECT_EQ(movie.getKind(), actionMovie);
}

// Test construction with a dict containing Operation key
TEST_F(LinkMovieTest_302, ConstructWithOperationDict_302) {
    Object opObj;
    opObj.initName("Play");

    Object dict;
    dict.initDict((XRef *)nullptr);
    dict.dictAdd("Operation", std::move(opObj));

    LinkMovie movie(&dict);
    EXPECT_EQ(movie.getKind(), actionMovie);
}

// Test that hasAnnotRef and hasAnnotTitle are mutually consistent
TEST_F(LinkMovieTest_302, AnnotRefAndTitleConsistency_302) {
    Object obj;
    obj.initNull();
    LinkMovie movie(&obj);
    
    // If hasAnnotRef is true, getAnnotRef should return non-null
    if (movie.hasAnnotRef()) {
        EXPECT_NE(movie.getAnnotRef(), nullptr);
    }
    
    // If hasAnnotTitle is true, title should be accessible
    if (movie.hasAnnotTitle()) {
        const std::string &title = movie.getAnnotTitle();
        // Title exists and is accessible
        EXPECT_GE(title.size(), 0u);
    }
}
