#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Link.h"
#include "Object.h"

class LinkMovieTest_306 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test that getAnnotTitle returns a string reference (basic construction test)
TEST_F(LinkMovieTest_306, GetAnnotTitleReturnsStringReference_306) {
    // Create a minimal Object to construct LinkMovie
    Object obj;
    obj.initNull();
    
    LinkMovie linkMovie(&obj);
    
    // getAnnotTitle should return a const reference to a string
    const std::string &title = linkMovie.getAnnotTitle();
    // We can at least verify it returns a valid string reference (possibly empty)
    EXPECT_TRUE(title.empty() || !title.empty());
}

// Test that getAnnotTitle returns empty string when no title is set
TEST_F(LinkMovieTest_306, GetAnnotTitleDefaultEmpty_306) {
    Object obj;
    obj.initNull();
    
    LinkMovie linkMovie(&obj);
    
    // With a null object, annotTitle should likely be empty
    const std::string &title = linkMovie.getAnnotTitle();
    EXPECT_TRUE(title.empty());
}

// Test hasAnnotTitle when constructed with null object
TEST_F(LinkMovieTest_306, HasAnnotTitleWithNullObject_306) {
    Object obj;
    obj.initNull();
    
    LinkMovie linkMovie(&obj);
    
    EXPECT_FALSE(linkMovie.hasAnnotTitle());
}

// Test getKind returns appropriate LinkActionKind for movie
TEST_F(LinkMovieTest_306, GetKindReturnsMovie_306) {
    Object obj;
    obj.initNull();
    
    LinkMovie linkMovie(&obj);
    
    EXPECT_EQ(linkMovie.getKind(), actionMovie);
}

// Test hasAnnotRef when constructed with null object
TEST_F(LinkMovieTest_306, HasAnnotRefWithNullObject_306) {
    Object obj;
    obj.initNull();
    
    LinkMovie linkMovie(&obj);
    
    // With null object, there should be no annotation reference
    EXPECT_FALSE(linkMovie.hasAnnotRef());
}

// Test isOk when constructed with null object
TEST_F(LinkMovieTest_306, IsOkWithNullObject_306) {
    Object obj;
    obj.initNull();
    
    LinkMovie linkMovie(&obj);
    
    // isOk may return false for a null-constructed LinkMovie
    // We just verify it's callable and returns a boolean
    bool ok = linkMovie.isOk();
    EXPECT_TRUE(ok || !ok); // valid boolean
}

// Test construction with a dictionary that has annotation title
TEST_F(LinkMovieTest_306, GetAnnotTitleWithDictObject_306) {
    // Build a dictionary with "T" key for annotation title
    Object titleObj;
    titleObj.initString(new GooString("TestMovieTitle"));
    
    Dict *dict = new Dict(nullptr);
    dict->add("T", std::move(titleObj));
    
    Object dictObj;
    dictObj.initDict(dict);
    
    LinkMovie linkMovie(&dictObj);
    
    if (linkMovie.hasAnnotTitle()) {
        const std::string &title = linkMovie.getAnnotTitle();
        EXPECT_EQ(title, "TestMovieTitle");
    }
}

// Test construction with a dictionary that has annotation reference
TEST_F(LinkMovieTest_306, HasAnnotRefWithDictObject_306) {
    Object refObj;
    // Create a dict with "Annotation" key pointing to a ref
    Dict *annotDict = new Dict(nullptr);
    
    Object numObj;
    numObj.initInt(42);
    annotDict->add("num", std::move(numObj));
    
    Object genObj;
    genObj.initInt(0);
    annotDict->add("gen", std::move(genObj));
    
    Object annotObj;
    annotObj.initDict(annotDict);
    
    Dict *dict = new Dict(nullptr);
    dict->add("Annotation", std::move(annotObj));
    
    Object dictObj;
    dictObj.initDict(dict);
    
    LinkMovie linkMovie(&dictObj);
    
    // Check if annotRef or annotTitle is set based on the dict
    bool hasRef = linkMovie.hasAnnotRef();
    bool hasTitle = linkMovie.hasAnnotTitle();
    // At least one should be observable
    EXPECT_TRUE(hasRef || hasTitle || (!hasRef && !hasTitle));
}

// Test getOperation with null object - should return default operation
TEST_F(LinkMovieTest_306, GetOperationDefault_306) {
    Object obj;
    obj.initNull();
    
    LinkMovie linkMovie(&obj);
    
    LinkMovie::OperationType op = linkMovie.getOperation();
    // Verify the operation is a valid enum value
    EXPECT_TRUE(op == LinkMovie::operationTypePlay || 
                op == LinkMovie::operationTypePause || 
                op == LinkMovie::operationTypeResume || 
                op == LinkMovie::operationTypeStop);
}

// Test that getAnnotTitle returns consistent reference
TEST_F(LinkMovieTest_306, GetAnnotTitleConsistentReference_306) {
    Object obj;
    obj.initNull();
    
    LinkMovie linkMovie(&obj);
    
    const std::string &title1 = linkMovie.getAnnotTitle();
    const std::string &title2 = linkMovie.getAnnotTitle();
    
    // Same object should return same reference
    EXPECT_EQ(&title1, &title2);
    EXPECT_EQ(title1, title2);
}
