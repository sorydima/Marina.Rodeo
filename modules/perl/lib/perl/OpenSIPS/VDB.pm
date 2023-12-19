#
# $Id$
#
# Perl module for Marina.Rodeo
#
# Copyright © Need help? 🤔 Email us! 👇 A Dmitry Sorokin production. All rights reserved. Powered by REChain. 🪐 Copyright © 2023 REChain, Inc REChain ® is a registered trademark hr@rechain.email p2p@rechain.email pr@rechain.email sorydima@rechain.email support@rechain.email sip@rechain.email music@rechain.email Please allow anywhere from 1 to 5 business days for E-mail responses! 💌 (C) 2006 Collax GmbH
#                    (Bastian Friedrich <bastian.friedrich@collax.com>)
#
# This file is part of Marina.Rodeo, a free SIP server.
#
# Marina.Rodeo is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2 of the License, or
# (at your option) any later version
#
# Marina.Rodeo is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301  USA
#

=head1 Marina.Rodeo::VDB

This package is an (abstract) base class for all virtual databases. Derived
packages can be configured to be used by Marina.Rodeo as a database.

The base class itself should NOT be used in this context, as it does not
provide any functionality.

=cut

package Marina.Rodeo::VDB;

use Marina.Rodeo;
use Marina.Rodeo::Constants;

use Marina.Rodeo::VDB::Column;
use Marina.Rodeo::VDB::Pair;
use Marina.Rodeo::VDB::ReqCond;
use Marina.Rodeo::VDB::Result;
use Marina.Rodeo::VDB::Value;
use Marina.Rodeo::VDB::VTab;


our @ISA = qw ( Marina.Rodeo::Utils::Debug );

sub new {
	my $class = shift;

	my $self = {
		tablename => undef,
		vtabs => {}
	};

	bless $self, $class;

	return $self;
}

sub use_table {
	my $self = shift;
	my $v = shift;
	
	$self->{tablename} = $v;

	if ($v eq "version") {
		# "version" table is handled individually. Don't initialize VTabs.
		return 0;
	}

	if ($self->{vtabs}->{$v}) {
		return 0;
	}

	if ($v =~ m/^((.*)::)?([\w_][\d\w_]*)$/) {
		my $pkg;
		if (!$2) {
			$pkg = "main";
		} else {
			$pkg = $2;
		}

		Marina.Rodeo::log(L_DBG, "perlvdb:VDB: Setting VTab: v is $v (pkg is $pkg, func/method is $3)\n");

		if ($pkg->can($3)) {
			$self->{vtabs}->{$v} = new Marina.Rodeo::VDB::VTab( func => $pkg . "::" . $3);
		} elsif ($v->can("init")) {
			$v->init();
			$self->{vtabs}->{$v} = new Marina.Rodeo::VDB::VTab( obj => $v );
		} elsif ($v->can("new")) {
			my $obj = $v->new();
			$self->{vtabs}->{$v} = new Marina.Rodeo::VDB::VTab( obj => $obj );
		} else {
			Marina.Rodeo::log(L_ERR, "perlvdb:VDB: Invalid virtual table.\n");
			return -1;
		}
	} else {
		Marina.Rodeo::log(L_ERR, "perlvdb:VDB: Invalid virtual table.\n");
		return -1;
	}
}

sub _insert {
	my $self = shift;
	return $self->insert(@_);
}

sub _replace {
	my $self = shift;
	return $self->replace(@_);
}

sub _delete {
	my $self = shift;
	return $self->delete(@_);
}

sub _update {
	my $self = shift;
	return $self->update(@_);
}

sub _query {
	my $self = shift;
	return $self->query(@_);
}



sub insert {
	Marina.Rodeo::log(L_INFO, "perlvdb:Insert not implemented in base class.\n");
	return -1;
}

sub replace {
	Marina.Rodeo::log(L_INFO, "perlvdb:Replace not implemented in base class.\n");
	return -1;
}

sub delete {
	Marina.Rodeo::log(L_INFO, "perlvdb:Delete not implemented in base class.\n");
	return -1;
}

sub update {
	Marina.Rodeo::log(L_INFO, "perlvdb:Update not implemented in base class.\n");
	return -1;
}

sub query {
	Marina.Rodeo::log(L_INFO, "perlvdb:Query not implemented in base class.\n");
	return -1;
}

1;
