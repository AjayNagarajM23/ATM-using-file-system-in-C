/* 
C PROGRAM TO IMPLEMENT AN ATM(ATOMATIC TELLER MACHINE)
IMPLEMENTED BY :-
    AJAY NAGARAJ M  2SD19CS008
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

// function declaration
void admin();
void user();
void GmenuWindowUser();
void GmenuWindow();
int check();


struct admin{
    char icardNo[10];
    char fname[20];
    char mname[20];
    char lname[20];
    char pin[10];
    char balance[50];
    char phoneNo[12];
    char deposit[20];
    char withdraw[20];
}a;

struct user{
    char transNo[20];
    char deposit[20];
    char withdraw[20];
    char balance[50];
    char mode[10];
    char day[10];
    char month[10];
    char date[10];
    char time[20];
    char year[20];
}u;
// Global declaration of some variables
int t=0;
int TotalBalance=50000;

int delay(double dly){
    /* save start time */
    const time_t start = time(NULL);

    time_t current;
    do{
        /* get current time */
        time(&current);

        /* break loop when the requested number of seconds have elapsed */
    }while(difftime(current, start) < dly);
    return 1;
}
/*
    FUNCTION NAME : AsetData
    FUNCTION TYPE : ADMIN FUNCTION
    RETURN TYPE : VOID
*/
void AsetData(){
    char temp[20];
    int len=0;
    for(;;){
        printf("Enter the last 6 digit of card number of customer : ");
        scanf("%s",a.icardNo);
        strcpy(temp,a.icardNo);
        if((len=strlen(temp)) == 6 ){
            break;
        }
        else{
            printf("Invalid card number ! Card number should be of 6-digits !!\n");
            printf("Please try again!\n");
            continue;
        }
    }

    for(;;){
        printf("Enter the ATM pin of the customer : ");
        scanf("%s",a.pin);
        strcpy(temp,a.pin);
        if((len=strlen(temp)) == 4 ){
            break;
        }
        else{
            printf("Invalid PIN ! PIN should be of 4-digits !!\n");
            printf("Please try again!\n");
            continue;
        }
    }

    printf("Enter the FIRST name of the customer : ");
    scanf("%s",a.fname);

    printf("Enter the MIDDLE name of the customer : ");
    scanf("%s",a.mname);

    printf("Enter the LAST name of the customer : ");
    scanf("%s",a.lname);

    printf("Enter the Intial Balance of the customer : ");
    scanf("%s",a.balance);

    for(;;){
    printf("Enter the phone number of customer : ");
    scanf("%s",a.phoneNo);
    strcpy(temp,a.phoneNo);
        if((len=strlen(temp)) == 10 ){
            break;
        }
        else{
            printf("Invalid Phone Number ! phone number should be of 10-digits !!\n");
            printf("Please try again!\n");
            continue;
        }
    }

}
/*
    FUNCTION NAME : AgetData
    FUNCTION TYPE : ADMIN FUNCTION
    RETURN TYPE : VOID
*/

void AgetData(){
    printf("|-----------------------------------------------------------------|\n");
    printf("|                                                                 |\n");
    printf("|       YOUR ENTERD DATA IS AS FALLOWS PLEASE VARIFY              |\n");
    printf("|       The card number of the customer is    : %s\n",a.icardNo);
    printf("|       The name of the customer is           : %s %s %s\n",a.fname,a.mname,a.lname);
    printf("|       The pin of the customer is            : %s\n",a.pin);
    printf("|       The Intial Balance of the customer is : %s\n",a.balance);
    printf("|       The phone number of cudtomer is       : %s\n",a.phoneNo);
    printf("|                                                                 |\n");
    printf("|-----------------------------------------------------------------|\n");

}

/*
    FUNCTION NAME : encrypt
    FUNCTION TYPE : GENERAL FUNCTION
    RETURN TYPE : VOID
*/

void encrypt(char* str,char password[])
{
	for(int i=0;i<strlen(password);i++)
	{
		password[i]=password[i]-0XAED;
	}
	strcpy(str,password);
}

/*
    FUNCTION NAME : decrypt
    FUNCTION TYPE : GENERAL FUNCTION
    RETURN TYPE : VOID
*/

