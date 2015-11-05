AM_CPPFLAGS = @VMOD_INCLUDES@ -Wall -Werror

vmoddir = @VMOD_DIR@
vmod_LTLIBRARIES = libvmod_maxmind_geoIP.la

libvmod_maxmind_geoIP_la_LDFLAGS = -module -export-dynamic -avoid-version -shared

libvmod_maxmind_geoIP_la_SOURCES = \
	vmod_maxmind_geoIP.c

nodist_libvmod_maxmind_geoIP_la_SOURCES = \
	vcc_if.c \
	vcc_if.h

vmod_maxmind_geoIP.lo: vcc_if.c vcc_if.h

vcc_if.c: vcc_if.h

vcc_if.h: @VMODTOOL@ $(top_srcdir)/src/vmod_maxmind_geoIP.vcc
	@VMODTOOL@ $(top_srcdir)/src/vmod_maxmind_geoIP.vcc

VMOD_TESTS = $(top_srcdir)/src/tests/*.vtc
.PHONY: $(VMOD_TESTS)

$(top_srcdir)/src/tests/*.vtc: libvmod_maxmind_geoIP.la
	@VARNISHTEST@ -Dvarnishd=@VARNISHD@ -Dvmod_topbuild=$(abs_top_builddir) $@

check: $(VMOD_TESTS)

EXTRA_DIST = \
	vmod_maxmind_geoIP.vcc \
	$(VMOD_TESTS)

CLEANFILES = \
	$(builddir)/vcc_if.c \
	$(builddir)/vcc_if.h \
	$(builddir)/vmod_maxmind_geoIP.rst \
	$(builddir)/vmod_maxmind_geoIP.man.rst
