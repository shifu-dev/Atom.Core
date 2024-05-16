{
    description = "atom.core";

    inputs = {
        nixpkgs.url = "github:nixos/nixpkgs/nixos-unstable";

        cpptrace.url = "github:jeremy-rifkin/cpptrace";
        cpptrace.flake = false;
    };

    outputs = inputs:
    let
        system = "x86_64-linux";
        pkgs = inputs.nixpkgs.legacyPackages.${system};
        stdenv = pkgs.llvmPackages_18.libcxxStdenv;
        lib = pkgs.lib;
    in
    {
        devShells.${system}.default = stdenv.mkDerivation {

            name = "atom.core";

            buildInputs = with pkgs; [
                catch2_3
                fmt
                magic-enum

                cmake
                cmake-format
                ninja
                git
            ];

            cpptrace_DIR = inputs.cpptrace;
            catch2_DIR = pkgs.catch2_3;

            CXXFLAGS = lib.strings.concatStrings [
                " -I /nix/store/csml9b5w7z51yc7hxgd2ax4m6vj36iyq-libcxx-18.1.5-dev/include"
                " -I /nix/store/2sf9x4kf8lihldhnhp2b8q3ybas3p83l-compiler-rt-libc-18.1.5-dev/include"
                " -I /nix/store/hrssqr2jypca2qcqyy1xmfdw71nv6n14-catch2-3.5.2/include"
                " -I /nix/store/zc8xnz48ca61zjplxc3zz1ha3zss046p-fmt-10.2.1-dev/include"
                " -I /nix/store/2j35qpxbprdgcixyg70lyy6m0yay9352-magic-enum-0.9.5/include"
                " -I /nix/store/k3701zl6gmx3la7y4dnflcvf3xfy88kh-python3-3.11.9/include"
                " -I /nix/store/csml9b5w7z51yc7hxgd2ax4m6vj36iyq-libcxx-18.1.5-dev/include/c++/v1"
                " -I /nix/store/fymdqlxx6zsqvlmfwls3h2fly9kz0vcf-clang-wrapper-18.1.5/resource-root/include"
                " -I /nix/store/s3pvsv4as7mc8i2nwnk2hnsyi2qdj4bq-glibc-2.39-31-dev/include"
            ];

            CMAKE_GENERATOR = "Ninja";
            CMAKE_BUILD_TYPE = "Debug";
            CMAKE_EXPORT_COMPILE_COMMANDS = "true";
        };
    };
}
