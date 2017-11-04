#include<stdio.h>
#include<conio.h>
#include<iostream.h>
#include<string.h>
#include<ctype.h>

float strtoflot(char []);
float evaluate(float [],char [],int,int);
void initialise(float[],char[],char[],char[]);
void flottostr(char a[80],float num);
float solve(char exp[80]);
float expression(char exp[80]);
float bsolve(char [80]);
void checkexp(char exp[80]);
int braktcheck(char dummy2[80]);
float funceval(char [80],float);

/************************************************************************/


float expression(char exp[80])//void main()
{

 int i,j,t,dlen,start,end,go,k,l,n1,n2;
 float operands[80],answer;
 char operators[80],dummy[80],temp[80];


//initialisation to prevent garbage values
initialise(operands,dummy,operators,temp);


		//set arrays
 dlen=0;  //dummylength

 for(i=0;exp[i]!='a';i++)     //scan exp and make dummy
 {
   if( isdigit(exp[i]))
     dummy[i]='d';
   else if(exp[i]=='.'||exp[i]=='\0')  dummy[i]=exp[i];
   else dummy[i]='o';

   dlen++;
 }
	       /*
		cout<<endl; ////
 for(i=0;i<dlen;i++)
 cout<<dummy[i];           getch();    */


  go=0; //ie. permission to do strtoflot(string to float)

 for(i=0,j=0;i<dlen;i++)
 {
  if(i==0)   start=i;
  else if(dummy[i]=='d'&&dummy[i-1]=='o')  start=i;

  if(dummy[i]=='.')   ;

  else if(dummy[i]=='o'||dummy[i]=='\0') {
			operators[j++]=exp[i];
			end=i-1;
			go=1;
			}
   if(go==1)
   {
    for(k=start,l=0;k<=end;k++,l++)
    {
     temp[l]=exp[k];
    }
    temp[l]='\0';

    operands[j-1]=strtoflot(temp);
    go=0;
   }
  }
	      /*//this hidden segment not required
  for(i=dlen;dummy[i]!='o';i--)
  {
   ;
  }

  start=i+1;
  end=dlen-1;

   for(k=start,l=0;k<=end;k++,l++)
    {
     temp[l]=exp[k];
    }
    temp[l]='\0';

    operands[j]=strtoflot(temp);         */

	    n1=j+1;
	    n2=j;
    /*
  cout<<endl;                                      ////
  for(i=0;i<j+1;i++)
  cout<<endl<<operands[i]<<"   "<<operators[i];
		cout<<endl<<n1<<"   "<<n2;
					  getch();   */
     //evaluate
   return(evaluate(operands,operators,n1,n2));
}


/**************************************************************************/

float strtoflot(char a[80])

{
  int i,j,p,strtforloop,endforloop,l,neg=0;
  float r=0,m=0,n=0,t; //NOTE:m=integral part of float,n=fractional part
  l=strlen(a); //in case exp starts with - sign,length of a(received string)
  p=l-1;       //is 0 and nothing is done here except that 0 is returned
	       //because both m and n are initialised to 0,and
	       //function returns m-n ie. 0

    if(a[0]=='-')
      {
       neg=1;
       endforloop=1;
      }

    else endforloop=0;

  for(i=0;i<l;i++)
    {
       if(a[i]=='.')
       {p=i;
       break;}
    }

		//      printf("\np=%d",p);
     if(p==l-1)
	  strtforloop=p;
     else strtforloop=p-1;

  for(i=strtforloop,t=1;i>=endforloop;i--,t*=10)
  {
   m+=int(a[i]-'0')*t;      //printf("\nm=%f",m);

  }

   for(j=p+1,t=10;j<=l-1;j++,t*=10)
  {

   n+=int(a[j]-'0')/(t);    //printf("\nn=%f",n);
  }

  r=m+n;                    //printf("\nr=%f",r);

  if(neg)
      return (0.0-r);
  else return r;
 }



 /*************************************************************************/

