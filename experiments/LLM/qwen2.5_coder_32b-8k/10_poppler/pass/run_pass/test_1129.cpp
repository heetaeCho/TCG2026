#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "TestProjects/poppler/poppler/FileSpec.h"

#include <string>



using namespace testing;



class EmbFileTest_1129 : public Test {

protected:

    void SetUp() override {

        // Setup code if necessary, but avoid accessing internal state

        GooString gooStr("dummyChecksum");

        m_embFile = new EmbFile(Object());

        // Assuming a way to set the checksum for testing purposes

        // This is a placeholder and should not be used to infer internal implementation

    }



    void TearDown() override {

        delete m_embFile;

    }



    EmbFile* m_embFile;

};



TEST_F(EmbFileTest_1129, ChecksumReturnsValidPointer_1129) {

    EXPECT_NE(m_embFile->checksum(), nullptr);

}



TEST_F(EmbFileTest_1129, ChecksumReturnsConsistentValue_1129) {

    const GooString* checksum1 = m_embFile->checksum();

    const GooString* checksum2 = m_embFile->checksum();

    EXPECT_EQ(checksum1, checksum2);

}



TEST_F(EmbFileTest_1129, ModDateReturnsValidPointer_1129) {

    EXPECT_NE(m_embFile->modDate(), nullptr);

}



TEST_F(EmbFileTest_1129, CreateDateReturnsValidPointer_1129) {

    EXPECT_NE(m_embFile->createDate(), nullptr);

}



TEST_F(EmbFileTest_1129, MimeTypeReturnsValidPointer_1129) {

    EXPECT_NE(m_embFile->mimeType(), nullptr);

}



TEST_F(EmbFileTest_1129, StreamObjectReturnsValidPointer_1129) {

    EXPECT_NE(m_embFile->streamObject(), nullptr);

}



TEST_F(EmbFileTest_1129, StreamReturnsValidPointer_1129) {

    EXPECT_NE(m_embFile->stream(), nullptr);

}



TEST_F(EmbFileTest_1129, IsOkReturnsTrueForValidObject_1129) {

    EXPECT_TRUE(m_embFile->isOk());

}



TEST_F(EmbFileTest_1129, SaveWithInvalidPathReturnsFalse_1129) {

    EXPECT_FALSE(m_embFile->save("/invalid/path/to/save"));

}
