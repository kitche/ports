# $FreeBSD$

PORTNAME=	httpd
PORTVERSION=	5.7.20150508
CATEGORIES=	www

MAINTAINER=	koue@chaosophia.net
COMMENT=	OpenBSD http server

LICENSE=	BSD3CLAUSE

DISTFILES=	${PORTNAME}-${PORTVERSION}.tar.gz

WRKSRC=		${WRKDIR}/${PORTNAME}-${PORTVERSION}/src/usr.sbin/${PORTNAME}

CONFLICTS=	apache2*

USE_GITHUB=	yes
GH_ACCOUNT=	koue
GH_PROJECT=	httpd
GH_TAGNAME=	${PORTVERSION}

USE_OPENSSL=	yes
USE_RC_SUBR=	httpd

WITH_OPENSSL_PORT=yes
OPENSSL_PORT=	security/libressl

CFLAGS+=	-Wall

MAKE_ARGS+=	BINDIR=${PREFIX}/sbin MANDIR=${PREFIX}/man/man

USERS=		www
GROUPS=		www

PLIST_FILES=	man/man5/httpd.conf.5.gz man/man8/httpd.8.gz sbin/httpd

.include <bsd.port.mk>
