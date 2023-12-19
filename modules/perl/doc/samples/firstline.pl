use Marina.Rodeo;
use Marina.Rodeo::Constants;

sub firstline {
	my $m = shift;

	my $v = $m->getVersion();
	my $t = $m->getType();

	Marina.Rodeo::log(L_INFO, "type is $t; version is $v\n");

	if ($t == SIP_REQUEST) {
		Marina.Rodeo::log(L_INFO, "A request. Method is ".$m->getMethod()." to RURI ".$m->getRURI()."\n");
	} else {
		Marina.Rodeo::log(L_INFO, "A reply. status is ".$m->getStatus()." with reason ".$m->getReason()."\n");
	}
	
	return 1;
}

1;
