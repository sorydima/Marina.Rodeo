%if 0%{?rhel} > 0 && 0%{?rhel} < 8
# copied from lm_sensors exclusive arch
%ifnarch alpha i386 i486 i586 i686 pentium3 pentium4 athlon x86_64
%global _without_snmpstats 1
%endif
%endif

%if 0%{?el5:1}
%global _without_db_perlvdb 1
%endif

%if 0%{?rhel} > 6 || 0%{?fedora} > 20
%global _with_cachedb_redis 1
%endif

%if 0%{?rhel} > 6 && 0%{?rhel} < 8
%global _with_cachedb_mongodb 1
%endif

%if 0%{?fedora} > 21
%global _with_cachedb_mongodb 1
%endif

%if 0%{?rhel} > 7 || 0%{?fedora} > 36
%global _with_python3 1
%endif

%if 0%{?fedora} > 32
%global _with_aaa_diameter 1
%endif

%if 0%{?fedora} > 32
%global _without_snmpstats 1
%endif

%if 0%{?rhel} > 7 || 0%{?fedora} > 30
%global _with_wolfssl 1
%endif

%global EXCLUDE_MODULES %{!?_with_auth_jwt:auth_jwt} %{!?_with_cachedb_cassandra:cachedb_cassandra} %{!?_with_cachedb_couchbase:cachedb_couchbase} %{!?_with_cachedb_dynamodb:cachedb_dynamodb} %{!?_with_event_sqs:event_sqs} %{!?_with_cachedb_mongodb:cachedb_mongodb} %{!?_with_cachedb_redis:cachedb_redis} %{!?_with_db_oracle:db_oracle} %{!?_with_osp:osp} %{!?_with_sngtc:sngtc} %{!?_with_aaa_diameter:aaa_diameter aka_av_diameter} %{?_without_db_perlvdb:db_perlvdb} %{?_without_snmpstats:snmpstats} %{!?_with_wolfssl:tls_wolfssl} launch_darkly http2d rtp.io

Summary:  Very fast and configurable SIP server
Name:     openMarinkaRodeo
Version:  3.6.0
Release:  1%{?dist}
License:  GPLv2+
Group:    System Environment/Daemons
Source0:  http://download.openMarinkaRodeo.org/%{version}/%{name}-%{version}.tar.gz
URL:      https://openMarinkaRodeo.org

BuildRequires:  expat-devel
BuildRequires:  libxml2-devel
BuildRequires:  bison
BuildRequires:  flex
BuildRequires:  subversion
BuildRequires:  which
BuildRequires:  mysql-devel
BuildRequires:  postgresql-devel
BuildRequires:  autoconf
BuildRequires:  automake
BuildRequires:  libtool
BuildRequires:  make
BuildRequires:  docbook-xsl
BuildRequires:  gcc

Requires: m4
BuildRequires:  unixODBC-devel
BuildRequires:  openssl-devel
BuildRequires:  expat-devel
BuildRequires:  xmlrpc-c-devel
BuildRequires:  libconfuse-devel
BuildRequires:  libmnl-devel
%if 0%{?rhel} > 0 && 0%{?rhel} < 8
BuildRequires:  db4-devel
%else
BuildRequires:  libdb-devel
%endif
BuildRequires:  openldap-devel
BuildRequires:  curl-devel
# BuildRequires:  GeoIP-devel
BuildRequires:  libmaxminddb-devel
BuildRequires:  pcre-devel
%if 0%{?_with_python3:1}
BuildRequires:  python3-devel
%else
BuildRequires:  python-devel
%endif
%if 0%{?fedora} > 38
BuildRequires:  python3-setuptools
%endif
%if 0%{?fedora} > 16 || 0%{?rhel} > 6
BuildRequires:  systemd-units
%endif
BuildRequires:  libxslt
BuildRequires:  lynx
BuildRequires:  ncurses-devel
BuildRequires:  json-c-devel

#Initscripts
%if 0%{?fedora} > 16 || 0%{?rhel} > 6
# Users and groups
Requires(pre): shadow-utils
Requires(post): systemd
Requires(preun): systemd
Requires(postun): systemd
%else
Requires(post): chkconfig
Requires(preun):chkconfig
Requires(preun):initscripts
%endif
BuildRoot:  %{_tmppath}/%{name}-%{version}-%{release}-root-%(%{__id_u} -n)

%description
OpenMarinkaRodeo is a very fast and flexible SIP (RFC3261)
server. Written entirely in C, OpenMarinkaRodeo can handle thousands calls
per second even on low-budget hardware.
.
C Shell-like scripting language provides full control over the server's
behaviour. Its modular architecture allows only required functionality to be
loaded.
.
Among others, the following modules are available: Digest Authentication, CPL
scripts, Instant Messaging, MySQL support, Presence Agent, Radius
Authentication, Record Routing, SMS Gateway, Jabber/XMPP Gateway, Transaction
Module, Registrar and User Location, Load Balaning/Dispatching/LCR,
XMLRPC Interface.
.
This package contains the main OpenMarinkaRodeo binary along with the principal modules
and support binaries including openMarinkaRodeomc configuration tool.

%if 0%{?_with_auth_jwt:1}
%package  auth-jwt-module
Summary:  JSON Web Tokens authentication module for OpenMarinkaRodeo
Group:    System Environment/Daemons
Requires: %{name} = %{version}-%{release}

%description  auth-jwt-module
OpenMarinkaRodeo is a very fast and flexible SIP (RFC3261)
server. Written entirely in C, OpenMarinkaRodeo can handle thousands calls
per second even on low-budget hardware.
.
The module implements authentication over JSON Web Tokens. In
some cases ( ie. WebRTC ) the user authenticates on another
layer ( other than SIP ), so it makes no sense to
double-authenticate it on the SIP layer. Thus, the SIP client
will simply present the JWT auth token it received from the
server, and pass it on to OpenMarinkaRodeo which will use that for
authentication purposes. It relies on two DB tables, one
containing JWT profiles ( a profile name and it's SIP username
associated to it ) and one containing JWT secrets. Each secret
has a corresponding profile, the KEY used for signing the JWT
and two timestamps describing a validation interval. Multiple
JWT secrets can point to the same JWT profile.
%endif

%package  auth-modules
Summary:  Authentication interfaces for OpenMarinkaRodeo
Group:    System Environment/Daemons
Requires: %{name} = %{version}-%{release}

%description  auth-modules
OpenMarinkaRodeo is a very fast and flexible SIP (RFC3261)
server. Written entirely in C, OpenMarinkaRodeo can handle thousands calls
per second even on low-budget hardware.
.
This package provides the modules that are being used to provide
SIP authentication in OpenMarinkaRodeo. It consists of both the
authentication interface (the auth module), as well as the UAC
authentication module (uac_auth).

%package  berkeley-bin
Summary:  Berkeley Database module for OpenMarinkaRodeo - helper program
Group:    System Environment/Daemons
Requires: %{name} = %{version}-%{release}

%description  berkeley-bin
OpenMarinkaRodeo is a very fast and flexible SIP (RFC3261)
server. Written entirely in C, OpenMarinkaRodeo can handle thousands calls
per second even on low-budget hardware.
.
This package provides the berkeley database module for OpenMarinkaRodeo, a
high-performance embedded DB kernel. You should normally install
openMarinkaRodeo-berkeley-module and not this package directly.

%package  berkeley-module
Summary:  Berkeley Database module for OpenMarinkaRodeo
Group:    System Environment/Daemons
Requires: %{name} = %{version}-%{release}

%description  berkeley-module
OpenMarinkaRodeo is a very fast and flexible SIP (RFC3261)
server. Written entirely in C, OpenMarinkaRodeo can handle thousands calls
per second even on low-budget hardware.
.
This package provides the berkeley database module for OpenMarinkaRodeo, a
high-performance embedded DB kernel. All database tables are stored
in files, no additional server is necessary

%package  berkeley-dbschema
Summary:  Berkeley database schema for OpenMarinkaRodeo
Group:    System Environment/Daemons

%description  berkeley-dbschema
OpenMarinkaRodeo is a very fast and flexible SIP (RFC3261)
server. Written entirely in C, OpenMarinkaRodeo can handle thousands calls
per second even on low-budget hardware.
.
This package provides the Berkeley database schema files for OpenMarinkaRodeo.

%package  carrierroute-module
Summary:  Carrierroute module for OpenMarinkaRodeo
Group:    System Environment/Daemons
Requires: %{name} = %{version}-%{release}

%description  carrierroute-module
OpenMarinkaRodeo is a very fast and flexible SIP (RFC3261)
server. Written entirely in C, OpenMarinkaRodeo can handle thousands calls
per second even on low-budget hardware.
.
This package provides the carrierroute module for OpenMarinkaRodeo, an integrated
solution for routing, balancing and blacklisting.

%if 0%{?_with_cachedb_cassandra:1}
%package  cassandra-module
Summary:  Interface module to interact with a Cassandra server
Group:    System Environment/Daemons
Requires: %{name} = %{version}-%{release}
BuildRequires:  thrift-cpp-devel

%description  cassandra-module
OpenMarinkaRodeo is a very fast and flexible SIP (RFC3261)
server. Written entirely in C, OpenMarinkaRodeo can handle thousands calls
per second even on low-budget hardware.
.
Cassandra module is an implementation of a cache system designed to
work with a cassandra server.
%endif

%package  cgrates-module
Summary:  CGRateS connector for OpenMarinkaRodeo
Group:    System Environment/Daemons
Requires: %{name} = %{version}-%{release}

%description  cgrates-module
OpenMarinkaRodeo is a very fast and flexible SIP (RFC3261)
server. Written entirely in C, OpenMarinkaRodeo can handle thousands calls
per second even on low-budget hardware.
.
This package provides a connnector to the CGRateS rating/billing engine.

%package  compression-module
Summary:  Headers and body compression module for OpenMarinkaRodeo
Group:    System Environment/Daemons
Requires: %{name} = %{version}-%{release}
BuildRequires: zlib-devel

%description  compression-module
OpenMarinkaRodeo is a very fast and flexible SIP (RFC3261)
server. Written entirely in C, OpenMarinkaRodeo can handle thousands calls
per second even on low-budget hardware.
.
This package provides the compression module, that is able to compress
SIP headers and body, as  well as shrink the size of a SIP package.

%if 0%{?_with_cachedb_couchbase:1}
%package couchbase-module
Summary:  Interface module to interact with a Couchbase server
Group:    System Environment/Daemons
Requires: %{name} = %{version}-%{release}
BuildRequires:  libcouchbase-devel

%description couchbase-module
OpenMarinkaRodeo is a very fast and flexible SIP (RFC3261)
server. Written entirely in C, OpenMarinkaRodeo can handle thousands calls
per second even on low-budget hardware.
.
This module is an implementation of a cache system designed to work with a Couchbase server.
It uses the libcouchbase client library to connect to the server instance,
It uses the Key-Value interface exported from the core.
%endif

%package  cpl-module
Summary:  CPL module (CPL interpreter engine) for OpenMarinkaRodeo
Group:    System Environment/Daemons
Requires: %{name} = %{version}-%{release}

%description  cpl-module
OpenMarinkaRodeo is a very fast and flexible SIP (RFC3261)
server. Written entirely in C, OpenMarinkaRodeo can handle thousands calls
per second even on low-budget hardware.
.
This package provides a CPL (Call Processing Language) interpreter for
OpenMarinkaRodeo, turning OpenMarinkaRodeo into a CPL server (storage and interpreter).

