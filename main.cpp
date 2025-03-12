#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct covid
{
	char id[20];
	char tstatus[10];
	char KKM[10];
	char day[10];
	char date[20];
	char name[50];
	char phone[15];
	char email[30];
	char lastloc[20];
	char loc[20];
	char address[100];
}cdat;

void mainmenu();
void puimenu();
void newrec();
void modifyrec();
void teststatus();
void lastloc();
void adminmenu();
void adminViewDetail();
void recordTestDetail();
void weekSummary();
void contMenu();


int main()
{
	mainmenu();
	return 0;
}

void mainmenu()
{
	int role;
	printf("Covid-19 test system\n\n");
	printf("Please select your role:  \n1. Person Under Investigation(PUI)\n2.KKM(Admin)\n3.End\n?");
	scanf("%d",&role);
	switch (role)
	{
		case 1:
			puimenu();
			break;
		case 2:
			adminmenu();
			break;
		case 3:
			contMenu();
			break;
		default :
			printf("Error!!\n\n");
			fflush(stdin);
			system("cls");
			mainmenu();
			break;	
	}
}

void puimenu()
{
	system ("cls");
	int choice;
	printf("Welcome, please select an option you want to do\n");
	printf("1. Create New Record\n2. Modify record\n3. Test Status\n4. Update last location\n5. Back\n?");
	scanf("%d",&choice);
	switch (choice)
	{
		case 1:
			system ("cls");
			newrec();
			break;
		case 2:
			modifyrec();
			break;
		case 3:
			teststatus();
			break;
		case 4:
			lastloc();
		case 5:
			system("cls");
			mainmenu();
			break;
		default:
			printf("Error!!\n\n");
			system ("cls");
			puimenu();
			break;
	}
}

