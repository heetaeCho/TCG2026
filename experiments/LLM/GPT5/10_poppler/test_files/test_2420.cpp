// poppler-movie-get-rotation-angle-test.cc
//
// Unit tests for poppler_movie_get_rotation_angle()
// File under test: ./TestProjects/poppler/glib/poppler-movie.cc

#include <gtest/gtest.h>

#include <glib-object.h>
#include <glib.h>

#include <poppler.h> // PopplerMovie, POPPLER_TYPE_MOVIE, POPPLER_IS_MOVIE

namespace {

// A small log-capture utility to observe g_return_val_if_fail() messages without
// depending on internal state.
class GlibLogCapture {
public:
  GlibLogCapture() {
    old_handler_ = g_log_set_default_handler(&GlibLogCapture::Handler, this);
  }

  ~GlibLogCapture() { g_log_set_default_handler(old_handler_, nullptr); }

  int critical_count() const { return critical_count_; }
  const std::string& last_message() const { return last_message_; }
  const std::string& last_domain() const { return last_domain_; }
  GLogLevelFlags last_level() const { return last_level_; }

private:
  static void Handler(const gchar* log_domain,
                      GLogLevelFlags log_level,
                      const gchar* message,
                      gpointer user_data) {
    auto* self = static_cast<GlibLogCapture*>(user_data);
    if (!self) {
      return;
    }

    self->last_domain_ = log_domain ? log_domain : "";
    self->last_level_ = log_level;
    self->last_message_ = message ? message : "";

    if (log_level & G_LOG_LEVEL_CRITICAL) {
      self->critical_count_++;
    }
  }

  GLogFunc old_handler_ = nullptr;
  int critical_count_ = 0;
  std::string last_message_;
  std::string last_domain_;
  GLogLevelFlags last_level_ = static_cast<GLogLevelFlags>(0);
};

// The production code uses these instance fields (and POPPLER_IS_MOVIE checks
// it is a proper GObject instance). In poppler-glib, PopplerMovie is a GObject.
// We replicate the instance layout *only* to prepare observable state for the
// public getter (black-box: we assert only via the getter).
struct _PopplerMovie {
  GObject parent_instance;

  int need_poster;
  int mode;
  int synchronous_play;
  int rate;
  int rotation_angle;
};

static PopplerMovie* NewMovieOrSkip() {
  // Ensure type system is initialized (harmless if already initialized).
  // For newer GLib, it's automatic, but this is safe.
#if !GLIB_CHECK_VERSION(2, 36, 0)
  g_type_init();
#endif

  // If POPPLER_TYPE_MOVIE isn't registered for some reason, skip rather than
  // crashing in g_object_new().
  GType t = poppler_movie_get_type();
  if (t == 0) {
    return nullptr;
  }

  PopplerMovie* movie = POPPLER_MOVIE(g_object_new(t, nullptr));
  return movie;
}

class PopplerMovieTest_2420 : public ::testing::Test {
protected:
  void TearDown() override {
    if (movie_) {
      g_object_unref(movie_);
      movie_ = nullptr;
    }
  }

  PopplerMovie* movie_ = nullptr;
};

} // namespace

TEST_F(PopplerMovieTest_2420, NullMovieReturnsZeroAndLogsCritical_2420) {
  GlibLogCapture capture;

  gushort angle = poppler_movie_get_rotation_angle(nullptr);

  EXPECT_EQ(angle, static_cast<gushort>(0));
  EXPECT_GE(capture.critical_count(), 1)
      << "Expected g_return_val_if_fail() to emit a CRITICAL log for nullptr.";
}

TEST_F(PopplerMovieTest_2420, ValidMovieRotationAngleZeroReturnsZero_2420) {
  movie_ = NewMovieOrSkip();
  ASSERT_NE(movie_, nullptr);

  // Prepare state (observable via getter).
  auto* impl = reinterpret_cast<_PopplerMovie*>(movie_);
  impl->rotation_angle = 0;

  EXPECT_EQ(poppler_movie_get_rotation_angle(movie_), static_cast<gushort>(0));
}

TEST_F(PopplerMovieTest_2420, ValidMovieRotationAngleTypicalValue_2420) {
  movie_ = NewMovieOrSkip();
  ASSERT_NE(movie_, nullptr);

  auto* impl = reinterpret_cast<_PopplerMovie*>(movie_);
  impl->rotation_angle = 90;

  EXPECT_EQ(poppler_movie_get_rotation_angle(movie_), static_cast<gushort>(90));
}

TEST_F(PopplerMovieTest_2420, BoundaryRotationAngleAtGushortMax_2420) {
  movie_ = NewMovieOrSkip();
  ASSERT_NE(movie_, nullptr);

  auto* impl = reinterpret_cast<_PopplerMovie*>(movie_);
  impl->rotation_angle = 65535; // G_MAXUSHORT

  EXPECT_EQ(poppler_movie_get_rotation_angle(movie_), static_cast<gushort>(65535));
}

TEST_F(PopplerMovieTest_2420, BoundaryRotationAngleAboveGushortMaxWrapsToCast_2420) {
  movie_ = NewMovieOrSkip();
  ASSERT_NE(movie_, nullptr);

  auto* impl = reinterpret_cast<_PopplerMovie*>(movie_);
  impl->rotation_angle = 65536; // one above max

  // The function returns gushort, so the observable result must match a cast.
  EXPECT_EQ(poppler_movie_get_rotation_angle(movie_),
            static_cast<gushort>(impl->rotation_angle));
}

TEST_F(PopplerMovieTest_2420, BoundaryRotationAngleNegativeWrapsToCast_2420) {
  movie_ = NewMovieOrSkip();
  ASSERT_NE(movie_, nullptr);

  auto* impl = reinterpret_cast<_PopplerMovie*>(movie_);
  impl->rotation_angle = -1;

  EXPECT_EQ(poppler_movie_get_rotation_angle(movie_),
            static_cast<gushort>(impl->rotation_angle));
}

TEST_F(PopplerMovieTest_2420, InvalidTypeObjectReturnsZeroAndLogsCritical_2420) {
  // Verify external interaction: POPPLER_IS_MOVIE should fail and g_return_val_if_fail
  // should log critical + return 0.
  GlibLogCapture capture;

  // Create a plain GObject instance (definitely not a PopplerMovie).
  GObject* not_movie = G_OBJECT(g_object_new(G_TYPE_OBJECT, nullptr));
  ASSERT_NE(not_movie, nullptr);

  gushort angle =
      poppler_movie_get_rotation_angle(reinterpret_cast<PopplerMovie*>(not_movie));

  EXPECT_EQ(angle, static_cast<gushort>(0));
  EXPECT_GE(capture.critical_count(), 1)
      << "Expected g_return_val_if_fail() to emit a CRITICAL log for non-movie object.";

  g_object_unref(not_movie);
}