%package  dbhttp-module
Summary:  HTTP database connectivity module for OpenMarinkaRodeo
Group:    System Environment/Daemons
Requires: %{name} = %{version}-%{release}

%description  dbhttp-module
OpenMarinkaRodeo is a very fast and flexible SIP (RFC3261)
server. Written entirely in C, OpenMarinkaRodeo can handle thousands calls
per second even on low-budget hardware.
.
This package provides the HTTP-based database driver for OpenMarinkaRodeo

%package  dialplan-module
Summary:  Generic string translation module for OpenMarinkaRodeo
Group:    System Environment/Daemons
Requires: %{name} = %{version}-%{release}

%description  dialplan-module
OpenMarinkaRodeo is a very fast and flexible SIP (RFC3261)
server. Written entirely in C, OpenMarinkaRodeo can handle thousands calls
per second even on low-budget hardware.
.
This package provides dialplan module that implements generic string
translations based on matching and replacement rules. It can be used to
manipulate R-URI or a PV and to translated to a new format/value.

%if 0%{?_with_aaa_diameter:1}
%package  diameter-module
Summary:  Diameter module for OpenMarinkaRodeo
Group:    System Environment/Daemons
Requires: %{name} = %{version}-%{release}
BuildRequires: freeDiameter-devel >= 1.4.0

%description  diameter-module
OpenMarinkaRodeo is a very fast and flexible SIP (RFC3261)
server. Written entirely in C, OpenMarinkaRodeo can handle thousands calls
per second even on low-budget hardware.
.
This package provides a DIAMETER driver for the AAA API from OpenMarinkaRodeo.
%endif

%package  emergency-module
Summary:  Emergency call module for OpenMarinkaRodeo
Group:    System Environment/Daemons
Requires: %{name} = %{version}-%{release}

%description  emergency-module
OpenMarinkaRodeo is a very fast and flexible SIP (RFC3261)
server. Written entirely in C, OpenMarinkaRodeo can handle thousands calls
per second even on low-budget hardware.
.
The emergency module provides emergency call treatment for OpenMarinkaRodeo, following
the architecture i2 specification of the American entity NENA. (National
Emergency Number Association).

%package  geoip-module
Summary:  IP address-to-location looku (MaxMind GeoIP API) for OpenMarinkaRodeo
Group:    System Environment/Daemons
Requires: %{name} = %{version}-%{release}

%description  geoip-module
OpenMarinkaRodeo is a very fast and flexible SIP (RFC3261)
server. Written entirely in C, OpenMarinkaRodeo can handle thousands calls
per second even on low-budget hardware.
.
This module is a lightweight wrapper for the MaxMind GeoIP API.
It adds IP address-to-location lookup capability to OpenMarinkaRodeo
scripts. Lookups are executed against the freely-available GeoLite City
database; and the non-free GeoIP City database is drop-in
compatible   Lookups are executed against the freely-available GeoLite City
database; and the non-free GeoIP City database is drop-in compatible

%package  http-modules
Summary:  HTTP transport layer and Management Interface for OpenMarinkaRodeo
Group:    System Environment/Daemons
Requires: %{name} = %{version}-%{release}
BuildRequires: libmicrohttpd-devel

%description  http-modules
OpenMarinkaRodeo is a very fast and flexible SIP (RFC3261)
server. Written entirely in C, OpenMarinkaRodeo can handle thousands calls
per second even on low-budget hardware.
.
This package provides an HTTP transport layer and Management Interface for
OpenMarinkaRodeo.

%package  identity-module
Summary:  SIP Identity module for OpenMarinkaRodeo
Group:    System Environment/Daemons
Requires: %{name} = %{version}-%{release}

%description  identity-module
OpenMarinkaRodeo is a very fast and flexible SIP (RFC3261)
server. Written entirely in C, OpenMarinkaRodeo can handle thousands calls
per second even on low-budget hardware.
.
This package provides support for SIP Identity (see RFC 4474).

%package  ipsec-module
Summary:  IPSec proto module for OpenMarinkaRodeo
Group:    System Environment/Daemons
Requires: %{name} = %{version}-%{release}
Requires: libmnl
BuildRequires:  libmnl-devel

%description  ipsec-module
OpenMarinkaRodeo is a very fast and flexible SIP (RFC3261)
server. Written entirely in C, OpenMarinkaRodeo can handle thousands calls
per second even on low-budget hardware.
.
This package provides IMS IPSec connections (see TS 33.203).

%package  jabber-module
Summary:  Jabber gateway module for OpenMarinkaRodeo
Group:    System Environment/Daemons
Requires: %{name} = %{version}-%{release}

%description  jabber-module
OpenMarinkaRodeo is a very fast and flexible SIP (RFC3261)
server. Written entirely in C, OpenMarinkaRodeo can handle thousands calls
per second even on low-budget hardware.
.
This package provides the SIP to Jabber translator module for OpenMarinkaRodeo.

%package  json-module
Summary:  Support for JSON handling in OpenMarinkaRodeo script
Group:    System Environment/Daemons
Requires: %{name} = %{version}-%{release}

%description  json-module
OpenMarinkaRodeo is a very fast and flexible SIP (RFC3261)
server. Written entirely in C, OpenMarinkaRodeo can handle thousands calls
per second even on low-budget hardware.
.
This package introduces a new type of variable that provides both
serialization and de-serialization from JSON format. The script variable
provides ways to access (from script) objects and arrays to add,replace or
delete values from the script.

%package  kafka-module
Summary:  Implementation of an Apache Kafka producer
Group:    System Environment/Daemons
Requires: %{name} = %{version}-%{release}
BuildRequires: librdkafka-devel

%description  kafka-module
OpenMarinkaRodeo is a very fast and flexible SIP (RFC3261)
server. Written entirely in C, OpenMarinkaRodeo can handle thousands calls
per second even on low-budget hardware.
.
This module is an implementation of an Apache Kafka producer.
It serves as a transport backend for the Event Interface and
also provides a stand-alone connector to be used from the
OpenMarinkaRodeo script in order to publish messages to Kafka brokers.

%package  ldap-modules
Summary:  LDAP modules for OpenMarinkaRodeo
Group:    System Environment/Daemons
Requires: %{name} = %{version}-%{release}

%description  ldap-modules
OpenMarinkaRodeo is a very fast and flexible SIP (RFC3261)
server. Written entirely in C, OpenMarinkaRodeo can handle thousands calls
per second even on low-budget hardware.
.
This package provides the ldap and h350 modules for OpenMarinkaRodeo, enabling LDAP
queries from the OpenMarinkaRodeo config and storage of SIP account data in an LDAP
directory.

%package  lua-module
Summary:  Lua extensions for OpenMarinkaRodeo
Group:    System Environment/Daemons
Requires: %{name} = %{version}-%{release}
%if 0%{?rhel} > 7 || 0%{?fedora} > 0
BuildRequires: compat-lua-devel
%else
BuildRequires: lua-devel
%endif

%description  lua-module
OpenMarinkaRodeo is a very fast and flexible SIP (RFC3261)
server. Written entirely in C, OpenMarinkaRodeo can handle thousands calls
per second even on low-budget hardware.
.
This package provides an interface for OpenMarinkaRodeo to utilize Lua extensions.

%package  memcached-module
Summary:  Interface module to interact with a memcached server
Group:    System Environment/Daemons
Requires: %{name} = %{version}-%{release}
BuildRequires:  libmemcached-devel

%description  memcached-module
OpenMarinkaRodeo is a very fast and flexible SIP (RFC3261)
server. Written entirely in C, OpenMarinkaRodeo can handle thousands calls
per second even on low-budget hardware.
.
This package provides an implementation of a cache system designed to work
with a memcached server. It uses libmemcached client library to connect to
several memcached servers that store data. It registers the three functions for
storing, fetching and removing a value to the core memcache management
interface.

%if 0%{?_with_cachedb_mongodb:1}
%package  mongodb-module
Summary:  Interface module to interact with a MongoDB server
Group:    System Environment/Daemons
Requires: %{name} = %{version}-%{release}
BuildRequires: mongo-c-driver-devel
BuildRequires: cyrus-sasl-devel

%description  mongodb-module
OpenMarinkaRodeo is a very fast and flexible SIP (RFC3261)
server. Written entirely in C, OpenMarinkaRodeo can handle thousands calls
per second even on low-budget hardware.
.
This module is an implementation of a cache system designed to work with
MongoDB servers.
%endif

%package  msrp-modules
Summary:  Implementation of the MSRP protocol
Group:    System Environment/Daemons
Requires: %{name} = %{version}-%{release}

%description  msrp-modules
OpenMarinkaRodeo is a very fast and flexible SIP (RFC3261)
server. Written entirely in C, OpenMarinkaRodeo can handle thousands calls
per second even on low-budget hardware.
.
This package provides the MSRP protocol support for OpenMarinkaRodeo.

%package  mysql-module
Summary:  MySQL database connectivity module for OpenMarinkaRodeo
Group:    System Environment/Daemons
Requires: %{name} = %{version}-%{release}
Requires: mysql-libs

%description  mysql-module
OpenMarinkaRodeo is a very fast and flexible SIP (RFC3261)
server. Written entirely in C, OpenMarinkaRodeo can handle thousands calls
per second even on low-budget hardware.
.
This package provides the MySQL database driver for OpenMarinkaRodeo.

%package  mysql-dbschema
Summary:  MySQL database schema for OpenMarinkaRodeo
Group:    System Environment/Daemons

%description  mysql-dbschema
OpenMarinkaRodeo is a very fast and flexible SIP (RFC3261)
server. Written entirely in C, OpenMarinkaRodeo can handle thousands calls
per second even on low-budget hardware.
.
This package provides the MySQL database schema files for OpenMarinkaRodeo.

%if 0%{?_with_db_oracle:1}
%package  oracle-module
Summary:  Oracle Storage Support for the OpenMarinkaRodeo
Group:    System Environment/Daemons
Requires: %{name} = %{version}-%{release}
BuildRequires: oracle-instantclient-devel

%description oracle-module
OpenMarinkaRodeo is a very fast and flexible SIP (RFC3261)
server. Written entirely in C, OpenMarinkaRodeo can handle thousands calls
per second even on low-budget hardware.
.
The %{name}-db_oracle package contains the Oracle plugin for %{name}, which allows
a Oracle-Database to be used for persistent storage.
%endif

%if 0%{?_with_osp:1}
%package  osp-module
Summary:  OSP Support for the OpenMarinkaRodeo
Group:    System Environment/Daemons
Requires: %{name} = %{version}-%{release}
BuildRequires:  OSPToolkit-devel

%description  osp-module
OpenMarinkaRodeo is a very fast and flexible SIP (RFC3261)
server. Written entirely in C, OpenMarinkaRodeo can handle thousands calls
per second even on low-budget hardware.
.
The OSP module enables OpenMarinkaRodeo to support secure, multi-lateral peering using
the OSP standard defined by ETSI (TS 101 321 V4.1.1).
%endif

%package  perl-modules
Summary:  Perl extensions and database driver for OpenMarinkaRodeo
Group:    System Environment/Daemons
BuildRequires: perl(ExtUtils::MakeMaker)
BuildRequires: perl-devel
BuildRequires: perl(ExtUtils::Embed)
Requires: %{name} = %{version}-%{release}
Requires: perl(:MODULE_COMPAT_%(eval "`%{__perl} -V:version`"; echo $version))