void decrypt(char* str,char password[])
{
	for(int i=0;i<strlen(password);i++)
	{
		password[i]=password[i]+0XAED;
	}
	strcpy(str,password);
}

/*
    FUNCTION NAME : AcreateFile
    FUNCTION TYPE : ADMIN FUNCTION
    RETURN TYPE : VOID
*/

void AcreateFile(){
    char ret[20];
    char name[30];
    FILE *fp;
    fp = fopen("Details.txt","a+");

    if( fp == NULL ){
        printf("Unable to open the file !\n");
    }
    else{
        sprintf(name,"%s %s %s",a.fname,a.mname,a.lname);
        fprintf(fp,"%-30s",name);
        fprintf(fp,"%-10s",a.icardNo);
        encrypt(ret,a.pin);
        fprintf(fp,"%-10s",ret);
        fprintf(fp,a.phoneNo);
        fprintf(fp,"\n"); 
    }
    fclose(fp);
}

/*
    FUNCTION NAME : AperFile
    FUNCTION TYPE : ADMIN FUNCTION
    RETURN TYPE : VOID
*/

void AperFile(){

    char temp[5]=".txt";
	char filename[30];
    char transNo[100];
    strcpy(filename,a.icardNo);
	strcat(filename,temp);
    strcpy(a.deposit,a.balance);
    strcpy(a.withdraw,"0");

    // converting INTEGERR to STRING
    sprintf(transNo,"%d",++t);
    time_t t;
    time(&t);
 
	FILE *fp1;

    // creating file named users card number to store further data
	fp1 = fopen(filename,"a+");

    if( fp1 == NULL ){
        printf("Failed to open the file !\n");
    }
    else{
        fprintf(fp1,"%-10s","ATM");
        fprintf(fp1,"%-10s",transNo);
        fprintf(fp1,"%-10s",a.deposit);
        fprintf(fp1,"%-10s",a.withdraw);
        fprintf(fp1,"%-10s",a.balance);
        fprintf(fp1,ctime(&t));
    }
    fclose(fp1);
}

/*
    FUNCTION NAME : AupdateBalance
    FUNCTION TYPE : ADMIN FUNCTION
    RETURN TYPE : VOID
*/

void AupdateBalance(){
    int upBal;
    printf("*****************************\n");
    printf("*Enter new Balance in ATM : *\n");
    printf("*****************************\n");

    scanf("%d",&upBal);

    TotalBalance = TotalBalance + upBal ;
    
}

/*
    FUNCTION NAME : Uauth
    FUNCTION TYPE : USER FUNCTION
    RETURN TYPE : VOID
    AUTHENTICATION FUNCTION
*/
void Uauth(){

    int cardNo,count=0;
    char ch;
    int password;
    double dly = 30 ;

    if( TotalBalance != 0 ){
        printf("*****************************************************\n");
        printf("*Enter the Last 6 - digit of the card to continue : *\n");
        printf("*****************************************************\n");
        scanf("%d",&cardNo);

        FILE *fp3 = fopen("Details.txt","r");

        // counting the number of lines in a file
        while((ch = fgetc(fp3)) != EOF){  
        if( ch == '\n')  
            count++;  
        }

        // setting file pointer to the beginning of file 
        fseek(fp3,0,SEEK_SET);

        // reading from the file till there is an match
        for( int i=0 ; i <= count ; i++ ){
            fscanf(fp3,"%s",a.fname);
            fscanf(fp3,"%s",a.mname);
            fscanf(fp3,"%s",a.lname);
            fscanf(fp3,"%s",a.icardNo);
            fscanf(fp3,"%s",a.pin);
            fscanf(fp3,"%s",a.phoneNo);

            // atoi --> convering STRING to INTEGER
            if(cardNo == atoi(a.icardNo)){
                printf("******************************************************************************************\n");
                printf("Hello %s %s %s please Enter your 4-digit ATM pin to continue : \n",a.fname,a.mname,a.lname);
                printf("******************************************************************************************\n");
                
                // ADDING TIME LIMIT TO ENTER THE PIN OF USER
                time_t start_t,end_t;
	            time(&start_t);
                scanf("%d",&password);
                time(&end_t);

                // CLACULATING DIFF B/W START TIME AND END TIME
                // TIME PERIOD WHERE USER ENTERS HIS PIN     
	            if(difftime(end_t, start_t) >= 30 ){
		            printf("Time limit reached to enter pin ! can't allow to login !\n");
                    GmenuWindow();
	            }

                for(int j=0 ; j < strlen(a.pin) ; j++ ){
                    a.pin[j] = a.pin[j] + 0XAED ;
                }

                if( password == atoi(a.pin)){
                    GmenuWindowUser();
                }
                else{
                    printf("*****************************************\n");
                    printf("*Wrong Password entered please verify !!*\n");
                    printf("*****************************************\n");
                    GmenuWindow();
                }
            }
            else{
                continue;
            }
        }

        // if not match
        if(cardNo != atoi(a.icardNo)){
            printf("***************************************************\n");
            printf("*CARD NUMBER NOT FOUND !! please cantact the ADMIN*\n");
            printf("***************************************************\n");
            GmenuWindow();
        }
        GmenuWindow();
        fclose(fp3);
    }
    else{
        printf("*************************************\n");
        printf("*!! ATM IS OUT OF CASH !!  SORRY !! *\n");
        printf("*************************************\n");
        GmenuWindow();
    }
}

