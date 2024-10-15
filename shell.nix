{ pkgs ? import <nixpkgs> {} }:
  pkgs.mkShell {
    # nativeBuildInputs is usually what you want -- tools you need to run
    nativeBuildInputs = with pkgs.buildPackages; [ platformio ];
    shellHook = ''
    export PLATFORMIO_CORE_DIR=$PWD/.platformio
    '';
}
