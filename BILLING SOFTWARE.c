#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<conio.h>
#include<stdlib.h>
//#include<graphics.h>
//#include<time.h>

int n; //used for Qauntity.txt
int ti=0; //customer index


//This structure stores details of products available at the supermarket
struct item
{
	int productno;
	char productname[20];
	int quantity;
	int price;
}item;

//Stores customer's cart
struct customer
{
	int productno;
	char productname[20];
	int quantity;
	int price;
	int amount;
}cst[100];

//Function to add products in inventory and file
void create()
{
	int i=0,rec_n;
	FILE *fp,*fpq;
	fp=fopen("Records.csv","a");
	fpq=fopen("Quantity.txt","w");
	if(fp==NULL)
	{
		printf("Error\n");
	}
	printf("\n\n\n\n\t");
	printf("Enter the Number of Records: ");
	scanf("%d",&rec_n);
	fscanf(fpq,"%d",&n);
	n=n+rec_n;
	fprintf(fpq,"%d",n);
	printf("\n");
	fclose(fpq);	
	while(i<rec_n)
	{
	    printf("\t");
		printf("Enter Product Code:");
		scanf("%d",&item.productno);
		printf("\t");
		printf("Enter Product Name:");
		scanf("%s",item.productname);
		printf("\t");
		printf("Enter Quantity:");
		scanf("%d",&item.quantity);
		printf("\t");
		printf("Enter Price:");
		scanf("%d",&item.price);
		printf("\n");
		i++;
		fprintf(fp,"\n%d %s %d %d",item.productno,item.productname,item.quantity,item.price);
	}
	fclose(fp);
}


void display()
{
	int record,read;
	read=0;
	FILE *fp;
	fp=fopen("Records.csv","r");
	record=0;
	if(feof(fp))
	{
		printf("Error in Opening Files\n");
	}
	printf("\t");
	printf("==============================================================\n");
	printf("\t");
	printf("|Product Number\t|Product Name\t|Quantity\t|Price\t\n");
	printf("\t");
	printf("==============================================================\n");
	while(!feof(fp))
	{
		read=fscanf(fp,"%d %s %d %d\n",&item.productno,item.productname,&item.quantity,&item.price);  
		if(read==4){
			record++;
			printf("\n\t  %14d|\t%8s|\t%8d|\t%d|\n",item.productno,item.productname,item.quantity,item.price);
        	printf("\n");
        }
        
		if(read!=4 && !feof(fp)){
			printf("\n\n\tFormat incorrect...\n\n\n");
			fclose(fp);
			return;
		}
	}
	fclose(fp);
}

void edit()
{
	FILE *fp;
	FILE *fptr;
	int h;
	int found=0;
	int n=0;
	fp=fopen("Records.csv","r");
	fptr=fopen("temp1.csv","w");
	printf("\t");
	printf("Enter the Product Number to Delete: ");
	scanf("%d",&h);
	printf("\n");
	while(!(feof(fp)))
	{
		n++;
		fscanf(fp,"%d",&item.productno);
		if(item.productno==h)
		{
			found=1;
			fscanf(fp,"%s",item.productname);
			fscanf(fp,"%d",&item.quantity);
			fscanf(fp,"%d",&item.price);
			
			printf("\t");
			printf("Product has been Successfully Deleted\n");
		}
		else
		{
			fscanf(fp,"%s",item.productname);
			fscanf(fp,"%d",&item.quantity);
			fscanf(fp,"%d",&item.price);
			fprintf(fptr,"%d %s %d %d ",item.productno,item.productname,item.quantity,item.price);
		}
	}
	fclose(fptr);
	fclose(fp);
	if(found==0)
	{
	    printf("\t");
		printf("Product no Found");
		printf("\n");
		printf("\n");
	}
	remove("Records.csv");
	rename("temp1.csv","Records.csv");
}

