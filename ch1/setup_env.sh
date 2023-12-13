#!/bin/bash

# Note: the URLs are customized for a macOS installation.

# Exit if any command fails.
set -e

if [ $# -ne 1 ]; then
  echo "Convenient script to install the required binaries"
  echo "to build and test LLVM on macOS"
  echo ""
  echo "Usage $0 'where_to_install_path'"
  exit -1
fi

install_prefix="$@"
# Poor's man path massage to get an absolute path.
first_char=`echo ${install_prefix} | cut -c1`
if [ "${first_char}"  != '/' ]; then
  install_prefix=${PWD}/${install_prefix}
fi

final_bin_dir="${install_prefix}/bin"
mkdir -p ${final_bin_dir}

# Couple of helper functions for easier-to-read code.
needs_binary () {
  # Don't abort when returning 0.
  set +e
  bin_name=$1
  if [ -f "`which $1`" ]; then
    return 0
  fi
  return 1
}

print_need_install () {
  need_bin=$1
  bin_name=$2
  if [ ${need_bin} -eq 0 ]; then
    echo "Found '${bin_name}' skipping installation for this package"
    echo "> Consider removing '${bin_name}' from your path to force the install"
    echo ""
  fi
}

print_path_to_add () {
  echo "Tools installed by this script are available at:"
  echo "'${final_bin_dir}'"
  echo ""
  echo "Please consider adding this location to your path"
  echo "export PATH=${final_bin_dir}:\${PATH}"
}

# Names of the packages to download

# Git is vented as part of xcode on macOS.
# We'll get it through Xcode install.
#git_pkg=${install_prefix}/git.tgz
#git_url=""
needs_binary 'git'
need_git=$?
print_need_install ${need_git} 'git'

# CMake's info.
cmake_pkg=${install_prefix}/cmake.tgz
cmake_url="https://github.com/Kitware/CMake/releases/download/v3.28.0/cmake-3.28.0-macos-universal.tar.gz"
needs_binary 'cmake'
need_cmake=$?
print_need_install ${need_cmake} 'cmake'

# The LLVM foundation doesn't vent a binary for MacOS.
# We have to resort on the Xcode installer for that.
#llvm_pkg=${install_prefix}/llvm.tgz
#llvm_url=""
needs_binary 'clang'
need_llvm=$?
print_need_install ${need_llvm} 'clang'

# Ninja's info.
ninja_pkg=${install_prefix}/ninja.zip
ninja_url="https://github.com/ninja-build/ninja/releases/download/v1.11.1/ninja-mac.zip"
needs_binary 'ninja'
need_ninja=$?
print_need_install ${need_ninja} 'ninja'

# Python's info.
python_pkg=${install_prefix}/python.pkg
needs_binary 'python3'
need_python=$?
print_need_install ${need_python} 'python3'

# Helper function to download the packages we need.
download_artifact() {
  pkg_name=$1
  pkg_filename=$2
  url=$3

  if [ -f ${pkg_filename} ]; then
    echo "Found ${pkg_name} package at '${pkg_filename}'"
    echo "> Skipping download"
    echo "> Consider removing this file if the package is out-of-date"
    echo ""
  else
    echo "Downloading ${pkg_name}"
    curl --location ${url} --output ${pkg_filename}
  fi
}

# Download and install Ninja, if needed.
if [ ${need_ninja} -eq 1 ]; then
  download_artifact "ninja" "${ninja_pkg}" "${ninja_url}"
  ninja_bin="${final_bin_dir}/ninja"
  if [ -f "${ninja_bin}" ]; then
    echo "Ninja already found at '${ninja_bin}'"
    echo "> Consider removing it if this is not the right version"
    echo ""
  else
    echo "Installing ninja"
    unzip ${ninja_pkg} -d ${final_bin_dir}
  fi
fi

# Download and install CMake, if needed.
if [ ${need_cmake} -eq 1 ]; then
  download_artifact "cmake" "${cmake_pkg}" "${cmake_url}"
  cmake_bin="${final_bin_dir}/cmake"
  if [ -f "${cmake_bin}" ]; then
    echo "CMake already found at '${cmake_bin}'"
    echo "> Consider removing it if this is not the right version"
    echo ""
  else
    echo "Installing CMake"
    tar xzf ${cmake_pkg} -C ${install_prefix}
    path_to_cmake=`find ${install_prefix} -name cmake | grep '/bin/cmake'`
    ln -sf ${path_to_cmake} ${cmake_bin}
  fi
fi

# Exit if all the other packages are already available.
if [ ${need_python} -eq 0 ] && [ ${need_git} -eq 0 ] && [ ${need_llvm} -eq 0 ]; then
  print_path_to_add
  exit 0
fi

echo "/!\ You have to set the install prefix yourself for the next installations"
read -p "Continue Y/n: " user_input

if [ "${user_input}" == "n" ] || [ "${user_input}" == "N" ];
then
  echo "Python and Xcode CLI tools not installed"
  exit 0
fi

if [ "${user_input}" != "y" ] && [ "${user_input}" != "Y" ] && [ "${user_input}" != "" ];
then
  echo "error: invalid response"
  exit -1
fi

# Install python if needed.
if [ ${need_python} -eq 1 ]; then
  download_artifact "python" "${python_pkg}" "${python_url}"
  echo "Installing python... Please follow installer instructions."
  open ${python_pkg}
fi

read -p "Press any key to continue" -n1

# On macOS the most official way to get git and clang is through xcode.
# if clang and git are already available, assume that they are correct.
if [ ${need_git} -eq 1 ] || [ ${need_llvm} -eq 1 ]; then
  echo "Installing Xcode CLI tools... Please follow installer instructions."
  xcode-select --install
fi

print_path_to_add
exit 0
