## Process this file with automake to produce Makefile.in

## Created by Anjuta


uidir = $(pkgdatadir)/ui


AM_CPPFLAGS = \
	-DPACKAGE_LOCALE_DIR=\""$(localedir)"\" \
	-DPACKAGE_SRC_DIR=\""$(srcdir)"\" \
	-DPACKAGE_DATA_DIR=\""$(pkgdatadir)"\" \
	$(DAGALTONE_CFLAGS)

AM_CFLAGS =\
	 -Wall\
	 -g

bin_PROGRAMS = dagaltone

dagaltone_SOURCES = \
	main.cc \
	c-dagal-tone.cc \
	c-dagal-tone.h

dagaltone_LDFLAGS = 

dagaltone_LDADD = $(DAGALTONE_LIBS)




EXTRA_DIST = $(ui_DATA)

# Remove ui directory on uninstall
uninstall-local:
	-rm -r $(uidir)
	-rm -r $(pkgdatadir)

