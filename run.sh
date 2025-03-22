#!/usr/bin/env bash

PROJ_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )
BUILD_DIR=${PROJ_DIR}/build

function build() {
  if [ ! -d "${BUILD_DIR}" ]; then
    mkdir "${BUILD_DIR}"
  fi
  cd "${BUILD_DIR}" || exit 1
  cmake ..
  make -j "$(nproc)"
}

function flash() {
  "${BUILD_DIR}/tools/bootsel"
  sleep 1
  picotool load -x "${BUILD_DIR}/src/firmware.uf2"
}

function show_help() {
  echo '██████╗ ██╗   ██╗███╗   ██╗
██╔══██╗██║   ██║████╗  ██║
██████╔╝██║   ██║██╔██╗ ██║
██╔══██╗██║   ██║██║╚██╗██║
██║  ██║╚██████╔╝██║ ╚████║
╚═╝  ╚═╝ ╚═════╝ ╚═╝  ╚═══╝
---------------------------
usage: run.sh <command>

commands:
build - compile cmake project
flash - force pico into bootsel & flash firmware
reload - build & flash
monitor - watch pico stdout over usb
clean - remove build artifacts
help - show this help message
'
}

case "$1" in
  "build")
    build;
    ;;

  "clean")
    if [ -d "${BUILD_DIR}" ]; then
      rm -r "${BUILD_DIR}"
    fi
    ;;

  "flash")
    flash;
    ;;

  "reload")
    build;
    flash;
    ;;

  "monitor")
    sudo minicom -D /dev/ttyACM0 -b 115200
    ;;

  "help")
    show_help;
    ;;

  *)
    show_help;
    ;;

esac