void newrec()
{
	fflush(stdin);
	FILE *ptr;
	FILE *loc;
	struct covid cd;
	char arr[20],pid[20];
	if ((ptr=fopen("covid.txt","r+")) == NULL)
	{
		ptr=fopen("covid.txt","w");
		newrec();
	}
	else
	{
		if ((loc = fopen("loc.txt","r+"))==NULL)
		{
			loc= fopen("loc.txt","w");
			newrec();
		}
		else
		{
			time_t tday;//time variable
			time(&tday);//obtian time now
			struct tm *local = localtime(&tday);//filled the structure with time,tm cannot be change
			strcpy(cd.KKM,"N/A");
			strcpy(cd.tstatus,"Pending");
			printf("Please enter ID-Card Number: ");
			scanf("%s",cd.id);
			while (!feof(ptr))
			{
				fscanf(ptr,"%s",arr);
				if (!strcmp(arr,cd.id))
				{
					printf("ID already exist!!\nPlease try again\n\n");
					int out;
					printf("Please enter\n1. try again\n2. Exit");
					scanf("%d",&out);
					if (out == 1)
					{
						system("cls");
						newrec();
					}
					else if (out == 2)
					{
						printf("thank you");
						exit(0);
					}
				}
			}
			printf("Please enter your name:  ");
			getchar();//needed to collect input
			fgets(cd.name,sizeof(cd.name),stdin);
			printf("The date today is : %d/%d/%d\n",local->tm_mday,local->tm_mon+1,local->tm_year+1900);
			printf("Please enter the day you test:  ");
			fgets(cd.day,sizeof(cd.day),stdin);
			printf("Please enter the location you test:  ");
			fgets(cd.loc,sizeof(cd.loc),stdin);
			printf("Please enter your phone number:  ");
			fgets(cd.phone,sizeof(cd.phone),stdin);
			printf("Please enter your email:  ");
			fgets(cd.email,sizeof(cd.email),stdin);
			printf("Please enter your last known location:  ");
			fgets(cd.lastloc,sizeof(cd.lastloc),stdin);
			printf("Please enter your address:  ");
			fgets(cd.address,sizeof(cd.address),stdin);
		
			printf("Your information is:\n");
			printf("1.ID=%s\n",cd.id);
			printf("2.Name=%s",cd.name);
			printf("3.Test Date = %d/%d/%d\n",local->tm_mday,local->tm_mon+1,local->tm_year+1900);
			printf("4.Day = %s",cd.day);
			printf("5.Test Location = %s",cd.loc);
			printf("6.Phone No=%s",cd.phone);
			printf("7.Email=%s",cd.email);
			printf("8.Last Known Location=%s",cd.lastloc);
			printf("9.Address=%s\n",cd.address);
			fprintf(ptr,"%s\n%s%d/%d/%d\n%s%s%s%s%s%s%s\n%s\n",cd.id,cd.name,local->tm_mday,local->tm_mon+1,local->tm_year+1900,cd.day,cd.loc,cd.phone,cd.email,cd.lastloc,cd.address,cd.KKM,cd.tstatus);
			fprintf(loc,"%s\n%s%d\n%d\n%d\n%d\n%d\n%d\n",cd.id,cd.lastloc,local->tm_mday,local->tm_mon+1,local->tm_year+1900,local->tm_hour,local->tm_min,local->tm_sec);
			fflush(stdin);
		}
		
	}
	fclose(ptr);
	fclose(loc);
	int out;
	printf("Please enter\n1. Main Menu\n2. End\n");
	scanf("%d",&out);
	if (out == 1)
	{
		system("cls");
		mainmenu();
	}
	else if(out==2)
	{
		printf("thank you");
		exit(0);
	}
	
}
void modifyrec()
{
	system ("cls");
	FILE *ptr;
	FILE *temp;
	struct covid cd;
	int changes;
	if ((ptr=fopen("covid.txt","r+"))==NULL)
	{
		puimenu();
		printf("Error,file not exist\n\n");
	}
	else
	{
		char pid[15],arr[100],newd[100];
		if ((temp = fopen("temp.txt","a"))==NULL)
		{
			temp =fopen ("temp.txt","w");
		}
		printf("Please enter your ID: ");
		scanf("%s",pid);
		while (!feof(ptr))
		{
			fscanf(ptr,"%s",arr);
			if (!strcmp(pid,arr))
			{
				printf("ID=%s\n",arr);
				fscanf(ptr,"%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n",cd.name,cd.date,cd.day,cd.loc,cd.phone,cd.email,cd.lastloc,cd.address,cd.KKM,cd.tstatus);
				printf("Name: %s\nDate of test: %s\nDay of test: %s\nLocation: %s\nPhone Number: %s\nEmail: %s\nLast Known Location: %s\nAddress: %s\n",cd.name,cd.date,cd.day,cd.loc,cd.phone,cd.email,cd.lastloc,cd.address);		
			}
			else
			{
				fscanf(ptr,"%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n",cd.name,cd.date,cd.day,cd.loc,cd.phone,cd.email,cd.lastloc,cd.address,cd.KKM,cd.tstatus);
				fprintf(temp,"\n%s\n%s%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n",arr,cd.name,cd.date,cd.day,cd.loc,cd.phone,cd.email,cd.lastloc,cd.address,cd.KKM,cd.tstatus);
			}
		}
		printf("Please enter what you want to modify: \n");
		printf("1. Name\n2. Day of testing\n3. Test location\n4. Phone  Number\n5. Email\n6. Last Location\n7. Address \n8. Back\n");
		scanf("%d",&changes);
	re:	switch (changes)
		{
			case 1:
				printf("\nPlease re-enter your name:");
				getchar();
				fgets(newd,sizeof(newd),stdin);
				fprintf(temp,"\n%s\n%s%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n",arr,newd,cd.date,cd.day,cd.loc,cd.phone,cd.email,cd.lastloc,cd.address,cd.KKM,cd.tstatus);
				fclose(ptr);
				fclose(temp);
				remove("covid.txt");
				rename("temp.txt","covid.txt");
				printf("\n\n");
				contMenu();
				break;
			case 2:
				printf("Please re-enter your testing day:");
				getchar();
				fgets(newd,sizeof(newd),stdin);
				fprintf(temp,"\n%s\n%s\n%s\n%s%s\n%s\n%s\n%s\n%s\n%s\n",arr,cd.name,cd.date,newd,cd.loc,cd.phone,cd.email,cd.lastloc,cd.address,cd.KKM,cd.tstatus);
				fclose(ptr);
				fclose(temp);
				remove("covid.txt");
				rename("temp.txt","covid.txt");
				printf("\n\n");
				contMenu();
				break;
			case 3:
				printf("Please re-enter your testing location:");
				getchar();
				fgets(newd,sizeof(newd),stdin);
				fprintf(temp,"\n%s\n%s\n%s\n%s%s\n%s\n%s\n%s\n%s\n%s\n",arr,cd.name,cd.date,cd.day,newd,cd.phone,cd.email,cd.lastloc,cd.address,cd.KKM,cd.tstatus);
				fclose(ptr);
				fclose(temp);
				remove("covid.txt");
				rename("temp.txt","covid.txt");
				printf("\n\n");
				contMenu();
				break;
			case 4:
				printf("Please re-enter your phone  number:");
				getchar();
				fgets(newd,sizeof(newd),stdin);
				fprintf(temp,"\n%s\n%s\n%s\n%s\n%s%s\n%s\n%s\n%s\n%s\n",arr,cd.name,cd.date,cd.day,cd.loc,newd,cd.email,cd.lastloc,cd.address,cd.KKM,cd.tstatus);
				fclose(ptr);
				fclose(temp);
				remove("covid.txt");
				rename("temp.txt","covid.txt");
				printf("\n\n");
				contMenu();
				break;
			case 5:
				printf("Please re-enter your Email:");
				getchar();
				fgets(newd,sizeof(newd),stdin);
				fprintf(temp,"\n%s\n%s\n%s\n%s\n%s\n%s%s\n%s\n%s\n%s\n",arr,cd.name,cd.date,cd.day,cd.loc,cd.phone,newd,cd.lastloc,cd.address,cd.KKM,cd.tstatus);
				fclose(ptr);
				fclose(temp);
				remove("covid.txt");
				rename("temp.txt","covid.txt");
				printf("\n\n");
				contMenu();
				break;
			case 6:
				printf("Please re-enter your address:");
				getchar();
				fgets(newd,sizeof(newd),stdin);
				fprintf(temp,"\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s%s\n%s\n",arr,cd.name,cd.date,cd.day,cd.loc,cd.phone,cd.email,cd.lastloc,newd,cd.KKM,cd.tstatus);
				fclose(ptr);
				fclose(temp);
				remove("covid.txt");
				rename("temp.txt","covid.txt");
				printf("\n\n");
				contMenu();
				break;
			case 7:
				puimenu();
				break ;
			default:
				printf("Error!!\n\n");
				fflush(stdin);
				printf("Please re-enter your choice:  ");
				scanf("%d",&changes);
				goto re;
				break;
				
		}
			
	}
	int out;
	printf("Please enter\n1. Main Menu\n2. End\n");
	scanf("%d",&out);
	if (out == 1)
	{
		system("cls");
		mainmenu();
	}
	else if(out==2)
	{
		printf("thank you");
		exit(0);
	}
	
}
void teststatus()
{
	system ("cls");
	fflush(stdin);
	FILE *ptr;
	struct covid cd;
	if ((ptr=fopen("covid.txt","r+"))==NULL)
	{
		printf("Error,file not exist");
		puimenu();
	}
	else
	{
		char pid[50],arr[50];
		printf("Please enter your ID:  ");
		scanf("%s",pid);
		while(!feof(ptr))
		{
			fscanf(ptr,"%s",arr);
			if (!strcmp(pid,arr))
			{
				printf("ID=%s\n",arr);
				fscanf(ptr,"%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n",cd.name,cd.date,cd.day,cd.loc,cd.phone,cd.email,cd.lastloc,cd.address,cd.KKM,cd.tstatus);
				printf("Test status = %s\n",cd.tstatus);		
			}
		}
	}
	fclose(ptr);
	int out;
	printf("Please enter\n1. Main Menu\n2. End\n");
	scanf("%d",&out);
	if (out == 1)
	{
		system("cls");
		mainmenu();
	}
	else if(out==2)
	{
		printf("thank you");
		exit(0);
	}
}