/*
    FUNCTION NAME : check
    FUNCTION TYPE : USER FUNCTION
    RETURN TYPE : INT
    returns 1 if all the flags are o else returns 0
    check date,month and year of a perticular transaction
*/
int check(){
    time_t t;
    time(&t);
    char day[20],month[20],date[20],time[20],year[20];

    FILE *fp12 = fopen("time.txt","a+");
    fprintf(fp12,"%s",ctime(&t));
    rewind(fp12);
    fscanf(fp12,"%s",day);
    fscanf(fp12,"%s",month);
	fscanf(fp12,"%s",date);
	fscanf(fp12,"%s",time);
	fscanf(fp12,"%s",year);
    remove("time.txt");
    fclose(fp12);

    //printf("%s %s %s\n",u.month,u.date,u.year);
    //printf("%s %s %s\n",month,date,year);
    int flag = 1;
    flag = strcmp(u.mode,"ATM");
    if(flag == 0 ){
        int flag1 = strcmp(month,u.month);
        int flag2 = strcmp(date,u.date);
        int flag3 = strcmp(year,u.year);

        if(flag1 == 0 && flag2 == 0 && flag3 == 0 ){
            return 1;
        }
        else{
            return 0;
        }
    }
    else{
        return 0;
    }
    
}

/*
    FUNCTION NAME : Uwithdraw
    FUNCTION TYPE : USER FUNCTION
    RETURN TYPE : VOID
*/
void Uwithdraw(){
    int amount,count=0,totalWith=0;
    char temp[5] = ".txt";
    char filename[20];
    char ch;
    strcpy( filename,a.icardNo);
    strcat(filename,temp);
    FILE *fp4 = fopen(filename,"r+");

    while((ch = fgetc(fp4)) != EOF){  
        if(ch == '\n')  
            count++;  
    }  
    fseek(fp4,0,SEEK_SET);

    if( TotalBalance != 0){
        printf("*********************\n");
        printf("*Enter the amount : *\n");
        printf("*********************\n");
        scanf("%d",&amount);

        if( amount <= TotalBalance ){
            // getting current time
            time_t t;
            time(&t);
            for( int i =0 ; i < count ; i++ ){
                fscanf(fp4,"%s",u.mode);
	            fscanf(fp4,"%s",u.transNo);
                fscanf(fp4,"%s",u.deposit);
                fscanf(fp4,"%s",u.withdraw);
	            fscanf(fp4,"%s",u.balance);
	            fscanf(fp4,"%s",u.day);
	            fscanf(fp4,"%s",u.month);
	            fscanf(fp4,"%s",u.date);
	            fscanf(fp4,"%s",u.time);
	            fscanf(fp4,"%s",u.year);

                if(check() == 1 ){
                    totalWith = totalWith + atoi(u.withdraw);
                }
            }
            if( atoi(u.balance) > amount ){
                
                if( (totalWith+amount) <= 25000 ){
                    int result = atoi(u.balance) - amount;
                    TotalBalance = TotalBalance-amount;
                    printf("*********************************************************************************\n");
                    printf("* An amount of %d has been debited from your account at time %s\n",amount,ctime(&t));
                    printf("*********************************************************************************\n");
                    int trans = atoi(u.transNo);
                    trans++;
                    sprintf(u.transNo,"%d",trans);
                    sprintf(u.balance,"%d",result);
                    sprintf(u.withdraw,"%d",amount);
                    strcpy(u.deposit,"0");

                    fprintf(fp4,"\n");
                    fprintf(fp4,"%-10s","ATM");
                    fprintf(fp4,"%-10s",u.transNo);
                    fprintf(fp4,"%-10s",u.deposit);
                    fprintf(fp4,"%-10s",u.withdraw);
                    fprintf(fp4,"%-10s",u.balance);
                    fprintf(fp4,ctime(&t));
                }
                else{
                    printf("***********************************************\n");
                    printf("Maximum Transaction limit is reached for %s \n",a.fname);
                    printf("***********************************************\n");
                }
            }
            else{
                printf("*********************************\n");
                printf("Insufficient balance in accout !!\n");
                printf("*********************************\n");
                GmenuWindow();
            }
        }
        else{
            printf("****************************\n");
            printf("ATM is out of money !! Sorry\n");
            printf("****************************\n");
            GmenuWindow();
        }
    }
    else{
        printf("******************************\n");
        printf("ATM is out of Money !! Sorry !\n");
        printf("******************************\n");
        GmenuWindow();
    }
    fclose(fp4);
}

