/**
    Tabela de Instruções opcode
*/
enum opCode {
    lw = '100011',
    sw = '101011',
    lb = '100000',
    sb = '101000',
    beq = '000100',
    bne = '000101',
    slt = '000000',
    j = '000010',
    jal = '000011',
    jr = '000000'
}