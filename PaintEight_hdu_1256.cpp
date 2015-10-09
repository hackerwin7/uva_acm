#include <stdio.h>
#define M 6
int N=0,h=0;
char c[10];
int  main()
{
	while(scanf("%d",&N)!=EOF)
	{
		int cases=0;
		while(N--)
		{
			scanf("%s%d",c,&h);
			if(cases++ > 0) printf("\n");
			if(h<5) {printf("\n");continue;}
			int verti_width=0,horiz_width=0,up_height=0,down_height=0;
			verti_width=h/6+1;
			down_height=(h-3)%2==0? (h-3)/2 : (h-3)/2 + 1;
			horiz_width=down_height;
			up_height=h-3-down_height;
			//first line
			for(int i=1;i<=verti_width;i++) printf(" ");
			for(int i=1;i<=horiz_width;i++) printf("%c",c[0]);
			printf("\n");
			//up_height
			for(int i=1;i<=up_height;i++)
			{
				for(int j=1;j<=verti_width;j++) printf("%c",c[0]);
				for(int j=1;j<=horiz_width;j++) printf(" ");
				for(int j=1;j<=verti_width;j++) printf("%c",c[0]);
				printf("\n");
			}
			//middle line
			for(int i=1;i<=verti_width;i++) printf(" ");
			for(int i=1;i<=horiz_width;i++) printf("%c",c[0] );
			printf("\n");
			//down_height
			for(int i=1;i<=down_height;i++)
			{
				for(int j=1;j<=verti_width;j++) printf("%c",c[0]);
				for(int j=1;j<=horiz_width;j++) printf(" ");
				for(int j=1;j<=verti_width;j++) printf("%c",c[0]);
				printf("\n");
			}
			//last line
			for(int i=1;i<=verti_width;i++) printf(" ");
			for(int i=1;i<=horiz_width;i++) printf("%c", c[0]);
			printf("\n");
		}
	}
	return(0);
}