FROM mcr.microsoft.com/vscode/devcontainers/base:ubuntu-24.04 AS base

ARG CLANG_VERSION="18"
ARG CATCH2_VERSION="3.8.0"
ARG CPPTRACE_VERSION="0.7.5"
ARG FMT_VERSION="11.1.3"
ARG MAGIC_ENUM_VERSION="0.9.7"
ARG TOOLCHAIN_URI="20250114/llvm-mingw-20250114-ucrt-ubuntu-20.04-x86_64.tar.xz"
ARG INSTALL_DIR="/out"

# -------------------------------------------------------------------------------------------------
# Install build tools
# -------------------------------------------------------------------------------------------------

RUN apt-get update \
    && apt-get install --yes --no-install-recommends \
    ninja-build \
    cmake \
    pkg-config \
    git \
    ca-certificates \
    && rm -rf /var/lib/apt/lists/*

ENV CMAKE_GENERATOR="Ninja"

# -------------------------------------------------------------------------------------------------
# Install toolchain
# -------------------------------------------------------------------------------------------------

ENV TOOLCHAIN_ROOT="/opt/llvm-mingw"
RUN wget https://github.com/mstorsjo/llvm-mingw/releases/download/$TOOLCHAIN_URI \
    -O llvm-mingw.tar.xz \
    && mkdir $TOOLCHAIN_ROOT \
    && tar -xf llvm-mingw.tar.xz --directory $TOOLCHAIN_ROOT --strip-components=1 \
    && rm llvm-mingw.tar.xz

ENV PATH=$TOOLCHAIN_ROOT/bin:$PATH \
    CC="$TOOLCHAIN_ROOT/bin/clang" \
    CXX="$TOOLCHAIN_ROOT/bin/clang++" \
    CMAKE_TOOLCHAIN_FILE="/opt/cmake/toolchain.cmake"

COPY cmake/llvm-mingw-w64-toolchain.cmake $CMAKE_TOOLCHAIN_FILE

# -------------------------------------------------------------------------------------------------
# Install catch2, required by
# - atom_core
# -------------------------------------------------------------------------------------------------

FROM base AS catch2-builder

RUN git clone "https://github.com/catchorg/catch2.git" \
    --depth 1 --branch v$CATCH2_VERSION \
    && cd catch2 \
    && cmake -S . -B build \
    && cmake --build build \
    && cmake --install build --prefix /out

    # --target Catch2

# -------------------------------------------------------------------------------------------------
# Install cpptrace, required by
# - atom_core
# -------------------------------------------------------------------------------------------------

FROM base AS cpptrace-builder

RUN git clone "https://github.com/jeremy-rifkin/cpptrace.git" \
    --depth 1 --branch v$CPPTRACE_VERSION \
    && cd cpptrace \
    && cmake -S . -B build \
    && cmake --build build \
    && cmake --install build --prefix /out

# -------------------------------------------------------------------------------------------------
# Install fmt, required by
# - atom_core
# -------------------------------------------------------------------------------------------------

FROM base AS fmt-builder

RUN git clone "https://github.com/fmtlib/fmt.git" \
    --depth 1 --branch $FMT_VERSION \
    && cd fmt \
    && cmake -S . -B build \
    && cmake --build build --target fmt \
    && cmake --install build --prefix /out

# -------------------------------------------------------------------------------------------------
# Install magic_enum, required by
# - atom_core
# -------------------------------------------------------------------------------------------------

FROM base AS magic_enum-builder

# We dont need to build anything for magic_enum, its header only
RUN git clone "https://github.com/neargye/magic_enum.git" \
    --depth 1 --branch v$MAGIC_ENUM_VERSION \
    && cd magic_enum \
    && cmake -S . -B build \
    && cmake --install build --prefix /out

# -------------------------------------------------------------------------------------------------
# Builder envrionment
# -------------------------------------------------------------------------------------------------

FROM base AS builder

# Install dependencies
COPY --from=catch2-builder /out /usr/local
COPY --from=cpptrace-builder /out /usr/local
COPY --from=fmt-builder /out /usr/local
COPY --from=magic_enum-builder /out /usr/

# -------------------------------------------------------------------------------------------------
# Development environment
# -------------------------------------------------------------------------------------------------

FROM builder AS devenv

# Install dev tools
RUN apt-get update \
    && apt-get install --yes --no-install-recommends \
    clang-format-$CLANG_VERSION \
    clang-tidy-$CLANG_VERSION \
    clangd-$CLANG_VERSION \
    lldb-$CLANG_VERSION \
    cmake-format \
    doxygen \
    vim \
    && rm -rf /var/lib/apt/lists/*

# -------------------------------------------------------------------------------------------------
# Runtime envrionment
# -------------------------------------------------------------------------------------------------

FROM builder AS runtime

COPY . .
RUN cmake -S . -B build \
    && cmake --build build --target atom_core \
    && cmake --install build --prefix $INSTALL_DIR
