#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "TestProjects/poppler/glib/poppler-attachment.cc"

#include "TestProjects/poppler/poppler/Object.h"

#include "TestProjects/poppler/poppler/FileSpec.h"



using namespace testing;



class MockEmbFile : public EmbFile {

public:

    MOCK_CONST_METHOD0(size, int());

    MOCK_CONST_METHOD0(modDate, const GooString*());

    MOCK_CONST_METHOD0(createDate, const GooString*());

    MOCK_CONST_METHOD0(checksum, const GooString*());

    MOCK_METHOD0(streamObject, Object*());

};



class MockFileSpec : public FileSpec {

public:

    explicit MockFileSpec(const Object *fileSpec) : FileSpec(fileSpec) {}



    MOCK_CONST_METHOD0(getFileName, const GooString*());

    MOCK_CONST_METHOD0(getDescription, const GooString*());

    MOCK_METHOD0(getEmbeddedFile, EmbFile*());

};



TEST(PopplerAttachmentTest_2270, NormalOperationWithAllFields_2270) {

    MockEmbFile mock_emb_file;

    MockFileSpec mock_file_spec(nullptr);



    EXPECT_CALL(mock_file_spec, getFileName()).WillOnce(Return(new GooString("testfile.pdf")));

    EXPECT_CALL(mock_file_spec, getDescription()).WillOnce(Return(new GooString("Test Description")));

    EXPECT_CALL(mock_file_spec, getEmbeddedFile()).WillRepeatedly(Return(&mock_emb_file));



    EXPECT_CALL(mock_emb_file, size()).WillOnce(Return(12345));

    EXPECT_CALL(mock_emb_file, modDate()).WillOnce(Return(new GooString("D:20231001123456Z")));

    EXPECT_CALL(mock_emb_file, createDate()).WillOnce(Return(new GooString("D:20230901123456Z")));

    EXPECT_CALL(mock_emb_file, checksum()).WillOnce(Return(new GooString("checksum_value")));

    EXPECT_CALL(mock_emb_file, streamObject()).WillRepeatedly(Return(new Object()));



    PopplerAttachment* attachment = _poppler_attachment_new(&mock_file_spec);



    ASSERT_NE(attachment, nullptr);

    EXPECT_STREQ(attachment->name, "testfile.pdf");

    EXPECT_STREQ(attachment->description, "Test Description");

    EXPECT_EQ(attachment->size, 12345);

    // The following checks depend on the conversion logic which is not mocked,

    // hence we assume that if create and mod dates are non-null, they are correctly converted.

    ASSERT_NE(attachment->ctime, static_cast<GTime>(0));

    ASSERT_NE(attachment->mtime, static_cast<GTime>(0));

    EXPECT_STREQ(attachment->checksum->str(), "checksum_value");



    g_object_unref(attachment);

}



TEST(PopplerAttachmentTest_2270, NormalOperationWithoutDescription_2270) {

    MockEmbFile mock_emb_file;

    MockFileSpec mock_file_spec(nullptr);



    EXPECT_CALL(mock_file_spec, getFileName()).WillOnce(Return(new GooString("testfile.pdf")));

    EXPECT_CALL(mock_file_spec, getDescription()).WillOnce(Return(nullptr));

    EXPECT_CALL(mock_file_spec, getEmbeddedFile()).WillRepeatedly(Return(&mock_emb_file));



    EXPECT_CALL(mock_emb_file, size()).WillOnce(Return(12345));

    EXPECT_CALL(mock_emb_file, modDate()).WillOnce(Return(new GooString("D:20231001123456Z")));

    EXPECT_CALL(mock_emb_file, createDate()).WillOnce(Return(new GooString("D:20230901123456Z")));

    EXPECT_CALL(mock_emb_file, checksum()).WillOnce(Return(new GooString("checksum_value")));

    EXPECT_CALL(mock_emb_file, streamObject()).WillRepeatedly(Return(new Object()));



    PopplerAttachment* attachment = _poppler_attachment_new(&mock_file_spec);



    ASSERT_NE(attachment, nullptr);

    EXPECT_STREQ(attachment->name, "testfile.pdf");

    EXPECT_EQ(attachment->description, nullptr);

    EXPECT_EQ(attachment->size, 12345);

    // The following checks depend on the conversion logic which is not mocked,

    // hence we assume that if create and mod dates are non-null, they are correctly converted.

    ASSERT_NE(attachment->ctime, static_cast<GTime>(0));

    ASSERT_NE(attachment->mtime, static_cast<GTime>(0));

    EXPECT_STREQ(attachment->checksum->str(), "checksum_value");



    g_object_unref(attachment);

}



