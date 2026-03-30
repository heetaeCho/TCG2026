#include <gtest/gtest.h>

#include <gmock/gmock.h>



// Mocking G_OBJECT_CLASS and related functions if necessary

class MockGObjectClass {

public:

    MOCK_METHOD1(finalize, void(GObject*));

};



extern "C" {

    GType poppler_annot_movie_get_type(void);

}



// Assuming PopplerAnnotMovie is a GObject-derived class

typedef struct _PopplerAnnotMovie {

    GObject parent_instance;

    gpointer movie; // Assuming movie is a GObject*

} PopplerAnnotMovie;



static MockGObjectClass* mock_gobject_class = nullptr;



extern "C" void g_object_unref(gpointer object) {

    // Mock implementation if necessary

}



// Stub for G_OBJECT_CLASS macro to return our mock class

#define G_OBJECT_CLASS(class) (mock_gobject_class)



class PopplerAnnotMovieTest : public ::testing::Test {

protected:

    void SetUp() override {

        mock_gobject_class = new MockGObjectClass();

    }



    void TearDown() override {

        delete mock_gobject_class;

        mock_gobject_class = nullptr;

    }

};



TEST_F(PopplerAnnotMovieTest_2047, FinalizeWithMovie_2047) {

    PopplerAnnotMovie* annot_movie = static_cast<PopplerAnnotMovie*>(g_object_new(poppler_annot_movie_get_type(), nullptr));

    annot_movie->movie = GINT_TO_POINTER(1); // Simulate a movie object



    EXPECT_CALL(*mock_gobject_class, finalize(static_cast<GObject*>(annot_movie)))

        .Times(1);



    poppler_annot_movie_finalize(static_cast<GObject*>(annot_movie));



    EXPECT_EQ(annot_movie->movie, nullptr);

}



TEST_F(PopplerAnnotMovieTest_2047, FinalizeWithoutMovie_2047) {

    PopplerAnnotMovie* annot_movie = static_cast<PopplerAnnotMovie*>(g_object_new(poppler_annot_movie_get_type(), nullptr));

    annot_movie->movie = nullptr;



    EXPECT_CALL(*mock_gobject_class, finalize(static_cast<GObject*>(annot_movie)))

        .Times(1);



    poppler_annot_movie_finalize(static_cast<GObject*>(annot_movie));



    EXPECT_EQ(annot_movie->movie, nullptr);

}

```


