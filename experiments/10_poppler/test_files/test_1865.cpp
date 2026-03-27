#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "ImageEmbeddingUtils.h"

#include "XRef.h"



using namespace ImageEmbeddingUtils;

using namespace testing;



class JpegEmbedderTest_1865 : public Test {

protected:

    std::vector<char> fileContent = {'J', 'F', 'I', 'F'};

    int width = 100;

    int height = 200;

    XRef xref;

    std::unique_ptr<JpegEmbedder> jpegEmbedder;



    void SetUp() override {

        jpegEmbedder = JpegEmbedder::create(std::move(fileContent));

        fileContent = {'J', 'F', 'I', 'F'}; // Restore file content since it's moved

    }

};



TEST_F(JpegEmbedderTest_1865, EmbedImageReturnsInvalidRefWhenFileContentEmpty_1865) {

    jpegEmbedder.reset(new JpegEmbedder(width, height, {}));

    EXPECT_EQ(jpegEmbedder->embedImage(&xref), Ref::INVALID());

}



TEST_F(JpegEmbedderTest_1865, EmbedImageAddsStreamObjectWithCorrectParameters_1865) {

    EXPECT_CALL(xref, addStreamObject(_, fileContent, StreamCompression::None))

        .WillOnce(Return(Ref{42, 0}));



    Ref result = jpegEmbedder->embedImage(&xref);

    EXPECT_EQ(result.num, 42);

    EXPECT_EQ(result.gen, 0);

}



TEST_F(JpegEmbedderTest_1865, EmbedImageCreatesDictWithCorrectEntries_1865) {

    Dict* dictMock = new Dict(&xref);

    ON_CALL(xref, addStreamObject(_, _, _))

        .WillByDefault(Return(Ref{42, 0}));



    EXPECT_CALL(*dictMock, add("ColorSpace", Object(objName, "DeviceRGB")))

        .Times(1);

    EXPECT_CALL(*dictMock, add("Width", Object(static_cast<int64_t>(width))))

        .Times(1);

    EXPECT_CALL(*dictMock, add("Height", Object(static_cast<int64_t>(height))))

        .Times(1);

    EXPECT_CALL(*dictMock, add("BitsPerComponent", Object(static_cast<int64_t>(8))))

        .Times(1);

    EXPECT_CALL(*dictMock, add("Filter", Object(objName, "DCTDecode")))

        .Times(1);



    jpegEmbedder->embedImage(&xref);

}