TEST(PopplerAttachmentTest_2270, NormalOperationWithoutChecksum_2270) {

    MockEmbFile mock_emb_file;

    MockFileSpec mock_file_spec(nullptr);



    EXPECT_CALL(mock_file_spec, getFileName()).WillOnce(Return(new GooString("testfile.pdf")));

    EXPECT_CALL(mock_file_spec, getDescription()).WillOnce(Return(new GooString("Test Description")));

    EXPECT_CALL(mock_file_spec, getEmbeddedFile()).WillRepeatedly(Return(&mock_emb_file));



    EXPECT_CALL(mock_emb_file, size()).WillOnce(Return(12345));

    EXPECT_CALL(mock_emb_file, modDate()).WillOnce(Return(new GooString("D:20231001123456Z")));

    EXPECT_CALL(mock_emb_file, createDate()).WillOnce(Return(new GooString("D:20230901123456Z")));

    EXPECT_CALL(mock_emb_file, checksum()).WillOnce(Return(nullptr));

    EXPECT_CALL(mock_emb_file, streamObject()).WillRepeatedly(Return(new Object()));



    PopplerAttachment* attachment = _poppler_attachment_new(&mock_file_spec);



    ASSERT_NE(attachment, nullptr);

    EXPECT_STREQ(attachment->name, "testfile.pdf");

    EXPECT_STREQ(attachment->description, "Test Description");

    EXPECT_EQ(attachment->size, 12345);

    // The following checks depend on the conversion logic which is not mocked,

    // hence we assume that if create and mod dates are non-null, they are correctly converted.

    ASSERT_NE(attachment->ctime, static_cast<GTime>(0));

    ASSERT_NE(attachment->mtime, static_cast<GTime>(0));

    EXPECT_EQ(attachment->checksum, nullptr);



    g_object_unref(attachment);

}



TEST(PopplerAttachmentTest_2270, NullFileName_2270) {

    MockEmbFile mock_emb_file;

    MockFileSpec mock_file_spec(nullptr);



    EXPECT_CALL(mock_file_spec, getFileName()).WillOnce(Return(nullptr));

    EXPECT_CALL(mock_file_spec, getDescription()).WillOnce(Return(new GooString("Test Description")));

    EXPECT_CALL(mock_file_spec, getEmbeddedFile()).WillRepeatedly(Return(&mock_emb_file));



    EXPECT_CALL(mock_emb_file, size()).WillOnce(Return(12345));

    EXPECT_CALL(mock_emb_file, modDate()).WillOnce(Return(new GooString("D:20231001123456Z")));

    EXPECT_CALL(mock_emb_file, createDate()).WillOnce(Return(new GooString("D:20230901123456Z")));

    EXPECT_CALL(mock_emb_file, checksum()).WillOnce(Return(new GooString("checksum_value")));

    EXPECT_CALL(mock_emb_file, streamObject()).WillRepeatedly(Return(new Object()));



    PopplerAttachment* attachment = _poppler_attachment_new(&mock_file_spec);



    ASSERT_NE(attachment, nullptr);

    EXPECT_EQ(attachment->name, nullptr);

    EXPECT_STREQ(attachment->description, "Test Description");

    EXPECT_EQ(attachment->size, 12345);

    // The following checks depend on the conversion logic which is not mocked,

    // hence we assume that if create and mod dates are non-null, they are correctly converted.

    ASSERT_NE(attachment->ctime, static_cast<GTime>(0));

    ASSERT_NE(attachment->mtime, static_cast<GTime>(0));

    EXPECT_STREQ(attachment->checksum->str(), "checksum_value");



    g_object_unref(attachment);

}



TEST(PopplerAttachmentTest_2270, MissingStreamObject_2270) {

    MockEmbFile mock_emb_file;

    MockFileSpec mock_file_spec(nullptr);



    EXPECT_CALL(mock_file_spec, getFileName()).WillOnce(Return(new GooString("testfile.pdf")));

    EXPECT_CALL(mock_file_spec, getDescription()).WillOnce(Return(new GooString("Test Description")));

    EXPECT_CALL(mock_file_spec, getEmbeddedFile()).WillRepeatedly(Return(&mock_emb_file));



    EXPECT_CALL(mock_emb_file, size()).WillOnce(Return(0));

    EXPECT_CALL(mock_emb_file, modDate()).WillOnce(Return(nullptr));

    EXPECT_CALL(mock_emb_file, createDate()).WillOnce(Return(nullptr));

    EXPECT_CALL(mock_emb_file, checksum()).WillOnce(Return(nullptr));

    EXPECT_CALL(mock_emb_file, streamObject()).WillRepeatedly(Return(nullptr));



    PopplerAttachment* attachment = _poppler_attachment_new(&mock_file_spec);



    EXPECT_EQ(attachment, nullptr);

}



TEST(PopplerAttachmentTest_2270, StreamObjectNotAStream_2270) {

    MockEmbFile mock_emb_file;

    MockFileSpec mock_file_spec(nullptr);



    EXPECT_CALL(mock_file_spec, getFileName()).WillOnce(Return(new GooString("testfile.pdf")));

    EXPECT_CALL(mock_file_spec, getDescription()).WillOnce(Return(new GooString("Test Description")));

    EXPECT_CALL(mock_file_spec, getEmbeddedFile()).WillRepeatedly(Return(&mock_emb_file));



    Object* non_stream_object = new Object();

    EXPECT_CALL(mock_emb_file, size()).WillOnce(Return(0));

    EXPECT_CALL(mock_emb_file, modDate()).WillOnce(Return(nullptr));

    EXPECT_CALL(mock_emb_file, createDate()).WillOnce(Return(nullptr));

    EXPECT_CALL(mock_emb_file, checksum()).WillOnce(Return(nullptr));

    EXPECT_CALL(mock_emb_file, streamObject()).WillRepeatedly(Return(non_stream_object));



    PopplerAttachment* attachment = _poppler_attachment_new(&mock_file_spec);



    EXPECT_EQ(attachment, nullptr);

}



TEST(PopplerAttachmentTest_2270, NullFileSpec_2270) {

    FileSpec* null_file_spec = nullptr;

    PopplerAttachment* attachment = _poppler_attachment_new(null_file_spec);



    EXPECT_EQ(attachment, nullptr);

}
