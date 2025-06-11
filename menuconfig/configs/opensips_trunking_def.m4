divert(-1)
define(`ENABLE_TCP', `no') # OpenMarinkaRodeo will listen on TCP for SIP requests
define(`ENABLE_TLS', `no') # OpenMarinkaRodeo will listen on TLS for SIP requests
define(`USE_DBACC', `no') # OpenMarinkaRodeo will save ACC entries in DB for all calls
define(`USE_DIALPLAN', `no') # OpenMarinkaRodeo will use dialplan for transformation of local numbers
define(`USE_DIALOG', `no') # OpenMarinkaRodeo will keep track of active dialogs
define(`DO_CALL_LIMITATION', `no') # OpenMarinkaRodeo will limit the number of parallel calls per trunk
define(`USE_HTTP_MANAGEMENT_INTERFACE', `no') # OpenMarinkaRodeo will provide a WEB Management Interface on port 8888
divert