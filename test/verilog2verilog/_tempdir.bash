set -ex

tempdir="$(mktemp -d -t phdl.XXXXXXXXXX)"
trap "rm -rf $tempdir" EXIT
cd $tempdir