/*
    FUNCTION NAME : Udeposit
    FUNCTION TYPE : USER FUNCTION
    RETURN TYPE : VOID
*/

void Udeposit(){
    int amount,count=0;
    char temp[5] = ".txt";
    char filename[20];
    char ch;
    
    strcpy( filename,a.icardNo);
    strcat(filename,temp);
    
    FILE *fp5 = fopen(filename,"r+");

    while((ch = fgetc(fp5)) != EOF){  
        if(ch == '\n')  
            count++;  
    }  
    fseek(fp5,0,SEEK_SET);
        printf("******************\n");
        printf("Enter the amount :\n");
        printf("******************\n");
        scanf("%d",&amount);

        time_t t;
        time(&t);
        for( int i =0 ; i <= count ; i++ ){
            fscanf(fp5,"%s",u.mode);
	        fscanf(fp5,"%s",u.transNo);
            fscanf(fp5,"%s",u.deposit);
            fscanf(fp5,"%s",u.withdraw);
	        fscanf(fp5,"%s",u.balance);
	        fscanf(fp5,"%s",u.day);
	        fscanf(fp5,"%s",u.month);
	        fscanf(fp5,"%s",u.date);
	        fscanf(fp5,"%s",u.time);
	        fscanf(fp5,"%s",u.year);
        }
        int result = atoi(u.balance) + amount;
        TotalBalance = TotalBalance + amount;
        printf("*********************************************************************************\n");
        printf("An amount of %d has been credited to your account at time %s\n",amount,ctime(&t));
        printf("*********************************************************************************\n");
        int trans = atoi(u.transNo);
        trans++;

        sprintf(u.transNo,"%d",trans);
        sprintf(u.balance,"%d",result);
        sprintf(u.deposit,"%d",amount);
        strcpy(u.withdraw,"0");

        fprintf(fp5,"%-10s","ATM");
        fprintf(fp5,"%-10s",u.transNo);
        fprintf(fp5,"%-10s",u.deposit);
        fprintf(fp5,"%-10s",u.withdraw);
        fprintf(fp5,"%-10s",u.balance);
        fprintf(fp5,ctime(&t));

        fclose(fp5);
}

/*
    FUNCTION NAME : UcheckBalance
    FUNCTION TYPE : USER FUNCTION
    RETURN TYPE : VOID
*/

