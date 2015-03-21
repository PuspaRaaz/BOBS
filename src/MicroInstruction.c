#include "MicroInstruction.h"

void get_token(){
    char* temp = token;
    //skip over spaces
    while(isspace(*input) && *input) ++input;
    //skip over new lines
    while (*input == '\n') {
        input += 2;
         while(isspace(*input) && *input) ++input;
    }
    //end of statement
    if(*input == '\0'){
        *token = '\0';
        token_t = EOS;
    }
    //alphabets
    else if (isalpha(*input)){
        while(isalpha(*input)){
            *temp++ = *input++;
            token_t = ALPHA;
        }

        while (isdigit(*input)){
            *temp++ = *input++;
            token_t = ALPHANUM;
        }

        if (*input == ':'){
            token_t = LABEL;
            input++;
        }

        *temp = '\0';
        if (strlen(token) == 1 && strchr("ABCDEHLMabcdehlm",*token))
            token_t = REGMEM;
    }

    //numeric values
    else if (isxdigit(*input)){
        while(isxdigit(*input)){
            *temp++ = *input++;
            token_t = NUMBER;
        }
        *temp = '\0';
    }
    //anything other than that
    else if (*input == ','){
        *temp++ = *input++;
        token_t = DELIMETER;

    }
    else{
        *token = '\0';
        token_t = INVALID;
    }
}

void Increase_O_pos(char* instruction){
    int i;
    if (strstr(" ADC ADD ANA CMA CMC CMP DAA DAD DCR DCX DI EI HLT INR INX LDAX MOV NOP ORA PCHL POP PUSH RAL RAR RC RET RIM RLC RM RNC RNZ RP RPE RPO RRC RST SBB SIM SPHL STAX STC SUB XCHG XRA XYHL", instruction)) Op_count += 1;
    if (strstr(" ACI ADI ANI CPI IN MVI ORI OUT SBI SUI XRI ", instruction)) Op_count += 2;
    if (strstr(" CALL CC CM CNC CNZ CP CPE CPO CZ JC JM JMP JNC JNZ JP JPE JPO JZ LDA LHLD LXI SHLD STA ",instruction)) Op_count += 3;
}

int Op_val(char in){
    switch (in){
        case 'A': return 0x7; break;
        case 'B': return 0x0; break;
        case 'C': return 0x1; break;
        case 'D': return 0x2; break;
        case 'E': return 0x3; break;
        case 'H': return 0x4; break;
        case 'L': return 0x5; break;
        case 'M': return 0x6; break;
    }
}

