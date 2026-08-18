    ORG $0100

start:
    ld b,4

loop:
    ld c,9
    ld de,msg
    call 5
    djnz loop

    ld c,0
    call 5
    halt

msg:
    db "Hello", '$'