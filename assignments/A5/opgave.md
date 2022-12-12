# Simulatoropgaven (A5, CompSys 2022)

Finn Schiermer Andersen, rev 1.0, 6. december.

Denne opgave stilles mandag den 5. december og skal afleveres kl 12 søndag den 18. december.



## Opgave

Der skal implementeres en simulator for RISC-V, 32-bit base instruktionssæt og udvidelsen
for 32-bit multiplikation/division. Dog skal enkelte specielle instruktioner ikke indgå.
Derudover skal simulatoren håndtere nogle få systemkald. Detaljer gives nedenfor. 
Simulatoren skal skrives i C.

Til hjælp udleveres en ufærdig simulator som skal færdiggøres. Den udleverede kode tager
hånd om simulation af lager og indlæsning af et program til dette lager. Den understøtter
også at man kan udskrive instruktioner på symbolsk form. For at færdiggøre
simulatoren skal I skrive funktionen "simulate()" som allerede er erklæret
i "simulate.h".

Der udleveres nogle programmer som skal afvikles på simulatoren. Disse programmer er skrevet i
'C' og oversat til et format som simulatoren kan læse.

Besvarelsen skal indeholde:

* En kort rapport (20%)
* Implementationen af simulerings-funktionen (40%)
* Dokumentation for kørsel af programmer på simulatoren (40%)

Hvis de udleverede programmer ikke kan bringes til at køre på simulatoren, skal det klart
fremgå af besvarelsen og der skal gøres et systematisk forsøg på at klarlægge hvilke
instruktioner der simuleres korrekt, og hvilke der ikke simuleres korrekt.

Bemærk at A6 vil bygge videre på jeres løsning af A5. Der vil ikke blive udleveret
en vejledende løsning af A5 der kan være udgangspunkt for A6.

## Udleverede filer

Der udleveres følgende filer som udgør den ufærdige simulator:

~~~
main.c: - hovedprogram
memory.c, memory.h: - simulering af computerens lager
assembly.c, assembly.h: - håndtering af assembler kildetekst
read_exec.c, read_exec.h: - indlæsning af risc-v eksekverbar
simulate.h: - header fil der erklærer funktionen simulate() som skal implementeres
~~~

Og fire test-programmer. Disse programmer findes dels som C-kildetekst og dels
som ".dis" filer. Sidstnævnte er det format, den udleverede simulator kan
indlæse:

~~~
hello.c, hello.dis: - det klassiske "hello world" .. sådan cirka.
echo.c, echo.dis: - et program der giver et ekko af input på output
fib.c, fib.dis: - beregning af fibonacci tal.
erat.c, erat.dis: - beregning af primtal mindre end 1000000
~~~

Det beskrives nedenfor hvordan filer på ".dis"-format kan laves ud fra C-kildetekst

## Instruktioner

Den autoritative reference for instruktionernes indkodning er her:

~~~
https://riscv.org/wp-content/uploads/2017/05/riscv-spec-v2.2.pdf
~~~

Simulatoren skal håndtere RISC-V 32 bit base instruktionssæt (I) og udvidelsen
for multiplikation (M)

Dog ikke følgende instruktioner: 

~~~
ebreak, fence, fence.i, CSRRW, CSRRS, CSRRC, CSRRWI, CSRRSI og CSRRCI.
~~~


## Systemkald

Systemkald udføres med "ecall" instruktionen. Værdien i A7 angiver hvilket systemkald der
er tale om. Der skal implementeres følgende fire systemkald.

~~~
Kald:           Effekt:
1               returner "getchar()" i A7
2               udfør "putchar(c)", hvor c tages fra A6
3 og 93         afslut simulationen
~~~

## Simulation

Den udleverede (ufærdige) simulator tager en ".dis" fil som første argument.
Som andet argument kan angives logning:

~~~
./sim myprog.dis                   # ingen logning
./sim myprog.dis -l log            # logning for indlæsning af dis-fil og for hver eneste instruktion
./sim myprog.dis -s log            # logning af afsluttende opsamling (antal instruktioner, simulationstid)
~~~

Simulatoren forventer at det simulerede program erklærer symbolet "_start" og vil
starte simulationen ved addressen på dette symbol. Programmer lavet som beskrevet
nedenfor vil automatisk opfylde dette krav.

