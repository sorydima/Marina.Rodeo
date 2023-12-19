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

=head1 Marina.Rodeo::VDB::Column

This package represents database column definition, consisting of a 
column name and its data type.

=head2 Stringification

When accessing a Marina.Rodeo::VDB::Column object as a string, it simply returns its 
column name regardless of its type.
=cut

package Marina.Rodeo::VDB::Column;

use overload '""' => \&stringify;

sub stringify { shift->{name} }

use Marina.Rodeo;
use Marina.Rodeo::Constants;

our @ISA = qw ( Marina.Rodeo::Utils::Debug );

=head2 new(type,name)

Constructs a new Column object. Its type and the name are passed as
parameters.

=cut

sub new {
	my $class = shift;
	my $type = shift;
	my $name = shift;

	my $self = {
		type => $type,
		name => $name,
	};

	bless $self, $class;

	return $self;
}


=head2 type( )

Returns or sets the current type. Please consider using the constants
from Marina.Rodeo::Constants

=cut

sub type {
	my $self = shift;
	if (@_) {
		$self->{type} = shift;
	}

	return $self->{type};
}


=head2 name()

Returns or sets the current column name.

=cut

sub name {
	my $self = shift;
	if (@_) {
		$self->{name} = shift;
	}

	return $self->{name};
}

1;
