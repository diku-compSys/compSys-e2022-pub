
# Løsninger til mandagens øvelsesopgaver.
Du bør læse [Finns noter](https://github.com/diku-compSys/compSys-e2022-pub/blob/main/resources/Afviklingsplot/plot.md), samt forsøge at løse opgaverne, før du orienterer dig i løsningen.

## 1.1
Først og fremmest skal vi forstå hvad koden gør, specielt linjen
```
*a++ = *b++
```
Her tildeles værdien af den integer, der peges på af `q`, til den integer, der peges på af `p`. Derefter øges pegerne `q` og `p` med én.

Dernæst kan vi skrive koden ved et simpelt loop:
~~~
loop:
    bge   x10, x12, end
    lw    x14, 0(x11)
    addi  x11, x11, 4
    sw    x14, 0(x10)
    addi  x10, x10, 4
    jal   loop
 end:
~~~
Bemærk hvordan at vi _ikke_ bruger instruktionen `blt`, men i stedet foretager vores hop såfremt vores løkkebetingelse er falsk. Bemærk dernæst at vi ved at benytte overstående rækkefølge af den første `addi` og den efterfølgende `sw` gør at vi undgår to stalls i opgaven nedenfor. Hvorfor?

## 1.2

Vi laver afviklingsplot i en simpel 5-trins pipeline med trinene givet ved `If, Id, Ex, Mem, Wb`. Vi antager yderligere fuld forwarding.

```
                        0   1   2   3   4   5   6   7   8   9   10  11  12  13  14  15
bge   x10, x12, end     If  Id  Ex  Mem Wb
lw    x14, 0(x11)           If  Id  Ex  Mem Wb
addi  x11, x11, 4               If  Id  Ex  Mem Wb
sw    x14, 0(x10)                   If  Id  Ex  Mem Wb
addi  x10, x10, 4                       If  Id  Ex  Mem Wb
jal   x0, loop                              If  Id  Ex  Mem  Wb
bge   x10, x12, end                             If  Id  Ex  Mem Wb
lw    x14, 0(x11)                                   If  Id  Ex  Mem Wb
addi  x11, x11, 4                                       If  Id  Ex  Mem Wb
sw    x14, 0(x10)                                           If  Id  Ex  Mem Wb
addi  x10, x10, 4                                               If  Id  Ex  Mem Wb
jal   loop                                                          If  Id  Ex  Mem  Wb
```
Her bemærkes at resultatet af `addi` kan forwardes fra instruktionens `ex` trin, mens at resultatet af `lw` kan forwardes fra instruktionens `mem` trin.


## 1.3
Vi antager en 2-vejs superskalar in-order maskine med fuld forwarding. Dernæst antager vi at betingede hop ikke forudsiges ikke-taget, samt at det tager 3 cykler at tilgå cachen (som foregår i `Fe` og `Mm`-trinene. Hvorfor?). Vi har derfor følgende resource-indeling:
```
load:  "Fa Fb Fc De Ag Ma Mb Mc Wb"
store: "Fa Fb Fc De Ag Ma Mb Mc"
andre: "Fa Fb Fc De Ex Wb"

ressourcer: F(a|b|c):2, De:2, Ex:2, Ag:1, M(a|b|c):1, Wb:2
```
som beskrevet i [Superskalar mikroarkitektur](https://github.com/diku-compSys/compSys-e2022-pub/blob/main/resources/Afviklingsplot/superskalar.md).

```
                        0   1   2   3   4   5   6   7   8   9   10  11  12  13  14  15  16
bge   x10, x12, end     Fa  Fb  Fc  De  Ex  Wb
lw    x14, 0(x11)       Fa  Fb  Fc  De  Ag  Ma  Mb  Mc  Wb
addi  x11, x11, 4           Fa  Fb  Fc  De  Ex  Wb
sw    x14, 0(x10)           Fa  Fb  Fc  De  Ag  >>  >>  Ma  Mb  Mc
addi  x10, x10, 4               Fa  Fb  Fc  De  Ex  Wb
jal   loop                      Fa  Fb  Fc  De  Ex  Wb
bge   x10, x12, end                 Fa  Fb  Fc  De  >>  Ex  Wb                            # x10 bliver først produceret i Wb jf. Finns note.
lw    x14, 0(x11)                   Fa  Fb  Fc  De  Ag  >>  Ma  Mb  Mc  Wb
addi  x11, x11, 4                       Fa  Fb  Fc  De  Ex  Wb
sw    x14, 0(x10)                       Fa  Fb  Fc  De  Ag  >>  >>  >>  Ma  Mb  Mc
addi  x10, x10, 4                           Fa  Fb  Fc  De  Ex  Wb
jal   loop                                  Fa  Fb  Fc  De  Ex  Wb
bge   x10, x12, end                             Fa  Fb  Fc  De  >>  Ex  Wb
```
Prøv eventuelt at gennemføre opgaven en gang til hvor du bytter om på rækkefølgen af den første `addi` samt den efterfølgende `sw`. Hvor mange stalls får du så? Du kan også prøve at gennemføre opgaven igen, denne gang hvor du antager at branches forudsiges taget. Hvor mange stalls får du nu?

## 1.4
Vi antager en 2-vejs superskalar out-of-order maskine med fuld forwarding og 2 instruktioner i dataflow-sektionen. Dernæst antager vi at betingede hop forudsiges ikke-taget, samt at det tager 3 cykler at tilgå cachen. Vi har derfor følgende resource-indeling:
```
ALU-op: Fa Fb Fc De Fu Al Rn Qu pk rd ex wb Ca Cb
branch: Fa Fb Fc De Fu Al Rn Qu pk rd ex Ca Cb

load:  Fa Fb Fc De Fu Al Rn Qu pk rd ag ma mb mc wb Ca Cb
store: Fa Fb Fc De Fu Al Rn Qu pk rd ag ma mb mc -- Ca Cb   // addresse
       -                    Qu -- -- -- -- pk rd st Ca Cb   // data

inorder: Fa, Fb, Fc, De, Fu, Al, Rn, Qu, Ca, Cb
outoforder: pk, rd, ex, wb

Resourcer: Fa:2, Fb:2, Fc:2, De:2, Fu:2, Al:2, Rn:2 [Qu-Ca]:2, Ca:2, Cb:2
```
som beskrevet i [Dynamisk Skedulering (Out-of-order execution)](https://github.com/diku-compSys/compSys-e2022-pub/blob/main/resources/Afviklingsplot/ooo.md).

```
                        0   1   2   3   4   5   6   7   8   9   10  11  12  13  14  15  16  17  18  19
bge   x10, x12, end     Fa  Fb  Fc  De  Fu  Al  Rn  Qu  pk  rd  ex  Ca  Cb
lw    x14, 0(x11)       Fa  Fb  Fc  De  Fu  Al  Rn  Qu  pk  rd  ag  ma  mb  mc  wb  Ca  Cb
addi  x11, x11, 4           Fa  Fb  Fc  De  Fu  Al  Rn  Qu  pk  rd  ex  wb  --  --  Ca  Cb
sw    x14, 0(x10)           Fa  Fb  Fc  De  Fu  Al  Rn  Qu  --  --  --  --  --  pk  rd  ag  ma  mb  mc  Ca  Cb                    # venter på `mc` for `lw` ovenfor
-                                                       Qu  --  --  --  --  --  --  --  --  --  pk  rd  st
addi  x10, x10, 4               Fa  Fb  Fc  De  Fu  Al  Rn  Qu  pk  rd  ex  wb  --  --  --  --  --  --  Ca  Cb
jal   loop                      Fa  Fb  Fc  De  Fu  Al  Rn  Qu  pk  rd  ex  --  --  --  --  --  --  --  --  Ca  Cb
bge   x10, x12, end                 Fa  Fb  Fc  De  Fu  Al  Rn  Qu  --  --  pk  rd  ex  --  --  --  --  --  Ca  Cb
lw    x14, 0(x11)                   Fa  Fb  Fc  De  Fu  Al  Rn  Qu  --  pk  rd  ag  ma  mb  mc  wb  --  --  --  Ca  Cb
addi  x11, x11, 4                       Fa  Fb  Fc  De  Fu  Al  Rn  Qu  pk  rd  ex  wb  --  --  --  --  --  --  --  Ca  Cb
sw    x14, 0(x10)                       Fa  Fb  Fc  De  Fu  Al  Rn  Qu  --  --  --  --  --  --  pk  rd  ag  ma  mb  mc  Ca  Cb
-                                                                   Qu  --  --  --  --  --  --  --  --  --  --  pk  rd  st
addi  x10, x10, 4                           Fa  Fb  Fc  De  Fu  Al  Rn  Qu  pk  rd  ex  wb  --  --  --  --  --  --  --  Ca  Cb
jal   loop                                  Fa  Fb  Fc  De  Fu  Al  Rn  Qu  pk  rd  ex  --  --  --  --  --  --  --  --  --  Ca  Cb
bge   x10, x12, end                             Fa  Fb  Fc  De  Fu  Al  Rn  Qu  --  --  pk  rd  ex  --  --  --  --  --  --  Ca  Cb
```
Hvordan vil det se ud hvis maskinen var 4-vejs superskalar out-of-order? Hvad med 8?
