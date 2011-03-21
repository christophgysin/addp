exec_program(
    "${CMAKE_CURRENT_SOURCE_DIR}/scripts/version.sh libaddp"
    OUTPUT_VARIABLE LIBADDP_VERSION)
exec_program(
    "${CMAKE_CURRENT_SOURCE_DIR}/scripts/version.sh addpc"
    OUTPUT_VARIABLE ADDPC_VERSION)
exec_program(
    "${CMAKE_CURRENT_SOURCE_DIR}/scripts/version.sh addpd"
    OUTPUT_VARIABLE ADDPD_VERSION)