void UcheckBalance(){
    int amount,count=0;
    char temp[5] = ".txt";
    char filename[20];
    char ch;
    strcpy( filename,a.icardNo);
    strcat(filename,temp);
    FILE *fp6 = fopen(filename,"r");

    while((ch = fgetc(fp6)) != EOF){  
        if(ch == '\n')  
            count++;  
    }  
    fseek(fp6,0,SEEK_SET);

    for( int i =0 ; i <= count ; i++ ){
        fscanf(fp6,"%s",u.mode);
	    fscanf(fp6,"%s",u.transNo);
        fscanf(fp6,"%s",u.deposit);
        fscanf(fp6,"%s",u.withdraw);
	    fscanf(fp6,"%s",u.balance);
	    fscanf(fp6,"%s",u.day);
	    fscanf(fp6,"%s",u.month);
	    fscanf(fp6,"%s",u.date);
	    fscanf(fp6,"%s",u.time);
	    fscanf(fp6,"%s",u.year);
    }
    printf("*********************************************************************************\n");
    printf(" Balance is : %s\n",u.balance);
    printf("*********************************************************************************\n");
    fclose(fp6);
}

/*
    FUNCTION NAME : UminiStatement
    FUNCTION TYPE : USER FUNCTION
    RETURN TYPE : VOID
*/
void UminiStatement(){
    char temp[5] = ".txt";
    char filename[20];
    char ch;
    int count=0,i,j,k;
    char var[20];
    strcpy( filename,a.icardNo);
    strcat(filename,temp);
    printf("\n");
    printf("*********************************************************************************\n");
    printf("MODE      TR/NO     DEPOSIT   WITHDRAW  BALANCE       TIME & DATE\n");
    FILE *fp7 = fopen(filename,"r");
    printf("*********************************************************************************\n");
    while((ch = fgetc(fp7)) != EOF){  
        if(ch == '\n')  
            count++;  
    }  
    fseek(fp7,0,SEEK_SET);
    if( count > 5 ){
       j = count-5;
       k = j*10;
       for( i = 0 ; i < k ; i++ ){
           fscanf(fp7,"%s",var);
       }
        ch = fgetc(fp7);
        while (ch != EOF)
        {
            printf ("%c", ch);
            ch = fgetc(fp7);
        }    
    }
    else{
        rewind(fp7);
        ch = fgetc(fp7);
        while (ch != EOF)
        {
            printf ("%c", ch);
            ch = fgetc(fp7);
        }
    }
    printf("*********************************************************************************\n");
    printf("\n");
    fclose(fp7);
}

/*
    FUNCTION NAME : ListUsers
    FUNCTION TYPE : ADMIN FUNCTION
    RETURN TYPE : VOID
*/

void ListUsers(){
    FILE *fp8 = fopen("Details.txt","r");

    char ch = fgetc(fp8);
    printf("\n");
    printf("*********************************************************************************\n");
    printf("LIST OF USERS --> \n");
    printf("*********************************************************************************\n");
    printf("   NAME                       CARD/NO   PIN         PH/NO\n");
    printf("*********************************************************************************\n");
    while (ch != EOF)
    {
        printf ("%c", ch);
        ch = fgetc(fp8);
    }
    printf("*********************************************************************************\n");
    printf("\n");
    fclose(fp8);
}

/*
    FUNCTION NAME : accTrans
    FUNCTION TYPE : USER FUNCTION
    RETURN TYPE : VOID
*/

