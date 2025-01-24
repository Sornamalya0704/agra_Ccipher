/*
  APPLICATIONS OF MATRICES IN CRYPTOGRAPHY
  CIPHER WITH AGRA CODE
*/

#include <stdio.h>
#include <string.h>
#define max_size 50
int key[3][2]={{4,1},{5,2},{6,3}};
int encrypt[5][max_size];
int decrypt[5][max_size];
char input[max_size];
char output[max_size];
int nom=0;

struct node
{
    char character[5];
    int value;
    struct node *next;
};
struct node* head=NULL;
void insertLast()
{
    struct node* p;
    p=(struct node*)(malloc(sizeof(struct node)));
    if(p==NULL)
        printf("\nINSERTION NOT POSSIBLE\n");
    else
    {
        struct node* temp;
        printf("\nENTER THE CHARACTER:");
        scanf("%s",&p->character);
        printf("\nENTER IT'S RESPECTIVE VALUE:");
        scanf("%d",&p->value);
        if(head==NULL)
        {
            p->next=NULL;
            head=p;
        }
        else
        {
            temp=head;
            while(temp->next!=NULL)
            {
                temp=temp->next;
            }
            temp->next=p;
            p->next=NULL;
        }
    }

}
void writeToFile(char filename[],struct node* head)
{
    struct node* temp=head;
    FILE *fp;
    fp=fopen(filename,"a");
    if(fp==NULL)
    {
        printf("\nFILE DOES NOT EXISTS\n");
        exit(1);
    }
    while(temp!=NULL)
    {
        fprintf(fp,"\n%s:%d",temp->character,temp->value);
        temp=temp->next;
    }
    if(fwrite!=0)
        printf("\nDATA STORED SUCCESSFULLY\n");
    else
        printf("\nERROR IN STORING");
    fclose(fp);
}
void sequencing()
{
    char again;
    do
    {
        insertLast();
        printf("\nDO YOU WANT TO INPUT AGRA CODE ?");
        printf("\nPRESS 'Y' OR 'y' TO INPUT :");
        scanf("%s",&again);
    }
    while(again=='Y'||again=='y');
    writeToFile("Sequence.txt",head);
}

//function to encrypt
void encryption(char input[max_size],int length)
{
    int inputNum[max_size];
    int flag=1;
    FILE *fp;
    fp=fopen("Sequence.txt","r");
    if(fp==NULL)
    {
        printf("\nFILE DOES NOT EXISTS\n");
        exit(1);
    }

    for(int i=0;i<length;i++)
    {
        fseek(fp,0,SEEK_SET);
        int ch;
        int oh=0;
        while(ch!=EOF)
        {
            ch=fgetc(fp);
            if(ch==input[i])
                break;
        }
        if(ch<69&&ch>64)
            flag=0;
        ch=fgetc(fp);
        ch=fgetc(fp);
        if(flag==1)
        {
            oh=fgetc(fp);
            inputNum[i]=(ch-48)*10+(oh-48);
        }
        else
            inputNum[i]=ch-48;
        flag=1;
    }

    fclose(fp);
    if((length)%2==1)
    {
        length=length+1;
        inputNum[length-1]=55;
        nom=length/2;
    }
    else
        nom=length/2;
    int in=0;
    int temp[5][5];
    int i=0;
    int j=0;
    int k=0;
    int a=0;
    while(a<nom)
    {
        temp[0][0]=inputNum[in];
        int store=temp[0][0];
        in++;
        temp[1][0]=inputNum[in];
        in++;
        for(i=0;i<3;i++)
        {
            for(j=0;j<1;j++)
            {
                encrypt[i][j+a]=0;
                for(k=0;k<2;k++)
                {
                    encrypt[i][j+a]+=key[i][k]*temp[k][j];
                }
            }
        }
        a++;
    }
    printf("\nENCRYPTED MATRIX OF MESSAGE\n");
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<a;j++)
            printf("|%d|\t",encrypt[i][j]);
        printf("\n");
    }
};

