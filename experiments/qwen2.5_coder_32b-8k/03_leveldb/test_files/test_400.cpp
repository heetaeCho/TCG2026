#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "leveldb/status.h"

#include "leveldb/slice.h"

#include "leveldb/options.h"

#include "leveldb/env.h"

#include "table/format.h"



using namespace leveldb;

using ::testing::Return;



class MockRandomAccessFile : public RandomAccessFile {

public:

    MOCK_METHOD4(Read, Status(uint64_t offset, size_t n, Slice* result, char* scratch));

};



class ReadBlockTest_400 : public ::testing::Test {

protected:

    MockRandomAccessFile mock_file;

    ReadOptions options;

    BlockHandle handle;

    BlockContents result;



    void SetUp() override {

        handle.set_offset(10);

        handle.set_size(100);

    }

};



TEST_F(ReadBlockTest_400, NormalOperationNoCompression_400) {

    char data[105] = { 0 }; // 100 bytes of data + 5 byte trailer

    Slice expected_data(data, 100);



    EXPECT_CALL(mock_file, Read(10, 105, testing::_, data))

        .WillOnce(testing::DoAll(testing::SetArgReferee<2>(Slice(data, 105)), Return(Status::OK())));



    Status s = ReadBlock(&mock_file, options, handle, &result);

    EXPECT_TRUE(s.ok());

    EXPECT_EQ(result.data, expected_data);

    EXPECT_FALSE(result.heap_allocated);

    EXPECT_FALSE(result.cachable);

}



TEST_F(ReadBlockTest_400, NormalOperationSnappyCompression_400) {

    char compressed_data[120] = { 0 }; // Compressed data + trailer

    char decompressed_data[100] = { 0 };

    Slice expected_data(decompressed_data, 100);



    EXPECT_CALL(mock_file, Read(10, 120, testing::_, compressed_data))

        .WillOnce(testing::DoAll(testing::SetArgReferee<2>(Slice(compressed_data, 120)), Return(Status::OK())));



    ON_CALL(mock_file, Read).WillByDefault(Return(Status::OK()));



    EXPECT_CALL(*port::Snappy_GetUncompressedLengthPtr(), Call(compressed_data, 100, testing::_))

        .WillOnce(testing::DoAll(testing::SetArgReferee<2>(100), Return(true)));



    EXPECT_CALL(*port::Snappy_UncompressPtr(), Call(compressed_data, 100, decompressed_data))

        .WillOnce(Return(true));



    Status s = ReadBlock(&mock_file, options, handle, &result);

    EXPECT_TRUE(s.ok());

    EXPECT_EQ(result.data, expected_data);

    EXPECT_TRUE(result.heap_allocated);

    EXPECT_TRUE(result.cachable);



    delete[] result.data.data();

}



TEST_F(ReadBlockTest_400, NormalOperationZstdCompression_400) {

    char compressed_data[120] = { 0 }; // Compressed data + trailer

    char decompressed_data[100] = { 0 };

    Slice expected_data(decompressed_data, 100);



    EXPECT_CALL(mock_file, Read(10, 120, testing::_, compressed_data))

        .WillOnce(testing::DoAll(testing::SetArgReferee<2>(Slice(compressed_data, 120)), Return(Status::OK())));



    ON_CALL(mock_file, Read).WillByDefault(Return(Status::OK()));



    EXPECT_CALL(*port::Zstd_GetUncompressedLengthPtr(), Call(compressed_data, 100, testing::_))

        .WillOnce(testing::DoAll(testing::SetArgReferee<2>(100), Return(true)));



    EXPECT_CALL(*port::Zstd_UncompressPtr(), Call(compressed_data, 100, decompressed_data))

        .WillOnce(Return(true));



    Status s = ReadBlock(&mock_file, options, handle, &result);

    EXPECT_TRUE(s.ok());

    EXPECT_EQ(result.data, expected_data);

    EXPECT_TRUE(result.heap_allocated);

    EXPECT_TRUE(result.cachable);



    delete[] result.data.data();

}



TEST_F(ReadBlockTest_400, TruncatedBlockReadError_400) {

    char data[5] = { 0 }; // Less than required 105 bytes



    EXPECT_CALL(mock_file, Read(10, 105, testing::_, data))

        .WillOnce(testing::DoAll(testing::SetArgReferee<2>(Slice(data, 5)), Return(Status::OK())));



    Status s = ReadBlock(&mock_file, options, handle, &result);

    EXPECT_TRUE(s.IsCorruption());

    EXPECT_EQ(s.ToString(), " Corruption: truncated block read");

}



TEST_F(ReadBlockTest_400, ChecksumMismatchError_400) {

    char data[105] = { 0 }; // Data with incorrect checksum



    options.verify_checksums = true;



    EXPECT_CALL(mock_file, Read(10, 105, testing::_, data))

        .WillOnce(testing::DoAll(testing::SetArgReferee<2>(Slice(data, 105)), Return(Status::OK())));



    Status s = ReadBlock(&mock_file, options, handle, &result);

    EXPECT_TRUE(s.IsCorruption());

    EXPECT_EQ(s.ToString(), " Corruption: block checksum mismatch");

}



