#include<string.h>
#include<conio.h>
#include"calcu22.cpp"

void main()

{
   int i=0,j=0,c=0,d=0,gofrom=0,gotill=0,gofrom2=0,gotill2=0,dlen2=0,
     isover=1 ,err=0;
   float answer=0;
   char exp[80],dummy2[80],expm[80],brakt[80],
	braktans[30],bopen[30],rest[80] ;

   clrscr();

 afresh:

   for ( i=0;i<80;i++)
     {
       exp[i]='a';
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

 cout<<"e:";
 cin>>exp;

      if(exp[0]=='e'||exp[0]=='E') goto theend;


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
     }
	 //cout<<endl<<dummy2<<":";
	 //cout<<endl<<dummy2<<"\n"<<dlen2;

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
		  cout<<endl<<"e:"<<answer;
		  goto end;
		}

      /******* otherwise following for in do determines its position *******/
	/******** actually it recognises most nested first to open bracket**/

      err=braktcheck(dummy2);
      if(err)
       {
	cout<<"\n\nSYNTAX ERROR !!!    Enter again or e+<enter> to exit\n";
	goto afresh;
       }

     for(i=0;i<dlen2;i++)
       {
	if(dummy2[i]=='s')  gofrom=i+1;
	if(dummy2[i]=='e')
			 {
			   gotill=i-1;
			   break;
			 }
       }
	    //cout<<"\ngofrom:"<<gofrom<<"  gotill"<<gotill;getch();
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
		 //cout<<endl<<"gofrom2:"<<gofrom2<<" gotill2:"<<gotill2;
		for(j=gofrom2,d=0;j<=gotill2;j++,d++)
		  {
		    bopen[d]=exp[j];
		  }
		   //so,bopen is the coefficient of bracket.
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

     cout<<endl<<"="<<exp;

 }while(1);/////////////////////////////////do ends///////////////////////

end:

cout<<"\n\n Enter new question or press e+<enter> to exit..\n";
goto afresh;

theend:

cout<<"\n\nend";
getch();
}