void lastloc()
{
	system ("cls");
	time_t tday;//time variable
	time(&tday);//obtian time now
	struct tm *local = localtime(&tday);//filled the structure with time,tm cannot be change
	struct covid cd;
	FILE *ptr;
	FILE *loc;
	FILE *temp;
	FILE *temp2;
	char pid[15],arr[100],newd[100];
	int d,m,y,h,mi,s,i=0;
	if ((ptr=fopen("covid.txt","r+"))==NULL)
	{
		printf("Error,file not exist");
	}
	else
	{
		if ((temp = fopen("temp.txt","a"))==NULL)
		{
			temp =fopen ("temp.txt","w");
		}
		else 
		{
			if ((loc = fopen("loc.txt","a"))==NULL)
			{
				loc= fopen("loc.txt","w");
				lastloc();
			}
			else
			{
				if ((temp2 = fopen("temp2.txt","a"))==NULL)
				{
					temp2 = fopen("temp2.txt","w");
					lastloc();
				}
				else
				{
					printf("Please enter your ID: ");
					scanf("%s",pid);
					while (!feof(ptr))
					{
						fscanf(ptr,"%s",arr);
						if (!strcmp(pid,arr))
						{
							printf("ID=%s\n",arr);
							fscanf(ptr,"%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n",cd.name,cd.date,cd.day,cd.loc,cd.phone,cd.email,cd.lastloc,cd.address,cd.KKM,cd.tstatus);
							printf("Name: %s\nDate of test: %s\nDay of test: %s\nLocation: %s\nPhone Number: %s\nEmail: %s\nLast Known Location: %s\nAddress: %s\n",cd.name,cd.date,cd.day,cd.loc,cd.phone,cd.email,cd.lastloc,cd.address);	
							while (!feof(loc))
							{
								fscanf(loc,"%s\n%s%d\n%d\n%d\n%d\n%d\n%d\n",cd.id,cd.lastloc,&d,&m,&y,&h,&mi,&s);
								if (d==local->tm_mday&&m==local->tm_mon+1&&y==local->tm_year+1900)
								{
									i++;
									printf("%d",i);
									if (i>2)
									{
										printf("You have entered twice today");
									}
									
								}
								else
								{
									goto one;
								}
							}		
						}	
					}
					one :printf("Please re-enter your last location:");
					getchar();
					fgets(newd,sizeof(newd),stdin);
					fprintf(temp,"\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s%s\n%s\n%s\n",arr,cd.name,cd.date,cd.day,cd.loc,cd.phone,cd.email,newd,cd.address,cd.KKM,cd.tstatus);
					fprintf(temp2,"%s\n%s%d\n%d\n%d\n%d\n%d\n%d\n",arr,newd,local->tm_mday,local->tm_mon+1,local->tm_year+1900,local->tm_hour,local->tm_min,local->tm_sec);
				}	
			}
		}
	}			
	fclose(ptr);
	fclose(temp);
	fclose(loc);
	fclose(temp2);
	remove("covid.txt");
	remove("loc.txt");
	rename("temp.txt","covid.txt");
	rename("temp2.txt","loc.txt");
	printf("\n\n");
	contMenu();
}


