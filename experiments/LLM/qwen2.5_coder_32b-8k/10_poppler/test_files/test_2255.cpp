#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-document.cc"

#include "poppler-private.h"



// Mocking external collaborators if needed

class MockPopplerDocument : public PopplerDocument {

public:

    MOCK_METHOD(void, unref, (), (override));

};



TEST_F(PopplerPSFileTest_2255, FinalizeFreesMemory_2255) {

    // Arrange

    PopplerPSFile ps_file;

    ps_file.document = new MockPopplerDocument();

    ps_file.out = new PSOutputDev();

    ps_file.filename = g_strdup("test_filename.ps");

#ifndef G_OS_WIN32

    int test_fd = 42; // Example file descriptor

    ps_file.fd = test_fd;

#endif /* !G_OS_WIN32 */



    EXPECT_CALL(*static_cast<MockPopplerDocument*>(ps_file.document), unref()).Times(1);

    

    // Act

    GObject *object = G_OBJECT(&ps_file);

    poppler_ps_file_finalize(object);



    // Assert

    // Memory should be freed, and file descriptor closed if not on Windows.

    EXPECT_EQ(ps_file.out, nullptr);

    EXPECT_EQ(ps_file.filename, nullptr);

#ifndef G_OS_WIN32

    EXPECT_NE(ps_file.fd, test_fd); // Assuming fd is set to -1 after closing

#endif /* !G_OS_WIN32 */

}



TEST_F(PopplerPSFileTest_2255, FinalizeWithNullOutDoesNotCrash_2255) {

    // Arrange

    PopplerPSFile ps_file;

    ps_file.document = new MockPopplerDocument();

    ps_file.out = nullptr; // Null output device

    ps_file.filename = g_strdup("test_filename.ps");



    EXPECT_CALL(*static_cast<MockPopplerDocument*>(ps_file.document), unref()).Times(1);

    

    // Act & Assert

    GObject *object = G_OBJECT(&ps_file);

    poppler_ps_file_finalize(object);



    // No crash expected

}



TEST_F(PopplerPSFileTest_2255, FinalizeWithNullFilenameDoesNotCrash_2255) {

    // Arrange

    PopplerPSFile ps_file;

    ps_file.document = new MockPopplerDocument();

    ps_file.out = new PSOutputDev();

    ps_file.filename = nullptr; // Null filename



    EXPECT_CALL(*static_cast<MockPopplerDocument*>(ps_file.document), unref()).Times(1);

    

    // Act & Assert

    GObject *object = G_OBJECT(&ps_file);

    poppler_ps_file_finalize(object);



    // No crash expected

}



TEST_F(PopplerPSFileTest_2255, FinalizeWithNullDocumentDoesNotCrash_2255) {

    // Arrange

    PopplerPSFile ps_file;

    ps_file.document = nullptr; // Null document

    ps_file.out = new PSOutputDev();

    ps_file.filename = g_strdup("test_filename.ps");



    // Act & Assert

    GObject *object = G_OBJECT(&ps_file);

    poppler_ps_file_finalize(object);



    // No crash expected, but unref should not be called

}
