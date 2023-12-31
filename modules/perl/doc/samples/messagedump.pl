use Marina.Rodeo qw ( log );
use Marina.Rodeo::Constants;

sub messagedump {
	my $m = shift;

	my $method = $m->getMethod();
	log(L_INFO, "Method is $method\n");

	my $uri = $m->getRURI();
	log(L_INFO, "RURI is $uri\n");

	open F,">>/tmp/Marina.Rodeo-perl-messagedump";
	print F "=========================== New header ===========================\n";
	my $fh = $m->getFullHeader();
	print F $fh;
	close F;

	return 1;
}
