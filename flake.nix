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
        tinylib = tinycmmc.lib { inherit nixpkgs; };
      in rec {
        packages = flake-utils.lib.flattenTree {
          expr = pkgs.stdenv.mkDerivation {
            pname = "expr";
            version = tinylib.version_from_file self;
            src = nixpkgs.lib.cleanSource ./.;
            cmakeFlags = [ "-DBUILD_EXTRA=ON" ];
            postFixup = ''
              wrapProgram $out/libexec/expr \
                --prefix LIBGL_DRIVERS_PATH ":" "${pkgs.mesa.drivers}/lib/dri" \
                --prefix LD_LIBRARY_PATH ":" "${pkgs.mesa.drivers}/lib"
            '';
            nativeBuildInputs = with pkgs; [
              cmake
              makeWrapper
              pkgconfig
            ];
            buildInputs = with pkgs; [
              tinycmmc.defaultPackage.${system}
            ];
          };
        };
        defaultPackage = packages.expr;
      }
    );
}
