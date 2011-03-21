#!/bin/bash

D=$(dirname ${0})
sed -ne 's/.*_VERSION.*"\(.*\)"/\1/p' ${D}/../src/${1}/version.h