//function to decrypt
void decryption(int encrypt[max_size][max_size])
{
    int keyT[10][10];
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            keyT[i][j]=key[j][i];
        }
    }
    int clue[10][10];
    for(int i=0;i<2;i++){
        for(int j=0;j<2;j++){
            clue[i][j]=0;
            for(int k=0;k<3;k++){
                clue[i][j]+=keyT[i][k]*key[k][j];
            }
        }
    }
    int mod_clue=clue[0][0]*clue[1][1]-clue[0][1]*clue[1][0];
    int clueI[10][10];
    clueI[0][0]=clue[1][1];
    clueI[1][1]=clue[0][0];
    for(int i=0;i<2;i++){
        for(int j=0;j<2;j++){
                if(i!=j)
                    clueI[i][j]=-clue[i][j];
        }
    }
    int keyPi[10][10]={0};
    for(int i=0;i<2;i++){
        for(int j=0;j<3;j++){
            keyPi[i][j]=0;
            for(int k=0;k<2;k++){
                keyPi[i][j]+=clueI[i][k]*keyT[k][j];
            }
        }
    }
    int a=0;
    int i=0;
    int j=0;
    int k=0;
    int temp[10][10];
    while(a!=nom)
    {
        for(int i=0;i<3;i++){
            for(int j=0;j<1;j++){
                temp[i][j]=encrypt[i][a];
            }
        }
        for(i=0;i<2;i++)
        {
            for(j=0;j<1;j++)
            {
                decrypt[i][j+a]=0;
                for(k=0;k<3;k++)
                {
                    decrypt[i][j+a]+=keyPi[i][k]*temp[k][j];
                }
            }
        }
        a++;
    }
    for(int i=0;i<2;i++){
        for(int j=0;j<a;j++){
            int temp=decrypt[i][j]/mod_clue;
            decrypt[i][j]=temp;
        }
    }
    int outputNum[max_size];
    for(int i=0;i<a+a;i++){
            outputNum[i]=0;
        if(i%2==0)
            outputNum[i]=decrypt[0][i/2];
        else
            outputNum[i]=decrypt[1][i/2];
    }
    FILE *fp;
    fp=fopen("Sequence.txt","r");
    if(fp==NULL)
    {
        printf("\nFILE DOES NOT EXISTS\n");
        exit(1);
    }

    for(int i=0;i<a+a;i++)
    {
        fseek(fp,1,SEEK_SET);
        int on=outputNum[i];
        char ch;
        int tp;
        int fd;
        int sd;
        while(tp!=EOF)
        {
            sd=fgetc(fp);
            ch=fgetc(fp);
            tp=fgetc(fp);
            if(tp==':')
            {
                fd=fgetc(fp);
                if(on>10)
                {
                    sd=fgetc(fp);
                    if(on/10==fd-48&&on%10==sd-48)
                        break;
                }
                else
                {
                    if(on==fd-48)
                        break;
                }
            }
        }
        output[i]=ch;
    }
    printf("\nDECRYPTED TEXT OF MESSAGE\n");
    if(output[a+a-1]=='_')
    {
        for(int i=0;i<a+a-1;i++)
            printf("%c",output[i]);
    }
    else
    {
        for(int i=0;i<a+a;i++)
            printf("%c",output[i]);
    }
}

int main()
{
    printf("\n\t\t\t\t\t-------------------------------------------");
    printf("\n\t\t\t\t\t| APPLICTIONS OF MATRICES IN CRYPTOGRAPHY |");
    printf("\n\t\t\t\t\t-------------------------------------------");
    printf("\n  1.SEQUENCING AGRA CODE");
    printf("\n  2.MESSAGE TEXT");
    printf("\n  3.MESSAGE ENCRPTION");
    printf("\n  4.MESSAGE DECRPTION");
    printf("\n  5.EXIT");
    int choice;
    while(1)
    {

        printf("\n\nENTER THE ACTION TO BE PERFORMED:");
        scanf("%d",&choice);
        if(choice==1)
            sequencing();
        else if(choice==2)
        {
            printf("\nENTER THE TEXT:\t");
            scanf("%s",&input);
        }
        else if(choice==3)
        {
            int length=strlen(input);
            encryption(input,length);
        }
        else if(choice==4)
        {
            decryption(encrypt);
        }
        else if(choice==5)
            break;
        else
            printf("\n\tPLEASE ENTER THE CORRECT OPTION");
    }
    return 0;
}
//must add the full procedure of encrption and decryption in README.md file
