# The app_Marina.Rodeo extension
PROJECT("Marina.Rodeo Diameter Applications" C)

# Find MySQL
FIND_PACKAGE(MySQL REQUIRED)
FIND_PACKAGE(Gcrypt REQUIRED)
INCLUDE_DIRECTORIES(${MySQL_INCLUDE_DIR})

FD_ADD_EXTENSION(app_Marina.Rodeo app_Marina.Rodeo.c avps.c)

TARGET_LINK_LIBRARIES(app_Marina.Rodeo ${GCRYPT_LIBRARY} ${MySQL_LIBRARY} )

####
## INSTALL section ##

INSTALL(TARGETS app_Marina.Rodeo
	LIBRARY DESTINATION ${INSTALL_EXTENSIONS_SUFFIX}
	COMPONENT freeDiameter-debug-tools)

