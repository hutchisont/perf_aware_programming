#!/usr/bin/env bash

function main() {
	if [[ ! -d "build/" ]]; then
		run/config.sh || exit 1
	fi

	cmake --build build/ || exit 1
}

main "$@"
