#!/bin/bash

status=true

# ---------------------------------------------------

./gauss AB.csv AB.actual.csv
cmp AB.expected.csv AB.actual.csv || status=false
rm -f AB.actual.csv

# ---------------------------------------------------

$status
