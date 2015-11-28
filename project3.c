#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<stdlib.h>



/*
Note: Input file has to be in the same format ;
*/


void main()
{
  char a[10],ad[10],label[10],opcode[10],operand[10],sym[10],ch,fnm[15],ab[15];
  int st,diff,diff1,i,addr,addr1,add,len,alen,finaddr,previousaddr,j=0;
  char mnemonic_array[15][15]={"LDA","STA","LDCH","STCH","ADD","SUB","MUL","DIV","J","JSUB"};
  int location_counter=0x0,start,l,c=0x0,k=0,bol=0;
  char code[15][15]={"00","0C","50","54","28","29","3A","3B","3E","3F"};
  FILE *fp1,*fp2,*fp3,*fp4;
  printf("ENTER THE PROGRAM FILE NAME  : \n");
  scanf("%s",&fnm);
  fp1 = fopen("mid.txt","w");
  fp3 = fopen(fnm,"r");
 printf("\n\n\t\t\tINPUT FILE:\n\n");
  ch=fgetc(fp3);
  while(ch!=EOF)
  {
   printf("%c",ch);
   ch=fgetc(fp3);
  }
 rewind(fp3);
printf("\n\nSTART OF PASS 1 ");

fp2=fopen("SYMTAB.txt","w");
  fscanf(fp3,"%s%s%s%X",label,opcode,operand,&addr);
    if(strcmp(operand,"START")==0)
    {
            start=addr;
            location_counter=start;
            previousaddr=location_counter;
            c=addr;
        fprintf(fp1,"%s\t%s\t%X\n",opcode,operand,addr);
    }
    else
        location_counter=0x0;
fscanf(fp3,"%s%s%s",label,opcode,operand);
while(strcmp(opcode,"END")!=0)
  {
      if(strcmp(label,"**")!=0)
        fprintf(fp2,"%s\t%X\n",label,location_counter);

        if(strcmp(opcode,"BYTE")==0)
            {
                fprintf(fp1,"%X\t%s\t%s\t%s\t\n",addr,label,opcode,operand);
                len=strlen(operand);
                addr+=len-3;
                location_counter+=len-3;
            }
            else if(strcmp(opcode,"RESB")==0)
           {
                fprintf(fp1,"%X\t%s\t%s\t%s\n",addr,label,opcode,operand);
                addr+=(atoi(operand));
                location_counter+=(atoi(operand));
           }
    else if (strcmp(opcode,"RESW")==0)
    {
        fprintf(fp1,"%X\t%s\t%s\t%s\n",addr,label,opcode,operand);
        addr+=(3*(atoi(operand)));
         location_counter+=(3*(atoi(operand)));
    }
   else
   {
      fprintf(fp1,"%X\t%s\t%s\t%s\n",addr,label,opcode,operand);
       addr+=3;
       location_counter+=3;
   }
   fscanf(fp3,"%s%s%s",label,opcode,operand);
  }
  fprintf(fp1,"%X\t%s\t%s\t%s\n",addr,label,opcode,operand);
  l=addr;
  fclose(fp1);
  fclose(fp2);
  fclose(fp3);
    printf("\n\nINTERMEDIATE FILE  : AFTER ADRESSING \n\n\t");
  fp1=fopen("mid.txt","r");
  ch=fgetc(fp1);
  while(ch!=EOF)
  {
   printf("%c",ch);
   ch=fgetc(fp1);
  }
  fclose(fp1);
  printf("\n\nTHE LENGTH OF THE PROGRAM IS : %X",l-c);
//ADDRESSING DONE IN MEDIATOR FILE;
//AFTER ADDRESING :
printf("\n\nSYMBOL TABLE CREATED");
  printf("\n\n\t\t\tSYMBOL TABLE :\n\n");
  fp2=fopen("SYMTAB.txt","r");
  ch=fgetc(fp2);
  while(ch!=EOF)
  {
   printf("%c",ch);
   ch=fgetc(fp2);
  }
fclose(fp2);
printf("\n\nEND OF PASS 1");
printf("\n\nSTART OF PASS 2 ");
 fp1 = fopen("OUTPUT.txt","w");
  fp2 = fopen("SYMTAB.txt","r");
  fp3 = fopen("mid.txt","r");
  fp4 = fopen("obj.txt","w");

  fscanf(fp3,"%s%s%s",label,opcode,operand);

  while(strcmp(opcode,"END")!=0)
  {
   previousaddr=addr;
   fscanf(fp3,"%X%s%s%s",&addr,label,opcode,operand);
  }

  finaddr=addr;
  fclose(fp3);

 fp3=fopen("mid.txt","r");

  fscanf(fp3,"%s%s%s",label,opcode,operand);
  if(strcmp(opcode,"START")==0)
  {
   fprintf(fp1,"\t%s\t%s\t%s\n",label,opcode,operand);
   fprintf(fp4,"H^%s^00%s^00%X\n",label,operand,finaddr);
   fscanf(fp3,"%X%s%s%s",&addr,label,opcode,operand);
   st=addr;
   diff=previousaddr-st;
    fprintf(fp4,"T^00%X^%X",addr,diff);
  }
  while(strcmp(opcode,"END")!=0)
  {
   if(strcmp(opcode,"BYTE")==0)
   {
    fprintf(fp1,"%X\t%s\t%s\t%s\t",addr,label,opcode,operand);
    len=strlen(operand);
    alen=len-3;
    fprintf(fp4,"^");
    for(i=2;i<(alen+2);i++)
    {
     itoa(operand[i],ad,16);
     fprintf(fp1,"%s",ad);
     fprintf(fp4,"%s",ad);
    }
    fprintf(fp1,"\n");
   }
   else if(strcmp(opcode,"WORD")==0)
   {
    len=strlen(operand);
    itoa(atoi(operand),a,10);
    fprintf(fp1,"%X\t%s\t%s\t%s\t00000%s\n",addr,label,opcode,operand,a);
    fprintf(fp4,"^00000%s",a);
   }
   else if((strcmp(opcode,"RESB")==0)||(strcmp(opcode,"RESW")==0))
    fprintf(fp1,"%X\t%s\t%s\t%s\n",addr,label,opcode,operand);
   else
   {
    while(strcmp(opcode,mnemonic_array[j])!=0)
     j++;
    if(strcmp(operand,"COPY")==0)
     fprintf(fp1,"%X\t%s\t%s\t%s\t%s0000\n",addr,label,opcode,operand,code[j]);
    else
    {
     rewind(fp2);
     fscanf(fp2,"%s%X",sym,&add);
      while(strcmp(operand,sym)!=0)
       fscanf(fp2,"%s%X",sym,&add);
     fprintf(fp1,"%X\t%s\t%s\t%s\t%s%X\n",addr,label,opcode,operand,code[j],add);
     fprintf(fp4,"^%s%X",code[j],add);
    }
   }
   fscanf(fp3,"%X%s%s%s",&addr,label,opcode,operand);
  }
  fprintf(fp1,"%X\t%s\t%s\t%s\n",addr,label,opcode,operand);
  fprintf(fp4,"\nE^00%X",st);
  printf("\n\n\tINTERMEDIATE FILE IS COVERTED INTO OBJECT CODE");
printf("\n\nEND OF PASS 2");
  fclose(fp1);
  fclose(fp2);
  fclose(fp3);
  fclose(fp4);
  printf("\n\n\t\t\tOUTPUT FILE :\n\n");
  fp1=fopen("OUTPUT.txt","r");
  ch=fgetc(fp1);
  while(ch!=EOF)
  {
   printf("%c",ch);
   ch=fgetc(fp1);
  }
  printf("\n\nCONTENTS OF OBJECT CODE FILE :\n\n");
  fp4=fopen("obj.txt","r");
  ch=fgetc(fp4);
  while(ch!=EOF)
  {
   printf("%c",ch);
   ch=fgetc(fp4);
  }
  fclose(fp1);
  fclose(fp3);
  fclose(fp4);
}
