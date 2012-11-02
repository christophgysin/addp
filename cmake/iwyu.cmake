include(CMakeForceCompiler)
CMAKE_FORCE_C_COMPILER(include-what-you-use CLANG)
CMAKE_FORCE_CXX_COMPILER(include-what-you-use CLANG)

add_custom_target(iwyu
    COMMAND make -k 3>&1 1>&2 2>&3 | tee iwyu.log
    COMMAND iwyu-fix_includes.py < iwyu.log)