void accTrans(){

    int count=0,count1=0,amount;
    int cradNo1,choice;
    char temp[5] = ".txt";
    char filename[20],filename1[20];
    char ch;
    
    strcpy( filename,a.icardNo);
    strcat(filename,temp);
    
    time_t t;
    time(&t);

    printf("***************************************************\n");
    printf("*         WELLCOME TO ACCOUNT TRANSFER            *\n");
    printf("*         ============================            *\n");
    printf("*Enter the 6 digit card number of the recipient : *\n");
    printf("***************************************************\n");
    scanf("%d",&cradNo1);
    
    sprintf(filename1,"%d",cradNo1);

    printf("***************************************\n");
    printf("*Enter the amount to be transferred : *\n");
    printf("***************************************\n");
    scanf("%d",&amount);

    FILE *fp9 = fopen(filename,"r+");

    while((ch = fgetc(fp9)) != EOF){  
        if(ch == '\n')  
            count++;  
    }  
    
    fseek(fp9,0,SEEK_SET);

    strcat(filename1,temp);
    
    FILE *fp10 = fopen(filename1,"r+");

     while((ch = fgetc(fp10)) != EOF){  
        if(ch == '\n')  
            count1++;  
    }  
    
    fseek(fp10,0,SEEK_SET);

    if(fp10 == NULL ){
        printf("wrong crad number enterd ! Please verify !");
        GmenuWindow();
    }
    else{
        for( int i =0 ; i <= count ; i++ ){
                fscanf(fp9,"%s",u.mode);
	            fscanf(fp9,"%s",u.transNo);
                fscanf(fp9,"%s",u.deposit);
                fscanf(fp9,"%s",u.withdraw);
	            fscanf(fp9,"%s",u.balance);
	            fscanf(fp9,"%s",u.day);
	            fscanf(fp9,"%s",u.month);
	            fscanf(fp9,"%s",u.date);
	            fscanf(fp9,"%s",u.time);
	            fscanf(fp9,"%s",u.year);
            }
            if( atoi(u.balance) > amount){

                FILE *fp11 = fopen("Details.txt","r");

                while((ch = fgetc(fp11)) != EOF){  
                if( ch == '\n')  
                    count++;  
                }
                
                fseek(fp11,0,SEEK_SET);

                for( int i=0 ; i <= count ; i++ ){
                    fscanf(fp11,"%s",a.fname);
                    fscanf(fp11,"%s",a.mname);
                    fscanf(fp11,"%s",a.lname);
                    fscanf(fp11,"%s",a.icardNo);
                    fscanf(fp11,"%s",a.pin);
                    fscanf(fp11,"%s",a.phoneNo);

                    // atoi --> convering STRING to INTEGER
                    if(cradNo1 == atoi(a.icardNo)){
                        printf("|*****************************************************************************************************\n");
                        printf("| Do you really want to transfer the money to MR/MRS %s %s %ss account ?? \n",a.fname,a.mname,a.lname);
                        printf("|        *********            ******** \n");
                        printf("|        | 1.YES |            | 2.NO | \n");
                        printf("|        *********            ******** \n");
                        printf("|*****************************************************************************************************\n");
                        scanf("%d",&choice);
                    
                        if(choice == 1 ){ 
                            int result = atoi(u.balance) - amount;
                            printf("*********************************************************************************\n");
                            printf("* An amount of %d has been debited from your account at time %s\n",amount,ctime(&t));
                            printf("*********************************************************************************\n");
                            
                            int trans = atoi(u.transNo);
                            trans++;
                            
                            sprintf(u.transNo,"%d",trans);
                            sprintf(u.balance,"%d",result);
                            sprintf(u.withdraw,"%d",amount);
                            strcpy(u.deposit,"0");

                            fprintf(fp9,"%-10s","Ac/Trans");
                            fprintf(fp9,"%-10s",u.transNo);
                            fprintf(fp9,"%-10s",u.deposit);
                            fprintf(fp9,"%-10s",u.withdraw);
                            fprintf(fp9,"%-10s",u.balance);
                            fprintf(fp9,ctime(&t));

                            for( int i =0 ; i <= count1 ; i++ ){
                                fscanf(fp10,"%s",u.mode);
	                            fscanf(fp10,"%s",u.transNo);
                                fscanf(fp10,"%s",u.deposit);
                                fscanf(fp10,"%s",u.withdraw);
	                            fscanf(fp10,"%s",u.balance);
	                            fscanf(fp10,"%s",u.day);
	                            fscanf(fp10,"%s",u.month);
	                            fscanf(fp10,"%s",u.date);
	                            fscanf(fp10,"%s",u.time);
	                            fscanf(fp10,"%s",u.year);
                            }
                            
                            int result1 = atoi(u.balance) + amount;
                            int trans1 = atoi(u.transNo);
                            trans1++;

                            sprintf(u.transNo,"%d",trans1);
                            sprintf(u.balance,"%d",result1);
                            sprintf(u.deposit,"%d",amount);
                            strcpy(u.withdraw,"0");

                            fprintf(fp10,"%-10s","Ac/Trans");
                            fprintf(fp10,"%-10s",u.transNo);
                            fprintf(fp10,"%-10s",u.deposit);
                            fprintf(fp10,"%-10s",u.withdraw);
                            fprintf(fp10,"%-10s",u.balance);
                            fprintf(fp10,ctime(&t));

                            fclose(fp10);
                            fclose(fp9);
                            GmenuWindow();
                        }
                    else{
                        GmenuWindow();
                    }
                }
                else{
                    continue;
                }
            }
            
        }
        else{
            printf("*********************************\n");
            printf("Insufficient balance in accout !!\n");
            printf("*********************************\n");
            GmenuWindow();
        }    
    }     
}
/*
    FUNCTION NAME : UchagePin
    FUNCTION TYPE : ADMIN/USER FUNCTION
    RETURN TYPE : VOID
*/
void UchagePin(){
    int val,choice;
    printf("##########################################################\n");
    printf("# This will require ADMINs permission to change password #\n");
    printf("#                                                        #\n");
    printf("#        1.continue              2.QUIT                  #\n");
    printf("#        **********              ******                  #\n");
    printf("# NOTE: if you press 1 the request will go to admin !    #\n");
    printf("#    IT MAY TAKE A WHILE TO PROCESS YOUR REQUEST         #\n");
    printf("##########################################################\n");
    printf("\n");
    printf("# Enter your choice : \n");
    printf("**********************\n");
    scanf("%d",&choice);
    if(choice == 1){
        printf("\t\tPROCESSING .....\n");
        val = delay(20);
    if(val == 1){
        printf(" $  ADMIN HAS APPROVED YOUR REQUEST ....  $\n");
        printf("\n");
        FILE *fp13 = fopen("Details.txt","r+");
        char ch,temp[20],pin[20],uval[20];
        int count=0;
        while((ch=getc(fp13)) != EOF ){
            if( ch == '\n')
                count++;
        }

        rewind(fp13);

        for( int i = 0 ; i < count ; i++ ){
            for( int j = 0 ; j < 6 ; j++ ){
                fscanf(fp13,"%s",temp);
                if(atoi(temp) == atoi(a.icardNo)){
                    for(;;){
                        printf("Enter new pin : ");
                        scanf("%s",pin);
                        if(strlen(pin) == 4 ){
                            encrypt(uval,pin);
                            fprintf(fp13,"%8s",uval);
                            printf("\n");
                            printf("********************************************\n");
                            printf("**** Pin has been updated sucessfully ! ****\n");
                            printf("********************************************\n");
                            break;
                        }
                        else{
                            printf("Pin must of 4-digits !! please try again !\n");
                            continue;
                        }
                    }
                }
            }
        }
    }
    }
    else{
        GmenuWindow();
    }
}


