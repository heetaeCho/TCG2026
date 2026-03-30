#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/preview.hpp"



namespace Exiv2 {

    class MockPreviewImage : public PreviewImage {

    public:

        MOCK_METHOD(size_t, width, (), const);

        MOCK_METHOD(size_t, height, (), const);

        MOCK_METHOD(PreviewId, id, (), const);

        MOCK_METHOD(DataBuf, copy, (), const);

        MOCK_METHOD(const byte*, pData, (), const);

        MOCK_METHOD(uint32_t, size, (), const);

        MOCK_METHOD(const std::string&, mimeType, (), const);

        MOCK_METHOD(const std::string&, extension, (), const);

        MOCK_METHOD(size_t, writeFile, (const std::string & path), const);

    };

}



using namespace Exiv2;



TEST_F(PreviewImageTest_1212, Width_ReturnsExpectedValue_1212) {

    PreviewImage image(PreviewProperties(), DataBuf());

    EXPECT_CALL(const_cast<MockPreviewImage&>(static_cast<const MockPreviewImage&>(image)), width())

        .WillOnce(testing::Return(800));

    EXPECT_EQ(image.width(), 800);

}



TEST_F(PreviewImageTest_1212, Height_ReturnsExpectedValue_1212) {

    PreviewImage image(PreviewProperties(), DataBuf());

    EXPECT_CALL(const_cast<MockPreviewImage&>(static_cast<const MockPreviewImage&>(image)), height())

        .WillOnce(testing::Return(600));

    EXPECT_EQ(image.height(), 600);

}



TEST_F(PreviewImageTest_1212, Id_ReturnsExpectedValue_1212) {

    PreviewProperties props;

    props.id_ = PreviewId{1};

    PreviewImage image(props, DataBuf());

    EXPECT_CALL(const_cast<MockPreviewImage&>(static_cast<const MockPreviewImage&>(image)), id())

        .WillOnce(testing::Return(PreviewId{1}));

    EXPECT_EQ(image.id(), PreviewId{1});

}



TEST_F(PreviewImageTest_1212, Copy_ReturnsDataBuf_1212) {

    PreviewImage image(PreviewProperties(), DataBuf());

    EXPECT_CALL(const_cast<MockPreviewImage&>(static_cast<const MockPreviewImage&>(image)), copy())

        .WillOnce(testing::Return(DataBuf()));

    auto data = image.copy();

    EXPECT_EQ(data.size, 0);

}



TEST_F(PreviewImageTest_1212, pData_ReturnsPointer_1212) {

    PreviewImage image(PreviewProperties(), DataBuf());

    EXPECT_CALL(const_cast<MockPreviewImage&>(static_cast<const MockPreviewImage&>(image)), pData())

        .WillOnce(testing::Return(static_cast<const byte*>(nullptr)));

    auto ptr = image.pData();

    EXPECT_EQ(ptr, nullptr);

}



TEST_F(PreviewImageTest_1212, Size_ReturnsSizeValue_1212) {

    PreviewImage image(PreviewProperties(), DataBuf());

    EXPECT_CALL(const_cast<MockPreviewImage&>(static_cast<const MockPreviewImage&>(image)), size())

        .WillOnce(testing::Return(1024));

    auto sz = image.size();

    EXPECT_EQ(sz, 1024);

}



TEST_F(PreviewImageTest_1212, MimeType_ReturnsMimeTypeString_1212) {

    PreviewProperties props;

    props.extension_ = "jpg";

    PreviewImage image(props, DataBuf());

    EXPECT_CALL(const_cast<MockPreviewImage&>(static_cast<const MockPreviewImage&>(image)), mimeType())

        .WillOnce(testing::ReturnRef(props.extension_));

    auto mime = image.mimeType();

    EXPECT_EQ(mime, "jpg");

}



TEST_F(PreviewImageTest_1212, Extension_ReturnsExtensionString_1212) {

    PreviewProperties props;

    props.extension_ = "jpg";

    PreviewImage image(props, DataBuf());

    EXPECT_CALL(const_cast<MockPreviewImage&>(static_cast<const MockPreviewImage&>(image)), extension())

        .WillOnce(testing::ReturnRef(props.extension_));

    auto ext = image.extension();

    EXPECT_EQ(ext, "jpg");

}



TEST_F(PreviewImageTest_1212, WriteFile_ReturnsWrittenSize_1212) {

    PreviewImage image(PreviewProperties(), DataBuf());

    EXPECT_CALL(const_cast<MockPreviewImage&>(static_cast<const MockPreviewImage&>(image)), writeFile(testing::_))

        .WillOnce(testing::Return(512));

    auto written = image.writeFile("/tmp/test.jpg");

    EXPECT_EQ(written, 512);

}



TEST_F(PreviewImageTest_1212, Width_ReturnsZeroForDefaultConstructor_1212) {

    PreviewProperties props;

    PreviewImage image(props, DataBuf());

    EXPECT_CALL(const_cast<MockPreviewImage&>(static_cast<const MockPreviewImage&>(image)), width())

        .WillOnce(testing::Return(0));

    EXPECT_EQ(image.width(), 0);

}



TEST_F(PreviewImageTest_1212, Height_ReturnsZeroForDefaultConstructor_1212) {

    PreviewProperties props;

    PreviewImage image(props, DataBuf());

    EXPECT_CALL(const_cast<MockPreviewImage&>(static_cast<const MockPreviewImage&>(image)), height())

        .WillOnce(testing::Return(0));

    EXPECT_EQ(image.height(), 0);

}
