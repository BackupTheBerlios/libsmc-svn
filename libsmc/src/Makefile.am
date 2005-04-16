lib_LTLIBRARIES = libsmc.la
libsmc_la_SOURCES = musiclibrary.cpp fileinfo.cpp musiclibrary.h fileinfo.h \
		xmlparser.cpp xmlparser.h exception.cpp exception.h

# set the include path found by configure
INCLUDES = $(all_includes)

# the library search path.
libsmc_la_LDFLAGS = $(all_libraries) @GLIBMM_LIBS@ @LIBXMLXX_LIBS@ @TAGLIB_LIBS@
AM_CXXFLAGS = -Wall @GLIBMM_CFLAGS@ @LIBXMLXX_CFLAGS@ @TAGLIB_CFLAGS@