int to_opcode(){
    int temp;
    char op1 , op2;

    while(token_t != EOS){
        get_token();

        if(!strcasecmp("ACI",token)){
            Append(0xCE);
            get_token();
            if (token_t != NUMBER){
                ThrowError("ACI needs an Immediate Value",Op_count);
                return -1; // -1 for error
            }
            else{
                temp = (int) strtol(token,NULL,16);
                Append(temp);
            }
        }

        else if (!strcasecmp("ADC",token)){
            get_token();
            if (token_t != REGMEM){
                ThrowError("ADC requires a REG/MEM", Op_count);
                return -1;
            }
            op1 = *token;
            temp = 0x88 + Op_val(op1);
            Append(temp);
        }

        else if (!strcasecmp("ADD",token)){
             get_token();
            if (token_t != REGMEM){
                ThrowError("ADC requires a REG/MEM", Op_count);
                return -1;
            }
            op1 = *token;
            temp = 0x80 + Op_val(op1);
            Append(temp);
        }

        else if (!strcasecmp("ADI",token)){
            Append(0xC6);
            get_token();
            if (token_t != NUMBER){
                ThrowError("ADI needs an Immediate Value",Op_count);
                return -1; // -1 for error
            }
            else{
                temp = (int) strtol(token,NULL,16);
                Append(temp);
            }
        }

        else if (!strcasecmp("ANA",token)){
             get_token();
            if (token_t != REGMEM){
                ThrowError("ANA requires a REG/MEM", Op_count);
                return -1;
            }
            op1 = *token;
            temp = 0xA0 + Op_val(op1);
            Append(temp);
        }

        else if (!strcasecmp("ANI",token)){
            Append(0xE6);
            get_token();
            if (token_t != NUMBER){
                ThrowError("ANI needs an Immediate Value",Op_count);
                return -1; // -1 for error
            }
            else{
                temp = (int) strtol(token,NULL,16);
                Append(temp);
            }
        }

        else if (!strcasecmp("CALL",token)){
            Append(0xCD);
            get_token();
            if (!(token_t != ALPHA || token_t != ALPHANUM)){
                ThrowError("Label needed",Op_count);
                return -1; // -1 for error
            }
            else{
                if((temp = Find_Label(token)) == -1){
                    ThrowError("Label not found",Op_count);
                    return -1;
                }
                else{
                    Append(temp & 0xFF);
                    Append((temp & 0xFF00)>>8);
                }
            }
        }

        else if (!strcasecmp("CC",token)){
            Append(0xDC);
            get_token();
            if (!(token_t != ALPHA || token_t != ALPHANUM)){
                ThrowError("Label needed",Op_count);
                return -1; // -1 for error
            }
            else{
                if((temp = Find_Label(token)) == -1){
                    ThrowError("Label not found",Op_count);
                    return -1;
                }
                else{
                    Append(temp & 0xFF);
                    Append((temp & 0xFF00)>>8);
                }
            }
        }

        else if (!strcasecmp("CM",token)){
            Append(0xFC);
            get_token();
            if (!(token_t != ALPHA || token_t != ALPHANUM)){
                ThrowError("Label needed",Op_count);
                return -1; // -1 for error
            }
            else{
                if((temp = Find_Label(token)) == -1){
                    ThrowError("Label not found",Op_count);
                    return -1;
                }
                else{
                    Append(temp & 0xFF);
                    Append((temp & 0xFF00)>>8);
                }
            }
        }

        else if (!strcasecmp("CMA",token)){
            Append(0x2f);
        }

        else if (!strcasecmp("CMC",token)){
            Append(0x3f);
        }

        else if (!strcasecmp("CMP",token)){
             get_token();
            if (token_t != REGMEM){
                ThrowError("CMP requires a REG/MEM", Op_count);
                return -1;
            }
            op1 = *token;
            temp = 0xB8 + Op_val(op1);
            Append(temp);
        }

        else if (!strcasecmp("CNC",token)){
            Append(0xD4);
            get_token();
            if (!(token_t != ALPHA || token_t != ALPHANUM)){
                ThrowError("Label needed",Op_count);
                return -1; // -1 for error
            }
            else{
                if((temp = Find_Label(token)) == -1){
                    ThrowError("Label not found",Op_count);
                    return -1;
                }
                else{
                    Append(temp & 0xFF);
                    Append((temp & 0xFF00)>>8);
                }
            }
        }

        else if (!strcasecmp("CNZ",token)){
            Append(0xC4);
            get_token();
            if (!(token_t != ALPHA || token_t != ALPHANUM)){
                ThrowError("Label needed",Op_count);
                return -1; // -1 for error
            }
            else{
                if((temp = Find_Label(token)) == -1){
                    ThrowError("Label not found",Op_count);
                    return -1;
                }
                else{
                    Append(temp & 0xFF);
                    Append((temp & 0xFF00)>>8);
                }
            }
        }

        else if (!strcasecmp("CP",token)){
            Append(0xF4);
            get_token();
            if (!(token_t != ALPHA || token_t != ALPHANUM)){
                ThrowError("Label needed",Op_count);
                return -1; // -1 for error
            }
            else{
                if((temp = Find_Label(token)) == -1){
                    ThrowError("Label not found",Op_count);
                    return -1;
                }
                else{
                    Append(temp & 0xFF);
                    Append((temp & 0xFF00)>>8);
                }
            }
        }

        else if (!strcasecmp("CPE",token)){
            Append(0xEC);
            get_token();
            if (!(token_t != ALPHA || token_t != ALPHANUM)){
                ThrowError("Label needed",Op_count);
                return -1; // -1 for error
            }
            else{
                if((temp = Find_Label(token)) == -1){
                    ThrowError("Label not found",Op_count);
                    return -1;
                }
                else{
                    Append(temp & 0xFF);
                    Append((temp & 0xFF00)>>8);
                }
            }
        }

        else if (!strcasecmp("CPI",token)){
            Append(0xFE);
            get_token();
            if (token_t != NUMBER){
                ThrowError("ADI needs an Immediate Value",Op_count);
                return -1; // -1 for error
            }
            else{
                temp = (int) strtol(token,NULL,16);
                Append(temp);
            }
        }

        else if (!strcasecmp("CPO",token)){
            Append(0xE4);
            get_token();
            if (!(token_t != ALPHA || token_t != ALPHANUM)){
                ThrowError("Label needed",Op_count);
                return -1; // -1 for error
            }
            else{
                if((temp = Find_Label(token)) == -1){
                    ThrowError("Label not found",Op_count);
                    return -1;
                }
                else{
                    Append(temp & 0xFF);
                    Append((temp & 0xFF00)>>8);
                }
            }
        }

        else if (!strcasecmp("CZ",token)){
            Append(0xCC);
            get_token();
            if (!(token_t != ALPHA || token_t != ALPHANUM)){
                ThrowError("Label needed",Op_count);
                return -1; // -1 for error
            }
            else{
                if((temp = Find_Label(token)) == -1){
                    ThrowError("Label not found",Op_count);
                    return -1;
                }
                else{
                    Append(temp & 0xFF);
                    Append((temp & 0xFF00)>>8);
                }
            }
        }

        else if (!strcasecmp("DAA",token)){
            Append(0x27);
        }

        else if (!strcasecmp("DAD",token)){
            get_token();
            if (!strstr(" B D H SP ",token)){
                ThrowError("NOT a register pair",Op_count);
                return -1;
            }
            else{
                switch(*token){
                    case 'B': Append(0x09);break;
                    case 'D': Append(0x19);break;
                    case 'H': Append(0x29);break;
                    default: Append(0x39);break;
                }
            }
        }

        else if (!strcasecmp("DCR",token)){
             get_token();
            if (token_t != REGMEM){
                ThrowError("DCR requires a REG/MEM", Op_count);
                return -1;
            }
            op1 = *token;
            temp = 0x05 + Op_val(op1)*8;
            Append(temp);
        }

        else if (!strcasecmp("DCX",token)){
            get_token();
            if (!strstr(" B D H SP ",token)){
                ThrowError("NOT a register pair",Op_count);
                return -1;
            }
            else{
                switch(*token){
                    case 'B': Append(0x0B);break;
                    case 'D': Append(0x1B);break;
                    case 'H': Append(0x2B);break;
                    default:  Append(0x3B);break;
                }
            }
        }

        else if (!strcasecmp("DI",token)){
            Append(0xF3);
        }

        else if (!strcasecmp("EI",token)){
            Append(0xFB);
        }

        else if (!strcasecmp("HLT",token)){
            Append(0x76);
        }

        else if (!strcasecmp("IN",token)){
            Append(0xDB);
            get_token();
            if (token_t != NUMBER){
                ThrowError("IN needs an Immediate Value",Op_count);
                return -1; // -1 for error
            }
            else{
                temp = (int) strtol(token,NULL,16);
                Append(temp);
            }
        }

        else if (!strcasecmp("INR",token)){
             get_token();
            if (token_t != REGMEM){
                ThrowError("INR requires a REG/MEM", Op_count);
                return -1;
            }
            op1 = *token;
            temp = 0x04 + Op_val(op1)*8;
            Append(temp);
        }

        else if (!strcasecmp("INX",token)){
            get_token();
            if (!strstr(" B D H SP ",token)){
                ThrowError("NOT a register pair",Op_count);
                return -1;
            }
            else{
                switch(*token){
                    case 'B': Append(0x03);break;
                    case 'D': Append(0x13);break;
                    case 'H': Append(0x23);break;
                    default:  Append(0x33);break;
                }
            }
        }

        else if (!strcasecmp("JC",token)){
            Append(0xDA);
            get_token();
            if (!(token_t != ALPHA || token_t != ALPHANUM)){
                ThrowError("Label needed",Op_count);
                return -1; // -1 for error
            }
            else{
                if((temp = Find_Label(token)) == -1){
                    ThrowError("Label not found",Op_count);
                    return -1;
                }
                else{
                    Append(temp & 0xFF);
                    Append((temp & 0xFF00)>>8);
                }
            }
        }

        else if (!strcasecmp("JM",token)){
            Append(0xFA);
            get_token();
            if (!(token_t != ALPHA || token_t != ALPHANUM)){
                ThrowError("Label needed",Op_count);
                return -1; // -1 for error
            }
            else{
                if((temp = Find_Label(token)) == -1){
                    ThrowError("Label not found",Op_count);
                    return -1;
                }
                else{
                    Append(temp & 0xFF);
                    Append((temp & 0xFF00)>>8);
                }
            }
        }

        else if (!strcasecmp("JMP",token)){
            Append(0xC3);
            get_token();
            if (!(token_t != ALPHA || token_t != ALPHANUM)){
                ThrowError("Label needed",Op_count);
                return -1; // -1 for error
            }
            else{
                if((temp = Find_Label(token)) == -1){
                    ThrowError("Label not found",Op_count);
                    return -1;
                }
                else{
                    Append(temp & 0xFF);
                    Append((temp & 0xFF00)>>8);
                }
            }
        }

        else if (!strcasecmp("JNC",token)){
            Append(0xD2);
            get_token();
            if (!(token_t != ALPHA || token_t != ALPHANUM)){
                ThrowError("Label needed",Op_count);
                return -1; // -1 for error
            }
            else{
                if((temp = Find_Label(token)) == -1){
                    ThrowError("Label not found",Op_count);
                    return -1;
                }
                else{
                    Append(temp & 0xFF);
                    Append((temp & 0xFF00)>>8);
                }
            }
        }

        else if (!strcasecmp("JNZ",token)){
            Append(0xC2);
            get_token();
            if (!(token_t != ALPHA || token_t != ALPHANUM)){
                ThrowError("Label needed",Op_count);
                return -1; // -1 for error
            }
            else{
                if((temp = Find_Label(token)) == -1){
                    ThrowError("Label not found",Op_count);
                    return -1;
                }
                else{
                    Append(temp & 0xFF);
                    Append((temp & 0xFF00)>>8);
                }
            }
        }

        else if (!strcasecmp("JP",token)){
            Append(0xF2);
            get_token();
            if (!(token_t != ALPHA || token_t != ALPHANUM)){
                ThrowError("Label needed",Op_count);
                return -1; // -1 for error
            }
            else{
                if((temp = Find_Label(token)) == -1){
                    ThrowError("Label not found",Op_count);
                    return -1;
                }
                else{
                    Append(temp & 0xFF);
                    Append((temp & 0xFF00)>>8);
                }
            }
        }

        else if (!strcasecmp("JPE",token)){
            Append(0xEA);
            get_token();
            if (!(token_t != ALPHA || token_t != ALPHANUM)){
                ThrowError("Label needed",Op_count);
                return -1; // -1 for error
            }
            else{
                if((temp = Find_Label(token)) == -1){
                    ThrowError("Label not found",Op_count);
                    return -1;
                }
                else{
                    Append(temp & 0xFF);
                    Append((temp & 0xFF00)>>8);
                }
            }
        }

        else if (!strcasecmp("JPO",token)){
            Append(0xE2);
            get_token();
            if (!(token_t != ALPHA || token_t != ALPHANUM)){
                ThrowError("Label needed",Op_count);
                return -1; // -1 for error
            }
            else{
                if((temp = Find_Label(token)) == -1){
                    ThrowError("Label not found",Op_count);
                    return -1;
                }
                else{
                    Append(temp & 0xFF);
                    Append((temp & 0xFF00)>>8);
                }
            }
        }

        else if (!strcasecmp("JZ",token)){
            Append(0xCA);
            get_token();
            if (!(token_t != ALPHA || token_t != ALPHANUM)){
                ThrowError("Label needed",Op_count);
                return -1; // -1 for error
            }
            else{
                if((temp = Find_Label(token)) == -1){
                    ThrowError("Label not found",Op_count);
                    return -1;
                }
                else{
                    Append(temp & 0xFF);
                    Append((temp & 0xFF00)>>8);
                }
            }
        }

        else if (!strcasecmp("LDA",token)){
            Append(0x3A);
            get_token();
            if (token_t != NUMBER){
                ThrowError("not a memory location",Op_count);
                return -1;
            }
            else{
                temp = (int) strtol(token,NULL,16);
                Append(temp & 0xFF);
                Append((temp & 0xFF00)>>8);
            }

        }

        else if (!strcasecmp("LDAX",token)){
            get_token();
            if (!strstr(" B D b d ",token)){
                ThrowError("NOT a register pair B or D",Op_count);
                return -1;
            }
            else{
                switch(*token){
                    case 'B': Append(0x0A);break;
                    case 'D': Append(0x1A);break;
                }
            }
        }

        else if (!strcasecmp("LHLD",token)){
            Append(0x2A);
            get_token();
            if (token_t != NUMBER){
                ThrowError("not a memory location",Op_count);
                return -1;
            }
            else{
                temp = (int) strtol(token,NULL,16);
                Append(temp & 0xFF);
                Append((temp & 0xFF00) >> 8);
            }

        }

        else if (!strcasecmp("LXI",token)){
            get_token();
            if (!strstr(" B D H SP ",token)){
                ThrowError("NOT a register pair",Op_count);
                return -1;
            }
            else{
                switch(*token){
                    case 'B': Append(0x01);break;
                    case 'D': Append(0x11);break;
                    case 'H': Append(0x21);break;
                    default:  Append(0x31);break;
                }
            }

            get_token();
            if(token_t != DELIMETER){
                ThrowError("Missing a comma(?)",Op_count);
                return -1;
            }
            get_token();
            temp = (int) strtol(token,NULL,16);

            Append(temp & 0xFF);
            Append((temp & 0xFF00)>>8);

        }

        else if (!strcasecmp("MOV",token)){
            get_token();
            if (token_t != REGMEM){
                ThrowError("NOT a REG/MEM", Op_count);
                return -1;
            }
            else{
                op1 = *token;
                get_token();
                if (token_t != DELIMETER)
                    ThrowError("Missing a comma(?)", Op_count);
                else{
                    get_token();
                    if (token_t != REGMEM){
                        ThrowError("NOT a REG/MEM", Op_count);
                        return -1;
                    }
                    op2 = *token;
                }
            }

            if(op1 == 'A'){
                temp = 0x78 + Op_val(op2);
                Append(temp);
            }

            else if(op1 == 'B'){
                temp = 0x40 + Op_val(op2);
                Append(temp);
            }

            else if(op1 == 'C'){
                temp = 0x48 + Op_val(op2);
                Append(temp);
            }

            else if(op1 == 'D'){
                temp = 0x50 + Op_val(op2);
                Append(temp);
            }

            else if(op1 == 'E'){
                temp = 0x58 + Op_val(op2);
                Append(temp);
            }

            else if(op1 == 'H'){
                temp = 0x60 + Op_val(op2);
                Append(temp);
            }

            else if(op1 == 'L'){
                temp = 0x68 + Op_val(op2);
                Append(temp);
            }

            else if(op1 == 'M'){
                if (op2 == op1){
                    ThrowError("Cannot move M to M", Op_count);
                    return -1;
                }

                temp = 0x70 + Op_val(op2);
                Append(temp);
            }

        }

        else if (!strcasecmp("MVI",token)){
            get_token();
            if (token_t != REGMEM){
                ThrowError("MVI needs an REG/MEM",Op_count);
                return -1; // -1 for error
            }
            else{
                op1 = *token;
                get_token();
                if (token_t != DELIMETER){
                    ThrowError("Missing a comma(?)", Op_count);
                    return -1;
                }
                else{
                    get_token();
                    if (token_t != NUMBER){
                        ThrowError("MVI needs an Immediate value", Op_count);
                        return -1;
                    }
                }
                temp = 0x06 + Op_val(op1)*8;
                Append(temp);

                temp = (int) strtol(token,NULL,16);
                Append(temp);
            }
        }

        else if (!strcasecmp("NOP",token)){
            Append(0x00);
        }

        else if (!strcasecmp("ORA",token)){
            get_token();
            if (token_t != REGMEM){
                ThrowError("ORA requires a REG/MEM", Op_count);
                return -1;
            }
            op1 = *token;
            temp = 0xB0 + Op_val(op1);
            Append(temp);
        }

        else if (!strcasecmp("ORI",token)){
            Append(0xF6);
            get_token();
            if (token_t != NUMBER){
                ThrowError("ORI needs an Immediate Value",Op_count);
                return -1; // -1 for error
            }
            else{
                temp = (int) strtol(token,NULL,16);
                Append(temp);
            }
        }

        else if (!strcasecmp("OUT",token)){
            Append(0xD3);
            get_token();
            if (token_t != NUMBER){
                ThrowError("OUT needs an Immediate Value",Op_count);
                return -1; // -1 for error
            }
            else{
                temp = (int) strtol(token,NULL,16);
                Append(temp);
            }
        }

        else if (!strcasecmp("PCHL",token)){
            Append(0xE9);
        }

        else if (!strcasecmp("POP",token)){
            get_token();
            if (!strstr(" B D H PSW ",token)){
                ThrowError("NOT a register pair",Op_count);
                return -1;
            }

            switch(*token){
                case 'B': Append(0xC1);break;
                case 'D': Append(0xD1);break;
                case 'H': Append(0xE1);break;
                default:  Append(0xF1);break;
            }

        }

        else if (!strcasecmp("PUSH",token)){
            get_token();
            if (!strstr(" B D H PSW ",token)){
                ThrowError("NOT a register pair",Op_count);
                return -1;
            }

            switch(*token){
                case 'B': Append(0xC5);break;
                case 'D': Append(0xD5);break;
                case 'H': Append(0xE5);break;
                default:  Append(0xF5);break;
            }

        }

        else if (!strcasecmp("RAL",token)){
            Append(0x17);
        }

        else if (!strcasecmp("RAR",token)){
            Append(0x1F);
        }

        else if (!strcasecmp("RC",token)){
            Append(0xD8);
        }

        else if (!strcasecmp("RET",token)){
            Append(0xc9);
        }

        else if (!strcasecmp("RIM",token)){
            Append(0x20);
        }

        else if (!strcasecmp("RLC",token)){
            Append(0x07);
        }

        else if (!strcasecmp("RM",token)){
            Append(0xF8);
        }

        else if (!strcasecmp("RNC",token)){
            Append(0xD0);
        }

        else if (!strcasecmp("RNZ",token)){
            Append(0xC0);
        }

        else if (!strcasecmp("RP",token)){
            Append(0xF0);
        }

        else if (!strcasecmp("RPE",token)){
            Append(0xE8);
        }

        else if (!strcasecmp("RPO",token)){
            Append(0xE0);
        }

        else if (!strcasecmp("RRC",token)){
            Append(0x0F);
        }

        else if (!strcasecmp("RST",token)){
            get_token();
            if (token_t != NUMBER){
                ThrowError("Invalid data to RST", Op_count);
                return -1;
            }
            temp = (int) strtol(token,NULL,16);
            if (temp >= 0  && temp < 8){
                Append(0xC7 + 8*temp);
            }
            else{
                ThrowError("Invalid data to RST", Op_count);
                return -1;
            }
        }

        else if (!strcasecmp("RZ",token)){
            Append(0xc8);
        }

        else if (!strcasecmp("SBB",token)){
            get_token();
            if (token_t != REGMEM){
                ThrowError("SBB requires a REG/MEM", Op_count);
                return -1;
            }
            op1 = *token;
            temp = 0x98 + Op_val(op1);
            Append(temp);
        }

        else if (!strcasecmp("SBI",token)){
            Append(0xDE);
            get_token();
            if (token_t != NUMBER){
                ThrowError("SBI needs an Immediate Value",Op_count);
                return -1; // -1 for error
            }
            else{
                temp = (int) strtol(token,NULL,16);
                Append(temp);
            }
        }

        else if (!strcasecmp("SHLD",token)){
            Append(0x22);
            get_token();
            if (token_t != NUMBER){
                ThrowError("not a memory location",Op_count);
                return -1;
            }
            else{
                temp = (int) strtol(token,NULL,16);
                Append(temp & 0x00FF);
                Append((temp & 0xFF00)>>8);
            }

        }

        else if (!strcasecmp("SIM",token)){
            Append(0x30);
        }

        else if (!strcasecmp("SPHL",token)){
            Append(0xf9);
        }

        else if (!strcasecmp("STA",token)){
            Append(0x32);
            get_token();
            if (token_t != NUMBER){
                ThrowError("not a memory location",Op_count);
                return -1;
            }
            else{
                temp = (int) strtol(token,NULL,16);
                Append(temp & 0x00FF);
                Append((temp & 0xFF00)>>8);
            }

        }

        else if (!strcasecmp("STAX",token)){
            get_token();
            if (!strstr(" B D ",token)){
                ThrowError("NOT a register pair B or D",Op_count);
                return -1;
            }
            else{
                switch(*token){
                    case 'B': Append(0x02);break;
                    case 'D': Append(0x12);break;
                }
            }
        }

        else if (!strcasecmp("STC",token)){
            Append(0x37);
        }

        else if (!strcasecmp("SUB",token)){
             get_token();
            if (token_t != REGMEM){
                ThrowError("SUB requires a REG/MEM", Op_count);
                return -1;
            }
            op1 = *token;
            temp = 0x90 + Op_val(op1);
            Append(temp);
        }

        else if (!strcasecmp("SUI",token)){
            Append(0xD6);
            get_token();
            if (token_t != NUMBER){
                ThrowError("SUI needs an Immediate Value",Op_count);
                return -1; // -1 for error
            }
            else{
                temp = (int) strtol(token,NULL,16);
                Append(temp);
            }
        }

        else if (!strcasecmp("XCHG",token)){
            Append(0xEB);
        }

        else if (!strcasecmp("XRA",token)){
            get_token();
            if (token_t != REGMEM){
                ThrowError("ORA requires a REG/MEM", Op_count);
                return -1;
            }
            op1 = *token;
            temp = 0xA8 + Op_val(op1);
            Append(temp);
        }

        else if (!strcasecmp("XRI",token)){
            Append(0xEE);
            get_token();
            if (token_t != NUMBER){
                ThrowError("XRI needs an Immediate Value",Op_count);
                return -1; // -1 for error
            }
            else{
                temp = (int) strtol(token,NULL,16);
                Append(temp);
            }
        }

        else if (!strcasecmp("XTHL",token)){
            Append(0xE3);
        }

        else if (!strcasecmp(" ",token)){

        }

        else{
           // ThrowError("I do not recognize the shit! you've written", Op_count);
        }

    }



}

