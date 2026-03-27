#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "ImageEmbeddingUtils.cc"  // Adjust the include path as necessary



using namespace ImageEmbeddingUtils;

using ::testing::_;

using ::testing::Return;



class MockXRef : public XRef {

public:

    MOCK_METHOD(Ref, addIndirectObject, (Object* obj), (override));

};



TEST_F(PngEmbedderTest_1860, CreateReturnsValidPointer_1860) {

    std::vector<char> fileContent = { /* Sample PNG content */ };

    auto pngEmbedder = PngEmbedder::create(std::move(fileContent));

    EXPECT_NE(pngEmbedder, nullptr);

}



TEST_F(PngEmbedderTest_1860, EmbedImageCallsAddIndirectObject_1860) {

    std::vector<char> fileContent = { /* Sample PNG content */ };

    auto pngEmbedder = PngEmbedder::create(std::move(fileContent));

    MockXRef mockXRef;

    EXPECT_CALL(mockXRef, addIndirectObject(_)).Times(1);

    pngEmbedder->embedImage(&mockXRef);

}



TEST_F(PngEmbedderTest_1860, EmbedImageReturnsValidRef_1860) {

    std::vector<char> fileContent = { /* Sample PNG content */ };

    auto pngEmbedder = PngEmbedder::create(std::move(fileContent));

    MockXRef mockXRef;

    Ref ref = pngEmbedder->embedImage(&mockXRef);

    EXPECT_TRUE(ref.is_valid());

}



TEST_F(PngEmbedderTest_1860, CreateWithEmptyFileContentThrowsException_1860) {

    std::vector<char> fileContent = {};

    EXPECT_THROW(PngEmbedder::create(std::move(fileContent)), std::runtime_error);

}
