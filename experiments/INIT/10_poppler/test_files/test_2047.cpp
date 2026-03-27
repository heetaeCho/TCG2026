#include <gtest/gtest.h>
#include <gmock/gmock.h>

// Mocks and dependencies
class MockGObject {
public:
    MOCK_METHOD(void, finalize, (GObject* object), ());
};

// PopplerAnnotMovie is a struct with the finalize function in the provided code
struct PopplerAnnotMovie {
    void* movie = nullptr;
};

// Test fixture for PopplerAnnotMovie
class PopplerAnnotMovieTest_2047 : public ::testing::Test {
protected:
    PopplerAnnotMovie annot_movie;
    MockGObject mock_gobject;
    
    void SetUp() override {
        // Set up any necessary test state
    }

    void TearDown() override {
        // Clean up after each test
    }
};

// Test normal operation where movie is non-null
TEST_F(PopplerAnnotMovieTest_2047, Finalize_WithMovie_2047) {
    annot_movie.movie = reinterpret_cast<void*>(0x123456); // Mock movie pointer
    EXPECT_CALL(mock_gobject, finalize(::testing::_)).Times(1);
    
    poppler_annot_movie_finalize(reinterpret_cast<GObject*>(&annot_movie));

    ASSERT_EQ(annot_movie.movie, nullptr);  // Movie should be nullified after finalize
}

// Test boundary condition where movie is null
TEST_F(PopplerAnnotMovieTest_2047, Finalize_WithNullMovie_2047) {
    annot_movie.movie = nullptr;  // Movie is already null
    EXPECT_CALL(mock_gobject, finalize(::testing::_)).Times(1);
    
    poppler_annot_movie_finalize(reinterpret_cast<GObject*>(&annot_movie));
    
    ASSERT_EQ(annot_movie.movie, nullptr);  // Movie should still be null
}

// Exceptional case: simulate a failure in unref handling (this would depend on the specific behavior of the underlying API)
// This test is currently theoretical as it's not observable directly via this interface, but can be included for completeness.
TEST_F(PopplerAnnotMovieTest_2047, Finalize_HandleUnrefFailure_2047) {
    annot_movie.movie = reinterpret_cast<void*>(0x123456);
    EXPECT_CALL(mock_gobject, finalize(::testing::_)).Times(1);

    // Assume an error occurs in the finalization
    // Specific error simulation would depend on the behavior of the finalize/unref function.

    poppler_annot_movie_finalize(reinterpret_cast<GObject*>(&annot_movie));

    ASSERT_EQ(annot_movie.movie, nullptr);  // Movie should still be null even if error occurred in unref
}