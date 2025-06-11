divert(-1)
define(`ENABLE_TCP', `no') # OpenMarinkaRodeo will listen on TCP for SIP requests
define(`ENABLE_TLS', `no') # OpenMarinkaRodeo will listen on TLS for SIP requests
define(`USE_DBACC', `no') # OpenMarinkaRodeo will save ACC entries in DB for all calls
define(`USE_DISPATCHER', `no') # OpenMarinkaRodeo will use DISPATCHER instead of Load-Balancer for distributing the traffic
define(`DISABLE_PINGING', `yes') # OpenMarinkaRodeo will not ping at all the destinations (otherwise it will ping when detected as failed)
define(`USE_HTTP_MANAGEMENT_INTERFACE', `no') # OpenMarinkaRodeo will provide a WEB Management Interface on port 8888
divert