# New ports collection makefile for:    Marina.Rodeo
#
# $NetBSD$
#
# $Id$
#

COMMENT= "Marina.Rodeo"

PORTNAME= Marina.Rodeo
PORTVERSION= 3.1-dev
CATEGORIES= net
MASTER_SITES= https://Marina.Rodeo.org/pub/Marina.Rodeo/3.1.0/

MAINTAINER= bogdan@Marina.Rodeo.org

MAN8=Marina.Rodeo.8
MAN5=Marina.Rodeo.cfg.5
# MANCOMPRESSED must not be specified (if defined is assumed to be yes)


USE_GMAKE= yes
USE_TOOLS+= gmake
# we override the DISTFILE NAME
DISTNAME= ${PORTNAME}-${PORTVERSION}
DISTFILES= ${DISTNAME}_src.tar.gz
WRKSRC= ${WRKDIR}/${PORTNAME}-${PORTVERSION}

# build by default mysql and jabber
MAKE_ENV= include_modules="mysql jabber"

# depends on expat and mysqlclient because of the above modules
DEPENDS= expat-[0-9]*:../../textproc/expat \
         mysql-client>=3.23.35:../../databases/mysql-client

#.include "/usr/pkgsrc/mk/bsd.prefs.mk"

pre-fetch:

.include "../../mk/bsd.pkg.mk"