## Output format

I kan frit bestemme hvad I vil udskrive for hver instruktion til logfilen.
Vi anbefaler at skrive noget der kan hjælpe jer med fejlfinding :-)

Til inspiration er her et eksempel på muligt output format (mindre kan gøre det):

~~~
   144 =>  10098 : 00044503     lbu      a0,0(s0)                                           R[10] <- 6e
   145     1009c : fe051ae3     bnez     a0,10090         <main+0x1c>                   {T}
   146 =>  10090 : 00140413     addi     s0,s0,1                                            R[ 8] <- 119a2
   147     10094 : 4d8000ef     jal      ra,1056c         <outp>                            R[ 1] <- 10098
   148 =>  1056c : 00200893     li       a7,2                                               R[17] <- 2
   149     10570 : 00a00833     add      a6,zero,a0                                         R[16] <- 6e
~~~

Symbolet "=>" indikerer at der er hoppet til denne instruktion.
Symbolet "{T}" indikerer et taget betinget hop.
Resten skulle gerne være selvforklarende.

Den disassemblerede kode er taget fra ".dis" filen.

## Fra "C" til ".dis" filer

Nedenstående er kun relevant, hvis du ønsker at afvikle dine egne "C"-programmer
på simulatoren, eller ønsker at modificere de udleverede testprogrammer. Ellers kan
de udleverede ".dis"-filer bruges.

Vi bruger en krydsoversætter til at frembringe ".dis" filer.

### Krydsoversætter

For at kunne oversætte fra 'C' til RISC-V er det nødvendigt at installere en kryds-oversætter.

Til Linux har jeg brugt den nyeste herfra:

~~~
https://github.com/stnolting/riscv-gcc-prebuilt
~~~

(brug en der er rettet mod 32-bit risv, ikke 64-bit)

Efter installation er krydsoversætteren tilgængelig som "/opt/riscv/bin/riscv32-unknown-elf-gcc"
på min maskine. Du kan under installationsprocessen vælge en anden sti. I det følgende
angiver jeg kommandoerne svarende til at installationskataloget er i PATH. 
Husk at tage højde for det, hvis du installerer værktøjerne anderledes.

### Brug af oversætteren

Til brug i opgaven udleverer vi et par funktioner til I/O og til at terminere programmet.
Disse funktioner finder du i filen "lib.c" som skal oversættes og linkes med. Det er vores minimale
"standardbibliotek". Vi kan ikke bruge det rigtige standardbibliotek med vores simple simulator
(så ting som printf, fopen etc virker ikke).

For at oversætte "test.c" (og "lib.c"):

~~~
riscv32-unknown-elf-gcc -march=rv32im -mabi=ilp32 -O1 test.c lib.c -static -nostartfiles -nostdlib -o test.riscv
~~~

Denne kommando laver en risc-v eksekverbar med navnet "test.riscv". Du kan evt vælge et andet
navn.

### Forberedelse af simulation

Den udleverede kode til simulatoren kan ikke læse en eksekverbar fil direkte.
Den eksekverbare skal først dis-assembleres til et format der både kan give simulatoren alt indhold
i lageret (også statisk data) og en læsevenlig dis-assemblering af hver instruktion.

Denne fil (som vi kalder en ".dis"-fil) laves med et værktøj der hedder "objdump" således:

~~~
riscv32-unknown-elf-objdump -s -w test.riscv > test.dis
riscv32-unknown-elf-objdump -S test.riscv >> test.dis
~~~

Vi udleverer en Makefile som kan drive oversættelsen - men bemærk at den skal tilpasses
til den lokale installation, før den kan bruges.

## Gode råd

Bare brug integers til så meget som muligt. Der er ikke brug for f.eks. "struct" erklæringer.
Læs op på hvordan man i C bruger skifte operationer og bitvis and/or til at "fiske" bitfelter ud af tal.

Vil du have simplere .dis filer? I kommandoen til krydsoversætteren udskiftes "-O1" med "-Os".

Vil du lave dine egne .dis filer fra en assembler fil? I kommandoen til krydsoversætteren
udskiftes C-filerne med din egen assembler fil. Den skal have suffix ".s" og indledes med

~~~
    .globl _start
_start:
~~~
