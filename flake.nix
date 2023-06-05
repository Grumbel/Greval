{
  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-23.05";
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
        packages = rec {
          default = greval;

          greval = pkgs.stdenv.mkDerivation {
            pname = "greval";
            version = tinycmmc.lib.versionFromFile self;
            src = nixpkgs.lib.cleanSource ./.;
            cmakeFlags = [
              "-DBUILD_EXTRA=ON"
              "-DWARNINGS=ON"
              "-DWERROR=ON"
            ];
            nativeBuildInputs = with pkgs; [
              cmake
            ];
            buildInputs = with pkgs; [
              gtest
            ] ++ [
              tinycmmc.packages.${system}.default
            ];
          };
        };

        apps = rec {
          default = greval-eval;

          greval-eval = flake-utils.lib.mkApp {
            drv = packages.greval;
            exePath = "/bin/greval-eval";
          };

          greval-lexer = flake-utils.lib.mkApp {
            drv = packages.greval;
            exePath = "/bin/greval-lexer";
          };
        };
      }
    );
}
