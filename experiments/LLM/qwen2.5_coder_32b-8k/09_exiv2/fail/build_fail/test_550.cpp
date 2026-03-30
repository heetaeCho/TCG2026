#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/basicio.hpp"

#include "exiv2/error.hpp"



namespace Exiv2 {



class FileIoTest : public ::testing::Test {

protected:

    void SetUp() override {

        fileIo = std::make_unique<FileIo>("dummy_path");

    }



    void TearDown() override {

        fileIo.reset();

    }



    std::unique_ptr<FileIo> fileIo;

};



TEST_F(FileIoTest_550, Mmap_SuccessfulReadMapping_550) {

    EXPECT_NO_THROW(fileIo->mmap(false));

}



TEST_F(FileIoTest_550, Mmap_SuccessfulWriteMapping_550) {

    EXPECT_NO_THROW(fileIo->mmap(true));

}



TEST_F(FileIoTest_550, Mmap_UnsuccessfulReadMappingWithError_550) {

    // Simulate an error in munmap

    ON_CALL(*fileIo.get(), munmap()).WillByDefault(::testing::Throw(Error(ErrorCode::kerCallFailed, "dummy_path", "strError", "munmap")));

    EXPECT_THROW(fileIo->mmap(false), Error);

}



TEST_F(FileIoTest_550, Mmap_UnsuccessfulWriteMappingWithError_550) {

    // Simulate an error in munmap

    ON_CALL(*fileIo.get(), munmap()).WillByDefault(::testing::Throw(Error(ErrorCode::kerCallFailed, "dummy_path", "strError", "munmap")));

    EXPECT_THROW(fileIo->mmap(true), Error);

}



TEST_F(FileIoTest_550, Mmap_WriteMappingSwitchModeFailure_550) {

    // Simulate an error in switchMode

    fileIo.reset(new FileIo("dummy_path"));

    ON_CALL(*fileIo.get(), munmap()).WillByDefault(::testing::Return(0));

    EXPECT_THROW(fileIo->mmap(true), Error);

}



TEST_F(FileIoTest_550, Munmap_SuccessfulUnmapping_550) {

    // Assuming mmap was successful

    fileIo->mmap(false);

    EXPECT_EQ(fileIo->munmap(), 0);

}



// Mocking munmap to simulate error conditions

class MockFileIo : public FileIo {

public:

    MOCK_METHOD(int, munmap, (), (override));

};



TEST(MockFileIoTest_550, Munmap_UnsuccessfulUnmappingWithError_550) {

    MockFileIo mockFileIo("dummy_path");

    EXPECT_CALL(mockFileIo, munmap()).WillOnce(::testing::Return(-1));



    EXPECT_THROW(mockFileIo.mmap(false), Error);

}



TEST_F(FileIoTest_550, Mmap_UnsuccessfulReadMappingWithInvalidHandle_550) {

    // Simulate an error in _get_osfhandle on Windows

#ifdef _WIN32

    ON_CALL(*fileIo.get(), munmap()).WillByDefault(::testing::Return(0));

    EXPECT_THROW(fileIo->mmap(false), Error);

#endif

}



TEST_F(FileIoTest_550, Mmap_UnsuccessfulWriteMappingWithInvalidHandle_550) {

    // Simulate an error in _get_osfhandle on Windows

#ifdef _WIN32

    ON_CALL(*fileIo.get(), munmap()).WillByDefault(::testing::Return(0));

    EXPECT_THROW(fileIo->mmap(true), Error);

#endif

}



TEST_F(FileIoTest_550, Mmap_UnsuccessfulReadMappingWithDuplicateHandleFailure_550) {

    // Simulate an error in DuplicateHandle on Windows

#ifdef _WIN32

    ON_CALL(*fileIo.get(), munmap()).WillByDefault(::testing::Return(0));

    EXPECT_THROW(fileIo->mmap(false), Error);

#endif

}



TEST_F(FileIoTest_550, Mmap_UnsuccessfulWriteMappingWithDuplicateHandleFailure_550) {

    // Simulate an error in DuplicateHandle on Windows

#ifdef _WIN32

    ON_CALL(*fileIo.get(), munmap()).WillByDefault(::testing::Return(0));

    EXPECT_THROW(fileIo->mmap(true), Error);

#endif

}



TEST_F(FileIoTest_550, Mmap_UnsuccessfulReadMappingWithCreateFileMappingFailure_550) {

    // Simulate an error in CreateFileMapping on Windows

#ifdef _WIN32

    ON_CALL(*fileIo.get(), munmap()).WillByDefault(::testing::Return(0));

    EXPECT_THROW(fileIo->mmap(false), Error);

#endif

}



TEST_F(FileIoTest_550, Mmap_UnsuccessfulWriteMappingWithCreateFileMappingFailure_550) {

    // Simulate an error in CreateFileMapping on Windows

#ifdef _WIN32

    ON_CALL(*fileIo.get(), munmap()).WillByDefault(::testing::Return(0));

    EXPECT_THROW(fileIo->mmap(true), Error);

#endif

}



TEST_F(FileIoTest_550, Mmap_UnsuccessfulReadMappingWithMapViewOfFileFailure_550) {

    // Simulate an error in MapViewOfFile on Windows

#ifdef _WIN32

    ON_CALL(*fileIo.get(), munmap()).WillByDefault(::testing::Return(0));

    EXPECT_THROW(fileIo->mmap(false), Error);

#endif

}



TEST_F(FileIoTest_550, Mmap_UnsuccessfulWriteMappingWithMapViewOfFileFailure_550) {

    // Simulate an error in MapViewOfFile on Windows

#ifdef _WIN32

    ON_CALL(*fileIo.get(), munmap()).WillByDefault(::testing::Return(0));

    EXPECT_THROW(fileIo->mmap(true), Error);

#endif

}



}  // namespace Exiv2