float evaluate(float oprn[80],char oper[80],int l1,int l2)

{
 int i,j;
 float m=0,n=0,r=0;

 afresh1:

 for(i=0;i<=l2;i++)
 {
  if(oper[i]=='/')
   {
    oprn[i]=oprn[i]/oprn[i+1];

    for(j=i+2;j<=l1;j++)
    oprn[j-1]=oprn[j];

    for(j=i+1;j<=l2;j++)
    oper[j-1]=oper[j];

    l1--;  l2--;
    goto afresh1;
   }
 }
			/*
  cout<<endl<<"after  /\n";       ////
  for(i=0;i<l1;i++)
  cout<<endl<<oprn[i]<<"   "<<oper[i];
		cout<<endl<<l1<<"   "<<l2;     */

   afresh2:

 for(i=0;i<=l2;i++)
 {
  if(oper[i]=='*')
   {
    oprn[i]=oprn[i]*oprn[i+1];

    for(j=i+2;j<=l1;j++)
    oprn[j-1]=oprn[j];

    for(j=i+1;j<=l2;j++)
    oper[j-1]=oper[j];

    l1--;  l2--;
    goto afresh2;
   }
 }
		  /*
  cout<<endl<<"after * \n";                    ////
  for(i=0;i<l1;i++)
  cout<<endl<<oprn[i]<<"   "<<oper[i];
		cout<<endl<<l1<<"   "<<l2;
		getch(); */

  for(i=0;i<=l2;i++)
 {
   if(i==0)  m+=oprn[i];
   if(oper[i]=='+') m+=oprn[i+1];
 }

 /*
  cout<<endl<<"after + \n";                                  ////
  for(i=0;i<l1;i++)
  cout<<endl<<oprn[i]<<"   "<<oper[i]<<"  m="<<m;
		cout<<endl<<l1<<"   "<<l2;  */

   for(i=0;i<=l2;i++)
 {
    if(oper[i]=='-') n+=oprn[i+1];
 }
		   /*
  cout<<endl<<"after -\n";                         ////
  for(i=0;i<l1;i++)
  cout<<endl<<oprn[i]<<"   "<<oper[i]<<"  n="<<n;
		cout<<endl<<l1<<"   "<<l2;   */

 r=m-n;

 return r;
}

/***********************************************************************/
void initialise(float operands[80],char dummy[80],
	       char operators[80],char temp[80])
{
int i;
 for (i=0;i<80;i++)
{
 operands[i]=0;
 operators[i]='a';
  dummy[i]='a';
   temp[i]='a';
}
 return;
}

/************************************************************************/

