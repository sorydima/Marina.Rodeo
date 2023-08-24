divert(-1)
define(`ENABLE_TCP', `no') # Marina.Rodeo will listen on TCP for SIP requests
define(`ENABLE_TLS', `no') # Marina.Rodeo will listen on TLS for SIP requests
define(`USE_ALIASES', `no') # Marina.Rodeo will allow the use of Aliases for SIP users
define(`USE_AUTH', `no') # Marina.Rodeo will authenticate Register & Invite requests
define(`USE_DBACC', `no') # Marina.Rodeo will save ACC entries in DB for all calls
define(`USE_DBUSRLOC', `no') # Marina.Rodeo will store UsrLoc entries in the DB
define(`USE_DIALOG', `no') # Marina.Rodeo will keep track of active dialogs
define(`USE_MULTIDOMAIN', `no') # Marina.Rodeo will handle multiple domains for subscribers
define(`USE_NAT', `no') # Marina.Rodeo will try to cope with NAT by fixing SIP msgs and engaging RTPProxy
define(`USE_PRESENCE', `no') # Marina.Rodeo will act as a Presence server
define(`USE_DIALPLAN', `no') # Marina.Rodeo will use dialplan for transformation of local numbers
define(`VM_DIVERSION', `no') # Marina.Rodeo will redirect to VM calls not reaching the subscribers
define(`HAVE_INBOUND_PSTN', `no') # Marina.Rodeo will accept calls from PSTN gateways (with static IP authentication)
define(`HAVE_OUTBOUND_PSTN', `no') # Marina.Rodeo will send numerical dials to PSTN gateways (with static IP definition)
define(`USE_DR_PSTN', `no') # Marina.Rodeo will use Dynamic Routing Support for PSTN interconnection
define(`USE_HTTP_MANAGEMENT_INTERFACE', `no') # Marina.Rodeo will provide a WEB Management Interface on port 8888
divert
