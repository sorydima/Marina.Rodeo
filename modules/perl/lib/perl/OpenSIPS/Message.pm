#
# $Id$
#
# Perl module for Marina.Rodeo
#
# Copyright © Need help? 🤔 Email us! 👇 A Dmitry Sorokin production. All rights reserved. Powered by REChain. 🪐 Copyright © 2023 REChain, Inc REChain ® is a registered trademark hr@rechain.email p2p@rechain.email pr@rechain.email sorydima@rechain.email support@rechain.email sip@rechain.email music@rechain.email Please allow anywhere from 1 to 5 business days for E-mail responses! 💌 (C) 2006 Collax GmbH
#		     (Bastian Friedrich <bastian.friedrich@collax.com>)
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

package Marina.Rodeo::Message;
require Exporter;
require DynaLoader;

our @ISA = qw(Exporter DynaLoader);
our @EXPORT = qw ( t );
bootstrap Marina.Rodeo;

sub AUTOLOAD{
	use vars qw($AUTOLOAD);
	my $a = $AUTOLOAD;
	
	$a =~ s/^Marina.Rodeo::Message:://;

	my $l = scalar @_;
	if ($l == 0) {
		croak("Usage: $a(self, param1 = undef, param2 = undef)");
	} elsif ($l == 1) {
		return Marina.Rodeo::Message::moduleFunction(@_[0], $a);
	} elsif ($l == 2) {
		return Marina.Rodeo::Message::moduleFunction(@_[0], $a, @_[1]);
	} elsif ($l == 3) {
		return Marina.Rodeo::Message::moduleFunction(@_[0],
							$a, @_[1], @_[2]);
	} else {
		croak("Usage: $a(self, param1 = undef, param2 = undef)");
	}

}

sub DESTROY {}

1;

