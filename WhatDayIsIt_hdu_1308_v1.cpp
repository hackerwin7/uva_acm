#include<stdio.h>
int month_day[13]={0,31,28,31,30,31,30,31,31,30,31,30,31};//begin with 1
int leap_month_day[13]={0,31,29,31,30,31,30,31,31,30,31,30,31};//begin with 1
typedef struct date
{
    int year;
    int month;
    int day;
    int week;
}date,* date_link;
char week_map[8][10]={"","Monday","Tuesday","Wednesday","Thursday","Friday","Saturday","Sunday"};//begin with 1
char month_map[13][10]={"","January","February","March","April","May","June","July","August","September","October","November","December"};//begin with 1
int in_year,in_month,in_day;
date date_start,special_date[5];//begin with 1
bool is_leap(int year)
{
    if(year<=1582) return(year%4==0);
    else return((year%4==0&&year%100!=0)||(year%400==0));
}
int week_mod(int a,int b)
{
    return(a%b?a%b:b);
}
int week_sub(int a,int b)
{
    return(a-b>0?a-b:a-b+7);
}
int week_add(int a, int b)
{
    return(a+b);
}
int comp_date(date a,date b)
{
    int a_num=a.year*10000+a.month*100+a.day;//ip to number to compare ip easily
    int b_num=b.year*10000+b.month*100+b.day;
    return(a_num-b_num);
}
int get_week(date &start,date &rear)
{
    int flag=comp_date(start,rear);
    if(flag>0)
    {
        int total_day=0;
        //start target to start 1/1
        if(start.year>rear.year)
        {
            //complete month
            for(int mi=1;mi<=start.month-1;mi++)
            {
                total_day+=month_day[mi];
                //leap year
                if(mi==2&&is_leap(start.year)) total_day+=1; 
                //special cover the non-existent days
                if(start.year==1582&&mi==10) total_day-=10;
                if(start.year==1752&&mi==9) total_day-=11;
            }
            //complete day
            for(int di=1;di<=start.day-1;di++) total_day++;
            //special cover the non-existent days
            if(start.year==1582&&start.month==10&&start.day>=15&&1<=4) total_day-=10;
            if(start.year==1752&&start.month==9&&start.day>=14&&1<=2) total_day-=11;
        }
        else if(start.year==rear.year)//the dis days is on the same year
        {
            //front
            if(start.month>rear.month)
            {
                for(int di=1;di<=start.day-1;di++) total_day++;
                //special cover the non-existent days
                if(start.year==1582&&start.month==10&&start.day>=15&&1<=4) total_day-=10;
                if(start.year==1752&&start.month==9&&start.day>=14&&1<=2) total_day-=11;
            }
            else if(start.month==rear.month)
            {
                for(int di=start.day-1;di>=rear.day;di--) total_day++;
                //special cover the non-existent days
                if(start.year==1582&&start.month==10&&start.day>=15&&rear.day<=4) total_day-=10;
                if(start.year==1752&&start.month==9&&start.day>=14&&rear.day<=2) total_day-=11;
            }
            //middle
            if(start.month-1>rear.month)
            {
                for(int mi=start.month-1;mi>=rear.month+1;mi--)
                {
                    total_day+=month_day[mi];
                    //leap
                    if(mi==2&&is_leap(start.year)) total_day+=1;
                    //special cover the non-existent days
                    if(start.year==1582&&mi==10) total_day-=10;
                    if(start.year==1752&&mi==9) total_day-=11;
                }
            }
            //rear
            if(start.month>rear.month)
            {
                for(int di=month_day[rear.month];di>=rear.day;di--) total_day++;
                //leap
                if(is_leap(rear.year)&&rear.month==2) total_day+=1;
                //special cover the non-existent days
                if(rear.year==1582&&rear.month==10&&rear.day<=4&&month_day[rear.month]>=15) total_day-=10;
                if(rear.year==1752&&rear.month==9&&rear.day<=2&&month_day[rear.month]>=14) total_day-=11;
            }
        }
        //start to end  complete year
        if(start.year-1>rear.year)
        {
            for(int yi=start.year-1;yi>=rear.year+1;yi--) 
            {
                total_day+=is_leap(yi)? 366 : 365;
                //special cover the non-existent days
                if(yi==1582) total_day-=10;
                if(yi==1752) total_day-=11;
            }
        }
        //end 12/31 to end target
        if(start.year>rear.year)
        {
            for(int mi=12;mi>=rear.month+1;mi--)
            {
                total_day+=month_day[mi];
                //leap
                if(is_leap(rear.year)&&mi==2) total_day+=1;
                //special cover the non-existent days
                if(start.year==1582&&mi==10) total_day-=10;
                if(start.year==1752&&mi==9) total_day-=11;
            }
            for(int di=month_day[rear.month];di>=rear.day;di--) total_day++;
            //leap
            if(is_leap(rear.year)&&rear.month==2) total_day+=1;
            //special cover the non-existent days
            if(rear.year==1582&&rear.month==10&&rear.day<=4&&month_day[rear.month]>=15) total_day-=10;
            if(rear.year==1752&&rear.month==9&&rear.day<=2&&month_day[rear.month]>=14) total_day-=11;
        }
        //calculate the rear's week according to total days
        rear.week=week_mod(week_sub(start.week,week_mod(total_day,7)),7);
    }
    else if(flag<0)
    {
        int total_day=0;
        //start target to end 12/31 the start.day is not in total days not in Dis
        if(start.year<rear.year)
        {
            //complete day
            for(int di=start.day+1;di<=month_day[start.month];di++) total_day++;
            //leap
            if(is_leap(start.year)&&start.month==2) total_day+=1;
            //special cover the non-existent days
            if(start.year==1582&&start.month==10&&month_day[start.month]>=15&&start.day<=4) total_day-=10;
            if(start.year==1752&&start.month==9&&month_day[start.month]>=14&&start.day<=2) total_day-=11;
            //complete month
            for(int mi=start.month+1;mi<=12;mi++)
            {
                total_day+=month_day[mi];
                //leap
                if(is_leap(start.month)&&mi==2) total_day+=1;
                //special cover the non-existent days
                if(start.year==1582&&mi==10) total_day-=10;
                if(start.year==1752&&mi==9) total_day-=11;
            }
        }
        else if(start.year==rear.year)//the dis days is on the same year
        {
            //front
            if(start.month<rear.month)
            {
                for(int di=start.day+1;di<=month_day[start.month];di++) total_day++;
                //leap
                if(is_leap(start.year)&&start.month==2) total_day+=1;
                //special cover the non-existent days
                if(start.year==1582&&start.month==10&&month_day[start.month]>=15&&start.day<=4) total_day-=10;
                if(start.year==1752&&start.month==9&&month_day[start.month]>=14&&start.day<=2) total_day-=11;
            }
            else if(start.month==rear.month)
            {
                for(int di=start.day+1;di<=rear.day;di++) total_day++;
                //special cover the non-existent days
                if(start.year==1582&&start.month==10&&rear.day>=15&&start.day<=4) total_day-=10;
                if(start.year==1752&&start.month==9&&rear.day>=14&&start.day<=2) total_day-=11;
            }
            //middle
            if(start.month+1<rear.month)
            {
                for(int mi=start.month+1;mi<=rear.month-1;mi++)
                {
                    total_day+=month_day[mi];
                    //leap
                    if(is_leap(start.year)&&mi==2) total_day+=1;
                    //special cover the non-existent days
                    if(start.year==1582&&mi==10) total_day-=10;
                    if(start.year==1752&&mi==9) total_day-=11;
                }
            }
            //rear
            if(start.month<rear.month)
            {
                for(int di=1;di<=rear.day;di++) total_day++;
                //special cover the non-existent days
                if(rear.year==1582&&rear.month==10&&1<=4&&rear.day>=15) total_day-=10;
                if(rear.year==1752&&rear.month==9&&1<=2&&rear.day>=14) total_day-=11;
            }
        }
        //start to end  complete year
        if(start.year+1<rear.year)
        {
            for(int yi=start.year+1;yi<=rear.year-1;yi++) 
            {
                total_day+=is_leap(yi)? 366 : 365;
                //special cover the non-existent days
                if(yi==1582) total_day-=10;
                if(yi==1752) total_day-=11;
            }
        }
        //end 12/31 to end target
        if(start.year<rear.year)
        {
            for(int mi=1;mi<=rear.month-1;mi++)
            {
                total_day+=month_day[mi];
                //leap
                if(is_leap(rear.year)&&mi==2) total_day+=1;
                //special cover the non-existent days
                if(start.year==1582&&mi==10) total_day-=10;
                if(start.year==1752&&mi==9) total_day-=11;
            }
            for(int di=1;di<=rear.day;di++) total_day++;
            //special cover the non-existent days
            if(rear.year==1582&&rear.month==10&&1<=4&&rear.day>=15) total_day-=10;
            if(rear.year==1752&&rear.month==9&&1<=2&&rear.day>=14) total_day-=11;
        }
        //calculate the rear's week according to total days
        rear.week=week_mod(week_add(start.week,week_mod(total_day,7)),7);
    }
    else//start == rear
    {
        rear.week=start.week;
    }
    return(0);
}
bool is_valid_date(date a)
{
    if(a.year<=0) return(false);
    if(a.month<=0||a.month>=13) return(false);
    if(!is_leap(a.year)&&(a.day<=0||a.day>month_day[a.month])) return(false);
    if(is_leap(a.year)&&(a.day<=0||a.day>leap_month_day[a.month])) return(false);
    return(true);
}
int main()
{
    special_date[1].year=1582;special_date[1].month=10;special_date[1].day=4;special_date[1].week=4;
    special_date[2].year=1582;special_date[2].month=10;special_date[2].day=15;special_date[2].week=5;
    special_date[3].year=1752;special_date[3].month=9;special_date[3].day=2;special_date[3].week=3;
    special_date[4].year=1752;special_date[4].month=9;special_date[4].day=14;special_date[4].week=4;
    date_start.year=2014;date_start.month=9;date_start.day=9;date_start.week=2;
    while(scanf("%d%d%d",&in_month,&in_day,&in_year)!=EOF&&(in_year+in_month+in_day)>0)
    {
        date date_end;
        date_end.year=in_year;
        date_end.month=in_month;
        date_end.day=in_day;
        if(is_valid_date(date_end))
        {
            get_week(date_start,date_end);
            printf("%s %d, %d is a %s\n",month_map[date_end.month],date_end.day,date_end.year,week_map[date_end.week]);
        }
        else
        {
            printf("%d/%d/%d is an invalid date.\n",date_end.month,date_end.day,date_end.year);
        }
    }
    return(0);
}
