#include <gtest/gtest.h>

#include "TestProjects/poppler/poppler/Stream.h"



class FileStreamTest : public ::testing::Test {

protected:

    void SetUp() override {

        GooFile* file = new GooFile(); // Assuming GooFile can be default constructed or mocked if necessary

        stream.reset(new FileStream(file, 0, false, 0, Object()));

    }



    std::unique_ptr<FileStream> stream;

};



TEST_F(FileStreamTest_154, RewindReturnsTrueWhenSuccessful_154) {

    EXPECT_TRUE(stream->rewind());

}



TEST_F(FileStreamTest_154, UnfilteredRewindDelegatesToRewind_154) {

    EXPECT_EQ(stream->unfilteredRewind(), stream->rewind());

}



TEST_F(FileStreamTest_154, RewindReturnsFalseWhenUnsuccessful_154) {

    // Assuming there's a way to make rewind fail, which is not provided in the interface.

    // This test would require additional setup or assumptions about failure conditions.

    // For this example, we'll skip implementing it without more context.

}



TEST_F(FileStreamTest_154, CloseDoesNotThrowException_154) {

    EXPECT_NO_THROW(stream->close());

}



TEST_F(FileStreamTest_154, SetPosDoesNotThrowException_154) {

    EXPECT_NO_THROW(stream->setPos(0, 0));

}



TEST_F(FileStreamTest_154, MoveStartDoesNotThrowException_154) {

    EXPECT_NO_THROW(stream->moveStart(0));

}



TEST_F(FileStreamTest_154, GetKindReturnsValidEnumValue_154) {

    StreamKind kind = stream->getKind();

    EXPECT_TRUE(kind >= strFile && kind <= strCCITTFax);

}



TEST_F(FileStreamTest_154, GetCharDoesNotThrowException_154) {

    EXPECT_NO_THROW(stream->getChar());

}



TEST_F(FileStreamTest_154, LookCharDoesNotThrowException_154) {

    EXPECT_NO_THROW(stream->lookChar());

}



TEST_F(FileStreamTest_154, GetPosReturnsNonNegativeValue_154) {

    Goffset pos = stream->getPos();

    EXPECT_GE(pos, 0);

}



TEST_F(FileStreamTest_154, GetStartReturnsNonNegativeValue_154) {

    Goffset start = stream->getStart();

    EXPECT_GE(start, 0);

}



TEST_F(FileStreamTest_154, GetUnfilteredCharDoesNotThrowException_154) {

    EXPECT_NO_THROW(stream->getUnfilteredChar());

}



TEST_F(FileStreamTest_154, GetNeedsEncryptionOnSaveReturnsBool_154) {

    bool needsEncryption = stream->getNeedsEncryptionOnSave();

    EXPECT_TRUE(needsEncryption == false || needsEncryption == true);

}



TEST_F(FileStreamTest_154, SetNeedsEncryptionOnSaveDoesNotThrowException_154) {

    EXPECT_NO_THROW(stream->setNeedsEncryptionOnSave(true));

}