/*
    FUNCTION NAME : GmenuWindowUser
    FUNCTION TYPE : GENERAL FUNCTION
    RETURN TYPE : VOID
*/

void GmenuWindowUser(){

    int choice;

    printf("|*****************************************************************************|\n");
    printf("|                                                                             |\n");
    printf("|           WELLCOME %s %s %s \n",a.fname,a.mname,a.lname);
    printf("|                                                                             |\n");
    printf("|*****************************************************************************|\n");
    printf("|                                                                             |\n");
    printf("|           ==================                  ===============               |\n");
    printf("|           |  1.WITHDRAWAL  |                  |  2.DEPOSIT  |               |\n");
    printf("|           ==================                  ===============               |\n");
    printf("|                                                                             |\n");
    printf("|          =====================               ==================             |\n");
    printf("|          |  3.CHECK BALANCE  |               |  4.MINI STMT   |             |\n");
    printf("|          =====================               ==================             |\n");
    printf("|                                                                             |\n");
    printf("|          ===============                      ================              |\n");
    printf("|          | 5.A/c TRANS |                      | 6.change PIN |              |\n");
    printf("|          ===============                      ================              |\n");
    printf("|                                                                             |\n");
    printf("|                                ============                                 |\n");
    printf("|                                |  7.EXIT  |                                 |\n");
    printf("|                                ============                                 |\n");
    printf("|*****************************************************************************|\n");

    scanf("%d",&choice);

    switch(choice){
        case 1: Uwithdraw();
                GmenuWindow();
                break;
        case 2: Udeposit();
                GmenuWindow();
                break;
        case 3: UcheckBalance();
                GmenuWindow();
                break;
        case 4: UminiStatement();
                GmenuWindow();
                break;
        case 7: GmenuWindow();
                break;
        case 5: accTrans();
                break;
                GmenuWindow();
        case 6: UchagePin();
                GmenuWindow();
                break;
        default:printf("*********************************\n");
                printf("Pleae choose the correct option !\n"); 
                printf("*********************************\n");
                GmenuWindowUser();       
    }
}

