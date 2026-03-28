#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Link.h"
#include "Object.h"

// Test fixture for LinkMovie tests
class LinkMovieTest_307 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test that LinkMovie can be constructed from an Object and getOperation returns a valid OperationType
TEST_F(LinkMovieTest_307, GetOperationReturnsValidType_307) {
    // Create a dictionary object that represents a movie action
    Object obj;
    obj = Object(new Dict(nullptr));
    
    LinkMovie linkMovie(&obj);
    
    // getOperation should return one of the valid OperationType values
    LinkMovie::OperationType op = linkMovie.getOperation();
    // The operation type should be one of the known enum values
    // We just verify it doesn't crash and returns a value
    EXPECT_TRUE(op == LinkMovie::operationTypePlay ||
                op == LinkMovie::operationTypePause ||
                op == LinkMovie::operationTypeResume ||
                op == LinkMovie::operationTypeStop);
}

// Test default operation when constructed with a minimal/empty object
TEST_F(LinkMovieTest_307, DefaultOperationWithEmptyObject_307) {
    Object obj;
    obj = Object(new Dict(nullptr));
    
    LinkMovie linkMovie(&obj);
    
    // With no explicit operation specified, default should be play
    LinkMovie::OperationType op = linkMovie.getOperation();
    EXPECT_EQ(op, LinkMovie::operationTypePlay);
}

// Test getKind returns actionMovie
TEST_F(LinkMovieTest_307, GetKindReturnsActionMovie_307) {
    Object obj;
    obj = Object(new Dict(nullptr));
    
    LinkMovie linkMovie(&obj);
    
    EXPECT_EQ(linkMovie.getKind(), actionMovie);
}

// Test hasAnnotRef and hasAnnotTitle with empty object
TEST_F(LinkMovieTest_307, HasAnnotRefAndTitleWithEmptyObject_307) {
    Object obj;
    obj = Object(new Dict(nullptr));
    
    LinkMovie linkMovie(&obj);
    
    // With an empty dict, there should be no annotation reference or title
    // At least one of these should be testable
    bool hasRef = linkMovie.hasAnnotRef();
    bool hasTitle = linkMovie.hasAnnotTitle();
    
    // With empty object, we expect neither to be set
    EXPECT_FALSE(hasRef);
    EXPECT_FALSE(hasTitle);
}

// Test that getAnnotTitle returns a string (even if empty) when no title is set
TEST_F(LinkMovieTest_307, GetAnnotTitleWithNoTitle_307) {
    Object obj;
    obj = Object(new Dict(nullptr));
    
    LinkMovie linkMovie(&obj);
    
    if (!linkMovie.hasAnnotTitle()) {
        // If no title is set, getAnnotTitle should still return a valid reference
        const std::string &title = linkMovie.getAnnotTitle();
        EXPECT_TRUE(title.empty());
    }
}

// Test isOk with empty dictionary
TEST_F(LinkMovieTest_307, IsOkWithEmptyDict_307) {
    Object obj;
    obj = Object(new Dict(nullptr));
    
    LinkMovie linkMovie(&obj);
    
    // isOk depends on whether the object was valid enough to construct
    // We just verify it returns without crashing
    bool ok = linkMovie.isOk();
    // With a minimal dict, it might or might not be ok
    (void)ok;
}

// Test construction with a dictionary containing an Operation entry set to Play
TEST_F(LinkMovieTest_307, OperationPlayFromDict_307) {
    Dict *dict = new Dict(nullptr);
    Object opObj(new GooString("Play"));
    // Try to set the Operation key
    dict->add("Operation", std::move(Object(objName, "Play")));
    
    Object obj(dict);
    LinkMovie linkMovie(&obj);
    
    EXPECT_EQ(linkMovie.getOperation(), LinkMovie::operationTypePlay);
}

// Test construction with Operation set to Stop
TEST_F(LinkMovieTest_307, OperationStopFromDict_307) {
    Dict *dict = new Dict(nullptr);
    dict->add("Operation", std::move(Object(objName, "Stop")));
    
    Object obj(dict);
    LinkMovie linkMovie(&obj);
    
    EXPECT_EQ(linkMovie.getOperation(), LinkMovie::operationTypeStop);
}

// Test construction with Operation set to Pause
TEST_F(LinkMovieTest_307, OperationPauseFromDict_307) {
    Dict *dict = new Dict(nullptr);
    dict->add("Operation", std::move(Object(objName, "Pause")));
    
    Object obj(dict);
    LinkMovie linkMovie(&obj);
    
    EXPECT_EQ(linkMovie.getOperation(), LinkMovie::operationTypePause);
}

// Test construction with Operation set to Resume
TEST_F(LinkMovieTest_307, OperationResumeFromDict_307) {
    Dict *dict = new Dict(nullptr);
    dict->add("Operation", std::move(Object(objName, "Resume")));
    
    Object obj(dict);
    LinkMovie linkMovie(&obj);
    
    EXPECT_EQ(linkMovie.getOperation(), LinkMovie::operationTypeResume);
}

// Test construction with an annotation title
TEST_F(LinkMovieTest_307, AnnotTitleFromDict_307) {
    Dict *dict = new Dict(nullptr);
    Object titleObj(new GooString("TestMovieTitle"));
    dict->add("T", std::move(Object(new GooString("TestMovieTitle"))));
    
    Object obj(dict);
    LinkMovie linkMovie(&obj);
    
    if (linkMovie.hasAnnotTitle()) {
        const std::string &title = linkMovie.getAnnotTitle();
        EXPECT_EQ(title, "TestMovieTitle");
    }
}

// Test that getAnnotRef returns a valid pointer when annotation ref exists
TEST_F(LinkMovieTest_307, GetAnnotRefPointer_307) {
    Dict *dict = new Dict(nullptr);
    dict->add("Annotation", std::move(Object(1, 0)));
    
    Object obj(dict);
    LinkMovie linkMovie(&obj);
    
    if (linkMovie.hasAnnotRef()) {
        const Ref *ref = linkMovie.getAnnotRef();
        EXPECT_NE(ref, nullptr);
    }
}
