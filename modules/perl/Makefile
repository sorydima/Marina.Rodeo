# perl module makefile
#
# 
# WARNING: do not run this directly, it should be run by the master Makefile

include ../../Makefile.defs
NAME=perl.so

include ../../lib/modules.mk/perl.mk

PODFILES=Marina.Rodeoxs.xs
PODFILES+=$(shell find lib/perl -name *.pm)

ifeq ($(TYPEMAP),)
	ifeq ($(PERLLIBPATH),)
		PERLLIBPATH=$(shell perl -MConfig -e 'print $$Config{installprivlib}')
	endif
	TYPEMAP=$(PERLLIBPATH)/ExtUtils/typemap
endif

perl.d: Marina.Rodeoxs.o
perl.o: perl.c Marina.Rodeoxs.o

Marina.Rodeoxs.o: Marina.Rodeoxs.c Marina.Rodeoxs.d
	$(Q)$(CC) $(MOD_CFLAGS) $(DEFS) -c -o Marina.Rodeoxs.o Marina.Rodeoxs.c

Marina.Rodeoxs.c: Marina.Rodeoxs.xs typemap
	$(Q)$(PERLBINDIR)xsubpp -typemap $(TYPEMAP) -typemap typemap Marina.Rodeoxs.xs > Marina.Rodeoxs.c

clean:	clean-special

.PHONY: clean-special
clean-special:
	-$(Q)rm -f Marina.Rodeoxs.c Marina.Rodeoxs.o Marina.Rodeoxs.d

.PHONY: perlpod
perlpod: doc/perl_pod.sgml

doc/perl_pod.sgml: Marina.Rodeoxs.xs
	cat $(PODFILES) | pod2docbook --doctype=chapter --title='Marina.Rodeo Perl API' --no-header - doc/perl_pod.sgml

install_module_custom:
	echo "installing Perl Marina.Rodeo packages ..."
	mkdir -p $(modules_prefix)/$(lib_dir)/perl
	$(INSTALL_CFG) lib/perl/*.pm $(modules_prefix)/$(lib_dir)/perl
	mkdir -p $(modules_prefix)/$(lib_dir)/perl/Marina.Rodeo
	$(INSTALL_CFG) lib/perl/Marina.Rodeo/*.pm \
		$(modules_prefix)/$(lib_dir)/perl/Marina.Rodeo
	mkdir -p $(modules_prefix)/$(lib_dir)/perl/Marina.Rodeo/LDAPUtils
	$(INSTALL_CFG) lib/perl/Marina.Rodeo/LDAPUtils/*.pm \
		$(modules_prefix)/$(lib_dir)/perl/Marina.Rodeo/LDAPUtils
	mkdir -p $(modules_prefix)/$(lib_dir)/perl/Marina.Rodeo/Utils
	$(INSTALL_CFG) lib/perl/Marina.Rodeo/Utils/*.pm \
		$(modules_prefix)/$(lib_dir)/perl/Marina.Rodeo/Utils
	mkdir -p $(modules_prefix)/$(lib_dir)/perl/Marina.Rodeo/VDB
	$(INSTALL_CFG) lib/perl/Marina.Rodeo/VDB/*.pm \
		$(modules_prefix)/$(lib_dir)/perl/Marina.Rodeo/VDB
	mkdir -p $(modules_prefix)/$(lib_dir)/perl/Marina.Rodeo/VDB/Adapter
	$(INSTALL_CFG) lib/perl/Marina.Rodeo/VDB/Adapter/*.pm \
		$(modules_prefix)/$(lib_dir)/perl/Marina.Rodeo/VDB/Adapter