TEST_F(ReadBlockTest_400, CorruptedSnappyCompressionLengthError_400) {

    char data[120] = { 0 }; // Compressed data + trailer



    options.verify_checksums = true;



    EXPECT_CALL(mock_file, Read(10, 120, testing::_, data))

        .WillOnce(testing::DoAll(testing::SetArgReferee<2>(Slice(data, 120)), Return(Status::OK())));



    ON_CALL(mock_file, Read).WillByDefault(Return(Status::OK()));



    EXPECT_CALL(*port::Snappy_GetUncompressedLengthPtr(), Call(data, 100, testing::_))

        .WillOnce(Return(false));



    Status s = ReadBlock(&mock_file, options, handle, &result);

    EXPECT_TRUE(s.IsCorruption());

    EXPECT_EQ(s.ToString(), " Corruption: corrupted snappy compressed block length");

}



TEST_F(ReadBlockTest_400, CorruptedSnappyCompressionContentsError_400) {

    char data[120] = { 0 }; // Compressed data + trailer



    options.verify_checksums = true;



    EXPECT_CALL(mock_file, Read(10, 120, testing::_, data))

        .WillOnce(testing::DoAll(testing::SetArgReferee<2>(Slice(data, 120)), Return(Status::OK())));



    ON_CALL(mock_file, Read).WillByDefault(Return(Status::OK()));



    EXPECT_CALL(*port::Snappy_GetUncompressedLengthPtr(), Call(data, 100, testing::_))

        .WillOnce(testing::DoAll(testing::SetArgReferee<2>(100), Return(true)));



    EXPECT_CALL(*port::Snappy_UncompressPtr(), Call(data, 100, testing::_))

        .WillOnce(Return(false));



    Status s = ReadBlock(&mock_file, options, handle, &result);

    EXPECT_TRUE(s.IsCorruption());

    EXPECT_EQ(s.ToString(), " Corruption: corrupted snappy compressed block contents");

}



TEST_F(ReadBlockTest_400, CorruptedZstdCompressionLengthError_400) {

    char data[120] = { 0 }; // Compressed data + trailer



    options.verify_checksums = true;



    EXPECT_CALL(mock_file, Read(10, 120, testing::_, data))

        .WillOnce(testing::DoAll(testing::SetArgReferee<2>(Slice(data, 120)), Return(Status::OK())));



    ON_CALL(mock_file, Read).WillByDefault(Return(Status::OK()));



    EXPECT_CALL(*port::Zstd_GetUncompressedLengthPtr(), Call(data, 100, testing::_))

        .WillOnce(Return(false));



    Status s = ReadBlock(&mock_file, options, handle, &result);

    EXPECT_TRUE(s.IsCorruption());

    EXPECT_EQ(s.ToString(), " Corruption: corrupted zstd compressed block length");

}



TEST_F(ReadBlockTest_400, CorruptedZstdCompressionContentsError_400) {

    char data[120] = { 0 }; // Compressed data + trailer



    options.verify_checksums = true;



    EXPECT_CALL(mock_file, Read(10, 120, testing::_, data))

        .WillOnce(testing::DoAll(testing::SetArgReferee<2>(Slice(data, 120)), Return(Status::OK())));



    ON_CALL(mock_file, Read).WillByDefault(Return(Status::OK()));



    EXPECT_CALL(*port::Zstd_GetUncompressedLengthPtr(), Call(data, 100, testing::_))

        .WillOnce(testing::DoAll(testing::SetArgReferee<2>(100), Return(true)));



    EXPECT_CALL(*port::Zstd_UncompressPtr(), Call(data, 100, testing::_))

        .WillOnce(Return(false));



    Status s = ReadBlock(&mock_file, options, handle, &result);

    EXPECT_TRUE(s.IsCorruption());

    EXPECT_EQ(s.ToString(), " Corruption: corrupted zstd compressed block contents");

}



TEST_F(ReadBlockTest_400, BadBlockTypeError_400) {

    char data[105] = { 0 }; // Data with unknown compression type



    options.verify_checksums = true;



    EXPECT_CALL(mock_file, Read(10, 105, testing::_, data))

        .WillOnce(testing::DoAll(testing::SetArgReferee<2>(Slice(data, 105)), Return(Status::OK())));



    Status s = ReadBlock(&mock_file, options, handle, &result);

    EXPECT_TRUE(s.IsCorruption());

    EXPECT_EQ(s.ToString(), " Corruption: bad block type");

}



TEST_F(ReadBlockTest_400, FileReadError_400) {

    char data[120] = { 0 }; // Compressed data + trailer



    options.verify_checksums = true;



    EXPECT_CALL(mock_file, Read(10, 120, testing::_, data))

        .WillOnce(Return(Status::IOError("File read error")));



    Status s = ReadBlock(&mock_file, options, handle, &result);

    EXPECT_TRUE(s.IsIOError());

    EXPECT_EQ(s.ToString(), " IOError: File read error");

}