void flottostr(char a[80],float num)
{
int c,i=0,j=0,integ,t=1,l=0,nofdigits=0;
char integdig[30],fracdig[30];
float frac=0.0;


 for (i=0;i<30;i++)
  {
    integdig[i]='a';
    fracdig[i]='a';
  }

if(num>=0)
  { //case num > 0 begins
  integ=num/1;   //         cout<<"\ninteg="<<integ;
  frac=num-integ;  //     printf("\nfrac=%f",frac); // cout<<"\nfrac="<<frac;

    if(integ==0)
     {  //if1b   --to set integdig
       integdig[0]='0';
       integdig[1]='\0';
      } //if1f

    else
    {  //else1b
      if(integ>0&&integ<10)  nofdigits=1;//if1.1bf

      else
      {  //else1.1b
       for(c=10,i=2;c<=integ;c*=10,i++)
	{ //forinelse1.1b
	  if (integ>=c&&integ<(c*10) )
	   {
	    nofdigits=i;
	    break;
	   }
	} //forinelse1.1f
      }  //else1.1f

	 for(i=0,t=1;i<nofdigits;i++,t*=10)
	  {    //forinelse1b
	   integdig[i]=char( (integ/t)%10 + 48) ;

	  }    //forinelse1f

  integdig[i]='\0';
     }  //else1f   --setting integdig over

  for(i=strlen(integdig)-1,j=0;i>=0;i--,j++)
   {
     a[j]=integdig[i];
   }
	     /*
   cout<<"\nafterintg:";
	for(i=0;i<30;i++)
    {
      cout<<"\nintegdig:"<<integdig[i]<<"  a:"<<a[i];
      if(i%10==0) getch();
    }          */

       a[j]='.';
	 l=j+1;
	 /*
	 cout<<"\nl afterint:"<<l;
	 cout<<"\nafterpoint";
	 for(i=0;i<30;i++)
    {
      cout<<"\na:"<<a[i];
      if(i%10==0) getch();
    }      */


  for( i=0,t=10;i<4;i++,t*=10)
   {
    fracdig[i]=char( int(((frac*t)/(1))) %10 + 48) ;
   }

  fracdig[i]='\0';

  for(i=0,j=l;i<strlen(fracdig);i++,j++)
   {
     a[j]=fracdig[i];
   }

	a[j]='\0';
	 l=j+1;
	     /*
	 cout<<"\nafterfrac:";
   for(i=0;i<30;i++)
    {
      cout<<"\nfracdig:"<<fracdig[i]<<"  a:"<<a[i];
      if(i%10==0) getch();
    }
      cout<<"::"<<l;    */

  }//case num>0 over

else //case num<0 begins
 {
  a[0]='-';
  num=num*(-1);
   integ=num/1;           // cout<<"\ninteg="<<integ;
  frac=num-integ;        // cout<<"\nfrac="<<frac;

  if(integ==0)
   {
    integdig[0]='0';
    integdig[1]='\0';
   }

  else
   {
       if(integ>0&&integ<10)  nofdigits=1;
      else
      {
       for(c=10,i=2;c<=integ;c*=10,i++)
	{
	  if (integ>=c&&integ<(c*10) )
	   {
	    nofdigits=i;
	    break;
	   }
	}
      }

	 for(i=0,t=1;i<nofdigits;i++,t*=10)
	  {
	   integdig[i]=char( (integ/t)%10 + 48) ;

	  }

  integdig[i]='\0';
   /*  i=0;  t=1;
     do
      {
       integdig[i++]=char( (integ/t)%10 + 48) ;
       t*=10;
      }while(integdig[i-1]!='0');

      integdig[i-1]='\0';  */
   }

  for(i=strlen(integdig)-1,j=1;i>=0;i--,j++)
   {
     a[j]=integdig[i];
   }
		     /*
   cout<<"\nafterintg:";
	for(i=0;i<30;i++)
    {
      cout<<"\nintegdig:"<<integdig[i]<<"  a:"<<a[i];
      if(i%10==0) getch();
    }                  */

       a[j]='.';
	 l=j+1;
			 /*
	 cout<<"\nafterpoint";
	 for(i=0;i<30;i++)
    {
      cout<<"\na:"<<a[i];
      if(i%10==0) getch();
    }                      */


  for( i=0,t=10;i<4;i++,t*=10)
   {
    fracdig[i]=char( int(((frac*t)/(1))) %10 + 48) ;
   }

  fracdig[i]='\0';

  for(i=0,j=l;i<strlen(fracdig);i++,j++)
   {
     a[j]=fracdig[i];
   }

	a[j]='\0';
	 l=j+1;
			  /*
	 cout<<"\nafterfrac:";
   for(i=0;i<30;i++)
    {
      cout<<"\nfracdig:"<<fracdig[i]<<"  a:"<<a[i];
      if(i%10==0) getch();
    }
      cout<<"::"<<l;        */
 }//case num<0 over
  return;
}
/************************************************************************/


float solve(char exp[80])