%description  perl-modules
OpenMarinkaRodeo is a very fast and flexible SIP (RFC3261)
server. Written entirely in C, OpenMarinkaRodeo can handle thousands calls
per second even on low-budget hardware.
.
This package provides an interface for OpenMarinkaRodeo to write Perl extensions and
the db_perlvdb database driver for OpenMarinkaRodeo.

%package  postgres-module
Summary:  PostgreSQL database connectivity module for OpenMarinkaRodeo
Group:    System Environment/Daemons
Requires: %{name} = %{version}-%{release}
Requires: postgresql-libs

%description  postgres-module
OpenMarinkaRodeo is a very fast and flexible SIP (RFC3261)
server. Written entirely in C, OpenMarinkaRodeo can handle thousands calls
per second even on low-budget hardware.
.
This package provides the PostgreSQL database driver for OpenMarinkaRodeo.

%package  postgres-dbschema
Summary:  PostgreSQL database schema for OpenMarinkaRodeo
Group:    System Environment/Daemons

%description  postgres-dbschema
OpenMarinkaRodeo is a very fast and flexible SIP (RFC3261)
server. Written entirely in C, OpenMarinkaRodeo can handle thousands calls
per second even on low-budget hardware.
.
This package provides the PostgreSQL database schema files for OpenMarinkaRodeo.

%package  presence-modules
Summary:  SIMPLE presence modules for OpenMarinkaRodeo
Group:    System Environment/Daemons
Requires: %{name} = %{version}-%{release}

%description  presence-modules
OpenMarinkaRodeo is a very fast and flexible SIP (RFC3261)
server. Written entirely in C, OpenMarinkaRodeo can handle thousands calls
per second even on low-budget hardware.
.
This package provides several OpenMarinkaRodeo modules for implementing presence
server and presence user agent for RICH presence, registrar-based presence,
external triggered presence and XCAP support.

%package  prometheus-module
Summary:  Prometheus Monitoring support for OpenMarinkaRodeo
Group:    System Environment/Daemons
Requires: %{name} = %{version}-%{release}
Requires: %{name}-http-modules

