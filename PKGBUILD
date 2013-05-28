pkgname=dwm-git
_pkgname=dwm
pkgver=6.0
pkgver(){
  cd $_pkgname
  git describe --tags |sed 's/-/./g'
}
pkgrel=1

pkgdesc="A dynamic window manager for X"
url="http://dwm.suckless.org"
arch=('i686' 'x86_64')
license=('MIT')
options=(zipman)
depends=('libx11' 'libxinerama')
makedepends=('git')
install=dwm.install
provides=('dwm')
conflicts=('dwm')
epoch=1
source=( dwm.desktop
    "$_pkgname::git+http://git.suckless.org/dwm#tag=6.0"
    "git://github.com/albanb/dwm-patch.git")

prepare() {
  cd "$srcdir/$_pkgname"

  # applying patches
  if ls $SRCDEST/*\.diff 2> /dev/null;then for i in $SRCDEST/*\.diff;do msg "applying $i"; git apply $i;done;fi

  # custom config
  if [[ -f $SRCDEST/config.h ]]; then
    #ln -sf $SRCDEST/config.h $srcdir/config.h
    cp $SRCDEST/config.h $srcdir/$_pkgname/config.h
  fi
}

build() {
  cd $_pkgname
  make X11INC=/usr/include/X11 X11LIB=/usr/lib/X11
}

package() {
  make -C $_pkgname PREFIX=/usr DESTDIR=$pkgdir install
  install -m644 -D $_pkgname/LICENSE $pkgdir/usr/share/licenses/$pkgname/LICENSE
  install -m644 -D $_pkgname/README $pkgdir/usr/share/doc/$pkgname/README
  install -m644 -D $srcdir/dwm.desktop $pkgdir/usr/share/xsessions/dwm.desktop
}

# vim:set ts=2 sw=2 et:
md5sums=('939f403a71b6e85261d09fc3412269ee'
         'SKIP')
