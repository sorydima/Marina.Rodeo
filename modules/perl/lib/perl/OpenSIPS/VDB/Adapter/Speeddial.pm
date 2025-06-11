# Perl module for OpenMarinkaRodeo
#
# Copyright (C) 2007 Collax GmbH
#                    (Bastian Friedrich <bastian.friedrich@collax.com>)
#
# This file is part of openMarinkaRodeo, a free SIP server.
#
# openMarinkaRodeo is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2 of the License, or
# (at your option) any later version
#
# openMarinkaRodeo is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301  USA
#

=head1 OpenMarinkaRodeo::VDB::Adapter::Speeddial

This adapter can be used with the speeddial module.

=cut

package OpenMarinkaRodeo::VDB::Adapter::Speeddial;

use OpenMarinkaRodeo::Constants;
use OpenMarinkaRodeo qw ( log );

use OpenMarinkaRodeo::VDB;
use OpenMarinkaRodeo::VDB::Column;
use OpenMarinkaRodeo::VDB::Result;

our @ISA = qw ( OpenMarinkaRodeo::VDB );

sub query {
	my $self = shift;

	my $conds = shift;
	my $retkeys = shift; # Unused value here.
	my $order = shift; # Unused value here.

	my @cols;
	
	my $requested_username;
	my $requested_sd_username;
	
	for my $c (@$conds) {
		if (($c->key() eq "username") && ($c->op() eq "=")) {
			$requested_username = $c->data();
		}
		if (($c->key() eq "sd_username") && ($c->op() eq "=")) {
			$requested_sd_username = $c->data();
		}
	}

	my $vtab = $self->{vtabs}->{$self->{tablename}};
	$newaddr = $vtab->call("query", $requested_username, $requested_sd_username);
	
	my $result;

	push @cols, new OpenMarinkaRodeo::VDB::Column(DB_STRING, "uid_name");

	if ($newaddr) {
		my $resval = new OpenMarinkaRodeo::VDB::Value(DB_STRING, $newaddr );
		push my @row, $resval;
		$result = new OpenMarinkaRodeo::VDB::Result(\@cols, (bless \@row, "OpenMarinkaRodeo::Utils::Debug"));
	} else {
		$result = new OpenMarinkaRodeo::VDB::Result(\@cols);
	}

	return $result;
}

1;
