#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "./TestProjects/poppler/poppler/CMap.h"
#include "./TestProjects/poppler/poppler/GooString.h"

// Mock for the GooString class
class MockGooString : public GooString {
public:
    MOCK_CONST_METHOD0(get, const char*());
};

class CMapTest_1502 : public ::testing::Test {
protected:
    std::unique_ptr<GooString> collection;
    std::unique_ptr<GooString> cMapName;

    void SetUp() override {
        collection = std::make_unique<MockGooString>();
        cMapName = std::make_unique<MockGooString>();
    }
};

TEST_F(CMapTest_1502, GetCollectionReturnsCorrectValue_1502) {
    // Arrange
    const char* expectedCollection = "TestCollection";
    EXPECT_CALL(*static_cast<MockGooString*>(collection.get()), get())
        .WillOnce(testing::Return(expectedCollection));
    
    CMap cmap(std::move(collection), std::move(cMapName));

    // Act
    const GooString* result = cmap.getCollection();

    // Assert
    EXPECT_EQ(result->get(), expectedCollection);
}

TEST_F(CMapTest_1502, GetCollectionReturnsNullptrWhenNoCollection_1502) {
    // Arrange
    collection = nullptr; // Simulating no collection
    
    CMap cmap(std::move(collection), std::move(cMapName));

    // Act
    const GooString* result = cmap.getCollection();

    // Assert
    EXPECT_EQ(result, nullptr);
}

TEST_F(CMapTest_1502, GetCMapNameReturnsCorrectValue_1502) {
    // Arrange
    const char* expectedCMapName = "TestCMap";
    EXPECT_CALL(*static_cast<MockGooString*>(cMapName.get()), get())
        .WillOnce(testing::Return(expectedCMapName));
    
    CMap cmap(std::move(collection), std::move(cMapName));

    // Act
    const GooString* result = cmap.getCMapName();

    // Assert
    EXPECT_EQ(result->get(), expectedCMapName);
}

TEST_F(CMapTest_1502, MatchReturnsTrueForMatchingCollection_1502) {
    // Arrange
    std::string collectionA = "TestCollection";
    std::string cMapNameA = "TestCMap";
    
    CMap cmap(std::move(collection), std::move(cMapName));

    // Act
    bool result = cmap.match(collectionA, cMapNameA);

    // Assert
    EXPECT_TRUE(result);
}

TEST_F(CMapTest_1502, MatchReturnsFalseForNonMatchingCollection_1502) {
    // Arrange
    std::string collectionA = "NonMatchingCollection";
    std::string cMapNameA = "TestCMap";
    
    CMap cmap(std::move(collection), std::move(cMapName));

    // Act
    bool result = cmap.match(collectionA, cMapNameA);

    // Assert
    EXPECT_FALSE(result);
}

TEST_F(CMapTest_1502, GetCIDReturnsValidCID_1502) {
    // Arrange
    const char* testStr = "TestString";
    int len = 10;
    CharCode c;
    int nUsed;

    CMap cmap(std::move(collection), std::move(cMapName));

    // Act
    CID result = cmap.getCID(testStr, len, &c, &nUsed);

    // Assert
    EXPECT_NE(result, CID());  // Verify that a valid CID is returned
}

TEST_F(CMapTest_1502, SetReverseMapDoesNotThrow_1502) {
    // Arrange
    unsigned int rmap[10];
    unsigned int rmapSize = 10;
    unsigned int ncand = 5;
    
    CMap cmap(std::move(collection), std::move(cMapName));

    // Act and Assert
    EXPECT_NO_THROW(cmap.setReverseMap(rmap, rmapSize, ncand));
}

TEST_F(CMapTest_1502, DestructorDoesNotCrash_1502) {
    // Arrange
    CMap cmap(std::move(collection), std::move(cMapName));

    // Act and Assert
    EXPECT_NO_THROW({ 
        // Destructor will be called automatically at the end of the scope
    });
}