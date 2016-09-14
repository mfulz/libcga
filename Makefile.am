# general settings #
ACLOCAL_AMFLAGS = -I m4

pkgconfigdir = $(libdir)/pkgconfig

# --------------------- libtctor --------------------- #
libcgaincludedir = $(pkgincludedir)-@PACKAGE_VERSION@

libcgainclude_HEADERS = \
						  libcga/include/cga.h \
						  libcga/include/vector.h

lib_LTLIBRARIES = libcga-@PACKAGE_VERSION@.la

libcga_@PACKAGE_VERSION@_la_SOURCES = \
    libcga/include/cga.h \
	libcga/src/vector.c

libcga_@PACKAGE_VERSION@_la_CFLAGS = -I libcga/include $(CFLAGS)
libcga_@PACKAGE_VERSION@_la_LDFLAGS = -version-info @TCTOR_ABI_VERSION@ $(LDFLAGS)

pkgconfig_DATA = cga-@PACKAGE_VERSION@.pc
# ----------------------------------------------- #

if HAS_DOXYGEN
all-local:
	$(DOXYGEN) docs/Doxyfile
endif

EXTRA_DIST = bootstrap
