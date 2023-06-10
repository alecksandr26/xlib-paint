# @file PKGBUILD 
# @brief The package script
# @author Erick Carrillo.
# @copyright Copyright (C) 2023, Erick Alejandro Carrillo López, All right reserved.
# @license This project is released under the MIT License 

# This is an example PKGBUILD file. Use this as a start to creating your own,
# and remove these comments. For more information, see 'man PKGBUILD'.
# NOTE: Please fill out the license field for your package! If it is unknown,
# then please put 'unknown'.

# Maintainer: alecksandr <sansepiol26@gmail.com>

# Move to the build directory
pkgname=paint
pkgver=1.0.0
pkgrel=1
epoch=
pkgdesc="Simple paint program, it
offers a simple and intuitive interface, allowing you to unleash your creativity on a
blank black whiteboard. With essential tools like brushes, erasers, and a variety of colors"
arch=('x86_64')
url=""
license=('MIT License')
depends=()
makedepends=(gcc git make binutils coreutils)
optdepends=(valgrind)
source=("$pkgname-$pkgver.tar.gz::$url")
md5sums=('SKIP')
basedir=$(pwd)

# Compile the source code 
build() {
    if [ -f "$basedir/$pkgname-$pkgver.tar.gz" ]; then
	echo "==> Compiling package..."
        tar -xf "$basedir/$pkgname-$pkgver.tar.gz"
        cd "$srcdir/$pkgname-$pkgver"
        make compile
    else
        echo "==> Compiling package locally..."
	echo "==> Trying to find the local source code path..."
	if [ -d "../../../../$pkgname" ]; then
	    echo "==> Source code $pkgname found..."
	    cd ../../../../$pkgname
	    make compile
	    mkdir -p $srcdir/$pkgname-$pkgver
	    mkdir -p $srcdir/$pkgname-$pkgver/bin
	    cp bin/main $srcdir/$pkgname-$pkgver/bin/paint
	else
	    echo "==> Error source code $pkgname not found..."
	    exit 1
	fi
    fi
}

# Set the compiled files to create the package
# in this specific order to be able to be installed
package() {
    cd $srcdir/$pkgname-$pkgver
    
    # Create the folders
    mkdir -p $pkgdir/usr
    mkdir -p $pkgdir/usr/bin
    
    # Install into the package the program
    cp -r bin/* $pkgdir/usr/bin/
}