{
 int i,j,k,t,dlen,start1,end1,start2,end2,neg,dodiv,domul,isover=1;
 float answer,a,b,finans=0;
 char expm[80],dummy[80],temp[30],ans[30],rest[80];

  for (i=0;i<80;i++)
   {
    dummy[i]='a';

    expm[i]='a';
    rest[i]='a';
   }
  for (i=0;i<30;i++)
   {
    temp[i]='a';
    ans[i]='a';
   }

   checkexp(exp);

do
 {
  isover=1;
  dodiv=0;
  domul=0;
  for(i=0;i<80;i++)
     {
       if(exp[i]=='/')
	 {
	  isover=0;
	  dodiv=1;
	  break;
	 }
     }

   for(i=0;i<80;i++)
     {
       if(exp[i]=='*'&& (dodiv==0) )
	 {
	  isover=0;
	  domul=1;
	  break;
	 }
     }

   if(isover)
     {
      break;
     }


  dlen=0;  //dummylength
  for(i=0;exp[i]!='a';i++)     //scan exp and make dummy
  {
   if( isdigit(exp[i]))
     dummy[i]='d';
   else if(exp[i]=='.'||exp[i]=='\0')  dummy[i]=exp[i];
   else dummy[i]='o';

   dlen++;
  }
		  /*
		cout<<endl; ////
 for(i=0;i<dlen;i++)
 cout<<dummy[i];           getch();     */


  for(i=0;i<dlen;i++)
   {
    if(dodiv)
    {
    if(exp[i]=='/')
     {
       for(j=i-1; ;j--)
	{
	 if(j==0)  {
		    start1=0;
		    break;
		   }
	 else if(dummy[j]=='o')
		   {
		    start1=j+1;
		    break;
		   }
	}
	end1=i-1;
       for(j=start1,k=0;j<=end1;j++,k++)
	{
	 temp[k]=exp[j];
	}
	temp[k]='\0';
	a=strtoflot(temp);     //cout<<"\ntemp1/="<<temp<<"\na/="<<a;

       if(exp[i+1]=='-')   neg=1;
       else                neg=0;

       start2=i+1;

       if(neg)    k=j+2;
       else       k=j+1;
	 for(j=k; !(dummy[j]=='\0'||dummy[j]=='o');j++)
	  {
	   ;
	  }
	 end2=j-1;

       for(j=start2,k=0;j<=end2;j++,k++)
	{
	 temp[k]=exp[j];
	}
       temp[k]='\0';
       b=strtoflot(temp);      //cout<<"\ntemp2="<<temp<<"\nb/="<<b;

       answer=a/b;             //cout<<"\nans/="<<answer;
       goto refresh;
     }
    }    //if in for in do ends
   if(domul)
    {
    if(exp[i]=='*')
     {
       for(j=i-1; ;j--)
	{
	 if(j==0)  {
		    start1=0;
		    break;
		   }
	 else if(dummy[j]=='o')
		   {
		    start1=j+1;
		    break;
		   }
	}
	end1=i-1;
       for(j=start1,k=0;j<=end1;j++,k++)
	{
	 temp[k]=exp[j];
	}
       temp[k]='\0';
       a=strtoflot(temp);     //cout<<"\ntemp1*="<<temp<<"\na*="<<a;

       if(exp[i+1]=='-')   neg=1;
       else                neg=0;

       start2=i+1;

       if(neg)    k=j+2;
       else       k=j+1;
	 for(j=k; !(dummy[j]=='\0'||dummy[j]=='o');j++)
	  {
	   ;
	  }
	 end2=j-1;

       for(j=start2,k=0;j<=end2;j++,k++)
	{
	 temp[k]=exp[j];
	}
	temp[k]='\0';
	b=strtoflot(temp);      //cout<<"\ntemp2*="<<temp<<"\nb*="<<b;

       answer=a*b;              //cout<<"\nans*="<<answer;
       goto refresh;
     } //if in for in do ends
    }

   } //for in do ends

   refresh:

     for(j=0,k=0;j<start1;j++,k++)
      {
       expm[k]=exp[j];
      }
    expm[k]='\0';

    flottostr(ans,answer);
    strcat(expm,ans);          //cout<<"\nafter e,a:\n"<<expm;

    for(j=end2+1,k=0;exp[j]!='\0';j++,k++)
     {
       rest[k]=exp[j];
     }
    rest[k]='\0';

    strcat(expm,rest);         //cout<<"\nafter e,r:\n"<<expm;

    for(j=0;j<80;j++)
     {
       exp[j]='a';
     }

    strcpy(exp,expm);        //cout<<"\nafter e,e:\n"<<expm;
			     //cout<<endl<<"="<<exp;
    for (i=0;i<80;i++)
     {
      expm[i]='a';
      dummy[i]='a';
      rest[i]='a';
     }
   for (i=0;i<30;i++)
     {
      temp[i]='a';
      ans[i]='a';
     }
 }while(1);//do ends


 for (i=0;i<80;i++)
     {
      dummy[i]='a';
     }

  dlen=0;  //dummylength

  for(i=0;exp[i]!='a';i++)     //scan exp and make dummy
  {
   if( isdigit(exp[i]))
     dummy[i]='d';
   else if(exp[i]=='.'||exp[i]=='\0')  dummy[i]=exp[i];
   else dummy[i]='o';

   dlen++;
  }
		      /*
		cout<<endl; ////
 for(i=0;i<dlen;i++)
 cout<<dummy[i];           getch(); */

 doagain:

 for(i=0;i<dlen;i++)
   {
   if(dummy[i]=='o'&&dummy[i+1]=='o')
    {
     if (  (exp[i]=='-'&&exp[i+1]=='-'  ) || (exp[i]=='+'&&exp[i+1]=='+' ) )
      {
	 exp[i]='+';
      for(j=i+1;j<80;j++)
       {
	exp[j]=exp[j+1];
       }
      }
     else if ( (exp[i]=='-'&&exp[i+1]=='+') || (exp[i]=='+'&&exp[i+1]=='-' ))
      {
	 exp[i]='-';
      for(j=i+1;j<80;j++)
       {
	exp[j]=exp[j+1];
       }
      }

     for (j=0;j<80;j++)
     {
      dummy[j]='a';
     }

     dlen=0;  //dummylength

    for(j=0;exp[j]!='a';j++)     //scan exp and make dummy
     {
      if( isdigit(exp[j]))
      dummy[j]='d';
      else if(exp[j]=='.'||exp[j]=='\0')  dummy[j]=exp[j];
      else dummy[j]='o';

      dlen++;
     }
     //cout<<endl<<"="<<exp;
     goto doagain;
    }
   }

		   /*
		cout<<endl; ////
 for(i=0;i<dlen;i++)
 cout<<dummy[i];           getch();          */



 for(i=0;exp[i]!='\0';i++)
   {
     for (k=0;k<30;k++)
      {
	temp[i]='a';
	ans[k]='a';
      }

		     //cout<<"\ni="<<i<<"  dummy[i]="<<dummy[i];
     if(exp[i]=='+'|| ( i==0 && dummy[i]=='d') )
       {               //               cout<<"\nin +";
	 if(dummy[i]=='d')   start1=i;
	 else start1=i+1;

	 for(j=i+1; !(dummy[j]=='\0'||dummy[j]=='o');j++)
	  {
	   ;
	  }
	 end1=j-1;
			//cout<<"\nstart+="<<start1<<" end+="<<end1;
	for(j=start1,k=0;j<=end1;j++,k++)
	 {
	  temp[k]=exp[j];
	 }
	  temp[k]='\0';
	  b=strtoflot(temp);    //  cout<<"\ntemp+="<<temp<<"\nb+="<<b;

				// cout<<"\nfai="<<finans;

	 finans+=b;             //cout<<"\nans+="<<finans;
       }
      else if(exp[i]=='-')
       {                        //cout<<"\nin -";
	 start1=i+1;

	 for(j=i+1; !(dummy[j]=='\0'||dummy[j]=='o');j++)
	  {
	   ;
	  }
	 end1=j-1;

	for(j=start1,k=0;j<=end1;j++,k++)
	 {
	  temp[k]=exp[j];
	 }
	  temp[k]='\0';
	  b=strtoflot(temp);     //cout<<"\ntemp-="<<temp<<"\nb-="<<b;

				 //cout<<"\nfai="<<finans;

	  finans-=b;             //cout<<"\nans-="<<finans;
       }

				//cout<<"\nans1p="<<finans; getch();
   }


 //cout<<"\nsolve ans="<<finans;
 return finans;
}