void bill()
{
	int na=0;  //used for product number in scanf function
	int a=0;	//quantity of a product
	int cont=0; //counter
	int k=0; //continue
	int r=0;
	int w=0;
	int ch=0;
	int l=0; //line counter in file	
	int bi=0;
	int ln=0; //repition of product number
	int read;
    printf("\n\t");
	l3: 
	printf("Enter the Product Number: ");
	scanf("%d",&na);
	printf("\n");
	FILE *fp;
	fp=fopen("Records.csv","r+");
	FILE *fptr;
	fptr=fopen("temp.csv","w");
	if(fp==NULL || fptr==NULL){
		printf("Error opening file");
		return;
	}
	while(!(feof(fp)))
	{
		l++;
		fscanf(fp,"%d %s %d %d\n",&item.productno,item.productname,&item.quantity,&item.price);
		if(item.productno == na)
		{
			ln++;
			if(ln==2)
			break;
			
			printf("Enter the Quantity: ");
			scanf("%d",&a);
			if(a <= item.quantity)
			{
				cst[ti].productno=item.productno;
				strcpy(cst[ti].productname,item.productname);
				cst[ti].quantity=a;
				cst[ti].price=item.price;
				item.quantity=item.quantity-a;
				ti++;
				
			}
			else
			{
				printf("Sorry Out of Stock\n");
				bi++;
				
			}
		}
		else
		{
			cont++;
			fprintf(fptr,"%d ",item.productno);
			fprintf(fptr,"%s ",item.productname);
			fprintf(fptr,"%d ",item.quantity);
			fprintf(fptr,"%d \n",item.price);
			continue;
		}
		fprintf(fptr,"%d ",item.productno);
		fprintf(fptr,"%s ",item.productname);
		fprintf(fptr,"%d ",item.quantity);
		fprintf(fptr,"%d \n",item.price);
	}
	if(l==cont)
	printf("Error:Choose Properly\n");
	fclose(fptr);
	fclose(fp);
	remove("Records.csv");
	rename("temp.csv","Records.csv");
	ln=0;
	printf("Do you Want to Shop More:\nPress 1 for More\nPress 2 to Exit\t");
	scanf("%d",&k);
	if(k==1)
	goto l3;
}

void invoice()
{
	int j;
	int o;
	float gt=0;
	if(ti==0)
	{
		printf("There are No Products in your Cart");
		printf("\n");
	}
	printf("\n\n");
	printf("****************************INVOICE**************************");
	printf("\n\n");
	printf("product number\t| product name\t| price\t| quantity\t| amount\t|\n");
	printf("*************************************************************\n");
	for(o=0;o<ti;o++)
	{
		cst[o].amount=0;
		cst[o].amount=((cst[o].price)*(cst[o].quantity));
		gt=gt+cst[o].amount;
	}
	for(j=0;j<ti;j++)
	{
		printf("%6d\t       |%9s   \t  | %3d\t|%3d\t        |   %3d\n",cst[j].productno,cst[j].productname,cst[j].price,cst[j].quantity,cst[j].amount);
	}
	printf("\nAmount Payable:%f",gt);
	printf("\n");
	printf("Thank you for Shopping");
	printf("\n");
	printf("Visit Again");
	printf("\n");
	int key;
	printf("Press any key to return to main menu\t");
	scanf("%d",&key);
}


