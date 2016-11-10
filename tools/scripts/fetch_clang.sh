#!/bin/bash -e
#
# Bareflank Hypervisor
#
# Copyright (C) 2015 Assured Information Security, Inc.
# Author: Rian Quinn        <quinnr@ainfosec.com>
# Author: Brendan Kerrigan  <kerriganb@ainfosec.com>
#
# This library is free software; you can redistribute it and/or
# modify it under the terms of the GNU Lesser General Public
# License as published by the Free Software Foundation; either
# version 2.1 of the License, or (at your option) any later version.
#
# This library is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
# Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public
# License along with this library; if not, write to the Free Software
# Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA

pushd /tmp/bareflank/

rm -Rf source_llvm

n=0
until [ $n -ge 5 ]
do
    git clone --depth 1 -b cfar_38 git@github.com:/securesystemslab/multicompiler-priv.git source_llvm && break
    n=$[$n+1]
    sleep 15
done

n=0
until [ $n -ge 5 ]
do
    git clone --depth 1 -b cfar_38 git@github.com:/securesystemslab/multicompiler-clang-priv.git source_llvm/tools/clang && break
    n=$[$n+1]
    sleep 15
done

n=0
until [ $n -ge 5 ]
do
    git clone --depth 1 -b cfar_38 git@github.com:/securesystemslab/multicompiler-compiler-rt-priv.git source_llvm/projects/compiler-rt && break
    n=$[$n+1]
    sleep 15
done

n=0
until [ $n -ge 5 ]
do
    git clone --depth 1 -b cfar_38 git@github.com:/securesystemslab/poolalloc source_llvm/projects/poolalloc && break
    n=$[$n+1]
    sleep 15
done

n=0
until [ $n -ge 5 ]
do
    git clone --depth 1 git@github.com:/rboggild/SVF source_llvm/projects/svf && break
    n=$[$n+1]
    sleep 15
done

popd
