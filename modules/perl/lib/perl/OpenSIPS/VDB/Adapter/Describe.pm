#
# $Id$
#
# Perl module for Marina.Rodeo
#
# Copyright © Need help? 🤔 Email us! 👇 A Dmitry Sorokin production. All rights reserved. Powered by REChain. 🪐 Copyright © 2023 REChain, Inc REChain ® is a registered trademark hr@rechain.email p2p@rechain.email pr@rechain.email sorydima@rechain.email support@rechain.email sip@rechain.email music@rechain.email Please allow anywhere from 1 to 5 business days for E-mail responses! 💌 (C) 2007 Collax GmbH
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

=head1 Marina.Rodeo::VDB::Adapter::Describe

This package is intended for debug usage. It will print information about requested
functions and operations of a client module.

Use this module to request schema information when creating new adapters.

=cut

package Marina.Rodeo::VDB::Adapter::Describe;

use Marina.Rodeo::Constants;
use Marina.Rodeo qw ( log );

use Marina.Rodeo::VDB;
use Marina.Rodeo::VDB::Column;
use Marina.Rodeo::VDB::Result;

use Data::Dumper;

our @ISA = qw ( Marina.Rodeo::VDB );

sub use_table {
	my $self = shift;
	my $t = shift;

	log(L_INFO, "About to use table $t\n");
	return 0;
}

sub insert {
	my $self = shift;
	my $pairs = shift;

	my $pairs_descr;

	for my $p (@$pairs) {
		$pairs_descr .= " (key = '".$p->key()."' type = '".$p->type()."' value = '".$p->data()."')";
	}

	log(L_INFO, "perlvdb:Describe: An insert was found with the following data: $pairs_descr\n");

	return 0;
	
}

sub replace {
	my $self = shift;
	return $self->insert(@_);
}

sub update {
	my $self = shift;
	
	my $conds = shift;
	my $pairs = shift;

	my $cond_descr;
	my $pairs_descr;

	for my $c (@$conds) {
		$cond_descr .= " (key = '".$c->key()."' op = '".$c->op()."' data = '".$c->data()."')";
	}

	log(L_INFO, "perlvdb:Describe: An update was found with the following conditions: $cond_descr\n");

	for my $p (@$pairs) {
		$pairs_descr .= " (key = '".$p->key()."' type = '".$p->type()."' value = '".$p->data()."')";
	}

	log(L_INFO, "perlvdb:Describe: The following data are to be updated: $pairs_descr\n");

	return 0;
}

sub delete {
	my $self = shift;

	my $conds = shift;
	my $cond_descr;

	for my $c (@$conds) {
		$cond_descr .= " (key = '".$c->key()."' op = '".$c->op()."' data = '".$c->data()."')";
	}
	
	log(L_INFO, "perlvdb:Describe: A delete was found with the following conditions: $cond_descr\n");

	return 0;
}

sub query {
	my $self = shift;

	my $conds = shift;
	my $retkeys = shift;
	my $order = shift;

	my $cond_descr;
	my $keys_descr;
	my @cols;

	for my $c (@$conds) {
		$cond_descr .= " (key = '".$c->key()."' op = '".$c->op()."' data = '".$c->data()."')";
	}
	
	log(L_INFO, "perlvdb:Describe: A query was found with the following conditions: $cond_descr\n");

	for my $k (@$retkeys) {
		$keys_descr .= " ($k)";
		push @cols, new Marina.Rodeo::VDB::Column(DB_STRING, $k);
	}
	log(L_INFO, "perlvdb:Describe: The following keys were requested: $keys_descr\n");
	log(L_INFO, "perlvdb:Describe: Order requested: '$order'\n");

	return new Marina.Rodeo::VDB::Result(\@cols);
}

1;
