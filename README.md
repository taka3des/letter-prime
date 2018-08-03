# letter-prime
letter-prime - generate primes for arbitrary letters
(c)2018 by Seishi Takamura

1. Compilation
Type "make all"
or
g++ -O3 gen-string.cpp -o gen-string
g++ -O3 string-prime.cpp miller-rabin-gmp.cpp -o string-prime -lgmp -lgmpxx

2. Execution example (ASCII)
./gen-string bdf_fonts/6x10.bdf TestStr | ./string-prime
./gen-string bdf_fonts/6x10.bdf TestStr | ./string-prime -nodup

"-nodup" option assigns different digit to each character.
By default, duplicate digits may be assigned.

3. Execution example (Japanese)
You need a JIS-code text and font file. An example to generate the text is:
echo Š¿Žš | nkf -j > tmp.txt
(NKF (network kanji filter, https://ja.osdn.net/projects/nkf/releases/p533)
should be installed beforehand.)
Or, use any text editor which is capable of JIS-code editing.
In the text file, NO ASCII CHARACTERS shall be included.
Then invoke e.g.,
./gen-string bdf_fonts/k20m.bdf -j tmp.txt | ./string-prime

4. Prerequisites
You need GMP (GNU Multi-Precision Library)
In Cygwin, install libgmp-devel, libgmp, libgmpxx.

5. Notes
o Prime checker
Miller-rabin-gmp.h and Miller-rabin-gmp.cpp are copied from
https://github.com/cslarsen/miller-rabin
Thank you.

o BDF font generation (ASCII)
gen-string needs a font in BDF format.
In Cygwin, install "xorg-x11-fonts-misc" package. Then lots of pcf.gz files are
deployed in /usr/share/X11/fonts/misc.

Then obtain pcf2bdf package from
https://github.com/ganaware/pcf2bdf
and compile. In my environment, I commented out the line 20 of pcf2bdf.cc:
#  define _setmode setmode
to suppress compilation error.

Then you can directly convert pcf.gz files into bdf file, e.g., 
pcf2bdf -v -o 4x6.bdf /usr/share/X11/fonts/misc/4x6-ISO8859-1.pcf.gz
bdf_fonts/[1-9]*.bdf are generated with this way.

Other Japanese fonts (bdf_fonts/jis*.bdf, k*.bdf) are public domain fonts.

