//
//  main.c
//  Mach-1
//
//  Created by Surya Dheeshjith on 02/03/19.
//  Copyright © 2019 Surya Dheeshjith. All rights reserved.
//

#include <stdio.h>
#define MAX 100
#define MAX_S 11.11
#define MIN_S 5.5

struct signal{
  
    int rtimer;
    int gtimer;
    
};

typedef struct signal signal;


//Assuming timer starts from 0 at start of trip
//Red timer starts first.


void findOptimum(signal s[],int n,float sDist[])
{
    float optimumSpeed[MAX],speed_max,speed_low;
    int l[MAX],h[MAX],i=0,ct,flag1,flag2=0,flag3,prevct[MAX],prevtime[MAX+1],backtrack[MAX],k=0;//flag2 for backtracking
    for(i=0;i<n;i++)
    {
        prevct[i]=-1;
        prevtime[i]=0;
        l[i]=s[i].rtimer;
        h[i]=l[i]+s[i].gtimer;
        backtrack[i]=0;
    }
    i=0;
    while(i<n) // Every signal in destination
    {
        ct=0;
        flag1=1;//To exit inner while
        flag3=0;//To calculate initial l and h values for later signals
        //printf("Hello");
        while(flag1) //
        {
           
        
            ////////////////////////////////
            //Initializing l[i] and h[i]
            /////////////////////////////////
            
            if(i==0&&ct==0)
            {
                //
            }
            else if(ct==0||flag3==1)
            {
                //printf("Heyy");
                if(l[i]<prevtime[i])
                {
                    if(h[i]>prevtime[i])//Under green light
                    {
                        l[i]=0;
                        h[i]=h[i]-prevtime[i];
                        flag3=0;
                        ct=0;
                        
                    }
                    else
                    {
                        flag3=1;
                        l[i]+=s[i].rtimer+s[i].gtimer;
                        h[i] = l[i]+s[i].gtimer;
                        ct++;
                        continue;
                    }
                }
                else{
                    l[i] = l[i]-prevtime[i];
                    h[i] = l[i]+s[i].gtimer;
                    flag3=0;
                    ct=0;
                }
            
            }
            else
            {
                l[i]+=s[i].rtimer+s[i].gtimer;
                h[i] =l[i]+s[i].gtimer;
            }
            
            //////////////////////////////////
            //For backtracking taking the next green light
            if(flag2==1 && ct==0)
            {
                while(flag2==1 && ct != prevct[i])//Backtracking
                {
                    ct++;
                    l[i]+=s[i].rtimer+s[i].gtimer;
                    h[i] =l[i]+s[i].gtimer;
                    continue;
                }
                l[i]+=s[i].rtimer+s[i].gtimer;
                h[i] =l[i]+s[i].gtimer;
                ct++;
            }
            /////////////////////////
            
            //TO CHECK
            //???????????????????????//
            printf("\n%d - %d %d\n",i,l[i],h[i]);
            printf("Prev time - %d\n",prevtime[i]);
            //???????????????????????//
            
            //////////////////////////////////////////////////////
            //Finding Max and low speeds to get green light
            ////////////////////////////////////////////////
            
            
            speed_max = sDist[i]/l[i];
            speed_low = sDist[i]/h[i];
            
            ///////////////////////////////////////////
            //Finding Optimum speed
            /////////////////////////////////////////
            
            
            if(speed_max>MAX_S)
            {
                if(speed_low>MAX_S)
                {
                    ct++;
                    continue;
                }
                
                else
                {
                    optimumSpeed[i]=MAX_S;
                    prevtime[i+1]=prevtime[i]+sDist[i]/MAX_S;
                    flag1=0;
                    flag2=0;
                    prevct[i]=ct;
                    if(backtrack[i+1]==1)
                    {
                        backtrack[i+1]=0;
                    }
                }
            }
            else if(speed_max<=MAX_S && speed_max>=MIN_S) //else if(speed_max>=MIN_S)
            {
                optimumSpeed[i] = speed_max;
                prevtime[i+1]=prevtime[i]+sDist[i]/speed_max;
                flag1=0;
                flag2=0;
                prevct[i]=ct;
                if(backtrack[i+1]==1)
                {
                    backtrack[i+1]=0;
                }
            }
            
            else if(speed_low<MIN_S) //If speed_max<MIN_S then speed_low<MIN_S //else
            {
                if(i==0) //|| flag2==1 )//|| prevct[i-1]==-2)//Preventing backtracking here.
                {
                    optimumSpeed[i]=speed_low;
                    prevtime[i+1]=prevtime[i]+sDist[i]/speed_low;
                    flag1=0;
                    flag2=0;
                    prevct[i]=ct;
                    
                    
                }
                else
                {
                flag2=1;
                flag1=0;
                l[i-1]=s[i-1].rtimer;
                h[i-1]=l[i-1]+s[i-1].gtimer;
                backtrack[i]=1;
                //prevtime[i]=;
                printf("Backtracking.......");
                //check
                }
                //Backtracking
            }
            
            
            //////////////////////////////////////////////
            ct++;
            
        }
        
    if(flag2==0)
        i++;
        
    else
        i--;
        
        

    }
    for(i=0;i<n-1;i++)
    printf("%f->",optimumSpeed[i]);
    printf("%f",optimumSpeed[i]);
}




int main(int argc, const char * argv[]) {
    
    //INITIALIZATION
    /////////////////////////////////////////
    float tDist, sDist[MAX],sum=0,last_stretch;
    int curr_hr,curr_min,curr_s,i,n;
    signal s[MAX];
    
    ///////////////////////////////////////
    //USER INPUT
    /////////////////////////////////////////
    //printf("Enter current time (HR:MIN:S): ");
    //scanf("%d:%d:%d",&curr_hr,&curr_min,&curr_s);
    //printf("Enter the total distance : ");
    //scanf("%f",&tDist);
    printf("Enter the number of signals in route : ");
    scanf("%d",&n);
    
    printf("Enter the distances between signals :\n");
    for(i =0;i<n;i++)
    {
        scanf("%f",&sDist[i]);
        sum+=sDist[i]; // To calculate distance between last signal and destination (Last stretch)
        
    }
   // last_stretch = tDist - sum; //
    
    printf("Enter time of green and red light for signals : \n");
    for(i=0;i<n;i++)
    {
        scanf("%d %d",&s[i].gtimer,&s[i].rtimer);
    }
    /////////////////////////////////////////////////
    findOptimum(s,n,sDist); // Function call
    
    return 0;
}