void adminmenu()
{
	system ("cls");
	int choice;
		printf("\nHello, Admin!\n What do you want to do?\n1 - View PUI detail\n2 - Record PUI test detail and KKM in charge\n3 - Weekly Test Summary\n4 - Go back\n\t\t\tChoice: ");
		scanf("%d", &choice);
		switch (choice)
		{
			case 1:
			{
				adminViewDetail();
				break;
			}
			case 2:
			{
				recordTestDetail();
				break;
			}
			case 3:
			{
				weekSummary();
				break;
			}
			case 4:
			{
				system("cls");
				mainmenu();
				break;
			}
			default:
			{
				printf("Error!!");
				fflush(stdin);
				adminmenu();
				break;	
			}
		}
	 
}

void adminViewDetail()
{
	fflush(stdin);
	system("cls");
	
	FILE *fDet;
	struct covid cd;

	if((fDet=fopen("covid.txt","r")) == NULL)
	{
		printf("Error,file does not exist!\n");
	}
	else
	{
		printf("\nHere is all the PUI details:\n\n");
		fscanf(fDet,"%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n",cd.id,cd.name,cd.date,cd.day,cd.loc,cd.phone,cd.email,cd.lastloc,cd.address,cd.KKM,cd.tstatus);
		printf("%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n",cd.id,cd.name,cd.date,cd.day,cd.loc,cd.phone,cd.email,cd.lastloc,cd.address,cd.KKM,cd.tstatus);
		while(!feof(fDet))
		{
			fscanf(fDet,"%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n",cd.id,cd.name,cd.date,cd.day,cd.loc,cd.phone,cd.email,cd.lastloc,cd.address,cd.KKM,cd.tstatus);
			printf("--------------------------------------------------------------------------------------------------------\n");
			printf("PUI ID-Card No:\t\t%s\n", cd.id);
			printf("Name:\t\t%s\n",cd.name);
			printf("Test Date:\t\t%s\n",cd.date);
			printf("Phone No:\t\t%d\n",cd.phone);
			printf("Email:\t\t%d\n",cd.email);
			printf("Last Known Location:\t\t%d\n",cd.lastloc);
			printf("Address:\t\t%d\n",cd.address);
			printf("--------------------------------------------------------------------------------------------------------\n");
		}
		fclose(fDet);
	}
	int out;
	printf("Please enter\n1. Main Menu\n2. End\n");
	scanf("%d",&out);
	if (out == 1)
	{
		system("cls");
		mainmenu();
	}
	else if(out==2)
	{
		printf("thank you");
		exit(0);
	}
}
void recordTestDetail()
{
	system ("cls");
	FILE *ptr;
	FILE *temp;
	struct covid cd;
	int choice;
	if ((ptr=fopen("covid.txt","r+"))==NULL)
	{
		printf("Error,file not exist");
		puimenu();
	}
	else
	{
		char pid[15],arr[100],newd[100];
		if ((temp = fopen("temp.txt","a"))==NULL)
		{
			temp =fopen ("temp.txt","w");
		}
		printf("Please enter your ID: ");
		scanf("%s",pid);
		while (!feof(ptr))
		{
			fscanf(ptr,"%s",arr);
			if (!strcmp(pid,arr))
			{
				printf("ID=%s\n",arr);
				fscanf(ptr,"%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n",cd.name,cd.date,cd.day,cd.loc,cd.phone,cd.email,cd.lastloc,cd.address,cd.KKM,cd.tstatus);
				printf("%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n",cd.name,cd.date,cd.day,cd.loc,cd.phone,cd.email,cd.lastloc,cd.address);		
			}
			else
			{
				fscanf(ptr,"%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n",cd.name,cd.date,cd.day,cd.loc,cd.phone,cd.email,cd.lastloc,cd.address,cd.KKM,cd.tstatus);
				fprintf(temp,"%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n",arr,cd.date,cd.day,cd.loc,cd.phone,cd.email,cd.lastloc,cd.address,cd.KKM,cd.tstatus);
			}
		}
		printf("Please select what to update.\n1. KKM Personal In Charge\n2. Test status");
		scanf("%d",&choice);
		switch (choice)
		{
			case 1:
				printf("\nPlease update the KKM Personal In Charge:");
				getchar();
				fgets(newd,sizeof(newd),stdin);
				fprintf(temp,"\n%s\n%s%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n",arr,cd.name,cd.date,cd.day,cd.loc,cd.phone,cd.email,cd.lastloc,cd.address,newd,cd.tstatus);
				fclose(ptr);
				fclose(temp);
				remove("covid.txt");
				rename("temp.txt","covid.txt");
				printf("\n\n");
				contMenu();
				break;
			case 2:
				printf("\nPlease update the Test status:");
				getchar();
				fgets(newd,sizeof(newd),stdin);
				fprintf(temp,"\n%s\n%s%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n",arr,cd.name,cd.date,cd.day,cd.loc,cd.phone,cd.email,cd.lastloc,cd.address,cd.KKM,newd);
				fclose(ptr);
				fclose(temp);
				remove("covid.txt");
				rename("temp.txt","covid.txt");
				printf("\n\n");
				contMenu();
				break;
			default:
				printf("Error, PLease try again");
				fflush(stdin);
				recordTestDetail();
				break;	
		}
	} 
	int out;
	printf("Please enter\n1. Main Menu\n2. End\n");
	scanf("%d",&out);
	if (out == 1)
	{
		system("cls");
		mainmenu();
	}
	else if(out==2)
	{
		printf("thank you");
		exit(0);
	}
}

