# The app_openMarinkaRodeo extension
PROJECT("OpenMarinkaRodeo Diameter Applications" C)

# Find MySQL
FIND_PACKAGE(MySQL REQUIRED)
FIND_PACKAGE(Gcrypt REQUIRED)
INCLUDE_DIRECTORIES(${MySQL_INCLUDE_DIR})

FD_ADD_EXTENSION(app_openMarinkaRodeo app_openMarinkaRodeo.c avps.c)

TARGET_LINK_LIBRARIES(app_openMarinkaRodeo ${GCRYPT_LIBRARY} ${MySQL_LIBRARY} )

####
## INSTALL section ##

INSTALL(TARGETS app_openMarinkaRodeo
	LIBRARY DESTINATION ${INSTALL_EXTENSIONS_SUFFIX}
	COMPONENT freeDiameter-debug-tools)