int main()
{
	//FRONT PAGE
	/*int gd=DETECT, gm;
	initgraph(&gd,&gm,"C:\\TURBOC3\\BGI");
	unsigned int x_hours=0;
	unsigned int x_minutes=0;
	unsigned int x_seconds=0;
	unsigned int x_milliseconds=0;
	unsigned int totaltime=0,count_down_time_in_secs=0,time_left=0;
	
	
	clock_t x_startTime,x_countTime;
	count_down_time_in_secs=30;  
	x_startTime=clock();  // start clock
    time_left=count_down_time_in_secs-x_seconds;
	//setting x,y coordinates to the center
	int x_coord=150;
	int y_coord=0;
	
	
	//setting text style
	settextstyle(8,0,4);
	//print text
	outtextxy(x_coord,y_coord,"SUPERMARKET BILLING SYSTEM");
	settextstyle(3,0,2);
	y_coord+=50;
	x_coord+=200;
	outtextxy(x_coord,y_coord,"by Dikshita and Neha");
	y_coord+=30;
	x_coord=0;
	//increment timer upto 30 seconds and then close front page
	while (time_left>0) 
	{
		x_countTime=clock();
		x_milliseconds=x_countTime-x_startTime;
		x_seconds=(x_milliseconds/(CLOCKS_PER_SEC))-(x_minutes*60);
		x_minutes=(x_milliseconds/(CLOCKS_PER_SEC))/60;
		x_hours=x_minutes/60;
		
		time_left=count_down_time_in_secs-x_seconds;
	}

	closegraph();*/
	
	
	// MAIN SYSTEM
	char ch,password[10],q[10]="admin";
	printf("\n");
	int i;
	int s=0; //choice for view
	int y=0; //choice for admin view
	//MENU
	
	
    q:
	printf("\n\t"); //defining label 'q' to go back to main menu without having to reenter code again
    printf("****************************");
    printf("\n");
    printf("\t");
    printf("Please select an option: ");
    printf("\n");
    printf("\t");
    printf("****************************");
    printf("\n\n");
    printf("\t");
	printf("01. ADMIN VIEW");
	printf("\n\t");
	printf("02. CUSTOMER VIEW");
	printf("\n\t");
	printf("03. EXIT APP");
	printf("\n");
	printf("\n\t");
	printf("Please Enter an Option: ");
	scanf("%d",&s);
	
	switch(s)
	{
	    case 1: //ADMIN VIEW
			printf("\tEnter Password:\t"); 
            for(i=0;i<5;i++)
            {
              ch = getch();
              password[i] = ch;
              ch = '*' ;
               printf("%c",ch);
			}
            password[i]='\0';
            
            //check if password is correct
            if(strcmp(password,q))
            {
            	system("cls");
                printf("\n\t");
                printf("Wrong Password Please Try Again");
                printf("\n\n");
                goto q;
            }
            //If password correct, enter Admin view
            else
               system("cls");
               goto l3;
               l3: printf("\n\t");
               printf("Access Granted\n");
               printf("\n\n");
               printf("\t");
               printf("****************************");
               printf("\n");
               printf("\t");
               printf("Please Select an Option: ");
               printf("\n");
               printf("\t");
               printf("****************************");
               printf("\n\n");
		       printf("\t01.ADD PRODUCTS TO INVENTORY");
		       printf("\n\t");
		       printf("02.DELETE PRODUCTS IN INVENTORY");
		       printf("\n\t");
		       printf("03.DISPLAY PRODUCTS IN INVENTORY");
		       printf("\n\t");
		       printf("04.GO BACK TO MAIN MENU");
		       printf("\n");
		       printf("\n");
		       printf("\t");
		       printf("Please Enter an Option: ");
		       scanf("%d",&y);
		       switch(y)
			   {
        			case 1:
        				system("cls");
						create();
						system("cls");
						printf("\t");
						printf("Records are Created");
						printf("\n\n");
        			    goto q;
  			    
					case 2:
						system("cls");
						edit();
  			            goto q;
					case 3:
						system("cls");
						display();
                        goto q;
                 	case 4:
					 	system("cls"); 
					    goto q;
                    default : 
                    	system("cls");
						printf("error\n");
				    	goto q;
        	   }
		         break;
		         
		         
		    case 2: 
		       system("cls");
			   printf("\n");
               printf("\t");
               printf("****************************");
               printf("\n");
               printf("\t");
               printf("Please Select an Option: ");
               printf("\n");
               printf("\t");
               printf("****************************");
               printf("\n");
               printf("\t");
               printf("01.MAKE BILL");
               printf("\n\t");
               printf("02.SHOW BILL");
               printf("\n\t");
               printf("03.MAIN MENU");
               printf("\n\n\n\t");
               printf("Please Enter an Option: ");
               scanf("%d",&y);
               printf("\n");
               switch(y)
		        {
                    case 1 : 
                    		system("cls");
							bill();
							system("cls");
        			        goto q;

                    case 2 : 
                    		system("cls");
							invoice();
							system("cls");
                            goto q;
                             
                    case 3 : 
							goto q;

                    default : 
							printf("Error\n");
                            goto q;
        		}
		         break;
		    	
		    case 3: //EXIT
				printf("\tExiting...\n");
				break;	
				
      		default: //INVALID VIEW
			    printf("\tInvalid Choice\n");
      			break;
	}
	return 0;
}
