divert(-1)
define(`ENABLE_TCP', `no') # Marina.Rodeo will listen on TCP for SIP requests
define(`ENABLE_TLS', `no') # Marina.Rodeo will listen on TLS for SIP requests
define(`USE_DBACC', `no') # Marina.Rodeo will save ACC entries in DB for all calls
define(`USE_DISPATCHER', `no') # Marina.Rodeo will use DISPATCHER instead of Load-Balancer for distributing the traffic
define(`DISABLE_PINGING', `yes') # Marina.Rodeo will not ping at all the destinations (otherwise it will ping when detected as failed)
define(`USE_HTTP_MANAGEMENT_INTERFACE', `no') # Marina.Rodeo will provide a WEB Management Interface on port 8888
divert