/***************************************************************************/

float bsolve(char exp[80])

{
   int i=0,j=0,c=0,d=0,gofrom=0,gotill=0,gofrom2=0,gotill2=0,dlen2=0,
     isover=1;
   float answer=0;
   char dummy2[80],expm[80],brakt[80],
		braktans[30],bopen[30],rest[80] ;


   for ( i=0;i<80;i++)
     {
       dummy2[i]='a';
       expm[i]='a';
       brakt[i]='a';
       rest[i]='a';
     }

     for ( i=0;i<30;i++)
     {
	braktans[i]='a';
	bopen[i]='a';
     }


     checkexp(exp);


 do
 {////////////////////////////////////do begins//////////////////////////
   /*********** do receives original or under calculation exp ***********/

     isover=1;
   for ( i=0;i<80;i++)
     {
       expm[i]='a';
       brakt[i]='a';
       rest[i]='a';
     }

   for (i=0;i<30;i++)
     {
	braktans[i]='a';
	bopen[i]='a';
     }
     gofrom=0;gotill=0;gofrom2=0;gotill2=0;
	/************in do exp is scanned and its dummy is made **********/

      dlen2=0;  //dummylength

   for(i=0;exp[i]!='a';i++)  /*******scan exp and make dummy *************/
     {
	if( isdigit(exp[i]))
	dummy2[i]='d';
	else if(exp[i]=='.'||exp[i]=='\0')  dummy2[i]=exp[i];
	else if(exp[i]=='(')  dummy2[i]='s';
	else if(exp[i]==')')  dummy2[i]='e';
	else dummy2[i]='o';

	dlen2++;
     }               /*
	   cout<<endl<<dummy2<<":";
	 cout<<endl<<dummy2<<"\n"<<dlen2;  */

       /******following for in do checks for absence of brackets in exp ***/
   for(i=0;i<80;i++)
     {
       if(dummy2[i]=='s'||dummy2[i]=='e')
	 {
	  isover=0;
	  break;
	 }
     }

  // cout<<"\nisover="<<isover<<"\nans=";

     if(isover) {/*****************if no brackets then just solve and end***/
		  answer=solve(exp);
		  //cout<<endl<<"e:"<<answer;
		  goto end;
		}

      /******* otherwise following for in do determines its position *******/
	/******** actually it recognises most nested first to open bracket**/

     for(i=0;i<dlen2;i++)
       {
	if(dummy2[i]=='s')  gofrom=i+1;
	if(dummy2[i]=='e')
			 {
			   gotill=i-1;
			   break;
			 }
       }

      /********** once bracket recognised , start further calculation *****/
	/*** it involves solving bracket and creating exp again to be ***/
	  /********* scanned as fresh problem in do loop *************/

	     for (j=gofrom,c=0;j<=gotill;j++,c++)
	      {
	       brakt[c]=exp[j];
	      }
	     brakt[c]='\0';

	     answer=solve(brakt); /****answer holds answer of bracket*/
	     //cout<<"\nbans="<<answer;

	     /***if there is a number just before bracket then ************/
		/********** set new exp as in folloig if in  do **********/
	     if(dummy2[gofrom-2]=='d')
	      {////////////////////if in do begins ////////////////////////
		gotill2=gofrom-2;

		for(j=gofrom-2;j>=0;j--)
		  {
		  if(!(dummy2[j]=='d'||dummy2[j]=='.') )
		    {
		      gofrom2=j+1;
		      break;
		    }
		  }

		for(j=gofrom2,d=0;j<=gotill2;j++,d++)
		  {
		    bopen[d]=exp[j];
		  }

		bopen[d]='\0';

		answer=answer*strtoflot(bopen);
		flottostr(braktans,answer);

		for(j=0,c=0;j<=(gofrom2-1);j++,c++)
		 {
		  expm[c]=exp[j];
		 }

		expm[c]='\0';
		strcat(expm,braktans);

	      }///////////////////if in do ends ////////////////////
	     else
	      {///////////////////else in do begins /////////////////

	       for(j=0,c=0;j<=(gofrom-2);j++,c++)
		 {
		  expm[c]=exp[j];
		 }
		 expm[c]='\0';
		 flottostr(braktans,answer);
		 strcat(expm,braktans);
	      }///////////////////else in do ends ///////////////////

	    for(j=gotill+2,c=0;exp[j]!='\0';j++,c++)
	     {
	      rest[c]=exp[j];
	     }
	      rest[c]='\0';

	     strcat(expm,rest);

	     for(j=0;j<80;j++)
	      {
	       exp[j]='a';
	      }

	      strcpy(exp,expm);

   for ( i=0;i<80;i++)
     {
       dummy2[i]='a';
     }

     //cout<<endl<<"="<<exp;

 }while(1);/////////////////////////////////do ends///////////////////////


end:
return answer;
}
/****************************************************************************/

