# Øvelser til 12. december

## Opsamling

Brug tid til at afklare spørgsmål A5.

Overskydende øvelser fra forrige uge.

## Øvelser i afviklingsplot

(se note her: https://github.com/diku-compSys/compSys-e2022-internal/blob/main/material/Afviklingsplot/plot.md)

### Opgave 1

Opstil et afviklingsplot for en simpel 5-trins pipeline som beskrevet i COD (og i begyndelsen af noten) for to
iterationer af følgende programstump:

~~~
Loop:
    addi x4,x4,1
    slli x11,x4,5
    add  x11,x16,x11
    lw	 x11,8(x11)
    slli x12,x4,2
    add	 x12,x17,x12
    sw   x11,0(x12)
    bge  x9,x4,Loop
~~~

### Opgave 2

Opstil et afviklingsplot for en 5-trins 2-vejs superskalar pipeline som beskrevet i noten for to
iterationer af programstumpen fra opgave 1.

Hvis der er tvivlspørgsmål undervejs vælges en mulig fortolkning - gå ikke i stå.
Anfør eventuelle antagelser om mikroarkitekturen.
