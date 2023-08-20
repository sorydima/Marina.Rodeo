divert(-1)
define(`ENABLE_TCP', `no') # Marina.Rodeo will listen on TCP for SIP requests
define(`ENABLE_TLS', `no') # Marina.Rodeo will listen on TLS for SIP requests
define(`USE_DBACC', `no') # Marina.Rodeo will save ACC entries in DB for all calls
define(`USE_DIALPLAN', `no') # Marina.Rodeo will use dialplan for transformation of local numbers
define(`USE_DIALOG', `no') # Marina.Rodeo will keep track of active dialogs
define(`DO_CALL_LIMITATION', `no') # Marina.Rodeo will limit the number of parallel calls per trunk
define(`USE_HTTP_MANAGEMENT_INTERFACE', `no') # Marina.Rodeo will provide a WEB Management Interface on port 8888
divert