/*
    FUNCTION NAME : GmenuWindow
    FUNCTION TYPE : GENERAL FUNCTION
    RETURN TYPE : VOID
*/

void GmenuWindow(){

    int choice;

    printf("|-----------------------------------------------------------------------------|\n");
    printf("|                                                                             |\n");
    printf("|*************************    WELLCOME TO ATM    *****************************|\n");
    printf("|                                                                             |\n");
    printf("|              ---------------                --------------                  |\n");
    printf("|              |   1.ADMIN   |                |   2.USER   |                  |\n");
    printf("|              ---------------                --------------                  |\n");
    printf("|                                                                             |\n");
    printf("|*************************   CHOOSE FROM ABOVE    ****************************|\n");
    printf("|                                                                             |\n");
    printf("|-----------------------------------------------------------------------------|\n");

    scanf("%d",&choice);
    if(choice == 1){
        admin();
    }
    else if( choice == 2 ){
        user();
    }
    else{
        printf("*********************************\n");
        printf("Pleae choose the correct option !\n");
        printf("*********************************\n");
        GmenuWindow();
    }
}

/*
    FUNCTION NAME : admin
    FUNCTION TYPE : ADMIN FUNCTION
    RETURN TYPE : VOID
    MAIN FUNCTION TO LOGIN AS AN ADMIN
*/

void admin(){
    int Apassword;
    int choice;

    printf("|===========================================|\n");
    printf("|Enter the password to continue as admin    :\n");
    printf("|===========================================|\n");

    time_t start_t,end_t;
	time(&start_t);
    scanf("%d",&Apassword);
    time(&end_t);

    // CLACULATING DIFF B/W START TIME AND END TIME
    // TIME PERIOD WHERE USER ENTERS HIS PIN     
	if(difftime(end_t, start_t) >= 30 ){
	    printf("Time limit reached to enter pin ! can't allow to login !\n");
        GmenuWindow();
	}

    if( Apassword == 1234){
        printf("|==========================================================================|\n");
        printf("|                                                                          |\n");
        printf("|                             **   ADMIN  **                               |\n");
        printf("|                                                                          |\n");
        printf("|       ----------------        ---------------         -----------------  |\n");
        printf("|       | 1.ADD USER   |        | 2.ADD CASH  |         | 3.MAIN MENU   |  |\n");
        printf("|       ----------------        ---------------         -----------------  |\n");
        printf("|                                                                          |\n");
        printf("|       ====================    ======================   =============     |\n");
        printf("|       | 4.List ALL USERS |    || 5.SWITCH OFF ATM ||   | 6.Balance |     |\n");
        printf("|       ====================    ======================   =============     |\n");
        printf("|                                                                          |\n");
        printf("|==========================================================================|\n");

        scanf("%d",&choice);
        switch( choice ){
            case 1: AsetData();
                    AgetData();
                    AcreateFile();
                    AperFile();
                    GmenuWindow();
                    break;
            case 2: AupdateBalance();
                    GmenuWindow();
                    break;
            case 3: GmenuWindow();
                    break;
            case 4: ListUsers();
                    GmenuWindow();
                    break;
            case 5: exit(0);
                    break;
            case 6: printf("**************************************\n");
                    printf("TOTAL BALANCE IS : %d\n",TotalBalance);
                    printf("**************************************\n");
                    GmenuWindow();
                    break;
            default:printf("*********************************\n");
                    printf("Pleae choose the correct option !\n");
                    printf("*********************************\n");
                    admin();        
        }
    }
    else{
        printf("Wrong password Enterd please varify -->\n");
        GmenuWindow();
    }
}

/*
    FUNCTION NAME : USER
    FUNCTION TYPE : USER FUNCTION
    RETURN TYPE : VOID
    MAIN FUNCTION TO LOGIN AS USER
*/
void user(){
    Uauth();
}

/*
    FUNCTION NAME : main
    FUNCTION TYPE : GENERAL FUNCTION
    RETURN TYPE : int
    Main Function
*/
int main(){
    GmenuWindow();
    return 0;
}
