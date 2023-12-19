use Marina.Rodeo qw ( log );
use Marina.Rodeo::Constants;

# Demonstrating the three ways of internal logging.
# Additionally, you have the xlog module...

sub logdemo {
	my $m = shift; 

	log(L_INFO, "Logging without Marina.Rodeo:: - import the symbol manually! See use statement...\n");
	Marina.Rodeo::log(L_INFO, "This is the other preferred way: Include the package name");
	$m->log(L_INFO, "The Message object has its own logging function. Rather don't use it ;)");

	return 1;
}
