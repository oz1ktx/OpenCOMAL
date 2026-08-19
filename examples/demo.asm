; OpenCOMAL Z80 demo program
; Prints a message via CP/M BDOS (function 9), then exits (function 0)

        ORG 0100h

START:  LD DE,MSG
        LD H, 43
        LD C,9
        CALL 5

        LD C,0
        CALL 5

MSG:    DB 'HELLO FROM OPENCOMAL Z80 DEMO$'
