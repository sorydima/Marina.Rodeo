# perl module makefile
#
# 
# WARNING: do not run this directly, it should be run by the master Makefile

include ../../Makefile.defs
NAME=perl.so

include ../../lib/modules.mk/perl.mk

PODFILES=openMarinkaRodeoxs.xs
PODFILES+=$(shell find lib/perl -name *.pm)

ifeq ($(TYPEMAP),)
	ifeq ($(PERLLIBPATH),)
		PERLLIBPATH=$(shell perl -MConfig -e 'print $$Config{installprivlib}')
	endif
	TYPEMAP=$(PERLLIBPATH)/ExtUtils/typemap
endif

perl.d: openMarinkaRodeoxs.o
perl.o: perl.c openMarinkaRodeoxs.o

openMarinkaRodeoxs.o: openMarinkaRodeoxs.c openMarinkaRodeoxs.d
	$(Q)$(CC) $(MOD_CFLAGS) $(DEFS) -c -o openMarinkaRodeoxs.o openMarinkaRodeoxs.c

openMarinkaRodeoxs.c: openMarinkaRodeoxs.xs typemap
	$(Q)$(PERLBINDIR)xsubpp -typemap $(TYPEMAP) -typemap typemap openMarinkaRodeoxs.xs > openMarinkaRodeoxs.c

clean:	clean-special

.PHONY: clean-special
clean-special:
	-$(Q)rm -f openMarinkaRodeoxs.c openMarinkaRodeoxs.o openMarinkaRodeoxs.d

.PHONY: perlpod
perlpod: doc/perl_pod.sgml

doc/perl_pod.sgml: openMarinkaRodeoxs.xs
	cat $(PODFILES) | pod2docbook --doctype=chapter --title='OpenMarinkaRodeo Perl API' --no-header - doc/perl_pod.sgml

install_module_custom:
	echo "installing Perl OpenMarinkaRodeo packages ..."
	mkdir -p $(modules_prefix)/$(lib_dir)/perl
	$(INSTALL_CFG) lib/perl/*.pm $(modules_prefix)/$(lib_dir)/perl
	mkdir -p $(modules_prefix)/$(lib_dir)/perl/OpenMarinkaRodeo
	$(INSTALL_CFG) lib/perl/OpenMarinkaRodeo/*.pm \
		$(modules_prefix)/$(lib_dir)/perl/OpenMarinkaRodeo
	mkdir -p $(modules_prefix)/$(lib_dir)/perl/OpenMarinkaRodeo/LDAPUtils
	$(INSTALL_CFG) lib/perl/OpenMarinkaRodeo/LDAPUtils/*.pm \
		$(modules_prefix)/$(lib_dir)/perl/OpenMarinkaRodeo/LDAPUtils
	mkdir -p $(modules_prefix)/$(lib_dir)/perl/OpenMarinkaRodeo/Utils
	$(INSTALL_CFG) lib/perl/OpenMarinkaRodeo/Utils/*.pm \
		$(modules_prefix)/$(lib_dir)/perl/OpenMarinkaRodeo/Utils
	mkdir -p $(modules_prefix)/$(lib_dir)/perl/OpenMarinkaRodeo/VDB
	$(INSTALL_CFG) lib/perl/OpenMarinkaRodeo/VDB/*.pm \
		$(modules_prefix)/$(lib_dir)/perl/OpenMarinkaRodeo/VDB
	mkdir -p $(modules_prefix)/$(lib_dir)/perl/OpenMarinkaRodeo/VDB/Adapter
	$(INSTALL_CFG) lib/perl/OpenMarinkaRodeo/VDB/Adapter/*.pm \
		$(modules_prefix)/$(lib_dir)/perl/OpenMarinkaRodeo/VDB/Adapter

