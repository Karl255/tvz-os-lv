# 1. priprema - sistemski pozivi

## Izvorni kod naredbi
`cp.c` sadrži izvorni kod za obje verzije naredbe. To je ostvareno koristeći makronaredbe i define opciju u naredbi za kompiliranje. `build_std.sh` i `build_sys.sh` su skripte koje kompiliraju zasebnu verziju naredbe. Korišten C/C++ kompajler `clang` bi se trebao moći zamijeniti sa `gcc` bez grešaka prilikom kompilacije.

Naredbe imaju relativno sofisticirano korisničko "sučelje". Podržane opcije (samo jedna od njih odjenom): `-b=[veličina buffera u bajtovima]`, `-h` te `--`.

## measure_all.py
Ova Python 3 skripta mjeri brzine kopiranja za određenu veličinu buffera koristeći `bash`-ovu `time` naredbu. Rezultate sprema u datoteku.

## Datotke za testiranje naredbi
Jedan način generiranja tih datoteka: `head -c 1G /dev/urandom > test_file_1GB`
