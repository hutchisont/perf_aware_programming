#!/usr/bin/env bash

function main() {
	rm -rf build/
	mkdir -p build/

	pushd build/ || exit 1
	cmake ../ || exit 1
	popd || exit 1
}

main "$@"
