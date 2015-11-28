MINI PROJECT :
MADE BY : 
vishal singh
2007737
it -5

MY MACHINE NAME IS : "MONTEUR"

"MONTEUR" is a german word for "ASSEMBLER";

Note: Input file has to be in the same format as present in "IN.txt";


MONTEUR Design:

Pass-1
1. Assign addresses to all the statements
2. Save the addresses assigned to all labels to be used in Pass-2
3. Perform some processing of assembler directives such as RESW, RESB to find
the length of data areas for assigning the address values.
4. Defines the symbols in the symbol table(generate the symbol table)


Pass-2
1. Assemble the instructions (translating operation codes and looking up addresses).
2. Generate data values defined by BYTE, WORD etc.
3. Perform the processing of the assembler directives not done during pass-1.
4. Write the object program and assembler listing.



ABOUT MONTEUR :

MNEMONICS CREATED ARE :
MONTEUR DIRECTIVES  (pseudo-instructions) :

START, END, BYTE, WORD, RESB, RESW.

These statements are not translated into machine instructions.
Instead, they provide instructions to the assembler itself.

LOAD AND STORE INSTRUCTIONS :
"LDA"-"00"
"STA"-"0C"
"LDCH"-"50"
"STCH"-"54"

ARITHMATIC INSTRUCTIONS :
"ADD"-"28"
"SUB"-"29"
"MUL"-"3A"
"DIV"-"3B"


Memory :
8-bit bytes;
3 consecutive bytes form a word; 
2^15 bytes in the computer memory;

Data Formats
Integers are stored as 24-bit binary numbers; 
2’s complement representation is used for negative values;
No floating-point hardware;



MONTEUR’s Functions : 

1. Convert mnemonic operation codes to their machine language equivalents , example :  LDA to 00
2. Convert symbolic operands (referred label)to their equivalent machine addresses .
3. Build the machine instructions in the proper format .
4. Convert the data constants to internal machine representations .
5. Write the object programand the assembly listing .


MONTEUR uses two internal tables : The OPTAB and SYMTAB.

OPTAB is used to look up mnemonic operation codesand translate them to their machine language equivalents.
LDA→00, STL→14, …
I have used mnemonics and code arrays.


The Symbol Table (SYMTAB) :
 
Include the name and value(address) for each label.
Pass 1, labels are entered into SYMTAB, along with assigned addresses (using LOCCTR).
Pass 2, symbols used as operands are look up in SYMTAB to obtain the addresses.

SYMTAB is used to store values (addresses) assigned to labels.
COPY→1000, FIRST→1000 …

Location Counter(LOCCTR) : 
LOCCTR is a variable for assignment addresses.
LOCCTR is initialized to address specified in START.
When reach a label, the current value of LOCCTR gives the address to be associated with that label.




Rules :
The object program (OP) will be loaded into memory for execution.

Three types of records :

Header: program name,starting address,last address.
Text:   starting address,length(from starting address till end),object code.
End:    address of first executable instruction.

HEADER RECORD :

Col. 1			H
Col. 2-6		Program name
Col. 7-12		Starting address of the object program(in hexadecimal)
Col. 13-18		Last address of the object program(in hexadecimal)


TEXT RECORD :

Col. 1			T
Col. 2-7		Starting address for object code(in hexadecimal)
Col. 8-11		Length(in hexadecimal)
Col. 12-69		Object code , represented in hexdecimal (2 Columns per byte of object code)

END RECORD :

Col. 1			E
Col. 2-7		Address of first executable instruction in object program (in hexadecimal)
