#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "leveldb/table.h"

#include "leveldb/status.h"

#include "leveldb/options.h"

#include "leveldb/randomaccessfile.h"

#include "leveldb/cache.h"

#include "table/format.h"



using namespace leveldb;

using ::testing::_;

using ::testing::Return;

using ::testing::InSequence;



class MockRandomAccessFile : public RandomAccessFile {

public:

    MOCK_METHOD4(Read, Status(uint64_t offset, size_t n, Slice* result, char* scratch));

};



class TableTest_419 : public ::testing::Test {

protected:

    Options options;

    MockRandomAccessFile mock_file;

    uint64_t file_size = 1024; // Arbitrary size greater than Footer::kEncodedLength

    Table* table;

};



TEST_F(TableTest_419, OpenWithNormalSize_419) {

    char footer_space[Footer::kEncodedLength];

    Slice footer_input(footer_space, Footer::kEncodedLength);

    Status status = Status::OK();

    EXPECT_CALL(mock_file, Read(file_size - Footer::kEncodedLength, Footer::kEncodedLength, _, _))

        .WillOnce(testing::DoAll(testing::SetArgReferee<2>(footer_input), Return(status)));



    Footer footer;

    EXPECT_CALL(footer, DecodeFrom(_)).WillOnce(Return(Status::OK()));



    BlockContents index_block_contents;

    EXPECT_CALL(mock_file, Read(_, _, _, _)).WillOnce(Return(Status::OK()));



    status = Table::Open(options, &mock_file, file_size, &table);

    EXPECT_TRUE(status.ok());

    EXPECT_NE(table, nullptr);



    delete table; // Clean up

}



TEST_F(TableTest_419, OpenWithTooShortFile_419) {

    uint64_t too_short_size = Footer::kEncodedLength - 1;

    Status status = Table::Open(options, &mock_file, too_short_size, &table);

    EXPECT_TRUE(status.IsCorruption());

}



TEST_F(TableTest_419, OpenWithReadFailure_419) {

    char footer_space[Footer::kEncodedLength];

    Slice footer_input(footer_space, Footer::kEncodedLength);

    Status read_failure = Status::IOError(Slice("read error"));

    EXPECT_CALL(mock_file, Read(file_size - Footer::kEncodedLength, Footer::kEncodedLength, _, _))

        .WillOnce(testing::DoAll(testing::SetArgReferee<2>(footer_input), Return(read_failure)));



    Status status = Table::Open(options, &mock_file, file_size, &table);

    EXPECT_EQ(status, read_failure);

}



TEST_F(TableTest_419, OpenWithFooterDecodeFailure_419) {

    char footer_space[Footer::kEncodedLength];

    Slice footer_input(footer_space, Footer::kEncodedLength);

    Status status = Status::OK();

    EXPECT_CALL(mock_file, Read(file_size - Footer::kEncodedLength, Footer::kEncodedLength, _, _))

        .WillOnce(testing::DoAll(testing::SetArgReferee<2>(footer_input), Return(status)));



    Footer footer;

    Status decode_failure = Status::Corruption(Slice("decode error"));

    EXPECT_CALL(footer, DecodeFrom(_)).WillOnce(Return(decode_failure));



    status = Table::Open(options, &mock_file, file_size, &table);

    EXPECT_EQ(status, decode_failure);

}



TEST_F(TableTest_419, OpenWithIndexBlockReadFailure_419) {

    char footer_space[Footer::kEncodedLength];

    Slice footer_input(footer_space, Footer::kEncodedLength);

    Status status = Status::OK();

    EXPECT_CALL(mock_file, Read(file_size - Footer::kEncodedLength, Footer::kEncodedLength, _, _))

        .WillOnce(testing::DoAll(testing::SetArgReferee<2>(footer_input), Return(status)));



    Footer footer;

    EXPECT_CALL(footer, DecodeFrom(_)).WillOnce(Return(Status::OK()));



    Status read_failure = Status::IOError(Slice("read error"));

    EXPECT_CALL(mock_file, Read(_, _, _, _)).WillOnce(Return(read_failure));



    status = Table::Open(options, &mock_file, file_size, &table);

    EXPECT_EQ(status, read_failure);

}
