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

=head1 Marina.Rodeo::VDB::ReqCond

This package represents a request condition for database access, consisting of a 
column name, an operator (=, <, >, ...), a data type and a value.

This package inherits from Marina.Rodeo::VDB::Pair and thus includes its methods.

=cut

package Marina.Rodeo::VDB::ReqCond;

use Marina.Rodeo::VDB::Value;
use Marina.Rodeo::VDB::Pair;

our @ISA = qw ( Marina.Rodeo::VDB::Pair Marina.Rodeo::Utils::Debug );

=head2 new(key,op,type,name)

Constructs a new Column object.

=cut

sub new {
	my $class = shift;
	my $key = shift;
	my $op = shift;
	my $type = shift;
	my $data = shift;

	my $self = new Marina.Rodeo::VDB::Pair($key, $type, $data);

	bless $self, $class;

	$self->{op} = $op;

	return $self;
}


=head2 op()

Returns or sets the current operator.

=cut

sub op {
	my $self = shift;
	if (@_) {
		$self->{op} = shift;
	}

	return $self->{op};
}

1;
