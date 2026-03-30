#include <gtest/gtest.h>
#include <gmock/gmock.h>

// Mock class for external dependencies (if needed)
class MockStrSrcMgr : public str_src_mgr {
public:
    MOCK_METHOD(void, str_fill_input_buffer, (j_decompress_ptr cinfo), ());
};

TEST_F(DCTStreamTest_1989, StrSkipInputData_NormalOperation_1989) {
    // Arrange: set up a j_decompress_ptr and str_src_mgr with a buffer
    j_decompress_ptr cinfo;
    str_src_mgr src_mgr;
    src_mgr.pub.bytes_in_buffer = 10;
    src_mgr.pub.next_input_byte = nullptr;
    cinfo->src = &src_mgr;

    // Act: Call the function with a valid num_bytes_l
    str_skip_input_data(cinfo, 5);

    // Assert: Verify the expected behavior (no actual internal access, but check observable effects)
    EXPECT_EQ(src_mgr.pub.bytes_in_buffer, 5);
}

TEST_F(DCTStreamTest_1989, StrSkipInputData_ZeroBytes_1989) {
    // Arrange: set up a j_decompress_ptr and str_src_mgr with a buffer
    j_decompress_ptr cinfo;
    str_src_mgr src_mgr;
    src_mgr.pub.bytes_in_buffer = 0;
    src_mgr.pub.next_input_byte = nullptr;
    cinfo->src = &src_mgr;

    // Act: Call the function with num_bytes_l = 0
    str_skip_input_data(cinfo, 0);

    // Assert: Verify that no changes were made to the state
    EXPECT_EQ(src_mgr.pub.bytes_in_buffer, 0);
}

TEST_F(DCTStreamTest_1989, StrSkipInputData_ExceedsBuffer_1989) {
    // Arrange: set up a j_decompress_ptr and str_src_mgr with a buffer
    j_decompress_ptr cinfo;
    str_src_mgr src_mgr;
    src_mgr.pub.bytes_in_buffer = 5;
    src_mgr.pub.next_input_byte = nullptr;
    cinfo->src = &src_mgr;

    // Mock the str_fill_input_buffer function to simulate refilling the buffer
    MockStrSrcMgr mock_mgr;
    EXPECT_CALL(mock_mgr, str_fill_input_buffer(cinfo)).Times(1);

    // Act: Call the function with num_bytes_l greater than the buffer size
    str_skip_input_data(cinfo, 10);

    // Assert: Verify that str_fill_input_buffer was called and buffer size updated
    EXPECT_EQ(src_mgr.pub.bytes_in_buffer, 0);
}

TEST_F(DCTStreamTest_1989, StrSkipInputData_LargeBytes_1989) {
    // Arrange: set up a j_decompress_ptr and str_src_mgr with a buffer
    j_decompress_ptr cinfo;
    str_src_mgr src_mgr;
    src_mgr.pub.bytes_in_buffer = 100;
    src_mgr.pub.next_input_byte = nullptr;
    cinfo->src = &src_mgr;

    // Act: Call the function with a large num_bytes_l value
    str_skip_input_data(cinfo, 50);

    // Assert: Verify that the buffer size has decreased as expected
    EXPECT_EQ(src_mgr.pub.bytes_in_buffer, 50);
}

TEST_F(DCTStreamTest_1989, StrSkipInputData_ExceptionalCase_NegativeBytes_1989) {
    // Arrange: set up a j_decompress_ptr and str_src_mgr with a buffer
    j_decompress_ptr cinfo;
    str_src_mgr src_mgr;
    src_mgr.pub.bytes_in_buffer = 10;
    src_mgr.pub.next_input_byte = nullptr;
    cinfo->src = &src_mgr;

    // Act: Call the function with a negative num_bytes_l
    str_skip_input_data(cinfo, -5);

    // Assert: Verify that the buffer state is unchanged (since negative bytes should not affect it)
    EXPECT_EQ(src_mgr.pub.bytes_in_buffer, 10);
}