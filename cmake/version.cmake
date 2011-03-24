set(VERSION_SCRIPT "${CMAKE_CURRENT_SOURCE_DIR}/scripts/version.sh")
exec_program("${VERSION_SCRIPT} major" OUTPUT_VARIABLE ADDP_VERSION_MAJOR)
exec_program("${VERSION_SCRIPT} minor" OUTPUT_VARIABLE ADDP_VERSION_MINOR)
exec_program("${VERSION_SCRIPT} patch" OUTPUT_VARIABLE ADDP_VERSION_PATCH)
set(ADDP_VERSION
    ${ADDP_VERSION_MAJOR}.${ADDP_VERSION_MINOR}.${ADDP_VERSION_PATCH})
