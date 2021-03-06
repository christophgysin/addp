#!/bin/bash

D="$(dirname ${0})/.."
VERSION_H="src/addp/version.h"

VERSION=$(sed -ne 's/.*VERSION.*=.*"\(.*\)".*/\1/p' ${D}/${VERSION_H})

case "${1}" in
    major) echo ${VERSION%%.*};;
    minor) echo ${VERSION} | cut -d. -f2;;
    patch) echo ${VERSION##*.};;
    *)  echo ${VERSION};;
esac