void weekSummary()
{
	system ("cls");
	struct covid cd;
	printf("\n\n");
	fflush(stdin);
	int freq[3][8]={0};
	int i, j;
	FILE *pSum;

	if((pSum = fopen("covid.txt", "r")) == NULL)
	{
		printf("File not exist!\n");
	}
	else
	{
		printf("Test Location\tMon\tTue\tWed\tThu\tFri\tSat\tSun\tTotal\n");
		while(!feof(pSum))
		{
			int f=0;
			fscanf(pSum,"%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n",cd.id,cd.name,cd.date,cd.day,cd.loc,cd.phone,cd.email,cd.lastloc,cd.address,cd.KKM,cd.tstatus);
			if (!strcmp(cd.loc,"Kuching")||!strcmp(cd.loc,"kuching")||!strcmp(cd.loc,"KUCHING"))
			{
				if(!strcmp(cd.day,"Monday")||!strcmp(cd.day,"monday")||!strcmp(cd.day,"MONDAY"))
				{
					freq[0][0]++;
				}
				if(!strcmp(cd.day,"Tuesday")||!strcmp(cd.day,"tuesday")||!strcmp(cd.day,"TUESDAY"))
				{
					freq[0][1]++;
				}
				if(!strcmp(cd.day,"Wednesday")||!strcmp(cd.day,"wednesday")||!strcmp(cd.day,"WEDNESDAY"))
				{
					freq[0][2]++;
				}
				if(!strcmp(cd.day,"Thurssday")||!strcmp(cd.day,"thursday")||!strcmp(cd.day,"THURSDAY"))
				{
					freq[0][3]++;
				}
				if(!strcmp(cd.day,"Friday")||!strcmp(cd.day,"friday")||!strcmp(cd.day,"FRIDAY"))
				{
					freq[0][4]++;
				}
				if(!strcmp(cd.day,"Saturday")||!strcmp(cd.day,"saturday")||!strcmp(cd.day,"SATURDAY"))
				{
					freq[0][5]++;
				}
				if(!strcmp(cd.day,"Sunday")||!strcmp(cd.day,"sunday")||!strcmp(cd.day,"SUNDAY"))
				{
					freq[0][6]++;
				}
			}
			else if (!strcmp(cd.loc,"Kota Samarahan")||!strcmp(cd.loc,"kota samarahan")||!strcmp(cd.loc,"KOTA SAMARAHAN"))
			{
				if(!strcmp(cd.day,"Monday")||!strcmp(cd.day,"monday")||!strcmp(cd.day,"MONDAY"))
				{
					freq[1][0]++;
				}
				if(!strcmp(cd.day,"Tuesday")||!strcmp(cd.day,"tuesday")||!strcmp(cd.day,"TUESDAY"))
				{
					freq[1][1]++;
				}
				if(!strcmp(cd.day,"Wednesday")||!strcmp(cd.day,"wednesday")||!strcmp(cd.day,"WEDNESDAY"))
				{
					freq[1][2]++;
				}
				if(!strcmp(cd.day,"Thurssday")||!strcmp(cd.day,"thursday")||!strcmp(cd.day,"THURSDAY"))
				{
					freq[1][3]++;
				}
				if(!strcmp(cd.day,"Friday")||!strcmp(cd.day,"friday")||!strcmp(cd.day,"FRIDAY"))
				{
					freq[1][4]++;
				}
				if(!strcmp(cd.day,"Saturday")||!strcmp(cd.day,"saturday")||!strcmp(cd.day,"SATURDAY"))
				{
					freq[1][5]++;
				}
				if(!strcmp(cd.day,"Sunday")||!strcmp(cd.day,"sunday")||!strcmp(cd.day,"SUNDAY"))
				{
					freq[1][6]++;
				}
			}
			else if (!strcmp(cd.loc,"Serian")||!strcmp(cd.loc,"SERIAN")||!strcmp(cd.loc,"serian"))
			{
				if(!strcmp(cd.day,"Monday")||!strcmp(cd.day,"monday")||!strcmp(cd.day,"MONDAY"))
				{
					freq[2][0]++;
				}
				if(!strcmp(cd.day,"Tuesday")||!strcmp(cd.day,"tuesday")||!strcmp(cd.day,"TUESDAY"))
				{
					freq[2][1]++;
				}
				if(!strcmp(cd.day,"Wednesday")||!strcmp(cd.day,"wednesday")||!strcmp(cd.day,"WEDNESDAY"))
				{
					freq[2][2]++;
				}
				if(!strcmp(cd.day,"Thurssday")||!strcmp(cd.day,"thursday")||!strcmp(cd.day,"THURSDAY"))
				{
					freq[2][3]++;
				}
				if(!strcmp(cd.day,"Friday")||!strcmp(cd.day,"friday")||!strcmp(cd.day,"FRIDAY"))
				{
					freq[2][4]++;
				}
				if(!strcmp(cd.day,"Saturday")||!strcmp(cd.day,"saturday")||!strcmp(cd.day,"SATURDAY"))
				{
					freq[2][5]++;
				}
				if(!strcmp(cd.day,"Sunday")||!strcmp(cd.day,"sunday")||!strcmp(cd.day,"SUNDAY"))
				{
					freq[2][6]++;
				}
			}
			
		}
		printf("a) Kuching\t");
		for(i = 0; i < 1; i++)
		{
			for(j = 0; j < 7; j++)
			{
				printf("%d\t", freq[i][j]);
			}
			printf("%d", freq[0][0]+freq[0][1]+freq[0][2]+freq[0][3]+freq[0][4]+freq[0][5]+freq[0][6]);
			printf("\n");
		}
		printf("b) Kota Samarahan\t\t");
		for(i = 1; i < 2; i++)
		{
			for(j = 0; j < 7; j++)
			{
				printf("%d\t", freq[i][j]);
			}
			printf("%d", freq[1][0]+freq[1][1]+freq[1][2]+freq[1][3]+freq[1][4]+freq[1][5]+freq[1][6]);
			printf("\n");
		}
		printf("c) Serian\t\t");
		for(i = 2; i < 3; i++)
		{
			for(j = 0; j < 7; j++)
			{
				printf("%d\t", freq[i][j]);
			}
			printf("%d", freq[2][0]+freq[2][1]+freq[2][2]+freq[2][3]+freq[2][4]+freq[2][5]+freq[2][6]);
			printf("\n");
		}
	}
	fclose(pSum);
	fflush(stdin);
	int out;
	printf("Please enter\n1. Main Menu\n2. End\n");
	scanf("%d",&out);
	if (out == 1)
	{
		system("cls");
		mainmenu();
	}
	else if(out==2)
	{
		printf("thank you");
		exit(0);
	}
}

void contMenu()
{
	system ("cls");
	fflush(stdin);
	char choice;
	printf("Do you want to continue[Y/N]?\nChoice: ");
	scanf("%c", &choice);
	if(choice == 'Y'||choice == 'y')
	{
		system("cls");
		mainmenu();
	}
	else
	{
		system("cls");
		printf("\nThank you for using our system! Take Care!");
	}

}
