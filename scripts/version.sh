#!/bin/bash

D=$(dirname ${0})
sed -ne 's/#define ADDP_VERSION.*"\(.*\)"/\1/p' ${D}/../src/libaddp/version.h
