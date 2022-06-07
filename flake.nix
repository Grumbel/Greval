{
  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-22.05";
    flake-utils.url = "github:numtide/flake-utils";

    tinycmmc.url = "github:grumbel/tinycmmc";
    tinycmmc.inputs.nixpkgs.follows = "nixpkgs";
    tinycmmc.inputs.flake-utils.follows = "flake-utils";
  };

  outputs = { self, nixpkgs, flake-utils, tinycmmc }:
    flake-utils.lib.eachDefaultSystem (system:
      let
        pkgs = nixpkgs.legacyPackages.${system};
      in rec {
        packages = flake-utils.lib.flattenTree {
          expr = pkgs.stdenv.mkDerivation {
            pname = "expr";
            version = tinycmmc.lib.versionFromFile self;
            src = nixpkgs.lib.cleanSource ./.;
            cmakeFlags = [
              "-DWARNINGS=ON"
              "-DWERROR=ON"
            ];
            nativeBuildInputs = with pkgs; [
              cmake
            ];
            buildInputs = with pkgs; [
              gtest
            ] ++ [
              tinycmmc.defaultPackage.${system}
            ];
          };
        };
        defaultPackage = packages.expr;
      }
    );
}