int Find_Label(char* name){
    int i;
    for(i=0;i<Label_count;i++){
        if (!strcasecmp(name,Label_list[i].name))
            return Label_list[i].addr;
    }
    return -1;
}

void Append(int opcode){
    Op[Op_count].value = opcode;
    Op[Op_count].addr = start_of_code + Op_count;
    Op_count ++ ;
}

void Init_labels(){
    Label_count = 0;

    get_token();
    while(token_t != EOS){

        if (token_t == INVALID){
            ThrowError("Not a valid token", Op_count);
            return;
        }

        if(token_t == LABEL){
            Label_list[Label_count].addr = start_of_code + Op_count-1;
            strcpy(Label_list[Label_count].name , token);
            Label_count++ ;
        }
        else{
            Increase_O_pos(token);
            while(*input != '\n'){
                input++ ;
                if (*input == '\0') break;
            }
        }

        get_token();
    }
}

void To_Start(){
    input = start;
    free(token);
    token = (char*) malloc(MAX_TOK_LEN*sizeof(char));
    Op_count = 0;
    token_t = -1;
}

void micro_main(char* instructions, FILE* outfile){
    start = instructions;
    input = instructions;
    Op_count = 0;

    int i;
    for (i=0;i<strlen(input);i++)
        input[i] = toupper(input[i]);

    Label_list = (label*) malloc (MAX_LABEL_LEN*sizeof(label));
    token = (char*) malloc(MAX_TOK_LEN*sizeof(char));

    //Initialize the labels, first parse
    Init_labels();
    //Revert to the start for secound parse
    To_Start();
    //convert the code to opcode
    to_opcode();

    Opcode_main(&Op,start_of_code);

    print(&Op,Op_count,outfile);
    free(Label_list);
    free(token);
}

void print(Memory* in , int c,FILE* outfile){
    int i;
    for( i =0;i<c;i++){
        fprintf(outfile,"%X : ",in[i].addr);
        fprintf(outfile,"%X \n",in[i].value);
    }
}