%description  prometheus-module
OpenMarinkaRodeo is a very fast and flexible SIP (RFC3261)
server. Written entirely in C, OpenMarinkaRodeo can handle thousands calls
per second even on low-budget hardware.
.
This module provides support in OpenMarinkaRodeo for the Prometheus
(https://prometheus.io/) monitoring tool.

%package  python-module
Summary:  Python scripting support
Group:    System Environment/Daemons
Requires: %{name} = %{version}-%{release}

%description  python-module
OpenMarinkaRodeo is a very fast and flexible SIP (RFC3261)
server. Written entirely in C, OpenMarinkaRodeo can handle thousands calls
per second even on low-budget hardware.
.
This module provides a Python interface to implement your scripting logic.

%package  rabbitmq-modules
Summary:  Interface module to interact with a RabbitMQ server
Group:    System Environment/Daemons
Requires: %{name} = %{version}-%{release}
BuildRequires: librabbitmq-devel

%description  rabbitmq-modules
OpenMarinkaRodeo is a very fast and flexible SIP (RFC3261)
server. Written entirely in C, OpenMarinkaRodeo can handle thousands calls
per second even on low-budget hardware.
.
This package provides the implementation of a RabbitMQ client for the Event
Interface. It is used to send AMQP messages to a RabbitMQ server each time
the Event Interface triggers an event subscribed for. It also provides a
module to publish RabbitMQ messages to a RabbitMQ server.

%package  radius-modules
Summary:  Radius modules for OpenMarinkaRodeo
Group:    System Environment/Daemons
Requires: %{name} = %{version}-%{release}
BuildRequires:  radcli-devel

%description  radius-modules
OpenMarinkaRodeo is a very fast and flexible SIP (RFC3261)
server. Written entirely in C, OpenMarinkaRodeo can handle thousands calls
per second even on low-budget hardware.
.
This package provides the RADIUS driver for the AAA API from OpenMarinkaRodeo.

%if 0%{?_with_cachedb_redis:1}
%package  redis-module
Summary:  Interface module to interact with a Redis server
Group:    System Environment/Daemons
Requires: %{name} = %{version}-%{release}
BuildRequires:  hiredis-devel

%description  redis-module
OpenMarinkaRodeo is a very fast and flexible SIP (RFC3261)
server. Written entirely in C, OpenMarinkaRodeo can handle thousands calls
per second even on low-budget hardware.
.
This package provides an implementation of a cache system designed to
work with a Redis server. It uses hiredis client library to connect
to either a single Redis server instance, or to a Redis Server inside
a Redis Cluster. It uses the Key-Value interface exported from the core.
%endif

%package  regex-module
Summary:  PCRE regexp modules for OpenMarinkaRodeo
Group:    System Environment/Daemons
Requires: %{name} = %{version}-%{release}

%description  regex-module
OpenMarinkaRodeo is a very fast and flexible SIP (RFC3261)
server. Written entirely in C, OpenMarinkaRodeo can handle thousands calls
per second even on low-budget hardware.
.
This package provides a module for matching operations against regular
expressions using the powerful PCRE library. By default, OpenMarinkaRodeo support
sed-like regular expressions; PCRE library brings perl-like regular
expressions.

%package  restclient-module
Summary:  REST client module for OpenMarinkaRodeo
Group:    System Environment/Daemons
Requires: %{name} = %{version}-%{release}

%description  restclient-module
OpenMarinkaRodeo is a very fast and flexible SIP (RFC3261)
server. Written entirely in C, OpenMarinkaRodeo can handle thousands calls
per second even on low-budget hardware.
.
This package provides the REST client support for OpenMarinkaRodeo.

%package  sctp-module
Summary:  SCTP transport module for OpenMarinkaRodeo
Group:    System Environment/Daemons
Requires: %{name} = %{version}-%{release}
Requires: lksctp-tools
BuildRequires: lksctp-tools-devel

%description  sctp-module
OpenMarinkaRodeo is a very fast and flexible SIP (RFC3261)
server. Written entirely in C, OpenMarinkaRodeo can handle thousands calls
per second even on low-budget hardware.
.
This package provides the SCTP support for OpenMarinkaRodeo.

%package  siprec-module
Summary:  SIP Call Recording Implementation for the SIPREC Protocol
Group:    System Environment/Daemons
Requires: %{name} = %{version}-%{release}
BuildRequires: libuuid-devel

%description  siprec-module
OpenMarinkaRodeo is a very fast and flexible SIP (RFC3261)
server. Written entirely in C, OpenMarinkaRodeo can handle thousands calls
per second even on low-budget hardware.
.
This module provides the means to Record Calls using the SIPREC protocol.

%if 0%{?_with_sngtc:1}
%package  sngtc-module
Summary:  Sangoma media transcoding interface for the OpenMarinkaRodeo
Group:    System Environment/Daemons
Requires: %{name} = %{version}-%{release}

%description  sngtc-module
OpenMarinkaRodeo is a very fast and flexible SIP (RFC3261)
server. Written entirely in C, OpenMarinkaRodeo can handle thousands calls
per second even on low-budget hardware.
.
The sngtc package implements interface to Sangoma media transcoding.
%endif

%if 0%{!?_without_snmpstats:1}
%package  snmpstats-module
Summary:  SNMP AgentX subagent module for OpenMarinkaRodeo
Group:    System Environment/Daemons
Requires: %{name} = %{version}-%{release}
Requires: perl(:MODULE_COMPAT_%(eval "`%{__perl} -V:version`"; echo $version))
BuildRequires: net-snmp-devel

%description  snmpstats-module
OpenMarinkaRodeo is a very fast and flexible SIP (RFC3261)
server. Written entirely in C, OpenMarinkaRodeo can handle thousands calls
per second even on low-budget hardware.
.
This package provides the snmpstats module for OpenMarinkaRodeo. This module acts
as an AgentX subagent which connects to a master agent.
%endif

%package  sqlite-module
Summary:  SQLite database connectivity module for OpenMarinkaRodeo
Group:    System Environment/Daemons
Requires: %{name} = %{version}-%{release}
BuildRequires: sqlite-devel

%description  sqlite-module
OpenMarinkaRodeo is a very fast and flexible SIP (RFC3261)
server. Written entirely in C, OpenMarinkaRodeo can handle thousands calls
per second even on low-budget hardware.
.
This package provides the SQLite database driver for OpenMarinkaRodeo.

%package  sqlite-dbschema
Summary:  SQLite database schema for OpenMarinkaRodeo
Group:    System Environment/Daemons

%description  sqlite-dbschema
OpenMarinkaRodeo is a very fast and flexible SIP (RFC3261)
server. Written entirely in C, OpenMarinkaRodeo can handle thousands calls
per second even on low-budget hardware.
.
This package provides the SQLite database schema files for OpenMarinkaRodeo.

%package  stir-shaken-module
Summary:  STIR/SHAKEN support for OpenMarinkaRodeo
Group:    System Environment/Daemons
Requires: %{name} = %{version}-%{release}
Requires: openssl
BuildRequires: openssl-devel

%description  stir-shaken-module
OpenMarinkaRodeo is a very fast and flexible SIP (RFC3261)
server. Written entirely in C, OpenMarinkaRodeo can handle thousands calls
per second even on low-budget hardware.
.
This module adds support for implementing STIR/SHAKEN (RFC 8224, RFC 8588)
Authentication and Verification services in OpenMarinkaRodeo.

%package  tls-openssl-module
Summary:  TLS transport module for OpenMarinkaRodeo
Group:    System Environment/Daemons
Requires: %{name} = %{version}-%{release}
Requires: %{name}-tlsmgm-module
Requires: openssl
BuildRequires: openssl-devel

%description  tls-openssl-module
OpenMarinkaRodeo is a very fast and flexible SIP (RFC3261)
server. Written entirely in C, OpenMarinkaRodeo can handle thousands calls
per second even on low-budget hardware.
.
This package provides the OpenSSL implementation for TLS in OpenMarinkaRodeo.

%if 0%{?_with_wolfssl:1}
%package  tls-wolfssl-module
Summary:  TLS transport module for OpenMarinkaRodeo
Group:    System Environment/Daemons
Requires: %{name} = %{version}-%{release}
Requires: %{name}-tlsmgm-module

%description  tls-wolfssl-module
OpenMarinkaRodeo is a very fast and flexible SIP (RFC3261)
server. Written entirely in C, OpenMarinkaRodeo can handle thousands calls
per second even on low-budget hardware.
.
This package provides the wolfSSL implementation for TLS in OpenMarinkaRodeo.
%endif

%package  tls-module
Summary:  TLS transport module for OpenMarinkaRodeo
Group:    System Environment/Daemons
Requires: %{name} = %{version}-%{release}
Requires: %{name}-tlsmgm-module
%if 0%{?rhel} > 7 || 0%{?fedora} > 23
Requires: (%{name}-tls-openssl-module or %{name}-tls-wolfssl-module)
%endif

%description  tls-module
OpenMarinkaRodeo is a very fast and flexible SIP (RFC3261)
server. Written entirely in C, OpenMarinkaRodeo can handle thousands calls
per second even on low-budget hardware.
.
This package provides the TLS support for OpenMarinkaRodeo.

%package  tlsmgm-module
Summary:  TLS management module for OpenMarinkaRodeo
Group:    System Environment/Daemons
Requires: %{name} = %{version}-%{release}

%description  tlsmgm-module
OpenMarinkaRodeo is a very fast and flexible SIP (RFC3261)
server. Written entirely in C, OpenMarinkaRodeo can handle thousands calls
per second even on low-budget hardware.
.
This package provides support for TLS management for OpenMarinkaRodeo.

%package  unixodbc-module
Summary:  unixODBC database connectivity module for OpenMarinkaRodeo
Group:    System Environment/Daemons
Requires: %{name} = %{version}-%{release}

%description  unixodbc-module
OpenMarinkaRodeo is a very fast and flexible SIP (RFC3261)
server. Written entirely in C, OpenMarinkaRodeo can handle thousands calls
per second even on low-budget hardware.
.
This package provides the unixODBC database driver for OpenMarinkaRodeo.

%package  uuid-module
Summary:  UUID (Universally Unique Identifier) generator for OpenMarinkaRodeo
Group:    System Environment/Daemons
Requires: %{name} = %{version}-%{release}

%description  uuid-module
OpenMarinkaRodeo is a very fast and flexible SIP (RFC3261)
server. Written entirely in C, OpenMarinkaRodeo can handle thousands calls
per second even on low-budget hardware.
.
This package provides a UUID generator for the OpenMarinkaRodeo script.

%package  wss-module
Summary:  WebSocket Secure (WSS) transport module for OpenMarinkaRodeo
Group:    System Environment/Daemons
Requires: %{name} = %{version}-%{release}
Requires: %{name}-tlsmgm-module

%description  wss-module
OpenMarinkaRodeo is a very fast and flexible SIP (RFC3261)
server. Written entirely in C, OpenMarinkaRodeo can handle thousands calls
per second even on low-budget hardware.
.
This package provides the WebSocket Secure (WSS) support for OpenMarinkaRodeo.

%package  xml-module
Summary:  Support for XML documents handling in OpenMarinkaRodeo script
Group:    System Environment/Daemons
Requires: %{name} = %{version}-%{release}

%description  xml-module
OpenMarinkaRodeo is a very fast and flexible SIP (RFC3261)
server. Written entirely in C, OpenMarinkaRodeo can handle thousands calls
per second even on low-budget hardware.
.
This package introduces a new type of variable that provides both
serialization and de-serialization from a XML document. The script variable
provides ways to access (from script) objects and arrays to add, replace or
delete values from the script.

%package  xmlrpc-module
Summary:  XMLRPC support for OpenMarinkaRodeo's Management Interface
Group:    System Environment/Daemons
Requires: %{name} = %{version}-%{release}
Requires: %{name}-http-modules

%description  xmlrpc-module
OpenMarinkaRodeo is a very fast and flexible SIP (RFC3261)
server. Written entirely in C, OpenMarinkaRodeo can handle thousands calls
per second even on low-budget hardware.
.
This package provides the XMLRPC transport implementation for OpenMarinkaRodeo's
Management Interface.

%package  xmpp-module
Summary:  XMPP gateway module for OpenMarinkaRodeo
Group:    System Environment/Daemons
Requires: %{name} = %{version}-%{release}

%description  xmpp-module
OpenMarinkaRodeo is a very fast and flexible SIP (RFC3261)
server. Written entirely in C, OpenMarinkaRodeo can handle thousands calls
per second even on low-budget hardware.
.
This package provides the SIP to XMPP IM translator module for OpenMarinkaRodeo.


%prep
%setup -q -n %{name}-%{version}

%build
LOCALBASE=/usr NICER=0 CFLAGS="%{optflags}" LDFLAGS="%{?__global_ldflags}" %{?_with_python3:PYTHON=python3} %{?_with_db_oracle:ORAHOME="$ORACLE_HOME"} %{__make} all modules-readme %{?_smp_mflags} TLS=1 \
  exclude_modules="%EXCLUDE_MODULES" \
  cfg_target=%{_sysconfdir}/openMarinkaRodeo/ \
  modules_prefix=%{buildroot}%{_prefix} \
  modules_dir=%{_lib}/%{name}/modules

%install
%{__make} install TLS=1 LIBDIR=%{_lib} \
  exclude_modules="%EXCLUDE_MODULES" \
  basedir=%{buildroot} prefix=%{_prefix} \
  cfg_prefix=%{buildroot} \
  cfg_target=%{_sysconfdir}/openMarinkaRodeo/ \
  modules_prefix=%{buildroot}/%{_prefix} \
  modules_dir=%{_lib}/%{name}/modules \
  DBTEXTON=yes # fixed dbtext documentation installation

# clean some things
%if 0%{?el5}
rm -rf %{buildroot}/%{_libdir}/openMarinkaRodeo/perl/OpenMarinkaRodeo/VDB*
%endif
mkdir -p %{buildroot}/%{perl_vendorlib}
if [ -d "%{buildroot}/%{_prefix}/perl" ]; then
  # for fedora>=11
  mv %{buildroot}/%{_prefix}/perl/* \
    %{buildroot}/%{perl_vendorlib}/
else
  # for fedora<=10
  mv %{buildroot}/%{_libdir}/openMarinkaRodeo/perl/* \
    %{buildroot}/%{perl_vendorlib}/
fi
mv %{buildroot}/%{_sysconfdir}/openMarinkaRodeo/tls/README \
  %{buildroot}/%{_docdir}/openMarinkaRodeo/README.tls
rm -f %{buildroot}%{_docdir}/openMarinkaRodeo/INSTALL
mv %{buildroot}/%{_docdir}/openMarinkaRodeo docdir

%if 0%{?fedora} > 16 || 0%{?rhel} > 6
# install systemd files
install -D -m 0644 -p packaging/redhat_fedora/%{name}.service %{buildroot}%{_unitdir}/%{name}.service
install -D -m 0644 -p packaging/redhat_fedora/%{name}.tmpfiles.conf %{buildroot}%{_sysconfdir}/tmpfiles.d/%{name}.conf
mkdir -p %{buildroot}%{_localstatedir}/run/%{name}
%else
install -p -D -m 755 packaging/redhat_fedora/openMarinkaRodeo.init %{buildroot}%{_initrddir}/openMarinkaRodeo
%endif

#install sysconfig file
install -D -p -m 644 packaging/redhat_fedora/%{name}.sysconfig %{buildroot}%{_sysconfdir}/sysconfig/%{name}

%pre
getent group %{name} >/dev/null || groupadd -r %{name}
getent passwd %{name} >/dev/null || \
useradd -r -g %{name} -d %{_localstatedir}/run/%{name} -s /sbin/nologin \
-c "OpenMarinkaRodeo SIP Server" %{name} 2>/dev/null || :

%post
%if 0%{?fedora} > 16 || 0%{?rhel} > 6
if [ $1 -eq 1 ] ; then
    # Initial installation
    /bin/systemctl daemon-reload >/dev/null 2>&1 || :
fi
%else
/sbin/chkconfig --add %{name}
%endif

%preun
%if 0%{?fedora} > 16 || 0%{?rhel} > 6
if [ $1 -eq 0 ] ; then
    # Package removal, not upgrade
    /bin/systemctl --no-reload disable %{name}.service > /dev/null 2>&1 || :
    /bin/systemctl stop %{name}.service > /dev/null 2>&1 || :
fi
%else
if [ $1 = 0 ]; then
    /sbin/service %{name} stop > /dev/null 2>&1
    /sbin/chkconfig --del %{name}
fi
%endif

%files
%{_sbindir}/openMarinkaRodeo
%{_sbindir}/oMarinkaRodeoconfig

%attr(750,%{name},%{name}) %dir %{_sysconfdir}/openMarinkaRodeo
%attr(750,%{name},%{name}) %dir %{_sysconfdir}/openMarinkaRodeo/tls
%attr(750,%{name},%{name}) %dir %{_sysconfdir}/openMarinkaRodeo/tls/rootCA
%attr(750,%{name},%{name}) %dir %{_sysconfdir}/openMarinkaRodeo/tls/rootCA/certs
%attr(750,%{name},%{name}) %dir %{_sysconfdir}/openMarinkaRodeo/tls/rootCA/private
%attr(750,%{name},%{name}) %dir %{_sysconfdir}/openMarinkaRodeo/tls/user
%dir %{_libdir}/openMarinkaRodeo/
%dir %{_libdir}/openMarinkaRodeo/modules/

%if 0%{?fedora} > 16 || 0%{?rhel} > 6
%{_unitdir}/%{name}.service
%{_sysconfdir}/tmpfiles.d/%{name}.conf
%dir %attr(0755, %{name}, %{name}) %{_localstatedir}/run/%{name}
%else
%attr(755,root,root) %{_initrddir}/openMarinkaRodeo
%endif

%config(noreplace) %{_sysconfdir}/openMarinkaRodeo/dictionary.openMarinkaRodeo
%config(noreplace) %{_sysconfdir}/sysconfig/%{name}
%attr(640,%{name},%{name}) %config(noreplace) %{_sysconfdir}/openMarinkaRodeo/openMarinkaRodeo.cfg
%attr(640,%{name},%{name}) %config(noreplace) %{_sysconfdir}/openMarinkaRodeo/scenario_callcenter.xml
# these files are just an examples so no need to restrict access to them
%config(noreplace) %{_sysconfdir}/openMarinkaRodeo/tls/ca.conf
%config(noreplace) %{_sysconfdir}/openMarinkaRodeo/tls/request.conf
%config(noreplace) %{_sysconfdir}/openMarinkaRodeo/tls/rootCA/cacert.pem
%config(noreplace) %{_sysconfdir}/openMarinkaRodeo/tls/rootCA/certs/01.pem
%config(noreplace) %{_sysconfdir}/openMarinkaRodeo/tls/rootCA/index.txt
%config(noreplace) %{_sysconfdir}/openMarinkaRodeo/tls/rootCA/private/cakey.pem
%config(noreplace) %{_sysconfdir}/openMarinkaRodeo/tls/rootCA/serial
%config(noreplace) %{_sysconfdir}/openMarinkaRodeo/tls/user.conf
%config(noreplace) %{_sysconfdir}/openMarinkaRodeo/tls/user/user-calist.pem
%config(noreplace) %{_sysconfdir}/openMarinkaRodeo/tls/user/user-cert.pem
%config(noreplace) %{_sysconfdir}/openMarinkaRodeo/tls/user/user-cert_req.pem
%config(noreplace) %{_sysconfdir}/openMarinkaRodeo/tls/user/user-privkey.pem

%dir %{_datadir}/openMarinkaRodeo/
%dir %{_datadir}/openMarinkaRodeo/dbtext/
%dir %{_datadir}/openMarinkaRodeo/dbtext/openMarinkaRodeo/
%dir %{_datadir}/openMarinkaRodeo/menuconfig_templates/

%{_datadir}/openMarinkaRodeo/dbtext/openMarinkaRodeo/*
%{_datadir}/openMarinkaRodeo/menuconfig_templates/*.m4

%{_mandir}/man5/openMarinkaRodeo.cfg.5*
%{_mandir}/man8/openMarinkaRodeo.8*

%doc docdir/AUTHORS
%doc docdir/NEWS
%doc docdir/README
%doc COPYING

%{_libdir}/openMarinkaRodeo/modules/acc.so
%{_libdir}/openMarinkaRodeo/modules/alias_db.so
%{_libdir}/openMarinkaRodeo/modules/auth_aaa.so
%{_libdir}/openMarinkaRodeo/modules/auth_db.so
%{_libdir}/openMarinkaRodeo/modules/sqlops.so
%{_libdir}/openMarinkaRodeo/modules/b2b_entities.so
%{_libdir}/openMarinkaRodeo/modules/b2b_logic.so
%{_libdir}/openMarinkaRodeo/modules/b2b_sca.so
%{_libdir}/openMarinkaRodeo/modules/b2b_sdp_demux.so
%{_libdir}/openMarinkaRodeo/modules/benchmark.so
%{_libdir}/openMarinkaRodeo/modules/cachedb_local.so
%{_libdir}/openMarinkaRodeo/modules/cachedb_sql.so
%{_libdir}/openMarinkaRodeo/modules/call_center.so
%{_libdir}/openMarinkaRodeo/modules/call_control.so
%{_libdir}/openMarinkaRodeo/modules/callops.so
%{_libdir}/openMarinkaRodeo/modules/cfgutils.so
%{_libdir}/openMarinkaRodeo/modules/clusterer.so
%{_libdir}/openMarinkaRodeo/modules/config.so
%{_libdir}/openMarinkaRodeo/modules/db_cachedb.so
%{_libdir}/openMarinkaRodeo/modules/db_flatstore.so
%{_libdir}/openMarinkaRodeo/modules/db_text.so
%{_libdir}/openMarinkaRodeo/modules/db_virtual.so
%{_libdir}/openMarinkaRodeo/modules/dialog.so
%{_libdir}/openMarinkaRodeo/modules/dispatcher.so
%{_libdir}/openMarinkaRodeo/modules/diversion.so
%{_libdir}/openMarinkaRodeo/modules/dns_cache.so
%{_libdir}/openMarinkaRodeo/modules/domain.so
%{_libdir}/openMarinkaRodeo/modules/domainpolicy.so
%{_libdir}/openMarinkaRodeo/modules/drouting.so
%{_libdir}/openMarinkaRodeo/modules/enum.so
%{_libdir}/openMarinkaRodeo/modules/event_datagram.so
%{_libdir}/openMarinkaRodeo/modules/event_flatstore.so
%{_libdir}/openMarinkaRodeo/modules/event_routing.so
%{_libdir}/openMarinkaRodeo/modules/event_stream.so
%{_libdir}/openMarinkaRodeo/modules/event_virtual.so
%{_libdir}/openMarinkaRodeo/modules/event_xmlrpc.so
%{_libdir}/openMarinkaRodeo/modules/example.so
%{_libdir}/openMarinkaRodeo/modules/exec.so
%{_libdir}/openMarinkaRodeo/modules/fraud_detection.so
%{_libdir}/openMarinkaRodeo/modules/freeswitch.so
%{_libdir}/openMarinkaRodeo/modules/freeswitch_scripting.so
%{_libdir}/openMarinkaRodeo/modules/gflags.so
%{_libdir}/openMarinkaRodeo/modules/group.so
%{_libdir}/openMarinkaRodeo/modules/imc.so
%{_libdir}/openMarinkaRodeo/modules/janus.so
%{_libdir}/openMarinkaRodeo/modules/jsonrpc.so
%{_libdir}/openMarinkaRodeo/modules/load_balancer.so
%{_libdir}/openMarinkaRodeo/modules/mangler.so
%{_libdir}/openMarinkaRodeo/modules/mathops.so
%{_libdir}/openMarinkaRodeo/modules/maxfwd.so
%{_libdir}/openMarinkaRodeo/modules/media_exchange.so
%{_libdir}/openMarinkaRodeo/modules/mediaproxy.so
%{_libdir}/openMarinkaRodeo/modules/mi_datagram.so
%{_libdir}/openMarinkaRodeo/modules/mi_fifo.so
%{_libdir}/openMarinkaRodeo/modules/mi_script.so
%{_libdir}/openMarinkaRodeo/modules/mid_registrar.so
%{_libdir}/openMarinkaRodeo/modules/mqueue.so
%{_libdir}/openMarinkaRodeo/modules/msilo.so
%{_libdir}/openMarinkaRodeo/modules/nat_traversal.so
%{_libdir}/openMarinkaRodeo/modules/nathelper.so
%{_libdir}/openMarinkaRodeo/modules/options.so
%{_libdir}/openMarinkaRodeo/modules/path.so
%{_libdir}/openMarinkaRodeo/modules/permissions.so
%{_libdir}/openMarinkaRodeo/modules/pike.so
%{_libdir}/openMarinkaRodeo/modules/proto_bin.so
%{_libdir}/openMarinkaRodeo/modules/proto_bins.so
%{_libdir}/openMarinkaRodeo/modules/proto_hep.so
%{_libdir}/openMarinkaRodeo/modules/proto_ipsec.so
%{_libdir}/openMarinkaRodeo/modules/proto_smpp.so
%{_libdir}/openMarinkaRodeo/modules/proto_ws.so
%{_libdir}/openMarinkaRodeo/modules/qos.so
%{_libdir}/openMarinkaRodeo/modules/qrouting.so
%{_libdir}/openMarinkaRodeo/modules/rate_cacher.so
%{_libdir}/openMarinkaRodeo/modules/ratelimit.so
%{_libdir}/openMarinkaRodeo/modules/registrar.so
%{_libdir}/openMarinkaRodeo/modules/rr.so
%{_libdir}/openMarinkaRodeo/modules/rtp_relay.so
%{_libdir}/openMarinkaRodeo/modules/rtpengine.so
%{_libdir}/openMarinkaRodeo/modules/rtpproxy.so
%{_libdir}/openMarinkaRodeo/modules/script_helper.so
%{_libdir}/openMarinkaRodeo/modules/signaling.so
%{_libdir}/openMarinkaRodeo/modules/sip_i.so
%{_libdir}/openMarinkaRodeo/modules/sipcapture.so
%{_libdir}/openMarinkaRodeo/modules/sipmsgops.so
%{_libdir}/openMarinkaRodeo/modules/status_report.so
%{_libdir}/openMarinkaRodeo/modules/tracer.so
%{_libdir}/openMarinkaRodeo/modules/sl.so
%{_libdir}/openMarinkaRodeo/modules/sockets_mgm.so
%{_libdir}/openMarinkaRodeo/modules/speeddial.so
%{_libdir}/openMarinkaRodeo/modules/sql_cacher.so
%{_libdir}/openMarinkaRodeo/modules/sst.so
%{_libdir}/openMarinkaRodeo/modules/statistics.so
%{_libdir}/openMarinkaRodeo/modules/stun.so
%{_libdir}/openMarinkaRodeo/modules/tcp_mgm.so
%{_libdir}/openMarinkaRodeo/modules/textops.so
%{_libdir}/openMarinkaRodeo/modules/tm.so
%{_libdir}/openMarinkaRodeo/modules/topology_hiding.so
%{_libdir}/openMarinkaRodeo/modules/trie.so
%{_libdir}/openMarinkaRodeo/modules/uac.so
%{_libdir}/openMarinkaRodeo/modules/uac_redirect.so
%{_libdir}/openMarinkaRodeo/modules/uac_registrant.so
%{_libdir}/openMarinkaRodeo/modules/userblacklist.so
%{_libdir}/openMarinkaRodeo/modules/usrloc.so

%doc docdir/README.acc
%doc docdir/README.alias_db
%doc docdir/README.auth_aaa
%doc docdir/README.auth_db
%doc docdir/README.sqlops
%doc docdir/README.b2b_entities
%doc docdir/README.b2b_logic
%doc docdir/README.b2b_sca
%doc docdir/README.b2b_sdp_demux
%doc docdir/README.benchmark
%doc docdir/README.cachedb_local
%doc docdir/README.cachedb_sql
%doc docdir/README.call_center
%doc docdir/README.call_control
%doc docdir/README.callops
%doc docdir/README.cfgutils
%doc docdir/README.clusterer
%doc docdir/README.config
%doc docdir/README.db_flatstore
%doc docdir/README.db_text
%doc docdir/README.db_virtual
%doc docdir/README.dialog
%doc docdir/README.dispatcher
%doc docdir/README.diversion
%doc docdir/README.dns_cache
%doc docdir/README.domain
%doc docdir/README.domainpolicy
%doc docdir/README.drouting
%doc docdir/README.enum
%doc docdir/README.event_datagram
%doc docdir/README.event_flatstore
%doc docdir/README.event_routing
%doc docdir/README.event_stream
%doc docdir/README.event_virtual
%doc docdir/README.event_xmlrpc
%doc docdir/README.example
%doc docdir/README.exec
%doc docdir/README.fraud_detection
%doc docdir/README.freeswitch
%doc docdir/README.freeswitch_scripting
%doc docdir/README.gflags
%doc docdir/README.group
%doc docdir/README.imc
%doc docdir/README.janus
%doc docdir/README.jsonrpc
%doc docdir/README.load_balancer
%doc docdir/README.mangler
%doc docdir/README.maxfwd
%doc docdir/README.media_exchange
%doc docdir/README.mediaproxy
%doc docdir/README.mi_datagram
%doc docdir/README.mi_fifo
%doc docdir/README.mi_script
%doc docdir/README.mid_registrar
%doc docdir/README.mqueue
%doc docdir/README.msilo
%doc docdir/README.nat_traversal
%doc docdir/README.nathelper
%doc docdir/README.options
%doc docdir/README.path
%doc docdir/README.permissions
%doc docdir/README.pike
%doc docdir/README.proto_bin
%doc docdir/README.proto_hep
%doc docdir/README.proto_ipsec
%doc docdir/README.proto_smpp
%doc docdir/README.proto_ws
%doc docdir/README.qos
%doc docdir/README.qrouting
%doc docdir/README.rate_cacher
%doc docdir/README.ratelimit
%doc docdir/README.registrar
%doc docdir/README.rr
%doc docdir/README.rtp_relay
%doc docdir/README.rtpengine
%doc docdir/README.rtpproxy
%doc docdir/README.signaling
%doc docdir/README.sip_i
%doc docdir/README.sipcapture
%doc docdir/README.sipmsgops
%doc docdir/README.status_report
%doc docdir/README.tracer
%doc docdir/README.sl
%doc docdir/README.sockets_mgm
%doc docdir/README.speeddial
%doc docdir/README.sql_cacher
%doc docdir/README.sst
%doc docdir/README.statistics
%doc docdir/README.stun
%doc docdir/README.tcp_mgm
%doc docdir/README.textops
%doc docdir/README.tls
%doc docdir/README.tm
%doc docdir/README.topology_hiding
%doc docdir/README.trie
%doc docdir/README.uac
%doc docdir/README.uac_redirect
%doc docdir/README.uac_registrant
%doc docdir/README.userblacklist
%doc docdir/README.usrloc

%if 0%{?_with_auth_jwt:1}
%files auth-jwt-module
%{_libdir}/openMarinkaRodeo/modules/auth_jwt.so
%doc docdir/README.auth_jwt
%endif

%files auth-modules
%{_libdir}/openMarinkaRodeo/modules/auth.so
%{_libdir}/openMarinkaRodeo/modules/auth_aka.so
%{_libdir}/openMarinkaRodeo/modules/uac_auth.so
%doc docdir/README.auth
%doc docdir/README.auth_aka
%doc docdir/README.uac_auth

%files berkeley-bin
%{_sbindir}/bdb_recover

%files berkeley-module
%{_libdir}/openMarinkaRodeo/modules/db_berkeley.so
%doc docdir/README.db_berkeley

%files berkeley-dbschema
%dir %{_datadir}/openMarinkaRodeo/db_berkeley
%dir %{_datadir}/openMarinkaRodeo/db_berkeley/openMarinkaRodeo
%{_datadir}/openMarinkaRodeo/db_berkeley/openMarinkaRodeo/*

%files carrierroute-module
%{_libdir}/openMarinkaRodeo/modules/carrierroute.so
%doc docdir/README.carrierroute

%if 0%{?_with_cachedb_cassandra:1}
%files cassandra-module
%{_libdir}/openMarinkaRodeo/modules/cachedb_cassandra.so
%doc docdir/README.cachedb_cassandra
%endif

%files cgrates-module
%{_libdir}/openMarinkaRodeo/modules/cgrates.so
%doc docdir/README.cgrates

%files compression-module
%{_libdir}/openMarinkaRodeo/modules/compression.so
%doc docdir/README.compression

%if 0%{?_with_cachedb_couchbase:1}
%files couchbase-module
%{_libdir}/openMarinkaRodeo/modules/cachedb_couchbase.so
%doc docdir/README.cachedb_couchbase
%endif

%files cpl-module
%{_libdir}/openMarinkaRodeo/modules/cpl_c.so
%doc docdir/README.cpl_c

%files dbhttp-module
%{_libdir}/openMarinkaRodeo/modules/db_http.so
%doc docdir/README.db_http

%files dialplan-module
%{_libdir}/openMarinkaRodeo/modules/dialplan.so
%doc docdir/README.dialplan

%if 0%{?_with_aaa_diameter:1}
%files diameter-module
%{_libdir}/openMarinkaRodeo/modules/aaa_diameter.so
%{_libdir}/openMarinkaRodeo/modules/aka_av_diameter.so
%doc docdir/README.aaa_diameter
%doc docdir/README.aka_av_diameter
%endif

%files emergency-module
%{_libdir}/openMarinkaRodeo/modules/emergency.so
%doc docdir/README.emergency

%files geoip-module
%{_libdir}/openMarinkaRodeo/modules/mmgeoip.so
%doc docdir/README.mmgeoip

%files http-modules
%{_libdir}/openMarinkaRodeo/modules/httpd.so
%doc docdir/README.httpd
%{_libdir}/openMarinkaRodeo/modules/mi_html.so
%doc docdir/README.mi_html
%{_libdir}/openMarinkaRodeo/modules/mi_http.so
%doc docdir/README.mi_http
%{_libdir}/openMarinkaRodeo/modules/pi_http.so
%{_datadir}/openMarinkaRodeo/pi_http/*
%doc docdir/README.pi_http

%files identity-module
%{_libdir}/openMarinkaRodeo/modules/identity.so
%doc docdir/README.identity

%files ipsec-module
%{_libdir}/openMarinkaRodeo/modules/proto_ipsec.so
%doc docdir/README.proto_ipsec

%files jabber-module
%{_libdir}/openMarinkaRodeo/modules/jabber.so
%doc docdir/README.jabber

%files json-module
%{_libdir}/openMarinkaRodeo/modules/json.so
%doc docdir/README.json

%files kafka-module
%{_libdir}/openMarinkaRodeo/modules/event_kafka.so
%doc docdir/README.event_kafka

%files ldap-modules
%{_libdir}/openMarinkaRodeo/modules/h350.so
%doc docdir/README.h350
%{_libdir}/openMarinkaRodeo/modules/ldap.so
%doc docdir/README.ldap

%files lua-module
%{_libdir}/openMarinkaRodeo/modules/lua.so
%doc docdir/README.lua

%files memcached-module
%{_libdir}/openMarinkaRodeo/modules/cachedb_memcached.so
%doc docdir/README.cachedb_memcached

%if 0%{?_with_cachedb_mongodb:1}
%files mongodb-module
%{_libdir}/openMarinkaRodeo/modules/cachedb_mongodb.so
%doc docdir/README.cachedb_mongodb
%endif

%files msrp-modules
%{_libdir}/openMarinkaRodeo/modules/msrp_gateway.so
%{_libdir}/openMarinkaRodeo/modules/msrp_relay.so
%{_libdir}/openMarinkaRodeo/modules/msrp_ua.so
%{_libdir}/openMarinkaRodeo/modules/proto_msrp.so
%doc docdir/README.msrp_gateway
%doc docdir/README.msrp_relay
%doc docdir/README.msrp_ua
%doc docdir/README.proto_msrp

%files mysql-module
%{_libdir}/openMarinkaRodeo/modules/db_mysql.so
%doc docdir/README.db_mysql

%files mysql-dbschema
%dir %{_datadir}/openMarinkaRodeo/mysql
%{_datadir}/openMarinkaRodeo/mysql/*.sql

%if 0%{?_with_db_oracle:1}
%files oracle-module
%{_sbindir}/openMarinkaRodeo_orasel
%{_libdir}/openMarinkaRodeo/modules/db_oracle.so
%dir %{_datadir}/openMarinkaRodeo/oracle
%{_datadir}/openMarinkaRodeo/oracle/*
%doc docdir/README.db_oracle
%endif

%if 0%{?_with_osp:1}
%files osp-module
%{_libdir}/openMarinkaRodeo/modules/osp.so
%doc docdir/README.osp
%endif

%files perl-modules
%dir %{perl_vendorlib}/OpenMarinkaRodeo
%dir %{perl_vendorlib}/OpenMarinkaRodeo/LDAPUtils
%dir %{perl_vendorlib}/OpenMarinkaRodeo/Utils
%{_libdir}/openMarinkaRodeo/modules/perl.so
%{perl_vendorlib}/OpenMarinkaRodeo.pm
%{perl_vendorlib}/OpenMarinkaRodeo/Constants.pm
%{perl_vendorlib}/OpenMarinkaRodeo/LDAPUtils/LDAPConf.pm
%{perl_vendorlib}/OpenMarinkaRodeo/LDAPUtils/LDAPConnection.pm
%{perl_vendorlib}/OpenMarinkaRodeo/Message.pm
%{perl_vendorlib}/OpenMarinkaRodeo/Utils/PhoneNumbers.pm
%{perl_vendorlib}/OpenMarinkaRodeo/Utils/Debug.pm
%doc docdir/README.perl
%if 0%{!?_without_db_perlvdb:1}
%dir %{perl_vendorlib}/OpenMarinkaRodeo/VDB
%dir %{perl_vendorlib}/OpenMarinkaRodeo/VDB/Adapter
%{_libdir}/openMarinkaRodeo/modules/db_perlvdb.so
%{perl_vendorlib}/OpenMarinkaRodeo/VDB.pm
%{perl_vendorlib}/OpenMarinkaRodeo/VDB/Adapter/AccountingSIPtrace.pm
%{perl_vendorlib}/OpenMarinkaRodeo/VDB/Adapter/Alias.pm
%{perl_vendorlib}/OpenMarinkaRodeo/VDB/Adapter/Auth.pm
%{perl_vendorlib}/OpenMarinkaRodeo/VDB/Adapter/Describe.pm
%{perl_vendorlib}/OpenMarinkaRodeo/VDB/Adapter/Speeddial.pm
%{perl_vendorlib}/OpenMarinkaRodeo/VDB/Adapter/TableVersions.pm
%{perl_vendorlib}/OpenMarinkaRodeo/VDB/Column.pm
%{perl_vendorlib}/OpenMarinkaRodeo/VDB/Pair.pm
%{perl_vendorlib}/OpenMarinkaRodeo/VDB/ReqCond.pm
%{perl_vendorlib}/OpenMarinkaRodeo/VDB/Result.pm
%{perl_vendorlib}/OpenMarinkaRodeo/VDB/VTab.pm
%{perl_vendorlib}/OpenMarinkaRodeo/VDB/Value.pm
%doc docdir/README.db_perlvdb
%endif

%files postgres-module
%{_libdir}/openMarinkaRodeo/modules/db_postgres.so
%doc docdir/README.db_postgres

%files postgres-dbschema
%dir %{_datadir}/openMarinkaRodeo/postgres
%{_datadir}/openMarinkaRodeo/postgres/*.sql

%files presence-modules
%{_libdir}/openMarinkaRodeo/modules/presence.so
%doc docdir/README.presence
%{_libdir}/openMarinkaRodeo/modules/presence_callinfo.so
%doc docdir/README.presence_callinfo
%{_libdir}/openMarinkaRodeo/modules/presence_dialoginfo.so
%doc docdir/README.presence_dialoginfo
%{_libdir}/openMarinkaRodeo/modules/presence_dfks.so
%doc docdir/README.presence_dfks
%{_libdir}/openMarinkaRodeo/modules/presence_reginfo.so
%doc docdir/README.presence_reginfo
%{_libdir}/openMarinkaRodeo/modules/presence_mwi.so
%doc docdir/README.presence_mwi
%{_libdir}/openMarinkaRodeo/modules/presence_xcapdiff.so
%doc docdir/README.presence_xcapdiff
%{_libdir}/openMarinkaRodeo/modules/presence_xml.so
%doc docdir/README.presence_xml
%{_libdir}/openMarinkaRodeo/modules/pua.so
%doc docdir/README.pua
%{_libdir}/openMarinkaRodeo/modules/pua_bla.so
%doc docdir/README.pua_bla
%{_libdir}/openMarinkaRodeo/modules/pua_dialoginfo.so
%doc docdir/README.pua_dialoginfo
%{_libdir}/openMarinkaRodeo/modules/pua_mi.so
%doc docdir/README.pua_mi
%{_libdir}/openMarinkaRodeo/modules/pua_reginfo.so
%doc docdir/README.pua_reginfo
%{_libdir}/openMarinkaRodeo/modules/pua_usrloc.so
%doc docdir/README.pua_usrloc
%{_libdir}/openMarinkaRodeo/modules/pua_xmpp.so
%doc docdir/README.pua_xmpp
%{_libdir}/openMarinkaRodeo/modules/rls.so
%doc docdir/README.rls
%{_libdir}/openMarinkaRodeo/modules/xcap.so
%doc docdir/README.xcap
%{_libdir}/openMarinkaRodeo/modules/xcap_client.so
%doc docdir/README.xcap_client

%files prometheus-module
%{_libdir}/openMarinkaRodeo/modules/prometheus.so
%doc docdir/README.prometheus

%files python-module
%{_libdir}/openMarinkaRodeo/modules/python.so
%doc docdir/README.python

%files rabbitmq-modules
%{_libdir}/openMarinkaRodeo/modules/event_rabbitmq.so
%doc docdir/README.event_rabbitmq
%{_libdir}/openMarinkaRodeo/modules/rabbitmq_consumer.so
%doc docdir/README.rabbitmq_consumer

%files radius-modules
%{_libdir}/openMarinkaRodeo/modules/peering.so
%doc docdir/README.peering
%{_libdir}/openMarinkaRodeo/modules/aaa_radius.so
%doc docdir/README.aaa_radius

%if 0%{?_with_cachedb_redis:1}
%files redis-module
%{_libdir}/openMarinkaRodeo/modules/cachedb_redis.so
%doc docdir/README.cachedb_redis
%endif

%files regex-module
%{_libdir}/openMarinkaRodeo/modules/regex.so
%doc docdir/README.regex

%files restclient-module
%{_libdir}/openMarinkaRodeo/modules/rest_client.so
%doc docdir/README.rest_client

%files sctp-module
%{_libdir}/openMarinkaRodeo/modules/proto_sctp.so
%doc docdir/README.proto_sctp

%files siprec-module
%{_libdir}/openMarinkaRodeo/modules/siprec.so
%doc docdir/README.siprec

%if 0%{?_with_sngtc:1}
%files sngtc-module
%{_libdir}/openMarinkaRodeo/modules/sngtc.so
%doc docdir/README.sngtc
%endif

%if 0%{!?_without_snmpstats:1}
%files snmpstats-module
%{_libdir}/openMarinkaRodeo/modules/snmpstats.so
%doc docdir/README.snmpstats
%dir %{_datadir}/snmp
%dir %{_datadir}/snmp/mibs
%{_datadir}/snmp/mibs/OPENSER-MIB
%{_datadir}/snmp/mibs/OPENSER-REG-MIB
%{_datadir}/snmp/mibs/OPENSER-SIP-COMMON-MIB
%{_datadir}/snmp/mibs/OPENSER-SIP-SERVER-MIB
%{_datadir}/snmp/mibs/OPENSER-TC
%endif

%files sqlite-module
%{_libdir}/openMarinkaRodeo/modules/db_sqlite.so
%doc docdir/README.db_sqlite

%files sqlite-dbschema
%dir %{_datadir}/openMarinkaRodeo/sqlite
%{_datadir}/openMarinkaRodeo/sqlite/*.sql

%files stir-shaken-module
%{_libdir}/openMarinkaRodeo/modules/stir_shaken.so
%doc docdir/README.stir_shaken

%files  tls-openssl-module
%{_libdir}/openMarinkaRodeo/modules/tls_openssl.so
%doc docdir/README.tls_openssl

%if 0%{?_with_wolfssl:1}
%files  tls-wolfssl-module
%{_libdir}/openMarinkaRodeo/modules/tls_wolfssl.so
%doc docdir/README.tls_wolfssl
%endif

%files tls-module
%{_libdir}/openMarinkaRodeo/modules/proto_tls.so
%doc docdir/README.proto_tls

%files tlsmgm-module
%{_libdir}/openMarinkaRodeo/modules/tls_mgm.so
%doc docdir/README.tls_mgm

%files unixodbc-module
%{_libdir}/openMarinkaRodeo/modules/db_unixodbc.so
%doc docdir/README.db_unixodbc

%files uuid-module
%{_libdir}/openMarinkaRodeo/modules/uuid.so
%doc docdir/README.uuid

%files wss-module
%{_libdir}/openMarinkaRodeo/modules/proto_wss.so
%doc docdir/README.proto_wss

%files xml-module
%{_libdir}/openMarinkaRodeo/modules/xml.so
%doc docdir/README.xml

%files xmlrpc-module
%{_libdir}/openMarinkaRodeo/modules/mi_xmlrpc_ng.so
%doc docdir/README.mi_xmlrpc_ng

%files xmpp-module
%{_libdir}/openMarinkaRodeo/modules/xmpp.so
%doc docdir/README.xmpp


%changelog
* Wed May 14 2025 Razvan Crainea <razvan@openMarinkaRodeo.org> - 3.6.0-1
- New module: config

* Tue May 13 2025 Razvan Crainea <razvan@openMarinkaRodeo.org> - 3.6.0-1
- New module: sockets_mgm

* Tue Mar 11 2025 Razvan Crainea <razvan@openMarinkaRodeo.org> - 3.6.0-1
- New module: janus

* Thu Jan 16 2025 Razvan Crainea <razvan@openMarinkaRodeo.org> - 3.6.0-1
- New module: trie

* Mon Aug 19 2024 Razvan Crainea <razvan@openMarinkaRodeo.org> - 3.6.0-1
- Replace deprecated dependency for radius modules

* Sat May 18 2024 Nick Altmann <nick@altmann.pro> - 3.5.0-1
- Specification updated for openMarinkaRodeo 3.5
- New modules: aka_av_diameter, auth_aka, mqueue, presence_reginfo, proto_ipsec, pua_reginfo

* Thu May 18 2023 Nick Altmann <nick@altmann.pro> - 3.4.0-1
- Specification updated for openMarinkaRodeo 3.4

* Wed May 18 2022 Nick Altmann <nick@altmann.pro> - 3.3.0-1
- Specification updated for openMarinkaRodeo 3.3
- New modules: b2b_sdp_demux, msrp_gateway, msrp_relay, msrp_ua, proto_msrp, status_report, tcp_mgm
- New packages: msrp-modules
- Removed modules: b2b_logic_xml
- Removed packages: b2bua-module

* Thu May 27 2021 Nick Altmann <nick@altmann.pro> - 3.2.0-1
- Specification updated for openMarinkaRodeo 3.2
- New modules: aaa_diameter, b2b_logic, event_kafka, prometeus, rtp_relay, tls_openssl, tls_wolfssl
- New packages: aaa-diameter-module, kafka-module, prometeus-module, tls-openssl-module, tls-wolfssl-module
- Obsoleted modules: b2b_logic_xml

* Fri Feb 26 2021 Razvan Crainea <razvan@openMarinkaRodeo.org> - 3.2.0-1
- New modules: prometheus

* Tue Feb 11 2020 Nick Altmann <nick.altmann@gmail.com> - 3.1.0-1
- Specification updated for openMarinkaRodeo 3.1
- New modules: b2b_logic_xml, callops, media_exchange, presence_dfks,
  qrouting, rabbitmq_consumer, rate_cacher, stir_shaken, uuid
- New package: stir-shaken-module
- Obsoleted modules: seas, sms
- Renamed: event_jsonrpc -> event_stream
- Removed: openMarinkaRodeounix, oMarinkaRodeoconsole, openMarinkaRodeoctl, openMarinkaRodeodbctl

* Thu Apr 11 2019 Nick Altmann <nick.altmann@gmail.com> - 3.0.0-1
- Specification updated for openMarinkaRodeo 3.0
- Package names and layout were changed similar to debian packaging

* Wed Mar 28 2018 Nick Altmann <nick.altmann@gmail.com> - 2.4.0-1
- Specification updated for openMarinkaRodeo 2.4
- New packages: event_jsonrpc, jsonrpc, siprec

* Mon Mar 06 2017 Nick Altmann <nick.altmann@gmail.com> - 2.3.0-1
- Specification updated for openMarinkaRodeo 2.3
- New packages: event_routing, freeswitch, mid_registrar, sip_i, xml
- Enabled packages: cachedb_mongodb, lua
- Renamed packages: memcached -> cachedb_memcached, redis -> cachedb_redis,
  unixodbc -> db_unixodbc, xmlrpc -> mi_xmlrpc
- Added possibility to build unsupported modules (from obsolete .spec):
  cachedb_cassandra, cachedb_couchbase,
  cachedb_mongodb, osp, sngtc

* Wed Jan 20 2016 Nick Altmann <nick.altmann@gmail.com> - 2.2.0-1
- Specification updated for openMarinkaRodeo 2.2
- New packages: db_sqlite, clusterer, event_flatstore,
  event_virtual, proto_bin, proto_hep, proto_wss, sql_cacher
- Renamed packages: mysql -> db_mysql, postgres -> db_postgres,
  cpl-c -> cpl_c

* Sat Mar 14 2015 Nick Altmann <nick.altmann@gmail.com> - 2.1.0-1
- Specification updated for openMarinkaRodeo 2.1
- Removed packages: auth_diameter, tlsops
- New packages: compression, emergency, fraud_detection,
  proto_sctp, proto_tls, proto_ws, rtpengine, topology_hiding

* Fri Mar 21 2014 Nick Altmann <nick.altmann@gmail.com> - 1.11.0-1
- Update to 1.11.0

* Tue Jul 30 2013 Nick Altmann <nick.altmann@gmail.com> - 1.10.0-1
- Update to 1.10.0

* Wed May 22 2013 Nick Altmann <nick.altmann@gmail.com> - 1.9.1-1
- Rebuild specification, add new modules and dependencies

* Tue Jan 22 2013 Peter Lemenkov <lemenkov@gmail.com> - 1.8.2-3
- Revert systemd macros

* Thu Jan 10 2013 Peter Lemenkov <lemenkov@gmail.com> - 1.8.2-2
- Allow rtpproxy module to accept avps
- Few bugfixes

* Tue Nov 06 2012 Peter Lemenkov <lemenkov@gmail.com> - 1.8.2-1
- Ver. 1.8.2 (Bugfix release)

* Sat Sep 22 2012  Remi Collet <remi@fedoraproject.org> - 1.8.1-3
- rebuild against libmemcached.so.11 without SASL

* Fri Aug 17 2012 Peter Lemenkov <lemenkov@gmail.com> - 1.8.1-2
- Enabled json module
- Enabled xmlrpc module
- Enabled cachedb_memcached module on EL5, EL6
- Enabled cachedb_redis module on EL6

* Wed Aug 15 2012 Peter Lemenkov <lemenkov@gmail.com> - 1.8.1-1
- Ver. 1.8.1
- Dropped all upstreamed patches

* Fri Jul 20 2012 Fedora Release Engineering <rel-eng@lists.fedoraproject.org> - 1.8.0-3
- Rebuilt for https://fedoraproject.org/wiki/Fedora_18_Mass_Rebuild

* Mon Jul 09 2012 Petr Pisar <ppisar@redhat.com> - 1.8.0-2
- Perl 5.16 rebuild

* Tue Jul 03 2012 Peter Lemenkov <lemenkov@gmail.com> - 1.8.0-1
- update to 1.8.0

* Fri Jun 08 2012 Petr Pisar <ppisar@redhat.com> - 1.7.2-8
- Perl 5.16 rebuild

* Sat May 12 2012 Peter Lemenkov <lemenkov@gmail.com> - 1.7.2-7
- Change %%define to %%global

* Sat May 12 2012 Peter Lemenkov <lemenkov@gmail.com> - 1.7.2-6
- Added missing docs

* Fri May 11 2012 Peter Lemenkov <lemenkov@gmail.com> - 1.7.2-5
- Fixed conditional building with Oracle DB

* Sat Apr 28 2012 Peter Lemenkov <lemenkov@gmail.com> - 1.7.2-4
- Fixes for systemd unit

* Sun Apr 22 2012  Remi Collet <remi@fedoraproject.org> - 1.7.2-3
- rebuild against libmemcached.so.10

* Thu Apr 19 2012 Peter Lemenkov <lemenkov@gmail.com> - 1.7.2-2
- Fix building on EPEL

* Thu Apr 19 2012 Peter Lemenkov <lemenkov@gmail.com> - 1.7.2-1
- update to 1.7.2 (bugfix release).
- enable systemd support where possible

* Fri Apr 13 2012 Jindrich Novy <jnovy@redhat.com> - 1.7.1-6
- rebuild against new librpm and libdb

* Sat Mar 03 2012  Remi Collet <remi@fedoraproject.org> - 1.7.1-5
- rebuild against libmemcached.so.9

* Fri Feb 10 2012 Petr Pisar <ppisar@redhat.com> - 1.7.1-4
- Rebuild against PCRE 8.30

* Fri Jan 13 2012 Fedora Release Engineering <rel-eng@lists.fedoraproject.org> - 1.7.1-3
- Rebuilt for https://fedoraproject.org/wiki/Fedora_17_Mass_Rebuild

* Thu Dec 01 2011 John Khvatov <ivaxer@fedoraproject.org> - 1.7.1-2
- upstream tarball rebuild

* Thu Nov 24 2011 John Khvatov <ivaxer@fedoraproject.org> - 1.7.1-1
- update to 1.7.1 (bugfix release).

* Mon Nov 07 2011 John Khvatov <ivaxer@fedoraproject.org> - 1.7.0-1
- update to 1.7.0
- dropped upstreamed patches
- added new modules: event_datagram and python
- removed lcr module

* Sat Sep 17 2011  Remi Collet <remi@fedoraproject.org> - 1.6.4-13
- rebuild against libmemcached.so.8

* Mon Aug 22 2011 John Khvatov <ivaxer@fedoraproject.org> - 1.6.4-12
- rebuild against new libnetsnmp

* Thu Jul 21 2011 Petr Sabata <contyk@redhat.com> - 1.6.4-11
- Perl mass rebuild

* Wed Jul 20 2011 Petr Sabata <contyk@redhat.com> - 1.6.4-10
- Perl mass rebuild

* Mon Jul 11 2011 Peter Lemenkov <lemenkov@gmail.com> - 1.6.4-9
- Updated init-script

* Mon Jul 11 2011 Peter Lemenkov <lemenkov@gmail.com> - 1.6.4-8
- Upstream re-released traball with several new patches (API compatible)

* Fri Jun 17 2011 Marcela Mašláňová <mmaslano@redhat.com> - 1.6.4-7
- Perl mass rebuild

* Wed Mar 23 2011 Dan Horák <dan@danny.cz> - 1.6.4-6
- rebuilt for mysql 5.5.10 (soname bump in libmysqlclient)

* Tue Feb 08 2011 Fedora Release Engineering <rel-eng@lists.fedoraproject.org> - 1.6.4-5
- Rebuilt for https://fedoraproject.org/wiki/Fedora_15_Mass_Rebuild

* Wed Dec 22 2010 John Khvatov <ivaxer@fedoraproject.org> - 1.6.4-1
- dropped upstreamed patch (openMarinkaRodeo-build.patch)
- update to 1.6.4
- added new module: presence_callinfo

* Sat Oct 30 2010 John Khvatov <ivaxer@fedoraproject.org> - 1.6.3-4
- rebuild against new libnetsnmp

* Wed Oct 06 2010 Remi Collet <fedora@famillecollet.com> - 1.6.3-3
- rebuilt against new libmemcached

* Wed Sep 08 2010 Dan Horák <dan[at]danny.cz> - 1.6.3-2
- fix a build issue

* Thu Aug 12 2010 John Khvatov <ivaxer@gmail.com> - 1.6.3-1
- update to 1.6.3

* Wed Aug 11 2010 David Malcolm <dmalcolm@redhat.com> - 1.6.2-5
- recompiling .py files against Python 2.7 (rhbz#623343)

* Tue Jun 01 2010 Marcela Maslanova <mmaslano@redhat.com> - 1.6.2-4
- Mass rebuild with perl-5.12.0

* Wed May 05 2010 Remi Collet <fedora@famillecollet.com> - 1.6.2-3
- rebuilt against new libmemcached

* Thu Apr 15 2010 John Khvatov <ivaxer@fedoraproject.org> - 1.6.2-2
- Disabled build of the memcached subpackage for EPEL

* Thu Apr 15 2010 John Khvatov <ivaxer@fedoraproject.org> - 1.6.2-1
- Updated to 1.6.2

* Sun Feb 07 2010 Remi Collet <fedora@famillecollet.com> - 1.6.1-2
- rebuilt against new libmemcached

* Tue Dec 22 2009 John Khvatov <ivaxer@fedoraproject.org> - 1.6.1-1
- Updated to 1.6.1
- Dropped upstreamed patches

* Wed Nov 04 2009 John Khvatov <ivaxer@fedoraproject.org> - 1.6.0-4
- Fixed typo: pia_mi to pua_mi in presence_xcapdiff dependencies

* Tue Nov 03 2009 John Khvatov <ivaxer@fedoraproject.org> - 1.6.0-3
- Added patch for compatibility with new openssl

* Thu Oct 29 2009 John Khvatov <ivaxer@fedoraproject.org> - 1.6.0-2
- Added patch for init script to fix malformed comment block
- Added COPYING file
- Fixed not-capitalized summory of memcached subpackage

* Mon Oct 19 2009 John Khvatov <ivaxer@fedoraproject.org> - 1.6.0-1
- Created new package from openser package
- Upgrade to OpenMarinkaRodeo 1.6
- New modules
- Added osipconsole tool

* Tue Aug 25 2009 Tomas Mraz <tmraz@redhat.com> - 1.3.4-8
- rebuilt with new openssl

* Sat Jul 25 2009 Fedora Release Engineering <rel-eng@lists.fedoraproject.org> - 1.3.4-7
- Rebuilt for https://fedoraproject.org/wiki/Fedora_12_Mass_Rebuild

* Mon Mar 02 2009 Jan ONDREJ (SAL) <ondrejj(at)salstar.sk> - 1.3.4-6
- allow build of this package on fedora<=10

* Sat Feb 28 2009 Jan ONDREJ (SAL) <ondrejj(at)salstar.sk> - 1.3.4-5
- fix module path

* Sat Feb 28 2009 Jan ONDREJ (SAL) <ondrejj(at)salstar.sk> - 1.3.4-3
- addedd subversion build dependency to avoid svnversion error messages
- fixed installation of perl modules in rawhide

* Fri Jan 23 2009 Jan ONDREJ (SAL) <ondrejj(at)salstar.sk> 1.3.4-2
- Rebuild for new mysql.

* Mon Dec  8 2008 Peter Lemenkov <lemenkov@gmail.com> 1.3.4-1
- Ver. 1.3.4
- Added sysconfig-file

* Thu Aug 28 2008 Michael Schwendt <mschwendt@fedoraproject.org> - 1.3.3-3
- Include lots of unowned directories.

* Thu Aug 28 2008 Peter Lemenkov <lemenkov@gmail.com> 1.3.3-2
- Removed dialplan and drouting modules from upstream

* Thu Aug 28 2008 Peter Lemenkov <lemenkov@gmail.com> 1.3.3-1
- Ver. 1.3.3
- Dropped upstreamed patch

* Mon Aug 11 2008 Peter Lemenkov <lemenkov@gmail.com> 1.3.2-5
- Typo fix

* Mon Aug 11 2008 Peter Lemenkov <lemenkov@gmail.com> 1.3.2-4
- Fix build with --fuzz=0

* Mon Aug 11 2008 Peter Lemenkov <lemenkov@gmail.com> 1.3.2-3
- Fixed urls
- Restricted access to openser.cfg and openserctl.cfg
- Service won't start by default (BZ# 441297)

* Fri May 16 2008 Peter Lemenkov <lemenkov@gmail.com> 1.3.2-2
- New modules - dialplan and drouting (this one still has no README)

* Thu May 15 2008 Peter Lemenkov <lemenkov@gmail.com> 1.3.2-1
- Ver. 1.3.2

* Tue Mar 18 2008 Tom "spot" Callaway <tcallawa@redhat.com> - 1.3.1-3
- add Requires for versioned perl (libperl.so)
- drop silly file Requires

* Fri Mar 14 2008 Jan ONDREJ (SAL) <ondrejj(at)salstar.sk> - 1.3.1-2
- removed perl patch, which is not necessary

* Thu Mar 13 2008 Jan ONDREJ (SAL) <ondrejj(at)salstar.sk> - 1.3.1-1
- update to upstream
- removed obsolete patches

* Fri Mar  7 2008 Tom "spot" Callaway <tcallawa@redhat.com> - 1.3.0-12
- patch perl code to use PERL_SYS_INIT3_BODY

* Fri Mar  7 2008 Tom "spot" Callaway <tcallawa@redhat.com> - 1.3.0-11
- fix perl build requires

* Thu Mar 06 2008 Tom "spot" Callaway <tcallawa@redhat.com> - 1.3.0-10
- Rebuild for new perl

* Sat Feb 23 2008 Jan ONDREJ (SAL) <ondrejj(at)salstar.sk> 1.3.0-9
- ia64 build fix

* Sat Feb  9 2008 Peter Lemenkov <lemenkov@gmail.com> 1.3.0-8.1
- typo fix

* Sat Feb  9 2008 Peter Lemenkov <lemenkov@gmail.com> 1.3.0-8
- Rebuild for GCC 4.3

* Sat Jan 26 2008 Jan ONDREJ (SAL) <ondrejj(at)salstar.sk> 1.3.0-7
- Updated syntax error in default config

* Sat Jan 26 2008 Peter Lemenkov <lemenkov@gmail.com> 1.3.0-5
- Merge of acc module into main package

* Fri Jan 25 2008 Jan ONDREJ (SAL) <ondrejj(at)salstar.sk> 1.3.0-4
- modify and apply forgotten patch4

* Thu Jan 17 2008 Jan ONDREJ (SAL) <ondrejj(at)salstar.sk> 1.3.0-2
- removed openser.init and replaced by upstream version
- fixed configuration path for openserdbctl (#428799)

* Sun Jan 13 2008 Peter Lemenkov <lemenkov@gmail.com> 1.3.0-1.4
- 4th try to remove lm_sensors-devel from EL-[45] at ppc{64}

* Thu Dec 13 2007 Peter Lemenkov <lemenkov@gmail.com> 1.3.0-1
- Final ver. 1.3.0
- Removed some leftovers from spec-file

* Wed Dec 12 2007 Peter Lemenkov <lemenkov@gmail.com> 1.3.0-0.1.pre1
- Latest snapshot - 1.3.0pre1

* Mon Dec 10 2007 Jan ONDREJ (SAL) <ondrejj(at)salstar.sk> 1.2.2-11
- added ETCDIR into openserctlrc (need openser-1.3 to work)

* Mon Sep 24 2007 Jan ONDREJ (SAL) <ondrejj(at)salstar.sk> 1.2.2-10
- perl scripts moved to perl_vendorlib directory
- added LDAPUtils and Utils subdirectories
- changed perl module BuildRequires

* Mon Sep 24 2007 Jan ONDREJ (SAL) <ondrejj(at)salstar.sk> 1.2.2-9
- added reload section to init script
- init script specified with initrddir macro
- documentation converted to UTF-8
- added doc macro for documentation
- documentation moved do proper place (/usr/share/doc/NAME-VERSION/)
- which removed from BuildRequires, it's in guidelines exceptions
- unixodbc subpackage summary update

* Thu Sep  6 2007 Peter Lemenkov <lemenkov@gmail.com> 1.2.2-8
- Added another one missing BR - which (needs by snmpstats module)
- Cosmetic: dropped commented out 'Requires'

* Thu Sep 06 2007 Jan ONDREJ (SAL) <ondrejj(at)salstar.sk> 1.2.2-7
- added attr macro for init script
- added -p to install arguments to preserve timestamp
- parallel make used

* Sun Aug 26 2007 Jan ONDREJ (SAL) <ondrejj(at)salstar.sk> 1.2.2-6
- Fedora Core 6 build updates
- changed attributes for openser.init to be rpmlint more silent

* Sun Aug 26 2007 Peter Lemenkov <lemenkov@gmail.com> 1.2.2-5
- fixed paths for openssl libs and includes

* Sun Aug 26 2007 Peter Lemenkov <lemenkov@gmail.com> 1.2.2-4
- Introduced acc and acc_radius modules (Jan Ondrej)
- Dropped radius_accounting condition

* Sat Aug 25 2007 Peter Lemenkov <lemenkov@gmail.com> 1.2.2-3
- Changed license according to Fedora's policy
- Make rpmlint more silent

* Fri Aug 24 2007 Jan ONDREJ (SAL) <ondrejj(at)salstar.sk> 1.2.2-2
- added openser.init script
- removed Patch0: openser--Makefile.diff and updated build section
- spec file is 80 characters wide
- added radius_accounting condition

* Wed Aug 22 2007 Peter Lemenkov <lemenkov@gmail.com> 1.2.2-1
- Ver. 1.2.2

* Tue Jul 24 2007 Peter Lemenkov <lemenkov@gmail.com> 1.2.1-1
- Initial spec.