void checkexp(char exp[80])
{
 int i,j,dlen;
 char dummy[80];

  checkagain:

    for (j=0;j<80;j++)
     {
      dummy[j]='a';
     }

     dlen=0;  //dummylength

    for(j=0;exp[j]!='a';j++)     //scan exp and make dummy
     {
      if( isdigit(exp[j]))
      dummy[j]='d';
      else if(exp[j]=='.'||exp[j]=='\0')  dummy[j]=exp[j];
      else dummy[j]='o';

      dlen++;
     }

   for (i=0;i<dlen;i++)
    {
     if(dummy[i]=='.' && (dummy[i-1]!='d'|| i==0) )
      {

       for(j=dlen-1;j>=i;j--)
	{
	  exp[j+1]=exp[j];
	 }
	exp[i]='0';

	goto checkagain;
      }
    }

    return;
}
/**************************************************************************/

int braktcheck(char dummy2[80])

{
 int m=0;
 for(int i=0;dummy2[i]!='\0';i++)
  {
   if (dummy2[i]=='s')   m++;
   if (dummy2[i]=='e')   m--;
  }

  if(m==0)  return 0;
  else return 1;
}

/**************************************************************************/

float funceval(char y[80],float x_var)   //finds y at x_var
{                //y shd. have: digits,+,-,*,/,(,),x only in correct syntax
 int i,t;        // note that in string y , x is 'small x' only
 char y_cpy[80],y_dummy[80],temp[80],x_str[80];
 float y_value,ans;
		//adapted from funceval.cpp. so refer it for debugging if any
 for(i=0;i<80;i++)
  {
   y_cpy[i]  ='a';
   y_dummy[i]='a';
   temp[i]   ='a';
   x_str[i]  ='a';
  }

 for(i=0;i<80;i++)
  {
   y_cpy[i]=y[i];
  }

 flottostr(x_str,x_var);


 int no_of_x=0;

 for(i=0;i<80;i++)
   {
    if(y_cpy[i]=='x') no_of_x++;
   }


 for(int q=0;q<no_of_x;q++)
  {

  for(i=0;i<80;i++)
   {
    if(y_cpy[i]!='x')
     { y_dummy[i]=y_cpy[i]; }
    else
     {
      int j=i+1;

      int k,k2;
      for( k=i,k2=0;x_str[k2]!='\0';k++,k2++)
       { y_dummy[k]=x_str[k2]; }

       int s,s2;
      for( s=k,s2=j;y_cpy[s2]!='a';s++,s2++)
       { y_dummy[s]=y_cpy[s2]; }

      for(int t=0;t<80;t++)
       y_cpy[t]=y_dummy[t];

     }
   }

  }

 return(bsolve(y_cpy));
}
