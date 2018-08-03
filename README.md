letter-prime
====

Generate primes for arbitrary letters

## Example
300-digit-long prime forming "PRIME"(folded every 30 digits)

    111111111111111111111111111111
    000011222211166611911191444441
    011101211121116111911191411111
    011101211121116111991991411111
    000011222211116111919191444411
    011111212111116111911191411111
    011111211211116111911191411111
    011111211121166611911191444441
    111111111111111111111111111111
    111111111111111111111111111111

## Requirements
You need GMP (GNU Multi-Precision Library).
In Cygwin, install libgmp-devel, libgmp, libgmpxx.

## Usage
    gen-string bdf_font AnyString | string-prime [-nodup]
    gen-string bdf_font -j jis_text | string-prime [-nodup]
`-nodup` option assigns different digit to each character.
By default, duplicate digits may be assigned to each character..


### Execution example (ASCII)
    ./gen-string bdf_fonts/6x10.bdf PRIME | ../string-prime

### Execution example (Japanese)
You need a JIS-code text and Japanese BDF file. An example to generate the text is:

    echo ���� | nkf -j > tmp.txt
Network kanji filter [NKF](https://ja.osdn.net/projects/nkf/releases/p533)
should be installed beforehand.
Or, use any text editor which is capable of JIS-code editing.
In the text file, *NO ASCII CHARACTERS* shall be included.
Then invoke e.g.,

    ./gen-string bdf_fonts/k20m.bdf -j tmp.txt | ./string-prime


## Install
    make all
or

    g++ -O3 gen-string.cpp -o gen-string
    g++ -O3 string-prime.cpp miller-rabin-gmp.cpp -o string-prime -lgmp -lgmpxx



## Notes
### Prime checker
Miller-rabin-gmp.h and Miller-rabin-gmp.cpp are copied from
[The Miller-Rabin probabilistic primality test in C++ w/GMP](https://github.com/cslarsen/miller-rabin) in Github.
Thank you.

### BDF font generation (ASCII)
`gen-string` needs a font in BDF format.
In Cygwin, install "xorg-x11-fonts-misc" package. Then lots of pcf.gz files are
deployed in /usr/share/X11/fonts/misc.

Then obtain [pcf2bdf](https://github.com/ganaware/pcf2bdf) package from Github
and compile. In my environment, I need to commented out the line 20 of pcf2bdf.cc:
`#  define _setmode setmode`
to suppress compilation error.

Then you can directly convert pcf.gz files into bdf file, e.g., 

    pcf2bdf -v -o 4x6.bdf /usr/share/X11/fonts/misc/4x6-ISO8859-1.pcf.gz
bdf_fonts/[1-9]*.bdf are generated with this way.

Other Japanese fonts (bdf_fonts/jis*.bdf, k*.bdf) are public domain fonts.


## Author
[Seishi Takamura](https://github.com/taka3des/)
