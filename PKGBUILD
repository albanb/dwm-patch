# $Id: PKGBUILD 146423 2015-11-09 10:39:50Z spupykin $
# Maintainer: Sergej Pupykin <pupykin.s+arch@gmail.com>
# Contributor: Dag Odenhall <dag.odenhall@gmail.com>
# Contributor: Grigorios Bouzakis <grbzks@gmail.com>

pkgname=dwm
pkgver=6.2
pkgrel=1
pkgdesc="A dynamic window manager for X"
url="http://dwm.suckless.org"
arch=('i686' 'x86_64')
license=('MIT')
options=(zipman)
depends=('libx11' 'libxinerama' 'libxft' 'freetype2' 'st' 'dmenu')
install=dwm.install
_source=(http://dl.suckless.org/dwm/dwm-$pkgver.tar.gz
	dwm.desktop)
_patchname=dwm-patch
_patches=("git://github.com/albanb/dwm-patch.git")

source=(${_source[@]} ${_patches[@]})

sha256sums=('97902e2e007aaeaa3c6e3bed1f81785b817b7413947f1db1d3b62b8da4cd110e'
            'bc36426772e1471d6dd8c8aed91f288e16949e3463a9933fee6390ee0ccd3f81'
            'SKIP')

prepare() {
  cd "$srcdir/$pkgname-$pkgver"

  # applying patches
  if ls $srcdir/$_patchname/*\.diff 2> /dev/null;then for i in $srcdir/$_patchname/*\.diff;do msg "applying $i"; patch -p1 <$i;done;fi

  # custom config
  if [[ -f $srcdir/$_patchname/config.h ]]; then
    #ln -sf $SRCDEST/config.h $srcdir/config.h
    cp "$srcdir/$_patchname/config.h" "$srcdir/$pkgname-$pkgver/config.h"
  fi
}

build() {
  cd $srcdir/$pkgname-$pkgver
  make X11INC=/usr/include/X11 X11LIB=/usr/lib/X11 FREETYPEINC=/usr/include/freetype2
}

package() {
  cd $srcdir/$pkgname-$pkgver
  make PREFIX=/usr DESTDIR=$pkgdir install
  install -m644 -D LICENSE $pkgdir/usr/share/licenses/$pkgname/LICENSE
  install -m644 -D README $pkgdir/usr/share/doc/$pkgname/README
  install -m644 -D $srcdir/dwm.desktop $pkgdir/usr/share/xsessions/dwm.desktop
}
