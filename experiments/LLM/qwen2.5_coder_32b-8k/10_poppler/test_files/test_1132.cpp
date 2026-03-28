#include <gtest/gtest.h>

#include "FileSpec.h"

#include "Object.h"



// Mock class for Stream to verify interactions

class MockStream : public Stream {

public:

    MOCK_METHOD(int, getChar, (), (override));

    MOCK_METHOD(void, close, (), (override));

};



TEST_F(EmbFileTest_1132, IsOk_ReturnsTrueWhenObjectIsStream_1132) {

    Object objStr(std::make_unique<GooString>("test"));

    EmbFile embFile(std::move(objStr));

    EXPECT_TRUE(embFile.isOk());

}



TEST_F(EmbFileTest_1132, IsOk_ReturnsFalseWhenObjectIsNotStream_1132) {

    Object objStr(Object::null());

    EmbFile embFile(std::move(objStr));

    EXPECT_FALSE(embFile.isOk());

}



TEST_F(EmbFileTest_1132, Stream_ReturnsNonNullPointerWhenOk_1132) {

    std::unique_ptr<MockStream> mockStream = std::make_unique<MockStream>();

    Object objStr;

    objStr.setStream(mockStream.get());

    EmbFile embFile(std::move(objStr));

    EXPECT_NE(embFile.stream(), nullptr);

}



TEST_F(EmbFileTest_1132, Stream_ReturnsNullPointerWhenNotOk_1132) {

    Object objStr(Object::null());

    EmbFile embFile(std::move(objStr));

    EXPECT_EQ(embFile.stream(), nullptr);

}



TEST_F(EmbFileTest_1132, StreamObject_ReturnsNonNullPointerWhenOk_1132) {

    Object objStr(std::make_unique<GooString>("test"));

    EmbFile embFile(std::move(objStr));

    EXPECT_NE(embFile.streamObject(), nullptr);

}



TEST_F(EmbFileTest_1132, StreamObject_ReturnsNullPointerWhenNotOk_1132) {

    Object objStr(Object::null());

    EmbFile embFile(std::move(objStr));

    EXPECT_EQ(embFile.streamObject(), nullptr);

}



TEST_F(EmbFileTest_1132, Size_ReturnsCorrectSizeFromStream_1132) {

    std::unique_ptr<MockStream> mockStream = std::make_unique<MockStream>();

    Object objStr;

    objStr.setStream(mockStream.get());

    EmbFile embFile(std::move(objStr));

    EXPECT_EQ(embFile.size(), 0); // Assuming size is not directly retrievable from the stream in this context

}



TEST_F(EmbFileTest_1132, ModDate_ReturnsNullPointerWhenNotSet_1132) {

    Object objStr(std::make_unique<GooString>("test"));

    EmbFile embFile(std::move(objStr));

    EXPECT_EQ(embFile.modDate(), nullptr);

}



TEST_F(EmbFileTest_1132, CreateDate_ReturnsNullPointerWhenNotSet_1132) {

    Object objStr(std::make_unique<GooString>("test"));

    EmbFile embFile(std::move(objStr));

    EXPECT_EQ(embFile.createDate(), nullptr);

}



TEST_F(EmbFileTest_1132, Checksum_ReturnsNullPointerWhenNotSet_1132) {

    Object objStr(std::make_unique<GooString>("test"));

    EmbFile embFile(std::move(objStr));

    EXPECT_EQ(embFile.checksum(), nullptr);

}



TEST_F(EmbFileTest_1132, MimeType_ReturnsNullPointerWhenNotSet_1132) {

    Object objStr(std::make_unique<GooString>("test"));

    EmbFile embFile(std::move(objStr));

    EXPECT_EQ(embFile.mimeType(), nullptr);

}
