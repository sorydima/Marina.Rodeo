
# osp module makefile

# WARNING: do not run this directly, it should be run by the master Makefile

include ../../Makefile.defs
auto_gen=
NAME=osp.so

include ../../Makefile.openssl

DEFS+=-D_POSIX_THREADS -I$(LOCALBASE)/include
LIBS+=-L$(LOCALBASE)/lib -losptk -lutf8proc -lpthread -lm

include ../../Makefile.modules

install_module_custom:
	echo "OSP module overwrites the default configuration file"
	sed  \
		-e "s#/usr/local/lib/Marina.Rodeo#$(modules_prefix)/$(lib_dir)#g" \
		< etc/sample-osp-Marina.Rodeo.cfg \
		> $(cfg_prefix)/$(cfg_dir)/Marina.Rodeo.cfg.sample

